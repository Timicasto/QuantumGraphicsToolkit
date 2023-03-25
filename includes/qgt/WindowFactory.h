#ifndef QUANTUNGRAPHICSTOOLKIT_WINDOWFACTORY_H
#define QUANTUNGRAPHICSTOOLKIT_WINDOWFACTORY_H

#include <glm/glm.hpp>
#include "Window.h"

typedef struct Context {
	int majorVer;
	int minorVer;
	bool forwardCompat;
	int profile;
	int api;
} Context;

class WindowFactory{
private:
	int width{}, height{};
	int monitor = INT_MAX;
	bool isFullscreen = false;
	bool isWindowedFullscreen = false;
	bool isScalable = false;
	bool isVsync = false;
	GLFWwindow* share;
	Context context;
	ScaleMode sMode;
	PosMode pMode;
	glm::ivec4 sizeLimit = {0, 0, 0, 0};
	glm::ivec2 aspectRatio = {0, 0};
	std::string windowTitle;
	
public:
	
	WindowFactory() : monitor(INT_MAX), share(nullptr) {
	
	}
	
	WindowFactory size(int w, int h) {
		width = w;
		height = h;
		return *this;
	}
	
	WindowFactory size(glm::ivec2 size) {
		width = size.x;
		height = size.y;
		return *this;
	}
	
	WindowFactory defaultContext() {
		context = {3, 3, true, GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_API};
		return *this;
	}
	
	WindowFactory contextVer(int major, int minor) {
		context = {major, minor, true, major >= 3 ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_API};
		return *this;
	}

	WindowFactory defaultESContext() {
		context = {3, 2, true, GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_ES_API};
		return *this;
	}
	
	WindowFactory fullscreen(int m) {
		isFullscreen = true;
		monitor = m;
		return *this;
	}
	
	WindowFactory windowedFullscreen() {
		isWindowedFullscreen = true;
		return *this;
	}
	
	WindowFactory scaleMode(ScaleMode s) {
		sMode = s;
		return *this;
	}
	
	WindowFactory posMode(PosMode p) {
		pMode = p;
		return *this;
	}
	
	WindowFactory title(const std::string& t) {
		windowTitle = t;
		return *this;
	}
	
	WindowFactory scalable(bool val) {
		isScalable = val;
		return *this;
	}
	
	WindowFactory vSync(bool val) {
		isVsync = val;
		return *this;
	}
	
	WindowFactory sizeLimitMin(int minW, int minH) {
		sizeLimit.x = minW;
		sizeLimit.y = minH;
		return *this;
	}
	
	WindowFactory sizeLimitMax(int maxW, int maxH) {
		sizeLimit.z = maxW;
		sizeLimit.w = maxH;
		return *this;
	}
	
	WindowFactory forceAspectRatio(int w, int h) {
		aspectRatio.x = w;
		aspectRatio.y = h;
		return *this;
	}
	
	Window construct() {
		if (isFullscreen && isWindowedFullscreen) {
			throw std::runtime_error("A window cannot be fullscreen and windowed fullscreen at the same time.");
		}
		if ((pMode == ABS_COORD || pMode == STD_COORD) && sMode == EXPAND) {
			throw std::runtime_error("Unsupported posmode *_COORD in EXPAND scalemode. (" + std::string(pMode == ABS_COORD ? "ABS_COORD" : "STD_COORD") + ")");
		}
		if (aspectRatio.x < 0 || aspectRatio.y < 0 || sizeLimit.x < 0 || sizeLimit.y < 0 || sizeLimit.z < 0 || sizeLimit.w < 0) {
			throw std::runtime_error("Window size limit or aspect ratio limit cannot be negative.");
		}
		auto ret = Window(windowTitle, width, height, context.majorVer, context.minorVer, context.profile, context.forwardCompat);
		if (isFullscreen) {
			int tmp;
			const auto videoMode = glfwGetVideoMode(glfwGetMonitors(&tmp)[monitor]);
			glfwSetWindowMonitor(ret.window, glfwGetMonitors(&tmp)[monitor], 0, 0, videoMode->width, videoMode->height, videoMode->refreshRate);
		}
		if (isWindowedFullscreen) {
			glfwMaximizeWindow(ret.window);
		}
		ret.setScaleMode(sMode);
		ret.setPosMode(pMode);
		ret.setVsync(isVsync);
		ret.setWindowScalable(isScalable);
		if (aspectRatio.x != 0 && aspectRatio.y != 0) {
			glfwSetWindowAspectRatio(ret.window, aspectRatio.x, aspectRatio.y);
		}
		if (sizeLimit.x != 0 && sizeLimit.y != 0 && (sizeLimit.z == 0 || sizeLimit.w == 0)) {
			glfwSetWindowSizeLimits(ret.window, sizeLimit.x, sizeLimit.y, GLFW_DONT_CARE, GLFW_DONT_CARE);
		}
		if ((sizeLimit.x == 0 || sizeLimit.y == 0) && sizeLimit.z != 0 && sizeLimit.w != 0) {
			glfwSetWindowSizeLimits(ret.window, GLFW_DONT_CARE, GLFW_DONT_CARE, sizeLimit.z, sizeLimit.w);
		}
		if (sizeLimit.x != 0 && sizeLimit.y != 0 && sizeLimit.z != 0 && sizeLimit.w != 0) {
			glfwSetWindowSizeLimits(ret.window, sizeLimit.x, sizeLimit.y, sizeLimit.z, sizeLimit.w);
		}
		return ret;
	}
	
	
};

#endif //QUANTUNGRAPHICSTOOLKIT_WINDOWFACTORY_H
