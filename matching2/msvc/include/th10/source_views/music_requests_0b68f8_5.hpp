#pragma once

#pragma code_seg()

// 0x00424460, 0x00424470 and 0x00434B80: the out-of-line copies of the
// pause, unpause and volume requests. Every use is inlined in retail; the
// copies that remain take the request table in EAX.
#pragma code_seg(".text$00h_unpause")
