"""Shared address space, ABI sentinels and loaders for differential x86 fixtures."""

from dataclasses import dataclass
from functools import cache
from pathlib import Path
import struct
import sys

from unicorn.x86_const import UC_X86_REG_EBX, UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI

# Standalone test scripts start with matching2/tests, not the repository, on sys.path.
ROOT = Path(__file__).resolve().parents[2]
if str(ROOT) not in sys.path:
    sys.path.insert(0, str(ROOT))

from matching2.tools.common.coff import function_body, read_object
from matching2.tools.common.project_paths import DEFAULT_PROJECT, project_support
from matching2.tools.matching.retail import load_manifest, load_verified_image, region_directory

CANDIDATE = 0x1000000
INPUT = 0x2000000
OUTPUT = 0x2100000
STACK = 0x2300000
STOP = 0x2400000
PRESERVED = {UC_X86_REG_EBX: 0x13579BDF, UC_X86_REG_EBP: 0x2468ACE0,
             UC_X86_REG_ESI: 0x12345678, UC_X86_REG_EDI: 0x87654321}


@dataclass(frozen=True)
class MaintainedRegion:
    source: Path
    symbol: str


@cache
def _region_owners():
    config = load_manifest(project_support(DEFAULT_PROJECT, 'regions.json'))
    return {int(r['address'], 0): MaintainedRegion(DEFAULT_PROJECT / r['source'], r['symbol'])
            for r in config['regions']}


def maintained_region(address):
    """Resolve a stable retail entry point without pinning a fixture to an old source path or symbol."""
    return _region_owners()[address]


def load_fixture(oracle):
    """Load the default project and require its retail text hash before emulation."""
    config = load_manifest(project_support(DEFAULT_PROJECT, 'regions.json'))
    image, _ = load_verified_image(oracle, config)
    return config, image


def load_candidate(path, config, requested_symbol, extra_bindings=None, code_address=CANDIDATE):
    """Relocate one external COFF function, binding dependencies to retail or fixture addresses."""
    function = function_body(read_object(path), requested_symbol, require_external=True)
    bindings = region_directory(config, config['regions'])
    if extra_bindings:
        bindings.update(extra_bindings)
    code = bytearray(function.data)
    for reloc in function.relocations:
        target = code_address + reloc.local if reloc.local is not None else bindings[reloc.symbol]
        value = struct.unpack_from('<I', code, reloc.offset)[0] + target
        if reloc.kind == 0x14:
            value -= code_address + reloc.offset + 4
        elif reloc.kind != 6:
            raise ValueError(f'unsupported relocation kind {reloc.kind:#x}')
        struct.pack_into('<I', code, reloc.offset, value & 0xFFFFFFFF)
    return bytes(code)
