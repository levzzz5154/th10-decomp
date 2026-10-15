# Static initializers and destructors

The compiler-generated dynamic initializers of TH10's global objects
(0x004658C0..0x004659E0, called from the CRT's `.CRT$XCU` table at start-up)
and the destructors they register with `atexit`
(0x00465A00..0x00465A80). Each `*_init.cpp` names the object it sets up; the
matching `*_exit.cpp` is its destructor.
