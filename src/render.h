/*
 * This file is part of vtrace.
 * vtrace is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * vtrace is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with vtrace. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#define MAX_VK_ENUMERATIONS 16
#define FRAMES_IN_FLIGHT 2

#define IS_SUCCESS(res) (res.vk == SUCCESS.vk && res.custom == SUCCESS.custom)

#define PROPAGATE(res)							\
    {									\
	result eval = res;						\
	if (!IS_SUCCESS(eval)) return eval;				\
    }

#define PROPAGATE_VK(res)						\
    {									\
	VkResult eval = res;						\
	if (eval != SUCCESS.vk) {					\
	    result ret = {.vk = eval, .custom = 0};			\
	    return ret;							\
	}								\
    }

#define PROPAGATE_CLEAN(res)						\
    {									\
    result PROPAGATE_CLEANUP_RETURN_VALUE_RESERVED = res;		\
    if (!IS_SUCCESS(eval)) {

#define PROPAGATE_END()					\
    return PROPAGATE_CLEANUP_RETURN_VALUE_RESEREVED;	\
    }							\
    }

#define PROPAGATE_VK_CLEAN(res)						\
    {									\
    VkResult PROPAGATE_CLEANUP_EVAL_VALUE_RESERVED = res;		\
    if (PROPAGATE_CLEANUP_EVAL_VALUE_RESERVED != SUCCESS.vk) {

#define PROPAGATE_VK_END()						\
    result PROPAGATE_CLEANUP_RETURN_VALUE_RESERVED = {.vk = PROPAGATE_CLEANUP_EVAL_VALUE_RESERVED, .custom = 0}; \
    return PROPAGATE_CLEANUP_RETURN_VALUE_RESERVED;			\
    }									\
    }

typedef struct renderer {
    uint32_t window_width;
    uint32_t window_height;
    uint32_t resized;
    GLFWwindow* window;

    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physical;
    VkDevice device;
    VkQueue queue;
    VkSwapchainKHR swapchain;
    uint32_t swapchain_size;
    VkImage* swapchain_images;
    VkFormat swapchain_format;
    VkExtent2D swapchain_extent;
    VkImageView* swapchain_image_views;
    VkPipelineLayout graphics_pipeline_layout;
    VkRenderPass render_pass;
    VkPipeline graphics_pipeline;
    VkFramebuffer* framebuffers;
    VkCommandPool command_pool;
    VkCommandBuffer command_buffer[FRAMES_IN_FLIGHT];
    VkSemaphore image_available_semaphore[FRAMES_IN_FLIGHT];
    VkSemaphore render_finished_semaphore[FRAMES_IN_FLIGHT];
    VkFence frame_in_flight_fence[FRAMES_IN_FLIGHT];
} renderer;

typedef struct swapchain_support {
    VkSurfaceCapabilitiesKHR capabilities;
    VkSurfaceFormatKHR formats[MAX_VK_ENUMERATIONS];
    VkPresentModeKHR present_modes[MAX_VK_ENUMERATIONS];
    uint32_t num_formats;
    uint32_t num_present_modes;
} swapchain_support;

typedef struct result {
    VkResult vk;
    int32_t custom;
} result;

uint64_t entry(void);

result init(void);

result create_instance(void);

result create_surface(void);

result create_physical(void);

int32_t physical_score(VkPhysicalDevice physical);

result physical_check_queue_family(VkPhysicalDevice physical, uint32_t* queue_family, VkQueueFlagBits bits);

result physical_check_extensions(VkPhysicalDevice physical);

result physical_check_swapchain_support(VkPhysicalDevice physical, swapchain_support* support);

result create_device(void);

result create_swapchain(void);

result choose_swapchain_options(swapchain_support* support, VkSurfaceFormatKHR* surface_format, VkPresentModeKHR* present_mode, VkExtent2D* swap_extent);

result create_shader_module(VkShaderModule* module, const char* shader);

result create_graphics_pipeline(void);

result create_framebuffers(void);

result create_command_pool(void);

result create_command_buffers(void);

result record_command_buffer(VkCommandBuffer command_buffer, uint32_t image_index);

result create_synchronization(void);

void cleanup(void);

void recreate_swapchain(void);

void cleanup_swapchain(void);

int32_t render_tick(void);
