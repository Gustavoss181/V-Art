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
#include <vart/contrib/viewerglutogl.h>
#include <vart/meshobject.h>
#include <vart/mesh.h>

#include <iostream>
#include <ctime>
#include <cmath>

#define TAM 20

using namespace std;

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


    // unsigned int n = 4;
    vector<VART::Point4D> pontos;

    // for(unsigned int i=0; i<n; i++){
    //     float angulo = i*(2*M_PI/n);
    //     pontos.push_back()
    // }

    pontos.push_back(VART::Point4D(0, 0, 0));
    pontos.push_back(VART::Point4D(2, 0, 0));
    pontos.push_back(VART::Point4D(2, 0, 2));
    pontos.push_back(VART::Point4D(0, 0, 2));

    float angulo = atan(1/sqrt(2));
    pontos.push_back(VART::Point4D(2+2*cos(2*angulo), 2*sin(2*angulo), 0));
    pontos.push_back(VART::Point4D(2+2*cos(2*angulo), 2*sin(2*angulo), 2));
    pontos.push_back(VART::Point4D(1, sqrt(2), 1));

    VART::MeshObject piramide;
    piramide.SetVertices(pontos);
    piramide.AddFace("0 1 2 3");
    piramide.AddFace("0 3 6");
    piramide.AddFace("3 2 6");
    piramide.AddFace("2 1 6");
    piramide.AddFace("1 0 6");


    piramide.AddFace("2 1 4 5");
    piramide.AddFace("4 1 6");
    piramide.AddFace("5 4 6");
    piramide.AddFace("6 2 5");


    piramide.SetMaterial(VART::Material::DARK_PLASTIC_GRAY());
    piramide.ComputeVertexNormals();

    scene.AddObject(&piramide);

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