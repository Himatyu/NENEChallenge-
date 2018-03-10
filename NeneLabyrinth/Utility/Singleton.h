#pragma once
#include<vector>
namespace NeneLabyrinth
{
	namespace Utility
	{
		/// <summary>
		/// シングルトン開放クラス
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
		/// シングルトンテンプレート
		/// </summary>
		template <class Type>
		class Singleton
		{
			static std::once_flag	initFlag;
			static Type*			pInstance;

		public:
			/// <summary>
			/// 実体を生成.
			/// </summary>
			/// <returns>実体参照</returns>
			static Type& Instantiate();

		private:
			static void Create();
			static void Destroy();
		};
#include"singleton.inl"
	}
}