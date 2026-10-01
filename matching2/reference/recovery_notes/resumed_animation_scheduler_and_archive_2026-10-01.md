# Animation, scheduler, manager destruction, and archive recovery: Wave19

This wave moves 44 complete original owners to C++, adding 6195 bytes (1.501192% of .text). Of these, 42 were assembly owners and 2 were game-generated exception handlers formerly labelled as toolkit code. The original owner boundaries and aliases are preserved. The wave includes Claude's interrupted animation/texture, entity/player, item/listener, music and resource-release work, plus the primary scheduler, manager destruction, and archive parser recovered during this continuation.

| Routine | Original address | Complete bytes |
| --- | --- | ---: |
| Entity_StartScript_00404f30 | 0x00404F30 | 202 |
| PowerDisplayOwner_SetPowerDigits_004054b0 | 0x004054B0 | 79 |
| PlayerFlags_ClearExpiredFlags_00405500 | 0x00405500 | 81 |
| Player_DrawSprites_00409190 | 0x00409190 | 46 |
| RecoveryEmitter_UpdateDecision_0040b9f0 | 0x0040B9F0 | 111 |
| Deletable_0040d710_DeleteIfPresent | 0x0040D730 | 19 |
| AnimationSlot_Release_004136c0 | 0x004136C0 | 97 |
| ManagerTeardown_0041ADF0 | 0x0041ADF0 | 216 |
| ItemManager_Draw_0041b8e0 | 0x0041B8E0 | 281 |
| ItemManager_OnDraw_0041ba30 | 0x0041BA30 | 29 |
| Item_EnterState2_0041be40 | 0x0041BE40 | 46 |
| ListenerOwner_Broadcast_0041c760 | 0x0041C760 | 102 |
| Music_PlayFile_00420b80 | 0x00420B80 | 125 |
| MusicRequests_Unpause_00424460 | 0x00424460 | 15 |
| MusicRequests_Pause_00424470 | 0x00424470 | 15 |
| PlaybackState_OnSwitch_00427ad0 | 0x00427AD0 | 12 |
| RecoveryMusicInstallSlot_0042c670 | 0x0042C670 | 95 |
| FindAnimationSlotChild_0042c7c0 | 0x0042C7C0 | 25 |
| MusicRequests_SetVolume_00434b80 | 0x00434B80 | 15 |
| Archive_BuildIndex_004350d0 | 0x004350D0 | 327 |
| Sound_LoadPendingSlot_0043d640 | 0x0043D640 | 37 |
| SoundCommandManager_StartMusicCommand_0043da80 | 0x0043DA80 | 44 |
| EntityArray_StartScripts_004415c0 | 0x004415C0 | 57 |
| AnimationInterpolatedObject_StartChannel208 | 0x00441F50 | 116 |
| AnimationInterpolatedObject_StartColor1BC | 0x00442050 | 208 |
| AnimationInterpolatedObject_StartColor0BC | 0x00442220 | 208 |
| AnmTexture_LoadFile_00446b70 | 0x00446B70 | 245 |
| AnmTexture_Upload_00446c70 | 0x00446C70 | 243 |
| AnmTexture_UploadAt_00446d70 | 0x00446D70 | 320 |
| AnmTexture_CreateFromMemory_00446eb0 | 0x00446EB0 | 132 |
| AnmTexture_CreateAndUpload_00446f40 | 0x00446F40 | 264 |
| AnmManager_LoadFileNow_00447080 | 0x00447080 | 50 |
| AnmManager_LoadFile_004470c0 | 0x004470C0 | 433 |
| AnmFile_PreloadEntryImage_004472e0 | 0x004472E0 | 214 |
| AnmManager_LoadNextEntry_004473c0 | 0x004473C0 | 174 |
| AnmFile_LoadEntry_00447470 | 0x00447470 | 650 |
| AnmManager_ServicePending_00447700 | 0x00447700 | 135 |
| AnimationManager_CopyToBackBuffer_00447fd0 | 0x00447FD0 | 330 |
| Scheduler_RunPrimary_00449c00 | 0x00449C00 | 308 |
| D3DResourceManager_ReleaseResources_00449eb0 | 0x00449EB0 | 30 |
| Archive_IndexConstructionCleanup_004653c0 | 0x004653C0 | 11 |
| Archive_IndexConstructionHandler_004653cb | 0x004653CB | 10 |
| ManagerArrayUnwind_00465400 | 0x00465400 | 28 |
| ManagerArrayHandler_0046541C | 0x0046541C | 10 |

The primary scheduler at 0x00449C00 is a public one-stack-argument RET4 entry. Ordinary C++ preserves lock-depth changes, all eight callback outcomes, saved-next-node traversal, list restart, and the removal callback. The retry label belongs inside the enabled branch; moving it there reproduces the natural loop alignment. Its entire308-byte native /Gy section, including the compiler switch table, matches literally after every ordinary COFF relocation is resolved. It uses no synthetic caller, assembly, volatile or barriers. Existing Secondary (268 bytes) and Allocator (74 bytes) remain exact. Three ordinary typed allocator models emit 69 versus 74 and are explicitly unselected; the old allocator assembly/volatile remains.

The manager destructor at 0x0041ADF0 is a genuine complete C++ member-array destructor: 2,198 elements of 1,008 bytes, starting at manager+0x14. Its native 216-byte body, generated array cleanup (28 bytes) and handler (10 bytes), and the complete 36-byte exception metadata all match literally. The actual element destructor and scheduler removal dependency bodies are used. The full owned-delete caller naturally emits 28 versus original 18 and is explicitly unselected; it receives no recovery credit.

The archive BuildIndex at 0x004350D0 parser uses ordinary C++ array allocation and construction with the original three stack inputs. Its complete 327-byte body, generated cleanup (11 bytes) and handler (10 bytes), and complete 36-byte exception metadata match. The preserved finite behavior proof covers 174 normal and 278 registered-unwind cases. The strict maintained cluster includes the complete genuine Index caller and cipher: Index naturally emits 357 versus original 350 and has a different receiver convention, so that caller remains unselected and its assembly owner remains maintained.

The surface loader at 0x00447C80 was prematurely classified semantic in Claude's tree. Its corrected candidate emits 577 versus original 576 and fails the layout gate; the original assembly owner remains exact, and the candidate is preserved with zero credit. See [surface failure details](animation_load_surface_00447c80_unmatched_2026-10-01.md). The back-buffer copier at 0x00447FD0 is independently recovered and verified.

The concurrent shared-workspace item-draw pair adds complete Draw (281 bytes) and Callback (29 bytes) bodies. Root independently rebuilt and verified them under the user's commit-everything instruction. Their supplied synthetic array-walking context (78 bytes) and dispatcher stand-in (19 bytes) remain explicit inherited provenance limitations, with zero context-byte credit. No genuine full 0x004451C0 dispatcher graph is claimed for this pair.

The current whole build compiles 1846 maintained sources with zero failures. The complete 487,936-byte executable is byte-identical to the original, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`. All current build-source hashes and native compiler inputs, objects, complete function extents and literal bytes are verified. No reference instruction bytes are used to construct the compiler bodies, and no comparison bytes are masked.

Since full-access work resumed, 92 complete routines / 13038 bytes have been recovered, including 5 previously misattributed game exception handlers / 50 bytes. Existing semantic source migrations receive zero new-byte credit. Current semantic coverage is 1960 owners / 113499 bytes. The full selected-body audit proves 1954 syntactically assembly-free owners / 108974 bytes (26.406929% of .text). Six mixed owners / 4,525 bytes remain explicit. The finite volatile intent review covers 40 owners / 7329 bytes and is not exhaustive. This includes three new ANM cursor users: their volatile member access is verified, while the original concurrency intent remains unproven.

Reproduce the fresh whole build with:

```sh
WINEPREFIX=/tmp/th10-decomp-wine-20261001 WINEDEBUG=-all python3 matching2/tools/matching/build_msvc.py --output matching2/build/resumed_wave19_msvc_2026_10_01 --verify matching2/build/oracle/th10.exe --jobs 16
```

Then run the current audit's audit.py, annotate.py and verify.py followed by `matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_wave19_build.py`. Frozen family receipts and complete diagnostic bodies are hash-pinned by the companion evidence JSON. Render and sound diagnostic families refer to their frozen earlier source snapshots; the final current whole-build and complete selected-body audit supersede their historical main-tree guards. They receive no new recovery credit. The full decompilation goal remains active.
