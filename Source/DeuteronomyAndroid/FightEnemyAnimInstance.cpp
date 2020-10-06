#include "FightEnemyAnimInstance.h"
#include "MyFightEnemy.h"

void UFightEnemyAnimInstance::EnemyMovementState(bool move)
{
	moveEnemy = move;
}

void UFightEnemyAnimInstance::TakeDamageAnimation(bool front)
{
	if (front)
		frontAttack = true;
	else
		backAttack = true;
}

void UFightEnemyAnimInstance::OnDeadState()
{
	enemyDead = true;
}

void UFightEnemyAnimInstance::NormalComboAttack()
{
	normalCombo = true;
}

void UFightEnemyAnimInstance::HardComboAttack()
{
	hardCombo = true;
}




