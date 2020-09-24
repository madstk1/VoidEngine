#ifndef VOID_MISC_STRING_H__
#define VOID_MISC_STRING_H__

#include <vector>
#include <string>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    class String {
    protected:
        static std::string k_DefaultWhitespace;

    public:
        static Vector<std::string> Split(std::string str, char delimiter);
        static Vector<std::string> Split(std::string str, std::string delimiter);

        static std::string TrimStart(std::string str, std::string whitespace = k_DefaultWhitespace);
        static std::string TrimEnd(std::string str, std::string whitespace = k_DefaultWhitespace);
        static std::string Trim(std::string str, std::string whitespace = k_DefaultWhitespace);

        static std::string PadLeft(std::string str, u32 width, char c = ' ');
        static std::string PadRight(std::string str, u32 width, char c = ' ');

        static std::string ToLower(std::string str);
        static std::string ToUpper(std::string str);

        static bool Contains(std::string str, char c);
        static bool Contains(std::string str, std::string c);

        static bool StartsWith(std::string str, char sub);
        static bool StartsWith(std::string str, std::string sub);

        static bool EndsWith(std::string str, char sub);
        static bool EndsWith(std::string str, std::string sub);

        static bool IsEmpty(std::string str);
        static bool Length(std::string str);
    };
};

#endif /* VOID_MISC_STRING_H__ */
