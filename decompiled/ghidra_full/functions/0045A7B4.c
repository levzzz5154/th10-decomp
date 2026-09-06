/* Raw Ghidra reference; not compilable reconstruction. Address: 0045A7B4 */

/* Library Function - Single Match
    __store_num
   
   Library: Visual Studio 2003 Release */

void __fastcall __store_num(uint *param_1,uint param_2,int param_3)

{
  char cVar1;
  uint uVar2;
  int in_EAX;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  int *unaff_EDI;
  int local_8;
  
  local_8 = 0;
  if (param_3 == 0) {
    if (param_2 < *param_1) {
      iVar3 = param_2 - 1;
      if (param_2 != 0) {
        do {
          local_8 = local_8 + 1;
          *(char *)(iVar3 + *unaff_EDI) = (char)(in_EAX % 10) + '0';
          iVar3 = iVar3 + -1;
          in_EAX = in_EAX / 10;
        } while (iVar3 != -1);
      }
      *unaff_EDI = *unaff_EDI + local_8;
      *param_1 = *param_1 - local_8;
    }
    else {
      *param_1 = 0;
    }
  }
  else {
    uVar2 = *param_1;
    pcVar5 = (char *)*unaff_EDI;
    do {
      if (uVar2 < 2) break;
      iVar3 = in_EAX / 10;
      *pcVar5 = (char)(in_EAX % 10) + '0';
      pcVar5 = pcVar5 + 1;
      *param_1 = *param_1 - 1;
      uVar2 = *param_1;
      in_EAX = iVar3;
    } while (0 < iVar3);
    pcVar4 = (char *)*unaff_EDI;
    *unaff_EDI = (int)pcVar5;
    pcVar5 = pcVar5 + -1;
    do {
      cVar1 = *pcVar5;
      *pcVar5 = *pcVar4;
      pcVar5 = pcVar5 + -1;
      *pcVar4 = cVar1;
      pcVar4 = pcVar4 + 1;
    } while (pcVar4 < pcVar5);
  }
  return;
}

