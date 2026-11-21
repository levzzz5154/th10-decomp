// 0x00424460..0x00424470: MusicRequests_Unpause, MusicRequests_Pause
#include "th10/source_views/music_requests_0b68f8_0.hpp"
#include "th10/source_views/music_requests_0b68f8_1.hpp"
#include "th10/source_views/music_requests_0b68f8_2.hpp"
#include "th10/source_views/music_requests_0b68f8_3.hpp"
#include "th10/source_views/music_requests_0b68f8_4.hpp"
#include "th10/source_views/music_requests_0b68f8_5.hpp"
__declspec(noinline) void __stdcall MusicRequests_Unpause(WaveSoundManager* requests) {
    requests->QueueMusicCommand("UnPause", kMusicCommandUnpause, 0);
}


#include "../../../include/th10/source_views/music_requests_0b68f8_6.hpp"
#include "th10/source_views/music_requests_0b68f8_0.hpp"
#include "th10/source_views/music_requests_0b68f8_1.hpp"
#include "th10/source_views/music_requests_0b68f8_2.hpp"
#include "th10/source_views/music_requests_0b68f8_3.hpp"
#include "th10/source_views/music_requests_0b68f8_4.hpp"
#include "th10/source_views/music_requests_0b68f8_5.hpp"
#include "th10/source_views/music_requests_0b68f8_6.hpp"
__declspec(noinline) void __stdcall MusicRequests_Pause(WaveSoundManager* requests) {
    requests->QueueMusicCommand("Pause", kMusicCommandPause, 0);
}

