#include <iostream>
#include <Components/Common/Logger.hpp>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::ofstream file("log.log");
    Common::Logger::Init(Common::Logger::Level::Verbose, &file);

    //! Logging test
    {
        LOG_VERBOSE << "Hello Yacht Simulator";
    }

    file.close();
    return 0;
}
