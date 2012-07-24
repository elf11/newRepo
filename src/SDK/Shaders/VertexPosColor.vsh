
attribute vec4 position3;
attribute vec4 color;

uniform mat4 transformmat;

varying vec4 theColor;

void main()
{
    //vec4 temppos = vec4(position3.x,position3.y,position3.z,1.0);
    gl_Position = transformmat * position3;
    theColor = color;
}
