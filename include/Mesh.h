#pragma once
#include <GL/glew.h>
namespace opengltut
{
    class Mesh
    {
    public:
        Mesh();

        void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
        void RenderMesh();
        void ClearMesh();

        ~Mesh();

    private:
        GLuint VAO, VBO, IBO;
        GLsizei indexCount;
    };
}