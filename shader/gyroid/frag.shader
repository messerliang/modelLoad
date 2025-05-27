#version 330 core



uniform vec3      iResolution;           // viewport resolution (in pixels)��width, height, 1.0
uniform float     iTime;                 // shader playback time (in seconds)

uniform float     iTimeDelta;            // render time (in seconds)
uniform float     iFrameRate;            // shader frame rate
uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform sampler2D iChannel0;           // input channel. XX = 2D/Cube
uniform sampler2D iChannel1;           // input channel. XX = 2D/Cube
uniform sampler2D iChannel2;           // input channel. XX = 2D/Cube
uniform sampler2D iChannel3;           // input channel. XX = 2D/Cube
uniform vec4      iDate;                 // (year, month, day, time in seconds)


//out vec4 FragColor;

in vec2 fragCoord;
out vec4 FragColor;

// void main()
// {
//     vec4 color = vec4(0.1, 0.2, 0.8, 1.0);
//     vec4 bgColor = vec4(0.9, 0.2, 0.1, 1.0);
//     // �����귶Χ�� [-1, 1] ӳ�䵽 [0, 1]
//     vec2 uv = fragCoord * 0.5 + 0.5;
// 
//     // ���㵽Բ�ĵľ��루Բ���� uv = (0.5, 0.5)��
//     float dist = distance(uv, vec2(0.5));
// 
//     // �뾶
//     float radius = 0.4;
// 
//     // �����Բ�ڣ���ʾ��ɫ������͸��
//     if (dist < radius)
//         FragColor = vec4(fragCoord, 0.2, 1.0); // ��ɫԲ
//     else
//         FragColor = bgColor; // ��ɫ�������ɸĳ�͸��������ɫ��
// }

uniform float curTime;

float g(vec4 p,float s) {
    return abs(dot(sin(p*=s),cos(p.wzxy))-1.)/s;
}

void mainImage(out vec4 O, vec2 C) {
    
    float i, d, z, s, T = iTime;
    vec4 o, q, p, U = vec4(2,1,0,3);
    for (
        vec2 r = iResolution.xy;
        ++i < 79.;
        z += d + 5E-4,
        q = vec4(normalize(vec3((C+C-r)/r.y, 2)) * z, .2),
        q.z += T/3E1,
        s = q.y + .1,
        q.y = abs(s),
        p = q,
        p.y -= .11,
        p.xy *= mat2(cos(11.*U.zywz - 2. * p.z )),
        p.y -= .2,
        d = abs(g(p,8.) - g(p,24.)) / 4.,
        p = 1. + cos(.7 * U + 5. * q.z)
    )
        o += (s > 0. ? 1. : .1) * p.w * p / max(s > 0. ? d : d*d*d, 5E-4);

    o += (1.4 + sin(T) * sin(1.7 * T) * sin(2.3 * T))
         * 1E3 * U / length(q.xy);

    O = tanh(o / 1E5);
    

}

// Gyroid ���뺯��
float gyroid(vec3 p, float scale, float thickness) {
    p *= scale; // ���ſ����������ܶ�
    float g = sin(p.x)*cos(p.y) + sin(p.y)*cos(p.z) + sin(p.z)*cos(p.x);
    return abs(g) - thickness; // �ú�ȿ��ƽṹ��ϸ
}

// ʾ��ʹ��
void mainImage2(out vec4 color, in vec2 fragCoord) {
    // ��һ�����굽 [-1,1]���������߱�
    vec2 uv = (2.0*fragCoord - iResolution.xy)/iResolution.y;
    
    // �������߲�������
    vec3 ro = vec3(0, 0, 3); // �����λ��
    vec3 rd = normalize(vec3(uv, -1)); // ���߷���
    
    // ���߲�����
    float t = 0.0;
    for(int i = 0; i < 100; i++) {
        vec3 p = ro + rd * t;
        float d = gyroid(p, 5.0, 0.1); // ����5�������0.1
        if (d < 0.001) break;
        t += d;
    }
    
    // ��ɫ��������Ⱥͷ��ߣ�
    vec3 col = vec3(1.0 - t*0.1);
    color = vec4(col, 1.0);
}


void main(){
	// ���䡪��������������������������
	//  vec4 tl = vec4(0.5, 0.1, 0.9, 1.);
	//  vec4 tr = vec4(0.3, 1., 0.8, 1.);
	//  vec4 bl = vec4(0.8, 0.6, 0.1, 1.);
	//  vec4 br = vec4(0.7, 0.1, 0.2, 1.);
    //  
	//  vec4 top = mix(tl, tr, fragCoord.x);
	//  vec4 bottom = mix(bl, br, fragCoord.x);

	//  FragColor = mix(top, bottom, fragCoord.y);
	
	// �ظ�ͼ����������������������������������
	//  vec2 newPos = fract(fragCoord * 10.);
	//  top = vec4(newPos, 1., 1.);
	//  FragColor = mix(top, bottom, fragCoord.y);

	// ʹ�� sin ��������������������������������
	// float pi = 3.1415926;
	// float x = fragCoord.x;
	// float y = fragCoord.y;
	// float fac = sin(curTime);
    // 
	// float r = 0.1*fac+0.5;
	// float g = 0.2*sin(pi / 3 + curTime*3 )+ 0.8;
	// float b = 0.5*fac+0.5;
	// FragColor = vec4(r, g, b, 1.);



    // ʹ�� shader toy
    vec4 color;
    vec2 shaderToyCoord = vec2((fragCoord.x / 2 + 0.5) * iResolution.x, (fragCoord.y / 2 + 0.5) * iResolution.y);
    mainImage(color, shaderToyCoord);
    FragColor = color;
}