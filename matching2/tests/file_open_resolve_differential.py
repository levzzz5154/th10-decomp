#!/usr/bin/env python3
"""Compare readable FileHandle Open/path-resolution candidates with retail.

The actual Close, first-byte search, strrchr and security-cookie helper run.
Windows imports are scripted, including selected changes to caller storage.
The standalone resolver cases also compare overlap and the missing-backslash
write fault. Native MSVC byte matching remains a separate gate.
"""

import argparse
from dataclasses import dataclass
from itertools import product
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from unicorn import Uc, UcError, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UC_HOOK_MEM_INVALID
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_ESP, UC_X86_REG_EIP
from lzss_compressor_differential import (
    ROOT, CANDIDATE, INPUT, OUTPUT, STACK, STOP, PRESERVED, PEImage,
    load_manifest, load_oracle, region_directory)
from coff_module import load_module

STATE, FILE, MODE = 0x2500000, 0x2500100, 0x2500200
IMPORTS = {0x4660C0: STOP + 0x100, 0x4660C4: STOP + 0x200,
           0x4660C8: STOP + 0x300, 0x4660CC: STOP + 0x400,
           0x4660DC: STOP + 0x500}
DELETE, CREATE, SEEK, CLOSE, MODULE = IMPORTS.values()


@dataclass(frozen=True)
class Case:
    path: bytes = b"data/asset.bin"
    mode: bytes = b"r"
    module: bytes = b"C:\\game\\th10.exe"
    module_result: object = None
    initial_handle: int = 0xFFFFFFFF
    initial_access: int = 0
    opened_handle: int = 0x1234
    mutate_at: object = None
    change_mode: object = None
    change_path: object = None
    change_access: object = None
    change_handle: object = None
    output_delta: object = None
    map_null: bool = False
    path_offset: int = 0x2000
    output_offset: int = 0x100


def compile_candidates(directory, config, code_base=CANDIDATE):
    bindings = region_directory(config, config["regions"])
    bindings.update({"_FirstByteSearch_00452730": 0x452730, "_strrchr": 0x452930,
                     "__imp__DeleteFileA@4": 0x4660C0, "__imp__CreateFileA@28": 0x4660C4,
                     "__imp__SetFilePointer@16": 0x4660C8, "__imp__GetModuleFileNameA@12": 0x4660DC})
    modules = {}
    for source, address in (("file_resolve_path.cpp", code_base + 0x4000),
                            ("file_handle_open.cpp", code_base)):
        obj = directory / (source + ".obj")
        subprocess.run([
            "clang++", "--target=i686-pc-windows-msvc", "-std=c++03", "-O2", "-mno-sse", "-mno-sse2",
            "-fno-exceptions", "-fno-rtti", "-fno-stack-protector", "-ffunction-sections",
            "-I", str(ROOT / "matching2/msvc/include"), "-c",
            str(ROOT / "matching2/reference/semantic_candidates" / source), "-o", str(obj)],
            check=True, timeout=60)
        module = load_module(obj, address, bindings)
        modules[source] = module
        if source == "file_resolve_path.cpp":
            bindings.update(module.symbols)
    return modules


def execute(image, modules, operation, case):
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    uc.mem_map(0x400000, 0x100000)
    for section in image.sections:
        uc.mem_write(section["address"], image.read(section["address"], section["raw_size"]))
    for address in (CANDIDATE, INPUT, OUTPUT, STACK, STOP, STATE):
        uc.mem_map(address, 0x10000)
    for module in (modules or {}).values():
        uc.mem_write(module.base, module.data)
    if case.map_null:
        uc.mem_map(0, 0x1000)
        uc.mem_write(0, b"\xA5" * 0x1000)

    def words(address, *values):
        uc.mem_write(address, struct.pack("<" + "I" * len(values), *(v & 0xFFFFFFFF for v in values)))

    def read_words(address, count):
        return struct.unpack("<" + "I" * count, uc.mem_read(address, count * 4))

    def string(address):
        result = bytearray()
        while True:
            byte = uc.mem_read(address + len(result), 1)[0]
            if not byte:
                return bytes(result)
            result.append(byte)
            assert len(result) < 2048

    def args(count):
        return read_words(uc.reg_read(UC_X86_REG_ESP) + 4, count)

    def finish(result, cleanup):
        sp = uc.reg_read(UC_X86_REG_ESP)
        uc.reg_write(UC_X86_REG_EIP, read_words(sp, 1)[0])
        uc.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        uc.reg_write(UC_X86_REG_EAX, result & 0xFFFFFFFF)

    path = INPUT + case.path_offset
    output = path + case.output_delta if case.output_delta is not None else OUTPUT + case.output_offset
    uc.mem_write(INPUT, b"\xA5" * 0x10000)
    uc.mem_write(OUTPUT, b"\xA5" * 0x10000)
    uc.mem_write(path, case.path + b"\0")
    uc.mem_write(MODE, case.mode + b"\0")
    words(FILE, 0x46F230, case.initial_handle, case.initial_access)
    for slot, address in IMPORTS.items():
        words(slot, address)
    events, faults = [], []

    def mutate(stage):
        if case.mutate_at != stage:
            return
        if case.change_mode is not None:
            uc.mem_write(MODE, case.change_mode + b"\0")
        if case.change_path is not None:
            uc.mem_write(path, case.change_path + b"\0")
        if case.change_access is not None:
            words(FILE + 8, case.change_access)
        if case.change_handle is not None:
            words(FILE + 4, case.change_handle)

    def hook(machine, address, size, context):
        state = read_words(FILE + 4, 2)
        if address == CLOSE:
            handle, = args(1)
            events.append(("close", handle, state))
            mutate("close")
            finish(0, 4)
        elif address == DELETE:
            name, = args(1)
            events.append(("delete", string(name), state))
            mutate("delete")
            finish(0, 4)
        elif address == MODULE:
            handle, buffer, capacity = args(3)
            assert handle == 0 and capacity == 260
            events.append(("module", handle, capacity, string(path), state))
            uc.mem_write(buffer, case.module + b"\0")
            mutate("module")
            finish(len(case.module) if case.module_result is None else case.module_result, 12)
        elif address == CREATE:
            name, access, share, security, disposition, flags, template = args(7)
            events.append(("create", string(name), access, share, security, disposition, flags, template, state))
            mutate("create")
            finish(case.opened_handle, 28)
        elif address == SEEK:
            arguments = args(4)
            events.append(("seek", arguments, state))
            mutate("seek")
            finish(0xFFFFFFFF, 16)
        else:
            raise AssertionError(hex(address))

    def fault(machine, kind, address, size, value, context):
        faults.append((kind, address, size, value))
        return False

    for address in IMPORTS.values():
        uc.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)
    uc.hook_add(UC_HOOK_MEM_INVALID, fault)
    if operation == "open":
        address = modules["file_handle_open.cpp"].symbols["?Open@FileHandle@@UAEEPBD0@Z"] if modules else 0x435370
        arguments, cleanup = [path, MODE], 8
        uc.reg_write(UC_X86_REG_ECX, FILE)
    else:
        assert operation == "resolve"
        if modules:
            symbols = modules["file_resolve_path.cpp"].symbols
            address = next(value for name, value in symbols.items() if name.startswith("?File_ResolvePath@@"))
            arguments, cleanup = [path, output], 0
        else:
            address, arguments, cleanup = 0x435610, [], 0
            uc.reg_write(UC_X86_REG_EAX, path)
            uc.reg_write(UC_X86_REG_ECX, output)
    sp = STACK + 0x8000
    words(sp, STOP, *arguments)
    uc.reg_write(UC_X86_REG_ESP, sp)
    for register, value in PRESERVED.items():
        uc.reg_write(register, value)
    try:
        uc.emu_start(address, STOP, count=2000000)
    except UcError:
        if not faults:
            raise
    if not faults:
        assert uc.reg_read(UC_X86_REG_EIP) == STOP, "instruction budget exhausted"
        assert uc.reg_read(UC_X86_REG_ESP) == sp + 4 + cleanup
        assert all(uc.reg_read(register) == value for register, value in PRESERVED.items())
    return {"result": uc.reg_read(UC_X86_REG_EAX) & 255 if operation == "open" and not faults else None,
            "events": events, "faults": faults,
            "file": bytes(uc.mem_read(FILE, 12)), "mode": bytes(uc.mem_read(MODE, 256)),
            "input": bytes(uc.mem_read(INPUT, 0x10000)),
            "output": bytes(uc.mem_read(OUTPUT, 0x10000)),
            "null": bytes(uc.mem_read(0, 16)) if case.map_null else None}


def open_cases():
    modes = (b"", b"x", b"RWA", b"r", b"rb", b"w", b"wb", b"a", b"ab",
             b"+br", b"xw", b"?a", b"rw", b"wr", b"ar", b"\xffr")
    for mode, initial, opened, path in product(modes, (0xFFFFFFFF, 0x7654),
                                              (0xFFFFFFFF, 0, 0x1234),
                                              (b"data/asset.bin", b"Z:\\asset.bin")):
        yield Case(mode=mode, initial_handle=initial, initial_access=0x11223344,
                   opened_handle=opened, path=path)
    for mode, mutation in product((b"r", b"w", b"a"), (b"", b"w", b"?ar")):
        yield Case(mode=mode, initial_handle=0x4321, mutate_at="close", change_mode=mutation,
                   change_path=b"after-close.bin", change_access=0xABCDEF01, change_handle=0x4567)
    for mode in (b"", b"r", b"a"):
        yield Case(mode=b"w", mutate_at="delete", change_mode=mode, change_path=b"after-delete.bin",
                   change_access=0x12345678, change_handle=0x2468)
    for stage, mode, opened in product(("module", "create", "seek"), (b"r", b"w", b"a"),
                                      (0xFFFFFFFF, 0xABCD)):
        yield Case(mode=mode, opened_handle=opened, mutate_at=stage, change_mode=b"",
                   change_path=b"after-callback.bin", change_access=0x12345678, change_handle=0x2468)
    for module, result in product((b"game.exe", b"", b"C:/game.exe", b"C:\\game.exe"), (0, 260)):
        yield Case(module=module, module_result=result)
    for length in (0, 1, 2, 3, 4, 7, 8, 127, 240):
        yield Case(path=b"x" * length)


def resolver_cases():
    paths = (b"", b"a", b"ab", b"abc", b"abcd", b"abcde", b"dir/file", b"..\\file",
             b"/rooted", b"\\rooted", b"C:relative", b"C:\\absolute", b"url:part", b"colon:")
    for path, module in product(paths, (b"C:\\game\\th10.exe", b"C:\\th10.exe", b"\\th10.exe",
                                       b"th10.exe", b"C:/game/th10.exe", b"")):
        yield Case(path=path, module=module)
    for path in paths:
        for delta in ((0, -1, -3, -7, -32) if b":" in path else (0, -1, -3, 1, 3, 8, 32)):
            yield Case(path=path, output_delta=delta)
    for module in (b"", b"plain.exe", b"C:/plain.exe"):
        yield Case(path=b"relative.bin", module=module, map_null=True)
    randomizer = random.Random(0x435610)
    for trial in range(80):
        path = bytes(randomizer.choice(b"ab./\\012") for _ in range(randomizer.randrange(320)))
        yield Case(path=path, module=b"C:\\directory\\game.exe", module_result=trial & 1)
    # Terminators at the last mapped source/destination byte. Relative paths
    # retain their byte-wise length scan after the two CRT search helpers.
    for length, absolute in product((*range(19), 31, 32, 33), (False, True)):
        path = (b"X:" if absolute else b"") + b"x" * length
        result_size = len(path) + 1 + (0 if absolute else len(b"C:\\game\\"))
        destination_size = max(result_size, 1 + len(Case().module)) if not absolute else result_size
        yield Case(path=path, path_offset=0x10000 - len(path) - 1,
                   output_offset=0x10000 - destination_size)
    # Keep the module-name write in bounds, then cross the output boundary
    # during the append. Compare the original dword/byte fault and writes.
    for shortage, absolute in product(range(1, 8), (False, True)):
        path = (b"X:" if absolute else b"") + b"x" * 100
        result_size = len(path) + 1 + (0 if absolute else len(b"C:\\game\\"))
        yield Case(path=path, output_offset=0x10000 - result_size + shortage)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--oracle", type=Path, default=ROOT / "matching2/build/oracle/th10.exe")
    options = parser.parse_args()
    config = load_manifest(ROOT / "matching2/msvc/regions.json")
    load_oracle(options.oracle, config)
    image = PEImage(options.oracle.read_bytes())
    with tempfile.TemporaryDirectory(prefix="th10-file-open-") as temporary:
        modules = compile_candidates(Path(temporary), config)
        counts, faults = {}, 0
        for operation, cases in (("open", open_cases()), ("resolve", resolver_cases())):
            counts[operation] = 0
            for index, case in enumerate(cases):
                expected = execute(image, None, operation, case)
                actual = execute(image, modules, operation, case)
                differences = tuple(key for key in expected if expected[key] != actual[key])
                assert not differences, (operation, index, case, differences,
                                         expected["events"], actual["events"], expected["faults"], actual["faults"])
                counts[operation] += 1
                faults += bool(expected["faults"])
        sizes = {name: len(module.data) for name, module in modules.items()}
        print(f"PASS: {counts['open']} FileHandle Open and {counts['resolve']} path-resolution "
              f"comparisons, including {faults} matching memory faults. Module bytes: {sizes}. "
              "Native MSVC region matching and security-cookie frame equivalence remain unverified.")


if __name__ == "__main__":
    main()
