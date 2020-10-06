#pragma once

#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"


UCLASS()
class DEUTERONOMYANDROID_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite)
	bool underAttack;
	UPROPERTY(BlueprintReadWrite)
	bool attackPlayer;
	UPROPERTY(BlueprintReadOnly)
	bool enemyDead;

	void TakeDamageAnimation();
	void AttackAnimation();
	void OnDeadState();
};
