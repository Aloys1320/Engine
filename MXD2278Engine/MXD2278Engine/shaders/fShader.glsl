#version 430

uniform sampler2D myTexture;
uniform vec3 lightLoc[2];
uniform vec3 camLoc;

in vec2 fragUV;
in vec3 worldLoc;	
in vec3 worldNormal;
vec3 finalColor;
vec4  texColor;

void main(){

finalColor = vec3( 0.0 ,0.0,0.0);
texColor = vec4 (0.0,0.0,0.0,0.0);

for(int i=0;i<2;i++){
	vec3 l = normalize(lightLoc[i] - worldLoc); //Direction to light from the fragment
	vec3 v = normalize(camLoc - worldLoc);	 //Direction to the camera from the fragment
	vec3 h = normalize (l + v);				 //Direction to halfway between light and camera
	vec3 n = normalize (worldNormal);		 //Normal vector

	float am = .01;
	float diff = .6* max(dot(l,n),0);
	float spec = .8 * pow(max(dot(h,n),0),16);
	float bright = am + diff + spec;

	texColor += texture(myTexture, fragUV);
	finalColor += vec3(texColor * bright);
	}
gl_FragColor = vec4(finalColor, texColor.a);
}