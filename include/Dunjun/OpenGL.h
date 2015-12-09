#ifndef DUNJUN_OPENGL_H
#define DUNJUN_OPENGL_H

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <GL/glew.h>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/GL.h>
#else
#include <GL/GL.h>
#endif

#endif // DUNJUN_OPENGL_H
