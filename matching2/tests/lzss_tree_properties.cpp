// Host-side structural checks for the actual maintained LZSS tree sources.
// Run from the repository root:
// g++ -std=c++17 -O2 -Wno-unknown-pragmas -iquote matching2/msvc/include \
//     matching2/tests/lzss_tree_properties.cpp -o /tmp/th10-lzss-tree-test
// /tmp/th10-lzss-tree-test

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <random>
#include <set>
#include <vector>
#define __declspec(x)
#define __fastcall
#define __stdcall
#define __cdecl
extern "C" void* asm_malloc_00452706(unsigned int size) { return malloc(size); }
#include "../msvc/src/archive/lzss.cpp"
LzssNode g_LzssTree[LZSS_WINDOW_SIZE + 1];
unsigned char g_LzssWindow[LZSS_WINDOW_SIZE];
const int root = 0x2000;
void verify_subtree(int node, int parent, int minimum, int maximum, std::set<int>& visited) {
    if (!node) return;
    assert(minimum < node && node < maximum);
    assert(visited.insert(node).second);
    assert(g_LzssTree[node].parent == parent);
    verify_subtree(g_LzssTree[node].smaller_child, node, minimum, node, visited);
    verify_subtree(g_LzssTree[node].larger_child, node, node, maximum, visited);
}
int main() {
    std::mt19937 random(0x436210);
    // Initialization replaces both stale child links and publishes root.larger_child.
    g_LzssTree[17] = {3, 8, 21};
    g_LzssTree[root].larger_child = 4;
    Lzss_InitTree(17);
    assert(g_LzssTree[root].larger_child == 17);
    assert(g_LzssTree[17].parent == root);
    assert(g_LzssTree[17].smaller_child == 0);
    assert(g_LzssTree[17].larger_child == 0);
    int deletions = 0;
    for (int trial = 0; trial < 50; ++trial) {
        memset(g_LzssTree, 0, sizeof(g_LzssTree));
        std::vector<int> order;
        for (int i = 1; i <= 127; ++i) order.push_back(i);
        std::shuffle(order.begin(), order.end(), random);
        Lzss_InitTree(order.front());
        std::set<int> expected;
        expected.insert(order.front());
        for (int value : order) {
            if (value == order.front()) continue;
            int parent = root;
            int* link = &g_LzssTree[root].larger_child;
            while (*link) {
                parent = *link;
                link = value < parent ? &g_LzssTree[parent].smaller_child
                                      : &g_LzssTree[parent].larger_child;
            }
            *link = value;
            g_LzssTree[value].parent = parent;
            expected.insert(value);
        }
        std::shuffle(order.begin(), order.end(), random);
        for (int value : order) {
            Lzss_DeleteString(value);
            ++deletions;
            expected.erase(value);
            assert(g_LzssTree[value].parent == 0);
            std::set<int> visited;
            verify_subtree(g_LzssTree[root].larger_child, root, 0, root, visited);
            assert(visited == expected);
            // Removing an already detached node must leave the active tree intact.
            Lzss_DeleteString(value);
            visited.clear();
            verify_subtree(g_LzssTree[root].larger_child, root, 0, root, visited);
            assert(visited == expected);
        }
    }
    // The compressor and decompressor are inverses, including on inputs with
    // long runs and on incompressible data.
    int round_trips = 0;
    for (int trial = 0; trial < 200; ++trial) {
        std::vector<unsigned char> input(random() % 20000);
        int alphabet = 1 + random() % 256;
        for (unsigned char& byte : input) byte = (unsigned char)(random() % alphabet);
        int packed_size = -1;
        unsigned char* packed = Lzss_Compress(input.data(), (int)input.size(), &packed_size);
        assert(packed && packed_size >= 0 && packed_size <= (int)input.size() * 2);
        std::vector<unsigned char> output(input.size() + 1, 0xA5);
        assert(DecompressDatLzss_00435dc0(packed, packed_size, output.data(),
                                          (unsigned int)input.size()) == output.data());
        assert(memcmp(output.data(), input.data(), input.size()) == 0);
        assert(output[input.size()] == 0xA5);
        free(packed);
        ++round_trips;
    }
    printf("PASS: %d compress/decompress round trips.\n", round_trips);
    printf("PASS: %d randomized deletions preserve ordering, membership and parent links; detached nodes remain inert.\n", deletions);
}
