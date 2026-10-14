#!/usr/bin/env python3
"""Compare the shipped item body against retail, executing retail collaborators.

Reuses the bounded historical fixture but inserts the *relocated production
bytes* into the oracle image. This checks the interface with the real callees,
which a separately linked candidate and its compiler-derived ABIs cannot check.
Animation ticking, PowerChanged, allocation and terminal conversion retain the
fixture's scripted boundaries. This is not a complete gameplay/replay test.
"""
import argparse
from dataclasses import asdict
import hashlib
import importlib.util
import json
from pathlib import Path
import struct
import sys

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from matching2.tools.common.pe import PEImage


def load_fixture():
    path = ROOT / 'matching2/reference/semantic_candidates/player_item_update_0041afd0/item_update_differential.py'
    spec = importlib.util.spec_from_file_location('historical_item_fixture', path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module, path


def replace_body(retail, body):
    data = bytearray(retail.data)
    for section in retail.sections:
        offset = 0x41AFD0 - section['address']
        if 0 <= offset and offset + len(body) <= section['raw_size']:
            start = section['raw_offset'] + offset
            data[start:start + len(body)] = body
            return PEImage(bytes(data))
    raise ValueError('oracle does not contain the item region')


def motion(observation):
    return [dict(position=struct.unpack_from('<3f', bytes.fromhex(item), 0x3AC),
                 velocity=struct.unpack_from('<3f', bytes.fromhex(item), 0x3B8),
                 state=struct.unpack_from('<I', bytes.fromhex(item), 0x3DC)[0])
            for item in observation['active_items']]


def execute(fixture, image, case):
    # Capture the machine without changing the historical fixture or its
    # scripted boundaries. Observe the player too: an incorrect receiver can
    # corrupt it while leaving the intended velocity record untouched.
    factory = fixture.Uc
    machines = []

    def capture(*args, **kwargs):
        machine = factory(*args, **kwargs)
        machines.append(machine)
        return machine

    fixture.Uc = capture
    try:
        observation = fixture.run(image, None, {}, case)
    finally:
        fixture.Uc = factory
    machine = machines[0]
    for name, address, size in [('player', fixture.PLAYER, 0x10000),
                                ('movement', fixture.MOVEMENT, 0x1000),
                                ('blocker', fixture.BLOCKER, 0x1000),
                                ('resource', fixture.RESOURCE, 0x10000),
                                ('bank', fixture.BANK, 0x400000)]:
        observation[name + '_sha256'] = hashlib.sha256(machine.mem_read(address, size)).hexdigest()
    for section in image.sections:
        if section['characteristics'] & 0x80000000:
            observation[section['name'] + '_sha256'] = hashlib.sha256(
                machine.mem_read(section['address'], section['virtual_size'])).hexdigest()
    return observation


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--oracle', type=Path, default=ROOT / 'matching2/build/oracle/th10.exe')
    parser.add_argument('--candidate', type=Path, default=ROOT / 'matching2/build/msvc/th10.exe')
    parser.add_argument('--draft-body', type=Path, help='emulate an oversized relocated draft; never install it in a game executable')
    parser.add_argument('--report', type=Path, default=ROOT / 'matching2/build/behavior/item-update.json')
    args = parser.parse_args()
    fixture, fixture_path = load_fixture()
    retail = PEImage(args.oracle.read_bytes())
    shipped = PEImage(args.candidate.read_bytes())
    body = args.draft_body.read_bytes() if args.draft_body else shipped.read(0x41AFD0, 2320)
    # Oversized drafts may overlap the next draw callback, which this bounded
    # fixture never calls. Do not allow them to overwrite ConvertItems.
    if len(body) > 0x41BA50 - 0x41AFD0:
        parser.error('draft overlaps a collaborator')
    isolated = replace_body(retail, body)
    failures, passed = [], 0
    cases = list(fixture.cases())
    for index, case in enumerate(cases):
        observations = []
        for label, image in [('retail', retail), ('candidate', isolated)]:
            try:
                observations.append(execute(fixture, image, case))
            except Exception as error:
                observations.append({'execution_error': repr(error), 'side': label})
        expected, actual = observations
        if 'execution_error' in expected or 'execution_error' in actual:
            failures.append(dict(case=asdict(case), retail=expected, candidate=actual))
        elif expected != actual:
            changed = [key for key in expected if expected[key] != actual[key]]
            failures.append(dict(case=asdict(case), changed=changed,
                                 retail_motion=motion(expected), candidate_motion=motion(actual),
                                 retail={key: expected[key] for key in changed},
                                 candidate={key: actual[key] for key in changed}))
        else:
            passed += 1
        if index % 50 == 0:
            print(f'{index + 1}/{len(cases)}: {passed} passed, {len(failures)} failed', flush=True)
    report = dict(scope=__doc__, cases=len(cases), passed=passed, failed=len(failures),
                  oracle_sha256=hashlib.sha256(retail.data).hexdigest(),
                  candidate_sha256=hashlib.sha256(shipped.data).hexdigest(),
                  candidate_body_sha256=hashlib.sha256(body).hexdigest(),
                  draft_body=str(args.draft_body) if args.draft_body else None,
                  body_bytes=len(body), fits_region=len(body) <= 2320,
                  fixture_sha256=hashlib.sha256(fixture_path.read_bytes()).hexdigest(), failures=failures)
    args.report.parent.mkdir(parents=True, exist_ok=True)
    args.report.write_text(json.dumps(report, indent=2) + '\n')
    print(f'{passed}/{len(cases)} passed; {len(failures)} failed; report: {args.report}')
    return int(bool(failures))


if __name__ == '__main__':
    sys.exit(main())
