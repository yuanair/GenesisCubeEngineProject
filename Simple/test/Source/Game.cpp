//
// Created by admin on 2023/12/19.
//
#include <GenesisCubeEngine/UI/PRect.h>
#include "Game.h"


void MainWindow::OnDropFiles(HDROP hDropInfo)
{
	
	TString message;
	TString fileName;
	Win32::FDragQueryFileReader reader(hDropInfo);
	for (size_t i = 0; reader.Get(fileName, i); i++)
	{
		message.append(fileName).push_back(TEXT('\n'));
	}
	FLogger::Inst().LogInfoODS(message);
	
	if (reader.GetFileCount() != 1)
	{
		Win32::MessageBoxT(
			this->program.language->fnOnDropFilesErrorMoreFiles.Get(), FCore::showName, Win32::MessageBoxIconInfo
		);
		return;
	}
	
	reader.Get(fileName, 0);
	tifStream.close();
	tifStream.open(fileName);
	if (!tifStream.is_open())
	{
		Win32::MessageBoxT(
			this->program.language->fnOnDropFilesErrorOpenFile.Get(), FCore::showName,
			Win32::MessageBoxIconError
		);
		return;
	}
	
	program.ReloadYuanShenWindow();
}

MainWindow::MainWindow(MyProgram &program)
	: program(program)
{
	bEnableOnChar = true;
	
	// 创建窗口
	Create(
		*program.mainWindowClass, program.language->mainWindowName.Get(),
		INT_MIN, INT_MIN, 400, 600, Win32::GetInstance()
	);
	
	//
	if (Bad())
	{
		Win32::MessageBoxT(
			std::format(TEXT("{}::Create() Failed"), FFormatter::GetTypeName<Win32::FWindow>()),
			FCore::showName, Win32::MessageBoxIconError
		);
		Win32::Exit(0);
		return;
	}
	
	// 获取文件拖拽权限
	if (!GetFileDragAndDropPermission())
	{
		Win32::MessageBoxT(
			std::format(TEXT("{}::GetFileDragAndDropPermission() Failed"), FFormatter::GetTypeName<Win32::FWindow>()),
			FCore::showName, Win32::MessageBoxIconError
		);
		Win32::Exit(0);
		return;
	}
	
	// 显示窗口
	ShowAndUpdate();
	
	// directX
	ThrowIfFailed(FD2D1Helpers::CreateHwndRenderTarget(hwndRenderTarget, this->program.factory, *this));
	
	FImageData data(this->program.language->backGroundImage.Get());
	ThrowIfFailed(
		FD2D1Helpers::CreateBitmapFromImageData(
			this->hwndRenderTarget.Get(), bitmap, data,
			D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)
		)
	);
	BitmapBrush(bitmap.Get(), ui.fillBrush);
	
	auto uRect = ui.NewChild<PRect>();
	uRect->SetCalRect({0.1f, 0.1f, 0.2f, 0.2f});
	SolidColorBrush(D2D1::ColorF(0.5f, 0.0f, 0.5f, 0.5f), uRect->fillBrush);
	
	showTextUI = ui.NewChild<UText>();
	
	SolidColorBrush(
		D2D1::ColorF(
			(float) program.language->showTextColorR.Get(), (float) program.language->showTextColorG.Get(),
			(float) program.language->showTextColorB.Get(), (float) program.language->showTextColorA.Get()),
		showTextUI->defaultFillBrush
	);
	showTextUI->showText = program.language->showText.Get();
	
	ThrowIfFailed(
		this->program.writeFactory->CreateTextFormat(
			TEXT("Consolas"), nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL, 20.0f, TEXT("Consolas"),
			showTextUI->textFormat.ReleaseAndGetAddressOf()
		)
	);
	
	mouseUI = ui.NewChild<UEllipse>();
	mouseUI->ellipse.radiusX = mouseUI->ellipse.radiusY = 50.0f;
	SolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 0.1f), mouseUI->fillBrush);
}

void MainWindow::OnChar(const TChar &input)
{
	FWindow::OnChar(input);
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
	FWindow::OnString(input);
	buffer += input;
	// input point
	inputPoint = {(int) buffer.size(), 0};
}

void MainWindow::OnTick(float deltaTime)
{
	FWindow::OnTick(deltaTime);
	
	hwndRenderTarget->BeginDraw();
	
	D2D1_SIZE_F renderTargetSize = hwndRenderTarget->GetSize();
	
	D2D1_SIZE_F scaleSize;
	scaleSize.width = renderTargetSize.width / bitmap->GetSize().width;
	scaleSize.height = scaleSize.width / bitmap->GetSize().width * bitmap->GetSize().height;
	ui.fillBrush->SetTransform(D2D1::Matrix3x2F::Scale(scaleSize));
	
	ui.SetMode(PPanel::ModeKeep);
	ui.SetCalRect({0.0f, 0.0f, renderTargetSize.width, renderTargetSize.height});
	ui.Render(hwndRenderTarget.Get());
	
	auto mousePosition = GetMousePosition();
	
	mouseUI->ellipse.point = D2D1::Point2F((float) mousePosition.x, (float) mousePosition.y);

//	{
//		TString text;
//		for (auto &item: program.GetOutput())
//		{
//			text += item;
//			text += TEXT("\n");
//		}
//		renderTargetRect.top += 100;
//		FD2D1Helpers::DrawString(
//			this->hwndRenderTarget.Get(), text, textFormat,
//			renderTargetRect,
//			brush.Get()
//		);
//	}

//	hwndRenderTarget.DrawText(
//		std::format(TEXT("{:.2f}fps\ndt: {:.6f}s"), this->program->timer.GetFps(), deltaTime), textFormat,
//		D2D1::RectF(0.0f, 000.0f, 500.0f, 100.0f), brush
//	);
	
	ThrowIfFailed(hwndRenderTarget->EndDraw());
	
	if (!tifStream.is_open()) return;
	
	program.yuanShenWindow.SetForegroundWindow();
	
	TChar vk;
	do
	{
		
		if (!tifStream.get(vk))
		{
			Stop();
			break;
		}
		if (vk >= 'A' && vk <= 'Z')
		{
			program.Output(std::format(TEXT("index: '{}'"), vk));
			program.yuanShenWindow.SeedKeyDown(vk);
			program.yuanShenWindow.SeedKeyUp(vk);
		}
		else if (vk >= 'a' && vk <= 'z')
		{
			program.Output(std::format(TEXT("index: '{}'"), vk));
			vk = vk - 'a' + 'A';
			program.yuanShenWindow.SeedKeyDown(vk);
			program.yuanShenWindow.SeedKeyUp(vk);
		}
		else if (vk == ' ')
		{
			program.Output(std::format(TEXT("sleep")));
			Sleep(100);
		}
		else if (vk == '\r' || vk == '\n' || vk == '\t' || vk == '\v')
		{
		
		}
		else
		{
			program.Output(std::format(TEXT("unknown index: '{}'"), vk));
		}
	}
	while (vk != TEXT(' '));
	
	
}

void MainWindow::OnDestroy()
{
	FWindow::OnDestroy();
	Win32::Exit(0);
}

void MainWindow::OnResize(const EventOnResizeArgs &args)
{
	FWindow::OnResize(args);
	if (!hwndRenderTarget) return;
	ThrowIfFailed(hwndRenderTarget->Resize(D2D1::SizeU(args.width, args.height)));
	this->program.Tick();
}

void MainWindow::OnKeyDown(const Win32::FWindow::EventKeyArgs &args)
{
	FWindow::OnKeyDown(args);
}

void MainWindow::OnKeyUp(const Win32::FWindow::EventKeyArgs &args)
{
	FWindow::OnKeyUp(args);
}

void MainWindow::Stop()
{
	this->tifStream.close();
}

void MainWindow::SolidColorBrush(const D2D_COLOR_F &color, TComPtr<UUI::Brush> &brush)
{
	if (Is<ID2D1SolidColorBrush>(brush.Get()))
		return ((ID2D1SolidColorBrush *) brush.Get())->SetColor(color);
	ThrowIfFailed(
		this->hwndRenderTarget->CreateSolidColorBrush(color, (ID2D1SolidColorBrush **) brush.ReleaseAndGetAddressOf())
	);
}

void MainWindow::BitmapBrush(ID2D1Bitmap *pBitmap, TComPtr<UUI::Brush> &brush)
{
	if (Is<ID2D1BitmapBrush>(brush.Get()))
		return ((ID2D1BitmapBrush *) brush.Get())->SetBitmap(pBitmap);
	ThrowIfFailed(
		this->hwndRenderTarget->CreateBitmapBrush(pBitmap, (ID2D1BitmapBrush **) brush.ReleaseAndGetAddressOf())
	);
}

void MyProgram::Tick()
{
	timer.Tick();
	mainWindow->Tick(timer.GetDeltaTimeF());
}

void MyProgram::InitDirectX()
{
	ThrowIfFailed(FD2D1Helpers::CreateFactory(this->factory));
	ThrowIfFailed(FDWriteHelpers::CreateFactory(this->writeFactory));
}

MyProgram::MyProgram()
{
	this->data = MakeUnique<DataJsonManagement>();
	this->language = MakeUnique<LanguageJsonManagement>(data->language.Get());
	InitDirectX();
	
	FCore::showName = this->language->mainWindowName.Get();
	mainWindowClass = MakeUnique<Win32::FWindowClass>(this->language->mainWindowClassName.Get(), Win32::GetInstance());
	
	// 注册窗口类
	if (!mainWindowClass->Register(
		Win32::GetIcon(IDI_ICON_Main), Win32::GetIcon(IDI_ICON_MainSm), Win32::GetIcon(IDI_CURSOR_Main)))
	{
		Win32::MessageBoxT(
			std::format(
				TEXT("{}::Register Failed\n{}"), FFormatter::GetTypeName<Win32::FWindowClass>(),
				FFormatter::FormatMessageT(GetLastError())),
			FCore::showName, Win32::MessageBoxIconError
		);
		Win32::Exit(0);
		return;
	}
	mainWindow = MakeUnique<MainWindow>(*this);
}

MyProgram::~MyProgram()
= default;

void MyProgram::ReloadYuanShenWindow()
{
	this->yuanShenWindow.Bind(Win32::FWindow::FindWindowFromName(this->language->boundWindowName.Get()));
	if (this->yuanShenWindow.Bad())
	{
		mainWindow->Stop();
		Win32::MessageBoxT(
			this->language->boundWindowErrorNotFound.Get(), FCore::showName,
			Win32::MessageBoxIconError
		);
		return;
	}
}


void JsonManagement::LoadJson(const TString &file)
{
	TIFStream ifStream(file, std::ios::in);
	if (!ifStream.is_open()) throw ENotFindException(TEXT("Cannot open file \"") + file + TEXT("\""));
	ifStream.imbue(std::locale(locName));
	Json::FJsonReader jsonReader(ifStream);
	json = *jsonReader.Next();
	ifStream.close();
}

DataJsonManagement::DataJsonManagement()
{
	LoadJson(TEXT("Data\\data.json"));
}

LanguageJsonManagement::LanguageJsonManagement(const TString &language)
{
	LoadJson(TEXT("Data\\languages\\") + language + TEXT(".json"));
}
