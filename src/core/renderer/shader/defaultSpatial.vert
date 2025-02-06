#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoords;

out vec2 fragTexCoords;  // Output to fragment shader

uniform mat4 model;      // Model matrix (e.g., for transformations)
uniform mat4 view;       // View matrix (camera position)
uniform mat4 projection; // Projection matrix (e.g., for perspective)

void main(void) {

	// Pass the texture coordinates to the fragment shader
    fragTexCoords = inTexCoords;
    
    // Transform the vertex position by model, view, and projection matrices
    gl_Position = projection * view * model * vec4(inPosition, 1.0);
}
