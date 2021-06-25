#include <Common/Logger.hpp>
#include <array>
#include <ctime>
#include <iomanip>
#include <mutex>

namespace Common
{
namespace
{
static std::ostream* g_loggingStream = &std::cout;
static Logger::Level g_loggingLevel = Logger::Level::Error;
static std::mutex loggingLock;
}  // anonymous namespace

//! \brief Create logging file with given path
void Logger::Init(Logger::Level level, std::ostream* stream)
{
    g_loggingStream = stream;
    g_loggingLevel = level;
}

Logger::Logger(Level level) : _level(level)
{
    //! Do nothing
}
Logger::~Logger()
{
    if (static_cast<int>(_level) >= static_cast<int>(g_loggingLevel))
    {
        std::lock_guard<std::mutex> lockGuard(loggingLock);
        *g_loggingStream << _buffer.str() << std::endl;
        g_loggingStream->flush();
    }
}
std::string Logger::GetHeader(Logger::Level level)
{
    std::time_t result = std::time(nullptr);
    std::stringstream sstr;
    sstr << std::put_time(std::localtime(&result), "%c") << ' '
         << LevelToString(level);
    return sstr.str();
}

std::string Logger::LevelToString(Logger::Level level)
{
    switch (level)
    {
        case Logger::Level::Verbose:
            return "Verbose";
            break;
        case Logger::Level::Debug:
            return "Debug";
            break;
        case Logger::Level::Warning:
            return "Warning";
            break;
        case Logger::Level::Error:
            return "Error";
            break;
        default:
            return "Unknown";
    }
}

};  // namespace Common