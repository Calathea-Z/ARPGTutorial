// Copyright Calathea Games

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * APlayerCharacter is a specialized character class derived from ACharacterBase.
 * It represents the player-controlled character in the game, and provides functionality
 * for possession and player state replication, as well as initializing ability-related actor information.
 */
UCLASS()
class AURA_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	virtual void InitAbilityActorInfo() override;
};
