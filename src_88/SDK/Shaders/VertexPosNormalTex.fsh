
varying vec2 newuv;
uniform sampler2D Texture1;

void main()
{
    gl_FragColor = texture2D(Texture1,newuv);
}

