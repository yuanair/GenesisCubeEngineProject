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
#include <GenesisCubeEngine/DirectX/GDevice.h>


#define Text(key) TText(TEXT(key))

using namespace GenesisCubeEngine;


class MyProgram
{
public:
	
	// 主窗口类名
	static constexpr TChar wndClassName[] = TEXT("my program window class");

public:
	
	MyProgram(const TString &cmdLine, int nShowCmd);
	
	~MyProgram();

public:
	
	TString TText(const TString &key);
	
	void Tick();

public:
	
	GDevice device;
	
	GDeviceContext deviceContext;
	
	GDXGIAdapter adapter;
	
	GDXGIFactory factory;
	
	// ----- ----- ----- -----
	
	TPtr<GWindow> mainWindow;
	
	FTimer timer;

private:
	
	GLanguage zh_cn;
	
	GLanguage en_us;
	
	GLanguage language_debug;
	
	GLanguage *nowLanguage = &zh_cn;
};

class DXWindow : public GWindow
{
public:
	
	DXWindow(const TString &wndClassName, const TString &windowName, int nShowCmd, MyProgram &program);
	
	~DXWindow() override = default;

protected:
	
	void OnTick(float deltaTIme) override;
	
	void OnResize(EventOnResizeArgs args) override;

protected:
	
	MyProgram &program;
	
	GDXGISwapChain swapChain;
	
	GTexture2D backBuffer;
	
	GRenderTargetView renderTargetView;
	
	GTexture2D depthStencilBuffer;
	
	GDepthStencilView depthStencilView;
	
};

class MainWindow : public DXWindow
{
public:

public:
	
	MainWindow(const TString &wndClassName, int nShowCmd, MyProgram &program);

protected:
	
	void OnChar(const TChar &input) override;
	
	void OnString(const TString &input) override;
	
	void OnTick(float deltaTime) override;
	
	void OnDropFiles(HDROP hDropInfo) override;
	
	void OnDestroy() override;

private:
	
	TString buffer;
	
};
