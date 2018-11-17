# MenuPadPlus
An Unreal Engine 4 UI Plugin

MenuPadPlus is an Unreal Engine 4 plugin that allows ready-to-use gamepads in UMG Blueprints.  It is written in C++. 
It is released under the terms of the MIT License for educational, research and/or 
commercial purposes.

## PROJECT DETAILS

MenuPadPlus is designed to allow gamepads to work within minutes for your UMG Blueprints in Unreal Engine 4.
I developed it in one of my games and later adapted it as this open source plugin.  It's designed for any type of navigable menu
and allows for changes in the UMG Blueprints graph.

**Features**

- Ready-to-use out of the box
- Supports up to 12 Navigable Menus
- Supports Alternate Button Images
- Custom UserWidget that you re-parent in your own Widget Blueprint which handles everything
- Custom Button that has optional text, if you need it
- An API that advanced C++ users can use to build upon

## GETTING STARTED

Video Tutorial [here](https://youtu.be/rJ23w__VuhQ)

The MenuPadPlus repository includes the UE4 project MenuPadPlusExample. If you do not wish to use this project example, 
move the Plugins folder of this repository to the root directory of your game and rebuild in Visual Studio.  Build out your Plugins
folders in Visual Studio with "Add Filter" then drag in each file.

##### **1. Create a Widget Blueprint**
![Alt text](/Screenshots/Directions1.PNG?raw=true)
##### 2. Re-parent your Widget Blueprint with UserWidget_MenuPadPlus
![Alt text](/Screenshots/Directions2.png?raw=true)
##### 3. Go to the Designer, and open the MenuPadPlus option in the Palette panel to reveal options.  
![Alt text](/Screenshots/Directions3.PNG?raw=true)
##### 4. Drag in a Vertical/Horizontal Box and then add Buttons to it.
![Alt text](/Screenshots/Directions4.PNG?raw=true)
##### 5. Design your menu to your liking
![Alt text](/Screenshots/Directions5.PNG?raw=true)
##### 6. Create a HUD Blueprint and create your widget from BeginPlay. (Make sure your GameMode has your HUD Blueprint set by default)
![Alt text](/Screenshots/Directions6.PNG?raw=true)
##### 7. Press Play and Enjoy MenuPadPlus!
![Alt text](/Screenshots/Directions7.PNG?raw=true)

If you are using your own Player Controller class, make changes to the source where necessary and move the 
class to your Plugin directory like in this example or else your project will not compile. 

**Include these Dependency Modules in your Project's Build.cs file:**
```
PublicDependencyModuleNames.AddRange(new string[] { 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"UMG",
				"MenuPadPlus" });

PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
```

When using C++, you should follow the MyHUD class example to create a widget.  If you make changes to the source code of MenuPadPlus,
you must rebuild both your project and the plugin in Visual Studio outside of Unreal Engine.

## NOTES

Tested to work in v4.20 and v4.21 for Windows.  This software requires one gamepad/controller.  MenuPadPlus is shipped as-is without warranty.
