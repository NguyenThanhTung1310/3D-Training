precision mediump float;
//varying vec3 ourColor;
uniform sampler2D u_texture;
varying vec2 v_uv;
void main()
{
	//gl_FragColor = vec4(ourColor, 1.0);
	gl_FragColor = texture2D(u_texture, v_uv);
}
