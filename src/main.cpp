#include "core/Application.h"
#include "scenes/TestScene.h"
#include "scenes/Assignment1Scene.h"
#include "scenes//Assignment2Scene.h"
#include "scenes/Assignment3.h"
#include "scenes/Assignment4.h"

int main(int argc, char** argv) {
    // Add newly created scenes here so that they show up in the menu.
    std::vector<Scene*> scenes = {new TestScene(), new Assignment1Scene(),
                                  new Assignment2Scene(), new Assignment3(),
                                  new Assignment4()
    };
    Application app(scenes);
    return app.Run();
}
