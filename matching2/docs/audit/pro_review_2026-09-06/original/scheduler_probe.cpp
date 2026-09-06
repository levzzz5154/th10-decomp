
#include "th10/game/scheduler.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstddef>

unsigned int DAT_00492274 = 0;
unsigned char DAT_0049231c = 0;
extern "C" void* operator_new(unsigned int n) { return std::malloc(n); }
extern "C" void _free(void* p) { std::free(p); }
extern "C" void EnterCriticalSection(void*) {}
extern "C" void LeaveCriticalSection(void*) {}

struct Owner { int calls; int first_result; int later_result; int seven_calls; };
static int callback(void* p) {
    Owner* o = static_cast<Owner*>(p);
    ++o->calls;
    return o->calls == 1 ? o->first_result : o->later_result;
}
static int seven(void* p) {
    ++static_cast<Owner*>(p)->seven_calls;
    return 1;
}
struct Device {
    alignas(std::max_align_t) unsigned char bytes[256];
    unsigned char* base;
    explicit Device(unsigned offset) {
        std::memset(bytes, 0, sizeof(bytes));
        const std::size_t a = alignof(SchedulerNode);
        base = bytes + (a - (offset % a)) % a;
    }
};
static void setup(SchedulerCallback& c, Owner& owner, int flags = 2) {
    std::memset(&c, 0, sizeof(c));
    c.flags = flags;
    c.function = callback;
    c.onResultSeven = seven;
    c.owner = &owner;
    c.node.owner = &c;
}
static void chain(Device& d, unsigned offset, SchedulerCallback& a, SchedulerCallback* b = nullptr) {
    SchedulerNode* head = reinterpret_cast<SchedulerNode*>(d.base + offset);
    head->owner = nullptr;
    head->next = &a.node;
    head->previous = nullptr;
    a.node.previous = head;
    a.node.next = b ? &b->node : nullptr;
    if (b) { b->node.previous = &a.node; b->node.next = nullptr; }
}
int main(int argc, char** argv) {
    const char* mode = argc > 1 ? argv[1] : "controls";
    bool secondary = std::strstr(mode, "secondary") != nullptr;
    const unsigned offset = secondary ? 0x38u : 0x14u;
    Device d(offset);
    SchedulerCallback a{}, b{};
    Owner oa{0,1,1,0}, ob{0,1,1,0};
    setup(a,oa); setup(b,ob);
    if (std::strcmp(mode, "primary-null-tail") == 0 ||
        std::strcmp(mode, "secondary-null-tail") == 0) {
        a.function = nullptr;
        chain(d,offset,a);
    } else if (std::strcmp(mode, "primary-tail-removal") == 0 ||
               std::strcmp(mode, "secondary-tail-removal") == 0) {
        ob.first_result = ob.later_result = 0;
        chain(d,offset,a,&b);
    } else if (std::strcmp(mode, "primary-restart") == 0) {
        ob.first_result = 6;
        chain(d,offset,a,&b);
    } else if (std::strcmp(mode, "secondary-six") == 0) {
        oa.first_result = 6;
        chain(d,offset,a);
    } else if (std::strcmp(mode, "secondary-seven") == 0 ||
               std::strcmp(mode, "primary-seven-control") == 0) {
        oa.first_result = oa.later_result = 7;
        chain(d,offset,a);
    } else if (std::strcmp(mode, "remove-unowned") == 0) {
        chain(d,offset,a);
        Scheduler_Remove(&a,d.base);
        std::printf("{\"function_cleared\":%s,\"owner_preserved\":%s,\"unlinked\":%s}\n",
                    a.function == nullptr ? "true":"false",
                    a.owner == &oa ? "true":"false",
                    a.node.previous == nullptr && a.node.next == nullptr ? "true":"false");
        return 0;
    } else if (std::strcmp(mode, "repeat-two-control") == 0) {
        oa.first_result = 2;
        chain(d,offset,a);
    } else if (std::strcmp(mode, "inactive-control") == 0) {
        a.flags = 0;
        chain(d,offset,a);
    } else {
        chain(d,offset,a,&b);
    }
    int value = secondary ? Scheduler_RunSecondary(d.base) : Scheduler_RunPrimary(d.base);
    std::printf("{\"result\":%d,\"a_calls\":%d,\"b_calls\":%d,\"seven_calls\":%d,\"critical_depth\":%u}\n",
                value, oa.calls, ob.calls, oa.seven_calls+ob.seven_calls,
                static_cast<unsigned>(DAT_0049231c));
}
