#pragma once
#include <GLM\glm.hpp>
struct Transform
{
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;
	Transform(glm::vec2 _position, float _rotation, glm::vec2 _scale)
	{
		position = _position;
		rotation = _rotation;
		scale = _scale;
	}
	Transform()
	{
		position = glm::vec2(0, 0);
		rotation = 0.0f;
		scale = glm::vec2(1.0f, 1.0f);
	}
};