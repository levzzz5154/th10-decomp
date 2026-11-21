"""Read the matching project's reference manifest, verified retail text and symbol addresses."""
import json
import os
from pathlib import Path

from matching2.tools.common.pe import PEImage
from matching2.tools.common.process import sha
from matching2.tools.common.project_paths import ROOT, project_support


def default_oracle():
    """Prefer a stable copy: a running build replaces the normal output."""
    override = os.environ.get('TH10_ORACLE')
    if override and Path(override).is_file():
        return Path(override)
    stable = ROOT / 'matching2/build/oracle/th10.exe'
    return stable if stable.is_file() else ROOT / 'matching2/build/msvc/th10.exe'


def load_manifest(path):
    config = json.loads(path.read_text())
    reference = json.loads(project_support(path.parent, 'pe_layout.json').read_text())['reference']
    if config['text_sha256'] != reference['text_section_sha256']:
        raise ValueError('project manifest does not match the supported retail image')
    return config


def load_verified_image(path, config):
    """Return the PE and its verified .text bytes from the same read."""
    image = PEImage(Path(path).read_bytes())
    text = image.read(int(config['text_start'], 0), config['text_bytes'])
    if sha(text) != config['text_sha256']:
        raise ValueError(f'{path} does not contain the supported .text bytes')
    return image, text


def load_oracle(path, config):
    """Read the verified .text bytes for a code comparison."""
    _, text = load_verified_image(path, config)
    return text


def region_directory(config, regions):
    """Map public definitions and manifest bindings to their retail addresses."""
    bindings = {name: int(address, 0) for name, address in config['symbols'].items()}
    for region in regions:
        bindings.setdefault(region['symbol'], int(region['address'], 0))
    return bindings
