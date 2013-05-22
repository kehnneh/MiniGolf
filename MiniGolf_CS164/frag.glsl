#version 130

in vec3 L;
in vec3 N;
in vec3 V;
in vec4 ambientLight;
in vec4 frag_color;

out vec4 end_color;

const float s = 32.0;
const vec4 L_s = vec4(1.0);
const vec4 L_d = vec4(1.0);
const vec4 K_s = vec4(1.0);

void main() {
    float LdotN = dot(L,N);
    if (LdotN > 0.0) {
    	vec4 diff = frag_color * L_d * LdotN;
        vec4 spec = K_s * L_s * pow(LdotN, s);
        //end_color = clamp(diff + spec, 0.0, 1.0);
		end_color = clamp(ambientLight + diff + spec, 0.0f, 1.0);
    } else {
        //end_color = vec4(0.0);
		end_color = ambientLight * frag_color;
    }
}