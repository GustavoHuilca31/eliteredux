Debug_ShowFieldMessageStringVar4::
	special ShowFieldMessageStringVar4
	waitmessage
	waitbuttonpress
	releaseall
	end

Debug_CheatStart::
	lockall
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar VAR_BIRCH_LAB_STATE, 2
	setvar VAR_ROUTE101_STATE, 3
	givemon SPECIES_TREECKO, 20, ITEM_NONE
	givemon SPECIES_TORCHIC, 20, ITEM_NONE
	givemon SPECIES_MUDKIP, 20, ITEM_NONE
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	setvar VAR_LITTLEROOT_TOWN_STATE, 4 @ 4: Received Running Shoes
	setvar VAR_LITTLEROOT_INTRO_STATE, 7 @ 7: Told to go meet rival
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2 @ 2: Met Rival's Mom (and is corresponding gender)
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2 @ 2: Met Rival's Mom (and is corresponding gender)
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4 @ 4: Received Pokedex
	setflag FLAG_RECEIVED_BIKE
	additem ITEM_ACRO_BIKE
	setvar VAR_BRINEY_HOUSE_STATE, 1
	setvar VAR_ROUTE116_STATE, 2
	setflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	closemessage
	release
	end

Debug_Script_1::
	cleartrainerflag TRAINER_KAYLEE
	trainerbattle_single TRAINER_KAYLEE, Route102_Text_RickIntro, Route102_Text_RickDefeated
	end

Debug_Script_2::
	setvar VAR_PETALBURG_GYM_STATE, 6
	end

Debug_Script_3::
	cleartrainerflag TRAINER_JUAN_1
	trainerbattle_single TRAINER_JUAN_1, Route102_Text_RickIntro, Route102_Text_RickDefeated
	end

Debug_Script_4::
	additem ITEM_MEGA_BRACELET
	setflag FLAG_SYS_RECEIVED_KEYSTONE
	end

Debug_Script_5::
	call MeteorFalls_HaxorusRoom_EventScript_MegaStoneTest
	end

Debug_Script_6::
	additem ITEM_ABOMASITE
	additem ITEM_ABSOLITE
	additem ITEM_AERODACTYLITE
	additem ITEM_AGGRONITE
	additem ITEM_ALAKAZITE
	additem ITEM_ALTARIANITE
	additem ITEM_AMPHAROSITE
	additem ITEM_AUDINITE
	additem ITEM_BANETTITE
	additem ITEM_BEEDRILLITE
	additem ITEM_BLASTOISINITE
	additem ITEM_CAMERUPTITE
	additem ITEM_CHARIZARDITE_X
	additem ITEM_CHARIZARDITE_Y
	additem ITEM_DIANCITE
	additem ITEM_GALLADITE
	additem ITEM_GARCHOMPITE
	additem ITEM_GARDEVOIRITE
	additem ITEM_GENGARITE
	additem ITEM_GLALITITE
	additem ITEM_GYARADOSITE
	additem ITEM_HERACRONITE
	additem ITEM_HOUNDOOMINITE
	additem ITEM_KANGASKHANITE
	additem ITEM_LATIASITE
	additem ITEM_LATIOSITE
	additem ITEM_LOPUNNITE
	additem ITEM_LUCARIONITE
	additem ITEM_MANECTITE
	additem ITEM_MAWILITE
	additem ITEM_MEDICHAMITE
	additem ITEM_METAGROSSITE
	additem ITEM_MEWTWONITE_X
	additem ITEM_MEWTWONITE_Y
	additem ITEM_PIDGEOTITE
	additem ITEM_PINSIRITE
	additem ITEM_SABLENITE
	additem ITEM_SALAMENCITE
	additem ITEM_SCEPTILITE
	additem ITEM_SCIZORITE
	additem ITEM_SHARPEDONITE
	additem ITEM_SLOWBRONITE
	additem ITEM_STEELIXITE
	additem ITEM_SWAMPERTITE
	additem ITEM_TYRANITARITE
	additem ITEM_VENUSAURITE
	additem ITEM_MILOTICITE
	additem ITEM_RED_ORB
	additem ITEM_BLUE_ORB
	additem ITEM_FLYGONITE
	additem ITEM_BUTTERFRENITE
	additem ITEM_LAPRASITE_Y
	additem ITEM_MACHAMPITE
	additem ITEM_KINGLERITE
	additem ITEM_KINGDRANITE
	additem ITEM_DEWGONGITE
	additem ITEM_HITMONCHANITE
	additem ITEM_HITMONLEENITE
	additem ITEM_HITMONTOPITE
	additem ITEM_CROBATITE
	additem ITEM_SKARMORITE
	additem ITEM_BRUXISHITE
	additem ITEM_TORTERRANITE
	additem ITEM_INFERNAPENITE
	additem ITEM_EMPOLEONITE
	additem ITEM_SHUCKLENITE
	additem ITEM_RELICANTHITE
	additem ITEM_QUAGSIRENITE
	additem ITEM_JELLICENTITE
	additem ITEM_IRON_PILL
	additem ITEM_TOUCANNONITE
	additem ITEM_DRAGONITENITE
	additem ITEM_BRELOOMITE
	additem ITEM_SLAKINGITE
	additem ITEM_PURPLE_ORB
	additem ITEM_SLOWKINGITE
	additem ITEM_GYARADOSITE_Y
	additem ITEM_FERALIGATRITE_X
	additem ITEM_FERALIGATRITE_Y
	additem ITEM_HAXORUSITE
	additem ITEM_LUXRAYNITE
	additem ITEM_GRANBULLITE
	additem ITEM_TYPHLOSIONITE
	additem ITEM_NIDOQUEENITE
	additem ITEM_NIDOKINGITE
	additem ITEM_SANDSLASHITE
	additem ITEM_MEGANIUMITE
	additem ITEM_KROOKODILENITE
	additem ITEM_MAGNEZONITE
	additem ITEM_SHEDINJITE
	additem ITEM_SWALOTITE
	additem ITEM_LANTURNITE
	additem ITEM_LAPRASITE_X
	end

Debug_Script_7::
	end

Debug_Script_8::
	end
