#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include <string>

namespace Renderer
{
class Device;
class Window;
class Renderer;
}  // namespace Renderer

class Application
{
 public:
    //! Default constructor
    Application();

    //! Default destructor
    ~Application();

    //! Initialize entire components of vulkan rendering system
    bool Initialize(int width, int height, const std::string& title);

    //! Run main loop of the Yacht Application
    void Run();

 protected:
    std::shared_ptr<Renderer::Window> _window;
    std::shared_ptr<Renderer::Device> _device;
    std::shared_ptr<Renderer::Renderer> _renderer;

 private:
};

#endif  //! APPLICATION_HPP