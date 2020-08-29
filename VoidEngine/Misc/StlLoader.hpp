#ifndef VOID_MISC_STLLOADER_H__
#define VOID_MISC_STLLOADER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Mesh.hpp>

namespace VOID_NS {
    class StlLoader {
    public:
        static Mesh *LoadStl(std::string);

    protected:
    private:
    };
};

#endif /* VOID_MISC_STLLOADER_H__ */
