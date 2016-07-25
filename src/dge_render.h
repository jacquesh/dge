#ifndef DGE_RENDER_H
#define DGE_RENDER_H

#include <stdio.h>

#include <SDL.h>
#include <GL/gl3w.h>

#include "dge_math.h"

namespace dge
{
    struct WindowData
    {
      int x;
      int y;
      int width;
      int height;

      uint32 flags;
      const char* title;
    };

    struct Camera2D
    {
      Vector2 position;
      Vector2 size;

      Vector2 screenToWorldLoc(Vector2 cameraLoc);
      Vector2 worldToScreenLoc(Vector2 worldLoc);
    };

#define glPrintError(alwaysPrint) dge::__glPrintError(__FILE__, __LINE__, alwaysPrint)
    static inline void __glPrintError(const char* file, int line, bool alwaysPrint)
    {
      GLenum error = glGetError();
      const char* errorStr;
      if(alwaysPrint || (error != GL_NO_ERROR))
      {
          switch(error)
          {
          case GL_NO_ERROR:
              errorStr = "GL_NO_ERROR";
              break;
          case GL_INVALID_ENUM:
              errorStr = "GL_INVALID_ENUM";
              break;
          case GL_INVALID_VALUE:
              errorStr = "GL_INVALID_VALUE";
              break;
          case GL_INVALID_OPERATION:
              errorStr = "GL_INVALID_OPERATION";
              break;
          case GL_INVALID_FRAMEBUFFER_OPERATION:
              errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
              break;
          case GL_OUT_OF_MEMORY:
              errorStr = "GL_OUT_OF_MEMORY";
              break;
          default:
              errorStr = "UNRECOGNIZED";
              break;
          }

          fprintf(stderr, "(%s:%d) OpenGL error: %s\n", file, line, errorStr);
      }
    }

    GLuint loadShader(const char* shaderFilename, GLenum shaderType);
    GLuint loadShaderProgram(const char* vertShaderFilename, const char* fragShaderFilename);
    GLuint loadShaderProgram(const char* vertShaderFilename,
                             const char* geomShaderFilename,
                             const char* fragShaderFilename);

    bool32 initRenderer(SDL_Window* window);
    void loadTexture(const char* fileName, GLuint textureID);
    void allocateAndLoadTexture(const char* fileName, GLuint* textureID);

    void loadDefaultShaders();
    void loadTextRenderer();
    void updateShaderCamera(Camera2D camera, GLuint shader);

    void drawLine2D(Camera2D camera, Vector2 fromLoc, Vector2 toLoc, Vector4 color);
    void renderString(Camera2D camera, const char* string, int length, Vector2 position, float size, Vector4 color);
    void renderQuad(Camera2D camera, Vector2 centre, Vector2 size, float rotation, Vector4 color);
    void renderSprite(Camera2D camera, GLuint textureID, Vector2 position, float rotation, Vector2 size, Vector4 color);
    void renderSprite(Camera2D camera, GLuint textureID, Vector2 position, float rotation, Vector2 size);
}

#endif
