/**************************
* @file: test_log.cpp
* @description: 
* @date: 2024/11/25 19:34
* @update: 2024/11/25 19:34
* @author: GQL
* @email: babygql@qq.com
**************************/

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include"../src/log2/log.h"

// std::ostream &operator<<(std::ostream & lhs, const catnet::Logger & rhs) {
//     lhs<<"logger";
//     return lhs;
// }

std::vector<std::string> split_string(const std::string& input_str) {
	std::vector<std::string> result;

	// 定义正则表达式：匹配转义项 % 后跟一个字母或 % 或普通字符项
	std::regex pattern(R"((%[a-zA-Z%])|(%[^a-zA-Z%])|([^%]+))");

	// 使用 std::sregex_iterator 查找所有匹配项
	auto begin = std::sregex_iterator(input_str.begin(), input_str.end(), pattern);
	auto end = std::sregex_iterator();

	// 遍历匹配结果，并将其存储在 result 中
	for (auto it = begin; it != end; ++it) {
		result.push_back(it->str());
	}
	std::cout << input_str;
	return result;
}

void test1() {
	catnet::Logger::ptr logger(new catnet::Logger("ROOT"));
	logger->setLevel(catnet::LogLevel::DEBUG);
	CATNET_LOG_INFO(logger) << "Hello World!";
	CATNET_LOG_DEBUG(logger) << "1111111111";
	CATNET_LOG_ERROR(logger) << "2222222222";
	CATNET_LOG_ERROR(logger) << "3333333333";
	CATNET_LOG_ERROR(logger) << "44444444444";
	const char *format_temp = "%d [%p] %f-%l %m %[ %%";
	catnet::LogFormatter::ptr formatter(new catnet::LogFormatter(format_temp));
	formatter->pattern();
	std::cout << "func test1() formatter:" << format_temp << std::endl;
	for (const auto& item: formatter->getItems()) {
		std::cout << *item << std::endl;
	}
}

void test2() {
	std::string input_str = "%d [%p] %f-%l %m %[ %%";

	std::vector<std::string> result = split_string(input_str);

	// 打印拆分结果
	for (const auto& item: result) {
		std::cout << "'" << item << "'" << std::endl;
	}
}

int main() {
	test1();
	//    test2();
	return 0;
}
