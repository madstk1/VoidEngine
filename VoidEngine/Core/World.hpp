#ifndef VOID_CORE_WORLD_H__
#define VOID_CORE_WORLD_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/ECS/Entity.hpp>

extern int main(int argc, char **argv);

namespace VOID_NS {
    class World {
    public:
        World(const ApplicationInfo &);
        ~World();

        inline std::vector<Entity *> GetEntities() { return m_WorldObjects; }

    protected:
        std::vector<Entity *> m_WorldObjects;

        void AddGameObject(Entity *);
        void DestroyGameObject(Entity *);

        void Start();
        void Update();
        void FixedUpdate();

        friend int ::main(int argc, char **argv);
        friend Time;
        friend Entity;
    };
};

#endif /* VOID_CORE_WORLD_H__ */
