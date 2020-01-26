#pragma once

#include "GameObjects/GameObject.hpp"
#include "Core/CollisionInfo.hpp"

class PlayerCar : public GameObject
{
private:

	/// <summary>	La velocit� massima. </summary>
	float maxSpeed;

	/// <summary>	La velocit� di base. </summary>
	float baseSpeed;

	/// <summary>	L'accelerazione. </summary>
	float acceleration;

public:

	/// <summary>	Il punteggio del giocatore. </summary>
	int points;

	/// <summary>	Eseguito ogni ciclo del motore di gioco. </summary>
	void onUpdate();

	/// <summary>	Chiamato in caso di collisione. </summary>
	///
	/// <param name="collisionInfo">	Le informazioni sulla collisione. </param>
	void onCollision(CollisionInfo collisionInfo);

	/// <summary>	Costruttore. </summary>
	///
	/// <param name="position">	La posizione iniziale. </param>
	/// <param name="baseSpeed"> La velocit� di base. </param>
	/// <param name="maxSpeed">	La velocit� massima. </param>
	/// <param name="acceleration"> L'accelerazione. </param>

	PlayerCar(Point2D position, float baseSpeed, float maxSpeed, float acceleration);
};