#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace Common
{
//! \brief Simple scope based logging system.
class Logger
{
 public:
    enum class Level
    {
        Verbose = 0,
        Debug = 1,
        Warning = 2,
        Error = 3,
    };
    //! \brief Create logging file with given path
    //! \param level Set global logging level
    //! \param stream Set global ostream for logging
    static void Init(Level level, std::ostream* stream);
    //! Constructor with Logging level
    explicit Logger(Level level);
    //! Default destructor
    ~Logger();
    //! Append meesages to buffer and then flushing them when destructor called
    template <typename Type>
    Logger& operator<<(Type&& message)
    {
        _buffer << std::forward<Type>(message);
        return *this;
    }
    //! Returns header string combined with localtime and logging level.
    static std::string GetHeader(Level level);

 private:
    //! Returns string matched with given logging level.
    static std::string LevelToString(Level level);

    std::stringstream _buffer;
    Level _level;
};
};  // namespace Common

#define LOG_VERBOSE                                                          \
    Common::Logger(Common::Logger::Level::Verbose)                           \
        << Common::Logger::GetHeader(Common::Logger::Level::Verbose) << " [" \
        << __FILE__ << "@" << __LINE__ << "] "
#define LOG_DEBUG                                                          \
    Common::Logger(Common::Logger::Level::Debug)                           \
        << Common::Logger::GetHeader(Common::Logger::Level::Debug) << " [" \
        << __FILE__ << "@" << __LINE__ << "] "
#define LOG_WARNING                                                          \
    Common::Logger(Common::Logger::Level::Warning)                           \
        << Common::Logger::GetHeader(Common::Logger::Level::Warning) << " [" \
        << __FILE__ << "@" << __LINE__ << "] "
#define LOG_ERROR                                                            \
    Common::Logger(Common::Logger::Level::Error)                             \
        << Common::Logger::GetHeader(Common::Logger::Level::Warning) << " [" \
        << __FILE__ << "@" << __LINE__ << "] "

#endif  //! LOGGER_HPP