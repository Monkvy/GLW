#pragma once
#include <GLM/glm.hpp>


namespace glw
{
	struct vec2
	{
		float x, y;
	};

	struct vec3
	{
		float x, y, z;
	};

	struct vec4
	{
		float x, y, z, w;
	};

	struct Vertex
	{
		vec2 position;
		vec4 color;
		vec2 texCoords;
		float texID;
	};
}