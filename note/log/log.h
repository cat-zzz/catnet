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
#include <functional>
#include <iostream>
#include <map>
#include <sstream>

namespace catnet {
	class Logger;

	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr;

		LogEvent(const char *file, int32_t line, uint32_t elapse,
			uint32_t thread_id, uint32_t fiber_id, uint64_t time);

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

		std::string getMContent() const {
			return m_content.str();
		}

	private:
		const char *m_file = nullptr;   // 文件名
		int32_t m_line = 0;             // 行号
		uint32_t m_elapse = 0;          // 程序开始运行到现在的毫秒数
		uint32_t m_threadId = 0;        // 线程id
		uint32_t m_fiberId = 0;         // 协程id
		uint64_t m_time = 0;            // 时间戳
		std::stringstream m_content;
	};

	// 日志级别
	class LogLevel {
	public:
		enum Level {
			UNKNOWN = 0,
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
		// todo 学习语法：shared_ptr, shared_ptr.reset()
		typedef std::shared_ptr<LogFormatter> ptr;

		LogFormatter(const std::string &pattern);

		std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

		class FormatItem {
		public:
			typedef std::shared_ptr<FormatItem> ptr;

			FormatItem(const std::string &fmt = "") {
			};

			virtual ~FormatItem() {
			}

			virtual void format(std::ostream &os, std::shared_ptr<Logger> logger, LogLevel::Level level,
								LogEvent::ptr event) = 0;  // "=0"表示纯虚函数
		};

		void init();

	private:
		std::string m_pattern;
		std::vector<FormatItem::ptr> m_items;
		bool m_error=false;
	};

	// 日志输出地
	class LogAppender {
	public:
		typedef std::shared_ptr<LogAppender> ptr;

		virtual ~LogAppender() {
		}

		virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) =0;

		void setFormatter(LogFormatter::ptr val) { m_formatter = val; }

		LogFormatter::ptr getFormatter() const { return m_formatter; }

	protected:
		LogLevel::Level m_level;
		LogFormatter::ptr m_formatter;
	};


	// 日志器
	class Logger : public std::enable_shared_from_this<Logger> {
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

		LogLevel::Level getMLevel() const { return m_level; }

		void setMLevel(LogLevel::Level val) { m_level = val; }

		std::string getMName() const {
			return m_name;
		}

	private:
		std::string m_name;         // 日志名称
		LogLevel::Level m_level;    // 日志级别
		std::list<LogAppender::ptr> m_appender_list;   // Appender集合
		LogFormatter::ptr m_formatter;
	};

	// 输出到控制台的Appender
	class StdoutLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<StdoutLogAppender> ptr;

		void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;  // override表示从父类继承出来的重写的实现
	};

	// 输出到文件的Appender
	class FileLogAppender : public LogAppender {
	public:
		typedef std::shared_ptr<FileLogAppender> ptr;

		FileLogAppender(const std::string &filename);

		void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;

		bool reopen();  // 重新打开文件
	private:
		std::string m_filename;
		std::ofstream m_filestream;
	};
}
#endif //CATNET_LOG_H
