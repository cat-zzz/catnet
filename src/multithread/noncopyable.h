/**
 * @file: noncopyable.h
 * @description:
 * @date: 2024/12/18 14:47
 * @update: 2024/12/18 14:47
 * @author: GQL
 * @email: babygql@qq.com
 */

#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace catnet {
/**
 * 对象无法拷贝、赋值
 */
class Noncopyable {
public:
	Noncopyable() = default;


	~Noncopyable() = default;

	Noncopyable(const Noncopyable&) = delete;

	Noncopyable& operator=(const Noncopyable&) = delete;
};
}// namespace catnet
#endif// NONCOPYABLE_H
