// 0x0041BEF0..0x0041C020: the base laser's virtual methods (vtable 0x0046DAB0).
//
// Every laser type (line 0x0046DA60, growing 0x0046DA10) starts from this
// table and overrides what it needs. Apart from Unlink, the base versions do
// nothing: an empty RET, or a zero result with the slot's stack arguments
// popped. Nothing calls them directly, so they are ordinary members here; the
// bytes are those of the virtual methods (this in ECX, callee pops).
//
// Slots 0x24..0x48 are the motion callbacks LineLaser::Update runs for each
// set flag bit (see build_support/layout/ltcg/laser_line/types.hpp).
struct LaserParameters;
struct LaserPoint;

struct Laser {
    void* vtable;
    Laser* next;                             // +0x04, laser list
    Laser* previous;                         // +0x08

    void RunCommands();                                                     // +0x00
    int Initialize(const LaserParameters* parameters);                      // +0x04
    int Update();                                                           // +0x08
    int Draw();                                                             // +0x0C
    int Unlink();                                                           // +0x10
    int CreateSegments(int mode);                                           // +0x14
    int OnPlayerHit(const LaserPoint* start, const LaserPoint* end, int);   // +0x18
    int Cut(const LaserPoint* start, const LaserPoint* end, int);           // +0x1C
    int HitTestCircle(const LaserPoint* center, float radius);              // +0x20
    void Motion0001();                                                      // +0x24
    void Motion0010();                                                      // +0x28
    void Motion0020();                                                      // +0x2C
    void Motion0040();                                                      // +0x30
    void Motion0100();                                                      // +0x34
    void Motion0080();                                                      // +0x38
    void Bounce();                                                          // +0x3C
    void Motion100000();                                                    // +0x40
    void Motion200000();                                                    // +0x44
    void Motion4000000();                                                   // +0x48
};

void Laser::RunCommands() {}                                                        // 0x0041BEF0
int Laser::Initialize(const LaserParameters*) { return 0; }                         // 0x0041BF00
int Laser::Update() { return 0; }                                                   // 0x0041BF10
int Laser::Draw() { return 0; }                                                     // 0x0041BF20

// 0x0041BF30: take the laser out of the list.
int Laser::Unlink() {
    next->previous = previous;
    if (previous)
        previous->next = next;
    return 0;
}

int Laser::Cut(const LaserPoint*, const LaserPoint*, int) { return 0; }             // 0x0041BF50
int Laser::OnPlayerHit(const LaserPoint*, const LaserPoint*, int) { return 0; }     // 0x0041BF60
int Laser::CreateSegments(int) { return 0; }                                        // 0x0041BF70
int Laser::HitTestCircle(const LaserPoint*, float) { return 0; }                    // 0x0041BF80
void Laser::Motion0001() {}                                                         // 0x0041BF90
void Laser::Motion0010() {}                                                         // 0x0041BFA0
void Laser::Motion0020() {}                                                         // 0x0041BFB0
void Laser::Motion0040() {}                                                         // 0x0041BFC0
void Laser::Motion0100() {}                                                         // 0x0041BFD0
void Laser::Motion0080() {}                                                         // 0x0041BFE0
void Laser::Bounce() {}                                                             // 0x0041BFF0
void Laser::Motion100000() {}                                                       // 0x0041C000
void Laser::Motion200000() {}                                                       // 0x0041C010
void Laser::Motion4000000() {}                                                      // 0x0041C020
