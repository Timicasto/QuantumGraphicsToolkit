#ifndef QUANTUMGRAPHICSTOOLKIT_SHADERFACTORY_H
#define QUANTUMGRAPHICSTOOLKIT_SHADERFACTORY_H

#include <vector>
#include <string>
#include <variant>
#include "utils.h"

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

std::string typesToString(GLSLTypes t) {
	if (t & 1) {
		return "bool";
	}
	if ((t >> 1) & 1) {
		return "int";
	}
	if ((t >> 2) & 1) {
		return "uint";
	}
	if ((t >> 3) & 1) {
		return "float";
	}
	if ((t >> 4) & 1) {
		return "bvec2";
	}
	if ((t >> 5) & 1) {
		return "bvec3";
	}
	if ((t >> 6) & 1) {
		return "bvec4";
	}
	if ((t >> 7) & 1) {
		return "ivec2";
	}
	if ((t >> 8) & 1) {
		return "ivec3";
	}
	if ((t >> 9) & 1) {
		return "ivec4";
	}
	if ((t >> 10) & 1) {
		return "uvec2";
	}
	if ((t >> 11) & 1) {
		return "uvec3";
	}
	if ((t >> 12) & 1) {
		return "uvec4";
	}
	if ((t >> 13) & 1) {
		return "vec2";
	}
	if ((t >> 14) & 1) {
		return "vec3";
	}
	if ((t >> 15) & 1) {
		return "vec4";
	}
}

typedef enum ShaderTypes {
	VERTEX = 1,
	FRAGMENT = 2,
	GEOMETRY = 4
} ShaderTypes;

typedef enum GLSLBuiltins {
	VERT_ID = 1,
	GL_POSITION = 2,
	POINT_SIZE = 4,
	FRAG_COLOR = 8,
	POINT_COORD = 16,
} GLSLBuiltins;

typedef enum Operations {
	ADD = 1,
	SUB = 2,
	MUL = 4,
	DIV = 8,
	EQUAL = 16
} Operations;

class ExpressionPart {
public:
	[[nodiscard]] virtual std::string toString() const {}
};

class Operation : public ExpressionPart {
public:
	Operations op;
	
	explicit Operation(Operations o) : op(o) {
	
	}
	
	std::string toString() {
		if (op & 1) {
			return "+";
		}
		if ((op >> 1) & 1) {
			return "-";
		}
		if ((op >> 2) & 1) {
			return "*";
		}
		if ((op >> 3) & 1) {
			return "/";
		}
		if ((op >> 4) & 1) {
			return "=";
		}
	}
};

class Variable : public ExpressionPart {
	GLSLTypes type;
	std::string name;
	bool isBuiltIn;
	GLSLBuiltins builtin;

public:
	Variable(GLSLTypes type, const std::string& name) : type(type), name(name) {
		isBuiltIn = false;
	}
	
	explicit Variable(GLSLBuiltins builtin) : builtin(builtin) {
		isBuiltIn = true;
	}
	
	[[nodiscard]] std::string toString() const override {
		if (isBuiltIn) {
			return (builtin & 1) ? "gl_VertexID" : ((builtin >> 1) & 1) ? "gl_Position" : ((builtin >> 2) & 1) ? "gl_PointSize" : ((builtin >> 3) & 1) ? "gl_FragColor" : "gl_PointCoord";
		} else {
			return typesToString(type) + " " + name;
		}
	}
};

class LiteralValue : public ExpressionPart {
public:
	GLSLTypes type;
	std::string val;
	
	LiteralValue(GLSLTypes t, const std::string& v) : type(t), val(v) {
	
	}
public:
	[[nodiscard]] std::string toString() const {
		if (type & 1) {
			return val;
		}
		if ((type >> 1) & 1) {
			return val;
		}
		if ((type >> 2) & 1) {
			return val + "U";
		}
		if ((type >> 3) & 1) {
			return val + "F";
		}
		if ((type >> 4) & 1) {
			auto splitted = split(val, " ");
			return "bvec2(" + splitted[0] + "," + splitted[1] + ")";
		}
		if ((type >> 5) & 1) {
			auto splitted = split(val, " ");
			return "bvec3(" + splitted[0] + "," + splitted[1] + "," + splitted[2] + ")";
		}
		if ((type >> 6) & 1) {
			auto splitted = split(val, " ");
			return "bvec4(" + splitted[0] + "," + splitted[1] + "," + splitted[2] + "," + splitted[3] + ")";
		}
		if ((type >> 7) & 1) {
			auto splitted = split(val, " ");
			return "ivec2(" + splitted[0] + "," + splitted[1] + ")";
		}
		if ((type >> 8) & 1) {
			auto splitted = split(val, " ");
			return "ivec3(" + splitted[0] + "," + splitted[1] + "," + splitted[2] + ")";
		}
		if ((type >> 9) & 1) {
			auto splitted = split(val, " ");
			return "ivec4(" + splitted[0] + "," + splitted[1] + "," + splitted[2] + "," + splitted[3] + ")";
		}
		if ((type >> 10) & 1) {
			auto splitted = split(val, " ");
			return "uvec2(" + splitted[0] + "U," + splitted[1] + "U)";
		}
		if ((type >> 11) & 1) {
			auto splitted = split(val, " ");
			return "uvec3(" + splitted[0] + "U," + splitted[1] + "U," + splitted[2] + "U)";
		}
		if ((type >> 12) & 1) {
			auto splitted = split(val, " ");
			return "uvec4(" + splitted[0] + "U," + splitted[1] + "U," + splitted[2] + "U," + splitted[3] + "U)";
		}
		if ((type >> 13) & 1) {
			auto splitted = split(val, " ");
			return "vec2(" + splitted[0] + "F," + splitted[1] + "F)";
		}
		if ((type >> 14) & 1) {
			auto splitted = split(val, " ");
			return "vec3(" + splitted[0] + "F," + splitted[1] + "F," + splitted[2] + "F)";
		}
		if ((type >> 15) & 1) {
			auto splitted = split(val, " ");
			return "vec4(" + splitted[0] + "F," + splitted[1] + "F," + splitted[2] + "F," + splitted[3] + "F)";
		}
	}
};

class Expression : public ExpressionPart {
public:
	ExpressionPart parent;
	ExpressionPart child;
	Operation op;
	
	Expression(const ExpressionPart& parent, const ExpressionPart& child, const Operation& op) : parent(parent),
	                                                                                             child(child), op(op) {}
	
	std::string toString() {
		return parent.toString() + op.toString() + child.toString();
	}
};

typedef struct ExpressionVisitor {
public:
	std::string* s;
	ExpressionVisitor(std::string& str) {
		s = &str;
	}
	void operator()(Expression& e) {
		*s += e.toString();
	}
	void operator()(Variable& v) {
		*s += v.toString();
	}
	void operator()(LiteralValue& l) {
		*s += l.toString();
	}
	void operator()(Operation& o) {
		*s += o.toString();
	}
} ExpressionVisitor;

class ShaderFactory {
public:
	std::vector<std::pair<GLSLTypes, std::string>> inputs{};
	std::vector<std::pair<GLSLTypes, std::string>> outputs{};
	std::vector<std::pair<GLSLTypes, std::string>> uniforms{};
	std::vector<std::pair<std::string, LiteralValue>> constants{};
	std::vector<std::variant<Operation, Variable, LiteralValue, Expression>> expressions{};
	ShaderTypes shaderTypes;
	unsigned int shaderVersion;
	
	ShaderFactory() = default;
	
	ShaderFactory version(unsigned int version) {
		shaderVersion = version;
		return *this;
	}
	
	ShaderFactory type(ShaderTypes type) {
		shaderTypes = type;
		return *this;
	}
	
	ShaderFactory addInput(GLSLTypes type, const std::string& name) {
		inputs.emplace_back(type, name);
		return *this;
	}
	
	ShaderFactory addOutput(GLSLTypes type, const std::string& name) {
		outputs.emplace_back(type, name);
		return *this;
	}
	
	ShaderFactory addUniform(GLSLTypes type, const std::string& name) {
		uniforms.emplace_back(type, name);
		return *this;
	}
	
	ShaderFactory addConst(GLSLTypes type, const std::string& name, const std::string& value) {
		constants.emplace_back(name, LiteralValue(type, value));
		return *this;
	}
	
	ShaderFactory assign(const ExpressionPart& target, const ExpressionPart& value) {
		expressions.emplace_back(Expression(target, value, Operation(EQUAL)));
		return *this;
	}
	
	std::string construct() {
		std::stringstream stream;
		stream << "#version " << shaderVersion << " core" << "\n";
		
		stream << "\n";
		
		for (const auto& item : inputs) {
			stream << "in " << typesToString(item.first) << " " << item.second << ";\n";
		}
		
		stream << "\n";
		
		for (const auto& item : outputs) {
			stream << "out " << typesToString(item.first) << " " << item.second << ";\n";
		}
		
		stream << "\n";
		
		for (const auto& item : uniforms) {
			stream << "uniform " << typesToString(item.first) << " " << item.second << ";\n";
		}
		
		stream << "\n";
		
		for (const auto& item : constants) {
			stream << "const " << typesToString(item.second.type) << " " << item.first << " = " << item.second.toString() << ";\n";
		}
	
		stream << "\n" << "void main() {\n";
		
		for (auto item : expressions) {
			auto reg = item.index();
			std::string tmp;
			std::visit(ExpressionVisitor(tmp), item);
			stream << tmp;
			stream << ";\n";
		}
		
		stream << "}";
		
		return stream.str();
	}
};

#endif //QUANTUMGRAPHICSTOOLKIT_SHADERFACTORY_H
