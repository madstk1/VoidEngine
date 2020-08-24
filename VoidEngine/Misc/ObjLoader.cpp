#include <fstream>
#include <cstring>
#include <stdexcept>

#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Mesh.hpp>
#include <VoidEngine/Misc/ObjLoader.hpp>

namespace VOID_NS {
    static std::string GetCommand(std::string line) {
        std::size_t pos = line.find(" ");
        if(pos == std::string::npos) {
            return line;
        }
        return line.substr(0, pos);
    }

    /* NOTE(max): christ almighty, this method is fucked */
    static void ReadVertex(Mesh *mesh, std::string line) {
         line = line.substr(2, std::string::npos);
        std::vector<float> verts;
        
        char *pch = strtok((char *) line.c_str(), " ");
        while(pch != nullptr) {
            try {
                verts.push_back(std::stof(pch));
            } catch(const std::invalid_argument &ex) {
                std::cerr << "Invalid vertex position: " << pch << std::endl;
            }
            pch = strtok(nullptr, " ");
        }
        
        assert(verts.size() >= 3);
        
        mesh->vertices.push_back(Vertex(glm::vec3(verts[0], verts[1], verts[2])));
    }

    /* NOTE(max): read above */
    static void ReadIndex(Mesh *mesh, std::string line) {
        line = line.substr(2, std::string::npos);
        std::vector<uint32_t> indices;
        
        char *pch = strtok((char *) line.c_str(), " ");
        while(pch != nullptr) {
            std::string p = pch;
            std::size_t slashPos = p.find("/");
            if(slashPos != std::string::npos) {
                p = p.substr(0, slashPos);
            }
        
            try {
                mesh->indices.push_back(std::stoul(p) - 1);
            } catch(const std::invalid_argument &ex) {
                std::cerr << "Invalid index: " << pch << std::endl;
            }
        
            pch = strtok(nullptr, " ");
        }
    }

    Mesh *ObjLoader::LoadObj(std::string path) {
        Mesh *mesh = Allocator::Allocate<Mesh>();

        std::ifstream file(path);
        std::string content;

        if(!file.is_open() || file.fail()) {
            Logger::LogError("Failed to open file: %s", path.c_str());
            return nullptr;
        }

        while(std::getline(file, content)) {
            std::string cmd = GetCommand(content);

            if(cmd == "v") {
                ReadVertex(mesh, content);
            } else if(cmd == "f") {
                ReadIndex(mesh, content);
            }
        }

        file.close();

        VOID_ASSERT(mesh->indices.size() % 3 == 0, "Invalid index count on mesh: %s", path.c_str());

        return mesh;
    }
};
