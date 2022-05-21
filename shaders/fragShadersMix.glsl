#version 330
in vec4 outColor;
in vec2 textCords;

out vec4 color;
uniform sampler2D myTextureSampler0;

uniform bool isTextured;

void main(){
    vec4 materialColor=texture(myTextureSampler0,textCords);
    color = outColor;
    if(isTextured)
         color=materialColor;
}