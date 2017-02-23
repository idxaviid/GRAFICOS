#include "Camera.h"

Camera::Camera():
    //obs(glm::vec3(-10.0f,10.0f,10.0f)),
    obs(glm::vec3(-10.0f,10.0f,10.0f)),
    vrp(glm::vec3(0.0f, 0.0f, 0.0f)),
    vup(glm::vec3(0.0f, 1.0f, 0.0f)),
    angleObertura(45.0f), zNear(1.0f), zFar(1000.0f),
    //viewportX(640), viewportY(480)
    viewportX(1024), viewportY(768)
{
}


Camera::Camera(const glm::vec3 &_obs,
               const glm::vec3 &_vrp,
               const glm::vec3 &_vup,
               float _angleObertura,
               float _zNear,
               float _zFar,
               int _viewportX,
               int _viewportY):
    obs(_obs), vrp(_vrp), vup(_vup),
    angleObertura(_angleObertura), zNear(_zNear), zFar(_zFar),
    viewportX(_viewportX), viewportY(_viewportY){
}

void Camera::IniViewProjMatrices()
{

    //  Inicialització de les matrius viewMatrix i projMatrix
    //	Utilitzeu els metodes de lookAt i perspective
    //  que teniu a  glm.h
    //  https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml

    float width = 10.0f;
    float height = 10.0f;
    //  PDF tema04 pagina 54
    //  CALCULO DEL ANGLE DE OBERTURA DE LA CAMARA Y LAS MATRICES MODELVIEW Y PROJECTION
    float aspectRatio = float(viewportX)/float(viewportY);
    width = width * aspectRatio;
    float distance = glm::length(obs - vrp);

    angleObertura = 2.0f * glm::tan( (height / 2.0f) / distance );
    angleObertura = angleObertura * (180.0f/M_PI);

    viewMatrix = glm::lookAt(obs,vrp,vup);
    projMatrix = glm::perspective(angleObertura,aspectRatio,zNear,zFar);

    //projMatrix = glm::perspectiveFov(angleObertura,float(viewportX),float(viewportY),zNear,zFar);


}
