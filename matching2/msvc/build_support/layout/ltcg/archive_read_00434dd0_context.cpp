// Complete real checksum -> file loader -> archive reader graph.
// Only the reader is selected as recovery in this dedicated scope.
#include "../../../src/pack/arcmngr/dat_archive_read.cpp"
#include "archive_read/find.cpp"
#include "archive_read/decrypt.cpp"
#include "archive_read/load.cpp"
#include "archive_read/checksum.cpp"
