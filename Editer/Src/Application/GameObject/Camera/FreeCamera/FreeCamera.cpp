#include "FreeCamera.h"

void FreeCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -5.0f);

	m_pos = {};

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void FreeCamera::Update()
{

	Math::Vector3 _moveVec = Math::Vector3::Zero;
	if (GetAsyncKeyState(VK_UP)) { _moveVec.y = 1.0f; }
	if (GetAsyncKeyState(VK_DOWN)) { _moveVec.y = -1.0f; }
	if (GetAsyncKeyState(VK_LEFT)) { _moveVec.x = -1.0f; }
	if (GetAsyncKeyState(VK_RIGHT)) { _moveVec.x = 1.0f; }
	if (GetAsyncKeyState('O')) { _moveVec.z = 1.0f; }
	if (GetAsyncKeyState('L')) { _moveVec.z = -1.0f; }

	m_pos += _moveVec;

	// カメラの回転
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		UpdateRotateByMouse();
	}
	m_mRotation = GetRotationMatrix();
	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_mRotation*_trans;
}

void FreeCamera::PostUpdate()
{
	
}
