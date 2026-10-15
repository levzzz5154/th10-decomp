#pragma once
// Opaque tags used by recovered C-linkage entry points below.
struct AnimationManager_00442F50;
struct CrtHeapBlock;
struct CxxUnregisterFrame_004630ce;
struct DecimalConversionRecord_00461841;
struct File;
struct FrameInfo;
struct FptostrRecord_00460D10;
struct LocaleInfo;
struct NameEntry;
struct RenderEntity;
struct HintCreateView;
struct Stream;
struct SchedulerTask;
struct ThreadData;
extern "C" void __cdecl CxxUnregisterExceptionObject_004630ce(
    CxxUnregisterFrame_004630ce* frame, int unwind);
#define VA_CxxUnregisterExceptionObject_004630ce 0x004630ce
extern "C" unsigned char* __stdcall Lzss_Compress_004359B0(
    const unsigned char* input, int input_size, int* output_size);
#define VA_Lzss_Compress_004359B0 0x004359b0
extern "C" int __fastcall Lzss_InsertString_00436000(
    int old_position, int position, int* best_position);
#define VA_Lzss_InsertString_00436000 0x00436000
extern "C" void __fastcall Lzss_RemoveNode_00436210(int node);
#define VA_Lzss_RemoveNode_00436210 0x00436210
struct MidiSequencer;
struct MidiTrack;
extern "C" void __stdcall ProcessMidiEvent_0043B110(
    MidiSequencer* sequencer, MidiTrack* track);
#define VA_ProcessMidiEvent_0043B110 0x0043b110
extern "C" unsigned char* __stdcall Lzss_Compress_004359B0(
    const unsigned char* input, int input_size, int* output_size);
#define VA_Lzss_Compress_004359B0 0x004359b0
extern "C" int __fastcall Lzss_InsertString_00436000(
    int old_position, int position, int* best_position);
#define VA_Lzss_InsertString_00436000 0x00436000
extern "C" void __fastcall Lzss_RemoveNode_00436210(int node);
#define VA_Lzss_RemoveNode_00436210 0x00436210
struct MidiSequencer;
struct MidiTrack;
extern "C" void __stdcall ProcessMidiEvent_0043B110(
    MidiSequencer* sequencer, MidiTrack* track);
#define VA_ProcessMidiEvent_0043B110 0x0043b110
extern "C" unsigned char* __stdcall Lzss_Compress_004359B0(
    const unsigned char* input, int input_size, int* output_size);
#define VA_Lzss_Compress_004359B0 0x004359b0
extern "C" int __fastcall Lzss_InsertString_00436000(
    int old_position, int position, int* best_position);
#define VA_Lzss_InsertString_00436000 0x00436000
extern "C" void __fastcall Lzss_RemoveNode_00436210(int node);
#define VA_Lzss_RemoveNode_00436210 0x00436210
struct MidiSequencer;
struct MidiTrack;
extern "C" void __stdcall ProcessMidiEvent_0043B110(
    MidiSequencer* sequencer, MidiTrack* track);
#define VA_ProcessMidiEvent_0043B110 0x0043b110
// Fixed retail anchors; the linker verifies every placed function.
extern "C" void __cdecl asm_1FileHandle_00435340();
#define VA_asm_1FileHandle_00435340 0x00435340
extern "C" void __cdecl asm_AddScaled_GameScore_00409d90();
#define VA_asm_AddScaled_GameScore_00409d90 0x00409d90
extern "C" void __cdecl asm_AddScaled_ScoreCounter_0041be80();
#define VA_asm_AddScaled_ScoreCounter_0041be80 0x0041be80
extern "C" void __cdecl asm_AdjustPointer_00462fc1();
#define VA_asm_AdjustPointer_00462fc1 0x00462fc1
extern "C" void __cdecl asm_Angle_NormalizeSum_0044bc10();
#define VA_asm_Angle_NormalizeSum_0044bc10 0x0044bc10
extern "C" void __cdecl asm_Angle_Normalize_0044bc70();
#define VA_asm_Angle_Normalize_0044bc70 0x0044bc70
extern "C" void __cdecl asm_Angle_Normalize_part_0044bcb0();
#define VA_asm_Angle_Normalize_part_0044bcb0 0x0044bcb0
extern "C" void __cdecl asm_AnimationColor_MultiplyChannel_004423c0();
#define VA_asm_AnimationColor_MultiplyChannel_004423c0 0x004423c0
extern "C" void __cdecl asm_AnimationManager_AppendQuadVertices_00442fe0();
#define VA_asm_AnimationManager_AppendQuadVertices_00442fe0 0x00442fe0
extern "C" void __cdecl asm_AnimationManager_ClearFlag_004495e0();
#define VA_asm_AnimationManager_ClearFlag_004495e0 0x004495e0
extern "C" void __cdecl asm_AnimationManager_ClearIndexedResources_00447f70();
#define VA_asm_AnimationManager_ClearIndexedResources_00447f70 0x00447f70
extern "C" void __cdecl asm_AnimationManager_ClearResourceSlot_004477d0();
#define VA_asm_AnimationManager_ClearResourceSlot_004477d0 0x004477d0
extern "C" void __cdecl asm_AnimationManager_CopyPositionRecord_00447940();
#define VA_asm_AnimationManager_CopyPositionRecord_00447940 0x00447940
extern "C" void __cdecl asm_AnimationManager_CreatePositionedPrimary_00448d50();
#define VA_asm_AnimationManager_CreatePositionedPrimary_00448d50 0x00448d50
extern "C" void __cdecl asm_AnimationManager_CreatePrimaryBack_00448d00();
#define VA_asm_AnimationManager_CreatePrimaryBack_00448d00 0x00448d00
extern "C" void __cdecl asm_AnimationManager_CreatePrimaryFront_00448e30();
#define VA_asm_AnimationManager_CreatePrimaryFront_00448e30 0x00448e30
extern "C" void __cdecl asm_AnimationManager_CreateSecondaryBack_00448f60();
#define VA_asm_AnimationManager_CreateSecondaryBack_00448f60 0x00448f60
extern "C" void __cdecl asm_AnimationManager_CreateSecondaryFront_00449090();
#define VA_asm_AnimationManager_CreateSecondaryFront_00449090 0x00449090
extern "C" void __cdecl asm_AnimationManager_FindChildByScriptIndex_004497d0();
#define VA_asm_AnimationManager_FindChildByScriptIndex_004497d0 0x004497d0
extern "C" void __cdecl asm_AnimationManager_Find_004491c0();
#define VA_asm_AnimationManager_Find_004491c0 0x004491c0
extern "C" void __cdecl asm_AnimationManager_FlushQuadBatch_00442f50();
#define VA_asm_AnimationManager_FlushQuadBatch_00442f50 0x00442f50
extern "C" void __cdecl asm_AnimationManager_MarkForRemovalAndClearHandle_00449630();
#define VA_asm_AnimationManager_MarkForRemovalAndClearHandle_00449630 0x00449630
extern "C" void __cdecl asm_AnimationManager_MarkResourceForRemoval_004493e0();
#define VA_asm_AnimationManager_MarkResourceForRemoval_004493e0 0x004493e0
extern "C" void __cdecl asm_AnimationManager_MarkResourceForRemoval_part_00449420();
#define VA_asm_AnimationManager_MarkResourceForRemoval_part_00449420 0x00449420
extern "C" void __cdecl asm_AnimationManager_QueueResource_0043dc90();
#define VA_asm_AnimationManager_QueueResource_0043dc90 0x0043dc90
extern "C" void __cdecl asm_AnimationManager_RegisterPrimaryBack_004489d0();
#define VA_asm_AnimationManager_RegisterPrimaryBack_004489d0 0x004489d0
extern "C" void __cdecl asm_AnimationManager_RegisterPrimaryFront_00448a50();
#define VA_asm_AnimationManager_RegisterPrimaryFront_00448a50 0x00448a50
extern "C" void __cdecl asm_AnimationManager_RegisterResource_0043e460();
#define VA_asm_AnimationManager_RegisterResource_0043e460 0x0043e460
extern "C" void __cdecl asm_AnimationManager_RegisterResource_part_0043e470();
#define VA_asm_AnimationManager_RegisterResource_part_0043e470 0x0043e470
extern "C" void __cdecl asm_AnimationManager_RegisterSecondaryBack_00448ac0();
#define VA_asm_AnimationManager_RegisterSecondaryBack_00448ac0 0x00448ac0
extern "C" void __cdecl asm_AnimationManager_RegisterSecondaryFront_00448b40();
#define VA_asm_AnimationManager_RegisterSecondaryFront_00448b40 0x00448b40
extern "C" void __cdecl asm_AnimationManager_RenderBucket_00448980();
#define VA_asm_AnimationManager_RenderBucket_00448980 0x00448980
extern "C" void __cdecl asm_AnimationManager_SelectSpriteFromCurrentResource_00449670();
#define VA_asm_AnimationManager_SelectSpriteFromCurrentResource_00449670 0x00449670
extern "C" void __cdecl asm_AnimationManager_SelectSpriteFromResource_004496a0();
#define VA_asm_AnimationManager_SelectSpriteFromResource_004496a0 0x004496a0
extern "C" void __cdecl asm_AnimationManager_SetFlagBit1_00449590();
#define VA_asm_AnimationManager_SetFlagBit1_00449590 0x00449590
extern "C" void __cdecl asm_AnimationManager_SetFlag_004492a0();
#define VA_asm_AnimationManager_SetFlag_004492a0 0x004492a0
extern "C" void __cdecl asm_AnimationManager_SetPosition_004492f0();
#define VA_asm_AnimationManager_SetPosition_004492f0 0x004492f0
extern "C" void __cdecl asm_AnimationManager_SetStopFrameAndRun_00449250();
#define VA_asm_AnimationManager_SetStopFrameAndRun_00449250 0x00449250
extern "C" void __cdecl asm_AnimationManager_SetStopFrameFromHandleRetail_00449470();
#define VA_asm_AnimationManager_SetStopFrameFromHandleRetail_00449470 0x00449470
extern "C" void __cdecl asm_AnimationManager_SetStopFrameFromHandleRetail_part_004494a0();
#define VA_asm_AnimationManager_SetStopFrameFromHandleRetail_part_004494a0 0x004494a0
extern "C" void __cdecl asm_AnimationManager_SetStopFrame_00449210();
#define VA_asm_AnimationManager_SetStopFrame_00449210 0x00449210
extern "C" void __cdecl asm_AnimationManager_SetTranslatedPosition_00449350();
#define VA_asm_AnimationManager_SetTranslatedPosition_00449350 0x00449350
extern "C" void __cdecl asm_AnimationManager_StopAtFrame2_0040c480();
#define VA_asm_AnimationManager_StopAtFrame2_0040c480 0x0040c480
extern "C" void __cdecl asm_AnimationManager_StopAtFrame3_0040c4d0();
#define VA_asm_AnimationManager_StopAtFrame3_0040c4d0 0x0040c4d0
extern "C" void __cdecl asm_AnimationManager_UpdatePrimary_00448860();
#define VA_asm_AnimationManager_UpdatePrimary_00448860 0x00448860
extern "C" void __cdecl asm_AnimationManager_UpdateSecondary_00448900();
#define VA_asm_AnimationManager_UpdateSecondary_00448900 0x00448900
extern "C" void __cdecl asm_AnimationManager_ValidateHandle_00449450();
#define VA_asm_AnimationManager_ValidateHandle_00449450 0x00449450
extern "C" void __cdecl asm_AnimationObject_ChangeScript_0043e8b0();
#define VA_asm_AnimationObject_ChangeScript_0043e8b0 0x0043e8b0
extern "C" void __cdecl asm_AnimationObject_ConfigureFromResource_0043e5a0();
#define VA_asm_AnimationObject_ConfigureFromResource_0043e5a0 0x0043e5a0
extern "C" void __cdecl asm_AnimationObject_LoadScriptPreservingState_0043e7e0();
#define VA_asm_AnimationObject_LoadScriptPreservingState_0043e7e0 0x0043e7e0
extern "C" void __cdecl asm_AnimationObject_LoadScript_0043e710();
#define VA_asm_AnimationObject_LoadScript_0043e710 0x0043e710
extern "C" void __cdecl asm_AnimationObject_ReadIntegerVariable_0043ec70();
#define VA_asm_AnimationObject_ReadIntegerVariable_0043ec70 0x0043ec70
extern "C" void __cdecl asm_AnimationObject_ResolveFloatVariable_0043ed00();
#define VA_asm_AnimationObject_ResolveFloatVariable_0043ed00 0x0043ed00
extern "C" void __cdecl asm_AnimationObject_ResolveIntegerVariable_0043eda0();
#define VA_asm_AnimationObject_ResolveIntegerVariable_0043eda0 0x0043eda0
extern "C" void __cdecl asm_AnimationSlot_ReleaseRetail_004136c0();
#define VA_asm_AnimationSlot_ReleaseRetail_004136c0 0x004136c0
extern "C" void __cdecl asm_AnimationTexture_Create_00447050();
#define VA_asm_AnimationTexture_Create_00447050 0x00447050
extern "C" void __cdecl asm_Animation_SetActiveCount_00413790();
#define VA_asm_Animation_SetActiveCount_00413790 0x00413790
extern "C" void __cdecl asm_Animation_SetActiveCount_part_004137d0();
#define VA_asm_Animation_SetActiveCount_part_004137d0 0x004137d0
extern "C" void __cdecl asm_AnmArchive_AdvanceScriptCursorRetail_004473c0();
#define VA_asm_AnmArchive_AdvanceScriptCursorRetail_004473c0 0x004473c0
extern "C" void __cdecl asm_AnmManager_SyncEntityRenderStateRetail_004425a0();
#define VA_asm_AnmManager_SyncEntityRenderStateRetail_004425a0 0x004425a0
extern "C" void __cdecl asm_AnmPending_ServiceRetail_00447700();
#define VA_asm_AnmPending_ServiceRetail_00447700 0x00447700
extern "C" void __cdecl asm_AnmTexture_CreateAndUploadRetail_00446f40();
#define VA_asm_AnmTexture_CreateAndUploadRetail_00446f40 0x00446f40
extern "C" void __cdecl asm_ArchiveCursor_Open_0044dbf0();
#define VA_asm_ArchiveCursor_Open_0044dbf0 0x0044dbf0
extern "C" void __cdecl asm_ArchiveCursor_ReadRetail_0044de10();
#define VA_asm_ArchiveCursor_ReadRetail_0044de10 0x0044de10
extern "C" void __cdecl asm_ArchiveCursor_SeekRetail_0044dd40();
#define VA_asm_ArchiveCursor_SeekRetail_0044dd40 0x0044dd40
extern "C" void __cdecl asm_ArrayUnwind_004525a1();
#define VA_asm_ArrayUnwind_004525a1 0x004525a1
extern "C" void __cdecl asm_AsciiManager_CreateRetail_0043c8b0();
#define VA_asm_AsciiManager_CreateRetail_0043c8b0 0x0043c8b0
extern "C" void __cdecl asm_Ascii_FormatShadowedRetail_00447ae0();
#define VA_asm_Ascii_FormatShadowedRetail_00447ae0 0x00447ae0
extern "C" void __cdecl asm_AssignRange_LegacyString_00438420();
#define VA_asm_AssignRange_LegacyString_00438420 0x00438420
extern "C" void __cdecl asm_AssignSubstring_LegacyString_00438260();
#define VA_asm_AssignSubstring_LegacyString_00438260 0x00438260
extern "C" void __cdecl asm_Assign_LegacyString_00438350();
#define VA_asm_Assign_LegacyString_00438350 0x00438350
extern "C" void __cdecl asm_Assign_LegacyString_part_00438360();
#define VA_asm_Assign_LegacyString_part_00438360 0x00438360
extern "C" void __cdecl asm_AtInterval_FrameCounterPair_00427c70();
#define VA_asm_AtInterval_FrameCounterPair_00427c70 0x00427c70
extern "C" void __cdecl asm_BossUi_ReleaseIndicatorsRetail_0040e5f0();
#define VA_asm_BossUi_ReleaseIndicatorsRetail_0040e5f0 0x0040e5f0
extern "C" void __cdecl asm_BuildCatchObject_00463399();
#define VA_asm_BuildCatchObject_00463399 0x00463399
extern "C" void __cdecl asm_BulletEntity_ClearResourceList_0040c6e0();
#define VA_asm_BulletEntity_ClearResourceList_0040c6e0 0x0040c6e0
extern "C" void __cdecl asm_BulletEntity_FindById_0040cf90();
#define VA_asm_BulletEntity_FindById_0040cf90 0x0040cf90
extern "C" void __cdecl asm_BulletEntity_MarkAnimationForRemoval_0040cea0();
#define VA_asm_BulletEntity_MarkAnimationForRemoval_0040cea0 0x0040cea0
extern "C" void __cdecl asm_BulletEntity_ReleaseResource_0040d680();
#define VA_asm_BulletEntity_ReleaseResource_0040d680 0x0040d680
extern "C" void __cdecl asm_BulletEntity_SetAnimationVector_0040cf60();
#define VA_asm_BulletEntity_SetAnimationVector_0040cf60 0x0040cf60
extern "C" void __cdecl asm_BulletManager_Create_0040af90();
#define VA_asm_BulletManager_Create_0040af90 0x0040af90
extern "C" void __cdecl asm_BulletManager_LoadScripts_0040ae70();
#define VA_asm_BulletManager_LoadScripts_0040ae70 0x0040ae70
extern "C" void __cdecl asm_BulletManager_Release_0040af00();
#define VA_asm_BulletManager_Release_0040af00 0x0040af00
extern "C" void __cdecl asm_BulletPool_ResetRetail_00405ed0();
#define VA_asm_BulletPool_ResetRetail_00405ed0 0x00405ed0
extern "C" void __cdecl asm_BulletSpawnParameters_Initialize_0040cf40();
#define VA_asm_BulletSpawnParameters_Initialize_0040cf40 0x0040cf40
extern "C" void __cdecl asm_CachedComSlot_ReleaseRetail_00421d20();
#define VA_asm_CachedComSlot_ReleaseRetail_00421d20 0x00421d20
extern "C" void __cdecl asm_CallCatchBlock2_00462a80();
#define VA_asm_CallCatchBlock2_00462a80 0x00462a80
extern "C" void __cdecl asm_CallCatchBlock_004631d5();
#define VA_asm_CallCatchBlock_004631d5 0x004631d5
extern "C" void __cdecl asm_CallCatchBlock_part_0046330f();
#define VA_asm_CallCatchBlock_part_0046330f 0x0046330f
extern "C" void __cdecl asm_CallMemberFunction0_00462706();
#define VA_asm_CallMemberFunction0_00462706 0x00462706
extern "C" void __cdecl asm_CallSETranslator_004627f8();
#define VA_asm_CallSETranslator_004627f8 0x004627f8
extern "C" void __cdecl asm_CallSettingFrame_12_00463a10();
#define VA_asm_CallSettingFrame_12_00463a10 0x00463a10
extern "C" void __cdecl asm_Camera_ApplyRetail_00421480();
#define VA_asm_Camera_ApplyRetail_00421480 0x00421480
extern "C" void __cdecl asm_CatchIt_0046363a();
#define VA_asm_CatchIt_0046363a 0x0046363a
extern "C" void __cdecl asm_ConfigureColorPlaybackState_00442220();
#define VA_asm_ConfigureColorPlaybackState_00442220 0x00442220
extern "C" void __cdecl asm_ConstructGameState_00402160();
#define VA_asm_ConstructGameState_00402160 0x00402160
extern "C" void __cdecl asm_CopyMan_0045d3bb();
#define VA_asm_CopyMan_0045d3bb 0x0045d3bb
extern "C" void __cdecl asm_CountPatternMatches_004088c0();
#define VA_asm_CountPatternMatches_004088c0 0x004088c0
extern "C" FrameInfo* __cdecl asm_CreateFrameInfo_004629eb(FrameInfo* frame, void* object);
#define VA_asm_CreateFrameInfo_004629eb 0x004629eb
extern "C" void __cdecl asm_CreateGameState_00402640();
#define VA_asm_CreateGameState_00402640 0x00402640
extern "C" void __cdecl asm_CreateGameThread_00401440();
#define VA_asm_CreateGameThread_00401440 0x00401440
extern "C" void __cdecl asm_CxxFrameHandler_0046276d();
#define VA_asm_CxxFrameHandler_0046276d 0x0046276d
extern "C" void __cdecl asm_CxxThrowException_8_00462afb();
#define VA_asm_CxxThrowException_8_00462afb 0x00462afb
extern "C" void __cdecl asm_D3DResourceList_ClearPending_00449a90();
#define VA_asm_D3DResourceList_ClearPending_00449a90 0x00449a90
extern "C" void __cdecl asm_D3DResourceList_ReleaseResources_00449e50();
#define VA_asm_D3DResourceList_ReleaseResources_00449e50 0x00449e50
extern "C" void __cdecl asm_D3DResourceManager_Destroy_00438880();
#define VA_asm_D3DResourceManager_Destroy_00438880 0x00438880
extern "C" void __cdecl asm_D3DResourceManager_Initialize_00449aa0();
#define VA_asm_D3DResourceManager_Initialize_00449aa0 0x00449aa0
extern "C" void __cdecl asm_D3DXCreateTextureFromFileInMemoryEx_004521ca();
#define VA_asm_D3DXCreateTextureFromFileInMemoryEx_004521ca 0x004521ca
extern "C" void __cdecl asm_D3DXCreateTexture_004521a0();
#define VA_asm_D3DXCreateTexture_004521a0 0x004521a0
extern "C" void __cdecl asm_D3DXLoadSurfaceFromFileInMemory_004521d0();
#define VA_asm_D3DXLoadSurfaceFromFileInMemory_004521d0 0x004521d0
extern "C" void __cdecl asm_D3DXLoadSurfaceFromMemory_004521a6();
#define VA_asm_D3DXLoadSurfaceFromMemory_004521a6 0x004521a6
extern "C" void __cdecl asm_D3DXLoadSurfaceFromSurface_004521d6();
#define VA_asm_D3DXLoadSurfaceFromSurface_004521d6 0x004521d6
extern "C" void __cdecl asm_D3DXMatrixLookAtLH_00452194();
#define VA_asm_D3DXMatrixLookAtLH_00452194 0x00452194
extern "C" void __cdecl asm_D3DXMatrixMultiply_004521b2();
#define VA_asm_D3DXMatrixMultiply_004521b2 0x004521b2
extern "C" void __cdecl asm_D3DXMatrixPerspectiveFovLH_0045219a();
#define VA_asm_D3DXMatrixPerspectiveFovLH_0045219a 0x0045219a
extern "C" void __cdecl asm_D3DXMatrixRotationX_004521ac();
#define VA_asm_D3DXMatrixRotationX_004521ac 0x004521ac
extern "C" void __cdecl asm_D3DXMatrixRotationY_004521b8();
#define VA_asm_D3DXMatrixRotationY_004521b8 0x004521b8
extern "C" void* __cdecl asm_D3DXMatrixRotationZ_004521be(void* out, float angle);
#define VA_asm_D3DXMatrixRotationZ_004521be 0x004521be
extern "C" void* __cdecl asm_D3DXMatrixTranslation_00452182(void* out, float x, float y, float z);
#define VA_asm_D3DXMatrixTranslation_00452182 0x00452182
extern "C" void __cdecl asm_D3DXVec3Normalize_0045217c();
#define VA_asm_D3DXVec3Normalize_0045217c 0x0045217c
extern "C" void __cdecl asm_D3DXVec3ProjectArray_00452188();
#define VA_asm_D3DXVec3ProjectArray_00452188 0x00452188
extern "C" void __cdecl asm_D3DXVec3Project_0045218e();
#define VA_asm_D3DXVec3Project_0045218e 0x0045218e
extern "C" void __cdecl asm_D3DXVec3Transform_004521c4();
#define VA_asm_D3DXVec3Transform_004521c4 0x004521c4
extern "C" void __cdecl asm_DatArchive_Close_00434d10();
#define VA_asm_DatArchive_Close_00434d10 0x00434d10
extern "C" void __cdecl asm_DatArchive_FindEntry_00434f30();
#define VA_asm_DatArchive_FindEntry_00434f30 0x00434f30
extern "C" void __cdecl asm_DatArchive_FindSize_00434ef0();
#define VA_asm_DatArchive_FindSize_00434ef0 0x00434ef0
extern "C" void __cdecl asm_DatArchive_LoadIndex_00434f70();
#define VA_asm_DatArchive_LoadIndex_00434f70 0x00434f70
extern "C" void __cdecl asm_DatArchive_Open_00434c30();
#define VA_asm_DatArchive_Open_00434c30 0x00434c30
extern "C" void __cdecl asm_DatArchive_Read_00434dd0();
#define VA_asm_DatArchive_Read_00434dd0 0x00434dd0
extern "C" void __cdecl asm_DatArchive_Read_part_00434e60();
#define VA_asm_DatArchive_Read_part_00434e60 0x00434e60
extern "C" void __cdecl asm_DatArchive_Reset_00434c20();
#define VA_asm_DatArchive_Reset_00434c20 0x00434c20
extern "C" void __cdecl asm_DecompressDatLzss_00435dc0();
#define VA_asm_DecompressDatLzss_00435dc0 0x00435dc0
extern "C" void __cdecl asm_DecryptDatBuffer_0044b0d0();
#define VA_asm_DecryptDatBuffer_0044b0d0 0x0044b0d0
extern "C" void __cdecl asm_DecryptDatBuffer_part_0044b1c0();
#define VA_asm_DecryptDatBuffer_part_0044b1c0 0x0044b1c0
extern "C" void __cdecl asm_DestroyEntityList_00438a30();
#define VA_asm_DestroyEntityList_00438a30 0x00438a30
extern "C" void __cdecl asm_DestroyGameState_00402440();
#define VA_asm_DestroyGameState_00402440 0x00402440
extern "C" void __cdecl asm_DestroyGameThread_00401260();
#define VA_asm_DestroyGameThread_00401260 0x00401260
extern "C" void __cdecl asm_DestructExceptionObject_00462f7c();
#define VA_asm_DestructExceptionObject_00462f7c 0x00462f7c
extern "C" void __cdecl asm_Direct3DCreate9_00452176();
#define VA_asm_Direct3DCreate9_00452176 0x00452176
extern "C" void __cdecl asm_DirectInput8Create_0045071e();
#define VA_asm_DirectInput8Create_0045071e 0x0045071e
extern "C" void __cdecl asm_ECL_FindVariable_00450160();
#define VA_asm_ECL_FindVariable_00450160 0x00450160
extern "C" void __cdecl asm_ECL_FindVariable_part_00450170();
#define VA_asm_ECL_FindVariable_part_00450170 0x00450170
extern "C" void __cdecl asm_ECL_PopScratchValue_004506d0();
#define VA_asm_ECL_PopScratchValue_004506d0 0x004506d0
extern "C" void __cdecl asm_ECL_PushScratchValue_00450690();
#define VA_asm_ECL_PushScratchValue_00450690 0x00450690
extern "C" void __cdecl asm_ECL_ResetVariableBindings_00450190();
#define VA_asm_ECL_ResetVariableBindings_00450190 0x00450190
extern "C" void __cdecl asm_ECL_ResolveFloatDestination_00450070();
#define VA_asm_ECL_ResolveFloatDestination_00450070 0x00450070
extern "C" void __cdecl asm_ECL_ResolveFloatOperand_0044fe40();
#define VA_asm_ECL_ResolveFloatOperand_0044fe40 0x0044fe40
extern "C" void __cdecl asm_ECL_ResolveFloatValue_0044ff80();
#define VA_asm_ECL_ResolveFloatValue_0044ff80 0x0044ff80
extern "C" void __cdecl asm_ECL_ResolveIntDestination_00412a10();
#define VA_asm_ECL_ResolveIntDestination_00412a10 0x00412a10
extern "C" void __cdecl asm_ECL_ResolveIntFromEntity_00412a00();
#define VA_asm_ECL_ResolveIntFromEntity_00412a00 0x00412a00
extern "C" void __cdecl asm_ECL_ResolveIntOperand_0044fdb0();
#define VA_asm_ECL_ResolveIntOperand_0044fdb0 0x0044fdb0
extern "C" void __cdecl asm_ECL_ResolveIntValue_0044ff00();
#define VA_asm_ECL_ResolveIntValue_0044ff00 0x0044ff00
extern "C" void __cdecl asm_ECL_ResolveVariableValue_00450030();
#define VA_asm_ECL_ResolveVariableValue_00450030 0x00450030
extern "C" void __cdecl asm_ECL_SetPolarVector_004501b0();
#define VA_asm_ECL_SetPolarVector_004501b0 0x004501b0
extern "C" void __cdecl asm_EclVm_SpawnChild_004500d0();
#define VA_asm_EclVm_SpawnChild_004500d0 0x004500d0
extern "C" void __cdecl asm_EclVm_StartChildRetail_0044df70();
#define VA_asm_EclVm_StartChildRetail_0044df70 0x0044df70
extern "C" void __cdecl asm_EclVm_TickChildren_0044fd10();
#define VA_asm_EclVm_TickChildren_0044fd10 0x0044fd10
extern "C" void __cdecl asm_Ecl_ForwardFloat_00412aa0();
#define VA_asm_Ecl_ForwardFloat_00412aa0 0x00412aa0
extern "C" void __cdecl asm_Ecl_SetResourceSlot_00412720();
#define VA_asm_Ecl_SetResourceSlot_00412720 0x00412720
extern "C" void __cdecl asm_EffectIndicatorPool_AllocateRetail_00427b50();
#define VA_asm_EffectIndicatorPool_AllocateRetail_00427b50 0x00427b50
extern "C" void __cdecl asm_EffectManagerRuntime_InitializeRetail_0042b4d0();
#define VA_asm_EffectManagerRuntime_InitializeRetail_0042b4d0 0x0042b4d0
extern "C" void __cdecl asm_EffectManager_InitializePoolsRetail_0042ae60();
#define VA_asm_EffectManager_InitializePoolsRetail_0042ae60 0x0042ae60
extern "C" void __cdecl asm_EffectManager_ResetAndPublishRetail_0042b430();
#define VA_asm_EffectManager_ResetAndPublishRetail_0042b430 0x0042b430
extern "C" void __cdecl asm_EffectPool_OutsideViewport_00428d70();
#define VA_asm_EffectPool_OutsideViewport_00428d70 0x00428d70
extern "C" void __cdecl asm_EffectPool_UpdateDrops_0042b6f0();
#define VA_asm_EffectPool_UpdateDrops_0042b6f0 0x0042b6f0
extern "C" void __cdecl asm_EmbeddedTimer_Reset_004050d0();
#define VA_asm_EmbeddedTimer_Reset_004050d0 0x004050d0
extern "C" void __cdecl asm_EmbeddedTimer_SetCountdownRetail_0042a930();
#define VA_asm_EmbeddedTimer_SetCountdownRetail_0042a930 0x0042a930
extern "C" void __cdecl asm_EncryptDatBuffer_0044b220();
#define VA_asm_EncryptDatBuffer_0044b220 0x0044b220
extern "C" void __cdecl asm_EnemyGrid_ScanCellsRetail_004073e0();
#define VA_asm_EnemyGrid_ScanCellsRetail_004073e0 0x004073e0
extern "C" void __cdecl asm_EnemyManager_CreateRetail_0040d6b0();
#define VA_asm_EnemyManager_CreateRetail_0040d6b0 0x0040d6b0
extern "C" void __cdecl Loading_Create();
#define VA_Loading_Create 0x0041fd00
extern "C" void __cdecl asm_Enemy_DeathSweepRetail_0040e6a0();
#define VA_asm_Enemy_DeathSweepRetail_0040e6a0 0x0040e6a0
extern "C" void __cdecl asm_Enemy_SweepPendingDropsRetail_0041ba50();
#define VA_asm_Enemy_SweepPendingDropsRetail_0041ba50 0x0041ba50
extern "C" void __cdecl asm_Enemy_TimerSweepRetail_0040d750();
#define VA_asm_Enemy_TimerSweepRetail_0040d750 0x0040d750
extern "C" void __cdecl asm_EntityScript_NextRandomModulo_0043cb80();
#define VA_asm_EntityScript_NextRandomModulo_0043cb80 0x0043cb80
extern "C" void __cdecl asm_Entity_AngleFromPoint_00426660();
#define VA_asm_Entity_AngleFromPoint_00426660 0x00426660
extern "C" void __cdecl asm_Entity_AngleToPoint_00426610();
#define VA_asm_Entity_AngleToPoint_00426610 0x00426610
extern "C" void __cdecl asm_Entity_ClearAnims_0040cc70();
#define VA_asm_Entity_ClearAnims_0040cc70 0x0040cc70
extern "C" void __cdecl asm_Entity_Constructor_00402050();
#define VA_asm_Entity_Constructor_00402050 0x00402050
extern "C" void __cdecl asm_Entity_Destructor_00401ff0();
#define VA_asm_Entity_Destructor_00401ff0 0x00401ff0
extern "C" void __cdecl asm_Entity_PointWithinBoundsInclusive_004061d0();
#define VA_asm_Entity_PointWithinBoundsInclusive_004061d0 0x004061d0
extern "C" void __cdecl asm_Entity_PointWithinBounds_00406160();
#define VA_asm_Entity_PointWithinBounds_00406160 0x00406160
extern "C" void __cdecl asm_Erase_LegacyString_00438510();
#define VA_asm_Erase_LegacyString_00438510 0x00438510
extern "C" void __cdecl asm_FF_MSGBANNER_0045909f();
#define VA_asm_FF_MSGBANNER_0045909f 0x0045909f
extern "C" void __cdecl asm_FID_conflict__CallMemberFunction1_0046270d();
#define VA_asm_FID_conflict__CallMemberFunction1_0046270d 0x0046270d
extern "C" void __cdecl asm_FID_conflict__CallMemberFunction1_00462714();
#define VA_asm_FID_conflict__CallMemberFunction1_00462714 0x00462714
extern "C" int __cdecl asm_FID_conflict___ld12tod_0045d5ce(const void* source, void* destination);
#define VA_asm_FID_conflict___ld12tod_0045d5ce 0x0045d5ce
extern "C" int __cdecl asm_FID_conflict___ld12tod_0045d5e4(const void* source, void* destination);
#define VA_asm_FID_conflict___ld12tod_0045d5e4 0x0045d5e4
extern "C" unsigned int __cdecl asm_FID_conflict___set_errno_from_matherr_0045e86c(int value);
#define VA_asm_FID_conflict___set_errno_from_matherr_0045e86c 0x0045e86c
extern "C" unsigned int __cdecl asm_FID_conflict___time32_00452b71(unsigned int* output);
#define VA_asm_FID_conflict___time32_00452b71 0x00452b71
extern "C" void __cdecl asm_FID_conflict__ungetc_0045e204();
#define VA_asm_FID_conflict__ungetc_0045e204 0x0045e204
extern "C" void __cdecl asm_FID_conflict_runtime_error_00462327();
#define VA_asm_FID_conflict_runtime_error_00462327 0x00462327
extern "C" void __cdecl asm_FID_conflict_runtime_error_00462468();
#define VA_asm_FID_conflict_runtime_error_00462468 0x00462468
extern "C" void __cdecl asm_FID_conflict_x64toa_20_004606df();
#define VA_asm_FID_conflict_x64toa_20_004606df 0x004606df
extern "C" void __cdecl asm_FUN_004015c0_004015c0();
#define VA_asm_FUN_004015c0_004015c0 0x004015c0
extern "C" void __cdecl asm_FUN_00401760_00401760();
#define VA_asm_FUN_00401760_00401760 0x00401760
extern "C" void __cdecl asm_FUN_00401a50_00401a50();
#define VA_asm_FUN_00401a50_00401a50 0x00401a50
extern "C" void __cdecl asm_FUN_00402720_00402720();
#define VA_asm_FUN_00402720_00402720 0x00402720
extern "C" void __cdecl asm_FUN_00402850_00402850();
#define VA_asm_FUN_00402850_00402850 0x00402850
extern "C" void __cdecl asm_FUN_00402ca0_00402ca0();
#define VA_asm_FUN_00402ca0_00402ca0 0x00402ca0
extern "C" void __cdecl asm_FUN_00403090_00403090();
#define VA_asm_FUN_00403090_00403090 0x00403090
extern "C" void __cdecl asm_FUN_00403850_00403850();
#define VA_asm_FUN_00403850_00403850 0x00403850
extern "C" void __cdecl asm_FUN_00403990_00403990();
#define VA_asm_FUN_00403990_00403990 0x00403990
extern "C" void __cdecl asm_FUN_00403990_part_004039b0();
#define VA_asm_FUN_00403990_part_004039b0 0x004039b0
extern "C" void __cdecl asm_FUN_00403a30_00403a30();
#define VA_asm_FUN_00403a30_00403a30 0x00403a30
extern "C" void __cdecl asm_FUN_00403a30_part_00403a90();
#define VA_asm_FUN_00403a30_part_00403a90 0x00403a90
extern "C" void __cdecl asm_FUN_00403a30_part_00403b00();
#define VA_asm_FUN_00403a30_part_00403b00 0x00403b00
extern "C" void __cdecl asm_FUN_00403c80_00403c80();
#define VA_asm_FUN_00403c80_00403c80 0x00403c80
extern "C" void __cdecl asm_FUN_00404450_00404450();
#define VA_asm_FUN_00404450_00404450 0x00404450
extern "C" void __cdecl asm_FUN_00404450_part_004044c0();
#define VA_asm_FUN_00404450_part_004044c0 0x004044c0
extern "C" void __cdecl asm_FUN_00404530_00404530();
#define VA_asm_FUN_00404530_00404530 0x00404530
extern "C" void __cdecl asm_FUN_00404610_00404610();
#define VA_asm_FUN_00404610_00404610 0x00404610
extern "C" void __cdecl asm_FUN_004049a0_004049a0();
#define VA_asm_FUN_004049a0_004049a0 0x004049a0
extern "C" void __cdecl asm_FUN_00404f30_00404f30();
#define VA_asm_FUN_00404f30_00404f30 0x00404f30
extern "C" void __cdecl asm_FUN_00405300_00405300();
#define VA_asm_FUN_00405300_00405300 0x00405300
extern "C" void __cdecl asm_FUN_004054b0_004054b0();
#define VA_asm_FUN_004054b0_004054b0 0x004054b0
extern "C" void __cdecl asm_FUN_00405730_00405730();
#define VA_asm_FUN_00405730_00405730 0x00405730
extern "C" void __cdecl asm_FUN_00405e20_00405e20();
#define VA_asm_FUN_00405e20_00405e20 0x00405e20
extern "C" void __cdecl asm_FUN_00406060_00406060();
#define VA_asm_FUN_00406060_00406060 0x00406060
extern "C" void __cdecl asm_FUN_00406140_00406140();
#define VA_asm_FUN_00406140_00406140 0x00406140
extern "C" void __cdecl asm_FUN_00406240_00406240();
#define VA_asm_FUN_00406240_00406240 0x00406240
extern "C" void __cdecl asm_FUN_004065c0_004065c0();
#define VA_asm_FUN_004065c0_004065c0 0x004065c0
extern "C" void __cdecl asm_FUN_004066e0_004066e0();
#define VA_asm_FUN_004066e0_004066e0 0x004066e0
extern "C" void __cdecl asm_FUN_004067d0_004067d0();
#define VA_asm_FUN_004067d0_004067d0 0x004067d0
extern "C" void __cdecl asm_FUN_004067d0_part_004067f0();
#define VA_asm_FUN_004067d0_part_004067f0 0x004067f0
extern "C" void __cdecl asm_FUN_00406d90_00406d90();
#define VA_asm_FUN_00406d90_00406d90 0x00406d90
extern "C" void __cdecl asm_FUN_00407560_00407560();
#define VA_asm_FUN_00407560_00407560 0x00407560
extern "C" void __cdecl asm_FUN_00407780_00407780();
#define VA_asm_FUN_00407780_00407780 0x00407780
extern "C" void __cdecl asm_FUN_004078e0_004078e0();
#define VA_asm_FUN_004078e0_004078e0 0x004078e0
extern "C" void __cdecl asm_FUN_00407a30_00407a30();
#define VA_asm_FUN_00407a30_00407a30 0x00407a30
extern "C" void __cdecl asm_FUN_00407be0_00407be0();
#define VA_asm_FUN_00407be0_00407be0 0x00407be0
extern "C" void __cdecl asm_FUN_00407ef0_00407ef0();
#define VA_asm_FUN_00407ef0_00407ef0 0x00407ef0
extern "C" void __cdecl asm_FUN_00408100_00408100();
#define VA_asm_FUN_00408100_00408100 0x00408100
extern "C" void __cdecl asm_FUN_00408210_00408210();
#define VA_asm_FUN_00408210_00408210 0x00408210
extern "C" void __cdecl asm_FUN_00408210_part_004082e0();
#define VA_asm_FUN_00408210_part_004082e0 0x004082e0
extern "C" void __cdecl asm_FUN_004089c0_004089c0();
#define VA_asm_FUN_004089c0_004089c0 0x004089c0
extern "C" void __cdecl asm_FUN_00408af0_00408af0();
#define VA_asm_FUN_00408af0_00408af0 0x00408af0
extern "C" void __cdecl asm_FUN_00408d60_00408d60();
#define VA_asm_FUN_00408d60_00408d60 0x00408d60
extern "C" void __cdecl asm_FUN_00408d60_part_00408ee0();
#define VA_asm_FUN_00408d60_part_00408ee0 0x00408ee0
extern "C" void __cdecl asm_FUN_00408d60_part_00408f60();
#define VA_asm_FUN_00408d60_part_00408f60 0x00408f60
extern "C" void __cdecl asm_FUN_00409280_00409280();
#define VA_asm_FUN_00409280_00409280 0x00409280
extern "C" void __cdecl asm_FUN_00409280_part_004093d0();
#define VA_asm_FUN_00409280_part_004093d0 0x004093d0
extern "C" void __cdecl asm_FUN_00409280_part_00409810();
#define VA_asm_FUN_00409280_part_00409810 0x00409810
extern "C" void __cdecl asm_FUN_00409c00_00409c00();
#define VA_asm_FUN_00409c00_00409c00 0x00409c00
extern "C" void __cdecl asm_FUN_00409e50_00409e50();
#define VA_asm_FUN_00409e50_00409e50 0x00409e50
extern "C" void __cdecl asm_FUN_00409eb0_00409eb0();
#define VA_asm_FUN_00409eb0_00409eb0 0x00409eb0
extern "C" void __cdecl asm_FUN_00409f90_00409f90();
#define VA_asm_FUN_00409f90_00409f90 0x00409f90
extern "C" void __cdecl asm_FUN_0040a010_0040a010();
#define VA_asm_FUN_0040a010_0040a010 0x0040a010
extern "C" void __cdecl asm_FUN_0040a040_0040a040();
#define VA_asm_FUN_0040a040_0040a040 0x0040a040
extern "C" void __cdecl EclView_RegisterTasks();
#define VA_asm_FUN_0040a130_0040a130 0x0040a130
extern "C" void __cdecl asm_FUN_0040a1a0_0040a1a0();
#define VA_asm_FUN_0040a1a0_0040a1a0 0x0040a1a0
extern "C" void __cdecl asm_FUN_0040a350_0040a350();
#define VA_asm_FUN_0040a350_0040a350 0x0040a350
extern "C" void __cdecl asm_FUN_0040a450_0040a450();
#define VA_asm_FUN_0040a450_0040a450 0x0040a450
extern "C" void __cdecl asm_FUN_0040a940_0040a940();
#define VA_asm_FUN_0040a940_0040a940 0x0040a940
extern "C" void __cdecl asm_FUN_0040ad20_0040ad20();
#define VA_asm_FUN_0040ad20_0040ad20 0x0040ad20
extern "C" void __cdecl asm_FUN_0040b3a0_0040b3a0();
#define VA_asm_FUN_0040b3a0_0040b3a0 0x0040b3a0
extern "C" void __cdecl asm_FUN_0040b3a0_part_0040b430();
#define VA_asm_FUN_0040b3a0_part_0040b430 0x0040b430
extern "C" void __cdecl asm_FUN_0040b480_0040b480();
#define VA_asm_FUN_0040b480_0040b480 0x0040b480
extern "C" void __cdecl asm_FUN_0040b560_0040b560();
#define VA_asm_FUN_0040b560_0040b560 0x0040b560
extern "C" void __cdecl asm_FUN_0040b7b0_0040b7b0();
#define VA_asm_FUN_0040b7b0_0040b7b0 0x0040b7b0
extern "C" void __cdecl asm_FUN_0040ba90_0040ba90();
#define VA_asm_FUN_0040ba90_0040ba90 0x0040ba90
extern "C" void __cdecl asm_FUN_0040bd80_0040bd80();
#define VA_asm_FUN_0040bd80_0040bd80 0x0040bd80
extern "C" void __cdecl asm_FUN_0040bd80_part_0040bde0();
#define VA_asm_FUN_0040bd80_part_0040bde0 0x0040bde0
extern "C" void __cdecl asm_FUN_0040c540_0040c540();
#define VA_asm_FUN_0040c540_0040c540 0x0040c540
extern "C" void __cdecl asm_FUN_0040c730_0040c730();
#define VA_asm_FUN_0040c730_0040c730 0x0040c730
extern "C" void __cdecl asm_FUN_0040c9d0_0040c9d0();
#define VA_asm_FUN_0040c9d0_0040c9d0 0x0040c9d0
extern "C" void __cdecl asm_FUN_0040cfb0_0040cfb0();
#define VA_asm_FUN_0040cfb0_0040cfb0 0x0040cfb0
extern "C" void __cdecl asm_FUN_0040d280_0040d280();
#define VA_asm_FUN_0040d280_0040d280 0x0040d280
extern "C" void __cdecl asm_FUN_0040d510_0040d510();
#define VA_asm_FUN_0040d510_0040d510 0x0040d510
extern "C" void __cdecl asm_FUN_0040d530_0040d530();
#define VA_asm_FUN_0040d530_0040d530 0x0040d530
extern "C" void __cdecl asm_FUN_0040d730_0040d730();
#define VA_asm_FUN_0040d730_0040d730 0x0040d730
extern "C" void __cdecl asm_FUN_0040d830_0040d830();
#define VA_asm_FUN_0040d830_0040d830 0x0040d830
extern "C" void __cdecl asm_FUN_0040dae0_0040dae0();
#define VA_asm_FUN_0040dae0_0040dae0 0x0040dae0
extern "C" void __cdecl asm_FUN_0040dc80_0040dc80();
#define VA_asm_FUN_0040dc80_0040dc80 0x0040dc80
extern "C" void __cdecl asm_FUN_0040e770_0040e770();
#define VA_asm_FUN_0040e770_0040e770 0x0040e770
extern "C" void __cdecl asm_FUN_004127a0_004127a0();
#define VA_asm_FUN_004127a0_004127a0 0x004127a0
extern "C" void __cdecl asm_FUN_00412ac0_00412ac0();
#define VA_asm_FUN_00412ac0_00412ac0 0x00412ac0
extern "C" void __cdecl asm_FUN_00412ff0_00412ff0();
#define VA_asm_FUN_00412ff0_00412ff0 0x00412ff0
extern "C" void __cdecl asm_FUN_00413350_00413350();
#define VA_asm_FUN_00413350_00413350 0x00413350
extern "C" void __cdecl asm_FUN_004135d0_004135d0();
#define VA_asm_FUN_004135d0_004135d0 0x004135d0
extern "C" void __cdecl asm_FUN_00413810_00413810();
#define VA_asm_FUN_00413810_00413810 0x00413810
extern "C" void __cdecl asm_FUN_00413a20_00413a20();
#define VA_asm_FUN_00413a20_00413a20 0x00413a20
extern "C" void __cdecl asm_FUN_00413bc0_00413bc0();
#define VA_asm_FUN_00413bc0_00413bc0 0x00413bc0
extern "C" void __cdecl asm_FUN_00413bc0_part_00413cb0();
#define VA_asm_FUN_00413bc0_part_00413cb0 0x00413cb0
extern "C" void __cdecl asm_FUN_00413bc0_part_00413d40();
#define VA_asm_FUN_00413bc0_part_00413d40 0x00413d40
extern "C" void __cdecl asm_FUN_00413bc0_part_00414230();
#define VA_asm_FUN_00413bc0_part_00414230 0x00414230
extern "C" void __cdecl asm_FUN_00414370_00414370();
#define VA_asm_FUN_00414370_00414370 0x00414370
extern "C" void __cdecl asm_FUN_00414370_part_00414520();
#define VA_asm_FUN_00414370_part_00414520 0x00414520
extern "C" void __cdecl asm_FUN_004145f0_004145f0();
#define VA_asm_FUN_004145f0_004145f0 0x004145f0
extern "C" void __cdecl asm_FUN_004145f0_part_004146c0();
#define VA_asm_FUN_004145f0_part_004146c0 0x004146c0
extern "C" void __cdecl asm_FUN_004145f0_part_00414720();
#define VA_asm_FUN_004145f0_part_00414720 0x00414720
extern "C" void __cdecl asm_FUN_004148e0_004148e0();
#define VA_asm_FUN_004148e0_004148e0 0x004148e0
extern "C" void __cdecl asm_FUN_00414900_00414900();
#define VA_asm_FUN_00414900_00414900 0x00414900
extern "C" void __cdecl asm_FUN_00414900_part_004149f0();
#define VA_asm_FUN_00414900_part_004149f0 0x004149f0
extern "C" void __cdecl asm_FUN_00414900_part_00414c90();
#define VA_asm_FUN_00414900_part_00414c90 0x00414c90
extern "C" void __cdecl asm_FUN_00414900_part_00414d50();
#define VA_asm_FUN_00414900_part_00414d50 0x00414d50
extern "C" void __cdecl asm_FUN_00414900_part_00415060();
#define VA_asm_FUN_00414900_part_00415060 0x00415060
extern "C" void __cdecl asm_FUN_00415800_00415800();
#define VA_asm_FUN_00415800_00415800 0x00415800
extern "C" void __cdecl asm_FUN_00415800_part_00415820();
#define VA_asm_FUN_00415800_part_00415820 0x00415820
extern "C" void __cdecl asm_FUN_00415800_part_004158a0();
#define VA_asm_FUN_00415800_part_004158a0 0x004158a0
extern "C" void __cdecl asm_FUN_00415800_part_004159d0();
#define VA_asm_FUN_00415800_part_004159d0 0x004159d0
extern "C" void __cdecl asm_FUN_00415800_part_00415ab0();
#define VA_asm_FUN_00415800_part_00415ab0 0x00415ab0
extern "C" void __cdecl asm_FUN_00415b00_00415b00();
#define VA_asm_FUN_00415b00_00415b00 0x00415b00
extern "C" void __cdecl asm_FUN_00415b00_part_00415d50();
#define VA_asm_FUN_00415b00_part_00415d50 0x00415d50
extern "C" void __cdecl asm_FUN_00415db0_00415db0();
#define VA_asm_FUN_00415db0_00415db0 0x00415db0
extern "C" void __cdecl asm_FUN_00415e90_00415e90();
#define VA_asm_FUN_00415e90_00415e90 0x00415e90
extern "C" void __cdecl asm_FUN_00417040_00417040();
#define VA_asm_FUN_00417040_00417040 0x00417040
extern "C" void __cdecl asm_FUN_004172e0_004172e0();
#define VA_asm_FUN_004172e0_004172e0 0x004172e0
extern "C" void __cdecl asm_FUN_004175e0_004175e0();
#define VA_asm_FUN_004175e0_004175e0 0x004175e0
extern "C" void __cdecl asm_FUN_00417870_00417870();
#define VA_asm_FUN_00417870_00417870 0x00417870
extern "C" void __cdecl asm_FUN_00417c80_00417c80();
#define VA_asm_FUN_00417c80_00417c80 0x00417c80
extern "C" void __cdecl asm_FUN_00418190_00418190();
#define VA_asm_FUN_00418190_00418190 0x00418190
extern "C" void __cdecl asm_FUN_00418ee0_00418ee0();
#define VA_asm_FUN_00418ee0_00418ee0 0x00418ee0
extern "C" void __cdecl asm_FUN_00419120_00419120();
#define VA_asm_FUN_00419120_00419120 0x00419120
extern "C" void __cdecl asm_FUN_00419120_part_004191e0();
#define VA_asm_FUN_00419120_part_004191e0 0x004191e0
extern "C" void __cdecl asm_FUN_00419650_00419650();
#define VA_asm_FUN_00419650_00419650 0x00419650
extern "C" void __cdecl asm_FUN_00419960_00419960();
#define VA_asm_FUN_00419960_00419960 0x00419960
extern "C" void __cdecl asm_FUN_00419960_part_00419bd0();
#define VA_asm_FUN_00419960_part_00419bd0 0x00419bd0
extern "C" void __cdecl asm_FUN_00419f40_00419f40();
#define VA_asm_FUN_00419f40_00419f40 0x00419f40
extern "C" void __cdecl asm_FUN_0041a200_0041a200();
#define VA_asm_FUN_0041a200_0041a200 0x0041a200
extern "C" void __cdecl asm_FUN_0041ab70_0041ab70();
#define VA_asm_FUN_0041ab70_0041ab70 0x0041ab70
extern "C" void __cdecl asm_FUN_0041adf0_0041adf0();
#define VA_asm_FUN_0041adf0_0041adf0 0x0041adf0
extern "C" void __cdecl asm_FUN_0041aed0_0041aed0();
#define VA_asm_FUN_0041aed0_0041aed0 0x0041aed0
extern "C" void __cdecl asm_FUN_0041afb0_0041afb0();
#define VA_asm_FUN_0041afb0_0041afb0 0x0041afb0
extern "C" void __cdecl asm_FUN_0041afd0_0041afd0();
#define VA_asm_FUN_0041afd0_0041afd0 0x0041afd0
extern "C" void __cdecl asm_FUN_0041afd0_part_0041b010();
#define VA_asm_FUN_0041afd0_part_0041b010 0x0041b010
extern "C" void __cdecl asm_FUN_0041b8e0_0041b8e0();
#define VA_asm_FUN_0041b8e0_0041b8e0 0x0041b8e0
extern "C" void __cdecl asm_FUN_0041b8e0_part_0041b900();
#define VA_asm_FUN_0041b8e0_part_0041b900 0x0041b900
extern "C" void __cdecl asm_FUN_0041bb00_0041bb00();
#define VA_asm_FUN_0041bb00_0041bb00 0x0041bb00
extern "C" void __cdecl asm_FUN_0041beb0_0041beb0();
#define VA_asm_FUN_0041beb0_0041beb0 0x0041beb0
extern "C" void __cdecl asm_FUN_0041c330_0041c330();
#define VA_asm_FUN_0041c330_0041c330 0x0041c330
extern "C" void __cdecl asm_FUN_0041c510_0041c510();
#define VA_asm_FUN_0041c510_0041c510 0x0041c510
extern "C" void __cdecl asm_FUN_0041c680_0041c680();
#define VA_asm_FUN_0041c680_0041c680 0x0041c680
extern "C" void __cdecl asm_FUN_0041c850_0041c850();
#define VA_asm_FUN_0041c850_0041c850 0x0041c850
extern "C" void __cdecl asm_FUN_0041c850_part_0041c860();
#define VA_asm_FUN_0041c850_part_0041c860 0x0041c860
extern "C" void __cdecl asm_FUN_0041d880_part_0041dc70();
#define VA_asm_FUN_0041d880_part_0041dc70 0x0041dc70
extern "C" void __cdecl asm_FUN_0041d880_part_0041dca0();
#define VA_asm_FUN_0041d880_part_0041dca0 0x0041dca0
extern "C" void __cdecl asm_FUN_0041dd80_part_0041e150();
#define VA_asm_FUN_0041dd80_part_0041e150 0x0041e150
extern "C" void __cdecl asm_FUN_0041dd80_part_0041e180();
#define VA_asm_FUN_0041dd80_part_0041e180 0x0041e180
extern "C" void __cdecl asm_FUN_0041eb00_part_0041ee50();
#define VA_asm_FUN_0041eb00_part_0041ee50 0x0041ee50
extern "C" void __cdecl asm_FUN_0041eb00_part_0041ee80();
#define VA_asm_FUN_0041eb00_part_0041ee80 0x0041ee80
extern "C" void __cdecl asm_FUN_0041efa0_part_0041f090();
#define VA_asm_FUN_0041efa0_part_0041f090 0x0041f090
extern "C" void __cdecl asm_FUN_0041efa0_part_0041f240();
#define VA_asm_FUN_0041efa0_part_0041f240 0x0041f240
extern "C" void __cdecl asm_FUN_0041efa0_part_0041f2c0();
#define VA_asm_FUN_0041efa0_part_0041f2c0 0x0041f2c0
extern "C" void __cdecl asm_FUN_0041efa0_part_0041f2f0();
#define VA_asm_FUN_0041efa0_part_0041f2f0 0x0041f2f0
extern "C" void __cdecl Loading_Release();
#define VA_Loading_Release 0x0041fb50
extern "C" void __cdecl asm_FUN_0041fdd0_0041fdd0();
#define VA_asm_FUN_0041fdd0_0041fdd0 0x0041fdd0
extern "C" void __cdecl asm_FUN_0041ff60_0041ff60();
#define VA_asm_FUN_0041ff60_0041ff60 0x0041ff60
extern "C" void __cdecl asm_FUN_00420100_00420100();
#define VA_asm_FUN_00420100_00420100 0x00420100
extern "C" void __cdecl asm_FUN_00420270_00420270();
#define VA_asm_FUN_00420270_00420270 0x00420270
extern "C" void __cdecl asm_FUN_00420470_00420470();
#define VA_asm_FUN_00420470_00420470 0x00420470
extern "C" void __cdecl asm_FUN_00420670_00420670();
#define VA_asm_FUN_00420670_00420670 0x00420670
extern "C" void __cdecl asm_FUN_00420870_00420870();
#define VA_asm_FUN_00420870_00420870 0x00420870
extern "C" void __cdecl asm_FUN_00420cd0_00420cd0();
#define VA_asm_FUN_00420cd0_00420cd0 0x00420cd0
extern "C" void __cdecl asm_FUN_00420ea0_00420ea0();
#define VA_asm_FUN_00420ea0_00420ea0 0x00420ea0
extern "C" void __cdecl asm_FUN_00421070_00421070();
#define VA_asm_FUN_00421070_00421070 0x00421070
extern "C" void __cdecl asm_FUN_00421070_part_004210c0();
#define VA_asm_FUN_00421070_part_004210c0 0x004210c0
extern "C" void __cdecl asm_FUN_00421070_part_00421100();
#define VA_asm_FUN_00421070_part_00421100 0x00421100
extern "C" void __cdecl asm_FUN_00421070_part_00421140();
#define VA_asm_FUN_00421070_part_00421140 0x00421140
extern "C" void __cdecl asm_FUN_00421300_00421300();
#define VA_asm_FUN_00421300_00421300 0x00421300
extern "C" void __cdecl asm_FUN_00421300_part_00421350();
#define VA_asm_FUN_00421300_part_00421350 0x00421350
extern "C" void __cdecl asm_FUN_00421300_part_00421390();
#define VA_asm_FUN_00421300_part_00421390 0x00421390
extern "C" void __cdecl asm_FUN_00421300_part_004213d0();
#define VA_asm_FUN_00421300_part_004213d0 0x004213d0
extern "C" void __cdecl asm_FUN_004215a0_004215a0();
#define VA_asm_FUN_004215a0_004215a0 0x004215a0
extern "C" void __cdecl asm_FUN_004216f0_004216f0();
#define VA_asm_FUN_004216f0_004216f0 0x004216f0
extern "C" void __cdecl asm_FUN_004218d0_004218d0();
#define VA_asm_FUN_004218d0_004218d0 0x004218d0
extern "C" void __cdecl asm_FUN_00421e00_00421e00();
#define VA_asm_FUN_00421e00_00421e00 0x00421e00
extern "C" void __cdecl asm_FUN_00421fa0_00421fa0();
#define VA_asm_FUN_00421fa0_00421fa0 0x00421fa0
extern "C" void __cdecl asm_FUN_00421fa0_part_00421fc0();
#define VA_asm_FUN_00421fa0_part_00421fc0 0x00421fc0
extern "C" void __cdecl asm_FUN_00422220_00422220();
#define VA_asm_FUN_00422220_00422220 0x00422220
extern "C" void __cdecl asm_FUN_004223f0_004223f0();
#define VA_asm_FUN_004223f0_004223f0 0x004223f0
extern "C" void __cdecl asm_FUN_004224c0_004224c0();
#define VA_asm_FUN_004224c0_004224c0 0x004224c0
extern "C" void __cdecl asm_FUN_00422660_00422660();
#define VA_asm_FUN_00422660_00422660 0x00422660
extern "C" void __cdecl asm_FUN_00422660_part_00422920();
#define VA_asm_FUN_00422660_part_00422920 0x00422920
extern "C" void __cdecl asm_FUN_00422ab0_00422ab0();
#define VA_asm_FUN_00422ab0_00422ab0 0x00422ab0
extern "C" void __cdecl asm_FUN_00422c80_00422c80();
#define VA_asm_FUN_00422c80_00422c80 0x00422c80
extern "C" void __cdecl asm_FUN_004231d0_004231d0();
#define VA_asm_FUN_004231d0_004231d0 0x004231d0
extern "C" void __cdecl asm_FUN_00423370_00423370();
#define VA_asm_FUN_00423370_00423370 0x00423370
extern "C" void __cdecl asm_FUN_00423570_00423570();
#define VA_asm_FUN_00423570_00423570 0x00423570
extern "C" void __cdecl asm_FUN_00423570_part_00423680();
#define VA_asm_FUN_00423570_part_00423680 0x00423680
extern "C" void __cdecl asm_FUN_004236f0_004236f0();
#define VA_asm_FUN_004236f0_004236f0 0x004236f0
extern "C" void __cdecl asm_FUN_00424480_00424480();
#define VA_asm_FUN_00424480_00424480 0x00424480
extern "C" void __cdecl asm_FUN_004246c0_004246c0();
#define VA_asm_FUN_004246c0_004246c0 0x004246c0
extern "C" void __cdecl asm_FUN_004247f0_004247f0();
#define VA_asm_FUN_004247f0_004247f0 0x004247f0
extern "C" void __cdecl asm_FUN_004247f0_part_00424940();
#define VA_asm_FUN_004247f0_part_00424940 0x00424940
extern "C" void __cdecl asm_FUN_00424d90_00424d90();
#define VA_asm_FUN_00424d90_00424d90 0x00424d90
extern "C" void __cdecl asm_FUN_00424ed0_00424ed0();
#define VA_asm_FUN_00424ed0_00424ed0 0x00424ed0
extern "C" void __cdecl asm_FUN_00425090_00425090();
#define VA_asm_FUN_00425090_00425090 0x00425090
extern "C" void __cdecl asm_FUN_004250b0_004250b0();
#define VA_asm_FUN_004250b0_004250b0 0x004250b0
extern "C" void __cdecl asm_FUN_004250b0_part_00425590();
#define VA_asm_FUN_004250b0_part_00425590 0x00425590
extern "C" void __cdecl asm_FUN_00425730_00425730();
#define VA_asm_FUN_00425730_00425730 0x00425730
extern "C" void __cdecl asm_FUN_00425730_part_004257d0();
#define VA_asm_FUN_00425730_part_004257d0 0x004257d0
extern "C" void __cdecl asm_FUN_00425730_part_00425810();
#define VA_asm_FUN_00425730_part_00425810 0x00425810
extern "C" void __cdecl asm_FUN_00425730_part_00425860();
#define VA_asm_FUN_00425730_part_00425860 0x00425860
extern "C" void __cdecl asm_FUN_00425730_part_00425a40();
#define VA_asm_FUN_00425730_part_00425a40 0x00425a40
extern "C" void __cdecl asm_FUN_00425730_part_00425b40();
#define VA_asm_FUN_00425730_part_00425b40 0x00425b40
extern "C" void __cdecl asm_FUN_00426360_00426360();
#define VA_asm_FUN_00426360_00426360 0x00426360
extern "C" void __cdecl asm_FUN_004266b0_004266b0();
#define VA_asm_FUN_004266b0_004266b0 0x004266b0
extern "C" void __cdecl asm_FUN_004267f0_004267f0();
#define VA_asm_FUN_004267f0_004267f0 0x004267f0
extern "C" void __cdecl asm_FUN_004269d0_004269d0();
#define VA_asm_FUN_004269d0_004269d0 0x004269d0
extern "C" void __cdecl asm_FUN_00426cf0_00426cf0();
#define VA_asm_FUN_00426cf0_00426cf0 0x00426cf0
extern "C" void __cdecl asm_FUN_00426cf0_part_00426da0();
#define VA_asm_FUN_00426cf0_part_00426da0 0x00426da0
extern "C" void __cdecl asm_FUN_00426f70_00426f70();
#define VA_asm_FUN_00426f70_00426f70 0x00426f70
extern "C" void __cdecl asm_FUN_00426f70_part_00427020();
#define VA_asm_FUN_00426f70_part_00427020 0x00427020
extern "C" void __cdecl asm_FUN_00426f70_part_004271a0();
#define VA_asm_FUN_00426f70_part_004271a0 0x004271a0
extern "C" void __cdecl asm_FUN_00426f70_part_004278e0();
#define VA_asm_FUN_00426f70_part_004278e0 0x004278e0
extern "C" void __cdecl asm_FUN_00427960_00427960();
#define VA_asm_FUN_00427960_00427960 0x00427960
extern "C" void __cdecl asm_FUN_00427960_part_00427a10();
#define VA_asm_FUN_00427960_part_00427a10 0x00427a10
extern "C" void __cdecl asm_FUN_00428280_00428280();
#define VA_asm_FUN_00428280_00428280 0x00428280
extern "C" void __cdecl asm_FUN_00428280_part_004282b0();
#define VA_asm_FUN_00428280_part_004282b0 0x004282b0
extern "C" void __cdecl asm_FUN_00428630_00428630();
#define VA_asm_FUN_00428630_00428630 0x00428630
extern "C" void __cdecl asm_FUN_00428ce0_00428ce0();
#define VA_asm_FUN_00428ce0_00428ce0 0x00428ce0
extern "C" void __cdecl asm_FUN_00428e10_00428e10();
#define VA_asm_FUN_00428e10_00428e10 0x00428e10
extern "C" void __cdecl asm_FUN_00428f60_00428f60();
#define VA_asm_FUN_00428f60_00428f60 0x00428f60
extern "C" void __cdecl asm_FUN_004294a0_004294a0();
#define VA_asm_FUN_004294a0_004294a0 0x004294a0
extern "C" void __cdecl asm_FUN_00429610_00429610();
#define VA_asm_FUN_00429610_00429610 0x00429610
extern "C" void __cdecl asm_FUN_004297d0_004297d0();
#define VA_asm_FUN_004297d0_004297d0 0x004297d0
extern "C" void __cdecl asm_FUN_00429a70_00429a70();
#define VA_asm_FUN_00429a70_00429a70 0x00429a70
extern "C" void __cdecl asm_FUN_00429b60_00429b60();
#define VA_asm_FUN_00429b60_00429b60 0x00429b60
extern "C" void __cdecl asm_FUN_0042a200_0042a200();
#define VA_asm_FUN_0042a200_0042a200 0x0042a200
extern "C" void __cdecl asm_FUN_0042a200_part_0042a330();
#define VA_asm_FUN_0042a200_part_0042a330 0x0042a330
extern "C" void __cdecl asm_FUN_0042a450_0042a450();
#define VA_asm_FUN_0042a450_0042a450 0x0042a450
extern "C" void __cdecl asm_FUN_0042a450_part_0042a610();
#define VA_asm_FUN_0042a450_part_0042a610 0x0042a610
extern "C" void __cdecl asm_FUN_0042a6a0_0042a6a0();
#define VA_asm_FUN_0042a6a0_0042a6a0 0x0042a6a0
extern "C" void __cdecl asm_FUN_0042ab20_0042ab20();
#define VA_asm_FUN_0042ab20_0042ab20 0x0042ab20
extern "C" void __cdecl asm_FUN_0042af20_0042af20();
#define VA_asm_FUN_0042af20_0042af20 0x0042af20
extern "C" void __cdecl asm_FUN_0042b030_0042b030();
#define VA_asm_FUN_0042b030_0042b030 0x0042b030
extern "C" void __cdecl asm_FUN_0042b1e0_0042b1e0();
#define VA_asm_FUN_0042b1e0_0042b1e0 0x0042b1e0
extern "C" void __cdecl asm_FUN_0042b570_0042b570();
#define VA_asm_FUN_0042b570_0042b570 0x0042b570
extern "C" void __cdecl asm_FUN_0042b6d0_0042b6d0();
#define VA_asm_FUN_0042b6d0_0042b6d0 0x0042b6d0
extern "C" void __cdecl asm_FUN_0042b780_0042b780();
#define VA_asm_FUN_0042b780_0042b780 0x0042b780
extern "C" void __cdecl asm_FUN_0042b9c0_0042b9c0();
#define VA_asm_FUN_0042b9c0_0042b9c0 0x0042b9c0
extern "C" void __cdecl asm_FUN_0042b9c0_part_0042b9f0();
#define VA_asm_FUN_0042b9c0_part_0042b9f0 0x0042b9f0
extern "C" void __cdecl asm_FUN_0042bad0_0042bad0();
#define VA_asm_FUN_0042bad0_0042bad0 0x0042bad0
extern "C" void __cdecl asm_FUN_0042bb30_0042bb30();
#define VA_asm_FUN_0042bb30_0042bb30 0x0042bb30
extern "C" void __cdecl asm_FUN_0042bbd0_0042bbd0();
#define VA_asm_FUN_0042bbd0_0042bbd0 0x0042bbd0
extern "C" void __cdecl asm_FUN_0042bc30_0042bc30();
#define VA_asm_FUN_0042bc30_0042bc30 0x0042bc30
extern "C" void __cdecl asm_FUN_0042be20_0042be20();
#define VA_asm_FUN_0042be20_0042be20 0x0042be20
extern "C" void __cdecl asm_FUN_0042bfc0_0042bfc0();
#define VA_asm_FUN_0042bfc0_0042bfc0 0x0042bfc0
extern "C" void __cdecl asm_FUN_0042c360_0042c360();
#define VA_asm_FUN_0042c360_0042c360 0x0042c360
extern "C" void __cdecl asm_FUN_0042c770_0042c770();
#define VA_asm_FUN_0042c770_0042c770 0x0042c770
extern "C" void __cdecl asm_FUN_0042c920_0042c920();
#define VA_asm_FUN_0042c920_0042c920 0x0042c920
extern "C" void __cdecl asm_FUN_0042c9f0_part_0042ca40();
#define VA_asm_FUN_0042c9f0_part_0042ca40 0x0042ca40
extern "C" void __cdecl asm_FUN_0042cb60_0042cb60();
#define VA_asm_FUN_0042cb60_0042cb60 0x0042cb60
extern "C" void __cdecl asm_FUN_0042cdf0_0042cdf0();
#define VA_asm_FUN_0042cdf0_0042cdf0 0x0042cdf0
extern "C" void __cdecl asm_FUN_0042d260_0042d260();
#define VA_asm_FUN_0042d260_0042d260 0x0042d260
extern "C" void __cdecl asm_FUN_0042d300_0042d300();
#define VA_asm_FUN_0042d300_0042d300 0x0042d300
extern "C" void __cdecl asm_FUN_0042d420_0042d420();
#define VA_asm_FUN_0042d420_0042d420 0x0042d420
extern "C" void __cdecl asm_FUN_0042d920_0042d920();
#define VA_asm_FUN_0042d920_0042d920 0x0042d920
extern "C" void __cdecl asm_FUN_0042d920_part_0042da30();
#define VA_asm_FUN_0042d920_part_0042da30 0x0042da30
extern "C" void __cdecl asm_FUN_0042d920_part_0042dae0();
#define VA_asm_FUN_0042d920_part_0042dae0 0x0042dae0
extern "C" void __cdecl asm_FUN_0042d920_part_0042ddd0();
#define VA_asm_FUN_0042d920_part_0042ddd0 0x0042ddd0
extern "C" void __cdecl asm_FUN_0042d920_part_0042de20();
#define VA_asm_FUN_0042d920_part_0042de20 0x0042de20
extern "C" void __cdecl asm_FUN_0042d920_part_0042de70();
#define VA_asm_FUN_0042d920_part_0042de70 0x0042de70
extern "C" void __cdecl asm_FUN_0042d920_part_0042dec0();
#define VA_asm_FUN_0042d920_part_0042dec0 0x0042dec0
extern "C" void __cdecl asm_FUN_0042d920_part_0042e1e0();
#define VA_asm_FUN_0042d920_part_0042e1e0 0x0042e1e0
extern "C" void __cdecl asm_FUN_0042d920_part_0042e460();
#define VA_asm_FUN_0042d920_part_0042e460 0x0042e460
extern "C" void __cdecl asm_FUN_0042e5a0_0042e5a0();
#define VA_asm_FUN_0042e5a0_0042e5a0 0x0042e5a0
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042e650();
#define VA_asm_FUN_0042e5a0_part_0042e650 0x0042e650
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042e740();
#define VA_asm_FUN_0042e5a0_part_0042e740 0x0042e740
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042ebe0();
#define VA_asm_FUN_0042e5a0_part_0042ebe0 0x0042ebe0
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042ec40();
#define VA_asm_FUN_0042e5a0_part_0042ec40 0x0042ec40
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042ecf0();
#define VA_asm_FUN_0042e5a0_part_0042ecf0 0x0042ecf0
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042ede0();
#define VA_asm_FUN_0042e5a0_part_0042ede0 0x0042ede0
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042ee40();
#define VA_asm_FUN_0042e5a0_part_0042ee40 0x0042ee40
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042ef40();
#define VA_asm_FUN_0042e5a0_part_0042ef40 0x0042ef40
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042efa0();
#define VA_asm_FUN_0042e5a0_part_0042efa0 0x0042efa0
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f050();
#define VA_asm_FUN_0042e5a0_part_0042f050 0x0042f050
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f110();
#define VA_asm_FUN_0042e5a0_part_0042f110 0x0042f110
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f170();
#define VA_asm_FUN_0042e5a0_part_0042f170 0x0042f170
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f260();
#define VA_asm_FUN_0042e5a0_part_0042f260 0x0042f260
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f2c0();
#define VA_asm_FUN_0042e5a0_part_0042f2c0 0x0042f2c0
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f370();
#define VA_asm_FUN_0042e5a0_part_0042f370 0x0042f370
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f3d0();
#define VA_asm_FUN_0042e5a0_part_0042f3d0 0x0042f3d0
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f430();
#define VA_asm_FUN_0042e5a0_part_0042f430 0x0042f430
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f490();
#define VA_asm_FUN_0042e5a0_part_0042f490 0x0042f490
extern "C" void __cdecl asm_FUN_0042e5a0_part_0042f4f0();
#define VA_asm_FUN_0042e5a0_part_0042f4f0 0x0042f4f0
extern "C" void __cdecl asm_FUN_0042f540_0042f540();
#define VA_asm_FUN_0042f540_0042f540 0x0042f540
extern "C" void __cdecl asm_FUN_0042f8b0_0042f8b0();
#define VA_asm_FUN_0042f8b0_0042f8b0 0x0042f8b0
extern "C" void __cdecl asm_FUN_0042f8b0_part_0042f960();
#define VA_asm_FUN_0042f8b0_part_0042f960 0x0042f960
extern "C" void __cdecl asm_FUN_0042f8b0_part_004300d0();
#define VA_asm_FUN_0042f8b0_part_004300d0 0x004300d0
extern "C" void __cdecl asm_FUN_00430320_00430320();
#define VA_asm_FUN_00430320_00430320 0x00430320
extern "C" void __cdecl asm_FUN_004306a0_004306a0();
#define VA_asm_FUN_004306a0_004306a0 0x004306a0
extern "C" void __cdecl asm_FUN_00430a60_00430a60();
#define VA_asm_FUN_00430a60_00430a60 0x00430a60
extern "C" void __cdecl asm_FUN_00430ff0_00430ff0();
#define VA_asm_FUN_00430ff0_00430ff0 0x00430ff0
extern "C" void __cdecl asm_FUN_00431410_00431410();
#define VA_asm_FUN_00431410_00431410 0x00431410
extern "C" void __cdecl asm_FUN_004315c0_004315c0();
#define VA_asm_FUN_004315c0_004315c0 0x004315c0
extern "C" void __cdecl asm_FUN_004315c0_part_004316f0();
#define VA_asm_FUN_004315c0_part_004316f0 0x004316f0
extern "C" void __cdecl asm_FUN_004315c0_part_004318b0();
#define VA_asm_FUN_004315c0_part_004318b0 0x004318b0
extern "C" void __cdecl asm_FUN_00431ba0_00431ba0();
#define VA_asm_FUN_00431ba0_00431ba0 0x00431ba0
extern "C" void __cdecl asm_FUN_00431ee0_00431ee0();
#define VA_asm_FUN_00431ee0_00431ee0 0x00431ee0
extern "C" void __cdecl asm_FUN_00431ee0_part_004323e0();
#define VA_asm_FUN_00431ee0_part_004323e0 0x004323e0
extern "C" void __cdecl asm_FUN_00431ee0_part_00432490();
#define VA_asm_FUN_00431ee0_part_00432490 0x00432490
extern "C" void __cdecl asm_FUN_00432690_00432690();
#define VA_asm_FUN_00432690_00432690 0x00432690
extern "C" void __cdecl asm_FUN_00432690_part_00432720();
#define VA_asm_FUN_00432690_part_00432720 0x00432720
extern "C" void __cdecl asm_FUN_00432690_part_00432990();
#define VA_asm_FUN_00432690_part_00432990 0x00432990
extern "C" void __cdecl asm_FUN_004329f0_004329f0();
#define VA_asm_FUN_004329f0_004329f0 0x004329f0
extern "C" void __cdecl asm_FUN_00432cb0_00432cb0();
#define VA_asm_FUN_00432cb0_00432cb0 0x00432cb0
extern "C" void __cdecl asm_FUN_00433230_00433230();
#define VA_asm_FUN_00433230_00433230 0x00433230
extern "C" void __cdecl asm_FUN_00433230_part_004333e0();
#define VA_asm_FUN_00433230_part_004333e0 0x004333e0
extern "C" void __cdecl asm_FUN_00433570_00433570();
#define VA_asm_FUN_00433570_00433570 0x00433570
extern "C" void __cdecl asm_FUN_00433570_part_004335f0();
#define VA_asm_FUN_00433570_part_004335f0 0x004335f0
extern "C" void __cdecl asm_FUN_00433b30_00433b30();
#define VA_asm_FUN_00433b30_00433b30 0x00433b30
extern "C" void __cdecl asm_FUN_00433b30_part_00433d10();
#define VA_asm_FUN_00433b30_part_00433d10 0x00433d10
extern "C" void __cdecl asm_FUN_00433ef0_00433ef0();
#define VA_asm_FUN_00433ef0_00433ef0 0x00433ef0
extern "C" void __cdecl asm_FUN_00433ef0_part_00434090();
#define VA_asm_FUN_00433ef0_part_00434090 0x00434090
extern "C" void __cdecl asm_FUN_004350d0_004350d0();
#define VA_asm_FUN_004350d0_004350d0 0x004350d0
extern "C" void __cdecl asm_FUN_004356f0_004356f0();
#define VA_asm_FUN_004356f0_004356f0 0x004356f0
extern "C" void __cdecl asm_FUN_004356f0_part_00435730();
#define VA_asm_FUN_004356f0_part_00435730 0x00435730
extern "C" void __cdecl asm_FUN_00435800_00435800();
#define VA_asm_FUN_00435800_00435800 0x00435800
extern "C" void __cdecl asm_FUN_004359b0_004359b0();
#define VA_asm_FUN_004359b0_004359b0 0x004359b0
extern "C" void __cdecl asm_FUN_004359b0_part_00435b30();
#define VA_asm_FUN_004359b0_part_00435b30 0x00435b30
extern "C" void __cdecl asm_FUN_00436000_00436000();
#define VA_asm_FUN_00436000_00436000 0x00436000
extern "C" void __cdecl asm_FUN_00436000_part_00436020();
#define VA_asm_FUN_00436000_part_00436020 0x00436020
extern "C" void __cdecl asm_FUN_00436890_00436890();
#define VA_asm_FUN_00436890_00436890 0x00436890
extern "C" void __cdecl asm_FUN_00436af0_00436af0();
#define VA_asm_FUN_00436af0_00436af0 0x00436af0
extern "C" void __cdecl asm_FUN_00436ca0_00436ca0();
#define VA_asm_FUN_00436ca0_00436ca0 0x00436ca0
extern "C" void __cdecl asm_FUN_00436da0_00436da0();
#define VA_asm_FUN_00436da0_00436da0 0x00436da0
extern "C" void __cdecl asm_FUN_00436da0_part_00436fe0();
#define VA_asm_FUN_00436da0_part_00436fe0 0x00436fe0
extern "C" void __cdecl asm_FUN_00437160_00437160();
#define VA_asm_FUN_00437160_00437160 0x00437160
extern "C" void __cdecl asm_FUN_00437380_00437380();
#define VA_asm_FUN_00437380_00437380 0x00437380
extern "C" void __cdecl asm_FUN_00437a00_00437a00();
#define VA_asm_FUN_00437a00_00437a00 0x00437a00
extern "C" void __cdecl asm_FUN_00437db0_00437db0();
#define VA_asm_FUN_00437db0_00437db0 0x00437db0
extern "C" void __cdecl asm_FUN_00437fe0_00437fe0();
#define VA_asm_FUN_00437fe0_00437fe0 0x00437fe0
extern "C" void __cdecl asm_FUN_0043874c_0043874c();
#define VA_asm_FUN_0043874c_0043874c 0x0043874c
extern "C" void __cdecl asm_FUN_00438a60_00438a60();
#define VA_asm_FUN_00438a60_00438a60 0x00438a60
extern "C" void __cdecl asm_FUN_004391f0_004391f0();
#define VA_asm_FUN_004391f0_004391f0 0x004391f0
extern "C" void __cdecl asm_FUN_00439390_00439390();
#define VA_asm_FUN_00439390_00439390 0x00439390
extern "C" void __cdecl asm_FUN_00439390_part_004393d0();
#define VA_asm_FUN_00439390_part_004393d0 0x004393d0
extern "C" void __cdecl asm_FUN_00439540_00439540();
#define VA_asm_FUN_00439540_00439540 0x00439540
extern "C" void __cdecl asm_FUN_00439730_00439730();
#define VA_asm_FUN_00439730_00439730 0x00439730
extern "C" void __cdecl asm_FUN_00439890_00439890();
#define VA_asm_FUN_00439890_00439890 0x00439890
extern "C" void __cdecl asm_FUN_00439d20_00439d20();
#define VA_asm_FUN_00439d20_00439d20 0x00439d20
extern "C" void __cdecl asm_FUN_00439ff0_00439ff0();
#define VA_asm_FUN_00439ff0_00439ff0 0x00439ff0
extern "C" void __cdecl asm_FUN_00439ff0_part_0043a120();
#define VA_asm_FUN_00439ff0_part_0043a120 0x0043a120
extern "C" void __cdecl asm_FUN_0043a1c0_0043a1c0();
#define VA_asm_FUN_0043a1c0_0043a1c0 0x0043a1c0
extern "C" void __cdecl asm_FUN_0043a290_0043a290();
#define VA_asm_FUN_0043a290_0043a290 0x0043a290
extern "C" void __cdecl asm_FUN_0043a730_0043a730();
#define VA_asm_FUN_0043a730_0043a730 0x0043a730
extern "C" void __cdecl asm_FUN_0043a910_0043a910();
#define VA_asm_FUN_0043a910_0043a910 0x0043a910
extern "C" void __cdecl asm_FUN_0043a9b0_0043a9b0();
#define VA_asm_FUN_0043a9b0_0043a9b0 0x0043a9b0
extern "C" void __cdecl asm_FUN_0043aa60_0043aa60();
#define VA_asm_FUN_0043aa60_0043aa60 0x0043aa60
extern "C" void __cdecl asm_FUN_0043aad0_0043aad0();
#define VA_asm_FUN_0043aad0_0043aad0 0x0043aad0
extern "C" void __cdecl asm_FUN_0043ace0_0043ace0();
#define VA_asm_FUN_0043ace0_0043ace0 0x0043ace0
extern "C" void __cdecl asm_FUN_0043ae20_0043ae20();
#define VA_asm_FUN_0043ae20_0043ae20 0x0043ae20
extern "C" void __cdecl asm_FUN_0043aeb0_0043aeb0();
#define VA_asm_FUN_0043aeb0_0043aeb0 0x0043aeb0
extern "C" void __cdecl asm_FUN_0043af30_part_0043b030();
#define VA_asm_FUN_0043af30_part_0043b030 0x0043b030
extern "C" void __cdecl asm_FUN_0043b110_0043b110();
#define VA_asm_FUN_0043b110_0043b110 0x0043b110
extern "C" void __cdecl asm_FUN_0043b7a0_0043b7a0();
#define VA_asm_FUN_0043b7a0_0043b7a0 0x0043b7a0
extern "C" void __cdecl asm_FUN_0043b8d0_0043b8d0();
#define VA_asm_FUN_0043b8d0_0043b8d0 0x0043b8d0
extern "C" void __cdecl asm_FUN_0043bda0_0043bda0();
#define VA_asm_FUN_0043bda0_0043bda0 0x0043bda0
extern "C" void __cdecl asm_FUN_0043c970_0043c970();
#define VA_asm_FUN_0043c970_0043c970 0x0043c970
extern "C" void __cdecl asm_FUN_0043cd30_0043cd30();
#define VA_asm_FUN_0043cd30_0043cd30 0x0043cd30
extern "C" void __cdecl asm_FUN_0043cd30_part_0043cf60();
#define VA_asm_FUN_0043cd30_part_0043cf60 0x0043cf60
extern "C" void __cdecl asm_FUN_0043d120_0043d120();
#define VA_asm_FUN_0043d120_0043d120 0x0043d120
extern "C" void __cdecl asm_FUN_0043d390_0043d390();
#define VA_asm_FUN_0043d390_0043d390 0x0043d390
extern "C" void __cdecl asm_FUN_0043d690_0043d690();
#define VA_asm_FUN_0043d690_0043d690 0x0043d690
extern "C" void __cdecl asm_FUN_0043d7d0_0043d7d0();
#define VA_asm_FUN_0043d7d0_0043d7d0 0x0043d7d0
extern "C" void __cdecl asm_FUN_0043d950_0043d950();
#define VA_asm_FUN_0043d950_0043d950 0x0043d950
extern "C" void __cdecl asm_FUN_0043db60_0043db60();
#define VA_asm_FUN_0043db60_0043db60 0x0043db60
extern "C" void __cdecl asm_FUN_0043db60_part_0043dbe0();
#define VA_asm_FUN_0043db60_part_0043dbe0 0x0043dbe0
extern "C" void __cdecl asm_FUN_0043dd10_0043dd10();
#define VA_asm_FUN_0043dd10_0043dd10 0x0043dd10
extern "C" void __cdecl asm_FUN_0043ddf0_0043ddf0();
#define VA_asm_FUN_0043ddf0_0043ddf0 0x0043ddf0
extern "C" void __cdecl asm_FUN_0043ddf0_part_0043de30();
#define VA_asm_FUN_0043ddf0_part_0043de30 0x0043de30
extern "C" void __cdecl asm_FUN_0043e9d0_part_0043ea60();
#define VA_asm_FUN_0043e9d0_part_0043ea60 0x0043ea60
extern "C" void __cdecl asm_FUN_0043eac0_0043eac0();
#define VA_asm_FUN_0043eac0_0043eac0 0x0043eac0
extern "C" void __cdecl asm_FUN_0043ee30_0043ee30();
#define VA_asm_FUN_0043ee30_0043ee30 0x0043ee30
extern "C" void __cdecl asm_FUN_0043ee30_part_004411d0();
#define VA_asm_FUN_0043ee30_part_004411d0 0x004411d0
extern "C" void __cdecl asm_FUN_00441600_00441600();
#define VA_asm_FUN_00441600_00441600 0x00441600
extern "C" void __cdecl asm_FUN_00441950_00441950();
#define VA_asm_FUN_00441950_00441950 0x00441950
extern "C" void __cdecl asm_FUN_00441ad0_00441ad0();
#define VA_asm_FUN_00441ad0_00441ad0 0x00441ad0
extern "C" void __cdecl asm_FUN_00442050_00442050();
#define VA_asm_FUN_00442050_00442050 0x00442050
extern "C" void __cdecl asm_FUN_004423e0_004423e0();
#define VA_asm_FUN_004423e0_004423e0 0x004423e0
extern "C" void __cdecl asm_FUN_00442670_00442670();
#define VA_asm_FUN_00442670_00442670 0x00442670
extern "C" void __cdecl asm_FUN_00442ad0_00442ad0();
#define VA_asm_FUN_00442ad0_00442ad0 0x00442ad0
extern "C" void __cdecl asm_FUN_00443080_00443080();
#define VA_asm_FUN_00443080_00443080 0x00443080
extern "C" void __cdecl asm_FUN_00443290_00443290();
#define VA_asm_FUN_00443290_00443290 0x00443290
extern "C" void __cdecl asm_FUN_004436c0_004436c0();
#define VA_asm_FUN_004436c0_004436c0 0x004436c0
extern "C" void __cdecl asm_FUN_00443910_00443910();
#define VA_asm_FUN_00443910_00443910 0x00443910
extern "C" void __cdecl asm_FUN_00443b60_00443b60();
#define VA_asm_FUN_00443b60_00443b60 0x00443b60
extern "C" void __cdecl asm_FUN_00443f80_00443f80();
#define VA_asm_FUN_00443f80_00443f80 0x00443f80
extern "C" void __cdecl asm_FUN_00443fb0_00443fb0();
#define VA_asm_FUN_00443fb0_00443fb0 0x00443fb0
extern "C" void __cdecl asm_FUN_00444240_00444240();
#define VA_asm_FUN_00444240_00444240 0x00444240
extern "C" void __cdecl asm_FUN_00444580_00444580();
#define VA_asm_FUN_00444580_00444580 0x00444580
extern "C" void __cdecl asm_FUN_004445c0_004445c0();
#define VA_asm_FUN_004445c0_004445c0 0x004445c0
extern "C" void __cdecl asm_FUN_00444760_00444760();
#define VA_asm_FUN_00444760_00444760 0x00444760
extern "C" void __cdecl asm_FUN_00444ce0_00444ce0();
#define VA_asm_FUN_00444ce0_00444ce0 0x00444ce0
extern "C" void __cdecl asm_FUN_004450e0_004450e0();
#define VA_asm_FUN_004450e0_004450e0 0x004450e0
extern "C" int __cdecl asm_FUN_004451c0_004451c0(AnimationManager_00442F50* manager, RenderEntity* entity);
#define VA_asm_FUN_004451c0_004451c0 0x004451c0
extern "C" void __cdecl asm_FUN_004452f0_004452f0();
#define VA_asm_FUN_004452f0_004452f0 0x004452f0
extern "C" void __cdecl asm_FUN_00445620_part_004456f0();
#define VA_asm_FUN_00445620_part_004456f0 0x004456f0
extern "C" void __cdecl asm_FUN_00445620_part_00445740();
#define VA_asm_FUN_00445620_part_00445740 0x00445740
extern "C" void __cdecl asm_FUN_00446220_00446220();
#define VA_asm_FUN_00446220_00446220 0x00446220
extern "C" void __cdecl asm_FUN_004462f0_004462f0();
#define VA_asm_FUN_004462f0_004462f0 0x004462f0
extern "C" void __cdecl asm_FUN_004465b0_004465b0();
#define VA_asm_FUN_004465b0_004465b0 0x004465b0
extern "C" void __cdecl asm_FUN_004465b0_part_004467d0();
#define VA_asm_FUN_004465b0_part_004467d0 0x004467d0
extern "C" void __cdecl asm_FUN_004470c0_004470c0();
#define VA_asm_FUN_004470c0_004470c0 0x004470c0
extern "C" void __cdecl asm_FUN_004472e0_004472e0();
#define VA_asm_FUN_004472e0_004472e0 0x004472e0
extern "C" void __cdecl asm_FUN_00447470_00447470();
#define VA_asm_FUN_00447470_00447470 0x00447470
extern "C" void __cdecl asm_FUN_00447470_part_004475f0();
#define VA_asm_FUN_00447470_part_004475f0 0x004475f0
extern "C" void __cdecl asm_FUN_00447810_00447810();
#define VA_asm_FUN_00447810_00447810 0x00447810
extern "C" void __cdecl asm_FUN_00447bb0_00447bb0();
#define VA_asm_FUN_00447bb0_00447bb0 0x00447bb0
extern "C" void __cdecl asm_FUN_00448270_00448270();
#define VA_asm_FUN_00448270_00448270 0x00448270
extern "C" void __cdecl asm_FUN_00448450_00448450();
#define VA_asm_FUN_00448450_00448450 0x00448450
extern "C" void __cdecl asm_FUN_00448bb0_00448bb0();
#define VA_asm_FUN_00448bb0_00448bb0 0x00448bb0
extern "C" void __cdecl asm_FUN_004496d0_004496d0();
#define VA_asm_FUN_004496d0_004496d0 0x004496d0
extern "C" void __cdecl asm_FUN_00449870_00449870();
#define VA_asm_FUN_00449870_00449870 0x00449870
extern "C" void __cdecl asm_FUN_00449950_00449950();
#define VA_asm_FUN_00449950_00449950 0x00449950
extern "C" void __cdecl asm_FUN_00449c00_00449c00();
#define VA_asm_FUN_00449c00_00449c00 0x00449c00
extern "C" void __cdecl asm_FUN_00449c00_part_00449c30();
#define VA_asm_FUN_00449c00_part_00449c30 0x00449c30
extern "C" void __cdecl asm_FUN_00449d40_00449d40();
#define VA_asm_FUN_00449d40_00449d40 0x00449d40
extern "C" void __cdecl asm_FUN_0044a0c0_0044a0c0();
#define VA_asm_FUN_0044a0c0_0044a0c0 0x0044a0c0
extern "C" void __cdecl asm_FUN_0044a190_0044a190();
#define VA_asm_FUN_0044a190_0044a190 0x0044a190
extern "C" void __cdecl asm_FUN_0044a190_part_0044a360();
#define VA_asm_FUN_0044a190_part_0044a360 0x0044a360
extern "C" void __cdecl asm_FUN_0044a5f0_0044a5f0();
#define VA_asm_FUN_0044a5f0_0044a5f0 0x0044a5f0
extern "C" void __cdecl asm_FUN_0044b360_0044b360();
#define VA_asm_FUN_0044b360_0044b360 0x0044b360
extern "C" void __cdecl asm_FUN_0044c1c0_0044c1c0();
#define VA_asm_FUN_0044c1c0_0044c1c0 0x0044c1c0
extern "C" void __cdecl asm_FUN_0044c350_0044c350();
#define VA_asm_FUN_0044c350_0044c350 0x0044c350
extern "C" void __cdecl asm_FUN_0044c8f0_0044c8f0();
#define VA_asm_FUN_0044c8f0_0044c8f0 0x0044c8f0
extern "C" void __cdecl asm_FUN_0044c8f0_part_0044cad0();
#define VA_asm_FUN_0044c8f0_part_0044cad0 0x0044cad0
extern "C" void __cdecl asm_FUN_0044cbf0_0044cbf0();
#define VA_asm_FUN_0044cbf0_0044cbf0 0x0044cbf0
extern "C" void __cdecl asm_FUN_0044cf20_0044cf20();
#define VA_asm_FUN_0044cf20_0044cf20 0x0044cf20
extern "C" void __cdecl asm_FUN_0044d850_0044d850();
#define VA_asm_FUN_0044d850_0044d850 0x0044d850
extern "C" void __cdecl asm_FUN_0044d850_part_0044d9f0();
#define VA_asm_FUN_0044d850_part_0044d9f0 0x0044d9f0
extern "C" void __cdecl asm_FUN_0044e1a0_0044e1a0();
#define VA_asm_FUN_0044e1a0_0044e1a0 0x0044e1a0
extern "C" void __cdecl asm_FUN_0044e1a0_part_0044e1e0();
#define VA_asm_FUN_0044e1a0_part_0044e1e0 0x0044e1e0
extern "C" void __cdecl asm_FUN_00450220_00450220();
#define VA_asm_FUN_00450220_00450220 0x00450220
extern "C" void __cdecl asm_FUN_00450470_00450470();
#define VA_asm_FUN_00450470_00450470 0x00450470
extern "C" void __cdecl asm_FUN_00450500_00450500();
#define VA_asm_FUN_00450500_00450500 0x00450500
extern "C" void __cdecl asm_FUN_004505b0_004505b0();
#define VA_asm_FUN_004505b0_004505b0 0x004505b0
extern "C" void __cdecl asm_FUN_00450700_00450700();
#define VA_asm_FUN_00450700_00450700 0x00450700
extern "C" void __cdecl asm_FUN_00452475_00452475();
#define VA_asm_FUN_00452475_00452475 0x00452475
extern "C" void __cdecl asm_FUN_00452577_00452577();
#define VA_asm_FUN_00452577_00452577 0x00452577
extern "C" void __cdecl asm_FUN_00452647_00452647();
#define VA_asm_FUN_00452647_00452647 0x00452647
extern "C" void __cdecl asm_FUN_004526d1_004526d1();
#define VA_asm_FUN_004526d1_004526d1 0x004526d1
extern "C" void __cdecl asm_FUN_00452730_00452730();
#define VA_asm_FUN_00452730_00452730 0x00452730
extern "C" int __cdecl asm_FUN_00452abc_00452abc(const char* path);
#define VA_asm_FUN_00452abc_00452abc 0x00452abc
extern "C" void __cdecl asm_FUN_00452e04_00452e04();
#define VA_asm_FUN_00452e04_00452e04 0x00452e04
extern "C" double __cdecl asm_FUN_00452ff0_00452ff0(double value);
#define VA_asm_FUN_00452ff0_00452ff0 0x00452ff0
extern "C" void __cdecl asm_FUN_00453111_00453111();
#define VA_asm_FUN_00453111_00453111 0x00453111
extern "C" void __cdecl asm_FUN_00453111_part_004531bf();
#define VA_asm_FUN_00453111_part_004531bf 0x004531bf
extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(int index);
#define VA_asm_FUN_00453b3f_00453b3f 0x00453b3f
extern "C" void __cdecl asm_FUN_00453c03_00453c03();
#define VA_asm_FUN_00453c03_00453c03 0x00453c03
extern "C" void __cdecl asm_FUN_00454ed7_00454ed7();
#define VA_asm_FUN_00454ed7_00454ed7 0x00454ed7
extern "C" void __cdecl asm_FUN_00455b10_00455b10();
#define VA_asm_FUN_00455b10_00455b10 0x00455b10
extern "C" void __cdecl asm_FUN_00455b19_00455b19();
#define VA_asm_FUN_00455b19_00455b19 0x00455b19
extern "C" void __cdecl asm_FUN_00455bf3_00455bf3();
#define VA_asm_FUN_00455bf3_00455bf3 0x00455bf3
extern "C" void __cdecl asm_FUN_00455d53_00455d53();
#define VA_asm_FUN_00455d53_00455d53 0x00455d53
extern "C" void __cdecl asm_FUN_00455fe7_00455fe7();
#define VA_asm_FUN_00455fe7_00455fe7 0x00455fe7
extern "C" void __cdecl asm_FUN_004564fa_004564fa();
#define VA_asm_FUN_004564fa_004564fa 0x004564fa
extern "C" void __cdecl asm_FUN_00456506_00456506();
#define VA_asm_FUN_00456506_00456506 0x00456506
extern "C" void __cdecl asm_FUN_00456674_00456674();
#define VA_asm_FUN_00456674_00456674 0x00456674
extern "C" void __cdecl asm_FUN_00456a8c_00456a8c();
#define VA_asm_FUN_00456a8c_00456a8c 0x00456a8c
extern "C" int* __cdecl asm_FUN_00456af2_00456af2();
#define VA_asm_FUN_00456af2_00456af2 0x00456af2
extern "C" unsigned int* __cdecl asm_FUN_00456afb_00456afb();
#define VA_asm_FUN_00456afb_00456afb 0x00456afb
extern "C" void __cdecl asm_FUN_00456e03_00456e03();
#define VA_asm_FUN_00456e03_00456e03 0x00456e03
extern "C" void __cdecl asm_FUN_00457212_00457212();
#define VA_asm_FUN_00457212_00457212 0x00457212
extern "C" void __cdecl asm_FUN_00457285_00457285();
#define VA_asm_FUN_00457285_00457285 0x00457285
extern "C" void __cdecl asm_FUN_00457395_00457395();
#define VA_asm_FUN_00457395_00457395 0x00457395
extern "C" void __cdecl asm_FUN_004574fd_004574fd();
#define VA_asm_FUN_004574fd_004574fd 0x004574fd
extern "C" void __cdecl asm_FUN_00457577_00457577();
#define VA_asm_FUN_00457577_00457577 0x00457577
extern "C" void __cdecl asm_FUN_00457580_00457580();
#define VA_asm_FUN_00457580_00457580 0x00457580
extern "C" void __cdecl asm_FUN_004576d8_004576d8();
#define VA_asm_FUN_004576d8_004576d8 0x004576d8
extern "C" void __cdecl asm_FUN_00457799_00457799();
#define VA_asm_FUN_00457799_00457799 0x00457799
extern "C" void __cdecl asm_FUN_0045794d_0045794d();
#define VA_asm_FUN_0045794d_0045794d 0x0045794d
extern "C" void __cdecl asm_FUN_0045794d_part_00457a1c();
#define VA_asm_FUN_0045794d_part_00457a1c 0x00457a1c
extern "C" void __cdecl asm_FUN_00457a13_00457a13();
#define VA_asm_FUN_00457a13_00457a13 0x00457a13
extern "C" void __cdecl asm_FUN_00457a7c_00457a7c();
#define VA_asm_FUN_00457a7c_00457a7c 0x00457a7c
extern "C" void __cdecl asm_FUN_00457a7c_part_0045825b();
#define VA_asm_FUN_00457a7c_part_0045825b 0x0045825b
extern "C" void __cdecl asm_FUN_004588a7_004588a7();
#define VA_asm_FUN_004588a7_004588a7 0x004588a7
extern "C" void __cdecl asm_FUN_00458b1e_00458b1e();
#define VA_asm_FUN_00458b1e_00458b1e 0x00458b1e
extern "C" void __cdecl asm_FUN_00458b1e_part_00458b46();
#define VA_asm_FUN_00458b1e_part_00458b46 0x00458b46
extern "C" void __cdecl asm_FUN_00458efd_00458efd(int errorCode);
#define VA_asm_FUN_00458efd_00458efd 0x00458efd
extern "C" void __cdecl asm_FUN_004597ba_part_004597ee();
#define VA_asm_FUN_004597ba_part_004597ee 0x004597ee
extern "C" void __cdecl asm_FUN_00459972_00459972();
#define VA_asm_FUN_00459972_00459972 0x00459972
extern "C" void __cdecl asm_FUN_00459cae_00459cae();
#define VA_asm_FUN_00459cae_00459cae 0x00459cae
extern "C" void __cdecl asm_FUN_00459cd2_00459cd2();
#define VA_asm_FUN_00459cd2_00459cd2 0x00459cd2
extern "C" void __cdecl asm_FUN_00459f15_00459f15();
#define VA_asm_FUN_00459f15_00459f15 0x00459f15
extern "C" void __cdecl asm_FUN_0045af1d_0045af1d();
#define VA_asm_FUN_0045af1d_0045af1d 0x0045af1d
extern "C" void __cdecl asm_FUN_0045bd80_0045bd80();
#define VA_asm_FUN_0045bd80_0045bd80 0x0045bd80
extern "C" void __cdecl asm_FUN_0045bd90_0045bd90();
#define VA_asm_FUN_0045bd90_0045bd90 0x0045bd90
extern "C" void __cdecl asm_FUN_0045c377_0045c377();
#define VA_asm_FUN_0045c377_0045c377 0x0045c377
extern "C" int __cdecl asm_FUN_0045c3f1_0045c3f1(short value);
#define VA_asm_FUN_0045c3f1_0045c3f1 0x0045c3f1
extern "C" void __cdecl asm_FUN_0045c5dc_0045c5dc();
#define VA_asm_FUN_0045c5dc_0045c5dc 0x0045c5dc
extern "C" void __cdecl asm_FUN_0045cd56_0045cd56();
#define VA_asm_FUN_0045cd56_0045cd56 0x0045cd56
extern "C" void __cdecl asm_FUN_0045cdae_0045cdae();
#define VA_asm_FUN_0045cdae_0045cdae 0x0045cdae
extern "C" void __cdecl asm_FUN_0045cfaf_0045cfaf();
#define VA_asm_FUN_0045cfaf_0045cfaf 0x0045cfaf
extern "C" void __cdecl asm_FUN_0045cfb8_0045cfb8();
#define VA_asm_FUN_0045cfb8_0045cfb8 0x0045cfb8
extern "C" void __cdecl asm_FUN_0045d2a3_0045d2a3();
#define VA_asm_FUN_0045d2a3_0045d2a3 0x0045d2a3
extern "C" void __cdecl asm_FUN_0045d676_0045d676(void* output, const unsigned char* text);
#define VA_asm_FUN_0045d676_0045d676 0x0045d676
extern "C" void __cdecl asm_FUN_0045d701_0045d701(void* output, const unsigned char* text);
#define VA_asm_FUN_0045d701_0045d701 0x0045d701
extern "C" void __cdecl asm_FUN_0045d746_0045d746();
#define VA_asm_FUN_0045d746_0045d746 0x0045d746
extern "C" void __cdecl asm_FUN_0045dd85_0045dd85();
#define VA_asm_FUN_0045dd85_0045dd85 0x0045dd85
extern "C" void __cdecl asm_FUN_0045de91_0045de91();
#define VA_asm_FUN_0045de91_0045de91 0x0045de91
extern "C" void __cdecl asm_FUN_0045def8_0045def8();
#define VA_asm_FUN_0045def8_0045def8 0x0045def8
extern "C" void __cdecl asm_FUN_0045e11a_0045e11a();
#define VA_asm_FUN_0045e11a_0045e11a 0x0045e11a
extern "C" int __cdecl asm_FUN_0045e3a0_0045e3a0();
#define VA_asm_FUN_0045e3a0_0045e3a0 0x0045e3a0
extern "C" void __cdecl asm_FUN_0045ea31_0045ea31();
#define VA_asm_FUN_0045ea31_0045ea31 0x0045ea31
extern "C" void __cdecl asm_FUN_0045edab_0045edab();
#define VA_asm_FUN_0045edab_0045edab 0x0045edab
extern "C" void __cdecl asm_FUN_0045ee1d_0045ee1d();
#define VA_asm_FUN_0045ee1d_0045ee1d 0x0045ee1d
extern "C" void __cdecl asm_FUN_0045ee1d_part_0045ef2e();
#define VA_asm_FUN_0045ee1d_part_0045ef2e 0x0045ef2e
extern "C" void __cdecl asm_FUN_0045ee1d_part_0045effc();
#define VA_asm_FUN_0045ee1d_part_0045effc 0x0045effc
extern "C" void __cdecl asm_FUN_0045ee1d_part_0045f129();
#define VA_asm_FUN_0045ee1d_part_0045f129 0x0045f129
extern "C" void __cdecl asm_FUN_0045f259_0045f259();
#define VA_asm_FUN_0045f259_0045f259 0x0045f259
extern "C" void __cdecl asm_FUN_0045f259_part_0045f29d();
#define VA_asm_FUN_0045f259_part_0045f29d 0x0045f29d
extern "C" void __cdecl asm_FUN_0045f7ac_0045f7ac();
#define VA_asm_FUN_0045f7ac_0045f7ac 0x0045f7ac
extern "C" void __cdecl asm_FUN_0045f7b5_0045f7b5(int file);
#define VA_asm_FUN_0045f7b5_0045f7b5 0x0045f7b5
extern "C" void __cdecl asm_FUN_0045fd21_0045fd21();
#define VA_asm_FUN_0045fd21_0045fd21 0x0045fd21
extern "C" void __cdecl asm_FUN_0045fd4d_0045fd4d();
#define VA_asm_FUN_0045fd4d_0045fd4d 0x0045fd4d
extern "C" void** __cdecl asm_FUN_0045fe7e_0045fe7e();
#define VA_asm_FUN_0045fe7e_0045fe7e 0x0045fe7e
extern "C" void __cdecl asm_FUN_00460163_00460163();
#define VA_asm_FUN_00460163_00460163 0x00460163
extern "C" long __cdecl asm_FUN_004601a1_004601a1(unsigned int locale);
#define VA_asm_FUN_004601a1_004601a1 0x004601a1
extern "C" void __cdecl asm_FUN_004601e8_004601e8();
#define VA_asm_FUN_004601e8_004601e8 0x004601e8
extern "C" void __cdecl asm_FUN_004601e8_part_004602e0();
#define VA_asm_FUN_004601e8_part_004602e0 0x004602e0
extern "C" void __cdecl asm_FUN_0046041e_0046041e();
#define VA_asm_FUN_0046041e_0046041e 0x0046041e
extern "C" void __cdecl asm_FUN_00460872_00460872();
#define VA_asm_FUN_00460872_00460872 0x00460872
extern "C" void __cdecl asm_FUN_0046095a_0046095a();
#define VA_asm_FUN_0046095a_0046095a 0x0046095a
extern "C" void __cdecl asm_FUN_00460b90_00460b90();
#define VA_asm_FUN_00460b90_00460b90 0x00460b90
extern "C" void __cdecl asm_FUN_00460e41_00460e41();
#define VA_asm_FUN_00460e41_00460e41 0x00460e41
extern "C" void __cdecl asm_FUN_00461184_00461184();
#define VA_asm_FUN_00461184_00461184 0x00461184
extern "C" void __cdecl asm_FUN_004613e8_004613e8();
#define VA_asm_FUN_004613e8_004613e8 0x004613e8
extern "C" void __cdecl asm_FUN_00461549_00461549();
#define VA_asm_FUN_00461549_00461549 0x00461549
extern "C" void __cdecl asm_FUN_00461841_00461841();
#define VA_asm_FUN_00461841_00461841 0x00461841
extern "C" void __cdecl asm_FUN_00461af9_00461af9();
#define VA_asm_FUN_00461af9_00461af9 0x00461af9
extern "C" void __cdecl asm_FUN_00461af9_part_00461cbe();
#define VA_asm_FUN_00461af9_part_00461cbe 0x00461cbe
extern "C" void __cdecl asm_FUN_00461af9_part_00461d57();
#define VA_asm_FUN_00461af9_part_00461d57 0x00461d57
extern "C" int __cdecl asm_FUN_00461f31_00461f31(
    char** environment_entry, int mode);
#define VA_asm_FUN_00461f31_00461f31 0x00461f31
extern "C" void __cdecl asm_FUN_00462201_00462201();
#define VA_asm_FUN_00462201_00462201 0x00462201
extern "C" void __cdecl asm_FUN_0046227b_0046227b();
#define VA_asm_FUN_0046227b_0046227b 0x0046227b
extern "C" void __cdecl asm_FUN_0046227b_part_00452720();
#define VA_asm_FUN_0046227b_part_00452720 0x00452720
extern "C" void __cdecl asm_FUN_00462371_00462371();
#define VA_asm_FUN_00462371_00462371 0x00462371
extern "C" void __cdecl asm_FUN_004623de_004623de();
#define VA_asm_FUN_004623de_004623de 0x004623de
extern "C" void __cdecl asm_FUN_0046241d_0046241d();
#define VA_asm_FUN_0046241d_0046241d 0x0046241d
extern "C" void __cdecl asm_FUN_00462428_00462428();
#define VA_asm_FUN_00462428_00462428 0x00462428
extern "C" void __cdecl asm_FUN_004624c3_004624c3();
#define VA_asm_FUN_004624c3_004624c3 0x004624c3
extern "C" void __cdecl asm_FUN_004624e5_004624e5();
#define VA_asm_FUN_004624e5_004624e5 0x004624e5
extern "C" void __cdecl asm_FUN_00462adc_00462adc();
#define VA_asm_FUN_00462adc_00462adc 0x00462adc
extern "C" void __cdecl asm_FUN_00462b72_00462b72();
#define VA_asm_FUN_00462b72_00462b72 0x00462b72
extern "C" void __cdecl asm_FUN_00462c12_00462c12();
#define VA_asm_FUN_00462c12_00462c12 0x00462c12
extern "C" void __cdecl asm_FUN_00462c5a_00462c5a();
#define VA_asm_FUN_00462c5a_00462c5a 0x00462c5a
extern "C" void __cdecl asm_FUN_00462d00_00462d00();
#define VA_asm_FUN_00462d00_00462d00 0x00462d00
extern "C" void __cdecl asm_FUN_00462d0b_00462d0b();
#define VA_asm_FUN_00462d0b_00462d0b 0x00462d0b
extern "C" void __cdecl asm_FUN_00462d24_00462d24();
#define VA_asm_FUN_00462d24_00462d24 0x00462d24
extern "C" void __cdecl asm_FUN_00462d3c_00462d3c();
#define VA_asm_FUN_00462d3c_00462d3c 0x00462d3c
extern "C" void __cdecl asm_FUN_00462d77_00462d77();
#define VA_asm_FUN_00462d77_00462d77 0x00462d77
extern "C" void __cdecl asm_FUN_00462f31_00462f31();
#define VA_asm_FUN_00462f31_00462f31 0x00462f31
extern "C" void __cdecl asm_FUN_0046332a_0046332a();
#define VA_asm_FUN_0046332a_0046332a 0x0046332a
extern "C" void __cdecl asm_FUN_00463b2c_00463b2c();
#define VA_asm_FUN_00463b2c_00463b2c 0x00463b2c
extern "C" void __cdecl asm_FUN_00463bba_00463bba();
#define VA_asm_FUN_00463bba_00463bba 0x00463bba
extern "C" void __cdecl asm_FUN_00463bf0_00463bf0();
#define VA_asm_FUN_00463bf0_00463bf0 0x00463bf0
extern "C" void __cdecl asm_FUN_00463c0d_00463c0d();
#define VA_asm_FUN_00463c0d_00463c0d 0x00463c0d
extern "C" void __cdecl asm_FUN_00463c0d_part_00464f9e();
#define VA_asm_FUN_00463c0d_part_00464f9e 0x00464f9e
extern "C" void __cdecl asm_FUN_00463d83_00463d83();
#define VA_asm_FUN_00463d83_00463d83 0x00463d83
extern "C" void __cdecl asm_FUN_00463d8a_00463d8a();
#define VA_asm_FUN_00463d8a_00463d8a 0x00463d8a
extern "C" void __cdecl asm_FUN_00464916_00464916();
#define VA_asm_FUN_00464916_00464916 0x00464916
extern "C" void __cdecl asm_FUN_00464b1c_00464b1c();
#define VA_asm_FUN_00464b1c_00464b1c 0x00464b1c
extern "C" void __cdecl asm_FUN_00464ea0_00464ea0();
#define VA_asm_FUN_00464ea0_00464ea0 0x00464ea0
extern "C" void __cdecl asm_FUN_00464f15_00464f15();
#define VA_asm_FUN_00464f15_00464f15 0x00464f15
extern "C" void __cdecl asm_FUN_00464f2c_00464f2c();
#define VA_asm_FUN_00464f2c_00464f2c 0x00464f2c
extern "C" void __cdecl asm_FUN_00464f88_00464f88();
#define VA_asm_FUN_00464f88_00464f88 0x00464f88
extern "C" void __cdecl asm_FUN_0046508c_0046508c();
#define VA_asm_FUN_0046508c_0046508c 0x0046508c
extern "C" void __cdecl asm_FUN_004659f0_004659f0();
#define VA_asm_FUN_004659f0_004659f0 0x004659f0
extern "C" void __cdecl asm_FaithGauge_AddRetail_00418930();
#define VA_asm_FaithGauge_AddRetail_00418930 0x00418930
extern "C" void __cdecl asm_FileHandle_OpenRetail_00435370();
#define VA_asm_FileHandle_OpenRetail_00435370 0x00435370
extern "C" void __cdecl asm_FileHandle_OpenRetail_part_004353b0();
#define VA_asm_FileHandle_OpenRetail_part_004353b0 0x004353b0
extern "C" void __cdecl asm_File_CloseProbeHandle_0044b7e0();
#define VA_asm_File_CloseProbeHandle_0044b7e0 0x0044b7e0
extern "C" void __cdecl asm_File_OpenSharedRead_0044b6b0();
#define VA_asm_File_OpenSharedRead_0044b6b0 0x0044b6b0
extern "C" void __cdecl asm_File_OpenSharedWrite_0044b620();
#define VA_asm_File_OpenSharedWrite_0044b620 0x0044b620
extern "C" void __cdecl asm_File_ProbeExists_0044b4d0();
#define VA_asm_File_ProbeExists_0044b4d0 0x0044b4d0
extern "C" void __cdecl asm_File_ReadShared_0044b790();
#define VA_asm_File_ReadShared_0044b790 0x0044b790
extern "C" void __cdecl asm_File_ResolvePath_00435610();
#define VA_asm_File_ResolvePath_00435610 0x00435610
extern "C" void __cdecl asm_File_WriteShared_0044b740();
#define VA_asm_File_WriteShared_0044b740 0x0044b740
extern "C" void __cdecl asm_File_WriteWholeFile_0044b540();
#define VA_asm_File_WriteWholeFile_0044b540 0x0044b540
extern "C" void __cdecl asm_FindAndUnlinkFrame_00462a34(FrameInfo* frame);
#define VA_asm_FindAndUnlinkFrame_00462a34 0x00462a34
extern "C" void __cdecl asm_FindHandlerForForeignException_004636a1();
#define VA_asm_FindHandlerForForeignException_004636a1 0x004636a1
extern "C" void __cdecl asm_FindHandler_0046375f();
#define VA_asm_FindHandler_0046375f 0x0046375f
extern "C" void __cdecl DeleteFontCacheObjects_00437d10();
#define VA_DeleteFontCacheObjects_00437d10 0x00437d10
extern "C" void __cdecl asm_FontCache_FlushRetail_00436a30();
#define VA_asm_FontCache_FlushRetail_00436a30 0x00436a30
extern "C" void __cdecl asm_FrameRateCounter_UpdateRetail_004134b0();
#define VA_asm_FrameRateCounter_UpdateRetail_004134b0 0x004134b0
extern "C" void __cdecl asm_FrameTimer_Advance_0044bf40();
#define VA_asm_FrameTimer_Advance_0044bf40 0x0044bf40
extern "C" void __cdecl asm_FrameTimer_Decrement_00428dd0();
#define VA_asm_FrameTimer_Decrement_00428dd0 0x00428dd0
extern "C" void __cdecl asm_FrameTimer_Tick_00404ed0();
#define VA_asm_FrameTimer_Tick_00404ed0 0x00404ed0
extern "C" void __cdecl asm_FrameUnwindToState_00462e7e();
#define VA_asm_FrameUnwindToState_00462e7e 0x00462e7e
extern "C" void __cdecl asm_FrameUnwindToState_part_00462f0a();
#define VA_asm_FrameUnwindToState_part_00462f0a 0x00462f0a
extern "C" void __cdecl asm_GameConfig_InitializeDefaults_00418c40();
#define VA_asm_GameConfig_InitializeDefaults_00418c40 0x00418c40
extern "C" void __cdecl asm_GameMain_00438ad0();
#define VA_asm_GameMain_00438ad0 0x00438ad0
extern "C" void __cdecl asm_GameMain_part_00439010();
#define VA_asm_GameMain_part_00439010 0x00439010
extern "C" void __cdecl asm_GameProgress_HasAnyPlayRecord_0042c850();
#define VA_asm_GameProgress_HasAnyPlayRecord_0042c850 0x0042c850
extern "C" void __cdecl asm_GameProgress_UnlockAllStages_0042c8c0();
#define VA_asm_GameProgress_UnlockAllStages_0042c8c0 0x0042c8c0
extern "C" void __cdecl asm_GameProgress_UnlockAllStages_part_0042c900();
#define VA_asm_GameProgress_UnlockAllStages_part_0042c900 0x0042c900
extern "C" void __cdecl asm_GameStateInit_00445900();
#define VA_asm_GameStateInit_00445900 0x00445900
extern "C" void __cdecl asm_GameStateInit_part_00445ae0();
#define VA_asm_GameStateInit_part_00445ae0 0x00445ae0
extern "C" void __cdecl asm_GameState_DisableTimerWithOwner_0042c5c0();
#define VA_asm_GameState_DisableTimerWithOwner_0042c5c0 0x0042c5c0
extern "C" void __cdecl asm_GameState_DispatchAnimationSlotSecondary_0042c750();
#define VA_asm_GameState_DispatchAnimationSlotSecondary_0042c750 0x0042c750
extern "C" void __cdecl asm_GameState_DispatchAnimationSlot_0042c730();
#define VA_asm_GameState_DispatchAnimationSlot_0042c730 0x0042c730
extern "C" void __cdecl asm_GameState_DispatchDummy_00420c00();
#define VA_asm_GameState_DispatchDummy_00420c00 0x00420c00
extern "C" void __cdecl asm_GameState_SetTimerTarget_0042c620();
#define VA_asm_GameState_SetTimerTarget_0042c620 0x0042c620
extern "C" void __cdecl asm_GameState_Unpause_00422c30();
#define VA_asm_GameState_Unpause_00422c30 0x00422c30
extern "C" void __cdecl asm_GameState_UpdateFrameMaximum_00421f60();
#define VA_asm_GameState_UpdateFrameMaximum_00421f60 0x00421f60
extern "C" void __cdecl asm_GameThread_AppendFormattedMarkedRetail_00401690();
#define VA_asm_GameThread_AppendFormattedMarkedRetail_00401690 0x00401690
extern "C" void __cdecl asm_GameThread_AppendFormatted_00401630();
#define VA_asm_GameThread_AppendFormatted_00401630 0x00401630
extern "C" void __cdecl asm_GameThread_AppendRecord_00401530();
#define VA_asm_GameThread_AppendRecord_00401530 0x00401530
extern "C" void __cdecl asm_GameThread_Construct_00401000();
#define VA_asm_GameThread_Construct_00401000 0x00401000
extern "C" void __cdecl asm_GameThread_SelectRenderStageRetail_00401d20();
#define VA_asm_GameThread_SelectRenderStageRetail_00401d20 0x00401d20
extern "C" void __cdecl asm_GameUi_CreateAndPublish_004180e0();
#define VA_asm_GameUi_CreateAndPublish_004180e0 0x004180e0
extern "C" void __cdecl asm_GetLcidFromCountry_0045c93e();
#define VA_asm_GetLcidFromCountry_0045c93e 0x0045c93e
extern "C" void __cdecl asm_GetLcidFromDefault_0045c35d();
#define VA_asm_GetLcidFromDefault_0045c35d 0x0045c35d
extern "C" void __cdecl asm_GetLcidFromLangCountry_0045c975();
#define VA_asm_GetLcidFromLangCountry_0045c975 0x0045c975
extern "C" void __cdecl asm_GetLcidFromLanguage_0045c9fb();
#define VA_asm_GetLcidFromLanguage_0045c9fb 0x0045c9fb
extern "C" void __cdecl asm_GetPrimaryLen_0045c527();
#define VA_asm_GetPrimaryLen_0045c527 0x0045c527
extern "C" void __cdecl asm_GetRangeOfTrysToCheck_00462971();
#define VA_asm_GetRangeOfTrysToCheck_00462971 0x00462971
extern "C" void __cdecl asm_Grow_LegacyString_004386b0();
#define VA_asm_Grow_LegacyString_004386b0 0x004386b0
extern "C" void __cdecl asm_Heap_DestroyOwnedSecondary_0042cdb0();
#define VA_asm_Heap_DestroyOwnedSecondary_0042cdb0 0x0042cdb0
extern "C" void __cdecl asm_Heap_DestroyOwned_00418150();
#define VA_asm_Heap_DestroyOwned_00418150 0x00418150
extern "C" void __cdecl asm_IncMan_0045d2fc(unsigned int* words, int bit);
#define VA_asm_IncMan_0045d2fc 0x0045d2fc
extern "C" void __cdecl asm_InitializeEntity_00401de0();
#define VA_asm_InitializeEntity_00401de0 0x00401de0
extern "C" void __cdecl asm_InitializeGameState_00402230();
#define VA_asm_InitializeGameState_00402230 0x00402230
extern "C" void __cdecl asm_InitializePlayer_00405860();
#define VA_asm_InitializePlayer_00405860 0x00405860
extern "C" void __cdecl asm_InputMaskActive_0040ace0();
#define VA_asm_InputMaskActive_0040ace0 0x0040ace0
extern "C" void __cdecl asm_Input_NormalizeKeyboardState_0044b080();
#define VA_asm_Input_NormalizeKeyboardState_0044b080 0x0044b080
extern "C" void __cdecl asm_Input_PollJoystickButtons_0044a4e0();
#define VA_asm_Input_PollJoystickButtons_0044a4e0 0x0044a4e0
extern "C" void __cdecl asm_Input_SetJoystickPropertyRetail_0044c7e0();
#define VA_asm_Input_SetJoystickPropertyRetail_0044c7e0 0x0044c7e0
extern "C" void __cdecl asm_Input_UpdateKeyboardState_0044b010();
#define VA_asm_Input_UpdateKeyboardState_0044b010 0x0044b010
extern "C" void __cdecl asm_InternalCxxFrameHandler_00463963();
#define VA_asm_InternalCxxFrameHandler_00463963 0x00463963
extern "C" int __cdecl asm_IsExceptionObjectToBeDestroyed_00462a13(void* object);
#define VA_asm_IsExceptionObjectToBeDestroyed_00462a13 0x00462a13
extern "C" int __cdecl asm_IsZeroMan_0045d3e2(const int* words);
#define VA_asm_IsZeroMan_0045d3e2 0x0045d3e2
extern "C" void __cdecl asm_ItemFrontRuntime_InitializeRetail_00413980();
#define VA_asm_ItemFrontRuntime_InitializeRetail_00413980 0x00413980
extern "C" void __cdecl asm_ItemManager_CreateRetail_00414830();
#define VA_asm_ItemManager_CreateRetail_00414830 0x00414830
extern "C" void __cdecl asm_BulletManager_DestroyRetail_00405f70();
#define VA_asm_BulletManager_DestroyRetail_00405f70 0x00405f70
extern "C" void __cdecl asm_JumpToContinuation_004626d6();
#define VA_asm_JumpToContinuation_004626d6 0x004626d6
extern "C" void __cdecl asm_KeyConfig_ReassignSlotRetail_00430250();
#define VA_asm_KeyConfig_ReassignSlotRetail_00430250 0x00430250
extern "C" void __cdecl asm_LcidFromHexString_0045c4f2();
#define VA_asm_LcidFromHexString_0045c4f2 0x0045c4f2
extern "C" void __cdecl asm_LegacyString_Clear_004381f0();
#define VA_asm_LegacyString_Clear_004381f0 0x004381f0
extern "C" void __cdecl asm_LegacyString_Duplicate_00435220();
#define VA_asm_LegacyString_Duplicate_00435220 0x00435220
extern "C" void __cdecl asm_LinkedPool_AllocateAndAppendRetail_0042aa50();
#define VA_asm_LinkedPool_AllocateAndAppendRetail_0042aa50 0x0042aa50
extern "C" void __cdecl asm_LoadGameThreadResources_00401110();
#define VA_asm_LoadGameThreadResources_00401110 0x00401110
extern "C" void __cdecl asm_MainMenu_RegisterTasksRetail_00422150();
#define VA_asm_MainMenu_RegisterTasksRetail_00422150 0x00422150
extern "C" void __cdecl asm_MemoryFile_FindPredecessor_00436330();
#define VA_asm_MemoryFile_FindPredecessor_00436330 0x00436330
extern "C" void __cdecl asm_MemoryFile_FindPredecessor_part_00436350();
#define VA_asm_MemoryFile_FindPredecessor_part_00436350 0x00436350
extern "C" void __cdecl asm_MemoryFile_RelinkChild_00436260();
#define VA_asm_MemoryFile_RelinkChild_00436260 0x00436260
extern "C" void __cdecl asm_MemoryFile_RemoveNode_00436210();
#define VA_asm_MemoryFile_RemoveNode_00436210 0x00436210
extern "C" void __cdecl asm_MemoryFile_ReplaceNode_004362b0();
#define VA_asm_MemoryFile_ReplaceNode_004362b0 0x004362b0
extern "C" void __cdecl asm_MenuCursor_Advance_0044bea0();
#define VA_asm_MenuCursor_Advance_0044bea0 0x0044bea0
extern "C" void __cdecl asm_MidiWorker_StopRetail_0043dab0();
#define VA_asm_MidiWorker_StopRetail_0043dab0 0x0043dab0
extern "C" void __cdecl asm_NLG_Notify1_00459969();
#define VA_asm_NLG_Notify1_00459969 0x00459969
extern "C" void __cdecl asm_Ordinal_11_00452170();
#define VA_asm_Ordinal_11_00452170 0x00452170
extern "C" void __cdecl asm_OutsideAxisAlignedBounds_004086b0();
#define VA_asm_OutsideAxisAlignedBounds_004086b0 0x004086b0
extern "C" void __cdecl asm_ParameterFile_LoadAndRelocateRetail_00426520();
#define VA_asm_ParameterFile_LoadAndRelocateRetail_00426520 0x00426520
extern "C" void __cdecl asm_ParameterFile_LoadAndRelocateRetail_part_00426590();
#define VA_asm_ParameterFile_LoadAndRelocateRetail_part_00426590 0x00426590
extern "C" void __cdecl asm_ParameterFile_LoadAndRelocateRetail_part_004265b0();
#define VA_asm_ParameterFile_LoadAndRelocateRetail_part_004265b0 0x004265b0
extern "C" void __cdecl asm_ParticleSeed_Combine_00404e10();
#define VA_asm_ParticleSeed_Combine_00404e10 0x00404e10
extern "C" void __cdecl asm_PathState_Reset_00417800();
#define VA_asm_PathState_Reset_00417800 0x00417800
extern "C" void __cdecl asm_Path_DecodeXor_00417010();
#define VA_asm_Path_DecodeXor_00417010 0x00417010
extern "C" void __cdecl asm_Path_FindBasenameSlot_0043d2a0();
#define VA_asm_Path_FindBasenameSlot_0043d2a0 0x0043d2a0
extern "C" void __cdecl asm_Platform_AggregateInterfaces_0044d550();
#define VA_asm_Platform_AggregateInterfaces_0044d550 0x0044d550
extern "C" void __cdecl asm_Platform_DeletingDestructorWithRelease_004297b0();
#define VA_asm_Platform_DeletingDestructorWithRelease_004297b0 0x004297b0
extern "C" void __cdecl asm_Platform_FindAvailable_0044d370();
#define VA_asm_Platform_FindAvailable_0044d370 0x0044d370
extern "C" void __cdecl asm_Platform_InvokeConfigured_0044d5d0();
#define VA_asm_Platform_InvokeConfigured_0044d5d0 0x0044d5d0
extern "C" void __cdecl asm_Platform_InvokeInterface_0044d5b0();
#define VA_asm_Platform_InvokeInterface_0044d5b0 0x0044d5b0
extern "C" void __cdecl asm_Platform_QueryInterfaces_0044d600();
#define VA_asm_Platform_QueryInterfaces_0044d600 0x0044d600
extern "C" void __cdecl asm_Platform_ReleaseOwnedArray_0044d080();
#define VA_asm_Platform_ReleaseOwnedArray_0044d080 0x0044d080
extern "C" void __cdecl asm_Platform_ReleaseOwnedHandle_00413450();
#define VA_asm_Platform_ReleaseOwnedHandle_00413450 0x00413450
extern "C" void __cdecl asm_Platform_RunInterface_0044d300();
#define VA_asm_Platform_RunInterface_0044d300 0x0044d300
extern "C" void __cdecl asm_Platform_SelectStreamRecord_0044dca0();
#define VA_asm_Platform_SelectStreamRecord_0044dca0 0x0044dca0
extern "C" void __cdecl asm_Platform_SetOperationDeadline_0044d4e0();
#define VA_asm_Platform_SetOperationDeadline_0044d4e0 0x0044d4e0
extern "C" void __cdecl asm_Platform_StopSoundWorkersRetail_0043cc40();
#define VA_asm_Platform_StopSoundWorkersRetail_0043cc40 0x0043cc40
extern "C" void __cdecl asm_Platform_StopWorkerNoDelete_0044c130();
#define VA_asm_Platform_StopWorkerNoDelete_0044c130 0x0044c130
extern "C" void __cdecl asm_Platform_StopWorker_0044c150();
#define VA_asm_Platform_StopWorker_0044c150 0x0044c150
extern "C" void __cdecl asm_PlayerAnimation_AdvanceFrame_004074b0();
#define VA_asm_PlayerAnimation_AdvanceFrame_004074b0 0x004074b0
extern "C" void __cdecl asm_PlayerAnimation_Create_00448db0();
#define VA_asm_PlayerAnimation_Create_00448db0 0x00448db0
extern "C" void __cdecl asm_PlayerManager_ConstructRetail_00408910();
#define VA_asm_PlayerManager_ConstructRetail_00408910 0x00408910
extern "C" void __cdecl asm_PlayerManager_CreateRetail_00408c90();
#define VA_asm_PlayerManager_CreateRetail_00408c90 0x00408c90
extern "C" void __cdecl asm_PlayerManager_StartMode_004045b0();
#define VA_asm_PlayerManager_StartMode_004045b0 0x004045b0
extern "C" void __cdecl asm_Player_AdjustPower_00405b60();
#define VA_asm_Player_AdjustPower_00405b60 0x00405b60
extern "C" void __cdecl asm_Player_ClearExpiredFlagsRetail_00405500();
#define VA_asm_Player_ClearExpiredFlagsRetail_00405500 0x00405500
extern "C" void __cdecl asm_Player_DeathShrink_004076a0();
#define VA_asm_Player_DeathShrink_004076a0 0x004076a0
extern "C" void __cdecl asm_Player_Draw_00405ac0();
#define VA_asm_Player_Draw_00405ac0 0x00405ac0
extern "C" void __cdecl asm_Player_ForwardAxisWrap_0040678e();
#define VA_asm_Player_ForwardAxisWrap_0040678e 0x0040678e
extern "C" void __cdecl asm_Player_HitTestRetail_004059f0();
#define VA_asm_Player_HitTestRetail_004059f0 0x004059f0
extern "C" void __cdecl asm_Player_ResetSchedulerLinksRetail_00405be0();
#define VA_asm_Player_ResetSchedulerLinksRetail_00405be0 0x00405be0
extern "C" void __cdecl asm_Player_SetSchedulerValue_00405410();
#define VA_asm_Player_SetSchedulerValue_00405410 0x00405410
extern "C" void __cdecl asm_Player_WrapHorizontal_00407da0();
#define VA_asm_Player_WrapHorizontal_00407da0 0x00407da0
extern "C" void __cdecl asm_Player_WrapVertical_00407e40();
#define VA_asm_Player_WrapVertical_00407e40 0x00407e40
extern "C" void __cdecl asm_Position_IsPartiallyInViewport_0041f7a0();
#define VA_asm_Position_IsPartiallyInViewport_0041f7a0 0x0041f7a0
extern "C" void __cdecl asm_ProgressManager_CreateAndStartWorker_0042cd50();
#define VA_asm_ProgressManager_CreateAndStartWorker_0042cd50 0x0042cd50
extern "C" void __cdecl asm_RTC_Initialize_00459776();
#define VA_asm_RTC_Initialize_00459776 0x00459776
extern "C" void __cdecl asm_RTC_Initialize_part_004597aa();
#define VA_asm_RTC_Initialize_part_004597aa 0x004597aa
extern "C" void __cdecl asm_RandomVector_StoreRoundedScalar_00441e50();
#define VA_asm_RandomVector_StoreRoundedScalar_00441e50 0x00441e50
extern "C" void __cdecl asm_ReadWhole_FileHandle_00435580();
#define VA_asm_ReadWhole_FileHandle_00435580 0x00435580
extern "C" void __cdecl asm_RecoveryLinkedCleanup_00417770();
#define VA_asm_RecoveryLinkedCleanup_00417770 0x00417770
extern "C" void __cdecl asm_RecoveryState_Configure41F50_00441f50();
#define VA_asm_RecoveryState_Configure41F50_00441f50 0x00441f50
extern "C" void __cdecl asm_RecoveryState_Configure42300_00442300();
#define VA_asm_RecoveryState_Configure42300_00442300 0x00442300
extern "C" void __cdecl asm_RecoveryState_Initialize_004220e0();
#define VA_asm_RecoveryState_Initialize_004220e0 0x004220e0
extern "C" void __cdecl asm_RecoveryTimer_Reset_00412db0();
#define VA_asm_RecoveryTimer_Reset_00412db0 0x00412db0
extern "C" void __cdecl asm_Recovery_AdvancePolarMotion_0044c2a0();
#define VA_asm_Recovery_AdvancePolarMotion_0044c2a0 0x0044c2a0
extern "C" void __cdecl asm_Recovery_AppendNode_0041ab10();
#define VA_asm_Recovery_AppendNode_0041ab10 0x0041ab10
extern "C" void __cdecl asm_Recovery_AppendPacket_0042a8a0();
#define VA_asm_Recovery_AppendPacket_0042a8a0 0x0042a8a0
extern "C" void __cdecl asm_Recovery_ClearAnimationSlot_0042c6d0();
#define VA_asm_Recovery_ClearAnimationSlot_0042c6d0 0x0042c6d0
extern "C" void __cdecl asm_Recovery_ClearEightBuckets_00419040();
#define VA_asm_Recovery_ClearEightBuckets_00419040 0x00419040
extern "C" void* __cdecl Bomb_Create(void);
#define VA_asm_Recovery_CreateFixedState_004056b0 0x004056b0
extern "C" void __cdecl SmollScore_Create();
#define VA_SmollScore_Create 0x0042b660
extern "C" void __cdecl asm_Recovery_CreateLargeResourceState_00425020();
#define VA_asm_Recovery_CreateLargeResourceState_00425020 0x00425020
extern "C" HintCreateView* __cdecl asm_Recovery_CreateResourceState_00419090(void);
#define VA_asm_Recovery_CreateResourceState_00419090 0x00419090
extern "C" void __cdecl asm_Recovery_CreateSmallState_0040b940();
#define VA_asm_Recovery_CreateSmallState_0040b940 0x0040b940
extern "C" void __cdecl asm_Recovery_CreateTextureFromMemory_00446eb0();
#define VA_asm_Recovery_CreateTextureFromMemory_00446eb0 0x00446eb0
extern "C" void __cdecl asm_Recovery_CreateTimerState_00422360();
#define VA_asm_Recovery_CreateTimerState_00422360 0x00422360
extern "C" void __cdecl asm_Recovery_DecayCounter_00418a00();
#define VA_asm_Recovery_DecayCounter_00418a00 0x00418a00
extern "C" void __cdecl asm_Recovery_DispatchRandomText_004479d0();
#define VA_asm_Recovery_DispatchRandomText_004479d0 0x004479d0
extern "C" void __cdecl asm_Recovery_DispatchSchedule_00428160();
#define VA_asm_Recovery_DispatchSchedule_00428160 0x00428160
extern "C" void __cdecl asm_Recovery_FindNamedValue_004198c0();
#define VA_asm_Recovery_FindNamedValue_004198c0 0x004198c0
extern "C" void __cdecl asm_Recovery_IncrementAnimationCount_004188a0();
#define VA_asm_Recovery_IncrementAnimationCount_004188a0 0x004188a0
extern "C" void __cdecl asm_Recovery_InitializeLargeState_00421f00();
#define VA_asm_Recovery_InitializeLargeState_00421f00 0x00421f00
extern "C" void __cdecl asm_Recovery_InitializeRandomTable_0042add0();
#define VA_asm_Recovery_InitializeRandomTable_0042add0 0x0042add0
extern "C" void __cdecl asm_Recovery_InitializeRandomTable_part_0042ae20();
#define VA_asm_Recovery_InitializeRandomTable_part_0042ae20 0x0042ae20
extern "C" void __cdecl asm_Recovery_InitializeSingleInterface_0044d6a0();
#define VA_asm_Recovery_InitializeSingleInterface_0044d6a0 0x0044d6a0
extern "C" void __cdecl asm_Recovery_InitializeStateTable_0041f850();
#define VA_asm_Recovery_InitializeStateTable_0041f850 0x0041f850
extern "C" void __cdecl asm_Recovery_InitializeTimedState_00423510();
#define VA_asm_Recovery_InitializeTimedState_00423510 0x00423510
extern "C" void __cdecl asm_Recovery_InitializeWordColor_00405040();
#define VA_asm_Recovery_InitializeWordColor_00405040 0x00405040
extern "C" void __cdecl asm_Recovery_InstallAnimationSlot_0042c670();
#define VA_asm_Recovery_InstallAnimationSlot_0042c670 0x0042c670
extern "C" void __cdecl asm_Recovery_InstallPairClearFlags_0041ad90();
#define VA_asm_Recovery_InstallPairClearFlags_0041ad90 0x0041ad90
extern "C" void __cdecl Bomb_RegisterTasks();
#define VA_asm_Recovery_InstallPairSetFlags_004055c0 0x004055c0
extern "C" void __cdecl asm_Recovery_LoadCachedResource_00447280();
#define VA_asm_Recovery_LoadCachedResource_00447280 0x00447280
extern "C" void __cdecl asm_Recovery_LoadStartupResources_0041f8d0();
#define VA_asm_Recovery_LoadStartupResources_0041f8d0 0x0041f8d0
extern "C" void __cdecl asm_Recovery_MarkAnimationTree_004243f0();
#define VA_asm_Recovery_MarkAnimationTree_004243f0 0x004243f0
extern "C" void __cdecl asm_Recovery_MarkLogState_00447a50();
#define VA_asm_Recovery_MarkLogState_00447a50 0x00447a50
extern "C" void __cdecl asm_Recovery_OffsetPoint_00418810();
#define VA_asm_Recovery_OffsetPoint_00418810 0x00418810
extern "C" void __cdecl asm_Recovery_PolarToVectorRetail_0044c5d0();
#define VA_asm_Recovery_PolarToVectorRetail_0044c5d0 0x0044c5d0
extern "C" void __cdecl asm_Recovery_ReleaseCompositeState_00414570();
#define VA_asm_Recovery_ReleaseCompositeState_00414570 0x00414570
extern "C" void __cdecl asm_Recovery_ReleaseGlobalStates_004203f0();
#define VA_asm_Recovery_ReleaseGlobalStates_004203f0 0x004203f0
extern "C" void __cdecl asm_Recovery_ReleasePair_0041f930();
#define VA_asm_Recovery_ReleasePair_0041f930 0x0041f930
extern "C" void __cdecl asm_Recovery_ReleaseRawPairAndReset_00405620();
#define VA_asm_Recovery_ReleaseRawPairAndReset_00405620 0x00405620
extern "C" void __cdecl asm_Recovery_ReleaseRawPair_0043cb00();
#define VA_asm_Recovery_ReleaseRawPair_0043cb00 0x0043cb00
extern "C" void __cdecl asm_Recovery_ReplaceExtensionWav_00420a90();
#define VA_asm_Recovery_ReplaceExtensionWav_00420a90 0x00420a90
extern "C" void __cdecl asm_Recovery_ResetDeviceStreams_0043bc40();
#define VA_asm_Recovery_ResetDeviceStreams_0043bc40 0x0043bc40
extern "C" void __cdecl asm_Recovery_ResetEmitter_0040c9a0();
#define VA_asm_Recovery_ResetEmitter_0040c9a0 0x0040c9a0
extern "C" void __cdecl asm_Recovery_ScaleColor_00404da0();
#define VA_asm_Recovery_ScaleColor_00404da0 0x00404da0
extern "C" void __cdecl asm_Recovery_SelectArchiveEntry_0043d790();
#define VA_asm_Recovery_SelectArchiveEntry_0043d790 0x0043d790
extern "C" void __cdecl asm_Recovery_SplitResourcePath_0041a050();
#define VA_asm_Recovery_SplitResourcePath_0041a050 0x0041a050
extern "C" void __cdecl asm_Recovery_StartWorker_0041fac0();
#define VA_asm_Recovery_StartWorker_0041fac0 0x0041fac0
extern "C" void __cdecl asm_Recovery_SwitchPlaybackState_00427ae0();
#define VA_asm_Recovery_SwitchPlaybackState_00427ae0 0x00427ae0
extern "C" void __cdecl asm_Recovery_TickState_0040bd20();
#define VA_asm_Recovery_TickState_0040bd20 0x0040bd20
extern "C" void __cdecl asm_Recovery_TrimWhitespace_0041a0a0();
#define VA_asm_Recovery_TrimWhitespace_0041a0a0 0x0041a0a0
extern "C" void __cdecl asm_Recovery_TrimWhitespace_part_0041a0e0();
#define VA_asm_Recovery_TrimWhitespace_part_0041a0e0 0x0041a0e0
extern "C" void __cdecl asm_Recovery_UpdateEmitterDecision_0040b9f0();
#define VA_asm_Recovery_UpdateEmitterDecision_0040b9f0 0x0040b9f0
extern "C" void __cdecl asm_Recovery_UpdateStageSequence_004281d0();
#define VA_asm_Recovery_UpdateStageSequence_004281d0 0x004281d0
extern "C" void __cdecl asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_004091c0();
#define VA_asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_004091c0 0x004091c0
extern "C" void __cdecl asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_part_004091e0();
#define VA_asm_ReleaseFlaggedEntityArrays_ScoreRuntimeState_part_004091e0 0x004091e0
extern "C" void __cdecl asm_Reserve_LegacyString_00438380();
#define VA_asm_Reserve_LegacyString_00438380 0x00438380
extern "C" void __cdecl asm_Resource_FindChunk_0043d250();
#define VA_asm_Resource_FindChunk_0043d250 0x0043d250
extern "C" void __cdecl asm_Resource_GetFileSizeRetail_004358e0();
#define VA_asm_Resource_GetFileSizeRetail_004358e0 0x004358e0
extern "C" void __cdecl asm_Retire_ScoreRuntimeCallbacks_00409e20();
#define VA_asm_Retire_ScoreRuntimeCallbacks_00409e20 0x00409e20
extern "C" void __cdecl asm_Rng_NextFloatSigned_0044bb90();
#define VA_asm_Rng_NextFloatSigned_0044bb90 0x0044bb90
extern "C" void __cdecl asm_Rng_NextFloat_0044bb20();
#define VA_asm_Rng_NextFloat_0044bb20 0x0044bb20
extern "C" void __cdecl asm_Rng_NextU32_0044b9e0();
#define VA_asm_Rng_NextU32_0044b9e0 0x0044b9e0
extern "C" void __cdecl asm_RoundMan_0045d349();
#define VA_asm_RoundMan_0045d349 0x0045d349
extern "C" void __cdecl asm_RtlUnwind_0046263a();
#define VA_asm_RtlUnwind_0046263a 0x0046263a
extern "C" void __cdecl asm_SEH_epilog_00454bf7();
#define VA_asm_SEH_epilog_00454bf7 0x00454bf7
extern "C" void __cdecl asm_SEH_prolog_00454bbc();
#define VA_asm_SEH_prolog_00454bbc 0x00454bbc
extern "C" void __cdecl asm_SaveSystemSettingsRetail_004392e0();
#define VA_asm_SaveSystemSettingsRetail_004392e0 0x004392e0
extern "C" SchedulerTask* __stdcall asm_SchedulerCallback_Create_00449ed0(
    void* callback);
#define VA_asm_SchedulerCallback_Create_00449ed0 0x00449ed0
extern "C" void __cdecl asm_Scheduler_CreateAndRegisterSecondary_0044a030();
#define VA_asm_Scheduler_CreateAndRegisterSecondary_0044a030 0x0044a030
extern "C" void __cdecl asm_Scheduler_CreateAndRegister_0044a000();
#define VA_asm_Scheduler_CreateAndRegister_0044a000 0x0044a000
extern "C" void __cdecl asm_Scheduler_RegisterPrimary_00449ae0();
#define VA_asm_Scheduler_RegisterPrimary_00449ae0 0x00449ae0
extern "C" void __cdecl asm_Scheduler_RegisterSecondary_00449b70();
#define VA_asm_Scheduler_RegisterSecondary_00449b70 0x00449b70
extern "C" void __cdecl asm_Scheduler_Remove_00449f60();
#define VA_asm_Scheduler_Remove_00449f60 0x00449f60
extern "C" void __cdecl LaserManager_RegisterTasks();
#define VA_LaserManager_RegisterTasks 0x0041c120
extern "C" void __cdecl asm_LaserManager_Destroy_0041c1c0();
#define VA_asm_LaserManager_Destroy_0041c1c0 0x0041c1c0
extern "C" void __cdecl asm_ScoreExtendedObject_Initialize_0041c5b0();
#define VA_asm_ScoreExtendedObject_Initialize_0041c5b0 0x0041c5b0
extern "C" void __cdecl asm_ScoreFile_InitializeDefaultsRetail_0042acb0();
#define VA_asm_ScoreFile_InitializeDefaultsRetail_0042acb0 0x0042acb0
extern "C" void __cdecl asm_ScoreFile_InitializeDefaultsRetail_part_0042acf0();
#define VA_asm_ScoreFile_InitializeDefaultsRetail_part_0042acf0 0x0042acf0
extern "C" void __cdecl asm_ScoreFile_InitializeDefaultsRetail_part_0042ad50();
#define VA_asm_ScoreFile_InitializeDefaultsRetail_part_0042ad50 0x0042ad50
extern "C" void __cdecl asm_ScoreGauge_AddWithMinimum_00412e70();
#define VA_asm_ScoreGauge_AddWithMinimum_00412e70 0x00412e70
extern "C" void __cdecl asm_ScoreGauge_SetTargetTenthAndDisableTimer_00418b80();
#define VA_asm_ScoreGauge_SetTargetTenthAndDisableTimer_00418b80 0x00418b80
extern "C" void __cdecl asm_ScoreList_InsertAfter_00413200();
#define VA_asm_ScoreList_InsertAfter_00413200 0x00413200
extern "C" void * __cdecl LaserManager_Create(void);
#define VA_LaserManager_Create 0x0041c290
extern "C" void __cdecl asm_Laser_Construct_0041c030();
#define VA_asm_Laser_Construct_0041c030 0x0041c030
extern "C" void __cdecl asm_ScoreOwnedObject_Destroy_0040b9d0();
#define VA_asm_ScoreOwnedObject_Destroy_0040b9d0 0x0040b9d0
extern "C" void __cdecl asm_ScoreRecords_CopyVectorAndEvaluate_0041c800();
#define VA_asm_ScoreRecords_CopyVectorAndEvaluate_0041c800 0x0041c800
extern "C" void __cdecl asm_ScoreRecords_MarkEligible_0041c7d0();
#define VA_asm_ScoreRecords_MarkEligible_0041c7d0 0x0041c7d0
extern "C" void __cdecl asm_ScoreState_ActivateFromResultRetail_00408030();
#define VA_asm_ScoreState_ActivateFromResultRetail_00408030 0x00408030
extern "C" void __cdecl asm_Score_IncrementCounterClampedNine_00418a90();
#define VA_asm_Score_IncrementCounterClampedNine_00418a90 0x00418a90
extern "C" void __cdecl asm_Score_InputHistorySave_0044be20();
#define VA_asm_Score_InputHistorySave_0044be20 0x0044be20
extern "C" void __cdecl asm_Score_InputHistoryStep_0044be70();
#define VA_asm_Score_InputHistoryStep_0044be70 0x0044be70
extern "C" void __cdecl asm_Score_SetMode_00412ed0();
#define VA_asm_Score_SetMode_00412ed0 0x00412ed0
extern "C" void __cdecl asm_Score_SetNormalizedAngle_00413170();
#define VA_asm_Score_SetNormalizedAngle_00413170 0x00413170
extern "C" void __cdecl asm_Score_SetPolarVector_00408750();
#define VA_asm_Score_SetPolarVector_00408750 0x00408750
extern "C" void __cdecl asm_SetInputMode_0040ac90();
#define VA_asm_SetInputMode_0040ac90 0x0040ac90
extern "C" void __cdecl asm_SetLength_LegacyString_00438590();
#define VA_asm_SetLength_LegacyString_00438590 0x00438590
extern "C" void __cdecl asm_SetPolar_Vector2_0041f800();
#define VA_asm_SetPolar_Vector2_0041f800 0x0041f800
extern "C" void __cdecl asm_ShrMan_0045d3fb();
#define VA_asm_ShrMan_0045d3fb 0x0045d3fb
extern "C" void __cdecl asm_SlotLockTable_LeaveRetail_00421c50();
#define VA_asm_SlotLockTable_LeaveRetail_00421c50 0x00421c50
extern "C" void __cdecl asm_SoundBuffer_DestructBaseRetail_0044d730();
#define VA_asm_SoundBuffer_DestructBaseRetail_0044d730 0x0044d730
extern "C" void __cdecl asm_SoundStream_Start_0044d440();
#define VA_asm_SoundStream_Start_0044d440 0x0044d440
extern "C" void __cdecl asm_Sound_ForwardFloatAsDouble_00427c50();
#define VA_asm_Sound_ForwardFloatAsDouble_00427c50 0x00427c50
extern "C" void __cdecl asm_Sound_PlayDummyRetail_00420b10();
#define VA_asm_Sound_PlayDummyRetail_00420b10 0x00420b10
extern "C" void __cdecl asm_Sound_PlayRandomVoiceRetail_00420c30();
#define VA_asm_Sound_PlayRandomVoiceRetail_00420c30 0x00420c30
extern "C" void __cdecl asm_StageBackground_RebindTextureRetail_0040c3c0();
#define VA_asm_StageBackground_RebindTextureRetail_0040c3c0 0x0040c3c0
extern "C" void __cdecl asm_StageManager_CreateRetail_004296f0();
#define VA_asm_StageManager_CreateRetail_004296f0 0x004296f0
extern "C" void __cdecl asm_StageText_ExtractLine_00434a20();
#define VA_asm_StageText_ExtractLine_00434a20 0x00434a20
extern "C" void __cdecl asm_StageText_Initialize_00434a80();
#define VA_asm_StageText_Initialize_00434a80 0x00434a80
extern "C" void __cdecl asm_StageText_SkipLine_004349e0();
#define VA_asm_StageText_SkipLine_004349e0 0x004349e0
extern "C" void __cdecl asm_StageTipManager_Construct_00418d40();
#define VA_asm_StageTipManager_Construct_00418d40 0x00418d40
extern "C" void __cdecl asm_StageTipRuntime_InitializeRetail_00418e30();
#define VA_asm_StageTipRuntime_InitializeRetail_00418e30 0x00418e30
extern "C" void __cdecl asm_StageTip_CreateRetail_0041a120();
#define VA_asm_StageTip_CreateRetail_0041a120 0x0041a120
extern "C" void __cdecl asm_StageTip_CreateUrgent_00424650();
#define VA_asm_StageTip_CreateUrgent_00424650 0x00424650
extern "C" void __cdecl asm_StageTip_Initialize_00418d00();
#define VA_asm_StageTip_Initialize_00418d00 0x00418d00
extern "C" void __cdecl asm_Streamer_FillBufferRetail_0044d110();
#define VA_asm_Streamer_FillBufferRetail_0044d110 0x0044d110
extern "C" void __cdecl asm_Streamer_RestartRetail_0044dad0();
#define VA_asm_Streamer_RestartRetail_0044dad0 0x0044dad0
extern "C" unsigned int __cdecl asm_Strftime_0045afe0(char* output, unsigned int capacity, const char* format, const void* time, void* locale_data);
#define VA_asm_Strftime_0045afe0 0x0045afe0
extern "C" void __cdecl asm_TextLog_AppendLine_0044b8e0();
#define VA_asm_TextLog_AppendLine_0044b8e0 0x0044b8e0
extern "C" void __cdecl asm_TextLog_Append_0044b810();
#define VA_asm_TextLog_Append_0044b810 0x0044b810
extern "C" void __cdecl asm_TimerWin32_Release_004203c0();
#define VA_asm_TimerWin32_Release_004203c0 0x004203c0
extern "C" void __cdecl asm_Title_RegisterTasksRetail_0042caa0();
#define VA_asm_Title_RegisterTasksRetail_0042caa0 0x0042caa0
extern "C" int __cdecl asm_TranslateName_0045c2fd(NameEntry* entries, int high, const char** key);
#define VA_asm_TranslateName_0045c2fd 0x0045c2fd
extern "C" void __cdecl asm_TranslatorGuardHandler_part_0046296e();
#define VA_asm_TranslatorGuardHandler_part_0046296e 0x0046296e
extern "C" void __cdecl asm_TypeMatch_00462e11();
#define VA_asm_TypeMatch_00462e11 0x00462e11
extern "C" void __cdecl asm_UnwindNestedFrames_0046271b();
#define VA_asm_UnwindNestedFrames_0046271b 0x0046271b
extern "C" void __cdecl asm_UpdateInputState_0040ac20();
#define VA_asm_UpdateInputState_0040ac20 0x0040ac20
extern "C" void __cdecl asm_UpdatePlayer_00405750();
#define VA_asm_UpdatePlayer_00405750 0x00405750
extern "C" void __cdecl asm_ValidateEH3RN_0045998a();
#define VA_asm_ValidateEH3RN_0045998a 0x0045998a
extern "C" int __cdecl asm_ValidateExecute_00463b02(const void* ptr);
#define VA_asm_ValidateExecute_00463b02 0x00463b02
extern "C" int __cdecl asm_ValidateRead_00463aca(const void* ptr, unsigned int size);
#define VA_asm_ValidateRead_00463aca 0x00463aca
extern "C" int __cdecl asm_ValidateWrite_00463ae6(void* ptr, unsigned int size);
#define VA_asm_ValidateWrite_00463ae6 0x00463ae6
extern "C" void __cdecl asm_Vec_Subtract_00404d40();
#define VA_asm_Vec_Subtract_00404d40 0x00404d40
extern "C" void __cdecl asm_Vector2_SetAnimationPolar_00441ef0();
#define VA_asm_Vector2_SetAnimationPolar_00441ef0 0x00441ef0
extern "C" void __cdecl asm_Vector2_SetEllipticPolar_00413270();
#define VA_asm_Vector2_SetEllipticPolar_00413270 0x00413270
extern "C" void __cdecl asm_Vector2_SetPolar_004458b0();
#define VA_asm_Vector2_SetPolar_004458b0 0x004458b0
extern "C" void __cdecl asm_Viewport_ApplyDefaultRetail_0043bcd0();
#define VA_asm_Viewport_ApplyDefaultRetail_0043bcd0 0x0043bcd0
extern "C" void __cdecl asm_WINNLSEnableIME_0045232c();
#define VA_asm_WINNLSEnableIME_0045232c 0x0045232c
extern "C" void __cdecl asm_WrappedAngleDifference_00408660();
#define VA_asm_WrappedAngleDifference_00408660 0x00408660
extern "C" void __cdecl asm_XcptFilter_004577ce();
#define VA_asm_XcptFilter_004577ce 0x004577ce
extern "C" int __cdecl asm_ZeroTail_0045d2ca(const unsigned int* words, int bits);
#define VA_asm_ZeroTail_0045d2ca 0x0045d2ca
extern "C" void __cdecl asm_abnormal_termination_00459946();
#define VA_asm_abnormal_termination_00459946 0x00459946
extern "C" void __cdecl asm_abort_0045a245();
#define VA_asm_abort_0045a245 0x0045a245
extern "C" void __cdecl asm_abstract_cw_00460ee4();
#define VA_asm_abstract_cw_00460ee4 0x00460ee4
extern "C" void __cdecl asm_add_12_004607b9(unsigned int* destination, const unsigned int* source);
#define VA_asm_add_12_004607b9 0x004607b9
extern "C" int __cdecl asm_addl_00460798(unsigned int left, unsigned int right, unsigned int* sum_out);
#define VA_asm_addl_00460798 0x00460798
extern "C" void __cdecl asm_allmul_00456640();
#define VA_asm_allmul_00456640 0x00456640
extern "C" void __cdecl asm_amsg_exit_0045373d();
#define VA_asm_amsg_exit_0045373d 0x0045373d
extern "C" void __cdecl asm_ascii_stricmp_004603d0();
#define VA_asm_ascii_stricmp_004603d0 0x004603d0
extern "C" void __cdecl asm_ascii_strnicmp_004617e0();
#define VA_asm_ascii_strnicmp_004617e0 0x004617e0
extern "C" int __cdecl asm_atexit_00452e0a(void* callback);
#define VA_asm_atexit_00452e0a 0x00452e0a
extern "C" double __cdecl asm_atof_00452a84(const char* input);
#define VA_asm_atof_00452a84 0x00452a84
extern "C" void __cdecl asm_atol_004527ee();
#define VA_asm_atol_004527ee 0x004527ee
extern "C" long __cdecl asm_atol_00452876(const char* text);
#define VA_asm_atol_00452876 0x00452876
extern "C" void __cdecl asm_aulldiv_00456b80();
#define VA_asm_aulldiv_00456b80 0x00456b80
extern "C" void __cdecl asm_aulldvrm_0045a1b0();
#define VA_asm_aulldvrm_0045a1b0 0x0045a1b0
extern "C" void __cdecl asm_basic_string_char_std_char_traits_char_std_allocator_char_00462301();
#define VA_asm_basic_string_char_std_char_traits_char_std_allocator_char_00462301 0x00462301
extern "C" void __cdecl asm_beginthread_00452eec();
#define VA_asm_beginthread_00452eec 0x00452eec
extern "C" void __cdecl asm_beginthreadex_00453683();
#define VA_asm_beginthreadex_00453683 0x00453683
extern "C" int __cdecl asm_callnewh_00455737(unsigned int size);
#define VA_asm_callnewh_00455737 0x00455737
extern "C" void __cdecl asm_cexit_0045770e();
#define VA_asm_cexit_0045770e 0x0045770e
extern "C" void __cdecl asm_cftoe2_0045dcd7();
#define VA_asm_cftoe2_0045dcd7 0x0045dcd7
extern "C" void __cdecl asm_cftof2_0045ddf5();
#define VA_asm_cftof2_0045ddf5 0x0045ddf5
extern "C" void __cdecl asm_chkstk_00458ec0();
#define VA_asm_chkstk_00458ec0 0x00458ec0
extern "C" int __cdecl asm_cinit_004575bf(int argument);
#define VA_asm_cinit_004575bf 0x004575bf
extern "C" void __cdecl asm_cintrindisp2_00463cc0();
#define VA_asm_cintrindisp2_00463cc0 0x00463cc0
extern "C" void __cdecl asm_close_0046218a();
#define VA_asm_close_0046218a 0x0046218a
extern "C" void __cdecl asm_close_lk_00462107();
#define VA_asm_close_lk_00462107 0x00462107
extern "C" void __cdecl asm_close_part_00462209();
#define VA_asm_close_part_00462209 0x00462209
extern "C" void __cdecl asm_clrfp_0045ed7b();
#define VA_asm_clrfp_0045ed7b 0x0045ed7b
extern "C" void __cdecl asm_commit_004614a9();
#define VA_asm_commit_004614a9 0x004614a9
extern "C" void __cdecl asm_commit_part_00461551();
#define VA_asm_commit_part_00461551 0x00461551
extern "C" unsigned int __cdecl asm_control87_0046105e(
    unsigned int new_value, unsigned int mask);
#define VA_asm_control87_0046105e 0x0046105e
extern "C" unsigned int __cdecl asm_controlfp_00461090(unsigned int new_value, unsigned int mask);
#define VA_asm_controlfp_00461090 0x00461090
extern "C" void __cdecl asm_copy_environ_00461ed0();
#define VA_asm_copy_environ_00461ed0 0x00461ed0
extern "C" void __cdecl asm_crtExitProcess_00457547();
#define VA_asm_crtExitProcess_00457547 0x00457547
extern "C" void __cdecl asm_crtGetEnvironmentStringsA_0045940a();
#define VA_asm_crtGetEnvironmentStringsA_0045940a 0x0045940a
extern "C" int __cdecl asm_crtGetLocaleInfoA_00461695(
    unsigned int locale_id,
    unsigned int locale_type,
    char* data,
    int capacity,
    int code_page);
#define VA_asm_crtGetLocaleInfoA_00461695 0x00461695
extern "C" void __cdecl asm_crtGetLocaleInfoA_part_0046175b();
#define VA_asm_crtGetLocaleInfoA_part_0046175b 0x0046175b
extern "C" int __cdecl asm_crtGetLocaleInfoW_00461565(
    unsigned int locale_id,
    unsigned int locale_type,
    unsigned short* data,
    int capacity,
    int code_page);
#define VA_asm_crtGetLocaleInfoW_00461565 0x00461565
extern "C" void __cdecl asm_crtGetLocaleInfoW_part_00461634();
#define VA_asm_crtGetLocaleInfoW_part_00461634 0x00461634
extern "C" int __cdecl asm_crtGetStringTypeA_0045a25d(
    unsigned int info_type,
    const char* source,
    int source_length,
    unsigned short* character_types,
    unsigned int code_page,
    unsigned int locale_id,
    int strict);
#define VA_asm_crtGetStringTypeA_0045a25d 0x0045a25d
extern "C" void __cdecl asm_crtGetStringTypeA_part_0045a34b();
#define VA_asm_crtGetStringTypeA_part_0045a34b 0x0045a34b
extern "C" void __cdecl asm_crtInitCritSecAndSpinCount_0045980e();
#define VA_asm_crtInitCritSecAndSpinCount_0045980e 0x0045980e
extern "C" void __cdecl asm_crtInitCritSecAndSpinCount_part_0045988f();
#define VA_asm_crtInitCritSecAndSpinCount_part_0045988f 0x0045988f
extern "C" void __cdecl asm_crtMessageBoxA_0045f3d0();
#define VA_asm_crtMessageBoxA_0045f3d0 0x0045f3d0
extern "C" void __cdecl asm_ctrandisp2_00463d3b();
#define VA_asm_ctrandisp2_00463d3b 0x00463d3b
extern "C" void __cdecl asm_ctrlfp_0045ed87();
#define VA_asm_ctrlfp_0045ed87 0x0045ed87
extern "C" void __cdecl asm_cvtdate_00456e90();
#define VA_asm_cvtdate_00456e90 0x00456e90
extern "C" void __cdecl asm_decomp_0045ecb4();
#define VA_asm_decomp_0045ecb4 0x0045ecb4
extern "C" void __cdecl asm_doexit_00457629();
#define VA_asm_doexit_00457629 0x00457629
extern "C" void __cdecl asm_doexit_part_004576e6();
#define VA_asm_doexit_part_004576e6 0x004576e6
extern "C" void __cdecl asm_dosmaperr_00456b04(unsigned int dos_error);
#define VA_asm_dosmaperr_00456b04 0x00456b04
extern "C" void __cdecl asm_dtold_00460d87();
#define VA_asm_dtold_00460d87 0x00460d87
extern "C" void __cdecl asm_eh_vector_constructor_iterator_0045252d();
#define VA_asm_eh_vector_constructor_iterator_0045252d 0x0045252d
extern "C" void __cdecl asm_eh_vector_destructor_iterator_004525ff();
#define VA_asm_eh_vector_destructor_iterator_004525ff 0x004525ff
extern "C" void __cdecl asm_endthread_00452e1c();
#define VA_asm_endthread_00452e1c 0x00452e1c
extern "C" void __cdecl asm_endthreadex_004535bd();
#define VA_asm_endthreadex_004535bd 0x004535bd
extern "C" void __cdecl asm_entry_part_004539a2();
#define VA_asm_entry_part_004539a2 0x004539a2
extern "C" void __cdecl asm_errcode_0045e8b4();
#define VA_asm_errcode_0045e8b4 0x0045e8b4
extern "C" void __cdecl asm_exception_00462c01();
#define VA_asm_exception_00462c01 0x00462c01
extern "C" void __cdecl asm_exception_00462cac();
#define VA_asm_exception_00462cac 0x00462cac
extern "C" void __cdecl asm_exit_004576ec(int code);
#define VA_asm_exit_004576ec 0x004576ec
extern "C" void __cdecl asm_exit_004576fd(int code);
#define VA_asm_exit_004576fd 0x004576fd
extern "C" void __cdecl asm_expandtime_0045a82d();
#define VA_asm_expandtime_0045a82d 0x0045a82d
extern "C" __declspec(noreturn) void __cdecl fast_error_exit_00453762(int errorCode);
#define VA_fast_error_exit_00453762 0x00453762
extern "C" int __cdecl asm_fclose_lk_0046140c(File* file);
#define VA_asm_fclose_lk_0046140c 0x0046140c
extern "C" int __cdecl asm_fflush_lk_0045fc53(File* file);
#define VA_asm_fflush_lk_0045fc53 0x0045fc53
extern "C" void __cdecl asm_filbuf_0045e123();
#define VA_asm_filbuf_0045e123 0x0045e123
extern "C" void __cdecl asm_findenv_00461e83();
#define VA_asm_findenv_00461e83 0x00461e83
extern "C" void __cdecl asm_fload_00463f04();
#define VA_asm_fload_00463f04 0x00463f04
extern "C" double __cdecl asm_floor_default_00458c39(double value);
#define VA_asm_floor_default_00458c39 0x00458c39
extern "C" void __cdecl asm_flsall_0045fc81();
#define VA_asm_flsall_0045fc81 0x0045fc81
extern "C" void __cdecl asm_flsall_part_0045fd32();
#define VA_asm_flsall_part_0045fd32 0x0045fd32
extern "C" void __cdecl asm_flsbuf_00454d11();
#define VA_asm_flsbuf_00454d11 0x00454d11
extern "C" int __cdecl asm_flush_0045fbf6(File* file);
#define VA_asm_flush_0045fbf6 0x0045fbf6
extern "C" void __cdecl asm_flushall_0045fda6();
#define VA_asm_flushall_0045fda6 0x0045fda6
extern "C" void __cdecl asm_fpmath_00456ad4(int set_default_precision);
#define VA_asm_fpmath_00456ad4 0x00456ad4
extern "C" void __cdecl asm_fptostr_00460d10();
#define VA_asm_fptostr_00460d10 0x00460d10
extern "C" void __cdecl asm_free_00452422(void* memory);
#define VA_asm_free_00452422 0x00452422
extern "C" void __cdecl asm_free_004524a1(void* memory);
#define VA_asm_free_004524a1 0x004524a1
extern "C" void __cdecl asm_free_lc_time_0045b39a();
#define VA_asm_free_lc_time_0045b39a 0x0045b39a
extern "C" void __cdecl asm_free_lconv_mon_0045b81b();
#define VA_asm_free_lconv_mon_0045b81b 0x0045b81b
extern "C" void __cdecl asm_free_lconv_num_0045b5bc(void** values);
#define VA_asm_free_lconv_num_0045b5bc 0x0045b5bc
extern "C" void __cdecl asm_free_osfhnd_0045f655();
#define VA_asm_free_osfhnd_0045f655 0x0045f655
extern "C" void __cdecl asm_free_part_0045247e();
#define VA_asm_free_part_0045247e 0x0045247e
extern "C" void __cdecl asm_freebuf_00462225(Stream* stream);
#define VA_asm_freebuf_00462225 0x00462225
extern "C" void __cdecl asm_freefls_4_004563c8();
#define VA_asm_freefls_4_004563c8 0x004563c8
extern "C" void __cdecl asm_freeptd_0045650f(void* data);
#define VA_asm_freeptd_0045650f 0x0045650f
extern "C" void __cdecl asm_freetlocinfo_004557fc(void* locale_info);
#define VA_asm_freetlocinfo_004557fc 0x004557fc
extern "C" void __cdecl asm_frnd_0045ebba();
#define VA_asm_frnd_0045ebba 0x0045ebba
extern "C" void __cdecl asm_get_lc_time_0045b033();
#define VA_asm_get_lc_time_0045b033 0x0045b033
extern "C" int __cdecl asm_get_osfhandle_0045f6d4(int file);
#define VA_asm_get_osfhandle_0045f6d4 0x0045f6d4
extern "C" void __cdecl asm_get_qualified_locale_0045ca50();
#define VA_asm_get_qualified_locale_0045ca50 0x0045ca50
extern "C" void __cdecl asm_getbuf_00459f39(Stream* stream);
#define VA_asm_getbuf_00459f39 0x00459f39
extern "C" void __cdecl asm_getenv_lk_0045e063();
#define VA_asm_getenv_lk_0045e063 0x0045e063
extern "C" ThreadData* __cdecl asm_getptd_00456357();
#define VA_asm_getptd_00456357 0x00456357
extern "C" void __cdecl asm_global_unwind2_0045989c();
#define VA_asm_global_unwind2_0045989c 0x0045989c
extern "C" void __cdecl asm_gmtime_0045728e();
#define VA_asm_gmtime_0045728e 0x0045728e
extern "C" void __cdecl asm_handle_exc_0045e648();
#define VA_asm_handle_exc_0045e648 0x0045e648
extern "C" void __cdecl asm_handle_qnan1_0045e97f();
#define VA_asm_handle_qnan1_0045e97f 0x0045e97f
extern "C" void __cdecl asm_heap_alloc_0045265f();
#define VA_asm_heap_alloc_0045265f 0x0045265f
extern "C" int __cdecl asm_heap_init_004539cb(int flag);
#define VA_asm_heap_init_004539cb 0x004539cb
extern "C" int __cdecl asm_heap_select_004539b1();
#define VA_asm_heap_select_004539b1 0x004539b1
extern "C" void __cdecl asm_hw_cw_00460f76();
#define VA_asm_hw_cw_00460f76 0x00460f76
extern "C" char* __cdecl asm_i64toa_0046074c(long long value, char* buffer, int radix);
#define VA_asm_i64toa_0046074c 0x0046074c
extern "C" void __cdecl asm_inc_00457a3c();
#define VA_asm_inc_00457a3c 0x00457a3c
extern "C" void __cdecl asm_inconsistency_004556e0();
#define VA_asm_inconsistency_004556e0 0x004556e0
extern "C" void __cdecl asm_inconsistency_part_00455708();
#define VA_asm_inconsistency_part_00455708 0x00455708
extern "C" int __cdecl asm_initmbctable_0045d2ac();
#define VA_asm_initmbctable_0045d2ac 0x0045d2ac
extern "C" void __cdecl asm_initptd_00456344(void* thread_data, void* locale);
#define VA_asm_initptd_00456344 0x00456344
extern "C" void __cdecl asm_initterm_00457589();
#define VA_asm_initterm_00457589 0x00457589
extern "C" void __cdecl asm_ioinit_0045952c();
#define VA_asm_ioinit_0045952c 0x0045952c
extern "C" int __cdecl asm_isatty_00459f7d(int handle);
#define VA_asm_isatty_00459f7d 0x00459f7d
extern "C" void __cdecl asm_isctype_mt_00455752();
#define VA_asm_isctype_mt_00455752 0x00455752
extern "C" int __cdecl asm_isdigit_0045685e(int c);
#define VA_asm_isdigit_0045685e 0x0045685e
extern "C" void __cdecl asm_isindst_00457250();
#define VA_asm_isindst_00457250 0x00457250
extern "C" void __cdecl asm_isindst_lk_00457048();
#define VA_asm_isindst_lk_00457048 0x00457048
extern "C" int __cdecl asm_ismbblead_0045f590(unsigned int character);
#define VA_asm_ismbblead_0045f590 0x0045f590
extern "C" int __cdecl asm_isspace_004568d7(int c);
#define VA_asm_isspace_004568d7 0x004568d7
extern "C" int __cdecl asm_isxdigit_00456898(int c);
#define VA_asm_isxdigit_00456898 0x00456898
extern "C" void __cdecl asm_itoa_00460674();
#define VA_asm_itoa_00460674 0x00460674
extern "C" void __cdecl asm_lc_lctostr_00455a90(char* output, const char* locale);
#define VA_asm_lc_lctostr_00455a90 0x00455a90
extern "C" void __cdecl asm_lc_strtolc_004559b4();
#define VA_asm_lc_strtolc_004559b4 0x004559b4
extern "C" void __cdecl asm_ld12cvt_0045d476();
#define VA_asm_ld12cvt_0045d476 0x0045d476
extern "C" void __cdecl asm_ld12told_0045d5fa();
#define VA_asm_ld12told_0045d5fa 0x0045d5fa
extern "C" void __cdecl asm_local_unwind2_004598de();
#define VA_asm_local_unwind2_004598de 0x004598de
extern "C" void __cdecl asm_localtime_00452baa();
#define VA_asm_localtime_00452baa 0x00452baa
extern "C" void __cdecl asm_lock_00453c0c(int number);
#define VA_asm_lock_00453c0c 0x00453c0c
extern "C" void __cdecl asm_lock_fhandle_0045f715(int fd);
#define VA_asm_lock_fhandle_0045f715 0x0045f715
extern "C" void __cdecl asm_lock_file2_0045a099(int number, void* file);
#define VA_asm_lock_file2_0045a099 0x0045a099
extern "C" void __cdecl asm_lseek_00459c27();
#define VA_asm_lseek_00459c27 0x00459c27
extern "C" void __cdecl asm_lseek_lk_00459bb3();
#define VA_asm_lseek_lk_00459bb3 0x00459bb3
extern "C" void __cdecl asm_lseek_part_00459cb6();
#define VA_asm_lseek_part_00459cb6 0x00459cb6
extern "C" void __cdecl asm_lseeki64_lk_0045fa1a();
#define VA_asm_lseeki64_lk_0045fa1a 0x0045fa1a
extern "C" char* __cdecl asm_ltoa_0046069e(long value, char* destination, int radix);
#define VA_asm_ltoa_0046069e 0x0046069e
extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);
#define VA_asm_malloc_00452706 0x00452706
extern "C" void __cdecl asm_math_exit_00464fab();
#define VA_asm_math_exit_00464fab 0x00464fab
extern "C" void __cdecl asm_mbctoupper_00458d0c();
#define VA_asm_mbctoupper_00458d0c 0x00458d0c
extern "C" int __cdecl asm_mbsnbicoll_004610a6(const unsigned char* first, const unsigned char* second, unsigned int count);
#define VA_asm_mbsnbicoll_004610a6 0x004610a6
extern "C" int __cdecl asm_mbtowc_0045e375(unsigned short* destination, const char* source, unsigned int size);
#define VA_asm_mbtowc_0045e375 0x0045e375
extern "C" void __cdecl asm_mbtowc_mt_0045e2b5();
#define VA_asm_mbtowc_mt_0045e2b5 0x0045e2b5
extern "C" void __cdecl asm_memcmp_0045cc10();
#define VA_asm_memcmp_0045cc10 0x0045cc10
extern "C" void __cdecl asm_memcpy_0045bfc0();
#define VA_asm_memcpy_0045bfc0 0x0045bfc0
extern "C" void __cdecl asm_memcpy_part_0045c01c();
#define VA_asm_memcpy_part_0045c01c 0x0045c01c
extern "C" void __cdecl asm_memcpy_part_0045c15c();
#define VA_asm_memcpy_part_0045c15c 0x0045c15c
extern "C" void __cdecl asm_memcpy_part_0045c184();
#define VA_asm_memcpy_part_0045c184 0x0045c184
extern "C" void __cdecl asm_memcpy_part_0045c190();
#define VA_asm_memcpy_part_0045c190 0x0045c190
extern "C" void __cdecl asm_memmove_00453280();
#define VA_asm_memmove_00453280 0x00453280
extern "C" void __cdecl asm_memmove_part_004532dc();
#define VA_asm_memmove_part_004532dc 0x004532dc
extern "C" void __cdecl asm_memmove_part_0045341c();
#define VA_asm_memmove_part_0045341c 0x0045341c
extern "C" void __cdecl asm_memmove_part_00453444();
#define VA_asm_memmove_part_00453444 0x00453444
extern "C" void __cdecl asm_memmove_part_00453450();
#define VA_asm_memmove_part_00453450 0x00453450
extern "C" void __cdecl asm_memset_0045bed0();
#define VA_asm_memset_0045bed0 0x0045bed0
extern "C" void __cdecl asm_ms_p5_mp_test_fdiv_0045e03a();
#define VA_asm_ms_p5_mp_test_fdiv_0045e03a 0x0045e03a
extern "C" void __cdecl asm_ms_p5_test_fdiv_0045dffa();
#define VA_asm_ms_p5_test_fdiv_0045dffa 0x0045dffa
extern "C" void __cdecl asm_msize_0045772c();
#define VA_asm_msize_0045772c 0x0045772c
extern "C" void __cdecl asm_mtdeletelocks_00453aea();
#define VA_asm_mtdeletelocks_00453aea 0x00453aea
extern "C" int __cdecl asm_mtinit_0045654a();
#define VA_asm_mtinit_0045654a 0x0045654a
extern "C" void __cdecl asm_mtinitlocknum_00453b6c();
#define VA_asm_mtinitlocknum_00453b6c 0x00453b6c
extern "C" int __cdecl asm_mtinitlocks_00453aa1();
#define VA_asm_mtinitlocks_00453aa1 0x00453aa1
extern "C" void __cdecl asm_mtterm_00456327();
#define VA_asm_mtterm_00456327 0x00456327
extern "C" void* __cdecl asm_nh_malloc_004526da(unsigned int size, int retry);
#define VA_asm_nh_malloc_004526da 0x004526da
extern "C" void __cdecl asm_onexit_00452dd2();
#define VA_asm_onexit_00452dd2 0x00452dd2
extern "C" void __cdecl asm_onexit_lk_00452d2a();
#define VA_asm_onexit_lk_00452d2a 0x00452d2a
extern "C" void* __cdecl asm_operator_new_00452493(unsigned int size);
#define VA_asm_operator_new_00452493 0x00452493
extern "C" void __cdecl asm_parse_cmdline_004591fc();
#define VA_asm_parse_cmdline_004591fc 0x004591fc
extern "C" int __cdecl asm_raise_00460028(int signal_number);
#define VA_asm_raise_00460028 0x00460028
extern "C" void __cdecl asm_raise_exc_0045e3a3();
#define VA_asm_raise_exc_0045e3a3 0x0045e3a3
extern "C" void __cdecl asm_raise_part_00460170();
#define VA_asm_raise_part_00460170 0x00460170
extern "C" int __cdecl asm_rand_0045371b();
#define VA_asm_rand_0045371b 0x0045371b
extern "C" void __cdecl asm_read_00461361();
#define VA_asm_read_00461361 0x00461361
extern "C" void __cdecl asm_read_part_004613f0();
#define VA_asm_read_part_004613f0 0x004613f0
extern "C" void __cdecl asm_report_failure_00458e74();
#define VA_asm_report_failure_00458e74 0x00458e74
extern "C" void __cdecl asm_report_failure_part_00458e98();
#define VA_asm_report_failure_part_00458e98 0x00458e98
extern "C" void __cdecl asm_resetstkoflw_00458d91();
#define VA_asm_resetstkoflw_00458d91 0x00458d91
extern "C" void __cdecl asm_sbh_alloc_block_004548be();
#define VA_asm_sbh_alloc_block_004548be 0x004548be
extern "C" void __cdecl asm_sbh_alloc_new_group_00454094();
#define VA_asm_sbh_alloc_new_group_00454094 0x00454094
extern "C" void __cdecl asm_sbh_alloc_new_region_00453fdd();
#define VA_asm_sbh_alloc_new_region_00453fdd 0x00453fdd
extern "C" CrtHeapBlock* __cdecl asm_sbh_find_block_00453c9a(unsigned int address);
#define VA_asm_sbh_find_block_00453c9a 0x00453c9a
extern "C" void __cdecl asm_sbh_free_block_00453cc5();
#define VA_asm_sbh_free_block_00453cc5 0x00453cc5
extern "C" void __cdecl asm_sbh_heap_init_00453c52();
#define VA_asm_sbh_heap_init_00453c52 0x00453c52
extern "C" void __cdecl asm_sbh_resize_block_0045419a();
#define VA_asm_sbh_resize_block_0045419a 0x0045419a
extern "C" void __cdecl asm_security_check_cookie_00458ea5();
#define VA_asm_security_check_cookie_00458ea5 0x00458ea5
extern "C" void __cdecl asm_security_init_cookie_0045f1f3(void);
#define VA_asm_security_init_cookie_0045f1f3 0x0045f1f3
extern "C" void __cdecl asm_setSBCS_0045cd85();
#define VA_asm_setSBCS_0045cd85 0x0045cd85
extern "C" void __cdecl asm_set_exp_0045ebcb();
#define VA_asm_set_exp_0045ebcb 0x0045ebcb
extern "C" void __cdecl asm_setargv_00459368();
#define VA_asm_setargv_00459368 0x00459368
extern "C" void __cdecl asm_setdefaultprecision_0045dfe8();
#define VA_asm_setdefaultprecision_0045dfe8 0x0045dfe8
extern "C" void __cdecl asm_setenvp_00459135();
#define VA_asm_setenvp_00459135 0x00459135
extern "C" void __cdecl asm_setmbcp_0045d15c();
#define VA_asm_setmbcp_0045d15c 0x0045d15c
extern "C" void __cdecl asm_shift_0045dcba();
#define VA_asm_shift_0045dcba 0x0045dcba
extern "C" void __cdecl asm_shl_12_00460817();
#define VA_asm_shl_12_00460817 0x00460817
extern "C" void __cdecl asm_shr_12_00460845();
#define VA_asm_shr_12_00460845 0x00460845
extern "C" void __cdecl asm_siglookup_0045fe47();
#define VA_asm_siglookup_0045fe47 0x0045fe47
extern "C" int __cdecl asm_sprintf_00452ae8(char* destination, const char* format, ...);
#define VA_asm_sprintf_00452ae8 0x00452ae8
extern "C" void __cdecl asm_sptype_0045ec59();
#define VA_asm_sptype_0045ec59 0x0045ec59
extern "C" int __cdecl asm_sscanf_00452fb9(char* input, const char* format, ...);
#define VA_asm_sscanf_00452fb9 0x00452fb9
extern "C" void __cdecl asm_startOneArgErrorHandling_00464eb7();
#define VA_asm_startOneArgErrorHandling_00464eb7 0x00464eb7
extern "C" void __cdecl asm_statfp_0045ed70();
#define VA_asm_statfp_0045ed70 0x0045ed70
extern "C" void __cdecl asm_store_num_0045a7b4();
#define VA_asm_store_num_0045a7b4 0x0045a7b4
extern "C" void __cdecl asm_store_str_0045a75e();
#define VA_asm_store_str_0045a75e 0x0045a75e
extern "C" void __cdecl asm_store_winword_0045aa93();
#define VA_asm_store_winword_0045aa93 0x0045aa93
extern "C" void __cdecl asm_store_winword_part_0045ab7d();
#define VA_asm_store_winword_part_0045ab7d 0x0045ab7d
extern "C" void __cdecl asm_strcats_00455990(void* destination, int count, ...);
#define VA_asm_strcats_00455990 0x00455990
extern "C" void __cdecl asm_strcmp_0045bf30();
#define VA_asm_strcmp_0045bf30 0x0045bf30
extern "C" void __cdecl asm_strcmp_part_0045bf74();
#define VA_asm_strcmp_part_0045bf74 0x0045bf74
extern "C" void __cdecl asm_strcspn_0045be80();
#define VA_asm_strcspn_0045be80 0x0045be80
extern "C" char* __cdecl asm_strdup_00462250(const char* source);
#define VA_asm_strdup_00462250 0x00462250
extern "C" int __cdecl asm_stricmp_0046054e(const unsigned char* left, const unsigned char* right);
#define VA_asm_stricmp_0046054e 0x0046054e
extern "C" void __cdecl asm_strlen_00456720();
#define VA_asm_strlen_00456720 0x00456720
extern "C" void __cdecl asm_strncmp_00452f80();
#define VA_asm_strncmp_00452f80 0x00452f80
extern "C" void __cdecl asm_strncnt_00461add();
#define VA_asm_strncnt_00461add 0x00461add
extern "C" void __cdecl asm_strncpy_00452960();
#define VA_asm_strncpy_00452960 0x00452960
extern "C" int __cdecl asm_strnicmp_004605b7(const unsigned char* left, const unsigned char* right, unsigned int count);
#define VA_asm_strnicmp_004605b7 0x004605b7
extern "C" void __cdecl asm_strpbrk_0045ccd0();
#define VA_asm_strpbrk_0045ccd0 0x0045ccd0
extern "C" void __cdecl asm_strrchr_00452930();
#define VA_asm_strrchr_00452930 0x00452930
extern "C" void __cdecl asm_target_004017a5();
#define VA_asm_target_004017a5 0x004017a5
extern "C" void __cdecl asm_target_004018a0();
#define VA_asm_target_004018a0 0x004018a0
extern "C" void __cdecl asm_target_004018b0();
#define VA_asm_target_004018b0 0x004018b0
extern "C" void __cdecl asm_target_004019ab();
#define VA_asm_target_004019ab 0x004019ab
extern "C" void __cdecl asm_target_004019bb();
#define VA_asm_target_004019bb 0x004019bb
extern "C" void __cdecl asm_target_004019c7();
#define VA_asm_target_004019c7 0x004019c7
extern "C" void __cdecl asm_target_004019e9();
#define VA_asm_target_004019e9 0x004019e9
extern "C" void __cdecl asm_target_00401a90();
#define VA_asm_target_00401a90 0x00401a90
extern "C" void __cdecl asm_target_00401b6d();
#define VA_asm_target_00401b6d 0x00401b6d
extern "C" void __cdecl asm_target_00401b77();
#define VA_asm_target_00401b77 0x00401b77
extern "C" void __cdecl asm_target_00401c15();
#define VA_asm_target_00401c15 0x00401c15
extern "C" void __cdecl asm_target_00401c37();
#define VA_asm_target_00401c37 0x00401c37
extern "C" void __cdecl asm_target_00402846();
#define VA_asm_target_00402846 0x00402846
extern "C" void __cdecl asm_target_00402a40();
#define VA_asm_target_00402a40 0x00402a40
extern "C" void __cdecl asm_target_00402baa();
#define VA_asm_target_00402baa 0x00402baa
extern "C" void __cdecl asm_target_00402c34();
#define VA_asm_target_00402c34 0x00402c34
extern "C" void __cdecl asm_target_00402e86();
#define VA_asm_target_00402e86 0x00402e86
extern "C" void __cdecl asm_target_00403841();
#define VA_asm_target_00403841 0x00403841
extern "C" void __cdecl asm_target_00403a24();
#define VA_asm_target_00403a24 0x00403a24
extern "C" void __cdecl asm_target_00403c3a();
#define VA_asm_target_00403c3a 0x00403c3a
extern "C" void __cdecl asm_target_00403c4f();
#define VA_asm_target_00403c4f 0x00403c4f
extern "C" void __cdecl asm_target_00403c64();
#define VA_asm_target_00403c64 0x00403c64
extern "C" void __cdecl asm_target_00403c75();
#define VA_asm_target_00403c75 0x00403c75
extern "C" void __cdecl asm_target_00403ca4();
#define VA_asm_target_00403ca4 0x00403ca4
extern "C" void __cdecl asm_target_00404086();
#define VA_asm_target_00404086 0x00404086
extern "C" void __cdecl asm_target_00404182();
#define VA_asm_target_00404182 0x00404182
extern "C" void __cdecl asm_target_00404251();
#define VA_asm_target_00404251 0x00404251
extern "C" void __cdecl asm_target_0040425d();
#define VA_asm_target_0040425d 0x0040425d
extern "C" void __cdecl asm_target_0040426b();
#define VA_asm_target_0040426b 0x0040426b
extern "C" void __cdecl asm_target_00404490();
#define VA_asm_target_00404490 0x00404490
extern "C" void __cdecl asm_target_004044fb();
#define VA_asm_target_004044fb 0x004044fb
extern "C" void __cdecl asm_target_00404518();
#define VA_asm_target_00404518 0x00404518
extern "C" void __cdecl asm_target_004046f0();
#define VA_asm_target_004046f0 0x004046f0
extern "C" void __cdecl asm_target_004047f2();
#define VA_asm_target_004047f2 0x004047f2
extern "C" void __cdecl asm_target_00404915();
#define VA_asm_target_00404915 0x00404915
extern "C" void __cdecl asm_target_00404a8f();
#define VA_asm_target_00404a8f 0x00404a8f
extern "C" void __cdecl asm_target_00404bfa();
#define VA_asm_target_00404bfa 0x00404bfa
extern "C" void __cdecl asm_target_00404c39();
#define VA_asm_target_00404c39 0x00404c39
extern "C" void __cdecl asm_target_0040581b();
#define VA_asm_target_0040581b 0x0040581b
extern "C" void __cdecl asm_target_00405825();
#define VA_asm_target_00405825 0x00405825
extern "C" void __cdecl asm_target_00406373();
#define VA_asm_target_00406373 0x00406373
extern "C" void __cdecl asm_target_0040643e();
#define VA_asm_target_0040643e 0x0040643e
extern "C" void __cdecl asm_target_00406519();
#define VA_asm_target_00406519 0x00406519
extern "C" void __cdecl asm_target_0040651b();
#define VA_asm_target_0040651b 0x0040651b
extern "C" void __cdecl asm_target_00406600();
#define VA_asm_target_00406600 0x00406600
extern "C" void __cdecl asm_target_00406694();
#define VA_asm_target_00406694 0x00406694
extern "C" void __cdecl asm_target_004068ac();
#define VA_asm_target_004068ac 0x004068ac
extern "C" void __cdecl asm_target_00406a7f();
#define VA_asm_target_00406a7f 0x00406a7f
extern "C" void __cdecl asm_target_00406db0();
#define VA_asm_target_00406db0 0x00406db0
extern "C" void __cdecl asm_target_00406f64();
#define VA_asm_target_00406f64 0x00406f64
extern "C" void __cdecl asm_target_0040703a();
#define VA_asm_target_0040703a 0x0040703a
extern "C" void __cdecl asm_target_00407089();
#define VA_asm_target_00407089 0x00407089
extern "C" void __cdecl asm_target_004070b2();
#define VA_asm_target_004070b2 0x004070b2
extern "C" void __cdecl asm_target_00407163();
#define VA_asm_target_00407163 0x00407163
extern "C" void __cdecl asm_target_0040724d();
#define VA_asm_target_0040724d 0x0040724d
extern "C" void __cdecl asm_target_004072f8();
#define VA_asm_target_004072f8 0x004072f8
extern "C" void __cdecl asm_target_004072ff();
#define VA_asm_target_004072ff 0x004072ff
extern "C" void __cdecl asm_target_0040731c();
#define VA_asm_target_0040731c 0x0040731c
extern "C" void __cdecl asm_target_00407323();
#define VA_asm_target_00407323 0x00407323
extern "C" void __cdecl asm_target_00407329();
#define VA_asm_target_00407329 0x00407329
extern "C" void __cdecl asm_target_00407336();
#define VA_asm_target_00407336 0x00407336
extern "C" void __cdecl asm_target_00407627();
#define VA_asm_target_00407627 0x00407627
extern "C" void __cdecl asm_target_0040783e();
#define VA_asm_target_0040783e 0x0040783e
extern "C" void __cdecl asm_target_0040799b();
#define VA_asm_target_0040799b 0x0040799b
extern "C" void __cdecl asm_target_00407b4b();
#define VA_asm_target_00407b4b 0x00407b4b
extern "C" void __cdecl asm_target_00407d9d();
#define VA_asm_target_00407d9d 0x00407d9d
extern "C" void __cdecl asm_target_00407eeb();
#define VA_asm_target_00407eeb 0x00407eeb
extern "C" void __cdecl asm_target_00407fbc();
#define VA_asm_target_00407fbc 0x00407fbc
extern "C" void __cdecl asm_target_00408110();
#define VA_asm_target_00408110 0x00408110
extern "C" void __cdecl asm_target_004081ec();
#define VA_asm_target_004081ec 0x004081ec
extern "C" void __cdecl asm_target_0040843a();
#define VA_asm_target_0040843a 0x0040843a
extern "C" void __cdecl asm_target_004084c0();
#define VA_asm_target_004084c0 0x004084c0
extern "C" void __cdecl asm_target_004085f9();
#define VA_asm_target_004085f9 0x004085f9
extern "C" void __cdecl asm_target_00408efb();
#define VA_asm_target_00408efb 0x00408efb
extern "C" void __cdecl asm_target_00408f76();
#define VA_asm_target_00408f76 0x00408f76
extern "C" void __cdecl asm_target_00408f7c();
#define VA_asm_target_00408f7c 0x00408f7c
extern "C" void __cdecl asm_target_00409178();
#define VA_asm_target_00409178 0x00409178
extern "C" void __cdecl asm_target_00409219();
#define VA_asm_target_00409219 0x00409219
extern "C" void __cdecl asm_target_004093be();
#define VA_asm_target_004093be 0x004093be
extern "C" void __cdecl asm_target_004097f9();
#define VA_asm_target_004097f9 0x004097f9
extern "C" void __cdecl asm_target_0040981d();
#define VA_asm_target_0040981d 0x0040981d
extern "C" void __cdecl asm_target_0040983e();
#define VA_asm_target_0040983e 0x0040983e
extern "C" void __cdecl asm_target_00409868();
#define VA_asm_target_00409868 0x00409868
extern "C" void __cdecl asm_target_00409903();
#define VA_asm_target_00409903 0x00409903
extern "C" void __cdecl asm_target_00409bb0();
#define VA_asm_target_00409bb0 0x00409bb0
extern "C" void __cdecl asm_target_00409bdc();
#define VA_asm_target_00409bdc 0x00409bdc
extern "C" void __cdecl asm_target_00409d52();
#define VA_asm_target_00409d52 0x00409d52
extern "C" void __cdecl asm_target_00409d8c();
#define VA_asm_target_00409d8c 0x00409d8c
extern "C" void __cdecl asm_target_0040a55b();
#define VA_asm_target_0040a55b 0x0040a55b
extern "C" void __cdecl asm_target_0040a6df();
#define VA_asm_target_0040a6df 0x0040a6df
extern "C" void __cdecl asm_target_0040a7ae();
#define VA_asm_target_0040a7ae 0x0040a7ae
extern "C" void __cdecl asm_target_0040a913();
#define VA_asm_target_0040a913 0x0040a913
extern "C" void __cdecl asm_target_0040ab61();
#define VA_asm_target_0040ab61 0x0040ab61
extern "C" void __cdecl asm_target_0040abbc();
#define VA_asm_target_0040abbc 0x0040abbc
extern "C" void __cdecl asm_target_0040b3d0();
#define VA_asm_target_0040b3d0 0x0040b3d0
extern "C" void __cdecl asm_target_0040b43f();
#define VA_asm_target_0040b43f 0x0040b43f
extern "C" void __cdecl asm_target_0040bb10();
#define VA_asm_target_0040bb10 0x0040bb10
extern "C" void __cdecl asm_target_0040be8c();
#define VA_asm_target_0040be8c 0x0040be8c
extern "C" void __cdecl asm_target_0040c25f();
#define VA_asm_target_0040c25f 0x0040c25f
extern "C" void __cdecl asm_target_0040c27c();
#define VA_asm_target_0040c27c 0x0040c27c
extern "C" void __cdecl asm_target_0040c2c7();
#define VA_asm_target_0040c2c7 0x0040c2c7
extern "C" void __cdecl asm_target_0040c33a();
#define VA_asm_target_0040c33a 0x0040c33a
extern "C" void __cdecl asm_target_0040c34a();
#define VA_asm_target_0040c34a 0x0040c34a
extern "C" void __cdecl asm_target_0040ca00();
#define VA_asm_target_0040ca00 0x0040ca00
extern "C" void __cdecl asm_target_0040ca10();
#define VA_asm_target_0040ca10 0x0040ca10
extern "C" void __cdecl asm_target_0040cb9c();
#define VA_asm_target_0040cb9c 0x0040cb9c
extern "C" void __cdecl asm_target_0040db70();
#define VA_asm_target_0040db70 0x0040db70
extern "C" void __cdecl asm_target_0040dfda();
#define VA_asm_target_0040dfda 0x0040dfda
extern "C" void __cdecl asm_target_0040e09b();
#define VA_asm_target_0040e09b 0x0040e09b
extern "C" void __cdecl asm_target_0040e09d();
#define VA_asm_target_0040e09d 0x0040e09d
extern "C" void __cdecl asm_target_0040e0a7();
#define VA_asm_target_0040e0a7 0x0040e0a7
extern "C" void __cdecl asm_target_0040e0e9();
#define VA_asm_target_0040e0e9 0x0040e0e9
extern "C" void __cdecl asm_target_0040e26b();
#define VA_asm_target_0040e26b 0x0040e26b
extern "C" void __cdecl asm_target_0040e275();
#define VA_asm_target_0040e275 0x0040e275
extern "C" void __cdecl asm_target_0040e379();
#define VA_asm_target_0040e379 0x0040e379
extern "C" void __cdecl asm_target_0040e510();
#define VA_asm_target_0040e510 0x0040e510
extern "C" void __cdecl asm_target_0040e53e();
#define VA_asm_target_0040e53e 0x0040e53e
extern "C" void __cdecl asm_target_0040e8fc();
#define VA_asm_target_0040e8fc 0x0040e8fc
extern "C" void __cdecl asm_target_0040e900();
#define VA_asm_target_0040e900 0x0040e900
extern "C" void __cdecl asm_target_0040ecfb();
#define VA_asm_target_0040ecfb 0x0040ecfb
extern "C" void __cdecl asm_target_0040f103();
#define VA_asm_target_0040f103 0x0040f103
extern "C" void __cdecl asm_target_0040f28c();
#define VA_asm_target_0040f28c 0x0040f28c
extern "C" void __cdecl asm_target_0040f33c();
#define VA_asm_target_0040f33c 0x0040f33c
extern "C" void __cdecl asm_target_0040f479();
#define VA_asm_target_0040f479 0x0040f479
extern "C" void __cdecl asm_target_0040f4f9();
#define VA_asm_target_0040f4f9 0x0040f4f9
extern "C" void __cdecl asm_target_0040fc07();
#define VA_asm_target_0040fc07 0x0040fc07
extern "C" void __cdecl asm_target_00410107();
#define VA_asm_target_00410107 0x00410107
extern "C" void __cdecl asm_target_00410114();
#define VA_asm_target_00410114 0x00410114
extern "C" void __cdecl asm_target_00410408();
#define VA_asm_target_00410408 0x00410408
extern "C" void __cdecl asm_target_004106da();
#define VA_asm_target_004106da 0x004106da
extern "C" void __cdecl asm_target_00410738();
#define VA_asm_target_00410738 0x00410738
extern "C" void __cdecl asm_target_00410949();
#define VA_asm_target_00410949 0x00410949
extern "C" void __cdecl asm_target_004109a3();
#define VA_asm_target_004109a3 0x004109a3
extern "C" void __cdecl asm_target_00411909();
#define VA_asm_target_00411909 0x00411909
extern "C" void __cdecl asm_target_0041194c();
#define VA_asm_target_0041194c 0x0041194c
extern "C" void __cdecl asm_target_00411951();
#define VA_asm_target_00411951 0x00411951
extern "C" void __cdecl asm_target_00411956();
#define VA_asm_target_00411956 0x00411956
extern "C" void __cdecl asm_target_00411a15();
#define VA_asm_target_00411a15 0x00411a15
extern "C" void __cdecl asm_target_00411ab8();
#define VA_asm_target_00411ab8 0x00411ab8
extern "C" void __cdecl asm_target_00411d16();
#define VA_asm_target_00411d16 0x00411d16
extern "C" void __cdecl asm_target_00411d18();
#define VA_asm_target_00411d18 0x00411d18
extern "C" void __cdecl asm_target_00412223();
#define VA_asm_target_00412223 0x00412223
extern "C" void __cdecl asm_target_004125ee();
#define VA_asm_target_004125ee 0x004125ee
extern "C" void __cdecl asm_target_004125f4();
#define VA_asm_target_004125f4 0x004125f4
extern "C" void __cdecl asm_target_004127dc();
#define VA_asm_target_004127dc 0x004127dc
extern "C" void __cdecl asm_target_00412879();
#define VA_asm_target_00412879 0x00412879
extern "C" void __cdecl asm_target_00412b90();
#define VA_asm_target_00412b90 0x00412b90
extern "C" void __cdecl asm_target_00412cfe();
#define VA_asm_target_00412cfe 0x00412cfe
extern "C" void __cdecl asm_target_004135bc();
#define VA_asm_target_004135bc 0x004135bc
extern "C" void __cdecl asm_target_0041366a();
#define VA_asm_target_0041366a 0x0041366a
extern "C" void __cdecl asm_target_004137db();
#define VA_asm_target_004137db 0x004137db
extern "C" void __cdecl asm_target_00413a64();
#define VA_asm_target_00413a64 0x00413a64
extern "C" void __cdecl asm_target_00413b27();
#define VA_asm_target_00413b27 0x00413b27
extern "C" void __cdecl asm_target_00413d86();
#define VA_asm_target_00413d86 0x00413d86
extern "C" void __cdecl asm_target_00413f87();
#define VA_asm_target_00413f87 0x00413f87
extern "C" void __cdecl asm_target_00413f94();
#define VA_asm_target_00413f94 0x00413f94
extern "C" void __cdecl asm_target_0041402b();
#define VA_asm_target_0041402b 0x0041402b
extern "C" void __cdecl asm_target_0041410d();
#define VA_asm_target_0041410d 0x0041410d
extern "C" void __cdecl asm_target_00414240();
#define VA_asm_target_00414240 0x00414240
extern "C" void __cdecl asm_target_004144c0();
#define VA_asm_target_004144c0 0x004144c0
extern "C" void __cdecl asm_target_0041452f();
#define VA_asm_target_0041452f 0x0041452f
extern "C" void __cdecl asm_target_0041472f();
#define VA_asm_target_0041472f 0x0041472f
extern "C" void __cdecl asm_target_00414a08();
#define VA_asm_target_00414a08 0x00414a08
extern "C" void __cdecl asm_target_00414a5c();
#define VA_asm_target_00414a5c 0x00414a5c
extern "C" void __cdecl asm_target_00414ca0();
#define VA_asm_target_00414ca0 0x00414ca0
extern "C" void __cdecl asm_target_00414cae();
#define VA_asm_target_00414cae 0x00414cae
extern "C" void __cdecl asm_target_00414cf0();
#define VA_asm_target_00414cf0 0x00414cf0
extern "C" void __cdecl asm_target_00414d60();
#define VA_asm_target_00414d60 0x00414d60
extern "C" void __cdecl asm_target_00414d6e();
#define VA_asm_target_00414d6e 0x00414d6e
extern "C" void __cdecl asm_target_00414de9();
#define VA_asm_target_00414de9 0x00414de9
extern "C" void __cdecl asm_target_00414def();
#define VA_asm_target_00414def 0x00414def
extern "C" void __cdecl asm_target_00414f33();
#define VA_asm_target_00414f33 0x00414f33
extern "C" void __cdecl asm_target_00414f40();
#define VA_asm_target_00414f40 0x00414f40
extern "C" void __cdecl asm_target_00414ffc();
#define VA_asm_target_00414ffc 0x00414ffc
extern "C" void __cdecl asm_target_00415070();
#define VA_asm_target_00415070 0x00415070
extern "C" void __cdecl asm_target_00415076();
#define VA_asm_target_00415076 0x00415076
extern "C" void __cdecl asm_target_0041508c();
#define VA_asm_target_0041508c 0x0041508c
extern "C" void __cdecl asm_target_0041513c();
#define VA_asm_target_0041513c 0x0041513c
extern "C" void __cdecl asm_target_00415490();
#define VA_asm_target_00415490 0x00415490
extern "C" void __cdecl asm_target_0041549a();
#define VA_asm_target_0041549a 0x0041549a
extern "C" void __cdecl asm_target_004155ba();
#define VA_asm_target_004155ba 0x004155ba
extern "C" void __cdecl asm_target_004156ce();
#define VA_asm_target_004156ce 0x004156ce
extern "C" void __cdecl asm_target_00415764();
#define VA_asm_target_00415764 0x00415764
extern "C" void __cdecl asm_target_00415a3c();
#define VA_asm_target_00415a3c 0x00415a3c
extern "C" void __cdecl asm_target_00415ac6();
#define VA_asm_target_00415ac6 0x00415ac6
extern "C" void __cdecl asm_target_00415f06();
#define VA_asm_target_00415f06 0x00415f06
extern "C" void __cdecl asm_target_00416041();
#define VA_asm_target_00416041 0x00416041
extern "C" void __cdecl asm_target_00416949();
#define VA_asm_target_00416949 0x00416949
extern "C" void __cdecl asm_target_00416d5c();
#define VA_asm_target_00416d5c 0x00416d5c
extern "C" void __cdecl asm_target_00416d66();
#define VA_asm_target_00416d66 0x00416d66
extern "C" void __cdecl asm_target_00416dd2();
#define VA_asm_target_00416dd2 0x00416dd2
extern "C" void __cdecl asm_target_00416de8();
#define VA_asm_target_00416de8 0x00416de8
extern "C" void __cdecl asm_target_00416e8a();
#define VA_asm_target_00416e8a 0x00416e8a
extern "C" void __cdecl asm_target_00416e98();
#define VA_asm_target_00416e98 0x00416e98
extern "C" void __cdecl asm_target_00416f09();
#define VA_asm_target_00416f09 0x00416f09
extern "C" void __cdecl asm_target_00416f25();
#define VA_asm_target_00416f25 0x00416f25
extern "C" void __cdecl asm_target_00416f2d();
#define VA_asm_target_00416f2d 0x00416f2d
extern "C" void __cdecl asm_target_004170f4();
#define VA_asm_target_004170f4 0x004170f4
extern "C" void __cdecl asm_target_004171ac();
#define VA_asm_target_004171ac 0x004171ac
extern "C" void __cdecl asm_target_00417355();
#define VA_asm_target_00417355 0x00417355
extern "C" void __cdecl asm_target_0041753a();
#define VA_asm_target_0041753a 0x0041753a
extern "C" void __cdecl asm_target_00417559();
#define VA_asm_target_00417559 0x00417559
extern "C" void __cdecl asm_target_004179e9();
#define VA_asm_target_004179e9 0x004179e9
extern "C" void __cdecl asm_target_00417b3c();
#define VA_asm_target_00417b3c 0x00417b3c
extern "C" void __cdecl asm_target_00417b3e();
#define VA_asm_target_00417b3e 0x00417b3e
extern "C" void __cdecl asm_target_00417db5();
#define VA_asm_target_00417db5 0x00417db5
extern "C" void __cdecl asm_target_00417ee7();
#define VA_asm_target_00417ee7 0x00417ee7
extern "C" void __cdecl asm_target_00417f80();
#define VA_asm_target_00417f80 0x00417f80
extern "C" void __cdecl asm_target_0041840b();
#define VA_asm_target_0041840b 0x0041840b
extern "C" void __cdecl asm_target_0041861e();
#define VA_asm_target_0041861e 0x0041861e
extern "C" void __cdecl asm_target_00418622();
#define VA_asm_target_00418622 0x00418622
extern "C" void __cdecl asm_target_00418f82();
#define VA_asm_target_00418f82 0x00418f82
extern "C" void __cdecl asm_target_00419140();
#define VA_asm_target_00419140 0x00419140
extern "C" void __cdecl asm_target_004191ef();
#define VA_asm_target_004191ef 0x004191ef
extern "C" void __cdecl asm_target_004192e8();
#define VA_asm_target_004192e8 0x004192e8
extern "C" void __cdecl asm_target_004193ab();
#define VA_asm_target_004193ab 0x004193ab
extern "C" void __cdecl asm_target_00419435();
#define VA_asm_target_00419435 0x00419435
extern "C" void __cdecl asm_target_00419440();
#define VA_asm_target_00419440 0x00419440
extern "C" void __cdecl asm_target_004194e2();
#define VA_asm_target_004194e2 0x004194e2
extern "C" void __cdecl asm_target_00419567();
#define VA_asm_target_00419567 0x00419567
extern "C" void __cdecl asm_target_004195b2();
#define VA_asm_target_004195b2 0x004195b2
extern "C" void __cdecl asm_target_004195b8();
#define VA_asm_target_004195b8 0x004195b8
extern "C" void __cdecl asm_target_0041962d();
#define VA_asm_target_0041962d 0x0041962d
extern "C" void __cdecl asm_target_0041963c();
#define VA_asm_target_0041963c 0x0041963c
extern "C" void __cdecl asm_target_004196b2();
#define VA_asm_target_004196b2 0x004196b2
extern "C" void __cdecl asm_target_00419858();
#define VA_asm_target_00419858 0x00419858
extern "C" void __cdecl asm_target_004199ea();
#define VA_asm_target_004199ea 0x004199ea
extern "C" void __cdecl asm_target_00419ac7();
#define VA_asm_target_00419ac7 0x00419ac7
extern "C" void __cdecl asm_target_00419acb();
#define VA_asm_target_00419acb 0x00419acb
extern "C" void __cdecl asm_target_00419e77();
#define VA_asm_target_00419e77 0x00419e77
extern "C" void __cdecl asm_target_00419e83();
#define VA_asm_target_00419e83 0x00419e83
extern "C" void __cdecl asm_target_00419f25();
#define VA_asm_target_00419f25 0x00419f25
extern "C" void __cdecl asm_target_00419f70();
#define VA_asm_target_00419f70 0x00419f70
extern "C" void __cdecl asm_target_0041a01d();
#define VA_asm_target_0041a01d 0x0041a01d
extern "C" void __cdecl asm_target_0041a03c();
#define VA_asm_target_0041a03c 0x0041a03c
extern "C" void __cdecl asm_target_0041a3e4();
#define VA_asm_target_0041a3e4 0x0041a3e4
extern "C" void __cdecl asm_target_0041a400();
#define VA_asm_target_0041a400 0x0041a400
extern "C" void __cdecl asm_target_0041a4e0();
#define VA_asm_target_0041a4e0 0x0041a4e0
extern "C" void __cdecl asm_target_0041a6f5();
#define VA_asm_target_0041a6f5 0x0041a6f5
extern "C" void __cdecl asm_target_0041a775();
#define VA_asm_target_0041a775 0x0041a775
extern "C" void __cdecl asm_target_0041a9f0();
#define VA_asm_target_0041a9f0 0x0041a9f0
extern "C" void __cdecl asm_target_0041aa5c();
#define VA_asm_target_0041aa5c 0x0041aa5c
extern "C" void __cdecl asm_target_0041aa79();
#define VA_asm_target_0041aa79 0x0041aa79
extern "C" void __cdecl asm_target_0041aaaf();
#define VA_asm_target_0041aaaf 0x0041aaaf
extern "C" void __cdecl asm_target_0041aabb();
#define VA_asm_target_0041aabb 0x0041aabb
extern "C" void __cdecl asm_target_0041b004();
#define VA_asm_target_0041b004 0x0041b004
extern "C" void __cdecl asm_target_0041b133();
#define VA_asm_target_0041b133 0x0041b133
extern "C" void __cdecl asm_target_0041b1d8();
#define VA_asm_target_0041b1d8 0x0041b1d8
extern "C" void __cdecl asm_target_0041b1e7();
#define VA_asm_target_0041b1e7 0x0041b1e7
extern "C" void __cdecl asm_target_0041b2a1();
#define VA_asm_target_0041b2a1 0x0041b2a1
extern "C" void __cdecl asm_target_0041b32a();
#define VA_asm_target_0041b32a 0x0041b32a
extern "C" void __cdecl asm_target_0041b341();
#define VA_asm_target_0041b341 0x0041b341
extern "C" void __cdecl asm_target_0041b347();
#define VA_asm_target_0041b347 0x0041b347
extern "C" void __cdecl asm_target_0041b718();
#define VA_asm_target_0041b718 0x0041b718
extern "C" void __cdecl asm_target_0041b737();
#define VA_asm_target_0041b737 0x0041b737
extern "C" void __cdecl asm_target_0041b7fd();
#define VA_asm_target_0041b7fd 0x0041b7fd
extern "C" void __cdecl asm_target_0041b85a();
#define VA_asm_target_0041b85a 0x0041b85a
extern "C" void __cdecl asm_target_0041b9dc();
#define VA_asm_target_0041b9dc 0x0041b9dc
extern "C" void __cdecl asm_target_0041ba60();
#define VA_asm_target_0041ba60 0x0041ba60
extern "C" void __cdecl asm_target_0041bccd();
#define VA_asm_target_0041bccd 0x0041bccd
extern "C" void __cdecl asm_target_0041bdf3();
#define VA_asm_target_0041bdf3 0x0041bdf3
extern "C" void __cdecl asm_target_0041c340();
#define VA_asm_target_0041c340 0x0041c340
extern "C" void __cdecl asm_target_0041c430();
#define VA_asm_target_0041c430 0x0041c430
extern "C" void __cdecl asm_target_0041c43b();
#define VA_asm_target_0041c43b 0x0041c43b
extern "C" void __cdecl asm_target_0041c876();
#define VA_asm_target_0041c876 0x0041c876
extern "C" void __cdecl asm_target_0041caa0();
#define VA_asm_target_0041caa0 0x0041caa0
extern "C" void __cdecl asm_target_0041cc51();
#define VA_asm_target_0041cc51 0x0041cc51
extern "C" void __cdecl asm_target_0041cc80();
#define VA_asm_target_0041cc80 0x0041cc80
extern "C" void __cdecl asm_target_0041cd19();
#define VA_asm_target_0041cd19 0x0041cd19
extern "C" void __cdecl asm_target_0041cd57();
#define VA_asm_target_0041cd57 0x0041cd57
extern "C" void __cdecl asm_target_0041cdba();
#define VA_asm_target_0041cdba 0x0041cdba
extern "C" void __cdecl asm_target_0041ce63();
#define VA_asm_target_0041ce63 0x0041ce63
extern "C" void __cdecl asm_target_0041ce75();
#define VA_asm_target_0041ce75 0x0041ce75
extern "C" void __cdecl asm_target_0041ce92();
#define VA_asm_target_0041ce92 0x0041ce92
extern "C" void __cdecl asm_target_0041cf50();
#define VA_asm_target_0041cf50 0x0041cf50
extern "C" void __cdecl asm_target_0041cf59();
#define VA_asm_target_0041cf59 0x0041cf59
extern "C" void __cdecl asm_target_0041cf5c();
#define VA_asm_target_0041cf5c 0x0041cf5c
extern "C" void __cdecl asm_target_0041cf62();
#define VA_asm_target_0041cf62 0x0041cf62
extern "C" void __cdecl asm_target_0041cf6f();
#define VA_asm_target_0041cf6f 0x0041cf6f
extern "C" void __cdecl asm_target_0041cf72();
#define VA_asm_target_0041cf72 0x0041cf72
extern "C" void __cdecl asm_target_0041d165();
#define VA_asm_target_0041d165 0x0041d165
extern "C" void __cdecl asm_target_0041d229();
#define VA_asm_target_0041d229 0x0041d229
extern "C" void __cdecl asm_target_0041d361();
#define VA_asm_target_0041d361 0x0041d361
extern "C" void __cdecl asm_target_0041d4cf();
#define VA_asm_target_0041d4cf 0x0041d4cf
extern "C" void __cdecl asm_target_0041d592();
#define VA_asm_target_0041d592 0x0041d592
extern "C" void __cdecl asm_target_0041d750();
#define VA_asm_target_0041d750 0x0041d750
extern "C" void __cdecl asm_target_0041da21();
#define VA_asm_target_0041da21 0x0041da21
extern "C" void __cdecl asm_target_0041dad7();
#define VA_asm_target_0041dad7 0x0041dad7
extern "C" void __cdecl asm_target_0041dbee();
#define VA_asm_target_0041dbee 0x0041dbee
extern "C" void __cdecl asm_target_0041dc57();
#define VA_asm_target_0041dc57 0x0041dc57
extern "C" void __cdecl asm_target_0041dd5a();
#define VA_asm_target_0041dd5a 0x0041dd5a
extern "C" void __cdecl asm_target_0041de70();
#define VA_asm_target_0041de70 0x0041de70
extern "C" void __cdecl asm_target_0041dfb8();
#define VA_asm_target_0041dfb8 0x0041dfb8
extern "C" void __cdecl asm_target_0041e0c7();
#define VA_asm_target_0041e0c7 0x0041e0c7
extern "C" void __cdecl asm_target_0041e136();
#define VA_asm_target_0041e136 0x0041e136
extern "C" void __cdecl asm_target_0041e23b();
#define VA_asm_target_0041e23b 0x0041e23b
extern "C" void __cdecl asm_target_0041e2f4();
#define VA_asm_target_0041e2f4 0x0041e2f4
extern "C" void __cdecl asm_target_0041e4b1();
#define VA_asm_target_0041e4b1 0x0041e4b1
extern "C" void __cdecl asm_target_0041e886();
#define VA_asm_target_0041e886 0x0041e886
extern "C" void __cdecl asm_target_0041e9c7();
#define VA_asm_target_0041e9c7 0x0041e9c7
extern "C" void __cdecl asm_target_0041eca1();
#define VA_asm_target_0041eca1 0x0041eca1
extern "C" void __cdecl asm_target_0041ed57();
#define VA_asm_target_0041ed57 0x0041ed57
extern "C" void __cdecl asm_target_0041ee31();
#define VA_asm_target_0041ee31 0x0041ee31
extern "C" void __cdecl asm_target_0041ef78();
#define VA_asm_target_0041ef78 0x0041ef78
extern "C" void __cdecl asm_target_0041f1d4();
#define VA_asm_target_0041f1d4 0x0041f1d4
extern "C" void __cdecl asm_target_0041f259();
#define VA_asm_target_0041f259 0x0041f259
extern "C" void __cdecl asm_target_0041f2a2();
#define VA_asm_target_0041f2a2 0x0041f2a2
extern "C" void __cdecl asm_target_0041f3d9();
#define VA_asm_target_0041f3d9 0x0041f3d9
extern "C" void __cdecl asm_target_0041f490();
#define VA_asm_target_0041f490 0x0041f490
extern "C" void __cdecl asm_target_0041f604();
#define VA_asm_target_0041f604 0x0041f604
extern "C" void __cdecl asm_target_0041f65f();
#define VA_asm_target_0041f65f 0x0041f65f
extern "C" void __cdecl asm_target_00420632();
#define VA_asm_target_00420632 0x00420632
extern "C" void __cdecl asm_target_00420635();
#define VA_asm_target_00420635 0x00420635
extern "C" void __cdecl asm_target_00420851();
#define VA_asm_target_00420851 0x00420851
extern "C" void __cdecl asm_target_00420942();
#define VA_asm_target_00420942 0x00420942
extern "C" void __cdecl asm_target_00421061();
#define VA_asm_target_00421061 0x00421061
extern "C" void __cdecl asm_target_004210d0();
#define VA_asm_target_004210d0 0x004210d0
extern "C" void __cdecl asm_target_00421110();
#define VA_asm_target_00421110 0x00421110
extern "C" void __cdecl asm_target_00421150();
#define VA_asm_target_00421150 0x00421150
extern "C" void __cdecl asm_target_00421168();
#define VA_asm_target_00421168 0x00421168
extern "C" void __cdecl asm_target_004212b6();
#define VA_asm_target_004212b6 0x004212b6
extern "C" void __cdecl asm_target_00421360();
#define VA_asm_target_00421360 0x00421360
extern "C" void __cdecl asm_target_004213a0();
#define VA_asm_target_004213a0 0x004213a0
extern "C" void __cdecl asm_target_004213e0();
#define VA_asm_target_004213e0 0x004213e0
extern "C" void __cdecl asm_target_004213fa();
#define VA_asm_target_004213fa 0x004213fa
extern "C" void __cdecl asm_target_0042198b();
#define VA_asm_target_0042198b 0x0042198b
extern "C" void __cdecl asm_target_004219a4();
#define VA_asm_target_004219a4 0x004219a4
extern "C" void __cdecl asm_target_00421ede();
#define VA_asm_target_00421ede 0x00421ede
extern "C" void __cdecl asm_target_00422584();
#define VA_asm_target_00422584 0x00422584
extern "C" void __cdecl asm_target_00422647();
#define VA_asm_target_00422647 0x00422647
extern "C" void __cdecl asm_target_004226c0();
#define VA_asm_target_004226c0 0x004226c0
extern "C" void __cdecl asm_target_00422a0a();
#define VA_asm_target_00422a0a 0x00422a0a
extern "C" void __cdecl asm_target_00422a48();
#define VA_asm_target_00422a48 0x00422a48
extern "C" void __cdecl asm_target_00422a52();
#define VA_asm_target_00422a52 0x00422a52
extern "C" void __cdecl asm_target_00422e28();
#define VA_asm_target_00422e28 0x00422e28
extern "C" void __cdecl asm_target_00423059();
#define VA_asm_target_00423059 0x00423059
extern "C" void __cdecl asm_target_004231b0();
#define VA_asm_target_004231b0 0x004231b0
extern "C" void __cdecl asm_target_004231b3();
#define VA_asm_target_004231b3 0x004231b3
extern "C" void __cdecl asm_target_004236d9();
#define VA_asm_target_004236d9 0x004236d9
extern "C" void __cdecl asm_target_004237e1();
#define VA_asm_target_004237e1 0x004237e1
extern "C" void __cdecl asm_target_00423816();
#define VA_asm_target_00423816 0x00423816
extern "C" void __cdecl asm_target_00423849();
#define VA_asm_target_00423849 0x00423849
extern "C" void __cdecl asm_target_0042388e();
#define VA_asm_target_0042388e 0x0042388e
extern "C" void __cdecl asm_target_00423a0a();
#define VA_asm_target_00423a0a 0x00423a0a
extern "C" void __cdecl asm_target_00423bfa();
#define VA_asm_target_00423bfa 0x00423bfa
extern "C" void __cdecl asm_target_00423c20();
#define VA_asm_target_00423c20 0x00423c20
extern "C" void __cdecl asm_target_00423cb9();
#define VA_asm_target_00423cb9 0x00423cb9
extern "C" void __cdecl asm_target_00423df9();
#define VA_asm_target_00423df9 0x00423df9
extern "C" void __cdecl asm_target_00423f6f();
#define VA_asm_target_00423f6f 0x00423f6f
extern "C" void __cdecl asm_target_0042406f();
#define VA_asm_target_0042406f 0x0042406f
extern "C" void __cdecl asm_target_00424204();
#define VA_asm_target_00424204 0x00424204
extern "C" void __cdecl asm_target_00424217();
#define VA_asm_target_00424217 0x00424217
extern "C" void __cdecl asm_target_0042426d();
#define VA_asm_target_0042426d 0x0042426d
extern "C" void __cdecl asm_target_00424376();
#define VA_asm_target_00424376 0x00424376
extern "C" void __cdecl asm_target_00424379();
#define VA_asm_target_00424379 0x00424379
extern "C" void __cdecl asm_target_00424855();
#define VA_asm_target_00424855 0x00424855
extern "C" void __cdecl asm_target_00424d4a();
#define VA_asm_target_00424d4a 0x00424d4a
extern "C" void __cdecl asm_target_00425169();
#define VA_asm_target_00425169 0x00425169
extern "C" void __cdecl asm_target_004252d0();
#define VA_asm_target_004252d0 0x004252d0
extern "C" void __cdecl asm_target_0042536d();
#define VA_asm_target_0042536d 0x0042536d
extern "C" void __cdecl asm_target_0042536f();
#define VA_asm_target_0042536f 0x0042536f
extern "C" void __cdecl asm_target_00425373();
#define VA_asm_target_00425373 0x00425373
extern "C" void __cdecl asm_target_004253b2();
#define VA_asm_target_004253b2 0x004253b2
extern "C" void __cdecl asm_target_004255a1();
#define VA_asm_target_004255a1 0x004255a1
extern "C" void __cdecl asm_target_004255c7();
#define VA_asm_target_004255c7 0x004255c7
extern "C" void __cdecl asm_target_004256c9();
#define VA_asm_target_004256c9 0x004256c9
extern "C" void __cdecl asm_target_00425804();
#define VA_asm_target_00425804 0x00425804
extern "C" void __cdecl asm_target_00425821();
#define VA_asm_target_00425821 0x00425821
extern "C" void __cdecl asm_target_004258ab();
#define VA_asm_target_004258ab 0x004258ab
extern "C" void __cdecl asm_target_00425a24();
#define VA_asm_target_00425a24 0x00425a24
extern "C" void __cdecl asm_target_00425a8a();
#define VA_asm_target_00425a8a 0x00425a8a
extern "C" void __cdecl asm_target_00425b9d();
#define VA_asm_target_00425b9d 0x00425b9d
extern "C" void __cdecl asm_target_00425bd9();
#define VA_asm_target_00425bd9 0x00425bd9
extern "C" void __cdecl asm_target_00425c93();
#define VA_asm_target_00425c93 0x00425c93
extern "C" void __cdecl asm_target_00425ca4();
#define VA_asm_target_00425ca4 0x00425ca4
extern "C" void __cdecl asm_target_00425d72();
#define VA_asm_target_00425d72 0x00425d72
extern "C" void __cdecl asm_target_00425d83();
#define VA_asm_target_00425d83 0x00425d83
extern "C" void __cdecl asm_target_00425e31();
#define VA_asm_target_00425e31 0x00425e31
extern "C" void __cdecl asm_target_00425ee6();
#define VA_asm_target_00425ee6 0x00425ee6
extern "C" void __cdecl asm_target_004264ed();
#define VA_asm_target_004264ed 0x004264ed
extern "C" void __cdecl asm_target_004264ef();
#define VA_asm_target_004264ef 0x004264ef
extern "C" void __cdecl asm_target_004265ee();
#define VA_asm_target_004265ee 0x004265ee
extern "C" void __cdecl asm_target_00426602();
#define VA_asm_target_00426602 0x00426602
extern "C" void __cdecl asm_target_004267e6();
#define VA_asm_target_004267e6 0x004267e6
extern "C" void __cdecl asm_target_004269bf();
#define VA_asm_target_004269bf 0x004269bf
extern "C" void __cdecl asm_target_00426b07();
#define VA_asm_target_00426b07 0x00426b07
extern "C" void __cdecl asm_target_00426be0();
#define VA_asm_target_00426be0 0x00426be0
extern "C" void __cdecl asm_target_00426fb7();
#define VA_asm_target_00426fb7 0x00426fb7
extern "C" void __cdecl asm_target_0042702f();
#define VA_asm_target_0042702f 0x0042702f
extern "C" void __cdecl asm_target_004270cc();
#define VA_asm_target_004270cc 0x004270cc
extern "C" void __cdecl asm_target_004270e6();
#define VA_asm_target_004270e6 0x004270e6
extern "C" void __cdecl asm_target_00427169();
#define VA_asm_target_00427169 0x00427169
extern "C" void __cdecl asm_target_00427381();
#define VA_asm_target_00427381 0x00427381
extern "C" void __cdecl asm_target_0042749b();
#define VA_asm_target_0042749b 0x0042749b
extern "C" void __cdecl asm_target_0042764e();
#define VA_asm_target_0042764e 0x0042764e
extern "C" void __cdecl asm_target_004277e1();
#define VA_asm_target_004277e1 0x004277e1
extern "C" void __cdecl asm_target_0042782f();
#define VA_asm_target_0042782f 0x0042782f
extern "C" void __cdecl asm_target_00427833();
#define VA_asm_target_00427833 0x00427833
extern "C" void __cdecl asm_target_00427857();
#define VA_asm_target_00427857 0x00427857
extern "C" void __cdecl asm_target_00427873();
#define VA_asm_target_00427873 0x00427873
extern "C" void __cdecl asm_target_004278f0();
#define VA_asm_target_004278f0 0x004278f0
extern "C" void __cdecl asm_target_004278fd();
#define VA_asm_target_004278fd 0x004278fd
extern "C" void __cdecl asm_target_00427924();
#define VA_asm_target_00427924 0x00427924
extern "C" void __cdecl asm_target_00427a9c();
#define VA_asm_target_00427a9c 0x00427a9c
extern "C" void __cdecl asm_target_00427a9e();
#define VA_asm_target_00427a9e 0x00427a9e
extern "C" void __cdecl asm_target_00428152();
#define VA_asm_target_00428152 0x00428152
extern "C" void __cdecl asm_target_00428268();
#define VA_asm_target_00428268 0x00428268
extern "C" void __cdecl asm_target_004282a4();
#define VA_asm_target_004282a4 0x004282a4
extern "C" void __cdecl asm_target_004284ad();
#define VA_asm_target_004284ad 0x004284ad
extern "C" void __cdecl asm_target_004285c3();
#define VA_asm_target_004285c3 0x004285c3
extern "C" void __cdecl asm_target_004286b2();
#define VA_asm_target_004286b2 0x004286b2
extern "C" void __cdecl asm_target_0042886c();
#define VA_asm_target_0042886c 0x0042886c
extern "C" void __cdecl asm_target_004288b0();
#define VA_asm_target_004288b0 0x004288b0
extern "C" void __cdecl asm_target_0042894d();
#define VA_asm_target_0042894d 0x0042894d
extern "C" void __cdecl asm_target_00428a0c();
#define VA_asm_target_00428a0c 0x00428a0c
extern "C" void __cdecl asm_target_00428a37();
#define VA_asm_target_00428a37 0x00428a37
extern "C" void __cdecl asm_target_00428a5e();
#define VA_asm_target_00428a5e 0x00428a5e
extern "C" void __cdecl asm_target_00428a60();
#define VA_asm_target_00428a60 0x00428a60
extern "C" void __cdecl asm_target_0042923f();
#define VA_asm_target_0042923f 0x0042923f
extern "C" void __cdecl asm_target_00429245();
#define VA_asm_target_00429245 0x00429245
extern "C" void __cdecl asm_target_00429480();
#define VA_asm_target_00429480 0x00429480
extern "C" void __cdecl asm_target_00429499();
#define VA_asm_target_00429499 0x00429499
extern "C" void __cdecl asm_target_004298f6();
#define VA_asm_target_004298f6 0x004298f6
extern "C" void __cdecl asm_target_004299cb();
#define VA_asm_target_004299cb 0x004299cb
extern "C" void __cdecl asm_target_00429a02();
#define VA_asm_target_00429a02 0x00429a02
extern "C" void __cdecl asm_target_00429a17();
#define VA_asm_target_00429a17 0x00429a17
extern "C" void __cdecl asm_target_00429a1e();
#define VA_asm_target_00429a1e 0x00429a1e
extern "C" void __cdecl asm_target_00429b1d();
#define VA_asm_target_00429b1d 0x00429b1d
extern "C" void __cdecl asm_target_00429bf4();
#define VA_asm_target_00429bf4 0x00429bf4
extern "C" void __cdecl asm_target_00429c30();
#define VA_asm_target_00429c30 0x00429c30
extern "C" void __cdecl asm_target_00429cc2();
#define VA_asm_target_00429cc2 0x00429cc2
extern "C" void __cdecl asm_target_00429cc6();
#define VA_asm_target_00429cc6 0x00429cc6
extern "C" void __cdecl asm_target_00429d50();
#define VA_asm_target_00429d50 0x00429d50
extern "C" void __cdecl asm_target_00429e31();
#define VA_asm_target_00429e31 0x00429e31
extern "C" void __cdecl asm_target_0042a3a9();
#define VA_asm_target_0042a3a9 0x0042a3a9
extern "C" void __cdecl asm_target_0042a5a3();
#define VA_asm_target_0042a5a3 0x0042a5a3
extern "C" void __cdecl asm_target_0042a802();
#define VA_asm_target_0042a802 0x0042a802
extern "C" void __cdecl asm_target_0042ace0();
#define VA_asm_target_0042ace0 0x0042ace0
extern "C" void __cdecl asm_target_0042b0a5();
#define VA_asm_target_0042b0a5 0x0042b0a5
extern "C" void __cdecl asm_target_0042b161();
#define VA_asm_target_0042b161 0x0042b161
extern "C" void __cdecl asm_target_0042b183();
#define VA_asm_target_0042b183 0x0042b183
extern "C" void __cdecl asm_target_0042b198();
#define VA_asm_target_0042b198 0x0042b198
extern "C" void __cdecl asm_target_0042b1d0();
#define VA_asm_target_0042b1d0 0x0042b1d0
extern "C" void __cdecl asm_target_0042b7d3();
#define VA_asm_target_0042b7d3 0x0042b7d3
extern "C" void __cdecl asm_target_0042b8b2();
#define VA_asm_target_0042b8b2 0x0042b8b2
extern "C" void __cdecl asm_target_0042b97e();
#define VA_asm_target_0042b97e 0x0042b97e
extern "C" void __cdecl asm_target_0042ba08();
#define VA_asm_target_0042ba08 0x0042ba08
extern "C" void __cdecl asm_target_0042ba62();
#define VA_asm_target_0042ba62 0x0042ba62
extern "C" void __cdecl asm_target_0042c154();
#define VA_asm_target_0042c154 0x0042c154
extern "C" void __cdecl asm_target_0042c1d6();
#define VA_asm_target_0042c1d6 0x0042c1d6
extern "C" void __cdecl asm_target_0042c298();
#define VA_asm_target_0042c298 0x0042c298
extern "C" void __cdecl asm_target_0042c340();
#define VA_asm_target_0042c340 0x0042c340
extern "C" void __cdecl asm_target_0042c474();
#define VA_asm_target_0042c474 0x0042c474
extern "C" void __cdecl asm_target_0042c568();
#define VA_asm_target_0042c568 0x0042c568
extern "C" void __cdecl asm_target_0042c8f0();
#define VA_asm_target_0042c8f0 0x0042c8f0
extern "C" void __cdecl asm_target_0042ca5a();
#define VA_asm_target_0042ca5a 0x0042ca5a
extern "C" void __cdecl asm_target_0042ca88();
#define VA_asm_target_0042ca88 0x0042ca88
extern "C" void __cdecl asm_target_0042ce2b();
#define VA_asm_target_0042ce2b 0x0042ce2b
extern "C" void __cdecl asm_target_0042d19f();
#define VA_asm_target_0042d19f 0x0042d19f
extern "C" void __cdecl asm_target_0042d405();
#define VA_asm_target_0042d405 0x0042d405
extern "C" void __cdecl asm_target_0042d700();
#define VA_asm_target_0042d700 0x0042d700
extern "C" void __cdecl asm_target_0042d7d7();
#define VA_asm_target_0042d7d7 0x0042d7d7
extern "C" void __cdecl asm_target_0042d8c2();
#define VA_asm_target_0042d8c2 0x0042d8c2
extern "C" void __cdecl asm_target_0042d8c4();
#define VA_asm_target_0042d8c4 0x0042d8c4
extern "C" void __cdecl asm_target_0042d9f7();
#define VA_asm_target_0042d9f7 0x0042d9f7
extern "C" void __cdecl asm_target_0042da42();
#define VA_asm_target_0042da42 0x0042da42
extern "C" void __cdecl asm_target_0042da4d();
#define VA_asm_target_0042da4d 0x0042da4d
extern "C" void __cdecl asm_target_0042da66();
#define VA_asm_target_0042da66 0x0042da66
extern "C" void __cdecl asm_target_0042daa8();
#define VA_asm_target_0042daa8 0x0042daa8
extern "C" void __cdecl asm_target_0042daf2();
#define VA_asm_target_0042daf2 0x0042daf2
extern "C" void __cdecl asm_target_0042dafd();
#define VA_asm_target_0042dafd 0x0042dafd
extern "C" void __cdecl asm_target_0042db13();
#define VA_asm_target_0042db13 0x0042db13
extern "C" void __cdecl asm_target_0042db8d();
#define VA_asm_target_0042db8d 0x0042db8d
extern "C" void __cdecl asm_target_0042dde6();
#define VA_asm_target_0042dde6 0x0042dde6
extern "C" void __cdecl asm_target_0042ddea();
#define VA_asm_target_0042ddea 0x0042ddea
extern "C" void __cdecl asm_target_0042de37();
#define VA_asm_target_0042de37 0x0042de37
extern "C" void __cdecl asm_target_0042de42();
#define VA_asm_target_0042de42 0x0042de42
extern "C" void __cdecl asm_target_0042de49();
#define VA_asm_target_0042de49 0x0042de49
extern "C" void __cdecl asm_target_0042de86();
#define VA_asm_target_0042de86 0x0042de86
extern "C" void __cdecl asm_target_0042de8a();
#define VA_asm_target_0042de8a 0x0042de8a
extern "C" void __cdecl asm_target_0042ded7();
#define VA_asm_target_0042ded7 0x0042ded7
extern "C" void __cdecl asm_target_0042dedb();
#define VA_asm_target_0042dedb 0x0042dedb
extern "C" void __cdecl asm_target_0042dedd();
#define VA_asm_target_0042dedd 0x0042dedd
extern "C" void __cdecl asm_target_0042def6();
#define VA_asm_target_0042def6 0x0042def6
extern "C" void __cdecl asm_target_0042df4a();
#define VA_asm_target_0042df4a 0x0042df4a
extern "C" void __cdecl asm_target_0042df57();
#define VA_asm_target_0042df57 0x0042df57
extern "C" void __cdecl asm_target_0042df66();
#define VA_asm_target_0042df66 0x0042df66
extern "C" void __cdecl asm_target_0042e007();
#define VA_asm_target_0042e007 0x0042e007
extern "C" void __cdecl asm_target_0042e014();
#define VA_asm_target_0042e014 0x0042e014
extern "C" void __cdecl asm_target_0042e021();
#define VA_asm_target_0042e021 0x0042e021
extern "C" void __cdecl asm_target_0042e044();
#define VA_asm_target_0042e044 0x0042e044
extern "C" void __cdecl asm_target_0042e11b();
#define VA_asm_target_0042e11b 0x0042e11b
extern "C" void __cdecl asm_target_0042e1bb();
#define VA_asm_target_0042e1bb 0x0042e1bb
extern "C" void __cdecl asm_target_0042e1f6();
#define VA_asm_target_0042e1f6 0x0042e1f6
extern "C" void __cdecl asm_target_0042e1fa();
#define VA_asm_target_0042e1fa 0x0042e1fa
extern "C" void __cdecl asm_target_0042e24a();
#define VA_asm_target_0042e24a 0x0042e24a
extern "C" void __cdecl asm_target_0042e24c();
#define VA_asm_target_0042e24c 0x0042e24c
extern "C" void __cdecl asm_target_0042e255();
#define VA_asm_target_0042e255 0x0042e255
extern "C" void __cdecl asm_target_0042e27b();
#define VA_asm_target_0042e27b 0x0042e27b
extern "C" void __cdecl asm_target_0042e291();
#define VA_asm_target_0042e291 0x0042e291
extern "C" void __cdecl asm_target_0042e2b4();
#define VA_asm_target_0042e2b4 0x0042e2b4
extern "C" void __cdecl asm_target_0042e2c1();
#define VA_asm_target_0042e2c1 0x0042e2c1
extern "C" void __cdecl asm_target_0042e39b();
#define VA_asm_target_0042e39b 0x0042e39b
extern "C" void __cdecl asm_target_0042e43b();
#define VA_asm_target_0042e43b 0x0042e43b
extern "C" void __cdecl asm_target_0042e472();
#define VA_asm_target_0042e472 0x0042e472
extern "C" void __cdecl asm_target_0042e4bd();
#define VA_asm_target_0042e4bd 0x0042e4bd
extern "C" void __cdecl asm_target_0042e4f6();
#define VA_asm_target_0042e4f6 0x0042e4f6
extern "C" void __cdecl asm_target_0042e574();
#define VA_asm_target_0042e574 0x0042e574
extern "C" void __cdecl asm_target_0042e577();
#define VA_asm_target_0042e577 0x0042e577
extern "C" void __cdecl asm_target_0042e666();
#define VA_asm_target_0042e666 0x0042e666
extern "C" void __cdecl asm_target_0042e668();
#define VA_asm_target_0042e668 0x0042e668
extern "C" void __cdecl asm_target_0042e6d9();
#define VA_asm_target_0042e6d9 0x0042e6d9
extern "C" void __cdecl asm_target_0042e756();
#define VA_asm_target_0042e756 0x0042e756
extern "C" void __cdecl asm_target_0042e758();
#define VA_asm_target_0042e758 0x0042e758
extern "C" void __cdecl asm_target_0042e7c8();
#define VA_asm_target_0042e7c8 0x0042e7c8
extern "C" void __cdecl asm_target_0042e839();
#define VA_asm_target_0042e839 0x0042e839
extern "C" void __cdecl asm_target_0042e8b8();
#define VA_asm_target_0042e8b8 0x0042e8b8
extern "C" void __cdecl asm_target_0042e928();
#define VA_asm_target_0042e928 0x0042e928
extern "C" void __cdecl asm_target_0042e999();
#define VA_asm_target_0042e999 0x0042e999
extern "C" void __cdecl asm_target_0042ea18();
#define VA_asm_target_0042ea18 0x0042ea18
extern "C" void __cdecl asm_target_0042ea88();
#define VA_asm_target_0042ea88 0x0042ea88
extern "C" void __cdecl asm_target_0042eaf9();
#define VA_asm_target_0042eaf9 0x0042eaf9
extern "C" void __cdecl asm_target_0042eb78();
#define VA_asm_target_0042eb78 0x0042eb78
extern "C" void __cdecl asm_target_0042ebf6();
#define VA_asm_target_0042ebf6 0x0042ebf6
extern "C" void __cdecl asm_target_0042ebf8();
#define VA_asm_target_0042ebf8 0x0042ebf8
extern "C" void __cdecl asm_target_0042ec56();
#define VA_asm_target_0042ec56 0x0042ec56
extern "C" void __cdecl asm_target_0042ec58();
#define VA_asm_target_0042ec58 0x0042ec58
extern "C" void __cdecl asm_target_0042eca8();
#define VA_asm_target_0042eca8 0x0042eca8
extern "C" void __cdecl asm_target_0042ed06();
#define VA_asm_target_0042ed06 0x0042ed06
extern "C" void __cdecl asm_target_0042ed08();
#define VA_asm_target_0042ed08 0x0042ed08
extern "C" void __cdecl asm_target_0042ed23();
#define VA_asm_target_0042ed23 0x0042ed23
extern "C" void __cdecl asm_target_0042ed2c();
#define VA_asm_target_0042ed2c 0x0042ed2c
extern "C" void __cdecl asm_target_0042ed35();
#define VA_asm_target_0042ed35 0x0042ed35
extern "C" void __cdecl asm_target_0042ed3e();
#define VA_asm_target_0042ed3e 0x0042ed3e
extern "C" void __cdecl asm_target_0042ed47();
#define VA_asm_target_0042ed47 0x0042ed47
extern "C" void __cdecl asm_target_0042ed50();
#define VA_asm_target_0042ed50 0x0042ed50
extern "C" void __cdecl asm_target_0042ed59();
#define VA_asm_target_0042ed59 0x0042ed59
extern "C" void __cdecl asm_target_0042ed62();
#define VA_asm_target_0042ed62 0x0042ed62
extern "C" void __cdecl asm_target_0042ed6b();
#define VA_asm_target_0042ed6b 0x0042ed6b
extern "C" void __cdecl asm_target_0042ed74();
#define VA_asm_target_0042ed74 0x0042ed74
extern "C" void __cdecl asm_target_0042ed7d();
#define VA_asm_target_0042ed7d 0x0042ed7d
extern "C" void __cdecl asm_target_0042ed86();
#define VA_asm_target_0042ed86 0x0042ed86
extern "C" void __cdecl asm_target_0042ed8f();
#define VA_asm_target_0042ed8f 0x0042ed8f
extern "C" void __cdecl asm_target_0042ed98();
#define VA_asm_target_0042ed98 0x0042ed98
extern "C" void __cdecl asm_target_0042eda1();
#define VA_asm_target_0042eda1 0x0042eda1
extern "C" void __cdecl asm_target_0042edaa();
#define VA_asm_target_0042edaa 0x0042edaa
extern "C" void __cdecl asm_target_0042edb3();
#define VA_asm_target_0042edb3 0x0042edb3
extern "C" void __cdecl asm_target_0042edf6();
#define VA_asm_target_0042edf6 0x0042edf6
extern "C" void __cdecl asm_target_0042edf8();
#define VA_asm_target_0042edf8 0x0042edf8
extern "C" void __cdecl asm_target_0042ee56();
#define VA_asm_target_0042ee56 0x0042ee56
extern "C" void __cdecl asm_target_0042ee58();
#define VA_asm_target_0042ee58 0x0042ee58
extern "C" void __cdecl asm_target_0042eefb();
#define VA_asm_target_0042eefb 0x0042eefb
extern "C" void __cdecl asm_target_0042ef04();
#define VA_asm_target_0042ef04 0x0042ef04
extern "C" void __cdecl asm_target_0042ef13();
#define VA_asm_target_0042ef13 0x0042ef13
extern "C" void __cdecl asm_target_0042ef1c();
#define VA_asm_target_0042ef1c 0x0042ef1c
extern "C" void __cdecl asm_target_0042ef56();
#define VA_asm_target_0042ef56 0x0042ef56
extern "C" void __cdecl asm_target_0042ef58();
#define VA_asm_target_0042ef58 0x0042ef58
extern "C" void __cdecl asm_target_0042efb6();
#define VA_asm_target_0042efb6 0x0042efb6
extern "C" void __cdecl asm_target_0042efb8();
#define VA_asm_target_0042efb8 0x0042efb8
extern "C" void __cdecl asm_target_0042f008();
#define VA_asm_target_0042f008 0x0042f008
extern "C" void __cdecl asm_target_0042f066();
#define VA_asm_target_0042f066 0x0042f066
extern "C" void __cdecl asm_target_0042f068();
#define VA_asm_target_0042f068 0x0042f068
extern "C" void __cdecl asm_target_0042f07e();
#define VA_asm_target_0042f07e 0x0042f07e
extern "C" void __cdecl asm_target_0042f0c9();
#define VA_asm_target_0042f0c9 0x0042f0c9
extern "C" void __cdecl asm_target_0042f126();
#define VA_asm_target_0042f126 0x0042f126
extern "C" void __cdecl asm_target_0042f128();
#define VA_asm_target_0042f128 0x0042f128
extern "C" void __cdecl asm_target_0042f186();
#define VA_asm_target_0042f186 0x0042f186
extern "C" void __cdecl asm_target_0042f188();
#define VA_asm_target_0042f188 0x0042f188
extern "C" void __cdecl asm_target_0042f1f4();
#define VA_asm_target_0042f1f4 0x0042f1f4
extern "C" void __cdecl asm_target_0042f1fd();
#define VA_asm_target_0042f1fd 0x0042f1fd
extern "C" void __cdecl asm_target_0042f206();
#define VA_asm_target_0042f206 0x0042f206
extern "C" void __cdecl asm_target_0042f20f();
#define VA_asm_target_0042f20f 0x0042f20f
extern "C" void __cdecl asm_target_0042f218();
#define VA_asm_target_0042f218 0x0042f218
extern "C" void __cdecl asm_target_0042f221();
#define VA_asm_target_0042f221 0x0042f221
extern "C" void __cdecl asm_target_0042f230();
#define VA_asm_target_0042f230 0x0042f230
extern "C" void __cdecl asm_target_0042f276();
#define VA_asm_target_0042f276 0x0042f276
extern "C" void __cdecl asm_target_0042f278();
#define VA_asm_target_0042f278 0x0042f278
extern "C" void __cdecl asm_target_0042f2d6();
#define VA_asm_target_0042f2d6 0x0042f2d6
extern "C" void __cdecl asm_target_0042f2d8();
#define VA_asm_target_0042f2d8 0x0042f2d8
extern "C" void __cdecl asm_target_0042f328();
#define VA_asm_target_0042f328 0x0042f328
extern "C" void __cdecl asm_target_0042f387();
#define VA_asm_target_0042f387 0x0042f387
extern "C" void __cdecl asm_target_0042f390();
#define VA_asm_target_0042f390 0x0042f390
extern "C" void __cdecl asm_target_0042f399();
#define VA_asm_target_0042f399 0x0042f399
extern "C" void __cdecl asm_target_0042f39f();
#define VA_asm_target_0042f39f 0x0042f39f
extern "C" void __cdecl asm_target_0042f3a8();
#define VA_asm_target_0042f3a8 0x0042f3a8
extern "C" void __cdecl asm_target_0042f3e6();
#define VA_asm_target_0042f3e6 0x0042f3e6
extern "C" void __cdecl asm_target_0042f3e8();
#define VA_asm_target_0042f3e8 0x0042f3e8
extern "C" void __cdecl asm_target_0042f446();
#define VA_asm_target_0042f446 0x0042f446
extern "C" void __cdecl asm_target_0042f448();
#define VA_asm_target_0042f448 0x0042f448
extern "C" void __cdecl asm_target_0042f4a6();
#define VA_asm_target_0042f4a6 0x0042f4a6
extern "C" void __cdecl asm_target_0042f4a8();
#define VA_asm_target_0042f4a8 0x0042f4a8
extern "C" void __cdecl asm_target_0042f506();
#define VA_asm_target_0042f506 0x0042f506
extern "C" void __cdecl asm_target_0042f508();
#define VA_asm_target_0042f508 0x0042f508
extern "C" void __cdecl asm_target_0042f524();
#define VA_asm_target_0042f524 0x0042f524
extern "C" void __cdecl asm_target_0042f52d();
#define VA_asm_target_0042f52d 0x0042f52d
extern "C" void __cdecl asm_target_0042f536();
#define VA_asm_target_0042f536 0x0042f536
extern "C" void __cdecl asm_target_0042f7d9();
#define VA_asm_target_0042f7d9 0x0042f7d9
extern "C" void __cdecl asm_target_0042f810();
#define VA_asm_target_0042f810 0x0042f810
extern "C" void __cdecl asm_target_0042f892();
#define VA_asm_target_0042f892 0x0042f892
extern "C" void __cdecl asm_target_0042f893();
#define VA_asm_target_0042f893 0x0042f893
extern "C" void __cdecl asm_target_0042f8f9();
#define VA_asm_target_0042f8f9 0x0042f8f9
extern "C" void __cdecl asm_target_0042f976();
#define VA_asm_target_0042f976 0x0042f976
extern "C" void __cdecl asm_target_0042f978();
#define VA_asm_target_0042f978 0x0042f978
extern "C" void __cdecl asm_target_0042f9e8();
#define VA_asm_target_0042f9e8 0x0042f9e8
extern "C" void __cdecl asm_target_0042fa59();
#define VA_asm_target_0042fa59 0x0042fa59
extern "C" void __cdecl asm_target_0042fac8();
#define VA_asm_target_0042fac8 0x0042fac8
extern "C" void __cdecl asm_target_0042fb39();
#define VA_asm_target_0042fb39 0x0042fb39
extern "C" void __cdecl asm_target_0042fba8();
#define VA_asm_target_0042fba8 0x0042fba8
extern "C" void __cdecl asm_target_0042fc19();
#define VA_asm_target_0042fc19 0x0042fc19
extern "C" void __cdecl asm_target_0042fc88();
#define VA_asm_target_0042fc88 0x0042fc88
extern "C" void __cdecl asm_target_0042fcf9();
#define VA_asm_target_0042fcf9 0x0042fcf9
extern "C" void __cdecl asm_target_0042fd68();
#define VA_asm_target_0042fd68 0x0042fd68
extern "C" void __cdecl asm_target_0042fdd9();
#define VA_asm_target_0042fdd9 0x0042fdd9
extern "C" void __cdecl asm_target_0042fe48();
#define VA_asm_target_0042fe48 0x0042fe48
extern "C" void __cdecl asm_target_0042feb9();
#define VA_asm_target_0042feb9 0x0042feb9
extern "C" void __cdecl asm_target_0042ff28();
#define VA_asm_target_0042ff28 0x0042ff28
extern "C" void __cdecl asm_target_0042ff99();
#define VA_asm_target_0042ff99 0x0042ff99
extern "C" void __cdecl asm_target_00430008();
#define VA_asm_target_00430008 0x00430008
extern "C" void __cdecl asm_target_00430079();
#define VA_asm_target_00430079 0x00430079
extern "C" void __cdecl asm_target_004300e6();
#define VA_asm_target_004300e6 0x004300e6
extern "C" void __cdecl asm_target_004300e8();
#define VA_asm_target_004300e8 0x004300e8
extern "C" void __cdecl asm_target_00430159();
#define VA_asm_target_00430159 0x00430159
extern "C" void __cdecl asm_target_0043018d();
#define VA_asm_target_0043018d 0x0043018d
extern "C" void __cdecl asm_target_00430196();
#define VA_asm_target_00430196 0x00430196
extern "C" void __cdecl asm_target_0043019f();
#define VA_asm_target_0043019f 0x0043019f
extern "C" void __cdecl asm_target_004301a8();
#define VA_asm_target_004301a8 0x004301a8
extern "C" void __cdecl asm_target_004301b1();
#define VA_asm_target_004301b1 0x004301b1
extern "C" void __cdecl asm_target_004301ba();
#define VA_asm_target_004301ba 0x004301ba
extern "C" void __cdecl asm_target_004301c3();
#define VA_asm_target_004301c3 0x004301c3
extern "C" void __cdecl asm_target_004301cc();
#define VA_asm_target_004301cc 0x004301cc
extern "C" void __cdecl asm_target_004301d5();
#define VA_asm_target_004301d5 0x004301d5
extern "C" void __cdecl asm_target_004301de();
#define VA_asm_target_004301de 0x004301de
extern "C" void __cdecl asm_target_004301e7();
#define VA_asm_target_004301e7 0x004301e7
extern "C" void __cdecl asm_target_004301f0();
#define VA_asm_target_004301f0 0x004301f0
extern "C" void __cdecl asm_target_004301f9();
#define VA_asm_target_004301f9 0x004301f9
extern "C" void __cdecl asm_target_00430202();
#define VA_asm_target_00430202 0x00430202
extern "C" void __cdecl asm_target_0043020b();
#define VA_asm_target_0043020b 0x0043020b
extern "C" void __cdecl asm_target_00430214();
#define VA_asm_target_00430214 0x00430214
extern "C" void __cdecl asm_target_0043021d();
#define VA_asm_target_0043021d 0x0043021d
extern "C" void __cdecl asm_target_00430226();
#define VA_asm_target_00430226 0x00430226
extern "C" void __cdecl asm_target_0043022f();
#define VA_asm_target_0043022f 0x0043022f
extern "C" void __cdecl asm_target_00430238();
#define VA_asm_target_00430238 0x00430238
extern "C" void __cdecl asm_target_00430241();
#define VA_asm_target_00430241 0x00430241
extern "C" void __cdecl asm_target_00430315();
#define VA_asm_target_00430315 0x00430315
extern "C" void __cdecl asm_target_00430674();
#define VA_asm_target_00430674 0x00430674
extern "C" void __cdecl asm_target_00430675();
#define VA_asm_target_00430675 0x00430675
extern "C" void __cdecl asm_target_0043077c();
#define VA_asm_target_0043077c 0x0043077c
extern "C" void __cdecl asm_target_00430a3c();
#define VA_asm_target_00430a3c 0x00430a3c
extern "C" void __cdecl asm_target_00430a3e();
#define VA_asm_target_00430a3e 0x00430a3e
extern "C" void __cdecl asm_target_00430bfc();
#define VA_asm_target_00430bfc 0x00430bfc
extern "C" void __cdecl asm_target_00430fcf();
#define VA_asm_target_00430fcf 0x00430fcf
extern "C" void __cdecl asm_target_00430fd2();
#define VA_asm_target_00430fd2 0x00430fd2
extern "C" void __cdecl asm_target_004311ad();
#define VA_asm_target_004311ad 0x004311ad
extern "C" void __cdecl asm_target_004311cb();
#define VA_asm_target_004311cb 0x004311cb
extern "C" void __cdecl asm_target_004311e9();
#define VA_asm_target_004311e9 0x004311e9
extern "C" void __cdecl asm_target_00431203();
#define VA_asm_target_00431203 0x00431203
extern "C" void __cdecl asm_target_00431221();
#define VA_asm_target_00431221 0x00431221
extern "C" void __cdecl asm_target_0043123f();
#define VA_asm_target_0043123f 0x0043123f
extern "C" void __cdecl asm_target_0043125d();
#define VA_asm_target_0043125d 0x0043125d
extern "C" void __cdecl asm_target_0043127b();
#define VA_asm_target_0043127b 0x0043127b
extern "C" void __cdecl asm_target_00431297();
#define VA_asm_target_00431297 0x00431297
extern "C" void __cdecl asm_target_004312b5();
#define VA_asm_target_004312b5 0x004312b5
extern "C" void __cdecl asm_target_004313eb();
#define VA_asm_target_004313eb 0x004313eb
extern "C" void __cdecl asm_target_004313ee();
#define VA_asm_target_004313ee 0x004313ee
extern "C" void __cdecl asm_target_00431489();
#define VA_asm_target_00431489 0x00431489
extern "C" void __cdecl asm_target_00431595();
#define VA_asm_target_00431595 0x00431595
extern "C" void __cdecl asm_target_004315aa();
#define VA_asm_target_004315aa 0x004315aa
extern "C" void __cdecl asm_target_00431731();
#define VA_asm_target_00431731 0x00431731
extern "C" void __cdecl asm_target_0043181a();
#define VA_asm_target_0043181a 0x0043181a
extern "C" void __cdecl asm_target_00431b5a();
#define VA_asm_target_00431b5a 0x00431b5a
extern "C" void __cdecl asm_target_00431b5d();
#define VA_asm_target_00431b5d 0x00431b5d
extern "C" void __cdecl asm_target_00431cd0();
#define VA_asm_target_00431cd0 0x00431cd0
extern "C" void __cdecl asm_target_00431d9d();
#define VA_asm_target_00431d9d 0x00431d9d
extern "C" void __cdecl asm_target_00431dd3();
#define VA_asm_target_00431dd3 0x00431dd3
extern "C" void __cdecl asm_target_00431eb1();
#define VA_asm_target_00431eb1 0x00431eb1
extern "C" void __cdecl asm_target_00431eca();
#define VA_asm_target_00431eca 0x00431eca
extern "C" void __cdecl asm_target_004321e9();
#define VA_asm_target_004321e9 0x004321e9
extern "C" void __cdecl asm_target_004322ea();
#define VA_asm_target_004322ea 0x004322ea
extern "C" void __cdecl asm_target_0043237f();
#define VA_asm_target_0043237f 0x0043237f
extern "C" void __cdecl asm_target_004324b0();
#define VA_asm_target_004324b0 0x004324b0
extern "C" void __cdecl asm_target_004324b6();
#define VA_asm_target_004324b6 0x004324b6
extern "C" void __cdecl asm_target_004324d4();
#define VA_asm_target_004324d4 0x004324d4
extern "C" void __cdecl asm_target_00432670();
#define VA_asm_target_00432670 0x00432670
extern "C" void __cdecl asm_target_00432672();
#define VA_asm_target_00432672 0x00432672
extern "C" void __cdecl asm_target_00432710();
#define VA_asm_target_00432710 0x00432710
extern "C" void __cdecl asm_target_00432735();
#define VA_asm_target_00432735 0x00432735
extern "C" void __cdecl asm_target_00432750();
#define VA_asm_target_00432750 0x00432750
extern "C" void __cdecl asm_target_00432760();
#define VA_asm_target_00432760 0x00432760
extern "C" void __cdecl asm_target_0043289c();
#define VA_asm_target_0043289c 0x0043289c
extern "C" void __cdecl asm_target_00432926();
#define VA_asm_target_00432926 0x00432926
extern "C" void __cdecl asm_target_0043295f();
#define VA_asm_target_0043295f 0x0043295f
extern "C" void __cdecl asm_target_0043299f();
#define VA_asm_target_0043299f 0x0043299f
extern "C" void __cdecl asm_target_004329a5();
#define VA_asm_target_004329a5 0x004329a5
extern "C" void __cdecl asm_target_004329c7();
#define VA_asm_target_004329c7 0x004329c7
extern "C" void __cdecl asm_target_00432a65();
#define VA_asm_target_00432a65 0x00432a65
extern "C" void __cdecl asm_target_00432b8d();
#define VA_asm_target_00432b8d 0x00432b8d
extern "C" void __cdecl asm_target_00432c9b();
#define VA_asm_target_00432c9b 0x00432c9b
extern "C" void __cdecl asm_target_00432eb0();
#define VA_asm_target_00432eb0 0x00432eb0
extern "C" void __cdecl asm_target_00432fd0();
#define VA_asm_target_00432fd0 0x00432fd0
extern "C" void __cdecl asm_target_0043310e();
#define VA_asm_target_0043310e 0x0043310e
extern "C" void __cdecl asm_target_0043311a();
#define VA_asm_target_0043311a 0x0043311a
extern "C" void __cdecl asm_target_0043312b();
#define VA_asm_target_0043312b 0x0043312b
extern "C" void __cdecl asm_target_00433209();
#define VA_asm_target_00433209 0x00433209
extern "C" void __cdecl asm_target_0043320c();
#define VA_asm_target_0043320c 0x0043320c
extern "C" void __cdecl asm_target_00433284();
#define VA_asm_target_00433284 0x00433284
extern "C" void __cdecl asm_target_0043337a();
#define VA_asm_target_0043337a 0x0043337a
extern "C" void __cdecl asm_target_004334b1();
#define VA_asm_target_004334b1 0x004334b1
extern "C" void __cdecl asm_target_00433551();
#define VA_asm_target_00433551 0x00433551
extern "C" void __cdecl asm_target_0043355b();
#define VA_asm_target_0043355b 0x0043355b
extern "C" void __cdecl asm_target_0043355f();
#define VA_asm_target_0043355f 0x0043355f
extern "C" void __cdecl asm_target_0043363c();
#define VA_asm_target_0043363c 0x0043363c
extern "C" void __cdecl asm_target_004339dc();
#define VA_asm_target_004339dc 0x004339dc
extern "C" void __cdecl asm_target_004339ed();
#define VA_asm_target_004339ed 0x004339ed
extern "C" void __cdecl asm_target_00433af6();
#define VA_asm_target_00433af6 0x00433af6
extern "C" void __cdecl asm_target_00433af9();
#define VA_asm_target_00433af9 0x00433af9
extern "C" void __cdecl asm_target_00433db0();
#define VA_asm_target_00433db0 0x00433db0
extern "C" void __cdecl asm_target_00433dbf();
#define VA_asm_target_00433dbf 0x00433dbf
extern "C" void __cdecl asm_target_00433df1();
#define VA_asm_target_00433df1 0x00433df1
extern "C" void __cdecl asm_target_00433ec3();
#define VA_asm_target_00433ec3 0x00433ec3
extern "C" void __cdecl asm_target_00433ec8();
#define VA_asm_target_00433ec8 0x00433ec8
extern "C" void __cdecl asm_target_00433edc();
#define VA_asm_target_00433edc 0x00433edc
extern "C" void __cdecl asm_target_00434054();
#define VA_asm_target_00434054 0x00434054
extern "C" void __cdecl asm_target_00434101();
#define VA_asm_target_00434101 0x00434101
extern "C" void __cdecl asm_target_00434172();
#define VA_asm_target_00434172 0x00434172
extern "C" void __cdecl asm_target_004342dd();
#define VA_asm_target_004342dd 0x004342dd
extern "C" void __cdecl asm_target_004343f6();
#define VA_asm_target_004343f6 0x004343f6
extern "C" void __cdecl asm_target_004344cd();
#define VA_asm_target_004344cd 0x004344cd
extern "C" void __cdecl asm_target_00434583();
#define VA_asm_target_00434583 0x00434583
extern "C" void __cdecl asm_target_00434667();
#define VA_asm_target_00434667 0x00434667
extern "C" void __cdecl asm_target_00434673();
#define VA_asm_target_00434673 0x00434673
extern "C" void __cdecl asm_target_004347fb();
#define VA_asm_target_004347fb 0x004347fb
extern "C" void __cdecl asm_target_00434803();
#define VA_asm_target_00434803 0x00434803
extern "C" void __cdecl asm_target_004349be();
#define VA_asm_target_004349be 0x004349be
extern "C" void __cdecl asm_target_004349c1();
#define VA_asm_target_004349c1 0x004349c1
extern "C" void __cdecl asm_target_004350ae();
#define VA_asm_target_004350ae 0x004350ae
extern "C" void __cdecl asm_target_00435160();
#define VA_asm_target_00435160 0x00435160
extern "C" void __cdecl asm_target_004351ed();
#define VA_asm_target_004351ed 0x004351ed
extern "C" void __cdecl asm_target_004353f6();
#define VA_asm_target_004353f6 0x004353f6
extern "C" void __cdecl asm_target_00435a90();
#define VA_asm_target_00435a90 0x00435a90
extern "C" void __cdecl asm_target_00435bb0();
#define VA_asm_target_00435bb0 0x00435bb0
extern "C" void __cdecl asm_target_00435bc0();
#define VA_asm_target_00435bc0 0x00435bc0
extern "C" void __cdecl asm_target_00435cf5();
#define VA_asm_target_00435cf5 0x00435cf5
extern "C" void __cdecl asm_target_00435cfb();
#define VA_asm_target_00435cfb 0x00435cfb
extern "C" void __cdecl asm_target_00435d62();
#define VA_asm_target_00435d62 0x00435d62
extern "C" void __cdecl asm_target_00435d6e();
#define VA_asm_target_00435d6e 0x00435d6e
extern "C" void __cdecl asm_target_00435e0e();
#define VA_asm_target_00435e0e 0x00435e0e
extern "C" void __cdecl asm_target_00435e10();
#define VA_asm_target_00435e10 0x00435e10
extern "C" void __cdecl asm_target_00435f7d();
#define VA_asm_target_00435f7d 0x00435f7d
extern "C" void __cdecl asm_target_00436015();
#define VA_asm_target_00436015 0x00436015
extern "C" void __cdecl asm_target_0043611c();
#define VA_asm_target_0043611c 0x0043611c
extern "C" void __cdecl asm_target_0043611f();
#define VA_asm_target_0043611f 0x0043611f
extern "C" void __cdecl asm_target_00436131();
#define VA_asm_target_00436131 0x00436131
extern "C" void __cdecl asm_target_00436360();
#define VA_asm_target_00436360 0x00436360
extern "C" void __cdecl asm_target_00436de0();
#define VA_asm_target_00436de0 0x00436de0
extern "C" void __cdecl asm_target_00436df4();
#define VA_asm_target_00436df4 0x00436df4
extern "C" void __cdecl asm_target_00436f6c();
#define VA_asm_target_00436f6c 0x00436f6c
extern "C" void __cdecl asm_target_00436f82();
#define VA_asm_target_00436f82 0x00436f82
extern "C" void __cdecl asm_target_00436fa3();
#define VA_asm_target_00436fa3 0x00436fa3
extern "C" void __cdecl asm_target_00436fc0();
#define VA_asm_target_00436fc0 0x00436fc0
extern "C" void __cdecl asm_target_0043711c();
#define VA_asm_target_0043711c 0x0043711c
extern "C" void __cdecl asm_target_00437135();
#define VA_asm_target_00437135 0x00437135
extern "C" void __cdecl asm_target_00437146();
#define VA_asm_target_00437146 0x00437146
extern "C" void __cdecl asm_target_0043752a();
#define VA_asm_target_0043752a 0x0043752a
extern "C" void __cdecl asm_target_004377f2();
#define VA_asm_target_004377f2 0x004377f2
extern "C" void __cdecl asm_target_00437816();
#define VA_asm_target_00437816 0x00437816
extern "C" void __cdecl asm_target_00437830();
#define VA_asm_target_00437830 0x00437830
extern "C" void __cdecl asm_target_004378ba();
#define VA_asm_target_004378ba 0x004378ba
extern "C" void __cdecl asm_target_004378e0();
#define VA_asm_target_004378e0 0x004378e0
extern "C" void __cdecl asm_target_00437930();
#define VA_asm_target_00437930 0x00437930
extern "C" void __cdecl asm_target_004379bf();
#define VA_asm_target_004379bf 0x004379bf
extern "C" void __cdecl asm_target_00437e81();
#define VA_asm_target_00437e81 0x00437e81
extern "C" void __cdecl asm_target_004380b1();
#define VA_asm_target_004380b1 0x004380b1
extern "C" void __cdecl asm_target_00438ba5();
#define VA_asm_target_00438ba5 0x00438ba5
extern "C" void __cdecl asm_target_00438cf1();
#define VA_asm_target_00438cf1 0x00438cf1
extern "C" void __cdecl asm_target_00438d95();
#define VA_asm_target_00438d95 0x00438d95
extern "C" void __cdecl asm_target_00438dce();
#define VA_asm_target_00438dce 0x00438dce
extern "C" void __cdecl asm_target_00438dd0();
#define VA_asm_target_00438dd0 0x00438dd0
extern "C" void __cdecl asm_target_00439029();
#define VA_asm_target_00439029 0x00439029
extern "C" void __cdecl asm_target_00439032();
#define VA_asm_target_00439032 0x00439032
extern "C" void __cdecl asm_target_004391a1();
#define VA_asm_target_004391a1 0x004391a1
extern "C" void __cdecl asm_target_004391d8();
#define VA_asm_target_004391d8 0x004391d8
extern "C" void __cdecl asm_target_004393e9();
#define VA_asm_target_004393e9 0x004393e9
extern "C" void __cdecl asm_target_00439511();
#define VA_asm_target_00439511 0x00439511
extern "C" void __cdecl asm_target_00439527();
#define VA_asm_target_00439527 0x00439527
extern "C" void __cdecl asm_target_00439991();
#define VA_asm_target_00439991 0x00439991
extern "C" void __cdecl asm_target_004399e0();
#define VA_asm_target_004399e0 0x004399e0
extern "C" void __cdecl asm_target_00439b13();
#define VA_asm_target_00439b13 0x00439b13
extern "C" void __cdecl asm_target_00439b33();
#define VA_asm_target_00439b33 0x00439b33
extern "C" void __cdecl asm_target_00439b4f();
#define VA_asm_target_00439b4f 0x00439b4f
extern "C" void __cdecl asm_target_0043a12a();
#define VA_asm_target_0043a12a 0x0043a12a
extern "C" void __cdecl asm_target_0043a16e();
#define VA_asm_target_0043a16e 0x0043a16e
extern "C" void __cdecl asm_target_0043a179();
#define VA_asm_target_0043a179 0x0043a179
extern "C" void __cdecl asm_target_0043a277();
#define VA_asm_target_0043a277 0x0043a277
extern "C" void __cdecl asm_target_0043a37e();
#define VA_asm_target_0043a37e 0x0043a37e
extern "C" void __cdecl asm_target_0043a45e();
#define VA_asm_target_0043a45e 0x0043a45e
extern "C" void __cdecl asm_target_0043a464();
#define VA_asm_target_0043a464 0x0043a464
extern "C" void __cdecl asm_target_0043abcf();
#define VA_asm_target_0043abcf 0x0043abcf
extern "C" void __cdecl asm_target_0043ac69();
#define VA_asm_target_0043ac69 0x0043ac69
extern "C" void __cdecl asm_target_0043b010();
#define VA_asm_target_0043b010 0x0043b010
extern "C" void __cdecl asm_target_0043b0ad();
#define VA_asm_target_0043b0ad 0x0043b0ad
extern "C" void __cdecl asm_target_0043b0c9();
#define VA_asm_target_0043b0c9 0x0043b0c9
extern "C" void __cdecl asm_target_0043b0fb();
#define VA_asm_target_0043b0fb 0x0043b0fb
extern "C" void __cdecl asm_target_0043b27f();
#define VA_asm_target_0043b27f 0x0043b27f
extern "C" void __cdecl asm_target_0043b283();
#define VA_asm_target_0043b283 0x0043b283
extern "C" void __cdecl asm_target_0043b287();
#define VA_asm_target_0043b287 0x0043b287
extern "C" void __cdecl asm_target_0043b2a2();
#define VA_asm_target_0043b2a2 0x0043b2a2
extern "C" void __cdecl asm_target_0043b386();
#define VA_asm_target_0043b386 0x0043b386
extern "C" void __cdecl asm_target_0043b5d8();
#define VA_asm_target_0043b5d8 0x0043b5d8
extern "C" void __cdecl asm_target_0043c85c();
#define VA_asm_target_0043c85c 0x0043c85c
extern "C" void __cdecl asm_target_0043c865();
#define VA_asm_target_0043c865 0x0043c865
extern "C" void __cdecl asm_target_0043ca69();
#define VA_asm_target_0043ca69 0x0043ca69
extern "C" void __cdecl asm_target_0043ca77();
#define VA_asm_target_0043ca77 0x0043ca77
extern "C" void __cdecl asm_target_0043ca78();
#define VA_asm_target_0043ca78 0x0043ca78
extern "C" void __cdecl asm_target_0043ccec();
#define VA_asm_target_0043ccec 0x0043ccec
extern "C" void __cdecl asm_target_0043cfb8();
#define VA_asm_target_0043cfb8 0x0043cfb8
extern "C" void __cdecl asm_target_0043d010();
#define VA_asm_target_0043d010 0x0043d010
extern "C" void __cdecl asm_target_0043d02a();
#define VA_asm_target_0043d02a 0x0043d02a
extern "C" void __cdecl asm_target_0043d247();
#define VA_asm_target_0043d247 0x0043d247
extern "C" void __cdecl asm_target_0043d45e();
#define VA_asm_target_0043d45e 0x0043d45e
extern "C" void __cdecl asm_target_0043d466();
#define VA_asm_target_0043d466 0x0043d466
extern "C" void __cdecl asm_target_0043d625();
#define VA_asm_target_0043d625 0x0043d625
extern "C" void __cdecl asm_target_0043d938();
#define VA_asm_target_0043d938 0x0043d938
extern "C" void __cdecl asm_target_0043da67();
#define VA_asm_target_0043da67 0x0043da67
extern "C" void __cdecl asm_target_0043db5e();
#define VA_asm_target_0043db5e 0x0043db5e
extern "C" void __cdecl asm_target_0043dc83();
#define VA_asm_target_0043dc83 0x0043dc83
extern "C" void __cdecl asm_target_0043de18();
#define VA_asm_target_0043de18 0x0043de18
extern "C" void __cdecl asm_target_0043df39();
#define VA_asm_target_0043df39 0x0043df39
extern "C" void __cdecl asm_target_0043df6b();
#define VA_asm_target_0043df6b 0x0043df6b
extern "C" void __cdecl asm_target_0043e0e5();
#define VA_asm_target_0043e0e5 0x0043e0e5
extern "C" void __cdecl asm_target_0043e123();
#define VA_asm_target_0043e123 0x0043e123
extern "C" void __cdecl asm_target_0043e13e();
#define VA_asm_target_0043e13e 0x0043e13e
extern "C" void __cdecl asm_target_0043e17a();
#define VA_asm_target_0043e17a 0x0043e17a
extern "C" void __cdecl asm_target_0043e18d();
#define VA_asm_target_0043e18d 0x0043e18d
extern "C" void __cdecl asm_target_0043e1c7();
#define VA_asm_target_0043e1c7 0x0043e1c7
extern "C" void __cdecl asm_target_0043e204();
#define VA_asm_target_0043e204 0x0043e204
extern "C" void __cdecl asm_target_0043e20f();
#define VA_asm_target_0043e20f 0x0043e20f
extern "C" void __cdecl asm_target_0043e212();
#define VA_asm_target_0043e212 0x0043e212
extern "C" void __cdecl asm_target_0043e243();
#define VA_asm_target_0043e243 0x0043e243
extern "C" void __cdecl asm_target_0043e348();
#define VA_asm_target_0043e348 0x0043e348
extern "C" void __cdecl asm_target_0043e36b();
#define VA_asm_target_0043e36b 0x0043e36b
extern "C" void __cdecl asm_target_0043e3c0();
#define VA_asm_target_0043e3c0 0x0043e3c0
extern "C" void __cdecl asm_target_0043e6fe();
#define VA_asm_target_0043e6fe 0x0043e6fe
extern "C" void __cdecl asm_target_0043e7ce();
#define VA_asm_target_0043e7ce 0x0043e7ce
extern "C" void __cdecl asm_target_0043e895();
#define VA_asm_target_0043e895 0x0043e895
extern "C" void __cdecl asm_target_0043e9cb();
#define VA_asm_target_0043e9cb 0x0043e9cb
extern "C" void __cdecl asm_target_0043e9cc();
#define VA_asm_target_0043e9cc 0x0043e9cc
extern "C" void __cdecl asm_target_0043ea93();
#define VA_asm_target_0043ea93 0x0043ea93
extern "C" void __cdecl asm_target_0043ea9d();
#define VA_asm_target_0043ea9d 0x0043ea9d
extern "C" void __cdecl asm_target_0043ec07();
#define VA_asm_target_0043ec07 0x0043ec07
extern "C" void __cdecl asm_target_0043eea4();
#define VA_asm_target_0043eea4 0x0043eea4
extern "C" void __cdecl asm_target_0043f00d();
#define VA_asm_target_0043f00d 0x0043f00d
extern "C" void __cdecl asm_target_0043f52f();
#define VA_asm_target_0043f52f 0x0043f52f
extern "C" void __cdecl asm_target_0043f532();
#define VA_asm_target_0043f532 0x0043f532
extern "C" void __cdecl asm_target_0043f546();
#define VA_asm_target_0043f546 0x0043f546
extern "C" void __cdecl asm_target_0043f62d();
#define VA_asm_target_0043f62d 0x0043f62d
extern "C" void __cdecl asm_target_00440dda();
#define VA_asm_target_00440dda 0x00440dda
extern "C" void __cdecl asm_target_00440e2b();
#define VA_asm_target_00440e2b 0x00440e2b
extern "C" void __cdecl asm_target_00440e35();
#define VA_asm_target_00440e35 0x00440e35
extern "C" void __cdecl asm_target_00440e42();
#define VA_asm_target_00440e42 0x00440e42
extern "C" void __cdecl asm_target_00441308();
#define VA_asm_target_00441308 0x00441308
extern "C" void __cdecl asm_target_0044133e();
#define VA_asm_target_0044133e 0x0044133e
extern "C" void __cdecl asm_target_004416eb();
#define VA_asm_target_004416eb 0x004416eb
extern "C" void __cdecl asm_target_004418b4();
#define VA_asm_target_004418b4 0x004418b4
extern "C" void __cdecl asm_target_00441a04();
#define VA_asm_target_00441a04 0x00441a04
extern "C" void __cdecl asm_target_00441ba0();
#define VA_asm_target_00441ba0 0x00441ba0
extern "C" void __cdecl asm_target_00441d0e();
#define VA_asm_target_00441d0e 0x00441d0e
extern "C" void __cdecl asm_target_00442509();
#define VA_asm_target_00442509 0x00442509
extern "C" void __cdecl asm_target_00442aa8();
#define VA_asm_target_00442aa8 0x00442aa8
extern "C" void __cdecl asm_target_00442abb();
#define VA_asm_target_00442abb 0x00442abb
extern "C" void __cdecl asm_target_00442f08();
#define VA_asm_target_00442f08 0x00442f08
extern "C" void __cdecl asm_target_00442f1b();
#define VA_asm_target_00442f1b 0x00442f1b
extern "C" void __cdecl asm_target_00443177();
#define VA_asm_target_00443177 0x00443177
extern "C" void __cdecl asm_target_00443246();
#define VA_asm_target_00443246 0x00443246
extern "C" void __cdecl asm_target_00443377();
#define VA_asm_target_00443377 0x00443377
extern "C" void __cdecl asm_target_0044343b();
#define VA_asm_target_0044343b 0x0044343b
extern "C" void __cdecl asm_target_0044357e();
#define VA_asm_target_0044357e 0x0044357e
extern "C" void __cdecl asm_target_00443640();
#define VA_asm_target_00443640 0x00443640
extern "C" void __cdecl asm_target_00443f6c();
#define VA_asm_target_00443f6c 0x00443f6c
extern "C" void __cdecl asm_target_00444128();
#define VA_asm_target_00444128 0x00444128
extern "C" void __cdecl asm_target_00444207();
#define VA_asm_target_00444207 0x00444207
extern "C" void __cdecl asm_target_00444337();
#define VA_asm_target_00444337 0x00444337
extern "C" void __cdecl asm_target_00444612();
#define VA_asm_target_00444612 0x00444612
extern "C" void __cdecl asm_target_004446f7();
#define VA_asm_target_004446f7 0x004446f7
extern "C" void __cdecl asm_target_0044489f();
#define VA_asm_target_0044489f 0x0044489f
extern "C" void __cdecl asm_target_004453f0();
#define VA_asm_target_004453f0 0x004453f0
extern "C" void __cdecl asm_target_0044571a();
#define VA_asm_target_0044571a 0x0044571a
extern "C" void __cdecl asm_target_00446620();
#define VA_asm_target_00446620 0x00446620
extern "C" void __cdecl asm_target_00446640();
#define VA_asm_target_00446640 0x00446640
extern "C" void __cdecl asm_target_0044676d();
#define VA_asm_target_0044676d 0x0044676d
extern "C" void __cdecl asm_target_00446782();
#define VA_asm_target_00446782 0x00446782
extern "C" void __cdecl asm_target_004467b0();
#define VA_asm_target_004467b0 0x004467b0
extern "C" void __cdecl asm_target_00446934();
#define VA_asm_target_00446934 0x00446934
extern "C" void __cdecl asm_target_00446948();
#define VA_asm_target_00446948 0x00446948
extern "C" void __cdecl asm_target_00446974();
#define VA_asm_target_00446974 0x00446974
extern "C" void __cdecl asm_target_00446990();
#define VA_asm_target_00446990 0x00446990
extern "C" void __cdecl asm_target_00446af8();
#define VA_asm_target_00446af8 0x00446af8
extern "C" void __cdecl asm_target_00446b0c();
#define VA_asm_target_00446b0c 0x00446b0c
extern "C" void __cdecl asm_target_00446b1d();
#define VA_asm_target_00446b1d 0x00446b1d
extern "C" void __cdecl asm_target_00446b20();
#define VA_asm_target_00446b20 0x00446b20
extern "C" void __cdecl asm_target_00447250();
#define VA_asm_target_00447250 0x00447250
extern "C" void __cdecl asm_target_00447258();
#define VA_asm_target_00447258 0x00447258
extern "C" void __cdecl asm_target_00447588();
#define VA_asm_target_00447588 0x00447588
extern "C" void __cdecl asm_target_004475de();
#define VA_asm_target_004475de 0x004475de
extern "C" void __cdecl asm_target_004476b8();
#define VA_asm_target_004476b8 0x004476b8
extern "C" void __cdecl asm_target_004478ff();
#define VA_asm_target_004478ff 0x004478ff
extern "C" void __cdecl asm_target_00447e50();
#define VA_asm_target_00447e50 0x00447e50
extern "C" void __cdecl asm_target_00447e77();
#define VA_asm_target_00447e77 0x00447e77
extern "C" void __cdecl asm_target_00447ea5();
#define VA_asm_target_00447ea5 0x00447ea5
extern "C" void __cdecl asm_target_004480af();
#define VA_asm_target_004480af 0x004480af
extern "C" void __cdecl asm_target_00448113();
#define VA_asm_target_00448113 0x00448113
extern "C" void __cdecl asm_target_00448201();
#define VA_asm_target_00448201 0x00448201
extern "C" void __cdecl asm_target_0044825e();
#define VA_asm_target_0044825e 0x0044825e
extern "C" void __cdecl asm_target_00448357();
#define VA_asm_target_00448357 0x00448357
extern "C" void __cdecl asm_target_0044843b();
#define VA_asm_target_0044843b 0x0044843b
extern "C" void __cdecl asm_target_0044843c();
#define VA_asm_target_0044843c 0x0044843c
extern "C" void __cdecl asm_target_004485c1();
#define VA_asm_target_004485c1 0x004485c1
extern "C" void __cdecl asm_target_00449439();
#define VA_asm_target_00449439 0x00449439
extern "C" void __cdecl asm_target_004494b0();
#define VA_asm_target_004494b0 0x004494b0
extern "C" void __cdecl asm_target_00449528();
#define VA_asm_target_00449528 0x00449528
extern "C" void __cdecl asm_target_00449794();
#define VA_asm_target_00449794 0x00449794
extern "C" void __cdecl asm_target_00449c40();
#define VA_asm_target_00449c40 0x00449c40
extern "C" void __cdecl asm_target_00449cf0();
#define VA_asm_target_00449cf0 0x00449cf0
extern "C" void __cdecl asm_target_00449e12();
#define VA_asm_target_00449e12 0x00449e12
extern "C" void __cdecl asm_target_0044a32e();
#define VA_asm_target_0044a32e 0x0044a32e
extern "C" void __cdecl asm_target_0044a397();
#define VA_asm_target_0044a397 0x0044a397
extern "C" void __cdecl asm_target_0044a3c2();
#define VA_asm_target_0044a3c2 0x0044a3c2
extern "C" void __cdecl asm_target_0044a5cc();
#define VA_asm_target_0044a5cc 0x0044a5cc
extern "C" void __cdecl asm_target_0044a754();
#define VA_asm_target_0044a754 0x0044a754
extern "C" void __cdecl asm_target_0044a8b3();
#define VA_asm_target_0044a8b3 0x0044a8b3
extern "C" void __cdecl asm_target_0044ab31();
#define VA_asm_target_0044ab31 0x0044ab31
extern "C" void __cdecl asm_target_0044ac90();
#define VA_asm_target_0044ac90 0x0044ac90
extern "C" void __cdecl asm_target_0044ae85();
#define VA_asm_target_0044ae85 0x0044ae85
extern "C" void __cdecl asm_target_0044afe4();
#define VA_asm_target_0044afe4 0x0044afe4
extern "C" void __cdecl asm_target_0044b15f();
#define VA_asm_target_0044b15f 0x0044b15f
extern "C" void __cdecl asm_target_0044b1d8();
#define VA_asm_target_0044b1d8 0x0044b1d8
extern "C" void __cdecl asm_target_0044b1fc();
#define VA_asm_target_0044b1fc 0x0044b1fc
extern "C" void __cdecl asm_target_0044b205();
#define VA_asm_target_0044b205 0x0044b205
extern "C" void __cdecl asm_target_0044b2ad();
#define VA_asm_target_0044b2ad 0x0044b2ad
extern "C" void __cdecl asm_target_0044b33c();
#define VA_asm_target_0044b33c 0x0044b33c
extern "C" void __cdecl asm_target_0044b345();
#define VA_asm_target_0044b345 0x0044b345
extern "C" void __cdecl asm_target_0044b41f();
#define VA_asm_target_0044b41f 0x0044b41f
extern "C" void __cdecl asm_target_0044b4a8();
#define VA_asm_target_0044b4a8 0x0044b4a8
extern "C" void __cdecl asm_target_0044bccb();
#define VA_asm_target_0044bccb 0x0044bccb
extern "C" void __cdecl asm_target_0044bdfc();
#define VA_asm_target_0044bdfc 0x0044bdfc
extern "C" void __cdecl asm_target_0044c522();
#define VA_asm_target_0044c522 0x0044c522
extern "C" void __cdecl asm_target_0044c54a();
#define VA_asm_target_0044c54a 0x0044c54a
extern "C" void __cdecl asm_target_0044cae5();
#define VA_asm_target_0044cae5 0x0044cae5
extern "C" void __cdecl asm_target_0044cb12();
#define VA_asm_target_0044cb12 0x0044cb12
extern "C" void __cdecl asm_target_0044cb8e();
#define VA_asm_target_0044cb8e 0x0044cb8e
extern "C" void __cdecl asm_target_0044cdd9();
#define VA_asm_target_0044cdd9 0x0044cdd9
extern "C" void __cdecl asm_target_0044ce5b();
#define VA_asm_target_0044ce5b 0x0044ce5b
extern "C" void __cdecl asm_target_0044cf90();
#define VA_asm_target_0044cf90 0x0044cf90
extern "C" void __cdecl asm_target_0044d03c();
#define VA_asm_target_0044d03c 0x0044d03c
extern "C" void __cdecl asm_target_0044d068();
#define VA_asm_target_0044d068 0x0044d068
extern "C" void __cdecl asm_target_0044d2d2();
#define VA_asm_target_0044d2d2 0x0044d2d2
extern "C" void __cdecl asm_target_0044d2e9();
#define VA_asm_target_0044d2e9 0x0044d2e9
extern "C" void __cdecl asm_target_0044d2ea();
#define VA_asm_target_0044d2ea 0x0044d2ea
extern "C" void __cdecl asm_target_0044d8d7();
#define VA_asm_target_0044d8d7 0x0044d8d7
extern "C" void __cdecl asm_target_0044da33();
#define VA_asm_target_0044da33 0x0044da33
extern "C" void __cdecl asm_target_0044dac0();
#define VA_asm_target_0044dac0 0x0044dac0
extern "C" void __cdecl asm_target_0044db98();
#define VA_asm_target_0044db98 0x0044db98
extern "C" void __cdecl asm_target_0044db9d();
#define VA_asm_target_0044db9d 0x0044db9d
extern "C" void __cdecl asm_target_0044dc99();
#define VA_asm_target_0044dc99 0x0044dc99
extern "C" void __cdecl asm_target_0044ddfe();
#define VA_asm_target_0044ddfe 0x0044ddfe
extern "C" void __cdecl asm_target_0044dfe5();
#define VA_asm_target_0044dfe5 0x0044dfe5
extern "C" void __cdecl asm_target_0044e08e();
#define VA_asm_target_0044e08e 0x0044e08e
extern "C" void __cdecl asm_target_0044f05c();
#define VA_asm_target_0044f05c 0x0044f05c
extern "C" void __cdecl asm_target_0044faa2();
#define VA_asm_target_0044faa2 0x0044faa2
extern "C" void __cdecl asm_target_0044fb57();
#define VA_asm_target_0044fb57 0x0044fb57
extern "C" void __cdecl asm_target_0044fb5d();
#define VA_asm_target_0044fb5d 0x0044fb5d
extern "C" void __cdecl asm_target_0044fb68();
#define VA_asm_target_0044fb68 0x0044fb68
extern "C" void __cdecl asm_target_0044fb77();
#define VA_asm_target_0044fb77 0x0044fb77
extern "C" void __cdecl asm_target_0044fb81();
#define VA_asm_target_0044fb81 0x0044fb81
extern "C" void __cdecl asm_target_0044fb85();
#define VA_asm_target_0044fb85 0x0044fb85
extern "C" void __cdecl asm_target_0044fb96();
#define VA_asm_target_0044fb96 0x0044fb96
extern "C" void __cdecl asm_target_0044fbb0();
#define VA_asm_target_0044fbb0 0x0044fbb0
extern "C" void __cdecl asm_target_0044fbb2();
#define VA_asm_target_0044fbb2 0x0044fbb2
extern "C" void __cdecl asm_target_0044feef();
#define VA_asm_target_0044feef 0x0044feef
extern "C" void __cdecl asm_target_00450181();
#define VA_asm_target_00450181 0x00450181
extern "C" void __cdecl asm_target_00450348();
#define VA_asm_target_00450348 0x00450348
extern "C" void __cdecl asm_target_00450442();
#define VA_asm_target_00450442 0x00450442
extern "C" void __cdecl asm_target_0045247f();
#define VA_asm_target_0045247f 0x0045247f
extern "C" void __cdecl asm_target_0045248d();
#define VA_asm_target_0045248d 0x0045248d
extern "C" void __cdecl asm_target_004525c4();
#define VA_asm_target_004525c4 0x004525c4
extern "C" void __cdecl asm_target_004529f3();
#define VA_asm_target_004529f3 0x004529f3
extern "C" void __cdecl asm_target_004529ff();
#define VA_asm_target_004529ff 0x004529ff
extern "C" void __cdecl asm_target_00452a0f();
#define VA_asm_target_00452a0f 0x00452a0f
extern "C" void __cdecl asm_target_00452a7c();
#define VA_asm_target_00452a7c 0x00452a7c
extern "C" void __cdecl asm_target_00452ced();
#define VA_asm_target_00452ced 0x00452ced
extern "C" void __cdecl asm_target_00452cef();
#define VA_asm_target_00452cef 0x00452cef
extern "C" void __cdecl asm_target_004531d2();
#define VA_asm_target_004531d2 0x004531d2
extern "C" void __cdecl asm_target_00453221();
#define VA_asm_target_00453221 0x00453221
extern "C" void __cdecl asm_target_00453e3c();
#define VA_asm_target_00453e3c 0x00453e3c
extern "C" void __cdecl asm_target_00453ecd();
#define VA_asm_target_00453ecd 0x00453ecd
extern "C" void __cdecl asm_target_00453fca();
#define VA_asm_target_00453fca 0x00453fca
extern "C" void __cdecl asm_target_00453fd8();
#define VA_asm_target_00453fd8 0x00453fd8
extern "C" void __cdecl asm_target_00453fd9();
#define VA_asm_target_00453fd9 0x00453fd9
extern "C" void __cdecl asm_target_00454195();
#define VA_asm_target_00454195 0x00454195
extern "C" void __cdecl asm_target_00454323();
#define VA_asm_target_00454323 0x00454323
extern "C" void __cdecl asm_target_00454335();
#define VA_asm_target_00454335 0x00454335
extern "C" void __cdecl asm_target_0045433c();
#define VA_asm_target_0045433c 0x0045433c
extern "C" void __cdecl asm_target_004543f1();
#define VA_asm_target_004543f1 0x004543f1
extern "C" void __cdecl asm_target_00454471();
#define VA_asm_target_00454471 0x00454471
extern "C" void __cdecl asm_target_00454474();
#define VA_asm_target_00454474 0x00454474
extern "C" void __cdecl asm_target_00454549();
#define VA_asm_target_00454549 0x00454549
extern "C" void __cdecl asm_target_0045458d();
#define VA_asm_target_0045458d 0x0045458d
extern "C" void __cdecl asm_target_0045458f();
#define VA_asm_target_0045458f 0x0045458f
extern "C" void __cdecl asm_target_00454594();
#define VA_asm_target_00454594 0x00454594
extern "C" void __cdecl asm_target_004545d6();
#define VA_asm_target_004545d6 0x004545d6
extern "C" void __cdecl asm_target_00454618();
#define VA_asm_target_00454618 0x00454618
extern "C" void __cdecl asm_target_004546bc();
#define VA_asm_target_004546bc 0x004546bc
extern "C" void __cdecl asm_target_004546d4();
#define VA_asm_target_004546d4 0x004546d4
extern "C" void __cdecl asm_target_00454786();
#define VA_asm_target_00454786 0x00454786
extern "C" void __cdecl asm_target_004547bc();
#define VA_asm_target_004547bc 0x004547bc
extern "C" void __cdecl asm_target_00454823();
#define VA_asm_target_00454823 0x00454823
extern "C" void __cdecl asm_target_0045482b();
#define VA_asm_target_0045482b 0x0045482b
extern "C" void __cdecl asm_target_0045482f();
#define VA_asm_target_0045482f 0x0045482f
extern "C" void __cdecl asm_target_00454833();
#define VA_asm_target_00454833 0x00454833
extern "C" void __cdecl asm_target_00454837();
#define VA_asm_target_00454837 0x00454837
extern "C" void __cdecl asm_target_0045483b();
#define VA_asm_target_0045483b 0x0045483b
extern "C" void __cdecl asm_target_0045483f();
#define VA_asm_target_0045483f 0x0045483f
extern "C" void __cdecl asm_target_00454843();
#define VA_asm_target_00454843 0x00454843
extern "C" void __cdecl asm_target_00454847();
#define VA_asm_target_00454847 0x00454847
extern "C" void __cdecl asm_target_0045484b();
#define VA_asm_target_0045484b 0x0045484b
extern "C" void __cdecl asm_target_0045484f();
#define VA_asm_target_0045484f 0x0045484f
extern "C" void __cdecl asm_target_00454853();
#define VA_asm_target_00454853 0x00454853
extern "C" void __cdecl asm_target_00454857();
#define VA_asm_target_00454857 0x00454857
extern "C" void __cdecl asm_target_0045485b();
#define VA_asm_target_0045485b 0x0045485b
extern "C" void __cdecl asm_target_00454958();
#define VA_asm_target_00454958 0x00454958
extern "C" void __cdecl asm_target_004549ec();
#define VA_asm_target_004549ec 0x004549ec
extern "C" void __cdecl asm_target_00454b68();
#define VA_asm_target_00454b68 0x00454b68
extern "C" void __cdecl asm_target_00454b74();
#define VA_asm_target_00454b74 0x00454b74
extern "C" void __cdecl asm_target_00454bb5();
#define VA_asm_target_00454bb5 0x00454bb5
extern "C" void __cdecl asm_target_00454cd9();
#define VA_asm_target_00454cd9 0x00454cd9
extern "C" void __cdecl asm_target_00454e1d();
#define VA_asm_target_00454e1d 0x00454e1d
extern "C" void __cdecl asm_target_00454f29();
#define VA_asm_target_00454f29 0x00454f29
extern "C" void __cdecl asm_target_00455176();
#define VA_asm_target_00455176 0x00455176
extern "C" void __cdecl asm_target_004551c1();
#define VA_asm_target_004551c1 0x004551c1
extern "C" void __cdecl asm_target_004551e1();
#define VA_asm_target_004551e1 0x004551e1
extern "C" void __cdecl asm_target_0045521c();
#define VA_asm_target_0045521c 0x0045521c
extern "C" void __cdecl asm_target_0045522d();
#define VA_asm_target_0045522d 0x0045522d
extern "C" void __cdecl asm_target_00455231();
#define VA_asm_target_00455231 0x00455231
extern "C" void __cdecl asm_target_00455238();
#define VA_asm_target_00455238 0x00455238
extern "C" void __cdecl asm_target_004552bc();
#define VA_asm_target_004552bc 0x004552bc
extern "C" void __cdecl asm_target_00455303();
#define VA_asm_target_00455303 0x00455303
extern "C" void __cdecl asm_target_00455367();
#define VA_asm_target_00455367 0x00455367
extern "C" void __cdecl asm_target_00455372();
#define VA_asm_target_00455372 0x00455372
extern "C" void __cdecl asm_target_004553ba();
#define VA_asm_target_004553ba 0x004553ba
extern "C" void __cdecl asm_target_004553c8();
#define VA_asm_target_004553c8 0x004553c8
extern "C" void __cdecl asm_target_004553f3();
#define VA_asm_target_004553f3 0x004553f3
extern "C" void __cdecl asm_target_0045541f();
#define VA_asm_target_0045541f 0x0045541f
extern "C" void __cdecl asm_target_00455439();
#define VA_asm_target_00455439 0x00455439
extern "C" void __cdecl asm_target_00455463();
#define VA_asm_target_00455463 0x00455463
extern "C" void __cdecl asm_target_0045548b();
#define VA_asm_target_0045548b 0x0045548b
extern "C" void __cdecl asm_target_0045553e();
#define VA_asm_target_0045553e 0x0045553e
extern "C" void __cdecl asm_target_00455541();
#define VA_asm_target_00455541 0x00455541
extern "C" void __cdecl asm_target_00455636();
#define VA_asm_target_00455636 0x00455636
extern "C" void __cdecl asm_target_00455649();
#define VA_asm_target_00455649 0x00455649
extern "C" void __cdecl asm_target_00455656();
#define VA_asm_target_00455656 0x00455656
extern "C" void __cdecl asm_target_00455658();
#define VA_asm_target_00455658 0x00455658
extern "C" void __cdecl asm_target_004556c3();
#define VA_asm_target_004556c3 0x004556c3
extern "C" void __cdecl asm_target_00455988();
#define VA_asm_target_00455988 0x00455988
extern "C" void __cdecl asm_target_00455a88();
#define VA_asm_target_00455a88 0x00455a88
extern "C" void __cdecl asm_target_00455bf0();
#define VA_asm_target_00455bf0 0x00455bf0
extern "C" void __cdecl asm_target_00455d04();
#define VA_asm_target_00455d04 0x00455d04
extern "C" void __cdecl asm_target_00455d41();
#define VA_asm_target_00455d41 0x00455d41
extern "C" void __cdecl asm_target_00455d42();
#define VA_asm_target_00455d42 0x00455d42
extern "C" void __cdecl asm_target_00455f6f();
#define VA_asm_target_00455f6f 0x00455f6f
extern "C" void __cdecl asm_target_00455fd7();
#define VA_asm_target_00455fd7 0x00455fd7
extern "C" void __cdecl asm_target_00455fd8();
#define VA_asm_target_00455fd8 0x00455fd8
extern "C" void __cdecl asm_target_00456057();
#define VA_asm_target_00456057 0x00456057
extern "C" void __cdecl asm_target_0045611a();
#define VA_asm_target_0045611a 0x0045611a
extern "C" void __cdecl asm_target_0045611f();
#define VA_asm_target_0045611f 0x0045611f
extern "C" void __cdecl asm_target_00456121();
#define VA_asm_target_00456121 0x00456121
extern "C" void __cdecl asm_target_00456135();
#define VA_asm_target_00456135 0x00456135
extern "C" void __cdecl asm_target_00456139();
#define VA_asm_target_00456139 0x00456139
extern "C" void __cdecl asm_target_004562ef();
#define VA_asm_target_004562ef 0x004562ef
extern "C" void __cdecl asm_target_0045630d();
#define VA_asm_target_0045630d 0x0045630d
extern "C" void __cdecl asm_target_00456316();
#define VA_asm_target_00456316 0x00456316
extern "C" void __cdecl asm_target_00456318();
#define VA_asm_target_00456318 0x00456318
extern "C" void __cdecl asm_target_004564ed();
#define VA_asm_target_004564ed 0x004564ed
extern "C" int __cdecl asm_target_0045694b(int c);
#define VA_asm_target_0045694b 0x0045694b
extern "C" void __cdecl asm_target_00456cf1();
#define VA_asm_target_00456cf1 0x00456cf1
extern "C" void __cdecl asm_target_00456dec();
#define VA_asm_target_00456dec 0x00456dec
extern "C" void __cdecl asm_target_00456e8a();
#define VA_asm_target_00456e8a 0x00456e8a
extern "C" void __cdecl asm_target_00456f98();
#define VA_asm_target_00456f98 0x00456f98
extern "C" void __cdecl asm_target_00457133();
#define VA_asm_target_00457133 0x00457133
extern "C" void __cdecl asm_target_0045715f();
#define VA_asm_target_0045715f 0x0045715f
extern "C" void __cdecl asm_target_00457247();
#define VA_asm_target_00457247 0x00457247
extern "C" void __cdecl asm_target_00457391();
#define VA_asm_target_00457391 0x00457391
extern "C" void __cdecl asm_target_004573d6();
#define VA_asm_target_004573d6 0x004573d6
extern "C" void __cdecl asm_target_004574a3();
#define VA_asm_target_004574a3 0x004574a3
extern "C" void __cdecl asm_target_004574f1();
#define VA_asm_target_004574f1 0x004574f1
extern "C" void __cdecl asm_target_00457533();
#define VA_asm_target_00457533 0x00457533
extern "C" void __cdecl asm_target_00457538();
#define VA_asm_target_00457538 0x00457538
extern "C" void __cdecl asm_target_0045753e();
#define VA_asm_target_0045753e 0x0045753e
extern "C" void __cdecl asm_target_00457540();
#define VA_asm_target_00457540 0x00457540
extern "C" void __cdecl asm_target_00457541();
#define VA_asm_target_00457541 0x00457541
extern "C" void __cdecl asm_target_00457911();
#define VA_asm_target_00457911 0x00457911
extern "C" void __cdecl asm_target_0045791f();
#define VA_asm_target_0045791f 0x0045791f
extern "C" void __cdecl asm_target_00457924();
#define VA_asm_target_00457924 0x00457924
extern "C" void __cdecl asm_target_0045792d();
#define VA_asm_target_0045792d 0x0045792d
extern "C" void __cdecl asm_target_0045796c();
#define VA_asm_target_0045796c 0x0045796c
extern "C" void __cdecl asm_target_00457981();
#define VA_asm_target_00457981 0x00457981
extern "C" void __cdecl asm_target_00457a1e();
#define VA_asm_target_00457a1e 0x00457a1e
extern "C" void __cdecl asm_target_00457ade();
#define VA_asm_target_00457ade 0x00457ade
extern "C" void __cdecl asm_target_00457ae4();
#define VA_asm_target_00457ae4 0x00457ae4
extern "C" void __cdecl asm_target_00457bb7();
#define VA_asm_target_00457bb7 0x00457bb7
extern "C" void __cdecl asm_target_00457c69();
#define VA_asm_target_00457c69 0x00457c69
extern "C" void __cdecl asm_target_00457c9a();
#define VA_asm_target_00457c9a 0x00457c9a
extern "C" void __cdecl asm_target_00457dd4();
#define VA_asm_target_00457dd4 0x00457dd4
extern "C" void __cdecl asm_target_00457fa4();
#define VA_asm_target_00457fa4 0x00457fa4
extern "C" void __cdecl asm_target_00457ff6();
#define VA_asm_target_00457ff6 0x00457ff6
extern "C" void __cdecl asm_target_00457ffc();
#define VA_asm_target_00457ffc 0x00457ffc
extern "C" void __cdecl asm_target_0045800e();
#define VA_asm_target_0045800e 0x0045800e
extern "C" void __cdecl asm_target_00458022();
#define VA_asm_target_00458022 0x00458022
extern "C" void __cdecl asm_target_00458032();
#define VA_asm_target_00458032 0x00458032
extern "C" void __cdecl asm_target_00458056();
#define VA_asm_target_00458056 0x00458056
extern "C" void __cdecl asm_target_00458159();
#define VA_asm_target_00458159 0x00458159
extern "C" void __cdecl asm_target_00458183();
#define VA_asm_target_00458183 0x00458183
extern "C" void __cdecl asm_target_0045818e();
#define VA_asm_target_0045818e 0x0045818e
extern "C" void __cdecl asm_target_0045831c();
#define VA_asm_target_0045831c 0x0045831c
extern "C" void __cdecl asm_target_00458321();
#define VA_asm_target_00458321 0x00458321
extern "C" void __cdecl asm_target_00458406();
#define VA_asm_target_00458406 0x00458406
extern "C" void __cdecl asm_target_00458409();
#define VA_asm_target_00458409 0x00458409
extern "C" void __cdecl asm_target_00458414();
#define VA_asm_target_00458414 0x00458414
extern "C" void __cdecl asm_target_0045841a();
#define VA_asm_target_0045841a 0x0045841a
extern "C" void __cdecl asm_target_00458433();
#define VA_asm_target_00458433 0x00458433
extern "C" void __cdecl asm_target_00458481();
#define VA_asm_target_00458481 0x00458481
extern "C" void __cdecl asm_target_00458488();
#define VA_asm_target_00458488 0x00458488
extern "C" void __cdecl asm_target_004584c9();
#define VA_asm_target_004584c9 0x004584c9
extern "C" void __cdecl asm_target_004584cf();
#define VA_asm_target_004584cf 0x004584cf
extern "C" void __cdecl asm_target_004584e9();
#define VA_asm_target_004584e9 0x004584e9
extern "C" void __cdecl asm_target_00458591();
#define VA_asm_target_00458591 0x00458591
extern "C" void __cdecl asm_target_00458611();
#define VA_asm_target_00458611 0x00458611
extern "C" void __cdecl asm_target_00458642();
#define VA_asm_target_00458642 0x00458642
extern "C" void __cdecl asm_target_0045864f();
#define VA_asm_target_0045864f 0x0045864f
extern "C" void __cdecl asm_target_0045872f();
#define VA_asm_target_0045872f 0x0045872f
extern "C" void __cdecl asm_target_0045873e();
#define VA_asm_target_0045873e 0x0045873e
extern "C" void __cdecl asm_target_0045877c();
#define VA_asm_target_0045877c 0x0045877c
extern "C" void __cdecl asm_target_004587b3();
#define VA_asm_target_004587b3 0x004587b3
extern "C" void __cdecl asm_target_0045881f();
#define VA_asm_target_0045881f 0x0045881f
extern "C" void __cdecl asm_target_0045883c();
#define VA_asm_target_0045883c 0x0045883c
extern "C" void __cdecl asm_target_0045885e();
#define VA_asm_target_0045885e 0x0045885e
extern "C" void __cdecl asm_target_00458969();
#define VA_asm_target_00458969 0x00458969
extern "C" void __cdecl asm_target_004589a5();
#define VA_asm_target_004589a5 0x004589a5
extern "C" void __cdecl asm_target_004589cb();
#define VA_asm_target_004589cb 0x004589cb
extern "C" void __cdecl asm_target_004589d7();
#define VA_asm_target_004589d7 0x004589d7
extern "C" void __cdecl asm_target_00458a59();
#define VA_asm_target_00458a59 0x00458a59
extern "C" void __cdecl asm_target_00458a60();
#define VA_asm_target_00458a60 0x00458a60
extern "C" void __cdecl asm_target_00458a8f();
#define VA_asm_target_00458a8f 0x00458a8f
extern "C" void __cdecl asm_target_00458a98();
#define VA_asm_target_00458a98 0x00458a98
extern "C" void __cdecl asm_target_00458ab5();
#define VA_asm_target_00458ab5 0x00458ab5
extern "C" void __cdecl asm_target_00458ad7();
#define VA_asm_target_00458ad7 0x00458ad7
extern "C" void __cdecl asm_target_00458adb();
#define VA_asm_target_00458adb 0x00458adb
extern "C" void __cdecl asm_target_00458b0b();
#define VA_asm_target_00458b0b 0x00458b0b
extern "C" void __cdecl asm_target_00458b0e();
#define VA_asm_target_00458b0e 0x00458b0e
extern "C" void __cdecl asm_target_00458b10();
#define VA_asm_target_00458b10 0x00458b10
extern "C" void __cdecl asm_target_00459032();
#define VA_asm_target_00459032 0x00459032
extern "C" void __cdecl asm_target_00459057();
#define VA_asm_target_00459057 0x00459057
extern "C" void __cdecl asm_target_00459279();
#define VA_asm_target_00459279 0x00459279
extern "C" void __cdecl asm_target_004592ae();
#define VA_asm_target_004592ae 0x004592ae
extern "C" void __cdecl asm_target_00459358();
#define VA_asm_target_00459358 0x00459358
extern "C" void __cdecl asm_target_00459684();
#define VA_asm_target_00459684 0x00459684
extern "C" void __cdecl asm_target_00459686();
#define VA_asm_target_00459686 0x00459686
extern "C" void __cdecl asm_target_00459725();
#define VA_asm_target_00459725 0x00459725
extern "C" void __cdecl asm_target_00459789();
#define VA_asm_target_00459789 0x00459789
extern "C" void __cdecl asm_target_004597b4();
#define VA_asm_target_004597b4 0x004597b4
extern "C" void __cdecl asm_target_004597cd();
#define VA_asm_target_004597cd 0x004597cd
extern "C" void __cdecl asm_target_004597f8();
#define VA_asm_target_004597f8 0x004597f8
extern "C" void __cdecl asm_target_0045997c();
#define VA_asm_target_0045997c 0x0045997c
extern "C" void __cdecl asm_target_004599c8();
#define VA_asm_target_004599c8 0x004599c8
extern "C" void __cdecl asm_target_00459b2b();
#define VA_asm_target_00459b2b 0x00459b2b
extern "C" void __cdecl asm_target_00459b2f();
#define VA_asm_target_00459b2f 0x00459b2f
extern "C" void __cdecl asm_target_00459bab();
#define VA_asm_target_00459bab 0x00459bab
extern "C" void __cdecl asm_target_00459bae();
#define VA_asm_target_00459bae 0x00459bae
extern "C" void __cdecl asm_target_00459baf();
#define VA_asm_target_00459baf 0x00459baf
extern "C" void __cdecl asm_target_00459ccc();
#define VA_asm_target_00459ccc 0x00459ccc
extern "C" void __cdecl asm_target_00459de6();
#define VA_asm_target_00459de6 0x00459de6
extern "C" void __cdecl asm_target_00459e49();
#define VA_asm_target_00459e49 0x00459e49
extern "C" void __cdecl asm_target_00459e78();
#define VA_asm_target_00459e78 0x00459e78
extern "C" void __cdecl asm_target_00459f33();
#define VA_asm_target_00459f33 0x00459f33
extern "C" void __cdecl asm_target_0045a06a();
#define VA_asm_target_0045a06a 0x0045a06a
extern "C" void __cdecl asm_target_0045a3a0();
#define VA_asm_target_0045a3a0 0x0045a3a0
extern "C" void __cdecl asm_target_0045a3c6();
#define VA_asm_target_0045a3c6 0x0045a3c6
extern "C" void __cdecl asm_target_0045a757();
#define VA_asm_target_0045a757 0x0045a757
extern "C" void __cdecl asm_target_0045a8f4();
#define VA_asm_target_0045a8f4 0x0045a8f4
extern "C" void __cdecl asm_target_0045a8f5();
#define VA_asm_target_0045a8f5 0x0045a8f5
extern "C" void __cdecl asm_target_0045a902();
#define VA_asm_target_0045a902 0x0045a902
extern "C" void __cdecl asm_target_0045a90a();
#define VA_asm_target_0045a90a 0x0045a90a
extern "C" void __cdecl asm_target_0045a91d();
#define VA_asm_target_0045a91d 0x0045a91d
extern "C" void __cdecl asm_target_0045a95a();
#define VA_asm_target_0045a95a 0x0045a95a
extern "C" void __cdecl asm_target_0045a963();
#define VA_asm_target_0045a963 0x0045a963
extern "C" void __cdecl asm_target_0045a9fd();
#define VA_asm_target_0045a9fd 0x0045a9fd
extern "C" void __cdecl asm_target_0045aa00();
#define VA_asm_target_0045aa00 0x0045aa00
extern "C" void __cdecl asm_target_0045aa01();
#define VA_asm_target_0045aa01 0x0045aa01
extern "C" void __cdecl asm_target_0045aa0b();
#define VA_asm_target_0045aa0b 0x0045aa0b
extern "C" void __cdecl asm_target_0045aa1e();
#define VA_asm_target_0045aa1e 0x0045aa1e
extern "C" void __cdecl asm_target_0045aa83();
#define VA_asm_target_0045aa83 0x0045aa83
extern "C" void __cdecl asm_target_0045aa8c();
#define VA_asm_target_0045aa8c 0x0045aa8c
extern "C" void __cdecl asm_target_0045aa8f();
#define VA_asm_target_0045aa8f 0x0045aa8f
extern "C" void __cdecl asm_target_0045abe4();
#define VA_asm_target_0045abe4 0x0045abe4
extern "C" void __cdecl asm_target_0045abe7();
#define VA_asm_target_0045abe7 0x0045abe7
extern "C" void __cdecl asm_target_0045abf0();
#define VA_asm_target_0045abf0 0x0045abf0
extern "C" void __cdecl asm_target_0045abf3();
#define VA_asm_target_0045abf3 0x0045abf3
extern "C" void __cdecl asm_target_0045ac04();
#define VA_asm_target_0045ac04 0x0045ac04
extern "C" void __cdecl asm_target_0045acde();
#define VA_asm_target_0045acde 0x0045acde
extern "C" void __cdecl asm_target_0045ad4f();
#define VA_asm_target_0045ad4f 0x0045ad4f
extern "C" void __cdecl asm_target_0045ad83();
#define VA_asm_target_0045ad83 0x0045ad83
extern "C" void __cdecl asm_target_0045ae68();
#define VA_asm_target_0045ae68 0x0045ae68
extern "C" void __cdecl asm_target_0045ae7f();
#define VA_asm_target_0045ae7f 0x0045ae7f
extern "C" void __cdecl asm_target_0045ae96();
#define VA_asm_target_0045ae96 0x0045ae96
extern "C" void __cdecl asm_target_0045aeab();
#define VA_asm_target_0045aeab 0x0045aeab
extern "C" void __cdecl asm_target_0045aece();
#define VA_asm_target_0045aece 0x0045aece
extern "C" void __cdecl asm_target_0045af0b();
#define VA_asm_target_0045af0b 0x0045af0b
extern "C" void __cdecl asm_target_0045afd3();
#define VA_asm_target_0045afd3 0x0045afd3
extern "C" void __cdecl asm_target_0045afdd();
#define VA_asm_target_0045afdd 0x0045afdd
extern "C" void __cdecl asm_target_0045b528();
#define VA_asm_target_0045b528 0x0045b528
extern "C" void __cdecl asm_target_0045b771();
#define VA_asm_target_0045b771 0x0045b771
extern "C" void __cdecl asm_target_0045b7c8();
#define VA_asm_target_0045b7c8 0x0045b7c8
extern "C" void __cdecl asm_target_0045b7e3();
#define VA_asm_target_0045b7e3 0x0045b7e3
extern "C" void __cdecl asm_target_0045b8f2();
#define VA_asm_target_0045b8f2 0x0045b8f2
extern "C" void __cdecl asm_target_0045baac();
#define VA_asm_target_0045baac 0x0045baac
extern "C" void __cdecl asm_target_0045bae6();
#define VA_asm_target_0045bae6 0x0045bae6
extern "C" void __cdecl asm_target_0045bb2c();
#define VA_asm_target_0045bb2c 0x0045bb2c
extern "C" void __cdecl asm_target_0045bce4();
#define VA_asm_target_0045bce4 0x0045bce4
extern "C" void __cdecl asm_target_0045bce7();
#define VA_asm_target_0045bce7 0x0045bce7
extern "C" void __cdecl asm_target_0045bcfc();
#define VA_asm_target_0045bcfc 0x0045bcfc
extern "C" void __cdecl asm_target_0045bdf5();
#define VA_asm_target_0045bdf5 0x0045bdf5
extern "C" void __cdecl asm_target_0045bf40();
#define VA_asm_target_0045bf40 0x0045bf40
extern "C" void __cdecl asm_target_0045bf70();
#define VA_asm_target_0045bf70 0x0045bf70
extern "C" void __cdecl asm_target_0045bf7c();
#define VA_asm_target_0045bf7c 0x0045bf7c
extern "C" void __cdecl asm_target_0045c443();
#define VA_asm_target_0045c443 0x0045c443
extern "C" void __cdecl asm_target_0045c453();
#define VA_asm_target_0045c453 0x0045c453
extern "C" void __cdecl asm_target_0045c77e();
#define VA_asm_target_0045c77e 0x0045c77e
extern "C" void __cdecl asm_target_0045c7b2();
#define VA_asm_target_0045c7b2 0x0045c7b2
extern "C" void __cdecl asm_target_0045c851();
#define VA_asm_target_0045c851 0x0045c851
extern "C" void __cdecl asm_target_0045c85e();
#define VA_asm_target_0045c85e 0x0045c85e
extern "C" void __cdecl asm_target_0045c860();
#define VA_asm_target_0045c860 0x0045c860
extern "C" void __cdecl asm_target_0045cb2a();
#define VA_asm_target_0045cb2a 0x0045cb2a
extern "C" void __cdecl asm_target_0045cbff();
#define VA_asm_target_0045cbff 0x0045cbff
extern "C" void __cdecl asm_target_0045cc02();
#define VA_asm_target_0045cc02 0x0045cc02
extern "C" void __cdecl asm_target_0045ceef();
#define VA_asm_target_0045ceef 0x0045ceef
extern "C" void __cdecl asm_target_0045d033();
#define VA_asm_target_0045d033 0x0045d033
extern "C" void __cdecl asm_target_0045d0da();
#define VA_asm_target_0045d0da 0x0045d0da
extern "C" void __cdecl asm_target_0045d0ea();
#define VA_asm_target_0045d0ea 0x0045d0ea
extern "C" void __cdecl asm_target_0045d112();
#define VA_asm_target_0045d112 0x0045d112
extern "C" void __cdecl asm_target_0045d124();
#define VA_asm_target_0045d124 0x0045d124
extern "C" void __cdecl asm_target_0045d12c();
#define VA_asm_target_0045d12c 0x0045d12c
extern "C" void __cdecl asm_target_0045d28e();
#define VA_asm_target_0045d28e 0x0045d28e
extern "C" void __cdecl asm_target_0045d58e();
#define VA_asm_target_0045d58e 0x0045d58e
extern "C" void __cdecl asm_target_0045d590();
#define VA_asm_target_0045d590 0x0045d590
extern "C" void __cdecl asm_target_0045d7a9();
#define VA_asm_target_0045d7a9 0x0045d7a9
extern "C" void __cdecl asm_target_0045d7c6();
#define VA_asm_target_0045d7c6 0x0045d7c6
extern "C" void __cdecl asm_target_0045d7d5();
#define VA_asm_target_0045d7d5 0x0045d7d5
extern "C" void __cdecl asm_target_0045d824();
#define VA_asm_target_0045d824 0x0045d824
extern "C" void __cdecl asm_target_0045d83e();
#define VA_asm_target_0045d83e 0x0045d83e
extern "C" void __cdecl asm_target_0045d865();
#define VA_asm_target_0045d865 0x0045d865
extern "C" void __cdecl asm_target_0045d890();
#define VA_asm_target_0045d890 0x0045d890
extern "C" void __cdecl asm_target_0045d99e();
#define VA_asm_target_0045d99e 0x0045d99e
extern "C" void __cdecl asm_target_0045d99f();
#define VA_asm_target_0045d99f 0x0045d99f
extern "C" void __cdecl asm_target_0045d9a2();
#define VA_asm_target_0045d9a2 0x0045d9a2
extern "C" void __cdecl asm_target_0045d9e3();
#define VA_asm_target_0045d9e3 0x0045d9e3
extern "C" void __cdecl asm_target_0045d9e5();
#define VA_asm_target_0045d9e5 0x0045d9e5
extern "C" void __cdecl asm_target_0045d9f1();
#define VA_asm_target_0045d9f1 0x0045d9f1
extern "C" void __cdecl asm_target_0045da0e();
#define VA_asm_target_0045da0e 0x0045da0e
extern "C" void __cdecl asm_target_0045da1a();
#define VA_asm_target_0045da1a 0x0045da1a
extern "C" void __cdecl asm_target_0045da1c();
#define VA_asm_target_0045da1c 0x0045da1c
extern "C" void __cdecl asm_target_0045da26();
#define VA_asm_target_0045da26 0x0045da26
extern "C" void __cdecl asm_target_0045da34();
#define VA_asm_target_0045da34 0x0045da34
extern "C" void __cdecl asm_target_0045da9e();
#define VA_asm_target_0045da9e 0x0045da9e
extern "C" void __cdecl asm_target_0045db02();
#define VA_asm_target_0045db02 0x0045db02
extern "C" void __cdecl asm_target_0045db29();
#define VA_asm_target_0045db29 0x0045db29
extern "C" void __cdecl asm_target_0045e1ff();
#define VA_asm_target_0045e1ff 0x0045e1ff
extern "C" void __cdecl asm_target_0045e2ab();
#define VA_asm_target_0045e2ab 0x0045e2ab
extern "C" void __cdecl asm_target_0045e2db();
#define VA_asm_target_0045e2db 0x0045e2db
extern "C" void __cdecl asm_target_0045e746();
#define VA_asm_target_0045e746 0x0045e746
extern "C" void __cdecl asm_target_0045e768();
#define VA_asm_target_0045e768 0x0045e768
extern "C" void __cdecl asm_target_0045e770();
#define VA_asm_target_0045e770 0x0045e770
extern "C" void __cdecl asm_target_0045e834();
#define VA_asm_target_0045e834 0x0045e834
extern "C" void __cdecl asm_target_0045e84a();
#define VA_asm_target_0045e84a 0x0045e84a
extern "C" void __cdecl asm_target_0045ed63();
#define VA_asm_target_0045ed63 0x0045ed63
extern "C" void __cdecl asm_target_0045f052();
#define VA_asm_target_0045f052 0x0045f052
extern "C" void __cdecl asm_target_0045f075();
#define VA_asm_target_0045f075 0x0045f075
extern "C" void __cdecl asm_target_0045f0ab();
#define VA_asm_target_0045f0ab 0x0045f0ab
extern "C" void __cdecl asm_target_0045f19c();
#define VA_asm_target_0045f19c 0x0045f19c
extern "C" void __cdecl asm_target_0045f1ad();
#define VA_asm_target_0045f1ad 0x0045f1ad
extern "C" void __cdecl asm_target_0045f1ea();
#define VA_asm_target_0045f1ea 0x0045f1ea
extern "C" void __cdecl asm_target_0045f28b();
#define VA_asm_target_0045f28b 0x0045f28b
extern "C" void __cdecl asm_target_0045f39c();
#define VA_asm_target_0045f39c 0x0045f39c
extern "C" void __cdecl asm_target_0045f48b();
#define VA_asm_target_0045f48b 0x0045f48b
extern "C" void __cdecl asm_target_0045f5d9();
#define VA_asm_target_0045f5d9 0x0045f5d9
extern "C" void __cdecl asm_target_0045f804();
#define VA_asm_target_0045f804 0x0045f804
extern "C" void __cdecl asm_target_0045f81f();
#define VA_asm_target_0045f81f 0x0045f81f
extern "C" void __cdecl asm_target_0045f878();
#define VA_asm_target_0045f878 0x0045f878
extern "C" void __cdecl asm_target_0045f8b0();
#define VA_asm_target_0045f8b0 0x0045f8b0
extern "C" void __cdecl asm_target_0045f8d5();
#define VA_asm_target_0045f8d5 0x0045f8d5
extern "C" void __cdecl asm_target_0045f8e1();
#define VA_asm_target_0045f8e1 0x0045f8e1
extern "C" void __cdecl asm_target_0045f938();
#define VA_asm_target_0045f938 0x0045f938
extern "C" void __cdecl asm_target_0045f944();
#define VA_asm_target_0045f944 0x0045f944
extern "C" void __cdecl asm_target_0045f94a();
#define VA_asm_target_0045f94a 0x0045f94a
extern "C" void __cdecl asm_target_0045fa12();
#define VA_asm_target_0045fa12 0x0045fa12
extern "C" void __cdecl asm_target_0045fb35();
#define VA_asm_target_0045fb35 0x0045fb35
extern "C" void __cdecl asm_target_0045fb3d();
#define VA_asm_target_0045fb3d 0x0045fb3d
extern "C" void __cdecl asm_target_0045fb5b();
#define VA_asm_target_0045fb5b 0x0045fb5b
extern "C" void __cdecl asm_target_0045fbed();
#define VA_asm_target_0045fbed 0x0045fbed
extern "C" void __cdecl asm_target_0045fd9c();
#define VA_asm_target_0045fd9c 0x0045fd9c
extern "C" void __cdecl asm_target_0045fe29();
#define VA_asm_target_0045fe29 0x0045fe29
extern "C" void __cdecl asm_target_0045ff59();
#define VA_asm_target_0045ff59 0x0045ff59
extern "C" void __cdecl asm_target_0045ffcd();
#define VA_asm_target_0045ffcd 0x0045ffcd
extern "C" void __cdecl asm_target_0046001b();
#define VA_asm_target_0046001b 0x0046001b
extern "C" void __cdecl asm_target_0046001f();
#define VA_asm_target_0046001f 0x0046001f
extern "C" void __cdecl asm_target_00460175();
#define VA_asm_target_00460175 0x00460175
extern "C" void __cdecl asm_target_00460199();
#define VA_asm_target_00460199 0x00460199
extern "C" void __cdecl asm_target_0046019b();
#define VA_asm_target_0046019b 0x0046019b
extern "C" void __cdecl asm_target_004602f4();
#define VA_asm_target_004602f4 0x004602f4
extern "C" void __cdecl asm_target_0046039d();
#define VA_asm_target_0046039d 0x0046039d
extern "C" void __cdecl asm_target_004603a0();
#define VA_asm_target_004603a0 0x004603a0
extern "C" void __cdecl asm_target_004603af();
#define VA_asm_target_004603af 0x004603af
extern "C" void __cdecl asm_target_00460502();
#define VA_asm_target_00460502 0x00460502
extern "C" void __cdecl asm_target_00460b60();
#define VA_asm_target_00460b60 0x00460b60
extern "C" void __cdecl asm_target_00460b66();
#define VA_asm_target_00460b66 0x00460b66
extern "C" void __cdecl asm_target_00460b81();
#define VA_asm_target_00460b81 0x00460b81
extern "C" void __cdecl asm_target_00460cda();
#define VA_asm_target_00460cda 0x00460cda
extern "C" void __cdecl asm_target_00461287();
#define VA_asm_target_00461287 0x00461287
extern "C" void __cdecl asm_target_00461331();
#define VA_asm_target_00461331 0x00461331
extern "C" void __cdecl asm_target_0046133f();
#define VA_asm_target_0046133f 0x0046133f
extern "C" void __cdecl asm_target_0046134f();
#define VA_asm_target_0046134f 0x0046134f
extern "C" void __cdecl asm_target_00461355();
#define VA_asm_target_00461355 0x00461355
extern "C" void __cdecl asm_target_0046135a();
#define VA_asm_target_0046135a 0x0046135a
extern "C" void __cdecl asm_target_0046135c();
#define VA_asm_target_0046135c 0x0046135c
extern "C" void __cdecl asm_target_00461406();
#define VA_asm_target_00461406 0x00461406
extern "C" void __cdecl asm_target_004614a1();
#define VA_asm_target_004614a1 0x004614a1
extern "C" void __cdecl asm_target_0046155f();
#define VA_asm_target_0046155f 0x0046155f
extern "C" void __cdecl asm_target_004615fa();
#define VA_asm_target_004615fa 0x004615fa
extern "C" void __cdecl asm_target_0046168c();
#define VA_asm_target_0046168c 0x0046168c
extern "C" void __cdecl asm_target_0046171e();
#define VA_asm_target_0046171e 0x0046171e
extern "C" void __cdecl asm_target_004617ba();
#define VA_asm_target_004617ba 0x004617ba
extern "C" void __cdecl asm_target_004617cc();
#define VA_asm_target_004617cc 0x004617cc
extern "C" void __cdecl asm_target_004619c3();
#define VA_asm_target_004619c3 0x004619c3
extern "C" void __cdecl asm_target_00461aa5();
#define VA_asm_target_00461aa5 0x00461aa5
extern "C" void __cdecl asm_target_00461ac8();
#define VA_asm_target_00461ac8 0x00461ac8
extern "C" void __cdecl asm_target_00461bce();
#define VA_asm_target_00461bce 0x00461bce
extern "C" void __cdecl asm_target_00461c65();
#define VA_asm_target_00461c65 0x00461c65
extern "C" void __cdecl asm_target_00461dab();
#define VA_asm_target_00461dab 0x00461dab
extern "C" void __cdecl asm_target_00461dc2();
#define VA_asm_target_00461dc2 0x00461dc2
extern "C" void __cdecl asm_target_00461def();
#define VA_asm_target_00461def 0x00461def
extern "C" void __cdecl asm_target_00461e70();
#define VA_asm_target_00461e70 0x00461e70
extern "C" void __cdecl asm_target_00461fa7();
#define VA_asm_target_00461fa7 0x00461fa7
extern "C" void __cdecl asm_target_00461faa();
#define VA_asm_target_00461faa 0x00461faa
extern "C" void __cdecl asm_target_00461fb4();
#define VA_asm_target_00461fb4 0x00461fb4
extern "C" void __cdecl asm_target_004620f5();
#define VA_asm_target_004620f5 0x004620f5
extern "C" void __cdecl asm_target_0046221f();
#define VA_asm_target_0046221f 0x0046221f
extern "C" void __cdecl asm_target_004628bc();
#define VA_asm_target_004628bc 0x004628bc
extern "C" void __cdecl asm_target_00462ea6();
#define VA_asm_target_00462ea6 0x00462ea6
extern "C" void __cdecl asm_target_00462f0f();
#define VA_asm_target_00462f0f 0x00462f0f
extern "C" void __cdecl asm_target_0046316a();
#define VA_asm_target_0046316a 0x0046316a
extern "C" void __cdecl asm_target_004632cc();
#define VA_asm_target_004632cc 0x004632cc
extern "C" void __cdecl asm_target_004634fa();
#define VA_asm_target_004634fa 0x004634fa
extern "C" void __cdecl asm_target_004634ff();
#define VA_asm_target_004634ff 0x004634ff
extern "C" void __cdecl asm_target_00463503();
#define VA_asm_target_00463503 0x00463503
extern "C" void __cdecl asm_target_004635f4();
#define VA_asm_target_004635f4 0x004635f4
extern "C" void __cdecl asm_target_00463622();
#define VA_asm_target_00463622 0x00463622
extern "C" void __cdecl asm_target_00463637();
#define VA_asm_target_00463637 0x00463637
extern "C" void __cdecl asm_target_0046375c();
#define VA_asm_target_0046375c 0x0046375c
extern "C" void __cdecl asm_target_0046382c();
#define VA_asm_target_0046382c 0x0046382c
extern "C" void __cdecl asm_target_0046387f();
#define VA_asm_target_0046387f 0x0046387f
extern "C" void __cdecl asm_target_0046390b();
#define VA_asm_target_0046390b 0x0046390b
extern "C" void __cdecl asm_target_00463920();
#define VA_asm_target_00463920 0x00463920
extern "C" void __cdecl asm_target_00463930();
#define VA_asm_target_00463930 0x00463930
extern "C" void __cdecl asm_target_00463935();
#define VA_asm_target_00463935 0x00463935
extern "C" void __cdecl asm_target_00463938();
#define VA_asm_target_00463938 0x00463938
extern "C" void __cdecl asm_target_00463de2();
#define VA_asm_target_00463de2 0x00463de2
extern "C" void __cdecl asm_target_00463e6f();
#define VA_asm_target_00463e6f 0x00463e6f
extern "C" void __cdecl asm_target_004640f9();
#define VA_asm_target_004640f9 0x004640f9
extern "C" void __cdecl asm_target_00464118();
#define VA_asm_target_00464118 0x00464118
extern "C" void __cdecl asm_target_004641aa();
#define VA_asm_target_004641aa 0x004641aa
extern "C" void __cdecl asm_target_004646c6();
#define VA_asm_target_004646c6 0x004646c6
extern "C" void __cdecl asm_target_004646d9();
#define VA_asm_target_004646d9 0x004646d9
extern "C" void __cdecl asm_target_00464ab0();
#define VA_asm_target_00464ab0 0x00464ab0
extern "C" void __cdecl asm_target_00464d68();
#define VA_asm_target_00464d68 0x00464d68
extern "C" void __cdecl asm_target_00464dd4();
#define VA_asm_target_00464dd4 0x00464dd4
extern "C" void __cdecl asm_target_00464ec0();
#define VA_asm_target_00464ec0 0x00464ec0
extern "C" void __cdecl asm_terminate_00455693();
#define VA_asm_terminate_00455693 0x00455693
extern "C" void __cdecl asm_terminate_part_004556bf();
#define VA_asm_terminate_part_004556bf 0x004556bf
extern "C" int __cdecl asm_tolower_00460cee(int character);
#define VA_asm_tolower_00460cee 0x00460cee
extern "C" void __cdecl asm_tolower_mt_00460c26();
#define VA_asm_tolower_mt_00460c26 0x00460c26
extern "C" void __cdecl asm_trandisp1_00463f40();
#define VA_asm_trandisp1_00463f40 0x00463f40
extern "C" void __cdecl asm_trandisp2_00463fa7();
#define VA_asm_trandisp2_00463fa7 0x00463fa7
extern "C" void __cdecl asm_type_info_00462b35();
#define VA_asm_type_info_00462b35 0x00462b35
extern "C" void __cdecl asm_tzset_004571cf();
#define VA_asm_tzset_004571cf 0x004571cf
extern "C" void __cdecl asm_tzset_lk_00456be8();
#define VA_asm_tzset_lk_00456be8 0x00456be8
extern "C" void __cdecl asm_tzset_lk_part_00456e0c();
#define VA_asm_tzset_lk_part_00456e0c 0x00456e0c
extern "C" char* __cdecl asm_ui64toa_0046077d(unsigned long long value, char* buffer, int radix);
#define VA_asm_ui64toa_0046077d 0x0046077d
extern "C" char* __cdecl asm_ultoa_004606c5(unsigned long value, char* destination, int radix);
#define VA_asm_ultoa_004606c5 0x004606c5
extern "C" void __cdecl asm_umatherr_0045e8e1();
#define VA_asm_umatherr_0045e8e1 0x0045e8e1
extern "C" void __cdecl asm_unassigned_00421c0b();
#define VA_asm_unassigned_00421c0b 0x00421c0b
extern "C" void __cdecl asm_unassigned_00449510();
#define VA_asm_unassigned_00449510 0x00449510
extern "C" void __cdecl asm_unassigned_00449780();
#define VA_asm_unassigned_00449780 0x00449780
extern "C" __int64 __cdecl asm_unassigned_0045287b(const char* text);
#define VA_asm_unassigned_0045287b 0x0045287b
extern "C" void __cdecl asm_unassigned_00454479(void);
#define VA_asm_unassigned_00454479 0x00454479
extern "C" void __cdecl asm_unassigned_004567ab();
#define VA_asm_unassigned_004567ab 0x004567ab
extern "C" void __cdecl asm_unassigned_0045771d();
#define VA_asm_unassigned_0045771d 0x0045771d
extern "C" void __cdecl asm_unassigned_0045a0bc(void* lock);
#define VA_asm_unassigned_0045a0bc 0x0045a0bc
extern "C" void __cdecl asm_unassigned_0045f7d7();
#define VA_asm_unassigned_0045f7d7 0x0045f7d7
extern "C" unsigned int __cdecl asm_unassigned_00461004(unsigned int status);
#define VA_asm_unassigned_00461004 0x00461004
extern "C" void __cdecl asm_unassigned_00461458();
#define VA_asm_unassigned_00461458 0x00461458
extern "C" void __cdecl asm_unassigned_00462e60();
#define VA_asm_unassigned_00462e60 0x00462e60
extern "C" void __cdecl asm_unassigned_00463321();
#define VA_asm_unassigned_00463321 0x00463321
extern "C" void __cdecl asm_unassigned_00464110();
#define VA_asm_unassigned_00464110 0x00464110
extern "C" void __cdecl asm_unassigned_00464bce();
#define VA_asm_unassigned_00464bce 0x00464bce
extern "C" void __cdecl asm_unassigned_00464f45();
#define VA_asm_unassigned_00464f45 0x00464f45
extern "C" void __cdecl asm_unlock_file2_0045a0eb(int number, void* file);
#define VA_asm_unlock_file2_0045a0eb 0x0045a0eb
extern "C" void __cdecl asm_updatetlocinfo_00455ade();
#define VA_asm_updatetlocinfo_00455ade 0x00455ade
extern "C" void __cdecl asm_updatetlocinfo_lk_004558cc();
#define VA_asm_updatetlocinfo_lk_004558cc 0x004558cc
extern "C" void __cdecl asm_updatetmbcinfo_0045cf49();
#define VA_asm_updatetmbcinfo_0045cf49 0x0045cf49
extern "C" int __cdecl asm_vsprintf_004524a6(char* destination, const char* format, void* arguments);
#define VA_asm_vsprintf_004524a6 0x004524a6
extern "C" int __cdecl asm_wctomb_0045a16e(char* destination, unsigned short wide);
#define VA_asm_wctomb_0045a16e 0x0045a16e
extern "C" int __cdecl asm_wctomb_mt_0045a10e(LocaleInfo* locale, char* destination, unsigned short wide);
#define VA_asm_wctomb_mt_0045a10e 0x0045a10e
extern "C" unsigned char* __cdecl asm_wincmdln_004590d8();
#define VA_asm_wincmdln_004590d8 0x004590d8
extern "C" void __cdecl asm_write_00459e8e();
#define VA_asm_write_00459e8e 0x00459e8e
extern "C" void __cdecl asm_write_char_00454e2a();
#define VA_asm_write_char_00454e2a 0x00454e2a
extern "C" void __cdecl asm_write_multi_char_00454e5d();
#define VA_asm_write_multi_char_00454e5d 0x00454e5d
extern "C" void __cdecl asm_write_part_00459f1d();
#define VA_asm_write_part_00459f1d 0x00459f1d
extern "C" void __cdecl asm_write_string_00454e81();
#define VA_asm_write_string_00454e81 0x00454e81
extern "C" void __cdecl asm_wtomb_environ_004610f4();
#define VA_asm_wtomb_environ_004610f4 0x004610f4
extern "C" int __cdecl asm_x_ismbbtype_0045f4c9(unsigned char character, unsigned int wide_mask, unsigned char byte_mask);
#define VA_asm_x_ismbbtype_0045f4c9 0x0045f4c9
extern "C" void __cdecl asm_xtoa_00460636();
#define VA_asm_xtoa_00460636 0x00460636
extern "C" unsigned char data_00466000;
extern "C" unsigned char data_00466008;
extern "C" unsigned char data_00466010;
extern "C" unsigned char data_00466014;
extern "C" unsigned char data_00466018;
extern "C" unsigned char data_0046601c;
extern "C" unsigned char data_00466020;
extern "C" unsigned char data_00466024;
extern "C" unsigned char data_00466028;
extern "C" unsigned char data_0046602c;
extern "C" unsigned char data_00466030;
extern "C" unsigned char data_00466034;
extern "C" unsigned char data_0046603c;
extern "C" unsigned char data_00466040;
extern "C" unsigned char data_00466044;
extern "C" unsigned char data_00466048;
extern "C" unsigned char data_0046604c;
extern "C" unsigned char data_00466050;
extern "C" unsigned char data_00466054;
extern "C" unsigned char data_00466058;
extern "C" unsigned char data_0046605c;
extern "C" unsigned char data_00466060;
extern "C" unsigned char data_00466064;
extern "C" unsigned char data_00466068;
extern "C" unsigned char data_0046606c;
extern "C" unsigned char data_00466070;
extern "C" unsigned char data_00466074;
extern "C" unsigned char data_00466078;
extern "C" unsigned char data_0046607c;
extern "C" unsigned char data_00466080;
extern "C" unsigned char data_00466084;
extern "C" unsigned char data_00466088;
extern "C" unsigned char data_0046608c;
extern "C" unsigned char data_00466090;
extern "C" unsigned char data_00466094;
extern "C" unsigned char data_00466098;
extern "C" unsigned char data_0046609c;
extern "C" unsigned char data_004660a0;
extern "C" unsigned char data_004660a4;
extern "C" unsigned char data_004660a8;
extern "C" unsigned char data_004660ac;
extern "C" unsigned char data_004660b0;
extern "C" unsigned char data_004660b4;
extern "C" unsigned char data_004660b8;
extern "C" unsigned char data_004660bc;
extern "C" unsigned char data_004660c0;
extern "C" unsigned char data_004660c4;
extern "C" unsigned char data_004660c8;
extern "C" unsigned char data_004660cc;
extern "C" unsigned char data_004660d0;
extern "C" unsigned char data_004660d4;
extern "C" unsigned char data_004660d8;
extern "C" unsigned char data_004660dc;
extern "C" unsigned char data_004660e0;
extern "C" unsigned char data_004660e4;
extern "C" unsigned char data_004660e8;
extern "C" unsigned char data_004660ec;
extern "C" unsigned char data_004660f0;
extern "C" unsigned char data_004660f4;
extern "C" unsigned char data_004660f8;
extern "C" unsigned char data_004660fc;
extern "C" unsigned char data_00466100;
extern "C" unsigned char data_00466104;
extern "C" unsigned char data_00466108;
extern "C" unsigned char data_0046610c;
extern "C" unsigned char data_00466110;
extern "C" unsigned char data_00466114;
extern "C" unsigned char data_00466118;
extern "C" unsigned char data_0046611c;
extern "C" unsigned char data_00466120;
extern "C" unsigned char data_00466124;
extern "C" unsigned char data_00466128;
extern "C" unsigned char data_0046612c;
extern "C" unsigned char data_00466130;
extern "C" unsigned char data_00466134;
extern "C" unsigned char data_00466138;
extern "C" unsigned char data_0046613c;
extern "C" unsigned char data_00466140;
extern "C" unsigned char data_00466144;
extern "C" unsigned char data_00466148;
extern "C" unsigned char data_0046614c;
extern "C" unsigned char data_00466150;
extern "C" unsigned char data_00466154;
extern "C" unsigned char data_00466158;
extern "C" unsigned char data_0046615c;
extern "C" unsigned char data_00466160;
extern "C" unsigned char data_00466164;
extern "C" unsigned char data_00466168;
extern "C" unsigned char data_0046616c;
extern "C" unsigned char data_00466170;
extern "C" unsigned char data_00466174;
extern "C" unsigned char data_00466178;
extern "C" unsigned char data_0046617c;
extern "C" unsigned char data_00466180;
extern "C" unsigned char data_00466184;
extern "C" unsigned char data_00466188;
extern "C" unsigned char data_0046618c;
extern "C" unsigned char data_00466190;
extern "C" unsigned char data_00466194;
extern "C" unsigned char data_00466198;
extern "C" unsigned char data_0046619c;
extern "C" unsigned char data_004661a0;
extern "C" unsigned char data_004661a4;
extern "C" unsigned char data_004661a8;
extern "C" unsigned char data_004661ac;
extern "C" unsigned char data_004661b0;
extern "C" unsigned char data_004661b4;
extern "C" unsigned char data_004661b8;
extern "C" unsigned char data_004661bc;
extern "C" unsigned char data_004661c0;
extern "C" unsigned char data_004661c4;
extern "C" unsigned char data_004661c8;
extern "C" unsigned char data_004661cc;
extern "C" unsigned char data_004661d0;
extern "C" unsigned char data_004661d4;
extern "C" unsigned char data_004661d8;
extern "C" unsigned char data_004661dc;
extern "C" unsigned char data_004661e0;
extern "C" unsigned char data_004661e4;
extern "C" unsigned char data_004661e8;
extern "C" unsigned char data_004661f0;
extern "C" unsigned char data_004661f4;
extern "C" unsigned char data_004661f8;
extern "C" unsigned char data_004661fc;
extern "C" unsigned char data_00466200;
extern "C" unsigned char data_00466204;
extern "C" unsigned char data_00466208;
extern "C" unsigned char data_0046620c;
extern "C" unsigned char data_00466210;
extern "C" unsigned char data_00466214;
extern "C" unsigned char data_00466218;
extern "C" unsigned char data_0046621c;
extern "C" unsigned char data_00466220;
extern "C" unsigned char data_00466224;
extern "C" unsigned char data_00466228;
extern "C" unsigned char data_0046622c;
extern "C" unsigned char data_00466230;
extern "C" unsigned char data_00466234;
extern "C" unsigned char data_00466238;
extern "C" unsigned char data_0046623c;
extern "C" unsigned char data_00466240;
extern "C" unsigned char data_00466244;
extern "C" unsigned char data_00466248;
extern "C" unsigned char data_0046624c;
extern "C" unsigned char data_00466250;
extern "C" unsigned char data_00466254;
extern "C" unsigned char data_00466258;
extern "C" unsigned char data_0046625c;
extern "C" unsigned char data_00466260;
extern "C" unsigned char data_00466264;
extern "C" unsigned char data_00466268;
extern "C" unsigned char data_00466270;
extern "C" unsigned char data_00466274;
extern "C" unsigned char data_00466278;
extern "C" unsigned char data_0046627c;
extern "C" unsigned char data_00466280;
extern "C" unsigned char data_00466284;
extern "C" unsigned char data_00466288;
extern "C" unsigned char data_0046628c;
extern "C" unsigned char data_00466290;
extern "C" unsigned char data_00466294;
extern "C" unsigned char data_00466298;
extern "C" unsigned char data_0046629c;
extern "C" unsigned char data_004662a0;
extern "C" unsigned char data_004662a4;
extern "C" unsigned char data_004662a8;
extern "C" unsigned char data_004662ac;
extern "C" unsigned char data_004662b4;
extern "C" unsigned char data_004662bc;
extern "C" unsigned char data_004662c0;
extern "C" unsigned char data_004662c4;
extern "C" unsigned char data_004662c8;
extern "C" unsigned char data_004662cc;
extern "C" unsigned char data_004662d0;
extern "C" unsigned char data_004662d4;
extern "C" unsigned char data_004662d8;
extern "C" unsigned char data_004662dc;
extern "C" unsigned char data_004662e0;
extern "C" unsigned char data_004662e4;
extern "C" unsigned char data_004662e8;
extern "C" unsigned char data_004662ec;
extern "C" unsigned char data_004662f0;
extern "C" unsigned char data_004662f4;
extern "C" unsigned char data_004662f8;
extern "C" unsigned char data_00466300;
extern "C" unsigned char data_00466304;
extern "C" unsigned char data_00466308;
extern "C" unsigned char data_0046a67c;
extern "C" unsigned char data_0046a680;
extern "C" unsigned char data_0046a684;
extern "C" unsigned char data_0046a688;
extern "C" unsigned char data_0046a700;
extern "C" unsigned char data_0046a710;
extern "C" unsigned char data_0046a720;
extern "C" unsigned char data_0046a730;
extern "C" unsigned char data_0046a740;
extern "C" unsigned char data_0046ac28;
extern "C" unsigned char data_0046c560;
extern "C" unsigned char data_0046c568;
extern "C" unsigned char data_0046dbe0;
extern "C" unsigned char data_0046dbe4;
extern "C" unsigned char data_0046dbe8;
extern "C" unsigned char data_0046e354;
extern "C" unsigned char data_0046e358;
extern "C" unsigned char data_0046e35c;
extern "C" unsigned char data_0046e858;
extern "C" unsigned char data_0046e85c;
extern "C" unsigned char data_0046e860;
extern "C" unsigned char data_0046f274;
extern "C" unsigned char data_0046f278;
extern "C" unsigned char data_004700e8;
extern "C" unsigned char data_004700ec;
extern "C" unsigned char data_00470afc;
extern "C" unsigned char data_00470b00;
extern "C" unsigned char data_00470b04;
extern "C" unsigned char data_00470b08;
extern "C" unsigned char data_00470b0c;
extern "C" unsigned char data_00470b10;
extern "C" unsigned char data_00470b14;
extern "C" unsigned char data_00470b18;
extern "C" unsigned char data_00470b1c;
extern "C" unsigned char data_00470b20;
extern "C" unsigned char data_00470b28;
extern "C" unsigned char data_00470b30;
extern "C" unsigned char data_00470b38;
extern "C" unsigned char data_00470b3c;
extern "C" unsigned char data_00470b40;
extern "C" unsigned char data_00470b44;
extern "C" unsigned char data_00470b48;
extern "C" unsigned char data_00470b4c;
extern "C" unsigned char data_00470b50;
extern "C" unsigned char data_00470b54;
extern "C" unsigned char data_00470b58;
extern "C" unsigned char data_00470b5c;
extern "C" unsigned char data_00470b60;
extern "C" unsigned char data_00470b64;
extern "C" unsigned char data_00470b68;
extern "C" unsigned char data_00470b6c;
extern "C" unsigned char data_00470b70;
extern "C" unsigned char data_00470b78;
extern "C" unsigned char data_00470b7c;
extern "C" unsigned char data_00470b80;
extern "C" unsigned char data_00470b88;
extern "C" unsigned char data_00470b90;
extern "C" unsigned char data_00470b94;
extern "C" unsigned char data_00470b98;
extern "C" unsigned char data_00470ba0;
extern "C" unsigned char data_00470ba8;
extern "C" unsigned char data_00470bb0;
extern "C" unsigned char data_00470bb8;
extern "C" unsigned char data_00470bc0;
extern "C" unsigned char data_00470bc8;
extern "C" unsigned char data_00470bcc;
extern "C" unsigned char data_00470bd0;
extern "C" unsigned char data_00470bd4;
extern "C" unsigned char data_00470bd8;
extern "C" unsigned char data_00470bdc;
extern "C" unsigned char data_00470be0;
extern "C" unsigned char data_00470be4;
extern "C" unsigned char data_00470be8;
extern "C" unsigned char data_00470bec;
extern "C" unsigned char data_00470bf0;
extern "C" unsigned char data_00470bf4;
extern "C" unsigned char data_00470bf8;
extern "C" unsigned char data_00470bfc;
extern "C" unsigned char data_00470c00;
extern "C" unsigned char data_00470c08;
extern "C" unsigned char data_00470c0c;
extern "C" unsigned char data_00470c10;
extern "C" unsigned char data_00470c14;
extern "C" unsigned char data_00470c18;
extern "C" unsigned char data_00470c1c;
extern "C" unsigned char data_00470c20;
extern "C" unsigned char data_00470c24;
extern "C" unsigned char data_00470c28;
extern "C" unsigned char data_00470c2c;
extern "C" unsigned char data_00470c30;
extern "C" unsigned char data_00470c34;
extern "C" unsigned char data_00470c38;
extern "C" unsigned char data_00470c3c;
extern "C" unsigned char data_00470c40;
extern "C" unsigned char data_00470c44;
extern "C" unsigned char data_00470c48;
extern "C" unsigned char data_00470c50;
extern "C" unsigned char data_00470c58;
extern "C" unsigned char data_00470c5c;
extern "C" unsigned char data_00470c60;
extern "C" unsigned char data_00470c64;
extern "C" unsigned char data_00470c68;
extern "C" unsigned char data_00470c6c;
extern "C" unsigned char data_00470c70;
extern "C" unsigned char data_00470c74;
extern "C" unsigned char data_00470c78;
extern "C" unsigned char data_00470c7c;
extern "C" unsigned char data_00470c80;
extern "C" unsigned char data_00470c84;
extern "C" unsigned char data_00470c88;
extern "C" unsigned char data_00470c90;
extern "C" unsigned char data_00470c98;
extern "C" unsigned char data_00470ca0;
extern "C" unsigned char data_00470ca4;
extern "C" unsigned char data_00470ca8;
extern "C" unsigned char data_00470cac;
extern "C" unsigned char data_00470cb0;
extern "C" unsigned char data_00470cb4;
extern "C" unsigned char data_00470cb8;
extern "C" unsigned char data_00470cbc;
extern "C" unsigned char data_00470cc0;
extern "C" unsigned char data_00470cc4;
extern "C" unsigned char data_00470cc8;
extern "C" unsigned char data_00470ccc;
extern "C" unsigned char data_00470cd0;
extern "C" unsigned char data_00470cd4;
extern "C" unsigned char data_00470cd8;
extern "C" unsigned char data_00470cdc;
extern "C" unsigned char data_00470ce0;
extern "C" unsigned char data_00470ce4;
extern "C" unsigned char data_00470ce8;
extern "C" unsigned char data_00470cf0;
extern "C" unsigned char data_00470cf8;
extern "C" unsigned char data_00470d00;
extern "C" unsigned char data_00470d08;
extern "C" unsigned char data_00470d10;
extern "C" unsigned char data_00470d18;
extern "C" unsigned char data_00470d1c;
extern "C" unsigned char data_00470d20;
extern "C" unsigned char data_00470d24;
extern "C" unsigned char data_00470d28;
extern "C" unsigned char data_00470d2c;
extern "C" unsigned char data_00470d30;
extern "C" unsigned char data_00470d34;
extern "C" unsigned char data_00470d38;
extern "C" unsigned char data_00470d3c;
extern "C" unsigned char data_00470d40;
extern "C" unsigned char data_00470d44;
extern "C" unsigned char data_00470d48;
extern "C" unsigned char data_00470d4c;
extern "C" unsigned char data_00470d50;
extern "C" unsigned char data_00470d58;
extern "C" unsigned char data_00470d60;
extern "C" unsigned char data_00470d68;
extern "C" unsigned char data_00470d70;
extern "C" unsigned char data_00470d78;
extern "C" unsigned char data_00470d80;
extern "C" unsigned char data_00470d88;
extern "C" unsigned char data_00470d90;
extern "C" unsigned char data_00470da4;
extern "C" unsigned char data_00470dac;
extern "C" unsigned char data_00470db4;
extern "C" unsigned char data_00470dbc;
extern "C" unsigned char data_00470dc4;
extern "C" unsigned char data_00470dcc;
extern "C" unsigned char data_00473070;
extern "C" unsigned char data_00473074;
extern "C" unsigned char data_004731a0;
extern "C" unsigned char data_004731a4;
extern "C" unsigned char data_004731a8;
extern "C" unsigned char data_0047320c;
extern "C" unsigned char data_00473210;
extern "C" unsigned char data_00473214;
extern "C" unsigned char data_00473230;
extern "C" unsigned char data_00473234;
extern "C" unsigned char data_004732ba;
extern "C" unsigned char data_0047334c;
extern "C" unsigned char data_00473354;
extern "C" unsigned char data_00473358;
extern "C" unsigned char data_00473364;
extern "C" unsigned char data_00473390;
extern "C" unsigned char data_004733a8;
extern "C" unsigned char data_004733ac;
extern "C" unsigned char data_004733b0;
extern "C" unsigned char data_00473520;
extern "C" unsigned char data_00473524;
extern "C" unsigned char data_00473528;
extern "C" unsigned char data_004735b0;
extern "C" unsigned char data_004735b4;
extern "C" unsigned char data_004735b8;
extern "C" unsigned char data_004735bc;
extern "C" unsigned char data_004735c0;
extern "C" unsigned char data_004735c4;
extern "C" unsigned char data_004735c8;
extern "C" unsigned char data_004735cc;
extern "C" unsigned char data_00473648;
extern "C" unsigned char data_0047364c;
extern "C" unsigned char data_00473650;
extern "C" unsigned char data_00473654;
extern "C" unsigned char data_00473658;
extern "C" unsigned char data_0047365c;
extern "C" unsigned int data_00473660;
extern "C" unsigned char data_004739c0;
extern "C" unsigned char data_004739c4;
extern "C" unsigned char data_004739c8;
extern "C" unsigned char data_004739cc;
extern "C" unsigned char data_004739d0;
extern "C" unsigned char data_004739d4;
extern "C" unsigned char data_004739d8;
extern "C" unsigned char data_004739dc;
extern "C" unsigned char data_004739e0;
extern "C" unsigned char data_00473aa4;
extern "C" unsigned char data_00473aa8;
extern "C" unsigned char data_00473aac;
extern "C" unsigned char data_00473ab0;
extern "C" unsigned char data_00473ab4;
extern "C" unsigned char data_00473ab8;
extern "C" unsigned char data_00473abc;
extern "C" unsigned char data_00473ac0;
extern "C" unsigned char data_00473ac4;
extern "C" unsigned char data_00473ac8;
extern "C" unsigned char data_00473ad4;
extern "C" unsigned char data_00473ae0;
extern "C" unsigned char data_00473af0;
extern "C" unsigned char data_00473af4;
extern "C" unsigned char data_00473af8;
extern "C" unsigned char data_00473c90;
extern "C" unsigned char data_00473d80;
extern "C" unsigned char data_00473d90;
extern "C" unsigned char data_00473da8;
extern "C" unsigned char data_00473db4;
extern "C" unsigned char data_004746d8;
extern "C" unsigned char data_00474764;
extern "C" unsigned char data_00474908;
extern "C" unsigned char data_00474918;
extern "C" unsigned char data_00474c38;
extern "C" unsigned char data_00474c40;
extern "C" unsigned char data_00474c44;
extern "C" unsigned char data_00474c48;
extern "C" unsigned char data_00474c4c;
extern "C" unsigned char data_00474c50;
extern "C" unsigned char data_00474c54;
extern "C" unsigned char data_00474c58;
extern "C" unsigned char data_00474c5c;
extern "C" unsigned char data_00474c60;
extern "C" unsigned char data_00474c64;
extern "C" unsigned char data_00474c68;
extern "C" unsigned char data_00474c6c;
extern "C" unsigned char data_00474c70;
extern "C" unsigned char data_00474c74;
extern "C" unsigned char data_00474c78;
extern "C" unsigned char data_00474c7c;
extern "C" unsigned char data_00474c80;
extern "C" unsigned char data_00474c84;
extern "C" unsigned char data_00474c88;
extern "C" unsigned char data_00474c8c;
extern "C" unsigned char data_00474c90;
extern "C" unsigned char data_00474c94;
extern "C" unsigned char data_00474c98;
extern "C" unsigned char data_00474c9c;
extern "C" unsigned char data_00474ca0;
extern "C" unsigned char data_00474ca4;
extern "C" unsigned char data_00474ca8;
extern "C" unsigned char data_00474cac;
extern "C" unsigned char data_00474db0;
extern "C" unsigned char data_00474dbc;
extern "C" unsigned char data_00474dc0;
extern "C" unsigned char data_00474dc4;
extern "C" unsigned char data_00474dd0;
extern "C" unsigned char data_00474dd4;
extern "C" unsigned char data_00474dd8;
extern "C" unsigned char data_00474de0;
extern "C" unsigned char data_00474de4;
extern "C" unsigned char data_00474dec;
extern "C" unsigned char data_00474e30;
extern "C" unsigned char data_00474e34;
extern "C" unsigned char data_00474e36;
extern "C" unsigned char data_00474e38;
extern "C" unsigned char data_00474e5a;
extern "C" unsigned char g_input;
extern "C" unsigned char data_00474e5e;
extern "C" unsigned char data_00474e62;
extern "C" unsigned char data_00474e64;
extern "C" unsigned char data_00474e88;
extern "C" unsigned char data_00474e8a;
extern "C" unsigned char data_00474e8c;
extern "C" unsigned char data_00474e8e;
extern "C" unsigned char data_00474e90;
extern "C" unsigned char data_00474e94;
extern "C" unsigned char data_00474e98;
extern "C" unsigned char data_00474f70;
extern "C" unsigned char data_00476f70;
extern "C" unsigned char data_00476f74;
extern "C" unsigned char data_00476f78;
extern "C" unsigned char data_00477060;
extern "C" unsigned char data_00477070;
extern "C" unsigned char data_00477084;
extern "C" unsigned char data_004770b0;
extern "C" unsigned char data_004770b4;
extern "C" unsigned char data_004770b8;
extern "C" unsigned char data_004770d4;
extern "C" unsigned char data_004770dc;
extern "C" unsigned char data_004770ec;
extern "C" unsigned char data_004770f4;
extern "C" unsigned char data_00477200;
extern "C" unsigned char data_00477204;
extern "C" unsigned char data_0047720c;
extern "C" unsigned char data_00477360;
extern "C" unsigned char data_00477364;
extern "C" unsigned char data_0047736c;
extern "C" unsigned char data_00477370;
extern "C" unsigned char data_00477374;
extern "C" unsigned char data_00477378;
extern "C" unsigned char data_0047737c;
extern "C" unsigned char data_00477380;
extern "C" unsigned char data_00477384;
extern "C" unsigned char data_00477388;
extern "C" unsigned char data_00477390;
extern "C" unsigned char data_004773d4;
extern "C" unsigned char data_004773d6;
extern "C" unsigned char data_004773d8;
extern "C" unsigned char data_004773da;
extern "C" unsigned char data_004773dc;
extern "C" unsigned char data_004773de;
extern "C" unsigned char data_004773e0;
extern "C" unsigned char data_004773e2;
extern "C" unsigned char data_004773e4;
extern "C" unsigned char data_00477428;
extern "C" unsigned char data_0047742a;
extern "C" unsigned char data_0047742c;
extern "C" unsigned char data_0047742e;
extern "C" unsigned char data_00477430;
extern "C" unsigned char data_00477432;
extern "C" unsigned char data_00477434;
extern "C" unsigned char data_00477436;
extern "C" unsigned char data_00477438;
extern "C" unsigned char data_0047743c;
extern "C" unsigned char data_00477440;
extern "C" unsigned char data_00477444;
extern "C" unsigned char data_00477470;
extern "C" unsigned char data_00477474;
extern "C" unsigned char data_00477478;
extern "C" unsigned char data_0047747c;
extern "C" unsigned char data_00477480;
extern "C" unsigned char data_00477484;
extern "C" unsigned char data_00477488;
extern "C" unsigned char data_00477490;
extern "C" unsigned char data_00477494;
extern "C" unsigned char data_00477498;
extern "C" unsigned char data_004774a0;
extern "C" unsigned char data_004774a8;
extern "C" unsigned char data_004774ac;
extern "C" unsigned char data_004774b0;
extern "C" unsigned char data_004774b4;
extern "C" unsigned char data_004775bc;
extern "C" unsigned char data_004775c0;
extern "C" unsigned char data_004775c4;
extern "C" unsigned char data_004775c8;
extern "C" unsigned char data_00477614;
extern "C" unsigned char data_00477618;
extern "C" unsigned char data_00477620;
extern "C" unsigned char data_00477624;
extern "C" unsigned char data_00477628;
extern "C" unsigned char data_00477629;
extern "C" unsigned char data_0047762c;
extern "C" unsigned char data_00477630;
extern "C" unsigned char data_00477634;
extern "C" unsigned char data_00477638;
extern "C" unsigned char data_0047763c;
extern "C" unsigned char data_00477640;
extern "C" unsigned char data_00477644;
extern "C" unsigned char data_00477648;
extern "C" unsigned char data_00477654;
extern "C" unsigned char data_00477658;
extern "C" unsigned char data_0047765c;
extern "C" unsigned char data_00477660;
extern "C" unsigned char data_00477664;
extern "C" unsigned char data_00477668;
extern "C" unsigned char data_00477678;
extern "C" unsigned char data_00477680;
extern "C" unsigned char data_00477686;
extern "C" unsigned char data_0047768a;
extern "C" unsigned char data_0047768c;
extern "C" unsigned char data_00477690;
extern "C" unsigned char data_00477694;
extern "C" unsigned char data_00477698;
extern "C" unsigned char data_0047769c;
extern "C" unsigned char data_004776a0;
extern "C" unsigned char data_004776a4;
extern "C" unsigned char data_004776a8;
extern "C" unsigned char data_004776ac;
extern "C" unsigned char data_004776b0;
extern "C" unsigned char data_004776b4;
extern "C" unsigned char data_004776b8;
extern "C" unsigned char data_004776bc;
extern "C" unsigned char data_004776c0;
extern "C" unsigned char data_004776cc;
extern "C" unsigned char data_004776d0;
extern "C" unsigned char data_004776d4;
extern "C" unsigned char data_004776d8;
extern "C" unsigned char g_ascii_manager;
extern "C" unsigned char data_004776e4;
extern "C" unsigned char data_004776e8;
extern "C" unsigned char g_bomb;
extern "C" unsigned char data_004776f0;
extern "C" unsigned char g_card;
extern "C" unsigned char g_ecl_view;
extern "C" unsigned char g_effect;
extern "C" unsigned char g_ending;
extern "C" unsigned char data_00477704;
extern "C" unsigned char data_00477708;
extern "C" unsigned char data_0047770c;
extern "C" unsigned char data_00477810;
extern "C" unsigned char g_hint;
extern "C" unsigned char data_00477818;
extern "C" unsigned char g_laser_manager;
extern "C" unsigned char g_loading;
extern "C" unsigned char data_00477824;
extern "C" unsigned char data_00477828;
extern "C" unsigned char data_0047782c;
extern "C" unsigned char g_pause;
extern "C" unsigned char g_player;
extern "C" unsigned char data_00477838;
extern "C" unsigned char data_0047783c;
extern "C" unsigned char g_smoll_score;
extern "C" unsigned char data_00477844;
extern "C" unsigned char data_00477848;
extern "C" unsigned char data_0047784c;
extern "C" unsigned char data_00477850;
extern "C" unsigned char data_00477864;
extern "C" unsigned char data_00477868;
extern "C" unsigned char data_0047786c;
extern "C" unsigned char data_0048f860;
extern "C" unsigned char data_00491868;
extern "C" unsigned char data_0049186c;
extern "C" unsigned char data_00491870;
extern "C" unsigned char data_00491874;
extern "C" unsigned char data_00491878;
extern "C" unsigned char data_0049187c;
extern "C" unsigned char data_00491880;
extern "C" unsigned char data_00491884;
extern "C" unsigned char data_00491888;
extern "C" unsigned char data_0049188c;
extern "C" unsigned char data_00491890;
extern "C" unsigned char data_00491894;
extern "C" unsigned char data_00491898;
extern "C" unsigned char data_0049189c;
extern "C" unsigned char data_004918a0;
extern "C" unsigned char data_004918a4;
extern "C" unsigned char data_004918a8;
extern "C" unsigned char data_004918b0;
extern "C" unsigned char data_004918b4;
extern "C" unsigned char data_00491be0;
extern "C" unsigned char data_00491be4;
extern "C" unsigned char data_00491be8;
extern "C" unsigned char data_00491bec;
extern "C" unsigned char data_00491bf0;
extern "C" unsigned char data_00491c00;
extern "C" unsigned char data_00491c04;
extern "C" unsigned char data_00491c08;
extern "C" unsigned char data_00491c10;
extern "C" unsigned char data_00491c14;
extern "C" unsigned char data_00491c18;
extern "C" unsigned char data_00491c1c;
extern "C" unsigned char data_00491c20;
extern "C" unsigned char data_00491c24;
extern "C" unsigned char data_00491c28;
extern "C" unsigned char data_00491c2c;
extern "C" unsigned char data_00491c30;
extern "C" unsigned char data_00491c34;
extern "C" unsigned char data_00491c38;
extern "C" unsigned char data_00491c3c;
extern "C" unsigned char data_00491c44;
extern "C" unsigned char data_00491c70;
extern "C" unsigned char data_00491cf4;
extern "C" unsigned char data_00491cf8;
extern "C" unsigned char data_00491cfc;
extern "C" unsigned char data_00491d00;
extern "C" unsigned char data_00491d04;
extern "C" unsigned char data_00491d08;
extern "C" unsigned char data_00491d14;
extern "C" unsigned char data_00491d44;
extern "C" unsigned char data_00491d48;
extern "C" unsigned char data_00491d4c;
extern "C" unsigned char data_00491d50;
extern "C" unsigned char data_00491d54;
extern "C" unsigned char data_00491d58;
extern "C" unsigned char data_00491d5c;
extern "C" unsigned char data_00491d5e;
extern "C" unsigned char data_00491d60;
extern "C" unsigned char data_00491d62;
extern "C" unsigned char data_00491d63;
extern "C" unsigned char data_00491d64;
extern "C" unsigned char data_00491d65;
extern "C" unsigned char data_00491d66;
extern "C" unsigned char data_00491d67;
extern "C" unsigned char data_00491d68;
extern "C" unsigned char data_00491d69;
extern "C" unsigned char data_00491d6a;
extern "C" unsigned char data_00491d78;
extern "C" unsigned char data_00491d7c;
extern "C" unsigned char data_00491d80;
extern "C" unsigned char data_00491d84;
extern "C" unsigned char data_00491d88;
extern "C" unsigned char data_00491d8c;
extern "C" unsigned char data_00491d90;
extern "C" unsigned char data_00491d94;
extern "C" unsigned char data_00491d98;
extern "C" unsigned char data_00491d9c;
extern "C" unsigned char data_00491da0;
extern "C" unsigned char data_00491da4;
extern "C" unsigned char data_00491da8;
extern "C" unsigned char data_00491db8;
extern "C" unsigned char data_00491dbc;
extern "C" unsigned char data_00491dc0;
extern "C" unsigned char data_00491dc4;
extern "C" unsigned char data_00491e48;
extern "C" unsigned char data_00491e4c;
extern "C" unsigned char data_00491e50;
extern "C" unsigned char data_00491e54;
extern "C" unsigned char data_00491e58;
extern "C" unsigned char data_00491e5c;
extern "C" unsigned char data_00491e60;
extern "C" unsigned char data_00491e64;
extern "C" unsigned char data_00491e68;
extern "C" unsigned char data_00491e6c;
extern "C" unsigned char data_00491e70;
extern "C" unsigned char data_00491e74;
extern "C" unsigned char data_00491e78;
extern "C" unsigned char data_00491e7c;
extern "C" unsigned char data_00491e80;
extern "C" unsigned char data_00491e84;
extern "C" unsigned char data_00491e88;
extern "C" unsigned char data_00491e90;
extern "C" unsigned char data_00491e94;
extern "C" unsigned char data_00491e98;
extern "C" unsigned char data_00491e9c;
extern "C" unsigned char data_00491ea0;
extern "C" unsigned char data_00491ea4;
extern "C" unsigned char data_00491ea8;
extern "C" unsigned char data_00491eac;
extern "C" unsigned char data_00491eb0;
extern "C" unsigned char data_00491eb4;
extern "C" unsigned char data_00491ed0;
extern "C" unsigned char data_00491ed4;
extern "C" unsigned char data_00491ed8;
extern "C" unsigned char data_00491edc;
extern "C" unsigned char data_00491f60;
extern "C" unsigned char data_00491f64;
extern "C" unsigned char data_00491f68;
extern "C" unsigned char data_00491f6c;
extern "C" unsigned char data_00491f70;
extern "C" unsigned char data_00491f74;
extern "C" unsigned char data_00491f78;
extern "C" unsigned char data_00491fac;
extern "C" unsigned char data_00491fb0;
extern "C" unsigned char data_00491fb4;
extern "C" unsigned char data_00491fb8;
extern "C" unsigned char data_00491fc0;
extern "C" unsigned char data_00491fc4;
extern "C" unsigned char data_00491fd4;
extern "C" unsigned char data_00491fdc;
extern "C" unsigned char data_00491fe0;
extern "C" unsigned char data_00491fe4;
extern "C" unsigned char data_00491fe8;
extern "C" unsigned char data_00491fec;
extern "C" unsigned char data_00491ff4;
extern "C" unsigned char data_00491ff8;
extern "C" unsigned char data_00492058;
extern "C" unsigned char data_00492090;
extern "C" unsigned char data_00492134;
extern "C" unsigned char data_00492148;
extern "C" unsigned char data_0049214c;
extern "C" unsigned char data_00492260;
extern "C" unsigned char data_00492264;
extern "C" unsigned char data_0049231c;
extern "C" unsigned char data_0049231e;
extern "C" unsigned char data_0049231f;
extern "C" unsigned char data_00492321;
extern "C" unsigned char data_00492378;
extern "C" unsigned char data_00492380;
extern "C" unsigned char data_00492384;
extern "C" unsigned char data_00492388;
extern "C" unsigned char data_0049238c;
extern "C" unsigned char data_004923a0;
extern "C" unsigned char data_004923a8;
extern "C" unsigned char data_004924f0;
extern "C" unsigned char data_004924f4;
extern "C" unsigned char data_004924f8;
extern "C" unsigned char data_004924fc;
extern "C" unsigned char data_00492500;
extern "C" unsigned char data_00492504;
extern "C" unsigned char data_00492508;
extern "C" unsigned char data_0049250c;
extern "C" unsigned char data_00492510;
extern "C" unsigned char data_00492514;
extern "C" unsigned char data_00492518;
extern "C" unsigned char data_0049251c;
extern "C" unsigned char data_00492520;
extern "C" unsigned char data_00492524;
extern "C" unsigned char data_00492528;
extern "C" unsigned char data_00492530;
extern "C" unsigned char data_00492538;
extern "C" unsigned char data_00492540;
extern "C" unsigned char data_00492548;
extern "C" unsigned char data_00492588;
extern "C" unsigned char data_00494514;
extern "C" unsigned char data_00494518;
extern "C" unsigned char data_00497698;
extern "C" unsigned char data_0049769c;
extern "C" unsigned char data_004976a0;
extern "C" unsigned char data_00497798;
extern "C" unsigned char data_004977a4;
extern "C" unsigned char data_004977a8;
extern "C" unsigned char data_004977ac;
extern "C" unsigned char data_004977b4;
extern "C" unsigned char data_004977b8;
extern "C" unsigned char data_004977bc;
extern "C" unsigned char data_00497854;
extern "C" unsigned char data_00497858;
extern "C" unsigned char data_0049785c;
extern "C" unsigned char data_0049786c;
extern "C" unsigned char data_00497870;
extern "C" unsigned char data_00497874;
extern "C" unsigned char data_00497884;
extern "C" unsigned char data_00497888;
extern "C" unsigned char data_0049788c;
extern "C" unsigned char data_0049789c;
extern "C" unsigned char data_004978a0;
extern "C" unsigned char data_004978a4;
extern "C" unsigned char data_004978b4;
extern "C" unsigned char data_004978b8;
extern "C" unsigned char data_004978bc;
extern "C" unsigned char data_004978c0;
extern "C" unsigned char data_004978c4;
extern "C" unsigned char data_004978c8;
extern "C" unsigned char data_004978cc;
extern "C" unsigned char data_004978d0;
extern "C" unsigned char data_004978d1;
extern "C" unsigned char data_004978d2;
extern "C" unsigned char data_004978d3;
extern "C" unsigned char data_004978d4;
extern "C" unsigned char data_004978d8;
extern "C" unsigned char data_004978dc;
extern "C" unsigned char data_004978e0;
extern "C" unsigned char data_004978e4;
extern "C" unsigned char data_004978e8;
extern "C" unsigned char data_004978ec;
extern "C" unsigned char data_004978f0;
extern "C" unsigned char data_004978f4;
extern "C" unsigned char data_004978f8;
extern "C" unsigned char data_004978fc;
extern "C" unsigned char data_00497900;
extern "C" unsigned char data_00497904;
extern "C" unsigned char data_00497908;
extern "C" unsigned char data_0049790c;
extern "C" unsigned char data_00497910;
extern "C" unsigned char data_00497914;
extern "C" unsigned char data_00497918;
extern "C" unsigned char data_0049791c;
extern "C" unsigned char data_00497920;
extern "C" unsigned char data_00497924;
extern "C" unsigned char data_00497928;
extern "C" unsigned char data_0049792c;
extern "C" unsigned char data_00497930;
extern "C" unsigned char data_00497934;
extern "C" unsigned char data_00497938;
extern "C" unsigned char data_00497940;
extern "C" unsigned char data_00497944;
extern "C" unsigned char data_00497948;
extern "C" unsigned char data_0049794c;
extern "C" unsigned char data_00497950;
extern "C" unsigned char data_00497958;
extern "C" unsigned char data_0049795c;
extern "C" unsigned char data_00497960;
extern "C" unsigned char data_00497964;
extern "C" unsigned char data_00497968;
extern "C" unsigned char data_00497970;
extern "C" unsigned char data_00497974;
extern "C" unsigned char data_00497978;
extern "C" unsigned char data_0049797c;
extern "C" unsigned char data_00497980;
extern "C" unsigned char data_00497988;
extern "C" unsigned char data_0049798c;
extern "C" unsigned char data_00497990;
extern "C" unsigned char data_00497994;
extern "C" unsigned char data_004979a0;
extern "C" unsigned char data_004979a4;
extern "C" unsigned char data_00497aaa;
extern "C" unsigned char data_00497aab;
extern "C" unsigned char data_00497aac;
extern "C" unsigned char data_00497aad;
extern "C" unsigned char data_00497aae;
extern "C" unsigned char data_00497aaf;
extern "C" unsigned char data_00497ab0;
extern "C" unsigned char data_00497ab1;
extern "C" unsigned char data_00497ab2;
extern "C" unsigned char data_00497ad9;
extern "C" unsigned char data_00497ada;
extern "C" unsigned char data_00497adb;
extern "C" unsigned char data_00497adc;
extern "C" unsigned char data_00497add;
extern "C" unsigned char data_00497ade;
extern "C" unsigned char data_00497adf;
extern "C" unsigned char data_00497ae0;
extern "C" unsigned char data_00497ae1;
extern "C" unsigned char data_00497ba8;
extern "C" unsigned char data_00497c38;
extern "C" unsigned char data_00497d80;
extern "C" unsigned char data_00497d84;
extern "C" unsigned char data_00497d88;
extern "C" unsigned char data_00497d8c;
extern "C" unsigned char data_00497f90;
extern "C" unsigned char data_00497f94;
extern "C" unsigned char data_00497f98;
extern "C" unsigned char data_00497fa0;
extern "C" unsigned char data_004980a4;
extern "C" unsigned char data_004980b0;
extern "C" unsigned char data_004981c0;
extern "C" unsigned char data_004981c4;
extern "C" unsigned char data_004981c8;
extern "C" unsigned char data_004981cc;
extern "C" unsigned char data_004981d0;
extern "C" unsigned char data_004981d4;
extern "C" unsigned char data_004991e0;
extern "C" unsigned char data_004991e4;
extern "C" unsigned char data_00499200;
extern "C" unsigned char data_00499300;
extern "C" unsigned char data_00499304;
extern "C" unsigned char data_00499308;
extern "C" unsigned char data_0049930c;
extern "C" unsigned char data_00499310;
extern "C" unsigned char data_00499314;
extern "C" unsigned char data_00499318;
extern "C" unsigned char data_00499324;
extern "C" unsigned char data_00499328;
extern "C" unsigned char data_0049932c;
extern "C" unsigned char data_00499330;
extern "C" unsigned char data_00499334;
extern "C" unsigned char data_00499338;
extern "C" unsigned char data_0049933c;
extern "C" unsigned char data_00499340;
extern "C" unsigned char data_00499344;
extern "C" unsigned char data_00499348;
extern "C" unsigned char force_disp32_zero;
extern "C" unsigned char force_imm32_zero;
