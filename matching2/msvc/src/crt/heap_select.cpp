extern "C" int _osplatform;
extern "C" unsigned int _winmajor;

extern "C" int __cdecl crt_heap_select() {
    if (_osplatform == 2 && _winmajor >= 5) return 1;
    return 3;
}
