#pragma once

#include "precompiled.hpp"

// Forward declarations.
class SpriteBatch;

//
// Text
//

namespace Text
{
	void DrawText(const std::string& text, int x, int y, SpriteBatch& sprite_batch);

	glm::vec4 GetCharUV(char c);
	glm::vec4 CalculateUV(int xi, int yi, int w, int h);
}
