#include "ImageTexture.h"

ImageTexture::ImageTexture() { }

ImageTexture::ImageTexture(unsigned char *_imageData, int _width, int _height)
	: imageData(_imageData), width(_width), height(_height)
{

}

Vector3 ImageTexture::Value(const Vector2 &uv, const Vector3 &p) const
{
	int i = uv.u * width;
	int j = (1 - uv.v) * height - 0.001f;

	if (i < 0)	i = 0;
	if (j < 0)	j = 0;
	if (i > width - 1)	i = width - 1;
	if (j > height - 1)	j = height - 1;

	float r = int(imageData[3 * i + 3 * width * j])		/ 255.0f;
	float g = int(imageData[3 * i + 3 * width * j + 1])	/ 255.0f;
	float b = int(imageData[3 * i + 3 * width * j + 2]) / 255.0f;

	return Vector3(r, g, b);
}