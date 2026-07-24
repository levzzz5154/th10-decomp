#pragma once

// 0x00437D10 - Tear down the GDI font cache: run the shared cache flush
// (retail 0x00436A30) and delete the fifteen cached GDI objects stored
// in the global handle table at 0x00491868..0x004918A0, from the
// highest slot down. Both edges are injected; the handle table is the
// retail global reproduced as a host array.
extern void* DAT_00491868[15];

void FontCache_DeleteGdiObjects(void (*flush)(), void (*delete_object)(void*));
