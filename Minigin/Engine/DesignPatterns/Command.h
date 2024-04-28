#pragma once
#include <glm/glm.hpp>

#include "Command.h"
#include "../../SceneObjects/GameObject.h"

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
		virtual ~GameObjectCommand() override = default;
	};

	class MovementComponent;

	class Move final : public GameObjectCommand {
	public:
		void Execute2DAxis(const glm::vec2& input) override;
		Move(GameObject* gameObject);
		virtual ~Move() override = default;

	private:
		MovementComponent* m_pMovementComp{nullptr};
	};

	class PlayerComponent;

	class Die final : public GameObjectCommand {
	public:
		void Execute() override;
		Die(GameObject* pOwner);
		virtual ~Die() override = default;

	private:
		PlayerComponent* m_pPlayerLifeComp{nullptr};
	};

	class GainPoints final : public GameObjectCommand {
	public:
		void Execute() override;
		GainPoints(GameObject* pOwner);
		virtual ~GainPoints() override = default;

	private:
		PlayerComponent* m_pPlayerComp{nullptr};
	};

	//ONLY FOR TESTING PURPOSES
	class PlaySound final : public GameObjectCommand {
	public:
		void Execute() override;
		PlaySound(GameObject* pOwner);
		virtual ~PlaySound() override = default;

	private:
	};
}
