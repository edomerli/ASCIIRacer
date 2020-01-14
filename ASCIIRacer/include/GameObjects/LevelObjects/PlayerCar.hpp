#pragma once

#include "GameObjects/PhysicalObject.hpp"

class PlayerCar : public PhysicalObject
{
public:
	int level = 0;
	int points = 0;
	void onStart() override;
	void onUpdate() override;
	void onCollision(ptr_PhysicalObject collider) override;

	PlayerCar(Point2D position);
};