#include "TestEditor.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Modules/ModuleManager.h"
#include <IContentBrowserSingleton.h>
#include <ContentBrowserModule.h>

IMPLEMENT_MODULE(FTestEditor, TestEditor)

void FTestEditor::StartupModule()
{
    // 메뉴 확장자 생성
    TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

    // 메뉴 확장 바인딩
    MenuExtender->AddMenuBarExtension(
        // 붙일 메뉴 위치(창 메뉴를 기준)
        "Window",
        // 위치 기준
        EExtensionHook::After,
        // 커맨드 리스트 (없으면 nullptr)
        nullptr,
        // 생성된 이후 호출될 델리게이트
        FMenuBarExtensionDelegate::CreateRaw(this, &FTestEditor::AddMenuBarEntry)
    );

    // 레벨 에디터 모듈 참조
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

    // 레벨 에디터에 메뉴 확장자 등록
    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);


    // 툴바 확장자 생성
    TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

    // "Content" 툴바 섹션 뒤에 버튼 추가
    ToolbarExtender->AddToolBarExtension(
        // 기준 섹션 (콘텐츠 버튼 뒤)
        "Content",                    
        // 그 뒤에
        EExtensionHook::After,       
        // 명령 목록
        nullptr,                 
        // 생성된 이후 호출될 델리게이트
        FToolBarExtensionDelegate::CreateRaw(this, &FTestEditor::AddToolbarButton)
    );

    // 툴바 확장 등록
    LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
}

void FTestEditor::AddToolbarButton(FToolBarBuilder& ToolbarBuilder)
{
    ToolbarBuilder.AddToolBarButton(
        FUIAction(
            FExecuteAction::CreateLambda([]()
                {
                    // 버튼 눌렀을 때 동작
                    UE_LOG(LogTemp, Log, TEXT("툴바 버튼 클릭됨!"));
                })
        ),
        FName(TEXT("MyButton")),
        FText::FromString(TEXT("My Button")),
        FText::FromString(TEXT("Tool tip")),
        FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.GameSettings") // 예시 아이콘
    );

    ToolbarBuilder.AddToolBarButton(
        FUIAction(FExecuteAction::CreateRaw(this, &FTestEditor::OpenAssetPickerWindow)),
        NAME_None,
        INVTEXT("Asset Picker"),
        INVTEXT("Open Slate Asset Picker"),
        FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.GameSettings")
    );
}

void FTestEditor::AddMenuBarEntry(FMenuBarBuilder& MenuBarBuilder)
{
    MenuBarBuilder.AddPullDownMenu(
        // 드롭다운 메뉴 이름
        FText::FromString("MyDropdown"),                                    
        // 툴팁
        FText::FromString("Open My Dropdown"),                              
        // 생성후 호출될 델리게이트
        FNewMenuDelegate::CreateRaw(this, &FTestEditor::FillPulldownMenu),
        // 메뉴 hook (id)
        FName(TEXT("MyDropdown"))
    );
}

void FTestEditor::FillPulldownMenu(FMenuBuilder& MenuBuilder)
{
    MenuBuilder.AddMenuEntry(
        // 메뉴 이름
        FText::FromString("Option 1"),
        // 툴팁
        FText::FromString("Do something 1"),
        // 아이콘
        FSlateIcon(),
        // 클릭후 실행될 Action
        FUIAction(
            //FExecuteAction = 델리게이트
            FExecuteAction::CreateLambda([this]()
                {
                    UE_LOG(LogTemp, Log, TEXT("Option 1 clicked Lambda!"));
                })
        )
    );

    MenuBuilder.AddMenuEntry(
        FText::FromString("Option 2"),
        FText::FromString("Do something 2"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &FTestEditor::OnClickMenuFun))
    );
}

void FTestEditor::OnClickMenuFun()
{
    UE_LOG(LogTemp, Warning, TEXT("FTestEditor::OnClickMenuFun"));
}

void FTestEditor::OpenAssetPickerWindow()
{
    if (PickerWindow.IsValid())
    {
        PickerWindow->BringToFront();
        return;
    }

    FAssetPickerConfig AssetPickerConfig;
    // StaticMesh만 필터링
    AssetPickerConfig.Filter.ClassNames.Add(UStaticMesh::StaticClass()->GetFName());
    // 상속 구조 포함 여부
    AssetPickerConfig.Filter.bRecursiveClasses = true;
    // 에셋 선택 모드 설정
    AssetPickerConfig.SelectionMode = ESelectionMode::Single;
    // 에셋 선택 후 호출될 델리게이트 설정
    AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateLambda([this](const FAssetData& SelectedAsset)
        {
            // 로그 출력
            UE_LOG(LogTemp, Log, TEXT("선택된 자산: %s"), *SelectedAsset.GetFullName());

            // Content Browser를 선택된 에셋이 들어있는 폴더로 이동/동기화
            FContentBrowserModule& CBModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
            TArray<FAssetData> AssetsToSync;
            AssetsToSync.Add(SelectedAsset);
            CBModule.Get().SyncBrowserToAssets(AssetsToSync, true);
        });
    AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;

    // Asset Picker 위젯 생성
    FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
    TSharedRef<SWidget> AssetPickerWidget = ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig);

    // 창 만들기
    PickerWindow = SNew(SWindow)
        .Title(INVTEXT("Slate Asset Picker"))
        .ClientSize(FVector2D(600, 400))
        .SupportsMinimize(false)
        .SupportsMaximize(false)
        [
            SNew(SBorder)
                .Padding(8)
                [
                    SNew(SVerticalBox)
                        + SVerticalBox::Slot()
                        .AutoHeight()
                        .Padding(0, 0, 0, 4)
                        [
                            SNew(STextBlock)
                                .Text(INVTEXT("Static Mesh 선택:"))
                                .Font(FCoreStyle::GetDefaultFontStyle("Regular", 14))
                        ]
                        + SVerticalBox::Slot()
                        .FillHeight(1.0f)
                        [
                            AssetPickerWidget
                        ]
                ]
        ];

    FSlateApplication::Get().AddWindow(PickerWindow.ToSharedRef());
}

void FTestEditor::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("FTestEditor::ShutdownModule"));
}
