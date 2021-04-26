#include "CollisionHandler.h"
#include"../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler>CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*>CollisionHandler::prevCollisions = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();

CollisionHandler::CollisionHandler() {
	colliders.reserve(10);
	prevCollisions.reserve(10);
}
CollisionHandler::~CollisionHandler() {
	OnDestroy();
}
CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();

}
void CollisionHandler::OnCreate()
{
	colliders.clear();
	prevCollisions.clear();
}

void CollisionHandler::AddObject(GameObject* go_)
{
	colliders.push_back(go_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_,
		CoreEngine::GetInstance()->GetScreenWidth(),
		CoreEngine::GetInstance()->GetScreenHeight(),
		CoreEngine::GetInstance()->GetCamera());

	GameObject* hitResult = nullptr;
	float shortestDistance = FLT_MAX;

	for (auto g : colliders) {
		if (mouseRay.IsColliding(&g->GetBoundingBox())) {
			if (mouseRay.intersectionDist < shortestDistance) {
				hitResult = g;
				shortestDistance = mouseRay.intersectionDist;
			}
		}

	}

	if (hitResult) {
		hitResult->SetHit(true, buttonType_);
	}

	for (auto c : prevCollisions) {
		if (hitResult != c && c != nullptr) {
			c->SetHit(false, buttonType_);
		}
	}

	prevCollisions.clear();
	if (hitResult) {
		prevCollisions.push_back(hitResult);
	}

}

void CollisionHandler::OnDestroy()
{
	for (auto entry : colliders) {
		entry = nullptr;
	}
	colliders.clear();
	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}


