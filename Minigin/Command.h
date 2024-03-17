#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Command {
		#pragma warning(disable : 4100)
	public:
		virtual ~Command() = default;

		virtual void Execute()
		{
		}

		virtual void ExecuteMovement(const glm::vec2& input)
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
		void ExecuteMovement(const glm::vec2& input) override;
		Move(GameObject* gameObject);
	};
}
