struct ExceptionNode { void* object; ExceptionNode* next; };
struct ThreadData { unsigned char padding[0x88]; ExceptionNode* exceptions; };
extern "C" ThreadData* __cdecl crt_getptd();

extern "C" int __cdecl crt_IsExceptionObjectToBeDestroyed(void* object) {
    ExceptionNode* node = crt_getptd()->exceptions;
    while (node) {
        if (node->object == object) return 0;
        node = node->next;
    }
    return 1;
}
