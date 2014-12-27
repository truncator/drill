#include "text.hpp"

#include "spritebatch.hpp"

void Text::DrawText(const std::string& text, int x, int y, SpriteBatch& sprite_batch)
{
	int pen_x = x;

	for (int i = 0; i < text.size(); i++)
	{
		glm::vec4 uv = GetCharUV(text[i]);
		sprite_batch.DrawQuad(glm::vec2(pen_x, y), glm::vec2(64, 64), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), uv);

		pen_x += 64;
	}
}

glm::vec4 Text::GetCharUV(char c)
{
	if (c == ' ')
		return CalculateUV(26, 0, 8, 8);

	// Normalize char int, e.g. 'A':65 -> 'A':0.
	char normalized = toupper(c) - 65;
	return CalculateUV((int)normalized, 0, 8, 8);
}

glm::vec4 Text::CalculateUV(int xi, int yi, int w, int h)
{
	const int IMAGE_SIZE = 1024;

	float x = (float)(xi * w) / IMAGE_SIZE;
	float y = (float)(yi * h) / IMAGE_SIZE;
	float _w = (float)w / IMAGE_SIZE;
	float _h = (float)h / IMAGE_SIZE;

	return glm::vec4(x, y, _w, _h);
}
