// Standalone game-globals blob.
//
// The reconstructed TUs extern the retail globals by their retail names
// (dword_/byte_/DAT_); the test suite defines them per test TU, while the
// standalone needs one stable home for the set the host-path code touches.
// The values are the host's runtime state (the retail .data lives in the
// retail binary; the standalone owns its own).

extern "C" {
unsigned int dword_477810 = 0;   // published game-UI manager
unsigned int dword_477834 = 0;   // player position record
unsigned int dword_491C10 = 0;   // animation manager
unsigned int dword_491C30 = 0;   // render batch state
unsigned int dword_491D78 = 0;   // view flags
unsigned int dword_492378 = 0;   // alpha-blend latch
// Input byte twin (retail byte_474E34). main_menu_dispatch.cpp externs it as
// unsigned int (the retail masks 0x10/0x20/0x40/0x80 all sit in the low
// byte), so the standalone definition must be dword-wide to match.
unsigned int byte_474E34 = 0;    // input byte twin
}
