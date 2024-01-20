//
// Created by admin on 2023/12/19.
//
#include <GenesisCubeEngine/UI/PRect.h>
#include "Game.h"


void MainWindow::OnDropFiles(HDROP hDropInfo)
{
	JSON::Json &onDropFilesJson = this->program.language[TEXT("OnDropFiles")];
	JSON::Json &errorTextJson = onDropFilesJson[TEXT("error texts")];
	
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
			errorTextJson[TEXT("more files")].GetString(TEXT("more files")), FCore::showName, Win32::MessageBoxIconInfo
		);
		return;
	}
	
	reader.Get(fileName, 0);
	tifStream.close();
	tifStream.open(fileName);
	if (!tifStream.is_open())
	{
		Win32::MessageBoxT(
			errorTextJson[TEXT("open file error")].GetString(TEXT("open file error")), FCore::showName,
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
	Create(*program.mainWindowClass, program.windowName, INT_MIN, INT_MIN, 400, 600, Win32::GetInstance());
	
	//
	if (Bad())
	{
		Win32::MessageBoxT(
			std::format(TEXT("{}::Create() Failed"), FFormatter::GetTypeName<Win32::FWindow>()),
			program.windowName, Win32::MessageBoxIconError
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
	
	FImageData data(this->program.language[TEXT("background")][TEXT("image")].GetString(TEXT("unknown file")));
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
	JSON::Json &showTextJson = program.language[TEXT("show text")];
	JSON::Json &colorJson = showTextJson[TEXT("color")];
	
	SolidColorBrush(
		D2D1::ColorF(colorJson[0].GetFloat(), colorJson[1].GetFloat(), colorJson[2].GetFloat()),
		showTextUI->defaultFillBrush
	);
	showTextUI->showText = showTextJson[TEXT("text")].GetString(TEXT("<show text>"));
	
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
	
	SetForegroundWindow(program.yuanShenWindow);
	
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
			program.Output(std::format(TEXT("key: '{}'"), vk));
			SeedKeyDown(program.yuanShenWindow, vk);
			SeedKeyUp(program.yuanShenWindow, vk);
		}
		else if (vk >= 'a' && vk <= 'z')
		{
			program.Output(std::format(TEXT("key: '{}'"), vk));
			vk = vk - 'a' + 'A';
			SeedKeyDown(program.yuanShenWindow, vk);
			SeedKeyUp(program.yuanShenWindow, vk);
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
			program.Output(std::format(TEXT("unknown key: '{}'"), vk));
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

void MainWindow::BitmapBrush(ID2D1Bitmap *bitmap, TComPtr<UUI::Brush> &brush)
{
	if (Is<ID2D1BitmapBrush>(brush.Get()))
		return ((ID2D1BitmapBrush *) brush.Get())->SetBitmap(bitmap);
	ThrowIfFailed(
		this->hwndRenderTarget->CreateBitmapBrush(bitmap, (ID2D1BitmapBrush **) brush.ReleaseAndGetAddressOf())
	);
}

void MyProgram::Tick()
{
	timer.Tick();
	auto deltaTime = (float) timer.GetDeltaTime();
	mainWindow->Tick(deltaTime);
}

void MyProgram::InitLocale()
{
	std::locale::global(std::locale("zh_CN.UTF-8"));
}

void MyProgram::InitJson()
{
	LoadJson(this->data, TEXT("Data\\data.json"));
	LoadJson(
		this->language,
		TEXT("Data\\languages\\") + this->data[TEXT("language")].GetString(TEXT("en_us")) + TEXT(".json")
	);
}

void MyProgram::InitDirectX()
{
	ThrowIfFailed(FD2D1Helpers::CreateFactory(this->factory));
	ThrowIfFailed(FDWriteHelpers::CreateFactory(this->writeFactory));
}

void MyProgram::Start()
{
	InitLocale();
	InitJson();
	InitDirectX();
	
	{
		Win32::FFileFinder fileFinder;
		WIN32_FIND_DATA fileData;
		fileFinder.Find(fileData, TEXT("./Data/languages/*.json"));
		do
		{
			Win32::MessageBoxT(std::format(TEXT("{}"), fileData.cFileName), FCore::showName);
		}
		while (fileFinder.Next(fileData));
	}
	
	{
		JSON::Json &mainWindowJson = this->language[TEXT("main window")];
		FCore::showName = windowName = mainWindowJson[TEXT("window name")].GetString(TEXT("<error>"));
		windowClassName = mainWindowJson[TEXT("window class name")].GetString(TEXT("Default Window Class Name"));
	}
	mainWindowClass = MakeUnique<Win32::FWindowClass>(windowClassName, Win32::GetInstance());
	
	if (windowClassName.empty()) windowClassName = TEXT("Default Window Class Name");
	
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

void MyProgram::End()
{

}


void MyProgram::LoadJson(JSON::Json &json, const TString &file)
{
	TIFStream ifStream(file);
	if (!ifStream.is_open()) throw ENotFindException(TEXT("Cannot open file \"") + file + TEXT("\""));
	JSON::FJsonReader jsonReader(ifStream);
	json = *jsonReader.Next();
	ifStream.close();
}

void MyProgram::ReloadYuanShenWindow()
{
	JSON::Json &boundWindowJson = this->language[TEXT("bound window")];
	this->yuanShenWindow = Win32::FWindow::FindWindowFromName(
		boundWindowJson[TEXT("window name")].GetString(TEXT("<error>")));
	if (this->yuanShenWindow == nullptr)
	{
		mainWindow->Stop();
		Win32::MessageBoxT(
			boundWindowJson[TEXT("error text")].GetString(TEXT("Unable to bind window")), FCore::showName,
			Win32::MessageBoxIconError
		);
		return;
	}
}



