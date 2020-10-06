#pragma once

#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "MagicEnemyAnimInstance.generated.h"


UCLASS()
class DEUTERONOMYANDROID_API UMagicEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	bool onTakeDamage;

	UPROPERTY(BlueprintReadWrite)
	bool attackPlayer;

	UPROPERTY(BlueprintReadOnly)
	bool enemyDead;

	UPROPERTY(BlueprintReadWrite)
	bool enemySpawned;
	
	UPROPERTY(BlueprintReadWrite)
	bool shotPlayer;


	void TakeDamageAnimation();
	void AttackAnimation();
	void ShotAnimation();
	void SpawnAnimation();
	void OnDeadState();
	
	
};
