#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include "Component.h"

class Mesh : public Component
{
public:
    struct Vertex
    {
        glm::vec3 position;      // Vertex position
        glm::vec3 normal;        // Normal vector
        glm::vec2 texCoord;      // Texture coordinates
        glm::vec3 tangent;       // Tangent vector for normal mapping
        glm::vec3 bitangent;     // Bitangent vector for normal mapping
        glm::vec4 color;         // Optional vertex color
        glm::ivec4 jointIndices; // Optional: Joint indices for skeletal animation
        glm::vec4 jointWeights;  // Optional: Joint weights for skeletal animation
    };

    // Constructor
    Mesh() = default;

    // Add vertices and indices
    void SetVertices(const std::vector<Vertex> &vertices)
    {
        this->vertices = vertices;
    }

    void SetIndices(const std::vector<uint32_t> &indices)
    {
        this->indices = indices;
    }

    const std::vector<Vertex> &GetVertices() const
    {
        return vertices;
    }

    std::vector<Vertex> &GetVertexData()
    {
        return vertices;
    }

    const std::vector<uint32_t> &GetIndices() const
    {
        return indices;
    }

    bool HasIndices() const
    {
        return !indices.empty();
    }

    // Optional metadata
    void SetName(const std::string &name)
    {
        this->name = name;
    }

    const std::string &GetName() const
    {
        return name;
    }

private:
    std::vector<Vertex> vertices;  // Vertex data
    std::vector<uint32_t> indices; // Index data (optional for indexed drawing)
    std::string name;              // Optional: Mesh name for identification
};