// Complete existing dependency semantics, with typed views of the shared
// animation manager. These native bodies are unselected in this cluster.
#include "message_teardown_dependencies.hpp"

#pragma code_seg(".text$01child")
__declspec(noinline) void EndingTextView::Destroy() {
    worker.Stop();
    for (int i = 0; i < 5; ++i) {
        MarkAnimationForRemoval(reinterpret_cast<AnimationBuckets*>(data_00491c10), animation_ids[i]);
        animation_ids[i] = 0;
    }
    worker.vtable = &platform_worker_vtable;
    worker.Stop();
}
#pragma code_seg()

#pragma code_seg(".text$09clear")
void NativeRenderManager::Clear(int index) {
    if (primary[index]) { primary[index]->methods->Release(primary[index]);primary[index]=0; }
    if (secondary[index]) { secondary[index]->methods->Release(secondary[index]);secondary[index]=0; }
    if (memory[index]) { entry_free_00452422(memory[index]);memory[index]=0; }
    memory[index]=0;
}
#pragma code_seg()

#pragma code_seg(".text$07release")
void AnimationResource_00447810::Release() {
    if (resource_108 == 0)
        return;
    reinterpret_cast<AnimationManager*>(data_00491c10)->MarkResourceForRemoval(this);
    for (int index = 0; index < entry_count_10c; ++index) {
        AnimationResourceEntry_00447810* entry = &entries_120[index];
        if (entry->handle != 0) {
            entry->handle->slot2();
            entry->handle = 0;
        }
        if (entry->allocation != 0) {
            entry_free_00452422(entry->allocation);
            entry->allocation = 0;
        }
    }
    if (entries_120 != 0) {
        entry_free_00452422(entries_120);
        entries_120 = 0;
    }
    if (auxiliary_118 != 0) {
        entry_free_00452422(auxiliary_118);
        auxiliary_118 = 0;
    }
    if (auxiliary_11c != 0) {
        entry_free_00452422(auxiliary_11c);
        auxiliary_11c = 0;
    }
    if (auxiliary_12c != 0) {
        entry_free_00452422(auxiliary_12c);
        auxiliary_12c = 0;
    }
    if (resource_108 != 0) {
        entry_free_00452422(resource_108);
        resource_108 = 0;
    }
}
#pragma code_seg()

#pragma code_seg(".text$11mark")
__declspec(noinline) void AnimationManager::MarkResourceForRemoval(void* resource) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(this);

    AnimationListNode* node = *reinterpret_cast<AnimationListNode**>(
        bytes + 0x72dad4);
    while (node) {
        AnimationListNode* next = node->next;
        unsigned char* object = static_cast<unsigned char*>(node->object);
        if (*reinterpret_cast<void**>(object + 0x308) == resource)
            *reinterpret_cast<unsigned int*>(object + 0x35c) |= 0x04000000u;
        node = next;
    }

    node = *reinterpret_cast<AnimationListNode**>(bytes + 0x72dadc);
    while (node) {
        AnimationListNode* next = node->next;
        unsigned char* object = static_cast<unsigned char*>(node->object);
        if (*reinterpret_cast<void**>(object + 0x308) == resource)
            *reinterpret_cast<unsigned int*>(object + 0x35c) |= 0x04000000u;
        node = next;
    }
}
#pragma code_seg()

#pragma code_seg(".text$13remove")
extern "C" __declspec(noinline) void __stdcall Scheduler_Remove(Scheduler* scheduler, SchedulerTask* task) {
    if (!task) return;
    TaskLink* node = &scheduler->primary.link;
    while (node) {
        if (node->task == task) break;
        node = node->next;
    }
    if (!node) {
        node = &scheduler->secondary.link;
        while (node) {
            if (node->task == task) break;
            node = node->next;
        }
    }
    if (node && node->previous) {
        node->Unlink();
        task->on_tick = 0;
        if (task->heap_owned) delete task;
    }
}
#pragma code_seg()

#pragma code_seg(".text$15stop")
__declspec(noinline) void PlatformWorker::Stop() {
    if (thread) {
        stop_requested = 1;
        running = 0;
        while (WaitForSingleObject(thread, 200) == 258) {
            stop_requested = 1;
            running = 0;
            Sleep(1);
        }
        CloseHandle(thread);
        thread = 0;
        entry = 0;
    }
}
#pragma code_seg()

