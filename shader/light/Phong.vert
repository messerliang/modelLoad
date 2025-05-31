#version 330 core

layout(location=0) in vec4 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoords;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * position;
	Normal = mat3(transpose(inverse(model))) * normal;	// �������ʹ���˲��ȱ��������ţ�Ϊ�˱�֤���������쳣��������ҪΪ���������ö�Ӧ�Ĳ���

	FragPos = vec3(model * position); // ������ʹ�� model ���󣬼�������������������ʵ��λ��
	TexCoords = texCoords;
};
