#pragma once

class Buffer {
public:
	Buffer(vk::raii::Device&, vk::PhysicalDeviceMemoryProperties&, vk::BufferCreateInfo&, vk::MemoryPropertyFlags);
	uint8_t* map();
	void unmap();
	void copyToBuffer(const void* data, size_t size);

	std::unique_ptr<vk::raii::Buffer> buffer;
	std::unique_ptr<vk::raii::DeviceMemory> memory;
private:
	uint32_t findMemoryType(vk::PhysicalDeviceMemoryProperties&, vk::MemoryRequirements&, vk::MemoryPropertyFlags);

	vk::MemoryRequirements memoryRequirements;
};