#version 330
in vec4 outColor;
in vec2 textCords;

out vec4 color;
uniform sampler2D myTextureSampler0;
uniform sampler2D myTextureSampler1;
uniform bool isTextured;
float celShading(in float cl){
    if(cl>0.7)
        return 1.0f;
    else if(cl<0.7&&cl>0.5)
        return 0.6f;
    else if(cl<0.5&&cl>0.3)
        return 0.4;
    else if(cl<0.3&&cl>0.1)
        return 0.2;  
    else
        return 0.0f;  
}
void main(){
    vec4 materialColor=texture(myTextureSampler0,textCords)*texture(myTextureSampler1,textCords);
    color = outColor;
    if(isTextured)
         color=vec4(celShading(materialColor[0]),celShading(materialColor[1]),celShading(materialColor[2]),materialColor[3]);
}