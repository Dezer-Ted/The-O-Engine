#pragma once
#include <iostream>
#include <memory>
#include <vector>

#include "Transform.h"
#include "Components/BaseComponent.h"
#include "Components/TextureComponent.h"
#include "Components/EncircleComponent.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update();
		void Render() const;
		void LateUpdate();

		
		void SetPosition(float x, float y);

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject&      operator=(const GameObject& other) = delete;
		GameObject&      operator=(GameObject&& other) = delete;
		Transform& GetTransform();
		void             DestroyComponents();
		bool             GetDestructionFlag() const;
		void             DestroyObject();	
		template <typename T>
        T* AddComponent()
        {
			m_ComponentList.push_back(std::make_unique<T>(this));
			return static_cast<T*>(m_ComponentList.back().get());
        }
        
        template <typename T>
        T* GetComponentByClass()
        {
        	try
        	{
        		for(auto& component : m_ComponentList)
            	{
					
            		T* castedComp = dynamic_cast<T*>(component.get());
            		if(castedComp != nullptr)
            		{
            			return castedComp;
            		}
            	}
        		throw "error";
            		
        	}
        	catch(...)
        	{
        		std::cout<< "Gameobject is missing the component\n";
        		return nullptr;
        	}
        
        	
        }
		template<typename T>
		void RemoveComponentByClass()
		{
			try
			{
				for(int i = 0; i < m_ComponentList.size(); ++i)
				{
					T* castedComp = dynamic_cast<T*>(m_ComponentList[i].get());
					if(castedComp != nullptr)
					{
						m_ComponentList[i]->DestroyComponent();
						return;
					}
				}
				throw "error";
			}
			catch(...)
			{
				std::cout << "Cannot Delete non existing Component\n";
			}
		}

		GameObject* GetParent() const;
		void SetParent(GameObject* pParent, bool keepWorldPosition = true);
		const std::vector<GameObject*>& GetChildren();
	private:
		std::vector<GameObject*>                    m_Children;
		GameObject*                                 m_Parent{nullptr};
		Transform                                   m_Transform;
		std::vector<std::unique_ptr<BaseComponent>> m_ComponentList;
		bool                                        m_DestructionFlag {false};
		// todo: mmm, every gameobject has a texture? Is that correct?
		//std::shared_ptr<Texture2D> m_texture{};
	};
}