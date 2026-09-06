/* Raw Ghidra reference; not compilable reconstruction. Address: 0043A910 */

void __fastcall FUN_0043a910(undefined4 param_1)

{
  undefined4 *in_EAX;
  undefined4 *puVar1;
  int iVar2;
  
  *in_EAX = &PTR_FUN_0046f80c;
  FUN_0043ae20(param_1);
  FUN_0043aa60();
  puVar1 = in_EAX + 0x26;
  iVar2 = 0x20;
  do {
    if ((void *)*puVar1 != (void *)0x0) {
      _free((void *)*puVar1);
      *puVar1 = 0;
    }
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if ((HMIDIOUT)in_EAX[0x4f] != (HMIDIOUT)0x0) {
    midiOutReset((HMIDIOUT)in_EAX[0x4f]);
    midiOutClose((HMIDIOUT)in_EAX[0x4f]);
    in_EAX[0x4f] = 0;
  }
  *in_EAX = &PTR_LAB_0046f810;
  if (in_EAX[1] != 0) {
    timeKillEvent(in_EAX[1]);
  }
  timeEndPeriod(in_EAX[2]);
  in_EAX[1] = 0;
  timeEndPeriod(in_EAX[2]);
  return;
}

