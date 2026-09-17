#include "../../src/game/version_list.cpp"
#pragma code_seg(".text$03context")
int __stdcall VersionList00420dd0CompilerContext(VersionList_00420dd0* list, const char* tag, int first, int second) { return list->Match(tag, first, second); }
#pragma code_seg()
