#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <functional>
#include <stack>

namespace Renderer
{
class Resource
{
 public:
    using DeletionType = std::function<void()>;
    //! Default constructor
    Resource();
    //! Default virtual destructr
    virtual ~Resource();
    //! Ban move, copy allocator and move, copy constructor
    Resource(const Resource&) = delete;
    Resource(Resource&&) = delete;
    Resource& operator=(const Resource&) = delete;
    Resource& operator=(Resource&&) = delete;
    //! Push the dealloc
    void PushDeletionCall(DeletionType&& deleteCall);
    //! Flush the deletion call in the stakc
    void FlushDeletion();

 protected:
 private:
    std::stack<DeletionType> _deletionStack;
};
};  // namespace Renderer

#endif  //! RESOURCE_HPP