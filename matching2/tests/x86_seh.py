"""Give a 32-bit Unicorn fixture an FS thread block while leaving NULL unmapped.

This installs only segment metadata and an exception-list sentinel. It does not
implement Windows exception dispatch or treat MSVC EH generations as compatible.
"""
import struct
from unicorn.x86_const import UC_X86_REG_GDTR, UC_X86_REG_FS, UC_X86_REG_CS, UC_X86_REG_DS, UC_X86_REG_ES, UC_X86_REG_SS

TEB = 0x2700000
INITIAL_EXCEPTION_LIST = 0xFEE1DEAD


def install(uc):
    uc.mem_map(TEB, 0x2000)
    gdt = TEB + 0x1000
    # Flat-size, present, writable 32-bit data segment, with the thread block
    # as base. FS selector 8 chooses descriptor one in this fixture's GDT.
    descriptor = struct.pack("<HHBBBB", 0xFFFF, TEB & 0xFFFF, (TEB >> 16) & 255,
                             0x93, 0xCF, (TEB >> 24) & 255)
    uc.mem_write(gdt + 8, descriptor)
    # Explicit flat code/data segments also retain 32-bit stack addressing;
    # leaving SS at its reset selector would make pushes wrap at 64 KiB.
    uc.mem_write(gdt + 16, struct.pack("<HHBBBB", 0xFFFF, 0, 0, 0x93, 0xCF, 0))
    uc.mem_write(gdt + 24, struct.pack("<HHBBBB", 0xFFFF, 0, 0, 0x9B, 0xCF, 0))
    uc.reg_write(UC_X86_REG_GDTR, (0, gdt, 0xFF, 0))
    uc.reg_write(UC_X86_REG_CS, 24)
    for register in (UC_X86_REG_DS, UC_X86_REG_ES, UC_X86_REG_SS):
        uc.reg_write(register, 16)
    uc.reg_write(UC_X86_REG_FS, 8)
    uc.mem_write(TEB, struct.pack("<I", INITIAL_EXCEPTION_LIST))


def exception_list(uc):
    return struct.unpack("<I", uc.mem_read(TEB, 4))[0]
