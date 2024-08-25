#include "FreeCamera.h"

void FreeCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, -5.0f);

	m_pos = {};

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//被写界深度	  
	m_spCamera->SetFocus(
		m_pos.z,		// ピントの位置
		m_pos.z - 8,		//手前のぼかし距離
		m_pos.z + 8);		//奥のぼかし距離

	////フォグ(霧)
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(true, true);
	////距離フォグ														↓色　　　↓密度
	KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 0.1f,0.1f,0.2f }, 0.1f);
	////高さフォグ														↓色	上の上限　下の上限　カメラとの距離
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0.1,0.1,0.2 }, m_pos.y+2, m_pos.y-5, 2);

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
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = m_mRotation*_trans;
}

void FreeCamera::PostUpdate()
{
	
}
