#pragma once
namespace dae
{
	class GameObject;

	class BaseComponent {
	public:
		virtual void Update(){}
		virtual void LateUpdate(){}
		virtual void Render(){}
		virtual void FixedUpdate(){}
		BaseComponent(const BaseComponent& baseComponent) = delete;
		BaseComponent(BaseComponent&& baseComponent) = delete;
		explicit       BaseComponent(GameObject* pParent);
		BaseComponent& operator=(const BaseComponent& baseComponent) = delete;
		BaseComponent& operator=(BaseComponent&& baseComponent) = delete;
		virtual        ~BaseComponent();
		virtual bool   GetDestructionFlag();
		virtual void   DestroyComponent();
	protected:
		GameObject* GetParent() const;
	private:
		bool m_DestructionFlag {false};
		GameObject* m_Parent;
		friend class GameObject;
	};
}
