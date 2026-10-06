#pragma once
struct MovementInput { union { unsigned int word; unsigned char bytes[4]; struct { unsigned int repeat : 1; unsigned int revive : 1; }; }; };
extern "C" MovementInput data_00474e5c;
