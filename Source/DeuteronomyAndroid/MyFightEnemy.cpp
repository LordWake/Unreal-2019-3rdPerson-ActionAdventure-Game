#include "MyFightEnemy.h"

AMyFightEnemy::AMyFightEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyFightEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	canFollow = true;
	isAttackAvailable = true;

	myMesh = FindComponentByClass<USkeletalMeshComponent>();
	if (myMesh)
		anim = Cast<UFightEnemyAnimInstance>(myMesh->GetAnimInstance());	
}

void AMyFightEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isDead || !startTheAttack) return;
		
	CheckCurrentState();
	ChangeState();
	FollowCoolDown(DeltaTime);
	AttackCoolDown(DeltaTime);
}

void AMyFightEnemy::CheckCurrentState()
{
	switch (current)
	{
		case EBehavioursEnemy::Follow:
		FollowPlayer();
		break;

		case  EBehavioursEnemy::AttackPlayer:
		AttackThePlayer();
		break;
	}
}

void AMyFightEnemy::FollowPlayer()
{
	if (!canFollow) return;
	catchPlayer = true;
}

void AMyFightEnemy::AttackThePlayer()
{
	if (onAttack || !isAttackAvailable) return;

	canFollow = false; //Lo pasamos a false para que no entre al followPlayer e inicie el coolDown para volver a seguirlo.
	onAttack = true;
	isAttackAvailable = false;
	
	hardAttackChance++;
	if (hardAttackChance >= 3)
	{
		if (anim)
			anim->HardComboAttack();
		
		hardAttackChance = 0;
	}
	else
	{
		if (anim)
			anim->NormalComboAttack();
	}
}

void AMyFightEnemy::ChangeState()
{
	if (distanceToPlayer <= maxDistanceToGetCloser)
	{
		catchPlayer = false;
		current = EBehavioursEnemy::AttackPlayer;
	}

	else
	{
		current = EBehavioursEnemy::Follow;
	}
}

void AMyFightEnemy::FollowAnimation(bool startFollow)
{
	//Funcion llamada desde el blueprint. Dependiendo en que estado esté el boolean catchPlayer
	//Va a llamar a esta funcion para manejar la animacion de seguimiento.
	if (isDead) return;

	if (startFollow)
	{
		if (anim)
			anim->EnemyMovementState(true);
	}
	else
	{
		if (anim)
			anim->EnemyMovementState(false);
	}

}

void AMyFightEnemy::FollowCoolDown(float deltaTimer)
{
	if (canFollow || onAttack) return; //Si no podemos seguirlo ni estamos en ataque, iniciamos un coolDown para volver a seguir al player.

	followTimer += deltaTimer;
	if (followTimer >= followAgainCoolDown)
	{
		canFollow = true; //canFollow permite que se ejecute la funcion FollowPlayer.
		followTimer = 0;
	}
}

void AMyFightEnemy::TakeDamage(float damageValue)
{
	if (isDead) return;

	damageParticle->Activate(true);

	enemyLife = enemyLife - damageValue;
	
	if (enemyLife <= 0)
		EnemyDead();
	else
	{
		if (!catchPlayer || onAttack) //La animacion de daño solo se ejecuta si no estamos caminando ni atacando. Sin embargo, el daño lo recibe igual. 
		{
			if (anim)
				anim->TakeDamageAnimation(isFront);
		}
	}

}

void AMyFightEnemy::AttackCoolDown(float deltaTimer)
{
	if (isAttackAvailable) return;
	canAttackTimer += deltaTimer;
	if (canAttackTimer >= attackAgainCoolDown)
	{
		isAttackAvailable = true;
		canAttackTimer = 0;
	}
}

void AMyFightEnemy::SetNormalTrigger(bool turn)
{
	if (turn)
		normalTrigger->SetGenerateOverlapEvents(true);
	else
		normalTrigger->SetGenerateOverlapEvents(false);
}

void AMyFightEnemy::SetHardTrigger(bool turn)
{
	if (turn)
		hardTrigger->SetGenerateOverlapEvents(true);
	else
		hardTrigger->SetGenerateOverlapEvents(false);
}

void AMyFightEnemy::EnemyDead()
{
	if (anim)
		anim->OnDeadState();
	
	portalReference->TakePortalDamage();
	isDead = true;
}

