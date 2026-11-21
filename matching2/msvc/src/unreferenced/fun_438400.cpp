// 0x00438400. The object pointer arrives in ECX and is handed straight back in
// EAX, so this is the identity method of a struct whose interface wants the
// object pointer as a method result.
struct RecoverySelf {
    RecoverySelf* Self();
};

RecoverySelf* RecoverySelf::Self() {
    return this;
}
