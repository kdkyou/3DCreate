#include "Framework/KdFramework.h"

#include "KdUtility.h"

// viewから画像情報を取得する
void KdGetTextureInfo(ID3D11View* view, D3D11_TEXTURE2D_DESC& outDesc)
{
	outDesc = {};

	ID3D11Resource* res;
	view->GetResource(&res);

	ID3D11Texture2D* tex2D;
	if (SUCCEEDED(res->QueryInterface<ID3D11Texture2D>(&tex2D)))
	{
		tex2D->GetDesc(&outDesc);
		tex2D->Release();
	}
	res->Release();
}

bool ConvertRectToUV(const KdTexture* srcTex, const Math::Rectangle& src, Math::Vector2& uvMin, Math::Vector2& uvMax)
{
	if (!srcTex) { return false; }

	uvMin.x = src.x / (float)srcTex->GetInfo().Width;
	uvMin.y = src.y / (float)srcTex->GetInfo().Height;

	uvMax.x = ( src.width  / (float)srcTex->GetInfo().Width) + uvMin.x;
	uvMax.y = ( src.height / (float)srcTex->GetInfo().Height) + uvMin.y;

	return true;
}

float EaseInOutSine(float progress)
{
	return (float)(-(std::cos(M_PI * progress) - 1.0f) / 2.0f);
}


//画像保存に利用するヘッダー
#include<gl/GL.h>
#include"stb_image_write.h"
#include"Src/Application/Scene/SceneManager.h"
void SaveScreenShot(const char* fileName, int width, int height)
{

	GLuint framebuffer;

	
	//データバッファを確保
	unsigned char* data = new unsigned char[width * height * 4];

	glFinish();	//描画コマンドの完了を保証
	//フレームバッファからピクセルデータを読み取る
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	

	//上下反転を修正
	for (int y = 0; y < height / 2; ++y) {
		for (int x = 0; x < width * 4; ++x) {
			std::swap(data[y * width * 4 + x], data[(height - 1 - y) * width * 4 + x]);
		}
	}
	//pngとして保存
	stbi_write_png(fileName, width, height, 4, data, width * 4);
	
	delete[]data;

}

#include<wincodec.h>
void ScreenShot(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11Texture2D* texture, const std::wstring& fileName)
{
	//テクスチャの情報を取得
	D3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);

	//CPUでアクセス可能なテクスチャを作成
	D3D11_TEXTURE2D_DESC cpuAccessDesc = desc;
	cpuAccessDesc.Usage = D3D11_USAGE_STAGING;
	cpuAccessDesc.BindFlags = 0;
	cpuAccessDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	cpuAccessDesc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
	HRESULT hr = device->CreateTexture2D(&cpuAccessDesc, nullptr, &stagingTexture);
	if (FAILED(hr)) {
		return;
	}

	//テクスチャデータをコピー
	context->CopyResource(stagingTexture.Get(), texture);

	DirectX::ScratchImage image;
	hr=DirectX::CaptureTexture(device,context,stagingTexture.Get(),image);
	if (FAILED(hr)) {
		return;
	}

	//pngとして保存
	const GUID containerFormat = GUID_ContainerFormatPng;
	hr = DirectX::SaveToWICFile(*image.GetImages(), DirectX::WIC_FLAGS_NONE, containerFormat,fileName.c_str());

}

