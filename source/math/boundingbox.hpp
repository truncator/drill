#pragma once

#include "precompiled.hpp"

struct BoundingBox
{
	glm::vec3 m_top_left;
	glm::vec3 m_size;

	BoundingBox(glm::vec3 top_left, glm::vec3 size) :
		m_top_left(top_left), m_size(size)
	{
	}

	bool PointInside(const glm::vec2& point) const
	{
		if (point.x > m_top_left.x && point.x < m_top_left.x + m_size.x)
		{
			if (point.y > m_top_left.y && point.y < m_top_left.y + m_size.y)
				return true;
		}

		return false;
	}
};
