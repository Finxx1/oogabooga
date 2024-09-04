const Gfx_Handle GFX_INVALID_HANDLE = 0;

// We wanna pack this at some point
// #Cleanup #Memory why am I doing alignat(16)?
typedef struct alignat(16) Vk_Vertex {
	Vector2 pos;
	Vector3 color;
} Vk_Vertex;

// #Types
typedef struct Vk_QueueFamilyIndices {
	bool has_graphics;
	uint32_t graphics;
	
	bool has_present;
	uint32_t present;
} Vk_QueueFamilyIndices;

typedef struct Vk_Swapchain_Details {
	VkSurfaceCapabilitiesKHR capabilities;
	
	uint32_t format_count;
	VkSurfaceFormatKHR* formats;
	
	uint32_t present_mode_count;
	VkPresentModeKHR* present_modes;
} Vk_Swapchain_Details;

typedef struct Vk_Swapchain {
	uint32_t swapchain_image_count;
	VkImage* swapchain_images;
	VkFormat format;
	VkExtent2D extent;
	VkSwapchainKHR swapchain;
} Vk_Swapchain;

typedef struct Vk_ImageViews {
	uint32_t view_count;
	VkImageView* views;
} Vk_ImageViews;

typedef struct Vk_Framebuffers {
	uint32_t count;
	VkFramebuffer* data;
} Vk_Framebuffers;

typedef struct Vk_Data {
	VkInstance instance;
	VkPhysicalDevice physical_device;
	VkDevice device;
	VkQueue graphics_queue;
	VkQueue present_queue;
	VkSurfaceKHR surface;
	Vk_QueueFamilyIndices family_indices;
	Vk_Swapchain swapchain;
	Vk_ImageViews image_views;
	VkShaderModule vert_shader;
	VkShaderModule frag_shader;
	VkRenderPass render_pass;
	VkPipelineLayout pipeline_layout;
	VkPipeline pipeline;
	Vk_Framebuffers framebuffers;
	VkCommandPool command_pool;
	u64 vertex_buffer_size;
	VkBuffer vertex_buffer;
	VkDeviceMemory vertex_buffer_mem;
	VkCommandBuffer command_buffers[2];
	VkSemaphore image_available[2];
	VkSemaphore render_finished[2];
	VkFence in_flight[2];
	uint32_t frame;
} Vk_Data;

// Commented out values trigger windows defender for some reason
const char* vk_result_table(VkResult r) {
	switch (r) {
	case VK_SUCCESS: return "VK_SUCCESS";
	case VK_NOT_READY: return "VK_NOT_READY";
	case VK_TIMEOUT: return "VK_TIMEOUT";
	case VK_EVENT_SET: return "VK_EVENT_SET";
	case VK_EVENT_RESET: return "VK_EVENT_RESET";
	case VK_INCOMPLETE: return "VK_INCOMPLETE";
	case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
	case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
	case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED";
	case VK_ERROR_DEVICE_LOST: return "VK_ERROR_DEVICE_LOST";
	case VK_ERROR_MEMORY_MAP_FAILED: return "VK_ERROR_MEMORY_MAP_FAILED";
	case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT";
	case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT";
	case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT";
	case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER";
	case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS";
	case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
	case VK_ERROR_FRAGMENTED_POOL: return "VK_ERROR_FRAGMENTED_POOL";
	case VK_ERROR_UNKNOWN: return "VK_ERROR_UNKNOWN";
	case VK_ERROR_OUT_OF_POOL_MEMORY: return "VK_ERROR_OUT_OF_POOL_MEMORY";
	case VK_ERROR_INVALID_EXTERNAL_HANDLE: return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
	case VK_ERROR_FRAGMENTATION: return "VK_ERROR_FRAGMENTATION";
	case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
	case VK_PIPELINE_COMPILE_REQUIRED: return "VK_PIPELINE_COMPILE_REQUIRED";
	case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR";
//	case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
	case VK_SUBOPTIMAL_KHR: return "VK_SUBOPTIMAL_KHR";
//	case VK_ERROR_OUT_OF_DATE_KHR: return "VK_ERROR_OUT_OF_DATE_KHR";
//	case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
//	case VK_ERROR_VALIDATION_FAILED_EXT: return "VK_ERROR_VALIDATION_FAILED_EXT";
//	case VK_ERROR_INVALID_SHADER_NV: return "VK_ERROR_INVALID_SHADER_NV";
//	case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR: return "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR";
//	case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR";
//	case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR";
//	case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR";
//	case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR";
//	case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR: return "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR";
//	case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
//	case VK_ERROR_NOT_PERMITTED_KHR: return "VK_ERROR_NOT_PERMITTED_KHR";
	case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
	case VK_THREAD_IDLE_KHR: return "VK_THREAD_IDLE_KHR";
	case VK_THREAD_DONE_KHR: return "VK_THREAD_DONE_KHR";
	case VK_OPERATION_DEFERRED_KHR: return "VK_OPERATION_DEFERRED_KHR";
	case VK_OPERATION_NOT_DEFERRED_KHR: return "VK_OPERATION_NOT_DEFERRED_KHR";
	case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR: return "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR";
	case VK_ERROR_COMPRESSION_EXHAUSTED_EXT: return "VK_ERROR_COMPRESSION_EXHAUSTED_EXT";
	case VK_INCOMPATIBLE_SHADER_BINARY_EXT: return "VK_INCOMPATIBLE_SHADER_BINARY_EXT";
	default: return "Unknown";
	}
}

// #Macros
#define vk_generic_enum(func, first, type, name)\
uint32_t name ## _count = 0;\
func ( first , & name ## _count, NULL);\
type * name ## s = alloc(get_heap_allocator(), sizeof(type) * name ## _count);\
func ( first , & name ## _count, name ## s)

#define vk_zero_check_enum(func, first, type, name)\
uint32_t name ## _count = 0;\
func ( first , & name ## _count, NULL);\
if ( name ## _count == 0) vk(VK_ERROR_UNKNOWN);\
type * name ## s = alloc(get_heap_allocator(), sizeof(type) * name ## _count);\
func ( first , & name ## _count, name ## s)

#define vk_zero_check_enum_2(func, first, second, type, name)\
uint32_t name ## _count = 0;\
func ( first , second , & name ## _count, NULL);\
if ( name ## _count == 0) vk(VK_ERROR_UNKNOWN);\
type * name ## s = alloc(get_heap_allocator(), sizeof(type) * name ## _count);\
func ( first , second , & name ## _count, name ## s)

#define vk(r) vk_impl(r, __FILE__, __LINE__)
void vk_impl(VkResult r, const char* file, int line) {
	if (r != VK_SUCCESS) {
		const char* errstr = vk_result_table(r);
		log_error("Vulkan Error %s at %s:%d", errstr, file, line);
	}
}

// #Global
Vk_Data vk_data;
u32 vk_swap_chain_width = 0;
u32 vk_swap_chain_height = 0;
const u64 vk_image_shader_vert_size;
const u8 vk_image_shader_vert[];
const u64 vk_image_shader_frag_size;
const u8 vk_image_shader_frag[];
Vk_Vertex* vk_staging_quad_buffer = NULL;
u64 vk_staging_quad_buffer_size = 0;

// TODO: Fix this when I figure out validation layers!
/*
const char* vk_stringify_severity(VkDebugUtilsMessageSeverityFlagBitsEXT severity) {
    switch (severity) {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT: return "Error";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT: return "Warning";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT: return "Info";
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT: return "Message";
    default: return "Unknown";
    }
}

const char* vk_stringify_category(VkDebugUtilsMessageTypeFlagsEXT category) {
    switch (category) {
    case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT: return "General";
    case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT: return "Validation Error";
    case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT: return "Performance Warning";
    default: return "Unknown";
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL vk_debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT category, const VkDebugUtilsMessengerCallbackDataEXT* data, void* userdata) {
	string msg = tprint("VULKAN MESSAGE [Category: %cs, Severity: %cs]: %cs", vk_stringify_category(category), vk_stringify_severity(severity), description);
	
	switch (severity) {
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			log_error(msg);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			log_warning(msg);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			log_info(msg);
			break;
		case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			log_verbose(msg);
			break;
		default:
			log("Ligma");
			break;
	}
}
*/

Vk_QueueFamilyIndices vk_find_queue_family(VkPhysicalDevice device) {
		Vk_QueueFamilyIndices indices = {0};
		
		vk_zero_check_enum(vkGetPhysicalDeviceQueueFamilyProperties, device, VkQueueFamilyProperties, queue_family);
		
		for (uint32_t i = 0; i < queue_family_count; i++) {
			VkBool32 present = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, vk_data.surface, &present);
			if (present) {
				indices.present = i;
				indices.has_present = true;
			}
			if (queue_familys[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphics = i;
				indices.has_graphics = true;
			}
		}
		dealloc(get_heap_allocator(), queue_familys);
		
		return indices;
}

Vk_Swapchain_Details vk_query_swapchain_details(VkPhysicalDevice device) {
	Vk_Swapchain_Details details = {0};
	
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, vk_data.surface, &details.capabilities);
	
	vk_zero_check_enum_2(vkGetPhysicalDeviceSurfaceFormatsKHR, device, vk_data.surface, VkSurfaceFormatKHR, format);
	
	details.format_count = format_count;
	details.formats = formats;
	
	vk_zero_check_enum_2(vkGetPhysicalDeviceSurfacePresentModesKHR, device, vk_data.surface, VkPresentModeKHR, present_mode);
	
	details.present_mode_count = present_mode_count;
	details.present_modes = present_modes;
	
	return details;
}

VkSurfaceFormatKHR vk_get_surface_format(Vk_Swapchain_Details details) {
	for (uint32_t i = 0; i < details.format_count; i++) {
		if (details.formats[i].format == VK_FORMAT_B8G8R8A8_SRGB && details.formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return details.formats[i];
		}
	}
	vk(VK_ERROR_UNKNOWN);
	return details.formats[0]; // unreached
}

VkPresentModeKHR vk_get_present_mode(Vk_Swapchain_Details details) {
	for (uint32_t i = 0; i < details.present_mode_count; i++) {
		if (details.present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			return details.present_modes[i];
	}
	
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkInstance vk_create_instance(void) {
	VkApplicationInfo appinfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "vktest",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "vktest",
		.engineVersion = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion = VK_API_VERSION_1_0,
	};
	
	const char* instance_extensions[] = {
		"VK_KHR_surface", "VK_KHR_win32_surface",
	};
	
	VkInstanceCreateInfo createinfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &appinfo,
		.enabledExtensionCount = 2,
		.ppEnabledExtensionNames = instance_extensions,
	};
	
	VkInstance r;
	vk(vkCreateInstance(&createinfo, NULL, &r));
	return r;
}

VkPhysicalDevice vk_create_physical_device(void) {
	vk_zero_check_enum(vkEnumeratePhysicalDevices, vk_data.instance, VkPhysicalDevice, device);
	
	// just choose the last discrete device, or the last overall device if there is no discrete device
	
	uint32_t chosen_device = 0;
	bool has_chosen = false;
	for (uint32_t i = 0; i < device_count; i++) {
		VkPhysicalDeviceProperties props;
		vkGetPhysicalDeviceProperties(devices[i], &props);
		
		if (vk_find_queue_family(devices[chosen_device]).has_graphics) {
			has_chosen = true;
			chosen_device = i;
		}
		
		if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			chosen_device = i;
			break;
		}
	}
	Vk_QueueFamilyIndices indices = vk_find_queue_family(devices[chosen_device]);
	if (!indices.has_graphics) vk(VK_ERROR_UNKNOWN);
	if (!indices.has_present) vk(VK_ERROR_UNKNOWN);
	
	VkPhysicalDevice r = devices[chosen_device];
	
	dealloc(get_heap_allocator(), devices);
	
	return r;
}

VkDevice vk_create_logical_device(void) {
	Vk_QueueFamilyIndices indices = vk_find_queue_family(vk_data.physical_device);
	
	float queue_priority = 1.0f;
	
	VkDeviceQueueCreateInfo queue_createinfo[] = {
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = indices.graphics,
			.queueCount = 1,
			.pQueuePriorities = &queue_priority,
		},
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = indices.present,
			.queueCount = 1,
			.pQueuePriorities = &queue_priority,
		}
	};
	
	VkPhysicalDeviceFeatures device_features = {0};
	
	const char* device_extensions[] = {
		"VK_KHR_swapchain"
	};
	
	VkDeviceCreateInfo device_createinfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pQueueCreateInfos = queue_createinfo,
		.queueCreateInfoCount = 1,
		.pEnabledFeatures = &device_features,
		.enabledExtensionCount = 1,
		.ppEnabledExtensionNames = device_extensions,
	};
	
	if (indices.graphics == indices.present)
		device_createinfo.queueCreateInfoCount = 1;
	else
		device_createinfo.queueCreateInfoCount = 2;
	
	VkDevice r;
	
	vk(vkCreateDevice(vk_data.physical_device, &device_createinfo, NULL, &r));
	
	return r;
}

VkQueue vk_create_queue(uint32_t family) {
	VkQueue r;
	vkGetDeviceQueue(vk_data.device, family, 0, &r);
	return r;
}

VkSurfaceKHR vk_create_surface(void* hWnd, void* hInstance) {
	VkWin32SurfaceCreateInfoKHR surface_createinfo = {
		.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		.hwnd = hWnd,
		.hinstance = hInstance,
	};
	
	VkSurfaceKHR r;
	vk(vkCreateWin32SurfaceKHR(vk_data.instance, &surface_createinfo, NULL, &r));
	return r;
}

Vk_Swapchain vk_create_swapchain(uint32_t w, uint32_t h, Vk_QueueFamilyIndices indices) {
	Vk_Swapchain_Details details = vk_query_swapchain_details(vk_data.physical_device);
	
	VkSurfaceFormatKHR format = vk_get_surface_format(details);
	VkPresentModeKHR present_mode = vk_get_present_mode(details);
	VkExtent2D extent = { w, h };
	
	uint32_t image_count = details.capabilities.minImageCount + 1;
	if (details.capabilities.maxImageCount > 0 && image_count > details.capabilities.maxImageCount)
		image_count = details.capabilities.maxImageCount;
	
	VkSwapchainCreateInfoKHR createinfo = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = vk_data.surface,
		.minImageCount = image_count,
		.imageFormat = format.format,
		.imageColorSpace = format.colorSpace,
		.imageExtent = extent,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
		.preTransform = details.capabilities.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = present_mode,
		.clipped = VK_TRUE,
		.oldSwapchain = VK_NULL_HANDLE,
	};
	
	uint32_t family_indices[] = { indices.graphics, indices.present };
	
	if (indices.graphics == indices.present) {
		createinfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	} else {
		createinfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createinfo.queueFamilyIndexCount = 2;
		createinfo.pQueueFamilyIndices = family_indices;
	}
	
	Vk_Swapchain r;
	vk(vkCreateSwapchainKHR(vk_data.device, &createinfo, NULL, &r.swapchain));
	
	dealloc(get_heap_allocator(), details.formats);
	dealloc(get_heap_allocator(), details.present_modes);
	
	r.format = format.format;
	r.extent = extent;
	
	vkGetSwapchainImagesKHR(vk_data.device, r.swapchain, &r.swapchain_image_count, NULL);
	r.swapchain_images = alloc(get_heap_allocator(), r.swapchain_image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(vk_data.device, r.swapchain, &r.swapchain_image_count, r.swapchain_images);
	
	return r;
}

Vk_ImageViews vk_create_image_views(void) {
	Vk_ImageViews r;
	r.view_count = vk_data.swapchain.swapchain_image_count;
	r.views = alloc(get_heap_allocator(), r.view_count * sizeof(VkImageView));
	
	for (uint32_t i = 0; i < r.view_count; i++) {
		VkImageViewCreateInfo createinfo = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = vk_data.swapchain.swapchain_images[i],
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = vk_data.swapchain.format,
			.components = {
				VK_COMPONENT_SWIZZLE_IDENTITY,
				VK_COMPONENT_SWIZZLE_IDENTITY,
				VK_COMPONENT_SWIZZLE_IDENTITY,
				VK_COMPONENT_SWIZZLE_IDENTITY,
			},
			.subresourceRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = 1,
				.baseArrayLayer = 0,
				.layerCount = 1,
			},
		};
		
		vk(vkCreateImageView(vk_data.device, &createinfo, NULL, &r.views[i]));
	}
	
	return r;
}

VkShaderModule vk_create_shader(const u8* data, u32 length) {
	VkShaderModuleCreateInfo createinfo = {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.codeSize = length,
		.pCode = (const uint32_t*)data,
	};
	
	VkShaderModule r;
	vk(vkCreateShaderModule(vk_data.device, &createinfo, NULL, &r));
	
	return r;
}

VkPipeline vk_create_graphics_pipeline(void) {
	VkPipelineShaderStageCreateInfo vert_shader_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = vk_data.vert_shader,
		.pName = "main",
	};
	
	VkPipelineShaderStageCreateInfo frag_shader_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = vk_data.frag_shader,
		.pName = "main",
	};
	
	VkPipelineShaderStageCreateInfo stages[] = { vert_shader_createinfo, frag_shader_createinfo };
	
	VkDynamicState states[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
	};
	
	VkPipelineDynamicStateCreateInfo state_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = 2,
		.pDynamicStates = states,
	};
	
	VkVertexInputBindingDescription vertex_input_binding_desc = {
		.binding = 0,
		.stride = sizeof(Vk_Vertex),
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
	};
	
	VkVertexInputAttributeDescription vertex_input_attrs[2] = {
		{
			.binding = 0,
			.location = 0,
			.format = VK_FORMAT_R32G32_SFLOAT,
			.offset = offsetof(Vk_Vertex, pos),
		},
		{
			.binding = 0,
			.location = 1,
			.format = VK_FORMAT_R32G32B32_SFLOAT,
			.offset = offsetof(Vk_Vertex, color),
		},
	};
	
	VkPipelineVertexInputStateCreateInfo vertex_input_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.vertexBindingDescriptionCount = 1,
		.pVertexBindingDescriptions = &vertex_input_binding_desc,
		.vertexAttributeDescriptionCount = 2,
		.pVertexAttributeDescriptions = vertex_input_attrs,
	};
	
	VkPipelineInputAssemblyStateCreateInfo input_assembly_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE,
	};
	
	VkViewport viewport = {
		.x = 0.0f,
		.y = 0.0f,
		.width = vk_data.swapchain.extent.width,
		.height = vk_data.swapchain.extent.height,
		.minDepth = 0.0f,
		.maxDepth = 1.0f,
	};
	
	VkRect2D scissor = {
		.offset = { 0, 0 },
		.extent = vk_data.swapchain.extent,
	};
	
	VkPipelineViewportStateCreateInfo viewport_state_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.pViewports = &viewport,
		.scissorCount = 1,
		.pScissors = &scissor,
	};
	
	VkPipelineRasterizationStateCreateInfo rasterization_state_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.lineWidth = 1.0f,
		.cullMode = VK_CULL_MODE_BACK_BIT,
		.frontFace = VK_FRONT_FACE_CLOCKWISE,
		.depthBiasEnable = VK_FALSE,
	};
	
	VkPipelineMultisampleStateCreateInfo sampling_state_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.sampleShadingEnable = VK_FALSE,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.minSampleShading = 1.0f,
		.pSampleMask = NULL,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE,
	};
	
	VkPipelineColorBlendAttachmentState blend_attachment = {
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
		.blendEnable = VK_FALSE,
	};
	
	VkPipelineColorBlendStateCreateInfo blend_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.attachmentCount = 1,
		.pAttachments = &blend_attachment,
	};
	
	VkGraphicsPipelineCreateInfo pipeline_create_info = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.stageCount = 2,
		.pStages = stages,
		.pVertexInputState = &vertex_input_createinfo,
		.pInputAssemblyState = &input_assembly_createinfo,
		.pViewportState = &viewport_state_createinfo,
		.pRasterizationState = &rasterization_state_createinfo,
		.pMultisampleState = &sampling_state_createinfo,
		.pDepthStencilState = NULL,
		.pColorBlendState = &blend_createinfo,
		.pDynamicState = &state_createinfo,
		.layout = vk_data.pipeline_layout,
		.renderPass = vk_data.render_pass,
		.subpass = 0,
		.basePipelineHandle = VK_NULL_HANDLE,
		.basePipelineIndex = -1,
	};
	
	VkPipeline r;
	vk(vkCreateGraphicsPipelines(vk_data.device, VK_NULL_HANDLE, 1, &pipeline_create_info, NULL, &r));
	return r;
}

VkPipelineLayout vk_create_pipeline_layout(void) {
	VkPipelineLayoutCreateInfo layout_createinfo = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
	};
	
	VkPipelineLayout r;
	vk(vkCreatePipelineLayout(vk_data.device, &layout_createinfo, NULL, &r));
	return r;
}

VkRenderPass vk_create_render_pass(void) {
	VkAttachmentDescription color = {
		.format = vk_data.swapchain.format,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
	};
	
	VkAttachmentReference reference = {
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
	};
	
	VkSubpassDescription subpass = {
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.colorAttachmentCount = 1,
		.pColorAttachments = &reference,
	};
	
	VkSubpassDependency dependency = {
		.srcSubpass = VK_SUBPASS_EXTERNAL,
		.dstSubpass = 0,
		.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask = 0,
	};
	
	VkRenderPassCreateInfo render_pass_create_info = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.attachmentCount = 1,
		.pAttachments = &color,
		.subpassCount = 1,
		.pSubpasses = &subpass,
		.dependencyCount = 1,
		.pDependencies = &dependency,
	};
	
	VkRenderPass r;
	vk(vkCreateRenderPass(vk_data.device, &render_pass_create_info, NULL, &r));
	return r;
}

Vk_Framebuffers vk_create_framebuffers(void) {
	Vk_Framebuffers r;
	r.count = vk_data.image_views.view_count;
	r.data = alloc(get_heap_allocator(), sizeof(VkFramebuffer) * r.count);
	
	for (uint32_t i = 0; i < r.count; i++) {
		VkImageView attachments[] = {
			vk_data.image_views.views[i]
		};
		
		VkFramebufferCreateInfo framebuffer_createinfo = {
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.renderPass = vk_data.render_pass,
			.attachmentCount = 1,
			.pAttachments = attachments,
			.width = vk_data.swapchain.extent.width,
			.height = vk_data.swapchain.extent.height,
			.layers = 1,
		};
		
		vk(vkCreateFramebuffer(vk_data.device, &framebuffer_createinfo, NULL, &r.data[i]));
	}
	
	return r;
}

VkCommandPool vk_create_command_pool(Vk_QueueFamilyIndices indices) {
	VkCommandPoolCreateInfo pool_createinfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = indices.graphics,
	};
	
	VkCommandPool r;
	vk(vkCreateCommandPool(vk_data.device, &pool_createinfo, NULL, &r));
	return r;
}

uint32_t vk_find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags props) {
	VkPhysicalDeviceMemoryProperties mem_props;
	vkGetPhysicalDeviceMemoryProperties(vk_data.physical_device, &mem_props);
	
	for (uint32_t i = 0; i < mem_props.memoryTypeCount; i++) {
		if ((type_filter & (1 << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props) {
			return i;
		}
	}
	
	vk(VK_ERROR_UNKNOWN);
	return 0;
}

VkBuffer vk_create_vertex_buffer(u64 number_of_bytes) {
	VkBufferCreateInfo buffer_createinfo = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = number_of_bytes,
		.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
	};
	
	VkBuffer r;
	vk(vkCreateBuffer(vk_data.device, &buffer_createinfo, NULL, &r));
	return r;
}

VkDeviceMemory vk_alloc_buffer_mem(VkBuffer buffer) {
	VkMemoryRequirements mem_reqs;
	vkGetBufferMemoryRequirements(vk_data.device, buffer, &mem_reqs);
	
	VkMemoryAllocateInfo allocinfo = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = mem_reqs.size,
		.memoryTypeIndex = vk_find_memory_type(mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT),
	};
	
	VkDeviceMemory r;
	vk(vkAllocateMemory(vk_data.device, &allocinfo, NULL, &r));
	
	vkBindBufferMemory(vk_data.device, buffer, r, 0);
	
	return r;
}

void vk_buffer_set_data(VkDeviceMemory mem, void* data, size_t len) {
	void* dst;
	vkMapMemory(vk_data.device, mem, 0, len, 0, &dst);
	memcpy(dst, data, len);
	vkUnmapMemory(vk_data.device, mem);
}

VkCommandBuffer vk_create_command_buffer(void) {
	VkCommandBufferAllocateInfo allocinfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.commandPool = vk_data.command_pool,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = 1,
	};
	
	VkCommandBuffer r;
	vk(vkAllocateCommandBuffers(vk_data.device, &allocinfo, &r));
	return r;
}

void gfx_clear_render_target(Gfx_Image* images, Vector4 color) {
	return; // TODO: Offscreen drawing!
}

void vk_record(VkCommandBuffer command_buffer, uint32_t index) {
	VkCommandBufferBeginInfo begin_info = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.flags = 0,
		.pInheritanceInfo = NULL,
	};
	
	vk(vkBeginCommandBuffer(command_buffer, &begin_info));
	
	VkClearValue clear_color = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
	VkRenderPassBeginInfo render_pass_info = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.renderPass = vk_data.render_pass,
		.framebuffer = vk_data.framebuffers.data[index],
		.renderArea = {
			.offset = { 0, 0 },
			.extent = vk_data.swapchain.extent,
		},
		.clearValueCount = 1,
		.pClearValues = &clear_color,
	};
	
	vkCmdBeginRenderPass(command_buffer, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);
	
	vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vk_data.pipeline);
	
	VkViewport viewport = {
		.x = 0.0f,
		.y = 0.0f,
		.width = vk_data.swapchain.extent.width,
		.height = vk_data.swapchain.extent.height,
		.minDepth = 0.0f,
		.maxDepth = 1.0f,
	};
	
	VkRect2D scissor = {
		.offset = { 0, 0 },
		.extent = vk_data.swapchain.extent,
	};
	
	vkCmdSetViewport(command_buffer, 0, 1, &viewport);
	vkCmdSetScissor(command_buffer, 0, 1, &scissor);
	
	VkDeviceSize offsets[] = {0};
	vkCmdBindVertexBuffers(command_buffer, 0, 1, &vk_data.vertex_buffer, offsets);
	
	vkCmdDraw(command_buffer, 3, 1, 0, 0);
	
	vkCmdEndRenderPass(command_buffer);
	vk(vkEndCommandBuffer(command_buffer));
}

VkSemaphore vk_create_semaphore(void) {
	VkSemaphoreCreateInfo createinfo = {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
	};
	
	VkSemaphore r;
	vk(vkCreateSemaphore(vk_data.device, &createinfo, NULL, &r));
	return r;
}

VkFence vk_create_fence(bool signaled) {
	VkFenceCreateInfo createinfo = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0,
	};
	
	VkFence r;
	vk(vkCreateFence(vk_data.device, &createinfo, NULL, &r));
	return r;
}

void vk_update_swapchain() {
	bool create = !vk_data.swapchain.swapchain;

	if (create) {
		panic("vk_update_swapchain called before initialization");
	} else {
		vkDeviceWaitIdle(vk_data.device);
		
		for (uint32_t i = 0; i < vk_data.framebuffers.count; i++) {
			vkDestroyFramebuffer(vk_data.device, vk_data.framebuffers.data[i], NULL);
		}
		for (uint32_t i = 0; i < vk_data.image_views.view_count; i++) {
			vkDestroyImageView(vk_data.device, vk_data.image_views.views[i], NULL);
		}
		vkDestroySwapchainKHR(vk_data.device, vk_data.swapchain.swapchain, NULL);
		
		RECT client_rect;
		bool ok = GetClientRect(window._os_handle, &client_rect);
		assert(ok, "GetClientRect failed with error code %lu", GetLastError());
		
		vk_swap_chain_width  = client_rect.right-client_rect.left;
		vk_swap_chain_height = client_rect.bottom-client_rect.top;
		
		vk_data.swapchain = vk_create_swapchain(vk_swap_chain_width, vk_swap_chain_height, vk_data.family_indices);
		vk_data.image_views = vk_create_image_views();
		vk_data.framebuffers = vk_create_framebuffers();
	}
}

bool
vk_compile_shader(void) {
	
	vk_data.vert_shader = vk_create_shader(vk_image_shader_vert, vk_image_shader_vert_size);
	vk_data.frag_shader = vk_create_shader(vk_image_shader_frag, vk_image_shader_frag_size);

	return true;
}

float verts[] = {
	 0.0f, -0.5f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
};
uint32_t vert_count = 3;

void gfx_init() {

	window.enable_vsync = false;

	log_verbose("vulkan gfx_init");

    HWND hwnd = window._os_handle;
	HINSTANCE hinstance = GetModuleHandle(NULL);

	vk(volkInitialize());
	vk_data.instance = vk_create_instance();
	volkLoadInstance(vk_data.instance);

// TODO: fix validation layers!
/*
#if CONFIGURATION == DEBUG
	hr = ID3D11Device_QueryInterface(d3d11_device, &IID_ID3D11Debug, (void**)&d3d11_debug);
	if (SUCCEEDED(hr)) {
		log_verbose("D3D11 debug is active");
	}
#endif*/
	
	log_verbose("Created Vulkan instance");
	
	vk_data.surface = vk_create_surface(hwnd, hinstance);
	vk_data.physical_device = vk_create_physical_device();
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(vk_data.physical_device, &props);
	log("Vulkan device is: %s", props.deviceName);
	
	vk_data.device = vk_create_logical_device();
	vk_data.family_indices = vk_find_queue_family(vk_data.physical_device);
	
	vk_data.graphics_queue = vk_create_queue(vk_data.family_indices.graphics);
	vk_data.present_queue = vk_create_queue(vk_data.family_indices.present);
	
	u32 window_width  = window.pixel_width;
	u32 window_height = window.pixel_height;
	
    vk_data.swapchain = vk_create_swapchain(window_width, window_height, vk_data.family_indices);
	vk_data.image_views = vk_create_image_views();
	
	bool ok = vk_compile_shader();
	assert(ok, "Failed compiling default shader");
	
	vk_data.render_pass = vk_create_render_pass();
	vk_data.pipeline_layout = vk_create_pipeline_layout();
	vk_data.pipeline = vk_create_graphics_pipeline();
	vk_data.framebuffers = vk_create_framebuffers();
	vk_data.command_pool = vk_create_command_pool(vk_data.family_indices);
	
	vk_data.vertex_buffer = vk_create_vertex_buffer(sizeof(verts[0]) * vert_count);
	vk_data.vertex_buffer_mem = vk_alloc_buffer_mem(vk_data.vertex_buffer);
	vk_buffer_set_data(vk_data.vertex_buffer_mem, verts, sizeof(verts[0]) * vert_count);
	
	vk_data.command_buffers[0] = vk_create_command_buffer();
	vk_data.image_available[0] = vk_create_semaphore();
	vk_data.render_finished[0] = vk_create_semaphore();
	vk_data.in_flight[0] = vk_create_fence(true);
	
	vk_data.command_buffers[1] = vk_create_command_buffer();
	vk_data.image_available[1] = vk_create_semaphore();
	vk_data.render_finished[1] = vk_create_semaphore();
	vk_data.in_flight[1] = vk_create_fence(true);

	log_info("Vulkan init done");
	
}

void vk_draw_call(int number_of_rendered_quads, VkImage *textures, u64 num_textures) {
	vkWaitForFences(vk_data.device, 1, &vk_data.in_flight[vk_data.frame], VK_TRUE, UINT64_MAX);
	vkResetFences(vk_data.device, 1, &vk_data.in_flight[vk_data.frame]);
	
	uint32_t image_index;
	vkAcquireNextImageKHR(vk_data.device, vk_data.swapchain.swapchain, UINT64_MAX, vk_data.image_available[vk_data.frame], VK_NULL_HANDLE, &image_index);
	
	vkResetCommandBuffer(vk_data.command_buffers[vk_data.frame], 0);
	vk_record(vk_data.command_buffers[vk_data.frame], image_index);
	
	VkSemaphore wait_semaphores[] = { vk_data.image_available[vk_data.frame] };
	VkPipelineStageFlags wait_stages = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	
	VkSemaphore signals[] = { vk_data.render_finished[vk_data.frame] };
	
	VkSubmitInfo submit_info = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = wait_semaphores,
		.pWaitDstStageMask = &wait_stages,
		.commandBufferCount = 1,
		.pCommandBuffers = &vk_data.command_buffers[vk_data.frame],
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = signals,
	};
	
	vk(vkQueueSubmit(vk_data.graphics_queue, 1, &submit_info, vk_data.in_flight[vk_data.frame]));
	
	VkPresentInfoKHR present_info = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = signals,
		.swapchainCount = 1,
		.pSwapchains = &vk_data.swapchain.swapchain,
		.pImageIndices = &image_index,
		.pResults = NULL,
	};
	
	vkQueuePresentKHR(vk_data.present_queue, &present_info);
	
	vk_data.frame = (vk_data.frame + 1) % 2;
}

void gfx_render_draw_frame(Draw_Frame *frame, Gfx_Image *render_target) {
	
	///
	// Maybe grow quad vbo
	
	if (!frame->quad_buffer) return;

	u64 number_of_quads = growing_array_get_valid_count(frame->quad_buffer);
	
	u32 required_size = sizeof(Vk_Vertex) * number_of_quads*6;

	if (required_size > vk_data.vertex_buffer_size) {
		if (vk_data.vertex_buffer) {
			vkDestroyBuffer(vk_data.device, vk_data.vertex_buffer, NULL);
			vkFreeMemory(vk_data.device, vk_data.vertex_buffer_mem, NULL);
			dealloc(get_heap_allocator(), vk_staging_quad_buffer);
		}
		vk_data.vertex_buffer = vk_create_vertex_buffer(required_size);
		vk_data.vertex_buffer_mem = vk_alloc_buffer_mem(vk_data.vertex_buffer);
		vk_buffer_set_data(vk_data.vertex_buffer_mem, verts, sizeof(verts[0]) * vert_count); // #TEMPORARY
		
		vk_staging_quad_buffer = alloc(get_heap_allocator(), vk_data.vertex_buffer_size);
		assert((u64)vk_staging_quad_buffer%16 == 0);
		
		log_verbose("Grew quad vbo to %d bytes.", vk_data.vertex_buffer_size);
	}

	if (number_of_quads > 0) {
		///
		// Render geometry from into vbo quad list
	    
		// TODO: All of this
		/*
		ID3D11ShaderResourceView *textures[32];
		ID3D11ShaderResourceView *last_texture = 0;
		u64 num_textures = 0;
		s8 last_texture_index = 0;
		
		D3D11_Vertex* head = (D3D11_Vertex*)d3d11_staging_quad_buffer;
		D3D11_Vertex* pointer = head;
		u64 number_of_rendered_quads = 0;
		
		tm_scope("Quad processing") {
			if (draw_frame.enable_z_sorting) tm_scope("Z sorting") {
				if (!sort_quad_buffer || (sort_quad_buffer_size < allocated_quads*sizeof(Draw_Quad))) {
					// #Memory #Heapalloc
					if (sort_quad_buffer) dealloc(get_heap_allocator(), sort_quad_buffer);
					sort_quad_buffer = alloc(get_heap_allocator(), allocated_quads*sizeof(Draw_Quad));
					sort_quad_buffer_size = allocated_quads*sizeof(Draw_Quad);
				}
				radix_sort(quad_buffer, sort_quad_buffer, draw_frame.num_quads, sizeof(Draw_Quad), offsetof(Draw_Quad, z), MAX_Z_BITS);
			}
		
			for (u64 i = 0; i < draw_frame.num_quads; i++)  {
				
				Draw_Quad *q = &quad_buffer[i];
				
				assert(q->z <= MAX_Z, "Z is too high. Z is %d, Max is %d.", q->z, MAX_Z);
				assert(q->z >= (-MAX_Z+1), "Z is too low. Z is %d, Min is %d.", q->z, -MAX_Z+1);
				
				s8 texture_index = -1;
				
				if (q->image) {
					
					if (last_texture == q->image->gfx_handle) {
						texture_index = last_texture_index;
					} else {
						// First look if texture is already bound
						for (u64 j = 0; j < num_textures; j++) {
							if (textures[j] == q->image->gfx_handle) {
								texture_index = (s8)j;
								break;
							}
						}
						// Otherwise use a new slot
						if (texture_index <= -1) {
							if (num_textures >= 32) {
								// If max textures reached, make a draw call and start over
								D3D11_MAPPED_SUBRESOURCE buffer_mapping;
								ID3D11DeviceContext_Map(d3d11_context, (ID3D11Resource*)d3d11_quad_vbo, 0, D3D11_MAP_WRITE_DISCARD, 0, &buffer_mapping);
								memcpy(buffer_mapping.pData, d3d11_staging_quad_buffer, number_of_rendered_quads*sizeof(D3D11_Vertex)*6);
								ID3D11DeviceContext_Unmap(d3d11_context, (ID3D11Resource*)d3d11_quad_vbo, 0);
								d3d11_draw_call(number_of_rendered_quads, textures, num_textures);
								head = (D3D11_Vertex*)d3d11_staging_quad_buffer;
								num_textures = 0;
								texture_index = 0;
								number_of_rendered_quads = 0;
								pointer = head;
							} else {
								texture_index = (s8)num_textures;
								num_textures += 1;
							}
						}
					}
					textures[texture_index] = q->image->gfx_handle;
					last_texture = q->image->gfx_handle;
					last_texture_index = texture_index;
				}
				
				if (q->type == QUAD_TYPE_TEXT) {
				
				    // This is meant to fix the annoying artifacts that shows up when sampling text from an atlas
				    // presumably for floating point precision issues or something.
				
				    // #Incomplete
				    // If we want to animate text with small movements then it will look wonky.
				    // This should be optional probably.
				    // Also, we might want to do this on non-text if rendering with linear filtering
				    // from a large texture atlas.
				
					float pixel_width = 2.0/(float)window.width;
					float pixel_height = 2.0/(float)window.height;

                    bool xeven = window.width % 2 == 0;
                    bool yeven = window.height % 2 == 0;
					
					q->bottom_left.x  = round(q->bottom_left.x  / pixel_width)  * pixel_width;
				    q->bottom_left.y  = round(q->bottom_left.y  / pixel_height) * pixel_height;
				    q->top_left.x     = round(q->top_left.x     / pixel_width)  * pixel_width;
				    q->top_left.y     = round(q->top_left.y     / pixel_height) * pixel_height;
				    q->top_right.x    = round(q->top_right.x    / pixel_width)  * pixel_width;
				    q->top_right.y    = round(q->top_right.y    / pixel_height) * pixel_height;
				    q->bottom_right.x = round(q->bottom_right.x / pixel_width)  * pixel_width;
				    q->bottom_right.y = round(q->bottom_right.y / pixel_height) * pixel_height;
				}
				
				// We will write to 6 vertices for the one quad (two tris)
				 {
				
					D3D11_Vertex* BL  = pointer + 0;
					D3D11_Vertex* TL  = pointer + 1;
					D3D11_Vertex* TR  = pointer + 2;
					D3D11_Vertex* BL2 = pointer + 3;
					D3D11_Vertex* TR2 = pointer + 4;
					D3D11_Vertex* BR  = pointer + 5;
					pointer += 6;
					
					BL->position = v4(q->bottom_left.x,  q->bottom_left.y,  0, 1);
					TL->position = v4(q->top_left.x,     q->top_left.y,     0, 1);
					TR->position = v4(q->top_right.x,    q->top_right.y,    0, 1);
					BR->position = v4(q->bottom_right.x, q->bottom_right.y, 0, 1);
					
					
					if (q->image) {

						BL->uv = v2(q->uv.x1, q->uv.y1);
						TL->uv = v2(q->uv.x1, q->uv.y2);
						TR->uv = v2(q->uv.x2, q->uv.y2);
						BR->uv = v2(q->uv.x2, q->uv.y1);
						// #Hack #Bug #Cleanup
						// When a window dimension is uneven it slightly under/oversamples on an axis by a
						// seemingly arbitrary amount. The 0.25 is a magic value I got from trial and error.
						// (It undersamples by a fourth of the atlas texture?)
						// Anything > 0.25 < will slightly over/undersample on my machine.
						// I have no idea about #Portability here.
						// - Charlie M 26th July 2024
						if (window.width % 2 != 0) {
							BL->uv.x += (2.0/(float)q->image->width)*0.25;
							TL->uv.x += (2.0/(float)q->image->width)*0.25;
							TR->uv.x += (2.0/(float)q->image->width)*0.25;
							BR->uv.x += (2.0/(float)q->image->width)*0.25;
						}
						if (window.height % 2 != 0) {
							BL->uv.y -= (2.0/(float)q->image->height)*0.25;
							TL->uv.y -= (2.0/(float)q->image->height)*0.25;
							TR->uv.y -= (2.0/(float)q->image->height)*0.25;
							BR->uv.y -= (2.0/(float)q->image->height)*0.25;
						}

						u8 sampler = -1;
						if (q->image_min_filter == GFX_FILTER_MODE_NEAREST
									&& q->image_mag_filter == GFX_FILTER_MODE_NEAREST)
								sampler = 0;
						if (q->image_min_filter == GFX_FILTER_MODE_LINEAR
									&& q->image_mag_filter == GFX_FILTER_MODE_LINEAR)
								sampler = 1;
						if (q->image_min_filter == GFX_FILTER_MODE_LINEAR
									&& q->image_mag_filter == GFX_FILTER_MODE_NEAREST)
								sampler = 2;
						if (q->image_min_filter == GFX_FILTER_MODE_NEAREST
									&& q->image_mag_filter == GFX_FILTER_MODE_LINEAR)
								sampler = 3;
						BL->sampler=TL->sampler=TR->sampler=BR->sampler = (u8)sampler;
								
					}
					BL->texture_index=TL->texture_index=TR->texture_index=BR->texture_index = texture_index;
					
					BL->self_uv = v2(0, 0);
					TL->self_uv = v2(0, 1);
					TR->self_uv = v2(1, 1);
					BR->self_uv = v2(1, 0);
					
					// #Speed
					memcpy(BL->userdata, q->userdata, sizeof(q->userdata));
					memcpy(TL->userdata, q->userdata, sizeof(q->userdata));
					memcpy(TR->userdata, q->userdata, sizeof(q->userdata));
					memcpy(BR->userdata, q->userdata, sizeof(q->userdata));
					
					BL->color = TL->color = TR->color = BR->color = q->color;
					
					BL->type=TL->type=TR->type=BR->type = (u8)q->type;
					
					float t = q->scissor.y1;
					q->scissor.y1 = q->scissor.y2;
					q->scissor.y2 = t;
					
					q->scissor.y1 = window.pixel_height - q->scissor.y1;
					q->scissor.y2 = window.pixel_height - q->scissor.y2;
					
					BL->has_scissor=TL->has_scissor=TR->has_scissor=BR->has_scissor = q->has_scissor;
					BL->scissor=TL->scissor=TR->scissor=BR->scissor = q->scissor;
					
					*BL2 = *BL;
					*TR2 = *TR;
					
					number_of_rendered_quads += 1;
				}
			}
		}
		
		tm_scope("Write to gpu") {
		    D3D11_MAPPED_SUBRESOURCE buffer_mapping;
			tm_scope("The Map call") {
				hr = ID3D11DeviceContext_Map(d3d11_context, (ID3D11Resource*)d3d11_quad_vbo, 0, D3D11_MAP_WRITE_DISCARD, 0, &buffer_mapping);
			d3d11_check_hr(hr);
			}
			tm_scope("The memcpy") {
				memcpy(buffer_mapping.pData, d3d11_staging_quad_buffer, number_of_rendered_quads*sizeof(D3D11_Vertex)*6);
			}
			tm_scope("The Unmap call") {
				ID3D11DeviceContext_Unmap(d3d11_context, (ID3D11Resource*)d3d11_quad_vbo, 0);
			}
		}
		
		///
		// Draw call*/
		//tm_scope("Draw call") d3d11_draw_call(number_of_rendered_quads, textures, num_textures);
		vk_draw_call(0, NULL, 0); // #TEMPORARY
    }
    
    draw_frame_reset(&draw_frame);
}

void gfx_render_draw_frame_to_window(Draw_Frame* frame) {
	gfx_render_draw_frame(frame, 0);
}

void gfx_update() {
	if (window.should_close) return;
	
	

	HRESULT hr;
	///
	// Maybe resize swap chain
	RECT client_rect;
	bool ok = GetClientRect(window._os_handle, &client_rect);
	assert(ok, "GetClientRect failed with error code %lu", GetLastError());
	u32 window_width  = client_rect.right-client_rect.left;
	u32 window_height = client_rect.bottom-client_rect.top;
	if (window_width != vk_swap_chain_width || window_height != vk_swap_chain_height) {
		vk_update_swapchain();
	}

	tm_scope("Present") {
		gfx_render_draw_frame_to_window(&draw_frame);
		draw_frame_reset(&draw_frame);
	}
	
	
#if CONFIGURATION == DEBUG
	//d3d11_output_debug_messages();
#endif
	
}

// TODO: Images

void gfx_init_image(Gfx_Image *image, void *initial_data, bool render_target) {
	return;/*
	void *data = initial_data;
    if (!initial_data){
    	// #Incomplete 8 bit width assumed
    	data = alloc(image->allocator, image->width*image->height*image->channels);
    	memset(data, 0, image->width*image->height*image->channels);
    }
    
	assert(image->channels > 0 && image->channels <= 4 && image->channels != 3, "Only 1, 2 or 4 channels allowed on images. Got %d", image->channels);

	D3D11_TEXTURE2D_DESC desc = ZERO(D3D11_TEXTURE2D_DESC);
	desc.Width = image->width;
	desc.Height = image->height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	switch (image->channels) {
		case 1: desc.Format = DXGI_FORMAT_R8_UNORM; break;
		case 2: desc.Format = DXGI_FORMAT_R8G8_UNORM; break;
		case 4: desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; break;
		default: panic("You should not be here");
	}
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA data_desc = ZERO(D3D11_SUBRESOURCE_DATA);
	data_desc.pSysMem = data;
	data_desc.SysMemPitch  = image->width * image->channels;
	
	ID3D11Texture2D* texture = 0;
	HRESULT hr = ID3D11Device_CreateTexture2D(d3d11_device, &desc, &data_desc, &texture);
	d3d11_check_hr(hr);
	
	hr = ID3D11Device_CreateShaderResourceView(d3d11_device, (ID3D11Resource*)texture, 0, &image->gfx_handle);
	d3d11_check_hr(hr);
	
	if (!initial_data) {
		dealloc(image->allocator, data);
	}
	
	log_verbose("Created a D3D11 image of width %d and height %d.", image->width, image->height);*/
}
void gfx_set_image_data(Gfx_Image *image, u32 x, u32 y, u32 w, u32 h, void *data) {
	return;/*
    assert(image && data, "Bad parameters passed to gfx_set_image_data");

    ID3D11ShaderResourceView *view = image->gfx_handle;
    ID3D11Resource *resource = NULL;
    ID3D11ShaderResourceView_GetResource(view, &resource);
    
    assert(resource, "Invalid image passed to gfx_set_image_data");
    
    assert(x+w <= image->width && y+h <= image->height, "Specified subregion in image is out of bounds");

    ID3D11Texture2D *texture = NULL;
    HRESULT hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture2D, (void**)&texture);
    assert(SUCCEEDED(hr), "Expected gfx resource to be a texture but it wasn't");

    D3D11_BOX destBox;
    destBox.left = x;
    destBox.right = x + w;
    destBox.top = y;
    destBox.bottom = y + h;
    destBox.front = 0;
    destBox.back = 1;

	// #Incomplete bit-width 8 assumed
    ID3D11DeviceContext_UpdateSubresource(d3d11_context, (ID3D11Resource*)texture, 0, &destBox, data, w * image->channels, 0);*/
}
void gfx_deinit_image(Gfx_Image *image) {
	return;/*
	ID3D11ShaderResourceView *view = image->gfx_handle;
	ID3D11Resource *resource = 0;
	ID3D11ShaderResourceView_GetResource(view, &resource);
	
	ID3D11Texture2D *texture = 0;
	HRESULT hr = ID3D11Resource_QueryInterface(resource, &IID_ID3D11Texture2D, (void**)&texture);
	if (SUCCEEDED(hr)) {
		D3D11Release(view);
		D3D11Release(texture);
		log("Destroyed an image");
	} else {
		panic("Unhandled D3D11 resource deletion");
	}*/
}

bool 
shader_recompile_with_extension(string ext_source, u64 cbuffer_size) {
	return true;/*

	string source = string_replace_all(STR(d3d11_image_shader_source), STR("$INJECT_PIXEL_POST_PROCESS"), ext_source, get_temporary_allocator());
	
	
	if (!d3d11_compile_shader(source)) return false;
	
	u64 aligned_cbuffer_size = (max(cbuffer_size, 16) + 16) & ~(15);
	
	if (d3d11_cbuffer) {
		D3D11Release(d3d11_cbuffer);
	}
	D3D11_BUFFER_DESC desc = ZERO(D3D11_BUFFER_DESC);
	desc.ByteWidth      = aligned_cbuffer_size;
	desc.Usage          = D3D11_USAGE_DYNAMIC;
	desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	HRESULT hr = ID3D11Device_CreateBuffer(d3d11_device, &desc, null, &d3d11_cbuffer);
	d3d11_check_hr(hr);
	
	d3d11_cbuffer_size = cbuffer_size;
	
	return true;*/
}

const u64 vk_image_shader_vert_size = 1080;
const u8 vk_image_shader_vert[] = {
	0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 
	0x0b, 0x00, 0x0d, 0x00, 0x21, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 
	0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30, 
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x0f, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 
	0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 
	0x12, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 
	0x1f, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0xc2, 0x01, 0x00, 0x00, 
	0x04, 0x00, 0x0a, 0x00, 0x47, 0x4c, 0x5f, 0x47, 
	0x4f, 0x4f, 0x47, 0x4c, 0x45, 0x5f, 0x63, 0x70, 
	0x70, 0x5f, 0x73, 0x74, 0x79, 0x6c, 0x65, 0x5f, 
	0x6c, 0x69, 0x6e, 0x65, 0x5f, 0x64, 0x69, 0x72, 
	0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x00, 0x00, 
	0x04, 0x00, 0x08, 0x00, 0x47, 0x4c, 0x5f, 0x47, 
	0x4f, 0x4f, 0x47, 0x4c, 0x45, 0x5f, 0x69, 0x6e, 
	0x63, 0x6c, 0x75, 0x64, 0x65, 0x5f, 0x64, 0x69, 
	0x72, 0x65, 0x63, 0x74, 0x69, 0x76, 0x65, 0x00, 
	0x05, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x6d, 0x61, 0x69, 0x6e, 0x00, 0x00, 0x00, 0x00, 
	0x05, 0x00, 0x06, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x67, 0x6c, 0x5f, 0x50, 0x65, 0x72, 0x56, 0x65, 
	0x72, 0x74, 0x65, 0x78, 0x00, 0x00, 0x00, 0x00, 
	0x06, 0x00, 0x06, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x67, 0x6c, 0x5f, 0x50, 
	0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x00, 
	0x06, 0x00, 0x07, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x67, 0x6c, 0x5f, 0x50, 
	0x6f, 0x69, 0x6e, 0x74, 0x53, 0x69, 0x7a, 0x65, 
	0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x07, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
	0x67, 0x6c, 0x5f, 0x43, 0x6c, 0x69, 0x70, 0x44, 
	0x69, 0x73, 0x74, 0x61, 0x6e, 0x63, 0x65, 0x00, 
	0x06, 0x00, 0x07, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x67, 0x6c, 0x5f, 0x43, 
	0x75, 0x6c, 0x6c, 0x44, 0x69, 0x73, 0x74, 0x61, 
	0x6e, 0x63, 0x65, 0x00, 0x05, 0x00, 0x03, 0x00, 
	0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x05, 0x00, 0x05, 0x00, 0x12, 0x00, 0x00, 0x00, 
	0x69, 0x6e, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 
	0x6f, 0x6e, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 
	0x1d, 0x00, 0x00, 0x00, 0x66, 0x72, 0x61, 0x67, 
	0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00, 
	0x05, 0x00, 0x04, 0x00, 0x1f, 0x00, 0x00, 0x00, 
	0x69, 0x6e, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 
	0x47, 0x00, 0x03, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x48, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x48, 0x00, 0x05, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x48, 0x00, 0x05, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 
	0x12, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 
	0x1d, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 
	0x1f, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
	0x16, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x20, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 
	0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x04, 0x00, 
	0x0a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x09, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x06, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 
	0x0a, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 
	0x0c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 
	0x0c, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x15, 0x00, 0x04, 0x00, 
	0x0e, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 
	0x0e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 
	0x10, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 
	0x11, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x10, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 
	0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x3f, 0x20, 0x00, 0x04, 0x00, 
	0x19, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x07, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 
	0x1b, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 
	0x1c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x1b, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 
	0x1c, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 
	0x1e, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x1b, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 
	0x1e, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x36, 0x00, 0x05, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 
	0x3d, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 
	0x13, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 
	0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x16, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 
	0x13, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x50, 0x00, 0x07, 0x00, 0x07, 0x00, 0x00, 0x00, 
	0x18, 0x00, 0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 
	0x17, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 
	0x15, 0x00, 0x00, 0x00, 0x41, 0x00, 0x05, 0x00, 
	0x19, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 
	0x0d, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 
	0x3e, 0x00, 0x03, 0x00, 0x1a, 0x00, 0x00, 0x00, 
	0x18, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x04, 0x00, 
	0x1b, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
	0x1f, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x03, 0x00, 
	0x1d, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
	0xfd, 0x00, 0x01, 0x00, 0x38, 0x00, 0x01, 0x00, 
};

const u64 vk_image_shader_frag_size = 572;
const u8 vk_image_shader_frag[] = {
	0x03, 0x02, 0x23, 0x07, 0x00, 0x00, 0x01, 0x00, 
	0x0b, 0x00, 0x0d, 0x00, 0x13, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x11, 0x00, 0x02, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x06, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x47, 0x4c, 0x53, 0x4c, 
	0x2e, 0x73, 0x74, 0x64, 0x2e, 0x34, 0x35, 0x30, 
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x0f, 0x00, 0x07, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 
	0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 
	0x0c, 0x00, 0x00, 0x00, 0x10, 0x00, 0x03, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x00, 
	0xc2, 0x01, 0x00, 0x00, 0x04, 0x00, 0x0a, 0x00, 
	0x47, 0x4c, 0x5f, 0x47, 0x4f, 0x4f, 0x47, 0x4c, 
	0x45, 0x5f, 0x63, 0x70, 0x70, 0x5f, 0x73, 0x74, 
	0x79, 0x6c, 0x65, 0x5f, 0x6c, 0x69, 0x6e, 0x65, 
	0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 0x69, 
	0x76, 0x65, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 
	0x47, 0x4c, 0x5f, 0x47, 0x4f, 0x4f, 0x47, 0x4c, 
	0x45, 0x5f, 0x69, 0x6e, 0x63, 0x6c, 0x75, 0x64, 
	0x65, 0x5f, 0x64, 0x69, 0x72, 0x65, 0x63, 0x74, 
	0x69, 0x76, 0x65, 0x00, 0x05, 0x00, 0x04, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x6d, 0x61, 0x69, 0x6e, 
	0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x05, 0x00, 
	0x09, 0x00, 0x00, 0x00, 0x6f, 0x75, 0x74, 0x43, 
	0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x00, 0x00, 0x00, 
	0x05, 0x00, 0x05, 0x00, 0x0c, 0x00, 0x00, 0x00, 
	0x66, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 
	0x72, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 
	0x09, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x47, 0x00, 0x04, 0x00, 
	0x0c, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x13, 0x00, 0x02, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x21, 0x00, 0x03, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 
	0x16, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x20, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 
	0x07, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x04, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0x07, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 
	0x08, 0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x17, 0x00, 0x04, 0x00, 
	0x0a, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x03, 0x00, 0x00, 0x00, 0x20, 0x00, 0x04, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x0a, 0x00, 0x00, 0x00, 0x3b, 0x00, 0x04, 0x00, 
	0x0b, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 
	0x01, 0x00, 0x00, 0x00, 0x2b, 0x00, 0x04, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x80, 0x3f, 0x36, 0x00, 0x05, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
	0xf8, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x00, 
	0x3d, 0x00, 0x04, 0x00, 0x0a, 0x00, 0x00, 0x00, 
	0x0d, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 
	0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x0f, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x05, 0x00, 
	0x06, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
	0x0d, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
	0x51, 0x00, 0x05, 0x00, 0x06, 0x00, 0x00, 0x00, 
	0x11, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00, 
	0x02, 0x00, 0x00, 0x00, 0x50, 0x00, 0x07, 0x00, 
	0x07, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 
	0x0f, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
	0x11, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 
	0x3e, 0x00, 0x03, 0x00, 0x09, 0x00, 0x00, 0x00, 
	0x12, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x01, 0x00, 
	0x38, 0x00, 0x01, 0x00, 
};
