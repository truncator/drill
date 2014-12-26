#include "random.hpp"

int Random::Int(int min, int max)
{
	std::uniform_int_distribution<> dis(min, max);
	return dis(g_gen);
}

float Random::Float()
{
	std::uniform_real_distribution<> dis(0, 1);
	return dis(g_gen);
}

float Random::Float(float min, float max)
{
	return min + Random::Float() * (max - min);
}

void Random::Step(glm::vec2& position, const glm::vec2& min, const glm::vec2& max, int& last_direction)
{
	// Step in a random direction.
	int direction = Random::Int(0, 3);

	// Force a different direction each step.
	while (direction == last_direction)
		direction = Random::Int(0, 3);

	if (direction == 0)
	{
		if (position.x < max.x - 1)
			position.x++;
		else
			position.x--;
	}
	else if (direction == 1)
	{
		if (position.y < max.y - 1)
			position.y++;
		else
			position.y--;
	}
	else if (direction == 2)
	{
		if (position.x > min.x)
			position.x--;
		else
			position.x++;
	}
	else if (direction == 3)
	{
		if (position.y > min.y)
			position.y--;
		else
			position.y++;
	}

	last_direction = direction;
}
