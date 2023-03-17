#ifndef QUANTUNGRAPHICSTOOLKIT_STATICFONTRENDERER_H
#define QUANTUNGRAPHICSTOOLKIT_STATICFONTRENDERER_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <string>
#include "glad/glad.h"
#include "Shader.h"

static const std::string staticDefVsh = "#version 330 core\nlayout (location = 0) in vec4 vertex;\nout vec2 texCoords;\n\nuniform mat4 projection;\n\nvoid main() {\n    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n    texCoords = vertex.zw;\n}";
static const std::string staticDefFsh = "#version 330 core\nin vec2 texCoords;\nout vec4 color;\n\nuniform sampler2D text;\nuniform vec3 textColor;\n\nvoid main() {\n    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);\n    color = vec4(textColor, 1.0) * sampled;\n}";

class StaticFontRenderer {
	GLuint vao{};

	StaticFontRenderer(const std::string& fontPath, int size, const std::wstring& text, Shader s, float x, float y, float scale, glm::vec3 color) {
		FT_Library lib;
		FT_Init_FreeType(&lib);
		FT_Face face;
		FT_New_Face(lib, fontPath.c_str(), 0, &face);
		FT_Set_Pixel_Sizes(face, 0, size);

		GLuint vbo;

		std::vector<float[24]> data;

		unsigned int idx = 0;
		for (const auto &item: text) {
			if (FT_Load_Char(face, item, FT_LOAD_RENDER)) {
				log(ERROR, "Error while loading glyph " + std::to_string(item));
			} else {
				log(DEBUG, "Loaded glyph " + std::to_string(item) +" from face " + face->family_name);
			}

			int sizeW, sizeH;
			sizeW = face->glyph->bitmap.width;
			sizeH = face->glyph->bitmap.rows;
			int bearingX, bearingY;
			bearingX = face->glyph->bitmap_left;
			bearingY = face->glyph->bitmap_top;
			int advance = face->glyph->advance.x;

			float xPos = x + bearingX * scale;
			float yPos = y - (sizeH - bearingY) * scale;
			float w = sizeW * scale;
			float h = sizeH * scale;

			float glyph[24] = {

			};

			data.emplace_back({xPos, yPos + h, 0.0, 0.0,
			                   xPos, yPos, 0.0, 1.0,
			                   xPos + w, yPos, 1.0, 1.0,
			                   xPos, yPos + h, 0.0, 0.0,
			                   xPos + w, yPos, 1.0, 1.0,
			                   xPos + w, yPos + h, 1.0, 0.0});
			++idx;
		}

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4 * text.size(), nullptr, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
};


#endif //QUANTUNGRAPHICSTOOLKIT_STATICFONTRENDERER_H
