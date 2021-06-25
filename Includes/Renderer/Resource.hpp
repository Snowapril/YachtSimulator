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