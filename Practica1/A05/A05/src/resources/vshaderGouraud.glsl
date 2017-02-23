#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

#define PI 3.14159265359


/*------- Entradas --------*/
IN vec4 vPosition;
IN vec3 vNormal;
IN vec2 vCoordTexture;


/* ------- Salidas -------- */
OUT vec4 color;
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


float attenuation(s_light l)
{
    float a, b, c, distance;
    distance = length(l.Position.xyz - vPosition.xyz);
    a = l.a * pow(distance, 2.0);
    b = l.b * distance;
    c = l.c;
    return (1.0 /(a + b + c));

}

vec3 LPoint(s_light l)
{

    // el vector direccion desde el punto hasta la fuente de luz, normalizada
    return vec3(normalize(l.Position.xyz - vPosition.xyz));

}

vec3 LDirectional(s_light l)
{

    return -vec3(normalize(l.Direction.xyz));

}

vec3 LSpotLight(s_light l)
{

    vec3 vDir = normalize((vPosition - l.Position).xyz);
    //Potse que dentro del angulo hay que hacer cosinus
    if (acos(dot(l.Direction.xyz, vDir.xyz)) > l.Angle ){
        return vDir;
    }
    return vec3(0.0);

}

vec3 getL(s_light l)
{

    if(l.type == 0) return LPoint(l);
    else if(l.type == 1) return LDirectional(l);
    else if(l.type == 2) return LSpotLight(l);
    return LPoint(l);

}

vec3 blinn_phong(s_light l)
{

    vec3 diffuse, ambient, specular, N, V, L, H;

    // la normal del vertice, normalizada
    N = normalize(vNormal.xyz);

    // el vector desde el punt fins al viewer
    V = normalize(vPosition.xyz);

    // el vector direccion desde el punto hasta la fuente de luz, normalizada
    L = getL(l);

    // the halfway, o l'optimitzacio de Blinn
    H = (L+V) / length(L+V);

    // la difusa es el producto de la difusa de la luz por la difusa del material
    diffuse = (l.DiffuseIntensity.xyz * v_material.Diffuse.xyz) * max(dot(L, N), 0.0);

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
    }

    //calculamos La iTotal sumando IaGlobal con el sumatorio de blin_phong
    vec4 iTotal = vec4(aGlobal + llum);

    return iTotal;
}


void main()
{
  gl_Position = vPosition;
  color = get_Color();
  v_texcoord = vCoordTexture;


}

  /* ------------------------------------ MANERA1 -------------------------------------
  //vec3 R = ( (N+N)* dot(L,N))-L;
  vec3 L = vec3(0.0);
  vec3 N = normalize(vNormal.xyz);
 //el if falla nusepk
  if(v_light[0].type == 0){
      L = LPoint();
  }
  else if(v_light[0].type == 1){
      L = LDirectional();
  }else{
      L = LSpotLight();
  }

  vec3 V = normalize (N *(dot(N,L))); //la v potse la caluulo mal
  vec3 H = normalize((L+V)/abs(L+V));
  //Model Phong ambiental
  vec3 ambientKI = v_material.Ambient.xyz * v_light[0].AmbientIntensity.xyz;
  //Model Phong difusa
  vec3 diffuseKI = v_material.Diffuse.xyz * v_light[0].DiffuseIntensity.xyz;
  //Model Phong Especular
  vec3 specularKI = v_material.Specular.xyz * v_light[0].SpecularIntensity.xyz;
  vec3 ambient = ambientKI;
  vec3 diffuse = diffuseKI * max(dot(L, N), 0.0);
  vec3 specular = specularKI * pow(max(dot(N, H), 0.0), v_material.Shininess);
  //length(v_light[0].Direction);cambiar la d Distancia por ese calculo
  vec3 c = ambientGlobal * v_material.Ambient.xyz + (1.0/(v_light[0].a + (v_light[0].b*v_light[0].d) + pow(v_light[0].c*v_light[0].d,2))) *(diffuse + ambient + specular);
  color = vec4(c,1.0);*/



  /* ------------------------------- MANERA 2 ------------------------------------------------
  //Model Phong ambiental
  vec3 ambient = v_material.Ambient.xyz * v_light[0].AmbientIntensity.xyz;
  //Model Phong difusa
  vec3 diffuse = (v_material.Diffuse.xyz * v_light[0].DiffuseIntensity.xyz) * max(dot(L, N), 0.0);
  //Model Phong Especular
  vec3 specular = (v_material.Specular.xyz * v_light[0].SpecularIntensity.xyz) * pow(max(dot(N, H), 0.0), v_material.Shininess);

  vec3 c = ambientGlobal * v_material.Ambient.xyz + (1.0/(v_light[0].a + (v_light[0].b*v_light[0].d) + pow(v_light[0].c*v_light[0].d,2))) *
          (diffuse + ambient + specular);
  color = vec4(c,1.0);*/


  /* ------------------------------- MANERA 3 ------------------------------------------------
  //Otra manera de hacerlo , casi es la misma solose camiba la V por la E
    /*
    vec3 N = normalize(vNormal.xyz);
    vec3 L = vec3(v_light[0].Position.xyz - vPosition.xyz);
    vec3 E = -normalize(vPosition.xyz);
    vec3 H = normalize ((L+E)/abs(L+E));
    vec3 ambient = v_light[0].AmbientIntensity.xyz *v_material.Ambient.xyz; //potse aki cross
    vec3 diffuse = (v_light[0].DiffuseIntensity.xyz * v_material.Diffuse.xyz) * max(dot(L, N), 0.0);
    vec3 specular = pow(max(dot(N, H), 0.0), v_material.Shininess) *(v_light[0].SpecularIntensity.xyz * v_material.Specular.xyz);

    color = vec4(( (ambientGlobal*v_material.Ambient.xyz) + ambient + diffuse + specular).xyz, 1.0);*/


  /* ------------------------------ TEST NORMALES -------------------------------------------------
    //color = vec4(abs(vNormal.x),abs(vNormal.y),abs(vNormal.z),1.0);
    //color = vec4(abs(vNormal),1.0);
    //color = vec4(normalize(point().xyz*normalize(vNormal.xyz)),1.0);
    //color = vec4(normalize(v_light[0].DiffuseIntensity.xyz),1.0);
    //color = get_Color();*/

