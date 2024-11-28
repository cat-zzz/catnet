/**************************
* @file: test_log.cpp
* @description: 
* @date: 2024/11/25 19:34
* @update: 2024/11/25 19:34
* @author: GQL
* @email: babygql@qq.com
**************************/
#include <ctime>

#include"../src/log/log.h"
int main() {
    std::cout << "Hello Catnet!"<<std::endl;
    // todo 学习语法，通过shared_ptr创建示例
    catnet::Logger::ptr logger(new catnet::Logger);
    catnet::LogAppender::ptr appender=catnet::LogAppender::ptr(new catnet::StdoutLogAppender);

    logger->addAppender(appender);
    catnet::LogEvent::ptr event(new catnet::LogEvent(__FILE__, __LINE__, 0,1,2,time(nullptr)));
    logger->log(catnet::LogLevel::DEBUG, event);
    return 0;
}