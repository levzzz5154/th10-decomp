#include "th10/runtime/missing_edge.hpp"

#include <cstdio>
#include <cstdlib>

[[noreturn]] void Runtime_MissingEdge(unsigned int retail_address,
                                      const char* edge_name) {
    std::fprintf(stderr,
                 "[th10-recon] FATAL missing runtime edge 0x%08X: %s\n",
                 retail_address,
                 edge_name != 0 ? edge_name : "(unnamed)");
    std::fflush(stderr);
    std::abort();
}
