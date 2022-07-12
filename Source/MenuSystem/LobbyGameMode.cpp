// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState) // player array를 갖고 있음
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1, 
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers)
			);

			APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
			if (PlayerState)
			{
				FString PlayerName = PlayerState->GetPlayerName();

				GEngine->AddOnScreenDebugMessage(
					2, 
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT("%s has joined the game!"), *PlayerName)
				);
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		FString PlayerName = PlayerState->GetPlayerName();

		GEngine->AddOnScreenDebugMessage(
			1, 
			60.f,
			FColor::Cyan,
			FString::Printf(TEXT("%s has exited the game!"), *PlayerName)
		);

		GEngine->AddOnScreenDebugMessage(
			2, 
			60.f,
			FColor::Yellow,
			FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers - 1)
		);
	}
}
