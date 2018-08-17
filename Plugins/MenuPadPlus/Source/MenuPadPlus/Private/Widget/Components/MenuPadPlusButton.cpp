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

#include "../../../Classes/Widget/Components/MenuPadPlusButton.h"
#include "Runtime/SlateCore/Public/Widgets/SNullWidget.h"
#include "Runtime/SlateCore/Public/Widgets/DeclarativeSyntaxSupport.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/UMG/Public/Components/ButtonSlot.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Engine/Font.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "../../../Classes/GameFramework/MyPlayerController.h"

#define LOCTEXT_NAMESPACE "MenuPadPlus"

UMenuPadPlusButton::UMenuPadPlusButton(const FObjectInitializer& ObjectInitializer)	: UButton(ObjectInitializer)
{
	bIsVariable = true;
	TextShadowOffset = FVector2D(1.0f, 1.0f);
	TextColorAndOpacity = FLinearColor::White;
	TextShadowColorAndOpacity = FLinearColor::Transparent;
	
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		TextFont = FSlateFontInfo(RobotoFontObj.Object, 24, FName("Bold"));
	}

	OnHovered.AddDynamic(this, &UMenuPadPlusButton::OnHoveredLogic);

	hasForcedNormal = false;
	hasForcedHover = false;
	hasForcedPressed = false;
	canPlayHoveredSound = false;
}

TSharedRef<SWidget> UMenuPadPlusButton::RebuildWidget()
{
	OptionalTextBlock = SNew(STextBlock);
	OptionalTextBlock->SetText(Text);
	OptionalTextBlock->SetColorAndOpacity(TextColorAndOpacity);
	OptionalTextBlock->SetFont(TextFont);
	OptionalTextBlock->SetJustification(TextJustification);
	OptionalTextBlock->SetMargin(TextMargin);
	
	MyButton = SNew(SButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
		.OnHovered_UObject(this, &ThisClass::SlateHandleHovered)
		.OnUnhovered_UObject(this, &ThisClass::SlateHandleUnhovered)
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.IsFocusable(IsFocusable)
		.Content()
		[
			OptionalTextBlock.ToSharedRef()
		]
	;

	if (GetChildrenCount() > 0)
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	
	return MyButton.ToSharedRef();
}

void UMenuPadPlusButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TAttribute<FText> RenderText = (TextDelegate.IsBound()) ? PROPERTY_BINDING(FText, Text) : Text;

	OptionalTextBlock->SetText(RenderText);
	OptionalTextBlock->SetColorAndOpacity(TextColorAndOpacity);
	OptionalTextBlock->SetFont(TextFont);
	OptionalTextBlock->SetJustification(TextJustification);
	OptionalTextBlock->SetMargin(TextMargin);
}

void UMenuPadPlusButton::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	OptionalTextBlock.Reset();
}

// Force text highlighting behavior
void UMenuPadPlusButton::ForceNormal()
{
	OptionalTextBlock->SetColorAndOpacity(TextColorAndOpacity);
	if (!hasForcedNormal) hasForcedNormal = true;
	if (hasForcedHover) hasForcedHover = false;
	if (hasForcedPressed) hasForcedPressed = false;
}

void UMenuPadPlusButton::ForceHover()
{
	OptionalTextBlock->SetColorAndOpacity(TextColorAndOpacityHover);
	if(!hasForcedHover) hasForcedHover = true;
	if (hasForcedNormal) hasForcedNormal = false;
	if (hasForcedPressed) hasForcedPressed = false;
}

void UMenuPadPlusButton::ForcePressed()
{
	OptionalTextBlock->SetColorAndOpacity(TextColorAndOpacityPressed);
	if (!hasForcedPressed) hasForcedPressed = true;
}

// Customize OnHovered Delegate
void UMenuPadPlusButton::OnHoveredLogic()
{
	auto const world = GetWorld();

	if (world != nullptr)
	{
		auto PC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(world, 0));
		if (PC != nullptr) this->SetUserFocus(PC);
	}
}

#if WITH_EDITOR
const FText UMenuPadPlusButton::GetPaletteCategory()
{
	return LOCTEXT("MenuPadPlus", "Menu Pad Plus");
}
#endif

#undef LOCTEXT_NAMESPACE