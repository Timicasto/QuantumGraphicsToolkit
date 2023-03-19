#include <memory>
#include "qgt/WindowFactory.h"
#include "qgt/FontRenderer.h"
#include "qgt/StaticFontRenderer.h"

int main() {
	auto w = WindowFactory().title("TestWindow").size(1280, 720).scaleMode(SCALE).posMode(PIXEL_NEG)
			.defaultContext().forceAspectRatio(16, 9).scalable(true).sizeLimitMin(200, 200)
			.sizeLimitMax(2000, 2000).construct();
	setLogLevel(DEBUG);
	auto renderer = FontRenderer();
	auto font = renderer.loadFont("./JetBrainsMono-Medium.ttf", 0x80, 48);
	
	auto s = StaticFontRenderer("JetBrainsMono-Medium.ttf", 48, L"Test text", 0.0F, 16.0F, 1.0F, glm::vec3(0.0F,0.0F,0.0F));
	
	while (!w.shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
		s.render();
		renderer.render(font, L"Test text", 0.0F, 80.0F, 1.0F, glm::vec3(0.0F, 0.0F, 0.0F));
		
		w.postToScreen();
		glfwPollEvents();
	}
	return 0;
}
