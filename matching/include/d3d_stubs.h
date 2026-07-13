#ifndef D3D_STUBS_H
#define D3D_STUBS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "windows_types.h"

/* ================================================================
 * Minimal D3D9 and D3DX stubs for MSVC 7.1
 * Types are defined in dependency order: primitives -> enums ->
 * structs -> vtables
 * ================================================================ */

/* --- Basic D3D type aliases --- */
typedef DWORD D3DCOLOR;
typedef DWORD D3DFORMAT;
typedef DWORD D3DPOOL;
typedef DWORD D3DMULTISAMPLE_TYPE;
typedef DWORD D3DSWAPEFFECT;
typedef DWORD D3DDEVTYPE;

/* --- Format constants --- */
#define D3DFMT_UNKNOWN              0
#define D3DFMT_R8G8B8               20
#define D3DFMT_A8R8G8B8             21
#define D3DFMT_X8R8G8B8             22
#define D3DFMT_R5G6B5               23
#define D3DFMT_X1R5G5B5             24
#define D3DFMT_A1R5G5B5             25
#define D3DFMT_A4R4G4B4             26
#define D3DFMT_A8                   28
#define D3DFMT_A8R3G3B2             29
#define D3DFMT_A2B10G10R10          31
#define D3DFMT_A8B8G8R8             32
#define D3DFMT_X8B8G8R8             33
#define D3DFMT_A2R10G10B10          35
#define D3DFMT_DXT1                 0x31545844
#define D3DFMT_DXT3                 0x33545844
#define D3DFMT_DXT5                 0x35545844

/* --- Pool constants --- */
#define D3DPOOL_DEFAULT             0
#define D3DPOOL_MANAGED             1
#define D3DPOOL_SYSTEMMEM           2
#define D3DPOOL_SCRATCH             3

/* --- MultiSampleType constants --- */
#define D3DMULTISAMPLE_NONE         0
#define D3DMULTISAMPLE_2_SAMPLES    2
#define D3DMULTISAMPLE_3_SAMPLES    3
#define D3DMULTISAMPLE_4_SAMPLES    4

/* --- SwapEffect constants --- */
#define D3DSWAPEFFECT_DISCARD       1
#define D3DSWAPEFFECT_FLIP          2
#define D3DSWAPEFFECT_COPY          3

/* --- DevType constants --- */
#define D3DDEVTYPE_HAL              1
#define D3DDEVTYPE_REF              2

/* --- Create flags --- */
#define D3DCREATE_SOFTWARE_VERTEXPROCESSING  0x00000020
#define D3DCREATE_HARDWARE_VERTEXPROCESSING  0x00000040
#define D3DCREATE_MIXED_VERTEXPROCESSING     0x00000080
#define D3DCREATE_FPU_PRESERVE               0x00000002
#define D3DCREATE_MULTITHREADED              0x00000004

/* --- HRESULT codes --- */
#define D3D_OK                     0x00000000
#define D3DERR_DEVICELOST          0x88760868
#define D3DERR_DEVICENOTRESET      0x88760869
#define S_OK                       0x00000000

/* --- Misc D3D constants --- */
#define D3DADAPTER_DEFAULT         0
#define D3DCLEAR_TARGET            0x00000001
#define D3DCLEAR_ZBUFFER           0x00000002
#define D3DFVF_XYZ                 0x002
#define D3DFVF_XYZRHW              0x004
#define D3DFVF_NORMAL              0x010
#define D3DFVF_DIFFUSE             0x040
#define D3DFVF_TEX1                0x100
#define D3DPT_TRIANGLELIST         4
#define D3DPT_TRIANGLESTRIP        5
#define D3DUSAGE_RENDERTARGET      0x00000001
#define D3DUSAGE_DEPTHSTENCIL      0x00000002

/* ================================================================
 * Enums (must come before structs that use them)
 * ================================================================ */

typedef enum _D3DRESOURCETYPE {
    D3DRTYPE_SURFACE        = 1,
    D3DRTYPE_VOLUME         = 2,
    D3DRTYPE_TEXTURE        = 3,
    D3DRTYPE_VOLUMETEXTURE  = 4,
    D3DRTYPE_CUBETEXTURE    = 5,
    D3DRTYPE_VERTEXBUFFER   = 6,
    D3DRTYPE_INDEXBUFFER    = 7
} D3DRESOURCETYPE;

typedef enum _D3DBACKBUFFER_TYPE {
    D3DBACKBUFFER_TYPE_MONO         = 0,
    D3DBACKBUFFER_TYPE_LEFT         = 1,
    D3DBACKBUFFER_TYPE_RIGHT        = 2
} D3DBACKBUFFER_TYPE;

typedef enum _D3DTRANSFORMSTATETYPE {
    D3DTS_VIEW          = 2,
    D3DTS_PROJECTION    = 3,
    D3DTS_WORLD         = 256
} D3DTRANSFORMSTATETYPE;

typedef enum _D3DRENDERSTATETYPE {
    D3DRS_ZENABLE                   = 7,
    D3DRS_FILLMODE                  = 8,
    D3DRS_SHADEMODE                 = 9,
    D3DRS_ZWRITEENABLE              = 14,
    D3DRS_ALPHATESTENABLE           = 15,
    D3DRS_SRCBLEND                  = 19,
    D3DRS_DESTBLEND                 = 20,
    D3DRS_CULLMODE                  = 22,
    D3DRS_ZFUNC                     = 23,
    D3DRS_ALPHAREF                  = 24,
    D3DRS_ALPHABLENDENABLE          = 27,
    D3DRS_FOGENABLE                 = 28,
    D3DRS_FOGCOLOR                  = 34,
    D3DRS_FOGSTART                  = 36,
    D3DRS_FOGEND                    = 37,
    D3DRS_RANGEFOGENABLE            = 48,
    D3DRS_CLIPPING                  = 136,
    D3DRS_LIGHTING                  = 137,
    D3DRS_AMBIENT                   = 139,
    D3DRS_COLORVERTEX               = 141,
    D3DRS_LOCALVIEWER               = 142,
    D3DRS_NORMALIZENORMALS          = 143,
    D3DRS_DIFFUSEMATERIALSOURCE     = 145,
    D3DRS_POINTSPRITEENABLE         = 156,
    D3DRS_MULTISAMPLEANTIALIAS      = 161,
    D3DRS_COLORWRITEENABLE          = 168,
    D3DRS_BLENDOP                   = 171,
    D3DRS_SCISSORTESTENABLE         = 174,
    D3DRS_SRGBWRITEENABLE           = 194,
    D3DRS_SEPARATEALPHABLENDENABLE  = 206,
    D3DRS_SRCBLENDALPHA             = 207,
    D3DRS_DESTBLENDALPHA            = 208,
    D3DRS_BLENDOPALPHA              = 209
} D3DRENDERSTATETYPE;

/* ================================================================
 * D3D Structures (dependency-ordered)
 * ================================================================ */

typedef struct _D3DVECTOR3 {
    float x;
    float y;
    float z;
} D3DVECTOR3;

typedef struct _D3DXMATRIX {
    union {
        struct {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };
} D3DXMATRIX, *LPD3DXMATRIX;

typedef struct _D3DXMATRIXA16 {
    D3DXMATRIX mat;
} D3DXMATRIXA16;

typedef struct _D3DRECT {
    LONG x1, y1, x2, y2;
} D3DRECT;

typedef struct _D3DVIEWPORT9 {
    DWORD X;
    DWORD Y;
    DWORD Width;
    DWORD Height;
    float MinZ;
    float MaxZ;
} D3DVIEWPORT9;

typedef struct _D3DDISPLAYMODE {
    UINT      Width;
    UINT      Height;
    UINT      RefreshRate;
    D3DFORMAT Format;
} D3DDISPLAYMODE;

typedef struct _D3DPRESENT_PARAMETERS {
    UINT                BackBufferWidth;
    UINT                BackBufferHeight;
    D3DFORMAT           BackBufferFormat;
    UINT                BackBufferCount;
    D3DMULTISAMPLE_TYPE MultiSampleType;
    DWORD               MultiSampleQuality;
    D3DSWAPEFFECT       SwapEffect;
    HWND                hDeviceWindow;
    BOOL                Windowed;
    BOOL                EnableAutoDepthStencil;
    D3DFORMAT           AutoDepthStencilFormat;
    DWORD               Flags;
    UINT                FullScreen_RefreshRateInHz;
    UINT                PresentationInterval;
} D3DPRESENT_PARAMETERS;

typedef struct _D3DGAMMARAMP {
    WORD red[256];
    WORD green[256];
    WORD blue[256];
} D3DGAMMARAMP;

typedef struct _D3DSURFACE_DESC {
    D3DFORMAT           Format;
    D3DRESOURCETYPE     Type;
    DWORD               Usage;
    D3DPOOL             Pool;
    D3DMULTISAMPLE_TYPE MultiSampleType;
    DWORD               MultiSampleQuality;
    UINT                Width;
    UINT                Height;
} D3DSURFACE_DESC;

typedef struct _D3DLOCKED_RECT {
    INT  Pitch;
    void *pBits;
} D3DLOCKED_RECT;

typedef struct _RGNDATA {
    void *rdh;
    DWORD dwSize;
    DWORD iType;
    DWORD nCount;
    DWORD nRgnSize;
    RECT  rcBound;
} RGNDATA;

/* ================================================================
 * D3D Interface stubs (vtable structs)
 * ================================================================ */

/* IDirect3D9 vtable */
typedef struct IDirect3D9Vtbl {
    HRESULT (WINAPI *QueryInterface)(void *self, void *riid, void **ppvObj);
    ULONG   (WINAPI *AddRef)(void *self);
    ULONG   (WINAPI *Release)(void *self);
    HRESULT (WINAPI *RegisterSoftwareDevice)(void *self, void *pInitFn);
    UINT    (WINAPI *GetAdapterCount)(void *self);
    HRESULT (WINAPI *GetAdapterIdentifier)(void *self, UINT Adapter, DWORD Flags, void *pId);
    UINT    (WINAPI *GetAdapterModeCount)(void *self, UINT Adapter, D3DFORMAT Format);
    HRESULT (WINAPI *EnumAdapterModes)(void *self, UINT Adapter, D3DFORMAT Format, UINT Mode,
                                       D3DDISPLAYMODE *pMode);
    HRESULT (WINAPI *GetAdapterDisplayMode)(void *self, UINT Adapter, D3DDISPLAYMODE *pMode);
    HRESULT (WINAPI *CheckDeviceType)(void *self, UINT Adapter, D3DDEVTYPE DevType,
                                      D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      BOOL bWindowed);
    HRESULT (WINAPI *CheckDeviceFormat)(void *self, UINT Adapter, D3DDEVTYPE DeviceType,
                                        D3DFORMAT AdapterFormat, DWORD Usage,
                                        D3DRESOURCETYPE RType, D3DFORMAT CheckFormat);
    HRESULT (WINAPI *CheckDeviceMultiSampleType)(void *self, UINT Adapter, D3DDEVTYPE DeviceType,
                                                  D3DFORMAT SurfaceFormat, BOOL Windowed,
                                                  D3DMULTISAMPLE_TYPE MultiSampleType,
                                                  DWORD *pQualityLevels);
    HRESULT (WINAPI *CheckDepthStencilMatch)(void *self, UINT Adapter, D3DDEVTYPE DeviceType,
                                              D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat,
                                              D3DFORMAT DepthStencilFormat);
    HRESULT (WINAPI *CheckDeviceFormatConversion)(void *self, UINT Adapter, D3DDEVTYPE DeviceType,
                                                   D3DFORMAT SourceFormat, D3DFORMAT TargetFormat);
    HRESULT (WINAPI *GetDeviceCaps)(void *self, UINT Adapter, D3DDEVTYPE DeviceType, void *pCaps);
    HMONITOR (WINAPI *GetAdapterMonitor)(void *self, UINT Adapter);
    HRESULT (WINAPI *CreateDevice)(void *self, UINT Adapter, D3DDEVTYPE DeviceType,
                                   HWND hFocusWindow, DWORD BehaviorFlags,
                                   D3DPRESENT_PARAMETERS *pPresentationParameters,
                                   void **ppReturnedDeviceInterface);
} IDirect3D9Vtbl;

typedef struct IDirect3D9 {
    IDirect3D9Vtbl *lpVtbl;
} IDirect3D9;

/* IDirect3DDevice9 vtable */
typedef struct IDirect3DDevice9Vtbl {
    HRESULT (WINAPI *QueryInterface)(void *self, void *riid, void **ppvObj);
    ULONG   (WINAPI *AddRef)(void *self);
    ULONG   (WINAPI *Release)(void *self);
    HRESULT (WINAPI *TestCooperativeLevel)(void *self);
    UINT    (WINAPI *GetAvailableTextureMem)(void *self);
    HRESULT (WINAPI *EvictManagedResources)(void *self);
    HRESULT (WINAPI *GetDirect3D)(void *self, IDirect3D9 **ppD3D9);
    HRESULT (WINAPI *GetDeviceCaps)(void *self, void *pCaps);
    HRESULT (WINAPI *GetDisplayMode)(void *self, UINT iSwapChain, D3DDISPLAYMODE *pMode);
    HRESULT (WINAPI *GetCreationParameters)(void *self, void *pParameters);
    HRESULT (WINAPI *SetCursorProperties)(void *self, UINT XHotSpot, UINT YHotSpot,
                                           void *pCursorBitmap);
    void    (WINAPI *SetCursorPosition)(void *self, int X, int Y, DWORD Flags);
    BOOL    (WINAPI *ShowCursor)(void *self, BOOL bShow);
    HRESULT (WINAPI *CreateAdditionalSwapChain)(void *self, D3DPRESENT_PARAMETERS *pParams,
                                                 void **pSwapChain);
    HRESULT (WINAPI *GetSwapChain)(void *self, UINT iSwapChain, void **pSwapChain);
    UINT    (WINAPI *GetNumberOfSwapChains)(void *self);
    HRESULT (WINAPI *Reset)(void *self, D3DPRESENT_PARAMETERS *pPresentationParameters);
    HRESULT (WINAPI *Present)(void *self, const RECT *pSourceRect, const RECT *pDestRect,
                              HWND hDestWindowOverride, const RGNDATA *pDirtyRegion);
    HRESULT (WINAPI *GetBackBuffer)(void *self, UINT iSwapChain, UINT iBackBuffer,
                                     D3DBACKBUFFER_TYPE Type, void **ppBackBuffer);
    HRESULT (WINAPI *GetRasterStatus)(void *self, UINT iSwapChain, void *pRasterStatus);
    HRESULT (WINAPI *SetDialogBoxMode)(void *self, BOOL bEnableDialogs);
    void    (WINAPI *SetGammaRamp)(void *self, UINT iSwapChain, DWORD Flags,
                                   const D3DGAMMARAMP *pRamp);
    void    (WINAPI *GetGammaRamp)(void *self, UINT iSwapChain, D3DGAMMARAMP *pRamp);
    HRESULT (WINAPI *CreateTexture)(void *self, UINT Width, UINT Height, UINT Levels,
                                    DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
                                    void **ppTexture, HANDLE *pSharedHandle);
    HRESULT (WINAPI *CreateVolumeTexture)(void *self, UINT Width, UINT Height, UINT Depth,
                                           UINT Levels, DWORD Usage, D3DFORMAT Format,
                                           D3DPOOL Pool, void **ppVolumeTexture,
                                           HANDLE *pSharedHandle);
    HRESULT (WINAPI *CreateCubeTexture)(void *self, UINT EdgeLength, UINT Levels,
                                         DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
                                         void **ppCubeTexture, HANDLE *pSharedHandle);
    HRESULT (WINAPI *CreateVertexBuffer)(void *self, UINT Length, DWORD Usage, DWORD FVF,
                                          D3DPOOL Pool, void **ppVertexBuffer,
                                          HANDLE *pSharedHandle);
    HRESULT (WINAPI *CreateIndexBuffer)(void *self, UINT Length, DWORD Usage, D3DFORMAT Format,
                                         D3DPOOL Pool, void **ppIndexBuffer,
                                         HANDLE *pSharedHandle);
    HRESULT (WINAPI *CreateRenderTarget)(void *self, UINT Width, UINT Height, D3DFORMAT Format,
                                          D3DMULTISAMPLE_TYPE MultiSample, DWORD MultiSampleQuality,
                                          BOOL Lockable, void **ppSurface, HANDLE *pSharedHandle);
    HRESULT (WINAPI *CreateDepthStencilSurface)(void *self, UINT Width, UINT Height,
                                                  D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample,
                                                  DWORD MultiSampleQuality, BOOL Discard,
                                                  void **ppSurface, HANDLE *pSharedHandle);
    HRESULT (WINAPI *UpdateSurface)(void *self, void *pSourceSurface, const RECT *pSourceRect,
                                     void *pDestSurface, const POINT *pDestPoint);
    HRESULT (WINAPI *UpdateTexture)(void *self, void *pSourceTexture, void *pDestTexture);
    HRESULT (WINAPI *GetRenderTargetData)(void *self, void *pRenderTarget, void *pDestSurface);
    HRESULT (WINAPI *GetFrontBufferData)(void *self, UINT iSwapChain, void *pDestSurface);
    HRESULT (WINAPI *StretchRect)(void *self, void *pSourceSurface, const RECT *pSourceRect,
                                   void *pDestSurface, const RECT *pDestRect, DWORD Filter);
    HRESULT (WINAPI *ColorFill)(void *self, void *pSurface, const RECT *pRect, D3DCOLOR color);
    HRESULT (WINAPI *CreateOffscreenPlainSurface)(void *self, UINT Width, UINT Height,
                                                    D3DFORMAT Format, D3DPOOL Pool,
                                                    void **ppSurface, HANDLE *pSharedHandle);
    HRESULT (WINAPI *SetRenderTarget)(void *self, DWORD RenderTargetIndex, void *pRenderTarget);
    HRESULT (WINAPI *GetRenderTarget)(void *self, DWORD RenderTargetIndex, void **ppRenderTarget);
    HRESULT (WINAPI *SetDepthStencilSurface)(void *self, void *pNewZStencil);
    HRESULT (WINAPI *GetDepthStencilSurface)(void *self, void **ppZStencilSurface);
    HRESULT (WINAPI *BeginScene)(void *self);
    HRESULT (WINAPI *EndScene)(void *self);
    HRESULT (WINAPI *Clear)(void *self, DWORD Count, const D3DRECT *pRects, DWORD Flags,
                            D3DCOLOR Color, float Z, DWORD Stencil);
    HRESULT (WINAPI *SetTransform)(void *self, D3DTRANSFORMSTATETYPE State,
                                    const D3DXMATRIX *pMatrix);
    HRESULT (WINAPI *GetTransform)(void *self, D3DTRANSFORMSTATETYPE State,
                                    D3DXMATRIX *pMatrix);
    HRESULT (WINAPI *MultiplyTransform)(void *self, D3DTRANSFORMSTATETYPE State,
                                         const D3DXMATRIX *pMatrix);
    HRESULT (WINAPI *SetViewport)(void *self, const D3DVIEWPORT9 *pViewport);
    HRESULT (WINAPI *GetViewport)(void *self, D3DVIEWPORT9 *pViewport);
    HRESULT (WINAPI *SetMaterial)(void *self, const void *pMaterial);
    HRESULT (WINAPI *GetMaterial)(void *self, void *pMaterial);
    HRESULT (WINAPI *SetLight)(void *self, DWORD Index, const void *pLight);
    HRESULT (WINAPI *GetLight)(void *self, DWORD Index, void *pLight);
    HRESULT (WINAPI *LightEnable)(void *self, DWORD Index, BOOL Enable);
    HRESULT (WINAPI *GetLightEnable)(void *self, DWORD Index, BOOL *pEnable);
    HRESULT (WINAPI *SetClipPlane)(void *self, DWORD Index, const float *pPlane);
    HRESULT (WINAPI *GetClipPlane)(void *self, DWORD Index, float *pPlane);
    HRESULT (WINAPI *SetRenderState)(void *self, D3DRENDERSTATETYPE State, DWORD Value);
    HRESULT (WINAPI *GetRenderState)(void *self, D3DRENDERSTATETYPE State, DWORD *pValue);
    HRESULT (WINAPI *CreateStateBlock)(void *self, DWORD Type, DWORD *pToken);
    HRESULT (WINAPI *BeginStateBlock)(void *self);
    HRESULT (WINAPI *EndStateBlock)(void *self, DWORD *pToken);
    HRESULT (WINAPI *SetClipStatus)(void *self, const void *pClipStatus);
    HRESULT (WINAPI *GetClipStatus)(void *self, void *pClipStatus);
    HRESULT (WINAPI *GetTexture)(void *self, DWORD Stage, void **ppTexture);
    HRESULT (WINAPI *SetTexture)(void *self, DWORD Stage, void *pTexture);
    HRESULT (WINAPI *GetTextureStageState)(void *self, DWORD Stage, DWORD Type, DWORD *pValue);
    HRESULT (WINAPI *SetTextureStageState)(void *self, DWORD Stage, DWORD Type, DWORD Value);
    HRESULT (WINAPI *GetSamplerState)(void *self, DWORD Sampler, DWORD Type, DWORD *pValue);
    HRESULT (WINAPI *SetSamplerState)(void *self, DWORD Sampler, DWORD Type, DWORD Value);
    HRESULT (WINAPI *ValidateDevice)(void *self, DWORD *pNumPasses);
    HRESULT (WINAPI *SetPaletteEntries)(void *self, UINT PaletteNumber, const void *pEntries);
    HRESULT (WINAPI *GetPaletteEntries)(void *self, UINT PaletteNumber, void *pEntries);
    HRESULT (WINAPI *SetCurrentTexturePalette)(void *self, UINT PaletteNumber);
    HRESULT (WINAPI *GetCurrentTexturePalette)(void *self, UINT *PaletteNumber);
    HRESULT (WINAPI *SetScissorRect)(void *self, const RECT *pRect);
    HRESULT (WINAPI *GetScissorRect)(void *self, RECT *pRect);
    HRESULT (WINAPI *SetSoftwareVertexProcessing)(void *self, BOOL bSoftware);
    BOOL    (WINAPI *GetSoftwareVertexProcessing)(void *self);
    HRESULT (WINAPI *SetNPatchMode)(void *self, float nSegments);
    float   (WINAPI *GetNPatchMode)(void *self);
    HRESULT (WINAPI *DrawPrimitive)(void *self, DWORD PrimitiveType, UINT StartVertex,
                                     UINT PrimitiveCount);
    HRESULT (WINAPI *DrawIndexedPrimitive)(void *self, DWORD PrimitiveType, INT BaseVertexIndex,
                                            UINT MinVertexIndex, UINT NumVertices,
                                            UINT startIndex, UINT primCount);
    HRESULT (WINAPI *DrawPrimitiveUP)(void *self, DWORD PrimitiveType, UINT PrimitiveCount,
                                       const void *pVertexStreamZeroData,
                                       UINT VertexStreamZeroStride);
    HRESULT (WINAPI *DrawIndexedPrimitiveUP)(void *self, DWORD PrimitiveType,
                                              UINT MinVertexIndex, UINT NumVertices,
                                              UINT PrimitiveCount, const void *pIndexData,
                                              D3DFORMAT IndexDataFormat,
                                              const void *pVertexStreamZeroData,
                                              UINT VertexStreamZeroStride);
    HRESULT (WINAPI *ProcessVertices)(void *self, UINT SrcStartIndex, UINT DestIndex,
                                       UINT VertexCount, void *pDestBuffer, void *pVertexDecl,
                                       DWORD Flags);
    HRESULT (WINAPI *CreateVertexDeclaration)(void *self, const void *pVertexElements,
                                               void **ppDecl);
    HRESULT (WINAPI *SetVertexDeclaration)(void *self, void *pDecl);
    HRESULT (WINAPI *GetVertexDeclaration)(void *self, void **ppDecl);
    HRESULT (WINAPI *SetFVF)(void *self, DWORD FVF);
    HRESULT (WINAPI *GetFVF)(void *self, DWORD *pFVF);
    HRESULT (WINAPI *CreateVertexShader)(void *self, const DWORD *pFunction, void **ppShader);
    HRESULT (WINAPI *SetVertexShader)(void *self, void *pShader);
    HRESULT (WINAPI *GetVertexShader)(void *self, void **ppShader);
    HRESULT (WINAPI *SetVertexShaderConstantF)(void *self, UINT StartRegister,
                                                const float *pConstantData, UINT Vector4fCount);
    HRESULT (WINAPI *GetVertexShaderConstantF)(void *self, UINT StartRegister,
                                                float *pConstantData, UINT Vector4fCount);
    HRESULT (WINAPI *SetVertexShaderConstantI)(void *self, UINT StartRegister,
                                                const int *pConstantData, UINT Vector4iCount);
    HRESULT (WINAPI *GetVertexShaderConstantI)(void *self, UINT StartRegister,
                                                int *pConstantData, UINT Vector4iCount);
    HRESULT (WINAPI *SetVertexShaderConstantB)(void *self, UINT StartRegister,
                                                const BOOL *pConstantData, UINT BoolCount);
    HRESULT (WINAPI *GetVertexShaderConstantB)(void *self, UINT StartRegister,
                                                BOOL *pConstantData, UINT BoolCount);
    HRESULT (WINAPI *SetStreamSource)(void *self, UINT StreamNumber, void *pStreamData,
                                       UINT OffsetInBytes, UINT Stride);
    HRESULT (WINAPI *GetStreamSource)(void *self, UINT StreamNumber, void **ppStreamData,
                                       UINT *pOffsetInBytes, UINT *pStride);
    HRESULT (WINAPI *SetStreamSourceFreq)(void *self, UINT StreamNumber, UINT Setting);
    HRESULT (WINAPI *GetStreamSourceFreq)(void *self, UINT StreamNumber, UINT *pSetting);
    HRESULT (WINAPI *SetIndices)(void *self, void *pIndexData);
    HRESULT (WINAPI *GetIndices)(void *self, void **ppIndexData);
    HRESULT (WINAPI *CreatePixelShader)(void *self, const DWORD *pFunction, void **ppShader);
    HRESULT (WINAPI *SetPixelShader)(void *self, void *pShader);
    HRESULT (WINAPI *GetPixelShader)(void *self, void **ppShader);
    HRESULT (WINAPI *SetPixelShaderConstantF)(void *self, UINT StartRegister,
                                               const float *pConstantData, UINT Vector4fCount);
    HRESULT (WINAPI *GetPixelShaderConstantF)(void *self, UINT StartRegister,
                                               float *pConstantData, UINT Vector4fCount);
    HRESULT (WINAPI *DrawRectPatch)(void *self, UINT Handle, const float *pNumSegs,
                                     const void *pRectPatchInfo);
    HRESULT (WINAPI *DrawTriPatch)(void *self, UINT Handle, const float *pNumSegs,
                                    const void *pTriPatchInfo);
    HRESULT (WINAPI *DeletePatch)(void *self, UINT Handle);
    HRESULT (WINAPI *CreateQuery)(void *self, DWORD Type, void **ppQuery);
} IDirect3DDevice9Vtbl;

typedef struct IDirect3DDevice9 {
    IDirect3DDevice9Vtbl *lpVtbl;
} IDirect3DDevice9;

typedef struct IDirect3DSurface9 {
    void *lpVtbl;
} IDirect3DSurface9;

typedef struct IDirect3DTexture9 {
    void *lpVtbl;
} IDirect3DTexture9;

#ifdef __cplusplus
}
#endif

#endif /* D3D_STUBS_H */
