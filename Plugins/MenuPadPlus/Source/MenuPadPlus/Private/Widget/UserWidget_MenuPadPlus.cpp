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

#include "../../Classes/Widget/UserWidget_MenuPadPlus.h"
#include "../../Classes/Widget/Components/MenuPadPlusButton.h"
#include "../../Classes/Widget/Components/MenuPadPlusVerticalBox.h"
#include "../../Classes/Widget/Components/MenuPadPlusHorizontalBox.h"
#include "../../Classes/Widget/Components/MenuPadPlusPanelWidget.h"
#include "../../Classes/Utilities/MenuPadPlusStatics.h"
#include "Runtime/UMG/Public/Components/PanelWidget.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "../../Classes/GameFramework/MyPlayerController.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Engine.h"

#define LOCTEXT_NAMESPACE "MenuPadPlus"

#pragma region UUserWidget Interface
// Sets default values
void UUserWidget_MenuPadPlus::NativeConstruct()
{
	Super::NativeConstruct();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					MenuPadPlus
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		
	HasFinishedSetup = false;
	Timer = 0.f;
	TimeNeededToLoad = 0.08f;
	InitMenus();
}

void UUserWidget_MenuPadPlus::NativeDestruct()
{
	Super::NativeDestruct();

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					MenuPadPlus
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ButtonProperties.ClearAll();
	OwnerContainer = nullptr;
}

// Called every frame
void UUserWidget_MenuPadPlus::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					MenuPadPlus
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	
	MenuPadPlusLogic(DeltaTime);
}

// Use to "Go Back" in Menus.
FReply UUserWidget_MenuPadPlus::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					MenuPadPlus
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	auto const world = GetWorld();
	auto ArrayLength = GetNumMenus(ButtonProperties.BoxArray);

	if (world != nullptr)
	{
		auto PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(world, 0));

		if (PC != nullptr)
		{
			if (ArrayLength > 1)
			{
				for (int32 i = 0; i < ArrayLength; ++i)
				{
					if (ButtonProperties.BoxArray[i]->IsVisible() && ButtonProperties.BoxArray.IsValidIndex(i - 1))
					{
						// Example: "B" Button (XBox controller)
						if (InKeyEvent.GetKey() == ButtonProperties.GoBackButton)
						{
							// Hide Current Menu
							ButtonProperties.BoxArray[i]->SetVisibility(ESlateVisibility::Hidden);

							// Show Previous Menu
							ButtonProperties.BoxArray[i - 1]->SetVisibility(ESlateVisibility::Visible);

							// Set new focus on previous menu button
							UMenuPadPlusStatics::SetButtonFocus(ButtonProperties.BoxArray[i - 1]->GetFirstWidget(), PC);

							// TODO: Add Pressed Sound

							return FReply::Handled();
						}
					}
				}
			}
		}
	}

	return FReply::Unhandled();
}
#pragma endregion

#pragma region MenuPadPlus
int32 UUserWidget_MenuPadPlus::InitMenus()
{
	// Allows 8 by default
	BoxData.RootMenu_1 = nullptr;
	BoxData.RootMenu_2 = nullptr;
	BoxData.RootMenu_3 = nullptr;
	BoxData.RootMenu_4 = nullptr;
	BoxData.RootMenu_5 = nullptr;
	BoxData.RootMenu_6 = nullptr;
	BoxData.RootMenu_7 = nullptr;
	BoxData.RootMenu_8 = nullptr;

	SetMenuChildren(BoxData.RootMenu_1, 0);
	SetMenuChildren(BoxData.RootMenu_2, 1);
	SetMenuChildren(BoxData.RootMenu_3, 2);
	SetMenuChildren(BoxData.RootMenu_4, 3);
	SetMenuChildren(BoxData.RootMenu_5, 4);
	SetMenuChildren(BoxData.RootMenu_6, 5);
	SetMenuChildren(BoxData.RootMenu_7, 6);
	SetMenuChildren(BoxData.RootMenu_8, 7);

	return 0;
}

UMenuPadPlusPanelWidget* UUserWidget_MenuPadPlus::AddToArray(class UMenuPadPlusPanelWidget* RootMenu)
{
	UMenuPadPlusPanelWidget* retVal = nullptr;

	if (RootMenu != nullptr)
	{
		ButtonProperties.BoxArray.Add(RootMenu);
		retVal = RootMenu;
	}

	return retVal;
}

void UUserWidget_MenuPadPlus::SetMenuChildren(class UMenuPadPlusPanelWidget* RootMenu, const int32 Index)
{
	if (UPanelWidget* RootPanel = Cast<UPanelWidget>(GetRootWidget()))
	{
		if ((RootMenu = Cast<UMenuPadPlusPanelWidget>(RootPanel->GetChildAt(Index))) != 0)
		{
			AddToArray(RootMenu);
			int32 BoxChildrenNum = RootMenu->GetChildrenCount();

			for (int32 i = 0; i < BoxChildrenNum; ++i)
			{
				if (UMenuPadPlusButton* Button = Cast<UMenuPadPlusButton>(RootMenu->GetChildAt(i)))
				{
					RootMenu->Buttons.Add(Button);
					Button->OwnerContainer = RootMenu;
				}
			}
		}
	}
}

// Runs the system
void UUserWidget_MenuPadPlus::MenuPadPlusLogic(float DeltaSeconds)
{
	if (!HasFinishedSetup)
	{
		if (GetDelay() < GetTimeNeededToLoad()) RunDelay(DeltaSeconds);
		else HasFinishedSetup = true;
	}
	else
	{
		HandleMenuAt(0);
		HandleMenuAt(1);
		HandleMenuAt(2);
		HandleMenuAt(3);
		HandleMenuAt(4);
		HandleMenuAt(5);
		HandleMenuAt(6);
		HandleMenuAt(7);
	}
}

void UUserWidget_MenuPadPlus::OnJoystickAxisChanged(
	  class TArray<class UMenuPadPlusButton*> ButtonsArray
	, class UObject* NormalTexture
	, class UObject* HoveredTexture
	, class UObject* PressedTexture
	, class AMyPlayerController* InPC)
{
	if (ButtonsArray.Num() > 0 && InPC)
	{
		int32 ArrayLength = ButtonsArray.Num();
		
		for (int32 i = 0; i < ArrayLength; ++i)
		{
			if (ButtonsArray[i]->HasUserFocus(InPC))
			{
				FButtonStyle ButtonStyle;
				ButtonStyle.Normal.SetResourceObject(HoveredTexture);
				ButtonStyle.Hovered.SetResourceObject(HoveredTexture);
				ButtonStyle.Pressed.SetResourceObject(PressedTexture);

				ButtonStyle.Normal.ImageSize = FVector2D(ButtonProperties.ImageX, ButtonProperties.ImageY);
				ButtonStyle.Hovered.ImageSize = FVector2D(ButtonProperties.ImageX, ButtonProperties.ImageY);
				ButtonStyle.Pressed.ImageSize = FVector2D(ButtonProperties.ImageX, ButtonProperties.ImageY);

				if (ButtonProperties.PressedSound != NULL) ButtonStyle.PressedSlateSound.SetResourceObject(ButtonProperties.PressedSound);

				if (ButtonProperties.HoveredSound != NULL)
				{
					if (!ButtonsArray[i]->canPlayHoveredSound)
					{
						auto const world = GetWorld();

						if (world != nullptr)
						{
							UGameplayStatics::PlaySound2D(world, ButtonProperties.HoveredSound);
							ButtonsArray[i]->canPlayHoveredSound = true;
						}
					}
				}

				ButtonsArray[i]->SetStyle(ButtonStyle);
				ButtonsArray[i]->ForceHover();
			}
			else
			{
				FButtonStyle ButtonStyle;
				ButtonStyle.Normal.SetResourceObject(NormalTexture);
				ButtonStyle.Hovered.SetResourceObject(NormalTexture);

				ButtonStyle.Normal.ImageSize = FVector2D(ButtonProperties.ImageX, ButtonProperties.ImageY);
				ButtonStyle.Hovered.ImageSize = FVector2D(ButtonProperties.ImageX, ButtonProperties.ImageY);

				if (ButtonsArray[i]->canPlayHoveredSound) ButtonsArray[i]->canPlayHoveredSound = false;

				ButtonsArray[i]->SetStyle(ButtonStyle);
				ButtonsArray[i]->ForceNormal();
			}
		}
	}
}

void UUserWidget_MenuPadPlus::HandleMenuAt(const int32 Index)
{
	if (GetNumMenus(ButtonProperties.BoxArray) > 0)
	{
		if (ButtonProperties.BoxArray.IsValidIndex(Index))
		{
			if (ButtonProperties.BoxArray[Index]->DoNotUseImages)
			{
				if (ButtonProperties.BoxArray[Index]->IsVisible())
				{
					if (ButtonProperties.BoxArray[Index]->DoesContainButtons())
					{
						OnJoystickAxisChanged(
							  ButtonProperties.BoxArray[Index]->Buttons							// Buttons
							, NULL, NULL, NULL													// Button Images
							, ButtonProperties.BoxArray[Index]->GetOwningPlayerController());	// The Player Controller
					}
				}
			}
			else
			{
				if (ButtonProperties.BoxArray[Index]->IsVisible())
				{
					if (ButtonProperties.BoxArray[Index]->DoesContainButtons())
					{
						OnJoystickAxisChanged(
							  ButtonProperties.BoxArray[Index]->Buttons															// Buttons
							, ButtonProperties.NormalTexture, ButtonProperties.HoveredTexture, ButtonProperties.PressedTexture	// Button Images
							, ButtonProperties.BoxArray[Index]->GetOwningPlayerController());									// The Player Controller
					}
				}
			}
		}
	}
}

UMenuPadPlusButton* UUserWidget_MenuPadPlus::GetFocusedWidget(TArray<class UMenuPadPlusButton*> Buttons)
{
	for (auto& Widget : Buttons)
	{
		if (Widget->hasForcedHover)
			return Widget;
	}

	return nullptr;
}

UMenuPadPlusButton* UUserWidget_MenuPadPlus::GetFirstWidget()
{
	if (UPanelWidget* RootPanel = Cast<UPanelWidget>(GetRootWidget()))
	{
		if (GetNumMenus(ButtonProperties.BoxArray) > 0)
		{
			if ((ButtonProperties.BoxArray[0] = Cast<UMenuPadPlusPanelWidget>(RootPanel->GetChildAt(0))) != 0)
				return ButtonProperties.BoxArray[0]->GetFirstWidget();
			else
				return nullptr;
		}
	}

	return nullptr;
}

UMenuPadPlusButton* UUserWidget_MenuPadPlus::GetPreviousWidget()
{
	auto VerticalArrayLength = GetNumMenus(ButtonProperties.BoxArray);

	if (VerticalArrayLength > 1)
		for (int32 i = 0; i < VerticalArrayLength; ++i)
			return ButtonProperties.BoxArray[i - 1]->GetFirstWidget();
		
	return nullptr;
}

void UUserWidget_MenuPadPlus::ResetAllWidgetFocus(TArray<class UMenuPadPlusButton*> CurrentButton)
{
	for (auto const& Widget : CurrentButton)
		Widget->ForceNormal();

	auto const world = GetWorld();
	
	if (world != nullptr)
	{
		auto PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(world, 0));
		if (PC != nullptr) UMenuPadPlusStatics::SetButtonFocus(GetFirstWidget(), PC);
	}
}

template<typename AllocatorType>
int32 UUserWidget_MenuPadPlus::GetNumMenus(TArray<class UMenuPadPlusPanelWidget*, AllocatorType>& RootMenus)
{
	return RootMenus.Num();
}

float UUserWidget_MenuPadPlus::GetDelay()
{
	return Timer;
}

float UUserWidget_MenuPadPlus::GetTimeNeededToLoad()
{
	return TimeNeededToLoad;
}

float UUserWidget_MenuPadPlus::RunDelay(float DeltaSeconds)
{
	return Timer += 1 * DeltaSeconds;
}
#pragma endregion

#undef LOCTEXT_NAMESPACE