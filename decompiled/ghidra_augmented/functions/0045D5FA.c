/* Raw Ghidra reference; not compilable reconstruction. Address: 0045D5FA */

/* Library Function - Single Match
    __ld12told
   
   Library: Visual Studio 2003 Release */

INTRNCVT_STATUS __cdecl __ld12told(_LDBL12 *_Ifp,_LDOUBLE *_Ld)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  INTRNCVT_STATUS local_8;
  
  local_8 = INTRNCVT_OK;
  uVar1 = *(ushort *)(_Ifp->ld12 + 10);
  local_14 = *(undefined4 *)(_Ifp->ld12 + 6);
  local_10 = *(undefined4 *)(_Ifp->ld12 + 2);
  local_c = (uint)*(ushort *)_Ifp->ld12 << 0x10;
  uVar3 = uVar1 & 0x7fff;
  iVar2 = __RoundMan((int)&local_14,0x40);
  if (iVar2 != 0) {
    local_14 = 0x80000000;
    uVar3 = uVar3 + 1;
  }
  if (uVar3 == 0x7fff) {
    local_8 = INTRNCVT_OVERFLOW;
  }
  *(undefined4 *)(_Ld->ld + 4) = local_14;
  *(ushort *)(_Ld->ld + 8) = uVar1 & 0x8000 | uVar3;
  *(undefined4 *)_Ld->ld = local_10;
  return local_8;
}

