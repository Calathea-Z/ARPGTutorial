#pragma once // Ensures the file is only included once during compilation

#include "CoreMinimal.h" // Includes the core minimal set of headers required for Unreal Engine
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h" // Includes the base character class from Unreal Engine
#include "CharacterBase.generated.h" // Generates the necessary code for the CharacterBase class

class UAbilitySystemComponent;
class UAttributeSet;
UCLASS(Abstract) // Declares this class as an abstract class, meaning it cannot be instantiated directly

class AURA_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY() // Macro that generates the boilerplate code needed for Unreal Engine classes

public: 
	ACharacterBase(); // Constructor for the ACharacterBase class
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const {return AttributeSet; }
protected:
	virtual void BeginPlay() override; // Override of the BeginPlay function, which is called when the game starts or when the actor is spawned

	UPROPERTY(EditAnywhere, Category="Combat") // Exposes the Weapon property to the Unreal Editor, allowing it to be edited in the "Combat" category
	TObjectPtr<USkeletalMeshComponent> Weapon; // Pointer to a USkeletalMeshComponent, representing the weapon of the character
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();



	

	// A pointer is a variable that stores the memory address of another variable. 
	// In C++, pointers are used to directly access and manipulate memory, which can be more efficient than copying data.
	// Pointers are declared using the asterisk (*) symbol. For example, 'int* ptr;' declares a pointer to an integer.
	// The address-of operator (&) is used to get the memory address of a variable, while the dereference operator (*) is used to access the value at the memory address stored in a pointer.
	// Pointers are powerful tools in C++ that allow for dynamic memory management, efficient array handling, and the implementation of complex data structures like linked lists and trees.
	// In Unreal Engine, pointers are often used to reference objects and components, allowing for flexible and efficient game development.
};
