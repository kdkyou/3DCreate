#include "FPSCamera.h"

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(0.0f, 0.5f, 0.0f);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	//被写界深度	  
	m_spCamera->SetFocus(
		m_mWorld.Translation().z,		// ピントの位置
		m_mWorld.Translation().z - 5,		//手前のぼかし距離
		m_mWorld.Translation().z + 5);		//奥のぼかし距離

	////フォグ(霧)
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
}

void FPSCamera::PostUpdate()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat	= Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget	= m_wpTarget.lock();	
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転
	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();
	m_mWorld	= m_mRotation * m_mLocalPos * _targetMat;

	////距離フォグ														↓色　　　↓密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 0.1f,0.1f,0.2f }, 0.05f);
	////高さフォグ														↓色	上の上限　下の上限　カメラとの距離
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 0.1,0.1,0.2 }, m_mWorld.Translation().y + 4, m_mWorld.Translation().y - 4, 2);

}
