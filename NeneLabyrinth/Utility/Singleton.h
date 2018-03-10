#pragma once
#include<vector>
namespace NeneLabyrinth
{
	namespace Utility
	{
		/// <summary>
		/// �V���O���g���J���N���X
		/// </summary>
		class SingletonFinalizer
		{
			using FinalizerFunc = void(*)();
			static std::vector<FinalizerFunc> m_Finalizers;
		public:
			static void AddFinalizer(FinalizerFunc _func);
			static void Finalize();
		};

		/// <summary>
		/// �V���O���g���e���v���[�g
		/// </summary>
		template <class Type>
		class Singleton
		{
			static std::once_flag	initFlag;
			static Type*			pInstance;

		public:
			/// <summary>
			/// ���̂𐶐�.
			/// </summary>
			/// <returns>���̎Q��</returns>
			static Type& Instantiate();

		private:
			static void Create();
			static void Destroy();
		};
#include"singleton.inl"
	}
}