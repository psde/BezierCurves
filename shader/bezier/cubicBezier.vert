#define SEGMENT_START1 1
#define SEGMENT_START2 2
#define SEGMENT_MID1 3
#define SEGMENT_MID2 4
#define SEGMENT_END1 5
#define SEGMENT_END2 6

uniform vec4 c1;
uniform vec4 c2;
uniform vec4 c3;
uniform vec4 c4;
//uniform float lvl;
uniform float width;
uniform float step;

void main(void)
{
    float lvl = gl_Vertex[2];
    int segment = gl_Vertex[0];
    
    gl_Vertex[0] = 0.0f;
    gl_Vertex[1] = 0.0f;
    gl_Vertex[2] = 0.0f;
    
    vec4 current = gl_Vertex;
    vec4 next = gl_Vertex;
    vec4 tangent = gl_Vertex;
    vec4 p_tangent = gl_Vertex;

    current.x = (c1.x * (1.0 - lvl) * (1.0 - lvl) * (1.0 - lvl)) +
                (c2.x * 3.0 * lvl * (1.0 - lvl) * (1.0 - lvl)) +
                (c3.x * 3.0 * lvl * lvl * (1.0 - lvl)) +
                (c4.x * lvl * lvl * lvl);

    current.y = c1.y * (1.0 - lvl) * (1.0 - lvl) * (1.0 - lvl) +
                c2.y * 3.0 * lvl * (1.0 - lvl) * (1.0 - lvl) +
                c3.y * 3.0 * lvl * lvl * (1.0 - lvl) +
                c4.y * lvl * lvl * lvl;
    
    lvl += step;
    
    next.x = (c1.x * (1.0 - lvl) * (1.0 - lvl) * (1.0 - lvl)) +
             (c2.x * 3.0 * lvl * (1.0 - lvl) * (1.0 - lvl)) +
             (c3.x * 3.0 * lvl * lvl * (1.0 - lvl)) +
             (c4.x * lvl * lvl * lvl);

    next.y = c1.y * (1.0 - lvl) * (1.0 - lvl) * (1.0 - lvl) +
             c2.y * 3.0 * lvl * (1.0 - lvl) * (1.0 - lvl) +
             c3.y * 3.0 * lvl * lvl * (1.0 - lvl) +
             c4.y * lvl * lvl * lvl;

    tangent = next - current;
    tangent = normalize(tangent);
    p_tangent = tangent;
    p_tangent.x = - tangent.y;
    p_tangent.y = tangent.x;
    
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    
    vec4 out_pos = gl_Vertex;
    out_pos = current;  
    
    if (segment == SEGMENT_START1) out_pos = current - (tangent * width) + (p_tangent * width);
    if (segment == SEGMENT_START2) out_pos = current - (tangent * width) - (p_tangent * width);
    if (segment == SEGMENT_MID1) out_pos = current + (p_tangent * width);
    if (segment == SEGMENT_MID2) out_pos = current - (p_tangent * width);
    if (segment == SEGMENT_END1) out_pos = current + (tangent * width) + (p_tangent * width);
    if (segment == SEGMENT_END2) out_pos = current + (tangent * width) - (p_tangent * width);
        
    gl_Position = gl_ModelViewProjectionMatrix * out_pos;

}
