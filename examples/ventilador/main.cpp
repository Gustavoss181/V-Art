// main.cpp - Test application for JointAction

// This application shows how to make simple animation using the class JointAction.

// Changelog
// Oct 19, 2012 - Bruno de Oliveira Schneider
// - Adapted to new keyboard handler methods.
// Jul 15, 2008 - Bruno Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/transform.h>
#include <vart/joint.h>
#include <vart/jointmover.h>
#include <vart/uniaxialjoint.h>
#include <vart/baseaction.h>
#include <vart/jointaction.h>
#include <vart/light.h>
#include <vart/callback.h>
#include <vart/meshobject.h>
#include <vart/sineinterpolator.h>
#include <vart/contrib/viewerglutogl.h>
#include <vart/arrow.h>

#include <iostream>
#include <cmath>

using namespace std;

class MyIHClass : public VART::ViewerGlutOGL::IdleHandler
{
    public:
        MyIHClass() : radians(0) {}
        virtual ~MyIHClass() {}
        virtual void OnIdle() {
            // VART::BaseAction::MoveAllActive();
            radians += M_PI/6;
            cout << eixoBase->GetCurrent() << endl;
            if(eixoBase->GetCurrent() == 0 or eixoBase->GetCurrent() == 1)
                variation *= -1;
            eixoBase->Move(variation);
            rotation->MakeRotation(VART::Point4D(0, 1.237193, 0), VART::Point4D::X(), radians);
            viewerPtr->PostRedisplay();
        }
        VART::Transform* rotation;
        VART::Dof* eixoBase;
    private:
        float radians;
        float variation = -0.005;
};

// The application itself:
int main(int argc, char* argv[])
{
    VART::ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)

    // create a camera (scene observer)
    VART::Camera camera(VART::Point4D(-3,3,-3), VART::Point4D::ORIGIN(), VART::Point4D::Y());
    MyIHClass idleHandler;

    list<VART::MeshObject*> objects;

    // Initialize scene objects
    VART::MeshObject::ReadFromOBJ("fan.obj", &objects);

    VART::MeshObject* helice;
    VART::MeshObject* base;
    VART::MeshObject* grade;
    VART::MeshObject* suporte_eixo;
    VART::MeshObject* eixo;

    // Build up the scene
    // list<VART::MeshObject*>::iterator iter = objects.begin();
    // for (; iter != objects.end(); ++iter) {
    //     cout << (*iter)->GetDescription() << endl;
    //     if((*iter)->GetDescription() == "helice")
    //         helice = (*iter);
    //     else if((*iter)->GetDescription() == "base")
    //         base = (*iter);
    //     else if((*iter)->GetDescription() == "grade")
    //         grade = (*iter);
    //     else if((*iter)->GetDescription() == "suporte-eixo")
    //         suporte_eixo = (*iter);
    //     else if((*iter)->GetDescription() == "eixo")
    //         eixo = (*iter);
    // }

    for ( auto item : objects ) {
        cout << (item)->GetDescription() << endl;
        if((item)->GetDescription() == "helice")
            helice = (item);
        else if((item)->GetDescription() == "base")
            base = (item);
        else if((item)->GetDescription() == "grade")
            grade = (item);
        else if((item)->GetDescription() == "suporte-eixo")
            suporte_eixo = (item);
        else if((item)->GetDescription() == "eixo")
            eixo = (item);
    }
    

    VART::UniaxialJoint eixoBase;
    VART::Dof* dofPtr1 = eixoBase.AddDof(VART::Point4D::Y(), VART::Point4D::ORIGIN(), 0, 110*M_PI/180); // ss gusta
    idleHandler.eixoBase = dofPtr1;
    base->AddChild(eixoBase);
    eixoBase.AddChild(*suporte_eixo);

    VART::Transform rotacaoHelice;

    idleHandler.rotation = &rotacaoHelice;
    suporte_eixo->AddChild(*grade);
    suporte_eixo->AddChild(rotacaoHelice);
    rotacaoHelice.AddChild(*eixo);
    eixo->AddChild(*helice);

    scene.AddObject(base);

    // flechas para referencia
    VART::Arrow arrowX(2);
    VART::Arrow arrowY(VART::Point4D::ORIGIN(), VART::Point4D::Y()*2);
    VART::Arrow arrowZ(VART::Point4D::ORIGIN(), VART::Point4D::Z()*2);
    arrowX.SetMaterial(VART::Material::PLASTIC_RED());
    arrowY.SetMaterial(VART::Material::PLASTIC_GREEN());
    arrowZ.SetMaterial(VART::Material::PLASTIC_BLUE());

    // Build the scene graph
    scene.AddObject(&arrowX);
    scene.AddObject(&arrowY);
    scene.AddObject(&arrowZ);


    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);
    // Build up the scene -- end =========================================================


    // VART::JointAction mover;
    // VART::SineInterpolator interpolator;
    // VART::JointMover* baseMoverPtr = mover.AddJointMover(&eixoBase, 4, interpolator);
    // baseMoverPtr->AddDofMover(VART::Joint::FLEXION, 0, 1, 1);
    // mover.Activate();

    // Set up the viewer
    viewer.SetScene(scene); // attach the scene
    // viewer.SetKbHandler(&kbh);
    viewer.SetIdleHandler(&idleHandler); // attach the idle handler to the viewer
    viewer.SetTitle("JointAction Example");

    //mover.Activate();

    // Run application
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}
