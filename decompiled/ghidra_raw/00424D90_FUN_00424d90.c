/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00424D90
 * Tracking name: FUN_00424d90
 * Ghidra name: FUN_00424d90
 * Tracked span: 320 bytes
 */


void FUN_00424d90(void)

{
  void *pvVar1;
  int unaff_ESI;
  
  *(undefined4 *)(unaff_ESI + 0x458) = 1;
  if ((*(uint *)(unaff_ESI + 0x470) & 1) == 0) {
    *(undefined4 *)(unaff_ESI + 0x464) = 0;
    *(undefined4 *)(unaff_ESI + 0x460) = 0xfff0bdc1;
    *(undefined4 *)(unaff_ESI + 0x468) = 0;
    *(undefined4 **)(unaff_ESI + 0x46c) = &DAT_00476f78;
    *(uint *)(unaff_ESI + 0x470) = *(uint *)(unaff_ESI + 0x470) | 1;
  }
  *(undefined4 *)(unaff_ESI + 0x464) = 0xffffffff;
  *(undefined4 *)(unaff_ESI + 0x468) = 0xbf800000;
  *(undefined4 *)(unaff_ESI + 0x460) = 0xfffffffe;
  if ((*(uint *)(unaff_ESI + 0x484) & 1) == 0) {
    *(undefined4 *)(unaff_ESI + 0x478) = 0;
    *(undefined4 *)(unaff_ESI + 0x474) = 0xfff0bdc1;
    *(undefined4 *)(unaff_ESI + 0x47c) = 0;
    *(undefined4 **)(unaff_ESI + 0x480) = &DAT_00476f78;
    *(uint *)(unaff_ESI + 0x484) = *(uint *)(unaff_ESI + 0x484) | 1;
  }
  *(undefined4 *)(unaff_ESI + 0x478) = 0;
  *(undefined4 *)(unaff_ESI + 0x47c) = 0;
  *(undefined4 *)(unaff_ESI + 0x474) = 0xffffffff;
  if ((*(uint *)(unaff_ESI + 0x498) & 1) == 0) {
    *(undefined4 *)(unaff_ESI + 0x48c) = 0;
    *(undefined4 *)(unaff_ESI + 0x488) = 0xfff0bdc1;
    *(undefined4 *)(unaff_ESI + 0x490) = 0;
    *(undefined4 **)(unaff_ESI + 0x494) = &DAT_00476f78;
    *(uint *)(unaff_ESI + 0x498) = *(uint *)(unaff_ESI + 0x498) | 1;
  }
  pvVar1 = g_pGameStateManager;
  *(undefined4 *)(unaff_ESI + 0x48c) = 0;
  *(undefined4 *)(unaff_ESI + 0x490) = 0;
  *(undefined4 *)(unaff_ESI + 0x488) = 0xffffffff;
  FUN_004492a0(&DAT_00476f78,(int)pvVar1,*(int *)(unaff_ESI + 0x329c));
  *(undefined4 *)(unaff_ESI + 0x329c) = 0;
  *(undefined4 *)(unaff_ESI + 0x329c) = 0;
  FUN_00413790(DAT_00474c70);
  return;
}

