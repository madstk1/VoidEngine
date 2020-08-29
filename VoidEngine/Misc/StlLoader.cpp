#include <cstdio>
#include <cstring>

#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Misc/Mesh.hpp>
#include <VoidEngine/Misc/StlLoader.hpp>

#define STL_HEADER_SIZE 80

namespace VOID_NS {
    static void ReadBytes(FILE *fp, void *dest, u64 size, u64 n) {
        u64 bytesRead = fread(dest, size, n, fp);
        
        /* NOTE(max): fread only returns the correct byte-count, when SIZE is 1. */
        if(bytesRead != n) {
            Logger::LogFatal("Invalid STL-file: failed to read bytes.");
        }
    }

    Mesh *StlLoader::LoadStl(std::string path) {
        Mesh *mesh = Allocator::Allocate<Mesh>();
        FILE *fp = fopen(path.c_str(), "rb");

        if(!fp) {
            Logger::LogError("Failed to open STL-file: %s", path.c_str());
            return nullptr;
        }

        uchar header[STL_HEADER_SIZE] = {0};
        u32 nTriangles = 0;

        ReadBytes(fp, header,      sizeof(uchar), STL_HEADER_SIZE);
        ReadBytes(fp, &nTriangles, sizeof(u32), 1);

        for(u32 i = 0; i < nTriangles; i++) {
            Vector3 normal, v1, v2, v3;
            u16 nAttr = 0;

            ReadBytes(fp, &normal, sizeof(Vector3), 1);
            ReadBytes(fp, &v1,     sizeof(Vector3), 1);
            ReadBytes(fp, &v2,     sizeof(Vector3), 1);
            ReadBytes(fp, &v3,     sizeof(Vector3), 1);
            ReadBytes(fp, &nAttr,  sizeof(u16),     1);

            /* Vertices */
            mesh->vertices.push_back(Vertex(v3, Color::White(), normal));
            mesh->vertices.push_back(Vertex(v2, Color::White(), normal));
            mesh->vertices.push_back(Vertex(v1, Color::White(), normal));

            /* Indices */
            mesh->indices.push_back(3 * i + 0);
            mesh->indices.push_back(3 * i + 1);
            mesh->indices.push_back(3 * i + 2);
        }

        return mesh;
    }
};
