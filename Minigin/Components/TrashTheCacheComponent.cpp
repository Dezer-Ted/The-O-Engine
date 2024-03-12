#include "TrashTheCacheComponent.h"

#include <chrono>
#include <SDL_syswm.h>

#include "../imgui-1.89.5/imgui.h"
#include "../imgui-1.89.5/imgui_plot.h"

void TrashTheCacheComponent::Render()
{
	ImGui::Begin("Exercise 2");
	ImGui::InputInt("# Samples", &m_SampleAmount);
	ImGui::SetWindowSize(ImVec2{500, 500});
	if(ImGui::Button("Trash The Cache with ints"))
	{
		PlotInts();
		m_ShowIntPlot = true;
	}
	if(m_ShowIntPlot)
	{
		ImGui::Plot("Integer Comparison", m_IntConfig);

	}
	if(ImGui::Button("Trash the Cache with Gameobjects"))
	{
		PlotGameObjects();
		m_ShowGameObjectPlot = true;
	}
	if(m_ShowGameObjectPlot)
	{
		ImGui::Plot("Gameobject Comparison", m_GameObjectConfig);
	}
	if(ImGui::Button("Trash the cache with Alt Gameobjects"))
	{
		PlotAltGameObjects();
		m_ShowAltGameObjectPlot = true;
	}
	if(m_ShowAltGameObjectPlot)
	{
		ImGui::Plot("Alt Gameobject Comparison",m_GameObjectAltConfig);
	}
	ImGui::End();
}

std::vector<long long> TrashTheCacheComponent::TrashTheCacheWithInts()
{
	std::vector<long long> times;

	int step = 1;
	while(step <= 1024)
	{
		const auto startTime{std::chrono::high_resolution_clock::now()};
		for(int i = 0; i < m_IntegerList.size(); i += step)
		{
			m_IntegerList[i] *= 2;
		}
		const auto endTime{std::chrono::high_resolution_clock::now()};
		const auto total{std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()};
		times.push_back(total);
		step *= 2;
	}
	return times;
}

std::vector<long long> TrashTheCacheComponent::TrashTheCacheWithGameObjects()
{
	std::vector<long long> times;

	int step = 1;
	while(step <= 1024)
	{
		const auto startTime{std::chrono::high_resolution_clock::now()};
		for(int i = 0; i < m_GameObject3DList.size(); i += step)
		{
			m_GameObject3DList[i].ID *= 2;
		}
		const auto endTime{std::chrono::high_resolution_clock::now()};
		const auto total{std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()};
		times.push_back(total);
		step *= 2;
	}
	return times;
}

void TrashTheCacheComponent::InitGameObjects()
{
	for(int i = 0; i < static_cast<int>(pow(2, 26)); ++i)
	{
		m_GameObject3DList.emplace_back(2);
	}
}

void TrashTheCacheComponent::PlotGameObjects()
{
	InitGameObjects();
	std::vector<std::vector<long long>> times;
	times.reserve(m_SampleAmount);
	for(int i = 0; i < m_SampleAmount; ++i)
	{
		times.push_back(TrashTheCacheWithGameObjects());
	}
	uint32_t selection_start = 0;
	uint32_t selection_length = 0;
	m_AverageTimesGameObject = GetAverage(times);
	ImGui::PlotConfig config{};
	config.values.ys = m_AverageTimesGameObject.get();
	config.values.xs = m_PowerOfTwoAxis.get();
	config.frame_size = ImVec2{250, 100};
	config.values.count = static_cast<int>(times[0].size());
	config.values.color = ImColor{0.f, 1.f, 0.f};
	config.scale.min = 0;
	config.scale.max = *std::max_element(m_AverageTimesGameObject.get(), m_AverageTimesGameObject.get() + times[0].size());
	config.tooltip.show = true;
	config.grid_x.show = true;
	config.grid_y.show = true;
	config.selection.show = true;
	config.selection.start = &selection_start;
	config.selection.length = &selection_length;
	config.line_thickness = 2.f;

	m_GameObjectConfig = config;
	m_GameObject3DList.clear();
}

void TrashTheCacheComponent::InitInts()
{
	for(int i = 0; i < static_cast<int>(pow(2, 26)); ++i)
	{
		m_IntegerList.push_back(2);
	}
}

void TrashTheCacheComponent::PlotInts()
{
	InitInts();
	std::vector<std::vector<long long>> times;
	times.reserve(m_SampleAmount);
	for(int i = 0; i < m_SampleAmount; ++i)
	{
		times.push_back(TrashTheCacheWithInts());
	}
	uint32_t selection_start = 0;
	uint32_t selection_length = 0;
	m_AverageTimesInt = GetAverage(times);
	ImGui::PlotConfig config{};
	config.values.ys = m_AverageTimesInt.get();
	config.values.xs = m_PowerOfTwoAxis.get();
	config.frame_size = ImVec2{250, 100};
	config.values.count = static_cast<int>(times[0].size());
	config.values.color = ImColor{1.f, 0.f, 0.f};
	config.scale.min = 0;
	config.scale.max = *std::max_element(m_AverageTimesInt.get(), m_AverageTimesInt.get() + times[0].size());
	config.tooltip.show = true;
	config.grid_x.show = true;
	config.grid_y.show = true;
	config.selection.show = true;
	config.selection.start = &selection_start;
	config.selection.length = &selection_length;
	config.line_thickness = 2.f;

	m_IntConfig = config;
	m_IntegerList.clear();
}

void TrashTheCacheComponent::InitAltGameObjects()
{
	for(int i = 0; i < static_cast<int>(pow(2, 26)); ++i)
	{
		m_GameObject3DAltList.emplace_back(2);
	}
}

void TrashTheCacheComponent::PlotAltGameObjects()
{

	InitAltGameObjects();
	std::vector<std::vector<long long>> times;
	times.reserve(m_SampleAmount);
	for(int i = 0; i < m_SampleAmount; ++i)
	{
		times.push_back(TrashTheCacheWithAltGameObjects());
	}
	uint32_t selection_start = 0;
	uint32_t selection_length = 0;
	m_AverageAltGameObjectTimes = GetAverage(times);
	ImGui::PlotConfig config{};
	config.values.ys = m_AverageAltGameObjectTimes.get();
	config.values.xs = m_PowerOfTwoAxis.get();
	config.frame_size = ImVec2{250, 100};
	config.values.count = static_cast<int>(times[0].size());
	config.values.color = ImColor{1.f, 0.f, 0.f};
	config.scale.min = 0;
	config.scale.max = *std::max_element(m_AverageAltGameObjectTimes.get(), m_AverageAltGameObjectTimes.get() + times[0].size());
	config.tooltip.show = true;
	config.grid_x.show = true;
	config.grid_y.show = true;
	config.selection.show = true;
	config.selection.start = &selection_start;
	config.selection.length = &selection_length;
	config.line_thickness = 2.f;

	m_GameObjectAltConfig = config;
	m_GameObject3DAltList.clear();
}

std::vector<long long> TrashTheCacheComponent::TrashTheCacheWithAltGameObjects()
{
	std::vector<long long> times;

	int step = 1;
	while(step <= 1024)
	{
		const auto startTime{std::chrono::high_resolution_clock::now()};
		for(int i = 0; i < m_GameObject3DAltList.size(); i += step)
		{
			m_GameObject3DAltList[i].ID *= 2;
		}
		const auto endTime{std::chrono::high_resolution_clock::now()};
		const auto total{std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()};
		times.push_back(total);
		step *= 2;
	}
	return times;
}

std::unique_ptr<float[]> TrashTheCacheComponent::GetAverage(const std::vector<std::vector<long long>>& times)
{
	std::unique_ptr<float[]> averageTimes = std::make_unique<float[]>(times[0].size());
	for(int i = 0; i < times[0].size(); ++i)
	{
		float total{};
		for(int j = 0; j < times.size(); ++j)
		{
			total += static_cast<float>(times[j][i]);
		}
		total /= static_cast<float>(times.size());
		averageTimes[i] = total;
		total = 0;

	}
	return std::move(averageTimes);
}

TrashTheCacheComponent::TrashTheCacheComponent(dae::GameObject* pParent) :
	BaseComponent(pParent),
	m_SampleAmount{10}
{
	m_PowerOfTwoAxis = std::make_unique<float[]>(11);
	float powerOfTwo{1};
	for(int i = 0; i < 11; ++i)
	{
		m_PowerOfTwoAxis[i] = powerOfTwo;
		powerOfTwo *= 2;
	}
}
