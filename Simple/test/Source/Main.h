//
// Created by admin on 2023/12/25.
//

#pragma once

#include <GenesisCubeEngine/Core/FCore.h>
#include <GenesisCubeEngine/Core/FFormatter.h>
#include <GenesisCubeEngine/Game/GWindow.h>
#include <GenesisCubeEngine/Debug/Debug.h>
#include <GenesisCubeEngine/Resource/resource.h>
#include <GenesisCubeEngine/Localization/Localization.h>
#include <GenesisCubeEngine/IO/GFileName.h>
#include <GenesisCubeEngine/JSON/Json.h>
#include <GenesisCubeEngine/JSON/JsonReader.h>
#include <GenesisCubeEngine/DirectX/GD2D1Factory.h>
#include <GenesisCubeEngine/Game/GUIVector.h>


#define Text(key) TText(TEXT(key))

using namespace GenesisCube;


class MyProgram : public FProgram
{
public:
	
	MyProgram(TString cmdLine, int nShowCmd)
		: nShowCmd(nShowCmd), cmdLine(std::move(cmdLine)) {}
	
	~MyProgram() noexcept override = default;

public:
	
	TString TText(const TString &key);

private:
	
	void Start() override;
	
	void End() override;
	
	void Tick() override;

public:
	
	const int nShowCmd;
	
	const TString cmdLine;
	
	// ----- ----- ----- -----
	
	TPtr<GWindow> mainWindow;
	
	FTimer timer;
	
	GD2D1Factory factory;
	
	GDWriteFactory writeFactory;

private:
	
	GLanguage zh_cn;
	
	GLanguage en_us;
	
	GLanguage language_debug;
	
	GLanguage *nowLanguage = &zh_cn;
	
};

class MainWindow : public GWindow
{
public:
	
	// 主窗口类名
	static constexpr TChar wndClassName[] = TEXT("my program window class");


public:
	
	explicit MainWindow(MyProgram &program);
	
	~MainWindow() override = default;

protected:
	
	void OnResize(EventOnResizeArgs args) override;
	
	void OnChar(const TChar &input) override;
	
	void OnString(const TString &input) override;
	
	void OnTick(float deltaTime) override;
	
	void OnDropFiles(HDROP hDropInfo) override;
	
	void OnDestroy() override;

private:
	
	GUIVector uis;
	
	TString buffer;
	
	GD2D1HwndRenderTarget hwndRenderTarget;
	
	GDWriteTextFormat textFormat;
	
	GD2D1SolidColorBrush brush;
	
	GD2D1Bitmap bitmap;
	
	GD2D1BitmapBrush bitmapBrush;
	
	MyProgram &program;
	
};
