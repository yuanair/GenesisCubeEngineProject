//
// Created by admin on 2023/12/25.
//

#pragma once

#include <GenesisCubeBase/Core/FFormatter.h>

#include <GenesisCubeBase/Json/Json.h>
#include <GenesisCubeBase/Json/FJsonReader.h>
#include <GenesisCubeBase/Json/JsonGetter.h>
#include <GenesisCubeBase/Win32/Win32.h>
#include <GenesisCubeBase/Core/Debug.h>

#include <GenesisCubeEngine/Core/FCore.h>
#include <GenesisCubeEngine/Core/FLocator.h>
#include <GenesisCubeEngine/DirectX/FD2D1Helpers.h>
#include <GenesisCubeEngine/DirectX/FDWriteHelpers.h>
#include <GenesisCubeEngine/Resource/resource.h>
#include <GenesisCubeEngine/UI/UUI.h>
#include <GenesisCubeEngine/UI/PRect.h>
#include <GenesisCubeEngine/UI/UEllipse.h>
#include <GenesisCubeEngine/UI/UText.h>

using namespace GenesisCube;

//
// 参考
//
// 1. 抽象和解耦让扩展代码更快更容易，
// 但除非确信需要灵活性，否则不要在这上面浪费时间。
//
// 2. 在整个开发周期中为性能考虑并做好设计，
// 但是尽可能推迟那些底层的，基于假设的优化，那会难以编写代码。
//
// 3. 相信我，发布项目前两个月不是开始思考“游戏运行只有1FPS”这种问题的时候。
//
// 4. 快速地探索游戏的设计空间，但不要跑得太快，在身后留下烂摊子。毕竟你总得回来打扫。
//
// 5. 如果打算抛弃这段代码，就不要尝试将其写完美。
//
// 6. 如果你想要做出让人享受的东西，那就享受做它的过程。
//
// 7. 避免在处理事件的代码中发送事件。
//
// PS: 使用组件时，我最不喜欢的就是组件Component这个单词的长度。
//



///
/// json管理类
class JsonManagement
{
public:
	
	JsonManagement() = default;
	
	~JsonManagement() = default;

public:
	
	///
	/// \param file 文件
	void LoadJson(const TString &file);

public:
	
	static constexpr Char locName[] = "zh_CN.UTF-8";

protected:
	
	Json::Json json;
	
	Json::FJsonGetter jsonGetter{json};
	
};

///
/// 数据json管理类
class DataJsonManagement : public JsonManagement
{
public:
	
	DataJsonManagement();
	
	~DataJsonManagement() = default;

public:
	
	Json::TJObjectValueGetter<TString> language{jsonGetter, TEXT("language"), TEXT("en_us")};
	
};

///
/// 语言管理类
class LanguageJsonManagement : public JsonManagement
{
public:
	
	explicit LanguageJsonManagement(const TString &language);
	
	~LanguageJsonManagement() = default;

public:
	
	Json::TJObjectValueGetter<TString> name{jsonGetter, TEXT("name"), TEXT("<error name>")};
	
	Json::TJObjectValueGetter<TString> displayName{jsonGetter, TEXT("display name"), TEXT("<error display name>")};
	
	// main window
	Json::FJObjectGetter mainWindowJson{jsonGetter, TEXT("main window")};
	
	Json::TJObjectValueGetter<TString> mainWindowName{
		mainWindowJson, TEXT("window name"), TEXT("<error language json>")
	};
	
	Json::TJObjectValueGetter<TString> mainWindowClassName{
		mainWindowJson, TEXT("window class name"), TEXT("default main window class name")
	};
	
	
	// bound window
	Json::FJObjectGetter boundWindowJson{jsonGetter, TEXT("bound window")};
	
	Json::TJObjectValueGetter<TString> boundWindowName{
		boundWindowJson, TEXT("window name"), TEXT("<error language json>")
	};
	
	Json::TJObjectValueGetter<TString> boundWindowErrorNotFound{
		boundWindowJson, TEXT("error not found")
	};
	
	// background
	Json::FJObjectGetter backGroundJson{jsonGetter, TEXT("background")};
	
	Json::TJObjectValueGetter<TString> backGroundImage{
		backGroundJson, TEXT("image"), TEXT("Data/images/background.png")
	};
	
	// show text
	Json::FJObjectGetter showTextJson{jsonGetter, TEXT("show text")};
	
	//// show text
	Json::TJObjectValueGetter<TString> showText{
		showTextJson, TEXT("text"), TEXT("<error language json>")
	};
	
	//// show text color
	Json::FJObjectGetter showTextColor{
		showTextJson, TEXT("color")
	};
	
	Json::TJArrayValueGetter<double_t> showTextColorR{
		showTextColor, 0, 0.0
	};
	
	Json::TJArrayValueGetter<double_t> showTextColorG{
		showTextColor, 1, 0.0
	};
	
	Json::TJArrayValueGetter<double_t> showTextColorB{
		showTextColor, 2, 0.0
	};
	
	Json::TJArrayValueGetter<double_t> showTextColorA{
		showTextColor, 3, 1.0
	};
	
	// fnOnDropFiles
	Json::FJObjectGetter fnOnDropFilesJson{jsonGetter, TEXT("fnOnDropFiles")};
	
	Json::FJObjectGetter fnOnDropFilesErrorText{fnOnDropFilesJson, TEXT("error texts")};
	
	Json::TJObjectValueGetter<TString> fnOnDropFilesErrorMoreFiles{fnOnDropFilesErrorText, TEXT("more files")};
	
	Json::TJObjectValueGetter<TString> fnOnDropFilesErrorOpenFile{fnOnDropFilesErrorText, TEXT("could not open file")};
	
};

class MyProgram : public FProgram
{
public:
	
	MyProgram();
	
	~MyProgram() override;

public:
	
	void ReloadYuanShenWindow();
	
	void InitDirectX();

public:
	
	void Tick() override;

public:
	
	
	void Output(const TString &value)
	{
		static size_t count = 0;
		this->output.push_back(ToTString(++count) + TEXT(": ") + value);
		if (this->output.size() > 20)
			this->output.erase(this->output.begin());
	}
	
	TList<TString> &GetOutput() { return this->output; }

public:
	
	TUniquePtr<DataJsonManagement> data;
	
	TUniquePtr<LanguageJsonManagement> language;

public:
	
	TUniquePtr<class MainWindow> mainWindow;
	
	FTimer timer;
	
	TComPtr<ID2D1Factory1> factory;
	
	TComPtr<IDWriteFactory> writeFactory;
	
	Win32::FWindow yuanShenWindow;

public:
	
	TUniquePtr<Win32::FWindowClass> mainWindowClass;

private:
	
	TList<TString> output;
	
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

public:
	
	///
	/// 创建笔刷
	/// \param color 颜色
	/// \param brush 笔刷
	void SolidColorBrush(const D2D_COLOR_F &color, TComPtr<UUI::Brush> &brush);
	
	///
	/// \param pBitmap 图片
	/// \param brush 笔刷
	void BitmapBrush(ID2D1Bitmap *pBitmap, TComPtr<UUI::Brush> &brush);

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
