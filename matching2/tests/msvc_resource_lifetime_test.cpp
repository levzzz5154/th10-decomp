// Exercise the maintained C++98 implementation, not the modern runtime copy.
// Win32 and heap calls are scripted boundaries; buffer cleanup is the real
// shared implementation. The byte-exact MSVC build separately checks x86 ABI.
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <set>
#include <string>

#define __declspec(attribute)
#define __stdcall
#define __cdecl
#include "../msvc/src/platform/resource_lifetime.cpp"

enum Failure { NoFailure, FindFailure, LoadFailure, LockFailure, AllocateFailure };
static Failure failure;
static std::string events;
static std::set<void*> allocations;
static unsigned char payload[37];
static DWORD resource_size;
static void* old_buffer;
static const char* expected_name;
static int resource_token, loaded_token;

static void record(const char* event) {
    if (!events.empty()) events += ',';
    events += event;
}

extern "C" HANDLE FindResourceA(HMODULE module, LPCSTR name, LPCSTR type) {
    record("find");
    assert(module == 0 && name == expected_name && type == (LPCSTR)10);
    return failure == FindFailure ? 0 : &resource_token;
}

extern "C" HANDLE LoadResource(HMODULE module, HANDLE resource) {
    record("load");
    assert(module == 0 && resource == &resource_token);
    return failure == LoadFailure ? 0 : &loaded_token;
}

extern "C" void* LockResource(HANDLE loaded) {
    record("lock");
    assert(loaded == &loaded_token);
    return failure == LockFailure ? 0 : payload;
}

extern "C" DWORD SizeofResource(HMODULE module, HANDLE resource) {
    record("size");
    assert(module == 0 && resource == &resource_token);
    return resource_size;
}

extern "C" BOOL FreeResource(HANDLE loaded) {
    if (failure == LockFailure) {
        assert(loaded == 0);  // Retail passes the failed lock result.
        record("release-null");
    } else {
        assert(loaded == &loaded_token);
        record("release");
    }
    return 0;  // The loader ignores the API's return value.
}

extern "C" void* entry_malloc_00452706(DWORD size) {
    record("allocate");
    assert(size == resource_size);
    if (failure == AllocateFailure) return 0;
    void* memory = std::malloc(size ? size : 1);
    assert(memory && allocations.insert(memory).second);
    return memory;
}

extern "C" void entry_free_00452422(void* memory) {
    assert(memory && allocations.erase(memory) == 1);
    record(memory == old_buffer ? "free-old" : "free-owned");
    if (memory == old_buffer) old_buffer = 0;
    std::free(memory);
}

// Unrelated virtual operations are explicit test boundaries. The constructor
// mirrors the field initialization in memory_file.cpp; the production inline
// Close and both production destructors above are used without substitutions.
BufferFile::BufferFile() : size_(0), position_(0), data_(0) {}
BYTE BufferFile::Open(const char*, const char*) { std::abort(); }
DWORD BufferFile::Read(void*, DWORD) { std::abort(); }
BYTE BufferFile::Write(const void*, DWORD) { std::abort(); }
DWORD BufferFile::Tell() const { std::abort(); }
DWORD BufferFile::GetSize() const { std::abort(); }
BYTE BufferFile::Seek(LONG, DWORD) { std::abort(); }

class ResourceFixture : public ResourceFile {
public:
    virtual void Close() {
        record("close");
        BufferFile::Close();
    }
    void own_old_buffer() {
        assert(!data_);
        old_buffer = std::malloc(11);
        assert(old_buffer && allocations.insert(old_buffer).second);
        data_ = (BYTE*)old_buffer;
        position_ = data_ + 3;
        size_ = 11;
    }
    BYTE* data() const { return data_; }
    BYTE* position() const { return position_; }
    DWORD size() const { return size_; }
    void assert_empty() const {
        assert(data_ == 0 && position_ == 0 && size_ == 0);
    }
};

static void reset(Failure next_failure, DWORD size = sizeof(payload)) {
    assert(allocations.empty());
    failure = next_failure;
    resource_size = size;
    old_buffer = 0;
    expected_name = "DEMO";
    events.clear();
    for (unsigned int i = 0; i < sizeof(payload); ++i)
        payload[i] = (unsigned char)(i * 7 + 3);
}

static void test_failure(Failure stage, const char* expected_events, bool existing) {
    reset(stage);
    {
        ResourceFixture file;
        if (existing) file.own_old_buffer();
        assert(file.Open(expected_name, "ignored") == 1);
        file.assert_empty();
        std::string prefix = existing ? "close,free-old," : "close,";
        assert(events == prefix + expected_events);
        events.clear();
    }
    assert(events.empty());  // Empty destruction cannot free a second time.
    assert(allocations.empty());
}

static void test_success(DWORD size, bool integer_name) {
    reset(NoFailure, size);
    if (integer_name) expected_name = (const char*)123;
    {
        ResourceFixture file;
        file.own_old_buffer();
        assert(file.Open(expected_name, 0) == 1);
        assert(events == "close,free-old,find,load,lock,size,allocate,release");
        assert(file.size() == size && file.position() == file.data());
        assert(file.data() != payload && allocations.count(file.data()) == 1);
        assert(std::memcmp(file.data(), payload, size) == 0);
        if (size) {
            BYTE first = file.data()[0];
            payload[0] ^= 0xff;
            assert(file.data()[0] == first);  // Owned copy, not resource alias.
        }
        events.clear();
        file.Close();
        assert(events == "close,free-owned");
        file.assert_empty();
        events.clear();
        file.Close();
        assert(events == "close");
        events.clear();
    }
    assert(events.empty() && allocations.empty());
}

static void test_reopen_and_polymorphic_destruction() {
    reset(NoFailure);
    ResourceFixture* file = new ResourceFixture;
    assert(file->Open(expected_name, "first") == 1);
    old_buffer = file->data();
    events.clear();
    assert(file->Open(expected_name, "second") == 1);
    assert(events == "close,free-old,find,load,lock,size,allocate,release");
    events.clear();
    FileInterface* owner = file;
    delete owner;
    // Destruction uses BufferFile::Close, not ResourceFixture::Close.
    assert(events == "free-owned" && allocations.empty());
}

int main() {
    for (int existing = 0; existing != 2; ++existing) {
        test_failure(FindFailure, "find,close", existing != 0);
        test_failure(LoadFailure, "find,load,close", existing != 0);
        test_failure(LockFailure, "find,load,lock,release-null,close", existing != 0);
        test_failure(AllocateFailure, "find,load,lock,size,allocate,close", existing != 0);
    }
    test_success(37, false);  // Word-copy loop plus its byte tail.
    test_success(4, true);
    test_success(1, false);
    test_success(0, true);   // A successful zero-byte allocation is still owned.
    test_reopen_and_polymorphic_destruction();
}
