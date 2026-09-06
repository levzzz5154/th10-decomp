/* Raw Ghidra reference; not compilable reconstruction. Address: 00437380 */

uint FUN_00437380(int param_1,int param_2,HGDIOBJ param_3,COLORREF param_4,COLORREF param_5)

{
  int iVar1;
  int iVar2;
  HDC hdc;
  uint in_EAX;
  HGDIOBJ pvVar3;
  int iVar4;
  LPCSTR unaff_EDI;
  tagRECT local_70;
  tagRECT local_60;
  tagRECT local_50;
  tagRECT local_40;
  tagRECT local_30;
  tagRECT local_20;
  tagRECT local_10;
  
  if (unaff_EDI == (LPCSTR)0x0) {
    return in_EAX & 0xffffff00;
  }
  iVar1 = *(int *)(in_EAX + 0x104);
  iVar2 = *(int *)(in_EAX + 0x108);
  hdc = *(HDC *)(in_EAX + 0x114);
  pvVar3 = SelectObject(hdc,param_3);
  SetBkMode(hdc,1);
  if (param_5 != 0xffffffff) {
    SetTextColor(hdc,param_5);
    local_70.left = param_1;
    iVar4 = param_1 + iVar1;
    local_70.right = iVar4 + -2;
    local_70.bottom = iVar2 + param_2 + -2;
    local_70.top = param_2;
    DrawTextA(hdc,unaff_EDI,-1,&local_70,0);
    local_50.bottom = iVar2 + param_2;
    local_50.left = param_1 + 2;
    local_50.right = iVar4 + 2;
    local_40.left = param_1 + 1;
    local_40.top = param_2 + 2;
    local_40.right = iVar4 + 1;
    local_40.bottom = local_50.bottom + 2;
    local_10.top = param_2 + 2;
    local_20.left = param_1;
    local_20.top = param_2 + 2;
    local_50.top = param_2;
    local_30.top = param_2;
    local_30.left = local_50.left;
    local_30.right = local_50.right;
    local_30.bottom = local_50.bottom;
    local_20.right = iVar4;
    local_20.bottom = local_40.bottom;
    local_10.left = local_50.left;
    local_10.right = local_50.right;
    local_10.bottom = local_40.bottom;
    DrawTextA(hdc,unaff_EDI,-1,&local_50,0);
    DrawTextA(hdc,unaff_EDI,-1,&local_40,0);
    DrawTextA(hdc,unaff_EDI,-1,&local_30,0);
    DrawTextA(hdc,unaff_EDI,-1,&local_20,0);
    DrawTextA(hdc,unaff_EDI,-1,&local_10,0);
  }
  SetTextColor(hdc,param_4);
  local_60.left = param_1 + 1;
  local_60.top = param_2 + 1;
  local_60.right = iVar1 + 1 + param_1;
  local_60.bottom = iVar2 + 1 + param_2;
  DrawTextA(hdc,unaff_EDI,-1,&local_60,0);
  pvVar3 = SelectObject(hdc,pvVar3);
  return CONCAT31((int3)((uint)pvVar3 >> 8),1);
}

