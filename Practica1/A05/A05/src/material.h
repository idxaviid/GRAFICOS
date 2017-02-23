#ifndef MATERIAL_H
#define MATERIAL_H
//#include "vec.h"
//#include "objecte.h"
#include <QObject>
#include <vector>
#include <Common.h>
#include <QGLShaderProgram>
#include <QOpenGLTexture>
// Classe que representa les propietats optiques d'un objecte
class Material {

public:
    Material();
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    GLfloat Shininess;
    GLfloat Alpha;
    //probar con cada uno
    // verde rgb(0,100,0)

    Material(vec3,vec3,vec3,GLfloat,GLfloat);
    ~Material();

    void toGPU(QGLShaderProgram *program);
};

#endif // MATERIAL_H
