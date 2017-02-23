#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

/*------- Entradas --------*/
IN vec4 vPosition;
IN vec3 vNormal;
IN vec2 vCoordTexture;


/* ------- Salidas -------- */
OUT vec4 Position;
OUT vec3 Normal;
OUT vec2 v_texcoord;

/* ------- Tipos Luces ----------- */
const int PUNTUAL =  0;
const int DIRECCIONAL = 1;
const int SPOT = 2;

/* ------- Estructura Materiales -------- */
struct s_material
{
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
    float Alpha;
};
uniform s_material v_material;

/* ------- Estructura Luces -------- */
struct s_light
{
    int type;
    vec4 Position; //POINT LIGHT ambient
    vec4 Direction; // DIRECCIONAL LIGHT
    vec4 AmbientIntensity;
    vec4 SpecularIntensity;
    vec3 DiffuseIntensity; //usada en ambient
    float Angle,Alpha;
    float a,b,c,d;
    bool ON;

};


uniform s_light v_light[3];//[0] POINT, [1] DIRECCIONAL, [2] SPOTLIGHT
uniform float ambientGlobal;
uniform bool conTextura;


void main()
{
  gl_Position = vPosition;
  Normal = vNormal;
  Position = gl_Position;
  v_texcoord = vCoordTexture;



}

