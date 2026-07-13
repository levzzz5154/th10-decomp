#ifndef DSOUND_STUBS_H
#define DSOUND_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "windows_types.h"

/* ================================================================
 * Minimal DirectSound 8 stubs for MSVC 7.1
 * Covers types used by th10.exe decompilation
 * ================================================================ */

/* --- DSound buffer flags --- */
#define DSBCAPS_PRIMARYBUFFER       0x00000001
#define DSBCAPS_STATIC              0x00000002
#define DSBCAPS_LOCHARDWARE         0x00000004
#define DSBCAPS_LOCSOFTWARE         0x00000008
#define DSBCAPS_CTRL3D              0x00000010
#define DSBCAPS_CTRLFREQUENCY       0x00000020
#define DSBCAPS_CTRLPAN             0x00000040
#define DSBCAPS_CTRLVOLUME          0x00000080
#define DSBCAPS_CTRLPOSITIONNOTIFY  0x00000100
#define DSBCAPS_CTRLFX              0x00000200
#define DSBCAPS_GETCURRENTPOSITION2 0x00010000
#define DSBCAPS_GLOBALFOCUS         0x00008000

/* --- WAVEFORMATEX --- */
typedef struct tWAVEFORMATEX {
    WORD  wFormatTag;
    WORD  nChannels;
    DWORD nSamplesPerSec;
    DWORD nAvgBytesPerSec;
    WORD  nBlockAlign;
    WORD  wBitsPerSample;
    WORD  cbSize;
} WAVEFORMATEX, *LPWAVEFORMATEX;

#define WAVE_FORMAT_PCM 1

/* --- DSBUFFERDESC --- */
typedef struct _DSBUFFERDESC {
    DWORD           dwSize;
    DWORD           dwFlags;
    DWORD           dwBufferBytes;
    DWORD           dwReserved;
    LPWAVEFORMATEX  lpwfxFormat;
} DSBUFFERDESC, *LPDSBUFFERDESC;

/* --- DSCAPS --- */
typedef struct _DSCAPS {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwMinSecondarySampleRate;
    DWORD dwMaxSecondarySampleRate;
    DWORD dwPrimaryBuffers;
    DWORD dwMaxHwMixingAllBuffers;
    DWORD dwMaxHwMixingStaticBuffers;
    DWORD dwMaxHwMixingStreamingBuffers;
    DWORD dwFreeHwMixingAllBuffers;
    DWORD dwFreeHwMixingStaticBuffers;
    DWORD dwFreeHwMixingStreamingBuffers;
    DWORD dwMaxHw3DAllBuffers;
    DWORD dwMaxHw3DStaticBuffers;
    DWORD dwMaxHw3DStreamingBuffers;
    DWORD dwFreeHw3DAllBuffers;
    DWORD dwFreeHw3DStaticBuffers;
    DWORD dwFreeHw3DStreamingBuffers;
    DWORD dwTotalHwMemBytes;
    DWORD dwFreeHwMemBytes;
    DWORD dwMaxContigFreeHwMemBytes;
    DWORD dwUnlockTransferRateHwBuffers;
    DWORD dwPlayCpuOverheadSwBuffers;
    DWORD dwReserved1;
    DWORD dwReserved2;
} DSCAPS, *LPDSCAPS;

/* --- DSBCAPS --- */
typedef struct _DSBCAPS {
    DWORD dwSize;
    DWORD dwFlags;
    DWORD dwBufferBytes;
    DWORD dwUnlockTransferRate;
    DWORD dwPlayCpuOverhead;
} DSBCAPS, *LPDSBCAPS;

/* --- DirectSound interfaces (opaque) --- */
typedef struct IDirectSound8 {
    void *lpVtbl;
} IDirectSound8;

typedef struct IDirectSoundBuffer8 {
    void *lpVtbl;
} IDirectSoundBuffer8;

/* --- DSBPLAY flags --- */
#define DSBPLAY_LOOPING         0x00000001

/* --- DSBSTATUS flags --- */
#define DSBSTATUS_PLAYING       0x00000001
#define DSBSTATUS_BUFFERLOST    0x00000002
#define DSBSTATUS_LOOPING       0x00000004

/* --- DirectSoundCreate8 ordinal --- */
#define DIRECTSOUNDCREATE8_ORDINAL 11

#ifdef __cplusplus
}
#endif

#endif /* DSOUND_STUBS_H */
