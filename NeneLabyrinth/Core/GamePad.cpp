#include "GamePad.h"
#include<math.h>

#pragma comment (lib, "xinput.lib")
namespace NeneLabyrinth
{
	namespace Core
	{
		GamePad::GamePad(float _thresholdOfOn, int _index) :
			thresholdOfOn(_thresholdOfOn),
			padIndex(_index)
		{
			if (_index > 3)
			{
				___THROW_EXCEPTION(Utility::Exception, "API上限を超える使用数要求");
				return;
			}
			inputState = {};
			inputPreviousState = {};
		}

		GamePad::~GamePad()
		{
			EndVibration();
		}

		void GamePad::UpdateInputState()
		{
			inputPreviousState = inputState;
			XInputGetState(padIndex, &inputState);
		}

		bool GamePad::IsDown(Code _code)
		{
			return 0b01 && GetBitSignature(_code);
		}

		bool GamePad::IsUp(Code _code)
		{
			return 0b10 && GetBitSignature(_code);
		}

		bool GamePad::IsInput(Code _code)
		{
			return GetState(inputState, _code);
		}

		float GamePad::FetchRawValue(Code _code)
		{
			return GetAbsoluteRaw(inputState, _code);
		}

		void GamePad::BeginVibration(signed lValue, signed rValue)
		{
			XINPUT_VIBRATION vib{ 10000 ,10000 };
			XInputSetState(padIndex, &vib);
			XInputEnable(true);
		}

		void GamePad::EndVibration()
		{
			XInputEnable(false);
		}

		float GamePad::GetAbsoluteRaw(XINPUT_STATE _state, Code _code)
		{
			float value = 0;
			switch (_code)
			{
			case NeneLabyrinth::Core::GamePad::LeftTrigger:
				value = _state.Gamepad.bLeftTrigger / 255.0f;
				break;
			case NeneLabyrinth::Core::GamePad::RightTrigger:
				value = _state.Gamepad.bRightTrigger / 255.0f;
				break;
			case NeneLabyrinth::Core::GamePad::LeftStickLeft: //1フレームで同時に押せるなら押して見なさいｗ
			case NeneLabyrinth::Core::GamePad::LeftStickRight:
				value = _state.Gamepad.sThumbLX / 32767.0f;
				break;
			case NeneLabyrinth::Core::GamePad::LeftStickUp:
			case NeneLabyrinth::Core::GamePad::LeftStickDown:
				value = _state.Gamepad.sThumbLY / 32767.0f;
				break;
			case NeneLabyrinth::Core::GamePad::RightStickLeft:
			case NeneLabyrinth::Core::GamePad::RightStickRight:
				value = _state.Gamepad.sThumbRX / 32767.0f;
				break;
			case NeneLabyrinth::Core::GamePad::RightStickUp:
			case NeneLabyrinth::Core::GamePad::RightStickDown:
				value = _state.Gamepad.sThumbRY / 32767.0f;
				break;
			default:
				break;
			}
			return fabs(value);
		}

		bool GamePad::GetState(XINPUT_STATE _state, Code _code)
		{
			if (_code <= Code::Y)
			{
				return _state.Gamepad.wButtons && _code;
			}
			return thresholdOfOn < GetAbsoluteRaw(_state, _code);
		}

		char GamePad::GetBitSignature(Code _code)
		{
			return (((char)GetState(inputPreviousState, _code)) << 1) + (char)GetState(inputState, _code);
		}


	}
}