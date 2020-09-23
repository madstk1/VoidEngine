#include <VoidEngine/Void.hpp>

using namespace Void;

class Game : public Application {
private:
protected:
public:
    Game(const ApplicationInfo &info) : Application(info) {}

    void Initialize() override {
        g_Camera = new FirstPersonCamera();
    };

    void Start() override {
        Light *light = new Light();
        light->position = Vector3(10.f, 10.f, 10.f);
        light->lightColor = Color::White();
        light->intensity = 600.0f;

        Quad *quad = new Quad();
        quad->position = Vector3(0.f, -3.0f, 0.f);
        quad->scale = Vector3(30, 1, 30);

        for(u32 x = 0; x < 10; x++) {
            for(u32 y = 0; y < 10; y++) {
                Cube *cube = new Cube();

                cube->position = Vector3(x * 2.0f, y * 2.0f, 0.0f);
                cube->scale = Vector3(0.9f);
            }
        }

        Cubemap *skybox = new Cubemap("Skybox 1", {
            Texture::LoadTexture("Right",  "../Resources/Skybox/right.jpg"),
            Texture::LoadTexture("Left",   "../Resources/Skybox/left.jpg"),
            Texture::LoadTexture("Top",    "../Resources/Skybox/top.jpg"),
            Texture::LoadTexture("Bottom", "../Resources/Skybox/bottom.jpg"),
            Texture::LoadTexture("Front",  "../Resources/Skybox/front.jpg"),
            Texture::LoadTexture("Back",   "../Resources/Skybox/back.jpg"),
        });
        g_Renderer->SetSkybox(skybox);
    }

    void Update() override {
    }

    void FixedUpdate() override {
    }
};

Application *Void::CreateApplication(ApplicationInfo info) {
    Logger::SetLogLevel(Logger::Level::Debug);

    info.Buffering  = SwapInterval::SingleBuffer;
    info.Background = Color(0.25f, 0.1f, 0.1, 1.0f);

    return new Game(info);
}
