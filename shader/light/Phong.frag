#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

    
uniform float ambientStrength;                          // ������ǿ��
uniform float specularStrength;                         // ���淴���ǿ��
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;                                   // �۲���λ��


void main()
{

    vec3 ambient = (ambientStrength * lightColor) ;
    

    
    vec3 norm = normalize(Normal);                      // ����������һ��
    
    // ������
    vec3 lightDir = normalize(lightPos - FragPos);      // �����ķ���
    float diff = max(dot(norm, lightDir), 0.0f);        // �ⷽ���뷨�������н�Խ��Խ��
    vec3 diffuse = diff * lightColor;                   // �൱���ǹ��ֱ��Ƕ�

    

    // ������Ͼ��淴��
    vec3 viewDir = normalize(viewPos - FragPos);        // 
    vec3 reflectDir = reflect(-lightDir, norm);          // ����������������ָ���������ķ�������
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular ) * objectColor;   // ������ + ������ + ���淴��

    outColor = vec4(result, 1.0f);
};