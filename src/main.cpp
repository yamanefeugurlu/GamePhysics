#include "core/Application.h"
#include "scenes/TestScene.h"
#include "scenes/Assignment1Scene.h"
#include "scenes//Assignment2Scene.h"

int main(int argc, char** argv) {
    // Add newly created scenes here so that they show up in the menu.
    std::vector<Scene*> scenes = {new TestScene(), new Assignment1Scene(),
                                  new Assignment2Scene()
    };
    Application app(scenes);
    return app.Run();
}
