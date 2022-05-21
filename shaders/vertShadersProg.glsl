#version 330
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normals;
layout(location = 2)in vec2 texturCords;


out vec2 textCords;

uniform mat4 MVP;


void main(){
	textCords=texturCords;
	gl_Position=MVP*vec4(pos,1.0);	
}