/**************************
* @file: log.cpp
* @description: 
* @date: 2024/11/28 16:30
* @update: 2024/11/28 16:30
* @author: GQL
* @email: babygql@qq.com
**************************/
#include "log.h"

namespace catnet {
Logger::Logger(const std::string &name): m_name(name), m_level(LogLevel::Level::INFO) {
}

Logger::~Logger() {
}
}
