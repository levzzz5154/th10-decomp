// 0x00427960: keep a trail sprite relative to the player's integer anchor.
// 0x00427950: its registered scheduler callback, which returns zero.
//
// When the trail mode is zero, the sprite remembers the head's relative offset.
// Otherwise it moves that head with the player and interpolates seven intervening
// trail points in eighths. Both paths publish the anchor plus the relative offset
// and remember the mode.
//
// CopyFrom copies the coordinates in order. Its ordinary inline C++ body
// preserves the source point's aliasing behavior; no raw bytes, assembly,
// volatile controls, or synthetic caller establish this private ESI receiver.

struct TrailPoint_00427960 {
    int x, y;
    TrailPoint_00427960() {}
    TrailPoint_00427960(int px, int py) : x(px), y(py) {}
    void CopyFrom(const TrailPoint_00427960& other) { x = other.x; y = other.y; }
    TrailPoint_00427960 operator+(const TrailPoint_00427960& other) const {
        return TrailPoint_00427960(x + other.x, y + other.y);
    }
};
struct PlayerTrail_00427960 {
    unsigned char reserved_000[0x3CC];
    TrailPoint_00427960 anchor;
    unsigned char reserved_3d4[0x436C-0x3D4];
    TrailPoint_00427960 points[33];
    int trail_mode;
};
extern "C" PlayerTrail_00427960* data_00477834;
struct TrailSprite_00427960 {
    unsigned char reserved_000[0x34];
    TrailPoint_00427960 position;
    unsigned char reserved_03c[8];
    TrailPoint_00427960 offset;
    unsigned char reserved_04c[0x84-0x4C];
    int trail_mode;
    int index;
    __declspec(noinline) void Update();
};
#pragma code_seg(".text$03worker")
void TrailSprite_00427960::Update() {
    PlayerTrail_00427960* player = data_00477834;
    int mode = player->trail_mode;
    position.CopyFrom(player->points[index * 8 + 8]);
    if (mode == 0) {
        offset.CopyFrom(TrailPoint_00427960(position.x - player->anchor.x, position.y - player->anchor.y));
    } else {
        player->points[index * 8 + 8].CopyFrom(TrailPoint_00427960(player->anchor.x + offset.x, player->anchor.y + offset.y));
        float fraction = 0.125f;
        for (int point = index * 8 + 1; point <= index * 8 + 7; ++point) {
            player->points[point].x = int((player->points[index * 8 + 8].x -
                                         player->points[index * 8].x) * fraction +
                                        player->points[index * 8].x);
            player->points[point].y = int((player->points[index * 8 + 8].y -
                                         player->points[index * 8].y) * fraction +
                                        player->points[index * 8].y);
            fraction += 0.125f;
        }
    }
    position.CopyFrom(player->anchor + offset);
    trail_mode = mode;
}
#pragma code_seg()
#pragma code_seg(".text$01callback")
__declspec(noinline) int __fastcall TrailSpriteUpdateCallback_00427950(TrailSprite_00427960* sprite) {
    sprite->Update();
    return 0;
}
#pragma code_seg()
