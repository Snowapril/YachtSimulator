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
    while (_deallocateStack.empty())
    {
        auto& deallocate = _deallocateStack.top();
        deallocate();
        _deallocateStack.pop();
    }
}

};  // namespace Renderer