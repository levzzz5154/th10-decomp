// =============================================================================
// pack_file_loader.cpp - Shared file loader and executable checksum
// =============================================================================
#include "th10/platform/pack_file_loader.hpp"

namespace {

const char* StripPath(const char* name) {
    const char* base = name;
    for (const char* cursor = name; *cursor != '\0'; ++cursor)
        if (*cursor == '\\' || *cursor == '/')
            base = cursor + 1;
    return base;
}

bool NamesEqualNoCase(const char* left, const char* right) {
    for (;; ++left, ++right) {
        char a = *left, b = *right;
        if (a >= 'A' && a <= 'Z') a = static_cast<char>(a - 'A' + 'a');
        if (b >= 'A' && b <= 'Z') b = static_cast<char>(b - 'A' + 'a');
        if (a != b) return false;
        if (a == '\0') return true;
    }
}

} // namespace

// 0x0044B360 - PackFile_Load: load a file either from the mounted archive
// table (DAT_00497990, stride four dwords: name/data/size/flags) or straight
// from disk. The whole operation runs under the file critical section.
// Returns a caller-owned buffer, or null. size_out is optional: retail tests
// its pointer before every store.
void* PackFile_Load(const char* name, unsigned int* size_out, int from_disk,
                    const PackFileTable* table, const PackFileHooks* hooks) {
    hooks->lock(hooks->context);
    void* buffer = 0;
    if (from_disk == 0) {
        // Archive path: strip any directory prefix, then look the entry up
        // case-insensitively in the mounted table.
        const char* base_name = StripPath(name);
        const PackFileEntry* found = 0;
        unsigned int entry_size = 0;
        for (unsigned int index = 0; index < table->entry_count; ++index) {
            const PackFileEntry* entry = &table->entries[index];
            if (!NamesEqualNoCase(entry->name, base_name))
                continue;
            found = entry;
            entry_size = entry->size;
            break;
        }
        // A miss leaves retail's v11 at zero and still publishes it, so a
        // caller that reuses its size variable sees 0 rather than stale data.
        if (size_out != 0)
            *size_out = entry_size;
        if (entry_size != 0) {
            buffer = hooks->alloc(hooks->context, entry_size);
            if (buffer != 0)
                hooks->extract_entry(hooks->context, found, buffer);
        }
    } else {
        // Disk path: CreateFileA / GetFileSize / ReadFile / CloseHandle.
        // Retail ignores ReadFile's status and publishes the byte count it
        // actually transferred, handing the buffer back either way; only a
        // failed open or a failed allocation produce a null result.
        void* handle = hooks->open_for_read(hooks->context, name);
        if (handle != 0) {
            unsigned int size = hooks->file_size(hooks->context, handle);
            buffer = hooks->alloc(hooks->context, size);
            if (buffer != 0) {
                const unsigned int read =
                    hooks->read(hooks->context, handle, buffer, size);
                if (size_out != 0)
                    *size_out = read;
            }
            hooks->close(hooks->context, handle);
        }
    }
    hooks->unlock(hooks->context);
    return buffer;
}

// 0x0043A1C0 - Executable_Checksum: sum every dword of the module file on
// disk (excluding the trailing padding dword) and record size + sum.
// Returns the checksum, or -1 when the module path or file read fails.
int Executable_Checksum(unsigned int* checksum_out, unsigned int* size_out,
                        const ExecutableChecksumHooks* hooks) {
    char path[0x105];
    if (hooks->module_file_name(hooks->context, path, sizeof(path)) == 0)
        return -1;
    unsigned int size = 0;
    void* image = hooks->load_file(hooks->context, path, &size);
    if (image == 0)
        return -1;
    const unsigned int* words = static_cast<const unsigned int*>(image);
    unsigned int sum = 0;
    // Retail is `v5 = size / 4 - 1; if (v5 > 0) do { ... } while (--v5);` -
    // a truncating divide, so exactly size/4 - 1 dwords are summed. Rounding
    // up with (size + 3) / 4 summed one extra dword whenever size was not a
    // multiple of four, reading up to three bytes past the buffer.
    for (unsigned int index = 0; index + 1 < size / 4; ++index)
        sum += words[index];
    hooks->release(hooks->context, image);
    *size_out = size;      // _DAT_00492384
    *checksum_out = sum;   // _DAT_00492380
    return static_cast<int>(sum);
}
