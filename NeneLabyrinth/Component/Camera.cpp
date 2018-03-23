#include "Camera.h"
#include "../Provider/CameraProvider.h"
#include "../Component/IBehavior.h"
#include "../Component/Behavior.h"
#include "../Component/Transform.h"
namespace NeneLabyrinth
{
	namespace Component
	{
		Camera::Camera(Behavior & _owner) :
			IBehavior(_owner, typeid(Camera))
		{
			CameraProvider::Instantiate().Register(this);
		}
		Camera::~Camera()
		{
			CameraProvider::Instantiate().UnRegister(this);
		}
		void Camera::Update()
		{
		}
		void Camera::ViewUpdata()
		{
			auto& transform = Owner.GetComponent<Transform>();
			auto position = transform->Position;

			auto lookAt = position + transform->Forward;//注視位置
			auto up = transform->Up;//注視位置

			D3DXMatrixLookAtLH(&View, &position, &lookAt, &up);

			// プロジェクショントランスフォーム
			D3DXMatrixPerspectiveFovLH(&Proj, D3DX_PI / 4, (FLOAT)640 / (FLOAT)480, 0.1f, 100.0f);
		}
		D3DXMATRIX Camera::GetVPMatrix()
		{
			return View*Proj;
		}
	}
}