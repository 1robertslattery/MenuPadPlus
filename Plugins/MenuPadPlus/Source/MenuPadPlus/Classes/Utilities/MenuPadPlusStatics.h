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
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MenuPadPlusStatics.generated.h"

class UUserWidget_MenuPadPlus;
class UMenuPadPlusButton;
class UMenuPadPlusInterface;

/**
* Static utilities for focusable buttons via MenuPadPlus
*/
UCLASS(Blueprintable, BlueprintType)
class MENUPADPLUS_API UMenuPadPlusStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	// **NOTE: Overriden by UUserWidget_MenuPadPlus** Used for changing navigation of VerticalBox/HorizontalBox container.
	UFUNCTION(Category = "MenuPadPlus | Utilities", BlueprintCallable)
	static void SetNewContainer(TScriptInterface<IMenuPadPlusInterface> Container, bool PreserveForCancel = false);

	// Get navigable container
	UFUNCTION(Category = "MenuPadPlus | Utilities", BlueprintCallable)
	static TScriptInterface<IMenuPadPlusInterface> GetActiveContainer();

	// Used for changing focus on a button inside a navigable container. NOTE: Currently, only implements Text changes
	UFUNCTION(Category = "MenuPadPlus | Utilities", BlueprintCallable)
	static void SetWidgetFocus(TScriptInterface<IMenuPadPlusInterface> Container, UMenuPadPlusButton* NavigableWidget);

	// Unfocus all navigable widgets for all containers
	UFUNCTION(Category = "MenuPadPlus | Utilities", BlueprintCallable)
	static void ResetAllWidgetFocus();

	// Get the hovered button inside a container
	UFUNCTION(Category = "MenuPadPlus | Utilities", BlueprintCallable)
	static UMenuPadPlusButton* GetFocusedWidget(TScriptInterface<IMenuPadPlusInterface> Container);

	// Disable interface for the current container
	UFUNCTION(Category = "MenuPadPlus | Utilities", BlueprintCallable)
	static bool DisableInterface(TScriptInterface<IMenuPadPlusInterface> Container);

	//UFUNCTION(Category = "MenuPadPlus | Utilities", BlueprintCallable)
	//static bool EnableInterface(TScriptInterface<IMenuPadPlusInterface> Container);

	// Sets Focus on a Button in Menu, using a Player Controller
	UFUNCTION(Category = "MenuPadPlus | Utilities", BlueprintCallable)
	static void SetButtonFocus(class UMenuPadPlusButton* NavigableWidget, class AMyPlayerController* InPC);


};