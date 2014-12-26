#pragma once

#include "precompiled.hpp"

namespace Random
{
	int Int();
	int Int(int min, int max);

	float Float();
	float Float(float min, float max);

	void Step(glm::vec2& position, const glm::vec2& min, const glm::vec2& max, int& last_direction);
}


static std::random_device g_rd;
static std::mt19937 g_gen(g_rd());
