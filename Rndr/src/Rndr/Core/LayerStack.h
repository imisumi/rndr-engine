#pragma once

#include "Base.h"
#include "Layer.h"

#include <vector>

namespace Rndr {

	class  LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		// std::vector<Layer*>::iterator m_LayerInsert;
		// std::vector<Layer*>::iterator m_LayerInsert = m_Layers.begin();
		unsigned int m_LayerInsertIndex = 0;
	};

}