#include "qgt/Window.h"

int main() {
	auto w = Window("TestWindow", 800, 600);
	w.setPosMode(PIXEL_NEG);
	w.setScaleMode(SCALE);
	w.setVsync(false);
	
	
	while (!w.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
		
		w.postToScreen();
		glfwPollEvents();
	}
	return 0;
}
