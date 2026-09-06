/* Raw Ghidra reference; not compilable reconstruction. Address: 0043CD30 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __thiscall FUN_0043cd30(void *this,HWND param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *unaff_EBX;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined2 uStack_44;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined1 *puStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  uint local_4;
  
  local_4 = DAT_00473660 ^ (uint)&uStack_4c;
  puVar4 = (undefined4 *)((int)this + 0x408);
  for (iVar3 = 0x80; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0xffffffff;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)((int)this + 0x620) = 0xffffffff;
  *(undefined4 *)((int)this + 0x624) = 0xffffffff;
  *(undefined4 *)((int)this + 0x628) = 0xffffffff;
  *(undefined4 *)((int)this + 0x62c) = 0xffffffff;
  *(undefined4 *)((int)this + 0x630) = 0xffffffff;
  *(undefined4 *)((int)this + 0x634) = 0xffffffff;
  *(undefined4 *)((int)this + 0x638) = 0xffffffff;
  *(undefined4 *)((int)this + 0x63c) = 0xffffffff;
  *(undefined4 *)((int)this + 0x640) = 0xffffffff;
  *(undefined4 *)((int)this + 0x644) = 0xffffffff;
  *(undefined4 *)((int)this + 0x648) = 0xffffffff;
  *(undefined4 *)((int)this + 0x64c) = 0xffffffff;
  piVar1 = operator_new(4);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    *piVar1 = 0;
  }
  *(int **)((int)this + 0x610) = piVar1;
  if ((int *)*piVar1 != (int *)0x0) {
    (**(code **)(*(int *)*piVar1 + 8))();
    *piVar1 = 0;
  }
  iVar3 = Ordinal_11();
  if ((iVar3 < 0) ||
     (iVar3 = (**(code **)(*(int *)*piVar1 + 0x18))((int *)*piVar1,param_1), iVar3 < 0)) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046fe0c);
    piVar1 = *(int **)((int)this + 0x610);
    if (piVar1 != (int *)0x0) {
      if ((int *)*piVar1 != (int *)0x0) {
        (**(code **)(*(int *)*piVar1 + 8))();
        *piVar1 = 0;
      }
      _free(piVar1);
      *(undefined4 *)((int)this + 0x610) = 0;
    }
    return 0xffffffff;
  }
  FUN_0044c7e0(0x10,piVar1);
  uStack_28 = 0;
  uStack_20 = 0;
  *(undefined4 *)this = **(undefined4 **)((int)this + 0x610);
  uStack_1c = 0;
  puStack_24 = &stack0xffffffac;
  puVar4 = (undefined4 *)((int)this + 0x608);
  uStack_18 = 0;
  *(undefined4 *)((int)this + 0x618) = 0;
  uStack_14 = 0;
  uStack_34 = 0x24;
  uStack_30 = 0x8008;
  uStack_2c = 0x8000;
  uStack_44 = 0;
  uStack_4c = 0x2b110;
  uStack_48 = 0x100004;
  iVar3 = (**(code **)(**(int **)this + 0xc))(*(int **)this,&uStack_34,puVar4,0);
  if ((-1 < iVar3) &&
     (iVar3 = (**(code **)(*(int *)*puVar4 + 0x2c))
                        ((int *)*puVar4,0,0x8000,&stack0xffffff98,&uStack_48,&stack0xffffffb0,
                         &uStack_4c,0), -1 < iVar3)) {
    puVar5 = unaff_EBX;
    for (iVar3 = 0x2000; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    (**(code **)(*(int *)*puVar4 + 0x4c))((int *)*puVar4,unaff_EBX,uStack_48,0xac44,uStack_4c);
    (**(code **)(*(int *)*puVar4 + 0x30))((int *)*puVar4,0,0,1);
    *(undefined4 *)((int)this + 0x52c4) = 100;
    *(undefined4 *)((int)this + 0x52c8) = 100;
    SetTimer(param_1,0,0xfa,(TIMERPROC)0x0);
    *(HWND *)((int)this + 0x60c) = param_1;
    iVar3 = 0;
    while (DAT_004977b4 != 2) {
      iVar2 = FUN_0043d390(iVar3,&DAT_00492590,(&PTR_s_se_plst00_wav_00474b40)[iVar3]);
      if (iVar2 != 0) {
        FUN_0044b810(&DAT_00474f70,&DAT_0046fdd4);
        return 0xffffffff;
      }
      iVar3 = iVar3 + 1;
      if (0x24 < iVar3) {
        FUN_0044b810(&DAT_00474f70,&DAT_0046fdac);
        return 0;
      }
    }
  }
  return 0xffffffff;
}

