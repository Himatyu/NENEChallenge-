#pragma once

#include"IProvider.h"
#include"Singleton.h"

#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

namespace NeneLabyrinth
{
	namespace Component
	{
		__interface IView
		{
			D3DXMATRIX GetVPMatrix();
			void ViewUpdata();
		};

		class CameraProvider :
			public Utility::IProvider<IView>,
			public Utility::Singleton<CameraProvider>
		{
			IView* pCurrentView = nullptr;
		public:
			PROPERTY_REF(receivers, Views, std::vector<IView*>);
			PROPERTY(pCurrentView, pCurrent, IView*);

			void Dispatch() override
			{
				if (pCurrentView == nullptr && receivers.size() != 0)
				{
					pCurrentView = receivers[0];
				}
				for (auto& camera : receivers)
				{
					camera->ViewUpdata();
				}
			}

		};
	}
}