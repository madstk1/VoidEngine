#include <fstream>
#include <iostream>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Misc/File.hpp>

namespace VOID_NS {
    std::string Filesytem::ReadFile(std::string path) {
        std::ifstream file(path);
        std::string result;

        file.seekg(0, std::ios::end);
        result.reserve(file.tellg());
        file.seekg(0, std::ios::beg);
        result.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

        return result;
    }
};
