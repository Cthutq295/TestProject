// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestProjectGameMode.h"

#include "Player/BaseCharacter.h"
#include "Player/UI/PlayerHUD.h"


ATestProjectGameMode::ATestProjectGameMode()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
	HUDClass = APlayerHUD::StaticClass();
}
