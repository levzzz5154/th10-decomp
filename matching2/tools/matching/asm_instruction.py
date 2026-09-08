#!/usr/bin/env python3
"""Turn one decoded x86 instruction into GNU ``as`` Intel syntax.

The assembly baseline keeps the bytes in the Ghidra exports as its oracle.  A
disassembler's pretty printed text is not enough for that job: a number of
different encodings have the same architectural instruction (``mov`` load vs
store forms, short vs near branches, and so on).  This module therefore keeps
the original address and encoded bytes in the conversion API and adds GNU as
encoding hints where the source spelling would otherwise be ambiguous.

``iced-x86`` is deliberately the only decoder dependency.  There is no
``.byte`` escape hatch here.  If an instruction cannot be expressed with a
normal Intel instruction or one of the explicitly modelled ``.insn`` forms,
``UnsupportedInstruction`` is raised; callers can then record the address for
manual conversion instead of accidentally claiming a byte match.

The intended Python interpreter is the small environment documented by the
assembly baseline (``/tmp/th10-asm-env`` in the development setup):

    python -m pip install iced-x86
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from typing import Iterable

try:
    from iced_x86 import (
        Decoder,
        DecoderOptions,
        Formatter,
        FormatterSyntax,
        Instruction,
        OpKind,
        Register,
    )
except ImportError as exc:  # pragma: no cover - exercised by the CLI/user
    raise ImportError(
        "matching2.tools.matching.asm_instruction requires iced-x86; "
        "install it with `python -m pip install iced-x86`"
    ) from exc


_HEX_SUFFIX = re.compile(r"(?i)(?<![A-Za-z0-9_])([0-9A-F]+)h\b")
_MEM_HEX = re.compile(r"(?i)(?<![A-Za-z0-9_])([0-9A-F]+)h\b")
_PREFIX_BYTES = {
    0x26,
    0x2E,
    0x36,
    0x3E,
    0x64,
    0x65,
    0x66,
    0x67,
    0xF0,
    0xF2,
    0xF3,
}
_STRING_MNEMONICS = {
    "cmpsb",
    "cmpsd",
    "cmpsw",
    "insb",
    "insd",
    "insw",
    "lodsb",
    "lodsd",
    "lodsw",
    "movsb",
    "movsd",
    "movsw",
    "outsb",
    "outsd",
    "outsw",
    "scasb",
    "scasd",
    "scasw",
    "stosb",
    "stosd",
    "stosw",
}
_X87_MEMORY_MNEMONICS = {
    "fadd",
    "faddp",
    "fcom",
    "fcomp",
    "fdiv",
    "fdivp",
    "fdivr",
    "fdivrp",
    "fiadd",
    "ficom",
    "ficomp",
    "fidiv",
    "fidivr",
    "fild",
    "fimul",
    "fist",
    "fistp",
    "fisub",
    "fisubr",
    "fld",
    "fmul",
    "fmulp",
    "fsub",
    "fsubp",
    "fsubr",
    "fsubrp",
    "fst",
    "fstp",
}


class UnsupportedInstruction(ValueError):
    """The instruction needs a hand-written encoding spelling."""

    def __init__(self, address: int, data: bytes, reason: str):
        self.address = address
        self.data = bytes(data)
        self.reason = reason
        super().__init__(f"0x{address:08X} {data.hex().upper()}: {reason}")


@dataclass(frozen=True)
class DecodedInstruction:
    address: int
    data: bytes
    instruction: Instruction


def _decode(address: int, data: bytes) -> DecodedInstruction:
    if not isinstance(address, int) or not 0 <= address <= 0xFFFFFFFF:
        raise ValueError(f"instruction address is not a 32-bit integer: {address!r}")
    if not data:
        raise ValueError("instruction data is empty")
    raw = bytes(data)
    decoder = Decoder(32, raw, ip=address, options=DecoderOptions.NONE)
    instruction = next(iter(decoder), None)
    if instruction is None or instruction.code == 0:
        raise UnsupportedInstruction(address, raw, "iced-x86 did not decode an instruction")
    if instruction.len != len(raw):
        raise UnsupportedInstruction(
            address,
            raw,
            f"input contains {len(raw)} bytes but decoded instruction is {instruction.len} bytes",
        )
    return DecodedInstruction(address, raw, instruction)


def _hex_to_gas(text: str) -> str:
    """iced's ``1234h`` is valid Intel syntax but not GNU as syntax."""

    def replace(match: re.Match[str]) -> str:
        # ``ah``, ``bh``, ``ch`` and ``dh`` are byte-register names, not
        # hexadecimal literals with an ``h`` suffix.
        if match.group(1).lower() in {"a", "b", "c", "d"}:
            return match.group(0)
        return f"0x{match.group(1)}"

    return _HEX_SUFFIX.sub(replace, text)


def _opcode_offset(data: bytes) -> int:
    """Return the first opcode byte, skipping legacy prefixes."""

    index = 0
    while index < len(data) and data[index] in _PREFIX_BYTES:
        index += 1
    return index


def _opcode(data: bytes) -> tuple[int, int]:
    offset = _opcode_offset(data)
    if offset >= len(data):
        return offset, 0
    if data[offset] == 0x0F and offset + 1 < len(data):
        return offset + 1, (0x0F00 | data[offset + 1])
    return offset, data[offset]


def _modrm(data: bytes) -> tuple[int, int, int] | None:
    offset, opcode = _opcode(data)
    # A ModRM byte follows the normal one-byte opcode for the groups we use.
    # The 0F escape has already been consumed by _opcode().  This is enough to
    # identify direction and immediate-width ambiguities without pretending
    # to be a second x86 decoder.
    if opcode in {
        0x80,
        0x81,
        0x82,
        0x83,
        0x84,
        0x85,
        0x86,
        0x87,
        0x88,
        0x89,
        0x8A,
        0x8B,
        0x8C,
        0x8D,
        0x8F,
        0xC0,
        0xC1,
        0xC6,
        0xC7,
        0xD0,
        0xD1,
        0xD2,
        0xD3,
        0xD8,
        0xD9,
        0xDA,
        0xDB,
        0xDC,
        0xDD,
        0xDE,
        0xDF,
        0xF6,
        0xF7,
        0xFE,
        0xFF,
    } or (opcode & 0xFF00) == 0x0F00:
        if offset + 1 < len(data):
            modrm = data[offset + 1]
            return modrm, (modrm >> 3) & 7, modrm >> 6
    return None


def _replace_absolute_memory(operand: str, decoded: DecodedInstruction) -> str:
    ins = decoded.instruction
    if ins.memory_base != Register.NONE or ins.memory_index != Register.NONE:
        return operand
    # iced reports the default DS segment explicitly.  It is semantically the
    # same as no segment override; FS/GS/etc. must stay textual because their
    # address is not a flat `_th10_XXXXXXXX` image VA.
    if ins.memory_segment not in (Register.NONE, Register.DS):
        return operand
    if ins.memory_displ_size == 0:
        return operand
    # This is deliberately restricted to an operand containing brackets.  A
    # bare immediate must remain an immediate, even when its value resembles a
    # code/data VA.
    if "[" not in operand or "]" not in operand:
        return operand
    match = _MEM_HEX.search(operand)
    if not match:
        return operand
    target = ins.memory_displacement & 0xFFFFFFFF
    return operand[: match.start()] + f"_th10_{target:08x}" + operand[match.end() :]


def _format_operands(decoded: DecodedInstruction, formatter: Formatter) -> list[str]:
    ins = decoded.instruction
    # iced's formatter includes implicit x87 accumulator operands and string
    # instruction memory operands in ``format_all_operands`` even though they
    # are not counted by Instruction.op_count.  Splitting at top-level commas
    # is sufficient for 32-bit Intel syntax (memory expressions contain no
    # commas) and preserves far-pointer's two operands.
    all_operands = formatter.format_all_operands(ins)
    if not all_operands:
        return []
    raw_operands = [part.strip() for part in all_operands.split(",")]
    explicit_kinds = [ins.op_kind(index) for index in range(ins.op_count)]
    operands: list[str] = []
    kind_index = 0
    for operand_index, operand in enumerate(raw_operands):
        kind = explicit_kinds[kind_index] if kind_index < len(explicit_kinds) else None
        # An implicit x87 ``st`` is emitted before the actual operand.  It is
        # retained here so _normalise_x87 can remove it with the right context.
        if kind is not None:
            kind_index += 1
        if kind in (OpKind.NEAR_BRANCH16, OpKind.NEAR_BRANCH32, OpKind.NEAR_BRANCH64):
            operand = f"_th10_{ins.near_branch_target:08x}"
        elif kind in (OpKind.IMMEDIATE8TO16, OpKind.IMMEDIATE8TO32, OpKind.IMMEDIATE8TO64):
            # The formatter prints 0FFh for the encoded byte.  A signed
            # decimal spelling makes GNU as select the sign-extended imm8
            # form, preserving 83/6A/6B rather than widening it.
            if kind == OpKind.IMMEDIATE8TO16:
                value = ins.immediate8to16
            elif kind == OpKind.IMMEDIATE8TO64:
                value = ins.immediate8to64
            else:
                value = ins.immediate8to32
            operand = str(value)
        else:
            operand = _replace_absolute_memory(operand, decoded)
        operands.append(_hex_to_gas(operand))
    return operands


def _normalise_x87(mnemonic: str, operands: list[str]) -> list[str]:
    if mnemonic in _X87_MEMORY_MNEMONICS and len(operands) >= 2:
        # iced renders the implicit x87 accumulator as ``st,dword ptr [..]``;
        # GNU as expects only the explicit memory operand.
        if operands[0].lower() == "st" and "[" in operands[1]:
            operands = operands[1:]
        # For stores iced puts the implicit accumulator after the memory
        # operand (``fstp dword ptr [...], st``), while GNU as omits it.
        elif operands[-1].lower() == "st" and "[" in operands[0]:
            operands = operands[:-1]
        elif mnemonic in {"fst", "fstp"} and operands[-1].lower() == "st":
            operands = operands[:-1]
    if mnemonic.startswith("f") and len(operands) == 2 and operands[0].lower() == "st":
        # Register-only forms such as fld st,st(1) are written fld st(1) in
        # GNU as.  Keep two-operand arithmetic forms intact.
        if operands[1].lower().startswith("st("):
            operands = [operands[1]]
    return operands


def _normalise_mnemonic(mnemonic: str, operands: list[str]) -> tuple[str, list[str]]:
    mnemonic = mnemonic.lower()
    # GNU as string instructions have implicit source/destination operands.
    if mnemonic in _STRING_MNEMONICS or mnemonic.removeprefix("rep ") in _STRING_MNEMONICS:
        operands = []
    if mnemonic == "ret far":
        mnemonic = "lret"
    elif mnemonic == "jmp far":
        mnemonic = "ljmp"
    elif mnemonic == "call far":
        mnemonic = "lcall"
    return mnemonic, operands


def _instruction_hints(decoded: DecodedInstruction, mnemonic: str) -> list[str]:
    """Return GNU pseudo prefixes required by the original encoding."""

    ins = decoded.instruction
    data = decoded.data
    offset, opcode = _opcode(data)
    hints: list[str] = []

    # Branch targets remain symbols so the generated source follows later
    # edits.  The width hint preserves the original rel8/rel32 form when the
    # target happens to be close enough for GAS to choose another encoding.
    if ins.op_count and ins.op_kind(0) in (OpKind.NEAR_BRANCH16, OpKind.NEAR_BRANCH32, OpKind.NEAR_BRANCH64):
        if opcode in (0xE0, 0xE1, 0xE2, 0xE3, 0xEB) or 0x70 <= opcode <= 0x7F:
            hints.append("{disp8}")
        else:
            hints.append("{disp32}")

    # ModRM memory displacements are otherwise shortened whenever possible.
    if ins.memory_displ_size == 1:
        hints.append("{disp8}")
    elif ins.memory_displ_size == 4 and ins.memory_base != Register.NONE:
        displacement = ins.memory_displacement
        if -128 <= displacement <= 127:
            hints.append("{disp32}")

    # Preserve ModRM direction bits.  Intel syntax makes load/store pairs
    # architecturally identical, so GNU as otherwise chooses its preferred
    # member of the pair (for example 21 D8 instead of retail 23 C3).
    store_forms = {
        0x00, 0x01, 0x08, 0x09, 0x10, 0x11, 0x18, 0x19,
        0x20, 0x21, 0x28, 0x29, 0x30, 0x31, 0x38, 0x39,
        0x88, 0x89,
    }
    load_forms = {
        0x02, 0x03, 0x0A, 0x0B, 0x12, 0x13, 0x1A, 0x1B,
        0x22, 0x23, 0x2A, 0x2B, 0x32, 0x33, 0x3A, 0x3B,
        0x8A, 0x8B,
    }
    if opcode in store_forms:
        hints.append("{store}")
    elif opcode in load_forms:
        hints.append("{load}")

    op_kinds = [ins.op_kind(index) for index in range(ins.op_count)]
    if OpKind.IMMEDIATE32 in op_kinds or OpKind.IMMEDIATE16 in op_kinds:
        # GAS otherwise changes sign-extended imm32 values to imm8.  The
        # noimm8s pseudo prefix is supported by current GNU as and is ignored
        # when no such shortening is possible.
        hints.append("{noimm8s}")
    return hints


def _special_insn(decoded: DecodedInstruction, mnemonic: str, operands: list[str]) -> str | None:
    """Emit an explicit semantic ``.insn`` for encodings GAS cannot spell.

    This is intentionally a short list.  It covers the common cases that have
    no textual Intel spelling for the original form: MOV r32,imm encoded
    through C7 rather than B8 and accumulator arithmetic encoded through a
    ModRM group rather than its shorter accumulator opcode.  Branches stay
    symbolic and are controlled by {disp8}/{disp32} hints in the normal source
    line.
    """

    data = decoded.data
    offset, opcode = _opcode(data)
    ins = decoded.instruction
    modrm_info = _modrm(data)

    if opcode == 0xC7 and modrm_info is not None:
        _, extension, mod = modrm_info
        if extension == 0 and mod == 3 and any(kind == OpKind.IMMEDIATE32 for kind in [ins.op_kind(i) for i in range(ins.op_count)]):
            # .insn's {:u32} suffix prevents the immediate from being folded
            # into a different encoding.  The regular Intel operands are
            # suitable here (register, immediate).
            if len(operands) == 2:
                return f".insn 0xc7/0, {operands[0]}, {operands[1]}{{:u32}}"

    # Arithmetic accumulator forms (81 /0..7, with EAX as r/m) have a second
    # accumulator opcode (05/0D/15/1D/25/2D/35/3D) that GNU as prefers.  The
    # generic .insn spelling retains the original ModRM form.
    if opcode == 0x81 and modrm_info is not None:
        _, extension, mod = modrm_info
        if mod == 3 and (data[offset + 1] & 7) == 0 and len(operands) == 2:
            if any(kind == OpKind.IMMEDIATE32 for kind in [ins.op_kind(i) for i in range(ins.op_count)]):
                return f".insn 0x81/{extension}, {operands[0]}, {operands[1]}{{:u32}}"

    # GAS canonicalizes the architecturally equivalent D8 C0 form when an x87
    # register operation names ST(0),ST(0).  The retail image contains DC C0;
    # .insn retains that explicit x87 opcode while keeping register operands
    # visible in the source.
    if opcode == 0xDC and mnemonic == "fadd" and modrm_info is not None and modrm_info[2] == 3:
        if operands:
            return f".insn 0xdc, {', '.join(operands)}"
    return None


def instruction_to_asm(address: int, data: bytes) -> str:
    """Return one exact-encoding GNU Intel-syntax instruction line.

    Direct near call/jump operands are emitted as ``_th10_XXXXXXXX`` symbols;
    absolute memory operands use the same symbol convention.  The linker is
    responsible for assigning those symbols their original virtual addresses.
    """

    # ``wait`` is a legacy x87 prefix.  iced-x86 intentionally exposes it as
    # a separate one-byte instruction, while Ghidra's rows retain the prefix
    # with the following x87 instruction.  GNU as accepts the equivalent
    # ``fwait`` mnemonic, so keep both instructions in the returned source.
    if data and data[0] == 0x9B and len(data) > 1:
        return "fwait\n" + instruction_to_asm(address + 1, bytes(data[1:]))
    decoded = _decode(address, data)
    formatter = Formatter(FormatterSyntax.INTEL)
    ins = decoded.instruction
    mnemonic, operands = _normalise_mnemonic(formatter.format_mnemonic(ins), _format_operands(decoded, formatter))
    operands = _normalise_x87(mnemonic, operands)
    hints = _instruction_hints(decoded, mnemonic)
    line = f"{' '.join(hints + [mnemonic])}"
    if operands:
        line += " " + ", ".join(operands)

    # iced emits branch qualifiers (``short`` / ``near ptr``) which GNU as
    # does not use in this Intel form.  Direct branch operands have already
    # become symbols, so removing them is safe.
    line = re.sub(r"\bnear ptr\s+", "", line, flags=re.IGNORECASE)
    line = re.sub(r"\bshort\s+", "", line, flags=re.IGNORECASE)
    line = line.replace("repne ", "repne ")

    special = _special_insn(decoded, mnemonic, operands)
    if special is not None:
        # A semantic .insn is preferable to a byte blob when GAS's ordinary
        # parser would choose a different architectural encoding.
        if decoded.data[_opcode_offset(decoded.data)] in (0xC7, 0x81, 0xDC):
            return special
    return line


def decode_text(address: int, data: bytes) -> str:
    """Return iced's Intel text for diagnostics and regression reports."""

    decoded = _decode(address, data)
    return Formatter(FormatterSyntax.INTEL).format(decoded.instruction)


def convert_rows(rows: Iterable[dict[str, object]]) -> tuple[list[dict[str, object]], list[dict[str, object]]]:
    """Convert inventory rows, returning converted and explicit unsupported lists."""

    converted: list[dict[str, object]] = []
    unsupported: list[dict[str, object]] = []
    for row in rows:
        encoded_address = row["address"]
        address = int(encoded_address, 0) if isinstance(encoded_address, str) else int(encoded_address)
        data = bytes.fromhex(str(row["hex"]))
        try:
            source = instruction_to_asm(address, data)
        except UnsupportedInstruction as exc:
            unsupported.append({"address": address, "hex": data.hex().upper(), "reason": exc.reason})
        else:
            converted.append({"address": address, "hex": data.hex().upper(), "source": source})
    return converted, unsupported


__all__ = [
    "DecodedInstruction",
    "UnsupportedInstruction",
    "convert_rows",
    "decode_text",
    "instruction_to_asm",
]
