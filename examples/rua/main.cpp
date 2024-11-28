#include <vart/scene.h>
#include <vart/light.h>
#include <vart/meshobject.h>
#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>

#include <iostream>
#include <cmath>

using namespace std;

// The application itself:
int main(int argc, char* argv[])
{
    VART::ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)
    // create a camera (scene observer)
    VART::Camera camera(VART::Point4D(0,1.68,-8),VART::Point4D(0, 1.68, 0),VART::Point4D::Y());

    list<VART::MeshObject*> rua;
    VART::MeshObject::ReadFromOBJ("street.obj", &rua);
    for (auto item : rua) {
        item->autoDelete = false;
    }

    list<VART::MeshObject*> poste;
    VART::MeshObject::ReadFromOBJ("light-pole.obj", &poste);
    for (auto item : poste) {
        item->autoDelete = false;
    }
    VART::Transform rotRua;
    rotRua.MakeYRotation(M_PI);
    for (auto item : rua) {
        rotRua.AddChild(*item);
    }

    VART::Transform transRua1, transRua2, transRua3;
    transRua1.MakeTranslation(0, 0, 0);
    transRua1.AddChild(rotRua);
    transRua2.MakeTranslation(0, 0, 16);
    transRua2.AddChild(rotRua);
    transRua3.MakeTranslation(0, 0, 32);
    transRua3.AddChild(rotRua);

    scene.AddObject(&transRua1);
    scene.AddObject(&transRua2);
    scene.AddObject(&transRua3);

    VART::Transform rotPosteX;
    rotPosteX.MakeXRotation(M_PI/2);
    for (auto item : poste) {
        rotPosteX.AddChild(*item);
    }

    VART::Transform rotPosteY;
    rotPosteY.MakeYRotation(M_PI);
    rotPosteY.AddChild(rotPosteX);

    VART::Transform transPoste1, transPoste2, transPoste3, transPoste4;
    transPoste1.MakeTranslation(3.2, 0, 0);
    transPoste1.AddChild(rotPosteY);
    transPoste2.MakeTranslation(-3.2, 0, 0);
    transPoste2.AddChild(rotPosteX);
    transPoste3.MakeTranslation(3.2, 0, 30);
    transPoste3.AddChild(rotPosteY);
    transPoste4.MakeTranslation(-3.2, 0, 30);
    transPoste4.AddChild(rotPosteX);
    
    scene.AddObject(&transPoste1);
    scene.AddObject(&transPoste2);
    scene.AddObject(&transPoste3);
    scene.AddObject(&transPoste4);

    // Add lights and cameras to the scene
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);

    // Set up the viewer
    viewer.SetTitle("Rua com Postes");
    viewer.SetScene(scene); // attach the scene

    // Run application
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop) and never return
    return 0;
}
