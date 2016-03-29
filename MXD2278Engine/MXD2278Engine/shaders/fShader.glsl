#version 430
in vec2 fragUV;
void main()

{

gl_FragColor = vec4(fragUV,0,1);

}