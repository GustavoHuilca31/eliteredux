.set LOCALID_NURSE, 1
.set LOCALID_LANETTE, 6

FallarborTown_PokemonCenter_1F_MapScripts:: @ 8200BCD
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FallarborTown_PokemonCenter_1F_OnTransition: @ 8200BD8
	setrespawn HEAL_LOCATION_FALLARBOR_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

FallarborTown_PokemonCenter_1F_EventScript_Nurse:: @ 8200BE1
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FallarborTown_PokemonCenter_1F_EventScript_Girl:: @ 8200BEF
	msgbox FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_ExpertM:: @ 8200BF8
	msgbox FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_Lanette:: @ 8200C01
	lock
	faceplayer
	msgbox FallarborTown_PokemonCenter_1F_Text_LanetteGreeting, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_NORTH, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth
	case DIR_WEST, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest
	case DIR_EAST, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitEast
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth:: @ 8200C28
	applymovement LOCALID_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest:: @ 8200C38
	applymovement LOCALID_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitEast::
	applymovement 6, FallarborTown_PokemonCenter_1F_Movement_LanetteExitEast
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExited:: @ 8200C48
	playse SE_SLIDING_DOOR
	removeobject LOCALID_LANETTE
	clearflag FLAG_HIDE_LANETTES_HOUSE_LANETTE
	release
	end

FallarborTown_PokemonCenter_1F_EventScript_Clerk2::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart PokeMart_PokeCenterFallarborTown
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
PokeMart_PokeCenterFallarborTown::
	.2byte ITEM_QUICK_BALL
	.2byte ITEM_DUSK_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_NONE
	release
	end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Text_LanetteGreeting: @ 8200C6B
	.string "Oh, hello.\n"
	.string "You are?\p"
	.string "Okay, your name's {PLAYER}{KUN}.\n"
	.string "I can see that you're a Trainer.\p"
	.string "So that means you use the Pokémon\n"
	.string "Storage System I developed.\p"
	.string "How I arrived at that conclusion is\n"
	.string "a simple deductive process.\p"
	.string "You spoke to me because you wanted\n"
	.string "to access something on this PC.\p"
	.string "Oh, I'm sorry. I'm Lanette.\p"
	.string "Honestly, I'm glad to meet you--it's\n"
	.string "great you're using the Storage System.\p"
	.string "If you could, please visit me at home.\n"
	.string "My house is on Route 114.$"

FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown: @ 8200E22
	.string "I wonder what Pokémon looked like\n"
	.string "long, long ago?\p"
	.string "Maybe the Fossil Maniac at the edge\n"
	.string "of town will know.$"

FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees: @ 8200E8B
	.string "In the fields of Fallarbor, we plant\n"
	.string "seedlings of hardy trees that thrive\l"
	.string "even in volcanic ash.$"
