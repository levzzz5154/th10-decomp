#include "th10/source_views/animation_manager_12b25f_0.hpp"
int AnimationObjectVariables_0043ec70::ReadIntegerVariable(int variable) const {
    switch (variable - 10000) {
    case 0: return integer_0;
    case 1: return integer_1;
    case 2: return integer_2;
    case 3: return integer_3;
    case 4: return (int)float_0;
    case 5: return (int)float_1;
    case 6: return (int)float_2;
    case 7: return (int)float_3;
    case 8: return integer_8;
    case 9: return integer_9;
    default: return variable;
    }
}
