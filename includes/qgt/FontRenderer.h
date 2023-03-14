#ifndef QUANTUNGRAPHICSTOOLKIT_FONTRENDERER_H
#define QUANTUNGRAPHICSTOOLKIT_FONTRENDERER_H

#include <ft2build.h>
#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include FT_FREETYPE_H
#include "RenderableCharacter.h"
#include "logger.h"
#include "Shader.h"
#include "states.h"

static const std::string defVsh = "#version 330 core\nlayout (location = 0) in vec4 vertex;\nout vec2 texCoords;\n\nuniform mat4 projection;\n\nvoid main() {\n    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n    texCoords = vertex.zw;\n}";
static const std::string defFsh = "#version 330 core\nin vec2 texCoords;\nout vec4 color;\n\nuniform sampler2D text;\nuniform vec3 textColor;\n\nvoid main() {\n    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, texCoords).r);\n    color = vec4(textColor, 1.0) * sampled;\n}";

class FontRenderer {
public:
	GLuint vao, vbo;
	FT_Library lib;
	std::vector<std::unordered_map<wchar_t, RenderableCharacter>> fonts;
	Shader s;
	
	FontRenderer() : FontRenderer(Shader(defVsh, defFsh)) {
	}
	
	FontRenderer(Shader shader) : s(shader) {
		if (FT_Init_FreeType(&lib)) {
			log(FATAL, "Failed to initialize Freetype Library");
		} else {
			log(INFO, "Freetype Library initialized.");
		}
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	// 1 for ascii 2 for cjk
	size_t loadFont(const std::string& path, uint32_t mode, int size) {
		FT_Face face;
		if (FT_New_Face(lib, path.c_str(), 0, &face)) {
			log(ERROR, "Error while reading font file " + path);
		} else {
			log(INFO, "Loaded vector font file " + path + " got font face " + face->family_name);
		}
		FT_Set_Pixel_Sizes(face, 0, size);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		std::vector<std::pair<wchar_t, wchar_t>> toLoad;
		
		if (mode % 2 != 0) {
			toLoad.emplace_back(0, 128);
		}
		
		if ((mode >> 1) % 2 != 0) {
			toLoad.emplace_back(0x4E00, 0x9FEA);
			toLoad.emplace_back(0x3430, 0x4DB5);
			toLoad.emplace_back(0xF900, 0xFAD9);
		}
		
		std::unordered_map<wchar_t, RenderableCharacter> fontMap;
		
		for (const auto& range : toLoad) {
			for (auto c = range.first; c <= range.second; ++c) {
				if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
					log(ERROR, "Error while loading glyph " + std::to_string(c));
				} else {
					log(DEBUG, "Loaded glyph " + std::to_string(c) +" from face " + face->family_name);
				}
				GLuint tex;
				glGenTextures(1, &tex);
				glBindTexture(GL_TEXTURE_2D, tex);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				auto ch = RenderableCharacter(tex, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x);
				fontMap.insert(std::make_pair(c, ch));
			}
		}
		fonts.emplace_back(fontMap);
		FT_Done_Face(face);
		return fonts.size() - 1;
	}
	
	void render(size_t font, const std::wstring& text, float x, float y, float scale, glm::vec3 color) {
		s.use();
		s.setVec3f("textColor", color);
		s.setMat4f("projection", getProjection());
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);
		
		for (const auto& item : text) {
			RenderableCharacter c = (*((fonts[font]).find(item))).second;
			GLfloat xPos = x + c.bearing.x * scale;
			GLfloat yPos = y - (c.size.y - c.bearing.y) * scale;
			GLfloat w = c.size.x * scale;
			GLfloat h = c.size.y * scale;
			
			GLfloat vertices[6][4] = {
					{xPos, yPos + h, 0.0, 0.0},
					{xPos, yPos, 0.0, 1.0},
					{xPos + w, yPos, 1.0, 1.0},
					{xPos, yPos + h, 0.0, 0.0},
					{xPos + w, yPos, 1.0, 1.0},
					{xPos + w, yPos + h, 1.0, 0.0}
			};
			glBindTexture(GL_TEXTURE_2D, c.texId);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (c.advance >> 6) * scale;
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};




#endif //QUANTUNGRAPHICSTOOLKIT_FONTRENDERER_H
