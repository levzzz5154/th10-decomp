/* Raw Ghidra reference; not compilable reconstruction. Address: 00438AD0 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 GameMain(HINSTANCE param_1)

{
  char cVar1;
  INT_PTR IVar2;
  void *pvVar3;
  undefined4 *puVar4;
  BOOL BVar5;
  char *pcVar6;
  int iVar7;
  void *this;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  LPCRITICAL_SECTION p_Var8;
  float10 fVar9;
  int local_20;
  tagMSG tStack_1c;
  
  local_20 = 0;
  _DAT_004924f8 = param_1;
  DAT_00491be0 = operator_new(0xa004);
  if (DAT_00491be0 == (undefined4 *)0x0) {
    DAT_00491be0 = (undefined4 *)0x0;
  }
  else {
    puVar4 = DAT_00491be0;
    for (iVar7 = 0x2801; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    DAT_00491be0[0x2800] = 0;
  }
  p_Var8 = (LPCRITICAL_SECTION)&DAT_00492274;
  iVar7 = 7;
  do {
    InitializeCriticalSection(p_Var8);
    p_Var8 = p_Var8 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  FUN_0044b810(&DAT_00474f70,&DAT_0046f77c);
  iVar7 = FUN_00439ff0();
  if (iVar7 == -1) goto LAB_00438dd0;
  _DAT_00491c28 = param_1;
  FUN_004392e0();
  iVar7 = FUN_00420870(this,0x491c28);
  if (iVar7 != 0) goto LAB_00438dd0;
  if ((DAT_00491d78 & 0x100) != 0) {
    IVar2 = DialogBoxParamA(param_1,&DAT_000000cb,(HWND)0x0,FUN_0043a3a0,0);
    DAT_00491d65 = IVar2 != 6;
  }
  FUN_0043a1c0();
  do {
    pvVar3 = operator_new(0x48);
    if (pvVar3 == (void *)0x0) {
      DAT_00491be4 = (void *)0x0;
    }
    else {
      DAT_00491be4 = (void *)FUN_00449aa0();
    }
    g_pD3D9 = (void *)Direct3DCreate9(0x20);
    if (g_pD3D9 == (void *)0x0) {
      FUN_0044b8e0(&DAT_0046f6a0);
    }
    else {
      iVar7 = FUN_00439730();
      pvVar3 = g_pWnd;
      if (iVar7 == 0) {
        puVar4 = &DAT_00492590;
        for (iVar7 = 0x14b4; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        DAT_004977b8 = pvVar3;
        _DAT_004977a8 =
             CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,FUN_0043ccf0,&DAT_00492590,0,
                          (LPDWORD)&DAT_004977b0);
        iVar7 = FUN_00439890();
        if (iVar7 == 0) {
          FUN_0044a0c0();
          FUN_0044b080();
          puVar4 = operator_new(0x732460);
          if (puVar4 == (undefined4 *)0x0) {
            g_pGameStateManager = (undefined4 *)0x0;
          }
          else {
            g_pGameStateManager = GameStateInit(puVar4);
          }
          if (DAT_00491d65 == '\0') {
            WINNLSEnableIME(0,0);
            ShowCursor(0);
            SetCursor((HCURSOR)0x0);
          }
          _DAT_00492540 = (double)_DAT_00470b70;
          fVar9 = FUN_00439540();
          _DAT_00492540 = (double)fVar9;
          _DAT_00492538 = (double)fVar9;
          _DAT_00492528 = (double)fVar9;
          _DAT_00492530 = (double)fVar9;
          SetForegroundWindow(g_pWnd);
          local_20 = FUN_00420470();
          if (local_20 == 0) {
            local_20 = 0;
            DAT_00492504 = 0xfc;
            while (DAT_004924f4 == 0) {
              BVar5 = PeekMessageA(&tStack_1c,(HWND)0x0,0,0,1);
              if (BVar5 == 0) {
                iVar7 = (**(code **)(*(int *)g_pD3DDevice + 0xc))(g_pD3DDevice);
                if (iVar7 == 0) {
                  local_20 = FUN_00439390(0x4924f0);
                  if (local_20 != 0) break;
                  DAT_00491ff4 = DAT_00491ff4 & 0xffffffef;
                }
                else if (iVar7 == -0x7789f797) {
                  FUN_00438a30();
                  iVar7 = (**(code **)(*(int *)g_pD3DDevice + 0x40))(g_pD3DDevice,&DAT_00491d0c);
                  if (iVar7 != 0) break;
                  FUN_00439d20(extraout_ECX);
                  _DAT_00491fd4 = 3;
                  DAT_00491ff4 = DAT_00491ff4 | 0x10;
                }
              }
              else {
                TranslateMessage(&tStack_1c);
                DispatchMessageA(&tStack_1c);
              }
            }
          }
          else if (local_20 != -1) {
            local_20 = 2;
          }
          FUN_00420270();
          pvVar3 = DAT_00491be4;
          if (DAT_00491be4 != (void *)0x0) {
            FUN_00438880((int)DAT_00491be4);
            _free(pvVar3);
          }
          DAT_00491be4 = (void *)0x0;
          do {
            iVar7 = FUN_0043ddf0(&DAT_00492590);
          } while (iVar7 != 0);
        }
      }
    }
LAB_00438dd0:
    DAT_004977b4 = 2;
    FUN_0043cc40();
    FUN_0043d120();
    pvVar3 = g_pGameStateManager;
    if (g_pGameStateManager != (void *)0x0) {
      FUN_00446220((int)g_pGameStateManager);
      _free(pvVar3);
    }
    g_pGameStateManager = (void *)0x0;
    if ((g_pD3DDevice != (void *)0x0) &&
       ((**(code **)(*(int *)g_pD3DDevice + 0x40))(g_pD3DDevice,&DAT_00491d0c),
       g_pD3DDevice != (void *)0x0)) {
      (**(code **)(*(int *)g_pD3DDevice + 8))(g_pD3DDevice);
      g_pD3DDevice = (void *)0x0;
    }
    if (g_pD3D9 != (void *)0x0) {
      (**(code **)(*(int *)g_pD3D9 + 8))(g_pD3D9);
      g_pD3D9 = (void *)0x0;
    }
    if (g_pWnd != (void *)0x0) {
      ShowWindow(g_pWnd,0);
      MoveWindow(g_pWnd,0,0,0,0,0);
      DestroyWindow(g_pWnd);
      g_pWnd = (void *)0x0;
    }
    ShowCursor(1);
    if (local_20 != 2) {
      WriteWholeFile("th10.cfg",&DAT_00491d48);
      if (DAT_00491fe8 != (void *)0x0) {
        FUN_0043ae20(extraout_ECX_00);
        pvVar3 = DAT_00491fe8;
        if (DAT_00491fe8 != (void *)0x0) {
          FUN_0043a910(extraout_ECX_01);
          _free(pvVar3);
        }
        DAT_00491fe8 = (void *)0x0;
      }
      if (PTR_DAT_00476f70 != &DAT_00474f70) {
        FUN_0044b810(&DAT_00474f70,"---------------------------------------------------------- \r\n"
                    );
        if (DAT_00476f74 != '\0') {
          MessageBoxA((HWND)0x0,&DAT_00474f70,"log",0x10);
        }
        pcVar6 = &DAT_00474f70;
        do {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
        } while (cVar1 != '\0');
        WriteWholeFile("./log.txt",&DAT_00474f70);
      }
      p_Var8 = (LPCRITICAL_SECTION)&DAT_00492274;
      iVar7 = 7;
      do {
        DeleteCriticalSection(p_Var8);
        p_Var8 = p_Var8 + 1;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      SystemParametersInfoA(0x11,DAT_0049251c,(PVOID)0x0,2);
      SystemParametersInfoA(0x55,DAT_00492520,(PVOID)0x0,2);
      SystemParametersInfoA(0x56,DAT_00492524,(PVOID)0x0,2);
      WINNLSEnableIME(0,1);
      puVar4 = DAT_00491be0;
      if (DAT_00491be0 != (undefined4 *)0x0) {
        if (DAT_00491be0[0x2800] != 0) {
          iVar7 = 0;
          do {
            pvVar3 = (void *)puVar4[iVar7];
            if (pvVar3 != (void *)0x0) {
              _free(pvVar3);
            }
            iVar7 = iVar7 + 1;
          } while (iVar7 < 0x2800);
        }
        _free(puVar4);
      }
      return 0;
    }
    PTR_DAT_00476f70 = &DAT_00474f70;
    DAT_00474f70 = 0;
    FUN_0044b810(&DAT_00474f70,&DAT_0046f6f0);
    if (DAT_00491d65 == '\0') {
      WINNLSEnableIME(0,1);
    }
    iVar7 = 0x3c;
    do {
      BVar5 = PeekMessageA(&tStack_1c,(HWND)0x0,0,0,1);
      if (BVar5 != 0) {
        TranslateMessage(&tStack_1c);
        DispatchMessageA(&tStack_1c);
      }
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  } while( true );
}

