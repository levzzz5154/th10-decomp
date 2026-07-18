#include "th10/platform/file.hpp"
#include "th10/platform/path.hpp"
#include "th10/platform/memory_file.hpp"
#include "th10/archive/dat.hpp"
#include "th10/archive/resource_manager.hpp"
#include <cassert>

static void TestSharedWrite();
static void TestSharedRead();
static void TestPathDecode();
static void TestResourceChunkLookup();
static void TestBasenameSlotLookup();

extern "C" void* malloc(unsigned long size);
extern "C" void free(void* memory);

namespace {

struct MockFile {
    const unsigned char* bytes;
    DWORD size;
    DWORD position;
    bool open;
    bool short_read;
    DWORD close_count;
};

MockFile g_file = {};
const char* g_module_path = "C:\\games\\th10\\th10.exe";
DWORD g_free_count = 0;
DWORD g_free_resource_count = 0;
bool g_resource_available = true;
bool g_resource_lock_available = true;
static const unsigned char g_resource_bytes[] = {11, 22, 33, 44};

void ResetMock(const unsigned char* bytes, DWORD size) {
    g_file.bytes = bytes;
    g_file.size = size;
    g_file.position = 0;
    g_file.open = true;
    g_file.short_read = false;
    g_file.close_count = 0;
}

bool TestReadWholeRestoresPosition() {
    static const unsigned char bytes[] = {1, 2, 3, 4};
    ResetMock(bytes, sizeof(bytes));
    g_file.position = 2;

    FileHandle file;
    file.handle = (HANDLE)&g_file;
    file.access = 0x80000000;
    unsigned char* result = (unsigned char*)file.ReadWhole(sizeof(bytes));
    bool passed = result != 0 && g_file.position == 2;
    for (DWORD index = 0; passed && index < sizeof(bytes); ++index) {
        if (result[index] != bytes[index]) passed = false;
    }
    free(result);
    return passed;
}

bool TestReadWholeFailureLeavesReadPosition() {
    static const unsigned char bytes[] = {5, 6, 7, 8};
    ResetMock(bytes, sizeof(bytes));
    g_file.position = 1;
    g_file.short_read = true;

    FileHandle file;
    file.handle = (HANDLE)&g_file;
    file.access = 0x80000000;
    return file.ReadWhole(sizeof(bytes)) == 0 && g_file.position == sizeof(bytes);
}

bool TestReadWholeRejectsCapacityAndWriteHandle() {
    static const unsigned char bytes[] = {9, 10};
    ResetMock(bytes, sizeof(bytes));
    FileHandle file;
    file.handle = (HANDLE)&g_file;
    file.access = 0x80000000;
    if (file.ReadWhole(sizeof(bytes) - 1) != 0 || g_file.position != 0) {
        return false;
    }
    file.access = 0x40000000;
    return file.ReadWhole(sizeof(bytes)) == 0 && g_file.position == 0;
}

bool TestResourceFallbackOpenFailure() {
    g_file.close_count = 0;
    g_file.open = false;
    return Resource_LoadFile("missing.bin", 0) == 0 &&
        Resource_GetFileSize("missing.bin") == 0 &&
        g_file.close_count == 0;
}

bool EqualText(const char* left, const char* right) {
    while (*left == *right) {
        if (*left == 0) return true;
        ++left;
        ++right;
    }
    return false;
}

bool TestResolvePath() {
    char output[260];
    File_ResolvePath("data\\score.dat", output);
    if (!EqualText(output, "C:\\games\\th10\\data\\score.dat")) {
        return false;
    }
    File_ResolvePath("D:\\custom\\score.dat", output);
    if (!EqualText(output, "D:\\custom\\score.dat")) return false;

    g_module_path = "th10.exe";
    File_ResolvePath("score.dat", output);
    g_module_path = "C:\\games\\th10\\th10.exe";
    return EqualText(output, "score.dat");
}

bool TestResourceFileOwnership() {
    DWORD frees_before = g_free_count;
    DWORD resource_frees_before = g_free_resource_count;
    {
        ResourceFile file;
        if (file.Open("TEST", "r") != 1 ||
                file.GetSize() != sizeof(g_resource_bytes) ||
                file.Tell() != 0) {
            return false;
        }
        unsigned char output[sizeof(g_resource_bytes)] = {};
        if (file.Read(output, sizeof(output)) != sizeof(output)) return false;
        for (DWORD index = 0; index < sizeof(output); ++index) {
            if (output[index] != g_resource_bytes[index]) return false;
        }
    }
    if (g_free_count != frees_before + 1 ||
            g_free_resource_count != resource_frees_before + 1) {
        return false;
    }

    g_resource_available = false;
    ResourceFile missing;
    bool passed = missing.Open("MISSING", "r") == 1 &&
        missing.GetSize() == 0;
    g_resource_available = true;
    return passed;
}

bool TestResourcePalettePacking() {
    unsigned short palette[3] = {0, 0, 0};
    ResourceFile_FillPalette(palette, 3, 0xabcde0f0);
    return palette[0] == 0xcef && palette[1] == 0xcef && palette[2] == 0xcef;
}

bool TestResourceLockFailureReleasesHandle() {
    DWORD frees_before = g_free_resource_count;
    g_resource_lock_available = false;
    ResourceFile file;
    bool passed = file.Open("LOCK_FAIL", "r") == 1 &&
        g_free_resource_count == frees_before + 1;
    g_resource_lock_available = true;
    return passed;
}

bool TestMemoryFileTreeRemoval() {
    MemoryFileLink links[8] = {};

    // Sentinel 7 owns root 1. The predecessor of 1 is the rightmost node (5)
    // under its left branch; node 5 itself has a left child to reconnect.
    links[7].left = 1;
    links[1] = {7, 2, 3};
    links[2] = {1, 4, 5};
    links[3] = {1, 0, 0};
    links[4] = {2, 0, 0};
    links[5] = {2, 6, 0};
    links[6] = {5, 0, 0};

    if (MemoryFile_FindPredecessor(links, 1) != 5) return false;
    MemoryFile_RemoveNode(links, 1);

    return links[7].left == 5 && links[5].parent == 7 &&
        links[5].left == 2 && links[5].right == 3 &&
        links[2].parent == 5 && links[3].parent == 5 &&
        links[2].right == 6 && links[6].parent == 2 &&
        links[1].parent == 0;
}

} // namespace

extern "C" BOOL __stdcall CloseHandle(HANDLE handle) {
    MockFile* file = (MockFile*)handle;
    ++file->close_count;
    file->open = false;
    return 1;
}

extern "C" BOOL __stdcall ReadFile(
        HANDLE handle, void* buffer, DWORD size, DWORD* bytes_read, void*) {
    MockFile* file = (MockFile*)handle;
    DWORD available = file->size - file->position;
    DWORD count = size < available ? size : available;
    for (DWORD index = 0; index < count; ++index) {
        ((unsigned char*)buffer)[index] = file->bytes[file->position + index];
    }
    file->position += count;
    *bytes_read = file->short_read && count ? count - 1 : count;
    return 1;
}

extern "C" BOOL __stdcall WriteFile(
        HANDLE, const void*, DWORD, DWORD* bytes_written, void*) {
    *bytes_written = 0;
    return 0;
}

extern "C" DWORD __stdcall SetFilePointer(
        HANDLE handle, LONG distance, LONG*, DWORD origin) {
    MockFile* file = (MockFile*)handle;
    LONG base = origin == 0 ? 0 : origin == 1 ? (LONG)file->position :
        (LONG)file->size;
    file->position = (DWORD)(base + distance);
    return file->position;
}

extern "C" DWORD __stdcall GetFileSize(HANDLE handle, DWORD*) {
    return ((MockFile*)handle)->size;
}

extern "C" HANDLE __stdcall CreateFileA(
        const char*, DWORD, DWORD, void*, DWORD, DWORD, HANDLE) {
    return (HANDLE)-1;
}

extern "C" BOOL __stdcall DeleteFileA(const char*) { return 1; }

extern "C" DWORD __stdcall GetModuleFileNameA(HANDLE, char* output, DWORD) {
    DWORD length = 0;
    do {
        output[length] = g_module_path[length];
    } while (g_module_path[length++] != 0);
    return length - 1;
}

extern "C" void* __cdecl _malloc(DWORD size) { return malloc(size); }
extern "C" void __cdecl _free(void* memory) {
    if (memory) ++g_free_count;
    free(memory);
}
extern "C" void* __stdcall SelectObject(void* dc, void* object) {
    return dc != 0 ? object : 0;
}
extern "C" int __stdcall DeleteDC(void*) { return 1; }
extern "C" int __stdcall DeleteObject(void*) { return 1; }

extern "C" HANDLE __stdcall FindResourceA(
        HANDLE, const char*, const char*) {
    return g_resource_available ? (HANDLE)1 : 0;
}
extern "C" HANDLE __stdcall LoadResource(HANDLE, HANDLE resource) {
    return resource;
}
extern "C" void* __stdcall LockResource(HANDLE resource) {
    return resource && g_resource_lock_available ? (void*)g_resource_bytes : 0;
}
extern "C" DWORD __stdcall SizeofResource(HANDLE, HANDLE) {
    return sizeof(g_resource_bytes);
}
extern "C" BOOL __stdcall FreeResource(HANDLE) {
    ++g_free_resource_count;
    return 1;
}

void DatArchive_Initialize(DatArchive*) {}
void DatArchive_Close(DatArchive*) {}
bool DatArchive_OpenFile(DatArchive*, const char*) { return false; }
uint8_t* DatArchive_Read(DatArchive*, const char*, uint8_t*) { return 0; }
uint32_t DatArchive_FindSize(const DatArchiveIndex*, const char*) { return 0; }

static int probeCloses;
static void* ProbeOpen(const char* path) {
    return path[0] == '!' ? (void*)-1 : (void*)0x1234;
}
static void ProbeClose(void*) { ++probeCloses; }

int main() {
    TestSharedWrite();
    TestSharedRead();
    TestPathDecode();
    TestResourceChunkLookup();
    TestBasenameSlotLookup();
    probeCloses = 0;
    if (!File_ProbeExists("ok", ProbeOpen, ProbeClose) ||
            File_ProbeExists("!missing", ProbeOpen, ProbeClose) ||
            probeCloses != 1) return 10;
    unsigned char probeDepth = 2;
    File_CloseProbeHandle((void*)0x1234, ProbeClose, &probeDepth);
    assert(probeCloses == 2 && probeDepth == 1);
    File_CloseProbeHandle((void*)-1, ProbeClose, &probeDepth);
    assert(probeCloses == 2 && probeDepth == 1);
    if (!TestReadWholeRestoresPosition()) return 1;
    if (!TestReadWholeFailureLeavesReadPosition()) return 2;
    if (!TestReadWholeRejectsCapacityAndWriteHandle()) return 3;
    if (!TestResourceFallbackOpenFailure()) return 4;
    if (!TestResolvePath()) return 5;
    if (!TestResourceFileOwnership()) return 6;
    if (!TestResourcePalettePacking()) return 7;
    if (!TestResourceLockFailureReleasesHandle()) return 8;
    if (!TestMemoryFileTreeRemoval()) return 9;
    return 0;
}
#include "th10/platform/file.hpp"

static DWORD g_written;
static int g_closed;
static DWORD TestWrite(void*, const void*, DWORD size) { return g_written ? g_written : size; }
static void TestClose(void*) { ++g_closed; }

static void TestSharedWrite() {
    unsigned char depth = 2;
    g_written = 0; g_closed = 0;
    assert(File_WriteShared((void*)1, "x", 4, TestWrite, TestClose, &depth) == 0);
    assert(g_closed == 0 && depth == 2);
    g_written = 2;
    assert(File_WriteShared((void*)1, "x", 4, TestWrite, TestClose, &depth) == -2);
    assert(g_closed == 1 && depth == 1);
}

static void* TestAllocate(DWORD size) {
    static unsigned char storage[32];
    return size <= sizeof(storage) ? storage : 0;
}
static DWORD TestRead(void*, void* destination, DWORD size) {
    ((unsigned char*)destination)[0] = 0x5a;
    return size;
}
static void TestSharedRead() {
    g_closed = 0;
    void* result = File_ReadShared((void*)1, 4, TestAllocate, TestRead, TestClose);
    assert(result != 0 && ((unsigned char*)result)[0] == 0x5a && g_closed == 0);
    result = File_ReadShared((void*)1, 64, TestAllocate, TestRead, TestClose);
    assert(result == 0 && g_closed == 1);
    assert(File_ReadShared((void*)-1, 4, TestAllocate, TestRead, TestClose) == 0);
}

static void TestPathDecode() {
    const unsigned char encoded[] = { (unsigned char)('o' ^ 0x77),
        (unsigned char)('k' ^ (0x77 + 7)), (unsigned char)(0x77 + 7 + 0x17) };
    char decoded[8] = {};
    assert(Path_DecodeXor(encoded, decoded) == decoded);
    assert(decoded[0] == 'o' && decoded[1] == 'k' && decoded[2] == 0);
}

static void TestResourceChunkLookup() {
    const unsigned char data[] = {
        'A','B','C','D', 2,0,0,0, 9,8,
        'T','E','S','T', 3,0,0,0, 1,2,3 };
    unsigned int size = 0;
    const unsigned char* payload = Resource_FindChunk(data, sizeof(data), "TEST", &size);
    assert(payload == data + 18 && size == 3 && payload[0] == 1);
    assert(Resource_FindChunk(data, sizeof(data), "NONE", &size) == 0 && size == 0);
}

static void TestBasenameSlotLookup() {
    const char table[] = "zero\0           one\0";
    assert(Path_FindBasenameSlot("dir/zero", table, 2, 16) == 0);
    assert(Path_FindBasenameSlot("x\\one", table, 2, 16) == 1);
    assert(Path_FindBasenameSlot("missing", table, 2, 16) == 0);
}
