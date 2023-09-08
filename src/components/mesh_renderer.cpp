#include "amuse/components/mesh_renderer.h"

void MeshRenderer::Init() {
	REQUIRE_COMPONENT(Transform);

	transform = &entity->GetComponent<Transform>();
}

void MeshRenderer::Render() {
	if (!mesh) {
		return;
	}

	static gl::Shader* defaultShader = new gl::Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
	
	if (!shader) {
		shader = defaultShader;
	}

	shader->Bind();

	glm::mat4 model = transform->GetModelMatrix();
	shader->SetUniformMatrix4fv("model", &model[0][0]);
	shader->SetCameraUniforms(*Camera::active);
	mesh->DrawTriangles();
	shader->Unbind();
}
