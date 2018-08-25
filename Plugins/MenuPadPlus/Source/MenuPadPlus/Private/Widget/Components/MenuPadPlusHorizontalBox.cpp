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

#include "../../../Classes/Widget/Components/MenuPadPlusHorizontalBox.h"
#include "../../../Classes/Widget/UserWidget_MenuPadPlus.h"
#include "../../../Classes/Widget/Components/MenuPadPlusButton.h"
#include "../../../Classes/Utilities/MenuPadPlusStatics.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"
#include "Runtime/UMG/Public/Components/HorizontalBoxSlot.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "MenuPadPlus"

UMenuPadPlusHorizontalBox::UMenuPadPlusHorizontalBox(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsVariable = false;

	SHorizontalBox::FArguments Defaults;
	Visibility = UWidget::ConvertRuntimeToSerializedVisibility(Defaults._Visibility.Get());
}

void UMenuPadPlusHorizontalBox::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Buttons.Empty();
	AlternateImages.Empty();
	AlternateHoveredSound = nullptr;
	AlternatePressedSound = nullptr;
	MyHorizontalBox.Reset();
}

UClass* UMenuPadPlusHorizontalBox::GetSlotClass() const
{
	return UHorizontalBoxSlot::StaticClass();
}

#pragma region UPanelWidget Interface
// Add Child
void UMenuPadPlusHorizontalBox::OnSlotAdded(UPanelSlot* InSlot)
{
	Super::OnSlotAdded(InSlot);

	// Add the child to the live canvas if it already exists
	if (MyHorizontalBox.IsValid())
	{
		CastChecked<UHorizontalBoxSlot>(InSlot)->BuildSlot(MyHorizontalBox.ToSharedRef());
	}
}

// Remove Child
void UMenuPadPlusHorizontalBox::OnSlotRemoved(UPanelSlot* InSlot)
{
	Super::OnSlotRemoved(InSlot);

	// Remove the widget from the live slot if it exists.
	if (MyHorizontalBox.IsValid())
	{
		TSharedPtr<SWidget> Widget = InSlot->Content->GetCachedWidget();
		if (Widget.IsValid())
		{
			MyHorizontalBox->RemoveSlot(Widget.ToSharedRef());
		}
	}
}
#pragma endregion

UHorizontalBoxSlot* UMenuPadPlusHorizontalBox::AddChildToHorizontalBox(UWidget* Content)
{
	return Cast<UHorizontalBoxSlot>(Super::AddChild(Content));
}

TSharedRef<SWidget> UMenuPadPlusHorizontalBox::RebuildWidget()
{
	MyHorizontalBox = SNew(SHorizontalBox);

	for (UPanelSlot* PanelSlot : Slots)
	{
		if (UHorizontalBoxSlot* TypedSlot = Cast<UHorizontalBoxSlot>(PanelSlot))
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyHorizontalBox.ToSharedRef());
		}
	}

	return MyHorizontalBox.ToSharedRef();
}

#if WITH_EDITOR
const FText UMenuPadPlusHorizontalBox::GetPaletteCategory()
{
	return LOCTEXT("MenuPadPlus", "Menu Pad Plus");
}
#endif

#undef LOCTECT_NAMESPACE