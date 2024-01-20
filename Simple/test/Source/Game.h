//
// Created by admin on 2023/12/25.
//

#pragma once

#include <GenesisCubeBase/Core/FFormatter.h>

#include <GenesisCubeBase/Json/Json.h>
#include <GenesisCubeBase/Json/FJsonReader.h>
#include <GenesisCubeBase/Win32/Win32.h>
#include <GenesisCubeBase/Core/Debug.h>

#include <GenesisCubeEngine/Core/FCore.h>
#include <GenesisCubeEngine/DirectX/FD2D1Helpers.h>
#include <GenesisCubeEngine/DirectX/FDWriteHelpers.h>
#include <GenesisCubeEngine/Resource/resource.h>
#include <GenesisCubeEngine/UI/UUI.h>
#include <GenesisCubeEngine/UI/PRect.h>
#include <GenesisCubeEngine/UI/UEllipse.h>
#include <GenesisCubeEngine/UI/UText.h>

using namespace GenesisCube;

class MyProgram : public FProgram
{
public:
	
	MyProgram() noexcept {}
	
	~MyProgram() noexcept override = default;

public:
	
	void ReloadYuanShenWindow();
	
	void InitLocale();
	
	void InitJson();
	
	void InitDirectX();

public:
	
	void Start() override;
	
	void End() override;
	
	void Tick() override;

public:
	
	///
	/// \param json JSON
	/// \param file 文件
	static void LoadJson(JSON::Json &json, const TString &file);
	
	
	void Output(const TString &value)
	{
		static size_t count = 0;
		this->output.push_back(ToTString(++count) + TEXT(": ") + value);
		if (this->output.size() > 20)
			this->output.erase(this->output.begin());
	}
	
	std::list<TString> &GetOutput() { return this->output; }

public:
	
	TUniquePtr<class MainWindow> mainWindow{};
	
	FTimer timer;
	
	TComPtr<ID2D1Factory1> factory;
	
	TComPtr<IDWriteFactory> writeFactory;
	
	JSON::Json language;
	
	JSON::Json data;
	
	void *yuanShenWindow = nullptr;

public:
	
	TString windowName;
	
	TString windowClassName;
	
	TUniquePtr<Win32::FWindowClass> mainWindowClass{};

private:
	
	std::list<TString> output;
	
};

class MainWindow : public Win32::FWindow
{
public:
	
	explicit MainWindow(MyProgram &program);
	
	~MainWindow() noexcept override = default;

public:
	
	void Stop();

protected:
	
	void OnKeyDown(const EventKeyArgs &args) override;
	
	void OnKeyUp(const EventKeyArgs &args) override;
	
	void OnResize(const EventOnResizeArgs &args) override;
	
	void OnChar(const TChar &input) override;
	
	void OnString(const TString &input) override;
	
	void OnTick(float deltaTime) override;
	
	void OnDropFiles(HDROP hDropInfo) override;
	
	void OnDestroy() override;
	
	///
	/// 创建笔刷
	/// \param color 颜色
	/// \param brush 笔刷
	void SolidColorBrush(const D2D_COLOR_F &color, TComPtr<UUI::Brush> &brush);
	
	///
	/// \param bitmap 图片
	/// \param brush 笔刷
	void BitmapBrush(ID2D1Bitmap *bitmap, TComPtr<UUI::Brush> &brush);

private:
	
	PRect ui;
	
	UEllipse *mouseUI;
	
	UText *showTextUI;
	
	TString buffer;
	
	TComPtr<ID2D1HwndRenderTarget> hwndRenderTarget;
	
	TComPtr<ID2D1Bitmap> bitmap;
	
	MyProgram &program;
	
	TIFStream tifStream;
	
};
