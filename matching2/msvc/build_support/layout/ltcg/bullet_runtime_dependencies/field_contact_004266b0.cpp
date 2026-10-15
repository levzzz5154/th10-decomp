extern "C" const float flt_24;
#include "th10/game/field_contact_004266b0.hpp"

#pragma code_seg(".text$03fcontact")
extern "C" __declspec(noinline) int __fastcall FieldContact004266B0(const ContactVector2* position,
                                                                    TriggerFieldContact* target,
                                                                    const ContactVector2* size) {
    ContactVector2 minimum = {position->x - size->x * 0.5f, position->y - size->y * 0.5f};
    ContactVector2 maximum = {position->x + size->x * 0.5f, position->y + size->y * 0.5f};

    // Strict ordered separation rejects; every unordered comparison passes.
    if (target->minimum.x > maximum.x || maximum.y < target->minimum.y ||
        target->maximum.x < minimum.x || target->maximum.y < minimum.y) {
        minimum.x = position->x - flt_24;
        minimum.y = position->y - flt_24;
        ContactVector2 outerMaximum = {position->x + flt_24, position->y + flt_24};
        // Negated strict predicates also accept unordered values here.
        if (outerMaximum.x < target->minimum.x || target->minimum.y > outerMaximum.y ||
            target->maximum.x < minimum.x || target->maximum.y < minimum.y)
            return 0;
        return 2;
    }
    if (g_front && g_front->active)
        return 0;
    if (target->mode == 2 || target->mode == 4 || target->mode == 3)
        return 0;
    if (target->activation_countdown <= 0)
        ActivateField00426CF0(target);
    return 1;
}
#pragma code_seg()
