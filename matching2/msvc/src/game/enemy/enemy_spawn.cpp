// 0x0040CFB0..0x0040D1F1: create an enemy.
//
// The record is allocated and bound to the named script entry, takes its
// position, score, life, drop item, two flags and eight script variables from
// the spawn description, and runs its script up to the first wait. Enemies
// flagged for boss-style drops swap the two power item kinds for their large
// forms. The death sound alternates with the creation count, the death effect
// follows the enemy kind the script chose, and the enemy joins the end of the
// manager's list. The switch tables follow the body.
//
// The spawn description arrives in EAX.
#include "th10/game/enemy_spawn.hpp"
#include <string.h>

enum EnemyDropItemId {
    ENEMY_DROP_POWER_SMALL = 1,
    ENEMY_DROP_POWER_LARGE = 4,
    ENEMY_DROP_POWER_BOSS_SMALL = 10,
    ENEMY_DROP_POWER_BOSS_LARGE = 11
};

enum EnemySpawnKind {
    ENEMY_KIND_FAIRY = 1
};

enum EnemyDeathEffectId {
    ENEMY_DEATH_EFFECT_RED = 0x164,
    ENEMY_DEATH_EFFECT_BLUE = 0x167,
    ENEMY_DEATH_EFFECT_YELLOW = 0x16A,
    ENEMY_DEATH_EFFECT_GREEN = 0x16D
};

#pragma code_seg(".text$0040cfb0_fn")
EnemySpawnView* EnemySpawn2::Create(EnemyCtrlSpawnView* manager, const char* entry) {
    EnemySpawnView* enemy = new EnemySpawnView(entry);

    enemy->data.position = position;
    enemy->data.score = score;
    enemy->data.life = life;
    enemy->data.drop_item = drop_item;
    enemy->data.flags.mirrored = mirrored;
    enemy->difficulty_mask = (unsigned char)(1 << g_globals.difficulty);
    memcpy(enemy->data.variables, variables, sizeof(variables));
    enemy->data.invulnerable_timer.Set(2);
    enemy->data.flags.quiet = quiet;
    EnemyData_Start(&enemy->data);

    if (enemy->data.flags.boss_items) {
        int item = enemy->data.drop_item;
        if (item == ENEMY_DROP_POWER_SMALL)
            item = ENEMY_DROP_POWER_BOSS_SMALL;
        else if (item == ENEMY_DROP_POWER_LARGE)
            item = ENEMY_DROP_POWER_BOSS_LARGE;
        enemy->data.drop_item = item;
    }

    enemy->data.death_sound = (manager->created & 1) + 2;
    enemy->data.death_effect = ENEMY_DEATH_EFFECT_BLUE;
    if (enemy->data.kind == ENEMY_KIND_FAIRY) {
        switch (enemy->data.kind_index) {
        case 0:
        case 20:
        case 49:
            enemy->data.death_effect = ENEMY_DEATH_EFFECT_BLUE;
            break;
        case 5:
        case 25:
        case 50:
            enemy->data.death_effect = ENEMY_DEATH_EFFECT_RED;
            break;
        case 15:
        case 35:
        case 52:
            enemy->data.death_effect = ENEMY_DEATH_EFFECT_GREEN;
            break;
        case 10:
        case 30:
        case 51:
            enemy->data.death_effect = ENEMY_DEATH_EFFECT_YELLOW;
            break;
        }
    }
    enemy->data.death_file = 0;

    EnemySpawnListNode* node = &enemy->data.node;
    if (manager->head == 0) {
        manager->head = node;
    } else {
        EnemySpawnListNode* tail = manager->tail;
        if (tail->next != 0) {
            node->next = tail->next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    manager->tail = node;
    ++manager->count;
    ++manager->created;
    return enemy;
}
#pragma code_seg()
