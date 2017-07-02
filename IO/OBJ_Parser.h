#ifndef OBJ_Parser_H
#define OBJ_Parser_H

#include "tiny_obj_loader.h"
#include <iostream>
#include <assert.h>
#include <vector>

class ObjParser
{
public:
	bool ParseObjFile(const char* fileName, const char* basePath = nullptr, bool triangulate = true);

private:
	void PrintObjInfo(const tinyobj::attrib_t& attrib,
		const std::vector<tinyobj::shape_t>& shapes,
		const std::vector<tinyobj::material_t>& materials);

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
};

#endif