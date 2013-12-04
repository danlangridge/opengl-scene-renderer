#version 120

uniform mat4 projectionMatrix, viewMatrix; 

attribute vec4 position;
attribute vec4 vertColor;

varying vec4 fragColor; 

void main()
{
    gl_Position = projectionMatrix * viewMatrix * position;
    
    // ----- Fragment input ----- // 
    fragColor = vertColor; 
}
