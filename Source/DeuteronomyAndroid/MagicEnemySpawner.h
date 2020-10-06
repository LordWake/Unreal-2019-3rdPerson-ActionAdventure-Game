#pragma once

#include "Engine.h"
#include "MagicEnemy.h"
#include "GameFramework/Actor.h"
#include "MagicEnemySpawner.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API AMagicEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicEnemySpawner();

	UPROPERTY(EditAnywhere)
		AMagicEnemy* magicEnemyPrefab;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* blockWall;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* blockWallTwo;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SpawnMagicEnemy();

	
	
};
