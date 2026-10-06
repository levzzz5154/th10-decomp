#pragma once
#include "runtime.hpp"
// Actual polymorphic records: virtual slot 5 retires a record and slot 7
// evaluates a point/radius/mode. All three callers save next before dispatch.
struct PlayerBullet {
    // The five preceding virtual slots are not used by this owner.
    virtual void Unknown0();
    virtual void Unknown1();
    virtual void Unknown2();
    virtual void Unknown3();
    virtual void Unknown4();
    virtual void Retire(int mode);
    virtual void Unknown6();
    virtual int Evaluate(const Vec3* point, float radius, int mode);
    unsigned int reserved_04;
    PlayerBullet* next;
    int state;
};
struct PlayerBulletManager {
    unsigned char reserved_00[0x18];
    PlayerBullet* first;
    __declspec(noinline) int Evaluate(const Vec3* point, float radius, int mode);
    unsigned char reserved_01c[0x440-0x1c];
    Vec3 evaluation_point;
    __declspec(noinline) int Reset(int mode);
};
typedef char BulletRecordNext[offsetof(PlayerBullet,next)==8?1:-1];
typedef char BulletRecordState[offsetof(PlayerBullet,state)==12?1:-1];
typedef char BulletManagerHead[offsetof(PlayerBulletManager,first)==0x18?1:-1];
typedef char BulletManagerPoint[offsetof(PlayerBulletManager,evaluation_point)==0x440?1:-1];
