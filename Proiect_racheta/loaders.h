#pragma once
#include <GL/glew.h>

GLuint LoadScrollingTexture(const char* filePath);
void LoadSVGObject(const char* filePath, GLuint& vaoId, GLuint& vboId, int& count, float scaleFactor);