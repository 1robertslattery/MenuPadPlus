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

#include "../../../Classes/Widget/Components/MenuPadPlusPanelWidget.h"
#include "../../../Classes/Widget/Components/MenuPadPlusButton.h"
#include "../../../Classes/Utilities/MenuPadPlusStatics.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/Texture.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "../../../Classes/GameFramework/MyPlayerController.h"

#define LOCTEXT_NAMESPACE "MenuPadPlus"

const int32 UMenuPadPlusPanelWidget::PLAYER_CONTROLLER_INDEX = 0;

void UMenuPadPlusPanelWidget::BindData()
{
	// Set data related to this class
}

void UMenuPadPlusPanelWidget::UnBindData()
{
	// Delete data related to this class
}

// Good for tracking status
UMenuPadPlusButton* UMenuPadPlusPanelWidget::GetFocusedWidget()
{
	for (auto& Widget : Buttons)
	{
		if (Widget->bHasForcedHover)
			return Widget;
	}

	return nullptr;
}

UMenuPadPlusButton* UMenuPadPlusPanelWidget::GetFirstWidget() const
{
	return Buttons[0];
}

AMyPlayerController* UMenuPadPlusPanelWidget::GetOwningPlayerController() const
{
	return Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), PLAYER_CONTROLLER_INDEX));
}

bool UMenuPadPlusPanelWidget::DoesContainButtons()
{
	return Buttons.Num() > 0;
}

void UMenuPadPlusPanelWidget::ResetAllWidgetFocus()
{
	for (auto const& Widget : Buttons)
		Widget->ForceNormalText();

	if (GetOwningPlayerController() != nullptr) UMenuPadPlusStatics::SetButtonFocus(GetFirstWidget(), GetOwningPlayerController());
}

#undef LOCTEXT_NAMESPACE