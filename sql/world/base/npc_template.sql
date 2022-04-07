-- NPC TEMPLATE FOR mod-instance-reset

SET
@Entry      := 300000,
@Model      := 24877,
@Name       := "Cromi",
@Title      := "Instance Reset";

-- NPC
DELETE FROM `creature_template` WHERE `entry` = @Entry;

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`) VALUES
(@Entry, @Model, @Name, @Title, "Speak", 0, 80, 80, 35, 0, 1, 1.14286, 1, 0, 1, 2, 7, 138936390, 1, 2, "instanceReset");

UPDATE `creature_template` SET `npcflag`=`npcflag`|1 WHERE `entry`=@Entry;

DELETE FROM `creature_template_locale` WHERE `entry`=@Entry AND `locale` IN ('esES', 'esMX');

INSERT INTO `creature_template_locale` (`entry`, `locale`, `Name`, `Title`, `VerifiedBuild`) VALUES
(@Entry, 'esES', @Name, 'Reinicio de instancias', 0),
(@Entry, 'esMX', @Name, 'Reinicio de instancias', 0);
