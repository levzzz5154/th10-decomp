#include "th10/source_views/animation_manager_12b25f_0.hpp"

enum AnmIntVarOffset {
    ANM_VAR_BASE = 10000,
    ANM_VAR_OFF_I0 = 0,
    ANM_VAR_OFF_I1 = 1,
    ANM_VAR_OFF_I2 = 2,
    ANM_VAR_OFF_I3 = 3,
    ANM_VAR_OFF_F0 = 4,
    ANM_VAR_OFF_F1 = 5,
    ANM_VAR_OFF_F2 = 6,
    ANM_VAR_OFF_F3 = 7,
    ANM_VAR_OFF_I4 = 8,
    ANM_VAR_OFF_I5 = 9
};

int AnimationObjectVariables::ReadIntegerVariable(int variable) const {
    switch (variable - ANM_VAR_BASE) {
    case ANM_VAR_OFF_I0: return integer_0;
    case ANM_VAR_OFF_I1: return integer_1;
    case ANM_VAR_OFF_I2: return integer_2;
    case ANM_VAR_OFF_I3: return integer_3;
    case ANM_VAR_OFF_F0: return (int)float_0;
    case ANM_VAR_OFF_F1: return (int)float_1;
    case ANM_VAR_OFF_F2: return (int)float_2;
    case ANM_VAR_OFF_F3: return (int)float_3;
    case ANM_VAR_OFF_I4: return integer_8;
    case ANM_VAR_OFF_I5: return integer_9;
    default: return variable;
    }
}
