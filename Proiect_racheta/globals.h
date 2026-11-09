#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glm/glm.hpp"

namespace Config {
    constexpr int WIN_WIDTH = 800;
    constexpr int WIN_HEIGHT = 600;
}

struct Particula {
    float x, y;
    float vx, vy;
    float life;
};

extern GLuint StarVaoId, StarVboId, RachetaVaoId, RachetaVboId, Copac1VaoId, Copac1VboId, ProgramId, BgProgramId;
extern GLuint myMatrixLocation, codColLocation, PamantVaoId, PamantVboId, SoareVaoId, SoareVboId;
extern GLuint BgVaoId, BgVboId, BgTextureId;
extern GLuint ParticulaVaoId, ParticulaVboId;

extern int codCol;
extern float rocketX, rocketY, copac1X, copac1Y, soareX, soareY;
extern float mouseX, mouseY, bgY;
extern bool isFlying, isTurbo;
extern float turboTimer;
extern int indexCuloare;
extern int RachetaVertexCount, Copac1VertexCount, StarVertexCount, SoareVertexCount;

extern glm::mat4 myMatrix, resizeMatrix;
extern std::vector<Particula> particule;