/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004218D0
 * Tracking name: FUN_004218d0
 * Ghidra name: FUN_004218d0
 * Tracked span: 704 bytes
 */


undefined4 FUN_004218d0(void)

{
  int iVar1;
  int in_EAX;
  void *pvVar2;
  
  if (*(int *)(in_EAX + 0x38c) == *(int *)(in_EAX + 0x390)) {
    return 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x6c4));
  iVar1 = *(int *)(in_EAX + 0x38c);
  *(char *)(in_EAX + 0x6f9) = *(char *)(in_EAX + 0x6f9) + '\x01';
  *(int *)(in_EAX + 0x394) = iVar1;
  *(undefined4 *)(in_EAX + 0x780) = 0xff000000;
  switch(*(undefined4 *)(in_EAX + 0x390)) {
  case 0:
    *(undefined4 *)(in_EAX + 0x390) = 1;
    pvVar2 = FUN_0041fd00();
    *(void **)(in_EAX + 0x768) = pvVar2;
    if (pvVar2 == (void *)0x0) {
      *(undefined4 *)(in_EAX + 0x390) = 3;
      goto switchD_00421924_caseD_3;
    }
    break;
  case 3:
switchD_00421924_caseD_3:
    FUN_004203f0();
    FUN_00421c50();
    return 4;
  case 4:
    switch(iVar1) {
    case 1:
    case 2:
      break;
    default:
      goto switchD_00421924_caseD_1;
    case 7:
      FUN_00418150();
      break;
    case 0xe:
      FUN_0040b9d0();
    }
    goto switchD_00421974_caseD_1;
  case 7:
    if (iVar1 == 4) {
      FUN_0042cdb0();
    }
    *(undefined4 *)(in_EAX + 0x39c) = 1;
    FUN_004180e0();
    break;
  case 10:
    FUN_00418150();
    *(undefined4 *)(in_EAX + 0x39c) = 1;
    *(undefined4 *)(in_EAX + 0x390) = 7;
    DAT_00477848 = &DAT_00474788 + DAT_00474c80 * 0x30;
    DAT_00474c7c = DAT_00474c80;
    FUN_004180e0();
    break;
  case 0xb:
    *(undefined4 *)(in_EAX + 0x39c) = 0;
    if (iVar1 == 7) {
      FUN_00418150();
    }
    *(undefined4 *)(in_EAX + 0x390) = 7;
    FUN_004180e0();
    break;
  case 0xc:
    if (iVar1 == 4) {
      FUN_0042cdb0();
    }
    *(undefined4 *)(in_EAX + 0x390) = 7;
    *(undefined4 *)(in_EAX + 0x39c) = 1;
    FUN_004180e0();
    break;
  case 0xd:
    FUN_00418150();
    *(undefined4 *)(in_EAX + 0x39c) = 1;
    *(undefined4 *)(in_EAX + 0x390) = 7;
    FUN_004180e0();
    break;
  case 0xe:
    if (iVar1 == 7) {
      FUN_00418150();
    }
    FUN_0040b940();
    break;
  case 0xf:
    if (iVar1 != 2) {
      if (iVar1 == 7) {
        FUN_00418150();
      }
      else {
        if (iVar1 != 0xe) break;
        FUN_0040b9d0();
      }
    }
    *(undefined4 *)(in_EAX + 0x390) = 4;
    DAT_00491c00 = 3;
switchD_00421974_caseD_1:
    FUN_0042cd50();
  }
switchD_00421924_caseD_1:
  *(undefined4 *)(in_EAX + 0x38c) = *(undefined4 *)(in_EAX + 0x390);
  LeaveCriticalSection((LPCRITICAL_SECTION)(in_EAX + 0x6c4));
  *(char *)(in_EAX + 0x6f9) = *(char *)(in_EAX + 0x6f9) + -1;
  return 1;
}

