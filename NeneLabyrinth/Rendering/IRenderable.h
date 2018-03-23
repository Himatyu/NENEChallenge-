#pragma once

namespace NeneLabyrinth
{
	namespace Rendering
	{
		__interface IRenderable //このインターフェースから破棄しない
		{
		public:
			void Render();
		};
	}
}