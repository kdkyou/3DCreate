﻿#include "LaserSystem.h"

#include"../LaserObject.h"
#include"../Laser/Laser.h"
#include"../Turret/Turret.h"
#include"../Qube/Qube.h"

#include"../../../../../Scene/SceneManager.h"

#include"json.hpp"

bool LaserSystem::SetParam(const std::string& fileName)
{
	nlohmann::json j;
	std::string name = fileName;
	std::ifstream inFile(name);
	inFile >> j;

	//jsonファイル内のデータをオブジェクトに反映していく
	for(const auto&item :j){

		Math::Matrix transMat = Math::Matrix::CreateTranslation({ item["pos"]["X"],item["pos"]["Y"] ,item["pos"]["Z"] });
		Math::Matrix scaleMat = Math::Matrix::CreateScale({ item["scale"]["X"],item["scale"]["Y"] ,item["scale"]["Z"] });
		Math::Matrix rotMat = Math::Matrix::CreateFromYawPitchRoll({item["rot"]["X"],item["rot"]["Y"],item["rot"]["Z"] });
		Math::Matrix mat = scaleMat * rotMat * transMat;

		if (item["LTB"]=="L") {
			std::shared_ptr<Laser>laser = std::make_shared<Laser>();
			laser->SetAngles(DirectX::XMConvertToDegrees(item["rot"]["Y"]),0);
			laser->SetMatrix(mat);
			laser->Init();
			SceneManager::Instance().AddGimmick(laser);
			m_objects.push_back(laser);
		}
		else if(item["LTB"]=="T")
		{
			std::shared_ptr<Turret> turret = std::make_shared<Turret>();
			turret->SetMatrix(mat);
			turret->Init();
			SceneManager::Instance().AddGimmick(turret);
			m_objects.push_back(turret);
		}
		else
		{
			std::shared_ptr<Qube> qube = std::make_shared<Qube>();
			qube->SetMatrix(mat);
			qube->Init();
			SceneManager::Instance().AddGimmick(qube);
			m_objects.push_back(qube);
		}
	}

	return false;
}

void LaserSystem::CheckAlignment()
{
	bool allAligned = true;

	for (const auto& obj : m_objects) {
		std::shared_ptr<LaserObject> lasr = obj.lock();
		if (!lasr)continue;
		if (lasr->IsAligned()) {
			allAligned = false;
			break;
		}
	}

	//全てのオブジェクトが目標角度に一致していればコールバックを呼び出す
	if (allAligned && m_callback) {
		m_callback;
	}
}

//void LaserSystem::UpdateObject(size_t index, float newAngle)
//{
//	if (index < m_objects.size()) {
//		std::shared_ptr<LaserObject> lasr = m_objects[index].lock();
//		if (!lasr)return;;
//		lasr->SetAngles(newAngle,);
//		CheckAlignment();
//	}
//}
void LaserSystem::BreakCallBack()
{
	for (const auto& obj : m_objects){
		std::shared_ptr<LaserObject> lasr = obj.lock();
		if (!lasr)continue;
		if (lasr->IsExpired()) {
			m_callback;
		}
	}
}

