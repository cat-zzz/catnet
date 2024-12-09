/**
 * @file: log.h
 * @description:
 * @date: 2024/11/28 15:40
 * @update: 2024/11/28 15:40
 * @author: GQL
 * @email: babygql@qq.com
 */

#ifndef LOG_H
#define LOG_H

#include <memory>
#include <string>
#include <sstream>

#define CATNET_LOG_LEVEL(logger, level) \
    if(level>=logger->getLevel()) catnet::LogWrap(logger).getLogger()->getStream()

#define CATNET_LOG_DEBUG(logger) CATNET_LOG_LEVEL(logger,catnet::LogLevel::DEBUG)
#define CATNET_LOG_INFO(logger) CATNET_LOG_LEVEL(logger,catnet::LogLevel::INFO)
#define CATNET_LOG_WARN(logger) CATNET_LOG_LEVEL(logger,catnet::LogLevel::WARN)
#define CATNET_LOG_ERROR(logger) CATNET_LOG_LEVEL(logger,catnet::LogLevel::ERROR)
#define CATNET_LOG_FATAL(logger) CATNET_LOG_LEVEL(logger,catnet::LogLevel::FATAL)

namespace catnet {
class LogLevel {
public:
    enum Level {
        DEBUG, INFO, WARN, ERROR, FATAL, UNKNOWN
    };
    
    /**
    * 返回值为char*而不是std::string，因为printf()的形参%s为char*类型
    */
    static const char *toString(Level level);
};

class LogEvent {
public:
    LogEvent(const char *mFile, int32_t mLine, int32_t mElapse, int32_t mThreadId, int32_t mFiberId,
             uint64_t mTimestamp, LogLevel::Level mLevel, std::stringstream& mContent)
            : m_file(mFile), m_line(mLine), m_elapse(mElapse),
              m_thread_id(mThreadId), m_fiber_id(mFiberId),
              m_timestamp(mTimestamp), m_level(mLevel), m_content(mContent) {}
    
    const char *getFile() const {
        return m_file;
    }
    
    int32_t getLine() const {
        return m_line;
    }
    
    int32_t getElapse() const {
        return m_elapse;
    }
    
    int32_t getThreadId() const {
        return m_thread_id;
    }
    
    int32_t getFiberId() const {
        return m_fiber_id;
    }
    
    uint64_t getTimestamp() const {
        return m_timestamp;
    }
    
    LogLevel::Level getLevel() const {
        return m_level;
    }
    
    std::stringstream& getContent() const {
        return m_content;
    }

private:
    const char *m_file = nullptr;
    int32_t m_line = 0;
    int32_t m_elapse = 0;     // 程序从启动开始到现在的毫秒数
    int32_t m_thread_id = 0;
    int32_t m_fiber_id = 0;
    uint64_t m_timestamp = 0;
    LogLevel::Level m_level;
    std::stringstream& m_content;
};

class FormatItem {
public:
    typedef std::shared_ptr<FormatItem> ptr;
    
    virtual ~FormatItem() = default;

protected:
    std::string m_format;
};

class MessageFormatItem : public FormatItem {
void func(){
    m_format;
}
};

class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    
    explicit LogFormatter(const std::string& format_str) : m_format_str(format_str) {}
    
    void pattern(const std::string& format_str = "");

private:
    std::string m_format_str;  // 格式化字符串
};

class LogAppender {

};

class StdoutLogAppender : LogAppender {

};

class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;
    
    explicit Logger(std::string name) : m_name(std::move(name)), m_level(LogLevel::Level::INFO) {
    }
    
    ~Logger() = default;
    
    [[nodiscard]] const std::string& getName() const { return m_name; }
    
    [[nodiscard]] LogLevel::Level getLevel() const { return m_level; }
    
    void setLevel(const LogLevel::Level level) { m_level = level; }
    
    [[nodiscard]] std::stringstream& getStream() {
        return m_stream;
    }
    
    void log();

private:
    std::string m_name;
    LogLevel::Level m_level;
    std::stringstream m_stream;
};

class LogWrap {
public:
    explicit LogWrap(Logger::ptr& logger)
            : m_logger(logger) {
    }
    
    ~LogWrap() {
        m_logger->log();
    }
    
    [[nodiscard]] Logger::ptr getLogger() const {
        return m_logger;
    }

private:
    Logger::ptr m_logger;
};

}// namespace catnet

#endif// LOG_H
