import unittest

from matching2.tools.matching.equivalence import (
    EquivalenceError, absolute_sites, apply_bodies, canonical_sib, compare_tail, find_differences, normalize)
from matching2.tools.matching.progress import recovered, summarize


def rows(start, *instructions):
    listing, offset = [], 0
    for size, text in instructions:
        listing.append((offset, text))
        offset += size
    return normalize(listing, start, offset, offset + 8, lambda value, spelling: spelling)


class EquivalenceTests(unittest.TestCase):
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
                  + b'\xe8' + ((0x1000 - delta) & 0xffffffff).to_bytes(4, 'little') + b'\xc3')
        self.assertEqual(absolute_sites(first, second, delta), [1])
        with self.assertRaises(EquivalenceError):
            absolute_sites(first, first[:1] + (0x406031 + delta).to_bytes(4, 'little') + first[5:], delta)

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
