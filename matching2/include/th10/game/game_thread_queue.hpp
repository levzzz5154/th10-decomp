#pragma once

struct GameThread;
typedef unsigned int GameThreadQueueWord;
typedef unsigned int uint32_t;

void GameThread_AppendRecord(GameThread* gameThread, const char* name,
                             const GameThreadQueueWord* vector);
void GameThread_AppendFormatted(GameThread* gameThread,
                                const GameThreadQueueWord* vector,
                                const char* format, ...);
void GameThread_AppendFormattedMarked(GameThread* gameThread,
                                      const GameThreadQueueWord* vector,
                                      const char* format, ...);
