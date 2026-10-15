// Link context for the 0x0043EE30 equivalent recovery: models of the helpers it
// calls and of a caller, so the checking LTCG link derives the same private
// register conventions as retail. Only AnmVm::Tick is compared.
#include "th10/runtime/core/sprtanim/anm_vm_tick.hpp"

float g_game_speed = 1.0f;
float flt_0 = 0.0f;
Float3 g_zero_vector;
Float3 g_scroll_step;
RngState g_replay_rng;
RngState g_effect_rng;
extern "C" float data_00491d7c[12];
extern "C" void* g_sprt_ctrl;
extern "C" void* __cdecl ext_alloc_vm(void* manager);
extern "C" AnmHandle* __cdecl ext_register(int which, void* manager, AnmHandle* out, void* vm);
extern "C" void* __fastcall ext_find(void* context, int id);
extern "C" int __stdcall ext_ring(AnmVm* vm);
float g_pi = 3.1415927f, g_tau = 6.2831855f, g_neg_pi = -3.1415927f;

void FrameTimer::Set(int value) {
    if (!(flags & 1)) {
        current = 0;
        previous = 0xFFF0BDC1;
        elapsed = 0.0f;
        speed = &g_game_speed;
        flags |= 1;
    }
    current = value;
    previous = value - 1;
    elapsed = (float)value;
}
void FrameTimer::Advance(float delta) {
    previous = current;
    if (*speed > 0.99f && *speed < 1.01f) {
        elapsed += delta;
    } else {
        elapsed += delta * *speed;
    }
    current = int(elapsed);
}
void FrameTimer::Decrement(int count) { Advance(float(-count)); }

static __forceinline unsigned short NextWord(RngState* s) {
    unsigned short value = s->seed ^ 0x9630;
    value -= 0x6553;
    s->seed = (value >> 14) + (value << 2);
    ++s->generation;
    return s->seed;
}
unsigned int RngState::NextModulo(unsigned int modulus) {
    if (modulus == 0) return 0;
    unsigned short high = NextWord(this);
    unsigned short low = NextWord(this);
    return ((unsigned int)high << 16 | low) % modulus;
}
float RngState::NextFloat() {
    unsigned short high = NextWord(this);
    unsigned short low = NextWord(this);
    return ((unsigned int)high << 16 | low) * (1.0f / 4294967296.0f);
}
float __stdcall Angle_NormalizeSum(float angle, float delta) {
    float sum = angle + delta;
    int iterations = 0;
    while (sum > g_pi) {
        sum -= g_tau;
        if (iterations++ > 0x20) break;
    }
    while (sum < g_neg_pi) {
        sum += g_tau;
        if (iterations++ > 0x20) break;
    }
    return sum;
}
static __forceinline void Restart(FrameTimer* timer) {
    if (!(timer->flags & 1u)) {
        timer->current = 0;
        timer->previous = -999999;
        timer->elapsed = 0;
        timer->speed = &g_game_speed;
        timer->flags |= 1u;
    }
    timer->current = 0;
    timer->elapsed = 0;
    timer->previous = -1;
}
void Float3Interp::Restart() { ::Restart(&timer); }

float __stdcall EvaluateCurve(unsigned int mode, float numerator, float denominator);
static __forceinline Float3 operator+(const Float3& a, const Float3& b) { return Float3(a.x + b.x, a.y + b.y, a.z + b.z); }
static __forceinline Float3 operator-(const Float3& a, const Float3& b) { return Float3(a.x - b.x, a.y - b.y, a.z - b.z); }
static __forceinline Float3 operator*(const Float3& a, float t) { return Float3(a.x * t, a.y * t, a.z * t); }
static __forceinline Float2 operator+(const Float2& a, const Float2& b) { return Float2(a.x + b.x, a.y + b.y); }
static __forceinline Float2 operator-(const Float2& a, const Float2& b) { return Float2(a.x - b.x, a.y - b.y); }
static __forceinline Float2 operator*(const Float2& a, float t) { return Float2(a.x * t, a.y * t); }
static __forceinline Int3 operator+(const Int3& a, const Int3& b) { return Int3(a.r + b.r, a.g + b.g, a.b + b.b); }
static __forceinline Int3 operator-(const Int3& a, const Int3& b) { return Int3(a.r - b.r, a.g - b.g, a.b - b.b); }
__declspec(noinline) Int3 Int3::operator*(float t) const { return Int3(int(r * t), int(g * t), int(b * t)); }
static __forceinline int Scale(int a, float t) { return int(a * t); }
#define EVAL(T, MUL) \
    if (end_time > 0) { \
        timer.Tick(); \
        if (timer.current >= end_time) { \
            int end = end_time; \
            if (!(timer.flags & 1)) { \
                timer.current = 0; timer.previous = 0xFFF0BDC1; timer.elapsed = 0.0f; \
                timer.speed = &g_game_speed; timer.flags |= 1; \
            } \
            timer.current = end; timer.previous = end - 1; timer.elapsed = (float)end; \
            end_time = 0; \
            if (mode != 7) return goal; \
            return initial; \
        } \
    } \
    if (mode == 7) { initial = initial + goal; return initial; } \
    if (mode == 0x11) { initial = initial + control_2; control_2 = control_2 + goal; return initial; } \
    if (mode == 8) { \
        float t = timer.elapsed / (float)end_time; \
        float u = t - 1.0f; \
        return MUL(initial, (1.0f + 2.0f * t) * u * u) + MUL(goal, (3.0f - 2.0f * t) * t * t) \
             + MUL(control_1, (1.0f - t) * (1.0f - t) * t) + MUL(control_2, u * t * t); \
    } \
    return MUL((goal - initial), EvaluateCurve(mode, timer.elapsed, (float)end_time)) + initial;
#define OPMUL(a, t) ((a) * (t))
Float3 Float3Interp::Evaluate() { EVAL(Float3, OPMUL) }
Int3 ColorInterp::Evaluate() { EVAL(Int3, OPMUL) }
int IntInterp::Evaluate() { EVAL(int, Scale) }
Float2 Float2Interp::Evaluate() { EVAL(Float2, OPMUL) }
float __stdcall EvaluateCurve(unsigned int mode, float numerator, float denominator) {
    float ratio = numerator / denominator;
    float x;
    switch (mode) {
    case 1: return ratio * ratio;
    case 4: x = 1.0f - ratio; return 1.0f - x * x;
    case 2: return ratio * ratio * ratio;
    case 5: return 1.0f - (1.0f - ratio) * (1.0f - ratio) * (1.0f - ratio);
    case 3: return ratio * ratio * ratio * ratio;
    case 15: return 0.0f;
    case 16: return 1.0f;
    default: return ratio;
    }
}
void __stdcall List_InsertAfter(ListNode* position, ListNode* node) {
    if (position->next != 0) {
        node->next = position->next;
        position->next->previous = node;
    }
    position->next = node;
    node->previous = position;
}
#define CREATE(name, which) \
    __declspec(noinline) AnmHandle* __stdcall name(AnmLoaded* anm, AnmHandle* out, int script, int layer) { \
        AnmVm* vm = (AnmVm*)ext_alloc_vm(g_sprt_ctrl); \
        unsigned int flags = vm->flags; \
        vm->layer = layer; \
        vm->flags = flags | 0x40000000u; \
        anm->SetSprite(vm, script); \
        ext_register(which, g_sprt_ctrl, out, vm); \
        return out; \
    }
CREATE(Anm_CreatePrimaryBack, 0)
CREATE(Anm_CreatePrimaryFront, 1)
CREATE(Anm_CreateSecondaryBack, 2)
CREATE(Anm_CreateSecondaryFront, 3)
AnmVm* __stdcall Anm_Resolve(AnmHandle* handle) {
    AnmVm* vm = (AnmVm*)ext_find(g_sprt_ctrl, (int)handle->value);
    if (vm == 0) handle->value = 0;
    return vm;
}
struct Matrix44 {
    float values[4][4];
    __forceinline void SetIdentity() {
        values[3][2] = 0.0f; values[3][1] = 0.0f; values[3][0] = 0.0f;
        values[2][3] = 0.0f; values[2][1] = 0.0f; values[2][0] = 0.0f;
        values[1][3] = 0.0f; values[1][2] = 0.0f; values[1][0] = 0.0f;
        values[0][3] = 0.0f; values[0][2] = 0.0f; values[0][1] = 0.0f;
        values[3][3] = 1.0f; values[2][2] = 1.0f; values[1][1] = 1.0f; values[0][0] = 1.0f;
    }
};
struct SpriteObject {
    unsigned char reserved_0000[0x04C];
    float width, height;
    unsigned char reserved_054[0x23C - 0x054];
    Matrix44 block_a, block_copy, block_b;
    unsigned char reserved_2fc[0x308 - 0x2FC];
    AnmLoaded* resource;
    unsigned char reserved_30c[0x384 - 0x30C];
    unsigned short record_index;
    unsigned char reserved_386[0x394 - 0x386];
    unsigned char* record;
};
int AnmLoaded::SetSprite(AnmVm* vm, int index) {
    SpriteObject* object = (SpriteObject*)vm;
    unsigned char* res = reinterpret_cast<unsigned char*>(this);
    if (*reinterpret_cast<void**>(res + 0x108) == 0 || *reinterpret_cast<unsigned int*>(res + 0x124) != 0)
        return -1;
    object->record_index = static_cast<unsigned short>(index);
    object->resource = this;
    object->record = *reinterpret_cast<unsigned char**>(res + 0x118) + index * 0x44;
    object->width = *reinterpret_cast<float*>(object->record + 0x34);
    object->height = *reinterpret_cast<float*>(object->record + 0x30);
    object->block_a.SetIdentity();
    object->block_b.SetIdentity();
    unsigned char* rec = object->record;
    object->block_a.values[0][0] = object->width * 0.00390625f;
    object->block_a.values[1][1] = object->height * 0.00390625f;
    object->block_b.values[0][0] = (*reinterpret_cast<float*>(rec + 0x38) / *reinterpret_cast<float*>(rec + 0x1C)) * object->width;
    object->block_b.values[1][1] = (*reinterpret_cast<float*>(rec + 0x3C) / *reinterpret_cast<float*>(rec + 0x18)) * object->height;
    object->block_copy = object->block_a;
    return 0;
}
int AnmVm::IntVar(int id) {
    switch (id - 10000) {
    case 0: return int_vars[0];
    case 1: return int_vars[1];
    case 2: return int_vars[2];
    case 3: return int_vars[3];
    case 4: return (int)float_vars[0];
    case 5: return (int)float_vars[1];
    case 6: return (int)float_vars[2];
    case 7: return (int)float_vars[3];
    case 8: return int_vars2[0];
    case 9: return int_vars2[1];
    default: return id;
    }
}
float AnmVm::FloatVar(float id) {
    switch ((int)id) {
    case 10000: return (float)int_vars[0];
    case 10001: return (float)int_vars[1];
    case 10002: return (float)int_vars[2];
    case 10003: return (float)int_vars[3];
    case 10004: return float_vars[0];
    case 10005: return float_vars[1];
    case 10006: return float_vars[2];
    case 10007: return float_vars[3];
    case 10008: return (float)int_vars2[0];
    case 10009: return (float)int_vars2[1];
    case 10011:
        if (f30) return g_replay_rng.NextFloat();
        return g_effect_rng.NextFloat();
    case 10013: return position.x;
    case 10014: return position.y;
    case 10015: return position.z;
    case 10016: return data_00491d7c[0];
    case 10017: return data_00491d7c[1];
    case 10018: return data_00491d7c[2];
    default: return id;
    }
}
int* __stdcall Anm_IntRef(int* value, AnmVm* vm, int index, unsigned short mask) {
    unsigned char* object = (unsigned char*)vm;
    if (((1u << index) & mask) != 0) {
        switch (*value) {
        case 10000: return (int*)(object + 0x30c);
        case 10001: return (int*)(object + 0x310);
        case 10002: return (int*)(object + 0x314);
        case 10003: return (int*)(object + 0x318);
        case 10008: return (int*)(object + 0x32c);
        case 10009: return (int*)(object + 0x330);
        }
    }
    return value;
}
float* __stdcall Anm_FloatRef(AnmVm* vm, int index, float* value, unsigned short mask) {
    unsigned char* object = (unsigned char*)vm;
    if (((1u << index) & mask) != 0) {
        switch ((int)*value) {
        case 10004: return (float*)(object + 0x31c);
        case 10005: return (float*)(object + 0x320);
        case 10006: return (float*)(object + 0x324);
        case 10007: return (float*)(object + 0x328);
        case 10013: return (float*)(object + 0x334);
        case 10014: return (float*)(object + 0x338);
        case 10015: return (float*)(object + 0x33c);
        }
    }
    return value;
}
void AnmVm::StartAlpha(int end_time, unsigned char mode, unsigned char initial, unsigned char goal) {
    alpha_interp.control_1 = 0;
    alpha_interp.control_2 = 0;
    alpha_interp.end_time = end_time;
    alpha_interp.mode = mode;
    alpha_interp.initial = initial;
    alpha_interp.goal = goal;
    ::Restart(&alpha_interp.timer);
}
void AnmVm::StartAlpha2(int end_time, unsigned char mode, unsigned char initial, unsigned char goal) {
    alpha2_interp.end_time = end_time;
    alpha2_interp.mode = mode;
    alpha2_interp.initial = initial;
    alpha2_interp.goal = goal;
    ::Restart(&alpha2_interp.timer);
}
#define STARTCOLOR(name, member) \
    void AnmVm::name(const unsigned char* initial, const unsigned char* goal, int end_time, unsigned char mode) { \
        member.end_time = end_time; \
        member.control_1 = Int3(0, 0, 0); \
        member.control_2 = Int3(0, 0, 0); \
        member.mode = mode; \
        Int3 from(initial); \
        Int3 to(goal); \
        member.initial = from; \
        member.goal = to; \
        ::Restart(&member.timer); \
    }
STARTCOLOR(StartColor, color_interp)
STARTCOLOR(StartColor2, color2_interp)
void AnmVm::StartScale(const Float2* initial, const Float2* goal, int end_time, unsigned char mode) {
    scale_interp.end_time = end_time;
    scale_interp.mode = mode;
    scale_interp.initial = *initial;
    scale_interp.goal = *goal;
    ::Restart(&scale_interp.timer);
}
AnmVertex* AnmVertex::SetPolar(float angle, float radius) {
    __asm {
        mov eax, this
        fld angle
        fsincos
        fmul radius
        fstp dword ptr [eax]
        fmul radius
        fstp dword ptr [eax + 4]
    }
}
void AnmVm::InitRing() {
    int count = int_vars[0];
    for (int i = 0; i < count; ++i) strip[i].w = (float)ext_ring(this);
}

extern "C" int __stdcall RigEntry(AnmVm** vms, int count) {
    int total = 0;
    for (int i = 0; i < count; ++i) total += AnmVm::Tick(vms[i]);
    return total;
}
