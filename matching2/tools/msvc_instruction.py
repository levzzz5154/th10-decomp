"""Readable MSVC inline assembly, with explicit helpers for ambiguous x86 encodings.

Only source generation needs iced-x86. Normal C++ builds do not import this module.
"""
import re
from iced_x86 import Decoder, Formatter, FormatterSyntax, MemorySizeOptions, Mnemonic, OpKind, Register

FORMATTER = Formatter(FormatterSyntax.MASM)
FORMATTER.memory_size_options = MemorySizeOptions.ALWAYS
FORMATTER.show_branch_size = True
FORMATTER.masm_add_ds_prefix32 = False
R8 = ['AL', 'CL', 'DL', 'BL', 'AH', 'CH', 'DH', 'BH']
R32 = ['EAX', 'ECX', 'EDX', 'EBX', 'ESP', 'EBP', 'ESI', 'EDI']


def inline_instruction(address, raw, local_addresses, target_name):
    """Return instruction lines, external address bindings, and encoding helper tags."""
    result, bindings, helpers = [], {}, []
    for ins in Decoder(32, raw, ip=address):
        if ins.code == 0:
            raise ValueError(f'invalid instruction at {address:#x}')
        encoded = raw[ins.ip - address:ins.next_ip - address]
        text = FORMATTER.format(ins)
        short = ins.is_jcc_short or ins.is_jmp_short or ins.is_loop or ins.is_loopcc or ins.is_jcx_short
        if ins.op_count and ins.op0_kind in (OpKind.NEAR_BRANCH16, OpKind.NEAR_BRANCH32):
            target = ins.near_branch_target
            if short and target in local_addresses:
                text = FORMATTER.format_mnemonic(ins) + ' short L_' + f'{target:08x}'
            elif short:
                name = target_name(target)
                # MSVC widens an external short jump even with `short`. Encode the
                # architectural rel8 form from the fixed, checked address contract.
                text = f'TH10_REL8(0x{encoded[0]:02x}, 0x{address:08x}, VA_{name})'
                helpers.append('external_rel8')
                bindings[name] = target
            else:
                name = target_name(target)
                text = FORMATTER.format_mnemonic(ins) + ' ' + name
                bindings[name] = target
        elif (ins.memory_displ_size and ins.memory_base == Register.NONE and
              ins.memory_index == Register.NONE and ins.memory_segment == Register.DS and '[' in text):
            target = ins.memory_displacement & 0xffffffff
            name = f'data_{target:08x}'
            bindings[name] = target
            text = re.sub(r'\[[0-9A-Fa-f]+h?\]', f'[{name}]', text)
        if (ins.mnemonic == Mnemonic.LEA and ins.memory_displ_size == 4 and
                ins.memory_base != Register.NONE and ins.memory_displacement == 0):
            bindings['force_disp32_zero'] = 0
            text = text.replace(']', '+force_disp32_zero]')
            helpers.append('explicit_disp32')
        if ins.mnemonic == Mnemonic.TEST and ins.op0_kind == OpKind.REGISTER and ins.op1_kind == OpKind.REGISTER:
            text = 'test ' + ','.join(reversed(FORMATTER.format_all_operands(ins).split(',')))
        if encoded == bytes.fromhex('8d4900'):
            text = 'TH10_NOP_LEA_ECX_DISP8()'
            helpers.append('lea_disp8')
        elif encoded == bytes.fromhex('8d642400'):
            text = 'TH10_NOP_LEA_ESP_DISP8()'
            helpers.append('lea_disp8')
        elif encoded[0] == 0x38 and len(encoded) == 2 and encoded[1] >= 0xc0:
            text = f'TH10_CMP_R8_STORE(TH10_R8_{R8[encoded[1] & 7]}, TH10_R8_{R8[(encoded[1] >> 3) & 7]})'
            helpers.append('cmp_store_form')
        elif (encoded[:2] == bytes.fromhex('6681') and ins.op0_kind == OpKind.MEMORY and
              (int.from_bytes(encoded[-2:], 'little') < 0x80 or int.from_bytes(encoded[-2:], 'little') >= 0xff80)):
            if len(encoded) == 5 and encoded[2] in (0, 1, 2):
                immediate = int.from_bytes(encoded[-2:], 'little')
                text = f'TH10_ADD_M16_IMM16(TH10_R32_{R32[encoded[2]]}, 0x{immediate:04x})'
            elif encoded == bytes.fromhex('66817dfaffff'):
                text = 'TH10_CMP_EBP_DISP8_IMM16(-6, 0xffff)'
            else:
                raise ValueError(f'unmodeled word immediate form at {address:#x}: {encoded.hex()}')
            helpers.append('explicit_imm16')
        elif encoded[:2] == bytes.fromhex('6683') and ins.op0_kind == OpKind.REGISTER and ins.op0_register == Register.AX:
            text = 'TH10_OPERAND16()\n' + text.replace('ax,', 'eax,')
            helpers.append('operand16_group83')
        elif encoded == bytes.fromhex('d8f0'):
            text = 'TH10_FDIV_ST_ST0()'
            helpers.append('x87_self_divide')
        elif encoded == bytes.fromhex('d8f8'):
            text = 'TH10_FDIVR_ST_ST0()'
            helpers.append('x87_self_divide')
        elif encoded == bytes.fromhex('0500000000'):
            bindings['force_imm32_zero'] = 0
            text = 'add eax,offset force_imm32_zero'
            helpers.append('explicit_imm32')
        if text in ('faddp', 'fmulp', 'fsubp', 'fsubrp', 'fdivp', 'fdivrp'):
            text += ' st(1),st'
        result.extend(text.splitlines())
    return result, bindings, helpers
