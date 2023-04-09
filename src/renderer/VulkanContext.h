#pragma once
#include <vulkan/vulkan_raii.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <shader/Shader.h>

class VulkanContext {
public:
	VulkanContext(SDL_Window*);
	void Draw();
private:
	void CreateVulkanInstance();
	void CreateVulkanPhysicalDevice();
	void CreateDevice();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateSwapChain();
	void CreateDepthBuffer();
	void CreateUniformBuffer();
	void CreatePipelineLayout();
	void CreateDescriptorSet();
	void CreateRenderPass();
	void CreateFrameBuffer();
	void CreateSyncStructures();
	void CreateGraphicsPipeline();
	void CreateShaderModules();
	void CreateVertexBuffer();

	uint32_t findMemoryType(vk::MemoryRequirements&, vk::MemoryPropertyFlags);
	SDL_Window* window;

	vk::raii::Context mRAIIContext;
	uint32_t mVulkanAPIVersion;
	vk::Extent2D swapchainExtent;

	std::unique_ptr<vk::PhysicalDeviceMemoryProperties> memoryProperties;
	std::vector<vk::QueueFamilyProperties> queueFamilyProperties;
	uint32_t graphicsQueueFamilyIndex;
	std::unique_ptr<vk::raii::Instance> mInstance;
	std::unique_ptr<vk::raii::PhysicalDevice> mPhysicalDevice;
	std::unique_ptr<vk::raii::Device> mDevice;
	std::unique_ptr<vk::raii::SurfaceKHR> mSurface;
	std::unique_ptr<vk::raii::SwapchainKHR> mSwapchain;

	std::vector<vk::Image> mImages;
	std::vector<vk::raii::ImageView> mImageViews;

	std::unique_ptr<vk::raii::Image> mDepthImage;
	std::unique_ptr<vk::raii::DeviceMemory> mDepthImageMemory;
	std::unique_ptr<vk::raii::ImageView> mDepthImageView;

	std::unique_ptr<vk::raii::DeviceMemory> uniformDataMemory;
	std::unique_ptr<vk::raii::Buffer> mUniformBuffer;

	std::unique_ptr<vk::raii::DescriptorSetLayout> mDescriptorSetLayout;
	std::unique_ptr<vk::raii::PipelineLayout> mPipelineLayout;

	std::unique_ptr<vk::raii::DescriptorPool> mDescriptorPool;
	std::unique_ptr<vk::raii::DescriptorSet> mDescriptorSet;

	std::unique_ptr<vk::raii::RenderPass> mRenderPass;

	std::vector<vk::raii::Framebuffer> mFramebuffers;

	std::vector<Shader> shaders;

	std::unique_ptr<vk::raii::Buffer> mVertexBuffer;
	std::unique_ptr<vk::raii::DeviceMemory> mVertexBufferMemory;

	std::unique_ptr<vk::raii::Pipeline> mPipeline;

	std::unique_ptr<vk::raii::Semaphore> mRenderSemaphore, mPresentSemaphore, imageAcquiredSemaphore;
	std::unique_ptr<vk::raii::Fence> mDrawFence;
	std::unique_ptr<vk::raii::CommandPool> mCommandPool;
	std::unique_ptr<vk::raii::CommandBuffers> mCommandBuffers;

	//VkDevice mVulkanDevice;
};

