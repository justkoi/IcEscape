#pragma once

#define D_SOUND_MAX 4

#define D_PHONE_WIDTH 480
#define D_PHONE_HEIGHT 800

#define D_SCREEN_SCALE_WIDTH(s) (D_PHONE_WIDTH/100) * s
#define D_SCREEN_SCALE_HEIGHT(s) (D_PHONE_HEIGHT/100) * s

#define D_BLOCKMAP_WIDTH 7
#define D_BLOCKMAP_HEIGHT 11

//#define	D_LINE_START_X -192.0f
//#define	D_LINE_START_Y 340.0f


#define	D_LINE_START_X 16.0f
#define	D_LINE_START_Y 732.0f


#define D_LINE_END_Y -300.0f

#define D_CALC_START_X -224
#define D_CALC_START_Y 372

#define D_LOGOVIB_MAX 8

#define D_CAM_Z_FIXED 695.0f


#define D_SCORE_CREATEBLOCK 3

#define D_SCORE_ICEBLOCK 3

#define D_SCORE_EROSIONBLOCK 1

#define D_BLOCK_SPEED 400.0f
#define D_BLOCK_PLUSSPEED 60.0f

#define D_EROSIONTIME 6.0f
#define D_FREEZETIME 4.0f

#define D_BLOCK_WIDTH 64
#define D_BLOCK_HEIGHT 64

#define D_SOUND_ICE_CHANNEL 5

#define D_INTERFACE_START_X 40

#define D_INTERFACE_NOWBLOCK_TEXT_Y 120
#define D_INTERFACE_MOUSELIST_TEXT_Y 140
#define D_INTERFACE_EROSIONSPEED_TEXT_Y 160
#define D_INTERFACE_CREATETIME_TEXT_Y 205
#define D_INTERFACE_EROSIONPLUSSPEED_TEXT_Y 260
#define D_INTERFACE_FREEMOVE_TEXT_Y 300

#define D_GAME_END_BLIND_TIME 1.5f
#define D_GAME_END_STAR_TIME 0.8f

#define D_INTERFACE_X -190

#define D_BLOCK_NUMBER 3

#define D_STAGEMENU_START_X - 150.0f
#define D_STAGEMENU_START_Y   300.0f

#define D_STAGEMENU_DISTANCE 150.0f

#define D_SNOW_RAND_POS_X 300.0f + CEMMath::RandomFloatInRange(300.0f ,600.0f)
#define D_SNOW_RAND_POS_Y 300.0f + CEMMath::RandomFloatInRange(-200.0f ,600.0f);

#define D_SNOW_MAX 3

#define D_COMBOTIME 2.0f

#define D_STAGEMENU_WIDTH_NUMBER 3


//#define D_SCENE_CHANGE_EFFECT_L(scene) CCScene *pScene = CCTransitionSlideInL::transitionWithDuration(1.0f,scene);

//#define D_SCENE_CHANGE_EFFECT_R(scene) CCScene *pScene = CCTransitionSlideInR::transitionWithDuration(1.0f,scene);

//#define D_SCENE_CHANGE_EFFECT_L(scene) CCScene *pScene = CCTransitionSlideInL::transitionWithDuration(1.0f,scene);

//#define D_SCENE_CHANGE_EFFECT_R(scene) CCScene *pScene = CCTransitionSlideInR::transitionWithDuration(1.0f,scene);

//m_pLoading->setVisible(true); \
	

#define D_SCENE_CHANGE_EFFECT_L(scene)  m_pLoading->setVisible(true); CCScene *pScene = CCTransitionFade::transitionWithDuration(1.0f,scene);

#define D_SCENE_CHANGE_EFFECT_R(scene)  m_pLoading->setVisible(true); CCScene *pScene = CCTransitionFade::transitionWithDuration(1.0f,scene);


#define D_SLIDE_NUM_MAX 20

#define D_STAGE_MAX 21

#define D_STAGEMENU_WIDTH 140
#define D_STAGEMENU_HEGIHT 140

#define D_SEA_LEVEL_POINT 4.0f
#define D_SEA_LEVEL_RESTORATION 1.0f

#define D_WARNING_TIME 1.0f
#define D_WARNING_DELAY_TIME 1.5f


#define D_MAX_TTMSG 4

#define D_BASIC_PHONE_WIDTH 480
#define D_BASIC_PHONE_HEIGHT 800

#define D_SCALE_WIDTH (g_PhoneSize.width/D_BASIC_PHONE_WIDTH)
#define D_SCALE_HEIGHT (g_PhoneSize.height/D_BASIC_PHONE_HEIGHT)