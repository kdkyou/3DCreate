#pragma once

class Fade:public KdGameObject
{
public:

	Fade() {}
	~Fade()override;

	enum FadeType
	{
		No,
		FadeIn,//割り込み可
		FadeOut,//割り込み可
		FadeInLeftRight,
		FadeOutLeftRight,
		FadeInRightLeft,
		FadeOutRightLeft,
	};
	FadeType nowFadeType = FadeType::No;


	void Init()			override;
	void DrawSprite()	override;
	void Update()		override;

	void SetFade(FadeType type, int time, const bool OutorIn = true);

	bool GetFillDisplay()const;
	bool GetCompleteFade()const;

private:

	void Release();

	std::shared_ptr<KdTexture> m_spTex;

	float m_alpha = 0.0f;

	int m_IncDec = 0;

	bool completeFade =false;
	int fadeFrame = 0;
	int fadeTime = 0;

	//画面を真っ暗にするか Fadein終了時にtrue,fadeout開始時にfalseになる
	bool fillDisplay = false;

	bool isLaunch =false;

};