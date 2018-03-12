#pragma once

#include <crtdbg.h>
#include <windows.h>
#include <tchar.h>
#include<stdio.h>
#include<mutex>

#pragma region property

/// <summary>
/// �ǂݏ����\�ȃv���p�e�B�B�l�n��
/// </summary>
#define PROPERTY(var,propertyName,type) 	\
		void Seter_##propertyName(type _val) { var = _val;} \
		type Geter_##propertyName() const {return var;} \
		__declspec(property(get = Geter_##propertyName, put = Seter_##propertyName)) type propertyName

/// <summary>
/// �ǂݏ����\�ȃv���p�e�B�B�Q�Ɠn��
/// </summary>
#define PROPERTY_REF(var,propertyName,type) 	\
		void Seter_##propertyName(const type& _val){ var = _val;} \
		type& Geter_##propertyName() {return var;} \
		__declspec(property(get = Geter_##propertyName, put =Seter_##propertyName)) type propertyName

/// <summary>
/// �ǂݏ����\�ȃv���p�e�B�B�E�Ӓl�n��
/// </summary>
#define PROPERTY_MOVE(var,propertyName,type) 	\
		void Seter_##propertyName(const type& _val){ var = std::move(_val);} \
		type&& Geter_##propertyName() {return std::move(var);} \
		__declspec(property(get = Geter_##propertyName, put =Seter_##propertyName)) type propertyName

/// <summary>
/// �ǂݐ�p�v���p�e�B�B�l�n��
/// </summary>
#define PROPERTY_R_ONLY(var,propertyName,type) 	\
		type Geter_##propertyName() const{return var;} \
		__declspec(property(get = Geter_##propertyName)) type propertyName

/// <summary>
/// �ǂݐ�p�v���p�e�B�B�Q�ƕԂ�
/// </summary>
#define PROPERTY_REF_R_ONLY(var,propertyName,type) 	\
		type& Geter_##propertyName() {return var;} \
		__declspec(property(get = Geter_##propertyName)) type propertyName

/// <summary>
/// �ǂݐ�p�v���p�e�B�B�R���X�g�Q�ƕԂ�
/// </summary>
#define PROPERTY_CR_R_ONLY(var,propertyName,type) 	\
		const type& Geter_##propertyName() const {return var;} \
		__declspec(property(get = Geter_##propertyName)) type propertyName

/// <summary>
/// ������p�v���p�e�B�B�l�n��
/// </summary>
#define PROPERTY_W_ONLY(var,propertyName,type) 	\
		void Seter_##propertyName(type _val){ var = _val;} \
		__declspec(property(put = Seter_##propertyName)) type propertyName

/// <summary>
/// ������p�v���p�e�B�B�R���X�g�Q��
/// </summary>
#define PROPERTY_REF_W_ONLY(var,propertyName,type) 	\
		void Seter_##propertyName(type& _val){ var = _val;} \
		__declspec(property(put = Seter_##propertyName)) type propertyName

/// <summary>
/// ������p�v���p�e�B�B�R���X�g�Q��
/// </summary>
#define PROPERTY_CR_W_ONLY(var,propertyName,type) 	\
		void Seter_##propertyName(const type& _val){ var = _val;} \
		__declspec(property(put = Seter_##propertyName)) type propertyName

/// <summary>
/// �ǂݏ����\�ȃv���p�e�B�B�l�n��
/// �����t�b�N�ł��邪����p�̖����悤�ɗ���.
/// </summary>
#define PROPERTY_W_HOOKABLE(var,propertyName,type,hook) 	\
		void Seter_##propertyName(type _val) { var = _val;hook();} \
		type Geter_##propertyName() const {return var;} \
		__declspec(property(get = Geter_##propertyName, put = Seter_##propertyName)) type propertyName

/// <summary>
/// �ǂݏ����\�ȃv���p�e�B.�Q�Ɠn��
/// �����t�b�N�ł��邪����p�̖����悤�ɗ���.
/// </summary>
#define PROPERTY_REF_W_HOOKABLE(var,propertyName,type,hook) 	\
		void Seter_##propertyName(const type& _val) { var = _val;hook();} \
		type& Geter_##propertyName() {return var;} \
		__declspec(property(get = Geter_##propertyName, put = Seter_##propertyName)) type propertyName

#pragma endregion

#pragma region stringMacro

/// <summary>
/// �f�B�X�|�C���^����`���擾
/// </summary>
#define ___GET_THIS_NAME(pthis)					\
		 std::string(typeid(*pthis).name())

/// <summary>
/// �^��string�ɕϊ�
/// </summary>
#define ___TYPE_TO_STRING(type)					\
		std::string(typeid(type).name())

/// <summary>
/// �R�[�h�𕶎���
/// </summary>
#define ___CODE_TO_STRING(_code)				\
		std::string(#_code)

#pragma endregion

#pragma region assert

/// <summary>
/// ���d�錾�}�N�� �x������
/// </summary>
#pragma warning ( disable : 4005 )

/// <summary>
/// �x��Lv3 �x������
/// </summary>
#pragma warning ( disable : 4996 )

/// <summary>
/// expr�̏�������������Ȃ�������A
/// ��2�����ɓn�������b�Z�[�W���f�o�b�O���|�[�g�E�B���h�E�ɕ\�L����
/// </summary>
#ifdef _DEBUG
#define ASSERT_EXPR(expr, msg) \
	(void) ((!!(expr)) || \
	(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg)) || \
	(_CrtDbgBreak(), 0))
#else
#    define _ASSERT_EXPR(expr, msg) {}// �����
#endif


#ifdef _DEBUG
#ifndef _ASSERT
#define _ASSERT(expr) _ASSERT_EXPR((expr), NULL)
#endif
#else
#    define _ASSERT(expr) {}// �����
#endif

#ifdef _DEBUG
#ifndef _ASSERTE
#define _ASSERTE(expr) _ASSERT_EXPR((expr), _CRT_WIDE(#expr))
#endif
#else
#    define _ASSERTE(expr) {}// �����
#endif

#pragma endregion

/// <summary>
/// �^�C�g���o�[�ɕ����Z�b�g
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
/// ���������[�N���o
/// </summary>
#ifdef _DEBUG
#define ON_SEARCH_LEAK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) 
#else
#define  ON_SEARCH_LEAK
#endif // !_DEBUG

/// <summary>
/// �������m�ێ��u���C�N
/// </summary>
#ifdef _DEBUG
#define ON_BREAK_ALLOC(no) _CrtSetBreakAlloc(no)
#else
#define  ON_BREAK_ALLOC
#endif

/// <summary>
/// ���d�J���h�~
/// </summary>
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(ptr)			if(ptr){ ptr->Release(); ptr=nullptr; }
#endif

/// <summary>
/// ���d�J���h�~
/// </summary>
#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr)			if(ptr){ delete ptr; ptr=nullptr; }
#endif

/// <summary>
/// ���d�J���h�~
/// </summary>
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(ptr)		if(ptr){ delete[] ptr; ptr=nullptr; }
#endif

#pragma endregion

//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------