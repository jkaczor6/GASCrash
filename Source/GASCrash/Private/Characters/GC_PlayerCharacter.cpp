// Copyright Jakub Kaczor


#include "GASCrash/Public/Characters/GC_PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GC_AttributeSet.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/GC_PlayerState.h"

AGC_PlayerCharacter::AGC_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	Tags.Add(GASTags::Player);
}

UAbilitySystemComponent* AGC_PlayerCharacter::GetAbilitySystemComponent() const
{
	AGC_PlayerState* GCPlayerState{ Cast<AGC_PlayerState>(GetPlayerState()) };
	if (!IsValid(GCPlayerState)) return nullptr;
	
	return GCPlayerState->GetAbilitySystemComponent();
}

void AGC_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!IsValid(GetAbilitySystemComponent()) || !HasAuthority()) return;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	GiveStartupAbilities();
	InitializeAttributes();
	
	
	UGC_AttributeSet* GC_AS = Cast<UGC_AttributeSet>(GetAttributeSet());
	if (!IsValid(GC_AS)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GC_AS->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void AGC_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	UGC_AttributeSet* GC_AS = Cast<UGC_AttributeSet>(GetAttributeSet());
	if (!IsValid(GC_AS)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GC_AS->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

UAttributeSet* AGC_PlayerCharacter::GetAttributeSet() const
{
	AGC_PlayerState* GCPlayerState{ Cast<AGC_PlayerState>(GetPlayerState()) };
	if (!IsValid(GCPlayerState)) return nullptr;
	
	return GCPlayerState->GetAttributeSet();
}

