#include "GameObjects/LevelObjects/PlayerCar.hpp"
#include "GameObjects/LevelObjects/Upgrade.hpp"
#include "GameObjects/LevelObjects/Obstacle.hpp"
#include "Engine/Graphics.hpp"
#include "Core/Utilities.hpp"

#include "Engine/System.hpp"
#include "Engine/Keyboard.hpp"
#include "Engine/GameEngine.hpp"

PlayerCar::PlayerCar(Point2D position) {
	this->name = "PlayerCar";
	this->layer = Layer::Content;
	this->velocity = Point2D(0, 0);
	Size size;
	std::string directory = System::getExecutableDirectory();
	this->sprite = Graphics::loadSpriteFromFile(directory + "/sprites/PlayerCar.txt", size);
	this->rect = Rect(position, size);
}

void PlayerCar::onStart() {}
void PlayerCar::onUpdate() {
	float speedX = 100;
	float speedY = 50;
	KeyboardStatus status = Keyboard::currentStatus;
	if (status.isDown(Key::Right)) {
		velocity.x = speedX;
	}
	else if (status.isDown(Key::Left)) {
		velocity.x = -speedX;
	}
	else {
		velocity.x = 0;
	}
	
}
void PlayerCar::onCollision(CollisionInfo collisionInfo) {
	ptr_GameObject collider = collisionInfo.collider;

	if (collider->solid) {
		if (collisionInfo.future.left || collisionInfo.future.right || collisionInfo.future.top) {
			this->velocity.x = 0;
			this->sprite[1][1].character = 'H';
		}

		if (collisionInfo.present.top) {
			//Scontro verticale
			this->sprite[1][1].character = 'V';

			//TODO: Non � garantito che questo controllo sia corretto
			if (this->rect.position.x + this->rect.size.width > 40) { 
				this->rect.position.x--;
			}
			else if (this->rect.position.x <= 30) { 
				this->rect.position.x++; 
			}

			this->velocity.x = 0;
		}
	}

	//cast per poter accedere ai rispettivi campi
	Upgrade* up = dynamic_cast<Upgrade*>(collider);
	Obstacle* obs = dynamic_cast<Obstacle*>(collider);
	if (collider->name == "Upgrade") { 
		this->points += up->bonus; 
		collider->toBeDestroyed = true; 

		up->parentLevel->removedIds.push_back(up->generationId);
	}
	else if (collider->name == "Obstacle") { 
		this->points -= obs->damage; 
		collider->toBeDestroyed = true; 

		obs->parentLevel->removedIds.push_back(obs->generationId);
	}
}