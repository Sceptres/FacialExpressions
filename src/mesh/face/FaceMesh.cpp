#include "FaceMesh.hpp"

const char* FaceMesh::MESH_PATHS[] = {
    "resources/meshes/faces/0.obj",
    "resources/meshes/faces/1.obj",
    "resources/meshes/faces/2.obj",
    "resources/meshes/faces/3.obj",
    "resources/meshes/faces/4.obj",
    "resources/meshes/faces/5.obj",
    "resources/meshes/faces/6.obj",
    "resources/meshes/faces/7.obj",
    "resources/meshes/faces/8.obj",
    "resources/meshes/faces/9.obj",
    "resources/meshes/faces/10.obj",
    "resources/meshes/faces/11.obj",
    "resources/meshes/faces/12.obj",
    "resources/meshes/faces/13.obj",
    "resources/meshes/faces/14.obj",
    "resources/meshes/faces/15.obj",
    "resources/meshes/faces/16.obj",
    "resources/meshes/faces/17.obj",
    "resources/meshes/faces/18.obj",
    "resources/meshes/faces/19.obj",
    "resources/meshes/faces/20.obj",
    "resources/meshes/faces/21.obj",
    "resources/meshes/faces/22.obj",
    "resources/meshes/faces/23.obj",
    "resources/meshes/faces/24.obj",
    "resources/meshes/faces/25.obj",
    "resources/meshes/faces/26.obj",
    "resources/meshes/faces/27.obj",
    "resources/meshes/faces/28.obj",
    "resources/meshes/faces/29.obj",
    "resources/meshes/faces/30.obj",
    "resources/meshes/faces/31.obj",
    "resources/meshes/faces/32.obj",
    "resources/meshes/faces/33.obj",
    "resources/meshes/faces/34.obj"
};

const char* FaceMesh::WEIGHT_PATHS[] = {
    "resources/meshes/weights/0.weights",
    "resources/meshes/weights/1.weights",
    "resources/meshes/weights/2.weights",
    "resources/meshes/weights/3.weights",
    "resources/meshes/weights/4.weights",
    "resources/meshes/weights/5.weights",
    "resources/meshes/weights/6.weights",
    "resources/meshes/weights/7.weights",
    "resources/meshes/weights/8.weights",
    "resources/meshes/weights/9.weights",
    "resources/meshes/weights/10.weights",
    "resources/meshes/weights/11.weights",
};

FaceMesh::FaceMesh() : Mesh("resources/meshes/faces/base.obj") {
    this->LoadMeshesAndWeights();
}

FaceMesh::~FaceMesh() {
    for(const auto& mesh : this->faceMeshes) {
        delete mesh;
    }

    for(const auto& meshWeight : this->faceMeshWeights) {
        delete meshWeight;
    }
}

void FaceMesh::LoadMeshesAndWeights() {
    // Import meshes
    for(const auto& path : FaceMesh::MESH_PATHS) {
        Mesh* mesh = new Mesh(path);
        this->faceMeshes.push_back(mesh);
    }

    // Import weights
    for(const auto& path : FaceMesh::WEIGHT_PATHS) {
        MeshWeight* meshWeight = new MeshWeight(path);
        this->faceMeshWeights.push_back(meshWeight);
    }
}

void FaceMesh::BlendMesh(unsigned int blendIndex) {
    this->ResetBlendMeshData();

    // Get the requested weights
    MeshWeight* faceMeshWeight = this->faceMeshWeights[blendIndex];
    std::vector<float> weights = faceMeshWeight->getWeights();

    // Build new vertices
    std::vector<GLfloat> blendVertices = this->attrib.vertices;
    for(unsigned int i=0; i < weights.size(); i++) {
        float weight = weights[i];
        Mesh* face = this->faceMeshes[i];

        for(unsigned int j=0; j < blendVertices.size(); j++) {
            blendVertices[j] += weight * (face->getAttrib().vertices[j] - Mesh::attrib.vertices[j]);
        }
    }

    // Build mesh to send to GPU using new blend vertices
    for(const auto& shape : this->shapes) {
        for(const auto& face : shape.mesh.indices) {
            unsigned int vid = face.vertex_index;
            unsigned int nid = face.normal_index;

            // Get vertex coordinates
            GLfloat vertX = blendVertices[vid*3];
            GLfloat vertY = blendVertices[vid*3+1];
            GLfloat vertZ = blendVertices[vid*3+2];

            // Get normal coordinates
            GLfloat normX = this->attrib.normals[nid*3];
            GLfloat normY = this->attrib.normals[nid*3+1];
            GLfloat normZ = this->attrib.normals[nid*3+2];

            // Store vertices and normal together for VBO
            this->blendMeshData.push_back(vertX);
            this->blendMeshData.push_back(vertY);
            this->blendMeshData.push_back(vertZ);
            this->blendMeshData.push_back(normX);
            this->blendMeshData.push_back(normY);
            this->blendMeshData.push_back(normZ);
        }
    }

    this->UpdateVBO();
}

void FaceMesh::Reset() {
    this->blendMeshData.assign(Mesh::meshData.begin(), Mesh::meshData.end());
    this->UpdateVBO();
}

void FaceMesh::UpdateVBO() {
    // Update the VBO with the new data
    this->vbo->UpdateData(this->blendMeshData, this->blendMeshData.size() * sizeof(GLfloat));
}

void FaceMesh::ResetBlendMeshData() {
    this->blendMeshData.clear();
}