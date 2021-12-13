#pragma once
#define TIMERHPP
#include <chrono>
#include <thread>
#include <functional>

class Timer {
public:
	Timer() {};
	void add(std::chrono::milliseconds delay, std::function<void()> callback, bool asynchronous = true);

	void add(std::chrono::microseconds delay, std::function<void()> callback, bool asynchronous = true);
};
