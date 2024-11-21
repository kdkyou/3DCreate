#include "GimmickScene.h"

#include"../../GameObject/Enemy/Megaro/Megaro.h"
#include"../../GameObject/Gimmick/Relief/Relief.h"
#include"../../GameObject/Gimmick/Nidle/Nidle.h"
#include"../../GameObject/Gimmick/FallPillar/FallPillar.h"
#include"../../GameObject/Gimmick/RotateBridge/RotateBridge.h"
#include"../../GameObject/Gimmick/Wall/Wall.h"
#include"../../GameObject/Gimmick/BreakWall/BreakWall.h"
#include"../../GameObject/Gimmick/ArrowBox/ArrowBox.h"
#include"../../GameObject/Gimmick/PitFall/PitFall.h"
#include"../../GameObject/Gimmick/SlideDoor/SlideDoor.h"
#include"../../GameObject/Gimmick/Pazzle/Light/Laser/Laser.h"
#include"../../GameObject/Gimmick/Pazzle/Light/Turret/Turret.h"
#include"../../GameObject/Gimmick/Pazzle/Light/LaserSystem/LaserSystem.h"


#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"

#include"json.hpp"


void GimmickScene::Init()
{
	nlohmann::json j;
	std::ifstream inFile("Asset/Data/GameObject/gimmick.json");
	inFile >> j;

	std::shared_ptr<KdModelData> _model;
	std::shared_ptr<KdModelWork> _Model;
	for (auto& item : j)
	{

		Math::Vector3 rot = { item["rot"]["X"],item["rot"]["Y"],item["rot"]["Z"] };

		_model = AssetRepository::Instance().GetModel(item["name"]);
		Math::Matrix transMat = Math::Matrix::CreateTranslation({ item["pos"]["X"],item["pos"]["Y"] ,item["pos"]["Z"] });
		Math::Matrix scaleMat = Math::Matrix::CreateScale({ item["scale"]["X"],item["scale"]["Y"] ,item["scale"]["Z"] });
		Math::Matrix rotMat = Math::Matrix::CreateFromYawPitchRoll(rot);
		Math::Matrix _mat = scaleMat * rotMat * transMat;

		if (item["name"] == "Nidle")
		{
			std::shared_ptr<Nidle> _nidle = std::make_shared<Nidle>();
			_Model = std::make_shared<KdModelWork>();
			_Model->SetModelData("Asset/Models/Terrains/Gimmick/Nidle/Nidle.gltf");
			_nidle->SetMatrix(_mat);
			_nidle->SetModel(_Model);
			_nidle->SetRot(rot);
			AddObject(_nidle);
		}
		else if (item["name"] == "Relief")
		{
			std::shared_ptr<Relief> relief = std::make_shared<Relief>();
			relief->Init();
			relief->SetMatrix(_mat);
			relief->SetRot(rot);
			static int num = 0;
			relief->SetNum(num);
			num++;
			AddObject(relief);
		}
		else if (item["name"] == "Fall")
		{
			std::shared_ptr<KdModelWork> _Model;
			std::shared_ptr<FallPillar> _fall = std::make_shared<FallPillar>();
			_Model = std::make_shared<KdModelWork>();
			_Model->SetModelData("Asset/Models/Terrains/Gimmick/FallPillar/Pillar.gltf");
			_fall->Init();
			_fall->SetMatrix(_mat);
			_fall->SetRot(rot);
			_fall->SetModel(_Model);
			AddObject(_fall);
		}
		else if (item["name"] == "Rotate")
		{
			std::shared_ptr<KdModelWork> _Model;
			std::shared_ptr<RotateBridge> _bridge = std::make_shared<RotateBridge>();
			_Model = std::make_shared<KdModelWork>();
			_Model->SetModelData("Asset/Models/Terrains/Gimmick/RotateBridge/RotateBridge.gltf");
			std::shared_ptr<KdModelData> _model;
			_model = std::make_shared<KdModelData>();
			_model->Load("Asset/Models/Terrains/Gimmick/RotateBridge/BridgeUp.gltf");
			_bridge->SetMatrix(_mat);
			_bridge->SetRot(rot);
			_bridge->SetModel(_Model);
			_bridge->SetModel(_model);

			AddObject(_bridge);
		}
		else if (item["name"] == "BreakWall")
		{
			std::shared_ptr<BreakWall> _break = std::make_shared<BreakWall>();
			std::shared_ptr<KdModelWork> _Model;
			_Model = std::make_shared<KdModelWork>();
			_Model->SetModelData("Asset/Models/Terrains/Gimmick/BreakWall/BreakWall.gltf");
			_break->Init();
			_break->SetMatrix(_mat);
			_break->SetRot(rot);
			_break->SetModel(_Model);
			AddObject(_break);
		}
		else if (item["name"] == "Wall")
		{
			std::shared_ptr<KdModelWork> _Model;
			std::shared_ptr<Wall> _wall = std::make_shared<Wall>();
			_Model = std::make_shared<KdModelWork>();
			_Model->SetModelData("Asset/Models/Terrains/Gimmick/Wall/Wall.gltf");
			_wall->Init();
			_wall->SetMatrix(_mat);
			_wall->SetRot(rot);
			_wall->SetModel(_Model);
			AddObject(_wall);
		}
		else if (item["name"] == "Arrow")
		{
			std::shared_ptr<ArrowBox> _arrow = std::make_shared<ArrowBox>();
			std::shared_ptr<KdModelData> _model;
			_model = std::make_shared<KdModelData>();
			_model->Load("Asset/Models/Terrains/Gimmick/ArrowBox/ArrowBox.gltf");
			_arrow->Init();
			_arrow->SetMatrix(_mat);
			_arrow->SetRot(rot);
			_arrow->SetModel(_model);
			AddObject(_arrow);
		}
		else if (item["name"] == "Pit")
		{
			std::shared_ptr<KdModelWork> _Model;
			std::shared_ptr<PitFall> _pit = std::make_shared<PitFall>();
			_Model = std::make_shared<KdModelWork>();
			_Model->SetModelData("Asset/Models/Terrains/Gimmick/PitFall/PitFall.gltf");
			_pit->Init();
			_pit->SetMatrix(_mat);
			_pit->SetRot(rot);
			_pit->SetModel(_Model);
			AddObject(_pit);
		}
		else if (item["name"] == "Slide")
		{
			std::shared_ptr<SlideDoor>_slide = std::make_shared<SlideDoor>();
			std::shared_ptr<KdModelData> _model = std::make_shared<KdModelData>();
			_slide->SetMatrix(_mat);
			_slide->Init();
			_slide->SetRot(rot);
			AddObject(_slide);
		}

	}

	std::shared_ptr<LaserSystem> lsystem = std::make_shared<LaserSystem>();
	lsystem->SetParam("Asset/Data/GameObject/Pazzle/Laser/Stage1.json");
	AddObject(lsystem);

	/*std::shared_ptr<Laser> laser = std::make_shared<Laser>();
	Math::Matrix matt = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0)) *
		Math::Matrix::CreateTranslation({ 16.0f,0.0f,0.0f });
	laser->SetMatrix(matt);
	laser->Init();
	AddObject(laser);

	std::shared_ptr<Turret> turret = std::make_shared<Turret>();
	matt = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90)) *
		Math::Matrix::CreateTranslation({ 16.0f,0.0f,2.0f });
	turret->SetMatrix(matt);
	turret->Init();
	AddObject(turret);

	turret = std::make_shared<Turret>();
	matt = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180)) *
		Math::Matrix::CreateTranslation({ 20.0f,0.0f,2.0f });
	turret->SetMatrix(matt);
	turret->Init();
	AddObject(turret);

	turret = std::make_shared<Turret>();
	matt = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(270)) *
		Math::Matrix::CreateTranslation({ 20.0f,0.0f,0.0f });
	turret->SetMatrix(matt);
	turret->Init();
	AddObject(turret);*/


	m_count = 0;
	
}

void GimmickScene::Event()
{
}

