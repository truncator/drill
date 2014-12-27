#include "lightsource.hpp"

#include "light.hpp"

void LightSource::AttachLight(Light* light, const glm::vec2& offset)
{
	light->SetOffset(offset);
	m_lights.push_back(light);
}

void LightSource::InitializeLights(const glm::vec2& position)
{
	int size = m_lights.size();
	for (int i = 0; i < size; i++)
	{
		m_lights[i]->SetPosition(position + m_lights[i]->GetOffset());
	}
}

void LightSource::UpdateLights(const glm::vec2& position)
{
	int size = m_lights.size();
	for (int i = 0; i < size; i++)
	{
		if (m_lights[i]->IsStatic())
			continue;

		m_lights[i]->SetPosition(position + m_lights[i]->GetOffset());
	}
}
