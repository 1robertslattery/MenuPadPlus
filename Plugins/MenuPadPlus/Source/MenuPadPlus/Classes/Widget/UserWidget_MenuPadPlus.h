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
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Components/TextWidgetTypes.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "UserWidget_MenuPadPlus.generated.h"

class IMenuPadPlusInterface;

USTRUCT(BlueprintType)
struct FMenuPadPlusButtonProperties
{
	GENERATED_USTRUCT_BODY()

	// Normal State Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets | Textures")
	class UObject* NormalTexture;

	// Hovered State Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets | Textures")
	class UObject* HoveredTexture;

	// Pressed State Image
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets | Textures")
	class UObject* PressedTexture;

	// Hovered Sound Cue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets | Sounds")
	class USoundCue* HoveredSound;

	// Pressed Sound Cue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets | Sounds")
	class USoundCue* PressedSound;
			
	// Button Size X
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets")
	float ImageX;

	// Button Size Y
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets")
	float ImageY;
			
	// Which key should we use to handle going back in menus?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets")
	FKey GoBackButton;

	// All Box Children
	TArray<class UMenuPadPlusPanelWidget*, TInlineAllocator<8>> BoxArray;
	
	FORCEINLINE void ClearAll()
	{
		BoxArray.Empty();
	}
	
	explicit FMenuPadPlusButtonProperties() {}

	FMenuPadPlusButtonProperties(
		  class UObject* _NormalTexture
		, class UObject* _HoveredTexture
		, class UObject* _PressedTexture
		, class USoundCue* _HoveredSound
		, class USoundCue* _PressedSound
		, float _ImageX
		, float _ImageY
		, FKey _GoBackButton
		, TArray<class UMenuPadPlusPanelWidget*, TInlineAllocator<8>> _BoxArray) :
		  NormalTexture(_NormalTexture)
		, HoveredTexture(_HoveredTexture)
		, PressedTexture(_PressedTexture)
		, HoveredSound(_HoveredSound)
		, PressedSound(_PressedSound)
		, ImageX(_ImageX)
		, ImageY(_ImageY)
		, GoBackButton(_GoBackButton)
		, BoxArray(_BoxArray)
		{}

	friend bool operator==(const FMenuPadPlusButtonProperties& A, const FMenuPadPlusButtonProperties& B)
	{
		return (A.NormalTexture == B.NormalTexture
			&& A.HoveredTexture == B.HoveredTexture
			&& A.PressedTexture == B.PressedTexture
			&& A.HoveredSound == B.HoveredSound
			&& A.PressedSound == B.HoveredSound
			&& A.ImageX == B.ImageX
			&& A.ImageY == B.ImageY
			&& A.GoBackButton == B.GoBackButton
			&& A.BoxArray == B.BoxArray);
	}
};

USTRUCT(BlueprintType)
struct FMenuPadPlusBoxData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_1;

	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_2;
	
	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_3;
	
	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_4;
	
	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_5;
	
	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_6;

	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_7;

	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_8;
	
	explicit FMenuPadPlusBoxData() {}

	FMenuPadPlusBoxData(
		  class UMenuPadPlusPanelWidget* _RootMenu_1
		, class UMenuPadPlusPanelWidget* _RootMenu_2
		, class UMenuPadPlusPanelWidget* _RootMenu_3
		, class UMenuPadPlusPanelWidget* _RootMenu_4
		, class UMenuPadPlusPanelWidget* _RootMenu_5
		, class UMenuPadPlusPanelWidget* _RootMenu_6
		, class UMenuPadPlusPanelWidget* _RootMenu_7
		, class UMenuPadPlusPanelWidget* _RootMenu_8) :
		  RootMenu_1(_RootMenu_1)
		, RootMenu_2(_RootMenu_2)
		, RootMenu_3(_RootMenu_3)
		, RootMenu_4(_RootMenu_4)
		, RootMenu_5(_RootMenu_5)
		, RootMenu_6(_RootMenu_6)
		, RootMenu_7(_RootMenu_7)
		, RootMenu_8(_RootMenu_8)
		{}

	friend bool operator==(const FMenuPadPlusBoxData& A, const FMenuPadPlusBoxData& B)
	{
		return (A.RootMenu_1 == B.RootMenu_1
			&& A.RootMenu_2 == B.RootMenu_2
			&& A.RootMenu_3 == B.RootMenu_3
			&& A.RootMenu_4 == B.RootMenu_4
			&& A.RootMenu_5 == B.RootMenu_5
			&& A.RootMenu_6 == B.RootMenu_6
			&& A.RootMenu_7 == B.RootMenu_7
			&& A.RootMenu_8 == B.RootMenu_8);
	}
};

UCLASS(Abstract, BlueprintType, Blueprintable, Category = "MenuPadPlus")
class MENUPADPLUS_API UUserWidget_MenuPadPlus : public UUserWidget
{
	GENERATED_BODY()
		
public:

	//~ Begin UUserWidget Interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	virtual FReply NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	//~ End UUserWidget Interface
	
public:

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					MenuPadPlus
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			
	// Find all possible Vertical/Horizontal Boxes (Supports up to 8)
	int32 InitMenus();
		
	// Adds Menus to array and sets their Button children
	void SetMenuChildren(class UMenuPadPlusPanelWidget* RootMenu, const int32 Index);
	UMenuPadPlusPanelWidget* AddToArray(class UMenuPadPlusPanelWidget* RootMenu);

	// Method to run the system
	void MenuPadPlusLogic(float DeltaSeconds);

	// The actual handling of Normal/Hover/Pressed States
	void OnJoystickAxisChanged(
		  TArray<class UMenuPadPlusButton*> ButtonsArray
		, class UObject* NormalTexture
		, class UObject* HoveredTexture
		, class UObject* PressedTexture
		, class AMyPlayerController* InPC);
		
	// Which menus will allow joystick changes?
	void HandleMenuAt(const int32 Index);

	UMenuPadPlusButton* GetFocusedWidget(TArray<class UMenuPadPlusButton*> Buttons);
	UMenuPadPlusButton* GetFirstWidget();
	UMenuPadPlusButton* GetPreviousWidget();
	void ResetAllWidgetFocus(TArray<class UMenuPadPlusButton*> CurrentButton);
		
	template<typename AllocatorType>
	int32 GetNumMenus(TArray<class UMenuPadPlusPanelWidget*, AllocatorType>& RootMenus);

	float GetDelay();
	float GetTimeNeededToLoad();
	float RunDelay(float DeltaSeconds);

private:

	float Timer;
	float TimeNeededToLoad;
	bool HasFinishedSetup;

public:

	// Interface Owner
	UPROPERTY(Category = "MenuPadPlus | Widgets | Navigation", BlueprintReadOnly)
	TScriptInterface<IMenuPadPlusInterface> OwnerContainer;
	
	// Allow Reference to FMenuPadPlusButtonProperties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus | Widgets")
	FMenuPadPlusButtonProperties ButtonProperties;
	
	// Allow Reference to FMenuPadPlusBoxData
	UPROPERTY(BlueprintReadOnly, Category = "MenuPadPlus | Widgets")
	FMenuPadPlusBoxData BoxData;
	//~ End MenuPadPlus 
};