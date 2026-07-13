/*
 * Raw Ghidra pseudocode reference; not directly compilable.
 * Address: 0x004465B0
 * Tracking name: FUN_004465b0
 * Ghidra name: FUN_004465b0
 * Tracked span: 1728 bytes
 */


/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_004465b0(void)

{
  ushort uVar1;
  undefined4 *in_EAX;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  undefined4 unaff_ESI;
  uint uVar6;
  uint *puVar7;
  undefined1 **ppuVar8;
  uint uVar9;
  uint uVar10;
  uint uStack_4c;
  undefined1 *puStack_48;
  undefined4 local_40 [4];
  byte abStack_2e [2];
  uint uStack_2c;
  uint uStack_28;
  
  puStack_48 = (undefined1 *)local_40;
  local_40[0] = 0;
  (**(code **)(*(int *)*in_EAX + 0x48))((int *)*in_EAX);
  (**(code **)(iRam00000000 + 0x30))();
  ppuVar8 = &puStack_48;
  puVar7 = &uStack_2c;
  (**(code **)(uStack_2c + 0x34))(&uStack_2c,ppuVar8,0,0);
  switch(unaff_ESI) {
  case 0:
  case 0x15:
    uVar9 = 0;
    if (uStack_28 != 0) {
      do {
        uVar10 = 0;
        if (uStack_2c != 0) {
          pbVar2 = abStack_2e;
          puVar5 = &uStack_2c;
          do {
            if (pbVar2[5] == 0) {
              puStack_48 = (undefined1 *)0x0;
              uStack_4c = 0;
              uVar3 = 0;
              uVar4 = 0;
              if ((uVar10 != 0) && (pbVar2[1] != 0)) {
                uStack_4c = (uint)pbVar2[-1];
                uVar3 = (uint)*pbVar2;
                puStack_48 = (undefined1 *)(uint)pbVar2[-2];
                uVar4 = 1;
              }
              if ((uVar10 < uStack_2c - 1) && (pbVar2[9] != 0)) {
                uVar3 = uVar3 + pbVar2[8];
                uStack_4c = uStack_4c + pbVar2[7];
                puStack_48 = puStack_48 + pbVar2[6];
                uVar4 = uVar4 + 1;
              }
              if ((uVar9 != 0) && (*(byte *)((int)puVar5 + 3) != 0)) {
                uVar3 = uVar3 + *(byte *)((int)puVar5 + 2);
                uStack_4c = uStack_4c + *(byte *)((int)puVar5 + 1);
                puStack_48 = puStack_48 + (byte)*puVar5;
                uVar4 = uVar4 + 1;
              }
              if ((uVar9 < uStack_28 - 1) && (*(byte *)((int)puVar5 + 3) != 0)) {
                uVar3 = uVar3 + *(byte *)((int)puVar5 + 2);
                uStack_4c = uStack_4c + *(byte *)((int)puVar5 + 1);
                puStack_48 = puStack_48 + (byte)*puVar5;
                uVar4 = uVar4 + 1;
              }
              if (1 < uVar4) {
                uVar3 = uVar3 / uVar4;
                uStack_4c = uStack_4c / uVar4;
                puStack_48 = (undefined1 *)((uint)puStack_48 / uVar4);
              }
              pbVar2[3] = (byte)uStack_4c;
              *(byte *)puVar5 = (byte)puStack_48;
              pbVar2[4] = (byte)uVar3;
            }
            puVar5 = puVar5 + 1;
            pbVar2 = pbVar2 + 4;
            uVar10 = uVar10 + 1;
          } while (uVar10 < uStack_2c);
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < uStack_28);
    }
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x16:
  case 0x17:
  case 0x18:
    break;
  case 0x19:
    uVar9 = 0;
    if (uStack_28 != 0) {
      do {
        uVar10 = 0;
        puVar5 = &uStack_2c;
        if (uStack_2c != 0) {
          do {
            if ((*puVar5 & 0x8000) == 0) {
              uVar4 = 0;
              uVar3 = 0;
              uVar6 = 0;
              puStack_48 = (undefined1 *)0x0;
              if (uVar10 != 0) {
                uVar1 = *(ushort *)((int)puVar5 + -2);
                if ((short)uVar1 < 0) {
                  uVar3 = uVar1 >> 10 & 0x1f;
                  uVar4 = uVar1 >> 5 & 0x1f;
                  puStack_48 = (undefined1 *)(uVar1 & 0x1f);
                  uVar6 = 1;
                }
              }
              if (uVar10 < uStack_2c - 1) {
                uVar1 = *(ushort *)((int)puVar5 + 2);
                if ((short)uVar1 < 0) {
                  uVar3 = uVar3 + (uVar1 >> 10 & 0x1f);
                  puStack_48 = puStack_48 + (uVar1 & 0x1f);
                  uVar4 = uVar4 + (uVar1 >> 5 & 0x1f);
                  uVar6 = uVar6 + 1;
                }
              }
              if (uVar9 != 0) {
                uVar1 = (ushort)*puVar5;
                if ((short)uVar1 < 0) {
                  uVar3 = uVar3 + (uVar1 >> 10 & 0x1f);
                  uVar4 = uVar4 + (uVar1 >> 5 & 0x1f);
                  puStack_48 = puStack_48 + (uVar1 & 0x1f);
                  uVar6 = uVar6 + 1;
                }
              }
              if (uVar9 < uStack_28 - 1) {
                uVar1 = (ushort)*puVar5;
                if ((short)uVar1 < 0) {
                  uVar3 = uVar3 + (uVar1 >> 10 & 0x1f);
                  uVar4 = uVar4 + (uVar1 >> 5 & 0x1f);
                  puStack_48 = puStack_48 + (uVar1 & 0x1f);
                  uVar6 = uVar6 + 1;
                }
              }
              if (1 < uVar6) {
                uVar3 = uVar3 / uVar6;
                uVar4 = uVar4 / uVar6;
                puStack_48 = (undefined1 *)((uint)puStack_48 / uVar6);
              }
              *(ushort *)puVar5 =
                   (ushort)(((uint)((byte)uVar3 & 0x1f) << 5 | uVar4 & 0xffffff1f) << 5) |
                   (ushort)*puVar5 & 0x8000 | (ushort)((byte)puStack_48 & 0x1f);
            }
            uVar10 = uVar10 + 1;
            puVar5 = (uint *)((int)puVar5 + 2);
          } while (uVar10 < uStack_2c);
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < uStack_28);
    }
    break;
  case 0x1a:
    uVar9 = 0;
    if (uStack_28 != 0) {
      do {
        uVar10 = 0;
        puVar5 = &uStack_2c;
        if (uStack_2c != 0) {
          do {
            if ((*puVar5 & 0xf000) == 0) {
              uVar4 = 0;
              uVar3 = 0;
              uVar6 = 0;
              puStack_48 = (undefined1 *)0x0;
              if (uVar10 != 0) {
                uVar1 = *(ushort *)((int)puVar5 + -2);
                if ((uVar1 & 0xf000) != 0) {
                  uVar3 = uVar1 >> 8 & 0xf;
                  uVar4 = uVar1 >> 4 & 0xf;
                  puStack_48 = (undefined1 *)(uVar1 & 0xf);
                  uVar6 = 1;
                }
              }
              if (uVar10 < uStack_2c - 1) {
                uVar1 = *(ushort *)((int)puVar5 + 2);
                if ((uVar1 & 0xf000) != 0) {
                  uVar4 = uVar4 + (uVar1 >> 4 & 0xf);
                  puStack_48 = puStack_48 + (uVar1 & 0xf);
                  uVar3 = uVar3 + (uVar1 >> 8 & 0xf);
                  uVar6 = uVar6 + 1;
                }
              }
              if (uVar9 != 0) {
                uVar1 = (ushort)*puVar5;
                if ((uVar1 & 0xf000) != 0) {
                  uVar3 = uVar3 + (uVar1 >> 8 & 0xf);
                  uVar4 = uVar4 + (uVar1 >> 4 & 0xf);
                  puStack_48 = puStack_48 + (uVar1 & 0xf);
                  uVar6 = uVar6 + 1;
                }
              }
              if (uVar9 < uStack_28 - 1) {
                uVar1 = (ushort)*puVar5;
                if ((uVar1 & 0xf000) != 0) {
                  uVar3 = uVar3 + (uVar1 >> 8 & 0xf);
                  uVar4 = uVar4 + (uVar1 >> 4 & 0xf);
                  puStack_48 = puStack_48 + (uVar1 & 0xf);
                  uVar6 = uVar6 + 1;
                }
              }
              if (1 < uVar6) {
                uVar3 = uVar3 / uVar6;
                uVar4 = uVar4 / uVar6;
                puStack_48 = (undefined1 *)((uint)puStack_48 / uVar6);
              }
              *(ushort *)puVar5 =
                   (ushort)(((uint)((byte)uVar3 & 0xf) << 4 | uVar4 & 0xffffff0f) << 4) |
                   (ushort)*puVar5 & 0xf000 | (ushort)((byte)puStack_48 & 0xf);
            }
            puVar5 = (uint *)((int)puVar5 + 2);
            uVar10 = uVar10 + 1;
          } while (uVar10 < uStack_2c);
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < uStack_28);
    }
    break;
  default:
    goto switchD_004465ff_default;
  }
switchD_004465ff_default:
  (**(code **)(*ppuVar8 + 0x38))(ppuVar8);
  (**(code **)(*puVar7 + 8))(puVar7);
  return;
}

