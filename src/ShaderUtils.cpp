#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>

#include <shaderc/shaderc.hpp>


std::vector<char> CompileShader(const std::string& source_name,
    shaderc_shader_kind kind,
    const std::string& source,
    bool optimize = false) {
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    // Like -DMY_DEFINE=1
    options.AddMacroDefinition("MY_DEFINE", "1");
    if (optimize) options.SetOptimizationLevel(shaderc_optimization_level_size);

    shaderc::SpvCompilationResult module =
        compiler.CompileGlslToSpv(source, kind, source_name.c_str(), options);

    if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
        std::cerr << module.GetErrorMessage();
        return std::vector<char>();
    }

    return { module.cbegin(), module.cend() };
}
std::vector<char> CompileShaderFromFile(std::string name) {
    std::filesystem::path projectPath = std::filesystem::current_path().parent_path();
    std::filesystem::path fileName(name);
 
    std::string fileType = fileName.extension().string();

    shaderc_shader_kind shaderType = shaderc_glsl_vertex_shader;
    if (fileType == ".vert") shaderType = shaderc_glsl_vertex_shader;
    else if (fileType == ".frag") shaderType = shaderc_glsl_fragment_shader;

    std::string shaderSource;
    std::filesystem::path absolutePath = projectPath / "src" / "shader" / fileName;
    std::ifstream ifs(absolutePath);
    if (ifs.is_open()) shaderSource = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    return CompileShader(name, shaderType, shaderSource, true);
}

std::vector<uint32_t> LoadShaderFromFile(std::string name) {
    std::filesystem::path projectPath = std::filesystem::current_path().parent_path();
    std::filesystem::path fileName(name);

    std::filesystem::path absolutePath = projectPath / "src" / "shader" / fileName;
    std::ifstream ifs(absolutePath, std::ios::binary | std::ios::ate);
    std::vector<uint32_t> shader;
    if (ifs.is_open()) {
        size_t fileSize = ifs.tellg();
        uint32_t numberOfBytes = fileSize / 4;
        uint32_t readByte;
        shader.reserve(numberOfBytes);
        ifs.seekg(0);
        for (int i = 0; i < fileSize/4; i++) {
            ifs.read(reinterpret_cast<char*>(&readByte), sizeof(uint32_t));
            shader.push_back(readByte);
        }
        ifs.close();
    }
    return shader;
}