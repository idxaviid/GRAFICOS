#if __VERSION__<130
#define IN varying
#define OUT varying
#else
#define IN in
#define OUT out
#endif



/*------- Entradas --------*/
IN vec4 Position;
IN vec3 Normal;
IN vec2 v_texcoord;



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

uniform s_light v_light[3];
uniform float ambientGlobal;
uniform sampler2D texMap;
uniform sampler2D texNormal;
uniform bool conTextura;



float attenuation(s_light l)
{
    float a, b, c, distance;
    distance = length(l.Position.xyz - Position.xyz);
    a = l.a * pow(distance, 2.0);
    b = l.b * distance;
    c = l.c;
    return (1.0 /(a + b + c));

}

vec3 LPoint(s_light l)
{

    // el vector direccion desde el punto hasta la fuente de luz, normalizada
    return vec3(normalize(l.Position.xyz - Position.xyz));

}

vec3 LDirectional(s_light l)
{

    return -vec3(normalize(l.Direction.xyz));

}

vec3 LSpotLight(s_light l)
{

    vec3 vDir = normalize((Position - l.Position).xyz);
    //Potse que dentro del angulo hay que hacer cosinus
    if (acos(dot(l.Direction.xyz, vDir.xyz)) > l.Angle ){
        return vDir;
    }
    return vec3(0.0);

}

vec3 getL(s_light l){

    if(l.type == 0) return LPoint(l);
    else if(l.type == 1) return LDirectional(l);
    else if(l.type == 2) return LSpotLight(l);
    return LPoint(l);

}

vec3 blinn_phong(s_light l)
{

    vec3 diffuse, ambient, specular, N, V, L, H;

    // la normal del vertice, normalizada

    N = normalize(Normal.xyz); //hacer otro shader ymultiplicar la normal de la textura por la textura normal
    //if(conTextura)
      //  N = normalize(Normal.xyz * -texture2D(texNormal, v_texcoord).rgb);
    // el vector desde el punt fins al viewer
    V = normalize(Position.xyz);

    // el vector direccion desde el punto hasta la fuente de luz, normalizada
    L = getL(l);

    // the halfway, o l'optimitzacio de Blinn
    H = (L+V) / length(L+V);

    // la difusa es el producto de la difusa de la luz por la difusa del material
    vec3 diffuseMat = vec3(v_material.Diffuse);
        if(conTextura)
            diffuseMat = diffuseMat * 0.2 +  0.8 *texture2D(texMap, v_texcoord).rgb;

    diffuse = (l.DiffuseIntensity.xyz * diffuseMat) * max(dot(L, N), 0.0);//v_material.Diffuse.xyz * 0.2

    // la especular es el producto del producto especular de la luz por el del material y  el dot de N y H elevado a E
    specular = (l.SpecularIntensity.xyz * v_material.Specular.xyz) * max(pow(dot(N, H), v_material.Shininess) , 0.0);

    // producto de light ambient y  ambient del material
    ambient = l.AmbientIntensity.xyz * v_material.Ambient.xyz;

    return (ambient + diffuse + specular);

}



vec4 get_Color()
{
    //calculamos ambente global IaGlobal * Ka
    vec4 aGlobal = vec4((ambientGlobal * v_material.Ambient.xyz),0.0);

    //hacemos la formula de blinn_phong para las 3 luces en el vector v_light
    vec4 llum = vec4 (0.0);
    for(int i = 0;i < 3; i++){
        if(v_light[i].ON)
            llum += vec4((attenuation(v_light[i]) * blinn_phong(v_light[i])), 1.0);
    }//TODO hacer bien la suma de las luces porque devuelve 0 cuando no estan
    //llum += vec4((attenuation(v_light[0]) * blinn_phong(v_light[0])), 1.0);

    //calculamos La iTotal sumando IaGlobal con el sumatorio de blin_phong

    vec4 iTotal = vec4(aGlobal + llum);

    return iTotal;

}


void main()
{

    //gl_FragColor = get_Color();

    if(conTextura == true)
    {
       gl_FragColor = 0.25 * get_Color() + 0.75 * texture2D(texMap, v_texcoord);
    }else{
       gl_FragColor = get_Color();
    }


}
