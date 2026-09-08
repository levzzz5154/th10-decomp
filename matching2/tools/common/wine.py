"""Shared Wine path conversion and MSVC toolkit location."""
import os
from pathlib import Path
import subprocess
from matching2.tools.common.process import sha

DEFAULT_TOOLKIT = Path.home() / ".local/share/th10-toolchains/msvc-13.10.6030"

def winpath(path):
    return subprocess.check_output(
        ["winepath", "-w", str(path)], env={**os.environ, "WINEDEBUG": "-all"},
        text=True, stderr=subprocess.DEVNULL,
    ).strip()


def compiler_environment(toolkit, *, include_library=False):
    env = {**os.environ, "WINEDEBUG": "-all", "INCLUDE": winpath(toolkit / "include")}
    if include_library:
        env["LIB"] = winpath(toolkit / "lib")
    return env


def toolchain_hashes(toolkit, names):
    return {name: sha((toolkit / "bin" / name).read_bytes()) for name in names}

