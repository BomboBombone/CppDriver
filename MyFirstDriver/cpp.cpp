#include "cpp.h"

void* kMalloc(size_t size, POOL_TYPE pool_type)
{
    void* p;
#ifndef DRIVER_TAG
    p = ExAllocatePool(pool_type, size);
#else
    p = ExAllocatePoolWithTag(pool_type, size, DRIVER_TAG);
#endif

    if (p == nullptr) {
        DbgMsg("Failed to allocate %d bytes\n", (int)size);
    }
    return p;
}

void* kNew(void* p)
{
    return p;
}

void kDelete(void* pObj)
{
#ifndef DRIVER_TAG
    ExFreePool(pObj);
#else
    ExFreePoolWithTag(pObj, DRIVER_TAG);
#endif
}
