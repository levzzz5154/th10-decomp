#!/usr/bin/env python3
"""Function categorization for th10 matching decomp.
Categorizes all 1196 functions into CRT, THUNK, and GAME.
CRT functions (0x452422+) match from libcmt.lib.
THUNK functions (import stubs) are trivial jmp stubs.
GAME functions need manual C++ matching.
"""

import json

# Full function list from Ghidra MCP output
FUNCTIONS = [
    # Game code - addresses below 0x450700
    # Each entry: (name, address, is_thunk)
]

# CRT starts at 0x00452422 - everything above is CRT
# Import thunks: jmp [IAT] stubs, marked as isThunk=true in Ghidra
# Last game function: FUN_004506d0 at 0x004506D0
# First CRT function: _free at 0x00452422
# Gap 0x450700-0x452422: thunk stubs

def categorize():
    """Read function list from saved file and categorize."""
    with open("/home/levzzz/.local/share/opencode/tool-output/tool_f590ed7a9002F911TN3800QHaq") as f:
        data = f.read()
    
    # Parse JSON like entries
    entries = []
    current = {}
    
    lines = data.split('\n')
    for line in lines:
        line = line.strip()
        if line.startswith('{"address"'):
            try:
                entry = json.loads(line.strip().rstrip(','))
                entries.append(entry)
            except:
                pass
    
    game_count = 0
    crt_count = 0
    thunk_count = 0
    total_bytes = {'game': 0, 'crt': 0, 'thunk': 0}
    
    categorized = []
    for e in entries:
        addr = int(e['address'], 16)
        name = e['name']
        is_thunk = e.get('isThunk', False)
        
        if is_thunk:
            cat = 'THUNK'
            thunk_count += 1
        elif addr >= 0x00452400:
            cat = 'CRT'
            crt_count += 1
        else:
            cat = 'GAME'
            game_count += 1
        
        categorized.append((addr, name, cat))
    
    # Save to file
    with open("/home/levzzz/Games/th10Decomp/matching/functions.json", "w") as f:
        json.dump([{
            "addr": f"0x{a:08X}",
            "name": n,
            "category": c
        } for a, n, c in sorted(categorized)], f, indent=2)
    
    print(f"Total functions: {len(categorized)}")
    print(f"GAME:  {game_count}  (need manual C++ matching)")
    print(f"CRT:   {crt_count}  (from libcmt.lib)")
    print(f"THUNK: {thunk_count}  (trivial import stubs)")
    print(f"\nAuto-matched: {crt_count + thunk_count}/{len(categorized)} = {(crt_count+thunk_count)/len(categorized)*100:.1f}%")
    print(f"Need manual:  {game_count}/{len(categorized)} = {game_count/len(categorized)*100:.1f}%")
    
    return categorized

if __name__ == "__main__":
    categorize()
