#ifndef VOID_CORE_WORLD_H__
#define VOID_CORE_WORLD_H__

#include <VoidEngine/Core/ApplicationInfo.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Time.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Misc/Singleton.hpp>

extern int main(int argc, char **argv);

namespace VOID_NS {
    class Light;

    class World : public Singleton<World> {
    public:
        World();
        ~World();

        inline Vector<Entity *> GetEntities() { return m_WorldObjects; }
        inline Vector<Light *> GetLights() { return m_Lights; }

    protected:
        Vector<Entity *> m_WorldObjects;
        Vector<Light *> m_Lights;

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
