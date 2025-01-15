# Compiling

## CMake

First you need to select a configure preset. See all available presets with
`cmake --list-presets`. You can select a preset with `cmake --preset debug`.

Once you selected a configure preset, you also need to select a build preset.
`cmake --build --list-presets` outputs the available presets.
To select one simply use the command `cmake --build --preset app-debug`.

If you've managed to do these then you should have a build directory filled
with all kinds of compiled files, and an executable binary.

You only need to do this once, then if you enter the build directory of
the preset, you can re-compile the code with `ninja` every time. If you change
your preset e.g.: for release build, you should re-do the steps above.

I do not have a Windows setup, so you have to figure out how to modify
the pre-included windows preset, so it can be compiled too. Add instructions
here for future reference.


## Variables

You can add compile-time variables to CMake to enable branching. See example
using the `set() function` in the `CMakeLists.txt` file. Alternatively you
can define variables in the `CMakePresets.json` file which can be accessed
inside the code. This will be useful for cross-compiling.

# Commits

Use the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
for the commit message format, this helps with semantic versioning,
and makes the commits more readable.
