#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Transform
{
public:
	Transform();
	Transform(glm::vec2 pos_) : pos(pos_) {}
	~Transform();

	glm::vec2 pos;
};

