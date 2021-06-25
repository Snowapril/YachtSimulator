#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vulkan/vulkan.h>

struct GLFWwindow;

namespace Renderer
{
class Window
{
 public:
    //! Default constructor
    Window();

    //! Constructor with window creation settings
    Window(int width, int height, const char* title);

    //! Default destructr
    ~Window();

    //! \brief Initialize vulkan window with given configuration
    //! \param width screen width of the generated window
    //! \param height screen height of the generated window
    //! \param title screen title of the generated window
    //! \return whether if window creation is successful or not
    bool Initialize(int width, int height, const char* title);

    //! \brief Return generated window screen size
    VkExtent2D GetScreenSize() const;

 protected:
    VkExtent2D _screenSize{ 0, 0 };
    GLFWwindow* _window = nullptr;
 private:
};
};  // namespace Renderer

#endif  //! WINDOW_HPP