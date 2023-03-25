#ifndef QUANTUNGRAPHICSTOOLKIT_WINDOW_H
#define QUANTUNGRAPHICSTOOLKIT_WINDOW_H

#include <string>
#include <stdexcept>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "logger.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "states.h"

typedef enum ScaleMode {
	SCALE,
	EXPAND
} ScaleMode;

typedef enum PosMode {
	PIXEL_NEG,
	PIXEL_POS,
	ABS_COORD,
	STD_COORD
} PosMode;

static ScaleMode mode = SCALE;
static PosMode pMode = PIXEL_NEG;

void processScale(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	if (mode == EXPAND) {
		if (pMode == PIXEL_NEG) {
			setProjection(glm::ortho(0.0F, static_cast<float>(width), 0.0F, static_cast<float>(height)));
		} else if (pMode == PIXEL_POS) {
			setProjection(glm::ortho(0.0F, (float)width, (float)height, 0.0F));
		}
	}
}

class Window {
public:
	GLFWwindow* window;
	ScaleMode scaleMode = SCALE;
	PosMode posMode = PIXEL_NEG;
	
	glm::mat4 projection;
	
	Window(const std::string& title, size_t width, size_t height) : Window(title, width, height, 3, 3, GLFW_OPENGL_CORE_PROFILE, true, GLFW_OPENGL_API){
	
	}
	
	Window(const std::string& title, size_t width, size_t height, int majorVer, int minorVer, int profile, bool fwdCompat, int api) {
		if (!glfwInit()) {
			char error[9];
			sprintf(error, "%08X", glfwGetError(nullptr));
			std::string err = error;
			log(FATAL, "Failed to initialize GLFW library, error code 0x" + err);
			glfwTerminate();
		} else {
			log(INFO, "GLFW initialized.");
		}
		glfwWindowHint(GLFW_CLIENT_API, api);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);
		glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, fwdCompat ? GL_TRUE : GL_FALSE);
		
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		
		projection = glm::ortho(0.0F, static_cast<float>(width), 0.0F, static_cast<float>(height));
		
		if (window == nullptr) {
			char error[9];
			sprintf(error, "%08X", glfwGetError(nullptr));
			std::string err = error;
			log(FATAL, "Failed to create window using GLFW calls, error code 0x" + err);
			glfwTerminate();
		} else {
			log(INFO, "GLFW window created with size " + std::to_string(width) + "*" + std::to_string(height) + " and context version " +
					std::to_string(majorVer) + "." + std::to_string(minorVer));
		}
		
		makeCurrent();
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			log(FATAL, "Failed to initialize GLAD.");
			glfwTerminate();
		} else {
			log(INFO, "Initialized GLAD with GLFW Process Address.");
		}
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glViewport(0, 0, width, height);
	}
	
	[[nodiscard]] bool shouldClose() const {
		return glfwWindowShouldClose(window);
	}
	
	void postToScreen() const {
		glfwSwapBuffers(window);
	}
	
	void makeCurrent() const {
		glfwMakeContextCurrent(window);
		setProjection(projection);
		mode = scaleMode;
		pMode = posMode;
	}
	
	void setWindowScalable(bool val) const {
		if (val) {
			glfwSetFramebufferSizeCallback(window, processScale);
		} else {
			glfwSetFramebufferSizeCallback(window, nullptr);
		}
	}
	
	void setVsync(bool val) {
		if (val) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
	}
	
	void setScaleMode(ScaleMode s) {
		if (s == EXPAND && (posMode == ABS_COORD || posMode == STD_COORD)) {
			throw std::runtime_error("Unsupported scalemode EXPAND in *_COORD posmode.");
		}
		scaleMode = s;
		makeCurrent();
	}
	
	void setPosMode(PosMode p) {
		if ((p == ABS_COORD || p == STD_COORD) && scaleMode == EXPAND) {
			throw std::runtime_error("Unsupported posmode *_COORD in EXPAND scalemode.");
		}
		posMode = p;
		int w, h;
		switch (p) {
			case PIXEL_NEG:
				glfwGetWindowSize(window, &w, &h);
				setProjection(glm::ortho(0.0F, (float)w, 0.0F, (float)h));
				break;
			case PIXEL_POS:
				glfwGetWindowSize(window, &w, &h);
				setProjection(glm::ortho(0.0F, (float)w, (float)h, 0.0F));
				break;
			case ABS_COORD:
				setProjection(glm::ortho(0.0F, 1.0F, 0.0F, 1.0F));
				break;
			case STD_COORD:
				setProjection(glm::ortho(-1.0F, 1.0F, -1.0F, 1.0F));
				break;
		}
		makeCurrent();
	}
	
	void maximize() const {
		glfwMaximizeWindow(window);
	}
	
	void fullscreen(GLFWmonitor* m) const {
		auto _mode = glfwGetVideoMode(m);
		glfwSetWindowMonitor(window, m, 0, 0, _mode->width, _mode->height, _mode->refreshRate);
	}
	
	void setTitle(const std::string& val) const {
		glfwSetWindowTitle(window, val.c_str());
	}
	
	void setSize(int x, int y) const {
		glfwSetWindowSize(window, x, y);
	}
	
	void setPos(int x, int y) const {
		glfwSetWindowPos(window, x, y);
	}
	
	[[nodiscard]] glm::ivec2 getPos() const {
		int x, y;
		glfwGetWindowPos(window, &x, &y);
		return {x, y};
	}
	
	[[nodiscard]] glm::ivec2 getSize() const {
		int x, y;
		glfwGetWindowSize(window, &x, &y);
		return {x, y};
	}
	
	void hide() const {
		glfwHideWindow(window);
	}
	
	void show() const {
		glfwShowWindow(window);
	}
	
	void focus() const {
		glfwFocusWindow(window);
	}
};


#endif //QUANTUNGRAPHICSTOOLKIT_WINDOW_H
