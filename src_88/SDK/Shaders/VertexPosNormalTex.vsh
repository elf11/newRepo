
attribute vec4 position3;
attribute vec3 normal;
attribute vec2 tex1;

uniform mat4 TransformMat;

varying vec2 newuv;

void main()
{
    gl_Position = TransformMat * position3;
    newuv = tex1;
    newuv.y = 1.0 - newuv.y;
}

