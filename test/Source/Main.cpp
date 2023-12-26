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
	ThrowIfFailed(this->factory.Create());
	ThrowIfFailed(this->hwndRenderTarget.Create(factory, *this));
	ThrowIfFailed(this->gdWriteFactory.Create());
	ThrowIfFailed(this->gdWriteFactory.CreateTextFormat(
		textFormat, TEXT("Consolas"), DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		50.0f, TEXT("Consolas")
	));
	ThrowIfFailed(this->hwndRenderTarget.CreateSolidBrush(brush, D2D1::ColorF(0.1f, 0.1f, 0.1f)));
	
	
}

void DXWindow::OnTick(float deltaTIme)
{
	GWindow::OnTick(deltaTIme);
	hwndRenderTarget.BeginDraw();
	hwndRenderTarget.Clear(D2D1::ColorF(1.0f, 0.0f, 1.0f));
	
	brush.SetColor(0.0f, 0.0f, 0.0f);
	
	hwndRenderTarget.FillRectangle(D2D1::RectF(0.0f, 0.0f, GetMouseX(), GetMouseY()), brush);
	brush.SetColor(1.0f, 1.0f, 1.0f);
	
	hwndRenderTarget.DrawText(TEXT("Hello World!"), textFormat, D2D1::RectF(0.0f, 0.0f, 500.0f, 500.0f), brush);
	
	ThrowIfFailed(hwndRenderTarget.EndDraw());
}

void DXWindow::OnResize(GWindow::EventOnResizeArgs args)
{
	GWindow::OnResize(args);
	if (hwndRenderTarget) ThrowIfFailed(hwndRenderTarget.Resize(args.width, args.height));
}
