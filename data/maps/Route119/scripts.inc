.set LOCALID_RIVAL, 16
.set LOCALID_RIVAL_ON_BIKE, 19
.set LOCALID_SCOTT, 34

Route119_MapScripts:: @ 81F4424
	map_script MAP_SCRIPT_ON_RESUME, Route119_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_OnTransition
	.byte 0

Route119_OnResume: @ 81F442F
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Route119_EventScript_TryRemoveKecleon
	end

Route119_EventScript_TryRemoveKecleon:: @ 81F4439
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

Route119_OnTransition: @ 81F444D
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	compare VAR_WEATHER_INSTITUTE_STATE, 1
	call_if_eq Route119_EventScript_MoveInstituteWorkersDownstairs
	special SetRoute119Weather
	end

Route119_EventScript_MoveInstituteWorkersDownstairs:: @ 81F4466
	setflag FLAG_HIDE_WEATHER_INSTITUTE_2F_WORKERS
	clearflag FLAG_HIDE_WEATHER_INSTITUTE_1F_WORKERS
	setvar VAR_WEATHER_INSTITUTE_STATE, 2
	return

Route119_EventScript_RivalTrigger1:: @ 81F4472
	setvar VAR_TEMP_1, 1
	goto Route119_EventScript_RivalEncounter
	end

Route119_EventScript_RivalTrigger2:: @ 81F447D
	setvar VAR_TEMP_1, 2
	goto Route119_EventScript_RivalEncounter
	end

Route119_EventScript_RivalEncounter:: @ 81F4488
	lockall
	addobject LOCALID_RIVAL_ON_BIKE
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq Route119_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	call_if_eq Route119_EventScript_PlayBrendanMusic
	delay 65
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_RivalEnter1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_RivalEnter2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 30
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_SetRivalPos1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_SetRivalPos2
	removeobject LOCALID_RIVAL_ON_BIKE
	addobject LOCALID_RIVAL
	delay 30
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq Route119_EventScript_BattleMay
	compare VAR_RESULT, FEMALE
	goto_if_eq Route119_EventScript_BattleBrendan
	releaseall
	end

Route119_EventScript_PlayMayMusic:: @ 81F4501
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

Route119_EventScript_PlayBrendanMusic:: @ 81F4506
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

Route119_EventScript_BattleMay:: @ 81F450B
	msgbox Route119_Text_MayIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route119_EventScript_BattleMayTreecko
	case 1, Route119_EventScript_BattleMayTorchic
	case 2, Route119_EventScript_BattleMayMudkip
	end

Route119_EventScript_BattleMayTreecko:: @ 81F453A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_119_TREECKO, Route119_Text_MayDefeat
	goto Route119_EventScript_DefeatedMay
	end

Route119_EventScript_BattleMayTorchic:: @ 81F454A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_119_TORCHIC, Route119_Text_MayDefeat
	goto Route119_EventScript_DefeatedMay
	end

Route119_EventScript_BattleMayMudkip:: @ 81F455A
	trainerbattle_no_intro TRAINER_MAY_ROUTE_119_MUDKIP, Route119_Text_MayDefeat
	goto Route119_EventScript_DefeatedMay
	end

Route119_EventScript_DefeatedMay:: @ 81F456A
	msgbox Route119_Text_MayPresentForYou, MSGBOX_DEFAULT
	call Route119_EventScript_GiveFlyHM
	msgbox Route119_Text_MayExplainFly, MSGBOX_DEFAULT
	goto Route119_EventScript_RivalExitScottArrive
	end

Route119_EventScript_BattleBrendan:: @ 81F4585
	msgbox Route119_Text_BrendanIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route119_EventScript_BattleBrendanTreecko
	case 1, Route119_EventScript_BattleBrendanTorchic
	case 2, Route119_EventScript_BattleBrendanMudkip
	end

Route119_EventScript_BattleBrendanTreecko:: @ 81F45B4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_119_TREECKO, Route119_Text_BrendanDefeat
	goto Route119_EventScript_DefeatedBrendan
	end

Route119_EventScript_BattleBrendanTorchic:: @ 81F45C4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_119_TORCHIC, Route119_Text_BrendanDefeat
	goto Route119_EventScript_DefeatedBrendan
	end

Route119_EventScript_BattleBrendanMudkip:: @ 81F45D4
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_119_MUDKIP, Route119_Text_BrendanDefeat
	goto Route119_EventScript_DefeatedBrendan
	end

Route119_EventScript_DefeatedBrendan:: @ 81F45E4
	msgbox Route119_Text_BrendanIllGiveYouThis, MSGBOX_DEFAULT
	call Route119_EventScript_GiveFlyHM
	msgbox Route119_Text_BrendanExplainFly, MSGBOX_DEFAULT
	goto Route119_EventScript_RivalExitScottArrive
	end

Route119_EventScript_GiveFlyHM:: @ 81F45FF
	giveitem ITEM_HM02_FLY
	setflag FLAG_RECEIVED_HM02
	return

Route119_EventScript_RivalExitScottArrive:: @ 81F460F
	closemessage
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_SetRivalPos1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_SetRivalPos2
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 30
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_RivalExit1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_RivalExit2
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_ROUTE119_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	delay 60
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_SetScottPos1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_SetScottPos2
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, Route119_Movement_ScottEnter
	waitmovement 0
	addvar VAR_SCOTT_STATE, 1
	msgbox Route119_Text_ScottWayToGoBeSeeingYou, MSGBOX_DEFAULT
	closemessage
	compare VAR_TEMP_1, 1
	call_if_eq Route119_EventScript_ScottExit1
	compare VAR_TEMP_1, 2
	call_if_eq Route119_EventScript_ScottExit2
	removeobject LOCALID_SCOTT
	releaseall
	end

Route119_EventScript_SetScottPos1:: @ 81F46A0
	setobjectxyperm LOCALID_SCOTT, 27, 25
	return

Route119_EventScript_SetScottPos2:: @ 81F46A8
	setobjectxyperm LOCALID_SCOTT, 28, 25
	return

Route119_EventScript_ScottExit1:: @ 81F46B0
	applymovement LOCALID_SCOTT, Route119_Movement_ScottExit1
	waitmovement 0
	return

Route119_EventScript_ScottExit2:: @ 81F46BB
	applymovement LOCALID_SCOTT, Route119_Movement_ScottExit2
	waitmovement 0
	return

Route119_EventScript_RivalEnter1:: @ 81F46C6
	applymovement LOCALID_RIVAL_ON_BIKE, Route119_Movement_RivalEnter1
	waitmovement 0
	return

Route119_EventScript_RivalEnter2:: @ 81F46D1
	applymovement LOCALID_RIVAL_ON_BIKE, Route119_Movement_RivalEnter2
	waitmovement 0
	return

Route119_EventScript_RivalExit1:: @ 81F46DC
	applymovement OBJ_EVENT_ID_PLAYER, Route119_Movement_PlayerWatchRivalExit1
	applymovement LOCALID_RIVAL_ON_BIKE, Route119_Movement_RivalExit1
	waitmovement 0
	return

Route119_EventScript_RivalExit2:: @ 81F46EE
	applymovement OBJ_EVENT_ID_PLAYER, Route119_Movement_PlayerWatchRivalExit2
	applymovement LOCALID_RIVAL_ON_BIKE, Route119_Movement_RivalExit2
	waitmovement 0
	return

Route119_EventScript_SetRivalPos1:: @ 81F4700
	setobjectxyperm LOCALID_RIVAL, 25, 32
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 25, 32
	return

Route119_EventScript_SetRivalPos2:: @ 81F470F
	setobjectxyperm LOCALID_RIVAL, 26, 32
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 26, 32
	return

Route119_Movement_PlayerWatchRivalExit1: @ 81F471E
	delay_16
	walk_in_place_fastest_right
	delay_8
	walk_in_place_fastest_up
	step_end

Route119_Movement_PlayerWatchRivalExit2: @ 81F4723
	delay_16
	walk_in_place_fastest_left
	delay_8
	walk_in_place_fastest_up
	step_end

Route119_Movement_RivalEnter1: @ 81F4728
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

Route119_Movement_RivalEnter2: @ 81F4732
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	step_end

Route119_Movement_RivalExit1: @ 81F473D
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route119_Movement_RivalExit2: @ 81F4747
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route119_Movement_ScottEnter: @ 81F4752
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

Route119_Movement_ScottExit1: @ 81F475A
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route119_Movement_ScottExit2: @ 81F4763
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route119_EventScript_CyclingTriathleteM:: @ 81F476B
	msgbox Route119_Text_TallGrassSnaresBikeTires, MSGBOX_NPC
	end

Route119_EventScript_RouteSignFortree:: @ 81F4774
	msgbox Route119_Text_RouteSignFortree, MSGBOX_SIGN
	end

Route119_EventScript_WeatherInstituteSign:: @ 81F477D
	msgbox Route119_Text_WeatherInstitute, MSGBOX_SIGN
	end

Route119_EventScript_Brent:: @ 81F4786
	trainerbattle_single TRAINER_BRENT, Route119_Text_BrentIntro, Route119_Text_BrentDefeat
	msgbox Route119_Text_BrentPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Donald:: @ 81F479D
	trainerbattle_single TRAINER_DONALD, Route119_Text_DonaldIntro, Route119_Text_DonaldDefeat
	msgbox Route119_Text_DonaldPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Taylor:: @ 81F47B4
	trainerbattle_single TRAINER_TAYLOR, Route119_Text_TaylorIntro, Route119_Text_TaylorDefeat
	msgbox Route119_Text_TaylorPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Doug:: @ 81F47CB
	trainerbattle_single TRAINER_DOUG, Route119_Text_DougIntro, Route119_Text_DougDefeat
	msgbox Route119_Text_DougPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Greg:: @ 81F47E2
	trainerbattle_single TRAINER_GREG, Route119_Text_GregIntro, Route119_Text_GregDefeat
	msgbox Route119_Text_GregPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Kent:: @ 81F47F9
	trainerbattle_single TRAINER_KENT, Route119_Text_KentIntro, Route119_Text_KentDefeat
	msgbox Route119_Text_KentPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Jackson:: @ 81F4810
	trainerbattle_single TRAINER_JACKSON_1, Route119_Text_JacksonIntro, Route119_Text_JacksonDefeat, Route119_EventScript_RegisterJackson
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route119_EventScript_RematchJackson
	msgbox Route119_Text_JacksonPostBattle, MSGBOX_DEFAULT
	release
	end

Route119_EventScript_RegisterJackson:: @ 81F483C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route119_Text_JacksonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JACKSON_1
	release
	end

Route119_EventScript_RematchJackson:: @ 81F485B
	trainerbattle_rematch TRAINER_JACKSON_1, Route119_Text_JacksonRematchIntro, Route119_Text_JacksonRematchDefeat
	msgbox Route119_Text_JacksonPostRematch, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Catherine:: @ 81F4872
	trainerbattle_single TRAINER_CATHERINE_1, Route119_Text_CatherineIntro, Route119_Text_CatherineDefeat, Route119_EventScript_RegisterCatherine
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route119_EventScript_RematchCatherine
	msgbox Route119_Text_CatherinePostBattle, MSGBOX_DEFAULT
	release
	end

Route119_EventScript_RegisterCatherine:: @ 81F489E
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route119_Text_CatherineRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CATHERINE_1
	release
	end

Route119_EventScript_RematchCatherine:: @ 81F48BD
	trainerbattle_rematch TRAINER_CATHERINE_1, Route119_Text_CatherineRematchIntro, Route119_Text_CatherineRematchDefeat
	msgbox Route119_Text_CatherinePostRematch, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Hugh:: @ 81F48D4
	trainerbattle_single TRAINER_HUGH, Route119_Text_HughIntro, Route119_Text_HughDefeat
	msgbox Route119_Text_HughPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Phil:: @ 81F48EB
	trainerbattle_single TRAINER_PHIL, Route119_Text_PhilIntro, Route119_Text_PhilDefeat
	msgbox Route119_Text_PhilPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Yasu:: @ 81F4902
	trainerbattle_single TRAINER_YASU, Route119_Text_YasuIntro, Route119_Text_YasuDefeat
	msgbox Route119_Text_YasuPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Takashi:: @ 81F4919
	trainerbattle_single TRAINER_TAKASHI, Route119_Text_TakashiIntro, Route119_Text_TakashiDefeat
	msgbox Route119_Text_TakashiPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Hideo:: @ 81F4930
	trainerbattle_single TRAINER_HIDEO, Route119_Text_HideoIntro, Route119_Text_HideoDefeat
	msgbox Route119_Text_HideoPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Chris:: @ 81F4947
	trainerbattle_single TRAINER_CHRIS, Route119_Text_ChrisIntro, Route119_Text_ChrisDefeat
	msgbox Route119_Text_ChrisPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Fabian:: @ 81F495E
	trainerbattle_single TRAINER_FABIAN, Route119_Text_FabianIntro, Route119_Text_FabianDefeat
	msgbox Route119_Text_FabianPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Dayton:: @ 81F4975
	trainerbattle_single TRAINER_DAYTON, Route119_Text_DaytonIntro, Route119_Text_DaytonDefeat
	msgbox Route119_Text_DaytonPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_Rachel:: @ 81F498C
	trainerbattle_single TRAINER_RACHEL, Route119_Text_RachelIntro, Route119_Text_RachelDefeat
	msgbox Route119_Text_RachelPostBattle, MSGBOX_AUTOCLOSE
	end

Route119_EventScript_BridgeAquaGrunt1:: @ 81F49A3
	lock
	faceplayer
	msgbox Route119_Text_StayAwayFromWeatherInstitute, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route119_EventScript_BridgeAquaGrunt2:: @ 81F49BA
	lock
	faceplayer
	msgbox Route119_Text_DontGoNearWeatherInstitute, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route119_EventScript_Boy1:: @ 81F49D1
	msgbox Route119_Text_ThoughtFlyByCatchingBirdMons, MSGBOX_NPC
	end

Route119_EventScript_Boy2:: @ 81F49DA
	msgbox Route119_Text_CanYourMonMakeSecretBase, MSGBOX_NPC
	end

Route119_EventScript_TrainerTipsDecoration:: @ 81F49E3
	msgbox Route119_Text_TrainerTipsDecoration, MSGBOX_SIGN
	end

Route119_EventScript_ScottWonAtFortreeGymCall:: @ 81F49EC
	lockall
	pokenavcall Route119_Text_ScottYouWonAtFortreeGym
	waitmessage
	clearflag FLAG_SCOTT_CALL_FORTREE_GYM
	addvar VAR_SCOTT_STATE, 1
	releaseall
	end

Route119_Text_MayIntro: @ 81F49FD
	.string "May: {PLAYER}{KUN}!\n"
	.string "Where were you? I was looking for you!\p"
	.string "How much stronger have you gotten?\n"
	.string "Let me check for you!\p"
	.string "Ready with your Pokémon?\n"
	.string "Of course you are! Go!$"

Route119_Text_MayDefeat: @ 81F4A98
	.string "Achah!\n"
	.string "{PLAYER}{KUN}, you're strong!\p"
	.string "I was worried that you might be\n"
	.string "struggling with your training.$"

Route119_Text_MayPresentForYou: @ 81F4AF3
	.string "May: But I had absolutely nothing to\n"
	.string "worry about! Keep it up!\p"
	.string "And, here! I have a present for you.$"

Route119_Text_MayExplainFly:
	.string "May: You should Fly home and visit\n"
	.string "Littleroot for a change.\p"
	.string "I bet your mom's worried about you,\n"
	.string "{PLAYER}{KUN}.\p"
	.string "Well, let's meet again somewhere!$"

Route119_Text_BrendanIntro: @ 81F4C9A
	.string "Brendan: {PLAYER}! So this is where\n"
	.string "you've been looking for Pokémon?\p"
	.string "Let me see how good you got.\n"
	.string "I'll test you!\p"
	.string "Now!\n"
	.string "It's a battle, so battle!$"

Route119_Text_BrendanDefeat: @ 81F4D24
	.string "Hmm…\n"
	.string "You've gotten pretty darn decent.$"

Route119_Text_BrendanIllGiveYouThis: @ 81F4D4B
	.string "Brendan: I'd say you're good enough\n"
	.string "to search for Pokémon anywhere.\p"
	.string "Here, I'll give you this.\n"
	.string "Try it out.$"

Route119_Text_BrendanExplainFly: @ 81F4DB5
	.string "Brendan: Anyway, I have to move along.$"

Route119_Text_ScottWayToGoBeSeeingYou: @ 81F4E60
	.string "Scott: Hahahah!\n"
	.string "Way to go, {PLAYER}{KUN}!\p"
	.string "I just passed by a Trainer riding\n"
	.string "a Bike.\p"
	.string "You just beat that Trainer, didn't you?\n"
	.string "It was pretty obvious that you did.\p"
	.string "The kid looked really upset with\n"
	.string "a face all red from anger.\p"
	.string "I sure seem to run into you often.\n"
	.string "Are you off to Fortree Gym next?\p"
	.string "I expect that you'll do well at the Gym.\n"
	.string "Well, I'll be seeing you!$"


Route119_Text_ScottYouWonAtFortreeGym: @ 81F4FBA
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "Scott: Hiya, {PLAYER}{KUN}, it's me!\p"
	.string "Just as I thought, you won at\n"
	.string "the Fortree Gym.\p"
	.string "Your strength…\n"
	.string "Perhaps you really are the Trainer\l"
	.string "that I've been searching for.\p"
	.string "Remember, you have a fan in me.\n"
	.string "I'll be cheering from the sidelines.\l"
	.string "Keep up the great work!\p"
	.string "… … … … … …\n"
	.string "… … … … … Click!$"

Route119_Text_StayAwayFromWeatherInstitute: @ 81F50EB
	.string "We're standing lookout here.\p"
	.string "Hey, you! Stay away from the Weather\n"
	.string "Institute. It's not safe.$"

Route119_Text_DontGoNearWeatherInstitute: @ 81F5147
	.string "Lookout duty is surprisingly boring.\p"
	.string "Hey, you! Please don't go near the\n"
	.string "Weather Institute.$"

Route119_Text_ThoughtFlyByCatchingBirdMons: @ 81F51A2
	.string "I thought you Fly by catching a whole\n"
	.string "flock of Bird Pokémon, and then\l"
	.string "hanging on to them somehow.\p"
	.string "But it turns out there's an HM move\n"
	.string "called Fly!\p"
	.string "I wish I'd known about that a long\n"
	.string "time ago…$"

Route119_Text_TallGrassSnaresBikeTires: @ 81F5261
	.string "Tch…\n"
	.string "It's a no-go…\p"
	.string "The tall grass snares Bike tires.\n"
	.string "There's no way you can cycle here.$"

Route119_Text_CanYourMonMakeSecretBase: @ 81F52B9
	.string "Can your Pokémon use its Secret Power\n"
	.string "on a big pile of grass and make a\l"
	.string "Secret Base?$"

Route119_Text_RouteSignFortree: @ 81F530E
	.string "Route 119\n"
	.string "{RIGHT_ARROW} Fortree City$"

Route119_Text_WeatherInstitute: @ 81F5327
	.string "Weather Institute$"

Route119_Text_TrainerTipsDecoration: @ 81F5339
	.string "Trainer Tips\p"
	.string "Up to sixteen decorations and\n"
	.string "furniture items can be placed in\l"
	.string "a Secret Base.\p"
	.string "Pick your favorite items and create\n"
	.string "your very own Secret Base exactly the\l"
	.string "way you want.$"

Route119_EventScript_LegendaryNPC::
	lock
	faceplayer
	msgbox Route119_EventScript_LegendaryNPC_Text_0, MSGBOX_YESNO
	compare VAR_RESULT, 1
	goto_if_eq Route119_EventScript_LegendaryNPC_2
	msgbox Route119_EventScript_LegendaryNPC_Text_4
Route119_EventScript_LegendaryNPC_1:
	release
	end

Route119_EventScript_LegendaryNPC_2:
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route119_EventScript_LegendaryNPC_5
	checktrainerflag TRAINER_BRENT
	goto_if 1, Route119_EventScript_LegendaryNPC_11
Route119_EventScript_LegendaryNPC_9:
	msgbox Route119_EventScript_LegendaryNPC_Text_3
	goto Route119_EventScript_LegendaryNPC_1

Route119_EventScript_LegendaryNPC_5:
	msgbox Route119_EventScript_LegendaryNPC_Text_1
	goto Route119_EventScript_LegendaryNPC_1

Route119_EventScript_LegendaryNPC_8:
	msgbox Route119_EventScript_LegendaryNPC_Text_2
	goto Route119_EventScript_LegendaryNPC_1

Route119_EventScript_LegendaryNPC_10:
	checktrainerflag TRAINER_TAYLOR
	goto_if 1, Route119_EventScript_LegendaryNPC_15
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_11:
	checktrainerflag TRAINER_DONALD
	goto_if 1, Route119_EventScript_LegendaryNPC_10
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_14:
	checktrainerflag TRAINER_GREG
	goto_if 1, Route119_EventScript_LegendaryNPC_19
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_15:
	checktrainerflag TRAINER_DOUG
	goto_if 1, Route119_EventScript_LegendaryNPC_14
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_18:
	checktrainerflag TRAINER_JACKSON_1
	goto_if 1, Route119_EventScript_LegendaryNPC_23
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_19:
	checktrainerflag TRAINER_KENT
	goto_if 1, Route119_EventScript_LegendaryNPC_18
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_22:
	checktrainerflag TRAINER_HUGH
	goto_if 1, Route119_EventScript_LegendaryNPC_27
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_23:
	checktrainerflag TRAINER_CATHERINE_1
	goto_if 1, Route119_EventScript_LegendaryNPC_22
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_26:
	checktrainerflag TRAINER_YASU
	goto_if 1, Route119_EventScript_LegendaryNPC_31
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_27:
	checktrainerflag TRAINER_PHIL
	goto_if 1, Route119_EventScript_LegendaryNPC_26
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_30:
	checktrainerflag TRAINER_HIDEO
	goto_if 1, Route119_EventScript_LegendaryNPC_35
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_31:
	checktrainerflag TRAINER_TAKASHI
	goto_if 1, Route119_EventScript_LegendaryNPC_30
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_34:
	checktrainerflag TRAINER_FABIAN
	goto_if 1, Route119_EventScript_LegendaryNPC_39
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_35:
	checktrainerflag TRAINER_CHRIS
	goto_if 1, Route119_EventScript_LegendaryNPC_34
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_38:
	checktrainerflag TRAINER_RACHEL
	goto_if 1, Route119_EventScript_LegendaryNPC_8
	goto Route119_EventScript_LegendaryNPC_9

Route119_EventScript_LegendaryNPC_39:
	checktrainerflag TRAINER_DAYTON
	goto_if 1, Route119_EventScript_LegendaryNPC_38
	goto Route119_EventScript_LegendaryNPC_9


Route119_EventScript_Gen8_NPC::
	lock
	faceplayer
	checktrainerflag TRAINER_DONALD
	goto_if 1, Route119_EventScript_Gen8_NPC_5
Route119_EventScript_Gen8_NPC_3:
	msgbox Route119_EventScript_Gen8_NPC_Text_2
Route119_EventScript_Gen8_NPC_1:
	release
	end

Route119_EventScript_Gen8_NPC_2:
	msgbox Route119_EventScript_Gen8_NPC_Text_0
	givemon SPECIES_ARCTOVISH, 50, ITEM_NONE
	playfanfare MUS_OBTAIN_ITEM
	message Route119_EventScript_Gen8_NPC_Text_1
	waitfanfare
	goto Route119_EventScript_Gen8_NPC_1

Route119_EventScript_Gen8_NPC_4:
	checktrainerflag TRAINER_KENT
	goto_if 1, Route119_EventScript_Gen8_NPC_9
	goto Route119_EventScript_Gen8_NPC_3

Route119_EventScript_Gen8_NPC_5:
	checktrainerflag TRAINER_GREG
	goto_if 1, Route119_EventScript_Gen8_NPC_4
	goto Route119_EventScript_Gen8_NPC_3

Route119_EventScript_Gen8_NPC_8:
	checktrainerflag TRAINER_TAYLOR
	goto_if 1, Route119_EventScript_Gen8_NPC_12
	goto Route119_EventScript_Gen8_NPC_3

Route119_EventScript_Gen8_NPC_9:
	checktrainerflag TRAINER_DOUG
	goto_if 1, Route119_EventScript_Gen8_NPC_8
	goto Route119_EventScript_Gen8_NPC_3

Route119_EventScript_Gen8_NPC_12:
	checktrainerflag TRAINER_BRENT
	goto_if 1, Route119_EventScript_Gen8_NPC_2
	goto Route119_EventScript_Gen8_NPC_3


Route119_EventScript_LegendaryNPC_Text_0:
	.string "Sage: I know a story... the story of how\n"
	.string "we, as humans, became humane.\l"
	.string "Interested in hearing it?$"

Route119_EventScript_LegendaryNPC_Text_1:
	.string "It is said that, when Arceus created\n"
	.string "mankind, the result was initally less\l"
	.string "than desirable.\p"
	.string "The humans were just hollow husks,\n"
	.string "bodies without mind and soul. They\l"
	.string "needed vigor and spirit.\p"
	.string "Arceus brought forth Azelf, Mesprit and\n"
	.string "Uxie for this task. The three gifted\l"
	.string "these husks with conscience,\l"
	.string "intelligence and emotion. But that\l"
	.string "wasn't enough.\p"
	.string "The newly improved humans only looked\n"
	.string "after themselves, and were content\l"
	.string "with surviving, rather than living. This\l"
	.string "wouldn't have lasted for long.\p"
	.string "They lacked humanity, empathy and\n"
	.string "willpower. And so, Arceus made a\l"
	.string "decision: he called Victini and Shaymin\l"
	.string "to impart a profound transformation\l"
	.string "upon humanity.\p"
	.string "They were still young Pokémon, but he\n"
	.string "trusted them with this task. And so,\l"
	.string "they got to work.\p"
	.string "Victini, envoy of success, embued\n"
	.string "humans with an indomitable spirit.\l"
	.string "Shaymin, envoy of gratitude, made them\l"
	.string "look after one another.\p"
	.string "Together, they gave us the tools to\n"
	.string "work toward common goals and\l"
	.string "objectives, allowing civilization to\l"
	.string "finally prosper.\p"
	.string "And so, the legacy of Victini and\n"
	.string "Shaymin endured, forever etched in the\l"
	.string "hearts of humanity. Their benevolent\l"
	.string "presence ensured that the spark of\l"
	.string "compassion continued to shine\l"
	.string "brightly, lighting the way for future\l"
	.string "generations.\p"
	.string "I now look forward to you: rekindle your\n"
	.string "love for victory, be grateful towards\l"
	.string "your traveling companions, and return\l"
	.string "when you're finally champion!$"

Route119_EventScript_LegendaryNPC_Text_2:
	.string "I have no doubts in my mind... you are\n"
	.string "now worthy of meeting Arceus, Shaymin\l"
	.string "and Victini; you are truly blessed with\l"
	.string "this once in a lifetime opportunity.\l"
	.string "Their location will appear when you use\l"
	.string "your DexNav, so make sure you're\l"
	.string "prepared. Good luck...$"

Route119_EventScript_LegendaryNPC_Text_3:
	.string "You truly are one special human. While\n"
	.string "initially it seemed like only Shaymin\l"
	.string "and Victini would be willing to meet\l"
	.string "you, it now seems like Arceus is about\l"
	.string "to get involved.\p"
	.string "However, it won't be easy convincing\n"
	.string "him. There's a lot of trainers around\l"
	.string "here, but if you best them... he might\l"
	.string "give you a chance.$"

Route119_EventScript_LegendaryNPC_Text_4:
	.string "Fair enough.$"

Route119_EventScript_Gen8_NPC_Text_0:
	.string "Thank you so much, you're my saviour! I\n"
	.string "think this little guy got messed up on\l"
	.string "the way to Hoenn, but I like them\l"
	.string "regardless!$"

Route119_EventScript_Gen8_NPC_Text_1:
	.string "{PLAYER} got an {COLOR BLUE}Arctovish{COLOR DARK_GRAY} as a gift\n"
	.string "for finding and defeating every\l"
	.string "trainer in the tall grass!$"

Route119_EventScript_Gen8_NPC_Text_2:
	.string "So I was just hiking here, but some guys\n"
	.string "came up to me and asked to play hide\l"
	.string "and seek. I was like 'man, I really wanna\l"
	.string "go on with my hike, I don't have time\l"
	.string "for this' but they insisted, so I\l"
	.string "accepted aaaand... now I gotta find\l"
	.string "them. Please, can you help me find\l"
	.string "them? I'll give you something special in\l"
	.string "return!$"
