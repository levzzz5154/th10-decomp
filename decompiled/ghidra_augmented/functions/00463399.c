/* Raw Ghidra reference; not compilable reconstruction. Address: 00463399 */

/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    void __cdecl BuildCatchObject(struct EHExceptionRecord *,void *,struct _s_HandlerType const
   *,struct _s_CatchableType const *)
   
   Library: Visual Studio 2003 Release */

void __cdecl
BuildCatchObject(EHExceptionRecord *param_1,void *param_2,_s_HandlerType *param_3,
                _s_CatchableType *param_4)

{
  int iVar1;
  void *pvVar2;
  void *_Src;
  byte *in_ECX;
  int *in_EDX;
  PMD *unaff_ESI;
  PMD *unaff_EDI;
  
  if (*(int *)((int)param_2 + 4) == 0) {
    return;
  }
  if (*(char *)(*(int *)((int)param_2 + 4) + 8) == '\0') {
    return;
  }
  if ((*(int *)((int)param_2 + 8) == 0) && ((*(byte *)((int)param_2 + 3) & 0x80) == 0)) {
    return;
  }
  if (-1 < (int)*(uint *)param_2) {
    in_EDX = (int *)(*(int *)((int)param_2 + 8) + 0xc + (int)in_EDX);
  }
  pvVar2 = *(void **)(param_1 + 0x18);
  if ((*(uint *)param_2 & 8) == 0) {
    if ((*in_ECX & 1) == 0) {
      if (*(int *)(in_ECX + 0x18) == 0) {
        iVar1 = _ValidateRead(pvVar2,1);
        if ((iVar1 != 0) && (iVar1 = _ValidateWrite(in_EDX,1), iVar1 != 0)) {
          pvVar2 = *(void **)(in_ECX + 0x14);
          _Src = AdjustPointer(pvVar2,unaff_EDI);
          _memmove(in_EDX,_Src,(size_t)pvVar2);
          return;
        }
      }
      else {
        iVar1 = _ValidateRead(pvVar2,1);
        if (((iVar1 != 0) && (iVar1 = _ValidateWrite(in_EDX,1), iVar1 != 0)) &&
           (iVar1 = _ValidateExecute(*(_func_int **)(in_ECX + 0x18)), iVar1 != 0)) {
          if ((*in_ECX & 4) != 0) {
            AdjustPointer((void *)0x1,unaff_EDI);
            FID_conflict__CallMemberFunction1(in_EDX,*(undefined **)(in_ECX + 0x18));
            return;
          }
          AdjustPointer(unaff_EDI,unaff_ESI);
          FID_conflict__CallMemberFunction1(in_EDX,*(undefined **)(in_ECX + 0x18));
          return;
        }
      }
    }
    else {
      iVar1 = _ValidateRead(pvVar2,1);
      if ((iVar1 != 0) && (iVar1 = _ValidateWrite(in_EDX,1), iVar1 != 0)) {
        _memmove(in_EDX,*(void **)(param_1 + 0x18),*(size_t *)(in_ECX + 0x14));
        if (*(int *)(in_ECX + 0x14) != 4) {
          return;
        }
        if (*in_EDX == 0) {
          return;
        }
        goto LAB_00463412;
      }
    }
  }
  else {
    iVar1 = _ValidateRead(pvVar2,1);
    if ((iVar1 != 0) && (iVar1 = _ValidateWrite(in_EDX,1), iVar1 != 0)) {
      *in_EDX = *(int *)(param_1 + 0x18);
LAB_00463412:
      pvVar2 = AdjustPointer(unaff_EDI,unaff_ESI);
      *in_EDX = (int)pvVar2;
      return;
    }
  }
  _inconsistency();
  return;
}

