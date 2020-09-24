#include <VoidEngine/Void.hpp>

using namespace Void;

class Game : public Application {
private:
protected:
public:
    Game() {}

    void Start() override {
        std::cout << "nice\n";
    }
};

Void::Application *Void::CreateApplication() {
    return new Game();
}
