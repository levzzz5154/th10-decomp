#!/usr/bin/env python3
"""Deal the next conversion wave and write one brief per agent.

Two pools are scheduled: regions a plain translation unit can express, and
regions that need a native LTCG cluster because their internal register
convention (an argument in EAX, a variadic member callee keeping ``this`` in
ECX) is not something a C++ prototype can declare.

Every assigned source is copied to ``backup<N>/`` first: that copy is the only
rollback an agent is allowed to use, and the parent uses it to restore a unit
that fails the whole-image build.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import shutil

import matching2.tools.waves.plan as plan


def deal(items, per_agent, agents):
    """Deal regions to agents, largest file first, so each gets a mix."""
    if agents < 1:
        return []
    by_file = {}
    for item in items:
        by_file.setdefault(item["source"], []).append(item)
    files = sorted(by_file.values(), key=lambda units: -sum(unit["size"] for unit in units))
    buckets = [[] for _ in range(agents)]
    for index, units in enumerate(files):
        bucket = min(buckets, key=lambda group: sum(unit["size"] for unit in group))
        if len(bucket) + len(units) > per_agent and all(len(b) >= per_agent for b in buckets):
            break
        bucket.extend(units)
    return [bucket for bucket in buckets if bucket]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--size", type=int, default=1200)
    parser.add_argument("--cluster-size", type=int, default=1024)
    parser.add_argument("--per-agent", type=int, default=20)
    parser.add_argument("--agents", type=int, default=12)
    parser.add_argument("--cluster-agents", type=int, default=6)
    parser.add_argument("--cluster-per-agent", type=int, default=10)
    parser.add_argument("--wave", type=int, default=4)
    args = parser.parse_args()
    signatures = plan.ida_signatures()
    everything = plan.candidates(1, max(args.size, args.cluster_size), 0x452000, signatures)
    # A region whose callee still needs an LTCG register convention cannot be
    # compiled until that callee is recovered, so it is left for a later wave.
    blocked = [item for item in everything if item["callee_blocked"]]
    open_items = [item for item in everything if not item["callee_blocked"]]
    plain = [item for item in open_items
             if not item["cluster_needed"] and item["size"] <= args.size]
    cluster = [item for item in open_items
               if item["cluster_needed"] and item["size"] <= args.cluster_size]
    dirty = plan.locally_modified()
    plain = [item for item in plain if f"matching2/msvc/{item['source']}" not in dirty]
    cluster = [item for item in cluster if f"matching2/msvc/{item['source']}" not in dirty]
    groups = ([("W", index, group) for index, group in
               enumerate(deal(plain, args.per_agent, args.agents))]
              + [("C", index, group) for index, group in
                 enumerate(deal(cluster, args.cluster_per_agent, args.cluster_agents))])
    backup = plan.WAVE / f"backup{args.wave}"
    briefs = plan.WAVE / f"briefs{args.wave}"
    briefs.mkdir(parents=True, exist_ok=True)
    assignments = []
    for prefix, index, group in groups:
        agent = f"{prefix}{args.wave}{index + 1:02d}"
        lines = [f"# {agent} — {len(group)} region(s), {sum(u['size'] for u in group)} bytes", ""]
        if prefix == "C":
            lines += ["Every region here needs a **native LTCG cluster**: its retail entry "
                      "convention puts an argument in a register MSVC only ever assigns to a "
                      "parameter under /GL. Read `matching2/tools/waves/briefs/CLUSTER.md` "
                      "before starting.", ""]
        for unit in group:
            source = ROOT / "matching2/msvc" / unit["source"]
            target = backup / unit["source"]
            if not target.is_file():
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(source, target)
            lines += [f"## `{unit['source']}`",
                      f"- address `{unit['address']}` size `{unit['size']}` symbol `{unit['symbol']}`",
                      f"- region name `{unit['name']}`",
                      f"- IDA signature: `{unit['signature']}`",
                      f"- ghidra pseudocode: {'yes' if unit['ghidra'] else 'no'}"
                      f"  cluster_needed: {unit['cluster_needed']}"
                      f"  blocked_by: {unit['blocked_by']}",
                      ""]
        (briefs / f"{agent}.md").write_text("\n".join(lines) + "\n")
        assignments.append({"agent": agent, "pool": "cluster" if prefix == "C" else "plain",
                            "units": group})
    (plan.WAVE / f"assignments{args.wave}.json").write_text(
        json.dumps({"excluded_local_changes": sorted(dirty), "assignments": assignments}, indent=2) + "\n")
    print(f"{len(plain)} plain regions -> {sum(1 for a in assignments if a['pool'] == 'plain')} agents; "
          f"{len(cluster)} cluster regions -> {sum(1 for a in assignments if a['pool'] == 'cluster')} agents; "
          f"{len(blocked)} region(s) waiting on an unrecovered callee "
          f"({sum(item['size'] for item in blocked)} bytes)")
    for item in assignments:
        print(f"  {item['agent']} ({item['pool']}): {len(item['units'])} regions, "
              f"{sum(u['size'] for u in item['units'])} bytes, "
              f"{len({u['source'] for u in item['units']})} files")
    return 0


if __name__ == "__main__":
    sys.exit(main())
