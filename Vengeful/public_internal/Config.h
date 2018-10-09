#pragma once
#include "JSON.h"
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <vector>
#include <algorithm>
#include <memory>
namespace Config
{
	void Load(std::string path);
	void Save(std::string path);
}