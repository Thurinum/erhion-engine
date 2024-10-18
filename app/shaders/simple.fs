#version 330 core
out vec4 FragColor;

// declare uniform for changing color
uniform vec3 ourColor;

void main() {
	FragColor = vec4(outColor, 1.0f);
}