#version 330
in vec3 aPos;
in vec3 norm;
in mat3 inversModel;

out vec4 color;
uniform samplerCube myTextureSampler;
uniform vec3 viewPos;

void main(){

    vec3 I =normalize(aPos-viewPos);
    vec3 R =inversModel* reflect(I,normalize(norm))* vec3(1, 1, -1);
    color=mix(vec4(texture(myTextureSampler,R).rgb,1.0),vec4(0.0,0.8,0.0,1.0),0.0);
}