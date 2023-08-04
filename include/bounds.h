#pragma once

#include <glm/glm.hpp>

namespace math {

    class Bounds {
    public:
        Bounds();
        Bounds(glm::vec3 center, glm::vec3 size);

        bool Intersect(Bounds& bounds);
        
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


}