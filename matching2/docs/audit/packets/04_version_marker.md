# Calibration packet: 0x00420100

Baseline: `895c4202387d1c6099cf0cec2e8798bdae6a1754`.

Review the exact address and each supplied C++ implementation independently. Compare valid-state behavior, branches, constants, side effects, ownership, return values and ABI adapters. Distinguish an actual mismatch from an unmeasured precision boundary or a justified host contract. Source comments and annotations are claims to check. No prior reviewer verdict is supplied.

Report one row per implementation, exact evidence lines, a minimal counterexample when possible, production reachability evidence, and what remains unknown. Assembly resolves decompiler disagreements. This packet does not establish the live retail floating-point environment or gameplay reachability. Request additional dependencies by path/address when needed; do not fill gaps with assumptions.

### [matching2/src/app/version_marker.cpp:1–30](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/app/version_marker.cpp#L1-L30)

Whole-file SHA-256: `8841455dafe7760e00e4251b91e09845dd374ec95cd7d1aa562c9bf7db29575d`

```text
1: #include "th10/app/version_marker.hpp"
2: 
3: #include <cstdio>
4: 
5: // 0x00420100 - probes the fixed version resource, then loads the generated
6: // version marker ("th10_0100a.ver"). The loaded pointer and byte count are
7: // published together. Both failure paths emit the retail diagnostic and
8: // return -1; a present marker returns 0.
9: int VersionMarker_Load(VersionMarkerEnv* env) {
10: 	if (!env->probe("th10.ver")) {
11: 		env->log(env->missing_probe_log);
12: 		return -1;
13: 	}
14: 
15: 	char name[128];
16: 	std::snprintf(name, sizeof(name), "th10_%.4x%c.ver", env->version,
17: 	              env->suffix);
18: 	std::size_t size = 0;
19: 	unsigned char* data = env->load(name, &size);
20: 	*env->published_data = data;
21: 	*env->published_size = size;
22: 	if (data != 0) {
23: 		return 0;
24: 	}
25: 
26: 	// Retail explicitly republishes null before logging the load failure.
27: 	*env->published_data = 0;
28: 	env->log(env->load_failure_log);
29: 	return -1;
30: }
```

### [matching2/include/th10/app/version_marker.hpp:1–19](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/include/th10/app/version_marker.hpp#L1-L19)

Whole-file SHA-256: `8d7cc897dde35aed5df088df89f61ccdb26ab259e78e01834d21721384307cf8`

```text
1: #pragma once
2: 
3: #include <cstddef>
4: 
5: // Version resource probe and version marker load (retail 0x00420100).
6: // --- 0x00420100: load the executable-version marker -------------------------
7: struct VersionMarkerEnv {
8: 	int version;                    // retail constant 0x100
9: 	char suffix;                    // retail constant 'a'
10: 	const char* missing_probe_log;  // retail DAT_0046dfa0
11: 	const char* load_failure_log;   // retail DAT_0046dfc8
12: 	bool (*probe)(const char* fixed_resource_name);
13: 	unsigned char* (*load)(const char* generated_name, std::size_t* size);
14: 	void (*log)(const char* text);
15: 	unsigned char** published_data; // retail DAT_0049238c
16: 	std::size_t* published_size;    // retail DAT_00492388
17: };
18: 
19: int VersionMarker_Load(VersionMarkerEnv* env);
```

### [ida/th10.exe.c:33109–33132](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.c#L33109-L33132)

Whole-file SHA-256: `61481fa38c3e5695794ef5f5dd439c7e2af4126514b508af0a83400bfb481163`

```text
33109: //----- (00420100) --------------------------------------------------------
33110: int sub_420100()
33111: {
33112:   int v1; // [esp+4h] [ebp-88h] BYREF
33113:   char Buffer[128]; // [esp+8h] [ebp-84h] BYREF
33114: 
33115:   if ( sub_434C30("th10.dat", (int)&dword_497990) )
33116:   {
33117:     sprintf(Buffer, "th10_%.4x%c.ver", 256, 97);
33118:     dword_49238C = sub_44B360(Buffer, (DWORD)&v1, 0);
33119:     dword_492388 = v1;
33120:     if ( dword_49238C )
33121:       return 0;
33122:     sub_44B8E0((int)&Text, aError_2);
33123:   }
33124:   else
33125:   {
33126:     sub_44B8E0((int)&Text, aError_0);
33127:   }
33128:   return -1;
33129: }
33130: // 492388: using guessed type int dword_492388;
33131: // 497990: using guessed type int dword_497990;
33132: 
```

### [ida/th10.exe.asm:45162–45221](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L45162-L45221)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
45162: sub_420100 proc near
45163: 
45164: var_88= dword ptr -88h
45165: Buffer= byte ptr -84h
45166: var_4= dword ptr -4
45167: 
45168: sub     esp, 88h
45169: mov     eax, ___security_cookie
45170: xor     eax, esp
45171: mov     [esp+88h+var_4], eax
45172: push    edi             ; ArgList
45173: mov     eax, offset aTh10Dat ; "th10.dat"
45174: mov     ecx, offset dword_497990
45175: call    sub_434C30
45176: test    al, al
45177: jz      short loc_420183
45178: push    61h ; 'a'
45179: push    100h
45180: lea     eax, [esp+94h+Buffer]
45181: push    offset aTh104xCVer ; "th10_%.4x%c.ver"
45182: push    eax             ; Buffer
45183: call    _sprintf
45184: add     esp, 10h
45185: push    0
45186: lea     ecx, [esp+90h+var_88]
45187: push    ecx
45188: lea     eax, [esp+94h+Buffer]
45189: call    sub_44B360
45190: test    eax, eax
45191: mov     edx, [esp+8Ch+var_88]
45192: mov     dword_49238C, eax
45193: mov     dword_492388, edx
45194: jnz     short loc_42016B
45195: push    offset aError_2 ; "error : "
45196: jmp     short loc_420188
45197: 
45198: loc_42016B:
45199: xor     eax, eax
45200: pop     edi
45201: mov     ecx, [esp+88h+var_4]
45202: xor     ecx, esp        ; StackCookie
45203: call    @__security_check_cookie@4 ; __security_check_cookie(x)
45204: add     esp, 88h
45205: retn
45206: 
45207: loc_420183:
45208: push    offset aError_0 ; "error : "
45209: 
45210: loc_420188:
45211: mov     edi, offset Text
45212: call    sub_44B8E0
45213: mov     ecx, [esp+90h+var_4]
45214: add     esp, 4
45215: pop     edi
45216: xor     ecx, esp        ; StackCookie
45217: or      eax, 0FFFFFFFFh
45218: call    @__security_check_cookie@4 ; __security_check_cookie(x)
45219: add     esp, 88h
45220: retn
45221: sub_420100 endp
```

## Referenced retail constants

### [ida/th10.exe.asm:158565–158565](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L158565-L158565)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
158565: aError_0 db 'error : '
```

### [ida/th10.exe.asm:158598–158598](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L158598-L158598)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
158598: aError_2 db 'error : '
```

### [ida/th10.exe.asm:158632–158632](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L158632-L158632)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
158632: aTh104xCVer db 'th10_%.4x%c.ver',0
```

### [ida/th10.exe.asm:158633–158633](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/ida/th10.exe.asm#L158633-L158633)

Whole-file SHA-256: `d08532437ba6b3012825986f4ff68492abe9f3db7d9e16ce6e8fe9b3ef96c32d`

```text
158633: aTh10Dat db 'th10.dat',0
```

### [decompiled/ghidra_raw/00420100_FUN_00420100.c:1–40](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/decompiled/ghidra_raw/00420100_FUN_00420100.c#L1-L40)

Whole-file SHA-256: `02dc72b919c4bf565f456ae77093b75a839091441b25f8b34d602452a6f2a102`

```text
1: /*
2:  * Raw Ghidra pseudocode reference; not directly compilable.
3:  * Address: 0x00420100
4:  * Tracking name: FUN_00420100
5:  * Ghidra name: FUN_00420100
6:  * Tracked span: 368 bytes
7:  */
8: 
9: 
10: /* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
11: /* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
12: 
13: undefined4 FUN_00420100(void)
14: 
15: {
16:   undefined4 uVar1;
17:   char *pcVar2;
18:   size_t local_88;
19:   char local_84 [128];
20:   uint local_4;
21:   
22:   local_4 = DAT_00473660 ^ (uint)&local_88;
23:   uVar1 = FUN_00434c30(0x497990);
24:   if ((char)uVar1 == '\0') {
25:     pcVar2 = &DAT_0046dfa0;
26:   }
27:   else {
28:     _sprintf(local_84,"th10_%.4x%c.ver",0x100,0x61);
29:     DAT_0049238c = FUN_0044b360(&local_88,0);
30:     _DAT_00492388 = local_88;
31:     if (DAT_0049238c != (byte *)0x0) {
32:       return 0;
33:     }
34:     pcVar2 = &DAT_0046dfc8;
35:     DAT_0049238c = (byte *)0x0;
36:   }
37:   FUN_0044b8e0(pcVar2);
38:   return 0xffffffff;
39: }
40: 
```

## Production textual cross-references

All token occurrences in versioned `src/` and `standalone/` C++/headers are listed below, including definitions and comments. These are navigation aids; indirect calls and differently named adapters require further inspection. Tests are deliberately excluded from this production search.

- [matching2/src/app/version_marker.cpp:9](https://github.com/levzzz5154/th10-decomp/blob/895c4202387d1c6099cf0cec2e8798bdae6a1754/matching2/src/app/version_marker.cpp#L9): `int VersionMarker_Load(VersionMarkerEnv* env) {`
