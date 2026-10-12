#!/usr/bin/env python3
"""Build and verify C++ recoveries that match retail except for recorded, reviewed differences.

Some functions cannot be reproduced byte-for-byte because the compiler breaks
ties with state the binary does not record (see the note each layout names).
Their region keeps its ``asm`` source for the exact link, and an entry under
``equivalent_recoveries`` in ``regions.json`` names a layout describing the
C++.  This tool compiles the C++ in a native ``/LTCG`` link, relocates the
function to the region's address (the bytes the default build ships), compares
them with the exact region instruction by instruction, and accepts only:

* ``base-index-order``: ``[a+b*1+d]`` against ``[b+a*1+d]``, the same address
  with the two registers encoded in the other order.  Recognised by rule; the
  layout records how many are expected.
* ``frame-offset``: the same instruction addressing its stack slot a fixed
  distance away, for functions whose frame is a different size.  Recognised by
  rule: the layout's optional ``frame_shift`` names the distances allowed and
  how many instructions are expected to differ this way.
* differences listed verbatim in the layout, each with a reviewed class.  A
  run of instructions that only sits elsewhere in the function (a deletion and
  an insertion with the same text, each closed by a jump or return) is still
  listed, but its instructions are paired so branches into it are followed.

Listing a difference does not make it acceptable.  Whatever the layout records,
a model fails when

* it calls a function retail does not call from this region, or the reverse;
* it names an image address (a global, a constant, a function pointer) retail
  does not name, or the reverse;
* a recorded difference replaces calls by the same number of calls to other
  functions;
* a difference of a tie-break class (every class outside ``STRUCTURAL_CLASSES``)
  adds or removes a call, a branch or a return;
* the structural differences cover more than ``STRUCTURAL_BUDGET`` of the
  region's instructions, or all differences more than ``TOTAL_BUDGET``.

A model outside these limits is a draft: its layout may stay under
``layout/equivalent/`` for ``--layout`` measurements, but it is not registered
in ``equivalent_recoveries``, is not built into the executable, and is not
counted as recovered.

A branch or jump-table entry must reach the instruction its counterpart
reaches.  Where the two compilations merged identical tails differently, the
targets are also accepted when the code from each runs the same instructions
(following unconditional jumps, and with every further branch held to the same
test) up to a return or to a pair of instructions already aligned.  A layout may
set ``listed_branch_targets``; a branch or table entry that still cannot be
shown to reach the same code is then a listed difference of class
``branch-target``, spelled with both destinations, instead of a failure.

Anything else, or any drift from the recorded set, fails.
"""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

import argparse
import difflib
import json
import re
import shutil
import struct
import subprocess
import tempfile

from matching2.tools.common.pe import PEImage
from matching2.tools.common.process import sha
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath
from matching2.tools.matching.ltcg_cluster import _absolute_object

ROOT = Path(__file__).resolve().parents[3]
DEFAULT_PROJECT = ROOT / 'matching2/msvc'
DEFAULT_OUTPUT = ROOT / 'matching2/build/msvc'
TEXT_START, IMAGE_BASE = 0x401000, 0x400000
# The model is linked a second time here; the fields that move with it are its absolute references.
SECOND_BASE = 0x10000000
# Bound code symbols are shifted by this much in the second link, which tells a function's address stored as
# data (it moves by the shift alone) from a relative call to it and from an address inside the image.
CODE_SHIFT = 0x00100000
# Share of the region's instructions that recorded differences may cover (see the module text).
STRUCTURAL_CLASSES = {'block-order', 'branch-target', 'code-shape'}
STRUCTURAL_BUDGET = 0.125
TOTAL_BUDGET = 1 / 3
# Addresses a model may only name where retail names them: everything the image maps above its headers.
IMAGE_END = 0x01000000
LISTED_CLASSES = {
    'stack-slot-order': 'two locals occupy each other\'s frame slots',
    'operand-order': 'a commutative sum is evaluated in another order',
    'register-choice': 'a short-lived value is held in another scratch or saved register',
    'evaluation-order': 'independent argument or operand loads are emitted in another order',
    'block-order': 'a basic block ending in a jump or return is placed elsewhere',
    'branch-target': 'a branch or table entry enters a differently merged tail; the two destinations were compared by hand',
    'code-shape': 'the same values reach the same places through another instruction sequence: a copy through an integer '
                  'or an x87 register, a read-modify-write folded or split, a shared tail duplicated or merged',
    'alignment-padding': 'loop-alignment filler of another length, a consequence of the other differences',
}
TABLE_JUMP = re.compile(rb'\xff\x24[\x85\x8d\x95\x9d\xad\xb5\xbd](....)', re.DOTALL)
SIB = re.compile(r'\[(e[a-z]{2})\+(e[a-z]{2})\*1((?:[+-]0x[0-9a-f]+)?)\]')
HEX = re.compile(r'0x[0-9a-f]+')
CALL = re.compile(r'call (0x[0-9a-f]+)$')
FLOW = re.compile(r'(?:call|ret|j[a-z]+)\b')
REGISTER = re.compile(r'\be(?:[abcd]x|[sd]i|bp)\b')
ESP_SLOT = re.compile(r'\[esp(?:\+(0x[0-9a-f]+))?\]')
BRANCH = re.compile(r'(?:call|j[a-z]+) 0x([0-9a-f]+)$')
MAP_SYMBOL = re.compile(r'^\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(?:f\s+)?(?:i\s+)?(\S+)', re.MULTILINE)


class EquivalenceError(ValueError):
    """A model is missing, malformed, or differs beyond its recorded set."""


def canonical_sib(text):
    """Spell a scale-1 two-register operand with its registers in sorted order."""
    return SIB.sub(lambda m: '[' + '+'.join(sorted((m[1], m[2]))) + '*1' + m[3] + ']', text)


def load_recoveries(project, config, regions):
    """Read and validate every equivalent recovery the manifest declares."""
    by_name = {region['name']: region for region in regions}
    recoveries, seen = [], set()
    for entry in config.get('equivalent_recoveries', []):
        if set(entry) != {'region', 'layout'}:
            raise EquivalenceError('an equivalent recovery names exactly a region and a layout')
        region = by_name.get(entry['region'])
        if region is None or region['kind'] != 'asm':
            raise EquivalenceError('equivalent recovery must name an assembly region: ' + str(entry['region']))
        if entry['region'] in seen:
            raise EquivalenceError('duplicate equivalent recovery: ' + entry['region'])
        seen.add(entry['region'])
        path = (project / entry['layout']).resolve()
        if not path.is_relative_to(project) or path.suffix != '.json':
            raise EquivalenceError('equivalent layout must be a project JSON file: ' + entry['layout'])
        layout = json.loads(path.read_text())
        required = {'schema_version', 'name', 'region', 'sources', 'entry_symbol', 'function',
                    'code_bytes', 'absolute_symbols', 'bindings', 'base_index_order', 'differences', 'note'}
        frame = layout.get('frame_shift')
        if frame is not None and (set(frame) != {'deltas', 'count'} or not frame['deltas']
                                  or not all(isinstance(delta, int) and delta for delta in frame['deltas'])):
            raise EquivalenceError('malformed frame shift in ' + entry['layout'])
        if layout.get('listed_branch_targets', True) is not True:
            raise EquivalenceError('listed_branch_targets is true or absent in ' + entry['layout'])
        if set(layout) - {'frame_shift', 'listed_branch_targets', 'context_cluster', 'context_sources', 'roots'} != required or layout['schema_version'] != 1 or layout['region'] != entry['region']:
            raise EquivalenceError('malformed equivalent layout: ' + entry['layout'])
        if not 0 < layout['code_bytes'] <= region['size']:
            raise EquivalenceError('code extent exceeds the region: ' + entry['layout'])
        sources = []
        for source in layout['sources']:
            source_path = (project / source).resolve()
            if not source_path.is_relative_to(project / 'equivalent') or source_path.suffix != '.cpp':
                raise EquivalenceError('model sources live under equivalent/: ' + source)
            sources.append(source_path)
        # Recovered sources of the callees, linked in so that the whole-program link derives the
        # register conventions retail has for them. They are context only; nothing of theirs is compared.
        # A source that needs more than the project flags (exception handling) is written
        # {"source": ..., "flags": [...]}.
        extra_flags = {}
        for item in layout.get('context_sources', []):
            source = item['source'] if isinstance(item, dict) else item
            source_path = (project / source).resolve()
            if not source_path.is_relative_to(project) or source_path.suffix != '.cpp':
                raise EquivalenceError('context sources are project C++ files: ' + source)
            if isinstance(item, dict):
                if set(item) != {'source', 'flags'} or not all(isinstance(flag, str) for flag in item['flags']):
                    raise EquivalenceError('malformed context source in ' + entry['layout'])
                extra_flags[source_path] = item['flags']
            sources.append(source_path)
        if 'context_cluster' in layout:
            sources = cluster_context(project, layout['context_cluster'], sources, entry['layout'])
        for item in layout['differences']:
            if set(item) != {'class', 'offset', 'retail', 'model'} or item['class'] not in LISTED_CLASSES:
                raise EquivalenceError('malformed recorded difference in ' + entry['layout'])
        recoveries.append({**layout, 'path': path, 'source_paths': sources, 'source_flags': extra_flags,
                           'region_record': region,
                           'address': int(region['address'], 0), 'size': region['size']})
    return recoveries


def cluster_context(project, name, models, where):
    """The model sources with the driver and context sources of a whole-program cluster, in cluster order.

    The compiler's choices depend on the order its inputs are given in, so the
    model sources keep the position the cluster gives them; any the cluster
    does not name come first.
    """
    path = (project / name).resolve()
    if not path.is_relative_to(project / 'layout/ltcg') or path.suffix != '.json':
        raise EquivalenceError('context cluster must be a layout/ltcg JSON file: ' + where)
    cluster = json.loads(path.read_text())
    context = []
    for source in [cluster['driver'], *cluster.get('additional_sources', [])]:
        source_path = (project / source).resolve()
        if not source_path.is_relative_to(project) or source_path.suffix != '.cpp':
            raise EquivalenceError('context cluster source must be a project C++ file: ' + source)
        context.append(source_path)
    return [model for model in models if model not in context] + context


def build_model(recovery, project, toolkit, flags, work):
    """Compile the model sources with /GL and link them natively; return the image and map text."""
    env = compiler_environment(toolkit, include_library=True)
    objects = []
    for index, source in enumerate(recovery['source_paths']):
        obj = work / f'model_{index:02d}.obj'
        command = ['wine', str(toolkit / 'bin/cl.exe'), *flags, *recovery.get('source_flags', {}).get(source, []),
                   '/GL', '/I' + winpath(project / 'include'),
                   '/Fo' + winpath(obj), winpath(source)]
        result = subprocess.run(command, env=env, cwd=work, capture_output=True, text=True, timeout=180)
        if result.returncode or not obj.is_file():
            raise EquivalenceError(f'model compilation failed for {source.name}:\n{result.stdout[-2000:]}')
        objects.append(obj)
    for stem, shift in (('model', 0), ('moved', CODE_SHIFT)):
        _absolute_object(work / (stem + '_bindings.obj'), [
            {'symbol': name, 'kind': 'relative_code' if item['kind'] == 'code' else 'data',
             'coff_value': int(item['address'], 0) - (IMAGE_BASE - shift if item['kind'] == 'code' else 0)}
            for name, item in sorted(recovery['absolute_symbols'].items())])
    entry = recovery['entry_symbol']
    images = []
    for base, stem in ((IMAGE_BASE, 'model'), (SECOND_BASE, 'moved')):
        executable, map_path = work / (stem + '.exe'), work / (stem + '.map')
        command = ['wine', str(toolkit / 'bin/link.exe'), '/nologo', '/LTCG', '/MACHINE:X86',
                   f'/BASE:{base:#x}', '/SUBSYSTEM:WINDOWS', '/ENTRY:' + (entry[1:] if entry.startswith('_') else entry),
                   '/FIXED', '/INCREMENTAL:NO', '/NODEFAULTLIB', '/OPT:REF', '/OPT:NOICF',
                   # Context sources built with exception handling carry handler tables.
                   *(['/SAFESEH:NO'] if recovery.get('source_flags') else []),
                   '/OUT:' + winpath(executable), '/MAP:' + winpath(map_path),
                   *[winpath(obj) for obj in objects], winpath(work / (stem + '_bindings.obj')),
                   # Functions the link keeps besides the entry, so that shared callees see every caller.
                   *['/INCLUDE:' + root for root in recovery.get('roots', [])]]
        result = subprocess.run(command, env=env, cwd=work, capture_output=True, text=True, timeout=300)
        if result.returncode or not executable.is_file():
            raise EquivalenceError('model link failed:\n' + (result.stdout + result.stderr)[-3000:])
        images.append(executable.read_bytes())
    return images[0], (work / 'model.map').read_text(errors='replace'), images[1]


def disassemble(data, address, work, name):
    """Return [(offset, text)] for raw code loaded at ``address``."""
    path = work / (name + '.bin')
    path.write_bytes(data)
    listing = subprocess.run(
        ['i686-w64-mingw32-objdump', '-D', '-b', 'binary', '-m', 'i386', '-M', 'intel',
         '--no-show-raw-insn', f'--adjust-vma={address:#x}', str(path)],
        capture_output=True, text=True, check=True).stdout
    rows = []
    for line in listing.splitlines():
        match = re.match(r'\s*([0-9a-f]+):\t(.*)', line)
        if match:
            rows.append((int(match[1], 16) - address, re.sub(r'\s+', ' ', match[2].strip())))
    return rows


def normalize(rows, start, code_bytes, size, rebind):
    """Return [(offset, text, targets)] with in-function addresses made position independent.

    Code targets become ``L`` placeholders whose offsets are returned separately,
    so they can be compared through the instruction alignment; table references
    become offsets from the table start; bound model symbols become retail addresses.
    """
    result = []
    for offset, text in rows:
        targets = []

        def replace(match):
            value = int(match[0], 16)
            if start <= value < start + code_bytes:
                targets.append(value - start)
                return 'L'
            if start + code_bytes <= value < start + size:
                return f'T+{value - start - code_bytes:#x}'
            return rebind(value, match[0])
        result.append((offset, HEX.sub(replace, text), tuple(targets)))
    return result


def render(row):
    """Spell one normalised instruction with its own side's target offsets."""
    targets = iter(row[2])
    return re.sub(r'\bL\b', lambda match: f'L+{next(targets):#x}', row[1])


def slot_offsets(text):
    return [int(match[1] or '0', 16) for match in ESP_SLOT.finditer(text)]


class Alignment(dict):
    """Retail-to-model instruction offsets, with a test for targets that run the same code."""

    reaches = None


def reaches(mapping, target, model_target):
    if mapping.get(target) == model_target:
        return True
    test = getattr(mapping, 'reaches', None)
    return bool(test and test(target, model_target))


def find_differences(retail_rows, model_rows, frame_deltas=(), counts=None, list_branches=False):
    """Return (base/index swap count, other differences as hunks, retail-to-model offset map).

    With ``frame_deltas``, instructions are aligned with their stack-slot offsets
    masked; a pair whose slots lie one of those distances apart (retail minus
    model) is counted in ``counts['frame']`` rather than listed.
    """
    def key(text):
        text = canonical_sib(text)
        return ESP_SLOT.sub('[esp+S]', text) if frame_deltas else text
    retail_key = [key(row[1]) for row in retail_rows]
    model_key = [key(row[1]) for row in model_rows]
    shifted = 0
    swaps, hunks, pairs, inserted, deleted, entries = 0, [], [], [], [], {}
    matcher = difflib.SequenceMatcher(None, retail_key, model_key, autojunk=False)
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == 'equal':
            pairs.extend((i1 + k, j1 + k) for k in range(i2 - i1))
            for k in range(i2 - i1):
                retail_text, model_text = retail_rows[i1 + k][1], model_rows[j1 + k][1]
                if retail_text == model_text:
                    continue
                moved = {a - b for a, b in zip(slot_offsets(retail_text), slot_offsets(model_text))} - {0}
                if moved - set(frame_deltas):
                    hunks.append({'offset': f'{retail_rows[i1 + k][0]:#x}', 'retail': [render(retail_rows[i1 + k])],
                                  'model': [render(model_rows[j1 + k])]})
                    continue
                shifted += bool(moved)
                swaps += ESP_SLOT.sub('S', retail_text) != ESP_SLOT.sub('S', model_text)
            continue
        # A run replaced by one of the same shape stays in step; otherwise only its start does.
        if i2 - i1 == j2 - j1:
            pairs.extend((i1 + k, j1 + k) for k in range(i2 - i1))
        elif i1 < i2 and j1 < j2:
            pairs.append((i1, j1))
        hunks.append({'offset': f'{retail_rows[min(i1, len(retail_rows) - 1)][0]:#x}',
                      'retail': [render(row) for row in retail_rows[i1:i2]],
                      'model': [render(row) for row in model_rows[j1:j2]]})
        if i1 == i2:
            inserted.append((j1, j2))
            # A branch to the instruction after an insertion may enter at the insertion.
            if i1 < len(retail_rows):
                entries.setdefault(retail_rows[i1][0], set()).add(model_rows[j1][0])
        elif j1 == j2:
            deleted.append((i1, i2))
            # A branch into a removed run may land where the model resumes.
            if j1 < len(model_rows):
                for row in retail_rows[i1:i2]:
                    entries.setdefault(row[0], set()).add(model_rows[j1][0])

    def closed(rows, index):
        return index >= 0 and rows[index][1].split()[0] in ('jmp', 'ret')
    # A block placed elsewhere: the same text removed in one place and added in another.
    for i1, i2 in deleted:
        for j1, j2 in inserted:
            if (retail_key[i1:i2] == model_key[j1:j2] and closed(retail_rows, i2 - 1) and closed(retail_rows, i1 - 1)
                    and closed(model_rows, j1 - 1)):
                pairs.extend((i1 + k, j1 + k) for k in range(i2 - i1))
                inserted.remove((j1, j2))
                break
    mapping = Alignment({retail_rows[i][0]: model_rows[j][0] for i, j in pairs})
    retail_at = {row[0]: index for index, row in enumerate(retail_rows)}
    model_at = {row[0]: index for index, row in enumerate(model_rows)}
    allowed = set(frame_deltas) | {0}

    def same_code(target, model_target, assumed=frozenset()):
        """Whether execution from the two offsets runs the same instructions to a return or an aligned pair."""
        assumed = set(assumed)
        for _ in range(4096):
            if mapping.get(target) == model_target or model_target in entries.get(target, ()):
                return True
            if (target, model_target) in assumed:
                return True
            assumed.add((target, model_target))
            i, j = retail_at.get(target), model_at.get(model_target)
            if i is None or j is None:
                return False
            # An unconditional jump only moves the point of execution.
            if retail_rows[i][1] == 'jmp L':
                target = retail_rows[i][2][0]
                assumed.discard((target, model_target))
                continue
            if model_rows[j][1] == 'jmp L':
                model_target = model_rows[j][2][0]
                assumed.discard((target, model_target))
                continue
            if retail_key[i] != model_key[j]:
                return False
            if {a - b for a, b in zip(slot_offsets(retail_rows[i][1]), slot_offsets(model_rows[j][1]))} - allowed:
                return False
            mnemonic = retail_rows[i][1].split()[0]
            if mnemonic == 'ret':
                return True
            if mnemonic == 'jmp' or i + 1 >= len(retail_rows) or j + 1 >= len(model_rows):
                return False  # an indirect jump is compared only where the two are aligned
            for branch, model_branch in zip(retail_rows[i][2], model_rows[j][2]):
                if not same_code(branch, model_branch, frozenset(assumed)):
                    return False
            target, model_target = retail_rows[i + 1][0], model_rows[j + 1][0]
        return False
    mapping.reaches = same_code
    for i, j in pairs:
        if retail_key[i] != model_key[j]:
            continue
        for target, model_target in zip(retail_rows[i][2], model_rows[j][2]):
            if not same_code(target, model_target):
                if list_branches:
                    hunks.append({'offset': f'{retail_rows[i][0]:#x}', 'retail': [render(retail_rows[i])],
                                  'model': [render(model_rows[j])]})
                    break
                raise EquivalenceError(f'branch at +{retail_rows[i][0]:#x} reaches a different instruction '
                                           f'(+{target:#x} against +{model_target:#x})')
    if counts is not None:
        counts['frame'] = shifted
    hunks.sort(key=lambda hunk: int(hunk['offset'], 16))
    return swaps, hunks, mapping


def absolute_sites(first, second, delta):
    """Offsets of the 32-bit fields that follow the image when it is linked at another base.

    Returns them with the offsets of the fields holding the address of a bound
    code symbol, which the first link wrote without the image base.
    """
    if len(first) != len(second):
        raise EquivalenceError('the model links to different sizes at different bases')
    sites, code_sites, cursor = [], [], 0
    while cursor < len(first):
        if first[cursor] == second[cursor]:
            cursor += 1
            continue
        # The two bases differ only in their upper half, so a field changes from its third byte.
        site = cursor - 2
        if site < 0 or site + 4 > len(first):
            raise EquivalenceError('unexplained difference between the two model links')
        moved = (struct.unpack_from('<I', second, site)[0] - struct.unpack_from('<I', first, site)[0]) & 0xffffffff
        if moved == delta:
            sites.append(site)
        elif moved == CODE_SHIFT:
            code_sites.append(site)
        elif moved != (CODE_SHIFT - delta) & 0xffffffff:  # a relative branch to a bound code symbol
            raise EquivalenceError('unexplained difference between the two model links')
        cursor = site + 4
    return sites, code_sites


def relocate(pe, moved, rows, model_start, model_code, tail, start, bound, own):
    """Return the model function's bytes as they must read at the retail address.

    Addresses inside the function move with it; bound model symbols become
    their retail addresses; anything else the link already resolved to an
    absolute retail address.  Only relocation sites and out-of-function
    relative branches are rewritten.
    """
    total = model_code + tail
    body = bytearray(pe.read(model_start, total))

    def retail_address(value):
        if model_start <= value < model_start + total:
            return start + value - model_start
        if value in bound:
            return bound[value]
        if own and own[0] <= value < own[-1] + 0x40:
            # A field of a bound object: the same displacement from its retail address.
            base = max((address for address in own if address <= value), default=None)
            if base in bound and 0 < value - base < 0x40:
                return bound[base] + value - base
            raise EquivalenceError(f'model references an unbound symbol at {value:#x}')
        return value

    delta = SECOND_BASE - IMAGE_BASE
    sites, code_sites = absolute_sites(body, moved.read(model_start + delta, total), delta)
    for offset in sites:
        struct.pack_into('<I', body, offset, retail_address(struct.unpack_from('<I', body, offset)[0]))
    for offset in code_sites:
        struct.pack_into('<I', body, offset, struct.unpack_from('<I', body, offset)[0] + IMAGE_BASE)
    for index, (offset, text) in enumerate(rows):
        match = BRANCH.match(text)
        if not match:
            continue
        target = int(match[1], 16)
        if model_start <= target < model_start + model_code:
            continue
        length = (rows[index + 1][0] if index + 1 < len(rows) else model_code) - offset
        if length < 5:
            raise EquivalenceError(f'short branch leaves the function at +{offset:#x}')
        struct.pack_into('<i', body, offset + length - 4, retail_address(target) - (start + offset + length))
    return bytes(body)


def external_references(rows):
    """Return (functions called, image addresses named) outside the region, from normalised instructions."""
    calls, addresses = set(), set()
    for _, text, _ in rows:
        match = CALL.search(text)
        for spelling in HEX.findall(text):
            if TEXT_START <= int(spelling, 16) < IMAGE_END:
                (calls if match and match[1] == spelling else addresses).add(spelling)
    return calls, addresses


def gate(recovery, retail_rows, model_rows, hunks, classes):
    """Return the reasons the model is not an equivalent recovery, whatever its layout records.

    ``classes`` gives the reviewed class of each hunk, or None while recording;
    unclassified hunks are held to the structural budget.
    """
    reasons = []
    for what, retail, model in zip(('calls', 'names'), external_references(retail_rows),
                                   external_references(model_rows)):
        if model - retail:
            reasons.append(f'the model {what} what retail does not: ' + ', '.join(sorted(model - retail)))
        if retail - model:
            reasons.append(f'retail {what} what the model does not: ' + ', '.join(sorted(retail - model)))
    structural = total = 0
    for index, hunk in enumerate(hunks):
        sides = [sorted(match[1] for match in map(CALL.search, hunk[side]) if match) for side in ('retail', 'model')]
        if sides[0] != sides[1] and len(sides[0]) == len(sides[1]):
            reasons.append(f'the difference at {hunk["offset"]} replaces {", ".join(sides[0])} by {", ".join(sides[1])}')
        kind = classes[index] if classes else 'code-shape'
        # An indirect call through another register is still the same call.
        flow = [sorted(REGISTER.sub('R', re.sub(r'L\+0x[0-9a-f]+', 'L', text)) for text in hunk[side] if FLOW.match(text))
                for side in ('retail', 'model')]
        if kind not in STRUCTURAL_CLASSES and flow[0] != flow[1]:
            reasons.append(f'the {kind} difference at {hunk["offset"]} changes calls or branches')
        weight = max(len(hunk['retail']), len(hunk['model']))
        total += weight
        structural += weight if kind in STRUCTURAL_CLASSES else 0
    count = len(retail_rows)
    if structural > STRUCTURAL_BUDGET * count:
        reasons.append(f'structural differences cover {structural} of {count} instructions '
                       f'({100 * structural / count:.1f}%, budget {100 * STRUCTURAL_BUDGET:.1f}%)')
    if total > TOTAL_BUDGET * count:
        reasons.append(f'recorded differences cover {total} of {count} instructions '
                       f'({100 * total / count:.1f}%, budget {100 * TOTAL_BUDGET:.1f}%)')
    return reasons


def compare_tail(retail, model, retail_start, model_start, code_bytes, mapping, unproven=None):
    """Jump tables after the code must agree once code pointers follow the alignment.

    With ``unproven`` a list, an entry whose destinations cannot be shown to run
    the same code is appended to it as a difference instead of failing.
    """
    if len(retail) != len(model):
        raise EquivalenceError('jump-table extent differs')
    cursor = 0
    while cursor < len(retail):
        if cursor + 4 <= len(retail):
            pointer = struct.unpack_from('<I', retail, cursor)[0] - retail_start
            if 0 <= pointer < code_bytes:
                target = struct.unpack_from('<I', model, cursor)[0] - model_start
                if not reaches(mapping, pointer, target) and unproven is not None:
                    unproven.append({'offset': f'table+{cursor:#x}', 'retail': [f'L+{pointer:#x}'],
                                     'model': [f'L+{target:#x}']})
                elif not reaches(mapping, pointer, target):
                    raise EquivalenceError(f'jump-table entry differs at table offset {cursor:#x}')
                cursor += 4
                continue
        if retail[cursor] != model[cursor]:
            raise EquivalenceError(f'jump-table data differs at table offset {cursor:#x}')
        cursor += 1


def verify_recovery(recovery, project, toolkit, flags, text, output, *, record=False):
    """Build one model and compare it with the built region; return a report."""
    start, size, code_bytes = recovery['address'], recovery['size'], recovery['code_bytes']
    retail = text[start - TEXT_START:start - TEXT_START + size]
    work_root = output / 'equivalent'
    work_root.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix=recovery['name'] + '-', dir=work_root))
    try:
        image, link_map, moved = build_model(recovery, project, toolkit, flags, work)
        symbols = {name: int(value, 16) for name, value, _ in MAP_SYMBOL.findall(link_map)}
        own = sorted(int(value, 16) for _, value, where in MAP_SYMBOL.findall(link_map) if where != '<absolute>')
        if recovery['function'] not in symbols:
            raise EquivalenceError('model function is absent from the link map: ' + recovery['function'])
        model_start = symbols[recovery['function']]
        # The model's code may be a few bytes longer or shorter; its tables follow its own code.
        window = b''
        for slack in (0x400, 0x100, 0):
            try:
                window = PEImage(image).read(model_start, size + slack)
                break
            except ValueError:
                continue
        tables = [value for value in (struct.unpack('<I', match[1])[0] for match in TABLE_JUMP.finditer(window))
                  if model_start < value <= model_start + size + 0x400]
        tail = size - code_bytes
        # The slack window can reach the code that follows this function in the
        # link.  When the retail region has no jump-table instruction and no
        # separate tail, the model cannot have one either -- the same function is
        # being compiled -- so every pattern in the window belongs to another
        # function and must not be taken as this one's table.
        if tail == 0 and not TABLE_JUMP.search(retail):
            tables = []
        model_code = min(tables) - model_start if tables else code_bytes
        # A draft may be measured while it is still too long; it cannot be built in.
        if model_code + tail > size and not record:
            raise EquivalenceError(f'{recovery["name"]}: the C++ body needs {model_code + tail} bytes; '
                                   f'the region has {size}')
        bound = {}
        for name, address in recovery['bindings'].items():
            if name not in symbols:
                raise EquivalenceError('bound model symbol is absent from the link map: ' + name)
            bound[symbols[name]] = int(address, 0)
        body = relocate(PEImage(image), PEImage(moved), disassemble(PEImage(image).read(model_start, model_code),
                                                    model_start, work, 'model'),
                        model_start, model_code, tail, start, bound, own)
        identity = lambda value, spelling: spelling
        retail_rows = normalize(disassemble(retail[:code_bytes], start, work, 'retail'),
                                start, code_bytes, size, identity)
        model_rows = normalize(disassemble(body[:model_code], start, work, 'body'),
                               start, model_code, model_code + tail, identity)
        frame, counts = recovery.get('frame_shift') or {'deltas': [], 'count': 0}, {}
        swaps, hunks, mapping = find_differences(retail_rows, model_rows, tuple(frame['deltas']), counts,
                                                  recovery.get('listed_branch_targets', False))
        unproven = [] if recovery.get('listed_branch_targets') else None
        compare_tail(retail[code_bytes:], body[model_code:], start, start, code_bytes, mapping, unproven)
        hunks.extend(unproven or [])
        body += b'\xcc' * (size - len(body))
    finally:
        shutil.rmtree(work, ignore_errors=True)
    listed = [{key: item[key] for key in ('offset', 'retail', 'model')} for item in recovery['differences']]
    changed = sum(len(hunk['retail']) for hunk in hunks)
    report = {'name': recovery['name'], 'region': recovery['region'], 'bytes': size,
              'instructions': len(retail_rows), 'identical': len(retail_rows) - swaps - changed - counts['frame'],
              'base_index_order': swaps, 'frame_offset': counts['frame'], 'listed_differences': len(hunks), 'listed_instructions': changed}
    report['code_bytes'] = model_code + tail
    if record:
        report['differences'] = hunks
        report['not_equivalent'] = gate(recovery, retail_rows, model_rows, hunks, None)
        if report['code_bytes'] > size:
            report['not_equivalent'].append(f'the C++ body needs {report["code_bytes"]} bytes; the region has {size}')
        return report, body
    if hunks != listed:
        raise EquivalenceError(
            f'{recovery["name"]}: differences are not the recorded set\n'
            + json.dumps({'unrecorded': [hunk for hunk in hunks if hunk not in listed],
                          'no_longer_present': [hunk for hunk in listed if hunk not in hunks]}, indent=2))
    if counts['frame'] != frame['count']:
        raise EquivalenceError(f'{recovery["name"]}: {counts["frame"]} frame-offset instructions, layout records '
                               f'{frame["count"]}')
    if swaps != recovery['base_index_order']:
        raise EquivalenceError(f'{recovery["name"]}: {swaps} base/index swaps, layout records '
                               f'{recovery["base_index_order"]}')
    reasons = gate(recovery, retail_rows, model_rows, hunks, [item['class'] for item in recovery['differences']])
    if reasons:
        raise EquivalenceError(f'{recovery["name"]} is a draft, not an equivalent recovery:\n  ' + '\n  '.join(reasons))
    return report, body


def verify_all(project, config, regions, toolkit, text, output):
    """Verify every declared equivalent recovery against the built .text bytes.

    Returns the reports and, per region name, the C++ body relocated to the
    region's address and padded to its size.  A result is reused only while
    the sources, the layout, this tool, the flags, and the region's built
    bytes are all unchanged.
    """
    reports, bodies = [], {}
    recoveries = load_recoveries(project, config, regions)
    if not recoveries:
        return reports, bodies
    shared = [Path(__file__).read_bytes(), json.dumps(config['flags']).encode(),
              *[path.read_bytes() for path in sorted((project / 'equivalent').rglob('*')) if path.is_file()]]
    for recovery in recoveries:
        offset = recovery['address'] - TEXT_START
        key = sha(b'\0'.join(sha(part).encode() for part in
                             [*shared, recovery['path'].read_bytes(), text[offset:offset + recovery['size']]]))
        cache = output / 'equivalent' / (recovery['name'] + '.json')
        stored = cache.with_suffix('.bin')
        if cache.is_file() and stored.is_file():
            saved = json.loads(cache.read_text())
            body = stored.read_bytes()
            if saved.get('key') == key and sha(body) == saved.get('body_sha256'):
                reports.append(saved['report'])
                bodies[recovery['region']] = body
                continue
        report, body = verify_recovery(recovery, project, toolkit, config['flags'], text, output)
        stored.write_bytes(body)
        cache.write_text(json.dumps({'key': key, 'report': report, 'body_sha256': sha(body)}, indent=2) + '\n')
        reports.append(report)
        bodies[recovery['region']] = body
    return reports, bodies


def apply_bodies(text, regions, bodies):
    """Return the .text image with each equivalent region built from its C++ body."""
    image = bytearray(text)
    for region in regions:
        body = bodies.get(region['name'])
        if body is None:
            continue
        if len(body) != region['size']:
            raise EquivalenceError('equivalent body does not fill its region: ' + region['name'])
        offset = int(region['address'], 0) - TEXT_START
        image[offset:offset + len(body)] = body
    return bytes(image)


def describe(report):
    return (f"{report['name']}: {report['code_bytes']:,} of {report['bytes']:,} bytes used, "
            f"{report['identical']:,} of {report['instructions']:,} instructions identical, "
            f"{report['base_index_order']} base/index swaps, {report.get('frame_offset', 0)} frame-offset, "
            f"{report['listed_instructions']} instructions in {report['listed_differences']} recorded differences")


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--toolkit', type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument('--output', type=Path, default=DEFAULT_OUTPUT)
    parser.add_argument('--name', help='verify only this recovery')
    parser.add_argument('--layout', help='measure a draft: a layout under layout/equivalent/ that is not registered '
                                         '(implies --record)')
    parser.add_argument('--record', action='store_true',
                        help='print the current differences for review instead of checking them')
    args = parser.parse_args()
    project, toolkit, output = args.project.resolve(), args.toolkit.resolve(), args.output.resolve()
    config = json.loads((project / 'regions.json').read_text())
    text_path = output / 'text.bin'
    if not text_path.is_file():
        parser.error('no built .text image; run make first')
    text = text_path.read_bytes()
    if sha(text) != config['text_sha256']:
        parser.error('built .text image is not the exact one')
    if args.layout:
        layout = json.loads((project / args.layout).read_text())
        config = {**config, 'equivalent_recoveries': [{'region': layout['region'], 'layout': args.layout}]}
        args.record = True
    recoveries = load_recoveries(project, config, config['regions'])
    if args.name:
        recoveries = [item for item in recoveries if item['name'] == args.name]
        if not recoveries:
            parser.error('no such equivalent recovery: ' + args.name)
    for recovery in recoveries:
        report, _ = verify_recovery(recovery, project, toolkit, config['flags'], text, output, record=args.record)
        if args.record:
            print(json.dumps(report, indent=2))
        else:
            print(describe(report))


if __name__ == '__main__':
    try:
        main()
    except EquivalenceError as error:
        sys.exit(f'equivalence check failed: {error}')
