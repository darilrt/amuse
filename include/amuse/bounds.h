#pragma once

#include <glm/glm.hpp>

namespace math {

    class Bounds {
    public:
        Bounds();
        Bounds(glm::vec3 center, glm::vec3 size);

        bool Intersects(Bounds& bounds);

        bool Contains(glm::vec3 point);
        
        void SetCenter(glm::vec3 center);
        
        void SetSize(glm::vec3 size);

        void SetMin(glm::vec3 min);

        void SetMax(glm::vec3 max);

        void SetExtends(glm::vec3 extends);

        void Expand(glm::vec3 point);

        inline glm::vec3 GetCenter()  const { return center; }

        inline glm::vec3 GetSize()    const { return size; }

        inline glm::vec3 GetMin()     const { return min; }

        inline glm::vec3 GetMax()     const { return max; }

        inline glm::vec3 GetExtends() const { return extends; }

    private:
        glm::vec3 center;
        glm::vec3 size;
        glm::vec3 extends;
        glm::vec3 min;
        glm::vec3 max;
    };

    class Bounds2D {
    public:
        Bounds2D();
        Bounds2D(glm::vec2 center, glm::vec2 size);

        bool Intersects(Bounds2D& bounds);

        bool Contains(glm::vec2 point);

        void SetCenter(glm::vec2 center);

        void SetSize(glm::vec2 size);

        void SetMin(glm::vec2 min);

        void SetMax(glm::vec2 max);

        void SetExtends(glm::vec2 extends);

        void Expand(glm::vec2 point);

        inline glm::vec2 GetCenter()  const { return center; }

        inline glm::vec2 GetSize()    const { return size; }

        inline glm::vec2 GetMin()     const { return min; }

        inline glm::vec2 GetMax()     const { return max; }

        inline glm::vec2 GetExtends() const { return extends; }

    private:
        glm::vec2 center;
        glm::vec2 size;
        glm::vec2 extends;
        glm::vec2 min;
        glm::vec2 max;
    };

}