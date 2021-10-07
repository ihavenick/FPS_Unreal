// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DenemeProjeHUD.generated.h"

UCLASS()
class ADenemeProjeHUD : public AHUD
{
	GENERATED_BODY()

public:
	ADenemeProjeHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

