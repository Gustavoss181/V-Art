// main.cpp - transform animation example

// V-ART example: Moving objects with an idle handler

// This application shows how to use ViewerGlutOGL's idle handler to animate objects.

// Changelog
// Jun 17, 2008 - Bruno de Oliveira Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/light.h>
#include <vart/sphere.h>
#include <vart/box.h>
#include <vart/uniaxialjoint.h>
#include <vart/transform.h>
#include <vart/contrib/viewerglutogl.h>

#include <iostream>
#include <cmath>

using namespace std;

class KeyboardHandler : public VART::ViewerGlutOGL::KbHandler
{
    public:
        KeyboardHandler() {
        }
        virtual void OnKeyDown(int key) {
            switch (key)
            {
                case VART::KEY_UP:
                    dofPtrVec[0]->Move(rotacao);
                    dofPtrVec[1]->Move(-rotacao);
                    dofPtrVec[2]->Move(-rotacao);
                    dofPtrVec[3]->Move(rotacao);
                    break;
                case VART::KEY_DOWN:
                    dofPtrVec[0]->Move(-rotacao);
                    dofPtrVec[1]->Move(rotacao);
                    dofPtrVec[2]->Move(rotacao);
                    dofPtrVec[3]->Move(-rotacao);
                    break;
                default:
                    break;

            }
            viewerPtr->PostRedisplay();
        }
        VART::Dof* dofPtrVec[4];
        VART::Transform* tanque;
        VART::Point4D* frente;
    private:
        float rotacao = 0.01;
};

class MyIHClass : public VART::ViewerGlutOGL::IdleHandler
{
    public:
        MyIHClass() : redRadians(0), greenRadians(0) {}
        virtual ~MyIHClass() {}
        virtual void OnIdle() {
            redRadians += 0.001;
            redRotPtr->MakeZRotation(redRadians);
            greenRadians += 0.001;
            greenRotPtr->MakeYRotation(greenRadians);
            viewerPtr->PostRedisplay();
        }
    //protected:
        VART::Transform* redRotPtr;
        VART::Transform* greenRotPtr;
    private:
        float redRadians;
        float greenRadians;
};

// The application itself:
int main(int argc, char* argv[]){

    VART::ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)

    // create a camera (scene observer)
    VART::Camera camera(VART::Point4D(0,15,20),VART::Point4D(0,15,0),VART::Point4D(0,1,0,0));
    // TRONCO
    VART::Box tronco;
    tronco.MakeBox(-3, 3, 10, 18, -2, 2);
    tronco.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());
    // CABECA
    VART::Transform transCabeca;
    transCabeca.MakeTranslation(VART::Point4D(0, 21, 0));
    VART::Sphere cabeca;
    cabeca.SetRadius(3);
    transCabeca.AddChild(cabeca);
    cabeca.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());
    // PERNA DIREITA
    VART::Box pernaD;
    pernaD.MakeBox(-3, -1, 0, 10, -1, 1);
    pernaD.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());
    // PERNA ESQUERDA
    VART::Box pernaE;
    pernaE.MakeBox(1, 3, 0, 10, -1, 1);
    pernaE.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());
    // BRAÇO DIREITO
    VART::Box bracoD;
    bracoD.MakeBox(-5, -3, 9, 18, -1, 1);
    bracoD.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());
    // BRAÇO ESQUERDO
    VART::Box bracoE;
    bracoE.MakeBox(3, 5, 9, 18, -1, 1);
    bracoE.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());

    // 
    tronco.AddChild(transCabeca);

    VART::UniaxialJoint juntaPernaD;
    VART::Dof* dof1 = juntaPernaD.AddDof(VART::Point4D::X(), VART::Point4D(0, 10, 0), -M_PI/4, M_PI/4);
    juntaPernaD.AddChild(pernaD);
    tronco.AddChild(juntaPernaD);

    VART::UniaxialJoint juntaPernaE;
    VART::Dof* dof2 = juntaPernaE.AddDof(VART::Point4D::X(), VART::Point4D(0, 10, 0), -M_PI/4, M_PI/4);
    juntaPernaE.AddChild(pernaE);
    tronco.AddChild(juntaPernaE);

    VART::UniaxialJoint juntaBracoD;
    VART::Dof* dof3 = juntaBracoD.AddDof(VART::Point4D::X(), VART::Point4D(0, 19, 0), -M_PI/4, M_PI/4);
    juntaBracoD.AddChild(bracoD);
    tronco.AddChild(juntaBracoD);

    VART::UniaxialJoint juntaBracoE;
    VART::Dof* dof4 = juntaBracoE.AddDof(VART::Point4D::X(), VART::Point4D(0, 19, 0), -M_PI/4, M_PI/4);
    juntaBracoE.AddChild(bracoE);
    tronco.AddChild(juntaBracoE);

    scene.AddObject(&tronco);

    KeyboardHandler kbh;
    kbh.dofPtrVec[0] = dof1;
    kbh.dofPtrVec[1] = dof2;
    kbh.dofPtrVec[2] = dof3;
    kbh.dofPtrVec[3] = dof4;

    scene.AddCamera(&camera);
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());

    // Set up the viewer
    viewer.SetKbHandler(&kbh);
    viewer.SetTitle("V-ART Glut idle handler example");
    viewer.SetScene(scene); // attach the scene

    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}
