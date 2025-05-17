#include "AbstractSyntaxTree.h"

#include"VariateProxy.h"

uint32_t AstNode::defineTimes = 0;
AbstractSyntaxTree abstractSyntaxTree;

std::unordered_map<std::string, std::string> ktm_class_mapping =
{
	{"struct ktm::vec<2,float,void>", "vec2"},
	{"struct ktm::vec<3,float,void>", "vec3"},
	{"struct ktm::vec<4,float,void>", "vec4"},
	{"struct ktm::vec<2,int,void>", "ivec2"},
	{"struct ktm::vec<3,int,void>", "ivec3"},
	{"struct ktm::vec<4,int,void>", "ivec4"},
	{"struct ktm::vec<2,unsigned int,void>", "uvec2"},
	{"struct ktm::vec<3,unsigned int,void>", "uvec3"},
	{"struct ktm::vec<4,unsigned int,void>", "uvec4"},
	{"struct ktm::vec<2,bool,void>", "bvec2"},
	{"struct ktm::vec<3,bool,void>", "bvec3"},
	{"struct ktm::vec<4,bool,void>", "bvec4"},
};