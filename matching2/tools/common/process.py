"""Hashing and logged subprocess execution for build tools."""
import hashlib
import subprocess

def sha(data):
    return hashlib.sha256(data).hexdigest()


def run(command, log, cwd, *, env=None, timeout=180):
    result = subprocess.run(command, cwd=cwd, env=env, capture_output=True, text=True, timeout=timeout)
    log.write_text(result.stdout + result.stderr)
    if result.returncode:
        raise RuntimeError(f"command failed ({result.returncode}): see {log}")
    return result
