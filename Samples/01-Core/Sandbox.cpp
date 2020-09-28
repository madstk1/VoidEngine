#include <VoidEngine/Void.hpp>

using namespace Void;

class Game : public App {
public:
    Game() : App("Void Example 01") {}

    void Start() override {
        //new Entity();
        //new Entity();
        //new Entity();
        //new Entity();
    }

    void Update() override {
        Logger::Debug(Engine::Get()->GetTime());
    }
};

int main() {
    Logger::SetLogLevel(Logger::Level::Debug);

    Engine::Get()->SetApp(new Game());
    Engine::Get()->Run();
}
