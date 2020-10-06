#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();	
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawner::SpawnEnemiesOnScene()
{
	for (int i=0; i < spawnEnemies.Num(); i++)
	{
		auto currentEnemy = Cast<AMyFightEnemy>(spawnEnemies[i]);
		currentEnemy->startTheAttack = true;
	}
}
