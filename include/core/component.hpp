#pragma once

class Component
{
public:
    virtual void on_start() {}

    virtual void on_update() {}

    virtual void on_inspector() {}
};