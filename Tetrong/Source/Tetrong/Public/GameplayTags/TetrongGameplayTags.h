// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

class UGameplayTagsManager;

/**
 * MyGameplayTags
 *
 *	Singleton containing native gameplay tags.
 */
struct FTetrongGameplayTags
{
public:

	static const FTetrongGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	//Input Tags
	FGameplayTag MenuInput_Confirm;
	FGameplayTag MenuInput_Cancel;
	FGameplayTag GameInput_MoveBlock;
	FGameplayTag GameInput_FallBlock;
	FGameplayTag GameInput_RotateBoard;

protected:

	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FTetrongGameplayTags GameplayTags;
};