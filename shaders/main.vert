uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 

void main()
{
    gl_Position = projectionMatrix *  viewMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
}
