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
	enum Level { DEBUG, INFO, WARN, ERROR, FATAL, UNKNOWN };

	/**
	* 返回值为char*而不是std::string，因为printf()的形参%s为char*
	*/
	static const char *toString(Level level);
};

class Logger {
public:
	typedef std::shared_ptr<Logger> ptr;

	explicit Logger(std::string name): m_name(std::move(name)), m_level(LogLevel::Level::INFO) {
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
