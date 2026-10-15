// The update helper the retail body hands the object to. It consumes the object
// on the stack, so the call is made through a __stdcall pointer while the symbol
// keeps the name the project already binds (a direct call, callee pops).
extern "C" int __cdecl asm_FUN_00422660_00422660(void);
typedef int (__stdcall* UpdateObjectFn)(void*);

// 0x00422AA0: the pause menu's draw task; forwards it to 0x00422660.
int __fastcall Pause_OnDraw(void* self) {
    return ((UpdateObjectFn)asm_FUN_00422660_00422660)(self);
}
