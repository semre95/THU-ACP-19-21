#version 410 core

out vec4 ourColor;

void main(){
    float r, g, b;
    r = (gl_PrimitiveID % 255) / 255.0f;
    g = ((gl_PrimitiveID / 255) % 255) / 255.0f;
    b = ((gl_PrimitiveID / (255 * 255)) % 255) / 255.0f;
    ourColor = vec4(r, g, b,1.0f);
}