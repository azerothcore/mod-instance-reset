#include "loader.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "Language.h"

static bool instancereset_enable;
static bool instancereset_normalmodeonly;

class instanceResetConfigLoad : public WorldScript {
public:

    instanceResetConfigLoad() : WorldScript("instanceResetConfigLoad") { }

    void OnBeforeConfigLoad(bool /*reload*/) override {
        instancereset_enable = sConfigMgr->GetBoolDefault("instanceReset.Enable", 1);
        instancereset_normalmodeonly = sConfigMgr->GetBoolDefault("instanceReset.NormalModeOnly", 0);
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
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to remove my instance saves.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
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
            creature->Whisper("Your instances have been reset.", LANG_UNIVERSAL, player);
            CloseGossipMenuFor(player);
        }
        return true;
    }
};

void AddInstanceResetScripts() {
    new instanceResetConfigLoad();
    new instanceReset();
}

