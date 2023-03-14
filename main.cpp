#include "qgt/Window.h"
#include "qgt/FontRenderer.h"

int main() {
	auto w = Window("TestWindow", 800, 600);
	w.setPosMode(PIXEL_NEG);
	w.setScaleMode(SCALE);
	w.setVsync(false);
	
	auto fontRenderer = FontRenderer();
	
	size_t font = fontRenderer.loadFont("jb.ttf", 1, 24);
	
	while (!w.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
		
		fontRenderer.render(font, L"Font Rendering Test", 200.0F, 200.0F, 1.0F, glm::vec3(0.0F, 0.0F, 0.0F));
		
		w.postToScreen();
		glfwPollEvents();
	}
	return 0;
}
