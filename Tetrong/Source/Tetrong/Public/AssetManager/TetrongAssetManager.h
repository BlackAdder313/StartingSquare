#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TetrongAssetManager.generated.h"

/**
 *
 */
UCLASS()
class TETRONG_API UTetrongAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	UTetrongAssetManager();

	// Returns the AssetManager singleton object.
	static UTetrongAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};