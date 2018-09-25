#version 410

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main () {
    vec3 color = vec3 (TexCoord, 1.0);
    // FragColor = vec4 (color, 1.0);
    FragColor = texture(ourTexture, TexCoord);
}

