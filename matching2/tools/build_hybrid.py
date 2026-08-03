#!/usr/bin/env python3
"""Build a runnable TH10 image by overlaying matched functions on the retail PE.

The retail executable supplies the not-yet-reimplemented code, global data,
imports, and resources. Every overlay is compiled from this tree and must match
the retail bytes outside linker relocation operands. This keeps the intermediate
binary playable while functions are replaced incrementally.
"""

import argparse
import hashlib
import shutil
import sys
from pathlib import Path

from compare_obj import IMAGE_BASE, read_coff_function


EXPECTED_SHA256 = "2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040"
DEFAULT_EXE = Path("/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe")

# object, unique symbol fragment, original virtual address
OVERLAYS = (
    ("entity.obj", "Entity_Destructor", 0x00401FF0),
    ("entity.obj", "Entity_Constructor", 0x00402050),
    ("entity.obj", "EntitySecondaryResource_Release", 0x00405DE0),
    ("entity.obj", "EntityAnimation_Release", 0x0041AD60),
    ("entity.obj", "DestroyEntityList", 0x00438A30),
    ("entity.obj", "?Entity_PointWithinBounds@@", 0x00406160),
    ("entity.obj", "?Entity_PointWithinBoundsInclusive@@", 0x004061D0),
    ("bullet.obj", "Entity_AttachResourceSnapshot", 0x0040B250),
    ("bullet.obj", "BulletSpawnParameters_Initialize", 0x0040CF40),
    ("bullet.obj", "BulletEntity_ClearResourceList", 0x0040C6E0),
    ("bullet.obj", "BulletEntity_SetAnimationVector", 0x0040CF60),
    ("bullet.obj", "BulletEntity_FindById", 0x0040CF90),
    ("bullet.obj", "BulletEntity_ReleaseResource", 0x0040D680),
    ("bullet.obj", "?BulletEntity_MarkAnimationForRemoval@@", 0x0040CEA0),
    ("bullet.obj", "?Entity_ClearAnims@@", 0x0040CC70),
    ("bullet.obj", "?BulletManager_Release@@", 0x0040AF00),
    ("bullet.obj", "?BulletManager_LoadScripts@@", 0x0040AE70),
    ("bullet.obj", "?BulletManager_Create@@", 0x0040AF90),
    ("heap.obj", "HeapBuffer_Release", 0x00435250),
    ("heap.obj", "0HeapBuffer", 0x004352C0),
    ("file.obj", "??_GFileHandle", 0x00435320),
    ("file.obj", "??1FileHandle", 0x00435340),
    ("file.obj", "Close@FileHandle", 0x00435460),
    ("file.obj", "Read@FileHandle", 0x00435490),
    ("file.obj", "Write@FileHandle", 0x004354D0),
    ("file.obj", "Tell@FileHandle", 0x00435510),
    ("file.obj", "GetSize@FileHandle", 0x00435530),
    ("file.obj", "Seek@FileHandle", 0x00435550),
    ("file.obj", "??1FileInterface", 0x00435690),
    ("file.obj", "??_GFileInterface", 0x004356A0),
    ("memory_file.obj", "Write@BufferFile", 0x00436370),
    ("memory_file.obj", "??_GBufferFile", 0x004363A0),
    ("memory_file.obj", "??1BufferFile", 0x004363C0),
    ("memory_file.obj", "Close@BufferFile", 0x00436430),
    ("memory_file.obj", "Read@BufferFile", 0x00436460),
    ("memory_file.obj", "Tell@BufferFile", 0x004364D0),
    ("memory_file.obj", "GetSize@BufferFile", 0x004364E0),
    ("resource_file.obj", "??_GResourceFile", 0x00436660),
    ("heap.obj", "LegacyString_Clear", 0x004381F0),
    ("heap.obj", "?Length@LegacyString", 0x00438250),
    ("heap.obj", "QAEPADXZ", 0x00438680),
    ("heap.obj", "Deallocate@LegacyAllocator", 0x00438690),
    ("heap.obj", "MaxSize@LegacyAllocator", 0x004386A0),
    ("heap.obj", "OwnsPointer@LegacyString", 0x00438800),
    ("heap.obj", "Allocate@LegacyAllocator", 0x00438840),
    ("heap.obj", "SetLength@LegacyString", 0x00438590),
    ("heap.obj", "?Heap_DestroyOwned@@", 0x00418150),
    ("heap.obj", "?Heap_DestroyOwnedSecondary@@", 0x0042CDB0),
    ("heap.obj", "?LegacyString_Duplicate@@", 0x00435220),
    ("heap.obj", "?Assign@LegacyString@@", 0x00438350),
    ("heap.obj", "?AssignSubstring@LegacyString@@", 0x00438260),
    ("heap.obj", "?Reserve@LegacyString@@", 0x00438380),
    ("heap.obj", "?AssignRange@LegacyString@@", 0x00438420),
    ("heap.obj", "?Erase@LegacyString@@", 0x00438510),
    ("heap.obj", "?Grow@LegacyString@@", 0x004386B0),
    ("runtime_pool.obj", "RuntimeAllocationPool_Initialize", 0x004388F0),
    ("stage_tips.obj", "StageTip_Initialize", 0x00418D00),
    ("angle.obj", "?Angle_Normalize@@", 0x0044BC70),
    ("angle.obj", "?Angle_NormalizeSum@@", 0x0044BC10),
    ("rng.obj", "?Rng_NextU32@@", 0x0044B9E0),
    ("rng.obj", "?Rng_NextU32DoubleStep@@", 0x0044BA80),
    ("rng.obj", "?Rng_NextFloat@@", 0x0044BB20),
    ("rng.obj", "?Rng_NextFloatSigned@@", 0x0044BB90),
    ("vector.obj", "?SetPolar@Vector2@@", 0x0041F800),
    ("vector.obj", "Vector2_SetPolar", 0x004458B0),
    ("timer.obj", "?GameState_SetTimerTarget@@", 0x0042C620),
    ("timer.obj", "?GameState_DisableTimerWithOwner@@", 0x0042C5C0),
    ("timer.obj", "?FrameTimer_Advance@@", 0x0044BF40),
    ("timer.obj", "?FrameTimer_Tick@@", 0x00404ED0),
    ("timer.obj", "?EmbeddedTimer_Reset@@", 0x004050D0),
    ("timer.obj", "?FrameTimer_Decrement@@", 0x00428DD0),
    ("math_utils.obj", "?Vec_Subtract@@", 0x00404D40),
    ("scheduler.obj", "?GameState_DispatchDummy@@", 0x00420C00),
    ("scheduler.obj", "?GameState_UpdateFrameMaximum@@", 0x00421F60),
    ("scheduler.obj", "?GameState_Unpause@@", 0x00422C30),
    ("scheduler.obj", "?GameState_DispatchAnimationSlot@@", 0x0042C730),
    ("scheduler.obj", "?GameState_DispatchAnimationSlotSecondary@@", 0x0042C750),
    ("scheduler.obj", "?Scheduler_CreateAndRegister@@", 0x0044A000),
    ("scheduler.obj", "?SchedulerCallback_Create@@", 0x00449ED0),
    ("scheduler.obj", "?Scheduler_RegisterPrimary@@", 0x00449AE0),
    ("scheduler.obj", "?Scheduler_RegisterSecondary@@", 0x00449B70),
    ("scheduler.obj", "?Scheduler_Remove@@", 0x00449F60),
    ("scheduler.obj", "?Scheduler_CreateAndRegisterSecondary@@", 0x0044A030),
    ("path.obj", "?Path_DecodeXor@@", 0x00417010),
    ("path.obj", "?Path_FindBasenameSlot@@", 0x0043D2A0),
    ("process.obj", "?Platform_InvokeInterface@@", 0x0044D5B0),
    ("win32_timer.obj", "?TimerWin32_Release@@", 0x004203C0),
    ("file.obj", "?File_CloseProbeHandle@@", 0x0044B7E0),
    ("file.obj", "?File_WriteShared@@", 0x0044B740),
    ("file.obj", "?File_ReadShared@@", 0x0044B790),
    ("file.obj", "?File_ProbeExists@@", 0x0044B4D0),
    ("file.obj", "?File_OpenSharedWrite@@", 0x0044B620),
    ("file.obj", "?File_OpenSharedRead@@", 0x0044B6B0),
    ("file.obj", "?File_WriteWholeFile@@", 0x0044B540),
    ("file.obj", "?File_ResolvePath@@", 0x00435610),
    ("file.obj", "?ReadWhole@FileHandle@@", 0x00435580),
    ("file.obj", "FileHandle_OpenRetail", 0x00435370),
    ("memory_file.obj", "?Resource_FindChunk@@", 0x0043D250),
    ("memory_file.obj", "?MemoryFile_RelinkChild@@", 0x00436260),
    ("memory_file.obj", "?MemoryFile_FindPredecessor@@", 0x00436330),
    ("memory_file.obj", "?MemoryFile_ReplaceNode@@", 0x004362B0),
    ("memory_file.obj", "?MemoryFile_RemoveNode@@", 0x00436210),
    ("stage_text.obj", "?StageText_SkipLine@@", 0x004349E0),
    ("stage_text.obj", "?StageText_ExtractLine@@", 0x00434A20),
    ("stage_text.obj", "?StageText_Initialize@@", 0x00434A80),
    ("dat.obj", "?DatArchive_Reset@@", 0x00434C20),
    ("dat.obj", "?DatArchive_Open@@", 0x00434C30),
    ("dat.obj", "?DatArchive_Close@@", 0x00434D10),
    ("dat.obj", "?DatArchive_Read@@", 0x00434DD0),
    ("dat.obj", "?DatArchive_LoadIndex@@", 0x00434F70),
    ("dat.obj", "?DatArchive_FindEntry@@", 0x00434F30),
    ("dat.obj", "?DatArchive_FindSize@@", 0x00434EF0),
    ("animation_manager.obj", "?AnimationColor_MultiplyChannel@@", 0x004423C0),
    ("animation_manager.obj", "?AnimationManager_ValidateHandle@@", 0x00449450),
    ("animation_manager.obj", "?AnimationManager_SelectSpriteFromCurrentResource@@", 0x00449670),
    ("animation_manager.obj", "?AnimationManager_SelectSpriteFromResource@@", 0x004496A0),
    ("animation_manager.obj", "?AnimationManager_SetStopFrame@@", 0x00449210),
    ("animation_manager.obj", "?AnimationManager_StopAtFrame2@@", 0x0040C480),
    ("animation_manager.obj", "?AnimationManager_SetStopFrameAndRun@@", 0x00449250),
    ("animation_manager.obj", "?AnimationManager_SetFlag@@", 0x004492A0),
    ("animation_manager.obj", "?AnimationManager_ClearResourceSlot@@", 0x004477D0),
    ("animation_manager.obj", "?AnimationManager_StopAtFrame3@@", 0x0040C4D0),
    ("animation_manager.obj", "?AnimationManager_ClearFlag@@", 0x004495E0),
    ("animation_manager.obj", "?AnimationManager_SetFlagBit1@@", 0x00449590),
    ("animation_manager.obj", "?AnimationManager_SetPosition@@", 0x004492F0),
    ("animation_manager.obj", "?AnimationManager_CreatePrimaryBack@@", 0x00448D00),
    ("animation_manager.obj", "?AnimationManager_CreatePositionedPrimary@@", 0x00448D50),
    ("animation_manager.obj", "?AnimationManager_CreatePrimaryFront@@", 0x00448E30),
    ("animation_manager.obj", "?AnimationManager_CreateSecondaryBack@@", 0x00448F60),
    ("animation_manager.obj", "?AnimationManager_CreateSecondaryFront@@", 0x00449090),
    ("animation_manager.obj", "?AnimationManager_Find@@", 0x004491C0),
    ("animation_manager.obj", "?AnimationManager_MarkForRemovalAndClearHandle@@", 0x00449630),
    ("animation_manager.obj", "?AnimationManager_RenderBucket@@", 0x00448980),
    ("animation_manager.obj", "?AnimationManager_ClearIndexedResources@@", 0x00447F70),
    ("animation_manager.obj", "?AnimationManager_RegisterPrimaryBack@@", 0x004489D0),
    ("animation_manager.obj", "?AnimationManager_RegisterPrimaryFront@@", 0x00448A50),
    ("animation_manager.obj", "?AnimationManager_RegisterSecondaryBack@@", 0x00448AC0),
    ("animation_manager.obj", "?AnimationManager_RegisterSecondaryFront@@", 0x00448B40),
    ("animation_manager.obj", "?PlayerAnimation_Create@@", 0x00448DB0),
    ("animation_manager.obj", "?AnimationManager_SetTranslatedPosition@@", 0x00449350),
    ("animation_manager.obj", "?AnimationManager_MarkResourceForRemoval@@", 0x004493E0),
    ("animation_manager.obj", "?AnimationManager_QueueResource@@", 0x0043DC90),
    ("animation_manager.obj", "?AnimationManager_CopyPositionRecord@@", 0x00447940),
    ("animation_manager.obj", "?AnimationManager_UpdatePrimary@@", 0x00448860),
    ("animation_manager.obj", "?AnimationManager_UpdateSecondary@@", 0x00448900),
    ("animation_manager.obj", "?AnimationManager_FindChildByScriptIndex@@", 0x004497D0),
    ("animation_manager.obj", "?AnimationTexture_Create@@", 0x00447050),
    ("animation_manager.obj", "?AnimationObject_ReadIntegerVariable@@", 0x0043EC70),
    ("animation_manager.obj", "?AnimationObject_ResolveIntegerVariable@@", 0x0043EDA0),
    ("animation_manager.obj", "?AnimationObject_ResolveFloatVariable@@", 0x0043ED00),
    ("animation_manager.obj", "?AnimationManager_RegisterResource@@", 0x0043E460),
    ("animation_manager.obj", "?AnimationObject_LoadScript@@", 0x0043E710),
    ("animation_manager.obj", "?AnimationObject_LoadScriptPreservingState@@", 0x0043E7E0),
    ("animation_manager.obj", "?AnimationObject_ConfigureFromResource@@", 0x0043E5A0),
    ("animation_manager.obj", "?AnimationObject_ChangeScript@@", 0x0043E8B0),
    ("d3d_resource_manager.obj", "?D3DResourceManager_Initialize@@", 0x00449AA0),
    ("d3d_resource_manager.obj", "?D3DResourceList_ClearPending@@", 0x00449A90),
    ("d3d_resource_manager.obj", "?D3DResourceList_ReleaseResources@@", 0x00449E50),
    ("d3d_resource_manager.obj", "?D3DResourceManager_Destroy@@", 0x00438880),
    ("ecl_vm.obj", "?ECL_ResolveIntFromEntity@@", 0x00412A00),
    ("ecl_vm.obj", "?ECL_ResolveIntDestination@@", 0x00412A10),
    ("ecl_vm.obj", "?ECL_ResolveIntValue@@", 0x0044FF00),
    ("ecl_vm.obj", "?ECL_ResolveIntOperand@@", 0x0044FDB0),
    ("ecl_vm.obj", "?ECL_ResolveFloatOperand@@", 0x0044FE40),
    ("ecl_vm.obj", "?ECL_ResolveFloatValue@@", 0x0044FF80),
    ("ecl_vm.obj", "?ECL_SetPolarVector@@", 0x004501B0),
    ("ecl_vm.obj", "?ECL_ResolveVariableValue@@", 0x00450030),
    ("ecl_vm.obj", "?ECL_ResolveFloatDestination@@", 0x00450070),
    ("ecl_vm.obj", "?ECL_FindVariable@@", 0x00450160),
    ("ecl_vm.obj", "?ECL_ResetVariableBindings@@", 0x00450190),
    ("ecl_vm.obj", "?ECL_PushScratchValue@@", 0x00450690),
    ("ecl_vm.obj", "?ECL_PopScratchValue@@", 0x004506D0),
    ("sound_float_forward.obj", "?Sound_ForwardFloatAsDouble@@", 0x00427C50),
    ("sound_stream_start.obj", "SoundStream_Start", 0x0044D440),
    ("process.obj", "?Platform_DestroyWorker@@", 0x0044C100),
    ("process.obj", "?Platform_StopWorkerNoDelete@@", 0x0044C130),
    ("process.obj", "?Platform_LaunchProcess@@", 0x00436570),
    ("process.obj", "?Platform_GetOsVersionCode@@", 0x0044BD10),
    ("process.obj", "?Platform_StopWorker@@", 0x0044C150),
    ("game_thread_queue.obj", "?GameThread_AppendFormatted@@", 0x00401630),
    ("game_thread_queue.obj", "?GameThread_AppendRecord@@", 0x00401530),
    ("archive_cursor_open.obj", "ArchiveCursor_Open", 0x0044DBF0),
    ("dat_file.obj", "DatArchive_OpenResource", 0x00434CA0),
    ("game_config_defaults.obj", "GameConfig_InitializeDefaults", 0x00418C40),
    ("prng.obj", "EntityScript_NextRandomModulo", 0x0043CB80),
    ("vector3_cross.obj", "Vector3_Cross", 0x00421B90),
    ("particle_seed.obj", "ParticleSeed_Combine", 0x00404E10),
    ("progress.obj", "GameProgress_HasAnyPlayRecord", 0x0042C850),
    ("menu.obj", "MenuCursor_Advance", 0x0044BEA0),
    ("ecl_vm_children.obj", "EclVm_SpawnChild", 0x004500D0),
    ("ecl_vm_children.obj", "EclVm_TickChildren", 0x0044FD10),
    ("weather_pool.obj", "EffectPool_UpdateDrops", 0x0042B6F0),
    ("random_vector.obj", "RandomVector_StoreRoundedScalar", 0x00441E50),
    ("quad_vertex_append.obj", "AnimationManager_AppendQuadVertices", 0x00442FE0),
    ("anm_batch_flush.obj", "AnimationManager_FlushQuadBatch", 0x00442F50),
    ("game_ui_create.obj", "GameUi_CreateAndPublish", 0x004180E0),
    ("stage_tip_manager.obj", "StageTip_CreateUrgent", 0x00424650),
    ("recovery_leaves.obj", "EffectManager_ResetAndPublishRetail", 0x0042B430),
    ("recovery_leaves.obj", "EffectManagerRuntime_InitializeRetail", 0x0042B4D0),
    ("progress.obj", "?GameProgress_UnlockAllStages@@", 0x0042C8C0),
    ("progress_worker.obj", "?ProgressManager_CreateAndStartWorker@@", 0x0042CD50),
    ("player.obj", "?PlayerManager_StartMode@@", 0x004045B0),
    ("player.obj", "Player_SetSchedulerValue", 0x00405410),
    ("player.obj", "Player_AdjustPower", 0x00405B60),
    ("player.obj", "Player_Draw", 0x00405AC0),
    ("player_motion.obj", "?Player_ForwardAxisWrap@@", 0x0040678E),
    ("player_motion.obj", "Player_WrapHorizontal", 0x00407DA0),
    ("score.obj", "?ScoreOwnedObject_Destroy@@", 0x0040B9D0),
    ("score.obj", "OutsideAxisAlignedBounds", 0x004086B0),
    ("score.obj", "Score_SetPolarVector", 0x00408750),
    ("score.obj", "?InputMaskActive@@", 0x0040ACE0),
    ("score.obj", "?SetInputMode@@", 0x0040AC90),
    ("score.obj", "?Score_InputHistoryStep@@", 0x0044BE70),
    ("score.obj", "?Score_InputHistorySave@@", 0x0044BE20),
    ("score.obj", "?AddScaled@ScoreCounter@@", 0x0041BE80),
    ("score.obj", "?ScoreGauge_AddWithMinimum@@", 0x00412E70),
    ("score.obj", "?Retire@ScoreRuntimeCallbacks@@", 0x00409E20),
    ("score.obj", "?RunArrayReleaseCallback@ScoreRuntimeState@@", 0x00409270),
    ("score.obj", "?WrappedAngleDifference@@", 0x00408660),
    ("score.obj", "?CountPatternMatches@@", 0x004088C0),
    ("score.obj", "?ReleaseFlaggedEntities@ScoreRuntimeState@@", 0x00409230),
    ("score.obj", "?ScoreRecords_MarkEligible@@", 0x0041C7D0),
    ("score.obj", "?ScoreRecords_CopyVectorAndEvaluate@@", 0x0041C800),
    ("score.obj", "?Position_IsPartiallyInViewport@@", 0x0041F7A0),
    ("score.obj", "?Entity_AngleToPoint@@", 0x00426610),
    ("score.obj", "?Entity_AngleFromPoint@@", 0x00426660),
    ("score.obj", "?Input_NormalizeKeyboardState@@", 0x0044B080),
    ("score.obj", "?EffectPool_OutsideViewport@@", 0x00428D70),
    ("score.obj", "?AddScaled@GameScore@@", 0x00409D90),
    ("score.obj", "?UpdateInputState@@", 0x0040AC20),
    ("score.obj", "?ReleaseFlaggedEntityArrays@ScoreRuntimeState@@", 0x004091C0),
    ("score.obj", "?Input_UpdateKeyboardState@@", 0x0044B010),
    ("recovery_leaves.obj", "?Score_SetNormalizedAngle@@", 0x00413170),
    ("recovery_leaves.obj", "GameThread_RunQueueLeaf", 0x00401520),
    ("recovery_leaves.obj", "Recovery_InvokeZero", 0x00427950),
    ("recovery_leaves.obj", "Recovery_InvokeVoid", 0x004198A0),
    ("recovery_leaves.obj", "Recovery_InvokePair", 0x00422A90),
    ("recovery_leaves.obj", "Score_SetMode", 0x00412ED0),
    ("recovery_leaves.obj", "RecoveryTimer_Reset", 0x00412DB0),
    ("recovery_leaves.obj", "ScoreList_InsertAfter", 0x00413200),
    ("recovery_leaves.obj", "Vector2_SetEllipticPolar", 0x00413270),
    ("recovery_leaves.obj", "Vector2_SetAnimationPolar", 0x00441EF0),
    ("recovery_leaves.obj", "PathState_Reset", 0x00417800),
    ("recovery_leaves.obj", "Bullet_DeletingDestructor", 0x0040CC50),
    ("recovery_leaves.obj", "?Platform_DeletingDestructor@@", 0x0044CF00),
    ("recovery_leaves.obj", "Ecl_ForwardFloat", 0x00412AA0),
    ("recovery_leaves.obj", "Ecl_SetResourceSlot", 0x00412720),
    ("recovery_leaves.obj", "Animation_SetActiveCount", 0x00413790),
    ("recovery_leaves.obj", "Recovery_TrimWhitespace", 0x0041A0A0),
    ("recovery_leaves.obj", "Recovery_OffsetPoint", 0x00418810),
    ("recovery_leaves.obj", "Recovery_DecayCounter", 0x00418A00),
    ("recovery_leaves.obj", "Platform_InvokeConfigured", 0x0044D5D0),
    ("recovery_leaves.obj", "?Platform_AggregateInterfaces@@", 0x0044D550),
    ("recovery_leaves.obj", "?Platform_QueryInterfaces@@", 0x0044D600),
    ("recovery_leaves.obj", "?Platform_FindAvailable@@", 0x0044D370),
    ("recovery_leaves.obj", "RecoveryLinkedCleanup", 0x00417770),
    ("recovery_leaves.obj", "RecoveryState_Initialize", 0x004220E0),
    ("recovery_leaves.obj", "?Platform_ReleaseOwnedArray@@", 0x0044D080),
    ("recovery_leaves.obj", "Recovery_AppendNode", 0x0041AB10),
    ("recovery_leaves.obj", "?Platform_DeletingDestructorVtable@@", 0x0044D710),
    ("recovery_leaves.obj", "?Platform_DeletingDestructorNoReturn@@", 0x0043C870),
    ("recovery_leaves.obj", "?RecoveryState_Configure41F50@@", 0x00441F50),
    ("recovery_leaves.obj", "Recovery_SplitResourcePath", 0x0041A050),
    ("recovery_leaves.obj", "Recovery_ResetEmitter", 0x0040C9A0),
    ("recovery_leaves.obj", "Recovery_ClearEightBuckets", 0x00419040),
    ("recovery_leaves.obj", "Recovery_InitializeStateTable", 0x0041F850),
    ("recovery_leaves.obj", "?Platform_SelectStreamRecord@@", 0x0044DCA0),
    ("recovery_leaves.obj", "?Recovery_SelectArchiveEntry@@", 0x0043D790),
    ("recovery_leaves.obj", "?Platform_ReleaseOwnedHandle@@", 0x00413450),
    ("recovery_leaves.obj", "?Recovery_SwitchPlaybackState@@", 0x00427AE0),
    ("recovery_leaves.obj", "?Platform_SetOperationDeadline@@", 0x0044D4E0),
    ("recovery_leaves.obj", "?Recovery_TickState@@", 0x0040BD20),
    ("recovery_leaves.obj", "?Platform_RunInterface@@", 0x0044D300),
    ("recovery_leaves.obj", "?Platform_DeletingDestructorWithRelease@@", 0x004297B0),
    ("recovery_leaves.obj", "?Recovery_ReleasePair@@", 0x0041F930),
    ("recovery_leaves.obj", "?Recovery_InitializeTimedState@@", 0x00423510),
    ("recovery_leaves.obj", "?Recovery_LoadCachedResource@@", 0x00447280),
    ("recovery_leaves.obj", "?Recovery_InitializeLargeState@@", 0x00421F00),
    ("recovery_leaves.obj", "?Recovery_LoadStartupResources@@", 0x0041F8D0),
    ("recovery_leaves.obj", "?Recovery_InstallAnimationSlot@@", 0x0042C670),
    ("recovery_leaves.obj", "?Recovery_ClearAnimationSlot@@", 0x0042C6D0),
    ("recovery_leaves.obj", "?Recovery_InstallPairSetFlags@@", 0x004055C0),
    ("recovery_leaves.obj", "?Recovery_InstallPairClearFlags@@", 0x0041AD90),
    ("recovery_leaves.obj", "Recovery_ScaleColor", 0x00404DA0),
    ("recovery_leaves.obj", "Recovery_InitializeWordColor", 0x00405040),
    ("recovery_leaves.obj", "Recovery_CreateFixedState", 0x004056B0),
    ("recovery_leaves.obj", "Recovery_CreateSmallState", 0x0040B940),
    ("recovery_leaves.obj", "Recovery_ReleaseRawPairAndReset", 0x00405620),
    ("recovery_leaves.obj", "Recovery_InitializeSingleInterface", 0x0044D6A0),
    ("recovery_leaves.obj", "Recovery_AdvancePolarMotion", 0x0044C2A0),
    ("recovery_leaves.obj", "Recovery_PolarToVectorRetail", 0x0044C5D0),
    ("recovery_leaves.obj", "Recovery_DispatchRandomText", 0x004479D0),
    ("recovery_leaves.obj", "Recovery_DispatchSchedule", 0x00428160),
    ("recovery_leaves.obj", "RecoveryState_Configure42300", 0x00442300),
    ("recovery_leaves.obj", "Recovery_UpdateStageSequence", 0x004281D0),
    ("recovery_leaves.obj", "Recovery_InitializeInterfaceArray", 0x0044CE80),
    ("recovery_leaves.obj", "Recovery_ReplaceExtensionWav", 0x00420A90),
    ("recovery_leaves.obj", "Recovery_ReleaseCompositeState", 0x00414570),
    ("recovery_leaves.obj", "Recovery_ReleaseGlobalStates", 0x004203F0),
    ("recovery_leaves.obj", "?Recovery_ReleaseRawPair@@", 0x0043CB00),
    ("recovery_leaves.obj", "Recovery_MarkAnimationTree", 0x004243F0),
    ("recovery_leaves.obj", "Recovery_AppendPacket", 0x0042A8A0),
    ("recovery_leaves.obj", "Recovery_CreateTimerState", 0x00422360),
    ("recovery_leaves.obj", "Recovery_CreateLargeResourceState", 0x00425020),
    ("recovery_leaves.obj", "Recovery_StartWorker", 0x0041FAC0),
    ("recovery_leaves.obj", "Recovery_InitializeRandomTable", 0x0042ADD0),
    ("recovery_leaves.obj", "Recovery_CreateHugeResourceState", 0x0042B660),
    ("recovery_leaves.obj", "Recovery_ResetDeviceStreams", 0x0043BC40),
    ("recovery_leaves.obj", "Recovery_CreateTextureFromMemory", 0x00446EB0),
    ("recovery_leaves.obj", "Recovery_MarkLogState", 0x00447A50),
    ("recovery_leaves.obj", "Recovery_UpdateEmitterDecision", 0x0040B9F0),
    ("recovery_leaves.obj", "Recovery_IncrementAnimationCount", 0x004188A0),
    ("recovery_leaves.obj", "Recovery_CreateResourceState", 0x00419090),
    ("recovery_leaves.obj", "Recovery_FindNamedValue", 0x004198C0),
)


def read_pe_sections(image):
    pe_offset = int.from_bytes(image[0x3C:0x40], "little")
    if image[pe_offset:pe_offset + 4] != b"PE\0\0":
        raise ValueError("input is not a PE image")
    coff = pe_offset + 4
    section_count = int.from_bytes(image[coff + 2:coff + 4], "little")
    optional_size = int.from_bytes(image[coff + 16:coff + 18], "little")
    table = coff + 20 + optional_size
    sections = []
    for index in range(section_count):
        offset = table + index * 40
        name = image[offset:offset + 8].rstrip(b"\0").decode("ascii")
        virtual_size = int.from_bytes(image[offset + 8:offset + 12], "little")
        virtual_address = int.from_bytes(image[offset + 12:offset + 16], "little")
        raw_size = int.from_bytes(image[offset + 16:offset + 20], "little")
        raw_offset = int.from_bytes(image[offset + 20:offset + 24], "little")
        sections.append((name, virtual_address, virtual_size, raw_offset, raw_size))
    return sections


def virtual_to_file(sections, address, size):
    rva = address - IMAGE_BASE
    for name, virtual_address, virtual_size, raw_offset, raw_size in sections:
        extent = max(virtual_size, raw_size)
        if virtual_address <= rva and rva + size <= virtual_address + extent:
            relative = rva - virtual_address
            if relative + size > raw_size:
                raise ValueError("overlay at 0x{:08X} reaches uninitialized {} data"
                                 .format(address, name))
            return raw_offset + relative
    raise ValueError("address 0x{:08X} is not backed by a PE section".format(address))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--original", type=Path, default=DEFAULT_EXE)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    original_hash = hashlib.sha256(args.original.read_bytes()).hexdigest()
    if original_hash != EXPECTED_SHA256:
        raise SystemExit("unsupported original executable (SHA-256 {})".format(original_hash))

    image = bytearray(args.original.read_bytes())
    sections = read_pe_sections(image)
    overlay_count = 0
    overlay_bytes = 0

    for object_name, symbol, address in OVERLAYS:
        resolved_name, compiled, relocation_bytes = read_coff_function(
            args.objects / object_name, symbol)
        file_offset = virtual_to_file(sections, address, len(compiled))
        retail = image[file_offset:file_offset + len(compiled)]
        mismatches = [index for index in range(len(compiled))
                      if index not in relocation_bytes and compiled[index] != retail[index]]
        if mismatches:
            preview = ", ".join("+0x{:X}".format(index) for index in mismatches[:8])
            raise SystemExit("{} is not matched: {} differing byte(s), {}"
                             .format(resolved_name, len(mismatches), preview))

        # Relocation fields in COFF objects are linker placeholders. Preserve
        # their already-resolved retail values while overlaying compiled bytes.
        for index, value in enumerate(compiled):
            if index not in relocation_bytes:
                image[file_offset + index] = value
        overlay_count += 1
        overlay_bytes += len(compiled) - len(relocation_bytes)
        print("overlay: {} at 0x{:08X} ({} verified bytes)"
              .format(resolved_name, address, len(compiled) - len(relocation_bytes)))

    args.output.parent.mkdir(parents=True, exist_ok=True)
    temporary = args.output.with_suffix(args.output.suffix + ".tmp")
    temporary.write_bytes(image)
    shutil.copymode(args.original, temporary)
    temporary.replace(args.output)

    result_hash = hashlib.sha256(image).hexdigest()
    print("built: {}".format(args.output))
    print("verified overlays: {} functions, {} bytes".format(overlay_count, overlay_bytes))
    print("SHA-256: {}".format(result_hash))
    if result_hash == original_hash:
        print("image match: 100% (all current C++ overlays are byte-identical)")


if __name__ == "__main__":
    main()
