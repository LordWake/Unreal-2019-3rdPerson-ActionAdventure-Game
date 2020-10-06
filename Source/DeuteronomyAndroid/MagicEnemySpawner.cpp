#include "MagicEnemySpawner.h"

AMagicEnemySpawner::AMagicEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMagicEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMagicEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagicEnemySpawner::SpawnMagicEnemy()
{
	auto currentEnemy = Cast<AMagicEnemy>(magicEnemyPrefab);
	currentEnemy->startTheAttack = true;
}

