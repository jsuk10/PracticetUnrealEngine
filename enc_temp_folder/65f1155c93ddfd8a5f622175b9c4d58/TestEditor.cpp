#include "TestEditor.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Modules/ModuleManager.h"

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
        "MyDropdown"                                                        
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

void FTestEditor::ShutdownModule()
{
    UE_LOG(LogTemp, Warning, TEXT("FTestEditor::ShutdownModule"));
}
