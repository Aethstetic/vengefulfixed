#pragma once
#include <memory>
class CGlow
{
public:
	void DoGlow();
};

extern std::unique_ptr<CGlow> glow;