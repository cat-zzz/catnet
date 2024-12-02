/**************************
* @file: env.cpp
* @description: 
* @date: 2024/11/30 14:27
* @update: 2024/11/30 14:27
* @author: GQL
* @email: babygql@qq.com
**************************/
#include <cstring>
#include <cstdlib>
#include "env.h"

bool catnet::Env::init(int argc, char **argv) {

    /*
     * 参数格式: -参数名 参数值
     * 参数值可以为空，参数名和参数值都是用string存储
     * 正确示例 ./bin/test_env -p 123 -l
     * 错误示例1（参数名前必须有'-'） ./bin/test_env p 123
     * 错误示例2（不能只有参数值，没有参数名） ./bin/test_env 123
     */
    const char *cur_key = nullptr;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {   // 参数名
            if (strlen(argv[i]) > 1) {
                if (cur_key) {
                    add(cur_key, "");
                }
                cur_key = argv[i] + 1;
            } else {
                return false;
            }
        } else {
            if (cur_key) {
                add(cur_key, argv[i]);
                cur_key = nullptr;
            } else {
                return false;
            }
        }
    }
    if (cur_key) {
        add(cur_key, "");
    }
    return true;
}

void catnet::Env::add(const std::string& key, const std::string& val) {
    m_args[key] = val;
}

void catnet::Env::del(const std::string& key) {
    m_args.erase(key);
}

bool catnet::Env::has(const std::string& key) {
    auto it = m_args.find(key);
    return it != m_args.end();
}

std::string catnet::Env::get(const std::string& key, const std::string& default_val) {
    auto it = m_args.find(key);
    return it != m_args.end() ? it->second : default_val;
}

bool catnet::Env::setEnv(const std::string& key, const std::string& val) {
    return !setenv(key.c_str(), val.c_str(), 1);
}

std::string catnet::Env::getEnv(const std::string& key, const std::string& default_val) {
    const char *v = getenv(key.c_str());
    if (v == nullptr) {
        return default_val;
    }
    return v;   // 在返回时会将v（char*）隐式转换为std::string类型
}

