#include "PPM_Image.h"

PPM_Image::PPM_Image() { }

PPM_Image::PPM_Image(unsigned int imageWidth, unsigned int imageHeight)
//											  Multiply by 3, rgb values for each pixel.
//											  TODO(Darren): Test the size difference with uint32_t
	: width(imageWidth), height(imageHeight), data(new uint8_t[imageWidth * imageHeight * 3])
{

}

PPM_Image::~PPM_Image()
{
	delete[] data;
}

void PPM_Image::WritePixel(unsigned int pixelPosX, unsigned pixelPosY, Vector3 &rgb)
{
	data[(pixelPosY * width * 3) + (pixelPosX * 3) + 0] = uint8_t(255 * rgb.r);
	data[(pixelPosY * width * 3) + (pixelPosX * 3) + 1] = uint8_t(255 * rgb.g);
	data[(pixelPosY * width * 3) + (pixelPosX * 3) + 2] = uint8_t(255 * rgb.b);
}

void PPM_Image::SavePPM(std::string fileName, std::ofstream &ppmFile)
{
	ppmFile.open(fileName + ".ppm", std::ofstream::out);

	// 255 is taken as the max component color value.
	ppmFile << "P3" << "\n" << width << " " << height << "\n" << 255 << "\n";

	for (unsigned int y = height; y > 0; y--)
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