#pragma once
#include <vulkan/vulkan_raii.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

class VulkanContext {
public:
	VulkanContext(SDL_Window *window);
	bool Initialize();
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

	uint32_t findMemoryType(vk::PhysicalDeviceMemoryProperties const& memoryProperties, uint32_t typeBits, vk::MemoryPropertyFlags requirementsMask);
	SDL_Window* mWindow;

	vk::raii::Context mRAIIContext;
	uint32_t mVulkanAPIVersion;
	vk::Extent2D swapchainExtent;

	std::vector<vk::QueueFamilyProperties> queueFamilyProperties;
	uint32_t graphicsQueueFamilyIndex;
	std::unique_ptr<vk::raii::Instance> mInstance;
	std::unique_ptr<vk::raii::PhysicalDevice> mPhysicalDevice;
	std::unique_ptr<vk::raii::Device> mDevice;
	std::unique_ptr<vk::raii::CommandPool> mCommandPool;
	std::unique_ptr<vk::raii::CommandBuffers> mCommandBuffers;
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

	std::unique_ptr<vk::raii::Fence> mRenderFence;
	std::unique_ptr<vk::raii::Semaphore> mRenderSemaphore, mPresentSemaphore;

	//VkDevice mVulkanDevice;
};

