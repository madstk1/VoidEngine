#include <VoidEngine/Core/Allocator.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Mesh.hpp>
#include <VoidEngine/Misc/ModelLoader.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace VOID_NS {
    static Assimp::Importer m_Importer;

    void ProcessNode(Mesh *, const aiScene *, aiNode *);
    void ProcessMesh(Mesh *, const aiScene *, aiMesh *);

    Mesh *ModelLoader::LoadModel(std::string path) {
        Mesh *mesh = Allocator::Allocate<Mesh>();
        const aiScene *scene = m_Importer.ReadFile(
            path,
            aiProcess_Triangulate |
            aiProcess_GenSmoothNormals |
            aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace
        );

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Logger::Error("Failed to load model: %s, %s", path.c_str(), m_Importer.GetErrorString());
            return nullptr;
        }

        ProcessNode(mesh, scene, scene->mRootNode);

        return mesh;
    }

    void ProcessNode(Mesh *mesh, const aiScene *scene, aiNode *node) {
        for(u32 i = 0; i < node->mNumMeshes; i++) {
            ProcessMesh(mesh, scene, scene->mMeshes[node->mMeshes[i]]);
        }

        for(u32 i = 0; i < node->mNumChildren; i++) {
            ProcessNode(mesh, scene, node->mChildren[i]);
        }
    }

    void ProcessMesh(Mesh *mesh, const aiScene *scene, aiMesh *aim) {
        for(u32 i = 0; i < aim->mNumVertices; i++) {
            Vertex v;

            v.position.x = aim->mVertices[i].x;
            v.position.y = aim->mVertices[i].y;
            v.position.z = aim->mVertices[i].z;

            if(aim->HasNormals()) {
                v.normal.x = aim->mNormals[i].x;
                v.normal.y = aim->mNormals[i].y;
                v.normal.z = aim->mNormals[i].z;
            } else {
                v.normal = {0, 0, 0};
            }

            if(aim->mTextureCoords[0]) {
                /* Texcoords */
                v.texCoords.x = aim->mTextureCoords[0][i].x;
                v.texCoords.y = aim->mTextureCoords[0][i].y;

                /* Tangents */
                v.tangents.x = aim->mTangents[i].x;
                v.tangents.y = aim->mTangents[i].y;
                v.tangents.z = aim->mTangents[i].z;

                /* Bitangents */
                v.bitangents.x = aim->mBitangents[i].x;
                v.bitangents.y = aim->mBitangents[i].y;
                v.bitangents.z = aim->mBitangents[i].z;
            } else {
                v.texCoords = {0, 0};
            }
            mesh->vertices.push_back(v);
        }

        for(u32 i = 0; i < aim->mNumFaces; i++) {
            aiFace face = aim->mFaces[i];
            for(u32 j = 0; j < face.mNumIndices; j++) {
                mesh->indices.push_back(face.mIndices[j]);
            }
        }
    }
};
