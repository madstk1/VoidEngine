#ifndef VOID_ECS_ENTITIES_LIGHT_H__
#define VOID_ECS_ENTITIES_LIGHT_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/ECS/Entity.hpp>
#include <VoidEngine/Math/Color.hpp>

namespace VOID_NS {
    class Light : public Entity {
    public:
        Light() {
            World::Get()->m_Lights.Append(this);
        }

        Color lightColor = Color::White();
        f32 intensity = 1.0f;
        
    protected:
    private:
    };
};

#endif /* VOID_ECS_ENTITIES_LIGHT_H__ */
