#include <VoidEngine/Void.hpp>

using namespace Void;

class Game : public App {
public:
    Game() : App("Void Example 01") {}

    void Start() override {
    }
};

int main() {
    Logger::SetLogLevel(Logger::Level::Debug);

    Engine::Get()->SetApp(new Game());
    Engine::Get()->Run();
}
