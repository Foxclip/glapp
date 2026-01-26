#pragma once

#include <map>
#include "glvis/rectangle.h"
#include "glvis/circle.h"
#include "glvis/vertex_array.h"
#include "glvis/texture.h"
#include "glvis/render_texture.h"
#include "glvis/window.h"
#include "glvis/view.h"

using namespace glvis;

namespace glapp {

class App {

public:
    App(int width, int height);
    ~App();
    View& getView();
    void start();
    Texture* addTexture(const std::filesystem::path& path);
    void removeTexture(Texture* texture);
    void removeTexture(const std::filesystem::path& path);
    Rectangle* addRectangle(float width, float height);
    Circle* addCircle(float radius = 0.0f, size_t numSegments = 30);
    VertexArray* addVertexArray(PrimitiveType type, std::size_t vertexCount = 0);

private:
    Window window;
    View view;
    int mouseX = 0;
    int mouseY = 0;
    float mouseXWorld = 0.0f;
    float mouseYWorld = 0.0f;
    bool firstMouse = true;
    bool leftMousePressed = false;
    bool rightMousePressed = false;
    std::vector<std::unique_ptr<Drawable>> drawables;
    std::map<std::string, std::unique_ptr<Texture>> textures;

    void mainLoop();
    void processMouse(double xpos, double ypos);
    void processMousePress(int button, int action, int mods);
    void processMouseScroll(double x, double y);
    void processMouseLeftPress(int x, int y);
    void processMouseRightPress(int x, int y);

};

}
