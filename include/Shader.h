#include <string>
#include <map>
#pragma once

namespace ShaderTypes
{
    const std::string Vertex = "vertex";
    const std::string Fragment = "fragment";
    const std::string Geometry = "geometry";
    const std::string TessControl = "tess_control";
    const std::string TessEval = "tess_eval";
    const std::string Compute = "compute";
}

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;

    void addShaderSource(const std::string &type, const std::string &source)
    {
        sources[type] = source;
    }

    const std::map<std::string, std::string> &getShaderSources() const
    {
        return sources;
    }

private:
    std::map<std::string, std::string> sources;
};
