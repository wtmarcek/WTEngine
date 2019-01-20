#include "wtfpch.h"
#include "Triangle.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <glad/glad.h>

WTF::Triangle::Triangle()
{
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0,
		 0.5f, -0.5f, 0.0,
		 0.0f,  0.5f, 0.0
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
}
