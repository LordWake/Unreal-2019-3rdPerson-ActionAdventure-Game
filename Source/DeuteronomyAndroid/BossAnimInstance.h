#pragma once

#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"


UCLASS()
class DEUTERONOMYANDROID_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

	float secondAttackChance;

	UPROPERTY(BlueprintReadWrite)
	bool moveBoss;
	UPROPERTY(BlueprintReadOnly)
	bool bossDead;
	UPROPERTY(BlueprintReadWrite)
	bool normalCombo;
	UPROPERTY(BlueprintReadWrite)
	bool secondNormalCombo;
	UPROPERTY(BlueprintReadWrite)
	bool hardCombo;

	void BossMovementState(bool move);
	void OnDeadState();
	void NormalComboAttack();
	void HardComboAttack();
	
	
};
