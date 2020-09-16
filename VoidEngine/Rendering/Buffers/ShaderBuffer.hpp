#ifndef VOID_RENDERING_BUFFERS_SHADER_BUFFER_H__
#define VOID_RENDERING_BUFFERS_SHADER_BUFFER_H__

#include <VoidEngine/Misc/Mesh.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Rendering/Shader.hpp>
#include <VoidEngine/Rendering/Buffers/Buffer.hpp>

namespace VOID_NS {
    class ShaderBuffer : public Buffer {
    public:
        typedef std::pair<Shader *, Mesh> ContentPair;

        Vector<ContentPair> content;

        ShaderBuffer() {}

        ShaderBuffer(
            BufferUsage usage
        ) : Buffer(usage) {}

        ShaderBuffer(
            Vector<ContentPair> content
        ) : content(content) {}

        ShaderBuffer(
            BufferUsage usage,
            Vector<ContentPair> content
        ) : Buffer(usage), content(content) {}

        ~ShaderBuffer() = default;

        inline void AppendPair(ContentPair pair) { content.Append(pair); }

    protected:
    private:
    };
};

#endif /* VOID_RENDERING_BUFFERS_SHADER_BUFFER_H__ */
