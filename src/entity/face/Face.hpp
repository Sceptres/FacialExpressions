#ifndef FACE_CLASS

#define FACE_CLASS

#include <glad/glad.h>
#include "../Entity.hpp"
#include "../../mesh/Mesh.hpp"

class Face : public Entity {
    public:
        Face(Mesh* mesh, glm::vec3 pos, GLfloat scale, GLfloat angle, glm::vec3 rotationAxis);

    private:
        Mesh* mesh;
        virtual void Draw() const override;
};

#endif