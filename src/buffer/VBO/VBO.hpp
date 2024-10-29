#ifndef VBO_CLASS

#define VBO_CLASS

#include <iostream>
#include <glad/glad.h>
#include "../Buffer.hpp"

class VBO : public Buffer {
    public:
        VBO(GLfloat verticies[], GLsizeiptr size);
        VBO(std::vector<GLfloat>& verticies, GLsizeiptr size);
        void Bind() const override;
        void Unbind() const override;
        void Delete() override;

    private:
        GLuint id;
};

#endif