#include "qgt/WindowFactory.h"

int main() {
	auto w = WindowFactory().title("TestWindow").size(1024, 768).scaleMode(SCALE).posMode(PIXEL_NEG)
			.defaultContext().forceAspectRatio(16, 9).scalable(true).sizeLimitMin(200, 200)
			.sizeLimitMax(2000, 2000).windowedFullscreen().construct();
	
	
	while (!w.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
		
		w.postToScreen();
		glfwPollEvents();
	}
	return 0;
}
