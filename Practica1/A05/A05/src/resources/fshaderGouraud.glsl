#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif
//Recibo un color del vshader
IN vec4 color;
IN vec2 v_texcoord;

uniform sampler2D texMap;
uniform bool conTextura;

void main()
{
    //gl_FragColor = color;
    //gl_FragColor = 0.25*color + 0.75*texture2D(texMap, v_texcoord);
    //gl_FragColor = texture2D(texMap, v_texcoord);
    if(conTextura)
        gl_FragColor = 0.25*color + 0.75*texture2D(texMap, v_texcoord);
    else
        gl_FragColor = color;



}

