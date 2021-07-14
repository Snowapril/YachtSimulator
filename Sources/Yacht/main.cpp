#include <Components/Common/Logger.hpp>
#include <Yacht/Application.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::ofstream file("YachtSimulator.log");
    Common::Logger::Init(Common::Logger::Level::Verbose, &file);

    Application application;
    if (!application.Initialize(1200, 900, "Test"))
        return 1;

    //! Enter the main loop of the application
    application.Run();

    file.close();
    return 0;
}
