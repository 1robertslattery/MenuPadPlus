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

#define SUCCESS 0
#define FAILURE -1

#define ROOT_MENU_ONE 0
#define ROOT_MENU_TWO 1
#define ROOT_MENU_THREE 2
#define ROOT_MENU_FOUR 3
#define ROOT_MENU_FIVE 4
#define ROOT_MENU_SIX 5
#define ROOT_MENU_SEVEN 6
#define ROOT_MENU_EIGHT 7
#define ROOT_MENU_NINE 8
#define ROOT_MENU_TEN 9
#define ROOT_MENU_ELEVEN 10
#define ROOT_MENU_TWELVE 11

#define PLAYER_CONTROLLER_INDEX 0

class IMenuPadPlusInterface;

USTRUCT(BlueprintType)
struct FMenuPadPlusButtonProperties
{
	GENERATED_USTRUCT_BODY()
				
	// Which key should we use to handle going back in menus?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus")
	FKey GoBackButton;

	// All Box Children
	TArray<class UMenuPadPlusPanelWidget*, TInlineAllocator<12>> BoxArray;

	// All Normal Texture Children
	TArray<class UTexture2D*, TInlineAllocator<64>> NormalTextureArray;

	// All Hovered Texture Children
	TArray<class UTexture2D*, TInlineAllocator<64>> HoveredTextureArray;

	// All Pressed Texture Children
	TArray<class UTexture2D*, TInlineAllocator<64>> PressedTextureArray;
	
	FORCEINLINE void ClearAll()
	{
		BoxArray.Empty();
		NormalTextureArray.Empty();
		HoveredTextureArray.Empty();
		PressedTextureArray.Empty();
	}
	
	explicit FMenuPadPlusButtonProperties() {}

	FMenuPadPlusButtonProperties(
		  FKey _GoBackButton
		, TArray<class UMenuPadPlusPanelWidget*, TInlineAllocator<12>> _BoxArray
		, TArray<class UTexture2D*, TInlineAllocator<64>> _NormalTextureArray
		, TArray<class UTexture2D*, TInlineAllocator<64>> _HoveredTextureArray
		, TArray<class UTexture2D*, TInlineAllocator<64>> _PressedTextureArray) :
		  GoBackButton(_GoBackButton)
		, BoxArray(_BoxArray)
		, NormalTextureArray(_NormalTextureArray)
		, HoveredTextureArray(_HoveredTextureArray)
		, PressedTextureArray(_PressedTextureArray)
		{}

	friend bool operator==(const FMenuPadPlusButtonProperties& A, const FMenuPadPlusButtonProperties& B)
	{
		return (A.GoBackButton == B.GoBackButton
			&& A.BoxArray == B.BoxArray
			&& A.NormalTextureArray == B.NormalTextureArray
			&& A.HoveredTextureArray == B.HoveredTextureArray
			&& A.PressedTextureArray == B.PressedTextureArray);
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

	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_9;

	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_10;

	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_11;

	UPROPERTY()
	class UMenuPadPlusPanelWidget* RootMenu_12;
	
	explicit FMenuPadPlusBoxData() {}

	FMenuPadPlusBoxData(
		  class UMenuPadPlusPanelWidget* _RootMenu_1
		, class UMenuPadPlusPanelWidget* _RootMenu_2
		, class UMenuPadPlusPanelWidget* _RootMenu_3
		, class UMenuPadPlusPanelWidget* _RootMenu_4
		, class UMenuPadPlusPanelWidget* _RootMenu_5
		, class UMenuPadPlusPanelWidget* _RootMenu_6
		, class UMenuPadPlusPanelWidget* _RootMenu_7
		, class UMenuPadPlusPanelWidget* _RootMenu_8
		, class UMenuPadPlusPanelWidget* _RootMenu_9
		, class UMenuPadPlusPanelWidget* _RootMenu_10
		, class UMenuPadPlusPanelWidget* _RootMenu_11
		, class UMenuPadPlusPanelWidget* _RootMenu_12) :
		  RootMenu_1(_RootMenu_1)
		, RootMenu_2(_RootMenu_2)
		, RootMenu_3(_RootMenu_3)
		, RootMenu_4(_RootMenu_4)
		, RootMenu_5(_RootMenu_5)
		, RootMenu_6(_RootMenu_6)
		, RootMenu_7(_RootMenu_7)
		, RootMenu_8(_RootMenu_8)
		, RootMenu_9(_RootMenu_9)
		, RootMenu_10(_RootMenu_10)
		, RootMenu_11(_RootMenu_11)
		, RootMenu_12(_RootMenu_12)
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
			&& A.RootMenu_8 == B.RootMenu_8
			&& A.RootMenu_9 == B.RootMenu_9
			&& A.RootMenu_10 == B.RootMenu_10
			&& A.RootMenu_11 == B.RootMenu_11
			&& A.RootMenu_12 == B.RootMenu_12);
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

	//~ Begin MenuPadPlus
	// Find all possible Vertical/Horizontal Boxes (Supports up to 12)
	int32 InitMenus();
		
	// Adds Menus to array and sets their Button children
	int32 SetMenuChildren(class UMenuPadPlusPanelWidget* RootMenu, const int32 Index);
	UMenuPadPlusPanelWidget* FillArrayWith(class UMenuPadPlusPanelWidget* RootMenu);

	// Method to run the system
	void RunMenuPadPlus(float DeltaSeconds);

	// The actual handling of Normal/Hover/Pressed States
	void OnJoystickAxisChanged(
		  TArray<class UMenuPadPlusButton*> ButtonsArray
		, class AMyPlayerController* InPC);

	void OnJoystickAxisChangedAlternate(
		  TArray<class UMenuPadPlusButton*> ButtonsArray
		, class UObject* NormalTexture
		, class UObject* HoveredTexture
		, class UObject* PressedTexture
		, float ImageSizeX
		, float ImageSizeY
		, class USoundCue* HoveredSound
		, class USoundCue* PressedSound
		, class AMyPlayerController* InPC);
		
	// Which menus will allow joystick changes?
	void RunMenuAt(const int32 Index);

	UMenuPadPlusButton* GetFocusedWidget(TArray<class UMenuPadPlusButton*> Buttons);
	UMenuPadPlusButton* GetFirstWidget();
	UMenuPadPlusButton* GetPreviousWidget();
	void ResetAllWidgetFocus(TArray<class UMenuPadPlusButton*> CurrentButton);
		
	template<typename AllocatorType>
	int32 GetNumMenus(TArray<class UMenuPadPlusPanelWidget*, AllocatorType>& RootMenus);
	float GetTimer();
	float GetTimeNeededToLoad();
	float RunTimer(float DeltaSeconds);

private:

	float Timer;
	float TimeNeededToLoad;
	bool bHasFinishedSetup;

public:

	// Interface Owner
	UPROPERTY(Category = "MenuPadPlus", BlueprintReadOnly)
	TScriptInterface<IMenuPadPlusInterface> OwnerContainer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus")
	FMenuPadPlusButtonProperties ButtonProperties;
	
	UPROPERTY(BlueprintReadOnly, Category = "MenuPadPlus")
	FMenuPadPlusBoxData BoxData;
	//~ End MenuPadPlus 
};