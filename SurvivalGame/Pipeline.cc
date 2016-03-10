// Helpers for OGL macros
#include <glm\gtc\type_ptr.hpp>
#include <GL\glew.h>

namespace Pipeline
{
	inline void draw_begin(GLuint va, GLuint shaderP)
	{
		__glewBindVertexArray(va);
		__glewUseProgram(shaderP);
	};

	inline void draw_end(size_t indexCount, GLenum mode)
	{
		glDrawElements(mode, indexCount * sizeof(uint32_t), GL_UNSIGNED_INT, 0);
	};
}