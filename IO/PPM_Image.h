#ifndef PPM_WRITER_H
#define PPM_WRITER_H

#include "..\Math\Vector3.h"
#include <string>
#include <fstream>

class PPM_Image
{
public:
	PPM_Image(unsigned int imageWidth, unsigned int imageHeight);
	~PPM_Image();

	void WritePixel(unsigned int pixelPosX, unsigned pixelPosY, Vector3 &rgb);
	void SavePPM(std::string fileName);

private:
	unsigned int width, height;
	uint8_t *data;

	std::ofstream ppmFile;
};

#endif