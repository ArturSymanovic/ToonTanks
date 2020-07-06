// Copyright Artur Symanovic 2020


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
	// Get references and game win/lose conditions

	// Call HandleGameStart to initialise the start countdown, turret activation, pawn check etc...
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of actor died. If turret tally. If player go to lose condition.
}

void ATankGameModeBase::HandleGamestart()
{
	// Initialise the start countdown, turret activation, pawn check etc...
	//Call blueprint version GameStart()
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	//See if the player has destroyed all turrets, show win result.
	//else if turret destroyed the player, show lose result.
	//Call Blueprint version of GameOver()
}
