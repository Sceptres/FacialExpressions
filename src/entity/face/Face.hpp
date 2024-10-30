#ifndef FACE_CLASS

#define FACE_CLASS

#include <glad/glad.h>
#include "../Entity.hpp"
#include "../../mesh/Mesh.hpp"

/**
 * The class representing the Face entity
 */
class Face : public Entity {
    public:
        /**
         * Instantiate a Face entity
         * 
         * @param[in, out] mesh The face mesh of the face entity to use in drawing the entity
         * @param[in] pos The initial position of the face
         * @param[in] scale The initial scaling factor of the face
         * @param[in] angle The initial angle to rotate the face by
         * @param[in] rotationAxis The initial rotation axis of the face
         */
        Face(Mesh* mesh, glm::vec3 pos, GLfloat scale, GLfloat angle, glm::vec3 rotationAxis);

    private:
        Mesh* mesh;

        /**
         * The draw method inherited from the entity class representing how the face is drawn.
         */
        virtual void Draw() const override;
};

#endif