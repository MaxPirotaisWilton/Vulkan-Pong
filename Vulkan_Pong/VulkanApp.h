#pragma once
#define GLFW_INCLUDE_VULKAN

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL

#include <GLFW/glfw3.h>

#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>
#include <tiny_obj_loader.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <array>
#include <set>
#include <fstream>
#include <unordered_map>

#include "Object.h"
#include "GameManager.h"
#include "InputManager.h"

const uint32_t WIDTH = 1200;
const uint32_t HEIGHT = 900;

static float aspectRatio;

const std::string MODEL_PATH = "models/viking_room.obj";
const std::string TEXTURE_PATH = "textures/viking_room.png";

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
const bool enableValidationLayers = false;
const bool enableDebugConsole = false;
#else
const bool enableValidationLayers = true;
const bool enableDebugConsole = true;
#endif

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};


class VulkanApp
{

    public:
        void run();

    private:

        std::vector<Object*> OBJECTS = {};

        GLFWwindow* window;
        int prevWidth = WIDTH;
        int prevHeight = HEIGHT;

        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;

        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;

        VkQueue graphicsQueue;
        VkQueue presentQueue;

        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        VkRenderPass renderPass;
        VkDescriptorSetLayout descriptorSetLayout;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        short indAndVertBufferIndex = 0;

        short vertexBufferIndex = 0;
        short indexBufferIndex = 0;

        VkBuffer vertexBuffers[2];
        VkDeviceMemory vertexBuffersMemory[2];
        void* vertexDatas[2];

        VkBuffer indexBuffers[2];
        VkDeviceMemory indexBuffersMemory[2];
        void* indexDatas[2];

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;
        std::vector<void*> uniformBuffersMapped;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        uint32_t mipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;

        VkImage colorImage;
        VkDeviceMemory colorImageMemory;
        VkImageView colorImageView;

        VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

        VkSampler textureSampler;

        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;

        bool framebufferResized = false;

        std::vector<VkFramebuffer> swapChainFramebuffers;
        std::vector<VkImageView> swapChainImageViews;

        uint32_t currentFrame = 0;

        std::chrono::steady_clock::time_point previousFrameTime = std::chrono::high_resolution_clock::now();

        int IVFrameRemovalCounter = 0;
        int prevObjectNum = OBJECTS.size();
        short changedIndex = -1;

        GameManager gameManager = GameManager(&OBJECTS);

        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();

        void drawFrame();

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        void createObjects();
        void initializeAllObjects();
        void renderAllObjects(float deltaTime);

        void createInstance();

        void listExtensions();

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        void setupDebugMessenger();

        void createSurface();

        void pickPhysicalDevice();

        void createLogicalDevice();

        void createSwapChain();

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        void cleanupSwapChain();
        void recreateSwapChain();

        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
        void createImageViews();

        void createRenderPass();

        void createDescriptorSetLayout();
        void createDescriptorPool();
        void createDescriptorSets();

        void createGraphicsPipeline();

        VkShaderModule createShaderModule(const std::vector<char>& code);

        void createFramebuffers();

        void createCommandPool();
        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

        void createColorResources();
        void createDepthResources();

        bool hasStencilComponent(VkFormat format);

        VkFormat findDepthFormat();

        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        void createTextureImage();
        void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format,
            VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);

        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        void createTextureImageView();
        void createTextureSampler();
        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);

        void createVertexBuffer(short index);
        void updateVertexBuffer(short index);
        void updateVertexBuffer(short index, VkDeviceSize bufferSize, void* data);

        void createIndexBuffer(short index);
        void updateIndexBuffer(short index);
        void updateIndexBuffer(short index, VkDeviceSize bufferSize, void* data);

        short recreateIndexAndVertexBuffer();
        void removeIndexAndVertexBuffers(short index);

        void createUniformBuffers();
        void updateUniformBuffer(uint32_t currentImage);

        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        void createSyncObjects();

        bool isDeviceSuitable(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        void loadModel();

        std::vector<const char*> getRequiredExtensions();

        bool checkValidationLayerSupport();

        VkSampleCountFlagBits getMaxUsableSampleCount();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

        static std::vector<char> readFile(const std::string& filename);

};

