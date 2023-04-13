#include "Buffer.h"

Buffer::Buffer(vk::raii::Device& device, vk::PhysicalDeviceMemoryProperties& memoryProperties, vk::BufferCreateInfo& bufferCreateInfo, vk::MemoryPropertyFlags memoryFlags)
{
    buffer = std::make_unique<vk::raii::Buffer>(device, bufferCreateInfo);
    memoryRequirements = buffer->getMemoryRequirements();
    uint32_t memoryTypeIndex = findMemoryType(memoryProperties, memoryRequirements, memoryFlags);
    vk::MemoryAllocateInfo memoryAllocateInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = memoryTypeIndex
    };
    memory = std::make_unique<vk::raii::DeviceMemory>(device, memoryAllocateInfo);
    //Map();
    //Unmap();
    buffer->bindMemory(**memory, 0);
}

uint8_t* Buffer::map()
{
    uint8_t* pData = static_cast<uint8_t*>(memory->mapMemory(0, memoryRequirements.size));
    return pData;
}

void Buffer::unmap()
{
    memory->unmapMemory();
}

void Buffer::copyToBuffer(const void* data, size_t size)
{
    uint8_t* mappedMemory = map();
    memcpy(mappedMemory, data, size);
    unmap();
}

uint32_t Buffer::findMemoryType(vk::PhysicalDeviceMemoryProperties& memoryProperties, vk::MemoryRequirements& memoryRequirements, vk::MemoryPropertyFlags requirementsMask)
{
    uint32_t typeBits = memoryRequirements.memoryTypeBits;
    uint32_t typeIndex = 0;
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        if ((typeBits & 1) && ((memoryProperties.memoryTypes[i].propertyFlags & requirementsMask) == requirementsMask))
        {
            typeIndex = i;
            break;
        }
        typeBits >>= 1;
    }
    assert(typeIndex != 0);
    return typeIndex;
}