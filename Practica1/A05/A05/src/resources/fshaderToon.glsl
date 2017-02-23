#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif

IN vec3 Normal;
IN vec4 Position;


struct s_light
{
    vec4 Position;
    vec4 Direction;

    vec4 AmbientIntensity;
    vec4 SpecularIntensity;
    vec3 DiffuseIntensity;

    float Angle,Alpha;
    float a,b,c,d;



};
uniform s_light v_light[3];
float Intensity(s_light l){

    //return dot(normalize(l.Direction.xyz), normalize(Normal.xyz)); //formula de teoria
    //usamos la posicion porque al mover posicion se ven las diferencias
    return dot(normalize(l.Position.xyz), normalize(Normal.xyz));

}

void main()
{
    vec4 color;
    float intensity = Intensity(v_light[2]);
    vec3 N = normalize(Normal.xyz);
    vec3 V = normalize(Position.xyz);

    float contorn = (1.0 - cos(dot(V,N)));
    if (intensity > 0.95)
        color = vec4(1.0,0.5,0.5,1.0) * contorn ;
    else if (intensity > 0.5)
        color = vec4(0.6,0.3,0.3,1.0) * contorn;
    else if (intensity > 0.25)
        color = vec4(0.4,0.2,0.2,1.0) * contorn;
    else
        color = vec4(0.2,0.1,0.1,1.0) * contorn;


    gl_FragColor = color;

}
