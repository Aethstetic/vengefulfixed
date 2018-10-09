#pragma once
#include <Windows.h>
#include <memory>
#include <vector>

class cutils {
public:
	std::uint8_t* PatternScan(void* module, const char* signature);
};

extern std::unique_ptr<cutils> utils;