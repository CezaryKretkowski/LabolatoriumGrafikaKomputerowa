#version 330
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normals;
layout(location = 2)in vec2 texturCords;


out vec3 aPos;
out vec3 norm;
out mat3 inversModel;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


void main(){
	aPos=vec3(P*V*M*vec4(pos,1.0));
    norm=mat3(transpose(inverse(M)))*norm;
    inversModel=mat3(inverse(M));
	gl_Position=P*V*M*vec4(pos,1.0);	
}