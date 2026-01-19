#include <iostream>
#include "glapp/app.h"
#include "glvis/utils.h"
#include "glvis/shader.h"
#include "glvis/glvis_common.h"

namespace glapp {

App::App(int width, int height) {
    START_TRY
    window.create(width, height);
    window.setMouseCallback([this](double xpos, double ypos) {
        processMouse(xpos, ypos);
    });
    window.setMouseButtonCallback([this](int button, int action, int mods) {
        processMousePress(button, action, mods);
    });
    window.setScrollCallback([this](double x, double y) {
        processMouseScroll(x, y);
    });
    END_TRY
}

App::~App() {
    drawables.clear();
    textures.clear();
}

Camera& App::getCamera() {
    return camera;
}

void App::start() {
    START_TRY
    mainLoop();
    END_TRY
}

Texture* App::addTexture(const std::filesystem::path& path) {
    std::unique_ptr<Texture> texture = std::make_unique<Texture>(path);
    Texture* texturePtr = texture.get();
    textures.emplace(path.string(), std::move(texture));
    return texturePtr;
}

void App::removeTexture(Texture* texture) {
    auto it = textures.find(texture->getPath().string());
    if (it != textures.end()) {
        textures.erase(it);
    }
}

void App::removeTexture(const std::filesystem::path& path) {
    textures.erase(path.string());
}

Rectangle* App::addRectangle(float width, float height) {
    std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(width, height);
    Rectangle* rectPtr = rect.get();
    drawables.push_back(std::move(rect));
    return rectPtr;
}

Circle* App::addCircle(float radius, size_t numSegments) {
    std::unique_ptr<Circle> circle = std::make_unique<Circle>(radius, numSegments);
    Circle* circlePtr = circle.get();
    drawables.push_back(std::move(circle));
    return circlePtr;
}

VertexArray* App::addVertexArray(PrimitiveType type, std::size_t vertexCount) {
    std::unique_ptr<VertexArray> va = std::make_unique<VertexArray>(type, vertexCount);
    VertexArray* vaPtr = va.get();
    drawables.push_back(std::move(va));
    return vaPtr;
}

void App::mainLoop() {
    while (window.isOpen()) {
        window.clear(Color::Black);
        for (auto& drawable : drawables) {
            window.draw(*drawable);
        }
        window.display();
    }
}

void App::processMouse(double xpos, double ypos) {
    if (firstMouse) {
        mouseX = (int)xpos;
        mouseY = (int)ypos;
        mouseXWorld = window.screenToWorld(mouseX, mouseY).x;
        mouseYWorld = window.screenToWorld(mouseX, mouseY).y;
        firstMouse = false;
    }
    float xoffset = (float)xpos - mouseX;
    float yoffset = (float)ypos - mouseY;
    if (rightMousePressed) {
        glm::vec2 offset = glm::vec2(xoffset / camera.getZoom(), yoffset / camera.getZoom());
        camera.setPosition(camera.getPosition() - offset);
    }
    mouseX = (int)xpos;
    mouseY = (int)ypos;
    mouseXWorld = window.screenToWorld(mouseX, mouseY).x;
    mouseYWorld = window.screenToWorld(mouseX, mouseY).y;
}

void App::processMousePress(int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        leftMousePressed = true;
        processMouseLeftPress(mouseX, mouseY);
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftMousePressed = false;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        rightMousePressed = true;
        processMouseRightPress(mouseX, mouseY);
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        rightMousePressed = false;
    }
}

void App::processMouseScroll(double x, double y) {
    float zoomFactor = powf(CAMERA_ZOOM_FACTOR, (float)y);
    camera.setZoom(camera.getZoom() * zoomFactor);
    glm::vec2 mouseWorld = glm::vec2(mouseXWorld, mouseYWorld);
    camera.setPosition((camera.getPosition() - mouseWorld) / zoomFactor + mouseWorld);
}

void App::processMouseLeftPress(int x, int y) {
    glm::vec2 worldPos = window.screenToWorld(x, y);
    std::cout << std::format("Screen: ({}, {}) World: ({}, {})", x, y, worldPos.x, worldPos.y) << std::endl;
}

void App::processMouseRightPress(int x, int y) {
}

}
