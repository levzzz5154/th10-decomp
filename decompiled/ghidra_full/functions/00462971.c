/* Raw Ghidra reference; not compilable reconstruction. Address: 00462971 */

/* Library Function - Single Match
    struct _s_TryBlockMapEntry const * __cdecl _GetRangeOfTrysToCheck(struct _s_FuncInfo const
   *,int,int,unsigned int *,unsigned int *)
   
   Library: Visual Studio 2003 Release */

_s_TryBlockMapEntry * __cdecl
_GetRangeOfTrysToCheck(_s_FuncInfo *param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  uint uVar1;
  TryBlockMapEntry *pTVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar1 = param_1->nTryBlocks;
  pTVar2 = param_1->pTryBlockMap;
  uVar5 = uVar1;
  uVar4 = uVar1;
  while (uVar3 = uVar5, -1 < param_2) {
    if (uVar1 == 0xffffffff) {
      _inconsistency();
    }
    uVar1 = uVar1 - 1;
    if (((pTVar2[uVar1].tryHigh < param_3) && (param_3 <= pTVar2[uVar1].catchHigh)) ||
       (uVar5 = uVar3, uVar1 == -1)) {
      param_2 = param_2 + -1;
      uVar5 = uVar1;
      uVar4 = uVar3;
    }
  }
  uVar1 = uVar1 + 1;
  *param_4 = uVar1;
  *param_5 = uVar4;
  if ((param_1->nTryBlocks < uVar4) || (uVar4 < uVar1)) {
    _inconsistency();
  }
  return pTVar2 + uVar1;
}

