#include "MovementCommand.h"
#include "../Components/MovementComponent.h"
void dae::Move::Execute2DAxis(const glm::vec2& input)
{
	m_pMovementComp->ApplyMovement(input);
}

dae::Move::Move(GameObject* gameObject) :
	GameObjectCommand{gameObject}
{
	m_pMovementComp = gameObject->GetComponentByClass<MovementComponent>();
}
