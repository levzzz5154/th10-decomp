/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x0040D830
 * Tracking name: FUN_0040d830
 * Ghidra name: FUN_0040d830
 * Tracked span: 688 bytes
 */


void __thiscall FUN_0040d830(void *this,byte *param_1)

{
  int iVar1;
  undefined4 *unaff_ESI;
  undefined4 *puVar2;
  
  unaff_ESI[0x404] = 0;
  unaff_ESI[0x405] = 0;
  *unaff_ESI = &PTR_LAB_0046d0c0;
  FUN_0040cc70(this,(int)(unaff_ESI + 0x40f));
  puVar2 = unaff_ESI + 0x40f;
  for (iVar1 = 0x537; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_ESI[2] = 0;
  unaff_ESI[3] = 0;
  unaff_ESI[0x407] = unaff_ESI;
  unaff_ESI[0x40a] = unaff_ESI[0x40a] & 0xfffffffe;
  unaff_ESI[0x408] = 0;
  unaff_ESI[1] = unaff_ESI + 2;
  unaff_ESI[0x406] = 0xffffffff;
  unaff_ESI[0x40c] = unaff_ESI + 2;
  unaff_ESI[0x40d] = 0;
  unaff_ESI[0x40e] = 0;
  unaff_ESI[0x945] = unaff_ESI;
  unaff_ESI[0x46f] = 0;
  unaff_ESI[0x482] = 0;
  unaff_ESI[0x491] = 0;
  unaff_ESI[0x4a0] = 0;
  unaff_ESI[0x4af] = 0;
  unaff_ESI[0x4be] = 0;
  puVar2 = unaff_ESI + 0x430;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = unaff_ESI + 0x425;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = unaff_ESI + 0x41a;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_ESI[0x43b] = 0x41c00000;
  unaff_ESI[0x43c] = 0x41c00000;
  unaff_ESI[0x43d] = 0x41c00000;
  unaff_ESI[0x43e] = 0x41c00000;
  unaff_ESI[0x923] = 0xffffffff;
  unaff_ESI[0x45b] = unaff_ESI;
  unaff_ESI[0x45c] = 0;
  unaff_ESI[0x45d] = 0;
  puVar2 = unaff_ESI + 0x902;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_ESI[0x910] = 0x42000000;
  unaff_ESI[0x90f] = 0x42000000;
  if ((unaff_ESI[0x45a] & 1) == 0) {
    unaff_ESI[0x457] = 0;
    unaff_ESI[0x456] = 0xfff0bdc1;
    unaff_ESI[0x458] = 0;
    unaff_ESI[0x459] = &DAT_00476f78;
    unaff_ESI[0x45a] = unaff_ESI[0x45a] | 1;
  }
  unaff_ESI[0x457] = 0;
  unaff_ESI[0x458] = 0;
  unaff_ESI[0x456] = 0xffffffff;
  if ((unaff_ESI[0x91a] & 1) == 0) {
    unaff_ESI[0x917] = 0;
    unaff_ESI[0x916] = 0xfff0bdc1;
    unaff_ESI[0x918] = 0;
    unaff_ESI[0x919] = &DAT_00476f78;
    unaff_ESI[0x91a] = unaff_ESI[0x91a] | 1;
  }
  unaff_ESI[0x917] = 0;
  unaff_ESI[0x918] = 0;
  unaff_ESI[0x916] = 0xffffffff;
  if ((unaff_ESI[0x91f] & 1) == 0) {
    unaff_ESI[0x91c] = 0;
    unaff_ESI[0x91b] = 0xfff0bdc1;
    unaff_ESI[0x91d] = 0;
    unaff_ESI[0x91e] = &DAT_00476f78;
    unaff_ESI[0x91f] = unaff_ESI[0x91f] | 1;
  }
  iVar1 = DAT_00477704;
  unaff_ESI[0x91c] = 0;
  unaff_ESI[0x91d] = 0;
  unaff_ESI[0x91b] = 0xffffffff;
  unaff_ESI[0x40b] = *(undefined4 *)(iVar1 + 0x54);
  iVar1 = FUN_00450470(param_1);
  *(int *)(unaff_ESI[1] + 4) = iVar1;
  *(undefined4 *)unaff_ESI[1] = 0;
  unaff_ESI[0x8ff] = 0;
  unaff_ESI[0x900] = 0;
  unaff_ESI[0x901] = 0;
  unaff_ESI[0x925] = 0xffffffff;
  unaff_ESI[0x926] = 0xffffffff;
  unaff_ESI[0x929] = 0xffffffff;
  unaff_ESI[0x92a] = 0xffffffff;
  unaff_ESI[0x92d] = 0xffffffff;
  unaff_ESI[0x92e] = 0xffffffff;
  unaff_ESI[0x931] = 0xffffffff;
  unaff_ESI[0x932] = 0xffffffff;
  unaff_ESI[0x935] = 0xffffffff;
  unaff_ESI[0x936] = 0xffffffff;
  unaff_ESI[0x939] = 0xffffffff;
  unaff_ESI[0x93a] = 0xffffffff;
  unaff_ESI[0x93d] = 0xffffffff;
  unaff_ESI[0x93e] = 0xffffffff;
  unaff_ESI[0x941] = 0xffffffff;
  unaff_ESI[0x942] = 0xffffffff;
  unaff_ESI[0x927] = 0;
  unaff_ESI[0x92b] = 0;
  unaff_ESI[0x92f] = 0;
  unaff_ESI[0x933] = 0;
  unaff_ESI[0x937] = 0;
  unaff_ESI[0x93b] = 0;
  unaff_ESI[0x93f] = 0;
  unaff_ESI[0x943] = 0;
  return;
}

