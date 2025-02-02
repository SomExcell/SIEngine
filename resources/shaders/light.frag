#version 330 core
out vec4 FragColor;

uniform bool isActive;
uniform vec4 color;

void main()
{
    if(isActive)
    {
        FragColor = color;
    }
    else if(!isActive)
    {
        FragColor = vec4(0.0);
    }
}
