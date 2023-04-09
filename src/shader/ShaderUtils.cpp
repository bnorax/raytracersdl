#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <chrono>

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
    std::filesystem::path absolutePath = projectPath / "resources" / "shaders" / fileName;

    auto start = std::chrono::high_resolution_clock::now();
    std::ifstream ifs(absolutePath, std::ios::binary | std::ios::ate);
    if (ifs.is_open())
    {
        size_t size = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        char* shaderCode = new char[size];
        ifs.read(shaderCode, size);
        ifs.close();
        uint32_t* uintArray = reinterpret_cast<uint32_t*>(shaderCode);
        std::vector<uint32_t> shader(uintArray, uintArray + size / 4); // SizeInChars/4 = SizeInUINT32_T  
        delete[]shaderCode;
        return shader;
    }
    return std::vector<uint32_t>();
}