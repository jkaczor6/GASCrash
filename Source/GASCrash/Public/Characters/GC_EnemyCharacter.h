// Copyright Jakub Kaczor

#pragma once

#include "CoreMinimal.h"
#include "GC_BaseCharacter.h"
#include "GC_EnemyCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class GASCRASH_API AGC_EnemyCharacter : public AGC_BaseCharacter
{
	GENERATED_BODY()

public:
	AGC_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
