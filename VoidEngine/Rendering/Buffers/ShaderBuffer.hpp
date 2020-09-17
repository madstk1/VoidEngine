#ifndef VOID_RENDERING_BUFFERS_SHADER_BUFFER_H__
#define VOID_RENDERING_BUFFERS_SHADER_BUFFER_H__

#include <unordered_map>

#include <VoidEngine/Misc/Material.hpp>
#include <VoidEngine/Misc/Mesh.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Rendering/Buffers/Buffer.hpp>

namespace VOID_NS {
    class ShaderBuffer : public Buffer {
    public:
        struct Content {
            friend ShaderBuffer;

            Material *material;
            Mesh mesh;

        private:
            /* Used for internal handling. */
            u32 indexExtension = 0;
        };

        ShaderBuffer() {}

        ShaderBuffer(
            BufferUsage usage
        ) : Buffer(usage) {}

        ~ShaderBuffer() = default;

        inline void Reset() { m_Content.clear(); }

        inline void AppendPair(Material *mat, Mesh mesh) {
            std::string key = mat->GetName();
            auto iter = m_Content.find(key);

            if(iter != m_Content.end()) {
                /* Handle vertices. */
                for(Vertex v : mesh.vertices) {
                    m_Content[key].mesh.vertices.push_back(v);
                }

                /* Handle indices. */
                for(u32 i : mesh.indices) {
                    m_Content[key].mesh.indices.push_back(i + iter->second.indexExtension);
                }

                /* Handle index extenion. */
                m_Content[key].indexExtension += mesh.vertices.size();
            } else {
                Content c;
                c.material = mat;
                c.mesh = Mesh();
                c.indexExtension = 0;
                
                /* Handle vertices. */
                for(Vertex v : mesh.vertices) {
                    c.mesh.vertices.push_back(v);
                }

                /* Handle indices. */
                for(u32 i : mesh.indices) {
                    c.mesh.indices.push_back(i + c.indexExtension);
                }

                /* Handle index extenion. */
                c.indexExtension += c.mesh.vertices.size();

                m_Content.emplace(std::make_pair(key, c));
            }
        }

        inline std::unordered_map<std::string, Content> GetData() const { return m_Content; }

    protected:
        std::unordered_map<std::string, Content> m_Content;
    };
};

#endif /* VOID_RENDERING_BUFFERS_SHADER_BUFFER_H__ */
