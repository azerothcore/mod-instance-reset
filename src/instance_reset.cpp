#include "instance_reset.h"

/*
* This method is used to override the npc_text
* Without resorting to the database, since it is a module.
* And we want to avoid adding information that is not blizzlike.
*/
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

void InstanceResetAnnouncer::OnLogin(Player* player)
{
    if (sConfigMgr->GetOption<bool>("instanceReset.Announcer", true))
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
            case LOCALE_ruRU:
            {
                message = "Этот сервер использует модуль |cff4CFF00Перезапуск подземелий|r.";
                break;
            }
            default:
                break;
        }

        ChatHandler(player->GetSession()).SendSysMessage(message);
    }
}

bool InstanceReset::OnGossipHello(Player* player, Creature* creature)
{
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
        case LOCALE_ruRU:
        {
            gossipText = "Я бы хотел удалить мои сохраненные подземелья.";
            message = "Приветствую, $n. Этот персонаж может удалить список посещенных подземелий, позволив Вам повторно их посетить не дожидаясь времени планового перезапуска. Разработан в AzerothCore community.";
            break;
        }
        default:
            break;
    }

    if (enable)
    {
        switch (transactionType)
        {
            case 0:
            {
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, gossipText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                break;
            }

            case 1:
            {
                if (player->HasItemCount(token, count, true))
                {
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, gossipText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                }
                else
                {
                    creature->Whisper("You do not have the required items or token.", LANG_UNIVERSAL, player);
                }
                break;
            }

            case 2:
            {
                if (player->GetMoney() >= money)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, gossipText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                }
                else
                {
                    creature->Whisper("You don't have enough money.", LANG_UNIVERSAL, player);
                }
                break;
            }

            case 3:
            {
                if ((player->HasItemCount(token, count, true)) && ((player->GetMoney() >= money)))
                {
                    AddGossipItemFor(player, GOSSIP_ICON_CHAT, gossipText, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                }
                else
                {
                    creature->Whisper("The reset requires a token and money.", LANG_UNIVERSAL, player);
                }
                break;
            }

            default:
                break;
        }
    }

    GossipSetText(player, message, DEFAULT_GOSSIP_MESSAGE);
    SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
    return true;
}

bool InstanceReset::OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
{
    ClearGossipMenuFor(player);
    uint32 diff = 2;

    if (action == GOSSIP_ACTION_INFO_DEF + 1)
    {
        if (!(sConfigMgr->GetOption<bool>("instanceReset.NormalModeOnly", true)))
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
            case LOCALE_ruRU:
            {
                creatureWhisper = "Ваши подземелья перезагружены.";
                break;
            }
            default:
                break;
        }

        creature->Whisper(creatureWhisper, LANG_UNIVERSAL, player);

        switch (transactionType)
        {
            case 0: break;

            case 1:
            {
                player->DestroyItemCount(token, count, true);
                break;
            }

            case 2:
            {
                player->ModifyMoney(-money);
                break;
            }

            case 3:
            {
                player->DestroyItemCount(token, count, true);
                player->ModifyMoney(-money);
                break;
            }

            default:
                break;
        }

        CloseGossipMenuFor(player);
    }

    return true;
}

void InstanceResetWorldConfig::OnBeforeConfigLoad(bool /*reload*/)
{
    enable = sConfigMgr->GetOption<bool>("instanceReset.Enable", true);
    transactionType = sConfigMgr->GetOption<uint32>("instanceReset.TransactionType", 0);
    token = sConfigMgr->GetOption<uint32>("instanceReset.TokenID", 49426);
    count = sConfigMgr->GetOption<uint16>("instanceReset.TokenCount", 26);
    money = sConfigMgr->GetOption<uint32>("instanceReset.MoneyCount", 10000000);
}
