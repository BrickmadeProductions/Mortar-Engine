#version 330 core

in vec2 fragTexCoords;  // Texture coordinates from vertex shader

out vec4 fragColor;      // Final output color

uniform sampler2D textureSampler; // Texture uniform

void main()
{
    // Sample the texture using the texture coordinates
    fragColor = texture(textureSampler, fragTexCoords);
}