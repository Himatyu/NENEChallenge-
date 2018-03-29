#pragma once
#include"Singleton.h"
#include"Window.h"
#include"Scene.h"
#include<memory>

namespace NeneLabyrinth
{
	namespace Core
	{
		class Application :
			public Utility::Singleton<Application>
		{
			std::shared_ptr<Scene> scenes;
			Core::Window* pWindow = nullptr;

			void DoUpdata();

			void DoRendering();

		public:
			~Application();

			void SetUp(HINSTANCE	_hInstance,
				int			_width = CW_USEDEFAULT,
				int			_height = CW_USEDEFAULT,
				LPCTSTR		_windowName = "NeneLabyrinth",
				LPCTSTR		_className = "NeneLabyrinth",
				int			_x = CW_USEDEFAULT,
				int			_y = CW_USEDEFAULT);

			template <class Type, class ...Param>
			std::shared_ptr<Type> OnLoad(Param&&...);

			void Quit();

			void Execute();

		};

		template<class Type, class ...Param>
		inline std::shared_ptr<Type> Application::OnLoad(Param && ...)
		{
			auto ins = std::make_shared<Type>(std::forward<Param>(_param)...);
			ins->Initialize();
			scenes = ins;
			return ins;
		}

	}
}