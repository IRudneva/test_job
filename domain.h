#pragma once
#include <string>
#include <ctime>
#include <mutex>
#pragma warning(disable : 4996)

inline std::mutex Q_MUTEX;

static std::string getCurrentDatetime() {

	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();

	std::time_t t = std::chrono::system_clock::to_time_t(p);

	return std::string(std::ctime(&t), std::strlen(std::ctime(&t)) - 1);
}
