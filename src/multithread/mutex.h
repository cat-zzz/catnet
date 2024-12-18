/**
 * @file: mutex.h
 * @description: 
 * @date: 2024/12/18 14:47
 * @update: 2024/12/18 14:47
 * @author: GQL
 * @email: babygql@qq.com
 */

#ifndef MUTEX_H
#define MUTEX_H
#include <pthread.h>

#include "noncopyable.h"

template<class T>
class ScopedLockImpl {
public:
	/**
	 * 构造函数
	 * @param mutex Mutex类型
	 */
	explicit ScopedLockImpl(T& mutex): m_mutex(mutex) {
		m_mutex.lock();
		m_locked = true;
	}

	/**
	 * 析构函数，自动释放锁
	 */
	~ScopedLockImpl() {
		unlock();
	}

	/**
	 * 加锁
	 */
	void lock() {
		if (!m_locked) {
			m_mutex.lock();
			m_locked = true;
		}
	}

	/**
	 * 解锁
	 */
	void unlock() {
		if (m_locked) {
			m_mutex.unlock();
			m_locked = false;
		}
	}

private:
	T& m_mutex;
	bool m_locked = false;	// 是否已上锁
};

class Spinlock:catnet::Noncopyable {
public:
	typedef ScopedLockImpl<Spinlock> Lock;
	Spinlock() {
		pthread_spin_init(&m_mutex, 0);
	}
	~Spinlock() {
		pthread_spin_destroy(&m_mutex);
	}
	void lock() {
		pthread_spin_lock(&m_mutex);
	}
	void unlock() {
		pthread_spin_unlock(&m_mutex);
	}
private:
	pthread_spinlock_t m_mutex;
};
#endif //MUTEX_H
