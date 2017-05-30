#ifndef VECTOR_2_H
#define VECTOR_2_H

class Vector2
{
public:
	union
	{
		struct { float x, y; };
		struct { float u, v; };

		float data[2];
	};

	Vector2();
	Vector2(float x, float y);
};

#endif
