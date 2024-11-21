#pragma once

class Fade:public KdGameObject
{
public:

	Fade() {}
	~Fade()override;

	enum FadeType
	{
		FadeIn,//割り込み可
		FadeOut,//割り込み可
		FadeInLeftRight,
		FadeOutLeftRight,
		FadeInRightLeft,
		FadeOutRightLeft,
	};
	FadeType nowFadeType;


	void Init()			override;
	void DrawSprite()	override;
	void Update()		override;

	void SetFade(FadeType type, int time, const bool OutorIn = true);

	bool GetFillDisplay()const;
	bool GetCompleteFade()const;

private:

	void Release();

	KdTexture m_tex;

	float m_alpha;

	int m_IncDec;

	bool completeFade;
	int fadeFrame;
	int fadeTime;

	//画面を真っ暗にするか Fadein終了時にtrue,fadeout開始時にfalseになる
	bool fillDisplay;

	bool isLaunch;

};