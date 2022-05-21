#version 330
in vec2 textCords;

out vec4 color;
uniform sampler2D myTextureSampler;

uniform bool whiteblackProg;
uniform bool whiteblack;
uniform bool cel_Shading;

vec4 progFunColor(in float brightness,in vec4 matColor){
    vec4 outColor;
    if(brightness>0.98){
        outColor=vec4(matColor[0],matColor[1]-0.8,matColor[2]*0.8,matColor[3]);
    }else if(brightness>0.5){
        outColor=vec4(matColor[0]*0.8,matColor[1]*0.4,matColor[2]*0.4,matColor[3]);
    }else if(brightness>0.25){
        outColor=vec4(matColor[0]*0.4,matColor[1]*0.2,matColor[2]*0.2,matColor[3]);
    }else
        outColor=vec4(matColor[0]*0.1,matColor[1]*0.1,matColor[2]*0.1,matColor[3]);

    return outColor;

}
vec4 toBlacWhite(in float brightness){
    return vec4(brightness,brightness,brightness,1.0f);
}
vec4 progFunBlackWhite(in float brightness,in vec4 matColor){
    if(brightness>0.5)
        return vec4(1.0f,1.0f,1.0f,1.0f);
    else
        return vec4(0.0f,0.0f,0.0f,1.0f);
}
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
    vec4 materialColor=texture(myTextureSampler,textCords);
    float brightness=(materialColor.r+materialColor.g+materialColor.b)/3.0f;

    if(whiteblackProg)
        color=progFunBlackWhite(brightness,materialColor);
    else
        color=progFunColor(brightness,materialColor);    
    if(whiteblack)
        color=toBlacWhite(brightness);

    if(cel_Shading)
        color=vec4(celShading(materialColor[0]),celShading(materialColor[1]),celShading(materialColor[2]),materialColor[3]);
}