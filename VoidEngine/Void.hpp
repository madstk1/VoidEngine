#pragma once

#include <VoidEngine/Core/Application.hpp>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>
#include <VoidEngine/Core/Engine.hpp>

#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Debug/Signal.hpp>

#include <VoidEngine/Math/Color.hpp>
#include <VoidEngine/Math/Shapes.hpp>
#include <VoidEngine/Math/Linear.hpp>
#include <VoidEngine/Math/Transform.hpp>

#include <VoidEngine/Memory/Allocator.hpp>

#include <VoidEngine/Misc/Delegate.hpp>
#include <VoidEngine/Misc/Delta.hpp>
#include <VoidEngine/Misc/GetSet.hpp>
#include <VoidEngine/Misc/Singleton.hpp>
#include <VoidEngine/Misc/Vector.hpp>
#include <VoidEngine/Misc/Translations.hpp>

#include <VoidEngine/Input/InputManager.hpp>
#include <VoidEngine/Input/Keycodes.hpp>

#include <VoidEngine/Graphics/Shader.hpp>
#include <VoidEngine/Graphics/Renderer.hpp>
#include <VoidEngine/Graphics/ShaderProcessor.hpp>
#include <VoidEngine/Graphics/RendererTypes.hpp>

#if defined(VOID_ENABLE_OPENGL)
#include <VoidEngine/Graphics/GL/Helper.hpp>
#include <VoidEngine/Graphics/GL/Renderer.hpp>
#endif
