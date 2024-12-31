#include "GL/glew.h"
#include "Mesh.h"
#include "Shader.h"
#include <iostream>
#include <vector>
#include <string>

class OpenGLRenderer
{
public:
    void Enqueue(const Mesh &mesh)
    {
        renderQueue.push_back(mesh);
    }

    void Render()
    {
        glUseProgram(shaderProgramID); // Ensure the shader program is active

        for (const Mesh &mesh : renderQueue)
        {
            // std::cout << "Rendering: " << mesh.GetName() << std::endl;
            RenderMesh(mesh);
        }

        renderQueue.clear(); // Clear the queue after rendering
    }

    void CompileAndLinkShader(const Shader &shader)
    {
        GLuint program = glCreateProgram();
        std::vector<GLuint> shaderIDs;

        // Compile and attach shaders
        for (const auto &[type, source] : shader.getShaderSources())
        {
            GLuint shaderID = CompileShader(type, source);
            if (shaderID != 0)
            {
                glAttachShader(program, shaderID);
                shaderIDs.push_back(shaderID);
            }
        }

        // Link the shader program
        glLinkProgram(program);
        CheckLinkStatus(program);

        // Clean up individual shaders
        for (GLuint shaderID : shaderIDs)
        {
            glDeleteShader(shaderID);
        }

        shaderProgramID = program;
    }

private:
    GLuint shaderProgramID = 0;    // Active shader program ID
    std::vector<Mesh> renderQueue; // Render queue for meshes

    void RenderMesh(const Mesh &mesh)
    {
        GLuint vao, vbo, ebo;

        // Generate and bind VAO
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        // Generate and bind VBO
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, mesh.GetVertices().size() * sizeof(Mesh::Vertex),
                     mesh.GetVertices().data(), GL_STATIC_DRAW);

        // Generate and bind EBO for indices (if any)
        if (mesh.HasIndices())
        {
            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndices().size() * sizeof(uint32_t),
                         mesh.GetIndices().data(), GL_STATIC_DRAW);
        }

        // Configure vertex attributes
        SetupVertexAttributes();

        // Draw the mesh
        if (mesh.HasIndices())
        {
            glDrawElements(GL_TRIANGLES, mesh.GetIndices().size(), GL_UNSIGNED_INT, nullptr);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, mesh.GetVertices().size());
        }

        // Clean up
        glBindVertexArray(0);
        glDeleteBuffers(1, &vbo);
        if (mesh.HasIndices())
            glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }

    void SetupVertexAttributes()
    {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *)offsetof(Mesh::Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void *)offsetof(Mesh::Vertex, color));
        glEnableVertexAttribArray(5);
    }

    GLuint CompileShader(const std::string &type, const std::string &source)
    {
        GLuint shader = 0;

        // Determine shader type
        if (type == ShaderTypes::Vertex)
            shader = glCreateShader(GL_VERTEX_SHADER);
        else if (type == ShaderTypes::Fragment)
            shader = glCreateShader(GL_FRAGMENT_SHADER);
        else
        {
            std::cerr << "Error: Unknown shader type: " << type << std::endl;
            return 0;
        }

        // Compile the shader
        const char *sourceCStr = source.c_str();
        glShaderSource(shader, 1, &sourceCStr, nullptr);
        glCompileShader(shader);

        // Check compilation status
        if (!CheckCompileStatus(shader, type))
        {
            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    bool CheckCompileStatus(GLuint shader, const std::string &type)
    {
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "Error: Compilation failed for shader type " << type << ".\n"
                      << infoLog << std::endl;
            return false;
        }
        return true;
    }

    void CheckLinkStatus(GLuint program)
    {
        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
            std::cerr << "Error: Shader program linking failed.\n"
                      << infoLog << std::endl;
            glDeleteProgram(program);
        }
        else
        {
            std::cout << "Shader program linked successfully. Program ID: " << program << std::endl;
        }
    }
};
