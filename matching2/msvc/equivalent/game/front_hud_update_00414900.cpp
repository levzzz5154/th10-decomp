// 0x00414900 - the stage-front scheduler tick. Every frame it advances the
// fifteen front animation banks, opens/closes the boss gauge against the play
// thresholds, spawns the difficulty banner object, runs the ten one-shot
// notice slots, drives the stage-script walker (0x00415E90) and releases its
// animations when the script finishes, replays the stage-progress banner and
// sounds, fades the boss name in near the boss, and returns one.
//
// The scheduler reaches this body through the 0x00415AE0 trampoline; the
// single stack argument is the stage-front runtime (0x0047770C).

#include <math.h>
#include "th10/game/front_hud_pair_00414900.hpp"

namespace {

// The play-state record behind 0x00477834.
struct PlayState_00477834 {
    unsigned char pad_0000[0x10];
    int field_10;
    unsigned char pad_0014[0x3C0 - 0x14];
    float field_3C0;
    float field_3C4;
    unsigned char pad_03c8[0x23FC - 0x3C8];
    int field_23FC;
    int field_2400;
};

// The sequence record behind 0x00477704.
struct SequenceRecord_00477704 {
    unsigned char pad_0000[0x10];
    unsigned char* field_10;
    unsigned char pad_0014[0x38 - 0x14];
    int field_38;
};

// The script body the sequence record points at.
struct ScriptBody {
    unsigned char pad_0000[0x1068];
    float boss_y_1068;
    unsigned char pad_106c[0x23FC - 0x106C];
    int gauge_value_23fc;
    int gauge_range_2400;
    int gate_frame_2404;
    unsigned char pad_2408[0x2480 - 0x2408];
    unsigned int flags_2480;
};

// The animation runtime sub-record at front+0x9EB8.
struct SequenceRuntime {
    unsigned char pad_0000[4];
    int ramp_previous;
    int ramp_current;
    float ramp_elapsed;
    const float* ramp_speed;
    unsigned char pad_0014[0x40 - 0x14];
    unsigned int slots[6];
};

// The two-list animation registration.
struct AnimationListNode {
    Entity* object;
    AnimationListNode* next;
    AnimationListNode* previous;
};

struct AnimationLists {
    unsigned char reserved[0x72DAD4];
    AnimationListNode* primary_head;
    AnimationListNode* primary_tail;
    AnimationListNode* secondary_head;
    unsigned char reserved_72dae0[0x732454 - 0x72DAE0];
    unsigned int next_id;
};

// The lookup walk the retail body inlines at every user.
__forceinline AnimationTreeNode* FindTree(unsigned int handle) {
    if (handle == 0) return 0;
    AnimationLists* lists = (AnimationLists*)data_00491c10;
    for (AnimationListNode* node = lists->primary_head; node != 0; node = node->next)
        if (*(int*)node->object == (int)handle)
            return (AnimationTreeNode*)node->object;
    for (AnimationListNode* node = lists->secondary_head; node != 0; node = node->next)
        if (*(int*)node->object == (int)handle)
            return (AnimationTreeNode*)node->object;
    return 0;
}

// Flag one animation tree's stop frame.
__forceinline void FlagStopFrame1(unsigned int handle) {
    AnimationTreeNode* node = FindTree(handle);
    if (node != 0) {
        volatile int frame = 1;
        node->stop_frame = (unsigned short)frame;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 1;
        }
    }
}

__forceinline void FlagStopFrame2(unsigned int handle) {
    AnimationTreeNode* node = FindTree(handle);
    if (node != 0) {
        volatile int frame = 2;
        node->stop_frame = (unsigned short)frame;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 2;
        }
    }
}

__forceinline void FlagStopFrame3(unsigned int handle) {
    AnimationTreeNode* node = FindTree(handle);
    if (node != 0) {
        volatile int frame = 3;
        node->stop_frame = (unsigned short)frame;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = 3;
        }
    }
}

// Flag one animation tree (and its unflagged children) for removal.
__forceinline void FlagTreeFlags(unsigned int handle) {
    AnimationTreeNode* node = FindTree(handle);
    if (node != 0) {
        *(unsigned int*)((char*)node + 0x35C) |= 0x4000000u;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                *(unsigned int*)((char*)child->object + 0x35C) |= 0x4000000u;
        }
    }
}

// Register one fresh object and return its new handle.
inline unsigned int RegisterFreshObject(Entity* object, FrontHudRuntime* front) {
    AnimationListNode* node = (AnimationListNode*)&object->manager_node_animation;
    node->object = object;
    node->next = 0;
    node->previous = 0;
    AnimationLists* lists = (AnimationLists*)data_00491c10;
    if (lists->primary_head == 0) {
        lists->primary_head = node;
    } else {
        AnimationListNode* tail = lists->primary_tail;
        AnimationListNode* next = tail->next;
        if (next != 0) {
            node->next = next;
            next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    lists->primary_tail = node;
    unsigned int id = lists->next_id + 1;
    lists->next_id = id;
    if (id == 0) {
        id = 1;
        lists->next_id = id;
    }
    object->animation_handle = (int)lists->next_id;
    return lists->next_id;
}

}  // namespace

#pragma code_seg(".text$00414900_fn")
__declspec(noinline) int __stdcall FrontHudUpdate_00414900(
    FrontHudRuntime* front) {
    if (front->flags_9eb4 & 0x10) {
        if (++front->banner_timer_9ecc >= 0x78) {
            unsigned int gate = *(unsigned int*)&data_00491ff4;
            data_00491fb8 = (gate & 0x1000 ? 0xFFFFFFF4u : 0) + 0xE;
        }
    }
    {
        FrontHudRuntime::BankObject* vm = front->objects;
        for (int n = 9; n != 0; --n) {
            AnmVm_Run_0043ee30(vm);
            vm += 1;
        }
    }
    {
        FrontHudRuntime::BankObject* vm = &front->objects[9];
        for (int n = 4; n != 0; --n) {
            AnmVm_Run_0043ee30(vm);
            vm += 1;
        }
    }
    {
        FrontHudRuntime::BankObject* vm = &front->objects[13];
        for (int n = 2; n != 0; --n) {
            AnmVm_Run_0043ee30(vm);
            vm += 1;
        }
    }
    if ((front->flags_9eb4 & 1) == 0) {
        PlayState_00477834* play = (PlayState_00477834*)data_00477834;
        if (play != 0 && play->field_3C4 > data_00470bdc &&
            play->field_3C0 < data_00470d10) {
            FrontHudRuntime::BankObject* obj = &front->objects[15];
            for (int n = 7; n != 0; --n) {
                obj->stop_frame = 3;
                obj += 1;
            }
            front->flags_9eb4 |= 1;
        }
    } else {
        PlayState_00477834* play = (PlayState_00477834*)data_00477834;
        if (play != 0 &&
            (play->field_3C4 < data_00470d08 || data_00470d00 < play->field_3C0)) {
            FrontHudRuntime::BankObject* obj = &front->objects[15];
            for (int n = 7; n != 0; --n) {
                obj->stop_frame = 2;
                obj += 1;
            }
            front->flags_9eb4 &= ~1u;
        }
    }
    {
        int value = data_00474c4c;
        int divisor = 10000;
        AnmVm_Run_0043ee30(&front->objects[15]);
        FrontHudRuntime::BankObject* obj = &front->objects[16];
        for (int n = 5; n != 0; --n) {
            int digit = value / divisor;
            value = value % divisor;
            ((Resource_0043e5a0*)front->resource_9ec8)->ConfigureObject(
                (AnimationObject_0043e5a0*)obj, digit + 0x1E);
            divisor = divisor / 10;
            AnmVm_Run_0043ee30(obj);
            obj += 1;
        }
    }
    AnmVm_Run_0043ee30(&front->objects[21]);

    SequenceRecord_00477704* seq = (SequenceRecord_00477704*)data_00477704;
    if (seq && seq->field_10 && !front->sequence_9eb8) {
        ScriptBody* body = (ScriptBody*)seq->field_10;
        int gauge_value = body->gauge_value_23fc;
        front->gauge_value_9e8c = gauge_value;
        float ratio = (float)gauge_value / (float)body->gauge_range_2400;
        front->gauge_ratio_9e88 = ratio;
        if (ratio > front->gauge_disp_9e84) {
            front->gauge_disp_9e84 += data_00470cf8;
        }
        if (front->gauge_disp_9e84 > ratio) {
            front->gauge_disp_9e84 = ratio;
        }
        PlayState_00477834* play = (PlayState_00477834*)data_00477834;
        if ((front->flags_9eb4 & 8) == 0) {
            if (play->field_3C4 <= data_00470bc8 && play->field_3C0 < data_00470b5c) {
                int count = front->boss_id_count_9e90;
                for (int i = 0; i < count; ++i) {
                    if (front->boss_ids_9e28[i] != 0) {
                        FlagStopFrame3(front->boss_ids_9e28[i]);
                    }
                }
                if (front->pending_id_9e24 != 0) {
                    FlagStopFrame3(front->pending_id_9e24);
                }
                front->flags_9eb4 |= 8;
            }
        } else {
            if (play->field_3C4 >= data_00470c28 || play->field_3C0 > data_00470b04) {
                int count = front->boss_id_count_9e90;
                for (int i = 0; i < count; ++i) {
                    if (front->boss_ids_9e28[i] != 0) {
                        FlagStopFrame2(front->boss_ids_9e28[i]);
                    }
                }
                int pending = front->pending_id_9e24;
                if (pending == 0) {
                    front->flags_9eb4 &= ~8u;
                } else {
                    FlagStopFrame2(pending);
                    front->flags_9eb4 &= ~8u;
                }
            }
        }
        if (front->pending_id_9e24 == 0) {
            int script = 0x85;
            switch (data_00474c7c) {
            case 1:
                if (data_00474c84 >= 0x18)
                    script = 0x86;
                break;
            case 2:
                if (data_00474c84 < 0x18)
                    goto have_script;
                script = 0x87;
                break;
            case 3:
                if (data_00474c84 < 0x18)
                    goto have_script;
                script = 0x88;
                break;
            case 4:
                script = (data_00474c84 >= 0x18 ? 1 : 0) + 0x89;
                break;
            case 5:
                script = 0x8B;
                break;
            case 6:
                script = 0x8C;
                break;
            case 7:
                script = (data_00474c84 >= 0x18 ? 1 : 0) + 0x8C;
                break;
            }
            {
                AnimationPool* pool = (AnimationPool*)data_00491c10;
                Entity* object = pool->Allocate();
                unsigned int flags = object->flags_35C;
                object->flags_35C = flags | 0x40000000u;
                object->render_bucket = 15;
                ((AnimationResource_00449870*)front->resource_9ec8)
                    ->InitializeObject(object, script);
                front->pending_id_9e24 = (int)RegisterFreshObject(object, front);
            }
        }
    have_script:;
    } else {
        if (front->pending_id_9e24 != 0) {
            FlagStopFrame1(front->pending_id_9e24);
            front->pending_id_9e24 = 0;
        }
        front->gauge_disp_9e84 = 0;
        *(int*)((char*)&front->gauge_disp_9e84 + 0x10) = 0;
        *(int*)((char*)&front->gauge_disp_9e84 + 0x18) = 0;
        *(int*)((char*)&front->gauge_disp_9e84 + 0x20) = 0;
        *(int*)((char*)&front->gauge_disp_9e84 + 0x28) = 0;
    }

    // Ten one-shot notice slots: create the missing ones, flag the live ones
    // and clear them after the walk.
    {
        int count = front->boss_id_count_9e90;
        for (int i = 0; i < 10; ++i) {
            int* slot = &front->boss_ids_9e28[i];
            if (i < count && *slot == 0) {
                AnimationPool* pool = (AnimationPool*)data_00491c10;
                Entity* object = pool->Allocate();
                unsigned int flags = object->flags_35C;
                object->flags_35C = flags | 0x40000000u;
                object->render_bucket = 15;
                ((AnimationResource_00449870*)front->resource_9ec8)
                    ->InitializeObject(object, 0x5B + i);
                *slot = (int)RegisterFreshObject(object, front);
            }
            if (*slot != 0) {
                FlagStopFrame1(*slot);
                *slot = 0;
            }
        }
    }

    SequenceRuntime* runtime = (SequenceRuntime*)front->sequence_9eb8;
    if (runtime != 0) {
        int finished = ResultDispatcher_00415e90((ResultDispatcherState*)front);
        if (finished == 0) {
            // The inlined frame-ramp tick on the sub-record.
            runtime->ramp_previous = runtime->ramp_current;
            if (*runtime->ramp_speed > data_00470b68 &&
                *runtime->ramp_speed < data_00470b64) {
                ++runtime->ramp_current;
                runtime->ramp_elapsed += 1.0f;
            } else {
                runtime->ramp_current =
                    (int)(runtime->ramp_elapsed += *runtime->ramp_speed);
            }
        } else {
            FlagTreeFlags(runtime->slots[0]);
            runtime->slots[0] = 0;
            FlagTreeFlags(runtime->slots[1]);
            runtime->slots[1] = 0;
            FlagTreeFlags(runtime->slots[2]);
            runtime->slots[2] = 0;
            FlagTreeFlags(runtime->slots[3]);
            runtime->slots[3] = 0;
            FlagTreeFlags(runtime->slots[4]);
            runtime->slots[4] = 0;
            FlagTreeFlags(runtime->slots[5]);
            runtime->slots[5] = 0;
            FrontFree_004524a1(front->sequence_9eb8);
            front->sequence_9eb8 = 0;
        }
    }

    seq = (SequenceRecord_00477704*)data_00477704;
    if (seq != 0) {
        int position = front->script_pos_9ec0;
        if (position >= 0) {
            ScriptBody* body = (ScriptBody*)seq->field_10;
            if (body != 0 && front->sequence_9eb8 == 0) {
                if (position < front->script_marked_9ec4) {
                    if (position <= 5) {
                        front->objects[13].stop_frame = 9;
                        front->objects[14].stop_frame = 9;
                        data_00492590.Queue(0x24, 0);
                    } else if (position <= 0xA) {
                        front->objects[13].stop_frame = 8;
                        front->objects[14].stop_frame = 8;
                        data_00492590.Queue(0x1B, 0);
                    }
                } else if (position > front->script_marked_9ec4) {
                    front->objects[13].stop_frame = 7;
                    front->objects[14].stop_frame = 7;
                }
                if (front->script_pos_9ec0 != front->script_marked_9ec4) {
                    int shown = front->script_pos_9ec0;
                    ((Resource_0043e5a0*)front->resource_9ec8)->ConfigureObject(
                        (AnimationObject_0043e5a0*)&front->objects[13],
                        shown / 10 + 8);
                    ((Resource_0043e5a0*)front->resource_9ec8)->ConfigureObject(
                        (AnimationObject_0043e5a0*)&front->objects[14],
                        shown % 10 + 8);
                }
                front->script_marked_9ec4 = front->script_pos_9ec0;
                // The difficulty gate adjusts the boss name display word.
                unsigned int flags = body->flags_2480;
                if (((~flags >> 4) & 1) != 0 && (~flags & 1) != 0) {
                    unsigned char* state = (unsigned char*)data_004776f4;
                    unsigned int lane = (front->flags_9eb4 >> 1) & 3;
                    int gate = body->gate_frame_2404;
                    int show;
                    unsigned short word;
                    if (state[0x378C] & 1) {
                        if (lane == 0) {
                            show = gate < 0x7D0;
                            word = 7;
                        } else if (lane == 1) {
                            show = gate < 0x3E8;
                            word = 8;
                        } else if (lane == 2) {
                            show = gate < 0x190;
                            word = 9;
                        } else {
                            show = gate > 0x190;
                            word = 0xA;
                        }
                    } else {
                        if (lane == 0) {
                            show = gate < 0x2BC;
                            word = 7;
                        } else if (lane == 1) {
                            show = gate < 0x190;
                            word = 8;
                        } else if (lane == 2) {
                            show = gate < 0xC8;
                            word = 9;
                        } else {
                            show = gate > 0xC8;
                            word = 0xA;
                        }
                    }
                    if (show) {
                        front->objects[22].stop_frame = word;
                        if (lane == 0) {
                            front->flags_9eb4 = (front->flags_9eb4 & ~4u) | 2;
                        } else if (lane == 1) {
                            front->flags_9eb4 = (front->flags_9eb4 & ~2u) | 4;
                        } else if (lane == 2) {
                            front->flags_9eb4 |= 6;
                        } else {
                            front->flags_9eb4 &= ~6u;
                        }
                    }
                    // The boss bank tick and its fade-in window.
                    AnmVm_Run_0043ee30(&front->objects[22]);
                    front->objects[22].height_344 = 480.0f;
                    front->objects[22].y_340 = body->boss_y_1068 + data_00470b4c;
                    float offset =
                        body->boss_y_1068 - ((PlayState_00477834*)data_00477834)->field_3C0;
                    if (fabs(offset) < data_00470cf0) {
                        front->objects[22].alpha_2ff =
                            (unsigned char)(0x40 - (int)(fabs(offset) * data_00470ce8));
                    } else {
                        front->objects[22].alpha_2ff = 0xFF;
                    }
                    if (body->boss_y_1068 < data_00470b40 ||
                        body->boss_y_1068 > data_00470b3c) {
                        front->objects[22].alpha_2ff = 0;
                    }
                }
            }
        }
    }
    // The boss frame ramp advance (an inlined copy of the frame timer tick).
    front->boss_frame_9e60 = front->boss_frame_prev_9e64;
    if (*front->boss_speed_9e6c > data_00470b68 &&
        *front->boss_speed_9e6c < data_00470b64) {
        ++front->boss_frame_prev_9e64;
        front->boss_frame_acc_9e68 += 1.0f;
    } else {
        front->boss_frame_acc_9e68 += *front->boss_speed_9e6c;
        front->boss_frame_prev_9e64 = (int)front->boss_frame_acc_9e68;
    }
    return 1;
}
#pragma code_seg()
