// Copyright Jakub Kaczor


#include "GASCrash/Public/Characters/GC_BaseCharacter.h"

AGC_BaseCharacter::AGC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}