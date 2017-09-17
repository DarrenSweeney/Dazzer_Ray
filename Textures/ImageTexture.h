#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

//#define STB_IMAGE_IMPLEMENTATION

#include "..\IO\stb_image.h"
#include "Texture.h"

class ImageTexture : public Texture
{
public:
	ImageTexture();
	ImageTexture(const char* imageLoc);
	~ImageTexture();

	Vector3 Value(const Vector2 &uv, const Vector3 &p) const override;

private:
	unsigned char *imageData;
	int width, height;
};

#endif