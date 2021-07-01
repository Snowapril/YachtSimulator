#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Renderer/Resource.hpp>
#include <Renderer/SwapChain.hpp>

namespace Renderer
{
class Renderer : public Resource
{
 public:
 protected:
    SwapChain _swapChain;

 private:
};
};  // namespace Renderer

#endif  //! RENDERER_HPP