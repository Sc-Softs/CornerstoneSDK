#include "app.hpp"
namespace{

template<typename FuncT>
FuncT _f(const Json& api, const string& name)
{
    return (FuncT*)((intptr_t)api[name]);
}

}