#version 430

uniform sampler2D myTexture;
vec3 lightLoc;
vec3 camLoc;

in vec2 fragUV;
in vec3 worldLoc;	
in vec3 worldNormal;

void main()

{

vec3 l = normalize(lightLoc - worldLoc); //Direction to light from the fragment
vec3 v = normalize(camLoc - worldLoc);	 //Direction to the camera from the fragment
vec3 h = normalize (l + v);				 //Direction to halfway between light and camera
vec3 n = normalize (worldNormal);		 //Normal vector

float am = 10;
float diff = .1 * max(dot(l,n),0);
float spec = .1 * pow(max(dot(h,n),0),16);
float bright = am + diff + spec;

vec4  texColor = texture(myTexture, fragUV);

gl_FragColor = vec4(vec3(texColor * bright), texColor.a);
}