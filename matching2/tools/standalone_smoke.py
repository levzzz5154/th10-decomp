#!/usr/bin/env python3
"""Build and smoke-test the independent SDL engine.

The process is expected to remain in its event loop.  A successful smoke run
therefore means that it opened the archive, created the renderer, and loaded
both title animation assets before the timeout terminates it.
"""

import argparse
import os
import pathlib
import subprocess
import sys


ROOT = pathlib.Path(__file__).resolve().parent.parent
GAME_DIR = pathlib.Path(
    os.environ.get("TH10_GAME_DIR", str(pathlib.Path.home() / "Games" / "TH10 - Mountain of Faith"))
)
OUTPUT = ROOT / "build" / "th10_standalone"


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--build", action="store_true")
    parser.add_argument("--timeout", type=float, default=5.0)
    args = parser.parse_args()

    if args.build:
        subprocess.run([str(ROOT / "build_standalone.sh")], check=True)
    if not OUTPUT.is_file():
        raise SystemExit("missing standalone binary; run build_standalone.sh")
    archive = GAME_DIR / "th10.dat"
    if not archive.is_file():
        raise SystemExit("missing TH10 archive: {}".format(archive))

    env = os.environ.copy()
    env.setdefault("SDL_AUDIODRIVER", "dummy")
    command = ["timeout", "--signal=TERM", "{}s".format(args.timeout),
               str(OUTPUT), "--game-dir", str(GAME_DIR)]
    result = subprocess.run(command, cwd=ROOT / "build", env=env,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                            text=True)
    output = result.stdout
    if result.returncode not in (124, 143):
        print(output, end="")
        raise SystemExit("standalone process exited before the smoke timeout")
    required = (
        "Textures: player=",
        "Title assets: title=ok title_v=ok",
        "[renderer] OpenGL",
    )
    missing = [marker for marker in required if marker not in output]
    print(output, end="")
    if missing:
        raise SystemExit("standalone smoke missing: {}".format(", ".join(missing)))
    print("standalone smoke: archive, renderer, and title assets initialized")


if __name__ == "__main__":
    main()
