#pragma once

#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "FightEnemyAnimInstance.generated.h"


UCLASS()
class DEUTERONOMYANDROID_API UFightEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public: 

	UPROPERTY(BlueprintReadWrite)
	bool moveEnemy;
	UPROPERTY(BlueprintReadWrite)
	bool frontAttack;
	UPROPERTY(BlueprintReadWrite)
	bool backAttack;
	UPROPERTY(BlueprintReadOnly)
	bool enemyDead;
	UPROPERTY(BlueprintReadWrite)
	bool normalCombo;
	UPROPERTY(BlueprintReadWrite)
	bool hardCombo;

	void EnemyMovementState(bool move);
	void TakeDamageAnimation(bool front);
	void OnDeadState();	
	void NormalComboAttack();
	void HardComboAttack();
	
};
