#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif


IN vec4 vPosition;
IN vec4 vColor;

OUT vec4 color;

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
  //TEST DE MATERIALES
  //color = vColor;
    //color = vec4(test.exemple1[0],test.exemple1[1],test.exemple1[2],test.exemple1[3]);
    //color = vec4(v_material.Ambient[0],v_material.Ambient[1],v_material.Ambient[2],v_material.Alpha);
    //color = vec4(v_material.Diffuse[0],v_material.Diffuse[1],v_material.Diffuse[2],1.0);
    //color = vec4(v_material.Specular[0],v_material.Specular[1],v_material.Specular[2],1.0);
    //color = vec4(v_material.Ambient[0],v_material.Ambient[1],v_material.Ambient[2],v_material.Shininess);
    //color = vec4(v_material.Ambient[0],v_material.Ambient[1],v_material.Ambient[2],v_material.Alpha);
  //TEST DE LLUMS
    //color = vec4(v_light[0].SpecularIntensity[0],v_light[0].SpecularIntensity[1],v_light[0].SpecularIntensity[2],v_light[0].SpecularIntensity[2]);
    //color = v_light[0].AmbientIntensity;

    color = vec4(v_light[0].DiffuseIntensity[0],v_light[0].DiffuseIntensity[1],v_light[0].DiffuseIntensity[2],1.0);
    //color = vec4(v_light[0].Angle,v_light[0].Alpha,v_light[0].a,1.0);
    //color = vec4(v_light[0].b,v_light[0].c,v_light[0].d,1.0);

}
