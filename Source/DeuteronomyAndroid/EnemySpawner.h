#pragma once

#include "Engine.h"
#include "MyFightEnemy.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	UPROPERTY(EditAnywhere)
	TArray<AMyFightEnemy *> spawnEnemies;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnEnemiesOnScene();
	
	
};
