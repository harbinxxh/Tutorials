// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "TutorialsGameModeBase.h"

#include "TutorialsPlayerController.h"


ATutorialsGameModeBase::ATutorialsGameModeBase()
	:Super()
{
	PlayerControllerClass = ATutorialsPlayerController::StaticClass();
}
