/**************************
* @file: test_crtp.cpp
* @description: 
* @date: 2024/12/9 22:27
* @update: 2024/12/9 22:27
* @author: GQL
* @email: babygql@qq.com
**************************/
// #include "animal.h"
#include "animal2.h"

// int main() {
//     // 显式触发注册
//     // initializeAnimalRegistry();
//
//     // 列出所有自动注册的类名
//     std::cout << "Registered classes:" << std::endl;
//     Animal::listRegisteredClasses();
//
//     // 根据类名创建对象并调用其方法
//     auto dog = Animal::create("Dog");
//     auto cat = Animal::create("Cat");
//     auto bird = Animal::create("Bird");
//
//     if (dog) {
//         dog->speak();  // 输出：Woof!
//     }
//     if (cat) {
//         cat->speak();  // 输出：Meow!
//     }
//     if (bird) {
//         bird->speak(); // 输出：Chirp!
//     }
//
//     return 0;
// }
