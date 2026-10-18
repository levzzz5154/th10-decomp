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
#include "th10/game/front_hud_pair.hpp"

namespace {

// The sequence record behind 0x00477704.
struct SequenceRecord {
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

struct AnimationRef {
    unsigned int value;
    AnimationRef() {}
    AnimationRef(unsigned int value_) : value(value_) {}
    unsigned int operator++() { return ++value; }
    bool operator==(unsigned int other) const { return value == other; }
};
struct AnimationLists {
    unsigned char reserved[0x72DAD4];
    AnimationListNode* primary_head;
    AnimationListNode* primary_tail;
    AnimationListNode* secondary_head;
    unsigned char reserved_72dae0[0x732454 - 0x72DAE0];
    AnimationRef next_id;
};

// The lookup walk the retail body inlines at every user.
__forceinline AnimationTreeNode* FindTree(unsigned int handle) {
    if (handle == 0) return 0;
    AnimationLists* lists = (AnimationLists*)g_sprt_ctrl;
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
        unsigned short frame = 1;
        node->stop_frame = frame;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}

__forceinline void FlagStopFrame2(unsigned int handle) {
    AnimationTreeNode* node = FindTree(handle);
    if (node != 0) {
        unsigned short frame = 2;
        node->stop_frame = frame;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
        }
    }
}

__forceinline void FlagStopFrame3(unsigned int handle) {
    AnimationTreeNode* node = FindTree(handle);
    if (node != 0) {
        unsigned short frame = 3;
        node->stop_frame = frame;
        if (!node->children_flagged) {
            for (AnimationTreeNode* child = node->children;
                 child != 0; child = child->next)
                child->object->stop_frame = frame;
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

__forceinline void FlagAndClearSlot(unsigned int& slot) {
    FlagTreeFlags(slot);
    slot = 0;
}

// Register one fresh object and return its new handle.
inline unsigned int RegisterFreshObject(Entity* object, FrontUpdateView* front) {
    AnimationListNode* node = (AnimationListNode*)&object->manager_node_animation;
    node->object = object;
    node->next = 0;
    node->previous = 0;
    AnimationLists* lists = (AnimationLists*)g_sprt_ctrl;
    if (lists->primary_head == 0) {
        lists->primary_head = node;
    } else {
        AnimationListNode* tail = lists->primary_tail;
        AnimationListNode* next = tail->next;
        if (next != 0) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    lists->primary_tail = node;
    ++lists->next_id;
    if (lists->next_id == 0) {
        ++lists->next_id;
    }
    object->animation_handle = (int)lists->next_id.value;
    return lists->next_id.value;
}

}  // namespace

#pragma code_seg(".text$00414900_fn")
__declspec(noinline) int __stdcall FrontHudUpdate(
    FrontUpdateView* front) {
    if (front->flags_9eb4 & 0x10) {
        if (++front->banner_timer_9ecc >= 0x78) {
            unsigned int gate = *(unsigned int*)&g_app_flags;
            g_main_state = (gate & 0x1000 ? 0xFFFFFFF4u : 0) + 0xE;
        }
    }
    {
        FrontUpdateView::BankObject* vm = front->objects;
        for (int n = 9; n != 0; --n) {
            AnmVm_Run(vm);
            vm += 1;
        }
    }
    {
        FrontUpdateView::BankObject* vm = &front->objects[9];
        for (int n = 4; n != 0; --n) {
            AnmVm_Run(vm);
            vm += 1;
        }
    }
    {
        FrontUpdateView::BankObject* vm = &front->objects[13];
        for (int n = 2; n != 0; --n) {
            AnmVm_Run(vm);
            vm += 1;
        }
    }
    if ((front->flags_9eb4 & 1) == 0) {
        Player* play = g_player;
        if (play != 0 && play->position.y > flt_416 &&
            play->position.x < dbl_neg128) {
            FrontUpdateView::BankObject* obj = &front->objects[15];
            for (int n = 7; n != 0; --n) {
                obj->stop_frame = 3;
                obj += 1;
            }
            front->flags_9eb4 |= 1;
        }
    } else {
        Player* play = g_player;
        if (play != 0 &&
            (play->position.y < flt_400 || dbl_neg112 < play->position.x)) {
            FrontUpdateView::BankObject* obj = &front->objects[15];
            for (int n = 7; n != 0; --n) {
                obj->stop_frame = 2;
                obj += 1;
            }
            front->flags_9eb4 &= ~1u;
        }
    }
    {
        int value = g_globals_gauge;
        int divisor = 10000;
        AnmVm_Run(&front->objects[15]);
        FrontUpdateView::BankObject* obj = &front->objects[16];
        for (int n = 5; n != 0; --n) {
            int digit = value / divisor;
            value = value % divisor;
            ((Resource2*)front->resource_9ec8)->ConfigureObject(
                (AnimationObject3*)obj, digit + 0x1E);
            divisor = divisor / 10;
            AnmVm_Run(obj);
            obj += 1;
        }
    }
    AnmVm_Run(&front->objects[21]);

    SequenceRecord* seq = (SequenceRecord*)g_enemy_ctrl;
    if (seq && seq->field_10 && !front->sequence_9eb8) {
        ScriptBody* body = (ScriptBody*)seq->field_10;
        int gauge_value = body->gauge_value_23fc;
        front->gauge_value_9e8c = gauge_value;
        front->gauge_ratio_9e88 = (float)gauge_value / (float)body->gauge_range_2400;
        if (front->gauge_ratio_9e88 > front->gauge_disp_9e84) {
            front->gauge_disp_9e84 = front->gauge_disp_9e84 + flt_0_025;
        }
        if (front->gauge_disp_9e84 > front->gauge_ratio_9e88) {
            *(int*)&front->gauge_disp_9e84 = *(int*)&front->gauge_ratio_9e88;
        }
        Player* play = g_player;
        if (front->flags_9eb4 & 8) {
            if (play->position.y >= flt_80 || play->position.x > flt_0) {
                for (int i = 0; i < front->boss_id_count_9e90; ++i) {
                    if (front->boss_ids_9e28[i] != 0) {
                        FlagStopFrame2(front->boss_ids_9e28[i]);
                    }
                }
                if (front->pending_id_9e24 != 0) {
                    FlagStopFrame2(front->pending_id_9e24);
                }
                front->flags_9eb4 &= ~8u;
            }
        } else {
            if (play->position.y <= flt_64 && play->position.x < flt_neg64) {
                for (int i = 0; i < front->boss_id_count_9e90; ++i) {
                    if (front->boss_ids_9e28[i] != 0) {
                        FlagStopFrame3(front->boss_ids_9e28[i]);
                    }
                }
                if (front->pending_id_9e24 != 0) {
                    FlagStopFrame3(front->pending_id_9e24);
                }
                front->flags_9eb4 |= 8;
            }
        }
        if (front->pending_id_9e24 == 0) {
            int script = 0x85;
            switch (g_globals_stage) {
            case 1:
                if ((int)g_stage_progress >= 0x18)
                    script = 0x86;
                break;
            case 2:
                if ((int)g_stage_progress < 0x18)
                    goto have_script;
                script = 0x87;
                break;
            case 3:
                if ((int)g_stage_progress < 0x18)
                    goto have_script;
                script = 0x88;
                break;
            case 4:
                script = ((int)g_stage_progress >= 0x18 ? 1 : 0) + 0x89;
                break;
            case 5:
                script = 0x8B;
                break;
            case 6:
                script = 0x8C;
                break;
            case 7:
                script = ((int)g_stage_progress >= 0x18 ? 1 : 0) + 0x8C;
                break;
            }
            {
                AnimationBank* resource =
                    (AnimationBank*)front->resource_9ec8;
                AnimationPool* pool = (AnimationPool*)g_sprt_ctrl;
                Entity* object = pool->Allocate();
                unsigned int flags = object->flags_35C;
                object->flags_35C = flags | 0x40000000u;
                object->render_bucket = 15;
                resource->InitializeObject(object, script);
                front->pending_id_9e24 = (int)RegisterFreshObject(object, front);
            }
        }
    have_script:
        // Ten one-shot notice slots: create the missing ones, flag the live ones
        // and clear them after the walk.
        {
            for (unsigned int i = 0; i < 10; ++i) {
                int* slot = &front->boss_ids_9e28[i];
                if ((int)i < front->boss_id_count_9e90) {
                    if (*slot != 0)
                        continue;
                    AnimationBank* resource =
                        (AnimationBank*)front->resource_9ec8;
                    AnimationPool* pool = (AnimationPool*)g_sprt_ctrl;
                    Entity* object = pool->Allocate();
                    unsigned int flags = object->flags_35C;
                    object->flags_35C = flags | 0x40000000u;
                    object->render_bucket = 15;
                    resource->InitializeObject(object, 0x5B + i);
                    *slot = (int)RegisterFreshObject(object, front);
                } else if (*slot != 0) {
                    FlagStopFrame1(*slot);
                    *slot = 0;
                }
            }
        }
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

    SequenceRuntime* runtime = (SequenceRuntime*)front->sequence_9eb8;
    if (runtime != 0) {
        int finished = ResultDispatcher2((ResultDispatcherState*)runtime);
        if (finished == 0) {
            // The inlined frame-ramp tick on the sub-record.
            runtime->ramp_previous = runtime->ramp_current;
            if (*runtime->ramp_speed > flt_0_99 &&
                *runtime->ramp_speed < flt_1_01) {
                ++runtime->ramp_current;
                runtime->ramp_elapsed += 1.0f;
            } else {
                runtime->ramp_current =
                    (int)(runtime->ramp_elapsed += *runtime->ramp_speed);
            }
        } else {
          runtime = (SequenceRuntime*)front->sequence_9eb8;
          if (runtime != 0) {
            FlagAndClearSlot(runtime->slots[0]);
            FlagAndClearSlot(runtime->slots[1]);
            FlagAndClearSlot(runtime->slots[2]);
            FlagAndClearSlot(runtime->slots[3]);
            FlagAndClearSlot(runtime->slots[4]);
            FlagAndClearSlot(runtime->slots[5]);
            FrontFree(runtime);
          }
            front->sequence_9eb8 = 0;
        }
    }

    seq = (SequenceRecord*)g_enemy_ctrl;
    if (seq != 0) {
        int position = front->script_pos_9ec0;
        if (position >= 0 && seq->field_10 != 0 && front->sequence_9eb8 == 0) {
            if (position < front->script_marked_9ec4) {
                if (position <= 5) {
                    front->objects[13].stop_frame = 9;
                    front->objects[14].stop_frame = 9;
                    g_sound_manager.Queue(0x24, 0);
                } else if (position <= 0xA) {
                    front->objects[13].stop_frame = 8;
                    front->objects[14].stop_frame = 8;
                    g_sound_manager.Queue(0x1B, 0);
                }
            } else if (position > front->script_marked_9ec4) {
                front->objects[13].stop_frame = 7;
                front->objects[14].stop_frame = 7;
            }
            if (front->script_pos_9ec0 != front->script_marked_9ec4) {
                ((Resource2*)front->resource_9ec8)->ConfigureObject(
                    (AnimationObject3*)&front->objects[13],
                    front->script_pos_9ec0 / 10 + 8);
                ((Resource2*)front->resource_9ec8)->ConfigureObject(
                    (AnimationObject3*)&front->objects[14],
                    front->script_pos_9ec0 % 10 + 8);
            }
            front->script_marked_9ec4 = front->script_pos_9ec0;
            seq = (SequenceRecord*)g_enemy_ctrl;
        }
        ScriptBody* body = (ScriptBody*)seq->field_10;
        if (body != 0) {
            // The difficulty gate adjusts the boss name display word.
            unsigned int gate_flags = body->flags_2480;
            if ((~(gate_flags >> 4) & 1) != 0 && (~gate_flags & 1) != 0) {
                unsigned char* state = (unsigned char*)g_card;
                if (state[0x378C] & 1) {
                    unsigned int flags = front->flags_9eb4;
                    unsigned int lane = (flags >> 1) & 3;
                    if (lane == 0) {
                        if (body->gate_frame_2404 < 0x7D0) {
                            front->objects[22].stop_frame = 7;
                            front->flags_9eb4 = (flags & ~4u) | 2;
                        }
                    } else if (lane == 1) {
                        if (body->gate_frame_2404 < 0x3E8) {
                            front->objects[22].stop_frame = 8;
                            front->flags_9eb4 = (flags & ~2u) | 4;
                        }
                    } else if (lane == 2) {
                        if (body->gate_frame_2404 < 0x190) {
                            front->objects[22].stop_frame = 9;
                            front->flags_9eb4 = flags | 6;
                        }
                    } else if (lane == 3) {
                        if (body->gate_frame_2404 > 0x190) {
                            front->objects[22].stop_frame = 0xA;
                            front->flags_9eb4 = flags & ~6u;
                        }
                    }
                } else {
                    unsigned int flags = front->flags_9eb4;
                    unsigned int lane = (flags >> 1) & 3;
                    if (lane == 0) {
                        if (body->gate_frame_2404 < 0x2BC) {
                            front->objects[22].stop_frame = 7;
                            front->flags_9eb4 = (flags & ~4u) | 2;
                        }
                    } else if (lane == 1) {
                        if (body->gate_frame_2404 < 0x190) {
                            front->objects[22].stop_frame = 8;
                            front->flags_9eb4 = (flags & ~2u) | 4;
                        }
                    } else if (lane == 2) {
                        if (body->gate_frame_2404 < 0xC8) {
                            front->objects[22].stop_frame = 9;
                            front->flags_9eb4 = flags | 6;
                        }
                    } else if (lane == 3) {
                        if (body->gate_frame_2404 > 0xC8) {
                            front->objects[22].stop_frame = 0xA;
                            front->flags_9eb4 = flags & ~6u;
                        }
                    }
                }
                // The boss bank tick and its fade-in window.
                AnmVm_Run(&front->objects[22]);
                front->objects[22].y_340 = body->boss_y_1068 + flt_224;
                front->objects[22].height_344 = 480.0f;
                float offset = (float)fabs(
                    body->boss_y_1068 - g_player->position.x);
                if (offset >= dbl_64) {
                    front->objects[22].alpha_2ff = 0xFF;
                } else {
                    front->objects[22].alpha_2ff =
                        (unsigned char)(0x40 - (int)(offset * flt_neg2_984375));
                }
                if (body->boss_y_1068 < flt_neg192 ||
                    body->boss_y_1068 > flt_192) {
                    front->objects[22].alpha_2ff = 0;
                }
            }
        }
    }
    // The boss frame ramp advance (an inlined copy of the frame timer tick).
    front->boss_frame_9e60 = front->boss_frame_prev_9e64;
    if (*front->boss_speed_9e6c > flt_0_99 &&
        *front->boss_speed_9e6c < flt_1_01) {
        ++front->boss_frame_prev_9e64;
        front->boss_frame_acc_9e68 += 1.0f;
    } else {
        front->boss_frame_acc_9e68 += *front->boss_speed_9e6c;
        front->boss_frame_prev_9e64 = (int)front->boss_frame_acc_9e68;
    }
    return 1;
}
#pragma code_seg()
