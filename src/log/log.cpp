/**************************
* @file: log.cpp
* @description: 
* @date: 2024/11/23 21:07
* @update: 2024/11/23 21:07
* @author: GQL
* @email: babygql@qq.com
**************************/
#include "log.h"

namespace catnet {

    Logger::Logger(const std::string &name) : m_name(name) {
    }

    void Logger::addAppender(LogAppender::ptr appender) {
        m_appender_list.push_back(appender);
    }

    void Logger::delAppender(LogAppender::ptr appender) {
        for (auto it = m_appender_list.begin(); it != m_appender_list.end(); ++it) {
            if (*it == appender) {
                m_appender_list.erase(it);
                break;
            }
        }
    }

    void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
        // 只输出日志级别大于等于当前level的日志
        if (level >= m_level) {
            for (auto &i: m_appender_list) {
                i->log(level, event);
            }
        }
    }

    void Logger::debug(LogEvent::ptr event) {
        log(LogLevel::DEBUG, event);
    }

    void Logger::info(LogEvent::ptr event) {

    }

    void Logger::warn(LogEvent::ptr event) {

    }

    void Logger::error(LogEvent::ptr event) {

    }

    void Logger::fatal(LogEvent::ptr event) {

    }

    FileLogAppender::FileLogAppender(const std::string &filename) : m_filename(filename) {
    }

    void FileLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
        LogAppender::log(level, event);
        if (level >= m_level) {
            m_filestream << m_formatter->format(event);
        }
    }

    // 重新打开文件，如果文件已经打开，先关闭再打开文件
    bool FileLogAppender::reopen() {
        if (m_filestream) {
            m_filestream.close();
        }
        m_filestream.open(m_filename);
        return !!m_filestream;  // !!实现转为0或1
    }

    void StdoutLogAppender::log(LogLevel::Level level, LogEvent::ptr event) {
        LogAppender::log(level, event);
        if (level >= m_level) {
            std::cout << m_formatter->format(event);
        }
    }

    LogFormatter::LogFormatter(const std::string &pattern) : m_pattern(pattern) {
    }

    std::string LogFormatter::format(LogLevel::Level level, LogEvent::ptr event) {
        std::stringstream ss;
        for (auto &i: m_items) {
            i->format(ss, level, event);
        }
        return ss.str();
    }

    // todo 这个函数感觉还有优化的地方
    void LogFormatter::init() {
        // tuple: str, format, type
        std::vector<std::tuple<std::string, std::string, int>> vec;
        std::string normal_str;
        for (size_t i = 0; i < m_pattern.size(); ++i) {
            if (m_pattern[i] != '%') {
                normal_str.append(1, m_pattern[i]);
                continue;
            }
            if ((i + 1) < m_pattern.size()) {
                if (m_pattern[i + 1] == '%') {
                    normal_str.append(1, '%');
                    continue;
                }
            }
            size_t n = i + 1;
            int fmt_status = 0;
            size_t fmt_begin = 0;

            std::string str;
            std::string fmt;
            while (n < m_pattern.size()) {
                if (isspace(m_pattern[n])) {
                    break;
                }
                if (fmt_status == 0) {
                    if (m_pattern[n] == '(') {
                        str = m_pattern.substr(i + 1, n - i);
                        fmt_status = 1;
                        ++n;
                        fmt_begin = n;
                        continue;
                    }
                }
                if (fmt_status == 1) {
                    if (m_pattern[n] == ')') {
                        fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                        fmt_status = 2;
                        break;
                    }
                }
            }
            if (fmt_status == 0) {
                if (!normal_str.empty()) {
                    vec.push_back(std::make_tuple(normal_str, "", 0));
                }
                str = m_pattern.substr(i + 1, n - i - 1);
                vec.push_back(std::make_tuple(str, fmt, 1));
                i = n;
            } else if (fmt_status == 1) {
                std::cout << "pattern parse error:" << m_pattern << " - " << m_pattern.substr(i) << std::endl;
                vec.push_back(std::make_tuple("<pattern_error>", fmt, 0));

            } else if (fmt_status == 2) {
                vec.push_back(std::make_tuple(str, fmt, 1));
                i = n;
            }
        }
        if (!normal_str.empty()) {
            vec.push_back(std::make_tuple(normal_str, "", 0));
        }
        /*
         * %m: 消息体
         * %p: level
         * %r: 启动后的时间
         * %c: 日志名称
         * %t: 线程id
         * %n: 回车换行
         * %d: 时间
         * %f: 文件名
         * %l: 行号
         */
    }


    const char *LogLevel::toString(LogLevel::Level level) {
        switch (level) {
#define XX(name) \
        case LogLevel::name: \
            return #name;    \
            break;
            XX(DEBUG);
            XX(INFO);
            XX(WARN);
            XX(ERROR);
            XX(FATAL);
            default:
                return "UNKNOWN";
        }
        return "UNKNOWN";
    }

    class MessageFormatItem : public LogFormatter::FormatItem {
    public:
        void format(std::ostream &os, LogLevel::Level level, LogEvent::ptr event) override {
            os << event->getMContent();
        }
    };

    class LevelFormatItem:public LogFormatter::FormatItem {
    public:
        void format(std::ostream &os, LogEvent::ptr event) override {
            os<<LogLevel::toString()
        }
    };
}

