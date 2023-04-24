#include "AssetManager/TetrongAssetManager.h"
#include "GameplayTags/TetrongGameplayTags.h"

UTetrongAssetManager::UTetrongAssetManager()
{

}

UTetrongAssetManager& UTetrongAssetManager::Get()
{
	check(GEngine);

	UTetrongAssetManager* MyAssetManager = Cast<UTetrongAssetManager>(GEngine->AssetManager);
	return *MyAssetManager;
}

void UTetrongAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//Load Native Tags
	FTetrongGameplayTags::InitializeNativeTags();
}