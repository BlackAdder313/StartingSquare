#include "GameplayTags/TetrongGameplayTags.h"
#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"

FTetrongGameplayTags FTetrongGameplayTags::GameplayTags;

void FTetrongGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FTetrongGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(MenuInput_Confirm,		"MenuInput.Confirm",	"Confirm menu option");
	AddTag(MenuInput_Cancel,		"MenuInput.Cancel",		"Cancel menu option");
	AddTag(GameInput_MoveBlock,		"GameInput.MoveBlock",	"Move block left or right");
	AddTag(GameInput_FallBlock,		"GameInput.FallBlock",  "Push block into falling faster");
	AddTag(GameInput_RotateBoard,	"GameInput.RotateBoard","Rotate board to shuffle blocks.");
}

void FTetrongGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}