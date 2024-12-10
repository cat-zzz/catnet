/**
 * @file: animal2.h
 * @description: 
 * @date: 2024/12/10 15:20
 * @update: 2024/12/10 15:20
 * @author: GQL
 * @email: babygql@qq.com
 */

#ifndef ANIMAL2_H
#define ANIMAL2_H
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

template<typename Derived>
class AnimalRegistrar;

// 子类 Dog
class Dog : public AnimalRegistrar<Dog> {
public:
    static std::string getClassName() { return "Dog"; }

    void speak() const override {
        std::cout << "Woof!" << std::endl;
    }
};

// 子类 Cat
class Cat : public AnimalRegistrar<Cat> {
public:
    static std::string getClassName() { return "Cat"; }

    void speak() const override {
        std::cout << "Meow!" << std::endl;
    }
};

// 子类 Bird
class Bird : public AnimalRegistrar<Bird> {
public:
    static std::string getClassName() { return "Bird"; }

    void speak() const override {
        std::cout << "Chirp!" << std::endl;
    }
};
// 基类 Animal
class Animal {
public:
    virtual ~Animal() = default;

    virtual void speak() const = 0;  // 每个动物的发声行为

    // 静态工厂方法：根据类名创建实例
    static std::unique_ptr<Animal> create(const std::string& className) {
        auto it = getRegistry().find(className);
        if (it != getRegistry().end()) {
            return it->second();  // 调用工厂函数创建对象
        }
        std::cerr << "Class not found: " << className << std::endl;
        return nullptr;
    }

    // 静态方法：列出所有注册的类名
    static void listRegisteredClasses() {
        for (const auto& entry : getRegistry()) {
            std::cout << entry.first << std::endl;
        }
    }

protected:
    // 注册子类工厂函数
    static void registerClass(const std::string& className, std::function<std::unique_ptr<Animal>()> creator) {
        getRegistry()[className] = creator;
    }

private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Animal>()>>& getRegistry() {
        static std::unordered_map<std::string, std::function<std::unique_ptr<Animal>()>> registry;
        return registry;
    }
};

// 模板类：自动注册子类
template<typename Derived>
class AnimalRegistrar : public Animal {
public:
    // 静态方法，确保注册
    static void ensureRegistered() {
        static bool registered = []() {
            Animal::registerClass(Derived::getClassName(), []() -> std::unique_ptr<Animal> {
                return std::make_unique<Derived>();
            });
            return true;
        }();
    }

protected:
    AnimalRegistrar() = default;
};

#endif //ANIMAL2_H
