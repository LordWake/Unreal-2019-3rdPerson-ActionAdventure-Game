#pragma once

#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


UCLASS()
class DEUTERONOMYANDROID_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite)
	float playerHUDLife;
	UPROPERTY(BlueprintReadWrite)
	float powerHUD;

	UPROPERTY(BlueprintReadOnly)
	bool onGameOver;
	UPROPERTY(BlueprintReadOnly)
	bool onGameOverTwo;
	UPROPERTY(BlueprintReadOnly)
	bool onGameOverThree;
	UPROPERTY(BlueprintReadWrite)
	bool goToMenu;
	UPROPERTY(BlueprintReadWrite)
	bool retryFirstLevel;
	UPROPERTY(BlueprintReadWrite)
	bool retrySecondLevel;
	UPROPERTY(BlueprintReadWrite)
	bool retryThirdLevel;
	UPROPERTY(BlueprintReadOnly)
	bool levelTwo;
	UPROPERTY(BlueprintReadOnly)
	bool levelThree;
	UPROPERTY(BlueprintReadOnly)
	bool victoryLevel;
	UPROPERTY(BlueprintReadWrite)
	bool hideCanvasForCinematic;
};
