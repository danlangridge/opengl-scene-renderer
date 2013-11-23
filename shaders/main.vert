uniform mat4 projectionMatrix; 
uniform mat4 modelMatrix; 
uniform mat4 viewMatrix; 

void main()
{
    gl_Position = projectionMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
}
