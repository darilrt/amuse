#pragma once

#include "amuse/texture.h"

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gl {

	class Camera {
	public:
		glm::vec3 position;
		glm::quat rotation;
		
		void Begin();
		
		void End();

		void Rotate(glm::vec3 rotation) { this->rotation = glm::quat(rotation) * this->rotation;  }

		void Translate(glm::vec3 translation) { this->position += translation; }

		glm::vec2 ScreenToWorld2D(glm::vec2 screenPosition);

		void SetPerspective(float fov,float near, float far);

		void SetOrthographic(float scale, float near, float far);

		inline void SetPosition(const glm::vec3& position) { this->position = position; }

		inline void SetRotation(const glm::vec3& rotation) { this->rotation = rotation; }

		inline void SetFOV(float fov) { this->fov = fov; }

		inline void SetAspect(float aspect) { this->aspect = aspect; }

		inline void SetNear(float _near) { this->_near = _near; }

		inline void SetFar(float _far) { this->_far = _far; }

		inline void SetScale(float scale) { this->scale = scale; }

		void SetViewport(const glm::vec4& viewport);

		inline void SetRenderTexture(Texture* renderTexture) { this->renderTexture = renderTexture; }

		inline glm::mat4 GetView() const { return view; }

		inline glm::mat4 GetProjection() const { return projection; }

	private:
		float fov;
		float aspect;
		float _near;
		float _far;
		float scale;
		glm::vec4 viewport;

		bool isOrthographic = false;

		glm::mat4 view;
		glm::mat4 projection;

		Texture* renderTexture = nullptr;
	};
}
