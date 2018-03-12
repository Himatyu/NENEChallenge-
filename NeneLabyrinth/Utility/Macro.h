#pragma once

#include <crtdbg.h>
#include <windows.h>
#include <tchar.h>
#include<stdio.h>
#include<mutex>

#pragma region property

/// <summary>
/// 読み書き可能なプロパティ。値渡し
/// </summary>
#define PROPERTY(var,propertyName,type) 	\
		void Seter_##propertyName(type _val) { var = _val;} \
		type Geter_##propertyName() const {return var;} \
		__declspec(property(get = Geter_##propertyName, put = Seter_##propertyName)) type propertyName

/// <summary>
/// 読み書き可能なプロパティ。参照渡し
/// </summary>
#define PROPERTY_REF(var,propertyName,type) 	\
		void Seter_##propertyName(const type& _val){ var = _val;} \
		type& Geter_##propertyName() {return var;} \
		__declspec(property(get = Geter_##propertyName, put =Seter_##propertyName)) type propertyName

/// <summary>
/// 読み書き可能なプロパティ。右辺値渡し
/// </summary>
#define PROPERTY_MOVE(var,propertyName,type) 	\
		void Seter_##propertyName(const type& _val){ var = std::move(_val);} \
		type&& Geter_##propertyName() {return std::move(var);} \
		__declspec(property(get = Geter_##propertyName, put =Seter_##propertyName)) type propertyName

/// <summary>
/// 読み専用プロパティ。値渡し
/// </summary>
#define PROPERTY_R_ONLY(var,propertyName,type) 	\
		type Geter_##propertyName() const{return var;} \
		__declspec(property(get = Geter_##propertyName)) type propertyName

/// <summary>
/// 読み専用プロパティ。参照返し
/// </summary>
#define PROPERTY_REF_R_ONLY(var,propertyName,type) 	\
		type& Geter_##propertyName() {return var;} \
		__declspec(property(get = Geter_##propertyName)) type propertyName

/// <summary>
/// 読み専用プロパティ。コンスト参照返し
/// </summary>
#define PROPERTY_CR_R_ONLY(var,propertyName,type) 	\
		const type& Geter_##propertyName() const {return var;} \
		__declspec(property(get = Geter_##propertyName)) type propertyName

/// <summary>
/// 書き専用プロパティ。値渡し
/// </summary>
#define PROPERTY_W_ONLY(var,propertyName,type) 	\
		void Seter_##propertyName(type _val){ var = _val;} \
		__declspec(property(put = Seter_##propertyName)) type propertyName

/// <summary>
/// 書き専用プロパティ。コンスト参照
/// </summary>
#define PROPERTY_REF_W_ONLY(var,propertyName,type) 	\
		void Seter_##propertyName(type& _val){ var = _val;} \
		__declspec(property(put = Seter_##propertyName)) type propertyName

/// <summary>
/// 書き専用プロパティ。コンスト参照
/// </summary>
#define PROPERTY_CR_W_ONLY(var,propertyName,type) 	\
		void Seter_##propertyName(const type& _val){ var = _val;} \
		__declspec(property(put = Seter_##propertyName)) type propertyName

/// <summary>
/// 読み書き可能なプロパティ。値渡し
/// 書きフックできるが副作用の無いように留意.
/// </summary>
#define PROPERTY_W_HOOKABLE(var,propertyName,type,hook) 	\
		void Seter_##propertyName(type _val) { var = _val;hook();} \
		type Geter_##propertyName() const {return var;} \
		__declspec(property(get = Geter_##propertyName, put = Seter_##propertyName)) type propertyName

/// <summary>
/// 読み書き可能なプロパティ.参照渡し
/// 書きフックできるが副作用の無いように留意.
/// </summary>
#define PROPERTY_REF_W_HOOKABLE(var,propertyName,type,hook) 	\
		void Seter_##propertyName(const type& _val) { var = _val;hook();} \
		type& Geter_##propertyName() {return var;} \
		__declspec(property(get = Geter_##propertyName, put = Seter_##propertyName)) type propertyName

#pragma endregion

#pragma region stringMacro

/// <summary>
/// ディスポインタから形名取得
/// </summary>
#define ___GET_THIS_NAME(pthis)					\
		 std::string(typeid(*pthis).name())

/// <summary>
/// 型をstringに変換
/// </summary>
#define ___TYPE_TO_STRING(type)					\
		std::string(typeid(type).name())

/// <summary>
/// コードを文字化
/// </summary>
#define ___CODE_TO_STRING(_code)				\
		std::string(#_code)

#pragma endregion

#pragma region assert

/// <summary>
/// 多重宣言マクロ 警告無視
/// </summary>
#pragma warning ( disable : 4005 )

/// <summary>
/// 警告Lv3 警告無視
/// </summary>
#pragma warning ( disable : 4996 )

/// <summary>
/// exprの条件が満たされなかったら、
/// 第2引数に渡したメッセージをデバッグレポートウィンドウに表記する
/// </summary>
#ifdef _DEBUG
#define ASSERT_EXPR(expr, msg) \
	(void) ((!!(expr)) || \
	(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg)) || \
	(_CrtDbgBreak(), 0))
#else
#    define _ASSERT_EXPR(expr, msg) {}// 空実装
#endif


#ifdef _DEBUG
#ifndef _ASSERT
#define _ASSERT(expr) _ASSERT_EXPR((expr), NULL)
#endif
#else
#    define _ASSERT(expr) {}// 空実装
#endif

#ifdef _DEBUG
#ifndef _ASSERTE
#define _ASSERTE(expr) _ASSERT_EXPR((expr), _CRT_WIDE(#expr))
#endif
#else
#    define _ASSERTE(expr) {}// 空実装
#endif

#pragma endregion

/// <summary>
/// タイトルバーに文字セット
/// </summary>
#define SET_TITLE(processName,str , ...)	\
		{								\
			TCHAR c[2048];					\
			_stprintf( c, str, __VA_ARGS__ ); \
			SetWindowText(FindWindow(processName,NULL),c); \
		}
#ifdef _DEBUG
#else
//#define SET_TITLE(str , ...) {}
#endif // !_DEBUG

#pragma region memory

/// <summary>
/// メモリリーク検出
/// </summary>
#ifdef _DEBUG
#define ON_SEARCH_LEAK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) 
#else
#define  ON_SEARCH_LEAK
#endif // !_DEBUG

/// <summary>
/// メモリ確保時ブレイク
/// </summary>
#ifdef _DEBUG
#define ON_BREAK_ALLOC(no) _CrtSetBreakAlloc(no)
#else
#define  ON_BREAK_ALLOC
#endif

/// <summary>
/// 多重開放防止
/// </summary>
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(ptr)			if(ptr){ ptr->Release(); ptr=nullptr; }
#endif

/// <summary>
/// 多重開放防止
/// </summary>
#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr)			if(ptr){ delete ptr; ptr=nullptr; }
#endif

/// <summary>
/// 多重開放防止
/// </summary>
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(ptr)		if(ptr){ delete[] ptr; ptr=nullptr; }
#endif

#pragma endregion

//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------