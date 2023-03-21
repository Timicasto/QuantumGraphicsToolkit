#ifndef QUANTUMGRAPHICSTOOLKIT_SHADERFACTORY_H
#define QUANTUMGRAPHICSTOOLKIT_SHADERFACTORY_H

#include <vector>
#include <string>

typedef enum GLSLTypes {
	BOOL = 1,
	INT = 2,
	UINT = 4,
	FLOAT = 8,
	BVEC2 = 16,
	BVEC3 = 32,
	BVEC4 = 64,
	IVEC2 = 128,
	IVEC3 = 256,
	IVEC4 = 512,
	UVEC2 = 1024,
	UVEC3 = 2048,
	UVEC4 = 4096,
	VEC2 = 8192,
	VEC3 = 16384,
	VEC4 = 32768
} GLSLTypes;

typedef enum ShaderTypes {
	VERTEX = 1,
	FRAGMENT = 2,
	GEOMETRY = 4
} ShaderTypes;

class ShaderFactory {
	std::vector<std::pair<GLSLTypes, std::string>> inputs;
	std::vector<std::pair<GLSLTypes, std::string>> outputs;
	std::vector<std::pair<GLSLTypes, std::string>> uniforms;
	ShaderTypes type;

	ShaderFactory() = default;
};

#endif //QUANTUMGRAPHICSTOOLKIT_SHADERFACTORY_H
