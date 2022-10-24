#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>

#define ASSERT(x) if ((!x)) break;
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line); 

#endif /* end of include guard: RENDERER_H_HWLOAG95 */
