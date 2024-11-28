// main.cpp - from V-ART template application

// This example shows how to use the Arrow class.

// Changelog
// Oct 19, 2012 - Bruno de Oliveira Schneider
// - Removed the unused keyboard handler.
// - Added more arrows.
// Sep 25, 2008 - Bruno de Oliveira Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/light.h>
#include <vart/arrow.h>
#include <vart/meshobject.h>
#include <vart/sphere.h>
#include <vart/contrib/viewerglutogl.h>
#include <vart/contrib/mousecontrol.h>
#include <vart/mesh.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

#define TAM 20

using namespace std;
using namespace VART;

// Define the click handler
class ClickHandlerClass : public VART::MouseControl::ClickHandler
{
    public:
        ClickHandlerClass() {
        }
        virtual ~ClickHandlerClass() {};
        virtual void OnClick() {
            if (mouseCtrlPtr->LastClickIsDown()) {
            }
        }
};

// The application itself:
int main(int argc, char* argv[]) {
    VART::ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static VART::Scene scene; // create a scene
    static VART::ViewerGlutOGL viewer; // create a viewer (application window)
    // ./create a camera (scene observer)
    VART::Camera camera(VART::Point4D(-5,1,-5),VART::Point4D::ORIGIN(),VART::Point4D::Y());

    // // Create some objects
    // VART::Arrow arrowX(2);
    // VART::Arrow arrowY(VART::Point4D::ORIGIN(), VART::Point4D::Y()*2);
    // VART::Arrow arrowZ(VART::Point4D::ORIGIN(), VART::Point4D::Z()*2);

    vector<Point4D> pontos;
    pontos.push_back(Point4D(0,0,0,1));
    pontos.push_back(Point4D(1,0,0,1));
    pontos.push_back(Point4D(1,0,1,1));
    pontos.push_back(Point4D(0,0,1,1));
    pontos.push_back(Point4D(0.5,1,0.5,1));

    MeshObject piramide;
    piramide.SetVertices(pontos);

    piramide.AddFace("1 4 2");
    piramide.AddFace("4 3 2");
    piramide.AddFace("4 0 3");
    piramide.AddFace("0 4 1");
    piramide.AddFace("0 1 2 3");

    piramide.ComputeVertexNormals();

    piramide.SetMaterial(Material::PLASTIC_GREEN());


    //Piramide 2

    vector<Point4D> pontos2;
    pontos2.push_back(Point4D(0,2,0,1));
    pontos2.push_back(Point4D(1,2,0,1));
    pontos2.push_back(Point4D(1,2,1,1));
    pontos2.push_back(Point4D(0,2,1,1));
    pontos2.push_back(Point4D(0.5,1,0.5,1));

    MeshObject piramide2;
    piramide2.SetVertices(pontos2);

    piramide2.AddFace("2 1 0 3");
    piramide2.AddFace("4 0 1");
    piramide2.AddFace("0 4 3");
    piramide2.AddFace("4 1 2");
    piramide2.AddFace("2 3 4");

    piramide2.ComputeVertexNormals();

    piramide2.SetMaterial(Material::PLASTIC_RED());



    // Initialize scene objects
    // arrowX.SetMaterial(VART::Material::PLASTIC_RED());
    // arrowY.SetMaterial(VART::Material::PLASTIC_GREEN());
    // arrowZ.SetMaterial(VART::Material::PLASTIC_BLUE());

    // // Build the scene graph
    // scene.AddObject(&arrowX);
    // scene.AddObject(&arrowY);
    // scene.AddObject(&arrowZ);
    scene.AddObject(&piramide);
    scene.AddObject(&piramide2);

    // Add lights and cameras to the scene
    scene.AddLight(VART::Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);

    // Set up the viewer
    viewer.SetTitle("V-ART arrow example");
    viewer.SetScene(scene); // attach the scene

    // Run application
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    VART::ViewerGlutOGL::MainLoop(); // Enter main loop (event loop) and never return
    return 0;
}
