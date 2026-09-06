/* Raw Ghidra reference; not compilable reconstruction. Address: 00418C40 */

void __fastcall FUN_00418c40(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_2;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)((int)param_2 + 0x16) = 600;
  *(undefined2 *)(param_2 + 6) = 600;
  *(undefined1 *)((int)param_2 + 0x1b) = 1;
  *(undefined1 *)(param_2 + 7) = 1;
  param_2[0xc] = param_2[0xc] | 0x100;
  *(undefined1 *)((int)param_2 + 0x1a) = 0;
  *param_2 = 0x100003;
  *(undefined1 *)((int)param_2 + 0x1d) = 0;
  *(undefined1 *)((int)param_2 + 0x1e) = 0;
  param_2[1] = DAT_00474e88;
  param_2[2] = DAT_00474e8c;
  param_2[3] = DAT_00474e90;
  param_2[4] = DAT_00474e94;
  *(undefined2 *)(param_2 + 5) = DAT_00474e98;
  *(undefined1 *)((int)param_2 + 0x1f) = 2;
  *(undefined1 *)((int)param_2 + 0x22) = 0;
  *(undefined1 *)(param_2 + 8) = 100;
  *(undefined1 *)((int)param_2 + 0x21) = 0x50;
  return;
}

