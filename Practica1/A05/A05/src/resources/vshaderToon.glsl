#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

/* ----- Entradas -----*/
IN vec4 vPosition;
IN vec3 vNormal;

/*------- Salidas -------*/
OUT vec3 Normal;
OUT vec4 Position;
/* ------- Tipos Luces ----------- */
const int PUNTUAL =  0;
const int DIRECCIONAL = 1;
const int SPOT = 2;


struct s_material
{
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
    float Alpha;
};
uniform s_material v_material;

struct s_light
{
    vec4 Position; //puntual,ambient
    vec4 Direction;

    vec4 AmbientIntensity;
    vec4 SpecularIntensity;
    vec3 DiffuseIntensity; //usada en ambient

    float Angle,Alpha;
    float a,b,c,d;

    //bool ON;
    //int type;

};
uniform s_light v_light[3]; //ponerlo a numLights


void main()
{
    gl_Position = vPosition;
    Position =vPosition;
    Normal = vNormal;

}
