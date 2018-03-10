#include "singleton.h"
#include"Estd.h"
namespace NeneLabyrinth
{
	namespace Utility
	{
		std::vector<SingletonFinalizer::
			FinalizerFunc>SingletonFinalizer::m_Finalizers = {};
		//-----------------------------------------------------------
		//  AddFinalizer
		//-----------------------------------------------------------
		void SingletonFinalizer::AddFinalizer(FinalizerFunc _func)
		{
			m_Finalizers.push_back(_func);
		}

		//-----------------------------------------------------------
		// Finalize
		//-----------------------------------------------------------
		void SingletonFinalizer::Finalize()
		{
			Estd::reverse(m_Finalizers);
			for (auto& it : m_Finalizers)
			{
				it();
			}
		}
	}
}