"""Shared classification rules for game-code recovery candidates."""
from __future__ import annotations

GAME_TEXT_START = 0x00401000
# These explicitly foreign-owned extents were inspected in wave 21 and proven
# to be valid continuations of their recorded owners. They are not independent
# recovery claims and should not be scheduled again.
INSPECTED_CONTINUATIONS = {
    0x0044D9F0,
    0x00452422,
    0x0045247E,
}

GAME_TEXT_END = 0x00452493


def address_of(region):
    return int(region["address"], 0)


def owner_class(region):
    """Classify manifest ownership without treating missing metadata as foreign."""
    owner = region.get("owner")
    if not owner:
        return "unowned"
    return "self" if int(owner, 0) == address_of(region) else "foreign"


def classify(region, *, game_only=True):
    """Return the scheduling class for one manifest region.

    Only remaining assembly in game code with self or absent ownership is directly
    schedulable. Explicitly foreign-owned records require structural inspection.
    """
    address = address_of(region)
    if region.get("kind") != "asm":
        return "not-assembly"
    if game_only and not GAME_TEXT_START <= address < GAME_TEXT_END:
        return "outside-game"
    ownership = owner_class(region)
    if ownership == "foreign":
        if address in INSPECTED_CONTINUATIONS:
            return "owned-continuation"
        return "structural"
    return "candidate"


def is_candidate(region, *, game_only=True):
    return classify(region, game_only=game_only) == "candidate"
