#version 450

vec3 positions[][] = vec3[][](
vec3[](vec3(-0.5, -0.5, 0.0), vec3(0.5, -0.5, 0.0), vec3(0.5, 0.5, 0.0)),
vec3[](vec3(-0.5, 0.5, 0.0), vec3(0.5, 0.5, 0.0), vec3(-0.5, -0.5, 0.0))
);
/*
var vertexPositionArray=[
    //----- triangle 1
    -0.5,-0.5,0, //bottom
    0.5,-0.5,0, //bottom right
    0.5,0.5,0,  //top right

    //----- triangle 2
    -0.5,0.5,0, //top left
    0.5,0.5,0, // top right
    -0.5,-0.5,0, // bottom left
];
*/

void main() {
    //gl_Position = positions; //vec4(positions[gl_VertexIndex], 0.0, 1.5);
}