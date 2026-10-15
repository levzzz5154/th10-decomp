#pragma once


// 0x00428DD0. MSVC emits the retail 32-bit negate before float conversion.
#pragma code_seg(".text$05decrement")
