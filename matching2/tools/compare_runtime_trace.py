#!/usr/bin/env python3
"""Compare deterministic TH10 reconstruction/retail JSONL traces."""
from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path
from typing import Any

_FORMAT = "th10-recon-jsonl-v1"
_FORBIDDEN_KEYS = ("pointer", "address", "timestamp", "wall_clock")


def _read(path: Path) -> list[dict[str, Any]]:
    events: list[dict[str, Any]] = []
    for line_number, line in enumerate(
        path.read_text(encoding="utf-8").splitlines(), 1
    ):
        if not line.strip():
            continue
        try:
            value = json.loads(line)
        except json.JSONDecodeError as exc:
            raise ValueError(f"{path}:{line_number}: invalid JSON: {exc}") from exc
        if not isinstance(value, dict):
            raise ValueError(f"{path}:{line_number}: event is not an object")
        event_type = value.get("type")
        if not isinstance(event_type, str) or not event_type:
            raise ValueError(f"{path}:{line_number}: missing event type")
        for key in value:
            if any(token in key.lower() for token in _FORBIDDEN_KEYS):
                raise ValueError(f"{path}:{line_number}: unstable key {key!r}")
        events.append(value)
    if not events:
        raise ValueError(f"{path}: trace is empty")
    header = events[0]
    if header.get("type") != "header" or header.get("format") != _FORMAT:
        raise ValueError(f"{path}: missing {_FORMAT} header")
    return events


def _semantic(event: dict[str, Any]) -> dict[str, Any]:
    # Sequence numbers are stream bookkeeping; compare all execution fields.
    return {key: value for key, value in event.items() if key != "seq"}


def _validate_lifecycles(events: list[dict[str, Any]], path: Path) -> None:
    # Stable identities must have one teardown event. This catches dropped VM
    # trees and manager slots even when two broken traces are otherwise equal.
    for create_type, destroy_type, key in (
        ("vm_create", "vm_destroy", "vm"),
        ("ecl_vm_create", "ecl_vm_destroy", "vm"),
        ("object", "object_destroy", "handle"),
    ):
        created: set[Any] = set()
        destroyed: set[Any] = set()
        for line_number, event in enumerate(events, 1):
            if event.get("type") == create_type:
                identity = event.get(key)
                if identity in created:
                    raise ValueError(
                        f"{path}: duplicate {create_type} identity {identity!r}"
                    )
                created.add(identity)
            elif event.get("type") == destroy_type:
                identity = event.get(key)
                if identity not in created:
                    raise ValueError(
                        f"{path}:{line_number}: {destroy_type} identity "
                        f"{identity!r} was not created"
                    )
                if identity in destroyed:
                    raise ValueError(
                        f"{path}:{line_number}: duplicate {destroy_type} "
                        f"identity {identity!r}"
                    )
                destroyed.add(identity)
        missing = created - destroyed
        if missing:
            raise ValueError(
                f"{path}: {create_type} identities without teardown: "
                f"{sorted(missing)!r}"
            )

    live_vms: set[Any] = set()
    for line_number, event in enumerate(events, 1):
        event_type = event.get("type")
        identity = event.get("vm")
        if event_type == "vm_create":
            live_vms.add(identity)
        elif event_type == "vm_destroy":
            live_vms.discard(identity)
        elif event_type in ("vm_tick", "draw", "object"):
            if identity not in live_vms:
                raise ValueError(
                    f"{path}:{line_number}: {event_type} references non-live "
                    f"VM {identity!r}"
                )

    live_entities: set[Any] = set()
    for line_number, event in enumerate(events, 1):
        if event.get("type") != "entity":
            continue
        identity = event.get("id")
        live = event.get("live")
        if live == 1:
            if identity in live_entities:
                raise ValueError(
                    f"{path}:{line_number}: duplicate live entity {identity!r}"
                )
            live_entities.add(identity)
        elif live == 0:
            if identity not in live_entities:
                raise ValueError(
                    f"{path}:{line_number}: entity teardown {identity!r} "
                    "was not live"
                )
            live_entities.remove(identity)
    if live_entities:
        raise ValueError(
            f"{path}: entity identities without teardown: "
            f"{sorted(live_entities)!r}"
        )


def compare(left: Path, right: Path) -> int:
    try:
        left_events = _read(left)
        right_events = _read(right)
    except ValueError as exc:
        print(f"TRACE_COMPARE_FAIL {exc}", file=sys.stderr)
        return 2
    try:
        _validate_lifecycles(left_events, left)
        _validate_lifecycles(right_events, right)
    except ValueError as exc:
        print(f"TRACE_COMPARE_FAIL {exc}", file=sys.stderr)
        return 2
    if len(left_events) != len(right_events):
        print(
            f"TRACE_COMPARE_FAIL event_count left={len(left_events)} "
            f"right={len(right_events)}",
            file=sys.stderr,
        )
        return 1
    for index, (left_event, right_event) in enumerate(
        zip(left_events, right_events)
    ):
        if _semantic(left_event) != _semantic(right_event):
            print(f"TRACE_COMPARE_FAIL event={index}", file=sys.stderr)
            print(json.dumps(left_event, sort_keys=True), file=sys.stderr)
            print(json.dumps(right_event, sort_keys=True), file=sys.stderr)
            return 1
    print(f"TRACE_COMPARE_PASS events={len(left_events)}")
    return 0


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("left", type=Path)
    parser.add_argument("right", type=Path)
    args = parser.parse_args()
    return compare(args.left, args.right)


if __name__ == "__main__":
    raise SystemExit(main())
