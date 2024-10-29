#include "Face.hpp"

Face::Face(Mesh* mesh, glm::vec3 pos, GLfloat scale, GLfloat angle, glm::vec3 rotationAxis) : 
    Entity(pos, scale, angle, rotationAxis) {
    this->mesh = mesh;
}

void Face::Draw() const {
    this->mesh->Bind();
    glDrawArrays(GL_TRIANGLES, 0, this->mesh->getMeshDataSize());
    this->mesh->Unbind();
}