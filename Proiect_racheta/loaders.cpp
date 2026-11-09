#include "loaders.h"
#include "globals.h"
#include <stdio.h>
#include <vector>
#include <SOIL.h>

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"
GLuint LoadScrollingTexture(const char* filePath) {
    GLuint textureID = SOIL_load_OGL_texture(
        filePath,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if (textureID == 0) {
        printf("Eroare la incarcarea imaginii SOIL: %s\n", SOIL_last_result());
        return 0;
    }

    // Setam repeatur-ul pentru derulare infinita
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureID;
}
void LoadSVGObject(const char* filePath, GLuint& vaoId, GLuint& vboId, int& count, float scaleFactor) {
    NSVGimage* image = nsvgParseFromFile(filePath, "px", 96.0f);
    if (!image) {
        printf("Eroare: Nu s-a putut deschide fisierul %s!\n", filePath);
        return;
    }

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    count = 0;

    float minX = 1e9f, maxX = -1e9f, minY = 1e9f, maxY = -1e9f;

    for (NSVGshape* shape = image->shapes; shape != NULL; shape = shape->next) {
        for (NSVGpath* path = shape->paths; path != NULL; path = path->next) {
            for (int i = 0; i < path->npts; i++) {
                float x = path->pts[i * 2];
                float y = path->pts[i * 2 + 1];
                if (x < minX) minX = x;
                if (x > maxX) maxX = x;
                if (y < minY) minY = y;
                if (y > maxY) maxY = y;
            }
        }
    }

    float width = maxX - minX;
    float height = maxY - minY;
    float centerX = minX + width / 2.0f;
    float centerY = minY + height / 2.0f;
    float maxDim = (width > height) ? width : height;
    float scale = scaleFactor / maxDim;

    for (NSVGshape* shape = image->shapes; shape != NULL; shape = shape->next) {
        for (NSVGpath* path = shape->paths; path != NULL; path = path->next) {
            for (int i = 0; i < path->npts; i++) {
                float rawX = path->pts[i * 2];
                float rawY = path->pts[i * 2 + 1];

                float normX = (rawX - centerX) * scale;
                float normY = -(rawY - centerY) * scale;

                vertices.push_back(normX);
                vertices.push_back(normY);
                vertices.push_back(0.0f);
                vertices.push_back(1.0f);

                colors.push_back(1.0f);
                colors.push_back(0.0f);
                colors.push_back(1.0f);
                colors.push_back(1.0f);

                count++;
            }
        }
    }

    nsvgDelete(image);

    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat) + colors.size() * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(GLfloat), vertices.data());
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), colors.size() * sizeof(GLfloat), colors.data());

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)(vertices.size() * sizeof(GLfloat)));

    glBindVertexArray(0);
}
