#version 330
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texturCords;

out vec4 outColor;
out vec3 outNormals;
out vec2 textCords;
out vec3 fragPos;

uniform mat4 MVP;
uniform mat4 model;
uniform vec4 inputColor;

void main(){
	outColor=inputColor;

	textCords=texturCords;
	gl_Position=MVP*vec4(pos,1.0);
	fragPos=vec3(model*vec4(pos,1.0));		
	outNormals=mat3(transpose(inverse(model))) * normals;
}