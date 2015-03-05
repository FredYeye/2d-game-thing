#pragma once

#include "render.hpp"


void initialize(GLuint &vao, const PixelArray *render);
GLuint create_program(std::string vertex, std::string fragment);
GLuint load_and_compile_shader(std::string sname, GLenum shaderType);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
