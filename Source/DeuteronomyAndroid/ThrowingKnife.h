#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "ThrowingKnife.generated.h"

UCLASS()
class DEUTERONOMYANDROID_API AThrowingKnife : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrowingKnife();

	UPROPERTY(EditAnywhere)
	float speed;
	UPROPERTY(EditAnywhere)
	float deadLimit;
	
	float deadTimer;

	UPROPERTY(BlueprintReadOnly)
	bool forceDead;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void MoveThisKnife(float deltaTimer);
	void CheckLifeTime(float deltaTimer);

};
