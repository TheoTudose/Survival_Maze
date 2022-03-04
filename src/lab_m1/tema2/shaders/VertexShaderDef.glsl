#version 330


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform float time;

out vec3 fColor;

float random(vec3 var)
{
    return fract(cos(dot(var.xyz ,vec3(4.9898,32.233, 22.3231))) * 2931.423); 
}

void main()
{

    fColor = object_color;

    vec3 newPosition = normal * 0.5 * random(position * time) + position;

    gl_Position = Projection * View * Model * vec4(newPosition, 1);

}
