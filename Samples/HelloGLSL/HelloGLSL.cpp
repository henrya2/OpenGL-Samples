//========================================================================
// Simple GLFW example
// Copyright (c) Camilla Berglund <elmindreda@elmindreda.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
//! [code]

#include "framework.h"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

std::string sampleName = "HelloGLSL";

GLSLProgram glslProgram;

//vertex array and vertex buffer object IDs
GLuint vaoID;
GLuint vboVerticesID;
GLuint vboIndicesID;

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};

//triangle vertices and indices
Vertex vertices[3];
GLushort indices[3];

//projection and modelview matrices
glm::mat4 projectionMat = glm::mat4(1);
glm::mat4 modelviewMat = glm::mat4(1);

void init()
{
	glslProgram.loadShader(GLSLShaderType::VERTEX, sampleName + "/" + "HelloGLSL.vert");
	glslProgram.loadShader(GLSLShaderType::FRAGMENT, sampleName + "/" + "HelloGLSL.frag");
	glslProgram.link();

	glslProgram.use();

	//setup triangle geometry
	//setup triangle vertices
	vertices[0].color = glm::vec3(1, 0, 0);
	vertices[1].color = glm::vec3(0, 1, 0);
	vertices[2].color = glm::vec3(0, 0, 1);

	vertices[0].position = glm::vec3(-1, -1, 0);
	vertices[1].position = glm::vec3(0, 1, 0);
	vertices[2].position = glm::vec3(1, -1, 0);

	//setup triangle indices
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboVerticesID);
	glGenBuffers(1, &vboIndicesID);
	GLsizei stride = sizeof(Vertex);

	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboVerticesID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(glslProgram.getAttributeLocation("vVertex"));
	glVertexAttribPointer(glslProgram.getAttributeLocation("vVertex"), 3, GL_FLOAT, GL_FALSE, stride, 0);

	glEnableVertexAttribArray(glslProgram.getAttributeLocation("vColor"));
	glVertexAttribPointer(glslProgram.getAttributeLocation("vColor"), 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(Vertex, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glslProgram.use();

	glslProgram.setUniform("MVP", projectionMat * modelviewMat);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
}

void shutdown()
{
	glslProgram.deleteProgram();

	glDeleteBuffers(1, &vboVerticesID);
	glDeleteBuffers(1, &vboIndicesID);
	glDeleteBuffers(1, &vaoID);
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
    GLFWwindow* window;

	SamplesHelper::setupTheCurrentDirectoryToAssets();

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

    window = glfwCreateWindow(640, 480, "HelloGLFW", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

	// Load the OpenGL functions.
	glewExperimental = true;
	GLenum err = glewInit();
	if (GLEW_OK != err)	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}
	else if (GLEW_VERSION_3_3)
	{
			std::cout << "Driver supports OpenGL 3.3\nDetails:" << std::endl;
	}

	//print information on screen
	std::cout << "\tUsing GLEW " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "\tVendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "\tRenderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "\tVersion: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "\tGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	init();

	float ratio;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(window))
    {

		render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	shutdown();

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

//! [code]
