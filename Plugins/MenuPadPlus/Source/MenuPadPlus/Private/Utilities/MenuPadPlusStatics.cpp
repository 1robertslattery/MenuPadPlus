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

// NOT IMPLEMENTED
void UMenuPadPlusStatics::SetNewContainer(TScriptInterface<IMenuPadPlusInterface> Container, bool PreserveForCancel)
{
	if (!Container || !Container->DoesContainButtons())
		return;

	// Get Container
	IMenuPadPlusInterface* CurrentContainer = (IMenuPadPlusInterface*)(UMenuPadPlusStatics::GetActiveContainer().GetInterface());
	TScriptInterface<IMenuPadPlusInterface> CurrentContainerInterface = UMenuPadPlusStatics::GetActiveContainer();

	// Shutdown if not preserving container
	if (PreserveForCancel == false)
		if (CurrentContainer != nullptr) 
			CurrentContainer->Shutdown();
	
	// Startup New Container
	Container->Startup();
	if (!Container->IsActive) Container->IsActive = true;

	// Set the current container as parent of the new one
	if (PreserveForCancel && CurrentContainer)
	{
		if (Container->IsActive) CurrentContainer->IsActive = false;
		Container->Parent = CurrentContainerInterface;
	}

	// Get Button to focus
	UMenuPadPlusButton* ButtonToFocus = (Container->GetFocusedWidget()) ? Container->GetFocusedWidget() : Container->GetFirstWidget();
	
	// Set Focus
	UMenuPadPlusStatics::SetWidgetFocus(Container, ButtonToFocus);
}

TScriptInterface<IMenuPadPlusInterface> UMenuPadPlusStatics::GetActiveContainer()
{
	TScriptInterface<IMenuPadPlusInterface> retVal = NULL;

	for (TObjectIterator<UObject> Itr; Itr; ++Itr)
	{
		UObject* Object = *Itr;

		if (IMenuPadPlusInterface* Interface = Cast<IMenuPadPlusInterface>(Object))
		{
			//if (Interface->IsActive)
			//{
				retVal.SetInterface(Interface);
				retVal.SetObject(Object);
				return retVal;
			//}
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
		Container->GetFocusedWidget()->ForceNormal();

	// Then Focus 
	if (Widget)
		Widget->ForceHover();
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

bool UMenuPadPlusStatics::DisableInterface(TScriptInterface<IMenuPadPlusInterface> Container)
{
	IMenuPadPlusInterface* CurrentContainer = (IMenuPadPlusInterface*)(Container.GetInterface());

	if (CurrentContainer)
	{
		if (CurrentContainer->Parent) 
			DisableInterface(CurrentContainer->Parent);

		CurrentContainer->Shutdown();
		return true;
	}

	return false;
}

//bool UMenuPadPlusStatics::EnableInput(TScriptInterface<IMenuPadPlusInterface> Container)
//{
//	IMenuPadPlusInterface* CurrentContainer = (IMenuPadPlusInterface*)(Container.GetInterface());
//
//	if (CurrentContainer)
//	{
//		SetNewContainer(Container);
//		return true;
//	}
//
//	return false;
//}

void UMenuPadPlusStatics::SetButtonFocus(class UMenuPadPlusButton* NavigableWidget, class AMyPlayerController* InPC)
{
	if (NavigableWidget != nullptr)
	{
		FInputModeUIOnly uiMode;
		uiMode.SetWidgetToFocus(NavigableWidget->GetCachedWidget());
		uiMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		if (InPC != nullptr) InPC->SetInputMode(uiMode);
	}
}
