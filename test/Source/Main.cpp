//
// Created by admin on 2023/12/19.
//
#include "Main.h"


void MainWindow::OnDropFiles(HDROP hDropInfo)
{
	std::list<TPtr<GFileName>> files;
	GFileName::DragQuery(hDropInfo, files);
	TString message;
	for (auto file: files)
	{
		message.append(file->GetFileName()).push_back(TEXT('\n'));
		if (auto *ptr = file.Cast<GDirectoryName>()) ptr->Find(files);
	}
	FLogger::Inst().LogInfoODS(message);
}

MainWindow::MainWindow(const TString &wndClassName, int nShowCmd, MyProgram &program)
	: DXWindow(wndClassName, program.Text("MainWindowName"), nShowCmd, program)
{
	
	bEnableOnChar = true;
	
}

void MainWindow::OnChar(const TChar &input)
{
	DXWindow::OnChar(input);
	if (input == VK_BACK)
	{
		if (!buffer.empty()) buffer.pop_back();
	}
	else buffer += input;
	// input point
	inputPoint = {(int) buffer.size(), 0};
}

void MainWindow::OnString(const TString &input)
{
	DXWindow::OnString(input);
	buffer += input;
	// input point
	inputPoint = {(int) buffer.size(), 0};
}

void MainWindow::OnTick(float deltaTime)
{
	DXWindow::OnTick(deltaTime);
//	HDC hdc = GetDC(GetHWnd());
//	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
//
//	RECT rect = {0, 0, 500, 500};
//	FillRect(hdc, &rect, brush);
//	DrawText(hdc, buffer.c_str(), -1, &rect, DT_LEFT);
//
//	DeleteBrush(brush);
//	DeleteDC(hdc);
}

void MainWindow::OnDestroy()
{
	DXWindow::OnDestroy();
	FCore::Exit(0);
}


MyProgram::MyProgram(const TString &cmdLine, int nShowCmd)
{
	GenesisCubeEngine::FCore::Init();
	
	{
		std::locale::global(std::locale("zh_CN.UTF-8"));
		TIFStream ifStream;
		ifStream.open(TEXT("Data/zh_cn.json"), std::ios::in);
		if (ifStream.is_open())
		{
			JSON::JsonReader jsonReader(ifStream);
			this->zh_cn.LoadFromJson(*jsonReader.NextSafe());
			ifStream.close();
		}
		else
		{
			GWindow::MBox(TEXT("can not open zh_cn.json"), FCore::name);
		}
		ifStream.open(TEXT("Data/en_us.json"), std::ios::in);
		if (ifStream.is_open())
		{
			JSON::JsonReader jsonReader(ifStream);
			this->en_us.LoadFromJson(*jsonReader.NextSafe());
			ifStream.close();
		}
		else
		{
			GWindow::MBox(TEXT("can not open en_us.json"), FCore::name);
		}
		
		ifStream.open(TEXT("Data/language_debug.json"), std::ios::in);
		if (ifStream.is_open())
		{
			JSON::JsonReader jsonReader(ifStream);
			this->language_debug.LoadFromJson(*jsonReader.NextSafe());
			ifStream.close();
		}
		else
		{
			GWindow::MBox(TEXT("can not open language_debug.json"), FCore::name);
		}
	}
	
	ThrowIfFailed(device.AutoCreate(deviceContext, adapter, factory));
	
	// 注册窗口类
	GWindow::Register(wndClassName, FCore::GetIcon(IDI_ICON_Main), FCore::GetIcon(IDI_ICON_MainSm));
	
	mainWindow = new MainWindow(wndClassName, nShowCmd, *this);
}

void MyProgram::Tick()
{
	timer.Tick();
	auto deltaTime = (float) timer.GetDeltaTime();
	mainWindow->Tick(deltaTime);
}

TString MyProgram::TText(const TString &key)
{
	if (nowLanguage == nullptr) return key;
	auto iter = nowLanguage->values.find(key);
	if (iter == nowLanguage->values.end()) return key;
	return iter->second;
}

MyProgram::~MyProgram() = default;

#ifdef UNICODE

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
#else

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
#ifdef _DEBUG
	MyProgram myProgram(lpCmdLine, nShowCmd);
	while (GWindow::PeekEvents())
	{
		myProgram.Tick();
	}
#else
	try
	{
		MyProgram myProgram(lpCmdLine, nShowCmd);
		while (GWindow::PeekEvents())
		{
			myProgram.Tick();
		}
	}
	catch (const EException &exception)
	{
		TString buffer = TEXT("error: ");
		buffer += exception.What();
		FLogger::Inst().LogFatalODS(buffer);
		GWindow::MBox(buffer, FCore::name, MB_OK | MB_ICONSTOP);
	}
	catch (const std::exception &ex)
	{
		TString buffer = TEXT("error: ");
		buffer += FFormatter::StringToWString(ex.what());
		FLogger::Inst().LogFatalODS(buffer);
		GWindow::MBox(buffer, FCore::name, MB_OK | MB_ICONSTOP);
	}
#endif
	return 0;
}

DXWindow::DXWindow(const TString &wndClassName, const TString &windowName, int nShowCmd, MyProgram &program)
	: program(program)
{
	// 创建窗口
	Create(wndClassName, windowName);
	
	// 显示窗口
	ShowAndUpdate(nShowCmd);
	
	// directX
//	program.factory.CreateSwapChain(swapChain, program.device, *this, 2);
//	swapChain.GetBuffer(backBuffer, 0);
//	program.device.CreateRenderTargetView(renderTargetView, backBuffer);
//
//	auto backDesc = backBuffer.GetDesc();
//	program.device.CreateTexture2D(depthStencilBuffer, GTexture2D::DepthStencilDesc(backDesc.Width, backDesc.Height));
//	program.device.CreateDepthStencilView(depthStencilView, depthStencilBuffer);
//
//	std::vector<D3D11_VIEWPORT> viewports = {
//		D3D11_VIEWPORT{
//			.TopLeftX = 0.0f,
//			.TopLeftY = 0.0f,
//			.Width=static_cast<FLOAT>(backDesc.Width),
//			.Height=static_cast<FLOAT>(backDesc.Height),
//			.MinDepth = 0.0f,
//			.MaxDepth = 1.0f,
//		}
//	};
//	program.deviceContext.RSSetViewports(viewports);
	
}

void DXWindow::OnTick(float deltaTIme)
{
	GWindow::OnTick(deltaTIme);
	program.deviceContext.ClearRenderTargetView(renderTargetView, {0.5f, 0.0f, 0.5f, 1.0f});
	program.deviceContext.ClearDepthStencilView(depthStencilView);
	std::vector<GRenderTargetView::TUnknown::Type *> buffer = {renderTargetView.Get()};
	program.deviceContext.OMSetRenderTargets(buffer, depthStencilView);
	swapChain.Present();
}

void DXWindow::OnResize(GWindow::EventOnResizeArgs args)
{
	GWindow::OnResize(args);
	backBuffer.Reset();
	renderTargetView.Reset();
	depthStencilBuffer.Reset();
	depthStencilView.Reset();
	swapChain.Reset();
	ThrowIfFailed(program.factory.CreateSwapChain(swapChain, program.device, *this, 2));
	ThrowIfFailed(swapChain.GetBuffer(backBuffer, 0));
	ThrowIfFailed(program.device.CreateRenderTargetView(renderTargetView, backBuffer));
	
	auto backDesc = backBuffer.GetDesc();
	ThrowIfFailed(program.device.CreateTexture2D(
		depthStencilBuffer, GTexture2D::DepthStencilDesc(backDesc.Width, backDesc.Height)));
	ThrowIfFailed(program.device.CreateDepthStencilView(depthStencilView, depthStencilBuffer));
	
	std::vector<D3D11_VIEWPORT> viewports = {
		D3D11_VIEWPORT{
			.TopLeftX = 0.0f,
			.TopLeftY = 0.0f,
			.Width=static_cast<FLOAT>(backDesc.Width),
			.Height=static_cast<FLOAT>(backDesc.Height),
			.MinDepth = 0.0f,
			.MaxDepth = 1.0f,
		}
	};
	program.deviceContext.RSSetViewports(viewports);
}
