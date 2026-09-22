struct ExceptionNode { void* object; ExceptionNode* next; };
struct ThreadData { unsigned char padding[0x88]; ExceptionNode* exceptions; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();

extern "C" int __cdecl asm_IsExceptionObjectToBeDestroyed_00462a13(void* object) {
    ExceptionNode* node = asm_getptd_00456357()->exceptions;
    while (node) {
        if (node->object == object) return 0;
        node = node->next;
    }
    return 1;
}
