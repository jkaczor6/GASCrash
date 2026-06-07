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
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|AI")
	float AcceptanceRadius{ 500.f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|AI")
	float MinAttackDelay{ .1f };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|AI")
	float MaxAttackDelay{ .5f };
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "GAS|AI")
	bool bIsBeingLaunched{ false };
	
	void StopMovementUntilLanded();
protected:
	virtual void BeginPlay() override;

	virtual void HandleDeath() override;
private:
	
	UFUNCTION()
	void EnableMovementOnLanded(const FHitResult& Hit);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

};
