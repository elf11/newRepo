#include "GLee.h"
#include "platform.h"
#define glClearDepthf glClearDepth
#define glLightModelx glLightModeli
#define GL_DEPTH_COMPONENT24_OES GL_DEPTH_COMPONENT24_ARB
#define GL_RGB565 GL_RGB5
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0xffff-1
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0xffff-2
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0xffff-3
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0xffff-4
#define glFogx glFogi
#define GL_DEPTH24_STENCIL8_OES GL_DEPTH24_STENCIL8
#define GL_DEPTH_STENCIL_OES GL_DEPTH_STENCIL_EXT
#define GL_UNSIGNED_INT_24_8_OES GL_UNSIGNED_INT_24_8_EXT
#define glDepthRangef glDepthRange

#define GL_RGBA8_OES GL_RGBA8
#define glRenderbufferStorageMultisampleAPPLE   glRenderbufferStorageMultisample

#define GL_READ_FRAMEBUFFER_APPLE   GL_READ_FRAMEBUFFER
#define GL_DRAW_FRAMEBUFFER_APPLE   GL_DRAW_FRAMEBUFFER

#define glGenQueriesEXT             glGenQueries
#define glDeleteQueriesEXT          glDeleteQueries
#define glBeginQueryEXT             glBeginQuery
#define glEndQueryEXT               glEndQuery
#define glGetQueryObjectuivEXT      glGetQueryObjectuiv
#define GL_ANY_SAMPLES_PASSED_EXT               GL_SAMPLES_PASSED
#define GL_ANY_SAMPLES_PASSED_CONSERVATIVE_EXT  GL_SAMPLES_PASSED
#define GL_QUERY_RESULT_EXT         GL_QUERY_RESULT

