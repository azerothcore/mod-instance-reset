# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

## mod-instance-reset

- Latest build status with azerothcore:

[![Build Status](https://github.com/azerothcore/mod-instance-reset/workflows/core-build/badge.svg)](https://github.com/azerothcore/mod-instance-reset)

## Description

Talk to the NPC to reset the instances you already visited. By default, it only resets for normal difficulty, if you want to reset for all difficulties, just edit the .conf file.

## Why use this?

The NPC can be spawned in a specific zone only accessible after completing a quest or having an item. It's up to you to find uses.

## How to use ingame

Talk to the npc, then you have not longer instances saves

![WoWScrnShot_031424_230956](https://github.com/azerothcore/mod-instance-reset/assets/2810187/1cba1337-c244-401f-91a0-744d167d3c5e)

![WoWScrnShot_031424_231122](https://github.com/azerothcore/mod-instance-reset/assets/2810187/63afd0cc-f968-4e8c-b141-6a198b25a16e)

## Installation

1. Simply place the module under the `modules` directory of your AzerothCore source.
2. Re-run cmake and launch a clean build of AzerothCore.
3. Add the npc via script or command wherever you like.
4. `npc add 300000` or `npc add temp 300000` (If you want to add it temporarily)

## Edit module configuration (optional)

- In the folder where authserver.exe and worldserver.exe are located, you find a folder called configs and within it, one called modules
- Copy the file instance-reset.conf.dist, and rename it instance-reset.conf (but do not delete the original, both must exist)
- Edit the file instance-reset.conf, having as a backup the other file, where future configurations that the community may add will be added.

## Credits

- Nefertumm (author): [GitHub](https://github.com/Nefertumm)
- AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
