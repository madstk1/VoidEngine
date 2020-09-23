#ifndef VOID_CORE_WORLD_H__
#define VOID_CORE_WORLD_H__

#include <vector>
#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/ECS/Entity.hpp>

extern int main(int argc, char **argv);

namespace VOID_NS {
    class Light;

    class World {
    public:
        World(const ApplicationInfo &);
        ~World();

        inline std::vector<Entity *> GetEntities() { return m_WorldObjects; }
        inline std::vector<Light *> GetLights() { return m_Lights; }

    protected:
        std::vector<Entity *> m_WorldObjects;
        std::vector<Light *> m_Lights;

        void AddGameObject(Entity *);
        void DestroyGameObject(Entity *);

        void Start();
        void Update();
        void FixedUpdate();

        friend int ::main(int argc, char **argv);
        friend Time;
        friend Entity;
        friend Light;
    };
};

#endif /* VOID_CORE_WORLD_H__ */
