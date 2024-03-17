#include "Command.h"

#include "GameObject.h"

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
	GetGameObject()->ProcessMovement(input);
}

dae::Move::Move(GameObject* gameObject) :
	GameObjectCommand{gameObject}
{
}


