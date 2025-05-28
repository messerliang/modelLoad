#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

    
uniform float ambientStrength;                          // 环境光强度
uniform float specularStrength;                         // 镜面反射的强度
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;                                   // 观察点的位置


void main()
{

    vec3 ambient = (ambientStrength * lightColor) ;
    

    
    vec3 norm = normalize(Normal);                      // 法向向量归一化
    
    // 漫反射
    vec3 lightDir = normalize(lightPos - FragPos);      // 计算光的方向
    float diff = max(dot(norm, lightDir), 0.0f);        // 光方向与法向向量夹角越大。越暗
    vec3 diffuse = diff * lightColor;                   // 相当于是光的直射角度

    

    // 下面加上镜面反射
    vec3 viewDir = normalize(viewPos - FragPos);        // 
    vec3 reflectDir = reflect(-lightDir, norm);          // 计算入射向量根据指定法向量的反射向量
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular ) * objectColor;   // 环境光 + 漫反射 + 镜面反射

    outColor = vec4(result, 1.0f);
};