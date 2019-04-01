/*
* MIT License
* Copyright (c) 2018-2019 Robert Slattery
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

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
		  const FKey& _GoBackButton
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
	TArray<class UMenuPadPlusPanelWidget*> RootMenuArray;
		
	FMenuPadPlusBoxData() { RootMenuArray.Empty(); }

	friend bool operator==(const FMenuPadPlusBoxData& A, const FMenuPadPlusBoxData& B)
	{
		return (A.RootMenuArray == B.RootMenuArray);
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
	template<class Type, typename Idx>
	Idx SetMenuChildren(Type* RootMenu, const Idx& Index);
	
	template<class Type>
	Type* FillArrayWith(Type* RootMenu);

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
		
	// Interface Owner
	UPROPERTY(Category = "MenuPadPlus", BlueprintReadOnly)
	TScriptInterface<IMenuPadPlusInterface> OwnerContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MenuPadPlus")
	FMenuPadPlusButtonProperties ButtonProperties;

	UPROPERTY(BlueprintReadOnly, Category = "MenuPadPlus")
	FMenuPadPlusBoxData BoxData;

	template<typename AllocatorType>
	FORCEINLINE constexpr int32 GetNumMenus(const TArray<class UMenuPadPlusPanelWidget*, AllocatorType>& RootMenus) const { return RootMenus.Num(); }
	
	// TODO: Timers for different platforms
	FORCEINLINE float GetTimer() const noexcept { return Timer; }
	FORCEINLINE float GetTimeNeededToLoad() const noexcept { return TimeNeededToLoad; }
	FORCEINLINE float RunTimer(float DeltaSeconds) { return Timer += (1 * DeltaSeconds); }

private:

	float Timer;
	float TimeNeededToLoad;
	bool bHasFinishedSetup;

	// Numericals for Menus
	const static int32 ROOT_MENU_ONE;
	const static int32 ROOT_MENU_TWO;
	const static int32 ROOT_MENU_THREE;
	const static int32 ROOT_MENU_FOUR;
	const static int32 ROOT_MENU_FIVE;
	const static int32 ROOT_MENU_SIX;
	const static int32 ROOT_MENU_SEVEN;
	const static int32 ROOT_MENU_EIGHT;
	const static int32 ROOT_MENU_NINE;
	const static int32 ROOT_MENU_TEN;
	const static int32 ROOT_MENU_ELEVEN;
	const static int32 ROOT_MENU_TWELVE;

	const static int32 PLAYER_CONTROLLER_INDEX;
	//~ End MenuPadPlus 
};