# MenuPadPlus

MenuPadPlus is an Unreal Engine 4 plugin that allows ready-to-use gamepads in UMG Blueprints.  It is written in C++. 
It is released under the terms of the MIT License for educational, research and/or 
commercial purposes.

## PROJECT DETAILS

MenuPadPlus is designed to allow gamepads to work within minutes for your UMG Blueprints in Unreal Engine 4.
I developed it in one of my games and later adapted it as this open source plugin.  It's designed for any type of navigable menu
and allows for changes in UMG Blueprints graph.

**Features**

- Ready-to-use out of the box
- Supports up to 8 Navigable Menus
- Custom UserWidget that you re-parent in your own blueprint which handles everything
- Custom Button that has optional text, if you need it
- An API that advanced C++ users can use to build upon

## GETTING STARTED

The MenuPadPlus repository includes the UE4 project MenuPadPlusProject. If you do not wish to use this project example, 
move the Plugins folder of this repository to the root directory of your game and rebuild in Visual Studio. If you are using your own
Player Controller class, make changes to the source where necessary and move the class to your Plugin directory like in this example or else 
your project will not compile. 

**Include these Dependency Modules in your Project's Build.cs file:**
```
PublicDependencyModuleNames.AddRange(new string[] { 
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"UMG",
				"GameplayTasks",
				"MenuPadPlus" });

PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
```

You should follow the MyHUD class example to create a widget.  If you make changes to the source code of MenuPadPlus,
you must rebuild both your project and the plugin in Visual Studio outside of Unreal Engine.

## NOTES

This software is a work in progress.  I'm working on making alternate images usable for buttons. Video demos coming soon. 
Compiled with v4.20.  MenuPadPlus is shipped as-is without warranty.
