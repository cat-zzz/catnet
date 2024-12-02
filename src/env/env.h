/**
 * @file: env.h
 * @description: 
 * @date: 2024/11/30 14:14
 * @update: 2024/11/30 14:14
 * @author: GQL
 * @email: babygql@qq.com
 */

#ifndef CATNET_ENV_H
#define CATNET_ENV_H

#include <string>
#include <map>

namespace catnet {
class Env {
public:
    bool init(int argc, char **argv);

    void add(const std::string& key, const std::string& val);

    void del(const std::string& key);

    bool has(const std::string& key);

    std::string get(const std::string& key, const std::string& default_val="");

    bool setEnv(const std::string& key, const std::string& val);

    std::string getEnv(const std::string& key, const std::string& default_val = "");


private:
    std::map<std::string, std::string> m_args;
};
}
#endif //CATNET_ENV_H
