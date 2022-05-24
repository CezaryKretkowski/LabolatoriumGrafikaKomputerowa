#version 330
in vec4 outColor;
in vec3 textCords;

out vec4 color;
uniform samplerCube myTextureSampler;
uniform bool isTextured;

void main(){
    vec4 materialColor=texture(myTextureSampler,textCords);
    color=materialColor;
}