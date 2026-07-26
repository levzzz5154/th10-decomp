#include "th10/archive/lzss.hpp"
#include "th10/archive/crypt.hpp"
#include "th10/archive/dat.hpp"
#include "th10/archive/resource_manager.hpp"
#include "th10/platform/file.hpp"
#include "th10/platform/memory_file.hpp"
#include "th10/render/resource_manager.hpp"
#include "th10/render/device_reset.hpp"
#include "th10/render/game_render_targets.hpp"
#include "th10/util/heap.hpp"
#include "th10/util/runtime_pool.hpp"

// Keep this harness free of host standard-library headers: the game headers
// intentionally model MSVC 7.1's 32-bit fundamental typedefs.
extern "C" void* malloc(unsigned long size);

static int g_prepare_result;
static int g_draw_calls;
static int TestPrepareRender() { return g_prepare_result; }
static int TestDrawRender(void*, int flags) {
    ++g_draw_calls;
    return flags == 0 ? 27 : -2;
}
static bool TestPrepareAndDraw() {
    g_prepare_result = 1;
    g_draw_calls = 0;
    if (Render_PrepareAndDraw((void*)1, TestPrepareRender, TestDrawRender) != -1 ||
        g_draw_calls != 0) return false;
    g_prepare_result = 0;
    return Render_PrepareAndDraw((void*)1, TestPrepareRender, TestDrawRender) == 27 &&
        g_draw_calls == 1;
}
static bool TestRenderScaleReset() {
    float factors[4] = {2.0f, -1.0f, 0.0f, 9.0f};
    Render_ResetScaleFactors(factors);
    return factors[0] == 1.0f && factors[1] == 1.0f &&
        factors[2] == 1.0f && factors[3] == 1.0f;
}
static int g_owned_cleanup;
static int g_owned_free;
static void OwnedCleanup(void*) { ++g_owned_cleanup; }
static void OwnedFree(void*) { ++g_owned_free; }
static bool TestOwnedDestroy() {
    g_owned_cleanup = g_owned_free = 0;
    Heap_DestroyOwned(0, OwnedCleanup, OwnedFree);
    if (g_owned_cleanup != 0 || g_owned_free != 0) return false;
    Heap_DestroyOwned((void*)1, OwnedCleanup, OwnedFree);
    return g_owned_cleanup == 1 && g_owned_free == 1;
}
static bool TestSecondaryOwnedDestroy() {
    g_owned_cleanup = g_owned_free = 0;
    Heap_DestroyOwnedSecondary((void*)1, OwnedCleanup, OwnedFree);
    return g_owned_cleanup == 1 && g_owned_free == 1;
}
extern "C" void free(void* memory);

extern "C" void* _malloc(uint32_t size) {
    return malloc((unsigned long)size);
}

extern "C" void _free(void* memory) {
    free(memory);
}

extern "C" void* _memmove(void* destination, const void* source, uint32_t size) {
    uint8_t* output = (uint8_t*)destination;
    const uint8_t* input = (const uint8_t*)source;
    if (output < input) {
        for (uint32_t index = 0; index < size; ++index) output[index] = input[index];
    } else if (output > input) {
        while (size != 0) {
            --size;
            output[size] = input[size];
        }
    }
    return destination;
}

extern "C" int _stricmp(const char* left, const char* right) {
    for (;;) {
        char a = *left++;
        char b = *right++;
        if (a >= 'A' && a <= 'Z') a = (char)(a + ('a' - 'A'));
        if (b >= 'A' && b <= 'Z') b = (char)(b + ('a' - 'A'));
        if (a != b || a == 0) return (int)(uint8_t)a - (int)(uint8_t)b;
    }
}

extern "C" void LegacyString_ThrowLengthError(void) {}
extern "C" void LegacyString_ThrowRangeError(void) {}
extern "C" void* operator_new(uint32_t size) { return _malloc(size); }

uint32_t DAT_00492274 = 0;
uint8_t DAT_0049231c = 0;
static uint32_t g_enter_count = 0;
static uint32_t g_leave_count = 0;
static uint32_t g_resource_release_count = 0;
static uint32_t g_worker_stop_count = 0;

extern "C" void EnterCriticalSection(void*) { ++g_enter_count; }
extern "C" void LeaveCriticalSection(void*) { ++g_leave_count; }

void D3DResource_Release(void*, void*) { ++g_resource_release_count; }
void D3DResourceWorker_Stop(void) { ++g_worker_stop_count; }

// GameRender_ReleaseCaptureTarget / GameRender_ReleasePrimaryTarget used to
// be replaced here by counting spies. src/render/game_render_targets.cpp now
// carries the real recovered definitions and this test links that TU for
// GameRenderTargets_Initialize/Release, so link-time substitution collides.
// The forwarding checks (which handle and args reached each helper) cannot be
// expressed without substitution; what remains observable is the handle
// clearing that GameRenderTargets_Release performs itself.

void* g_pD3DDevice = (void*)1;
extern "C" void* __stdcall SelectObject(void* dc, void* object) {
    return dc != 0 ? object : 0;
}
extern "C" int __stdcall DeleteDC(void*) { return 1; }
extern "C" int __stdcall DeleteObject(void*) { return 1; }
void* g_pGameStateManager = 0;
uint32_t DAT_00474e36 = 0;
uint32_t DAT_00491fd4 = 0;
static int g_device_test_result = 0;
static uint32_t g_device_reset_count = 0;
static uint32_t g_entity_reset_count = 0;
static uint32_t g_render_reinitialize_count = 0;
static uint32_t g_directory_create_count = 0;
static uint32_t g_file_exists_count = 0;
static uint32_t g_screenshot_count = 0;
static char g_screenshot_path[32] = {0};

int D3DDevice_TestCooperativeLevel(void*) { return g_device_test_result; }
int D3DDevice_Reset(void*) { ++g_device_reset_count; return 0; }
void GameStateManager_DestroyEntitiesForReset(void*) { ++g_entity_reset_count; }
void Render_ReinitializeAfterReset(void) { ++g_render_reinitialize_count; }
void Directory_Create(const char*) { ++g_directory_create_count; }
int File_Exists(const char*) { return g_file_exists_count++ < 2; }
void Screenshot_Capture(const char* path) {
    ++g_screenshot_count;
    uint32_t index = 0;
    do {
        g_screenshot_path[index] = path[index];
    } while (path[index++] != 0);
}

uint8_t* Resource_LoadFile(const char*, uint8_t*) { return 0; }
uint32_t Resource_GetFileSize(const char*) { return 0; }

class TestBufferFile : public BufferFile {
public:
    bool SetData(const uint8_t* source, DWORD size) {
        Close();
        data_ = (BYTE*)_malloc(size);
        if (!data_) return false;
        for (DWORD index = 0; index < size; ++index) {
            data_[index] = source[index];
        }
        size_ = size;
        position_ = data_;
        return true;
    }
};

class BitWriter {
public:
    BitWriter() : size_(0), bit_(0) {}

    void Bit(bool set) {
        if (bit_ == 0) {
            bytes_[size_++] = 0;
        }
        if (set) {
            bytes_[size_ - 1] |= (uint8_t)(0x80 >> bit_);
        }
        bit_ = (bit_ + 1) & 7;
    }

    void Bits(uint32_t value, uint32_t mask) {
        while (mask != 0) {
            Bit((value & mask) != 0);
            mask >>= 1;
        }
    }

    void Literal(uint8_t value) {
        Bit(true);
        Bits(value, 0x80);
    }

    void BackReference(uint32_t offset, uint32_t length_code) {
        Bit(false);
        Bits(offset, 0x1000);
        Bits(length_code, 8);
    }

    void End() {
        Bit(false);
        Bits(0, 0x1000);
    }

    const uint8_t* Bytes() const { return bytes_; }
    int32_t Size() const { return size_; }

private:
    uint8_t bytes_[64];
    int32_t size_;
    uint32_t bit_;
};

static bool Equal(const uint8_t* left, const char* right, uint32_t size) {
    for (uint32_t index = 0; index < size; ++index) {
        if (left[index] != (uint8_t)right[index]) {
            return false;
        }
    }
    return true;
}

static bool TestPathComponentHelper() {
    const char* nested = "dir/sub/file.anm";
    const char* plain = "file.anm";
    char archive_path[260];
    Resource_ArchivePathForAsset(nested, archive_path);
    return File_AfterFirstSlash(nested) == nested + 4 &&
        File_AfterFirstSlash(plain) == plain &&
        archive_path[0] == 'd' && archive_path[1] == 'i' &&
        archive_path[2] == 'r' && archive_path[3] == '.' &&
        archive_path[4] == 'd' && archive_path[5] == 'a' &&
        archive_path[6] == 't' && archive_path[7] == 0;
}

static bool TestBufferFileMethods() {
    const uint8_t source[5] = {1, 2, 3, 4, 5};
    uint8_t output[5] = {0};
    TestBufferFile file;
    if (!file.SetData(source, sizeof(source)) ||
            file.GetSize() != sizeof(source) || file.Tell() != 0) {
        return false;
    }
    if (file.Read(output, 3) != 3 || file.Tell() != 3 ||
            file.Read(output + 3, 4) != 2 || file.Tell() != 5) {
        return false;
    }
    for (uint32_t index = 0; index < sizeof(source); ++index) {
        if (output[index] != source[index]) return false;
    }
    return file.Seek(0, 0) && file.Tell() == 0 &&
        file.Seek(4, 0) && file.Tell() == 4 &&
        !file.Seek(5, 0) && file.Seek(0, 2) && file.Tell() == 5 &&
        file.Seek(-2, 1) && file.Tell() == 3 &&
        file.Write(output, sizeof(output)) == 0;
}

static bool TestLegacyStringAssignment() {
    LegacyString string = {};
    string.capacity = 15;
    string.Assign("mountain");
    if (string.length != 8 || string.capacity != 15) return false;
    const char* expected = "mountain";
    for (uint32_t index = 0; index <= string.length; ++index) {
        if (string.storage.inline_data[index] != expected[index]) return false;
    }
    string.AssignRange("faith", 5);
    if (string.length != 5 || string.storage.inline_data[5] != 0 ||
            string.storage.inline_data[0] != 'f' ||
            string.storage.inline_data[4] != 'h') {
        return false;
    }

    LegacyString source = {};
    source.capacity = 15;
    source.Assign("outside");
    string.AssignSubstring(&source, 1, 3);
    if (string.length != 3 || string.storage.inline_data[0] != 'u' ||
            string.storage.inline_data[1] != 't' ||
            string.storage.inline_data[2] != 's' ||
            string.storage.inline_data[3] != 0) {
        return false;
    }

    string.Assign("abcdefghijklmnopqrst");
    if (string.length != 20 || string.capacity != 31 ||
            string.Data()[19] != 't' || string.Data()[20] != 0) {
        return false;
    }
    string.Erase(5, 10);
    const char* erased = "abcdepqrst";
    for (uint32_t index = 0; index <= 10; ++index) {
        if (string.Data()[index] != erased[index]) return false;
    }
    const char* owned = string.Data();
    if (!string.OwnsPointer(owned) ||
            !string.OwnsPointer(owned + string.Length() - 1) ||
            string.OwnsPointer(owned + string.Length()) ||
            string.OwnsPointer("external")) {
        return false;
    }
    string.AssignSubstring(&string, 2, 4);
    const char* substring = "cdep";
    bool passed = string.length == 4 && string.Data()[4] == 0;
    for (uint32_t index = 0; passed && index < 4; ++index) {
        if (string.Data()[index] != substring[index]) passed = false;
    }
    if (!string.Reserve(40, false) || string.capacity < 40 ||
            string.length != 4 || !string.Reserve(8, true) ||
            string.capacity != 15 || string.length != 4) {
        passed = false;
    }
    for (uint32_t index = 0; passed && index < 4; ++index) {
        if (string.Data()[index] != substring[index]) passed = false;
    }
    LegacyString_Clear(&string);
    return passed && string.length == 0 && string.capacity == 15 &&
        string.storage.inline_data[0] == 0;
}

static bool TestRuntimeOwners() {
    RuntimeAllocationPool pool;
    pool.allocations[0] = 1;
    pool.allocations[0x27FF] = 2;
    pool.has_allocations = 3;
    RuntimeAllocationPool_Initialize(0, &pool);
    if (pool.allocations[0] != 0 || pool.allocations[0x27FF] != 0 ||
            pool.has_allocations != 0) {
        return false;
    }
    pool.has_allocations = 1;
    RuntimeAllocationPool_ReleaseAll(&pool);
    if (pool.has_allocations != 0) return false;

    D3DResourceManager manager = {};
    manager.primary.flags = 0xFFFFFFFF;
    manager.secondary.flags = 0xFFFFFFFF;
    manager.primary.pending_008 = 1;
    manager.secondary.pending_010 = 1;
    D3DResourceManager_Initialize(&manager);
    if (manager.primary.owner != &manager.primary ||
            manager.secondary.owner != &manager.secondary ||
            manager.primary.flags != 0xFFFFFFFE ||
            manager.secondary.flags != 0xFFFFFFFE ||
            manager.primary.pending_008 != 0 ||
            manager.secondary.pending_010 != 0) {
        return false;
    }

    D3DResourceNode tail = {(void*)2, 0};
    D3DResourceNode skipped = {0, &tail};
    D3DResourceNode head = {(void*)1, &skipped};
    manager.primary.first = &head;
    D3DResourceManager_Destroy(&manager);
    return g_worker_stop_count == 1 && g_resource_release_count == 2 &&
        g_enter_count == 2 && g_leave_count == 2 && DAT_0049231c == 0 &&
        manager.primary.pending_008 == 0 &&
        manager.primary.pending_00C == 0 &&
        manager.primary.pending_010 == 0;
}

static bool TestGameRenderTargets() {
    GameRenderTargets targets;
    targets.primary_handle = 4;
    targets.capture_handle = 5;
    targets.capture_args[0] = 1;
    targets.primary_args[7] = 2;
    GameRenderTargets_Initialize(&targets);
    if (targets.primary_handle != -1 || targets.capture_handle != -1) {
        return false;
    }
    for (uint32_t index = 0; index < 9; ++index) {
        if (targets.capture_args[index] != 0) return false;
    }
    for (uint32_t index = 0; index < 8; ++index) {
        if (targets.primary_args[index] != 0) return false;
    }

    targets.capture_handle = 7;
    targets.primary_handle = 9;
    targets.capture_args[0] = 11;
    targets.primary_args[0] = 13;
    GameRenderTargets_Release(&targets);
    if (targets.capture_handle != -1 || targets.primary_handle != -1) {
        return false;
    }
    // A second release must be idempotent: the handles are already -1, so
    // the helpers take their early-out and nothing changes.
    GameRenderTargets_Release(&targets);
    return targets.capture_handle == -1 && targets.primary_handle == -1;
}

static bool TestDeviceResetAndSnapshot() {
    GameRenderTargets targets = {};
    targets.primary_handle = 3;
    targets.capture_handle = 4;
    g_pGameStateManager = &targets;
    g_device_test_result = -1;
    DAT_00474e36 = 0x800;
    Render_HandleDeviceResetAndSnapshot();
    const char* expected = "snapshot/th002.bmp";
    for (uint32_t index = 0;; ++index) {
        if (g_screenshot_path[index] != expected[index]) return false;
        if (expected[index] == 0) break;
    }
    return g_device_reset_count == 1 && g_entity_reset_count == 1 &&
        g_render_reinitialize_count == 1 && DAT_00491fd4 == 2 &&
        g_directory_create_count == 1 && g_file_exists_count == 3 &&
        g_screenshot_count == 1 &&
        targets.primary_handle == -1 && targets.capture_handle == -1;
}

static bool TestLiteralsAndAllocation() {
    BitWriter encoded;
    encoded.Literal('H');
    encoded.Literal('E');
    encoded.Literal('L');
    encoded.Literal('L');
    encoded.Literal('O');
    encoded.End();

    uint8_t* decoded = Dat_LzssDecompress(
        encoded.Bytes(), encoded.Size(), 0, 5);
    bool passed = decoded != 0 && Equal(decoded, "HELLO", 5);
    free(decoded);
    return passed;
}

static bool TestOverlappingBackReference() {
    BitWriter encoded;
    encoded.Literal('A');
    encoded.Literal('B');
    encoded.BackReference(1, 1); // four bytes copied from dictionary offset 1
    encoded.End();

    uint8_t decoded[6] = {0};
    uint8_t* result = Dat_LzssDecompress(
        encoded.Bytes(), encoded.Size(), decoded, sizeof(decoded));
    return result == decoded && Equal(decoded, "ABABAB", sizeof(decoded));
}

static bool TestCompressionRoundTrip() {
    static const uint8_t input[6] = {'A', 'B', 'A', 'B', 'A', 'B'};
    int32_t compressed_size = 0;
    uint8_t* compressed = Dat_LzssCompress(
        input, sizeof(input), &compressed_size);
    if (!compressed) return false;

    BitWriter expected;
    expected.Literal('A');
    expected.Literal('B');
    expected.BackReference(1, 1);
    expected.End();
    bool passed = compressed_size == expected.Size();
    for (int32_t index = 0; passed && index < compressed_size; ++index) {
        if (compressed[index] != expected.Bytes()[index]) passed = false;
    }

    uint8_t decoded[sizeof(input)] = {0};
    if (passed) {
        passed = Dat_LzssDecompress(
            compressed,
            compressed_size,
            decoded,
            sizeof(decoded)) == decoded;
    }
    for (uint32_t index = 0; passed && index < sizeof(input); ++index) {
        if (decoded[index] != input[index]) passed = false;
    }
    free(compressed);
    return passed;
}

static bool TestRetailArchiveHeader() {
    uint8_t header[16] = {
        0x13, 0x55, 0xB3, 0xB0, 0xF0, 0xF4, 0x54, 0xD4,
        0xCB, 0xD4, 0x9F, 0x77, 0xF4, 0x8B, 0x5C, 0x00,
    };
    DatArchiveHeader decoded;
    return DatArchive_DecodeHeader(header, &decoded) &&
        decoded.magic == 0x31414854 &&
        decoded.entry_list_size == 3416 &&
        decoded.entry_list_compressed_size == 1886 &&
        decoded.entry_count == 138;
}

static bool TestRetailCryptParameterTable() {
    static const DatCryptParams expected[8] = {
        {0x1B, 0x37, 0x0040, 0x2800},
        {0x51, 0xE9, 0x0040, 0x3000},
        {0xC1, 0x51, 0x0080, 0x3200},
        {0x03, 0x19, 0x0400, 0x7800},
        {0xAB, 0xCD, 0x0200, 0x2800},
        {0x12, 0x34, 0x0080, 0x3200},
        {0x35, 0x97, 0x0080, 0x2800},
        {0x99, 0x37, 0x0400, 0x2000},
    };
    for (uint32_t index = 0; index < 8; ++index) {
        if (g_dat_crypt_params[index].key != expected[index].key ||
            g_dat_crypt_params[index].step != expected[index].step ||
            g_dat_crypt_params[index].block_size != expected[index].block_size ||
            g_dat_crypt_params[index].byte_limit != expected[index].byte_limit) {
            return false;
        }
    }
    return Dat_GetCryptParamIndex("a") == ('a' & 7) &&
        Dat_GetCryptParams("a") ==
            &g_dat_crypt_params[Dat_GetCryptParamIndex("a")];
}

static bool TestRetailCryptLeaves() {
    uint8_t decoded[6] = {10, 20, 30, 40, 50, 60};
    Dat_Decrypt(decoded, sizeof(decoded), 0x10, 1, 4, sizeof(decoded));
    const uint8_t expected[6] = {0x3B, 0x05, 0x0C, 0x1A, 0x29, 0x26};
    for (uint32_t index = 0; index < sizeof(decoded); ++index) {
        if (decoded[index] != expected[index]) return false;
    }
    Dat_Encrypt(decoded, sizeof(decoded), 0x10, 1, 4, sizeof(decoded));
    for (uint32_t index = 0; index < sizeof(decoded); ++index) {
        if (decoded[index] != (uint8_t)((index + 1) * 10)) return false;
    }

    uint8_t parity_edge[69];
    for (uint32_t index = 0; index < sizeof(parity_edge); ++index)
        parity_edge[index] = (uint8_t)index;
    Dat_Decrypt(parity_edge, sizeof(parity_edge), 0, 0, 64,
                sizeof(parity_edge));
    if (parity_edge[62] != 0 || parity_edge[63] != 63 ||
        parity_edge[68] != 68) return false;

    uint8_t round_trip[0x123];
    uint8_t original[sizeof(round_trip)];
    for (uint32_t index = 0; index < sizeof(round_trip); ++index) {
        round_trip[index] = (uint8_t)(index * 13 + 7);
        original[index] = round_trip[index];
    }
    Dat_Encrypt(round_trip, sizeof(round_trip), 0x3D, 0x7A, 0x80, 0x400);
    Dat_Encrypt(round_trip, sizeof(round_trip), 0xAA, 0xE1, 0x400, 0x1000);
    Dat_Decrypt(round_trip, sizeof(round_trip), 0xAA, 0xE1, 0x400, 0x1000);
    Dat_Decrypt(round_trip, sizeof(round_trip), 0x3D, 0x7A, 0x80, 0x400);
    for (uint32_t index = 0; index < sizeof(round_trip); ++index) {
        if (round_trip[index] != original[index]) return false;
    }
    return true;
}

static void EncryptBlockForTest(
        const uint8_t* plain,
        uint8_t* encrypted,
        uint32_t size,
        uint8_t key,
        uint8_t step) {
    uint32_t source = 0;
    for (int32_t destination = (int32_t)size - 1;
            destination >= 0; destination -= 2) {
        encrypted[source++] = plain[destination] ^ key;
        key = (uint8_t)(key + step);
    }
    for (int32_t destination = (int32_t)size - 2;
            destination >= 0; destination -= 2) {
        encrypted[source++] = plain[destination] ^ key;
        key = (uint8_t)(key + step);
    }
}

class MemoryFile : public FileInterface {
public:
    MemoryFile(uint8_t* data, uint32_t size)
        : data_(data), size_(size), position_(0) {}

    virtual BYTE Open(const char*, const char*) {
        position_ = 0;
        return 1;
    }
    virtual void Close() {}
    virtual DWORD Read(void* destination, DWORD size) {
        if (position_ + size > size_) return 0;
        uint8_t* output = (uint8_t*)destination;
        for (DWORD index = 0; index < size; ++index) {
            output[index] = data_[position_ + index];
        }
        position_ += size;
        return size;
    }
    virtual BYTE Write(const void*, DWORD) { return 0; }
    virtual DWORD Tell() const { return position_; }
    virtual DWORD GetSize() const { return size_; }
    virtual BYTE Seek(LONG distance, DWORD origin) {
        if (origin != 0 || distance < 0 || (DWORD)distance > size_) return 0;
        position_ = (DWORD)distance;
        return 1;
    }
private:
    uint8_t* data_;
    DWORD size_;
    DWORD position_;
};

static bool TestEntryDataDecode() {
    uint8_t plain[64];
    uint8_t encrypted[64];
    uint8_t decoded[64] = {0};
    for (uint32_t index = 0; index < sizeof(plain); ++index) {
        plain[index] = (uint8_t)(index * 3 + 1);
    }
    const char* name = "a";
    const DatCryptParams* params = Dat_GetCryptParams(name);
    EncryptBlockForTest(
        plain, encrypted, sizeof(encrypted), params->key, params->step);

    DatEntry entries[2] = {
        {name, 0x20, sizeof(plain), 0},
        {0, 0x60, 0, 0},
    };
    uint8_t* result = DatArchive_DecodeEntryData(entries, encrypted, decoded);
    if (result != decoded ||
            DatEntry_GetCompressedSize(entries) != sizeof(plain)) {
        return false;
    }
    for (uint32_t index = 0; index < sizeof(plain); ++index) {
        if (decoded[index] != plain[index]) {
            return false;
        }
    }
    return true;
}

static bool TestArchiveEntryRead() {
    uint8_t plain[64];
    uint8_t file_data[96] = {0};
    uint8_t decoded[64] = {0};
    for (uint32_t index = 0; index < sizeof(plain); ++index) {
        plain[index] = (uint8_t)(0xA5 ^ index);
    }

    const char* name = "a";
    const DatCryptParams* params = Dat_GetCryptParams(name);
    EncryptBlockForTest(
        plain,
        file_data + 32,
        sizeof(plain),
        params->key,
        params->step);

    DatEntry entries[2] = {
        {name, 32, sizeof(plain), 0},
        {0, sizeof(file_data), 0, 0},
    };
    MemoryFile file(file_data, sizeof(file_data));
    DatArchive archive;
    DatArchive_Initialize(&archive);
    archive.entries = entries;
    archive.entry_count = 1;
    archive.file = &file;

    if (DatArchive_Read(&archive, "A", decoded) != decoded ||
            file.Tell() != sizeof(file_data)) {
        return false;
    }
    for (uint32_t index = 0; index < sizeof(plain); ++index) {
        if (decoded[index] != plain[index]) return false;
    }
    return true;
}

static void WriteU32(uint8_t* destination, uint32_t value) {
    destination[0] = (uint8_t)value;
    destination[1] = (uint8_t)(value >> 8);
    destination[2] = (uint8_t)(value >> 16);
    destination[3] = (uint8_t)(value >> 24);
}

static bool TestArchiveOpenAndRead() {
    uint8_t packed_entry[16] = {0};
    packed_entry[0] = 'a';
    WriteU32(packed_entry + 4, 16);
    WriteU32(packed_entry + 8, 64);

    BitWriter encoded_table;
    for (uint32_t index = 0; index < sizeof(packed_entry); ++index) {
        encoded_table.Literal(packed_entry[index]);
    }
    encoded_table.End();

    uint8_t file_data[128] = {0};
    uint8_t decoded[64] = {0};
    uint8_t asset[64];
    for (uint32_t index = 0; index < sizeof(asset); ++index) {
        asset[index] = (uint8_t)(index + 0x31);
    }

    const DatCryptParams* asset_params = Dat_GetCryptParams("a");
    EncryptBlockForTest(
        asset,
        file_data + 16,
        sizeof(asset),
        asset_params->key,
        asset_params->step);

    uint32_t table_offset = 80;
    uint32_t table_compressed_size = (uint32_t)encoded_table.Size();
    // The retail cipher deliberately leaves a trailing fragment smaller than
    // one quarter of its 0x80-byte block untouched.
    for (uint32_t index = 0; index < table_compressed_size; ++index) {
        file_data[table_offset + index] = encoded_table.Bytes()[index];
    }

    uint8_t header[16];
    WriteU32(header, 0x31414854);
    WriteU32(header + 4, 123456789 + sizeof(packed_entry));
    WriteU32(header + 8, 987654321 + table_compressed_size);
    WriteU32(header + 12, 135792468 + 1);
    EncryptBlockForTest(header, file_data, sizeof(header), 0x1B, 0x37);

    MemoryFile* file = new MemoryFile(
        file_data, table_offset + table_compressed_size);
    DatArchive archive;
    DatArchive_Initialize(&archive);
    if (!DatArchive_Open(&archive, file, "synthetic.dat")) {
        return false;
    }
    bool passed = archive.entry_count == 1 && archive.entries != 0 &&
        archive.entries[0].offset == 16 &&
        archive.entries[0].uncompressed_size == sizeof(asset) &&
        archive.entries[1].offset == table_offset &&
        DatArchive_Read(&archive, "A", decoded) == decoded;
    for (uint32_t index = 0; passed && index < sizeof(asset); ++index) {
        if (decoded[index] != asset[index]) passed = false;
    }
    DatArchive_Close(&archive);
    return passed && archive.entries == 0 && archive.filename == 0 &&
        archive.file == 0 && archive.entry_count == 0;
}

static bool TestArchiveIndexLoaderRejectsBadHeader() {
    uint8_t file_data[16] = {0};
    MemoryFile file(file_data, sizeof(file_data));
    DatArchive archive;
    DatArchive_Initialize(&archive);
    archive.file = &file;

    bool passed = !DatArchive_LoadIndex(&archive, "invalid.dat") &&
        archive.entries == 0 && archive.entry_count == 0 &&
        archive.file == &file;
    archive.file = 0;
    return passed;
}

static bool TestPackedEntryTable() {
    uint8_t packed[36] = {0};
    packed[0] = 'a'; packed[1] = '.'; packed[2] = 't'; packed[3] = 'x';
    packed[4] = 't';
    WriteU32(packed + 8, 0x20);
    WriteU32(packed + 12, 3);
    WriteU32(packed + 16, 7);
    packed[20] = 'b';
    WriteU32(packed + 24, 0x30);
    WriteU32(packed + 28, 4);
    WriteU32(packed + 32, 8);

    DatEntry* entries = DatArchive_ParseEntries(packed, 2, 0x40);
    if (!entries) return false;
    DatArchiveIndex archive = {entries, 2};
    const DatEntry* found = DatArchive_FindEntry(&archive, "A.TXT");
    bool passed = found == entries && found->offset == 0x20 &&
        found->uncompressed_size == 3 && found->reserved_metadata == 7 &&
        entries[1].offset == 0x30 && entries[2].offset == 0x40 &&
        DatArchive_FindSize(&archive, "B") == 4 &&
        DatArchive_FindSize(&archive, "missing") == 0 &&
        DatArchive_FindEntry(&archive, "missing") == 0;
    DatArchive_FreeEntries(entries, 2);
    return passed;
}

int main() {
    if (!TestPrepareAndDraw()) return 17;
    if (!TestRenderScaleReset()) return 18;
    if (!TestOwnedDestroy()) return 19;
    if (!TestSecondaryOwnedDestroy()) return 20;
    if (!TestPathComponentHelper()) {
        return 1;
    }
    if (!TestBufferFileMethods()) {
        return 2;
    }
    if (!TestLiteralsAndAllocation()) {
        return 3;
    }
    if (!TestOverlappingBackReference()) {
        return 4;
    }
    if (!TestCompressionRoundTrip()) {
        return 5;
    }
    if (!TestRetailArchiveHeader()) {
        return 6;
    }
    if (!TestRetailCryptParameterTable()) {
        return 7;
    }
    if (!TestRetailCryptLeaves()) {
        return 21;
    }
    if (!TestEntryDataDecode()) {
        return 8;
    }
    if (!TestArchiveEntryRead()) {
        return 9;
    }
    if (!TestArchiveOpenAndRead()) {
        return 10;
    }
    if (!TestPackedEntryTable()) {
        return 11;
    }
    if (!TestArchiveIndexLoaderRejectsBadHeader()) {
        return 16;
    }
    if (!TestLegacyStringAssignment()) {
        return 12;
    }
    if (!TestRuntimeOwners()) {
        return 13;
    }
    if (!TestGameRenderTargets()) {
        return 14;
    }
    if (!TestDeviceResetAndSnapshot()) {
        return 15;
    }
    return 0;
}
