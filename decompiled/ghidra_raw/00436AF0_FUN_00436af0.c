/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x00436AF0
 * Tracking name: FUN_00436af0
 * Ghidra name: FUN_00436af0
 * Tracked span: 432 bytes
 */


uint FUN_00436af0(int param_1,int param_2,int param_3)

{
  int in_EAX;
  uint uVar1;
  int iVar2;
  HBITMAP h;
  HDC hdc;
  HGDIOBJ pvVar3;
  int iVar4;
  BITMAPINFO *pBVar5;
  undefined4 *puVar6;
  undefined4 *local_70;
  BITMAPINFO local_6c;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  
  FUN_00436a30();
  uVar1 = 0;
  pBVar5 = &local_6c;
  for (iVar4 = 0x1b; iVar2 = DAT_00474918, iVar4 != 0; iVar4 = iVar4 + -1) {
    (pBVar5->bmiHeader).biSize = 0;
    pBVar5 = (BITMAPINFO *)&(pBVar5->bmiHeader).biWidth;
  }
  while ((iVar2 != -1 && (iVar2 != param_3))) {
    uVar1 = uVar1 + 1;
    iVar2 = (&DAT_00474918)[uVar1 * 6];
  }
  if ((param_3 == -1) || (iVar4 = uVar1 * 0x18, iVar4 == -0x474918)) {
    return uVar1 & 0xffffff00;
  }
  iVar2 = *(int *)(iVar4 + 0x47491c) * param_1;
  iVar2 = ((int)(iVar2 + (iVar2 >> 0x1f & 7U)) >> 3) + 3;
  local_6c.bmiHeader.biHeight = -1 - param_2;
  local_6c.bmiHeader.biBitCount = *(WORD *)(iVar4 + 0x47491c);
  iVar2 = ((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2) * 4;
  local_6c.bmiHeader.biSizeImage = iVar2 * param_2;
  local_6c.bmiHeader.biSize = 0x6c;
  local_6c.bmiHeader.biWidth = param_1;
  local_6c.bmiHeader.biPlanes = 1;
  if ((param_3 != 0x18) && (param_3 != 0x16)) {
    local_6c.bmiColors[0] = *(RGBQUAD *)(iVar4 + 0x474924);
    local_40 = *(undefined4 *)(iVar4 + 0x474928);
    local_3c = *(undefined4 *)(iVar4 + 0x47492c);
    local_38 = *(undefined4 *)(iVar4 + 0x474920);
    local_6c.bmiHeader.biCompression = 3;
  }
  h = CreateDIBSection((HDC)0x0,&local_6c,0,&local_70,(HANDLE)0x0,0);
  if (h != (HBITMAP)0x0) {
    puVar6 = local_70;
    for (uVar1 = local_6c.bmiHeader.biSizeImage >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    for (uVar1 = local_6c.bmiHeader.biSizeImage & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined1 *)puVar6 = 0;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    hdc = CreateCompatibleDC((HDC)0x0);
    pvVar3 = SelectObject(hdc,h);
    *(HGDIOBJ *)(in_EAX + 0x118) = pvVar3;
    *(int *)(in_EAX + 0x110) = iVar2;
    *(undefined4 **)(in_EAX + 0x120) = local_70;
    *(DWORD *)(in_EAX + 0x10c) = local_6c.bmiHeader.biSizeImage;
    *(HDC *)(in_EAX + 0x114) = hdc;
    *(HBITMAP *)(in_EAX + 0x11c) = h;
    *(int *)(in_EAX + 0x104) = param_1;
    *(int *)(in_EAX + 0x108) = param_2;
    *(int *)(in_EAX + 0x100) = param_3;
    return CONCAT31((int3)((uint)param_1 >> 8),1);
  }
  return 0;
}

