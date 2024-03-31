#pragma once
#include <functional>

#include "BaseComponent.h"
#include "../SceneObjects/GameObject.h"

namespace dae
{
	class MiscFunctionComponent final : public BaseComponent {
	public:
		MiscFunctionComponent(GameObject* parent);
		MiscFunctionComponent(const MiscFunctionComponent& component) = delete;
		MiscFunctionComponent(MiscFunctionComponent&& component) = delete;
		MiscFunctionComponent& operator=(const MiscFunctionComponent& component) = delete;
		MiscFunctionComponent& operator=(MiscFunctionComponent&& textComponent) = delete;
		~MiscFunctionComponent() override = default;
		void SetFunction(const std::function<void(GameObject*)>& function);
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:
		std::function<void(GameObject*)> m_Function;
	};
}

