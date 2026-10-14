import unittest

from matching2.tools.matching.equivalence import (
    CODE_SHIFT, EquivalenceError, absolute_sites, apply_bodies, canonical_sib, cap_function_extent, compare_tail, find_differences, gate,
    normalize, rebase_bound_calls, rebase_map, validate_code_extent)
from matching2.tools.matching.progress import recovered, summarize


def rows(start, *instructions):
    listing, offset = [], 0
    for size, text in instructions:
        listing.append((offset, text))
        offset += size
    return normalize(listing, start, offset, offset + 8, lambda value, spelling: spelling)


class EquivalenceTests(unittest.TestCase):
    def test_declared_tail_must_include_the_complete_jump_table(self):
        start = 0x4236f0
        code = b'\xff\x24\x85' + (start + 16).to_bytes(4, 'little') + b'\x90' * 9
        code += (start + 7).to_bytes(4, 'little') * 8
        validate_code_extent(code, start, 16)
        # The old replay-submenu layout included seven entries as code and
        # copied only four bytes of tail data into the executable.
        with self.assertRaisesRegex(EquivalenceError, 'omit or misalign table entries'):
            validate_code_extent(code, start, 44)

    def test_extraction_stops_before_the_next_function_not_at_a_data_symbol(self):
        link_map = '''
 0001:00000000       _SaveHints@8              00401000 f   model_00.obj
 0001:00000010       _local_constant           00401010     model_00.obj
 0000:0044b740       _absolute_callee          0044b740     <absolute>
 0001:000008c0       _WriteShared              004018c0 f i model_01.obj
'''
        self.assertEqual(cap_function_extent(link_map, 0x401000, 2247), 2240)
        self.assertEqual(cap_function_extent(link_map, 0x401000, 2000), 2000)
        self.assertEqual(cap_function_extent(link_map, 0x4018c0, 100), 100)

    def test_base_index_order_is_canonical_only_at_scale_one(self):
        self.assertEqual(canonical_sib('mov ecx,DWORD PTR [esi+eax*1+0x8]'),
                         canonical_sib('mov ecx,DWORD PTR [eax+esi*1+0x8]'))
        self.assertNotEqual(canonical_sib('mov ecx,DWORD PTR [esi+eax*4]'),
                            canonical_sib('mov ecx,DWORD PTR [eax+esi*4]'))

    def test_swap_is_counted_and_other_changes_are_hunks(self):
        retail = rows(0x1000, (3, 'mov ecx,DWORD PTR [esi+eax*1]'), (4, 'mov DWORD PTR [esp+0x20],ecx'), (1, 'ret'))
        model = rows(0x2000, (3, 'mov ecx,DWORD PTR [eax+esi*1]'), (4, 'mov DWORD PTR [esp+0x24],ecx'), (1, 'ret'))
        swaps, hunks, mapping = find_differences(retail, model)
        self.assertEqual(swaps, 1)
        self.assertEqual(hunks, [{'offset': '0x3', 'retail': ['mov DWORD PTR [esp+0x20],ecx'],
                                  'model': ['mov DWORD PTR [esp+0x24],ecx']}])
        self.assertEqual(mapping, {0: 0, 3: 3, 7: 7})

    def test_branch_targets_follow_the_alignment(self):
        retail = rows(0x1000, (2, 'jmp 0x1004'), (2, 'nop'), (1, 'ret'))
        same = rows(0x2000, (2, 'jmp 0x2004'), (2, 'nop'), (1, 'ret'))
        other = rows(0x2000, (2, 'jmp 0x2002'), (2, 'nop'), (1, 'ret'))
        self.assertEqual(find_differences(retail, same)[:2], (0, []))
        with self.assertRaises(EquivalenceError):
            find_differences(retail, other)

    def test_branches_follow_a_block_placed_elsewhere(self):
        block = [(2, 'mov eax,0x1'), (1, 'ret')]
        other = [(2, 'xor eax,eax'), (2, 'xor ecx,ecx'), (2, 'xor edx,edx'), (2, 'jmp 0x%x')]
        retail = rows(0x1000, (2, 'je 0x1004'), (2, 'jmp 0x1007'), *block,
                      *other[:3], (2, 'jmp 0x1000'))
        model = rows(0x2000, (2, 'je 0x200c'), (2, 'jmp 0x2004'),
                     *other[:3], (2, 'jmp 0x2000'), *block)
        swaps, hunks, mapping = find_differences(retail, model)
        self.assertEqual((swaps, len(hunks)), (0, 2))
        self.assertEqual(mapping[4], 0xc)
        wrong = rows(0x2000, (2, 'je 0x200e'), (2, 'jmp 0x2004'),
                     *other[:3], (2, 'jmp 0x2000'), *block)
        with self.assertRaises(EquivalenceError):
            find_differences(retail, wrong)

    def test_branch_into_a_removed_run_may_land_where_the_model_resumes(self):
        retail = rows(0x1000, (2, 'je 0x1004'), (2, 'jmp 0x1006'), (2, 'mov esi,eax'), (1, 'push esi'), (1, 'ret'))
        model = rows(0x2000, (2, 'je 0x2004'), (2, 'jmp 0x2004'), (1, 'push esi'), (1, 'ret'))
        self.assertEqual(len(find_differences(retail, model)[1]), 1)

    def test_frame_offset_is_counted_only_for_the_named_distances(self):
        retail = rows(0x1000, (4, 'mov DWORD PTR [esp+0x20],ecx'), (4, 'mov eax,DWORD PTR [esp+0x14]'), (1, 'ret'))
        model = rows(0x2000, (4, 'mov DWORD PTR [esp+0x10],ecx'), (4, 'mov eax,DWORD PTR [esp+0x18]'), (1, 'ret'))
        counts = {}
        swaps, hunks, _ = find_differences(retail, model, (0x10,), counts)
        self.assertEqual((swaps, counts['frame']), (0, 1))
        self.assertEqual(hunks, [{'offset': '0x4', 'retail': ['mov eax,DWORD PTR [esp+0x14]'],
                                  'model': ['mov eax,DWORD PTR [esp+0x18]']}])

    def test_branch_may_enter_a_tail_merged_differently(self):
        tail = [(2, 'xor eax,eax'), (1, 'ret')]
        retail = rows(0x1000, (2, 'je 0x1005'), *tail, *tail)
        model = rows(0x2000, (2, 'je 0x2002'), *tail)
        self.assertEqual(len(find_differences(retail, model)[1]), 1)
        longer = rows(0x1000, (2, 'je 0x1005'), *tail, (1, 'push esi'), *tail)
        with self.assertRaises(EquivalenceError):
            find_differences(longer, model)

    def test_unproven_branch_targets_are_listed_only_on_request(self):
        retail = rows(0x1000, (2, 'jmp 0x1004'), (2, 'nop'), (1, 'ret'))
        other = rows(0x2000, (2, 'jmp 0x2002'), (2, 'nop'), (1, 'ret'))
        hunks = find_differences(retail, other, list_branches=True)[1]
        self.assertEqual(hunks, [{'offset': '0x0', 'retail': ['jmp L+0x4'], 'model': ['jmp L+0x2']}])
        unproven = []
        compare_tail((0x1004).to_bytes(4, 'little'), (0x2000).to_bytes(4, 'little'), 0x1000, 0x2000, 8,
                     {0: 0, 4: 4}, unproven)
        self.assertEqual(unproven, [{'offset': 'table+0x0', 'retail': ['L+0x4'], 'model': ['L+0x0']}])

    def test_absolute_fields_are_those_that_move_with_the_image(self):
        delta = 0x0fc00000
        first = b'\xa1' + (0x406030).to_bytes(4, 'little') + b'\xe8' + (0x1000).to_bytes(4, 'little') + b'\xc3'
        second = (b'\xa1' + (0x406030 + delta).to_bytes(4, 'little')
                  + b'\xe8' + ((0x1000 + CODE_SHIFT - delta) & 0xffffffff).to_bytes(4, 'little') + b'\xc3')
        self.assertEqual(absolute_sites(first, second, delta), ([1], []))
        with self.assertRaises(EquivalenceError):
            absolute_sites(first, first[:1] + (0x406031 + delta).to_bytes(4, 'little') + first[5:], delta)

    def test_stored_address_of_a_bound_function_is_told_from_a_call_to_it(self):
        delta = 0x0fc00000
        first = b'\x68' + (0x3a3a0).to_bytes(4, 'little') + b'\xc3'
        second = b'\x68' + (0x3a3a0 + CODE_SHIFT).to_bytes(4, 'little') + b'\xc3'
        self.assertEqual(absolute_sites(first, second, delta), ([], [1]))

    def test_gate_rejects_other_callees_and_addresses_whatever_is_listed(self):
        retail = rows(0x401000, (5, 'call 0x44b8e0'), (5, 'push 0x43a3a0'), (1, 'ret'))
        self.assertEqual(gate({}, retail, retail, [], []), [])
        model = rows(0x401000, (5, 'call 0x44b810'), (5, 'push 0x3a3a0'), (1, 'ret'))
        hunk = {'offset': '0x0', 'retail': ['call 0x44b8e0'], 'model': ['call 0x44b810']}
        reasons = '\n'.join(gate({}, retail, model, [hunk], ['code-shape']))
        self.assertIn('the model calls what retail does not: 0x44b810', reasons)
        self.assertIn('retail calls what the model does not: 0x44b8e0', reasons)
        self.assertIn('retail names what the model does not: 0x43a3a0', reasons)
        self.assertIn('replaces 0x44b8e0 by 0x44b810', reasons)

    def test_gate_holds_tie_break_classes_to_the_same_flow_and_all_classes_to_a_budget(self):
        body = [(2, 'mov eax,ecx')] * 30
        retail = rows(0x401000, (2, 'call ebx'), *body, (1, 'ret'))
        model = rows(0x401000, (2, 'call ebp'), *body, (1, 'ret'))
        renamed = {'offset': '0x0', 'retail': ['call ebx'], 'model': ['call ebp']}
        self.assertEqual(gate({}, retail, model, [renamed], ['register-choice']), [])
        dropped = {'offset': '0x0', 'retail': ['call ebx'], 'model': []}
        self.assertIn('changes calls or branches', gate({}, retail, model, [dropped], ['evaluation-order'])[0])
        wide = {'offset': '0x2', 'retail': ['mov eax,ecx'] * 5, 'model': ['mov eax,edx'] * 5}
        self.assertEqual(gate({}, retail, model, [wide], ['register-choice']), [])
        self.assertIn('structural differences cover 5 of 32', gate({}, retail, model, [wide], ['code-shape'])[0])
        # Unclassified differences, as when recording, count as structural.
        self.assertIn('structural differences', gate({}, retail, model, [wide], None)[0])
        self.assertIn('recorded differences cover 11 of 32',
                      '\n'.join(gate({}, retail, model, [dict(wide, retail=wide['retail'] * 2 + ['nop'])],
                                     ['register-choice'])))

    def test_structural_label_cannot_accept_a_truncated_return(self):
        body = [(2, 'mov eax,ecx')] * 30
        retail = rows(0x401000, *body, (3, 'ret 0x4'))
        model = rows(0x401000, *body)
        hunk = {'offset': '0x3c', 'retail': ['ret 0x4'], 'model': []}
        for classes in (['code-shape'], ['block-order'], None):
            self.assertIn('return instructions or stack cleanup differ',
                          '\n'.join(gate({}, retail, model, [hunk], classes)))

    def test_gate_rejects_changed_return_cleanup(self):
        body = [(2, 'mov eax,ecx')] * 30
        retail = rows(0x401000, *body, (3, 'ret 0x4'))
        model = rows(0x401000, *body, (1, 'ret'))
        hunk = {'offset': '0x3c', 'retail': ['ret 0x4'], 'model': ['ret']}
        self.assertIn('return instructions or stack cleanup differ',
                      '\n'.join(gate({}, retail, model, [hunk], ['code-shape'])))

    def test_gate_allows_merged_identical_return_sites(self):
        body = [(2, 'mov eax,ecx')] * 30
        retail = rows(0x401000, *body, (3, 'ret 0x4'), (3, 'ret 0x4'))
        model = rows(0x401000, *body, (3, 'ret 0x4'))
        hunk = {'offset': '0x3f', 'retail': ['ret 0x4'], 'model': []}
        self.assertEqual(gate({}, retail, model, [hunk], ['code-shape']), [])

    def test_gate_rejects_an_instruction_cut_at_the_extraction_boundary(self):
        body = [(2, 'mov eax,ecx')] * 30
        retail = rows(0x401000, *body, (1, 'ret'))
        for invalid in ('.byte 0xe9', '.byte 0x83', '(bad)', 'data16'):
            model = rows(0x401000, *body, (1, 'ret'), (1, invalid))
            hunk = {'offset': '0x3d', 'retail': [], 'model': [invalid]}
            self.assertIn('incomplete or invalid instruction',
                          '\n'.join(gate({}, retail, model, [hunk], ['code-shape'])))

    def test_rebase_bound_calls_rewrites_an_authorized_in_window_call(self):
        rows = [(0, 'call 0x2000'), (5, 'ret')]
        body = bytearray(b'\xe8\xfb\xff\xff\xff\xc3')
        rebased = rebase_bound_calls(rows, body, 0x1000, {0x2000: 0x9000})
        self.assertEqual(rebased, [{'offset': '0x0', 'model': 'call 0x2000',
                                    'retail': 'call 0x9000'}])
        self.assertEqual(bytes(body), b'\xe8\xfb\x7f\x00\x00\xc3')

    def test_rebase_bound_calls_leaves_unbound_calls_alone(self):
        rows = [(0, 'call 0x2000'), (5, 'ret')]
        body = bytearray(b'\xe8\xfb\xff\xff\xff\xc3')
        rebased = rebase_bound_calls(rows, body, 0x1000, {0x3000: 0x9000})
        self.assertEqual(rebased, [])
        self.assertEqual(bytes(body), b'\xe8\xfb\xff\xff\xff\xc3')

    def test_rebase_bound_calls_skips_calls_of_other_lengths(self):
        rows = [(0, 'jmp 0x2000'), (2, 'ret')]
        body = bytearray(b'\xe9\xfb\x00\x00\x00\xc3')
        rebased = rebase_bound_calls(rows, body, 0x1000, {0x2000: 0x9000})
        self.assertEqual(rebased, [])
        self.assertEqual(bytes(body), b'\xe9\xfb\x00\x00\x00\xc3')

    def test_rebase_map_authorizes_an_outside_region_semantic_callee(self):
        regions = [{'kind': 'semantic', 'symbol': '?WriteShared@@YGHPBXI@Z',
                    'address': '0x9000', 'name': 'semantic_WriteShared', 'size': 76}]
        rebind = rebase_map({'?WriteShared@@YGHPBXI@Z': '0x9000'},
                            {'?WriteShared@@YGHPBXI@Z': 0x1400}, 0x1000, 0x800,
                            0x1000, 0x800, {'?WriteShared@@YGHPBXI@Z': [(0x9000, 'semantic_WriteShared')]},
                            'probe')
        self.assertEqual(rebind, ({0x1400: 0x9000},
                                  [{'symbol': '?WriteShared@@YGHPBXI@Z', 'model': '0x1400',
                                    'retail': '0x9000',
                                    'verified': 'semantic region semantic_WriteShared (byte-exact elsewhere)'}]))

    def test_rebase_map_refuses_an_unverified_in_window_callee(self):
        with self.assertRaises(EquivalenceError) as caught:
            rebase_map({'?Callee@@YGHPBXI@Z': '0x9000'},
                       {'?Callee@@YGHPBXI@Z': 0x1400}, 0x1000, 0x800,
                       0x1000, 0x800, {}, 'probe')
        self.assertIn('without a verified semantic region', str(caught.exception))

    def test_rebase_map_skips_bindings_inside_the_region(self):
        rebind = rebase_map({'?Inside@@YGHPBXI@Z': '0x1400'},
                            {'?Inside@@YGHPBXI@Z': 0x2000}, 0x1000, 0x800,
                            0x1000, 0x800, {}, 'probe')
        self.assertEqual(rebind, ({}, []))

    def test_bodies_replace_only_their_regions(self):
        regions = [{'name': 'a', 'address': '0x401000', 'size': 2}, {'name': 'b', 'address': '0x401002', 'size': 3}]
        self.assertEqual(apply_bodies(b'12345', regions, {'b': b'xyz'}), b'12xyz')
        with self.assertRaises(EquivalenceError):
            apply_bodies(b'12345', regions, {'b': b'xy'})

    def test_jump_table_pointers_are_rebased_and_data_is_exact(self):
        mapping = {0: 0, 4: 4}
        retail = (0x1004).to_bytes(4, 'little') + b'\x01\x02'
        compare_tail(retail, (0x2004).to_bytes(4, 'little') + b'\x01\x02', 0x1000, 0x2000, 8, mapping)
        with self.assertRaises(EquivalenceError):
            compare_tail(retail, (0x2000).to_bytes(4, 'little') + b'\x01\x02', 0x1000, 0x2000, 8, mapping)
        with self.assertRaises(EquivalenceError):
            compare_tail(retail, (0x2004).to_bytes(4, 'little') + b'\x01\x03', 0x1000, 0x2000, 8, mapping)

    def test_progress_counts_equivalent_apart_from_exact_and_assembly(self):
        regions = [{'name': 'a', 'kind': 'semantic', 'size': 30}, {'name': 'b', 'kind': 'asm', 'size': 50},
                   {'name': 'c', 'kind': 'asm', 'size': 20}]
        summary = summarize(regions, [{'region': 'b', 'layout': 'x.json'}])
        self.assertEqual(summary['bytes'], {'semantic': 30, 'equivalent': 50, 'asm': 20,
                                            'library': 0, 'data': 0, 'padding': 0})
        self.assertIn('80.0% of bytes', recovered(summary))
        self.assertIn('byte-exact alone 30.0%', recovered(summary))
        with self.assertRaises(ValueError):
            summarize(regions, [{'region': 'a', 'layout': 'x.json'}])
        with self.assertRaises(ValueError):
            summarize(regions, [{'region': 'missing', 'layout': 'x.json'}])


if __name__ == '__main__':
    unittest.main()
