#ifndef TH10_CHOICE_TREE_HPP
#define TH10_CHOICE_TREE_HPP
struct AnimationTreeNode {
    AnimationTreeNode* object;
    AnimationTreeNode* next;
    unsigned char reserved_008[0x0C];
    AnimationTreeNode* children;
    int children_flagged;
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;
};
#endif
