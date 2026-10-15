#pragma once


// 0x0044B620 - Open the shared probe file for writing, truncating it. A
// failure formats the Win32 error text, releases it again and unwinds the
// critical section, reporting -1; the shared handle is -1 after a failure.
