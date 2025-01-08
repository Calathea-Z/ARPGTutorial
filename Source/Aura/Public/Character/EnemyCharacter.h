// Copyright Calathea Games

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AEnemyCharacter : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

	// Enemy Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	// End Enemy Interface

	//Combat Interface
	virtual int32 GetPlayerLevel() override;
	//End Combat Interface

	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

protected:
	virtual void BeginPlay() override;
	
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1 ;
};
