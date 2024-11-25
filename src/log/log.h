/**
 * @file: log.h
 * @description: 
 * @date: 2024/11/23 20:16
 * @update: 2024/11/23 20:16
 * @author: GQL
 * @email: babygql@qq.com
 */

#ifndef CATNET_LOG_H
#define CATNET_LOG_H

#include<string>
#include<cstdint>
#include<memory>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

namespace catnet {
    class LogEvent {
    public:
        typedef std::shared_ptr<LogEvent> ptr;

        LogEvent();

        const char *getMFile() const {
            return m_file;
        }

        int32_t getMLine() const {
            return m_line;
        }

        uint32_t getMElapse() const {
            return m_elapse;
        }

        uint32_t getMThreadId() const {
            return m_threadId;
        }

        uint32_t getMFiberId() const {
            return m_fiberId;
        }

        uint64_t getMTime() const {
            return m_time;
        }

        const std::string &getMContent() const {
            return m_content;
        }

    private:
        const char *m_file = nullptr;   // 文件名
        int32_t m_line = 0;             // 行号
        uint32_t m_elapse = 0;          // 程序开始运行到现在的毫秒数
        uint32_t m_threadId = 0;        // 线程id
        uint32_t m_fiberId = 0;         // 协程id
        uint64_t m_time = 0;            // 时间戳
        std::string m_content;
    };

    // 日志级别
    class LogLevel {
    public:
        enum Level {
            UNKNOWN=0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };

        static const char *toString(LogLevel::Level level);
    };

    // 日志格式器
    class LogFormatter {
    public:
        typedef std::shared_ptr<LogFormatter> ptr;

        LogFormatter(const std::string &pattern);

        std::string format(LogLevel::Level level, LogEvent::ptr event);

    public:
        class FormatItem {
        public:
            typedef std::shared_ptr<FormatItem> ptr;

            virtual ~FormatItem() {}

            virtual void format(std::ostream& os,LogLevel::Level level, LogEvent::ptr event) = 0;  // "=0"表示纯虚函数
        };

        void init();
    private:
        std::string m_pattern;
        std::vector<FormatItem::ptr> m_items;
    };

    // 日志输出地
    class LogAppender {
    public:
        typedef std::shared_ptr<LogAppender> ptr;

        virtual ~LogAppender() {}

        virtual void log(LogLevel::Level level, LogEvent::ptr event);

        void setFormatter(LogFormatter::ptr val) { m_formatter = val; }

        LogFormatter::ptr getFormatter() const { return m_formatter; }

    protected:
        LogLevel::Level m_level;
        LogFormatter::ptr m_formatter;
    };


    // 日志器
    class Logger {
    public:
        typedef std::shared_ptr<Logger> ptr;


        Logger(const std::string &name = "root");

        void log(LogLevel::Level level, LogEvent::ptr event);

        void debug(LogEvent::ptr event);

        void info(LogEvent::ptr event);

        void warn(LogEvent::ptr event);

        void error(LogEvent::ptr event);

        void fatal(LogEvent::ptr event);

        void addAppender(LogAppender::ptr appender);

        void delAppender(LogAppender::ptr appender);

        LogLevel::Level getLevel() const { return m_level; }

        void setLevel(LogLevel::Level val) { m_level = val; }

    private:
        std::string m_name;
        LogLevel::Level m_level;
        std::list<LogAppender::ptr> m_appender_list;   // Appender集合
    };

    // 输出到控制台的Appender
    class StdoutLogAppender : public LogAppender {
    public:
        typedef std::shared_ptr<StdoutLogAppender> ptr;

        void log(LogLevel::Level level, LogEvent::ptr event) override;  // override表示从父类继承出来的重写的实现
    private:
    };

    // 输出到文件的Appender
    class FileLogAppender : public LogAppender {
    public:
        typedef std::shared_ptr<FileLogAppender> ptr;

        FileLogAppender(const std::string &filename);

        void log(LogLevel::Level level, LogEvent::ptr event) override;

        bool reopen();  // 重新打开文件
    private:
        std::string m_filename;
        std::ofstream m_filestream;
    };
}
#endif //CATNET_LOG_H
