#pragma once

#include "glm/glm.hpp"
#include <stddef.h>

struct VertexPositionColorNormalUV
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uv;
};

#if defined(_MSC_VER) && !defined(_CRT_USE_BUILTIN_OFFSETOF)
#ifdef __cplusplus
	#define VERTEX_ATTRIB_OFFSET(s,m) ((GLsizei)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
#else
	#define VERTEX_ATTRIB_OFFSET(s,m) ((GLsizei)&(((s*)0)->m))
#endif
#else
	#define VERTEX_ATTRIB_OFFSET(s,m) (GLsizei)__builtin_offsetof(s,m)
#endif
