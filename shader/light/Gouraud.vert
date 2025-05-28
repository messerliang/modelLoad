#version 330 core

layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec3 LightingColor;

uniform float ambientStrength;                          // ������ǿ��
uniform float specularStrength;                         // ���淴���ǿ��

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;                                   // �۲���λ��


void main()
{
	gl_Position = projection * view * model * position;


	// ����ʹ�� gouraud shading
	// ������
    vec3 ambient = (ambientStrength * lightColor);
    
    vec3 Position = vec3(model * position);
	vec3 norm = mat3(transpose(inverse(model))) * normal;	// �������ʹ���˲��ȱ��������ţ�Ϊ�˱�֤���������쳣��������ҪΪ���������ö�Ӧ�Ĳ���

	// ������
    vec3 lightDir = normalize(lightPos - Position);      // �����ķ���
    float diff = max(dot(norm, lightDir), 0.0f);        // �ⷽ���뷨�������н�Խ��Խ��
    vec3 diffuse = diff * lightColor;                   // �൱���ǹ��ֱ��Ƕ�

	// ������Ͼ��淴��
    vec3 viewDir = normalize(viewPos - Position);        // 
    vec3 reflectDir = reflect(-lightDir, norm);          // ����������������ָ���������ķ�������
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor;

    vec3 result = (ambient + diffuse + specular );   // ������ + ������ + ���淴��

    LightingColor = result;

};
