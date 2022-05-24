#version 330
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normals;
layout(location = 2)in vec2 texturCords;

out vec4 outColor;
out vec3 textCords;

uniform mat4 MVP;
uniform vec4 inputColor;

void main(){
	outColor=inputColor;
	textCords=pos;
	gl_Position=MVP*vec4(pos,1.0);	
}