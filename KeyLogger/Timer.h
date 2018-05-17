#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>

class Timer {
	std::thread thr;
	bool alive = false;
	long callNumber = -1L;
	long repeat_count = -1L;
	std::chrono::milliseconds interval = std::chrono::milliseconds(0);
	std::function<void(void)> func = nullptr;

	void sleepAndRun() {
		std::this_thread::sleep_for(interval);
		if (alive)
			Function()();
	}

	void threadFunc() {
		if (callNumber == infinite)
			while (alive)
				sleepAndRun();
		else
			while (repeat_count--)
				sleepAndRun();
	}

public:
	static const long infinite = -1L;
	Timer() {

	}

	Timer(const std::function<void(void)> &f) : func(f) {

	}

	Timer(const std::function<void(void)> &f,
		const unsigned long &i,
		const long repeat = Timer::infinite): func(f), 
		interval(std::chrono::milliseconds(i)),
		callNumber(repeat) {
		
	}

	void start(bool async = true) {
		if (isAlive())
			return;
		alive = true;
		repeat_count = callNumber;
		if (async)
			thr = std::thread(&Timer::threadFunc, this);
		else
			this->threadFunc();
	}

	void stop() {
		alive = false;
		thr.join();
	}

	bool isAlive() const {
		return alive;
	}

	void repeatCount(const long r) {
		if (alive)
			return;
		callNumber = r;
	}

	void setFunction(const std::function<void(void)> &f) {
		func = f;
	}

	long getLeftCount() const { //how many iterations are left
		return repeat_count;
	}

	long repeatCount() const {
		return callNumber;
	}

	void setInterval(const unsigned long &i) {
		if (alive)
			return;
		interval = std::chrono::milliseconds(i);
	}

	unsigned long getInterval() const {
		return (unsigned long)interval.count();
	}

	const std::function<void(void)> &Function() const {
		return func;
	}
};

#endif