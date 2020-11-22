# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore
## mod-instance-reset
- Latest build status with azerothcore: [![Build Status](https://github.com/azerothcore/mod-instance-reset/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/azerothcore/mod-instance-reset)

## Description

Talk to the NPC to reset the instances you already visited. By default, it only resets for normal difficulty, if you want to reset for all difficulties, just edit the .conf file.

## Why use this?
The NPC can be spawned in a specific zone only accessible after completing a quest or having an item. It's up to you to find uses.

## How to use ingame

Talk to the npc, then you have not longer instances saves

## Requirements

This module requires:

- AzerothCore v1.0.1+


## Installation

```
1) Simply place the module under the `modules` directory of your AzerothCore source. 
2) Import the SQL manually to the world Database.
3) Re-run cmake and launch a clean build of AzerothCore.
```

## Edit module configuration (optional)

If you need to change the module configuration, go to your server configuration folder (where your `worldserver` or `worldserver.exe` is), copy `save_cleaner.conf.dist` to `save_cleaner.conf` and edit that new file.


## Credits

Nefertumm (author):

Barbz: best guy

Talamortis: almost best guy

AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
