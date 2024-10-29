#ifndef MESH_CLASS

#define MESH_CLASS

#include <iostream>
#include <tiny_obj_loader.h>
#include "exception/FailedToLoadMeshException.hpp"
#include "../buffer/VBO/VBO.hpp"
#include "../buffer/EBO/EBO.hpp"
#include "../array/VAO.hpp"

class Mesh {
    public:
        Mesh(const char* source);
        ~Mesh();
        void GLInit();
        GLuint getVertexCount();
        GLuint getNormalCount();
        GLuint getMeshDataSize();
        void Bind();
        void Unbind();
        void Delete();

    private:
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::vector<GLfloat> verticies;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> meshData;
        VAO* vao;
        VBO* vbo;
};

#endif