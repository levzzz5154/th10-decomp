// 0x0041BEE0..0x0041BEE6: link two intrusive nodes.
// Native LTCG preserves the receiver in EAX and the peer in ECX.
struct H3401LinkNode {
    unsigned char pad_000[4];
    H3401LinkNode* peer_004;
    H3401LinkNode* peer_008;
    __declspec(noinline) H3401LinkNode* Link(
        H3401LinkNode* peer);
};

#pragma code_seg(".text$01target")
H3401LinkNode*
H3401LinkNode::Link(H3401LinkNode* peer) {
    peer->peer_004 = this;
    peer_008 = peer;
    return this;
}
#pragma code_seg()
