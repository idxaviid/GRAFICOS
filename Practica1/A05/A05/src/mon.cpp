#include "mon.h"
#define MAX 3
Mon::Mon() {

    //Intensidad global
    ambientGlobal = 0.2;
    //Textura objeto
    conTextura = false;


}

Mon::~Mon() {
    elements.clear();
}

void Mon::addObjecte(Objecte *obj) {
    elements.push_back(obj);
}

void Mon::draw() {
    for(unsigned int i=0; i < elements.size(); i++){
        elements.at(i)->draw();
    }

}

Llum* Mon::getLlumActual() {
    // Ara per ara dona com a llum actual la darrera que s'ha inserit, però es podria canviar segons el
    // que es vulgui fer en la GUI
    return (llums[llums.size()-1]);
}

void Mon::llumsToGPU(QGLShaderProgram *program){

    typedef struct
    {

        GLuint Position;
        GLuint Direction;
        GLuint AmbientIntensity;
        GLuint SpecularIntensity;
        GLuint DiffuseIntensity;
        GLuint Angle;
        GLuint Alpha;
        GLuint a,b,c,d;
        GLuint ON;
        GLuint type;
    }gl_IdLights;

    gl_IdLights *gl_IdVect = new gl_IdLights[llums.size()];

    for(unsigned int i = 0; i < llums.size();i++){
        Llum *actual;
        actual = llums[i];

        if(actual->getON()){
            gl_IdVect[ i ].Position = program->uniformLocation(QString("v_light[%1].Position").arg( i ));
            gl_IdVect[ i ].Direction = program->uniformLocation(QString("v_light[%1].Direction").arg( i ));
            gl_IdVect[ i ].AmbientIntensity = program->uniformLocation(QString("v_light[%1].AmbientIntensity").arg( i ));
            gl_IdVect[ i ].SpecularIntensity = program->uniformLocation(QString("v_light[%1].SpecularIntensity").arg( i ));
            gl_IdVect[ i ].DiffuseIntensity = program->uniformLocation(QString("v_light[%1].DiffuseIntensity").arg( i ));
            gl_IdVect[ i ].Angle = program->uniformLocation(QString("v_light[%1].Angle").arg( i ));
            gl_IdVect[ i ].Alpha = program->uniformLocation(QString("v_light[%1].Alpha").arg( i ));
            gl_IdVect[ i ].a = program->uniformLocation(QString("v_light[%1].a").arg( i ));
            gl_IdVect[ i ].b = program->uniformLocation(QString("v_light[%1].b").arg( i ));
            gl_IdVect[ i ].c = program->uniformLocation(QString("v_light[%1].c").arg( i ));
            gl_IdVect[ i ].d = program->uniformLocation(QString("v_light[%1].d").arg( i ));
            gl_IdVect[ i ].ON = program->uniformLocation(QString("v_light[%1].ON").arg( i ));
            gl_IdVect[ i ].type = program->uniformLocation(QString("v_light[%1].type").arg( i ));



            glUniform4fv(gl_IdVect[ i ].Position, 1, actual->getLightPosition());
            glUniform4fv(gl_IdVect[ i ].Direction, 1, actual->getDirection());
            glUniform4fv(gl_IdVect[ i ].AmbientIntensity, 1, actual->getAmbientIntensity());
            glUniform4fv(gl_IdVect[ i ].SpecularIntensity, 1, actual->getSpecularIntensity());
            glUniform3fv(gl_IdVect[ i ].DiffuseIntensity, 1, actual->getDiffuseIntensity());


            glUniform1f(gl_IdVect[ i ].Angle, actual->getAngle());
            glUniform1f(gl_IdVect[ i ].Alpha, actual->getAlpha());
            glUniform1f(gl_IdVect[ i ].a, actual->getA());
            glUniform1f(gl_IdVect[ i ].b, actual->getB());
            glUniform1f(gl_IdVect[ i ].c, actual->getC());
            glUniform1f(gl_IdVect[ i ].d, actual->getD());
            glUniform1f(gl_IdVect[ i ].ON, actual->getON());
            glUniform1f(gl_IdVect[ i ].type, actual->getType());
        }
    }

}

void Mon::addLlum(Llum *l) {
    llums.push_back(l);

}

void Mon::setAmbientToGPU(QGLShaderProgram *program){
    GLuint GL_ambientGlobal = program->uniformLocation("ambientGlobal");
    glUniform1f(GL_ambientGlobal,  this->ambientGlobal);

}

void Mon::setconTexturaToGPU(QGLShaderProgram *program)
{
    //cout << conTextura << endl;
    GLuint conTextLocation = program->uniformLocation("conTextura");
    glUniform1f( conTextLocation, conTextura );
}
