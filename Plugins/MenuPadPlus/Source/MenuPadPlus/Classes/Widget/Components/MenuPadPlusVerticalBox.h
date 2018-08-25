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
#include "Widgets/SWidget.h"
#include "Widgets/SBoxPanel.h"
#include "MenuPadPlusPanelWidget.h"
#include "MenuPadPlusVerticalBox.generated.h"

class UVerticalBoxSlot;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMenuPadPlusVerticalBoxChangedChild, int32, ChildIndex);

/**
* A navigable vertical box widget is a layout panel allowing child widgets to be automatically laid out
* vertically and user can navigate through their navigable child widgets
*
* * Many Children
* * Flows Vertical
*/
UCLASS(AutoExpandCategories = ("MenuPadPlus | Widgets"), meta = (DisplayName = "VerticalBox"))
class MENUPADPLUS_API UMenuPadPlusVerticalBox : public UMenuPadPlusPanelWidget
{
	GENERATED_BODY()

public:

	// Constructor
	UMenuPadPlusVerticalBox(const FObjectInitializer& ObjectInitializer);
		
	/**  */
	UFUNCTION(BlueprintCallable, Category = "Panel")
	UVerticalBoxSlot* AddChildToVerticalBox(UWidget* Content);

#if WITH_EDITOR
	//~ Begin UWidget Interface
	virtual const FText GetPaletteCategory() override;
	//~ End UWidget Interface
#endif
	
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

protected:

	//~ Begin UPanelWidget
	virtual UClass* GetSlotClass() const override;
	virtual void OnSlotAdded(UPanelSlot* Slot) override;
	virtual void OnSlotRemoved(UPanelSlot* Slot) override;
	//~ End UPanelWidget

	TSharedPtr<class SVerticalBox> MyVerticalBox;

	//~ Begin UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget interface

public:
			
	UPROPERTY(BlueprintAssignable, Category = "MenuPadPlus | Widgets")
	FMenuPadPlusVerticalBoxChangedChild OnVerticalBoxChangedChild;

};