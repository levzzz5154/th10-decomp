/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00445900
 * Tracking name: GameStateInit
 * Ghidra name: GameStateInit
 * Tracked span: 2336 bytes
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * GameStateInit(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_ECX;
  void *unaff_EBX;
  int local_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004657a5;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  _eh_vector_constructor_iterator_(param_1 + 0x1a,0x3ac,0x1000,FUN_00402050,FUN_00401ff0);
  param_1[0xeb467] = param_1[0xeb467] & 0xfffffffe;
  param_1[0xeb478] = param_1[0xeb478] & 0xfffffffe;
  param_1[0xeb48b] = param_1[0xeb48b] & 0xfffffffe;
  param_1[0xeb496] = param_1[0xeb496] & 0xfffffffe;
  param_1[0xeb4a9] = param_1[0xeb4a9] & 0xfffffffe;
  param_1[0xeb4b8] = param_1[0xeb4b8] & 0xfffffffe;
  param_1[0xeb4cb] = param_1[0xeb4cb] & 0xfffffffe;
  param_1[0xeb4d6] = param_1[0xeb4d6] & 0xfffffffe;
  param_1[0xeb52a] = param_1[0xeb52a] & 0xfffffffe;
  puVar1 = param_1 + 0xeb44c;
  for (iVar2 = 0xeb; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  *(undefined2 *)(param_1 + 0xeb52d) = 0xffff;
  local_4._0_1_ = 1;
  local_4._1_3_ = 0;
  _eh_vector_constructor_iterator_(param_1 + 0x1cb6b9,0x3ac,0x14,FUN_00402050,FUN_00401ff0);
  local_4 = CONCAT31(local_4._1_3_,2);
  puVar1 = param_1;
  for (iVar2 = 0x1cc918; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  _DAT_004978b4 = 0x3f800000;
  _DAT_0049789c = 0x3f800000;
  _DAT_00497884 = 0x3f800000;
  _DAT_0049786c = 0x3f800000;
  _DAT_00497870 = 0;
  _DAT_00497874 = 0;
  _DAT_00497888 = 0x3f800000;
  _DAT_0049788c = 0;
  _DAT_004978a0 = 0;
  _DAT_004978a4 = 0x3f800000;
  _DAT_004978b8 = 0x3f800000;
  _DAT_004978bc = 0x3f800000;
  _DAT_00497920 = 0x3f800000;
  _DAT_00497904 = 0x3f800000;
  _DAT_004978e8 = 0x3f800000;
  _DAT_004978cc = 0x3f800000;
  _DAT_004978d4 = 0;
  _DAT_004978d8 = 0;
  _DAT_004978f0 = 0x3f800000;
  _DAT_004978f4 = 0;
  _DAT_0049790c = 0;
  _DAT_00497910 = 0x3f800000;
  _DAT_00497928 = 0x3f800000;
  _DAT_0049792c = 0x3f800000;
  param_1[0xeb69d] = 0;
  param_1[0xeb699] = 0;
  *(undefined1 *)(param_1 + 0xeb69a) = 0;
  *(undefined1 *)((int)param_1 + 0x3ada69) = 0;
  param_1[0xeb698] = 1;
  *(undefined1 *)((int)param_1 + 0x3ada6a) = 0;
  *(undefined1 *)(param_1 + 0xeb69b) = 0xff;
  *(undefined1 *)((int)param_1 + 0x3ada6b) = 0;
  param_1[1] = 0xffffffff;
  *param_1 = 0xffffffff;
  puVar1 = param_1 + 0x1a;
  local_10 = 0x1000;
  uVar3 = 0;
  do {
    FUN_00401de0(uVar3,puVar1);
    puVar1 = puVar1 + 0xeb;
    local_10 = local_10 + -1;
    uVar3 = extraout_ECX;
  } while (local_10 != 0);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004485d0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449ae0(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004485e0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449ae0(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004485f0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448600;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448610;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448620;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004486a0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004486b0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004486c0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004486d0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004486e0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004486f0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448700;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448710;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448720;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448730;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448740;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448770;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  puVar1[1] = puVar1[1] | 3;
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_004487c0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  FUN_00449b70(iVar2);
  puVar1 = operator_new(0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *puVar1 = 0;
    puVar1[1] = puVar1[1] & 0xfffffffe;
    puVar1[5] = puVar1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  iVar2 = DAT_00491be4;
  puVar1[2] = &LAB_00448810;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[8] = param_1;
  puVar1[1] = puVar1[1] | 3;
  FUN_00449b70(iVar2);
  (**(code **)(*(int *)g_pD3DDevice + 0x170))(g_pD3DDevice,0);
  ExceptionList = unaff_EBX;
  return param_1;
}

