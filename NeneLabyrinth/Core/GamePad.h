#pragma once
#include <windows.h>
#include<Xinput.h>
#pragma comment (lib, "xinput.lib")

namespace NeneLabyrinth
{
	namespace Core
	{
		//デッドゾーン未対応
		class GamePad
		{
			XINPUT_STATE inputState;
			XINPUT_STATE inputPreviousState;
			float thresholdOfOn;
			int padIndex;
		public:
			enum Code
			{
				DpadUp = 0x0001,
				DpadDown = 0x0002,
				DpadLeft = 0x0004,
				DpadRight = 0x0008,
				Start = 0x0010,
				Back = 0x0020,
				LeftThumb = 0x0040,
				RightThumb = 0x0080,
				LeftShoulder = 0x0100,
				RightShoulder = 0x0200,
				A = 0x1000,
				B = 0x2000,
				X = 0x4000,
				Y = 0x8000,
				LeftTrigger,
				RightTrigger,
				LeftStickLeft,
				LeftStickRight,
				LeftStickUp,
				LeftStickDown,
				RightStickLeft,
				RightStickRight,
				RightStickUp,
				RightStickDown,
			};

			GamePad(float _thresholdOfOn = 0.8f, int _index = 0);
			~GamePad();

			void UpdateInputState();

			bool IsDown(Code);
			bool IsUp(Code);
			bool IsInput(Code);

			float FetchRawValue(Code);

			void BeginVibration(signed lValue, signed rValue);
			void EndVibration();
		private:
			float GetAbsoluteRaw(XINPUT_STATE, Code);
			bool GetState(XINPUT_STATE, Code);
			char GetBitSignature(Code);
		};


	}
}
