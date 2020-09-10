#ifndef VOID_MISC_MODELLOADER_H__
#define VOID_MISC_MODELLOADER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Mesh.hpp>

namespace VOID_NS {
    class ModelLoader {
    public:
        static Mesh *LoadModel(std::string);

    protected:
    private:
        ModelLoader() {}
        ~ModelLoader() {}
    };
};

#endif /* VOID_MISC_MODELLOADER_H__ */
