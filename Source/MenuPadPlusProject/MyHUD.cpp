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

#include "MyHUD.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"

// MenuPadPlus Plugin Includes
#include "../../Plugins/MenuPadPlus/Source/MenuPadPlus/Classes/Widget/UserWidget_MenuPadPlus.h"
#include "../../Plugins/MenuPadPlus/Source/MenuPadPlus/Classes/Widget/Components/MenuPadPlusButton.h"
#include "../../Plugins/MenuPadPlus/Source/MenuPadPlus/Classes/Utilities/MenuPadPlusStatics.h"
#include "../../Plugins/MenuPadPlus/Source/MenuPadPlus/Classes/GameFramework/MyPlayerController.h"

AMyHUD::AMyHUD()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					MenuPadPlus
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UUserWidget_MenuPadPlus> WidgetAsset(TEXT("/Game/UI/MainMenu_Mixed"));
	if (WidgetAsset.Succeeded()) MenuWidgetBlueprint = WidgetAsset.Class;
	MenuPtr = nullptr;
}

#pragma region Actor Interface
void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					MenuPadPlus
	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	InitMenuPadPlus();
}
#pragma endregion

#pragma region MenuPadPlus
// Create widget and add to viewport
void AMyHUD::InitMenuPadPlus()
{
	auto const world = GetWorld();

	if (world != nullptr)
	{
		auto PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(world, 0));

		if (PC != nullptr)
		{
			if (MenuWidgetBlueprint != NULL)
			{
				MenuPtr = CreateWidget<UUserWidget_MenuPadPlus>(world, MenuWidgetBlueprint);

				if (MenuPtr != nullptr)
				{
					MenuPtr->AddToViewport();

					// Sets Focus on a Button in Menu, using a Player Controller
					UMenuPadPlusStatics::SetButtonFocus(MenuPtr->GetFirstWidget(), PC);
				}
			}
		}
	}
}
#pragma endregion

