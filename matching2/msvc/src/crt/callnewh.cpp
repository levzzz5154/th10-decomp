extern "C" int (__cdecl *_pnhHeap)(unsigned int);

extern "C" int __cdecl crt_callnewh(unsigned int size) {
    int (__cdecl *handler)(unsigned int) = _pnhHeap;
    if (handler && handler(size)) return 1;
    return 0;
}
