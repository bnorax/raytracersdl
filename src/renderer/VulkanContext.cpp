#include "VulkanContext.h"
#include <shader/ShaderUtils.h>
#include <graphics/Vertex.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


static const std::vector<Vertex> coloredCubeData{
    //red face
    {{ -1.0f, -1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 0.0f, 1.0f }},
    {{ -1.0f,  1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 0.0f, 1.0f }},
    {{  1.0f, -1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 0.0f, 1.0f }},
    {{  1.0f, -1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 0.0f, 1.0f }},
    {{ -1.0f,  1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 0.0f, 1.0f }},
    {{  1.0f,  1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 0.0f, 1.0f }},
    //green face                 
    {{ -1.0f, -1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 0.0f, 1.0f }},
    {{  1.0f, -1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 0.0f, 1.0f }},
    {{ -1.0f,  1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 0.0f, 1.0f }},
    {{ -1.0f,  1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 0.0f, 1.0f }},
    {{  1.0f, -1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 0.0f, 1.0f }},
    {{  1.0f,  1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 0.0f, 1.0f }},
    // blue face                 
    {{ -1.0f,  1.0f,  1.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f }},
    {{ -1.0f, -1.0f,  1.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f }},
    {{ -1.0f,  1.0f, -1.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f }},
    {{ -1.0f,  1.0f, -1.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f }},
    {{ -1.0f, -1.0f,  1.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f }},
    {{ -1.0f, -1.0f, -1.0f, 1.0f},    {0.0f, 0.0f, 1.0f, 1.0f }},
    // yellow face               
    {{  1.0f,  1.0f,  1.0f, 1.0f},    {1.0f, 1.0f, 0.0f, 1.0f }},
    {{  1.0f,  1.0f, -1.0f, 1.0f},    {1.0f, 1.0f, 0.0f, 1.0f }},
    {{  1.0f, -1.0f,  1.0f, 1.0f},    {1.0f, 1.0f, 0.0f, 1.0f }},
    {{  1.0f, -1.0f,  1.0f, 1.0f},    {1.0f, 1.0f, 0.0f, 1.0f }},
    {{  1.0f,  1.0f, -1.0f, 1.0f},    {1.0f, 1.0f, 0.0f, 1.0f }},
    {{  1.0f, -1.0f, -1.0f, 1.0f},    {1.0f, 1.0f, 0.0f, 1.0f }},
    // magenta face              
    {{  1.0f,  1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 1.0f, 1.0f }},
    {{ -1.0f,  1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 1.0f, 1.0f }},
    {{  1.0f,  1.0f, -1.0f, 1.0f},    {1.0f, 0.0f, 1.0f, 1.0f }},
    {{  1.0f,  1.0f, -1.0f, 1.0f},    {1.0f, 0.0f, 1.0f, 1.0f }},
    {{ -1.0f,  1.0f,  1.0f, 1.0f},    {1.0f, 0.0f, 1.0f, 1.0f }},
    {{ -1.0f,  1.0f, -1.0f, 1.0f},    {1.0f, 0.0f, 1.0f, 1.0f }},
    // cyan face                 
    {{  1.0f, -1.0f,  1.0f, 1.0f},    {0.0f, 1.0f, 1.0f, 1.0f }},
    {{  1.0f, -1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 1.0f, 1.0f }},
    {{ -1.0f, -1.0f,  1.0f, 1.0f},    {0.0f, 1.0f, 1.0f, 1.0f }},
    {{ -1.0f, -1.0f,  1.0f, 1.0f},    {0.0f, 1.0f, 1.0f, 1.0f }},
    {{  1.0f, -1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 1.0f, 1.0f }},
    {{ -1.0f, -1.0f, -1.0f, 1.0f},    {0.0f, 1.0f, 1.0f, 1.0f }}
};


VulkanContext::VulkanContext(SDL_Window* _window, Time& _time) : window(_window), time{_time}
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
    CreateFrameBuffer();
    CreateSyncStructures();
    CreateShaderModules();
    CreateVertexBuffer();
    CreateGraphicsPipeline();
}

void VulkanContext::Draw()
{
    //std::cout << time.deltaTime()<<std::endl;
    while (vk::Result::eTimeout == mDevice->waitForFences({ **mDrawFence }, VK_TRUE, UINT64_MAX));
    mDevice->resetFences(**mDrawFence);

    vk::Result result;
    uint32_t   imageIndex;
    std::tie(result, imageIndex) = mSwapchain->acquireNextImage(UINT64_MAX, **imageAcquiredSemaphore);
    assert(result == vk::Result::eSuccess);
    assert(imageIndex < mSwapchain->getImages().size());


    auto cmb = &mCommandBuffers->front();
    //cmb->reset();


    std::array<vk::ClearValue, 2> clearValues{};
    clearValues[0].color = vk::ClearColorValue{ .float32 = {{1.0f, 0.3f, 0.3f, 1.0f}} };
    clearValues[1].depthStencil = vk::ClearDepthStencilValue{ .depth = 1.0f, .stencil = 0 };
    cmb->begin({});

    vk::RenderPassBeginInfo renderPassBeginInfo{
        .renderPass = **mRenderPass,
        .framebuffer = *mFramebuffers[imageIndex],
        .renderArea = vk::Rect2D(vk::Offset2D(0, 0), swapchainExtent),
        .clearValueCount = static_cast<uint32_t>(clearValues.size()),
        .pClearValues = clearValues.data()
    };
    cmb->beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
    //cmb->clearColorImage(mImages[imageIndex], vk::ImageLayout::eGeneral, clearValues.data(), );
    cmb->bindPipeline(vk::PipelineBindPoint::eGraphics, **mPipeline);
    cmb->bindDescriptorSets(vk::PipelineBindPoint::eGraphics, **mPipelineLayout, 0, { **mDescriptorSet }, nullptr);
    cmb->bindVertexBuffers(0, { **mVertexBuffer }, { 0 });
    cmb->setViewport(
        0, vk::Viewport(0.0f, 0.0f, static_cast<float>(swapchainExtent.width), static_cast<float>(swapchainExtent.height), 0.0f, 1.0f));
    cmb->setScissor(0, vk::Rect2D(vk::Offset2D(0, 0), swapchainExtent));
    cmb->draw(16*3, 1, 0, 0);
    cmb->endRenderPass();
    cmb->end();



    vk::PipelineStageFlags waitDestinationStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
    vk::SubmitInfo         submitInfo{
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &**imageAcquiredSemaphore,
        .pWaitDstStageMask = &waitDestinationStageMask,
        .commandBufferCount = 1,
        .pCommandBuffers = &**cmb,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &**mRenderSemaphore
    };
    vk::raii::Queue graphicsQueue( *mDevice, graphicsQueueFamilyIndex, 0 );
    vk::raii::Queue presentQueue(*mDevice, graphicsQueueFamilyIndex, 0 );
    graphicsQueue.submit(submitInfo, **mDrawFence);


    vk::PresentInfoKHR presentInfoKHR{
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &**mRenderSemaphore,
        .swapchainCount = 1,
        .pSwapchains = &**mSwapchain,
        .pImageIndices = &imageIndex
    };
    result = presentQueue.presentKHR(presentInfoKHR);
    switch (result)
    {
    case vk::Result::eSuccess: break;
    case vk::Result::eSuboptimalKHR: std::cout << "vk::Queue::presentKHR returned vk::Result::eSuboptimalKHR !\n"; break;
    default: assert(false);  // an unexpected result is returned !
    }
    mDevice->waitIdle();
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //mCommandBuffers->front().reset();
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


    SDL_Vulkan_GetInstanceExtensions(window, &extensionsCount, nullptr);
    //std::unique_ptr<const char[]> extensionNames = std::make_unique<const char[]>(extensionCount);
    const char** extensionNames = new const char*[extensionsCount];
    SDL_Vulkan_GetInstanceExtensions(window, &extensionsCount, extensionNames);

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
    memoryProperties = std::make_unique<vk::PhysicalDeviceMemoryProperties>(mPhysicalDevice->getMemoryProperties());

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

    std::vector<const char*> enabledExtensions = {
        "VK_KHR_swapchain"
    };
    vk::DeviceCreateInfo deviceInfo{
        .flags = vk::DeviceCreateFlags(),
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &deviceQueueInfo,
        .enabledExtensionCount = static_cast<uint32_t>(enabledExtensions.size()),
        .ppEnabledExtensionNames = enabledExtensions.data()
        
    };
    mDevice = std::make_unique<vk::raii::Device>(*mPhysicalDevice, deviceInfo);

}

void VulkanContext::CreateCommandPool()
{
    vk::CommandPoolCreateInfo commandPoolInfo{
        .flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
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
        SDL_Vulkan_CreateSurface(window, **mInstance, &_surface);
        mSurface = std::make_unique<vk::raii::SurfaceKHR>(*mInstance, _surface);
    }

    uint32_t presentQueueFamilyIndex = mPhysicalDevice->getSurfaceSupportKHR(graphicsQueueFamilyIndex, **mSurface)
        ? graphicsQueueFamilyIndex
        : queueFamilyProperties.size();

    if (presentQueueFamilyIndex == queueFamilyProperties.size())
    {
        // the graphicsQueueFamilyIndex doesn't support present -> look for an other family index that supports both
        // graphics and present
        for (size_t i = 0; i < queueFamilyProperties.size(); i++)
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
    vk::Format format = (formats[0].format == vk::Format::eUndefined) ? vk::Format::eB8G8R8A8Srgb : formats[0].format;

    vk::SurfaceCapabilitiesKHR surfaceCapabilities = mPhysicalDevice->getSurfaceCapabilitiesKHR(**mSurface);
    vk::Extent2D               swapchainExtent = surfaceCapabilities.currentExtent;
    vk::PresentModeKHR swapchainPresentMode = vk::PresentModeKHR::eFifoRelaxed;

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

    mImages = mSwapchain->getImages();
    mImageViews.reserve(mImages.size());
    vk::ImageViewCreateInfo imageViewInfo{
        .viewType = vk::ImageViewType::e2D,
        .format = format,
        .subresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 }
    };
    for (auto image : mImages)
    {
        imageViewInfo.image = image;
        mImageViews.push_back(vk::raii::ImageView(*mDevice, imageViewInfo));
    }
}

void VulkanContext::CreateDepthBuffer()
{
    vk::SurfaceCapabilitiesKHR surfaceCapabilities = mPhysicalDevice->getSurfaceCapabilitiesKHR(**mSurface);
    swapchainExtent = surfaceCapabilities.currentExtent;

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
    uint32_t memoryTypeIndex = findMemoryType(memoryRequirements, vk::MemoryPropertyFlagBits::eDeviceLocal);
    vk::MemoryAllocateInfo memoryAllocateInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = memoryTypeIndex
    };
    mDepthImageMemory = std::make_unique<vk::raii::DeviceMemory>(*mDevice, memoryAllocateInfo);
    mDepthImage->bindMemory(**mDepthImageMemory, 0);
    vk::ImageViewCreateInfo imageViewCreateInfo{
        .image = **mDepthImage,
        .viewType = vk::ImageViewType::e2D,
        .format = depthFormat,
        .subresourceRange = { vk::ImageAspectFlagBits::eDepth, 0, 1, 0, 1 }
    };
    mDepthImageView = std::make_unique<vk::raii::ImageView>(*mDevice, imageViewCreateInfo);
}

void VulkanContext::CreateUniformBuffer()
{
    //glm::mat4x4 mvpc = uniformBufferObjects.model * uniformBufferObjects.view * uniformBufferObjects.projection * uniformBufferObjects.clip;
    vk::BufferCreateInfo bufferCreateInfo{
        .size = sizeof(uniformBufferObjects),
        .usage = vk::BufferUsageFlagBits::eUniformBuffer
    };
    mUniformBuffer = std::make_unique<vk::raii::Buffer>(*mDevice, bufferCreateInfo);

    vk::MemoryRequirements memoryRequirements = mUniformBuffer->getMemoryRequirements();
    uint32_t memoryTypeIndex = findMemoryType(memoryRequirements, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    vk::MemoryAllocateInfo memoryAllocateInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = memoryTypeIndex
    };
    uniformDataMemory = std::make_unique<vk::raii::DeviceMemory>(*mDevice, memoryAllocateInfo);
    uint8_t* pData = static_cast<uint8_t*>(uniformDataMemory->mapMemory(0, memoryRequirements.size));
    memcpy(pData, &uniformBufferObjects, sizeof(uniformBufferObjects));
    uniformDataMemory->unmapMemory();

    mUniformBuffer->bindMemory(**uniformDataMemory, 0);
}

void VulkanContext::CreatePipelineLayout()
{
    vk::DescriptorSetLayoutBinding    descriptorSetLayoutBinding{
        .binding = 0,
        .descriptorType = vk::DescriptorType::eUniformBuffer,
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
        .setLayoutCount = 1,
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
        .poolSizeCount = 1,
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
    //vk::Format colorFormat = vk::Format::eB8G8R8A8Srgb;
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
        .colorAttachmentCount = 1,
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

void VulkanContext::CreateFrameBuffer(){
    std::array<vk::ImageView, 2> attachments;
    attachments[1] = **mDepthImageView;
;
    mFramebuffers.reserve(mSwapchain->getImages().size());

    for (auto const& view : mImageViews)
    {
        attachments[0] = *view;
        vk::FramebufferCreateInfo framebufferCreateInfo{
            .renderPass = **mRenderPass,
            .attachmentCount = static_cast<uint32_t>(mImageViews.size()),
            .pAttachments = attachments.data(),
            .width = swapchainExtent.width,
            .height = swapchainExtent.height,
            .layers = 1
        };

        mFramebuffers.push_back(vk::raii::Framebuffer(*mDevice, framebufferCreateInfo));
    }
}

void VulkanContext::CreateSyncStructures()
{
    vk::FenceCreateInfo fenceCreateInfo{
        .flags = vk::FenceCreateFlagBits::eSignaled
    };
    mDrawFence = std::make_unique<vk::raii::Fence>(*mDevice, fenceCreateInfo);

    vk::SemaphoreCreateInfo semaphoreCreateInfo;

    mRenderSemaphore = std::make_unique<vk::raii::Semaphore>(*mDevice, semaphoreCreateInfo);
    mPresentSemaphore = std::make_unique<vk::raii::Semaphore>(*mDevice, semaphoreCreateInfo);
    imageAcquiredSemaphore = std::make_unique<vk::raii::Semaphore>(*mDevice, semaphoreCreateInfo);

}

void VulkanContext::CreateGraphicsPipeline()
{
    std::array<vk::PipelineShaderStageCreateInfo, 2> pipelineShaderStageCreateInfos = {
      vk::PipelineShaderStageCreateInfo{.stage = vk::ShaderStageFlagBits::eVertex, .module = shaders[0].GetShaderModule(), .pName = "main"},
      vk::PipelineShaderStageCreateInfo{.stage = vk::ShaderStageFlagBits::eFragment, .module = shaders[1].GetShaderModule(), .pName = "main"}
    };
    vk::VertexInputBindingDescription                  vertexInputBindingDescription(0, sizeof(Vertex), vk::VertexInputRate::eVertex);
    std::array<vk::VertexInputAttributeDescription, 2> vertexInputAttributeDescriptions = {
      vk::VertexInputAttributeDescription(0, 0, vk::Format::eR32G32B32A32Sfloat, 0),
      vk::VertexInputAttributeDescription(1, 0, vk::Format::eR32G32B32A32Sfloat, 16)
    };

    vk::PipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo{  
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &vertexInputBindingDescription,    // vertexBindingDescriptions
        .vertexAttributeDescriptionCount = 2,// flags
        .pVertexAttributeDescriptions = vertexInputAttributeDescriptions.data()  // vertexAttributeDescriptions
    };

    vk::PipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo{.topology =  vk::PrimitiveTopology::eTriangleList };

    vk::PipelineViewportStateCreateInfo pipelineViewportStateCreateInfo{.viewportCount = 1, .scissorCount = 1};

    vk::PipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo{
        .depthClampEnable = false,                        // depthClampEnable
        .rasterizerDiscardEnable = false,                        // rasterizerDiscardEnable
        .polygonMode = vk::PolygonMode::eFill,       // polygonMode
        .cullMode = vk::CullModeFlagBits::eBack,  // cullMode
        .frontFace = vk::FrontFace::eClockwise,    // frontFace
        .depthBiasEnable = false,                        // depthBiasEnable
        .depthBiasConstantFactor = 0.0f,                         // depthBiasConstantFactor
        .depthBiasClamp = 0.0f,                         // depthBiasClamp
        .depthBiasSlopeFactor = 0.0f,                         // depthBiasSlopeFactor
        .lineWidth = 1.0f                          // lineWidth
    };

    vk::PipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo{
        .rasterizationSamples = vk::SampleCountFlagBits::e1  // rasterizationSamples
        // other values can be default
    };

    vk::StencilOpState stencilOpState(vk::StencilOp::eKeep, vk::StencilOp::eKeep, vk::StencilOp::eKeep, vk::CompareOp::eAlways);
    vk::PipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo{                           // flags
        .depthTestEnable = true,                         // depthTestEnable
        .depthWriteEnable = true,                         // depthWriteEnable
        .depthCompareOp = vk::CompareOp::eLessOrEqual,  // depthCompareOp
        .depthBoundsTestEnable = false,                        // depthBoundTestEnable
        .stencilTestEnable = false,                        // stencilTestEnable
        .front = stencilOpState,               // front
        .back = stencilOpState                // back
    };

    vk::ColorComponentFlags colorComponentFlags(vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB |
        vk::ColorComponentFlagBits::eA);
    vk::PipelineColorBlendAttachmentState pipelineColorBlendAttachmentState(false,                   // blendEnable
        vk::BlendFactor::eZero,  // srcColorBlendFactor
        vk::BlendFactor::eZero,  // dstColorBlendFactor
        vk::BlendOp::eAdd,       // colorBlendOp
        vk::BlendFactor::eZero,  // srcAlphaBlendFactor
        vk::BlendFactor::eZero,  // dstAlphaBlendFactor
        vk::BlendOp::eAdd, 
// alphaBlendOp
        colorComponentFlags      // colorWriteMask
    );
    vk::PipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo{                                 // flags
        .logicOpEnable = false,                              // logicOpEnable
        .logicOp = vk::LogicOp::eNoOp,  
        .attachmentCount = 1,
        .pAttachments = &pipelineColorBlendAttachmentState,  // attachments
        .blendConstants = {{ 1.0f, 1.0f, 1.0f, 1.0f }}     // blendConstants
    };

    std::array<vk::DynamicState, 2>    dynamicStates = { vk::DynamicState::eViewport, vk::DynamicState::eScissor };
    vk::PipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo{ .dynamicStateCount = static_cast<uint32_t>(dynamicStates.size()), .pDynamicStates = dynamicStates.data() };

    vk::GraphicsPipelineCreateInfo graphicsPipelineCreateInfo{
        .stageCount = static_cast<uint32_t>(pipelineShaderStageCreateInfos.size()),// flags
        .pStages = pipelineShaderStageCreateInfos.data(),         // stages
        .pVertexInputState = &pipelineVertexInputStateCreateInfo,    // pVertexInputState
        .pInputAssemblyState = &pipelineInputAssemblyStateCreateInfo,  // pInputAssemblyState
        .pViewportState = &pipelineViewportStateCreateInfo,       // pViewportState
        .pRasterizationState = &pipelineRasterizationStateCreateInfo,  // pRasterizationState
        .pMultisampleState = &pipelineMultisampleStateCreateInfo,    // pMultisampleState
        .pDepthStencilState = &pipelineDepthStencilStateCreateInfo,   // pDepthStencilState
        .pColorBlendState = &pipelineColorBlendStateCreateInfo,     // pColorBlendState
        .pDynamicState = &pipelineDynamicStateCreateInfo,        // pDynamicState
        .layout = **mPipelineLayout,                        // layout
        .renderPass = **mRenderPass                             // renderPass
    };
    mPipeline = std::make_unique<vk::raii::Pipeline>(*mDevice, nullptr, graphicsPipelineCreateInfo);

    switch (mPipeline->getConstructorSuccessCode())
    {
    case vk::Result::eSuccess: break;
    case vk::Result::ePipelineCompileRequiredEXT:
        // something meaningfull here
        break;
    default: assert(false);  // should never happen
    }

    //std::vector<uint32_t> vertShader = CompileShaderFromFile("VertexShader.vert");

}

void VulkanContext::CreateShaderModules()
{
    shaders.push_back(Shader("vert.spv", *mDevice));
    shaders.push_back(Shader("frag.spv", *mDevice));
}

void VulkanContext::CreateVertexBuffer()
{

    vk::BufferCreateInfo bufferCreateInfo{
        .size = coloredCubeData.size()*sizeof(Vertex),
        .usage = vk::BufferUsageFlagBits::eVertexBuffer
    };
    mVertexBuffer = std::make_unique<vk::raii::Buffer>(*mDevice, bufferCreateInfo);

    vk::MemoryRequirements memoryRequirements = mVertexBuffer->getMemoryRequirements();
    uint32_t typeIndex = findMemoryType(memoryRequirements, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);
    vk::MemoryAllocateInfo memoryAllocateInfo{
        .allocationSize = memoryRequirements.size,
        .memoryTypeIndex = typeIndex
    };
    
    mVertexBufferMemory = std::make_unique<vk::raii::DeviceMemory>(*mDevice, memoryAllocateInfo);

    uint8_t* pData = static_cast<uint8_t*>(mVertexBufferMemory->mapMemory(0, memoryRequirements.size));
    memcpy(pData, coloredCubeData.data(), coloredCubeData.size() * sizeof(Vertex));
    mVertexBufferMemory->unmapMemory();
    mVertexBuffer->bindMemory(**mVertexBufferMemory, 0);

   // std::shared_ptr<vk::raii::Semaphore> imageAcquiredSemaphore = std::make_shared<vk::raii::Semaphore>(*mDevice, vk::SemaphoreCreateInfo());

   // vk::Result result;
   // uint32_t   imageIndex;
   // std::tie(result, imageIndex) = mSwapchain->acquireNextImage(100'000'000, **imageAcquiredSemaphore);
   // assert(result == vk::Result::eSuccess);
   // assert(imageIndex < mSwapchain->getImages().size());

   // std::array<vk::ClearValue, 2> clearValues{};
   // clearValues[0].color = vk::ClearColorValue{ .float32 = {{0.2f, 0.2f, 0.2f, 0.2f}} };
   // clearValues[1].depthStencil = vk::ClearDepthStencilValue{ .depth = 1.0f, .stencil = 0 };

   // mCommandBuffers->front().begin({});

   // vk::RenderPassBeginInfo renderPassBeginInfo{
   //     .renderPass = **mRenderPass,
   //     .framebuffer = *mFramebuffers[imageIndex],
   //     .renderArea = vk::Rect2D(vk::Offset2D(0, 0), swapchainExtent),
   //     .clearValueCount = static_cast<uint32_t>(clearValues.size()),
   //     .pClearValues = clearValues.data()
   // };
   // 
   // mCommandBuffers->front().beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);

   // mCommandBuffers->front().bindVertexBuffers(0, { **mVertexBuffer }, { 0 });
   // mCommandBuffers->front().endRenderPass();
   // mCommandBuffers->front().end();

   // //std::shared_ptr<vk::raii::Queue> queue = std::make_shared<vk::raii::Queue>(*mDevice, graphicsQueueFamilyIndex);
   // vk::SubmitInfo submitInfo{
   //     .commandBufferCount = 1,
   //     .pCommandBuffers = &*mCommandBuffers->front()
   // };
   // vk::Queue queue = *mDevice->getQueue(graphicsQueueFamilyIndex, 0);
   //// mRenderFence->
   // mDevice->resetFences(**mRenderFence);
   // queue.submit(submitInfo, **mRenderFence);
   // while (vk::Result::eTimeout == mDevice->waitForFences(**mRenderFence, VK_TRUE, 100'000'000)) ;

}

uint32_t VulkanContext::findMemoryType(vk::MemoryRequirements& memoryRequirements, vk::MemoryPropertyFlags requirementsMask)
{
    uint32_t typeBits = memoryRequirements.memoryTypeBits;
    uint32_t typeIndex = 0;
    for (uint32_t i = 0; i < memoryProperties->memoryTypeCount; i++)
    {
        if ((typeBits & 1) && ((memoryProperties->memoryTypes[i].propertyFlags & requirementsMask) == requirementsMask))
        {
            typeIndex = i;
            break;
        }
        typeBits >>= 1;
    }
    assert(typeIndex != 0);
    return typeIndex;
}
