#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include <shader/Shader.h>
#include <application/Time.h>
#include <renderer/Renderer.h>
#include <renderer/Buffer.h>
#include <scene/Scene.h>
#include <scene/systems/Systems.h>

class VulkanRenderer : public Renderer{
public:
	VulkanRenderer(SDL_Window* _window);
	void Draw();
	void DrawFrame();
	void Start();
private:
	void CreateVulkanInstance();
	void CreateVulkanPhysicalDevice();
	void CreateDevice();
	void CreateCommandPool();
	void CreateCommandBuffers();
	void CreateSwapChain();
	void CreateDepthImage();
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

	std::unique_ptr<Scene> activeScene;
	std::unique_ptr<Systems> systems;

	struct {
		glm::mat4x4 model = glm::mat4x4(1.0f);
		glm::mat4x4 view = glm::lookAt(glm::vec3(-3.0f, -3.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		glm::mat4x4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 100.0f);
		glm::mat4x4 clip = glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.0f, 0.0f, 0.5f, 1.0f);  // vulkan clip space has inverted y and half z !
		// clang-format on
	}ubo;

	glm::mat4x4 mvpc;
	bool scalingUp;
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

	std::unique_ptr<Buffer> uniformBuffer;
	std::unique_ptr<Buffer> vertexBuffer;

	std::unique_ptr<vk::raii::DescriptorSetLayout> mDescriptorSetLayout;
	std::unique_ptr<vk::raii::PipelineLayout> mPipelineLayout;

	std::unique_ptr<vk::raii::DescriptorPool> mDescriptorPool;
	std::unique_ptr<vk::raii::DescriptorSet> mDescriptorSet;

	std::unique_ptr<vk::raii::RenderPass> mRenderPass;

	std::vector<vk::raii::Framebuffer> mFramebuffers;

	std::vector<Shader> shaders;

	std::unique_ptr<vk::raii::Pipeline> mPipeline;

	std::unique_ptr<vk::raii::Semaphore> mRenderSemaphore, mPresentSemaphore, imageAcquiredSemaphore;
	std::unique_ptr<vk::raii::Fence> mDrawFence;
	std::unique_ptr<vk::raii::CommandPool> mCommandPool;
	std::unique_ptr<vk::raii::CommandBuffers> mCommandBuffers;

	//VkDevice mVulkanDevice;
};

