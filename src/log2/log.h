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

namespace catnet {
class LogLevel {
public:
	enum Level { DEBUG, INFO, WARN, ERROR, FATAL };
};

class Logger {
public:
	typedef std::shared_ptr<Logger> ptr;

	explicit Logger(const std::string& name = "UNKNOWN");

	~Logger();

	[[nodiscard]] const std::string& getName() const { return m_name; }

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
}// namespace catnet

#endif// LOG_H
