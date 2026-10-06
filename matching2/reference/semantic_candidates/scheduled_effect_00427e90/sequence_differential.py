"""Execute real effect-update/sweep sequences on shared records and animation lists."""
import hashlib
import itertools
import json
from pathlib import Path
import sys

from differential import run, PEImage, MAP_SYMBOL


def cases():
    sequences = [('effect', 'sweep'), ('sweep', 'effect'),
                 ('effect', 'sweep', 'effect'), ('sweep', 'effect', 'sweep')]
    for sequence, kind, state, callback, secondary in itertools.product(
            sequences, [0, 2, 3], [1, 2],
            ['', 'clear_state', 'clear_primary', 'move'], [False, True]):
        yield {'sequence': sequence, 'effect_callback': callback,
               'effect_secondary': secondary, 'children': True,
               'center': (16., 200.), 'size': (64., 64.),
               'pickups': [{'type': kind, 'state': state}]}
    for sequence, kind, slot, control in itertools.product(
            sequences, [0, 2, 3], [0, 63, 127], [0x37f, 0x27f, 0x7f]):
        yield {'sequence': sequence, 'fpcw': control, 'effect_secondary': True,
               'loaded_script': True, 'children': True,
               'center': (0., 200.), 'size': (64., 64.),
               'pickups': [{'slot': slot, 'type': kind, 'current': 10}],
               'regions': [{'slot': 31, 'flags': 3, 'radius': 100., 'value': 11}]}
    for sequence, angle, orbit in itertools.product(sequences, [0., 0.5], [False, True]):
        yield {'sequence': sequence, 'effect_secondary': True,
               'pickups': [{'type': 3, 'motion_angle': angle, 'orbit': orbit}],
               'regions': [{'angle': 0.5, 'size': (64., 64.), 'value': -7}]}
    for sequence, state in itertools.product(sequences, [0, 1, 2]):
        yield {'sequence': sequence, 'effect_callback': 'clear_state',
               'pickups': [{'slot': slot, 'type': 3, 'state': state}
                           for slot in range(128)]}


def main():
    work = Path('matching2/build/experiments/scheduled_effect_2026_10_06') / (
        sys.argv[1] if len(sys.argv) > 1 else 'sequence_graph')
    retail = PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    native = PEImage((work / 'model.exe').read_bytes())
    symbols = {name: int(value, 16) for name, value, _ in
               MAP_SYMBOL.findall((work / 'model.map').read_text())}
    suite = [dict(case, label=f'sequence_{index}') for index, case in enumerate(cases())]
    observations, failures = [], []
    (work / 'sequence_cases.json').write_text(json.dumps(suite, indent=2) + '\n')
    for case in suite:
        expected = run(retail, None, {}, case, full_creation=True)
        actual = run(retail, native, symbols, case, full_creation=True)
        observations.append({'case': case['label'], 'retail': expected, 'native': actual})
        if expected != actual:
            failures.append({'case': case['label'],
                             'fields': [key for key in expected if expected[key] != actual.get(key)]})
    artifact = work / 'sequence_observations.json'
    artifact.write_text(json.dumps(observations, indent=2) + '\n')
    report = {'cases': len(suite), 'failures': failures,
              'caller_invocations': {name: sum(case['sequence'].count(name) for case in suite)
                                     for name in ['effect', 'sweep']},
              'native_pe_sha256': hashlib.sha256(native.data).hexdigest(),
              'observations_sha256': hashlib.sha256(artifact.read_bytes()).hexdigest(),
              'scope': 'Both complete real callers execute in sequence on the same records and animation lists; complete state, call results/order, preserved registers, cleanup and x87 balance.',
              'scripted_boundaries': ['successful operator new', 'animation VM supplies a valid sprite', 'descriptor callback'],
              'shared_raw_retail_boundaries': ['SetPolar', 'NormalizeAngle', 'floor', '_ftol2', 'already-recovered constructor'],
              'instruction_patches': 0, 'selection_evidence': False}
    (work / 'sequence_differential.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2), flush=True)
    return bool(failures)


if __name__ == '__main__':
    sys.exit(main())
