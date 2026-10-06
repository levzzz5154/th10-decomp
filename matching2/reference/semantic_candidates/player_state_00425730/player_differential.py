"""Compare the full player state owner with scripted external collaborators."""
import hashlib
import itertools
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from differential import run
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.equivalence import MAP_SYMBOL


def cases():
    for phase, frame, focus, power in itertools.product(
            range(5), [-1, 0, 3, 4, 7, 8, 14, 15, 29, 30, 59, 60], [0, 2], [0, 19, 20, 64, 100]):
        yield {'label': f'state_{phase}_{frame}_{focus}_{power}',
               'player_phase': phase, 'player_frame': frame,
               'input_flags': focus, 'power': power}
    for phase, frame, lives, practice in itertools.product([2, 4], [30, 60], [-1, 0], [0, 1]):
        yield {'label': f'death_{phase}_{frame}_{lives}_{practice}',
               'player_phase': phase, 'player_frame': frame, 'lives': lives,
               'practice_mode': practice}
    for phase, slots, orbit, count, speed, cw in itertools.product(
            [1, 5], [[0], [31], [0, 15, 31]], [0, 1], [1, 5], [0.5, 1., 2.], [0x37f, 0x27f, 0x7f]):
        yield {'label': f'indicators_{phase}_{slots}_{orbit}_{count}_{speed}_{cw}',
               'player_phase': phase, 'player_frame': 31, 'indicator_slots': slots,
               'indicator_motion_flags': orbit, 'indicator_frames': count,
               'player_speed': speed, 'fpcw': cw}
    for frame, invulnerable, same, speed in itertools.product([0, 1, 3, 15], [0, 1, 10], [False, True], [0.5, 1., 2.]):
        yield {'label': f'blink_{frame}_{invulnerable}_{same}_{speed}',
               'player_frame': frame, 'invulnerable': invulnerable,
               'player_previous': frame if same else frame-1, 'player_speed': speed}
    for enabled, script, missing, hold in itertools.product([0, 1], [0, 1], [False, True], [-1025, -1024, 1023, 1024]):
        yield {'label': f'hold_{enabled}_{script}_{missing}_{hold}',
               'config_enabled': enabled, 'front_script': script, 'missing_config': missing,
               'player_frame': 59, 'hold_counter': hold}
    for level in [0, 1, 3, 4]:
        yield {'label': f'history_{level}', 'player_phase': 0, 'player_frame': 31,
               'familiar_level': level, 'mutate_bullet_next': True}
    for phase in [0, 1, 2, 3, 4, 5, -1]:
        yield {'label': f'repeat_{phase}', 'player_phase': phase, 'player_frame': 3,
               'sequence': ['stateupdate', 'stateupdate'], 'movement_changes_position': True}


if __name__ == '__main__':
    work = Path('matching2/build/experiments/player_state_2026_10_06') / (
        sys.argv[1] if len(sys.argv) > 1 else 'initial_graph')
    retail = PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    native = PEImage((work / 'model.exe').read_bytes())
    symbols = {name: int(address, 16) for name, address, _ in
               MAP_SYMBOL.findall((work / 'model.map').read_text())}
    suite = [{'player_state': True, 'sequence': ['stateupdate'], **case} for case in cases()]
    if '--smoke' in sys.argv:
        suite = suite[::50]
    (work / 'player_cases.json').write_text(json.dumps(suite, indent=2) + '\n')
    observations, failures = [], []
    for case in suite:
        expected = run(retail, None, {}, case, full_creation=True)
        actual = run(retail, native, symbols, case, full_creation=True)
        observations.append({'case': case['label'], 'retail': expected, 'native': actual})
        if expected != actual:
            failures.append({'case': case['label'], 'fields': [key for key in expected if expected[key] != actual.get(key)]})
    path = work / 'player_observations.json'
    path.write_text(json.dumps(observations, indent=2) + '\n')
    report = {'cases': len(suite), 'failures': failures,
              'cases_sha256': hashlib.sha256((work / 'player_cases.json').read_bytes()).hexdigest(),
              'observations_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
              'native_pe_sha256': hashlib.sha256(native.data).hexdigest(),
              'smoke': '--smoke' in sys.argv, 'instruction_patches': 0,
              'selection_evidence': False,
              'scope': 'Complete owner including five states, 32 indicators, blink, rectangle bounds, timers, sequence and effect tail.',
              'boundaries': ['collision/record activation, bullet reset/evaluation and virtual retirement scripted',
                             'movement, contact, familiar refresh, initialization and power display scripted',
                             'angle return, item creation, gauge, scene/input mode and VM scripted',
                             'complete native timer, motion, indicator, sequence and effect graph executes']}
    (work / 'player_differential.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    assert not failures
