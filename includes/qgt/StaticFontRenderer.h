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
	GLuint vao{}, tex{};
	Shader s;
	glm::vec3 color;
	int length{};

public:
	StaticFontRenderer(const std::string& fontPath, int size, const std::wstring& text, float x, float y, float scale, glm::vec3 color) : StaticFontRenderer(fontPath, size, text, Shader(staticDefVsh, staticDefFsh), x, y, scale, color) {}

	StaticFontRenderer(const std::string& fontPath, int size, const std::wstring& text, Shader sh, float x, float y, float scale, glm::vec3 c) : s(sh), color(c), length(text.size()) {
		FT_Library lib;
		FT_Init_FreeType(&lib);
		FT_Face face;
		FT_New_Face(lib, fontPath.c_str(), 0, &face);
		FT_Set_Pixel_Sizes(face, 0, size);

		GLuint vbo;
		
		auto** data = new float*[text.size()];
		for (int i = 0 ; i < text.size() ; ++i) {
			data[i] = new float[24];
		}
		std::vector<std::tuple<std::vector<unsigned char>, int, int>> glyphs;

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
			
			data[idx][0] = data[idx][4] = data[idx][12] = xPos;
			data[idx][5] = data[idx][9] = data[idx][17] = yPos;
			data[idx][8] = data[idx][16] = data[idx][20] = xPos + w;
			data[idx][1] = data[idx][13] = data[idx][21] = yPos + h;
			
			std::vector<unsigned char> tmp = {face->glyph->bitmap.buffer, face->glyph->bitmap.buffer + face->glyph->bitmap.width * face->glyph->bitmap.rows};
			glyphs.emplace_back(tmp, sizeW, sizeH);
			++idx;
			x += (advance >> 6) * scale;
		}
		
		int totalH = std::get<2>(glyphs[0]), totalW = 0;
		for (const auto& item : glyphs) {
			if (std::get<2>(item) > totalH) {
				totalH = std::get<2>(item);
			}
			totalW += std::get<1>(item);
		}
		
		auto** texture = new unsigned char*[totalW];
		for (int i = 0 ; i < totalW ; ++i) {
			texture[i] = new unsigned char[totalH];
		}
		
		int startX = 0, startY = 0, it = 0;
		for (const auto& item : glyphs)  {
			int currX = 0, currY = 0, tarX = std::get<1>(item) - 1;
			for (const auto& bit : std::get<0>(item)) {
				auto dta = std::get<0>(item) ;
				texture[startX + currX][currY] = bit;
				if (currX == tarX) {
					currX = 0;
					++currY;
				} else {
					++currX;
				}
			}
			
			data[it][2] = data[it][6] = data[it][14] = (float)startX / totalW;
			startX += std::get<1>(item);
			data[it][10] = data[it][18] = data[it][22] = (float)startX / totalW;
			data[it][3] = data[it][15] = data[it][23] = 0.0F;
			data[it][7] = data[it][11] = data[it][19] = (float)std::get<2>(item) / totalH;
			++it;
		}
		
		float vertices[text.size() * 24];
		int cx = 0;
		for (int ch = 0 ; ch < text.size() ; ++ch) {
			for (int vert = 0 ; vert < 24 ; ++vert) {
				vertices[cx] = data[ch][vert];
				++cx;
			}
		}
		
		unsigned char texPtr[totalW * totalH];
		std::fill(texPtr, texPtr + totalW + totalH, 0);
		int ptr = 0;
		for (int iy = 0 ; iy < totalH ; ++iy) {
			for (int ix = 0 ; ix < totalW ; ++ix) {
				texPtr[ptr] = texture[ix][iy];
				++ptr;
			}
		}

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, totalW, totalH, 0, GL_RED, GL_UNSIGNED_BYTE, texPtr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4 * text.size(), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void render() {
		s.use();
		s.setVec3f("textColor", color);
		s.setMat4f("projection", getProjection());
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, 6 * length);
	}
};


#endif //QUANTUNGRAPHICSTOOLKIT_STATICFONTRENDERER_H
