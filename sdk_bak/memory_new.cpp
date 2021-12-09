#include <cstddef>

extern "C" void* AncPlatformMalloc(size_t size);
extern "C" void AncPlatformFree(void* ptr);

void* operator new(std::size_t size) {
    if (size == 0)
        size = 1;
    auto ret = AncPlatformMalloc(size);
    return ret;
}

void operator delete(void* ptr) noexcept {
    if (ptr)
        AncPlatformFree(ptr);
}

void* operator new[](size_t size) {
    return ::operator new(size);
}

void operator delete[](void* ptr) noexcept {
    ::operator delete(ptr);
}
