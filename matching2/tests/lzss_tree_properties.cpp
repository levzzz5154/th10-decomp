// Host-side structural checks for the actual maintained LZSS tree sources.
// Run from the repository root:
// g++ -std=c++17 -O2 -Wno-unknown-pragmas -iquote matching2/msvc/include \
//     matching2/tests/lzss_tree_properties.cpp -o /tmp/th10-lzss-tree-test
// /tmp/th10-lzss-tree-test

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <random>
#include <set>
#include <vector>
#define __declspec(x)
#define __fastcall
#define __stdcall
#include "../msvc/src/game/compression_tree.cpp"
#include "../msvc/src/archive/lzss_tree_remove.cpp"
#include "../msvc/src/archive/lzss_tree_replace.cpp"
#include "../msvc/src/archive/lzss_tree_initialize_root.cpp"
CompressionTree g_compression_tree;
const int root = 0x2000;
void verify_subtree(int node, int parent, int minimum, int maximum, std::set<int>& visited) {
    if (!node) return;
    assert(minimum < node && node < maximum);
    assert(visited.insert(node).second);
    assert(g_compression_tree.nodes[node].parent == parent);
    verify_subtree(g_compression_tree.nodes[node].left, node, minimum, node, visited);
    verify_subtree(g_compression_tree.nodes[node].right, node, node, maximum, visited);
}
int main() {
    std::mt19937 random(0x436210);
    // Initialization replaces both stale child links and publishes root.right.
    g_compression_tree.nodes[17] = {3, 8, 21};
    g_compression_tree.nodes[root].right = 4;
    Lzss_InitializeRoot(17);
    assert(g_compression_tree.nodes[root].right == 17);
    assert(g_compression_tree.nodes[17].parent == root);
    assert(g_compression_tree.nodes[17].left == 0);
    assert(g_compression_tree.nodes[17].right == 0);
    int deletions = 0;
    for (int trial = 0; trial < 50; ++trial) {
        memset(&g_compression_tree, 0, sizeof(g_compression_tree));
        std::vector<int> order;
        for (int i = 1; i <= 127; ++i) order.push_back(i);
        std::shuffle(order.begin(), order.end(), random);
        Lzss_InitializeRoot(order.front());
        std::set<int> expected;
        expected.insert(order.front());
        for (int value : order) {
            if (value == order.front()) continue;
            int parent = root;
            int* link = &g_compression_tree.nodes[root].right;
            while (*link) {
                parent = *link;
                link = value < parent ? &g_compression_tree.nodes[parent].left
                                      : &g_compression_tree.nodes[parent].right;
            }
            *link = value;
            g_compression_tree.nodes[value].parent = parent;
            expected.insert(value);
        }
        std::shuffle(order.begin(), order.end(), random);
        for (int value : order) {
            Lzss_RemoveNode_00436210(value);
            ++deletions;
            expected.erase(value);
            assert(g_compression_tree.nodes[value].parent == 0);
            std::set<int> visited;
            verify_subtree(g_compression_tree.nodes[root].right, root, 0, root, visited);
            assert(visited == expected);
            // Removing an already detached node must leave the active tree intact.
            Lzss_RemoveNode_00436210(value);
            visited.clear();
            verify_subtree(g_compression_tree.nodes[root].right, root, 0, root, visited);
            assert(visited == expected);
        }
    }
    printf("PASS: %d randomized deletions preserve ordering, membership and parent links; detached nodes remain inert.\n", deletions);
}
