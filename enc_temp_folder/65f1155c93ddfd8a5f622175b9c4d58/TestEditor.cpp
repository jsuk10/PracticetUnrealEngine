#include "TestEditor.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_MODULE(FTestEditor, TestEditor)

void FTestEditor::StartupModule()
{
    // �޴� Ȯ���� ����
    TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());

    // �޴� Ȯ�� ���ε�
    MenuExtender->AddMenuBarExtension(
        // ���� �޴� ��ġ(â �޴��� ����)
        "Window",
        // ��ġ ����
        EExtensionHook::After,
        // Ŀ�ǵ� ����Ʈ (������ nullptr)
        nullptr,
        // ������ ���� ȣ��� ��������Ʈ
        FMenuBarExtensionDelegate::CreateRaw(this, &FTestEditor::AddMenuBarEntry)
    );

    // ���� ������ ��� ����
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

    // ���� �����Ϳ� �޴� Ȯ���� ���
    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FTestEditor::AddMenuBarEntry(FMenuBarBuilder& MenuBarBuilder)
{
    MenuBarBuilder.AddPullDownMenu(
        // ��Ӵٿ� �޴� �̸�
        FText::FromString("MyDropdown"),                                    
        // ����
        FText::FromString("Open My Dropdown"),                              
        // ������ ȣ��� ��������Ʈ
        FNewMenuDelegate::CreateRaw(this, &FTestEditor::FillPulldownMenu),
        // �޴� hook (id)
        "MyDropdown"                                                        
    );
}

void FTestEditor::FillPulldownMenu(FMenuBuilder& MenuBuilder)
{
    MenuBuilder.AddMenuEntry(
        // �޴� �̸�
        FText::FromString("Option 1"),
        // ����
        FText::FromString("Do something 1"),
        // ������
        FSlateIcon(),
        // Ŭ���� ����� Action
        FUIAction(
            //FExecuteAction = ��������Ʈ
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
