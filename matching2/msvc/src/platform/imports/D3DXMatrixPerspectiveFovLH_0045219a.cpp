typedef void* (__stdcall* D3DXMatrixPerspectiveFovLHFn_0045219a)(
    void* out, float fov_y, float aspect, float z_near, float z_far);
extern "C" D3DXMatrixPerspectiveFovLHFn_0045219a data_004662e8;

// 0x0045219A..0x0045219F: imported D3DXMatrixPerspectiveFovLH tail thunk.
extern "C" void* __stdcall asm_D3DXMatrixPerspectiveFovLH_0045219a(
    void* out, float fov_y, float aspect, float z_near, float z_far) {
    return data_004662e8(out, fov_y, aspect, z_near, z_far);
}
