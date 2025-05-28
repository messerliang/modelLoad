#version 330 core

in vec4 color;

out vec4 outColor;

uniform vec3      iResolution;           // viewport resolution (in pixels)£¬width, height, 1.0
uniform float     iTime;                 // shader playback time (in seconds)



void main()
{


    outColor = color;
};