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
    Application() = default;

    /**
     * @brief Construct application instance with given config
     *
     * @param width screen width
     * @param height screen height
     * @param title application title
     */
    Application(int width, int height, const std::string& title);

    //! Default destructor
    ~Application();

    /**
     * @brief Initialize entire components of vulkan rendering system
     *
     * @param width screen width
     * @param height screen height
     * @param title application title
     */
    bool Initialize(int width, int height, const std::string& title);

    //! Run main loop of the Yacht Application
    void Run();

 private:
    std::shared_ptr<Renderer::Window> _window;
    std::shared_ptr<Renderer::Device> _device;
    std::shared_ptr<Renderer::Renderer> _renderer;
};

#endif  //! APPLICATION_HPP