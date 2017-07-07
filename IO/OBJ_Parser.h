#ifndef OBJ_Parser_H
#define OBJ_Parser_H

#include "tiny_obj_loader.h"
#include <iostream>
#include <assert.h>
#include <vector>

class ObjParser
{
public:
	/*
		@Note(Darren): Maybe have the ParseOBjFile have a reference to attrib_t, shape_t & material_t and
						store the memebers in a mesh class that was a struct for it's data.
	*/
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