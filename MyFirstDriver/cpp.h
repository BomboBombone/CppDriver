//This file contains all the useful definitions that you would normally find in usermode
//but reimplemented for kernel mode c++ :)
#pragma warning (disable: 4100)

#pragma once
#include <ntifs.h>

#include <Shared/macros.h>

//allocate new takes a pool type and returns a ptr to that mem, without calling the constructor of the obj tho
void* kMalloc(size_t size, POOL_TYPE pool_type = NonPagedPool);
//placement new takes an already allocated memory pool and calls the constructor of the obj
void* kNew(void* p);
void kDelete(void* pObj);
