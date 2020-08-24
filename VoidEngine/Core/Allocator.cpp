#include <VoidEngine/Core/Allocator.hpp>

namespace VOID_NS {
    u64 Allocator::m_AllocatedSize = 0;
};

#if defined(VOID_CUSTOM_ALLOC)
void *operator new(u64 size) {
    return Void::Allocator::Allocate(size);
}

void operator delete(void *mem) noexcept {
    Void::Allocator::Free(mem);
}
#endif /* VOID_CUSTOM_ALLOC */
