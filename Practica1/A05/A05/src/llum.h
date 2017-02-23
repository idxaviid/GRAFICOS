#ifndef LLUM_H
#define LLUM_H

#include <Common.h>

// Tipus de llums
enum Lights {Puntual, Direccional, SpotLight};

// Classe que representa els atributs d'una llum
class Llum {
private:
    vec4 Position; //puntual,ambient
    vec4 Direction;
    vec4 AmbientIntensity;
    vec4 SpecularIntensity;
    vec3 DiffuseIntensity; //usada en ambient
    GLfloat Angle,Alpha;

    //coeficients datenuacio en profundidad
    //a = constant, b = lineal i c = quadràtica , d es la distancia pro es inutil por ahora
    GLfloat a,b,c,d;
    bool ON;
    Lights type; //o int
public:
    Llum(Lights l);

    void setTipusLlum(Lights t);

    void setLightPosition(vec4 v);
    vec4 getLightPosition(); // vec4 getPosition() const;

    vec4 getDirection() const;
    void setDirection(const vec4 &value);

    vec4 getAmbientIntensity() const;
    void setAmbientIntensity(const vec4 &value);

    vec4 getSpecularIntensity() const;
    void setSpecularIntensity(const vec4 &value);

    vec3 getDiffuseIntensity();
    void setDiffuseIntensity(vec3 i); //void setPosition(const vec4 &value);

    GLfloat getAngle() const;
    void setAngle(const GLfloat &value);

    GLfloat getAlpha() const;
    void setAlpha(const GLfloat &value);

    GLfloat getA() const;
    void setA(const GLfloat &value);

    GLfloat getB() const;
    void setB(const GLfloat &value);

    GLfloat getC() const;
    void setC(const GLfloat &value);

    GLfloat getD() const;
    void setD(const GLfloat &value);

    void switchOnOff();    
    bool getON() const;

    int getType() const;


};

#endif // LLUM_H
