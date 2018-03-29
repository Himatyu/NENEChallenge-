#pragma once
#include"IProvider.h"
#include"Singleton.h"
#include"../Rendering/IRenderable.h"
#include"../Provider/CameraProvider.h"
namespace NeneLabyrinth
{
	namespace Rendering
	{
		class RenderProvider final :
			public Utility::IProvider<IRenderable>,
			public Utility::Singleton<RenderProvider>
		{
		public:
			void Dispatch() override
			{
				auto& cameraProvider = Component::CameraProvider::Instantiate();
				auto views = cameraProvider.Views;

				for (auto pView : views)
				{
					cameraProvider.pCurrent = pView;
					for (auto& render : receivers)
					{
						render->Render();
					}
				}

			}
		};
	}
}
