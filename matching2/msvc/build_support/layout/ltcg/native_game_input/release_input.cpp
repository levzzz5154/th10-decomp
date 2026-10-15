#pragma code_seg(".text$a02cached")
void GameInputSystem::ReleaseInput() {
    GameDirectInput* input=direct_input;
    if (input) {
        input->vtable->Release(input);
        direct_input=0;
    }
}
#pragma code_seg()
