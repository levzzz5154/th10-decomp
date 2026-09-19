#!/usr/bin/env python3
"""Schedule an address-exclusive compiler-reconstruction campaign.

The campaign has four specialized lanes: mechanical translations, structural
ownership repairs, dependency work selected for downstream leverage, and hard
compiler-shape/ABI work. One translation unit is always owned by one agent.
Dry runs classify and deal the current manifest without writing backups,
briefs, claims, or any file below ``matching2/msvc``.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import shutil

import matching2.tools.waves.plan as plan




LANE_GUIDANCE = {
    "mechanical": (
        "Translate the claimed functions directly. Keep the source boundary and "
        "prove exact bytes before reporting success."
    ),
    "structural": (
        "Resolve ownership and function boundaries before translation. Foreign-owned "
        "assembly is scheduled only in this lane; do not claim adjacent addresses."
    ),
    "dependency": (
        "Work in dependency order. These claims rank highly because recovering them "
        "unblocks or teaches high-byte-count callers."
    ),
    "hard": (
        "Investigate compiler shape, ABI, and LTCG context deliberately. Record every "
        "meaningfully different variant rather than cycling cosmetic source edits."
    ),
}

BLOCKED_FIELDS = (
    "closest_byte_count, first_diff, residual_class, variants_tested, next_lever"
)


def _claim_records(assignments):
    claims = []
    seen = set()
    source_agents = {}
    spans = []
    for assignment in assignments:
        for unit in assignment["units"]:
            address = int(unit["address"], 0)
            if address in seen:
                raise ValueError(f"duplicate campaign claim {unit['address']}")
            owner = source_agents.setdefault(unit["source"], assignment["agent"])
            if owner != assignment["agent"]:
                raise ValueError(f"shared campaign source {unit['source']}")
            spans.append((address, address + unit["size"], unit["address"]))
            seen.add(address)
            claims.append({
                "address": unit["address"],
                "source": unit["source"],
                "lane": assignment["lane"],
                "expected_path": unit["expected_path"],
                "target_file": f"matching2/msvc/{unit['source']}",
                "dependencies": unit["dependencies"],
                "score": unit["score"],
                "status": "CLAIMED",
                "agent": assignment["agent"],
            })
    spans.sort()
    for previous, current in zip(spans, spans[1:]):
        if current[0] < previous[1]:
            raise ValueError(f"overlapping campaign claims {previous[2]} and {current[2]}")
    return sorted(claims, key=lambda claim: int(claim["address"], 0))


def _brief(assignment):
    units = assignment["units"]
    lines = [
        f"# {assignment['agent']} — {assignment['lane']} lane",
        "",
        LANE_GUIDANCE[assignment["lane"]],
        "",
        "Edit only each claim's `target_file`. Address claims are exclusive.",
        f"A `BLOCKED` record must contain: `{BLOCKED_FIELDS}`.",
        "",
    ]
    for unit in units:
        dependencies = ", ".join(f"`{value}`" for value in unit["dependencies"]) or "none"
        lines += [
            f"## `{unit['address']}` — `{unit['source']}`",
            f"- target file: `matching2/msvc/{unit['source']}`",
            f"- expected recovery path: `{unit['expected_path']}`",
            f"- size: {unit['size']} bytes; score: {unit['score']}",
            f"- symbol: `{unit['symbol']}`",
            f"- IDA signature: `{unit['signature']}`",
            f"- ghidra pseudocode: {'yes' if unit['ghidra'] else 'no'}",
            f"- cluster needed: {'yes' if unit['cluster_needed'] else 'no'}",
            "",
        ]
    return "\n".join(lines) + "\n"


def _lane_brief(lane, assignments):
    lines = [f"# {lane} lane", "", LANE_GUIDANCE[lane], "",
             f"A `BLOCKED` record must contain: `{BLOCKED_FIELDS}`.", ""]
    for assignment in assignments:
        if assignment["lane"] != lane:
            continue
        lines += [
            f"## {assignment['agent']}",
            *[f"- `{unit['address']}` `{unit['source']}` score {unit['score']}"
              for unit in assignment["units"]],
            "",
        ]
    return "\n".join(lines) + "\n"


def _write_campaign(args, assignments, claims, dirty, lane_counts):
    backup = plan.WAVE / f"backup{args.wave}"
    briefs = plan.WAVE / f"briefs{args.wave}"
    briefs.mkdir(parents=True, exist_ok=True)
    for assignment in assignments:
        for unit in assignment["units"]:
            source = plan.ROOT / "matching2/msvc" / unit["source"]
            target = backup / unit["source"]
            if not target.is_file():
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(source, target)
        (briefs / f"{assignment['agent']}.md").write_text(_brief(assignment))
    for lane in plan.LANES:
        (briefs / f"{lane}.md").write_text(_lane_brief(lane, assignments))

    summary = {
        "schema": 1,
        "wave": args.wave,
        "excluded_local_changes": sorted(dirty),
        "lanes": lane_counts,
        "claims": claims,
    }
    (plan.WAVE / f"claims{args.wave}.json").write_text(
        json.dumps(summary, indent=2, sort_keys=True) + "\n")
    # Keep the historical assignment artifact for existing integration scripts.
    (plan.WAVE / f"assignments{args.wave}.json").write_text(
        json.dumps({"excluded_local_changes": sorted(dirty),
                    "assignments": assignments}, indent=2, sort_keys=True) + "\n")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--size", "--mechanical-max-size", dest="mechanical_max_size",
                        type=int, default=512,
                        help="largest otherwise-simple region kept in the mechanical lane")
    parser.add_argument("--cluster-size", type=int, default=None,
                        help=argparse.SUPPRESS)
    parser.add_argument("--per-agent", type=int, default=8)
    parser.add_argument("--agents", "--mechanical-agents", dest="mechanical_agents",
                        type=int, default=4)
    parser.add_argument("--cluster-agents", "--structural-agents",
                        dest="structural_agents", type=int, default=1)
    parser.add_argument("--cluster-per-agent", type=int, default=None)
    parser.add_argument("--dependency-agents", type=int, default=2)
    parser.add_argument("--hard-agents", type=int, default=1)
    parser.add_argument("--max-address", type=lambda value: int(value, 0),
                        default=plan.GAME_TEXT_END)
    parser.add_argument("--wave", type=int, default=4)
    parser.add_argument("--dry-run", action="store_true",
                        help="print classifications and claims without writing artifacts")
    parser.add_argument("--include-deferred", action="store_true",
                        help="schedule measured blockers even when their required lever has not changed")
    parser.add_argument("--write", action="store_true", help=argparse.SUPPRESS)
    args = parser.parse_args()
    if args.hard_agents != 1:
        parser.error("--hard-agents must be exactly 1")
    lane_agents = {
        "mechanical": args.mechanical_agents,
        "structural": args.structural_agents,
        "dependency": args.dependency_agents,
        "hard": args.hard_agents,
    }
    if not 8 <= sum(lane_agents.values()) <= 10:
        parser.error("campaign allocation must total 8 to 10 agents")
    if any(value < 1 for value in lane_agents.values()):
        parser.error("every lane needs at least one agent")

    signatures = plan.ida_signatures()
    everything = plan.campaign_candidates(
        signatures, max_address=args.max_address,
        mechanical_max_size=args.mechanical_max_size)
    dirty = plan.locally_modified()
    eligible = [item for item in everything
                if (args.include_deferred or not item["deferred"])
                and f"matching2/msvc/{item['source']}" not in dirty]
    per_agent = {lane: args.per_agent for lane in plan.LANES}
    if args.cluster_per_agent is not None:
        per_agent["structural"] = args.cluster_per_agent
    assignments = plan.deal_campaign(eligible, lane_agents, per_agent, args.wave)
    claims = _claim_records(assignments)
    lane_counts = {}
    for lane in plan.LANES:
        lane_counts[lane] = {
            "available": sum(item["lane"] == lane for item in eligible),
            "claimed": sum(claim["lane"] == lane for claim in claims),
            "agents": lane_agents[lane],
        }
    deferred_count = sum(item["deferred"] for item in everything)
    print(f"{len(eligible)} eligible regions; {deferred_count} measured blocker(s) deferred; "
          f"{len(dirty)} locally modified file(s) excluded")
    for lane in plan.LANES:
        counts = lane_counts[lane]
        print(f"  {lane}: {counts['available']} available, {counts['claimed']} claimed, "
              f"{counts['agents']} agent(s)")
    print(f"{len(claims)} exclusive address claims across {len(assignments)} briefs")
    if args.dry_run:
        return 0
    _write_campaign(args, assignments, claims, dirty, lane_counts)
    print(f"wrote {plan.WAVE / f'claims{args.wave}.json'} and "
          f"{plan.WAVE / f'briefs{args.wave}'}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
