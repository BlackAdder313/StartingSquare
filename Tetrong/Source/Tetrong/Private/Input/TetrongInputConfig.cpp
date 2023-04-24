#include "Input/TetrongInputConfig.h"
#include "GameplayTagContainer.h"
#include "Components\Input\TetrongEnhancedInputComponent.h"

const UInputAction* UInputConfig::FindInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FTaggedInputAction& TaggedInputAction : TaggedInputActions)
	{
		if (TaggedInputAction.InputAction && TaggedInputAction.InputTag == InputTag)
		{
			return TaggedInputAction.InputAction;
		}
	}

	return nullptr;
}