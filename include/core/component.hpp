#pragma once

#include <string>

class Actor;

class Component
{
public:
    Actor *actor;
    bool enabled = true;
    std::string _name;

    virtual void on_start() {}

    virtual void on_update() {}

    virtual void on_inspector() {}
};