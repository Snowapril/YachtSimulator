#include <Renderer/Resource.hpp>

namespace Renderer
{
Resource::Resource()
{
    //! Do nothing
}

Resource::~Resource()
{
    FlushDeletion();
}

void Resource::PushDeletionCall(DeletionType&& deleteCall)
{
    _deletionStack.emplace(std::move(deleteCall));
}

void Resource::FlushDeletion()
{
    while (_deletionStack.empty())
    {
        auto& deletionCall = _deletionStack.top();
        deletionCall();
        _deletionStack.pop();
    }
}

};  // namespace Renderer