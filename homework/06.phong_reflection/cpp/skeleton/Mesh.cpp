#include "Mesh.h"

void Mesh::init_buffer_objects() 
{
    // TODO : initialize position, normal, index buffer
    // use your code from the previous assignment

    glGenBuffers(1, &position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mMesh->mNumVertices * 3, mMesh->mVertices, GL_STATIC_DRAW);

    // glGenBuffers(1, &color_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, color_buffer); 
    // glBufferData(GL_ARRAY_BUFFER, sizeof(aiColor4D) * mMesh->mNumVertices * 4, mMesh->mColors[0], GL_STATIC_DRAW);

    for(int i = 0; i < mMesh->mNumFaces; i++)
    {
        aiFace face = mMesh->mFaces[i];
        
        for(int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }  

    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &normal_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mMesh->mNumVertices * 3, &mMesh->mNormals[0], GL_STATIC_DRAW);
}


void Mesh::draw(int loc_a_position, int loc_a_normal)
{
    // TODO : draw a mesh
    // use your code from the previous assignment
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glEnableVertexAttribArray(loc_a_position);
    glVertexAttribPointer(loc_a_position, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glEnableVertexAttribArray(loc_a_normal);
    glVertexAttribPointer(loc_a_normal, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

}
    
void Mesh::print_info()
{
    std::cout << "print mesh info" << std::endl;

    std::cout << "num vertices " << mMesh->mNumVertices << std::endl;
    for (int i = 0; i < mMesh->mNumVertices; ++i)
    {
        aiVector3D vertex = mMesh->mVertices[i];
        std::cout << "  vertex  (" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")" << std::endl;

        if (mMesh->mColors[0] != NULL)
        {
            aiColor4D color = mMesh->mColors[0][i];
            std::cout << "  color  (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")" << std::endl;
        }
    }
}