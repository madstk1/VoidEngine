#include <VoidEngine/Void.hpp>

using namespace Void;

class Game : public Application {
private:
protected:
public:
    Game(const ApplicationInfo &info) : Application(info) {}

    void Start() override {
        Cube *cube1 = new Cube();
        Cube *cube2 = new Cube();

        cube1->position = Vector3(0, 0, 0);
        cube2->position = Vector3(3, 3, 3);
    }

    void Update() override {
    }

    void FixedUpdate() override {
        float speed = 5.00f;
        Logger::LogInfo("FPS: %f", Logger::GetFramesPerSecond());

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
