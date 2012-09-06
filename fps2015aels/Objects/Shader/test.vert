


void main(void)
{
	vec4	col;


	col = gl_Color;
	col[0] = 1.0f;
	col[1] = col[1] - 0.2f;
	col[2] = col[2] - 0.2f;

	gl_FrontColor = col;
	gl_Position =  gl_ModelViewProjectionMatrix* gl_Vertex ;
}
