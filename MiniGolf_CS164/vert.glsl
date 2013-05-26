#version 130

// These variables change on a per frame basis
uniform mat4 camera; // Camera matrix
uniform mat4 transform; // models transform
uniform mat4 proj; // Projection matrix
uniform mat3 normalMat; // Normal matrix
uniform vec3 L_p; // Light position
//uniform vec3 Eye; // eye position
uniform vec4 ambient; // ambient light intensity

//input variables from host
in vec3 pos; //vertex position
in vec3 norm; //vertex normal
in vec4 color; //vertex color

//variables to be passed to the fragment shader
out vec3 L;
out vec3 N;
out vec3 V;
out vec4 ambientLight;
out vec4 frag_color;

void main() {
    mat4 modelView = camera * transform;

	vec3 eye = -camera[3].xyz * mat3(camera);
	
    vec4 posT = modelView * vec4(pos, 1.0);
    
    L = normalize(modelView * vec4(L_p, 1.0)).xyz;

    V = (modelView * vec4(eye, 1.0)).xyz;

    N = normalize(normalMat * norm);
    L = normalize(L - posT.xyz);
    V = normalize(V - posT.xyz);
    
    frag_color = color;
    
	ambientLight = ambient;
    gl_Position = proj * posT;
}
