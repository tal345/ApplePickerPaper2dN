// Copyright Epic Games, Inc. All Rights Reserved.

#include "ApplePickerPaper2dNGameMode.h"
#include "ApplePickerPaper2dNCharacter.h"

AApplePickerPaper2dNGameMode::AApplePickerPaper2dNGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AApplePickerPaper2dNCharacter::StaticClass();	
}
