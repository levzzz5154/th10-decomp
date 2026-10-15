// 0x0040C5E0..0x0040C6C4: the ECL VM base class's virtual methods (vtable
// 0x0046D0D8). The enemy (vtable 0x0046D0C0) overrides every slot; these
// defaults answer nothing. Nothing calls them directly, so they are ordinary
// members here with the virtual methods' bytes (this in ECX, callee pops).
//
//   +0x00 Run                  enemy 0x0040E760
//   +0x04 GetIntValue          enemy 0x00411FC0
//   +0x08 GetFloatVarAddress   enemy 0x00412300
//   +0x0C GetFloatValue        enemy 0x00412350
//   +0x10 GetIntVarAddress     enemy 0x004126D0
//   +0x14 deleting destructor  base 0x0040C7B0, enemy 0x0040CC50
extern "C" unsigned char data_00470b04;   // 0.0f

struct EclVm {
    int Run();
    int GetIntValue(int id);
    float* GetFloatVarAddress(int id);
    double GetFloatValue(int id);
    int* GetIntVarAddress(int id);
};

int EclVm::Run() { return 0; }                                    // 0x0040C5E0
int EclVm::GetIntValue(int) { return 0; }                         // 0x0040C690
float* EclVm::GetFloatVarAddress(int) { return 0; }               // 0x0040C6A0
double EclVm::GetFloatValue(int) {                                // 0x0040C6B0
    return *(float*)&data_00470b04;
}
int* EclVm::GetIntVarAddress(int) { return 0; }                   // 0x0040C6C0
