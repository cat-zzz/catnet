/**************************
* @file: test_log.cpp
* @description: 
* @date: 2024/11/25 19:34
* @update: 2024/11/25 19:34
* @author: GQL
* @email: babygql@qq.com
**************************/

#include <iostream>

#include"../src/log2/log.h"

// std::ostream &operator<<(std::ostream & lhs, const catnet::Logger & rhs) {
//     lhs<<"logger";
//     return lhs;
// }

int main() {
	catnet::Logger::ptr logger(new catnet::Logger("ROOT"));
	logger->setLevel(catnet::LogLevel::DEBUG);
	CATNET_LOG_INFO(logger) << "Hello World!";
	CATNET_LOG_DEBUG(logger) << "1111111111";
	CATNET_LOG_ERROR(logger) << "2222222222";
	CATNET_LOG_ERROR(logger) << "3333333333";
	CATNET_LOG_ERROR(logger) << "44444444444";
	return 0;
}
