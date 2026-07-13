#!/usr/bin/env python3
"""Auto-generate naked asm source files from original binary bytes.
Uses objdump to disassemble raw x86 bytes, generates __declspec(naked) .cpp.
"""

import struct, subprocess, os, csv, re, sys

ORIG_EXE = "/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe"
MATCHING = "/home/levzzz/Games/th10Decomp/matching"
SRC_DIR = os.path.join(MATCHING, "src", "th10")
BUILD_DIR = os.path.join(MATCHING, "build")
TEXT_RVA = 0x1000
TEXT_RAW = 0x400
IMAGE_BASE = 0x400000

os.makedirs(SRC_DIR, exist_ok=True)
os.makedirs(BUILD_DIR, exist_ok=True)

def read_func_bytes(func_addr, size):
    """Read raw bytes from original binary."""
    rva = func_addr - IMAGE_BASE
    offset = TEXT_RAW + (rva - TEXT_RVA)
    with open(ORIG_EXE, 'rb') as f:
        f.seek(offset)
        return f.read(size)

def disasm_raw_bytes(data, base_addr=0):
    """Disassemble x86 bytes using objdump."""
    with open('/tmp/th10_func.bin', 'wb') as f:
        f.write(data)
    
    result = subprocess.run(
        ['objdump', '-D', '-b', 'binary', '-m', 'i386', '-M', 'intel',
         '--adjust-vma=' + str(base_addr), '/tmp/th10_func.bin'],
        capture_output=True, text=True
    )
    return result.stdout

def parse_objdump(disasm_text):
    """Parse objdump -D output into instruction list."""
    insns = []
    for line in disasm_text.split('\n'):
        # Match: "   0: 33 c9          xor    ecx,ecx"
        m = re.match(r'\s+([0-9a-f]+):\s+((?:[0-9a-f]{2}\s)+)\s+(.+)', line)
        if m:
            addr = int(m.group(1), 16)
            hex_str = m.group(2).strip()
            mnem = m.group(3).strip()
            # Clean up AT&T to Intel style
            insns.append((addr, hex_str, mnem))
    return insns

def load_func_names():
    """Load function name lookup from tracking CSV."""
    names = {}
    with open(os.path.join(MATCHING, 'tracking.csv')) as f:
        reader = csv.DictReader(f)
        for r in reader:
            addr = int(r['address'], 16)
            safe = r['name'].replace('@', '_').replace('`', '_').replace("'", "_")
            names[addr] = safe
    return names

FUNC_NAMES = load_func_names()

def resolve_call_target(instr, base_addr, cur_addr, func_end):
    """Replace hex call/jmp targets with function names or local labels."""
    import re
    m = re.match(r'(call|jmp|je|jne|jz|jnz|ja|jae|jb|jbe|jg|jge|jl|jle|jo|jno|js|jns|jp|jnp|jcxz|loop|loope|loopne)\s+(0x[0-9a-fA-F]+)(.*)', instr)
    if m:
        op = m.group(1)
        target_addr = int(m.group(2), 16)
        suffix = m.group(3)
        
        # If target is this function's entry point, use self-reference
        if target_addr == base_addr:
            # Get self name
            self_name = None
            for addr_key, name_val in FUNC_NAMES.items():
                if addr_key == base_addr:
                    self_name = name_val
                    break
            if self_name:
                return f"{op} {self_name}{suffix}"
        
        # If target is within this function, create a local label
        if base_addr <= target_addr < func_end:
            label = f"loc_{target_addr:08X}"
            return f"{op} {label}{suffix}"
        
        # Otherwise resolve to function name
        target_name = FUNC_NAMES.get(target_addr, f"FUN_{target_addr:08X}")
        return f"{op} {target_name}{suffix}"
    return instr

def insns_to_asm(insns, base_addr=0, func_end=0):
    """Convert parsed instructions to inline __asm syntax."""
    # First pass: collect all local label targets
    label_addrs = set()
    import re
    for addr, hex_bytes, text in insns:
        m = re.match(r'(jmp|je|jne|jz|jnz|ja|jae|jb|jbe|jg|jge|jl|jle|jo|jno|js|jns|jp|jnp|jcxz|loop|loope|loopne)\s+(0x[0-9a-fA-F]+)', text)
        if m:
            target_addr = int(m.group(2), 16)
            if base_addr <= target_addr < func_end:
                label_addrs.add(target_addr)
    
    lines = []
    for addr, hex_bytes, text in insns:
        # objdump addresses already include base via --adjust-vma
        cur_addr = addr
        
        # Emit label if this address is a jump target
        if cur_addr in label_addrs:
            lines.append(f"    loc_{cur_addr:08X}:")
        
        # Skip nop/int3 padding at end
        if text.startswith('nop') or text.startswith('int3') or text.startswith('xchg %ax,%ax'):
            if lines and ('ret' in lines[-1].lower()):
                break
        
        # Convert AT&T operand order to Intel
        # objdump -M intel gives Intel syntax, so operands should be fine
        # Format: "xor ecx,ecx" or "mov DWORD PTR [eax+0x8],ecx"
        instr = text.replace('  ', ' ')
        
        # Skip empty or whitespace-only instructions
        if not instr.strip():
            continue
        
        # Skip standalone .byte / .word directives from objdump (unrecognized)
        if instr.strip().startswith('.byte') or instr.strip().startswith('.word') or instr.strip().startswith('.long'):
            # Convert .byte to _emit
            parts = instr.strip().split()
            if parts[0] == '.byte':
                hex_vals = ' '.join(parts[1:])
                lines.append(f"        _emit {hex_vals}")
            continue
        
        # Fix common AT&T-isms if present
        instr = instr.replace('(%', '[').replace(')', ']')
        
        # Fix rep stos syntax for MSVC inline asm
        instr = instr.replace('rep stos DWORD PTR es:[edi],eax', 'rep stosd')
        instr = instr.replace('rep stos BYTE PTR es:[edi],al', 'rep stosb')
        instr = instr.replace('rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]', 'rep movsd')
        instr = instr.replace('repne scas BYTE PTR es:[edi],al', 'repne scasb')
        
        # Fix nop syntax
        instr = instr.replace('xchg %ax,%ax', 'nop')
        instr = instr.replace('lea esp,[esp+0x0]', 'nop')
        instr = instr.replace('lea ecx,[ecx+0x0]', 'nop')
        instr = instr.replace('lea  ecx,[ecx+0x0]', 'nop')
        instr = instr.replace('lea  esp,[esp+0x0]', 'nop')
        instr = instr.replace('lea  esp,[esp+0]', 'nop')
        
        # Fix data16 prefix
        instr = instr.replace('data16 ', '')
        
        # Fix lock prefix (should be fine as-is)
        
        # Fix FPU stack register: objdump produces st(1] instead of st(1)
        instr = re.sub(r'\bst\((\d+)\]', r'st(\1)', instr)
        
        # Resolve call/jmp targets to function names
        instr = resolve_call_target(instr, base_addr, addr, func_end)
        
        lines.append(f"        {instr}")
    
    return lines

def find_external_refs(insns):
    """Find all external function references in call/jmp instructions."""
    refs = set()
    for _, _, text in insns:
        m = re.match(r'(call|jmp|je|jne|jz|jnz|ja|jae|jb|jbe|jg|jge|jl|jle)\s+(0x[0-9a-fA-F]+)', text)
        if m:
            target_addr = int(m.group(2), 16)
            if target_addr >= 0x401000 and target_addr != 0:  # game code range
                refs.add(target_addr)
    return refs

def generate_cpp(func_addr, func_name, func_size):
    """Generate a __declspec(naked) .cpp file for a function."""
    bytes_data = read_func_bytes(func_addr, func_size)
    
    # Find actual function end by looking for RET instruction
    # and determine padding
    disasm = disasm_raw_bytes(bytes_data, func_addr)
    insns = parse_objdump(disasm)
    
    # Filter padding: keep all instructions, trim trailing int3/nops only
    code_insns = []
    
    # Find the last meaningful instruction (non-padding)
    last_meaningful = len(insns) - 1
    for i in range(len(insns) - 1, -1, -1):
        _, _, text = insns[i]
        if not (text.startswith('nop') or text.startswith('int3') or 
                text.startswith('xchg %ax,%ax') or text.startswith('lea esp,')):
            last_meaningful = i
            break
    
    for i, (addr, hex_bytes, text) in enumerate(insns):
        if i > last_meaningful:
            break
        
        # Skip standalone padding between functions (but keep within-function nops)
        if text.startswith('int3') and i > 0:
            prev_text = insns[i-1][2]
            if prev_text.startswith('ret') or prev_text.startswith('retf'):
                if all(insns[j][2].startswith('int3') or insns[j][2].startswith('nop') 
                       for j in range(i, min(i+4, len(insns)))):
                    break
        
        code_insns.append((addr, hex_bytes, text))
    
    actual_code_len = len(code_insns)
    if actual_code_len == 0:
        return None
    
    # Generate asm lines
    asm_lines = insns_to_asm(code_insns, func_addr, func_addr + func_size)
    
    # Collect local labels that were referenced and insert them
    # We need to insert label: before the appropriate instruction
    # For now, skip - labels need to be placed at exact instruction addresses
    # This requires matching instruction offsets to the asm lines
    # We'll handle this in a future pass
    
    # Generate source
    safe_name = func_name.replace('@', '_').replace('`', '_').replace("'", "_")
    
    # Generate extern declarations for call targets (only external functions)
    extern_decls = ""
    external_refs = find_external_refs(code_insns)
    for ref_addr in sorted(external_refs):
        # Skip if target is within this function
        if func_addr <= ref_addr < func_addr + func_size:
            continue
        ref_name = FUNC_NAMES.get(ref_addr, f"FUN_{ref_addr:08X}")
        extern_decls += f"extern \"C\" void {ref_name}(void);\n"
    
    cpp = f"""// {func_addr:08X}: {func_name}
// Original size: {func_size} bytes, actual code: {actual_code_len} instructions
{extern_decls}
__declspec(naked) void {safe_name}(void) {{
    __asm {{
"""
    for line in asm_lines:
        cpp += f"{line}\n"
    cpp += """    }
}
"""
    return cpp

def main():
    max_bytes = int(sys.argv[1]) if len(sys.argv) > 1 else 999999
    
    # Read tracking CSV
    with open(os.path.join(MATCHING, 'tracking.csv')) as f:
        reader = csv.DictReader(f)
        funcs = [(r['address'], r['name'], int(r['size_bytes']))
                 for r in reader if r['category'] == 'GAME' and r['status'] == 'pending' and int(r['size_bytes']) <= max_bytes]
    
    print(f"Processing {len(funcs)} pending game functions (<= {max_bytes} bytes)...")
    
    generated = 0
    for addr_str, name, size in funcs:
        addr = int(addr_str, 16)
        safe_name = name.replace('@', '_').replace('`', '_').replace("'", "_")
        filepath = os.path.join(SRC_DIR, f"{safe_name}.cpp")
        
        cpp = generate_cpp(addr, name, size)
        if cpp:
            with open(filepath, 'w') as f:
                f.write(cpp)
            generated += 1
        else:
            print(f"  SKIP {addr_str}: no code found")
    
    print(f"\nGenerated {generated}/{len(funcs)} source files in {SRC_DIR}")

if __name__ == "__main__":
    main()
