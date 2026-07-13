#pragma once

// Recover from a lost D3D device, release reset-sensitive targets, and service
// the pending screenshot request.
void Render_HandleDeviceResetAndSnapshot(void);
