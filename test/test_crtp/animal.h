/**
 * @file: animal.h
 * @description: 
 * @date: 2024/12/9 22:25
 * @update: 2024/12/9 22:25
 * @author: GQL
 * @email: babygql@qq.com
 */

#ifndef CATNET_ANIMAL_H
#define CATNET_ANIMAL_H
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <functional>

// 基类 Animal
class Animal {
public:
    virtual ~Animal() = default;

    virtual void speak() const = 0;

    // 工厂函数类型
    using Creator = std::function<std::unique_ptr<Animal>()>;

    // 静态方法：根据类名创建对象
    static std::unique_ptr<Animal> create(const std::string& className) {
        auto it = getRegistry().find(className);
        if (it != getRegistry().end()) {
            return it->second();  // 调用工厂函数创建对象
        }
        std::cerr << "Class not found: " << className << std::endl;
        return nullptr;
    }

    // 静态方法：获取所有注册的类名
    static void listRegisteredClasses() {
        for (const auto& entry : getRegistry()) {
            std::cout << entry.first << std::endl;
        }
    }

protected:
    // 静态方法：注册子类的工厂函数
    static void registerClass(const std::string& className, Creator creator) {
        getRegistry()[className] = creator;
    }

private:
    // 获取注册表
    static std::unordered_map<std::string, Creator>& getRegistry() {
        static std::unordered_map<std::string, Creator> registry;
        return registry;
    }
};

// 模板类，用于自动注册子类
template<typename Derived>
class AnimalRegistrar : public Animal {
public:
    // 静态方法：显式触发注册
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

// 全局函数：显式触发所有子类注册
inline void initializeAnimalRegistry() {
    Dog::ensureRegistered();
    Cat::ensureRegistered();
    Bird::ensureRegistered();
}

#endif //CATNET_ANIMAL_H
