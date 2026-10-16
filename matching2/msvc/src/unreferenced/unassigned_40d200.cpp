// 0x0040D200: unlink the list node at this+0x116C from the manager's pair of
// head pointers and decrement its count.
struct Link2 {
    void* field_000;
    Link2* field_004;
    Link2* field_008;
};
struct Node {
    unsigned char pad_000[0x116C];
    unsigned char link_116c[4];
    Link2* field_1170;
    Link2* field_1174;
};
struct Manager2 {
    unsigned char pad_000[0x58];
    Link2* head_058;
    Link2* head_05c;
    int count_060;
};
extern "C" int __fastcall RemoveNode(Manager2* manager, Node* node);
int __fastcall RemoveNode(Manager2* manager, Node* node) {
    Link2* link = (Link2*)node->link_116c;
    if (manager->head_058 == link) manager->head_058 = node->field_1170;
    if (manager->head_05c == link) manager->head_05c = node->field_1174;
    if (link->field_004 != 0) link->field_004->field_008 = link->field_008;
    if (link->field_008 != 0) link->field_008->field_004 = link->field_004;
    link->field_004 = 0;
    link->field_008 = 0;
    return --manager->count_060;
}
