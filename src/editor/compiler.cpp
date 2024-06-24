#include "editor/compiler.hpp"

void Compiler::compile(const std::string &source, const std::string &output)
{
    std::string command = cxx + " -c -o " + output + " " + source + " ";
    for (const auto &include : includes)
    {
        command += "-I" + include + " ";
    }
    for (const auto &define : defines)
    {
        command += "-D" + define + " ";
    }
    for (const auto &flag : flags)
    {
        command += flag + " ";
    }
    for (const auto &lib : libs)
    {
        command += "-l" + lib + " ";
    }
    for (const auto &lib_path : lib_paths)
    {
        command += "-L" + lib_path + " ";
    }
    system(command.c_str());
}