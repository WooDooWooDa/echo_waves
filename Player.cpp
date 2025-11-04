#include "Player.h"
#include <iostream>

void Player::Init()
{
	position.X = 768.0 / 2;
	position.Y = 768.0 / 2;
	speed = 1.0;
	size = LEVEL_TILE_SIZE / 2;
	color = vector3(255, 255, 255);
}

void Player::Update(Uint64 delta)
{
	GameObject::Update(delta);
}

void Player::OnCollisionEnter(CollisionResult res)
{
	std::cout << res.collisionNormal.ToString() << std::endl;
}
