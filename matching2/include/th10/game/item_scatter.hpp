#pragma once

// Configured item-group scatter around the plan origin (retail 0x0040C9D0).
// Retail function 0x0040C9D0.
struct ItemDropVec3{float x,y,z;};
struct ItemDropPlan{int counts[12];ItemDropVec3 origin;float radius_x,radius_y;};
struct ItemDropEnv{float(*random_unit)();float(*random_signed)();void(*spawn)(const ItemDropVec3&,int,int,float,float);};
int ItemDrop_ScatterGroups(ItemDropPlan*,const ItemDropEnv*);
