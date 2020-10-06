#include "MyCharacter.h"


AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	onCinematic = true;
	canAttack = true;
	canMove = true;
	life = maxLife;
	powerAmount = maxPowerAmount;

	myMesh = FindComponentByClass<USkeletalMeshComponent>();
    myMesh->SetVisibility(false);
	cameraHandler = FindComponentByClass<USpringArmComponent>();
	
	if (myMesh)
		anim = Cast<UPlayerAnimInstance>(myMesh->GetAnimInstance());

	if (normalTrigger)
		normalTrigger->SetGenerateOverlapEvents(false);
	if (hardTrigger)
		hardTrigger->SetGenerateOverlapEvents(false);
	
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (playerIsDead || onCinematic) return;
	MovePlayerAnimation(movementDirection);
	CameraZoom();
	ReleaseCameraZoom();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (playerIsDead || onCinematic) return;
	PlayerInputComponent->BindAction("LB", IE_Pressed, this, &AMyCharacter::BlockAttacks);
	PlayerInputComponent->BindAction("LB", IE_Released, this, &AMyCharacter::UnblockAttacks);
	PlayerInputComponent->BindAction("X", IE_Pressed, this, &AMyCharacter::NormalAttackCombo);
	PlayerInputComponent->BindAction("Y", IE_Pressed, this, &AMyCharacter::HardAttackCombo);
	PlayerInputComponent->BindAction("B", IE_Pressed, this, &AMyCharacter::SpecialAttack);
}

void AMyCharacter::MovePlayerAnimation(FVector2D myDirection)
{
	if (anim)
		anim->SetDirectionPlayer(movementDirection);	
}

void AMyCharacter::BlockAttacks()
{
	if (!canAttack) return;

	onBlockState = true;
	doZoom = true;
	startTheCameraZoom = true;
	
	if (anim)
		anim->SetBlock(onBlockState);
}

void AMyCharacter::UnblockAttacks()
{
	onBlockState = false;
	doZoom = false;
	startTheCameraZoom = true;

	if (anim)
		anim->SetBlock(onBlockState);
}

void AMyCharacter::NormalAttackCombo()
{
	if (!canAttack || onDamage) return;

	outOfCombat = false;
	doZoom = true;
	startTheCameraZoom = true;

	switch (normalAttackCount)
	{
		case 0:
			if(anim)
				anim->SetNormalAttack(normalAttackCount);

			normalAttackCount++;
			canAttack = false;
		break;

		case 1:
			if(anim)
				anim->SetNormalAttack(normalAttackCount);

			normalAttackCount++;
			canAttack = false;
		break;

		case 2:
			if(anim)
				anim->SetNormalAttack(normalAttackCount);

			normalAttackCount++;
			canAttack = false;
		break;

		case 3:
			if(anim)
				anim->SetNormalAttack(normalAttackCount);

			normalAttackCount = 0;
			canAttack = false;
		break;
	}
}

void AMyCharacter::HardAttackCombo()
{
	if (!canAttack || onDamage) return;

	outOfCombat = false;
	doZoom = true;
	startTheCameraZoom = true;

	switch (hardAttackCount)
	{
		case 0:
			canMove = false;
			if (anim)
				anim->SetHardAttack(hardAttackCount);

		hardAttackCount++;
		canAttack = false;
		break;

		case 1:
			canMove = false;
			if (anim)
				anim->SetHardAttack(hardAttackCount);

			hardAttackCount++;
			canAttack = false;
		break;

		case 2:
			canMove = false;
			if (anim)
				anim->SetHardAttack(hardAttackCount);

			hardAttackCount++;
			canAttack = false;
		break;

		case 3:
			canMove = false;
			if (anim)
				anim->SetHardAttack(hardAttackCount);

			hardAttackCount = 0;
			canAttack = false;
		break;
	}
}

void AMyCharacter::SpecialAttack()
{
	if (powerAmount < maxPowerAmount || !canAttack || onDamage) return;

	outOfCombat = false;
	doZoom = true;
	startTheCameraZoom = true;
	canAttack = false;
	powerAmount = 0;

	if (anim)
		anim->SetSpecialAttack();

	UpdateHUDPower();
}

#pragma region Camera Zoom
void AMyCharacter::CameraZoom()
{
	if (!startTheCameraZoom) return;

	if (doZoom)
	{
		if (cameraHandler->TargetArmLength < maxCamZoom)
			cameraHandler->TargetArmLength += (GetWorld()->GetDeltaSeconds() * zoomCameraSpeed);
		else
			startTheCameraZoom = false;

	}
	else
	{
		if (cameraHandler->TargetArmLength > minCamZoom)
			cameraHandler->TargetArmLength -= (GetWorld()->GetDeltaSeconds() * zoomCameraSpeed * 2);
		else
			startTheCameraZoom = false;

	}
}

void AMyCharacter::ReleaseCameraZoom()
{
	if (outOfCombat)
	{
		timerZoomCombat += GetWorld()->GetDeltaSeconds();
		if (timerZoomCombat >= 2.5f)
		{
			doZoom = false;
			startTheCameraZoom = true;
			outOfCombat = false;
		}
	}
	else
		timerZoomCombat = 0;
}

#pragma endregion 

#pragma region AttackTriggers

void AMyCharacter::NormalTriggerOn()
{
	normalTrigger->SetGenerateOverlapEvents(true);
}

void AMyCharacter::NormalTriggerOff()
{
	normalTrigger->SetGenerateOverlapEvents(false);
}

void AMyCharacter::HardTriggerOn()
{
	hardTrigger->SetGenerateOverlapEvents(true);
}

void AMyCharacter::HardTriggerOff()
{
	hardTrigger->SetGenerateOverlapEvents(false);
}

void AMyCharacter::SpecialTriggerSwitch(bool turn)
{
	if(turn)
		specialTrigger->SetGenerateOverlapEvents(true);
	else
		specialTrigger->SetGenerateOverlapEvents(false);
}
#pragma endregion 

void AMyCharacter::NormalTakeDamage(float damageValue)
{
	if (playerIsDead) return;
	
	if (onBlockState)
	{
		blockAudio->Play();
		return;
	}

	onDamage = true;
	damageParticle->Activate(true);
	life = life - damageValue;
	UpdateHUDLife();

	if (life <= 0)
		PlayerDead();
	else
	{
		if (anim)
			anim->SetPlayerTakeDamage();
	}
}

void AMyCharacter::HardTakeDamage(float damageValue)
{
	if (playerIsDead) return;

	onDamage = true;
	hardDamageParticle->Activate(true);
	life = life - damageValue;
	UpdateHUDLife();

	if (life <= 0)
		PlayerDead();
	else
	{
		if (anim)
			anim->SetPlayerTakeDamage();
	}

}

void AMyCharacter::TakePower(float powerValue)
{
	if (powerAmount < maxPowerAmount)
	{
		powerAmount += powerValue;
		UpdateHUDPower();
	}
}

void AMyCharacter::TakePowerDamage(float damageValue)
{
	powerAmount = powerAmount - damageValue;
	if (powerAmount <= 0)
		powerAmount = 0;

	UpdateHUDPower();

	if (anim)
		anim->SetPlayerTakeDamage();
}

void AMyCharacter::UpdateHUDLife()
{
	auto lifeCanvas = Cast<ALevelCanvas>(GetWorld()->GetFirstPlayerController());
	float lifeValue = life / maxLife;
	if (lifeCanvas)
		lifeCanvas->UpdatePlayerLife(lifeValue);
}

void AMyCharacter::UpdateHUDPower()
{
	float powerPercent = powerAmount / maxPowerAmount;
	
	auto myCanvas = Cast<ALevelCanvas>(GetWorld()->GetFirstPlayerController());
	if (myCanvas)
		myCanvas->UpdatePlayerPower(powerPercent);
}

void AMyCharacter::PlayerDead()
{
	playerIsDead = true;
	cameraHandler->TargetArmLength = maxCamZoom;

	if (anim)
		anim->SetPlayerDead();
}

void AMyCharacter::NotifyGameOver()
{
	auto myCanvas = Cast<ALevelCanvas>(GetWorld()->GetFirstPlayerController());
	if (myCanvas)
		myCanvas->PlayerGameOver(currentLevelChecker);
}

void AMyCharacter::NotifyCinematicFinish()
{
	myMesh->SetVisibility(true);
	onCinematic = false;
}

void AMyCharacter::NotifyCinematicStart()
{
	myMesh->SetVisibility(false);
	onCinematic = true;
}

