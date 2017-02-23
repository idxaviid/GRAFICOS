#include "material.h"
using namespace std;
#include<iostream>
Material::Material() {
    this->Ambient =  vec3(0.2,0.2,0.2);
    this->Diffuse =  vec3(0.8,0.0,0.0);
    this->Specular  = vec3(1.0,1.0,1.0);
    this->Shininess = 200;
    this->Alpha  = 1.0;
}

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, GLfloat shininess, GLfloat alpha)
{
    this->Ambient = ambient;
    this->Diffuse = diffuse;
    this->Specular = specular;
    this->Shininess = shininess;
    this->Alpha = alpha;
}

void Material::toGPU(QGLShaderProgram *program)
{
    struct{
            GLuint Ambient;
            GLuint Diffuse;
            GLuint Specular;
            GLuint Shininess;
            GLuint Alpha;
    }gl_IdMaterial;

    gl_IdMaterial.Ambient = program->uniformLocation("v_material.Ambient");
    gl_IdMaterial.Diffuse = program->uniformLocation("v_material.Diffuse");
    gl_IdMaterial.Specular = program->uniformLocation("v_material.Specular");
    gl_IdMaterial.Shininess = program->uniformLocation("v_material.Shininess");
    gl_IdMaterial.Alpha = program->uniformLocation("v_material.Alpha");

    glUniform3fv(gl_IdMaterial.Ambient, 1, this->Ambient );
    glUniform3fv(gl_IdMaterial.Diffuse, 1, this->Diffuse );
    glUniform3fv(gl_IdMaterial.Specular, 1, this->Specular);
    glUniform1f( gl_IdMaterial.Shininess, this->Shininess);
    glUniform1f( gl_IdMaterial.Alpha, this->Alpha);

}
