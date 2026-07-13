#!/usr/bin/env python3
import json
import csv
import os
import sys

JSON_PATH = os.path.expanduser("~/.local/share/opencode/tool-output/tool_f590ed7a9002F911TN3800QHaq")
CSV_OUT = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "tracking.csv")

GAME_BOUNDARY = 0x452400

def main():
    with open(JSON_PATH) as f:
        data = json.load(f)

    functions = data["functions"]

    game_funcs = []
    crt_funcs = []
    thunk_funcs = []

    for f in functions:
        addr = int(f["address"], 16)
        if f["isThunk"]:
            thunk_funcs.append((addr, f["name"]))
        elif addr >= GAME_BOUNDARY:
            crt_funcs.append((addr, f["name"]))
        else:
            game_funcs.append((addr, f["name"]))

    game_funcs.sort(key=lambda x: x[0])

    rows = []

    for i, (addr, name) in enumerate(game_funcs):
        if i + 1 < len(game_funcs):
            next_addr = game_funcs[i + 1][0]
        else:
            next_addr = GAME_BOUNDARY
        size = next_addr - addr
        rows.append((addr, name, size, "GAME", "pending", ""))

    rows.sort(key=lambda x: x[2])

    for addr, name in crt_funcs:
        rows.append((addr, name, 0, "CRT", "auto", ""))

    for addr, name in thunk_funcs:
        rows.append((addr, name, 0, "THUNK", "auto", ""))

    os.makedirs(os.path.dirname(CSV_OUT), exist_ok=True)
    with open(CSV_OUT, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["address", "name", "size_bytes", "category", "status", "notes"])
        for addr, name, size, cat, status, notes in rows:
            writer.writerow([f"0x{addr:08X}", name, size, cat, status, notes])

    total = len(functions)
    auto_count = len(crt_funcs) + len(thunk_funcs)
    pending = len(game_funcs)
    pct = auto_count / total * 100

    print(f"Total functions: {total}")
    print(f"Auto (CRT+THUNK): {auto_count} ({pct:.1f}%)")
    print(f"Pending (GAME):   {pending} ({pending/total*100:.1f}%)")
    print()
    print("Top 10 smallest GAME functions:")
    print(f"{'Address':<12} {'Name':<25} {'Size':>6}")
    print("-" * 45)
    for addr, name, size, _, _, _ in rows[:10]:
        print(f"0x{addr:08X}  {name:<25} {size:>6}")

    print(f"\nTracking CSV written to: {CSV_OUT}")


if __name__ == "__main__":
    main()
