#pragma once
#include<vector>
#include"Estd.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		__interface IReceivable
		{
			void Receive();
		};

		template<class T>
		class IProvider
		{
		public:
			using Pointer = T*;
		protected:
			std::vector<Pointer> receivers;
		public:

			virtual void Register(Pointer _pointer)
			{
				receivers.push_back(_pointer);
			}
			virtual void UnRegister(Pointer _pointer)
			{
				Utility::Estd::remove_if(
					receivers,
					[_pointer](Pointer _)
				{
					return _ == _pointer;
				});
			}

			virtual void Dispatch() = 0;

		};
	}
}