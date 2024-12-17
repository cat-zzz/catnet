/**************************
* @file: log.cpp
* @description: 
* @date: 2024/11/28 16:30
* @update: 2024/11/28 16:30
* @author: GQL
* @email: babygql@qq.com
**************************/
#include "log.h"

#include <iostream>
#include <regex>

namespace catnet {
const char *LogLevel::toString(const Level level) {
	switch (level) {
#define XX(name) case name: return #name;
		XX(DEBUG);
		XX(INFO);
		XX(WARN);
		XX(ERROR);
		XX(FATAL);
#undef XX
		default:
			return "UNKNOWN LEVEL";
	}
}

void Logger::log() {
	std::cout << "[" << m_name << "]    "
			<< "[" << LogLevel::toString(m_level) << "]    "
			<< m_stream.str() << std::endl;
	m_stream.str("");    // 清空输出流中的内容，防止重复输出
}

// 属性
// log_appender_list: 日志输出地
// log_formatter: 日志格式
// log_level: 只输出级别大于等于log_level的日志
// 用到的参数
// log_event: 一种消费品，一个log_event对应一个日志，log_event带有日志级别

// 要完成的任务
// 将log_event按照log_formatter的格式输出到log_appender_list中的每个log_appender
/*
 * logger.setLevel(ERROR);
 * logger.debug("111"); // 只输出级别大于等于ERROR的日志，所以此时不会输出111
 * logger.error("222");
 */


void log(LogLevel, LogEvent) {
}

void debug(LogEvent) {
}

void LogFormatter::pattern(const std::string& format_str) {
	if (!format_str.empty()) {
		m_format_str = format_str;
	}
	// 定义正则表达式：匹配%及其之后的一个英文字母，或%及其之后任意一个字符，或其他子字符穿串
	// "%% %[ "将被划分为"%%"，" "，"%["，" "，而不是"%%"，" %[ "
	const std::regex pattern(R"((%[a-zA-Z%])|(%[^a-zA-Z%])|([^%]+))");
	// 使用 std::sregex_iterator 查找所有匹配项
	const auto begin = std::sregex_iterator(m_format_str.begin(), m_format_str.end(), pattern);
	const auto end = std::sregex_iterator();
	// 遍历匹配结果，并将其存储在m_items中
	for (auto it = begin; it != end; ++it) {
		// m_items.push_back(it->str());
		std::cout << it->str() << std::endl;
		// FormatItemFactory& format_item_factory = FormatItemFactory::getInstance();
		auto item = FormatItemFactory::create_format_item(it->str());
		m_items.push_back(item);
	}
}

FormatItemFactory& FormatItemFactory::getInstance() {
	static FormatItemFactory factory;
	return factory;
}

std::shared_ptr<FormatItem> FormatItemFactory::create_format_item(const std::string& format) {
	if (format == "%d") {
		return std::make_shared<DateTimeFormatItem>();
	}
	if (format == "%p") {
		return std::make_shared<LevelFormatItem>();
	}
	if (format == "%c") {
		return std::make_shared<LoggerNameFormatItem>();
	}
	if (format == "%m") {
		return std::make_shared<MessageFormatItem>();
	}
	// 如果不是上述的格式化项，就当作普通字符串处理
	return std::make_shared<StringFormatItem>(format);
}

std::ostream& operator<<(std::ostream & os, const FormatItem & item) {
	os<<typeid(item).name()<<"  "<<item.getFormat();
	return os;
}

}
