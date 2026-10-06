"""Execute the genuine sequence-update/walker/spawn chain without ABI patches."""
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
    for rank, alternate, frame, repeat in itertools.product(
            [0, 19, 20, 80, 100, 65535], [0, 1], [-1, 0, 1, 2, 14, 15, 16, 19, 31], [0, 1]):
        yield {'label': f'schedule_{rank}_{alternate}_{frame}_{repeat}',
               'schedule_rank': rank, 'schedule_alternate': alternate,
               'schedule_frame': frame, 'schedule_repeat': repeat}
    for running, repeat, frame in itertools.product([0, 2], [0, 1], [-1, 0, 15]):
        yield {'label': f'schedule_inactive_{running}_{repeat}_{frame}',
               'schedule_running': running, 'schedule_repeat': repeat,
               'schedule_frame': frame}
    for speed, flags, frame, cw in itertools.product(
            [0.5, 1., 2.], [0, 1], [-1, 14, 15, 16], [0x37f, 0x27f, 0x7f]):
        yield {'label': f'schedule_clock_{speed}_{flags}_{frame}_{cw}',
               'schedule_speed': speed, 'schedule_timer_flags': flags,
               'schedule_frame': frame, 'schedule_repeat': 1, 'fpcw': cw}
    for rank, sequence in itertools.product([0, 20, 40],
            [['schedule', 'schedule', 'effect', 'sweep'],
             ['schedule', 'effect', 'schedule', 'sweep']]):
        yield {'label': f'schedule_sequence_{rank}_{sequence}',
               'schedule_rank': rank, 'schedule_repeat': 1, 'sequence': sequence,
               'loaded_script': True, 'spawn_sound': 3}
    for frame, repeat in itertools.product([0, 1, 15], [0, 1]):
        yield {'label': f'schedule_same_frame_{frame}_{repeat}',
               'schedule_frame': frame, 'schedule_previous': frame,
               'schedule_repeat': repeat}


if __name__ == '__main__':
    work = Path('matching2/build/experiments/scheduled_effect_2026_10_06') / (
        sys.argv[1] if len(sys.argv) > 1 else 'sequence_graph')
    retail = PEImage(Path('matching2/build/oracle/th10.exe').read_bytes())
    native = PEImage((work / 'model.exe').read_bytes())
    symbols = {name: int(address, 16) for name, address, _ in
               MAP_SYMBOL.findall((work / 'model.map').read_text())}
    suite = [{'spawn': True, 'schedule': True, 'sequence': ['schedule'], **case}
             for case in cases()]
    case_path = work / 'schedule_cases.json'
    case_path.write_text(json.dumps(suite, indent=2) + '\n')
    observations, failures = [], []
    helper_calls = {name: 0 for name in ['update','dispatch','set','tick','advance','spawn']}
    for case in suite:
        expected = run(retail, None, {}, case, full_creation=True)
        actual = run(retail, native, symbols, case, full_creation=True)
        for call in expected['calls']:
            if call[0] == 'schedule_helper':
                helper_calls[call[1]] += 1
        expected.pop('retail_coverage')
        actual.pop('retail_coverage')
        observations.append({'case': case['label'], 'retail': expected, 'native': actual})
        if expected != actual:
            failures.append(case['label'])
    path = work / 'schedule_observations.json'
    path.write_text(json.dumps(observations, indent=2) + '\n')
    assert all(helper_calls.values()), helper_calls
    report = {'executed_helper_calls': helper_calls, 'cases': len(suite), 'failures': failures,
              'cases_sha256': hashlib.sha256(case_path.read_bytes()).hexdigest(),
              'observations_sha256': hashlib.sha256(path.read_bytes()).hexdigest(),
              'native_pe_sha256': hashlib.sha256(native.data).hexdigest(),
              'executed': 'complete sequence Update, private Dispatch, spawn and timer/scheduler helpers',
              'entry_abi': 'retail EAX receiver; actual rooted C++ member ECX receiver; no entry-byte patches',
              'instruction_patches': 0, 'selection_evidence': False}
    (work / 'schedule_differential.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
    assert not failures
