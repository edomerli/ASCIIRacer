#pragma once

#include "Car.hpp"

class PlayerCar : public Car
{
public:
	int level = 0;
	int points = 0;
	void onStart() override;
	void onUpdate() override;
	void onCollision(PhysicalObject collider) override;

	PlayerCar(Point2D position);
};