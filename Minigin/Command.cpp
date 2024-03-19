#include "Command.h"

#include "GameObject.h"
#include "Components/MovementComponent.h"

dae::GameObject* dae::GameObjectCommand::GetGameObject() const
{
	return m_Owner;
}

dae::GameObjectCommand::GameObjectCommand(GameObject* gameObject) :
	m_Owner{gameObject}
{
	
}

void dae::Move::ExecuteMovement(const glm::vec2& input)
{
	m_pMovementComp->ApplyMovement(input);
}

dae::Move::Move(GameObject* gameObject) :
	GameObjectCommand{gameObject}
{
	m_pMovementComp = gameObject->GetComponentByClass<MovementComponent>();
}


