#ifndef VOID_MISC_OBJLOADER_H__
#define VOID_MISC_OBJLOADER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Mesh.hpp>

namespace VOID_NS {
    class ObjLoader {
    public:
        static Mesh *LoadObj(std::string);

    protected:
    private:
    };
};

#endif /* VOID_MISC_OBJLOADER_H__ */
