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

## New features

Inside the configuration file, you can find new options.

```
#
#   instanceReset.TransactionType
#       Descripcion: Positive integer value, which determines the type of transaction to be carried out with the npc.
#       Default: 0 (You are not charged anything)
#       Value:
#           0 (You are not charged anything)
#           1 (You are charged with the token)
#           2 (You are charged with money)
#           3 (You are charged money and token)
#
```

- This option allows you to establish the type of transaction that the player must make with the NPC. Token, Gold or both or neither.
- You can also choose the token or item, and the quantity. Just like gold.
- The 4 options were tested with the `.reload config` command and they seem to work perfectly.
- Attached are images of the tests carried out.

![WoWScrnShot_032624_054034](https://github.com/azerothcore/mod-instance-reset/assets/2810187/712c9c3e-9c81-47fe-a7bc-7d71a76bda66)

![WoWScrnShot_032624_054056](https://github.com/azerothcore/mod-instance-reset/assets/2810187/6099c9be-7a1c-48c8-a99d-95c57003caf9)

![WoWScrnShot_032624_054108](https://github.com/azerothcore/mod-instance-reset/assets/2810187/bfe468f3-61ac-4786-8ee9-129e6a3a33e1)

![WoWScrnShot_032624_054128](https://github.com/azerothcore/mod-instance-reset/assets/2810187/fc3f27e4-0715-43a4-a14c-df35a9c7a10e)

![WoWScrnShot_032624_054151](https://github.com/azerothcore/mod-instance-reset/assets/2810187/fe0a84e1-d019-4c5f-81a6-12f03e316967)

![WoWScrnShot_032624_054313](https://github.com/azerothcore/mod-instance-reset/assets/2810187/92fe5951-a749-44cd-85ee-b5bf12d2e827)

![WoWScrnShot_032624_054335](https://github.com/azerothcore/mod-instance-reset/assets/2810187/e3439e51-b2bb-4bab-b048-422e9a39c390)

![WoWScrnShot_032624_054343](https://github.com/azerothcore/mod-instance-reset/assets/2810187/e1316fa3-55e7-4c03-bb18-19c97e5c60a4)

![WoWScrnShot_032624_054405](https://github.com/azerothcore/mod-instance-reset/assets/2810187/22bd5dbb-acd8-418c-a84f-342f6a1bf4e2)

![WoWScrnShot_032624_054416](https://github.com/azerothcore/mod-instance-reset/assets/2810187/8a688bbf-2fb3-4c84-9361-aa49250b5c42)

![WoWScrnShot_032624_054452](https://github.com/azerothcore/mod-instance-reset/assets/2810187/532870e1-1e2a-42cd-844a-dfd899250059)

![WoWScrnShot_032624_054458](https://github.com/azerothcore/mod-instance-reset/assets/2810187/e01c9c0d-8e8e-4088-b3c0-f588b98d0dbe)

## Credits

- Nefertumm (author): [GitHub](https://github.com/Nefertumm)
- AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
