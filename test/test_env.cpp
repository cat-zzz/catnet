/**************************
* @file: test_env.cpp
* @description: 
* @date: 2024/11/30 14:19
* @update: 2024/11/30 14:19
* @author: GQL
* @email: babygql@qq.com
**************************/
#include "../src/env/env.h"
#include <iostream>
int main(int argc, char** argv) {
    std::cout<<"Hello test_env"<<std::endl;
    catnet::Env env;
    env.init(argc, argv);
    std::cout << env.get("p") << std::endl;
    return 0;
}