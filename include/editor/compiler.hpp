#pragma once

#include <vector>
#include <string>

class Compiler
{
public:
    std::string cxx;
    std::vector<std::string> includes;
    std::vector<std::string> defines;
    std::vector<std::string> flags;
    std::vector<std::string> libs;
    std::vector<std::string> lib_paths;

    void compile(const std::string &source, const std::string &output);
};