// Copyright Artur Symanovic 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class ATankGameModeBase;
class UDamageType;
class AController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(
		AActor* DamageActor, 
		float Damage, 
		const UDamageType* DamageType, 
		AController* InstigatedBy, 
		AActor* DamageCauser
	);
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float DefaultHealth = 100.0f;
	float Health = 0.0f;
	

	AActor* Owner;
	ATankGameModeBase* GameModeRef;
};
