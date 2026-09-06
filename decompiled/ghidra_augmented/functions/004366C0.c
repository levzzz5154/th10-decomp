/* Raw Ghidra reference; not compilable reconstruction. Address: 004366C0 */

undefined4 __thiscall FUN_004366c0(void *this,LPCSTR param_1)

{
  HRSRC hResInfo;
  HGLOBAL hResData;
  undefined4 *puVar1;
  undefined4 uVar2;
  DWORD _Size;
  undefined4 *puVar3;
  BOOL BVar4;
  uint uVar5;
  uint uVar6;
  
  (**(code **)(*(int *)this + 4))();
  hResInfo = FindResourceA((HMODULE)0x0,param_1,&DAT_0000000a);
  if (hResInfo != (HRSRC)0x0) {
    hResData = LoadResource((HMODULE)0x0,hResInfo);
    if (hResData != (HGLOBAL)0x0) {
      puVar1 = LockResource(hResData);
      if (puVar1 == (undefined4 *)0x0) {
        FreeResource((HGLOBAL)0x0);
        uVar2 = (**(code **)(*(int *)this + 4))();
        return CONCAT31((int3)((uint)uVar2 >> 8),1);
      }
      _Size = SizeofResource((HMODULE)0x0,hResInfo);
      *(DWORD *)((int)this + 4) = _Size;
      puVar3 = _malloc(_Size);
      *(undefined4 **)((int)this + 0xc) = puVar3;
      if (puVar3 != (undefined4 *)0x0) {
        uVar6 = *(uint *)((int)this + 4);
        for (uVar5 = uVar6 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *puVar3 = *puVar1;
          puVar1 = puVar1 + 1;
          puVar3 = puVar3 + 1;
        }
        for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined1 *)puVar3 = *(undefined1 *)puVar1;
          puVar1 = (undefined4 *)((int)puVar1 + 1);
          puVar3 = (undefined4 *)((int)puVar3 + 1);
        }
        *(undefined4 *)((int)this + 8) = *(undefined4 *)((int)this + 0xc);
        BVar4 = FreeResource(hResData);
        return CONCAT31((int3)((uint)BVar4 >> 8),1);
      }
    }
  }
  uVar2 = (**(code **)(*(int *)this + 4))();
  return CONCAT31((int3)((uint)uVar2 >> 8),1);
}

