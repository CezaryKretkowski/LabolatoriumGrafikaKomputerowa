#version 330
in vec4 outColor;
in vec3 outNormals;
in vec2 textCords;
in vec3 fragPos;

out vec4 color;
uniform sampler2D myTextureSampler;
uniform bool isTextured;
uniform vec3 viewPos;
uniform bool blin;

void main(){
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 LightPos=vec3(0.0,4.0,0.0);
    vec3 lightColor=vec3(1.0,1.0,1.0);
    vec3 ambient=ambientStrength*lightColor;
    vec4 materialColor=texture(myTextureSampler,textCords);


    vec3 norm=normalize(outNormals);
    vec3 lightDir=normalize(LightPos-fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 reflectDir = reflect(-lightDir, norm); 
    vec3 halfwayDir = normalize(lightDir + viewDir);


    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); 

    float spec1 = pow(max(dot(outNormals, halfwayDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor; 
    vec3 specular1 = lightColor*spec1;

    vec3 result=(ambient+diffuse+ specular)*materialColor.rgb;
    if(blin)
        result=(ambient+diffuse+ specular1)*materialColor.rgb;
    color=vec4(result,1.0);
    
}