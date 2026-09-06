/* Raw Ghidra reference; not compilable reconstruction. Address: 004588A7 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl FUN_004588a7(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  undefined4 local_28;
  char *local_24;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_00473660 ^ (uint)&stack0xfffffffc;
  if (0xa1 < param_4) {
    if (param_4 < 0x3eb) {
      if (param_4 != 0x3ea) {
        if (param_4 == 0xa2) {
          local_28 = 4;
          goto LAB_00458a59;
        }
        if (param_4 == 0xa6) {
          local_28 = 3;
          local_24 = "exp10";
        }
        else {
          if (param_4 != 0xaa) {
            if (param_4 == 0xab) {
              local_24 = "log2";
              goto LAB_00458adb;
            }
            if (param_4 == 1000) {
              local_24 = "log";
            }
            else {
              if (param_4 != 0x3e9) {
                return;
              }
              local_24 = "log10";
            }
            goto LAB_00458ad7;
          }
          local_28 = 2;
          local_24 = "log2";
        }
        goto LAB_00458a60;
      }
      local_24 = "exp";
    }
    else if (param_4 == 0x3eb) {
      local_24 = "atan";
    }
    else if (param_4 == 0x3ec) {
      local_24 = "ceil";
    }
    else if (param_4 == 0x3ed) {
      local_24 = "floor";
    }
    else {
      if (param_4 == 0x3ee) {
LAB_00458ab5:
        local_24 = "pow";
        goto LAB_00458adb;
      }
      if (param_4 != 0x3ef) {
        return;
      }
      local_24 = "modf";
    }
LAB_00458ad7:
    *param_3 = *param_1;
    goto LAB_00458adb;
  }
  if (param_4 == 0xa1) {
    local_28 = 3;
LAB_00458a59:
    local_24 = "exp2";
    goto LAB_00458a60;
  }
  if (param_4 < 0x19) {
    if (param_4 == 0x18) {
      local_28 = 3;
      goto LAB_0045895d;
    }
    if (param_4 == 2) {
      local_28 = 2;
      local_24 = "log";
    }
    else {
      if (param_4 == 3) {
        local_24 = "log";
LAB_00458adb:
        local_20 = *param_1;
        local_18 = *param_2;
        local_28 = 1;
        local_10 = *param_3;
        iVar1 = (*(code *)PTR_FUN_00473658)(&local_28);
        if (iVar1 == 0) {
          piVar2 = FUN_00456af2();
          *piVar2 = 0x21;
        }
        goto LAB_00458b0e;
      }
      if (param_4 == 8) {
        local_28 = 2;
        local_24 = "log10";
      }
      else {
        if (param_4 == 9) {
          local_24 = "log10";
          goto LAB_00458adb;
        }
        if (param_4 != 0xe) {
          if (param_4 != 0xf) {
            return;
          }
          local_24 = "exp";
          goto LAB_004589a5;
        }
        local_28 = 3;
        local_24 = "exp";
      }
    }
  }
  else {
    if (param_4 == 0x19) {
      local_24 = "pow";
LAB_004589a5:
      local_20 = *param_1;
      local_18 = *param_2;
      local_28 = 4;
      local_10 = *param_3;
      (*(code *)PTR_FUN_00473658)(&local_28);
      goto LAB_00458b0e;
    }
    if (param_4 == 0x1a) {
      local_10 = 0x3ff0000000000000;
      goto LAB_00458b0e;
    }
    if (param_4 != 0x1b) {
      if (param_4 == 0x1c) goto LAB_00458ab5;
      if (param_4 != 0x1d) {
        return;
      }
      local_24 = "pow";
      goto LAB_00458ad7;
    }
    local_28 = 2;
LAB_0045895d:
    local_24 = "pow";
  }
LAB_00458a60:
  local_20 = *param_1;
  local_18 = *param_2;
  local_10 = *param_3;
  iVar1 = (*(code *)PTR_FUN_00473658)(&local_28);
  if (iVar1 == 0) {
    piVar2 = FUN_00456af2();
    *piVar2 = 0x22;
  }
LAB_00458b0e:
  *param_3 = local_10;
  return;
}

