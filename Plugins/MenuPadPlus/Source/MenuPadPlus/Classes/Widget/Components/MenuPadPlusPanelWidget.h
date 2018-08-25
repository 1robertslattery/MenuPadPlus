// The MIT License(MIT)
//
// Copyright(c) 2018 Robert Slattery
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), 
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
// and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObjectGlobals.h"
#include "Components/PanelSlot.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/PanelWidget.h"
#include "../MenuPadPlusInterface.h"
#include "MenuPadPlusPanelWidget.generated.h"

class UMenuPadPlusButton;

UCLASS(AutoExpandCategories = ("MenuPadPlus | Widgets"))
class MENUPADPLUS_API UMenuPadPlusPanelWidget : public UPanelWidget, public IMenuPadPlusInterface
{
	GENERATED_BODY()
	
public:
		
	// All Button Children
	UPROPERTY(BlueprintReadOnly, Category = "MenuPadPlus | Widgets")
	TArray<class UMenuPadPlusButton*> Buttons;
	
	// Do we want to replace our Normal/Hovered/Pressed button images with different ones?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Images", meta = (DisplayName = "Use Alternate Images"))
	bool bUseAlternateImages;

	// All Alternate Normal/Hovered/Pressed Images
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Images")
	TArray<class UTexture2D*> AlternateImages;

	// Alternate Button Size X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Images")
	float AlternateSizeX;

	// Alternate Button Size Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Images")
	float AlternateSizeY;

	// Alternate Hovered Sound Cue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Sounds")
	class USoundCue* AlternateHoveredSound;

	// Alternate Pressed Sound Cue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Sounds")
	class USoundCue* AlternatePressedSound;
	
public:

	//~ Begin IMenuPadPlusInterface
	virtual void BindData() override;
	virtual void UnBindData() override;
	virtual UMenuPadPlusButton* GetFocusedWidget() override;
	virtual UMenuPadPlusButton* GetFirstWidget() override;
	virtual AMyPlayerController* GetOwningPlayerController() override;
	virtual bool DoesContainButtons() override;
	virtual void ResetAllWidgetFocus() override;
	//~ End IMenuPadPlusInterface
		
};