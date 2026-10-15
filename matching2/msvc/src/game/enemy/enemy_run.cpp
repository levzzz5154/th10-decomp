// 0x0040E760: Enemy::Run (vtable 0x0046D0C0 slot 0x00): run the enemy's ECL
// script state embedded at +0x103C (0x0040E770).

struct EnemyEcl {
    unsigned char bytes[0x100];
    __declspec(noinline) void Run();
};

struct Enemy {
    unsigned char pad_000[0x103C];
    EnemyEcl inner;
    __declspec(noinline) void Run();
};

#pragma code_seg(".text$01run")
void Enemy::Run() {
    inner.Run();
}
#pragma code_seg()
