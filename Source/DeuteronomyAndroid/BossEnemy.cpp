
#include "BossEnemy.h"

ABossEnemy::ABossEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();

	canFollow = true;
	isAttackAvailable = true;

	myMesh = FindComponentByClass<USkeletalMeshComponent>();
	if (myMesh)
		anim = Cast<UBossAnimInstance>(myMesh->GetAnimInstance());
	
}

void ABossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	StartAttack();
	if (!startTheAttack || isDead) return;
	CheckCurrentState();
	ChangeState();
	FollowCoolDown(DeltaTime);
	AttackCoolDown(DeltaTime);
}

void ABossEnemy::StartAttack()
{
	if (distanceToPlayer < 500)
		startTheAttack = true;
}

void ABossEnemy::CheckCurrentState()
{
	switch (current)
	{
		case EBehavioursBoss::Follow:
		FollowPlayer();
		break;

		case  EBehavioursBoss::AttackPlayer:
		AttackThePlayer();
		break;
	}
}

void ABossEnemy::ChangeState()
{
	if (distanceToPlayer <= maxDistanceToGetCloser)
	{
		catchPlayer = false;
		current = EBehavioursBoss::AttackPlayer;
	}
	else
	{
		current = EBehavioursBoss::Follow;
	}
}

void ABossEnemy::FollowPlayer()
{
	if (!canFollow) return;
	catchPlayer = true;
}

void ABossEnemy::AttackThePlayer()
{
	if (onAttack || !isAttackAvailable) return;
	canFollow = false;
	onAttack = true;
	isAttackAvailable = false;

	float randomChance = FMath::FRandRange(0, 10);
	if (randomChance <= 6)
	{
		if (anim)
			anim->NormalComboAttack();
	}
	else
	{
		if (anim)
			anim->HardComboAttack();
	}
}

void ABossEnemy::SetNormalTrigger(bool turn)
{
	if (turn)
		normalTrigger->SetGenerateOverlapEvents(true);
	else
		normalTrigger->SetGenerateOverlapEvents(false);
}

void ABossEnemy::SetHardTrigger(bool turn)
{
	if (turn)
		hardTrigger->SetGenerateOverlapEvents(true);
	else
		hardTrigger->SetGenerateOverlapEvents(false);
}

void ABossEnemy::AttackRocksFX()
{
	rockParticle->Activate(true);
}

void ABossEnemy::FollowCoolDown(float deltaTimer)
{
	if (canFollow || onAttack) return;
	followTimer += deltaTimer;
	
	if (followTimer >= followAgainCoolDown)
	{
		canFollow = true;
		followTimer = 0;
	}
	
}

void ABossEnemy::AttackCoolDown(float deltaTimer)
{
	if (isAttackAvailable) return;
	canAttackTimer += deltaTimer;
	if (canAttackTimer >= attackAgainCoolDown)
	{
		isAttackAvailable = true;
		canAttackTimer = 0;
	}
}

void ABossEnemy::FollowAnimation(bool startFollow)
{
	if (isDead) return;

	if (startFollow)
	{
		if (anim)
			anim->BossMovementState(true);
	}
	else
	{
		if (anim)
			anim->BossMovementState(false);
	}
}

void ABossEnemy::TakeDamage(float damageValue)
{
	if (isDead)return;

	damageParticle->Activate(true);
	enemyLife = enemyLife - damageValue;

	if (enemyLife <= 0)
		BossDead();
}

void ABossEnemy::BossDead()
{
	if (anim)
		anim->OnDeadState();

	portalReference->TakePortalDamage();
	isDead = true;
}


