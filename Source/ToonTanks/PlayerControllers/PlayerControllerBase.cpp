// Copyright Artur Symanovic 2020


#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
		APlayerControllerBase::bShowMouseCursor = true;
	}
	else
	{
		GetPawn()->DisableInput(this);
		APlayerControllerBase::bShowMouseCursor = false;
	}
}
