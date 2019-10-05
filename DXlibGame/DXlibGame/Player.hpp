#ifndef DEF_PLAYER
#define DEF_PLAYER
#include "Vector2.hpp"

const float left{ -1.f };
const float right{ 1.f };

struct Player
{
public:
	int handle{};
	Vector2 position_{};
	Vector2 moveVector_{};
	Vector2 GetPos() { return position_; }
	void Init();
	void Update();
	void Move(float);
	void Draw();
};
#endif