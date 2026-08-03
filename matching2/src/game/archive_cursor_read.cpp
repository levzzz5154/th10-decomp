// 0x0044DE10 FUN_0044de10
// Readable reconstruction of retail helper FUN_0044de10 (archive-cursor
// read).  See the header for the cursor slot layout and the retail ABI
// reification.

#include "th10/game/archive_cursor_read.hpp"

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#else
#include <cstdint>
#endif
#include <cstring>

#ifdef _MSC_VER
extern "C" void* __imp_ReadFile;
#endif

extern "C" {

typedef void* HANDLE;
typedef uint32_t* LPDWORD;

// Win32 kernel32 export.  Resolved against Wine's kernel32 on the
// production target; declared extern so the Linux-side test fixture can
// override the symbol at link time.
__stdcall int ReadFile(HANDLE hFile, void* lpBuffer, uint32_t nNumberOfBytesToRead,
                       LPDWORD lpNumberOfBytesRead, void* lpOverlapped);

}  // extern "C"


#ifdef _MSC_VER
// 0x0044DE10 - Retail archive-cursor read. Custom ABI: cursor in EAX, byte
// count in EDX, destination and out-count on the stack; returns 8 bytes of
// stack. Copies from the in-memory cursor or issues ReadFile on the handle.
__declspec(naked) uint32_t ArchiveCursor_ReadRetail() {
    __asm {
        mov ecx, [eax+7Ch]
        test ecx, ecx
        push ebx
        mov ebx, [esp+8]
        push esi
        push edi
        mov edi, [esp+14h]
        jz loc_44DE91
        mov ecx, [eax+84h]
        test ecx, ecx
        jnz loc_44DE37
loc_44DE2C:
        pop edi
        pop esi
        mov eax, 800401F0h
        pop ebx
        ret 8
loc_44DE37:
        test edi, edi
        jz loc_44DE41
        mov dword ptr [edi], 0
loc_44DE41:
        mov ebx, [eax+88h]
        mov ecx, [eax+80h]
        mov esi, [eax+84h]
        push ebp
        lea ebp, [esi+edx]
        lea edi, [ecx+ebx]
        cmp ebp, edi
        pop ebp
        jbe loc_44DE65
        sub ecx, esi
        add ecx, ebx
        mov edx, ecx
loc_44DE65:
        mov edi, [esp+10h]
        mov ecx, edx
        mov ebx, ecx
        shr ecx, 2
        rep movsd
        mov ecx, ebx
        and ecx, 3
        rep movsb
        add [eax+84h], edx
        mov eax, [esp+14h]
        test eax, eax
        jz loc_44DE89
        mov [eax], edx
loc_44DE89:
        pop edi
        pop esi
        xor eax, eax
        pop ebx
        ret 8
loc_44DE91:
        mov esi, [eax+8Ch]
        test esi, esi
        jz loc_44DE2C
        test ebx, ebx
        jz loc_44DECF
        test edi, edi
        jz loc_44DECF
        mov ecx, [eax+8]
        cmp edx, ecx
        jbe loc_44DEAC
        mov edx, ecx
loc_44DEAC:
        sub ecx, edx
        push 0
        mov [eax+8], ecx
        lea eax, [esp+14h]
        push eax
        push edx
        push ebx
        push esi
        call dword ptr [__imp_ReadFile]
        mov ecx, [esp+10h]
        mov [edi], ecx
        pop edi
        pop esi
        xor eax, eax
        pop ebx
        ret 8
loc_44DECF:
        pop edi
        pop esi
        mov eax, 80070057h
        pop ebx
        ret 8
    }
}
#endif

uint32_t ArchiveCursor_Read(void* cursor, uint32_t byte_count,
                            void* destination,
                            uint32_t* out_bytes_read) {
    if (cursor == 0) return 0x800401f0u;
    uint8_t* bytes = static_cast<uint8_t*>(cursor);

    if (*reinterpret_cast<int32_t*>(bytes + 0x7c) == 0) {
        // File-backed branch.
        HANDLE hFile = *reinterpret_cast<HANDLE*>(bytes + 0x8c);
        if (hFile == 0) {
            return 0x800401f0u;
        }
        if (destination == 0 || out_bytes_read == 0) {
            return 0x80070057u;
        }
        const uint32_t remaining = *reinterpret_cast<uint32_t*>(bytes + 0x08);
        if (byte_count > remaining) {
            byte_count = remaining;
        }
        *reinterpret_cast<uint32_t*>(bytes + 0x08) = remaining - byte_count;
        ReadFile(hFile, destination, byte_count,
                 reinterpret_cast<LPDWORD>(&destination),
                 0);
        *out_bytes_read = static_cast<uint32_t>(
            reinterpret_cast<uintptr_t>(destination));
        return 0;
    }

    // Memory-backed branch.
    if (*reinterpret_cast<int32_t*>(bytes + 0x84) == 0) {
        return 0x800401f0u;
    }
    if (out_bytes_read != 0) {
        *out_bytes_read = 0;
    }
    if (destination == 0 || out_bytes_read == 0) {
        return 0x80070057u;
    }
    const uint8_t* cursor_ptr =
        *reinterpret_cast<uint8_t**>(bytes + 0x84);
    const uint8_t* base_ptr =
        *reinterpret_cast<uint8_t**>(bytes + 0x80);
    const int32_t end_offset =
        *reinterpret_cast<int32_t*>(bytes + 0x88);
    // The retail computes the bound as 32-bit integer arithmetic:
    //   limit = (int)base + end_offset
    //   if (limit < (int)cursor + byte_count)
    //       byte_count = (int)base - (int)cursor + end_offset;
    // On a 64-bit host the in-buffer pointer remains valid as long as
    // the cursor+count fits inside the buffer of end_offset bytes
    // starting at base.
    const uintptr_t base_addr =
        reinterpret_cast<uintptr_t>(base_ptr);
    const uintptr_t cursor_addr =
        reinterpret_cast<uintptr_t>(cursor_ptr);
    const uintptr_t limit_addr = base_addr + end_offset;
    if (limit_addr < cursor_addr + byte_count) {
        byte_count = static_cast<uint32_t>(limit_addr - cursor_addr);
    }
    // Word-wise copy then byte tail, exactly as the retail unrolled it.
    uint8_t* out = static_cast<uint8_t*>(destination);
    const uint8_t* in = cursor_ptr;
    // Note: *cursor_ptr is a single malloc'd buffer of at least
    // ``byte_count`` bytes, so the dword pointer cast below is
    // well-aligned (4-byte aligned within a malloc'd region).
    for (uint32_t words = byte_count >> 2; words != 0; --words) {
        std::memcpy(out, in, 4);
        out += 4;
        in += 4;
    }
    for (uint32_t tail = byte_count & 3; tail != 0; --tail) {
        *out++ = *in++;
    }
    *reinterpret_cast<uint8_t**>(bytes + 0x84) =
        const_cast<uint8_t*>(in);
    if (out_bytes_read != 0) {
        *out_bytes_read = byte_count;
    }
    return 0;
}
