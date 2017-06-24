#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "Texture.h"
#include "stb_image.h"

class ImageTexture : public Texture
{
public:
	ImageTexture();
	ImageTexture(unsigned char *_imageData, int _width, int _height);

	Vector3 Value(const Vector2 &uv, const Vector3 &p) const override;

private:
	unsigned char *imageData;
	int width, height;
};

#endif