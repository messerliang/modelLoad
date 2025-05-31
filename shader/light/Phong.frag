#version 330 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 outColor;

    
//uniform float ambientStrength;                          // ������ǿ��
//uniform float specularStrength;                         // ���淴���ǿ��
//uniform vec3 objectColor;


uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;                                   // �۲���λ��


// ʹ�ýṹ�������в���
struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;


struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shiness;
};



// ����Ҳ����ͨ��������������ͼ�;��淴����ͼ��ʵ��
struct MaterialTex{
    sampler2D diffuse;
    sampler2D specular;
    float shiness;
};


//uniform Material material;
//void calcColor(out vec3 result){
//    // ͨ���ṹ���������������ɫ��
//    vec3 ambient = (material.ambient * light.ambient) ;
//    
//    vec3 norm = normalize(Normal);                      // ����������һ��
//    
//    // ������
//    vec3 lightDir = normalize(lightPos - FragPos);      // �����ķ���
//    float diff = max(dot(norm, lightDir), 0.0f);        // �ⷽ���뷨�������н�Խ��Խ��
//    vec3 diffuse = light.diffuse * diff * material.diffuse;                   // �൱���ǹ��ֱ��Ƕ�
//
//    
//
//    // ������Ͼ��淴��
//    vec3 viewDir = normalize(viewPos - FragPos);        // 
//    vec3 reflectDir = reflect(-lightDir, norm);          // ����������������ָ���������ķ�������
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shiness);
//    vec3 specular = (spec  * material.specular)* light.specular;
//    result = (ambient + diffuse + specular );   // ������ + ������ + ���淴��
//}


uniform MaterialTex materialTex;
void calcColorUsingTex(out vec3 result){
    vec3 norm = normalize(Normal);

    vec3 basicColor = vec3(texture(materialTex.diffuse, TexCoords));


    vec3 lightDir = normalize(lightPos - FragPos);      // �����ķ���
    float diff = max(dot(norm, lightDir), 0.0f);        // �ⷽ���뷨�������н�Խ��Խ��
    
    vec3 diffuse = light.diffuse * (diff * basicColor); // ������
    vec3 ambient = light.ambient * basicColor;          // ������

    // ������
    vec3 specColor = vec3(texture(materialTex.specular, TexCoords));
    vec3 viewDir = normalize(viewPos - FragPos);        // 
    vec3 reflectDir = reflect(-lightDir, norm);          // ����������������ָ���������ķ�������
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialTex.shiness);
    vec3 specular = (spec  * specColor)* light.specular;
    result = (ambient + diffuse + specular );           // ������ + ������ + ���淴��

}

void main()
{
    vec3 result;
    calcColorUsingTex(result);
    outColor = vec4(result, 1.0f);
};