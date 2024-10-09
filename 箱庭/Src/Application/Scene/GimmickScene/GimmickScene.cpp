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

#include"../../Scene/SceneManager.h"

#include"../../AssetRepository/AssetRepository.h"

#include"json.hpp"


void GimmickScene::Init()
{
	nlohmann::json j;
	std::ifstream inFile("Asset/Data/GameObject/gimmick.json");
	inFile >> j;

	std::shared_ptr<Relief> _relief;
	std::shared_ptr<Nidle> _nidle;
	std::shared_ptr<Megaro> _megaro;
	std::shared_ptr<KdModelData>_model;
	for (auto& item : j)
	{
		_model = std::make_shared<KdModelData>();

		Math::Vector3 pos = { item["posX"],item["posY"] ,item["posZ"] };

		Math::Vector3 rot = { item["rotX"],item["rotY"],item["rotZ"] };
		Math::Matrix transMat = Math::Matrix::CreateTranslation(pos);
		Math::Matrix scaleMat = Math::Matrix::CreateScale({ item["scaleX"],item["scaleY"] ,item["scaleZ"] });
		Math::Matrix rotMat = Math::Matrix::CreateFromYawPitchRoll(rot);

		Math::Matrix _mat = scaleMat * rotMat * transMat;

			
		if (item["name"] == "Nidle")
		{
			_nidle = std::make_shared<Nidle>();
			std::shared_ptr<KdModelWork> _Model = std::make_shared<KdModelWork>();
			_Model->SetModelData("Asset/Models/Terrains/Gimmick/Nidle/Nidle.gltf");
			_nidle->SetMatrix(_mat);
			_nidle->SetModel(_Model);
			AddObject(_nidle);
		}
		else if (item["name"] == "Relief")
		{
			_relief = std::make_shared<Relief>();
			_model = AssetRepository::Instance().GetModel(item["name"]);
			_relief->SetMatrix(_mat);
			_relief->SetModel(_model);
			AddObject(_relief);
		}
		
	}
	Math::Matrix _mat = Math::Matrix::CreateTranslation({ 30.f,5.f,0.f });
	std::shared_ptr<KdModelWork> _Model ;

	std::shared_ptr<FallPillar> _fall = std::make_shared<FallPillar>();
	_fall->SetMatrix(_mat);
	_Model = std::make_shared<KdModelWork>();
	_Model->SetModelData("Asset/Models/Terrains/Gimmick/FallPillar/Pillar.gltf");
	_fall->Init();
	_fall->SetModel(_Model);
	AddObject(_fall);

	/*std::shared_ptr<RotateBridge> _bridge = std::make_shared<RotateBridge>();
	_Model = std::make_shared<KdModelWork>();
	_Model->SetModelData("Asset/Models/Terrains/Gimmick/RotateBridge/RotateBridge.gltf");
	_model = std::make_shared<KdModelData>();
	_model->Load("Asset/Models/Terrains/Gimmick/RotateBridge/BridgeUp.gltf");
	 _mat = Math::Matrix::CreateTranslation({ 10,2,0 });
	 _bridge->SetMatrix(_mat);
	 _bridge->SetModel(_Model);
	 _bridge->SetModel(_model);
	AddObject(_bridge);*/

	std::shared_ptr<BreakWall> _break = std::make_shared<BreakWall>();
	_Model = std::make_shared<KdModelWork>();
	_Model->SetModelData("Asset/Models/Terrains/Gimmick/BreakWall/BreakWall.gltf");
	_mat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90)) * Math::Matrix::CreateTranslation({ 40.f,5.f,2.f });
	_break->SetMatrix(_mat);
	_break->Init();
	_break->SetModel(_Model);
	AddObject(_break);


	/*std::shared_ptr<Wall> _wall = std::make_shared<Wall>();
	_Model = std::make_shared<KdModelWork>();
	_Model->SetModelData("Asset/Models/Terrains/Gimmick/Wall/Wall.gltf");
	_mat=Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90))* Math::Matrix::CreateTranslation({ -10.f,0.f,0.f });
	_wall->Init();
	_wall->SetMatrix(_mat);
	_wall->SetModel(_Model);
	AddObject(_wall);*/

	std::shared_ptr<ArrowBox> _arrow = std::make_shared<ArrowBox>();
	_model = std::make_shared<KdModelData>();
	_model->Load("Asset/Models/Terrains/Gimmick/ArrowBox/ArrowBox.gltf");
	_mat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0)) * Math::Matrix::CreateTranslation({ -5.f,0.f,0.f });
	_arrow->SetMatrix(_mat);
	_arrow->Init();
	_arrow->SetModel(_model);
	AddObject(_arrow);

	std::shared_ptr<PitFall> _pit = std::make_shared<PitFall>();
	_Model = std::make_shared<KdModelWork>();
	_Model->SetModelData("Asset/Models/Terrains/Gimmick/PitFall/PitFall.gltf");
	_mat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0)) * Math::Matrix::CreateTranslation({ -13.f,0.f,0.f });
	_pit->SetMatrix(_mat);
	_pit->Init();
	_pit->SetModel(_Model);
	AddObject(_pit);

	std::shared_ptr<SlideDoor>_slide = std::make_shared<SlideDoor>();
	_model = std::make_shared<KdModelData>();
	_mat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(0)) * Math::Matrix::CreateTranslation({ 20.f,5.f,0.f });
	_slide->SetMatrix(_mat);
	_slide->Init();
	AddObject(_slide);



	m_count = 0;
	time = 0;
}

void GimmickScene::Event()
{

	if (GetAsyncKeyState('P'))m_count = 3;
	if (m_count >= RELIEFCOUNT)
	{
		time++;
		if (time > 180)
		{
			SceneManager::Instance().SetNextScene(SceneManager::SceneType::Title);
			KdAudioManager::Instance().StopAllSound();
		}
	}
}

