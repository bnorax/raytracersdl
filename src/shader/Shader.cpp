#include "Shader.h"

Shader::Shader(std::string shaderName, vk::raii::Device& deviceArg) : name{shaderName}, device{deviceArg}
{
    loadShaderFromFile();
}
vk::ShaderModule Shader::getShaderModule()
{
    return **vkModule;
}
void Shader::loadShaderFromFile() {
    std::filesystem::path projectPath = std::filesystem::current_path().parent_path();
    std::filesystem::path absolutePath = projectPath / "resources" / "shaders" / name;

    std::ifstream ifs(absolutePath, std::ios::binary | std::ios::ate);
    if (ifs.is_open())
    {
        size_t size = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        char* shaderCode = new char[size];
        ifs.read(shaderCode, size);
        ifs.close();
        uint32_t* uintArray = reinterpret_cast<uint32_t*>(shaderCode);

        vk::ShaderModuleCreateInfo shaderModuleCreateInfo{
        .flags = vk::ShaderModuleCreateFlags(),
        .codeSize = static_cast<uint32_t>(size),
        .pCode = uintArray
        };
        vkModule = std::make_unique<vk::raii::ShaderModule>(device, shaderModuleCreateInfo);
        delete[]shaderCode;
    }
}