#pragma once

#include <algorithm>
#include <vector>
#include <type_traits>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "./etypes.h"

struct earray_head{
    void * data;
    HANDLE heap;

    earray_head() noexcept
    {
        this->heap = GetProcessHeap();
        this->data = HeapAlloc(heap, HEAP_ZERO_MEMORY, 1);
        reinterpret_cast<std::uint8_t*>(this->data)[0] = 1;
    }

    ~earray_head() noexcept
    {
        HeapFree(this->heap, 0, this->data);
    }

    operator void**(){
        return &this->data;
    }
};

template<typename EType,typename CPPType>
size_t earray1d2vector(const earray_head& earr,::std::vector<CPPType>& out){
    auto srcptr = reinterpret_cast<eint*>(earr.data);
    auto dim = srcptr[0];
    if(dim != 1) return static_cast<size_t>(-1);
    auto size = srcptr[1];
    if constexpr (::std::is_compound<CPPType>::value){
        auto pptr = reinterpret_cast<EType**>(srcptr+2);
        out.clear();
        out.reserve(size);
        ::std::for_each(pptr, pptr + size,[&](auto ptr){
            out.emplace_back(*ptr);
        });
    }
    else{
        auto ptr = reinterpret_cast<EType*>(srcptr+2);
        out.clear();
        out.reserve(size);
        ::std::for_each(ptr, ptr + size,[&](auto val){
            out.emplace_back(val);
        });
    }
    return size;
}