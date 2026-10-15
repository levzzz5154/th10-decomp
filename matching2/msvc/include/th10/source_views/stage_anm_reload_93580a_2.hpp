#pragma once

#pragma code_seg()

// 0x0040C3C0: load the stage's animation file into its slot, clear the reload
// request and take down the loading sprite. The stage arrives in EBX.
#pragma code_seg(".text$05reload")
