#include "loader.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "Language.h"
#include "Chat.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"

static bool instancereset_enable;
static bool instancereset_normalmodeonly;

void GossipSetText(Player* player, std::string message, uint32 textID)
{
    WorldPacket data(SMSG_NPC_TEXT_UPDATE, 100);
    data << textID;
    for (uint8 i = 0; i < MAX_GOSSIP_TEXT_OPTIONS; ++i)
    {
        data << float(0);
        data << message;
        data << message;
        data << uint32(0);
        data << uint32(0);
        data << uint32(0);
        data << uint32(0);
        data << uint32(0);
        data << uint32(0);
        data << uint32(0);
    }
    player->GetSession()->SendPacket(&data);
}

class InstanceResetAnnouncer : public PlayerScript
{
public:
    InstanceResetAnnouncer() : PlayerScript("InstanceResetAnnouncer") {}

    void OnLogin(Player* player)
    {
        if (sConfigMgr->GetOption<bool>("instanceResetAnnouncer.announceEnable", true))
        {
            std::string message = "";
            switch (player->GetSession()->GetSessionDbLocaleIndex())
            {
                case LOCALE_enUS:
                case LOCALE_koKR:
                case LOCALE_frFR:
                case LOCALE_deDE:
                case LOCALE_zhCN:
                case LOCALE_zhTW:
                case LOCALE_ruRU:
                {
                    message = "This server is running the |cff4CFF00Instance Reset |rmodule.";
                    break;

                }
                case LOCALE_esES:
                case LOCALE_esMX:
                {
                    message = "Este servidor está ejecutando el módulo |cff4CFF00Instance reset|r";
                    break;
                }
            }
            ChatHandler(player->GetSession()).SendSysMessage(message);
        }
    }
};

class instanceResetConfigLoad : public WorldScript {
public:

    instanceResetConfigLoad() : WorldScript("instanceResetConfigLoad") { }

    void OnBeforeConfigLoad(bool /*reload*/) override {
        instancereset_enable = sConfigMgr->GetOption<bool>("instanceReset.Enable", 1);
        instancereset_normalmodeonly = sConfigMgr->GetOption<bool>("instanceReset.NormalModeOnly", 0);
    }
};

class instanceReset : public CreatureScript
{
public:
    instanceReset() : CreatureScript("instanceReset") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (instancereset_enable) {
            ClearGossipMenuFor(player);
            std::string gossipText = "";
            std::string message = "";
            switch (player->GetSession()->GetSessionDbLocaleIndex())
            {
                case LOCALE_enUS:
                case LOCALE_koKR:
                case LOCALE_frFR:
                case LOCALE_deDE:
                case LOCALE_zhCN:
                case LOCALE_zhTW:
                case LOCALE_ruRU:
                {
                    gossipText = "I would like to remove my instance saves.";
                    message = "Greetings $n. This is an npc that allows you to reset instance ids, allowing you to re-enter, without the need to wait for the reset time to expire. It was developed by the AzerothCore community.";
                    break;

                }
                case LOCALE_esES:
                case LOCALE_esMX:
                {
                    gossipText = "Me gustaría reiniciar mis ids de instancias.";
                    message = "Saludos $n. Este es un npc que te permite reiniciar los ids de las instancias, permitiéndote volver a entrar, sin la necesidad de esperar a que se cumpla el tiempo para el reinicio. Fue desarrollado por la comunidad de AzerothCore.";
                    break;
                }
            }
            GossipSetText(player, message, DEFAULT_GOSSIP_MESSAGE);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, gossipText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        ClearGossipMenuFor(player);
        uint32 diff = 2;
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            if (!instancereset_normalmodeonly)
                diff = MAX_DIFFICULTY;
            for (uint8 i = 0; i < diff; ++i)
            {
                BoundInstancesMap const& m_boundInstances = sInstanceSaveMgr->PlayerGetBoundInstances(player->GetGUID(), Difficulty(i));
                for (BoundInstancesMap::const_iterator itr = m_boundInstances.begin(); itr != m_boundInstances.end();)
                {
                    if (itr->first != player->GetMapId())
                    {
                        sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUID(), itr->first, Difficulty(i), true, player);
                        itr = m_boundInstances.begin();
                    }
                    else
                        ++itr;
                }
            }
            std::string creatureWhisper = "";
            switch (player->GetSession()->GetSessionDbLocaleIndex())
            {
                case LOCALE_enUS:
                case LOCALE_koKR:
                case LOCALE_frFR:
                case LOCALE_deDE:
                case LOCALE_zhCN:
                case LOCALE_zhTW:
                case LOCALE_ruRU:
                {
                    creatureWhisper = "Your instances have been reset.";
                    break;
                }
                case LOCALE_esES:
                case LOCALE_esMX:
                {
                    creatureWhisper = "Sus instancias han sido restablecidas.";
                    break;
                }
            }
            creature->Whisper(creatureWhisper, LANG_UNIVERSAL, player);
            CloseGossipMenuFor(player);
        }
        return true;
    }
};

void AddInstanceResetScripts() {
    new instanceResetConfigLoad();
    new instanceReset();
    new InstanceResetAnnouncer();
}
