#pragma once
#include <glm/glm.hpp>

#include "Command.h"
#include "Command.h"


namespace dae
{
	class GameObject;
	class MovementComponent;
	
	class Command {
		#pragma warning(disable : 4100)

	public:
		virtual ~Command() = default;

		virtual void Execute()
		{
		}

		virtual void Execute2DAxis(const glm::vec2& input)
		{
		}
	};

	class GameObjectCommand : public Command {
	private:
		GameObject* m_Owner;

	protected:
		GameObject* GetGameObject() const;

	public:
		GameObjectCommand(GameObject* gameObject);
		virtual ~GameObjectCommand() = default;
	};

	class Move : public GameObjectCommand {
	public:
		void Execute2DAxis(const glm::vec2& input) override;
		Move(GameObject* gameObject);

	private:
		MovementComponent* m_pMovementComp{nullptr};
	};
}
