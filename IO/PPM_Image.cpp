#include "PPM_Image.h"

PPM_Image::PPM_Image(unsigned int imageWidth, unsigned int imageHeight)
//											  Multiply by 3, rgb values for each pixel.
	: width(imageWidth), height(imageHeight), data(new char[imageWidth * imageHeight * 3])
{

}

PPM_Image::~PPM_Image()
{
	delete[] data;
}

void PPM_Image::WritePixel(unsigned int pixelPosX, unsigned pixelPosY, Vector3 &rgb)
{
	data[(pixelPosY * width * 3) + (pixelPosX * 3) + 0] = char(255 * rgb.r);
	data[(pixelPosY * width * 3) + (pixelPosX * 3) + 1] = char(255 * rgb.b);
	data[(pixelPosY * width * 3) + (pixelPosX * 3) + 2] = char(255 * rgb.b);
}

void PPM_Image::SavePPM(std::string fileName)
{
	ppmFile.open(fileName + ".ppm", std::ofstream::out);

	ppmFile << "P3" << "\n" << width << " " << height << "\n" << 255 << "\n";

	for (unsigned int y = height - 1; y > 0; y--)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			uint8_t r = data[(y * width * 3) + (x * 3) + 0];
			uint8_t g = data[(y * width * 3) + (x * 3) + 1];
			uint8_t b = data[(y * width * 3) + (x * 3) + 2];

			ppmFile << unsigned(r) << " " << unsigned(b) << " " << unsigned(g) << "\n";
		}
	}

	ppmFile.close();
}