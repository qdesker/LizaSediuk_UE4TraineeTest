// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeadDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChangedDelegate);

class UDamageDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLEDEFENDER_API UCharacterHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	float GetCurrentHealthValue() const { return CurrentHealth; }

	float GetInitialHealthValue() const { return InitialHealth; }

	virtual void OnDamageReceived(float Damage, const FName& HitInBone);

	void AddHealth(float ValueToAdd);

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return CurrentHealth <= 0.0f; }

	UPROPERTY(BlueprintAssignable)
	FOnDeadDelegate OnDeadDelegate;

	FOnHealthChangedDelegate OnHealthChanged;

protected:

	virtual void BeginPlay() override;

	virtual void OnDead();

private:

	float CurrentHealth = 0.0f;

	UPROPERTY(EditAnywhere)
	float InitialHealth = 100.0f;

	UPROPERTY(EditAnywhere)
	UDamageDataAsset* DamageDatabase;
};
