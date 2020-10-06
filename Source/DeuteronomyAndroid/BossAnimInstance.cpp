#include "BossAnimInstance.h"


void UBossAnimInstance::BossMovementState(bool move)
{
	moveBoss = move;
}


void UBossAnimInstance::OnDeadState()
{
	bossDead = true;
}

void UBossAnimInstance::NormalComboAttack()
{
	float randomChance = FMath::FRandRange(0, 10);

	if (secondAttackChance < 2)
	{
		if (randomChance < 5)
			normalCombo = true;
		else
		{
			secondAttackChance++;
			secondNormalCombo = true;
		}
	}
	else
	{
		normalCombo = true;
		secondAttackChance = 0;
	}
}

void UBossAnimInstance::HardComboAttack()
{
	hardCombo = true;
}




