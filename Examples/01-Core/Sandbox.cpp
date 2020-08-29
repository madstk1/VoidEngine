#include <VoidEngine/Void.hpp>

using namespace Void;

class Game : public Application {
private:
protected:
public:
    Game(const ApplicationInfo &info) : Application(info) {}

    void Start() override {
        Light *light = new Light();
        light->position = Vector3(10.f, 10.f, 10.f);
        light->lightColor = Color::White();
        light->intensity = 0.01f;

        for(u32 x = 0; x < 10; x++) {
            for(u32 y = 0; y < 10; y++) {
                Cube *cube = new Cube();

                cube->position = Vector3(x * 2.0f, 0.0f, y * 2.0f);
                cube->rotation = Vector3(6.f, 2.f, 5.f) * (f32)(x + y);
                cube->scale = Vector3(2.0f / (x + y + 1));
            }
        }
    }

    void Update() override {
    }

    void FixedUpdate() override {
        float speed = 5.00f;

        if(Input::GetKeyDown(Keycode::KeyW)) {
            g_Camera->GameObject()->position += g_Camera->Forward() * speed * Time::GetFixedDeltaTime();
        }

        if(Input::GetKeyDown(Keycode::KeyS)) {
            g_Camera->GameObject()->position -= g_Camera->Forward() * speed * Time::GetFixedDeltaTime();
        }

        if(Input::GetKeyDown(Keycode::KeyD)) {
            g_Camera->GameObject()->position += g_Camera->Right() * speed * Time::GetFixedDeltaTime();
        }

        if(Input::GetKeyDown(Keycode::KeyA)) {
            g_Camera->GameObject()->position -= g_Camera->Right() * speed * Time::GetFixedDeltaTime();
        }

        if(Input::GetKeyDown(Keycode::KeySpace)) {
            g_Camera->GameObject()->position += g_Camera->Up() * speed * Time::GetFixedDeltaTime();
        }

        if(Input::GetKeyDown(Keycode::KeyC)) {
            g_Camera->GameObject()->position -= g_Camera->Up() * speed * Time::GetFixedDeltaTime();
        }
    }
};

Application *Void::CreateApplication(ApplicationInfo info) {
    Logger::SetLogLevel(LogLevel::VOID_LOG_LEVEL_DEBUG);

    info.Buffering  = SwapInterval::SingleBuffer;
    info.Background = Color(0.25f, 0.1f, 0.1, 1.0f);

    return new Game(info);
}
