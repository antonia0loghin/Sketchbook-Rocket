#include "renderer.h"
#include "globals.h"
#include "loaders.h"
#include "loadShaders.h"
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"


void CreateShaders(void) {
    ProgramId = LoadShaders("example.vert", "example.frag");
    BgProgramId = LoadShaders("bg.vert", "bg.frag");
}

void CreateVBO(void) {
    //incarcam obiectele din svg uri
    LoadSVGObject("racheta.svg", RachetaVaoId, RachetaVboId, RachetaVertexCount, 0.6f);
    LoadSVGObject("copac.svg", Copac1VaoId, Copac1VboId, Copac1VertexCount, 0.3f);
    LoadSVGObject("star.svg", StarVaoId, StarVboId, StarVertexCount, 0.2f);
    LoadSVGObject("soare.svg", SoareVaoId, SoareVboId, SoareVertexCount, 0.3f);
    //pamant
    GLfloat pamantVertices[] = {
    -1.0f, -0.65f, 0.0f, 1.0f,
     1.0f, -0.65f, 0.0f, 1.0f
    };

    GLfloat pamantColors[] = {
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f
    };

    GLfloat particulaVertices[] = {
    -0.015f, -0.015f, 0.0f, 1.0f,
     0.015f, -0.015f, 0.0f, 1.0f,
     0.015f,  0.015f, 0.0f, 1.0f,
    -0.015f,  0.015f, 0.0f, 1.0f
    };

    GLfloat particulaColors[] = {
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &PamantVaoId);
    glBindVertexArray(PamantVaoId);

    glGenBuffers(1, &PamantVboId);
    glBindBuffer(GL_ARRAY_BUFFER, PamantVboId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(pamantVertices) + sizeof(pamantColors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pamantVertices), pamantVertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(pamantVertices), sizeof(pamantColors), pamantColors);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(pamantVertices));

    glBindVertexArray(0);

    glGenVertexArrays(1, &ParticulaVaoId);
    glBindVertexArray(ParticulaVaoId);

    glGenBuffers(1, &ParticulaVboId);
    glBindBuffer(GL_ARRAY_BUFFER, ParticulaVboId);

    glBufferData(GL_ARRAY_BUFFER, sizeof(particulaVertices) + sizeof(particulaColors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(particulaVertices), particulaVertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(particulaVertices), sizeof(particulaColors), particulaColors);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)sizeof(particulaVertices));

    glBindVertexArray(0);
}
void DestroyShaders(void) {
    glDeleteProgram(ProgramId);
}

void DestroyVBO(void) {
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //racheta
    glDeleteBuffers(1, &RachetaVboId);
    glDeleteVertexArrays(1, &RachetaVaoId);

    // Copac
    glDeleteBuffers(1, &Copac1VboId);
    glDeleteVertexArrays(1, &Copac1VaoId);

    // Stea
    glDeleteBuffers(1, &StarVboId);
    glDeleteVertexArrays(1, &StarVaoId);

    // Soare
    glDeleteBuffers(1, &SoareVboId);
    glDeleteVertexArrays(1, &SoareVaoId);

    // Pamant
    glDeleteBuffers(1, &PamantVboId);
    glDeleteVertexArrays(1, &PamantVaoId);

    // Particule
    glDeleteBuffers(1, &ParticulaVboId);
    glDeleteVertexArrays(1, &ParticulaVaoId);

    // Fundal derulant
    glDeleteBuffers(1, &BgVboId);
    glDeleteVertexArrays(1, &BgVaoId);

    // Curatam si textura SOIL de pe GPU
    if (BgTextureId != 0) {
        glDeleteTextures(1, &BgTextureId);
    }
    
}

void CreateBackgroundVBO(void) {
    GLfloat bgVertices[] = {
        -1.0f,  1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f,   1.0f, 0.0f,

        -1.0f,  1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f,   1.0f, 1.0f
    };

    glGenVertexArrays(1, &BgVaoId);
    glBindVertexArray(BgVaoId);

    glGenBuffers(1, &BgVboId);
    glBindBuffer(GL_ARRAY_BUFFER, BgVboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgVertices), bgVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid*)(4 * sizeof(GLfloat)));

    glBindVertexArray(0);
}

void Cleanup(void) {
    DestroyShaders();
    DestroyVBO();
}

void Initialize(void) {
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    CreateShaders();
    CreateVBO();
    CreateBackgroundVBO();
    BgTextureId = LoadScrollingTexture("bg.png");
    if (BgTextureId == 0) {
        printf("ATENTIE: Textura bg.jpg nu s-a incarcat!\n");
    }
    myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
    codColLocation = glGetUniformLocation(ProgramId, "codCol");

    resizeMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
}

void TimerFunction(int value) {
    if (isFlying) {
        if (turboTimer > 0.0f) {
            turboTimer -= 0.016f;
            isTurbo = true;
        }
        else {
            isTurbo = false;
        }

        float vitezaBg = isTurbo ? 0.04f : 0.01f;
        float vitezaRacheta = isTurbo ? 0.15f : 0.05f;

        bgY -= vitezaBg;

        rocketX += (mouseX - rocketX) * vitezaRacheta;
        rocketY += (mouseY - rocketY) * vitezaRacheta;

        if (isTurbo) {
            float dx = mouseX - rocketX;
            float dy = mouseY - rocketY;
            float dist = sqrt(dx * dx + dy * dy);

            float dirX = 0.0f;
            float dirY = -1.0f;

            if (dist > 0.0001f) {
                dirX = dx / dist;
                dirY = dy / dist;
            }

            float offsetDist = 0.20f;

            for (int i = 0; i < 3; i++) {
                Particula p;
                p.x = rocketX - dirX * offsetDist + ((float)rand() / RAND_MAX - 0.5f) * 0.03f;
                p.y = rocketY - dirY * offsetDist + ((float)rand() / RAND_MAX - 0.5f) * 0.03f;

                float pSpeed = 0.015f + ((float)rand() / RAND_MAX) * 0.01f;
                p.vx = -dirX * pSpeed + ((float)rand() / RAND_MAX - 0.5f) * 0.005f;
                p.vy = -dirY * pSpeed + ((float)rand() / RAND_MAX - 0.5f) * 0.005f;

                p.life = 1.0f;
                particule.push_back(p);
            }
        }

        for (size_t i = 0; i < particule.size(); i++) {
            particule[i].x += particule[i].vx;
            particule[i].y += particule[i].vy - vitezaBg;
            particule[i].life -= 0.04f;

            if (particule[i].life <= 0.0f) {
                particule.erase(particule.begin() + i);
                i--;
            }
        }


    }
    glutPostRedisplay();
    glutTimerFunc(16, TimerFunction, 0);
}


void RenderFunction(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (BgTextureId != 0) {
        glUseProgram(BgProgramId);

        glUniform1f(glGetUniformLocation(BgProgramId, "bgOffset"), -bgY * 0.3f);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, BgTextureId);
        glUniform1i(glGetUniformLocation(BgProgramId, "bgTexture"), 0);

        glBindVertexArray(BgVaoId);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    glUseProgram(BgProgramId);
    glUniform1f(glGetUniformLocation(BgProgramId, "bgOffset"), -bgY * 0.3f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, BgTextureId);
    glUniform1i(glGetUniformLocation(BgProgramId, "bgTexture"), 0);

    glBindVertexArray(BgVaoId);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glUseProgram(ProgramId);
    glUniform1i(codColLocation, indexCuloare);
    glBindVertexArray(RachetaVaoId);

    glLineWidth(3.0f);

    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(rocketX, rocketY, 0.0f));

    float angle = 0.0f;
    if (isFlying) {
        angle = atan2(mouseY - rocketY, mouseX - rocketX) - 1.5708f;
    }
    glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

    myMatrix = resizeMatrix * translateMat * rotateMat;


    //matrice racheta
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
    glDrawArrays(GL_LINE_LOOP, 0, RachetaVertexCount);

    glBindVertexArray(0);


    glBindVertexArray(Copac1VaoId);
    //matrice copac
    glm::mat4 translateCopac = glm::translate(glm::mat4(1.0f), glm::vec3(copac1X, copac1Y + bgY, 0.0f));
    glm::mat4 Copac1Matrix = resizeMatrix * translateCopac;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &Copac1Matrix[0][0]);

    glDrawArrays(GL_LINE_LOOP, 0, Copac1VertexCount);
    glBindVertexArray(0);

    glBindVertexArray(SoareVaoId);
    //matrice soare
    glm::mat4 translateSoare = glm::translate(glm::mat4(1.0f), glm::vec3(soareX, soareY + bgY, 0.0f));
    glm::mat4 SoareMatrix = resizeMatrix * translateSoare;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &SoareMatrix[0][0]);

    glDrawArrays(GL_LINE_LOOP, 0, SoareVertexCount);
    glBindVertexArray(0);


    glBindVertexArray(PamantVaoId);
    //matrice pamant
    glm::mat4 translatePamant = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, bgY, 0.0f));
    glm::mat4 PamantMatrix = resizeMatrix * translatePamant;
    glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &PamantMatrix[0][0]);

    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);

    if (bgY < -0.8f) {
        float stea1Y = bgY + 2.5f;
        while (stea1Y < -1.2f) stea1Y += 2.4f;

        float stea2Y = bgY + 3.7f;
        while (stea2Y < -1.2f) stea2Y += 2.4f;

        glBindVertexArray(StarVaoId);

        glm::mat4 transStea1 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.7f, stea1Y, 0.0f));
        glm::mat4 stea1Matrix = resizeMatrix * transStea1;
        glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &stea1Matrix[0][0]);
        glDrawArrays(GL_LINE_LOOP, 0, StarVertexCount);

        glm::mat4 scaleMirror = glm::scale(glm::mat4(1.0f), glm::vec3(-1.0f, 1.0f, 1.0f));
        glm::mat4 transStea2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.7f, stea2Y, 0.0f));
        glm::mat4 stea2Matrix = resizeMatrix * transStea2 * scaleMirror;
        glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &stea2Matrix[0][0]);
        glDrawArrays(GL_LINE_LOOP, 0, StarVertexCount);

        glBindVertexArray(0);
    }

    glBindVertexArray(0);

    glBindVertexArray(ParticulaVaoId);

    for (const auto& p : particule) {
        glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(p.x, p.y, 0.0f));
        glm::mat4 sca = glm::scale(glm::mat4(1.0f), glm::vec3(p.life, p.life, 1.0f));
        glm::mat4 partMat = resizeMatrix * trans * sca;

        glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &partMat[0][0]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    }
    glBindVertexArray(0);

    glutSwapBuffers();

}
void AfiseazaControaleConsola(void) {
    printf("\n======================================\n");
    printf("              CONTROLS       \n");
    printf("======================================\n");
    printf(" Click Stanga : Start Zbor \n");
    printf(" SPACE        : Turbo Mode  \n");
    printf(" Tastele A/D  : Schimbare culori  \n");
    printf("======================================\n\n");
}
