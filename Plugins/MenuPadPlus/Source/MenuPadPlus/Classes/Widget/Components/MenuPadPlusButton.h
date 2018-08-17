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
#include "Runtime/UMG/Public/Components/Button.h"
#include "Misc/Attribute.h"
#include "Layout/Margin.h"
#include "Components/Widget.h"
#include "Framework/Text/TextLayout.h"
#include "MenuPadPlusButton.generated.h"

class STextBlock;
class IMenuPadPlusInterface;

/**
* The button is a click-able primitive widget to enable basic interaction, you
* can place any other widget inside a button to make a more complex and
* interesting click-able element in your UI.
*
* * Single Child
* * Clickable
* * Text (Optional)
*/
UCLASS(Blueprintable, BlueprintType)
class MENUPADPLUS_API UMenuPadPlusButton : public UButton
{
	GENERATED_BODY()

public:

	UMenuPadPlusButton(const FObjectInitializer& ObjectInitializer);
	
	// Bindings for Text Color
	PROPERTY_BINDING_IMPLEMENTATION(FText, Text);
	PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, TextColorAndOpacity);
	PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, TextColorAndOpacityHover);
	PROPERTY_BINDING_IMPLEMENTATION(FSlateColor, TextColorAndOpacityPressed);
	PROPERTY_BINDING_IMPLEMENTATION(FLinearColor, TextShadowColorAndOpacity);

	// The Text
	UPROPERTY(Category = "Text", EditAnywhere, meta = (MultiLine = "true"))
	FText Text;

	// A delegate to allow logic to drive the text of the widget 
	UPROPERTY()
	FGetText TextDelegate;

	// Text justification
	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ETextJustify::Type> TextJustification;
	
	// Margin
	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadOnly)
	FMargin TextMargin;

	// Normal Color and Opacity
	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadOnly)
	FSlateColor TextColorAndOpacity;

	// A delegate for Normal Color and Opacity
	UPROPERTY()
	FGetSlateColor TextColorAndOpacityDelegate;

	// Hover Color and Opacity 
	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadOnly)
	FSlateColor TextColorAndOpacityHover;

	// A delegate for Hover Color and Opacity
	UPROPERTY()
	FGetSlateColor TextColorAndOpacityHoverDelegate;

	// Pressed  Color and Opacity 
	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadOnly)
	FSlateColor TextColorAndOpacityPressed;

	// A delegate for Pressed Color and Opacity
	UPROPERTY()
	FGetSlateColor TextColorAndOpacityPressedDelegate;

	// The Font 
	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadOnly)
	FSlateFontInfo TextFont;

	// The direction the shadow is cast
	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadOnly)
	FVector2D TextShadowOffset;

	// Shadow Color 
	UPROPERTY(Category = "Text", EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Shadow Color"))
	FLinearColor TextShadowColorAndOpacity;

	// A delegate for the Shadow Color and Opacity
	UPROPERTY()
	FGetLinearColor TextShadowColorAndOpacityDelegate;
		
	UPROPERTY(Category = "MenuPadPlus | Widgets | Navigation", BlueprintReadOnly)
	TScriptInterface<IMenuPadPlusInterface> OwnerContainer;
 
	UFUNCTION(Category = "Button", BlueprintCallable)
	virtual void ForceNormal();

	UFUNCTION(Category = "Button", BlueprintCallable)
	virtual void ForceHover();

	UFUNCTION(Category = "Button", BlueprintCallable)
	virtual void ForcePressed();

	bool hasForcedNormal;
	bool hasForcedHover;
	bool hasForcedPressed;
	bool canPlayHoveredSound;

	// Customize OnHovered Delegate
	UFUNCTION(Category=Default)
	virtual void OnHoveredLogic();

	// Pointer to the underlying slate button owned by this UWidget
	TSharedPtr<STextBlock> OptionalTextBlock;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
		
protected:

	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void SynchronizeProperties() override;
	//~ End UWidget Interface

	//~ Begin UVisual Interface
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	//~ End UVisual Interface

};