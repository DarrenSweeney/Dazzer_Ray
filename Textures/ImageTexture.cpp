#include "ImageTexture.h"

ImageTexture::ImageTexture() { }

ImageTexture::ImageTexture(const char* imageLoc)
{
	int comp;
	imageData = stbi_load(imageLoc, &width, &height, &comp, 0);

	if (!imageData)
		printf("ImageTexture:: Image was not loaded");
}

ImageTexture::~ImageTexture()
{
	if (imageData)
		delete imageData;
}

Vector3 ImageTexture::Value(const Vector2 &uv, const Vector3 &p) const
{
	if (imageData)
	{
		int i = uv.u * width;
		int j = (1 - uv.v) * height - 0.001f;

		if (i < 0)	i = 0;
		if (j < 0)	j = 0;
		if (i > width - 1)	i = width - 1;
		if (j > height - 1)	j = height - 1;

		float r = int(imageData[3 * i + 3 * width * j]) / 255.0f;
		float g = int(imageData[3 * i + 3 * width * j + 1]) / 255.0f;
		float b = int(imageData[3 * i + 3 * width * j + 2]) / 255.0f;

		return Vector3(r, g, b);
	}
}