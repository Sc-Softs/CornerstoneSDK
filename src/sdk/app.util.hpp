#include "app.hpp"
#include <functional>

template <typename FuncT = std::function<void(void)>>
inline FuncT* _f(Json api, const char* name)
{
    return (FuncT*)((intptr_t)api[name]);
}
