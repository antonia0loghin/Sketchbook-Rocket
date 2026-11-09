#include "globals.h"

GLuint StarVaoId, StarVboId, RachetaVaoId, RachetaVboId, Copac1VaoId, Copac1VboId, ProgramId, BgProgramId;
GLuint myMatrixLocation, codColLocation, PamantVaoId, PamantVboId, SoareVaoId, SoareVboId;
GLuint BgVaoId, BgVboId, BgTextureId;
GLuint ParticulaVaoId, ParticulaVboId;

int codCol = 0;
float rocketX = 0.0f, rocketY = -0.35f;
float copac1X = -0.75f, copac1Y = -0.5f;
float soareX = 0.70f, soareY = 0.70f;
float mouseX = 0.0f, mouseY = 0.0f, bgY = 0.0f;
bool isFlying = false, isTurbo = false;
float turboTimer = 0.0f;
int indexCuloare = 6;
int RachetaVertexCount = 0, Copac1VertexCount = 0, StarVertexCount = 0, SoareVertexCount = 0;

glm::mat4 myMatrix, resizeMatrix;
std::vector<Particula> particule;