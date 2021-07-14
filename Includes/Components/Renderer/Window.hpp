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
    //! \brief Constructor with window creation settings
    //! \param width screen width of the generated window
    //! \param height screen height of the generated window
    //! \param title screen title of the generated window
    Window(int width, int height, const std::string &title);

    //! Default destructr
    ~Window();

    //! \brief Initialize vulkan window with given configuration
    //! \return whether if window creation is successful or not
    bool Initialize(int width, int height, const std::string &title);

    //! Setup given window surface ptr with given vulkan instance
    void CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    //! Return whether this window should close because of program closed
    bool WindowShouldClose();

    //! Process events in the event queue. This call will cause the window
    //! and input callbacks associated with those events to be called
    void PollEvents();

    //! Return generated window screen size
    inline VkExtent2D GetScreenSize() const
    {
        return _screenSize;
    }

    //! Return generated window screen title
    inline std::string GetWindowTitle() const
    {
        return _title;
    }

 protected:
    VkExtent2D _screenSize{ 0, 0 };
    GLFWwindow *_window = nullptr;
    std::string _title;

 private:
};
};  // namespace Renderer

#endif  //! WINDOW_HPP