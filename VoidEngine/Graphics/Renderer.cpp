#include <VoidEngine/Graphics/Renderer.hpp>

namespace VOID_NS {
    void Renderer::Initialize() {
        this->InitializeInt();

        this->SetCullFace(CullFace::Front);
        this->SetFrontFace(FrontFace::CW);
        this->SetDepthTest(DepthTest::Less);

        for(const string &ext : this->GetExtensions()) {
            Logger::Debug("[EXT] ", ext);
        }
    }

    void Renderer::Destroy() {
        this->DestroyInt();
    }
    
    void Renderer::Render() {
        this->Clear((ClearFlag) (ClearColor | ClearDepth));

        this->Begin();
        this->Draw();
        this->End();

        this->SwapBuffers();
    }
};
