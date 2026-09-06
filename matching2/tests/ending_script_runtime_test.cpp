#include "th10/game/event_script_runtime.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace th10::event_script;

static void CountEvent(void* context, int, const EndingCommand&) {
    ++*static_cast<int*>(context);
}

static bool Confirm(void*) {
    return true;
}

struct LoaderContext {
    int calls{};
    std::string name;
};

static bool LoadNext(void* context, const std::string& name,
                     std::vector<EndingCommand>& stream) {
    auto* loader = static_cast<LoaderContext*>(context);
    ++loader->calls;
    loader->name = name;
    stream.push_back(EndingCommand{0, 9, {0x13579b}, {}});
    return true;
}

static bool FailLoad(void*, const std::string&,
                     std::vector<EndingCommand>&) {
    return false;
}

int main() {
    // Retail cases 5/6 leave the command pointer and frame clock unchanged
    // while a positive countdown remains.  The old host model dispatched the
    // event and advanced both immediately.
    {
        EndingState state;
        const std::vector<EndingCommand> script{
            {0, 5, {3}, {}},
            {0, 9, {0x2468ac}, {}},
        };
        int events = 0;
        EndingEdges edges{&events, CountEvent, nullptr, nullptr};
        assert(EndingScript_Update(state, script, 1.0f, edges) == 0);
        assert(state.cursor == 0 && state.time == 0 && state.wait_counter == 2);
        assert(events == 0 && state.color == 0xffffff);
        assert(EndingScript_Update(state, script, 1.0f, edges) == 0);
        assert(state.cursor == 0 && state.time == 0 && state.wait_counter == 1);
        assert(EndingScript_Update(state, script, 1.0f, edges) == 0);
        assert(state.cursor == 2 && state.time == 1 && state.wait_counter == 0);
        assert(events == 1 && state.color == 0x2468ac);
    }

    // Confirmation is the host representation of the permitted skip path;
    // it releases a still-positive wait in the same update.
    {
        EndingState state;
        const std::vector<EndingCommand> script{
            {0, 6, {60}, {}},
            {0, 9, {0xabcdef}, {}},
        };
        int events = 0;
        EndingEdges edges{&events, CountEvent, Confirm, nullptr};
        assert(EndingScript_Update(state, script, 1.0f, edges) == 0);
        assert(state.cursor == 2 && state.time == 1);
        assert(events == 1 && state.color == 0xabcdef);
    }

    // Retail stores elapsed time in a float and derives the integer command
    // time from it.  Fractional updates must retain the half-frame remainder.
    {
        EndingState state;
        const std::vector<EndingCommand> empty;
        for (int i = 0; i != 10; ++i)
            assert(EndingScript_Update(state, empty, 1.0f, {}) == 0);
        assert(state.time == 10 && state.fraction == 10.0f);
        assert(EndingScript_Update(state, empty, 0.5f, {}) == 0);
        assert(state.time == 10 && std::fabs(state.fraction - 10.5f) < 0.001f);
        assert(EndingScript_Update(state, empty, 0.5f, {}) == 0);
        assert(state.time == 11 && std::fabs(state.fraction - 11.0f) < 0.001f);
    }

    // Opcode 12 installs the stream returned by the loader and keeps using it
    // on subsequent calls.  It must not silently restart the old vector.
    {
        EndingState state;
        const std::vector<EndingCommand> old_script{
            {0, 12, {}, "ending/next"},
        };
        LoaderContext loader;
        EndingEdges edges{&loader, nullptr, nullptr, LoadNext};
        assert(EndingScript_Update(state, old_script, 1.0f, edges) == 0);
        assert(loader.calls == 1 && loader.name == "ending/next");
        assert(state.using_loaded_stream && state.cursor == 1);
        assert(state.time == 1 && state.color == 0x13579b);
        assert(EndingScript_Update(state, old_script, 1.0f, edges) == 0);
        assert(loader.calls == 1 && state.time == 2);
    }

    // A missing or failed loader follows retail's -1 load-failure result.
    {
        EndingState missing;
        const std::vector<EndingCommand> script{{0, 12, {}, "missing"}};
        assert(EndingScript_Update(missing, script, 1.0f, {}) == -1);
        assert(missing.cursor == 0 && missing.time == 0);
        EndingState failed;
        EndingEdges edges{nullptr, nullptr, nullptr, FailLoad};
        assert(EndingScript_Update(failed, script, 1.0f, edges) == -1);
        assert(failed.cursor == 0 && failed.time == 0);
    }

    std::cout << "ENDING_SCRIPT_RUNTIME_TESTS_PASS\n";
}
