// The update helper the retail body hands the object to. It consumes the object
// on the stack, so the call is made through a __stdcall pointer while the symbol
// keeps the name the project already binds (a direct call, callee pops).
extern "C" int __cdecl asm_FUN_00422660_00422660(void);
typedef int (__stdcall* UpdateObjectFn)(void*);

// 0x00422AA0: FUN_00422aa0 - forward an object to the update helper.
int __fastcall FUN_00422aa0(void* self) {
    return ((UpdateObjectFn)asm_FUN_00422660_00422660)(self);
}
