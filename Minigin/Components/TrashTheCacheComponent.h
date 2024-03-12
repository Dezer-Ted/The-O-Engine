#pragma once
#include <memory>
#include <vector>

#include "BaseComponent.h"
#include "../imgui-1.89.5/imgui_plot.h"


class TrashTheCacheComponent final : public dae::BaseComponent {
public:
	TrashTheCacheComponent(dae::GameObject* pParent);
	TrashTheCacheComponent(const TrashTheCacheComponent& component) = delete;
	TrashTheCacheComponent(TrashTheCacheComponent&& component) = delete;
	TrashTheCacheComponent& operator=(const TrashTheCacheComponent& component) = delete;
	TrashTheCacheComponent& operator=(TrashTheCacheComponent&& component) = delete;
	~TrashTheCacheComponent() override = default;
	void Render() override;

private:
	struct Transform {
		float matrix[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};

	class GameObject3D {
	public:
		Transform transform;
		int       ID;

		GameObject3D(int Id)
		{
			ID = Id;
			transform = Transform{};
		}
	};

	class GameObject3DAlt {
	public:
		std::unique_ptr<Transform> transform;
		int                        ID;

		GameObject3DAlt(int id)
		{
			ID = id;
			transform = std::make_unique<Transform>();
		}
	};

	std::vector<int>             m_IntegerList;
	std::vector<GameObject3D>    m_GameObject3DList;
	std::vector<GameObject3DAlt> m_GameObject3DAltList;
	int                          m_SampleAmount;
	std::vector<long long>       TrashTheCacheWithInts();
	std::vector<long long>       TrashTheCacheWithGameObjects();
	void                         InitGameObjects();
	void                         PlotGameObjects();
	void                         InitInts();
	void                         PlotInts();
	void                         InitAltGameObjects();
	void                         PlotAltGameObjects();
	std::vector<long long>       TrashTheCacheWithAltGameObjects();
	std::unique_ptr<float[]>     GetAverage(const std::vector<std::vector<long long>>& times);
	std::unique_ptr<float[]>     m_PowerOfTwoAxis;
	std::unique_ptr<float[]>     m_AverageTimesInt;
	std::unique_ptr<float[]>     m_AverageTimesGameObject;
	std::unique_ptr<float[]>     m_AverageAltGameObjectTimes;
	bool                         m_ShowIntPlot{false};
	bool                         m_ShowGameObjectPlot{false};
	bool                         m_ShowAltGameObjectPlot{false};
	ImGui::PlotConfig            m_IntConfig{};
	ImGui::PlotConfig            m_GameObjectConfig{};
	ImGui::PlotConfig            m_GameObjectAltConfig{};
};
