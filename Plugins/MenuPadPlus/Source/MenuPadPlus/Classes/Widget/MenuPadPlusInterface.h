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
#include "MenuPadPlusInterface.generated.h"

class UMenuPadPlusButton;
class AMyPlayerController;

UINTERFACE(Blueprintable)
class MENUPADPLUS_API UMenuPadPlusInterface : public UInterface
{
	GENERATED_BODY()

};

class MENUPADPLUS_API IMenuPadPlusInterface
{
	GENERATED_BODY()

public:
	
	// Interface Status Variables
	bool Initialized;
	bool IsActive;

	// Allows reference to interface derived from UObject
	TScriptInterface<class IMenuPadPlusInterface> Parent;

	//~ Begin IMenuPadPlusInterface
	virtual void Startup();
	virtual void Shutdown();
	virtual void BindData() = 0;
	virtual void UnBindData() = 0;
	virtual UMenuPadPlusButton* GetFocusedWidget() { return nullptr; }
	virtual UMenuPadPlusButton* GetFirstWidget() { return nullptr; }
	virtual AMyPlayerController* GetOwningPlayerController() = 0;
	virtual void ResetAllWidgetFocus() = 0;
	virtual bool DoesContainButtons() = 0;
	//~ End IMenuPadPlusInterface

protected:

	// Constructor (Allowed only for child classes)
	explicit IMenuPadPlusInterface() {}
	IMenuPadPlusInterface(const IMenuPadPlusInterface&) = delete;

	// Protected assignment operator to prevent assignment on reference to this interface
	IMenuPadPlusInterface &operator=(const IMenuPadPlusInterface&) { return *this; }

};