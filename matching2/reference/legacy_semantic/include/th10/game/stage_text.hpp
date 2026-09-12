#pragma once

char* StageText_SkipLine(char* cursor, int* remaining);
void StageText_ExtractLine(char* cursor, char* destination, int* remaining);

struct StageTextState {
    float first[3];
    float second[3];
    float defaults_a[3];
    float defaults_b[3];
    int resource;
    unsigned int mode;
    int current;
    int length;
    int selection;
};

void StageText_Initialize(
    StageTextState* state, const float* first, const float* second,
    int resource, unsigned char mode, const float* defaults);
