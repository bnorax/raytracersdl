#pragma once
#include <vulkan/vulkan_raii.hpp>

class Buffer {
public:
	Buffer(vk::raii::Device&, vk::PhysicalDeviceMemoryProperties&, vk::BufferCreateInfo&, vk::MemoryPropertyFlags);
	uint8_t* Map();
	void Unmap();
	void CopyToBuffer(const void* data, size_t size);
	std::unique_ptr<vk::raii::Buffer> buffer;
	std::unique_ptr<vk::raii::DeviceMemory> memory;
private:
	vk::MemoryRequirements memoryRequirements;
	uint32_t FindMemoryType(vk::PhysicalDeviceMemoryProperties&, vk::MemoryRequirements&, vk::MemoryPropertyFlags);
};