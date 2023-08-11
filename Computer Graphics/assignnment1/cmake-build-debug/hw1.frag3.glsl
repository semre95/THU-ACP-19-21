#version 410 core

out vec4 ourColor;

void main(){
    float r, g, b;
    r = (gl_PrimitiveID % 7) / 7.0f;
    g = (gl_PrimitiveID % 5) / 5.0f;
    b = (gl_PrimitiveID % 9) / 9.0f;
    ourColor = vec4(r, g, b,1.0f);
}