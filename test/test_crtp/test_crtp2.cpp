/**************************
* @file: test_crtp2.cpp
* @description: 
* @date: 2024/12/10 15:35
* @update: 2024/12/10 15:35
* @author: GQL
* @email: babygql@qq.com
**************************/
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

    static std::unique_ptr<Animal> create(const std::string& className);
    static void listRegisteredClasses();

protected:
    static void registerClass(const std::string& className, std::function<std::unique_ptr<Animal>()> creator);

private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<Animal>()>>& getRegistry();
};

// 模板类：自动注册子类
template<typename Derived>
class AnimalRegistrar : public Animal {
public:
    // 静态变量，用于自动注册子类
    static bool registered;

    // 构造函数，触发注册
    AnimalRegistrar() {
        if (!registered) {
            Animal::registerClass(Derived::getClassName(), []() -> std::unique_ptr<Animal> {
                return std::make_unique<Derived>();
            });
            registered = true;  // 确保每个子类只注册一次
        }
    }
};

// 静态变量初始化，确保每个子类会自动注册
template<typename Derived>
bool AnimalRegistrar<Derived>::registered = false;

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

int main() {
    // 只要程序启动，Dog, Cat, Bird 会自动注册
    // 列出所有自动注册的类名
    std::cout << "Registered classes:" << std::endl;
    Animal::listRegisteredClasses();

    // 根据类名创建对象并调用其方法
    auto dog = Animal::create("Dog");
    auto cat = Animal::create("Cat");
    auto bird = Animal::create("Bird");

    if (dog) dog->speak();  // 输出：Woof!
    if (cat) cat->speak();  // 输出：Meow!
    if (bird) bird->speak(); // 输出：Chirp!

    return 0;
}
