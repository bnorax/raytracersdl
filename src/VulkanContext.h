#pragma once
#include <vulkan/vulkan_raii.hpp>
#include <SDL.h>
#include <SDL_vulkan.h>

class VulkanContext {
public:
	VulkanContext(SDL_Window *window);
	bool Initialize();
private:
	void CreateVulkanInstance();
	void CreateVulkanPhysicalDevice();
	void CreateDevice();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateSwapChain();
	void CreateDepthBuffer();
	void CreateUniformBuffer();
	bool CheckValidationLayerSupport();
	SDL_Window* mWindow;

	vk::raii::Context mRAIIContext;
	uint32_t mVulkanAPIVersion;

	std::vector<vk::QueueFamilyProperties> queueFamilyProperties;
	uint32_t graphicsQueueFamilyIndex;
	std::unique_ptr<vk::raii::Instance> mInstance;
	std::unique_ptr<vk::raii::PhysicalDevice> mPhysicalDevice;
	std::unique_ptr<vk::raii::Device> mDevice;
	std::unique_ptr<vk::raii::CommandPool> mCommandPool;
	std::unique_ptr<vk::raii::CommandBuffers> mCommandBuffers;
	std::unique_ptr<vk::raii::SurfaceKHR> mSurface;
	std::unique_ptr<vk::raii::SwapchainKHR> mSwapchain;
	std::vector<vk::raii::ImageView> mImageViews;
	std::unique_ptr<vk::raii::Image> mDepthImage;
	//VkDevice mVulkanDevice;
};