#include "VulkanContext.h"
#include  <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

VulkanContext::VulkanContext(SDL_Window* window) : mWindow(window)
{
    mVulkanAPIVersion = mRAIIContext.enumerateInstanceVersion();
    CreateVulkanInstance();
    CreateVulkanPhysicalDevice();
    CreateDevice();
    CreateCommandPool();
    CreateCommandBuffers();
    CreateSwapChain();
    CreateDepthBuffer();
    CreateUniformBuffer();
    CreatePipelineLayout();
    CreateDescriptorSet();
    CreateRenderPass();
}


bool VulkanContext::Initialize()
{
	return false;
}

void VulkanContext::CreateVulkanInstance()
{
    const vk::ApplicationInfo applicationInfo{
        .pApplicationName = "Ray Tracer SDL2 Vulkan",
        .applicationVersion = VK_MAKE_API_VERSION(1, 0, 0, 0),
        .pEngineName = "Very cool engine",
        .engineVersion = VK_MAKE_API_VERSION(1, 0, 0, 0),
        .apiVersion = VK_API_VERSION_1_3,
    };
    uint32_t extensionsCount = 0;


    SDL_Vulkan_GetInstanceExtensions(mWindow, &extensionsCount, nullptr);
    //std::unique_ptr<const char[]> extensionNames = std::make_unique<const char[]>(extensionCount);
    const char** extensionNames = new const char*[extensionsCount];
    SDL_Vulkan_GetInstanceExtensions(mWindow, &extensionsCount, extensionNames);

    const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation",
    "VK_LAYER_LUNARG_monitor"
    };


    vk::InstanceCreateInfo instanceInfo{
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = static_cast<uint32_t>(validationLayers.size()),
        .ppEnabledLayerNames = validationLayers.data(),
        .enabledExtensionCount = extensionsCount,
        .ppEnabledExtensionNames = extensionNames
    };
    mInstance = std::make_unique<vk::raii::Instance>(mRAIIContext, instanceInfo);
}

void VulkanContext::CreateVulkanPhysicalDevice()
{
    vk::raii::PhysicalDevices devices(*mInstance);
    mPhysicalDevice = std::make_unique<vk::raii::PhysicalDevice>(devices.front());

}

void VulkanContext::CreateDevice()
{
    queueFamilyProperties = mPhysicalDevice->getQueueFamilyProperties();
    auto propertyIterator = std::find_if(
        queueFamilyProperties.begin(),
        queueFamilyProperties.end(),
        [](vk::QueueFamilyProperties& qfp) {return qfp.queueFlags & vk::QueueFlagBits::eGraphics ; });
    graphicsQueueFamilyIndex = std::distance(queueFamilyProperties.begin(), propertyIterator);
   
    float queuePriority = 0.0f;

    vk::DeviceQueueCreateInfo deviceQueueInfo{
        .flags = vk::DeviceQueueCreateFlags(),
        .queueFamilyIndex = graphicsQueueFamilyIndex,
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };
   // uint32_t extensionCount = 0;
    //VkExtensionProperties extensionProperties;
    //vkEnumerateDeviceExtensionProperties(**mPhysicalDevice, nullptr, &extensionCount, nullptr);
    //vkEnumerateDeviceExtensionProperties(**mPhysicalDevice, nullptr, &extensionCount, &extensionProperties);


    const char* ext("VK_KHR_swapchain");
    vk::DeviceCreateInfo deviceInfo{
        .flags = vk::DeviceCreateFlags(),
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &deviceQueueInfo,
        .enabledExtensionCount = 1,
        .ppEnabledExtensionNames = &ext
        
    };
    mDevice = std::make_unique<vk::raii::Device>(*mPhysicalDevice, deviceInfo);
}

void VulkanContext::CreateCommandPool()
{
    vk::CommandPoolCreateInfo commandPoolInfo{
        .flags = vk::CommandPoolCreateFlags(),
        .queueFamilyIndex = graphicsQueueFamilyIndex
    };
    mCommandPool = std::make_unique<vk::raii::CommandPool>(*mDevice, commandPoolInfo);
}

void VulkanContext::CreateCommandBuffers()
{
    vk::CommandBufferAllocateInfo commandBufferInfo{
        .commandPool = **mCommandPool,
        .level = vk::CommandBufferLevel::ePrimary,
        .commandBufferCount = 1
    };

    mCommandBuffers = std::make_unique<vk::raii::CommandBuffers>(*mDevice, commandBufferInfo);
}

void VulkanContext::CreateSwapChain()
{
    {
        VkSurfaceKHR _surface;
        SDL_Vulkan_CreateSurface(mWindow, **mInstance, &_surface);
        mSurface = std::make_unique<vk::raii::SurfaceKHR>(*mInstance, _surface);
    }

    uint32_t presentQueueFamilyIndex = mPhysicalDevice->getSurfaceSupportKHR(graphicsQueueFamilyIndex, **mSurface)
        ? graphicsQueueFamilyIndex
        : queueFamilyProperties.size();

    if (presentQueueFamilyIndex == queueFamilyProperties.size())
    {
        // the graphicsQueueFamilyIndex doesn't support present -> look for an other family index that supports both
        // graphics and present
        for (uint32_t i = 0; i < queueFamilyProperties.size(); i++)
        {
            if ((queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics) &&
                mPhysicalDevice->getSurfaceSupportKHR(i, **mSurface))
            {
                graphicsQueueFamilyIndex = i;
                presentQueueFamilyIndex = i;
                break;
            }
        }
        if (presentQueueFamilyIndex == queueFamilyProperties.size())
        {
            // there's nothing like a single family index that supports both graphics and present -> look for an other
            // family index that supports present
            for (size_t i = 0; i < queueFamilyProperties.size(); i++)
            {
                if (mPhysicalDevice->getSurfaceSupportKHR(i, **mSurface))
                {
                    presentQueueFamilyIndex = i;
                    break;
                }
            }
        }
    }
    if ((graphicsQueueFamilyIndex == queueFamilyProperties.size()) || (presentQueueFamilyIndex == queueFamilyProperties.size()))
    {
        throw std::runtime_error("Could not find a queue for graphics or present -> terminating");
    }

    std::vector<vk::SurfaceFormatKHR> formats = mPhysicalDevice->getSurfaceFormatsKHR(**mSurface);
    assert(!formats.empty());
    vk::Format format = (formats[0].format == vk::Format::eUndefined) ? vk::Format::eB8G8R8A8Srgb : formats[1].format;

    vk::SurfaceCapabilitiesKHR surfaceCapabilities = mPhysicalDevice->getSurfaceCapabilitiesKHR(**mSurface);
    vk::Extent2D               swapchainExtent = surfaceCapabilities.currentExtent;

    vk::PresentModeKHR swapchainPresentMode = vk::PresentModeKHR::eFifo;

    vk::SurfaceTransformFlagBitsKHR preTransform = (surfaceCapabilities.supportedTransforms & vk::SurfaceTransformFlagBitsKHR::eIdentity)
        ? vk::SurfaceTransformFlagBitsKHR::eIdentity
        : surfaceCapabilities.currentTransform;

    vk::CompositeAlphaFlagBitsKHR compositeAlpha =
        (surfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePreMultiplied) ? vk::CompositeAlphaFlagBitsKHR::ePreMultiplied
        : (surfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::ePostMultiplied) ? vk::CompositeAlphaFlagBitsKHR::ePostMultiplied
        : (surfaceCapabilities.supportedCompositeAlpha & vk::CompositeAlphaFlagBitsKHR::eInherit) ? vk::CompositeAlphaFlagBitsKHR::eInherit
        : vk::CompositeAlphaFlagBitsKHR::eOpaque;

    vk::SwapchainCreateInfoKHR swapchainInfo{

        .flags = vk::SwapchainCreateFlagsKHR(),
        .surface = **mSurface,
        .minImageCount = surfaceCapabilities.minImageCount,
        .imageFormat = format,
        .imageColorSpace = vk::ColorSpaceKHR::eSrgbNonlinear,
        .imageExtent = swapchainExtent,
        .imageArrayLayers = 1,
        .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
        .imageSharingMode = vk::SharingMode::eExclusive,
        .preTransform = preTransform,
        .compositeAlpha = compositeAlpha,
        .presentMode = swapchainPresentMode,
        .clipped = true
    };
    if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
    {
        // If the graphics and present queues are from different queue families, we either have to explicitly transfer
        // ownership of images between the queues, or we have to create the swapchain with imageSharingMode as
        // VK_SHARING_MODE_CONCURRENT
        uint32_t queueFamilyIndices[2] = { graphicsQueueFamilyIndex, presentQueueFamilyIndex };
        swapchainInfo.imageSharingMode = vk::SharingMode::eConcurrent;
        swapchainInfo.queueFamilyIndexCount = 2;
        swapchainInfo.pQueueFamilyIndices = queueFamilyIndices;
    }

    mSwapchain = std::make_unique<vk::raii::SwapchainKHR>(*mDevice, swapchainInfo);

    std::vector<vk::Image> images = mSwapchain->getImages();
    mImageViews.reserve(images.size());
    vk::ImageViewCreateInfo imageViewInfo{
        .viewType = vk::ImageViewType::e2D,
        .format = format,
        .subresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 }
    };
    for (auto image : images)
    {
        imageViewInfo.image = image;
        mImageViews.push_back(vk::raii::ImageView(*mDevice, imageViewInfo));
    }
}

void VulkanContext::CreateDepthBuffer()
{
    vk::SurfaceCapabilitiesKHR surfaceCapabilities = mPhysicalDevice->getSurfaceCapabilitiesKHR(**mSurface);
    vk::Extent2D               swapchainExtent = surfaceCapabilities.currentExtent;

    const vk::Format depthFormat = vk::Format::eD16Unorm;
    vk::FormatProperties formatProperties = mPhysicalDevice->getFormatProperties(depthFormat);

    vk::ImageTiling tiling;
    if (formatProperties.linearTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment)
    {
        tiling = vk::ImageTiling::eLinear;
    }
    else if (formatProperties.optimalTilingFeatures & vk::FormatFeatureFlagBits::eDepthStencilAttachment)
    {
        tiling = vk::ImageTiling::eOptimal;
    }
    else
    {
        throw std::runtime_error("DepthStencilAttachment is not supported for D16Unorm depth format.");
    }
    vk::ImageCreateInfo imageCreateInfo{

        .imageType = vk::ImageType::e2D,
        .format = depthFormat,
        .extent = vk::Extent3D(swapchainExtent.width, swapchainExtent.height, 1),
        .mipLevels = 1,
        .arrayLayers = 1,
        .samples = vk::SampleCountFlagBits::e1,
        .tiling = tiling,
        .usage = vk::ImageUsageFlagBits::eDepthStencilAttachment

    };
    mDepthImage = std::make_unique<vk::raii::Image>(*mDevice, imageCreateInfo);

    vk::MemoryRequirements memoryRequirements = mDepthImage->getMemoryRequirements();
    vk::PhysicalDeviceMemoryProperties memoryProperties = mPhysicalDevice->getMemoryProperties();
    uint32_t typeBits = memoryRequirements.memoryTypeBits;
    uint32_t typeIndex = 0;
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++)
    {
        if ((typeBits & 1) &&
            ((memoryProperties.memoryTypes[i].propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal) == vk::MemoryPropertyFlagBits::eDeviceLocal))
        {
            typeIndex = i;
            break;
        }
        typeBits >>= 1;
    }
    assert(typeIndex != uint32_t(~0));
    vk::MemoryAllocateInfo memoryAllocateInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = typeIndex
    };
    vk::raii::DeviceMemory depthMemory(*mDevice, memoryAllocateInfo);
    mDepthImage->bindMemory(*depthMemory, 0);
    vk::ImageViewCreateInfo imageViewCreateInfo{
        .image = **mDepthImage,
        .viewType = vk::ImageViewType::e2D,
        .format = depthFormat,
        .subresourceRange = { vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1 }
    };
    vk::raii::ImageView depthView(*mDevice, imageViewCreateInfo);
}

void VulkanContext::CreateUniformBuffer()
{
    glm::mat4x4 model = glm::mat4x4(1.0f);
    glm::mat4x4 view = glm::lookAt(glm::vec3(-5.0f, 3.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    glm::mat4x4 projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4x4 clip = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 1.0f);  // vulkan clip space has inverted y and half z !
    // clang-format on
    glm::mat4x4 mvpc = clip * projection * view * model;

    vk::BufferCreateInfo bufferCreateInfo{
        .size = sizeof(mvpc),
        .usage = vk::BufferUsageFlagBits::eUniformBuffer
    };
    mUniformBuffer = std::make_unique<vk::raii::Buffer>(*mDevice, bufferCreateInfo);

    vk::MemoryRequirements memoryRequirements = mUniformBuffer->getMemoryRequirements();

    uint32_t typeIndex = findMemoryType(mPhysicalDevice->getMemoryProperties(),
        memoryRequirements.memoryTypeBits,
        vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    vk::MemoryAllocateInfo memoryAllocateInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = typeIndex
    };
    uniformDataMemory = std::make_unique<vk::raii::DeviceMemory>(*mDevice, memoryAllocateInfo);
    uint8_t* pData = static_cast<uint8_t*>(uniformDataMemory->mapMemory(0, memoryRequirements.size));
    memcpy(pData, &mvpc, sizeof(mvpc));
    uniformDataMemory->unmapMemory();

    mUniformBuffer->bindMemory(**uniformDataMemory, 0);
}

void VulkanContext::CreatePipelineLayout()
{
    vk::DescriptorSetLayoutBinding    descriptorSetLayoutBinding{
        .binding = 0,
        .descriptorType = vk::DescriptorType::eUniformBuffer,\
        .descriptorCount = 1,
        .stageFlags = vk::ShaderStageFlagBits::eVertex
    };
    vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo{
        .bindingCount = 1,
        .pBindings = &descriptorSetLayoutBinding
    };
    mDescriptorSetLayout = std::make_unique<vk::raii::DescriptorSetLayout>(*mDevice, descriptorSetLayoutCreateInfo);
    // create a PipelineLayout using that DescriptorSetLayout
    vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo{
        
        .pSetLayouts = &**mDescriptorSetLayout,
    };
    mPipelineLayout = std::make_unique<vk::raii::PipelineLayout>(*mDevice, pipelineLayoutCreateInfo);
}

void VulkanContext::CreateDescriptorSet()
{
    vk::DescriptorPoolSize poolSize{
        .type = vk::DescriptorType::eUniformBuffer,
        .descriptorCount = 1
    };

    vk::DescriptorPoolCreateInfo descriptorPoolCreateInfo{
        .flags = vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet,
        .maxSets = 1,
        .pPoolSizes = &poolSize,
    };
    mDescriptorPool = std::make_unique<vk::raii::DescriptorPool>(*mDevice, descriptorPoolCreateInfo);

    vk::DescriptorSetAllocateInfo descriptorSetAllocateInfo{
        .descriptorPool = **mDescriptorPool,
        .descriptorSetCount = 1,
        .pSetLayouts = &**mDescriptorSetLayout
    };
    mDescriptorSet = 
        std::make_unique<vk::raii::DescriptorSet>(std::move(vk::raii::DescriptorSets(*mDevice, descriptorSetAllocateInfo).front()));

    vk::DescriptorBufferInfo descriptorBufferInfo{
        .buffer = **mUniformBuffer,
        .offset = 0,
        .range = sizeof(glm::mat4x4)
    };
    
    vk::WriteDescriptorSet writeDescriptorSet{
        .dstSet = **mDescriptorSet,
        .dstBinding = 0,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = vk::DescriptorType::eUniformBuffer,
        .pBufferInfo = &descriptorBufferInfo,   
    };
    
    mDevice->updateDescriptorSets(writeDescriptorSet, nullptr);

}

void VulkanContext::CreateRenderPass()
{
    vk::Format colorFormat = mPhysicalDevice->getSurfaceFormatsKHR(**mSurface).front().format;
    vk::Format depthFormat = vk::Format::eD16Unorm;

    std::array<vk::AttachmentDescription, 2> attachmentDescriptions;
    attachmentDescriptions[0] = vk::AttachmentDescription{
        .format = colorFormat,
        .samples = vk::SampleCountFlagBits::e1,
        .loadOp = vk::AttachmentLoadOp::eClear,
        .storeOp = vk::AttachmentStoreOp::eStore,
        .stencilLoadOp = vk::AttachmentLoadOp::eDontCare,
        .stencilStoreOp = vk::AttachmentStoreOp::eDontCare,
        .initialLayout = vk::ImageLayout::eUndefined,
        .finalLayout = vk::ImageLayout::ePresentSrcKHR
    };
    attachmentDescriptions[1] = vk::AttachmentDescription{
         .format = depthFormat,
         .samples = vk::SampleCountFlagBits::e1,
         .loadOp = vk::AttachmentLoadOp::eClear,
         .storeOp = vk::AttachmentStoreOp::eDontCare,
         .stencilLoadOp = vk::AttachmentLoadOp::eDontCare,
         .stencilStoreOp = vk::AttachmentStoreOp::eDontCare,
         .initialLayout = vk::ImageLayout::eUndefined,
         .finalLayout = vk::ImageLayout::eDepthStencilAttachmentOptimal
    };

    vk::AttachmentReference colorReference(0, vk::ImageLayout::eColorAttachmentOptimal);
    vk::AttachmentReference depthReference(1, vk::ImageLayout::eDepthStencilAttachmentOptimal);
    vk::SubpassDescription  subpass{
        .pipelineBindPoint = vk::PipelineBindPoint::eGraphics,
        .pColorAttachments = &colorReference,
        .pDepthStencilAttachment = &depthReference
    
    };
    vk::RenderPassCreateInfo renderPassCreateInfo{
        .attachmentCount = attachmentDescriptions.size(),
        .pAttachments = attachmentDescriptions.data(),
        .subpassCount = 1,
        .pSubpasses = &subpass
    };
    
    mRenderPass = std::make_unique<vk::raii::RenderPass>(*mDevice, renderPassCreateInfo);
}

uint32_t VulkanContext::findMemoryType(vk::PhysicalDeviceMemoryProperties const& memoryProperties, uint32_t typeBits, vk::MemoryPropertyFlags requirementsMask)
{
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
