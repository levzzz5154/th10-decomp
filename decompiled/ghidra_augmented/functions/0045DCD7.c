/* Raw Ghidra reference; not compilable reconstruction. Address: 0045DCD7 */

/* Library Function - Single Match
    __cftoe2
   
   Library: Visual Studio 2003 Release */

void __cdecl __cftoe2(int param_1,int param_2,char param_3)

{
  int *in_EAX;
  undefined1 *puVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  undefined1 *unaff_EBX;
  
  if (param_3 != '\0') {
    __shift();
  }
  if (*in_EAX == 0x2d) {
    *unaff_EBX = 0x2d;
    unaff_EBX = unaff_EBX + 1;
  }
  puVar1 = unaff_EBX;
  if (0 < param_1) {
    puVar1 = unaff_EBX + 1;
    *unaff_EBX = *puVar1;
    *puVar1 = DAT_00473af4;
  }
  puVar2 = FUN_0045bd80((uint *)(puVar1 + param_1 + (uint)(param_3 == '\0')),(uint *)"e+000");
  if (param_2 != 0) {
    *(undefined1 *)puVar2 = 0x45;
  }
  if (*(char *)in_EAX[3] != '0') {
    iVar3 = in_EAX[1] + -1;
    if (iVar3 < 0) {
      iVar3 = -iVar3;
      *(undefined1 *)((int)puVar2 + 1) = 0x2d;
    }
    if (99 < iVar3) {
      iVar4 = iVar3 / 100;
      iVar3 = iVar3 % 100;
      *(char *)((int)puVar2 + 2) = *(char *)((int)puVar2 + 2) + (char)iVar4;
    }
    if (9 < iVar3) {
      iVar4 = iVar3 / 10;
      iVar3 = iVar3 % 10;
      *(char *)((int)puVar2 + 3) = *(char *)((int)puVar2 + 3) + (char)iVar4;
    }
    *(char *)(puVar2 + 1) = (char)puVar2[1] + (char)iVar3;
  }
  return;
}

