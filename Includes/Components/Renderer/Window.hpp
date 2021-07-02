#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vulkan/vulkan.h>
#include <Components/Renderer/Resource.hpp>

struct GLFWwindow;

namespace Renderer
{
class Window : public Resource
{
 public:
    //! Default constructor
    Window();

    //! Constructor with window creation settings
    Window(int width, int height, const std::string &title);

    //! Default destructr
    ~Window();

    //! \brief Initialize vulkan window with given configuration
    //! \param width screen width of the generated window
    //! \param height screen height of the generated window
    //! \param title screen title of the generated window
    //! \return whether if window creation is successful or not
    bool Initialize(int width, int height, const std::string &title);

    //! Return generated window screen size
    VkExtent2D GetScreenSize() const;

    //! Return generated window screen title
    std::string GetWindowTitle() const;

    //! Setup given window surface ptr with given vulkan instance 
    bool CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

 protected:
    VkExtent2D _screenSize{ 0, 0 };
    GLFWwindow *_window = nullptr;
    std::string _title;

 private:
};
};  // namespace Renderer

#endif  //! WINDOW_HPP