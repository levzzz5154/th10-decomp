extern "C" void** data_00473ad4;
extern "C" void* data_00473ab0;
extern "C" void* data_00473ab4;
extern "C" void* data_00473ab8;
extern "C" void* data_00473abc;
extern "C" void* data_00473ac0;
extern "C" void* data_00473ac4;
extern "C" void* data_00473ac8;
extern "C" void __cdecl asm_free_00452422(void* memory);

extern "C" void __cdecl asm_free_lconv_mon_0045b81b(void* monetary_info) {
    if (monetary_info == 0) {
        return;
    }

    void** fields = static_cast<void**>(monetary_info);
    void** active_defaults = data_00473ad4;

    void* value = fields[3];
    if (value != active_defaults[3] && value != data_00473ab0) {
        asm_free_00452422(value);
    }

    value = fields[4];
    if (value != active_defaults[4] && value != data_00473ab4) {
        asm_free_00452422(value);
    }

    value = fields[5];
    if (value != active_defaults[5] && value != data_00473ab8) {
        asm_free_00452422(value);
    }

    value = fields[6];
    if (value != active_defaults[6] && value != data_00473abc) {
        asm_free_00452422(value);
    }

    value = fields[7];
    if (value != active_defaults[7] && value != data_00473ac0) {
        asm_free_00452422(value);
    }

    value = fields[8];
    if (value != active_defaults[8] && value != data_00473ac4) {
        asm_free_00452422(value);
    }

    value = fields[9];
    if (value != active_defaults[9] && value != data_00473ac8) {
        asm_free_00452422(value);
    }
}
