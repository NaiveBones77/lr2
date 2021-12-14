#include "Timer.h"
#define TIMERHPP
#include <chrono>
#include <thread>
#include <functional>

///ÂÑÅÌ ÏÐÈÂÅÒ
///ÂÑÅÌ ÏÐÈÂÅÒ
/// ///ÂÑÅÌ ÏÐÈÂÅÒ
/// ///ÂÑÅÌ ÏÐÈÂÅÒ
///ÂÑÅÌ ÏÐÈÂÅÒ
///ÂÑÅÌ ÏÐÈÂÅÒ
/// ///ÂÑÅÌ ÏÐÈÂÅÒ
/// ///ÂÑÅÌ ÏÐÈÂÅÒ
void Timer::add(std::chrono::milliseconds delay, std::function<void()> callback, bool asynchronous = true)
{
		if (asynchronous) {
			std::thread([=]() {
				while (1) {
					std::this_thread::sleep_for(std::chrono::milliseconds(delay));
					callback();
				}
				}).detach();
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			callback();
		}
}


void Timer::add(std::chrono::microseconds delay, std::function<void()> callback, bool asynchronous = true)
{
		if (asynchronous) {
			std::thread([=]() {
				while (1) {
					std::this_thread::sleep_for(std::chrono::microseconds(delay));
					callback();
				}
				}).detach();
		}
		else {
			std::this_thread::sleep_for(std::chrono::microseconds(delay));
			callback();
		}
}