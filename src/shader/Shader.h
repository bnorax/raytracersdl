#pragma once

class Shader {
public:
	Shader(std::string shaderName, vk::raii::Device& device);
	vk::ShaderModule getShaderModule();
private:
	void loadShaderFromFile();

	std::string name;
	std::unique_ptr<vk::raii::ShaderModule> vkModule;
	vk::raii::Device& device;
};