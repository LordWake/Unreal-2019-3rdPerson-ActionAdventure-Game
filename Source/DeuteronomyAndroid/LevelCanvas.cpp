#include "LevelCanvas.h"

void ALevelCanvas::BeginPlay() 
{
	Super::BeginPlay();
	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);

	if (canvas)
	{
		canvas->AddToViewport();
		canvas->playerHUDLife = 1;
		canvas->powerHUD = 1;
	}
}

void ALevelCanvas::UpdatePlayerLife(float life)
{
	if (canvas)
		canvas->playerHUDLife = life;
}

void ALevelCanvas::UpdatePlayerPower(float power)
{
	if (canvas)
		canvas->powerHUD = power;
}


void ALevelCanvas::PlayerGameOver(int gameOverLevel)
{
	switch (gameOverLevel)
	{
	case 1:
		if (canvas)
			canvas->onGameOver = true;
		break;

	case 2:
		if (canvas)
			canvas->onGameOverTwo = true;
		break;

	case 3:
		if (canvas)
			canvas->onGameOverThree = true;
		break;
	}

}

void ALevelCanvas::LoadNextLevel(int level)
{
	switch (level)
	{
	case 1:
		if (canvas)
			canvas->levelTwo = true;
		break;

	case 2:
		if (canvas)
			canvas->levelThree = true;
		break;

	case  3:
		if (canvas)
			canvas->victoryLevel = true;
		break;
	}
}

void ALevelCanvas::HideCanvas(bool hide)
{
	if (hide)
		canvas->hideCanvasForCinematic = true;
	else
		canvas->hideCanvasForCinematic = false;
}




