#ifndef VBO_CLASS

#define VBO_CLASS

#include <iostream>
#include <glad/glad.h>
#include "../Buffer.hpp"

/**
 * A class that represents a Vertex Buffer Object (VBO) used to store and send vertices in OpenGL.
 */
class VBO : public Buffer {
    public:
        /**
         * Instantiate a VBO with the vertices and dataset size
         * 
         * @param[in] verticies The list of vertices of the VBO
         * @param[in] size The size of the data set
         */
        VBO(GLfloat verticies[], GLsizeiptr size);
        
        /**
         * Instantiate a VBO with the vertices and dataset size
         * 
         * @param[in] verticies The vector containing the verticies of the VBO
         * @param[in] size The size of the data set
         */
        VBO(std::vector<GLfloat>& verticies, GLsizeiptr size);

        /**
         * Binds the VBO
         */
        void Bind() const override;

        /**
         * Unbinds the VBO
         */
        void Unbind() const override;

        /**
         * Deletes the VBO
         */
        void Delete() override;

    private:
        GLuint id;
};

#endif