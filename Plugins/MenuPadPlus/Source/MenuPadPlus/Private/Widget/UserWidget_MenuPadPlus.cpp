/*
* MIT License
* Copyright (c) 2018 Robert Slattery
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

const int32 UUserWidget_MenuPadPlus::ROOT_MENU_ONE = 0;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_TWO = 1;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_THREE = 2;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_FOUR = 3;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_FIVE = 4;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_SIX = 5;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_SEVEN = 6;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_EIGHT = 7;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_NINE = 8;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_TEN = 9;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_ELEVEN = 10;
const int32 UUserWidget_MenuPadPlus::ROOT_MENU_TWELVE = 11;
const int32 UUserWidget_MenuPadPlus::PLAYER_CONTROLLER_INDEX = 0;

#pragma region UUserWidget Interface
void UUserWidget_MenuPadPlus::NativeConstruct()
{
	Super::NativeConstruct();

	//~ Begin MenuPadPlus
	bHasFinishedSetup = false;
	Timer = 0.f;
	TimeNeededToLoad = 0.08f;
	ButtonProperties.NormalTextureArray.Empty();
	ButtonProperties.HoveredTextureArray.Empty();
	ButtonProperties.PressedTextureArray.Empty();
	InitMenus();
	//~ End MenuPadPlus
}

void UUserWidget_MenuPadPlus::NativeDestruct()
{
	Super::NativeDestruct();

	//~ Begin MenuPadPlus
	ButtonProperties.ClearAll();
		
	if (BoxData.RootMenu_1)  { delete BoxData.RootMenu_1;  BoxData.RootMenu_1 = nullptr; }
	if (BoxData.RootMenu_2)  { delete BoxData.RootMenu_2;  BoxData.RootMenu_2 = nullptr; }
	if (BoxData.RootMenu_3)  { delete BoxData.RootMenu_3;  BoxData.RootMenu_3 = nullptr; }
	if (BoxData.RootMenu_4)  { delete BoxData.RootMenu_4;  BoxData.RootMenu_4 = nullptr; }
	if (BoxData.RootMenu_5)  { delete BoxData.RootMenu_5;  BoxData.RootMenu_5 = nullptr; }
	if (BoxData.RootMenu_6)  { delete BoxData.RootMenu_6;  BoxData.RootMenu_6 = nullptr; }
	if (BoxData.RootMenu_7)  { delete BoxData.RootMenu_7;  BoxData.RootMenu_7 = nullptr; }
	if (BoxData.RootMenu_8)  { delete BoxData.RootMenu_8;  BoxData.RootMenu_8 = nullptr; }
	if (BoxData.RootMenu_9)	 { delete BoxData.RootMenu_9;  BoxData.RootMenu_9 = nullptr; }
	if (BoxData.RootMenu_10) { delete BoxData.RootMenu_10; BoxData.RootMenu_10 = nullptr; }
	if (BoxData.RootMenu_11) { delete BoxData.RootMenu_11; BoxData.RootMenu_11 = nullptr; }
	if (BoxData.RootMenu_12) { delete BoxData.RootMenu_12; BoxData.RootMenu_12 = nullptr; }
	
	OwnerContainer = nullptr;
	//~ End MenuPadPlus
}

void UUserWidget_MenuPadPlus::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	
	//~ Begin MenuPadPlus
	RunMenuPadPlus(DeltaTime);
	//~ End MenuPadPlus
}

// Use to "Go Back" in Menus.
FReply UUserWidget_MenuPadPlus::NativeOnKeyUp(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	//~ Begin MenuPadPlus
	auto const WorldPtr = GetWorld();
	auto ArrayLength = GetNumMenus(ButtonProperties.BoxArray);
	auto const MenuCount = 1;

	if (ensure(WorldPtr))
	{
		auto PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(WorldPtr, PLAYER_CONTROLLER_INDEX));

		if (PC != nullptr)
		{
			if (ArrayLength > MenuCount)
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

							// Force Normal State of Buttons
							int32 BoxChildrenNum = ButtonProperties.BoxArray[i - 1]->Buttons.Num();
							
							for (int32 j = 0; j < BoxChildrenNum; ++j)
								ButtonProperties.BoxArray[i - 1]->Buttons[j]->ForceNormalText();
							
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
	//~ End MenuPadPlus

	return FReply::Unhandled();
}
#pragma endregion

#pragma region MenuPadPlus
int32 UUserWidget_MenuPadPlus::InitMenus()
{
	// Allows 12 by default
	BoxData.RootMenu_1 = nullptr;
	BoxData.RootMenu_2 = nullptr;
	BoxData.RootMenu_3 = nullptr;
	BoxData.RootMenu_4 = nullptr;
	BoxData.RootMenu_5 = nullptr;
	BoxData.RootMenu_6 = nullptr;
	BoxData.RootMenu_7 = nullptr;
	BoxData.RootMenu_8 = nullptr;
	BoxData.RootMenu_9 = nullptr;
	BoxData.RootMenu_10 = nullptr;
	BoxData.RootMenu_11 = nullptr;
	BoxData.RootMenu_12 = nullptr;

	SetMenuChildren(BoxData.RootMenu_1, ROOT_MENU_ONE);
	SetMenuChildren(BoxData.RootMenu_2, ROOT_MENU_TWO);
	SetMenuChildren(BoxData.RootMenu_3, ROOT_MENU_THREE);
	SetMenuChildren(BoxData.RootMenu_4, ROOT_MENU_FOUR);
	SetMenuChildren(BoxData.RootMenu_5, ROOT_MENU_FIVE);
	SetMenuChildren(BoxData.RootMenu_6, ROOT_MENU_SIX);
	SetMenuChildren(BoxData.RootMenu_7, ROOT_MENU_SEVEN);
	SetMenuChildren(BoxData.RootMenu_8, ROOT_MENU_EIGHT);
	SetMenuChildren(BoxData.RootMenu_9, ROOT_MENU_NINE);
	SetMenuChildren(BoxData.RootMenu_10, ROOT_MENU_TEN);
	SetMenuChildren(BoxData.RootMenu_11, ROOT_MENU_ELEVEN);
	SetMenuChildren(BoxData.RootMenu_12, ROOT_MENU_TWELVE);

	return SUCCESS;
}

template<class Type>
Type* UUserWidget_MenuPadPlus::FillArrayWith(Type* RootMenu)
{
	if (RootMenu != nullptr)
	{
		ButtonProperties.BoxArray.Add(RootMenu);
		return RootMenu;
	}

	return nullptr;
}

template<class Type, typename Idx>
Idx UUserWidget_MenuPadPlus::SetMenuChildren(Type* RootMenu, const Idx& Index)
{
	if (UPanelWidget* RootPanel = Cast<UPanelWidget>(GetRootWidget()))
	{
		if ((RootMenu = Cast<Type>(RootPanel->GetChildAt(Index))) != 0)
		{
			FillArrayWith(RootMenu);
			auto BoxChildrenNum = RootMenu->GetChildrenCount();

			for (int32 i = 0; i < BoxChildrenNum; ++i)
			{
				if (UMenuPadPlusButton* Button = Cast<UMenuPadPlusButton>(RootMenu->GetChildAt(i)))
				{
					RootMenu->Buttons.Add(Button);
					Button->OwnerContainer = RootMenu;

					auto ButtonChildrenNum = RootMenu->Buttons.Num();

					for (int32 j = 0; j < ButtonChildrenNum; ++j)
					{
						if (UTexture2D* NormalImage = Cast<UTexture2D>(RootMenu->Buttons[j]->WidgetStyle.Normal.GetResourceObject()))
							ButtonProperties.NormalTextureArray.Add(NormalImage);

						if (UTexture2D* HoveredImage = Cast<UTexture2D>(RootMenu->Buttons[j]->WidgetStyle.Hovered.GetResourceObject()))
							ButtonProperties.HoveredTextureArray.Add(HoveredImage);

						if (UTexture2D* PressedImage = Cast<UTexture2D>(RootMenu->Buttons[j]->WidgetStyle.Pressed.GetResourceObject()))
							ButtonProperties.PressedTextureArray.Add(PressedImage);
					}
				}
			}
		}
	}
	
	return SUCCESS;
}

// Runs the system
void UUserWidget_MenuPadPlus::RunMenuPadPlus(float DeltaSeconds)
{
	if (!bHasFinishedSetup)
	{
		if (GetTimer() < GetTimeNeededToLoad()) RunTimer(DeltaSeconds);
		else bHasFinishedSetup = true;
	}
	else
	{
		RunMenuAt(ROOT_MENU_ONE);
		RunMenuAt(ROOT_MENU_TWO);
		RunMenuAt(ROOT_MENU_THREE);
		RunMenuAt(ROOT_MENU_FOUR);
		RunMenuAt(ROOT_MENU_FIVE);
		RunMenuAt(ROOT_MENU_SIX);
		RunMenuAt(ROOT_MENU_SEVEN);
		RunMenuAt(ROOT_MENU_EIGHT);
		RunMenuAt(ROOT_MENU_NINE);
		RunMenuAt(ROOT_MENU_TEN);
		RunMenuAt(ROOT_MENU_ELEVEN);
		RunMenuAt(ROOT_MENU_TWELVE);
	}
}

void UUserWidget_MenuPadPlus::OnJoystickAxisChanged(
	  TArray<class UMenuPadPlusButton*> ButtonsArray
	, class AMyPlayerController* InPC)
{
	auto const MenuCount = 0;

	if (ButtonsArray.Num() > MenuCount && InPC)
	{
		int32 ArrayLength = ButtonsArray.Num();
				
		for (int32 i = 0; i < ArrayLength; ++i)
		{
			FVector2D NormalSize = ButtonsArray[i]->WidgetStyle.Normal.GetImageSize();
			FVector2D HoveredSize = ButtonsArray[i]->WidgetStyle.Hovered.GetImageSize();
			FVector2D PressedSize = ButtonsArray[i]->WidgetStyle.Pressed.GetImageSize();

			auto HoveredSound = Cast<USoundCue>(ButtonsArray[i]->WidgetStyle.HoveredSlateSound.GetResourceObject());
			auto PressedSound = Cast<USoundCue>(ButtonsArray[i]->WidgetStyle.PressedSlateSound.GetResourceObject());
			
			if (ButtonsArray[i]->HasUserFocus(InPC))
			{
				FButtonStyle ButtonStyle;

				ButtonStyle.Normal.SetResourceObject(ButtonProperties.HoveredTextureArray[i]);
				ButtonStyle.Hovered.SetResourceObject(ButtonProperties.HoveredTextureArray[i]);
				ButtonStyle.Pressed.SetResourceObject(ButtonProperties.PressedTextureArray[i]);

				ButtonStyle.Normal.ImageSize = NormalSize;
				ButtonStyle.Hovered.ImageSize = HoveredSize;
				ButtonStyle.Pressed.ImageSize = PressedSize;

				ButtonStyle.HoveredSlateSound.SetResourceObject(HoveredSound);
				ButtonStyle.PressedSlateSound.SetResourceObject(PressedSound);

				if (!ButtonsArray[i]->bCanPlayHoveredSound)
				{
					auto const WorldPtr = GetWorld();
					if (ensure(WorldPtr)) UGameplayStatics::PlaySound2D(WorldPtr, HoveredSound);
					ButtonsArray[i]->bCanPlayHoveredSound = true;
				}

				ButtonsArray[i]->SetStyle(ButtonStyle);
				if (!ButtonsArray[i]->bHasForcedPressed) ButtonsArray[i]->ForceHoveredText();
			}
			else
			{
				FButtonStyle ButtonStyle;
					
				ButtonStyle.Normal.SetResourceObject(ButtonProperties.NormalTextureArray[i]);
				ButtonStyle.Hovered.SetResourceObject(ButtonProperties.HoveredTextureArray[i]);
				ButtonStyle.Pressed.SetResourceObject(ButtonProperties.PressedTextureArray[i]);

				ButtonStyle.Normal.ImageSize = NormalSize;
				ButtonStyle.Hovered.ImageSize = HoveredSize;
				ButtonStyle.Pressed.ImageSize = PressedSize;

				ButtonStyle.PressedSlateSound.SetResourceObject(PressedSound);
				ButtonStyle.HoveredSlateSound.SetResourceObject(HoveredSound);
					
				if (ButtonsArray[i]->bCanPlayHoveredSound) ButtonsArray[i]->bCanPlayHoveredSound = false;
										
				ButtonsArray[i]->SetStyle(ButtonStyle);
				ButtonsArray[i]->ForceNormalText();
			}
		}
	}
}

// When we want to use different images
void UUserWidget_MenuPadPlus::OnJoystickAxisChangedAlternate(
	  TArray<class UMenuPadPlusButton*> ButtonsArray
	, class UObject* NormalTexture
	, class UObject* HoveredTexture
	, class UObject* PressedTexture
	, float ImageSizeX
	, float ImageSizeY
	, class USoundCue* HoveredSound
	, class USoundCue* PressedSound
	, class AMyPlayerController* InPC)
{
	auto const MenuCount = 0;

	if (ButtonsArray.Num() > MenuCount && InPC)
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

				ButtonStyle.Normal.ImageSize = FVector2D(ImageSizeX, ImageSizeY);
				ButtonStyle.Hovered.ImageSize = FVector2D(ImageSizeX, ImageSizeY);
				ButtonStyle.Pressed.ImageSize = FVector2D(ImageSizeX, ImageSizeY);

				if (PressedSound != NULL) ButtonStyle.PressedSlateSound.SetResourceObject(PressedSound);

				if (HoveredSound != NULL)
				{
					if (!ButtonsArray[i]->bCanPlayHoveredSound)
					{
						auto const WorldPtr = GetWorld();
						if (ensure(WorldPtr)) UGameplayStatics::PlaySound2D(WorldPtr, HoveredSound);
						ButtonsArray[i]->bCanPlayHoveredSound = true;
					}
				}

				ButtonsArray[i]->SetStyle(ButtonStyle);
				if (!ButtonsArray[i]->bHasForcedPressed) ButtonsArray[i]->ForceHoveredText();
			}
			else
			{
				FButtonStyle ButtonStyle;
				ButtonStyle.Normal.SetResourceObject(NormalTexture);
				ButtonStyle.Hovered.SetResourceObject(NormalTexture);

				ButtonStyle.Normal.ImageSize = FVector2D(ImageSizeX, ImageSizeY);
				ButtonStyle.Hovered.ImageSize = FVector2D(ImageSizeX, ImageSizeY);

				if (ButtonsArray[i]->bCanPlayHoveredSound) ButtonsArray[i]->bCanPlayHoveredSound = false;

				ButtonsArray[i]->SetStyle(ButtonStyle);
				ButtonsArray[i]->ForceNormalText();
			}
		}
	}
}

void UUserWidget_MenuPadPlus::RunMenuAt(const int32 Index)
{
	auto const MenuCount = 0;
	auto const AlternateImageCount = 2;

	if (GetNumMenus(ButtonProperties.BoxArray) > MenuCount)
	{
		if (ButtonProperties.BoxArray.IsValidIndex(Index))
		{
			if (ButtonProperties.BoxArray[Index]->bUseAlternateImages == true)
			{
				if (ButtonProperties.BoxArray[Index]->IsVisible())
				{
					if (ButtonProperties.BoxArray[Index]->DoesContainButtons())
					{
						if (ButtonProperties.BoxArray[Index]->GetAlternateImagesSize() > AlternateImageCount)
						{
							OnJoystickAxisChangedAlternate(
								  ButtonProperties.BoxArray[Index]->GetButtons()						// Buttons
								, ButtonProperties.BoxArray[Index]->GetAlternateImages_Normal()			// Normal Texture
								, ButtonProperties.BoxArray[Index]->GetAlternateImages_Hovered()		// Hovered Texture
								, ButtonProperties.BoxArray[Index]->GetAlternateImages_Pressed()		// Pressed Texture
								, ButtonProperties.BoxArray[Index]->GetAlternateSizeX()					// Size X
								, ButtonProperties.BoxArray[Index]->GetAlternateSizeY()					// Size Y
								, ButtonProperties.BoxArray[Index]->GetAlternateHoveredSound()			// Hovered Sound
								, ButtonProperties.BoxArray[Index]->GetAlternatePressedSound()			// Pressed Sound
								, ButtonProperties.BoxArray[Index]->GetOwningPlayerController());		// The Player Controller
						}
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
							  ButtonProperties.BoxArray[Index]->GetButtons()						// Buttons
							, ButtonProperties.BoxArray[Index]->GetOwningPlayerController());		// The Player Controller
					}
				}
			}
		}
	}
}

UMenuPadPlusButton* UUserWidget_MenuPadPlus::GetFocusedWidget(TArray<class UMenuPadPlusButton*> Buttons)
{
	for (auto& Widget : Buttons)
		if (Widget->bHasForcedHover)
			return Widget;
	
	return nullptr;
}

UMenuPadPlusButton* UUserWidget_MenuPadPlus::GetFirstWidget()
{
	auto const MenuCount = 0;

	if (UPanelWidget* RootPanel = Cast<UPanelWidget>(GetRootWidget()))
	{
		if (GetNumMenus(ButtonProperties.BoxArray) > MenuCount)
		{
			if ((ButtonProperties.BoxArray[ROOT_MENU_ONE] = Cast<UMenuPadPlusPanelWidget>(RootPanel->GetChildAt(MenuCount))) != 0)
				return ButtonProperties.BoxArray[ROOT_MENU_ONE]->GetFirstWidget();
			else
				return nullptr;
		}
	}

	return nullptr;
}

UMenuPadPlusButton* UUserWidget_MenuPadPlus::GetPreviousWidget()
{
	auto const MenuCount = 1;
	auto VerticalArrayLength = GetNumMenus(ButtonProperties.BoxArray);

	if (VerticalArrayLength > MenuCount)
		for (int32 i = 0; i < VerticalArrayLength; ++i)
			return ButtonProperties.BoxArray[i - 1]->GetFirstWidget();
		
	return nullptr;
}

void UUserWidget_MenuPadPlus::ResetAllWidgetFocus(TArray<class UMenuPadPlusButton*> CurrentButton)
{
	for (auto const& Widget : CurrentButton)
		Widget->ForceNormalText();

	auto const WorldPtr = GetWorld();

	if (ensure(WorldPtr))
	{
		auto PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(WorldPtr, PLAYER_CONTROLLER_INDEX));
		if (PC != nullptr) UMenuPadPlusStatics::SetButtonFocus(GetFirstWidget(), PC);
	}
}
#pragma endregion

#undef LOCTEXT_NAMESPACE