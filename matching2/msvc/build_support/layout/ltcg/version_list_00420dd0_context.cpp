#include "../../../src/game/mother/version_list.cpp"
#pragma code_seg(".text$03context")
int __stdcall VersionList00420dd0CompilerContext(VersionList* list, const char* tag, int first, int second) { return list->Match(tag, first, second); }
#pragma code_seg()
