#include "MagicBall.h"



AMagicBall::AMagicBall()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMagicBall::BeginPlay()
{
	Super::BeginPlay();	
}

void AMagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisMagicBall(DeltaTime);
	CheckLifeTime(DeltaTime);
}

void AMagicBall::MoveThisMagicBall(float deltaTimer)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * deltaTimer);
}

void AMagicBall::CheckLifeTime(float deltaTimer)
{
	deadTimer += deltaTimer;
	if (deadTimer >= deadLimit)
		forceDead = true;
}

