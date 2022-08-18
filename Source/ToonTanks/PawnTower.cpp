// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTower.h"

#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

APawnTower::APawnTower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APawnTower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTower::CheckFireCondition, FireRate, true);
}

void APawnTower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bTankInFireRange())
	{
		LookAtTarget(Tank->GetActorLocation());
	}
}

bool APawnTower::bTankInFireRange() const
{
	return GetDistanceFromTank() < FireRange;
}

float APawnTower::GetDistanceFromTank() const
{
	if (Tank)
	{
		return (Tank->GetActorLocation() - GetActorLocation()).Length();
	}
	return TNumericLimits<float>::Max();
}

void APawnTower::CheckFireCondition()
{
	if(bTankInFireRange())
	{
		Fire();
	}
}
