#ifndef FACE_MESH_CLASS
#define FACE_MESH_CLASS

#include "../Mesh.hpp"
#include "../../weights/MeshWeight.hpp"
#include <glad/glad.h>

/**
 * A class representing a blendable face mesh using a base face and 34 other meshes to create new faces
 */
class FaceMesh : public Mesh {
    public:
        /**
         * Initializes a FaceMesh Instance
         */
        FaceMesh();

        /**
         * FaceMesh destructor that clears imported meshes and weights
         */
        ~FaceMesh();
        
        /**
         * Sets the blend of the mesh using an index in the range [0, 11]
         * 
         * @param[in] blendIndex The index of the blend of this mesh. An integer in the range [0, 11]
         */
        void BlendMesh(unsigned int blendIndex);

        /**
         * Resets the mesh to the base mesh
         */
        void Reset();

    private:
        std::vector<GLfloat> blendMeshData;
        std::vector<Mesh*> faceMeshes;
        std::vector<MeshWeight*> faceMeshWeights;

        /**
         * Resets the blend mesh data by clearing it
         */
        void ResetBlendMeshData();

        /**
         * Loads the meshes and weights from the disk
         */
        void LoadMeshesAndWeights();

        /**
         * Updates the mesh VBO with the new blend mesh data
         */
        void UpdateVBO();

        // A list of all the paths to the face mesh obj files
        static const char* MESH_PATHS[];

        // A list of all the paths to the weights files
        static const char* WEIGHT_PATHS[];
};

#endif