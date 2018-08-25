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

#include "../../Classes/Utilities/MenuPadPlusStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "../../Classes/Widget/UserWidget_MenuPadPlus.h"
#include "../../Classes/Widget/Components/MenuPadPlusButton.h"
#include "../../Classes/Widget/Components/MenuPadPlusVerticalBox.h"
#include "../../Classes/Widget/Components/MenuPadPlusPanelWidget.h"
#include "../../Classes/Widget/MenuPadPlusInterface.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../Classes/GameFramework/MyPlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "Runtime/Engine/Classes/Engine/World.h"

TScriptInterface<IMenuPadPlusInterface> UMenuPadPlusStatics::GetActiveContainer()
{
	TScriptInterface<IMenuPadPlusInterface> retVal = NULL;

	for (TObjectIterator<UObject> Itr; Itr; ++Itr)
	{
		UObject* Object = *Itr;

		if (IMenuPadPlusInterface* Interface = Cast<IMenuPadPlusInterface>(Object))
		{
			if (Interface->bIsActive)
			{
				retVal.SetInterface(Interface);
				retVal.SetObject(Object);
				return retVal;
			}
		}
	}

	return retVal;
}

void UMenuPadPlusStatics::SetWidgetFocus(TScriptInterface<IMenuPadPlusInterface> Container, UMenuPadPlusButton* Widget)
{
	if (!Container)
		return;

	// UnFocus
	if (Container->GetFocusedWidget())
		Container->GetFocusedWidget()->ForceNormalText();

	// Then Focus 
	if (Widget)
		Widget->ForceHoveredText();
}

void UMenuPadPlusStatics::ResetAllWidgetFocus()
{
	for (TObjectIterator<UObject> Itr; Itr; ++Itr)
	{
		UObject* Object = *Itr;

		if (IMenuPadPlusInterface* Interface = Cast<IMenuPadPlusInterface>(Object))
			Interface->ResetAllWidgetFocus();
	}
}

UMenuPadPlusButton* UMenuPadPlusStatics::GetFocusedWidget(TScriptInterface<IMenuPadPlusInterface> Container)
{
	if (Container) 
		return Container->GetFocusedWidget();

	return nullptr;
}

void UMenuPadPlusStatics::SetButtonFocus(class UMenuPadPlusButton* NavigableWidget, class AMyPlayerController* PlayerController)
{
	if (NavigableWidget != nullptr)
	{
		FInputModeUIOnly uiMode;
		uiMode.SetWidgetToFocus(NavigableWidget->GetCachedWidget());
		uiMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		if (PlayerController != nullptr) PlayerController->SetInputMode(uiMode);
	}
}
