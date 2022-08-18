// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PawnTower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTower : public ABasePawn
{
	GENERATED_BODY()

public:
	APawnTower();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float FireRange = 1000.f;

	bool bTankInFireRange() const;
	float GetDistanceFromTank() const;
	void CheckFireCondition();
	
	class APawnTank* Tank;
	float FireRate = 2.f;
	FTimerHandle FireRateTimerHandle;
};
