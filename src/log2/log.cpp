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
	m_stream.str("");	// 清空输出流中的内容，防止重复输出
}
}
