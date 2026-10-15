struct RuntimeException_00462d9e {
    RuntimeException_00462d9e* Assign(RuntimeException_00462d9e* other);
    void Destroy();
    void BaseInit(RuntimeException_00462d9e* other);
};
RuntimeException_00462d9e* RuntimeException_00462d9e::Assign(RuntimeException_00462d9e* other) {
    if (this != other) {
        Destroy();
        BaseInit(other);
    }
    return this;
}
