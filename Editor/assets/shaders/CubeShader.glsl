#ifdef _TYPE_VERT_SHADER
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_Texcoord;
layout(location = 3) in vec3 a_Normal;
layout(location = 4) in int a_EntityID;

uniform mat4 u_ViewProjection;

out vec3 v_Color;
out vec2 v_Texcoord;
out vec3 v_Normal;
out flat int v_EntityID;


void main()
{
	v_Color = a_Color;
	v_Texcoord = a_Texcoord;
	v_Normal = a_Normal;
	v_EntityID = a_EntityID;
	gl_Position = u_ViewProjection  * vec4(a_Position, 1.0);
}
#endif

#ifdef _TYPE_FRAG_SHADER
layout(location = 0) out vec4 color;
layout(location = 1) out int id;

in vec3 v_Color;
in vec2 v_Texcoord;
in vec3 v_Normal;
in flat int v_EntityID;

// void main ()
// {
// 	vec4 
// 	color = vec4(v_Color, 1.0);
// 	vec3 col = v_Normal * 0.5 + 0.5;
// 	// vec3 col = v_Normal;
// 	color = vec4(col, 1.0);
// 	color = vec4(v_Color, 1.0);
// 	id = v_EntityID;
// }
void main()
{
    // Original color based on v_Color
    vec4 baseColor = vec4(v_Color, 1.0);
    
    // Compute a slight tint color based on the normal
    vec3 normalTint = v_Normal * 0.1 + 0.0;  // Adjust the multiplier to change tint strength
    
    // Combine the base color with the tint
    vec3 tintedColor = baseColor.rgb + normalTint;
    
    // Ensure the color values are within the valid range [0, 1]
    tintedColor = clamp(tintedColor, 0.0, 1.0);
    
    // Set the final color output
    color = vec4(tintedColor, 1.0);
    
    // Set the entity ID (unchanged)
    id = v_EntityID;
}
#endif