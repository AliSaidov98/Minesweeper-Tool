🎮 Minesweeper Editor Tool for Unreal Engine 5

A fully-featured Minesweeper game implemented as an editor tool inside Unreal Engine 5. The tool is built entirely in C++ using Slate and showcases modular editor programming, validation logic, and custom tool UI integration.

● Setup Instructions

Clone the Repository to any location on your system.
Open the project by launching the Minesweeper.uproject file in Unreal Engine 5.
When prompted, compile the project. This will build the custom editor tool located in Plugins/Minesweeper_Tool.
After opening the project, click the Minesweeper button in the main editor toolbar to launch the game tool window. (Window/Minesweeper_Tool)

● Integrating the Plugin Into Your Own Project

If you want to use just the plugin in another Unreal Engine 5 project:

Copy the folder Plugins/Minesweeper_Tool into your own project's Plugins/ directory.
Regenerate project files (Right-click .uproject → Generate Visual Studio project files).
Open your project in Visual Studio and build it.
Launch the project in Unreal Engine 5 and enable the plugin if not already active (Edit → Plugins → Minesweeper Tool).

The Minesweeper editor tool will then be accessible in your project's editor window.

● Features

Slate-based custom window (no UMG)

Grid configuration with input validation

Recursive tile reveal logic

Game over detection with styled popup

Clean and maintainable structure

● Notes & Design Decisions

Built as part of the UE5 project directly, but easily reusable as a standalone plugin.

Uses editor-only dependencies, isolated from runtime modules.

Organized code into logically separated classes and widgets.

Minimalistic UX, no unnecessary visual clutter.

Designed for quick iteration and future extensibility.

● License

This project is licensed under the MIT License.
