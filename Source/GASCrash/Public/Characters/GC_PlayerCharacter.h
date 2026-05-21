// Copyright Jakub Kaczor

#pragma once

#include "CoreMinimal.h"
#include "GC_BaseCharacter.h"
#include "GC_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GASCRASH_API AGC_PlayerCharacter : public AGC_BaseCharacter
{
	GENERATED_BODY()

public:
	AGC_PlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
