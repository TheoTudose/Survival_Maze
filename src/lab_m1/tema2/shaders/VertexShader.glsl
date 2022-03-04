#version 330


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 texCoord;
layout (location = 3) in vec3 normal;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;

out vec3 fColor;

void main()
{
    fColor = object_color;

    gl_Position = Projection * View * Model * vec4(position, 1);

}
