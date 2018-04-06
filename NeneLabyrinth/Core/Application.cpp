#include "Application.h"
#include "Singleton.h"
#include "Debug.h"
#include "../Rendering/Graphics.h"
#include "../Provider/BehaviorProvider.h"
#include "../Provider/CameraProvider.h"
#include "../Provider/CollisionProvider.h"
#include "../Provider/RenderProvider.h"
#include "TimerServer.h"

namespace NeneLabyrinth
{
	using namespace Utility;
	namespace Core
	{
		Application::~Application()
		{
			SAFE_DELETE(pWindow);
		}

		void Application::SetUp(
			HINSTANCE _hInstance,
			int _width,
			int _height,
			LPCTSTR _windowName,
			LPCTSTR _className,
			int _x, int _y)
		{
			pWindow = new Window(
				_hInstance,
				_windowName,
				_className,
				_width,
				_height,
				_x,
				_y);
			pWindow->Create();

			auto& graphics = Rendering::Graphics::Instantiate();
			graphics.Initialize(*pWindow, _width, _height);
		}

		void Application::Quit()
		{
			::PostQuitMessage(0);
		}

		void  Application::Execute()
		{
			Debug::Instantiate().ActivateDebugConsole();
			Debug::Instantiate().IsUseOutputLog = true;
			Debug::Instantiate().IsUseVSDebugOutput = true;

			while (!pWindow->IsReceiveQuitMessage())
			{
				DoUpdata();
				DoRendering();
			}
		}
		void Application::DoUpdata()
		{
			scenes->Updata();

			//Render‚æ‚èæ‚ÉView‚ğ—pˆÓ‚µ‚È‚¢‚Æ—‚¿‚é
			Component::CameraProvider::Instantiate().Dispatch();
			Component::BehaviorProvider::Instantiate().Dispatch();
			Collision::CollisionProvider::Instantiate().Dispatch();
			Utility::TimerServer::Instantiate().Update();
		}
		void Application::DoRendering()
		{
			auto& graphics = Rendering::Graphics::Instantiate();
			graphics.ClearBackBuffer();

			Rendering::RenderProvider::Instantiate().Dispatch();

			graphics.Presetnt();
		}

	}
}