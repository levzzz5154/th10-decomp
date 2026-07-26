#pragma once

// A production runtime edge must never silently report success when its
// recovered body has not been connected. This terminates the executable with
// the retail address and a readable edge name.
[[noreturn]] void Runtime_MissingEdge(unsigned int retail_address,
                                      const char* edge_name);
