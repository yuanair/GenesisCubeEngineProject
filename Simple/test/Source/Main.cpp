//
// Created by admin on 2023/12/19.
//
#include <GenesisCubeEngine/Game/GBox.h>
#include "Main.h"


void MainWindow::OnDropFiles(HDROP hDropInfo)
{
	std::list<TPtr<GFileName>> files;
	GFileName::DragQuery(hDropInfo, files);
	TString message;
	for (auto& file : files)
	{
		message.append(file->GetFileName()).push_back(TEXT('\n'));
		if (auto *ptr = file.Cast<GDirectoryName>()) ptr->Find(files);
	}
	FLogger::Inst().LogInfoODS(message);
}

MainWindow::MainWindow(MyProgram &program)
	: program(program)
{
	// 注册窗口类
	GWindow::Register(wndClassName, FCore::GetIcon(IDI_ICON_Main), FCore::GetIcon(IDI_ICON_MainSm));
	
	// 启用OnChar
	bEnableOnChar = true;
	
	// 创建窗口
	Create(wndClassName, program.Text("windowName"));
	
	// 显示窗口
	ShowAndUpdate(program.nShowCmd);
	
	// directX
	this->program.factory.CreateHwndRenderTarget(hwndRenderTarget, *this).ThrowIfThrow();
	
	this->program.writeFactory.CreateTextFormat(textFormat, TEXT("Consolas"), TEXT("Consolas"), 50.0f).ThrowIfThrow();
	this->hwndRenderTarget.CreateSolidBrush(brush, D2D1::ColorF(0.1f, 0.1f, 0.1f)).ThrowIfThrow();
	
	FImageData data;
	data.LoadFromFile(TEXT("Data/ys/w5.png"));
	this->hwndRenderTarget.CreateBitmapFromImageData(bitmap, data).ThrowIfThrow();
	this->hwndRenderTarget.CreateBitmapBrush(bitmapBrush, bitmap.Get()).ThrowIfThrow();
	
	auto box = uis.AddUI<GBox>();
	hwndRenderTarget.CreateSolidBrush(
		reinterpret_cast<GD2D1SolidColorBrush &>(box->brush), D2D1::ColorF(0.5f, 0.0f, 0.5f, 0.1f)).ThrowIfThrow();
	box->w = 500.f;
	box->h = 256.f;
}

void MainWindow::OnChar(const TChar &input)
{
	GWindow::OnChar(input);
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
	GWindow::OnString(input);
	buffer += input;
	// input point
	inputPoint = {(int) buffer.size(), 0};
}

void MainWindow::OnTick(float deltaTime)
{
	GWindow::OnTick(deltaTime);
	hwndRenderTarget.BeginDraw();
	hwndRenderTarget.Clear(D2D1::ColorF(0.01f, 0.01f, 0.01f));
	
	hwndRenderTarget.FillRectangle(D2D1::RectF(0.0f, 0.0f, 256.0f, 256.0f), bitmapBrush);
	
	uis.Render(hwndRenderTarget.Get());
	
	brush.SetColor(1.0f, 1.0f, 1.0f, 0.2f);
	
	hwndRenderTarget.FillCircle(D2D1::Point2F((float) GetMouseX(), (float) GetMouseY()), 50.0f, brush);
	brush.SetColor(1.0f, 1.0f, 1.0f);
	
	hwndRenderTarget.DrawText(buffer, textFormat, D2D1::RectF(0.0f, 0.0f, 500.0f, 500.0f), brush);
	
	hwndRenderTarget.EndDraw().ThrowIfThrow();
}

void MainWindow::OnDestroy()
{
	GWindow::OnDestroy();
	FCore::Exit(0);
}

void MainWindow::OnResize(GWindow::EventOnResizeArgs args)
{
	GWindow::OnResize(args);
	if (hwndRenderTarget) hwndRenderTarget.Resize(args.width, args.height).ThrowIfThrow();
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

void MyProgram::Start()
{
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
	
	GD2D1Factory::Create(this->factory.ReleaseAndGetAddressOf()).ThrowIfThrow();
	GDWriteFactory::Create(this->writeFactory.ReleaseAndGetAddressOf()).ThrowIfThrow();
	mainWindow = new MainWindow(*this);
}

void MyProgram::End()
{

}

#ifdef UNICODE

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
#else

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#endif
{
#ifdef _DEBUG
	MyProgram myProgram(lpCmdLine, nShowCmd);
	FCore::Running(myProgram, FCore::EditorDebug);
#else
	try
	{
		MyProgram myProgram(lpCmdLine, nShowCmd);
		FCore::Running(myProgram, FCore::EditorDebug);
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

