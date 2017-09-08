#ifndef PPM_WRITER_H
#define PPM_WRITER_H

#include "..\Math\Vector3.h"
#include <string>
#include <fstream>
#include <iostream>

class PPM_Image
{
public:
	PPM_Image();
	PPM_Image(uint16_t imageWidth, uint16_t imageHeight);
	~PPM_Image();

	void WritePixel(unsigned int pixelPosX, unsigned pixelPosY, Vector3 &rgb);
	void SavePPM(std::string fileName, std::ofstream &ppmFile);

private:
	uint16_t width, height;
	uint8_t *data;
};

#endif