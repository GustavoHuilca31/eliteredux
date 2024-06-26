PetalburgCity_Mart_MapScripts:: @ 8207D68
	.byte 0

PetalburgCity_Mart_EventScript_Clerk:: @ 8207D69
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart PetalburgCity_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Mart_Pokemart_Basic:
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFENSE
	.2byte ITEM_X_SP_ATK
	.2byte ITEM_X_SP_DEF
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_NONE
	release
	end

PetalburgCity_Mart_EventScript_Woman:: @ 8207DD6
	msgbox PetalburgCity_Mart_Text_WeakWillGrowStronger, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Boy:: @ 8207DDF
	msgbox PetalburgCity_Mart_Text_RepelIsUseful, MSGBOX_NPC
	end

PetalburgCity_Mart_EventScript_Man:: @ 8207DE8
	msgbox PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou, MSGBOX_NPC
	end

PetalburgCity_Mart_Text_WeakWillGrowStronger: @ 8207DF1
	.string "Even if a Pokémon is weak now,\n"
	.string "it will grow stronger.\p"
	.string "The most important thing is love!\n"
	.string "Love for your Pokémon!$"

PetalburgCity_Mart_Text_RepelIsUseful: @ 8207E60
	.string "Do you use Repel?\n"
	.string "It keeps Pokémon away, so it's\l"
	.string "useful when you're in a hurry.$"

PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou: @ 8207EB0
	.string "Do you have any Antidotes with\n"
	.string "you?\p"
	.string "If you walk around with a poisoned\n"
	.string "Pokémon, it will lose HP until it faints.\l"
	.string "Take some Antidotes with you.$"
