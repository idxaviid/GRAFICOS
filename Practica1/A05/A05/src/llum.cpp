#include "llum.h"


vec4 Llum::getDirection() const
{
    return Direction;
}

void Llum::setDirection(const vec4 &value)
{
    Direction = value;
}

vec4 Llum::getSpecularIntensity() const
{
    return SpecularIntensity;
}

void Llum::setSpecularIntensity(const vec4 &value)
{
    SpecularIntensity = value;
}

bool Llum::getON() const
{
    return ON;
}

int Llum::getType() const
{
    return type;
}

vec4 Llum::getAmbientIntensity() const
{
    return AmbientIntensity;
}

void Llum::setAmbientIntensity(const vec4 &value)
{
    AmbientIntensity = value;
}

GLfloat Llum::getAngle() const
{
    return Angle;
}

void Llum::setAngle(const GLfloat &value)
{
    Angle = value;
}

GLfloat Llum::getAlpha() const
{
    return Alpha;
}

void Llum::setAlpha(const GLfloat &value)
{
    Alpha = value;
}

GLfloat Llum::getA() const
{
    return a;
}

void Llum::setA(const GLfloat &value)
{
    a = value;
}

GLfloat Llum::getB() const
{
    return b;
}

void Llum::setB(const GLfloat &value)
{
    b = value;
}

GLfloat Llum::getC() const
{
    return c;
}

void Llum::setC(const GLfloat &value)
{
    c = value;
}

GLfloat Llum::getD() const
{
    return d;
}

void Llum::setD(const GLfloat &value)
{
    d = value;
}

Llum::Llum(Lights t) {
    setTipusLlum(t);
    //ponemos los valores por defecto para poder hacer pruebas
    this->AmbientIntensity = vec4(0.2,0.2,0.2,1.0);
    this->SpecularIntensity = vec4(1.0,1.0,1.0,1.0);
    this->DiffuseIntensity = vec3(0.8,0.8,0.8);
    this->Position = vec4(2.0,2.0,2.0,1.0);
    this->Direction = vec4(0.0,0.0,10.0,1.0);
    this->Angle = 0.0;
    this->Alpha = 1.0;
    this->a = 0.0;
    this->b = 0.0;
    this->c = 1.0;
    this->d = 1.0;
    this->switchOnOff();


}


void Llum::setTipusLlum(Lights t) {
    type = t;
}

vec3 Llum::getDiffuseIntensity() {
    // A canviar
    return this->DiffuseIntensity;
    //return(vec3(1.0, 0.0, 0.0));

}

vec4 Llum::getLightPosition() {
    // A canviar
    return this->Position;
    //return(vec4(0.0, 0.0, 0.0, 0.0));
}

void Llum::setDiffuseIntensity(vec3 i) {
// el float que es reb ha de multiplicar els tres valors de la intensitat digusa de la llum
    //DiffuseIntensity.x *=i.x;
    //DiffuseIntensity.y *=i.y;
    //DiffuseIntensity.z *=i.z;

    this->DiffuseIntensity = i;
}

void Llum::setLightPosition(vec4 v) {
    Position = v;
}

void Llum::switchOnOff() {
    // Si esta en on la posa a off i a l'inreves
    ON = !ON;

}
