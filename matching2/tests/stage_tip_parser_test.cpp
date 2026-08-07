// Host tests for retail 0x00419960 (ParseStageTips), reconstructed in
// src/game/stage_tip_parser.cpp.  The parser loads its input through the
// reconstructed pack-loader hooks, so the harness feeds it real files through
// a disk-path hook set.
#include "th10/game/stage_tip_parser.hpp"

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>

namespace {

struct FileHooks {
    FILE* file;
};

void* Alloc(void*, unsigned int size) { return std::malloc(size); }
void Release(void*, void* memory) { std::free(memory); }
void NoOp(void*) {}
void* Open(void* context, const char* name) {
    static_cast<FileHooks*>(context)->file = std::fopen(name, "rb");
    return static_cast<FileHooks*>(context)->file;
}
unsigned int FileSize(void*, void* handle) {
    FILE* file = static_cast<FILE*>(handle);
    long position = std::ftell(file);
    std::fseek(file, 0, SEEK_END);
    long size = std::ftell(file);
    std::fseek(file, position, SEEK_SET);
    return static_cast<unsigned int>(size);
}
unsigned int Read(void*, void* handle, void* buffer, unsigned int size) {
    return static_cast<unsigned int>(
        std::fread(buffer, 1, size, static_cast<FILE*>(handle)));
}
void Close(void*, void* handle) { std::fclose(static_cast<FILE*>(handle)); }

const PackFileHooks kHooks = {
    /*context=*/0, /*lock=*/NoOp, /*unlock=*/NoOp,
    /*alloc=*/Alloc, /*release=*/Release, /*extract_entry=*/0,
    /*open_for_read=*/Open, /*file_size=*/FileSize, /*read=*/Read,
    /*close=*/Close,
};
const PackFileTable kEmptyTable = {0, 0};

int Parse(StageTipManager* manager, const char* path, int suppress) {
    FileHooks context = {0};
    PackFileHooks hooks = kHooks;
    hooks.context = &context;
    return ParseStageTips(manager, path, suppress, &kEmptyTable, &hooks);
}

// Write `text` to a fresh temp file and return its path (caller frees).
char* WriteTips(const char* text) {
    static const char kPattern[] = "/tmp/th10-tips-XXXXXX";
    char* path = static_cast<char*>(std::malloc(sizeof(kPattern)));
    std::strcpy(path, kPattern);
    int fd = ::mkstemp(path);
    assert(fd >= 0);
    std::size_t length = std::strlen(text);
    assert(::write(fd, text, length) == static_cast<ssize_t>(length));
    ::close(fd);
    return path;
}

int CountChain(const StageTipManager& manager, int index) {
    int count = 0;
    for (const StageTipNode* node = manager.lists[index].next; node != 0;
         node = node->next)
        ++count;
    return count;
}

StageTip* FirstTip(const StageTipManager& manager, int index) {
    return manager.lists[index].next != 0 ? manager.lists[index].next->owner
                                          : 0;
}

void FreeChains(StageTipManager* manager) {
    for (int index = 0; index < 16; ++index) {
        StageTipNode* node = manager->lists[index].next;
        while (node != 0) {
            StageTipNode* next = node->next;
            std::free(node->owner);
            node = next;
        }
        manager->lists[index].next = 0;
        manager->lists[index].previous = 0;
    }
}

void TestFullRecord() {
    char* path = WriteTips(
        "Version: 0.0\n"
        "Stage: 2\n"
        "Tips:\n"
        "Pos: 10, 20\n"
        "Text: \"hello tip\"\n"
        "Count: 7\n"
        "Time: 300\n"
        "Base: boss_5\n"
        "Align: left\n"
        "Remain: 60\n"
        "Scale: 2.5\n"
        "Color: 1,2,3\n"
        "Alpha: 4\n"
        "End:\n"
        "StageEnd:\n");
    StageTipManager manager = {};
    assert(Parse(&manager, path, 1) == 0);
    assert(CountChain(manager, 1) == 0 && CountChain(manager, 2) == 1 &&
           CountChain(manager, 3) == 0);
    assert(CountChain(manager, 10) == 0);  // duplicate chain untouched
    StageTip* tip = FirstTip(manager, 2);
    assert(tip != 0);
    assert(tip->x == 10.0f && tip->y == 20.0f);
    assert(std::strcmp(tip->name, "hello tip") == 0);
    assert(tip->display_value == 7);   // Count
    assert(tip->duration == 300);      // Time
    assert(tip->display_mode == 28);   // Base: boss_5
    assert(tip->display_zero == 1);    // Align: left
    assert(tip->selection == 60);      // Remain
    assert(tip->scale == 2.5f);
    // Color 1,2,3 + Alpha 4: retail stores first at +0x86, second at +0x85,
    // third at +0x84, alpha at +0x87 -> memory bytes [3,2,1,4].
    assert(tip->state == 0x04010203);
    float width = 0.0f;
    std::memcpy(&width, &tip->rendered_width, sizeof(width));
    assert(width == 9.0f * 2.5f * 7.5f);  // strlen("hello tip") * scale * 7.5
    FreeChains(&manager);
    std::free(path);
}

void TestDuplicate() {
    char* path = WriteTips(
        "Version: 0.0\nStage: 3\nTips:\nText: \"dup\"\nEnd:\nStageEnd:\n");
    StageTipManager manager = {};
    assert(Parse(&manager, path, 0) == 0);
    assert(CountChain(manager, 3) == 1 && CountChain(manager, 11) == 1);
    StageTip* tip = FirstTip(manager, 3);
    StageTip* dup = FirstTip(manager, 11);
    assert(std::strcmp(tip->name, "dup") == 0);
    assert(std::strcmp(dup->name, "dup") == 0);
    assert(dup->node.owner == dup);  // copied record re-self-links its node
    FreeChains(&manager);
    std::free(path);
}

void TestVersionMismatchWipes() {
    char* path = WriteTips(
        "Stage: 1\nTips:\nText: \"doomed\"\nEnd:\nStageEnd:\n"
        "Version: 1.0\n");
    StageTipManager manager = {};
    assert(Parse(&manager, path, 1) == 0);
    assert(CountChain(manager, 1) == 0);  // wiped by the bad version line
    // The manager is reusable after the wipe.
    char* good = WriteTips("Version: 0.0\nStage: 1\nTips:\nEnd:\nStageEnd:\n");
    assert(Parse(&manager, good, 1) == 0);
    assert(CountChain(manager, 1) == 1);
    FreeChains(&manager);
    std::free(path);
    std::free(good);
}

void TestStageBoundsAndCap() {
    char* path = WriteTips(
        "Version: 0.0\n"
        "Stage: 0\nTips:\nEnd:\n"
        "Stage: 8\nTips:\nEnd:\n"
        "Stage: 7\nTips:\nEnd:\nStageEnd:\n");
    StageTipManager manager = {};
    assert(Parse(&manager, path, 1) == 0);
    assert(CountChain(manager, 7) == 1);
    FreeChains(&manager);
    std::free(path);

    // 256 tips under one stage: the 255-count cap drops the rest and the
    // stage goes inactive.
    std::string many = "Version: 0.0\nStage: 1\n";
    for (int i = 0; i < 256; ++i)
        many += "Tips:\nPos: 1,2\nEnd:\n";
    many += "StageEnd:\n";
    path = WriteTips(many.c_str());
    StageTipManager capped = {};
    assert(Parse(&capped, path, 1) == 0);
    assert(CountChain(capped, 1) == 255);
    FreeChains(&capped);
    std::free(path);
}

void TestLineHandling() {
    char* path = WriteTips(
        "# leading comment\n"
        "\n"
        "Version: 0.0\r\n"
        "Stage: 1\r\n"
        "Tips:\r\n"
        "Text: \"x\" # trailing comment\n"
        "End:\n");
    StageTipManager manager = {};
    assert(Parse(&manager, path, 1) == 0);
    StageTip* tip = FirstTip(manager, 1);
    assert(tip != 0 && std::strcmp(tip->name, "x") == 0);
    FreeChains(&manager);
    std::free(path);
}

void TestTextWithoutClose() {
    // A Text line without a closing quote aborts the tip's property lines;
    // the partially parsed record is still inserted.
    char* path = WriteTips(
        "Version: 0.0\nStage: 1\nTips:\nText: \"unclosed\nPos: 5,6\nEnd:\n");
    StageTipManager manager = {};
    assert(Parse(&manager, path, 1) == 0);
    StageTip* tip = FirstTip(manager, 1);
    assert(tip != 0 && tip->x == 0.0f && tip->y == 0.0f &&
           tip->name[0] == 0);
    FreeChains(&manager);
    std::free(path);
}

void TestScaleClampAndUnknownKeys() {
    char* path = WriteTips(
        "Version: 0.0\n"
        "Stage: 1\n"
        "Tips:\n"
        "Scale: 9\n"
        "Pos: 7\n"
        "Bogus: 1\n"
        "End:\n"
        "Tips:\n"
        "Scale: -9\n"
        "End:\n");
    StageTipManager manager = {};
    assert(Parse(&manager, path, 1) == 0);
    StageTip* tip = FirstTip(manager, 1);
    assert(tip->scale == 4.0f && tip->x == 0.0f);
    assert(tip->node.next != 0 && tip->node.next->owner->scale == -4.0f);
    FreeChains(&manager);
    std::free(path);
}

void TestMissingFileAndBareVersion() {
    StageTipManager manager = {};
    assert(Parse(&manager, "/tmp/th10-tips-does-not-exist-4242", 1) == -1);
    char* path = WriteTips("Version: 0.0\n");
    assert(Parse(&manager, path, 1) == 0);
    assert(CountChain(manager, 1) == 0);
    std::free(path);
}

}  // namespace

int main() {
    TestFullRecord();
    TestDuplicate();
    TestVersionMismatchWipes();
    TestStageBoundsAndCap();
    TestLineHandling();
    TestTextWithoutClose();
    TestScaleClampAndUnknownKeys();
    TestMissingFileAndBareVersion();
    std::cout << "STAGE_TIP_PARSER_TESTS_PASS\n";
    return 0;
}
