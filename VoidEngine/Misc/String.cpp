#include <cstring>
#include <VoidEngine/Misc/String.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    std::string String::k_DefaultWhitespace = " \r\n\t";

    const std::string k_LowerCase = "abcdefghijklmnopqrstuvwxyz";
    const std::string k_UpperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    Vector<std::string> String::Split(std::string str, char delimiter) {
        return Split(str, std::string(&delimiter));
    }

    Vector<std::string> String::Split(std::string str, std::string delimiter) {
        Vector<std::string> substrings;
        char *pch = strtok((char *) str.c_str(), delimiter.c_str());

        while(pch) {
            substrings.Append(std::string(pch));
            pch = strtok(nullptr, delimiter.c_str());
        }
        return substrings;
    }

    std::string String::TrimStart(std::string str, std::string whitespace) {
        str.erase(0, str.find_first_not_of(whitespace));
        return str;
    }

    std::string String::TrimEnd(std::string str, std::string whitespace) {
        str.erase(str.find_last_not_of(whitespace) + 1);
        return str;
    }

    std::string String::Trim(std::string str, std::string whitespace) {
        return String::TrimEnd(String::TrimStart(str, whitespace), whitespace);
    }

    std::string String::PadLeft(std::string str, u32 width, char c) {
        for(u32 i = str.length(); i < width - 1; i++) {
            str = c + str;
        }
        return str;
    }

    std::string String::PadRight(std::string str, u32 width, char c) {
        for(u32 i = str.length(); i < width - 1; i++) {
            str += c;
        }
        return str;
    }

    std::string String::ToLower(std::string str) {
        for(u32 i = 0; i < str.length(); i++) {
            for(u32 j = 0; j < k_UpperCase.length(); j++) {
                if(str[i] == k_UpperCase[j]) {
                    str[i] += 32;
                }
            }
        }
        return str;
    }
    
    std::string String::ToUpper(std::string str) {
        for(u32 i = 0; i < str.length(); i++) {
            for(u32 j = 0; j < k_LowerCase.length(); j++) {
                if(str[i] == k_LowerCase[j]) {
                    str[i] -= 32;
                }
            }
        }
        return str;
    }
    

    bool String::Contains(std::string str, char c) {
        return Contains(str, std::string(&c));
    }

    bool String::Contains(std::string str, std::string c) {
        const char *pch = strstr(str.c_str(), c.c_str());
        return (pch != nullptr);
    }

    bool String::StartsWith(std::string str, char sub) {
        return StartsWith(str, std::string(&sub));
    }

    bool String::StartsWith(std::string str, std::string sub) {
        u64 pos = str.find(sub);
        return pos == 0;
    }

    bool String::EndsWith(std::string str, char sub) {
        return EndsWith(str, std::string(&sub));
    }

    bool String::EndsWith(std::string str, std::string sub) {
        u64 pos = str.find(sub);
        return pos == (str.length() - sub.length());
    }

    bool String::IsEmpty(std::string str) {
        return str.length() <= 0;
    }

    bool String::Length(std::string str) {
        return str.length();
    }
};
