#version 330 core



uniform vec3      iResolution;           // viewport resolution (in pixels)，width, height, 1.0
uniform float     iTime;                 // shader playback time (in seconds)


//out vec4 FragColor;

in vec2 fragCoord;
out vec4 FragColor;



uniform float curTime;

float g(vec4 p,float s) {
    
    return abs(dot(sin(p*=s),cos(p.zxwy))-1.)/s;
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

// Gyroid 距离函数
float gyroid(vec3 p, float scale, float thickness) {
    p *= scale; // 缩放控制周期性密度
    float g = sin(p.x)*cos(p.y) + sin(p.y)*cos(p.z) + sin(p.z)*cos(p.x);
    return abs(g) - thickness; // 用厚度控制结构粗细
}



void main(){


    // 使用 shader toy
    vec4 color;
    vec2 shaderToyCoord = vec2((fragCoord.x / 2 +0.5) * iResolution.x, (fragCoord.y / 2 + 0.5) * iResolution.y);
    mainImage(color, shaderToyCoord);
    FragColor = color;
}