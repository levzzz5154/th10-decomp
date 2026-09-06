/* Raw Ghidra reference; not compilable reconstruction. Address: 00420870 */

undefined4 __thiscall FUN_00420870(void *this,size_t param_1)

{
  size_t sVar1;
  byte *_Memory;
  int iVar2;
  undefined4 extraout_ECX;
  LPCSTR unaff_EBX;
  byte *pbVar3;
  undefined4 *puVar4;
  char *pcVar5;
  
  sVar1 = param_1;
  FUN_00418c40(this,&DAT_00491d48);
  _Memory = FUN_0044b360(&param_1,1);
  if (_Memory == (byte *)0x0) {
    pcVar5 = &DAT_0046de7c;
  }
  else {
    pbVar3 = _Memory;
    puVar4 = &DAT_00491d48;
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *(undefined4 *)pbVar3;
      pbVar3 = pbVar3 + 4;
      puVar4 = puVar4 + 1;
    }
    _free(_Memory);
    if (((((DAT_00491d62 < 2) && (DAT_00491d63 < 3)) && (DAT_00491d64 < 2)) &&
        ((DAT_00491d65 < 2 && (DAT_00491d66 < 3)))) &&
       ((DAT_00491d67 < 3 && ((DAT_00491d48 == 0x100003 && (param_1 == 0x34)))))) {
      DAT_00474e88 = DAT_00491d4c;
      DAT_00474e8c = DAT_00491d50;
      DAT_00474e90 = DAT_00491d54;
      DAT_00474e94 = DAT_00491d58;
      DAT_00474e98 = DAT_00491d5c;
      goto LAB_00420959;
    }
    pcVar5 = &DAT_0046de48;
  }
  FUN_0044b810(&DAT_00474f70,pcVar5);
  FUN_00418c40(extraout_ECX,&DAT_00491d48);
LAB_00420959:
  *(undefined4 *)(sVar1 + 0x3b4) = 0;
  if ((*(byte *)(sVar1 + 0x150) & 4) != 0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046de2c);
  }
  if ((*(byte *)(sVar1 + 0x150) & 1) != 0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046de04);
  }
  if (*(char *)(sVar1 + 0x13d) != '\0') {
    FUN_0044b810(&DAT_00474f70,&DAT_0046dde4);
  }
  if ((*(byte *)(sVar1 + 0x150) & 2) != 0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046ddbc);
  }
  if ((*(byte *)(sVar1 + 0x150) & 8) != 0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046dd84);
  }
  if ((*(byte *)(sVar1 + 0x150) & 0x10) != 0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046dd64);
  }
  if ((*(byte *)(sVar1 + 0x150) & 0x20) != 0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046dd4c);
    DAT_00491fdc = 1;
  }
  if ((*(byte *)(sVar1 + 0x150) & 0x40) != 0) {
    FUN_0044b810(&DAT_00474f70,&DAT_0046dd28);
  }
  iVar2 = WriteWholeFile(unaff_EBX,&DAT_00491d48);
  if (iVar2 != 0) {
    FUN_0044b8e0(&DAT_0046dd08);
    FUN_0044b8e0(&DAT_0046dcb0);
    return 0xffffffff;
  }
  return 0;
}

