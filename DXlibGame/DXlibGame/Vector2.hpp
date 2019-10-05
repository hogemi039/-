#ifndef DEF_VECTOR2
#define DEF_VECTOR2

struct Vector2
{
public:
	float x{};
	float y{};
	Vector2() = default;
	Vector2(float x, float y) :x(x), y(y) {};
};

#endif
