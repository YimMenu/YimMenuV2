#pragma once
#include "invoker/Invoker.hpp"

// clang-format off
namespace SYSTEM
{
	FORCEINLINE void WAIT(int ms) { return YimMenu::NativeInvoker::Invoke<0, void>(ms); }
	FORCEINLINE int START_NEW_SCRIPT(const char* scriptName, int stackSize) { return YimMenu::NativeInvoker::Invoke<1, int>(scriptName, stackSize); }
	FORCEINLINE int START_NEW_SCRIPT_WITH_ARGS(const char* scriptName, Any* args, int argCount, int stackSize) { return YimMenu::NativeInvoker::Invoke<2, int>(scriptName, args, argCount, stackSize); }
	FORCEINLINE int START_NEW_SCRIPT_WITH_NAME_HASH(Hash scriptHash, int stackSize) { return YimMenu::NativeInvoker::Invoke<3, int>(scriptHash, stackSize); }
	FORCEINLINE int START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(Hash scriptHash, Any* args, int argCount, int stackSize) { return YimMenu::NativeInvoker::Invoke<4, int>(scriptHash, args, argCount, stackSize); }
	FORCEINLINE int TIMERA() { return YimMenu::NativeInvoker::Invoke<5, int>(); }
	FORCEINLINE int TIMERB() { return YimMenu::NativeInvoker::Invoke<6, int>(); }
	FORCEINLINE void SETTIMERA(int value) { return YimMenu::NativeInvoker::Invoke<7, void>(value); }
	FORCEINLINE void SETTIMERB(int value) { return YimMenu::NativeInvoker::Invoke<8, void>(value); }
	FORCEINLINE float TIMESTEP() { return YimMenu::NativeInvoker::Invoke<9, float>(); }
	FORCEINLINE float SIN(float value) { return YimMenu::NativeInvoker::Invoke<10, float>(value); }
	FORCEINLINE float COS(float value) { return YimMenu::NativeInvoker::Invoke<11, float>(value); }
	FORCEINLINE float SQRT(float value) { return YimMenu::NativeInvoker::Invoke<12, float>(value); }
	FORCEINLINE float POW(float base, float exponent) { return YimMenu::NativeInvoker::Invoke<13, float>(base, exponent); }
	FORCEINLINE float LOG10(float value) { return YimMenu::NativeInvoker::Invoke<14, float>(value); }
	FORCEINLINE float VMAG(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<15, float>(x, y, z); }
	FORCEINLINE float VMAG2(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<16, float>(x, y, z); }
	FORCEINLINE float VDIST(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<17, float>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE float VDIST2(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<18, float>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE int SHIFT_LEFT(int value, int bitShift) { return YimMenu::NativeInvoker::Invoke<19, int>(value, bitShift); }
	FORCEINLINE int SHIFT_RIGHT(int value, int bitShift) { return YimMenu::NativeInvoker::Invoke<20, int>(value, bitShift); }
	FORCEINLINE int FLOOR(float value) { return YimMenu::NativeInvoker::Invoke<21, int>(value); }
	FORCEINLINE int CEIL(float value) { return YimMenu::NativeInvoker::Invoke<22, int>(value); }
	FORCEINLINE int ROUND(float value) { return YimMenu::NativeInvoker::Invoke<23, int>(value); }
	FORCEINLINE float TO_FLOAT(int value) { return YimMenu::NativeInvoker::Invoke<24, float>(value); }
	FORCEINLINE void SET_THIS_THREAD_PRIORITY(int priority) { return YimMenu::NativeInvoker::Invoke<25, void>(priority); }
}

namespace APP
{
	FORCEINLINE bool APP_DATA_VALID() { return YimMenu::NativeInvoker::Invoke<26, bool>(); }
	FORCEINLINE int APP_GET_INT(const char* property) { return YimMenu::NativeInvoker::Invoke<27, int>(property); }
	FORCEINLINE float APP_GET_FLOAT(const char* property) { return YimMenu::NativeInvoker::Invoke<28, float>(property); }
	FORCEINLINE const char* APP_GET_STRING(const char* property) { return YimMenu::NativeInvoker::Invoke<29, const char*>(property); }
	FORCEINLINE void APP_SET_INT(const char* property, int value) { return YimMenu::NativeInvoker::Invoke<30, void>(property, value); }
	FORCEINLINE void APP_SET_FLOAT(const char* property, float value) { return YimMenu::NativeInvoker::Invoke<31, void>(property, value); }
	FORCEINLINE void APP_SET_STRING(const char* property, const char* value) { return YimMenu::NativeInvoker::Invoke<32, void>(property, value); }
	FORCEINLINE void APP_SET_APP(const char* appName) { return YimMenu::NativeInvoker::Invoke<33, void>(appName); }
	FORCEINLINE void APP_SET_BLOCK(const char* blockName) { return YimMenu::NativeInvoker::Invoke<34, void>(blockName); }
	FORCEINLINE void APP_CLEAR_BLOCK() { return YimMenu::NativeInvoker::Invoke<35, void>(); }
	FORCEINLINE void APP_CLOSE_APP() { return YimMenu::NativeInvoker::Invoke<36, void>(); }
	FORCEINLINE void APP_CLOSE_BLOCK() { return YimMenu::NativeInvoker::Invoke<37, void>(); }
	FORCEINLINE bool APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT() { return YimMenu::NativeInvoker::Invoke<38, bool>(); }
	FORCEINLINE bool APP_HAS_SYNCED_DATA(const char* appName) { return YimMenu::NativeInvoker::Invoke<39, bool>(appName); }
	FORCEINLINE void APP_SAVE_DATA() { return YimMenu::NativeInvoker::Invoke<40, void>(); }
	FORCEINLINE int APP_GET_DELETED_FILE_STATUS() { return YimMenu::NativeInvoker::Invoke<41, int>(); }
	FORCEINLINE bool APP_DELETE_APP_DATA(const char* appName) { return YimMenu::NativeInvoker::Invoke<42, bool>(appName); }
}

namespace AUDIO
{
	FORCEINLINE void PLAY_PED_RINGTONE(const char* ringtoneName, Ped ped, bool p2) { return YimMenu::NativeInvoker::Invoke<43, void>(ringtoneName, ped, p2); }
	FORCEINLINE bool IS_PED_RINGTONE_PLAYING(Ped ped) { return YimMenu::NativeInvoker::Invoke<44, bool>(ped); }
	FORCEINLINE void STOP_PED_RINGTONE(Ped ped) { return YimMenu::NativeInvoker::Invoke<45, void>(ped); }
	FORCEINLINE bool IS_MOBILE_PHONE_CALL_ONGOING() { return YimMenu::NativeInvoker::Invoke<46, bool>(); }
	FORCEINLINE bool IS_MOBILE_INTERFERENCE_ACTIVE() { return YimMenu::NativeInvoker::Invoke<47, bool>(); }
	FORCEINLINE void CREATE_NEW_SCRIPTED_CONVERSATION() { return YimMenu::NativeInvoker::Invoke<48, void>(); }
	FORCEINLINE void ADD_LINE_TO_CONVERSATION(int index, const char* p1, const char* p2, int p3, int p4, bool p5, bool p6, bool p7, bool p8, int p9, bool p10, bool p11, bool p12) { return YimMenu::NativeInvoker::Invoke<49, void>(index, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	FORCEINLINE void ADD_PED_TO_CONVERSATION(int index, Ped ped, const char* p2) { return YimMenu::NativeInvoker::Invoke<50, void>(index, ped, p2); }
	FORCEINLINE void SET_POSITION_FOR_NULL_CONV_PED(Any p0, float p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<51, void>(p0, p1, p2, p3); }
	FORCEINLINE void SET_ENTITY_FOR_NULL_CONV_PED(int p0, Entity entity) { return YimMenu::NativeInvoker::Invoke<52, void>(p0, entity); }
	FORCEINLINE void SET_MICROPHONE_POSITION(bool toggle, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) { return YimMenu::NativeInvoker::Invoke<53, void>(toggle, x1, y1, z1, x2, y2, z2, x3, y3, z3); }
	FORCEINLINE void SET_CONVERSATION_AUDIO_CONTROLLED_BY_ANIM(bool p0) { return YimMenu::NativeInvoker::Invoke<54, void>(p0); }
	FORCEINLINE void SET_CONVERSATION_AUDIO_PLACEHOLDER(bool p0) { return YimMenu::NativeInvoker::Invoke<55, void>(p0); }
	FORCEINLINE void START_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<56, void>(p0, p1); }
	FORCEINLINE void PRELOAD_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<57, void>(p0, p1); }
	FORCEINLINE void START_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<58, void>(p0, p1, p2, p3); }
	FORCEINLINE void PRELOAD_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<59, void>(p0, p1, p2, p3); }
	FORCEINLINE void START_PRELOADED_CONVERSATION() { return YimMenu::NativeInvoker::Invoke<60, void>(); }
	FORCEINLINE bool GET_IS_PRELOADED_CONVERSATION_READY() { return YimMenu::NativeInvoker::Invoke<61, bool>(); }
	FORCEINLINE bool IS_SCRIPTED_CONVERSATION_ONGOING() { return YimMenu::NativeInvoker::Invoke<62, bool>(); }
	FORCEINLINE bool IS_SCRIPTED_CONVERSATION_LOADED() { return YimMenu::NativeInvoker::Invoke<63, bool>(); }
	FORCEINLINE int GET_CURRENT_SCRIPTED_CONVERSATION_LINE() { return YimMenu::NativeInvoker::Invoke<64, int>(); }
	FORCEINLINE void PAUSE_SCRIPTED_CONVERSATION(bool p0) { return YimMenu::NativeInvoker::Invoke<65, void>(p0); }
	FORCEINLINE void RESTART_SCRIPTED_CONVERSATION() { return YimMenu::NativeInvoker::Invoke<66, void>(); }
	FORCEINLINE int STOP_SCRIPTED_CONVERSATION(bool p0) { return YimMenu::NativeInvoker::Invoke<67, int>(p0); }
	FORCEINLINE void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE() { return YimMenu::NativeInvoker::Invoke<68, void>(); }
	FORCEINLINE void INTERRUPT_CONVERSATION(Ped ped, const char* voiceline, const char* speaker) { return YimMenu::NativeInvoker::Invoke<69, void>(ped, voiceline, speaker); }
	FORCEINLINE void INTERRUPT_CONVERSATION_AND_PAUSE(Ped ped, const char* p1, const char* speaker) { return YimMenu::NativeInvoker::Invoke<70, void>(ped, p1, speaker); }
	FORCEINLINE int GET_VARIATION_CHOSEN_FOR_SCRIPTED_LINE(Any* p0) { return YimMenu::NativeInvoker::Invoke<71, int>(p0); }
	FORCEINLINE void SET_NO_DUCKING_FOR_CONVERSATION(bool p0) { return YimMenu::NativeInvoker::Invoke<72, void>(p0); }
	FORCEINLINE void REGISTER_SCRIPT_WITH_AUDIO(int p0) { return YimMenu::NativeInvoker::Invoke<73, void>(p0); }
	FORCEINLINE void UNREGISTER_SCRIPT_WITH_AUDIO() { return YimMenu::NativeInvoker::Invoke<74, void>(); }
	FORCEINLINE bool REQUEST_MISSION_AUDIO_BANK(const char* audioBank, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<75, bool>(audioBank, p1, p2); }
	FORCEINLINE bool REQUEST_AMBIENT_AUDIO_BANK(const char* audioBank, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<76, bool>(audioBank, p1, p2); }
	FORCEINLINE bool REQUEST_SCRIPT_AUDIO_BANK(const char* audioBank, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<77, bool>(audioBank, p1, p2); }
	FORCEINLINE bool HINT_MISSION_AUDIO_BANK(const char* audioBank, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<78, bool>(audioBank, p1, p2); }
	FORCEINLINE bool HINT_AMBIENT_AUDIO_BANK(const char* audioBank, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<79, bool>(audioBank, p1, p2); }
	FORCEINLINE bool HINT_SCRIPT_AUDIO_BANK(const char* audioBank, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<80, bool>(audioBank, p1, p2); }
	FORCEINLINE void RELEASE_MISSION_AUDIO_BANK() { return YimMenu::NativeInvoker::Invoke<81, void>(); }
	FORCEINLINE void RELEASE_AMBIENT_AUDIO_BANK() { return YimMenu::NativeInvoker::Invoke<82, void>(); }
	FORCEINLINE void RELEASE_NAMED_SCRIPT_AUDIO_BANK(const char* audioBank) { return YimMenu::NativeInvoker::Invoke<83, void>(audioBank); }
	FORCEINLINE void RELEASE_SCRIPT_AUDIO_BANK() { return YimMenu::NativeInvoker::Invoke<84, void>(); }
	FORCEINLINE void UNHINT_AMBIENT_AUDIO_BANK() { return YimMenu::NativeInvoker::Invoke<85, void>(); }
	FORCEINLINE void UNHINT_SCRIPT_AUDIO_BANK() { return YimMenu::NativeInvoker::Invoke<86, void>(); }
	FORCEINLINE void UNHINT_NAMED_SCRIPT_AUDIO_BANK(const char* audioBank) { return YimMenu::NativeInvoker::Invoke<87, void>(audioBank); }
	FORCEINLINE int GET_SOUND_ID() { return YimMenu::NativeInvoker::Invoke<88, int>(); }
	FORCEINLINE void RELEASE_SOUND_ID(int soundId) { return YimMenu::NativeInvoker::Invoke<89, void>(soundId); }
	FORCEINLINE void PLAY_SOUND(int soundId, const char* audioName, const char* audioRef, bool p3, Any p4, bool p5) { return YimMenu::NativeInvoker::Invoke<90, void>(soundId, audioName, audioRef, p3, p4, p5); }
	FORCEINLINE void PLAY_SOUND_FRONTEND(int soundId, const char* audioName, const char* audioRef, bool p3) { return YimMenu::NativeInvoker::Invoke<91, void>(soundId, audioName, audioRef, p3); }
	FORCEINLINE void PLAY_DEFERRED_SOUND_FRONTEND(const char* soundName, const char* soundsetName) { return YimMenu::NativeInvoker::Invoke<92, void>(soundName, soundsetName); }
	FORCEINLINE void PLAY_SOUND_FROM_ENTITY(int soundId, const char* audioName, Entity entity, const char* audioRef, bool isNetwork, Any p5) { return YimMenu::NativeInvoker::Invoke<93, void>(soundId, audioName, entity, audioRef, isNetwork, p5); }
	FORCEINLINE void PLAY_SOUND_FROM_ENTITY_HASH(int soundId, Hash model, Entity entity, Hash soundSetHash, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<94, void>(soundId, model, entity, soundSetHash, p4, p5); }
	FORCEINLINE void PLAY_SOUND_FROM_COORD(int soundId, const char* audioName, float x, float y, float z, const char* audioRef, bool isNetwork, int range, bool p8) { return YimMenu::NativeInvoker::Invoke<95, void>(soundId, audioName, x, y, z, audioRef, isNetwork, range, p8); }
	FORCEINLINE void UPDATE_SOUND_COORD(int soundId, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<96, void>(soundId, x, y, z); }
	FORCEINLINE void STOP_SOUND(int soundId) { return YimMenu::NativeInvoker::Invoke<97, void>(soundId); }
	FORCEINLINE int GET_NETWORK_ID_FROM_SOUND_ID(int soundId) { return YimMenu::NativeInvoker::Invoke<98, int>(soundId); }
	FORCEINLINE int GET_SOUND_ID_FROM_NETWORK_ID(int netId) { return YimMenu::NativeInvoker::Invoke<99, int>(netId); }
	FORCEINLINE void SET_VARIABLE_ON_SOUND(int soundId, const char* variable, float p2) { return YimMenu::NativeInvoker::Invoke<100, void>(soundId, variable, p2); }
	FORCEINLINE void SET_VARIABLE_ON_STREAM(const char* variable, float p1) { return YimMenu::NativeInvoker::Invoke<101, void>(variable, p1); }
	FORCEINLINE void OVERRIDE_UNDERWATER_STREAM(const char* p0, bool p1) { return YimMenu::NativeInvoker::Invoke<102, void>(p0, p1); }
	FORCEINLINE void SET_VARIABLE_ON_UNDER_WATER_STREAM(const char* variableName, float value) { return YimMenu::NativeInvoker::Invoke<103, void>(variableName, value); }
	FORCEINLINE bool HAS_SOUND_FINISHED(int soundId) { return YimMenu::NativeInvoker::Invoke<104, bool>(soundId); }
	FORCEINLINE void PLAY_PED_AMBIENT_SPEECH_NATIVE(Ped ped, const char* speechName, const char* speechParam, Any p3) { return YimMenu::NativeInvoker::Invoke<105, void>(ped, speechName, speechParam, p3); }
	FORCEINLINE void PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE(Ped ped, const char* speechName, const char* speechParam, Any p3) { return YimMenu::NativeInvoker::Invoke<106, void>(ped, speechName, speechParam, p3); }
	FORCEINLINE void PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(Ped ped, const char* speechName, const char* voiceName, const char* speechParam, bool p4) { return YimMenu::NativeInvoker::Invoke<107, void>(ped, speechName, voiceName, speechParam, p4); }
	FORCEINLINE void PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE(const char* speechName, const char* voiceName, float x, float y, float z, const char* speechParam) { return YimMenu::NativeInvoker::Invoke<108, void>(speechName, voiceName, x, y, z, speechParam); }
	FORCEINLINE void OVERRIDE_TREVOR_RAGE(const char* voiceEffect) { return YimMenu::NativeInvoker::Invoke<109, void>(voiceEffect); }
	FORCEINLINE void RESET_TREVOR_RAGE() { return YimMenu::NativeInvoker::Invoke<110, void>(); }
	FORCEINLINE void SET_PLAYER_ANGRY(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<111, void>(ped, toggle); }
	FORCEINLINE void PLAY_PAIN(Ped ped, int painID, int p1, Any p3) { return YimMenu::NativeInvoker::Invoke<112, void>(ped, painID, p1, p3); }
	FORCEINLINE void RELEASE_WEAPON_AUDIO() { return YimMenu::NativeInvoker::Invoke<113, void>(); }
	FORCEINLINE void ACTIVATE_AUDIO_SLOWMO_MODE(const char* mode) { return YimMenu::NativeInvoker::Invoke<114, void>(mode); }
	FORCEINLINE void DEACTIVATE_AUDIO_SLOWMO_MODE(const char* mode) { return YimMenu::NativeInvoker::Invoke<115, void>(mode); }
	FORCEINLINE void SET_AMBIENT_VOICE_NAME(Ped ped, const char* name) { return YimMenu::NativeInvoker::Invoke<116, void>(ped, name); }
	FORCEINLINE void SET_AMBIENT_VOICE_NAME_HASH(Ped ped, Hash hash) { return YimMenu::NativeInvoker::Invoke<117, void>(ped, hash); }
	FORCEINLINE Hash GET_AMBIENT_VOICE_NAME_HASH(Ped ped) { return YimMenu::NativeInvoker::Invoke<118, Hash>(ped); }
	FORCEINLINE void SET_PED_VOICE_FULL(Ped ped) { return YimMenu::NativeInvoker::Invoke<119, void>(ped); }
	FORCEINLINE void SET_PED_RACE_AND_VOICE_GROUP(Ped ped, int p1, Hash voiceGroup) { return YimMenu::NativeInvoker::Invoke<120, void>(ped, p1, voiceGroup); }
	FORCEINLINE void SET_PED_VOICE_GROUP(Ped ped, Hash voiceGroupHash) { return YimMenu::NativeInvoker::Invoke<121, void>(ped, voiceGroupHash); }
	FORCEINLINE void SET_PED_VOICE_GROUP_FROM_RACE_TO_PVG(Ped ped, Hash voiceGroupHash) { return YimMenu::NativeInvoker::Invoke<122, void>(ped, voiceGroupHash); }
	FORCEINLINE void SET_PED_GENDER(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<123, void>(ped, p1); }
	FORCEINLINE void STOP_CURRENT_PLAYING_SPEECH(Ped ped) { return YimMenu::NativeInvoker::Invoke<124, void>(ped); }
	FORCEINLINE void STOP_CURRENT_PLAYING_AMBIENT_SPEECH(Ped ped) { return YimMenu::NativeInvoker::Invoke<125, void>(ped); }
	FORCEINLINE bool IS_AMBIENT_SPEECH_PLAYING(Ped ped) { return YimMenu::NativeInvoker::Invoke<126, bool>(ped); }
	FORCEINLINE bool IS_SCRIPTED_SPEECH_PLAYING(Ped p0) { return YimMenu::NativeInvoker::Invoke<127, bool>(p0); }
	FORCEINLINE bool IS_ANY_SPEECH_PLAYING(Ped ped) { return YimMenu::NativeInvoker::Invoke<128, bool>(ped); }
	FORCEINLINE bool IS_ANY_POSITIONAL_SPEECH_PLAYING() { return YimMenu::NativeInvoker::Invoke<129, bool>(); }
	FORCEINLINE bool DOES_CONTEXT_EXIST_FOR_THIS_PED(Ped ped, const char* speechName, bool p2) { return YimMenu::NativeInvoker::Invoke<130, bool>(ped, speechName, p2); }
	FORCEINLINE bool IS_PED_IN_CURRENT_CONVERSATION(Ped ped) { return YimMenu::NativeInvoker::Invoke<131, bool>(ped); }
	FORCEINLINE void SET_PED_IS_DRUNK(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<132, void>(ped, toggle); }
	FORCEINLINE void PLAY_ANIMAL_VOCALIZATION(Ped pedHandle, int p1, const char* speechName) { return YimMenu::NativeInvoker::Invoke<133, void>(pedHandle, p1, speechName); }
	FORCEINLINE bool IS_ANIMAL_VOCALIZATION_PLAYING(Ped pedHandle) { return YimMenu::NativeInvoker::Invoke<134, bool>(pedHandle); }
	FORCEINLINE void SET_ANIMAL_MOOD(Ped animal, int mood) { return YimMenu::NativeInvoker::Invoke<135, void>(animal, mood); }
	FORCEINLINE bool IS_MOBILE_PHONE_RADIO_ACTIVE() { return YimMenu::NativeInvoker::Invoke<136, bool>(); }
	FORCEINLINE void SET_MOBILE_PHONE_RADIO_STATE(bool state) { return YimMenu::NativeInvoker::Invoke<137, void>(state); }
	FORCEINLINE int GET_PLAYER_RADIO_STATION_INDEX() { return YimMenu::NativeInvoker::Invoke<138, int>(); }
	FORCEINLINE const char* GET_PLAYER_RADIO_STATION_NAME() { return YimMenu::NativeInvoker::Invoke<139, const char*>(); }
	FORCEINLINE const char* GET_RADIO_STATION_NAME(int radioStation) { return YimMenu::NativeInvoker::Invoke<140, const char*>(radioStation); }
	FORCEINLINE int GET_PLAYER_RADIO_STATION_GENRE() { return YimMenu::NativeInvoker::Invoke<141, int>(); }
	FORCEINLINE bool IS_RADIO_RETUNING() { return YimMenu::NativeInvoker::Invoke<142, bool>(); }
	FORCEINLINE bool IS_RADIO_FADED_OUT() { return YimMenu::NativeInvoker::Invoke<143, bool>(); }
	FORCEINLINE void SET_RADIO_RETUNE_UP() { return YimMenu::NativeInvoker::Invoke<144, void>(); }
	FORCEINLINE void SET_RADIO_RETUNE_DOWN() { return YimMenu::NativeInvoker::Invoke<145, void>(); }
	FORCEINLINE void SET_RADIO_TO_STATION_NAME(const char* stationName) { return YimMenu::NativeInvoker::Invoke<146, void>(stationName); }
	FORCEINLINE void SET_VEH_RADIO_STATION(Vehicle vehicle, const char* radioStation) { return YimMenu::NativeInvoker::Invoke<147, void>(vehicle, radioStation); }
	FORCEINLINE void SET_VEH_HAS_NORMAL_RADIO(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<148, void>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_RADIO_ON(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<149, bool>(vehicle); }
	FORCEINLINE void SET_VEH_FORCED_RADIO_THIS_FRAME(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<150, void>(vehicle); }
	FORCEINLINE void SET_EMITTER_RADIO_STATION(const char* emitterName, const char* radioStation, Any p2) { return YimMenu::NativeInvoker::Invoke<151, void>(emitterName, radioStation, p2); }
	FORCEINLINE void SET_STATIC_EMITTER_ENABLED(const char* emitterName, bool toggle) { return YimMenu::NativeInvoker::Invoke<152, void>(emitterName, toggle); }
	FORCEINLINE void LINK_STATIC_EMITTER_TO_ENTITY(const char* emitterName, Entity entity) { return YimMenu::NativeInvoker::Invoke<153, void>(emitterName, entity); }
	FORCEINLINE void SET_RADIO_TO_STATION_INDEX(int radioStation) { return YimMenu::NativeInvoker::Invoke<154, void>(radioStation); }
	FORCEINLINE void SET_FRONTEND_RADIO_ACTIVE(bool active) { return YimMenu::NativeInvoker::Invoke<155, void>(active); }
	FORCEINLINE void UNLOCK_MISSION_NEWS_STORY(int newsStory) { return YimMenu::NativeInvoker::Invoke<156, void>(newsStory); }
	FORCEINLINE bool IS_MISSION_NEWS_STORY_UNLOCKED(int newsStory) { return YimMenu::NativeInvoker::Invoke<157, bool>(newsStory); }
	FORCEINLINE int GET_AUDIBLE_MUSIC_TRACK_TEXT_ID() { return YimMenu::NativeInvoker::Invoke<158, int>(); }
	FORCEINLINE void PLAY_END_CREDITS_MUSIC(bool play) { return YimMenu::NativeInvoker::Invoke<159, void>(play); }
	FORCEINLINE void SKIP_RADIO_FORWARD() { return YimMenu::NativeInvoker::Invoke<160, void>(); }
	FORCEINLINE void FREEZE_RADIO_STATION(const char* radioStation) { return YimMenu::NativeInvoker::Invoke<161, void>(radioStation); }
	FORCEINLINE void UNFREEZE_RADIO_STATION(const char* radioStation) { return YimMenu::NativeInvoker::Invoke<162, void>(radioStation); }
	FORCEINLINE void SET_RADIO_AUTO_UNFREEZE(bool toggle) { return YimMenu::NativeInvoker::Invoke<163, void>(toggle); }
	FORCEINLINE void SET_INITIAL_PLAYER_STATION(const char* radioStation) { return YimMenu::NativeInvoker::Invoke<164, void>(radioStation); }
	FORCEINLINE void SET_USER_RADIO_CONTROL_ENABLED(bool toggle) { return YimMenu::NativeInvoker::Invoke<165, void>(toggle); }
	FORCEINLINE void SET_RADIO_TRACK(const char* radioStation, const char* radioTrack) { return YimMenu::NativeInvoker::Invoke<166, void>(radioStation, radioTrack); }
	FORCEINLINE void SET_RADIO_TRACK_WITH_START_OFFSET(const char* radioStationName, const char* mixName, int p2) { return YimMenu::NativeInvoker::Invoke<167, void>(radioStationName, mixName, p2); }
	FORCEINLINE void SET_NEXT_RADIO_TRACK(const char* radioName, const char* radioTrack, const char* p2, const char* p3) { return YimMenu::NativeInvoker::Invoke<168, void>(radioName, radioTrack, p2, p3); }
	FORCEINLINE void SET_VEHICLE_RADIO_LOUD(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<169, void>(vehicle, toggle); }
	FORCEINLINE bool CAN_VEHICLE_RECEIVE_CB_RADIO(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<170, bool>(vehicle); }
	FORCEINLINE void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(bool toggle) { return YimMenu::NativeInvoker::Invoke<171, void>(toggle); }
	FORCEINLINE bool DOES_PLAYER_VEH_HAVE_RADIO() { return YimMenu::NativeInvoker::Invoke<172, bool>(); }
	FORCEINLINE bool IS_PLAYER_VEH_RADIO_ENABLE() { return YimMenu::NativeInvoker::Invoke<173, bool>(); }
	FORCEINLINE void SET_VEHICLE_RADIO_ENABLED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<174, void>(vehicle, toggle); }
	FORCEINLINE void SET_POSITIONED_PLAYER_VEHICLE_RADIO_EMITTER_ENABLED(Any p0) { return YimMenu::NativeInvoker::Invoke<175, void>(p0); }
	FORCEINLINE void SET_CUSTOM_RADIO_TRACK_LIST(const char* radioStation, const char* trackListName, bool p2) { return YimMenu::NativeInvoker::Invoke<176, void>(radioStation, trackListName, p2); }
	FORCEINLINE void CLEAR_CUSTOM_RADIO_TRACK_LIST(const char* radioStation) { return YimMenu::NativeInvoker::Invoke<177, void>(radioStation); }
	FORCEINLINE int GET_NUM_UNLOCKED_RADIO_STATIONS() { return YimMenu::NativeInvoker::Invoke<178, int>(); }
	FORCEINLINE int FIND_RADIO_STATION_INDEX(Hash stationNameHash) { return YimMenu::NativeInvoker::Invoke<179, int>(stationNameHash); }
	FORCEINLINE void SET_RADIO_STATION_MUSIC_ONLY(const char* radioStation, bool toggle) { return YimMenu::NativeInvoker::Invoke<180, void>(radioStation, toggle); }
	FORCEINLINE void SET_RADIO_FRONTEND_FADE_TIME(float fadeTime) { return YimMenu::NativeInvoker::Invoke<181, void>(fadeTime); }
	FORCEINLINE void UNLOCK_RADIO_STATION_TRACK_LIST(const char* radioStation, const char* trackListName) { return YimMenu::NativeInvoker::Invoke<182, void>(radioStation, trackListName); }
	FORCEINLINE void LOCK_RADIO_STATION_TRACK_LIST(const char* radioStation, const char* trackListName) { return YimMenu::NativeInvoker::Invoke<183, void>(radioStation, trackListName); }
	FORCEINLINE void UPDATE_UNLOCKABLE_DJ_RADIO_TRACKS(bool enableMixes) { return YimMenu::NativeInvoker::Invoke<184, void>(enableMixes); }
	FORCEINLINE void LOCK_RADIO_STATION(const char* radioStationName, bool toggle) { return YimMenu::NativeInvoker::Invoke<185, void>(radioStationName, toggle); }
	FORCEINLINE void SET_RADIO_STATION_AS_FAVOURITE(const char* radioStation, bool toggle) { return YimMenu::NativeInvoker::Invoke<186, void>(radioStation, toggle); }
	FORCEINLINE bool IS_RADIO_STATION_FAVOURITED(const char* radioStation) { return YimMenu::NativeInvoker::Invoke<187, bool>(radioStation); }
	FORCEINLINE bool GET_NEXT_AUDIBLE_BEAT(float* out1, float* out2, int* out3) { return YimMenu::NativeInvoker::Invoke<188, bool>(out1, out2, out3); }
	FORCEINLINE void FORCE_MUSIC_TRACK_LIST(const char* radioStation, const char* trackListName, int milliseconds) { return YimMenu::NativeInvoker::Invoke<189, void>(radioStation, trackListName, milliseconds); }
	FORCEINLINE int GET_CURRENT_TRACK_PLAY_TIME(const char* radioStationName) { return YimMenu::NativeInvoker::Invoke<190, int>(radioStationName); }
	FORCEINLINE Hash GET_CURRENT_TRACK_SOUND_NAME(const char* radioStationName) { return YimMenu::NativeInvoker::Invoke<191, Hash>(radioStationName); }
	FORCEINLINE void SET_VEHICLE_MISSILE_WARNING_ENABLED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<192, void>(vehicle, toggle); }
	FORCEINLINE void SET_AMBIENT_ZONE_STATE(const char* zoneName, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<193, void>(zoneName, p1, p2); }
	FORCEINLINE void CLEAR_AMBIENT_ZONE_STATE(const char* zoneName, bool p1) { return YimMenu::NativeInvoker::Invoke<194, void>(zoneName, p1); }
	FORCEINLINE void SET_AMBIENT_ZONE_LIST_STATE(const char* ambientZone, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<195, void>(ambientZone, p1, p2); }
	FORCEINLINE void CLEAR_AMBIENT_ZONE_LIST_STATE(const char* ambientZone, bool p1) { return YimMenu::NativeInvoker::Invoke<196, void>(ambientZone, p1); }
	FORCEINLINE void SET_AMBIENT_ZONE_STATE_PERSISTENT(const char* ambientZone, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<197, void>(ambientZone, p1, p2); }
	FORCEINLINE void SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(const char* ambientZone, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<198, void>(ambientZone, p1, p2); }
	FORCEINLINE bool IS_AMBIENT_ZONE_ENABLED(const char* ambientZone) { return YimMenu::NativeInvoker::Invoke<199, bool>(ambientZone); }
	FORCEINLINE void REFRESH_CLOSEST_OCEAN_SHORELINE() { return YimMenu::NativeInvoker::Invoke<200, void>(); }
	FORCEINLINE void SET_CUTSCENE_AUDIO_OVERRIDE(const char* name) { return YimMenu::NativeInvoker::Invoke<201, void>(name); }
	FORCEINLINE void SET_VARIABLE_ON_SYNCH_SCENE_AUDIO(const char* variableName, float value) { return YimMenu::NativeInvoker::Invoke<202, void>(variableName, value); }
	FORCEINLINE int PLAY_POLICE_REPORT(const char* name, float p1) { return YimMenu::NativeInvoker::Invoke<203, int>(name, p1); }
	FORCEINLINE void CANCEL_ALL_POLICE_REPORTS() { return YimMenu::NativeInvoker::Invoke<204, void>(); }
	FORCEINLINE void BLIP_SIREN(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<205, void>(vehicle); }
	FORCEINLINE void OVERRIDE_VEH_HORN(Vehicle vehicle, bool override, int hornHash) { return YimMenu::NativeInvoker::Invoke<206, void>(vehicle, override, hornHash); }
	FORCEINLINE bool IS_HORN_ACTIVE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<207, bool>(vehicle); }
	FORCEINLINE void SET_AGGRESSIVE_HORNS(bool toggle) { return YimMenu::NativeInvoker::Invoke<208, void>(toggle); }
	FORCEINLINE void SET_RADIO_POSITION_AUDIO_MUTE(bool p0) { return YimMenu::NativeInvoker::Invoke<209, void>(p0); }
	FORCEINLINE void SET_VEHICLE_CONVERSATIONS_PERSIST(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<210, void>(p0, p1); }
	FORCEINLINE void SET_VEHICLE_CONVERSATIONS_PERSIST_NEW(bool p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<211, void>(p0, p1, p2); }
	FORCEINLINE bool IS_STREAM_PLAYING() { return YimMenu::NativeInvoker::Invoke<212, bool>(); }
	FORCEINLINE int GET_STREAM_PLAY_TIME() { return YimMenu::NativeInvoker::Invoke<213, int>(); }
	FORCEINLINE bool LOAD_STREAM(const char* streamName, const char* soundSet) { return YimMenu::NativeInvoker::Invoke<214, bool>(streamName, soundSet); }
	FORCEINLINE bool LOAD_STREAM_WITH_START_OFFSET(const char* streamName, int startOffset, const char* soundSet) { return YimMenu::NativeInvoker::Invoke<215, bool>(streamName, startOffset, soundSet); }
	FORCEINLINE void PLAY_STREAM_FROM_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<216, void>(ped); }
	FORCEINLINE void PLAY_STREAM_FROM_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<217, void>(vehicle); }
	FORCEINLINE void PLAY_STREAM_FROM_OBJECT(Object object) { return YimMenu::NativeInvoker::Invoke<218, void>(object); }
	FORCEINLINE void PLAY_STREAM_FRONTEND() { return YimMenu::NativeInvoker::Invoke<219, void>(); }
	FORCEINLINE void PLAY_STREAM_FROM_POSITION(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<220, void>(x, y, z); }
	FORCEINLINE void STOP_STREAM() { return YimMenu::NativeInvoker::Invoke<221, void>(); }
	FORCEINLINE void STOP_PED_SPEAKING(Ped ped, bool shaking) { return YimMenu::NativeInvoker::Invoke<222, void>(ped, shaking); }
	FORCEINLINE void BLOCK_ALL_SPEECH_FROM_PED(Ped ped, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<223, void>(ped, p1, p2); }
	FORCEINLINE void STOP_PED_SPEAKING_SYNCED(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<224, void>(ped, p1); }
	FORCEINLINE void DISABLE_PED_PAIN_AUDIO(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<225, void>(ped, toggle); }
	FORCEINLINE bool IS_AMBIENT_SPEECH_DISABLED(Ped ped) { return YimMenu::NativeInvoker::Invoke<226, bool>(ped); }
	FORCEINLINE void BLOCK_SPEECH_CONTEXT_GROUP(const char* p0, int p1) { return YimMenu::NativeInvoker::Invoke<227, void>(p0, p1); }
	FORCEINLINE void UNBLOCK_SPEECH_CONTEXT_GROUP(const char* p0) { return YimMenu::NativeInvoker::Invoke<228, void>(p0); }
	FORCEINLINE void SET_SIREN_WITH_NO_DRIVER(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<229, void>(vehicle, toggle); }
	FORCEINLINE void SET_SIREN_BYPASS_MP_DRIVER_CHECK(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<230, void>(vehicle, toggle); }
	FORCEINLINE void TRIGGER_SIREN_AUDIO(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<231, void>(vehicle); }
	FORCEINLINE void SET_HORN_PERMANENTLY_ON(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<232, void>(vehicle); }
	FORCEINLINE void SET_HORN_ENABLED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<233, void>(vehicle, toggle); }
	FORCEINLINE void SET_AUDIO_VEHICLE_PRIORITY(Vehicle vehicle, Any p1) { return YimMenu::NativeInvoker::Invoke<234, void>(vehicle, p1); }
	FORCEINLINE void SET_HORN_PERMANENTLY_ON_TIME(Vehicle vehicle, float time) { return YimMenu::NativeInvoker::Invoke<235, void>(vehicle, time); }
	FORCEINLINE void USE_SIREN_AS_HORN(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<236, void>(vehicle, toggle); }
	FORCEINLINE void FORCE_USE_AUDIO_GAME_OBJECT(Vehicle vehicle, const char* audioName) { return YimMenu::NativeInvoker::Invoke<237, void>(vehicle, audioName); }
	FORCEINLINE void PRELOAD_VEHICLE_AUDIO_BANK(Hash vehicleModel) { return YimMenu::NativeInvoker::Invoke<238, void>(vehicleModel); }
	FORCEINLINE void SET_VEHICLE_STARTUP_REV_SOUND(Vehicle vehicle, const char* p1, const char* p2) { return YimMenu::NativeInvoker::Invoke<239, void>(vehicle, p1, p2); }
	FORCEINLINE void RESET_VEHICLE_STARTUP_REV_SOUND(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<240, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_FORCE_REVERSE_WARNING(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<241, void>(p0, p1); }
	FORCEINLINE bool IS_VEHICLE_AUDIBLY_DAMAGED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<242, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_AUDIO_ENGINE_DAMAGE_FACTOR(Vehicle vehicle, float damageFactor) { return YimMenu::NativeInvoker::Invoke<243, void>(vehicle, damageFactor); }
	FORCEINLINE void SET_VEHICLE_AUDIO_BODY_DAMAGE_FACTOR(Vehicle vehicle, float intensity) { return YimMenu::NativeInvoker::Invoke<244, void>(vehicle, intensity); }
	FORCEINLINE void ENABLE_VEHICLE_FANBELT_DAMAGE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<245, void>(vehicle, toggle); }
	FORCEINLINE void ENABLE_VEHICLE_EXHAUST_POPS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<246, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_BOOST_ACTIVE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<247, void>(vehicle, toggle); }
	FORCEINLINE void SET_PLAYER_VEHICLE_ALARM_AUDIO_ACTIVE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<248, void>(vehicle, toggle); }
	FORCEINLINE void SET_SCRIPT_UPDATE_DOOR_AUDIO(Hash doorHash, bool toggle) { return YimMenu::NativeInvoker::Invoke<249, void>(doorHash, toggle); }
	FORCEINLINE void PLAY_VEHICLE_DOOR_OPEN_SOUND(Vehicle vehicle, int doorId) { return YimMenu::NativeInvoker::Invoke<250, void>(vehicle, doorId); }
	FORCEINLINE void PLAY_VEHICLE_DOOR_CLOSE_SOUND(Vehicle vehicle, int doorId) { return YimMenu::NativeInvoker::Invoke<251, void>(vehicle, doorId); }
	FORCEINLINE void ENABLE_STALL_WARNING_SOUNDS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<252, void>(vehicle, toggle); }
	FORCEINLINE bool IS_GAME_IN_CONTROL_OF_MUSIC() { return YimMenu::NativeInvoker::Invoke<253, bool>(); }
	FORCEINLINE void SET_GPS_ACTIVE(bool active) { return YimMenu::NativeInvoker::Invoke<254, void>(active); }
	FORCEINLINE void PLAY_MISSION_COMPLETE_AUDIO(const char* audioName) { return YimMenu::NativeInvoker::Invoke<255, void>(audioName); }
	FORCEINLINE bool IS_MISSION_COMPLETE_PLAYING() { return YimMenu::NativeInvoker::Invoke<256, bool>(); }
	FORCEINLINE bool IS_MISSION_COMPLETE_READY_FOR_UI() { return YimMenu::NativeInvoker::Invoke<257, bool>(); }
	FORCEINLINE void BLOCK_DEATH_JINGLE(bool toggle) { return YimMenu::NativeInvoker::Invoke<258, void>(toggle); }
	FORCEINLINE bool START_AUDIO_SCENE(const char* scene) { return YimMenu::NativeInvoker::Invoke<259, bool>(scene); }
	FORCEINLINE void STOP_AUDIO_SCENE(const char* scene) { return YimMenu::NativeInvoker::Invoke<260, void>(scene); }
	FORCEINLINE void STOP_AUDIO_SCENES() { return YimMenu::NativeInvoker::Invoke<261, void>(); }
	FORCEINLINE bool IS_AUDIO_SCENE_ACTIVE(const char* scene) { return YimMenu::NativeInvoker::Invoke<262, bool>(scene); }
	FORCEINLINE void SET_AUDIO_SCENE_VARIABLE(const char* scene, const char* variable, float value) { return YimMenu::NativeInvoker::Invoke<263, void>(scene, variable, value); }
	FORCEINLINE void SET_AUDIO_SCRIPT_CLEANUP_TIME(int time) { return YimMenu::NativeInvoker::Invoke<264, void>(time); }
	FORCEINLINE void ADD_ENTITY_TO_AUDIO_MIX_GROUP(Entity entity, const char* groupName, float p2) { return YimMenu::NativeInvoker::Invoke<265, void>(entity, groupName, p2); }
	FORCEINLINE void REMOVE_ENTITY_FROM_AUDIO_MIX_GROUP(Entity entity, float p1) { return YimMenu::NativeInvoker::Invoke<266, void>(entity, p1); }
	FORCEINLINE bool AUDIO_IS_MUSIC_PLAYING() { return YimMenu::NativeInvoker::Invoke<267, bool>(); }
	FORCEINLINE bool AUDIO_IS_SCRIPTED_MUSIC_PLAYING() { return YimMenu::NativeInvoker::Invoke<268, bool>(); }
	FORCEINLINE bool PREPARE_MUSIC_EVENT(const char* eventName) { return YimMenu::NativeInvoker::Invoke<269, bool>(eventName); }
	FORCEINLINE bool CANCEL_MUSIC_EVENT(const char* eventName) { return YimMenu::NativeInvoker::Invoke<270, bool>(eventName); }
	FORCEINLINE bool TRIGGER_MUSIC_EVENT(const char* eventName) { return YimMenu::NativeInvoker::Invoke<271, bool>(eventName); }
	FORCEINLINE bool IS_MUSIC_ONESHOT_PLAYING() { return YimMenu::NativeInvoker::Invoke<272, bool>(); }
	FORCEINLINE int GET_MUSIC_PLAYTIME() { return YimMenu::NativeInvoker::Invoke<273, int>(); }
	FORCEINLINE void SET_GLOBAL_RADIO_SIGNAL_LEVEL(Any p0) { return YimMenu::NativeInvoker::Invoke<274, void>(p0); }
	FORCEINLINE void RECORD_BROKEN_GLASS(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<275, void>(x, y, z, radius); }
	FORCEINLINE void CLEAR_ALL_BROKEN_GLASS() { return YimMenu::NativeInvoker::Invoke<276, void>(); }
	FORCEINLINE void SCRIPT_OVERRIDES_WIND_ELEVATION(bool p0, Any p1) { return YimMenu::NativeInvoker::Invoke<277, void>(p0, p1); }
	FORCEINLINE void SET_PED_WALLA_DENSITY(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<278, void>(p0, p1); }
	FORCEINLINE void SET_PED_INTERIOR_WALLA_DENSITY(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<279, void>(p0, p1); }
	FORCEINLINE void FORCE_PED_PANIC_WALLA() { return YimMenu::NativeInvoker::Invoke<280, void>(); }
	FORCEINLINE bool PREPARE_ALARM(const char* alarmName) { return YimMenu::NativeInvoker::Invoke<281, bool>(alarmName); }
	FORCEINLINE void START_ALARM(const char* alarmName, bool p2) { return YimMenu::NativeInvoker::Invoke<282, void>(alarmName, p2); }
	FORCEINLINE void STOP_ALARM(const char* alarmName, bool toggle) { return YimMenu::NativeInvoker::Invoke<283, void>(alarmName, toggle); }
	FORCEINLINE void STOP_ALL_ALARMS(bool stop) { return YimMenu::NativeInvoker::Invoke<284, void>(stop); }
	FORCEINLINE bool IS_ALARM_PLAYING(const char* alarmName) { return YimMenu::NativeInvoker::Invoke<285, bool>(alarmName); }
	FORCEINLINE Hash GET_VEHICLE_DEFAULT_HORN(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<286, Hash>(vehicle); }
	FORCEINLINE Hash GET_VEHICLE_DEFAULT_HORN_IGNORE_MODS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<287, Hash>(vehicle); }
	FORCEINLINE void RESET_PED_AUDIO_FLAGS(Ped ped) { return YimMenu::NativeInvoker::Invoke<288, void>(ped); }
	FORCEINLINE void SET_PED_FOOTSTEPS_EVENTS_ENABLED(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<289, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CLOTH_EVENTS_ENABLED(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<290, void>(ped, toggle); }
	FORCEINLINE void OVERRIDE_PLAYER_GROUND_MATERIAL(Hash hash, bool toggle) { return YimMenu::NativeInvoker::Invoke<291, void>(hash, toggle); }
	FORCEINLINE void USE_FOOTSTEP_SCRIPT_SWEETENERS(Ped ped, bool p1, Hash hash) { return YimMenu::NativeInvoker::Invoke<292, void>(ped, p1, hash); }
	FORCEINLINE void OVERRIDE_MICROPHONE_SETTINGS(Hash hash, bool toggle) { return YimMenu::NativeInvoker::Invoke<293, void>(hash, toggle); }
	FORCEINLINE void FREEZE_MICROPHONE() { return YimMenu::NativeInvoker::Invoke<294, void>(); }
	FORCEINLINE void DISTANT_COP_CAR_SIRENS(bool value) { return YimMenu::NativeInvoker::Invoke<295, void>(value); }
	FORCEINLINE void SET_SIREN_CAN_BE_CONTROLLED_BY_AUDIO(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<296, void>(vehicle, p1); }
	FORCEINLINE void ENABLE_STUNT_JUMP_AUDIO() { return YimMenu::NativeInvoker::Invoke<297, void>(); }
	FORCEINLINE void SET_AUDIO_FLAG(const char* flagName, bool toggle) { return YimMenu::NativeInvoker::Invoke<298, void>(flagName, toggle); }
	FORCEINLINE bool PREPARE_SYNCHRONIZED_AUDIO_EVENT(const char* audioEvent, Any p1) { return YimMenu::NativeInvoker::Invoke<299, bool>(audioEvent, p1); }
	FORCEINLINE bool PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(int sceneID, const char* audioEvent) { return YimMenu::NativeInvoker::Invoke<300, bool>(sceneID, audioEvent); }
	FORCEINLINE bool PLAY_SYNCHRONIZED_AUDIO_EVENT(int sceneID) { return YimMenu::NativeInvoker::Invoke<301, bool>(sceneID); }
	FORCEINLINE bool STOP_SYNCHRONIZED_AUDIO_EVENT(int sceneID) { return YimMenu::NativeInvoker::Invoke<302, bool>(sceneID); }
	FORCEINLINE void INIT_SYNCH_SCENE_AUDIO_WITH_POSITION(const char* audioEvent, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<303, void>(audioEvent, x, y, z); }
	FORCEINLINE void INIT_SYNCH_SCENE_AUDIO_WITH_ENTITY(const char* audioEvent, Entity entity) { return YimMenu::NativeInvoker::Invoke<304, void>(audioEvent, entity); }
	FORCEINLINE void SET_AUDIO_SPECIAL_EFFECT_MODE(int mode) { return YimMenu::NativeInvoker::Invoke<305, void>(mode); }
	FORCEINLINE void SET_PORTAL_SETTINGS_OVERRIDE(const char* p0, const char* p1) { return YimMenu::NativeInvoker::Invoke<306, void>(p0, p1); }
	FORCEINLINE void REMOVE_PORTAL_SETTINGS_OVERRIDE(const char* p0) { return YimMenu::NativeInvoker::Invoke<307, void>(p0); }
	FORCEINLINE void STOP_SMOKE_GRENADE_EXPLOSION_SOUNDS() { return YimMenu::NativeInvoker::Invoke<308, void>(); }
	FORCEINLINE int GET_MUSIC_VOL_SLIDER() { return YimMenu::NativeInvoker::Invoke<309, int>(); }
	FORCEINLINE void REQUEST_TENNIS_BANKS(Ped ped) { return YimMenu::NativeInvoker::Invoke<310, void>(ped); }
	FORCEINLINE void UNREQUEST_TENNIS_BANKS() { return YimMenu::NativeInvoker::Invoke<311, void>(); }
	FORCEINLINE void SET_SKIP_MINIGUN_SPIN_UP_AUDIO(bool p0) { return YimMenu::NativeInvoker::Invoke<312, void>(p0); }
	FORCEINLINE void STOP_CUTSCENE_AUDIO() { return YimMenu::NativeInvoker::Invoke<313, void>(); }
	FORCEINLINE bool HAS_LOADED_MP_DATA_SET() { return YimMenu::NativeInvoker::Invoke<314, bool>(); }
	FORCEINLINE bool HAS_LOADED_SP_DATA_SET() { return YimMenu::NativeInvoker::Invoke<315, bool>(); }
	FORCEINLINE int GET_VEHICLE_HORN_SOUND_INDEX(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<316, int>(vehicle); }
	FORCEINLINE void SET_VEHICLE_HORN_SOUND_INDEX(Vehicle vehicle, int value) { return YimMenu::NativeInvoker::Invoke<317, void>(vehicle, value); }
}

namespace BRAIN
{
	FORCEINLINE void ADD_SCRIPT_TO_RANDOM_PED(const char* name, Hash model, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<318, void>(name, model, p2, p3); }
	FORCEINLINE void REGISTER_OBJECT_SCRIPT_BRAIN(const char* scriptName, Hash modelHash, int p2, float activationRange, int p4, int p5) { return YimMenu::NativeInvoker::Invoke<319, void>(scriptName, modelHash, p2, activationRange, p4, p5); }
	FORCEINLINE bool IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Object object) { return YimMenu::NativeInvoker::Invoke<320, bool>(object); }
	FORCEINLINE void REGISTER_WORLD_POINT_SCRIPT_BRAIN(const char* scriptName, float activationRange, int p2) { return YimMenu::NativeInvoker::Invoke<321, void>(scriptName, activationRange, p2); }
	FORCEINLINE bool IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE() { return YimMenu::NativeInvoker::Invoke<322, bool>(); }
	FORCEINLINE void ENABLE_SCRIPT_BRAIN_SET(int brainSet) { return YimMenu::NativeInvoker::Invoke<323, void>(brainSet); }
	FORCEINLINE void DISABLE_SCRIPT_BRAIN_SET(int brainSet) { return YimMenu::NativeInvoker::Invoke<324, void>(brainSet); }
	FORCEINLINE void REACTIVATE_ALL_WORLD_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE() { return YimMenu::NativeInvoker::Invoke<325, void>(); }
	FORCEINLINE void REACTIVATE_ALL_OBJECT_BRAINS_THAT_ARE_WAITING_TILL_OUT_OF_RANGE() { return YimMenu::NativeInvoker::Invoke<326, void>(); }
	FORCEINLINE void REACTIVATE_NAMED_WORLD_BRAINS_WAITING_TILL_OUT_OF_RANGE(const char* scriptName) { return YimMenu::NativeInvoker::Invoke<327, void>(scriptName); }
	FORCEINLINE void REACTIVATE_NAMED_OBJECT_BRAINS_WAITING_TILL_OUT_OF_RANGE(const char* scriptName) { return YimMenu::NativeInvoker::Invoke<328, void>(scriptName); }
}

namespace CAM
{
	FORCEINLINE void RENDER_SCRIPT_CAMS(bool render, bool ease, int easeTime, bool p3, bool p4, Any p5) { return YimMenu::NativeInvoker::Invoke<329, void>(render, ease, easeTime, p3, p4, p5); }
	FORCEINLINE void STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP(bool render, float p1, int p2, Any p3) { return YimMenu::NativeInvoker::Invoke<330, void>(render, p1, p2, p3); }
	FORCEINLINE Cam CREATE_CAM(const char* camName, bool p1) { return YimMenu::NativeInvoker::Invoke<331, Cam>(camName, p1); }
	FORCEINLINE Cam CREATE_CAM_WITH_PARAMS(const char* camName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, bool p8, int p9) { return YimMenu::NativeInvoker::Invoke<332, Cam>(camName, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); }
	FORCEINLINE Cam CREATE_CAMERA(Hash camHash, bool p1) { return YimMenu::NativeInvoker::Invoke<333, Cam>(camHash, p1); }
	FORCEINLINE Cam CREATE_CAMERA_WITH_PARAMS(Hash camHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, bool p8, Any p9) { return YimMenu::NativeInvoker::Invoke<334, Cam>(camHash, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9); }
	FORCEINLINE void DESTROY_CAM(Cam cam, bool bScriptHostCam) { return YimMenu::NativeInvoker::Invoke<335, void>(cam, bScriptHostCam); }
	FORCEINLINE void DESTROY_ALL_CAMS(bool bScriptHostCam) { return YimMenu::NativeInvoker::Invoke<336, void>(bScriptHostCam); }
	FORCEINLINE bool DOES_CAM_EXIST(Cam cam) { return YimMenu::NativeInvoker::Invoke<337, bool>(cam); }
	FORCEINLINE void SET_CAM_ACTIVE(Cam cam, bool active) { return YimMenu::NativeInvoker::Invoke<338, void>(cam, active); }
	FORCEINLINE bool IS_CAM_ACTIVE(Cam cam) { return YimMenu::NativeInvoker::Invoke<339, bool>(cam); }
	FORCEINLINE bool IS_CAM_RENDERING(Cam cam) { return YimMenu::NativeInvoker::Invoke<340, bool>(cam); }
	FORCEINLINE Cam GET_RENDERING_CAM() { return YimMenu::NativeInvoker::Invoke<341, Cam>(); }
	FORCEINLINE Vector3 GET_CAM_COORD(Cam cam) { return YimMenu::NativeInvoker::Invoke<342, Vector3>(cam); }
	FORCEINLINE Vector3 GET_CAM_ROT(Cam cam, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<343, Vector3>(cam, rotationOrder); }
	FORCEINLINE float GET_CAM_FOV(Cam cam) { return YimMenu::NativeInvoker::Invoke<344, float>(cam); }
	FORCEINLINE float GET_CAM_NEAR_CLIP(Cam cam) { return YimMenu::NativeInvoker::Invoke<345, float>(cam); }
	FORCEINLINE float GET_CAM_FAR_CLIP(Cam cam) { return YimMenu::NativeInvoker::Invoke<346, float>(cam); }
	FORCEINLINE float GET_CAM_NEAR_DOF(Cam cam) { return YimMenu::NativeInvoker::Invoke<347, float>(cam); }
	FORCEINLINE float GET_CAM_FAR_DOF(Cam cam) { return YimMenu::NativeInvoker::Invoke<348, float>(cam); }
	FORCEINLINE float GET_CAM_DOF_STRENGTH(Cam cam) { return YimMenu::NativeInvoker::Invoke<349, float>(cam); }
	FORCEINLINE void SET_CAM_PARAMS(Cam cam, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fieldOfView, Any p8, int p9, int p10, int p11) { return YimMenu::NativeInvoker::Invoke<350, void>(cam, posX, posY, posZ, rotX, rotY, rotZ, fieldOfView, p8, p9, p10, p11); }
	FORCEINLINE void SET_CAM_COORD(Cam cam, float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<351, void>(cam, posX, posY, posZ); }
	FORCEINLINE void SET_CAM_ROT(Cam cam, float rotX, float rotY, float rotZ, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<352, void>(cam, rotX, rotY, rotZ, rotationOrder); }
	FORCEINLINE void SET_CAM_FOV(Cam cam, float fieldOfView) { return YimMenu::NativeInvoker::Invoke<353, void>(cam, fieldOfView); }
	FORCEINLINE void SET_CAM_NEAR_CLIP(Cam cam, float nearClip) { return YimMenu::NativeInvoker::Invoke<354, void>(cam, nearClip); }
	FORCEINLINE void SET_CAM_FAR_CLIP(Cam cam, float farClip) { return YimMenu::NativeInvoker::Invoke<355, void>(cam, farClip); }
	FORCEINLINE void FORCE_CAM_FAR_CLIP(Cam cam, float p1) { return YimMenu::NativeInvoker::Invoke<356, void>(cam, p1); }
	FORCEINLINE void SET_CAM_MOTION_BLUR_STRENGTH(Cam cam, float strength) { return YimMenu::NativeInvoker::Invoke<357, void>(cam, strength); }
	FORCEINLINE void SET_CAM_NEAR_DOF(Cam cam, float nearDOF) { return YimMenu::NativeInvoker::Invoke<358, void>(cam, nearDOF); }
	FORCEINLINE void SET_CAM_FAR_DOF(Cam cam, float farDOF) { return YimMenu::NativeInvoker::Invoke<359, void>(cam, farDOF); }
	FORCEINLINE void SET_CAM_DOF_STRENGTH(Cam cam, float dofStrength) { return YimMenu::NativeInvoker::Invoke<360, void>(cam, dofStrength); }
	FORCEINLINE void SET_CAM_DOF_PLANES(Cam cam, float p1, float p2, float p3, float p4) { return YimMenu::NativeInvoker::Invoke<361, void>(cam, p1, p2, p3, p4); }
	FORCEINLINE void SET_CAM_USE_SHALLOW_DOF_MODE(Cam cam, bool toggle) { return YimMenu::NativeInvoker::Invoke<362, void>(cam, toggle); }
	FORCEINLINE void SET_USE_HI_DOF() { return YimMenu::NativeInvoker::Invoke<363, void>(); }
	FORCEINLINE void SET_USE_HI_DOF_ON_SYNCED_SCENE_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<364, void>(); }
	FORCEINLINE void SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE(Cam camera, float p1) { return YimMenu::NativeInvoker::Invoke<365, void>(camera, p1); }
	FORCEINLINE void SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE_BLEND_LEVEL(Any p0, float p1) { return YimMenu::NativeInvoker::Invoke<366, void>(p0, p1); }
	FORCEINLINE void SET_CAM_DOF_FNUMBER_OF_LENS(Cam camera, float p1) { return YimMenu::NativeInvoker::Invoke<367, void>(camera, p1); }
	FORCEINLINE void SET_CAM_DOF_FOCAL_LENGTH_MULTIPLIER(Cam camera, float multiplier) { return YimMenu::NativeInvoker::Invoke<368, void>(camera, multiplier); }
	FORCEINLINE void SET_CAM_DOF_FOCUS_DISTANCE_BIAS(Cam camera, float p1) { return YimMenu::NativeInvoker::Invoke<369, void>(camera, p1); }
	FORCEINLINE void SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(Cam camera, float p1) { return YimMenu::NativeInvoker::Invoke<370, void>(camera, p1); }
	FORCEINLINE void SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(Cam camera, float p1) { return YimMenu::NativeInvoker::Invoke<371, void>(camera, p1); }
	FORCEINLINE void ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, float xOffset, float yOffset, float zOffset, bool isRelative) { return YimMenu::NativeInvoker::Invoke<372, void>(cam, entity, xOffset, yOffset, zOffset, isRelative); }
	FORCEINLINE void ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, float x, float y, float z, bool heading) { return YimMenu::NativeInvoker::Invoke<373, void>(cam, ped, boneIndex, x, y, z, heading); }
	FORCEINLINE void HARD_ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, float p3, float p4, float p5, float p6, float p7, float p8, bool p9) { return YimMenu::NativeInvoker::Invoke<374, void>(cam, ped, boneIndex, p3, p4, p5, p6, p7, p8, p9); }
	FORCEINLINE void HARD_ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, float xRot, float yRot, float zRot, float xOffset, float yOffset, float zOffset, bool isRelative) { return YimMenu::NativeInvoker::Invoke<375, void>(cam, entity, xRot, yRot, zRot, xOffset, yOffset, zOffset, isRelative); }
	FORCEINLINE void ATTACH_CAM_TO_VEHICLE_BONE(Cam cam, Vehicle vehicle, int boneIndex, bool relativeRotation, float rotX, float rotY, float rotZ, float offsetX, float offsetY, float offsetZ, bool fixedDirection) { return YimMenu::NativeInvoker::Invoke<376, void>(cam, vehicle, boneIndex, relativeRotation, rotX, rotY, rotZ, offsetX, offsetY, offsetZ, fixedDirection); }
	FORCEINLINE void DETACH_CAM(Cam cam) { return YimMenu::NativeInvoker::Invoke<377, void>(cam); }
	FORCEINLINE void SET_CAM_INHERIT_ROLL_VEHICLE(Cam cam, bool p1) { return YimMenu::NativeInvoker::Invoke<378, void>(cam, p1); }
	FORCEINLINE void POINT_CAM_AT_COORD(Cam cam, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<379, void>(cam, x, y, z); }
	FORCEINLINE void POINT_CAM_AT_ENTITY(Cam cam, Entity entity, float p2, float p3, float p4, bool p5) { return YimMenu::NativeInvoker::Invoke<380, void>(cam, entity, p2, p3, p4, p5); }
	FORCEINLINE void POINT_CAM_AT_PED_BONE(Cam cam, Ped ped, int boneIndex, float x, float y, float z, bool p6) { return YimMenu::NativeInvoker::Invoke<381, void>(cam, ped, boneIndex, x, y, z, p6); }
	FORCEINLINE void STOP_CAM_POINTING(Cam cam) { return YimMenu::NativeInvoker::Invoke<382, void>(cam); }
	FORCEINLINE void SET_CAM_AFFECTS_AIMING(Cam cam, bool toggle) { return YimMenu::NativeInvoker::Invoke<383, void>(cam, toggle); }
	FORCEINLINE void SET_CAM_CONTROLS_MINI_MAP_HEADING(Cam cam, bool toggle) { return YimMenu::NativeInvoker::Invoke<384, void>(cam, toggle); }
	FORCEINLINE void SET_CAM_IS_INSIDE_VEHICLE(Cam cam, bool toggle) { return YimMenu::NativeInvoker::Invoke<385, void>(cam, toggle); }
	FORCEINLINE void ALLOW_MOTION_BLUR_DECAY(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<386, void>(p0, p1); }
	FORCEINLINE void SET_CAM_DEBUG_NAME(Cam camera, const char* name) { return YimMenu::NativeInvoker::Invoke<387, void>(camera, name); }
	FORCEINLINE Cam GET_DEBUG_CAM() { return YimMenu::NativeInvoker::Invoke<388, Cam>(); }
	FORCEINLINE void ADD_CAM_SPLINE_NODE(Cam camera, float x, float y, float z, float xRot, float yRot, float zRot, int length, int smoothingStyle, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<389, void>(camera, x, y, z, xRot, yRot, zRot, length, smoothingStyle, rotationOrder); }
	FORCEINLINE void ADD_CAM_SPLINE_NODE_USING_CAMERA_FRAME(Cam cam, Cam cam2, int length, int p3) { return YimMenu::NativeInvoker::Invoke<390, void>(cam, cam2, length, p3); }
	FORCEINLINE void ADD_CAM_SPLINE_NODE_USING_CAMERA(Cam cam, Cam cam2, int length, int p3) { return YimMenu::NativeInvoker::Invoke<391, void>(cam, cam2, length, p3); }
	FORCEINLINE void ADD_CAM_SPLINE_NODE_USING_GAMEPLAY_FRAME(Cam cam, int length, int p2) { return YimMenu::NativeInvoker::Invoke<392, void>(cam, length, p2); }
	FORCEINLINE void SET_CAM_SPLINE_PHASE(Cam cam, float p1) { return YimMenu::NativeInvoker::Invoke<393, void>(cam, p1); }
	FORCEINLINE float GET_CAM_SPLINE_PHASE(Cam cam) { return YimMenu::NativeInvoker::Invoke<394, float>(cam); }
	FORCEINLINE float GET_CAM_SPLINE_NODE_PHASE(Cam cam) { return YimMenu::NativeInvoker::Invoke<395, float>(cam); }
	FORCEINLINE void SET_CAM_SPLINE_DURATION(Cam cam, int timeDuration) { return YimMenu::NativeInvoker::Invoke<396, void>(cam, timeDuration); }
	FORCEINLINE void SET_CAM_SPLINE_SMOOTHING_STYLE(Cam cam, int smoothingStyle) { return YimMenu::NativeInvoker::Invoke<397, void>(cam, smoothingStyle); }
	FORCEINLINE int GET_CAM_SPLINE_NODE_INDEX(Cam cam) { return YimMenu::NativeInvoker::Invoke<398, int>(cam); }
	FORCEINLINE void SET_CAM_SPLINE_NODE_EASE(Cam cam, int easingFunction, int p2, float p3) { return YimMenu::NativeInvoker::Invoke<399, void>(cam, easingFunction, p2, p3); }
	FORCEINLINE void SET_CAM_SPLINE_NODE_VELOCITY_SCALE(Cam cam, int p1, float scale) { return YimMenu::NativeInvoker::Invoke<400, void>(cam, p1, scale); }
	FORCEINLINE void OVERRIDE_CAM_SPLINE_VELOCITY(Cam cam, int p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<401, void>(cam, p1, p2, p3); }
	FORCEINLINE void OVERRIDE_CAM_SPLINE_MOTION_BLUR(Cam cam, int p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<402, void>(cam, p1, p2, p3); }
	FORCEINLINE void SET_CAM_SPLINE_NODE_EXTRA_FLAGS(Cam cam, int p1, int flags) { return YimMenu::NativeInvoker::Invoke<403, void>(cam, p1, flags); }
	FORCEINLINE bool IS_CAM_SPLINE_PAUSED(Cam cam) { return YimMenu::NativeInvoker::Invoke<404, bool>(cam); }
	FORCEINLINE void SET_CAM_ACTIVE_WITH_INTERP(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation) { return YimMenu::NativeInvoker::Invoke<405, void>(camTo, camFrom, duration, easeLocation, easeRotation); }
	FORCEINLINE bool IS_CAM_INTERPOLATING(Cam cam) { return YimMenu::NativeInvoker::Invoke<406, bool>(cam); }
	FORCEINLINE void SHAKE_CAM(Cam cam, const char* type, float amplitude) { return YimMenu::NativeInvoker::Invoke<407, void>(cam, type, amplitude); }
	FORCEINLINE void ANIMATED_SHAKE_CAM(Cam cam, const char* p1, const char* p2, const char* p3, float amplitude) { return YimMenu::NativeInvoker::Invoke<408, void>(cam, p1, p2, p3, amplitude); }
	FORCEINLINE bool IS_CAM_SHAKING(Cam cam) { return YimMenu::NativeInvoker::Invoke<409, bool>(cam); }
	FORCEINLINE void SET_CAM_SHAKE_AMPLITUDE(Cam cam, float amplitude) { return YimMenu::NativeInvoker::Invoke<410, void>(cam, amplitude); }
	FORCEINLINE void STOP_CAM_SHAKING(Cam cam, bool p1) { return YimMenu::NativeInvoker::Invoke<411, void>(cam, p1); }
	FORCEINLINE void SHAKE_SCRIPT_GLOBAL(const char* p0, float p1) { return YimMenu::NativeInvoker::Invoke<412, void>(p0, p1); }
	FORCEINLINE void ANIMATED_SHAKE_SCRIPT_GLOBAL(const char* p0, const char* p1, const char* p2, float p3) { return YimMenu::NativeInvoker::Invoke<413, void>(p0, p1, p2, p3); }
	FORCEINLINE bool IS_SCRIPT_GLOBAL_SHAKING() { return YimMenu::NativeInvoker::Invoke<414, bool>(); }
	FORCEINLINE void STOP_SCRIPT_GLOBAL_SHAKING(bool p0) { return YimMenu::NativeInvoker::Invoke<415, void>(p0); }
	FORCEINLINE void TRIGGER_VEHICLE_PART_BROKEN_CAMERA_SHAKE(Vehicle vehicle, int p1, float p2) { return YimMenu::NativeInvoker::Invoke<416, void>(vehicle, p1, p2); }
	FORCEINLINE bool PLAY_CAM_ANIM(Cam cam, const char* animName, const char* animDictionary, float x, float y, float z, float xRot, float yRot, float zRot, bool p9, int p10) { return YimMenu::NativeInvoker::Invoke<417, bool>(cam, animName, animDictionary, x, y, z, xRot, yRot, zRot, p9, p10); }
	FORCEINLINE bool IS_CAM_PLAYING_ANIM(Cam cam, const char* animName, const char* animDictionary) { return YimMenu::NativeInvoker::Invoke<418, bool>(cam, animName, animDictionary); }
	FORCEINLINE void SET_CAM_ANIM_CURRENT_PHASE(Cam cam, float phase) { return YimMenu::NativeInvoker::Invoke<419, void>(cam, phase); }
	FORCEINLINE float GET_CAM_ANIM_CURRENT_PHASE(Cam cam) { return YimMenu::NativeInvoker::Invoke<420, float>(cam); }
	FORCEINLINE bool PLAY_SYNCHRONIZED_CAM_ANIM(Any p0, Any p1, const char* animName, const char* animDictionary) { return YimMenu::NativeInvoker::Invoke<421, bool>(p0, p1, animName, animDictionary); }
	FORCEINLINE void SET_FLY_CAM_HORIZONTAL_RESPONSE(Cam cam, float p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<422, void>(cam, p1, p2, p3); }
	FORCEINLINE void SET_FLY_CAM_VERTICAL_RESPONSE(Cam cam, float p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<423, void>(cam, p1, p2, p3); }
	FORCEINLINE void SET_FLY_CAM_MAX_HEIGHT(Cam cam, float height) { return YimMenu::NativeInvoker::Invoke<424, void>(cam, height); }
	FORCEINLINE void SET_FLY_CAM_COORD_AND_CONSTRAIN(Cam cam, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<425, void>(cam, x, y, z); }
	FORCEINLINE void SET_FLY_CAM_VERTICAL_CONTROLS_THIS_UPDATE(Cam cam) { return YimMenu::NativeInvoker::Invoke<426, void>(cam); }
	FORCEINLINE bool WAS_FLY_CAM_CONSTRAINED_ON_PREVIOUS_UDPATE(Cam cam) { return YimMenu::NativeInvoker::Invoke<427, bool>(cam); }
	FORCEINLINE bool IS_SCREEN_FADED_OUT() { return YimMenu::NativeInvoker::Invoke<428, bool>(); }
	FORCEINLINE bool IS_SCREEN_FADED_IN() { return YimMenu::NativeInvoker::Invoke<429, bool>(); }
	FORCEINLINE bool IS_SCREEN_FADING_OUT() { return YimMenu::NativeInvoker::Invoke<430, bool>(); }
	FORCEINLINE bool IS_SCREEN_FADING_IN() { return YimMenu::NativeInvoker::Invoke<431, bool>(); }
	FORCEINLINE void DO_SCREEN_FADE_IN(int duration) { return YimMenu::NativeInvoker::Invoke<432, void>(duration); }
	FORCEINLINE void DO_SCREEN_FADE_OUT(int duration) { return YimMenu::NativeInvoker::Invoke<433, void>(duration); }
	FORCEINLINE void SET_WIDESCREEN_BORDERS(bool p0, int p1) { return YimMenu::NativeInvoker::Invoke<434, void>(p0, p1); }
	FORCEINLINE bool ARE_WIDESCREEN_BORDERS_ACTIVE() { return YimMenu::NativeInvoker::Invoke<435, bool>(); }
	FORCEINLINE Vector3 GET_GAMEPLAY_CAM_COORD() { return YimMenu::NativeInvoker::Invoke<436, Vector3>(); }
	FORCEINLINE Vector3 GET_GAMEPLAY_CAM_ROT(int rotationOrder) { return YimMenu::NativeInvoker::Invoke<437, Vector3>(rotationOrder); }
	FORCEINLINE float GET_GAMEPLAY_CAM_FOV() { return YimMenu::NativeInvoker::Invoke<438, float>(); }
	FORCEINLINE void SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE(float p0) { return YimMenu::NativeInvoker::Invoke<439, void>(p0); }
	FORCEINLINE void SET_GAMEPLAY_CAM_MAX_MOTION_BLUR_STRENGTH_THIS_UPDATE(float p0) { return YimMenu::NativeInvoker::Invoke<440, void>(p0); }
	FORCEINLINE float GET_GAMEPLAY_CAM_RELATIVE_HEADING() { return YimMenu::NativeInvoker::Invoke<441, float>(); }
	FORCEINLINE void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading) { return YimMenu::NativeInvoker::Invoke<442, void>(heading); }
	FORCEINLINE float GET_GAMEPLAY_CAM_RELATIVE_PITCH() { return YimMenu::NativeInvoker::Invoke<443, float>(); }
	FORCEINLINE void SET_GAMEPLAY_CAM_RELATIVE_PITCH(float angle, float scalingFactor) { return YimMenu::NativeInvoker::Invoke<444, void>(angle, scalingFactor); }
	FORCEINLINE void RESET_GAMEPLAY_CAM_FULL_ATTACH_PARENT_TRANSFORM_TIMER() { return YimMenu::NativeInvoker::Invoke<445, void>(); }
	FORCEINLINE void FORCE_CAMERA_RELATIVE_HEADING_AND_PITCH(float roll, float pitch, float yaw) { return YimMenu::NativeInvoker::Invoke<446, void>(roll, pitch, yaw); }
	FORCEINLINE void FORCE_BONNET_CAMERA_RELATIVE_HEADING_AND_PITCH(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<447, void>(p0, p1); }
	FORCEINLINE void SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING(float yaw) { return YimMenu::NativeInvoker::Invoke<448, void>(yaw); }
	FORCEINLINE void SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH(float pitch) { return YimMenu::NativeInvoker::Invoke<449, void>(pitch); }
	FORCEINLINE void SET_SCRIPTED_CAMERA_IS_FIRST_PERSON_THIS_FRAME(bool p0) { return YimMenu::NativeInvoker::Invoke<450, void>(p0); }
	FORCEINLINE void SHAKE_GAMEPLAY_CAM(const char* shakeName, float intensity) { return YimMenu::NativeInvoker::Invoke<451, void>(shakeName, intensity); }
	FORCEINLINE bool IS_GAMEPLAY_CAM_SHAKING() { return YimMenu::NativeInvoker::Invoke<452, bool>(); }
	FORCEINLINE void SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(float amplitude) { return YimMenu::NativeInvoker::Invoke<453, void>(amplitude); }
	FORCEINLINE void STOP_GAMEPLAY_CAM_SHAKING(bool p0) { return YimMenu::NativeInvoker::Invoke<454, void>(p0); }
	FORCEINLINE void SET_GAMEPLAY_CAM_FOLLOW_PED_THIS_UPDATE(Ped ped) { return YimMenu::NativeInvoker::Invoke<455, void>(ped); }
	FORCEINLINE bool IS_GAMEPLAY_CAM_RENDERING() { return YimMenu::NativeInvoker::Invoke<456, bool>(); }
	FORCEINLINE bool IS_INTERPOLATING_FROM_SCRIPT_CAMS() { return YimMenu::NativeInvoker::Invoke<457, bool>(); }
	FORCEINLINE bool IS_INTERPOLATING_TO_SCRIPT_CAMS() { return YimMenu::NativeInvoker::Invoke<458, bool>(); }
	FORCEINLINE void SET_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_STATE(bool p0) { return YimMenu::NativeInvoker::Invoke<459, void>(p0); }
	FORCEINLINE void DISABLE_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<460, void>(); }
	FORCEINLINE bool IS_GAMEPLAY_CAM_LOOKING_BEHIND() { return YimMenu::NativeInvoker::Invoke<461, bool>(); }
	FORCEINLINE void SET_GAMEPLAY_CAM_IGNORE_ENTITY_COLLISION_THIS_UPDATE(Entity entity) { return YimMenu::NativeInvoker::Invoke<462, void>(entity); }
	FORCEINLINE void DISABLE_CAM_COLLISION_FOR_OBJECT(Entity entity) { return YimMenu::NativeInvoker::Invoke<463, void>(entity); }
	FORCEINLINE void BYPASS_CAMERA_COLLISION_BUOYANCY_TEST_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<464, void>(); }
	FORCEINLINE void SET_GAMEPLAY_CAM_ENTITY_TO_LIMIT_FOCUS_OVER_BOUNDING_SPHERE_THIS_UPDATE(Entity entity) { return YimMenu::NativeInvoker::Invoke<465, void>(entity); }
	FORCEINLINE void DISABLE_FIRST_PERSON_CAMERA_WATER_CLIPPING_TEST_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<466, void>(); }
	FORCEINLINE void SET_FOLLOW_CAM_IGNORE_ATTACH_PARENT_MOVEMENT_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<467, void>(); }
	FORCEINLINE bool IS_SPHERE_VISIBLE(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<468, bool>(x, y, z, radius); }
	FORCEINLINE bool IS_FOLLOW_PED_CAM_ACTIVE() { return YimMenu::NativeInvoker::Invoke<469, bool>(); }
	FORCEINLINE bool SET_FOLLOW_PED_CAM_THIS_UPDATE(const char* camName, int p1) { return YimMenu::NativeInvoker::Invoke<470, bool>(camName, p1); }
	FORCEINLINE void USE_SCRIPT_CAM_FOR_AMBIENT_POPULATION_ORIGIN_THIS_FRAME(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<471, void>(p0, p1); }
	FORCEINLINE void SET_FOLLOW_PED_CAM_LADDER_ALIGN_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<472, void>(); }
	FORCEINLINE void SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(float minimum, float maximum) { return YimMenu::NativeInvoker::Invoke<473, void>(minimum, maximum); }
	FORCEINLINE void SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(float minimum, float maximum) { return YimMenu::NativeInvoker::Invoke<474, void>(minimum, maximum); }
	FORCEINLINE void SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(float p0, float distance) { return YimMenu::NativeInvoker::Invoke<475, void>(p0, distance); }
	FORCEINLINE void SET_IN_VEHICLE_CAM_STATE_THIS_UPDATE(Vehicle p0, int p1) { return YimMenu::NativeInvoker::Invoke<476, void>(p0, p1); }
	FORCEINLINE void DISABLE_ON_FOOT_FIRST_PERSON_VIEW_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<477, void>(); }
	FORCEINLINE void DISABLE_FIRST_PERSON_FLASH_EFFECT_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<478, void>(); }
	FORCEINLINE void BLOCK_FIRST_PERSON_ORIENTATION_RESET_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<479, void>(); }
	FORCEINLINE int GET_FOLLOW_PED_CAM_ZOOM_LEVEL() { return YimMenu::NativeInvoker::Invoke<480, int>(); }
	FORCEINLINE int GET_FOLLOW_PED_CAM_VIEW_MODE() { return YimMenu::NativeInvoker::Invoke<481, int>(); }
	FORCEINLINE void SET_FOLLOW_PED_CAM_VIEW_MODE(int viewMode) { return YimMenu::NativeInvoker::Invoke<482, void>(viewMode); }
	FORCEINLINE bool IS_FOLLOW_VEHICLE_CAM_ACTIVE() { return YimMenu::NativeInvoker::Invoke<483, bool>(); }
	FORCEINLINE void SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_THIS_UPDATE(bool p0) { return YimMenu::NativeInvoker::Invoke<484, void>(p0); }
	FORCEINLINE void SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_EVERY_UPDATE(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<485, void>(p0, p1); }
	FORCEINLINE bool SET_TABLE_GAMES_CAMERA_THIS_UPDATE(Hash hash) { return YimMenu::NativeInvoker::Invoke<486, bool>(hash); }
	FORCEINLINE int GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL() { return YimMenu::NativeInvoker::Invoke<487, int>(); }
	FORCEINLINE void SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(int zoomLevel) { return YimMenu::NativeInvoker::Invoke<488, void>(zoomLevel); }
	FORCEINLINE int GET_FOLLOW_VEHICLE_CAM_VIEW_MODE() { return YimMenu::NativeInvoker::Invoke<489, int>(); }
	FORCEINLINE void SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(int viewMode) { return YimMenu::NativeInvoker::Invoke<490, void>(viewMode); }
	FORCEINLINE int GET_CAM_VIEW_MODE_FOR_CONTEXT(int context) { return YimMenu::NativeInvoker::Invoke<491, int>(context); }
	FORCEINLINE void SET_CAM_VIEW_MODE_FOR_CONTEXT(int context, int viewMode) { return YimMenu::NativeInvoker::Invoke<492, void>(context, viewMode); }
	FORCEINLINE int GET_CAM_ACTIVE_VIEW_MODE_CONTEXT() { return YimMenu::NativeInvoker::Invoke<493, int>(); }
	FORCEINLINE void USE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<494, void>(); }
	FORCEINLINE void USE_DEDICATED_STUNT_CAMERA_THIS_UPDATE(const char* camName) { return YimMenu::NativeInvoker::Invoke<495, void>(camName); }
	FORCEINLINE void FORCE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<496, void>(); }
	FORCEINLINE void SET_FOLLOW_VEHICLE_CAM_SEAT_THIS_UPDATE(int seatIndex) { return YimMenu::NativeInvoker::Invoke<497, void>(seatIndex); }
	FORCEINLINE bool IS_AIM_CAM_ACTIVE() { return YimMenu::NativeInvoker::Invoke<498, bool>(); }
	FORCEINLINE bool IS_AIM_CAM_ACTIVE_IN_ACCURATE_MODE() { return YimMenu::NativeInvoker::Invoke<499, bool>(); }
	FORCEINLINE bool IS_FIRST_PERSON_AIM_CAM_ACTIVE() { return YimMenu::NativeInvoker::Invoke<500, bool>(); }
	FORCEINLINE void DISABLE_AIM_CAM_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<501, void>(); }
	FORCEINLINE float GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR() { return YimMenu::NativeInvoker::Invoke<502, float>(); }
	FORCEINLINE void SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR(float zoomFactor) { return YimMenu::NativeInvoker::Invoke<503, void>(zoomFactor); }
	FORCEINLINE void SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR_LIMITS_THIS_UPDATE(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<504, void>(p0, p1); }
	FORCEINLINE void SET_FIRST_PERSON_AIM_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<505, void>(p0, p1); }
	FORCEINLINE void SET_FIRST_PERSON_AIM_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<506, void>(p0, p1); }
	FORCEINLINE void SET_FIRST_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(float p0) { return YimMenu::NativeInvoker::Invoke<507, void>(p0); }
	FORCEINLINE void SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(float p0) { return YimMenu::NativeInvoker::Invoke<508, void>(p0); }
	FORCEINLINE void SET_ALLOW_CUSTOM_VEHICLE_DRIVE_BY_CAM_THIS_UPDATE(bool p0) { return YimMenu::NativeInvoker::Invoke<509, void>(p0); }
	FORCEINLINE void FORCE_TIGHTSPACE_CUSTOM_FRAMING_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<510, void>(); }
	FORCEINLINE Vector3 GET_FINAL_RENDERED_CAM_COORD() { return YimMenu::NativeInvoker::Invoke<511, Vector3>(); }
	FORCEINLINE Vector3 GET_FINAL_RENDERED_CAM_ROT(int rotationOrder) { return YimMenu::NativeInvoker::Invoke<512, Vector3>(rotationOrder); }
	FORCEINLINE Vector3 GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_ROT(Player player, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<513, Vector3>(player, rotationOrder); }
	FORCEINLINE float GET_FINAL_RENDERED_CAM_FOV() { return YimMenu::NativeInvoker::Invoke<514, float>(); }
	FORCEINLINE float GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_FOV(Player player) { return YimMenu::NativeInvoker::Invoke<515, float>(player); }
	FORCEINLINE float GET_FINAL_RENDERED_CAM_NEAR_CLIP() { return YimMenu::NativeInvoker::Invoke<516, float>(); }
	FORCEINLINE float GET_FINAL_RENDERED_CAM_FAR_CLIP() { return YimMenu::NativeInvoker::Invoke<517, float>(); }
	FORCEINLINE float GET_FINAL_RENDERED_CAM_NEAR_DOF() { return YimMenu::NativeInvoker::Invoke<518, float>(); }
	FORCEINLINE float GET_FINAL_RENDERED_CAM_FAR_DOF() { return YimMenu::NativeInvoker::Invoke<519, float>(); }
	FORCEINLINE float GET_FINAL_RENDERED_CAM_MOTION_BLUR_STRENGTH() { return YimMenu::NativeInvoker::Invoke<520, float>(); }
	FORCEINLINE void SET_GAMEPLAY_COORD_HINT(float x, float y, float z, int duration, int blendOutDuration, int blendInDuration, int p6) { return YimMenu::NativeInvoker::Invoke<521, void>(x, y, z, duration, blendOutDuration, blendInDuration, p6); }
	FORCEINLINE void SET_GAMEPLAY_PED_HINT(Ped ped, float x1, float y1, float z1, bool p4, int duration, int blendOutDuration, int blendInDuration) { return YimMenu::NativeInvoker::Invoke<522, void>(ped, x1, y1, z1, p4, duration, blendOutDuration, blendInDuration); }
	FORCEINLINE void SET_GAMEPLAY_VEHICLE_HINT(Vehicle vehicle, float offsetX, float offsetY, float offsetZ, bool p4, int time, int easeInTime, int easeOutTime) { return YimMenu::NativeInvoker::Invoke<523, void>(vehicle, offsetX, offsetY, offsetZ, p4, time, easeInTime, easeOutTime); }
	FORCEINLINE void SET_GAMEPLAY_OBJECT_HINT(Object object, float xOffset, float yOffset, float zOffset, bool p4, int time, int easeInTime, int easeOutTime) { return YimMenu::NativeInvoker::Invoke<524, void>(object, xOffset, yOffset, zOffset, p4, time, easeInTime, easeOutTime); }
	FORCEINLINE void SET_GAMEPLAY_ENTITY_HINT(Entity entity, float xOffset, float yOffset, float zOffset, bool p4, int time, int easeInTime, int easeOutTime, int p8) { return YimMenu::NativeInvoker::Invoke<525, void>(entity, xOffset, yOffset, zOffset, p4, time, easeInTime, easeOutTime, p8); }
	FORCEINLINE bool IS_GAMEPLAY_HINT_ACTIVE() { return YimMenu::NativeInvoker::Invoke<526, bool>(); }
	FORCEINLINE void STOP_GAMEPLAY_HINT(bool p0) { return YimMenu::NativeInvoker::Invoke<527, void>(p0); }
	FORCEINLINE void STOP_GAMEPLAY_HINT_BEING_CANCELLED_THIS_UPDATE(bool p0) { return YimMenu::NativeInvoker::Invoke<528, void>(p0); }
	FORCEINLINE void STOP_CODE_GAMEPLAY_HINT(bool p0) { return YimMenu::NativeInvoker::Invoke<529, void>(p0); }
	FORCEINLINE bool IS_CODE_GAMEPLAY_HINT_ACTIVE() { return YimMenu::NativeInvoker::Invoke<530, bool>(); }
	FORCEINLINE void SET_GAMEPLAY_HINT_FOV(float FOV) { return YimMenu::NativeInvoker::Invoke<531, void>(FOV); }
	FORCEINLINE void SET_GAMEPLAY_HINT_FOLLOW_DISTANCE_SCALAR(float value) { return YimMenu::NativeInvoker::Invoke<532, void>(value); }
	FORCEINLINE void SET_GAMEPLAY_HINT_BASE_ORBIT_PITCH_OFFSET(float value) { return YimMenu::NativeInvoker::Invoke<533, void>(value); }
	FORCEINLINE void SET_GAMEPLAY_HINT_CAMERA_RELATIVE_SIDE_OFFSET(float xOffset) { return YimMenu::NativeInvoker::Invoke<534, void>(xOffset); }
	FORCEINLINE void SET_GAMEPLAY_HINT_CAMERA_RELATIVE_VERTICAL_OFFSET(float yOffset) { return YimMenu::NativeInvoker::Invoke<535, void>(yOffset); }
	FORCEINLINE void SET_GAMEPLAY_HINT_CAMERA_BLEND_TO_FOLLOW_PED_MEDIUM_VIEW_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<536, void>(toggle); }
	FORCEINLINE void SET_CINEMATIC_BUTTON_ACTIVE(bool p0) { return YimMenu::NativeInvoker::Invoke<537, void>(p0); }
	FORCEINLINE bool IS_CINEMATIC_CAM_RENDERING() { return YimMenu::NativeInvoker::Invoke<538, bool>(); }
	FORCEINLINE void SHAKE_CINEMATIC_CAM(const char* shakeType, float amount) { return YimMenu::NativeInvoker::Invoke<539, void>(shakeType, amount); }
	FORCEINLINE bool IS_CINEMATIC_CAM_SHAKING() { return YimMenu::NativeInvoker::Invoke<540, bool>(); }
	FORCEINLINE void SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(float p0) { return YimMenu::NativeInvoker::Invoke<541, void>(p0); }
	FORCEINLINE void STOP_CINEMATIC_CAM_SHAKING(bool p0) { return YimMenu::NativeInvoker::Invoke<542, void>(p0); }
	FORCEINLINE void DISABLE_CINEMATIC_BONNET_CAMERA_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<543, void>(); }
	FORCEINLINE void DISABLE_CINEMATIC_VEHICLE_IDLE_MODE_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<544, void>(); }
	FORCEINLINE void INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE() { return YimMenu::NativeInvoker::Invoke<545, void>(); }
	FORCEINLINE void INVALIDATE_IDLE_CAM() { return YimMenu::NativeInvoker::Invoke<546, void>(); }
	FORCEINLINE bool IS_CINEMATIC_IDLE_CAM_RENDERING() { return YimMenu::NativeInvoker::Invoke<547, bool>(); }
	FORCEINLINE bool IS_CINEMATIC_FIRST_PERSON_VEHICLE_INTERIOR_CAM_RENDERING() { return YimMenu::NativeInvoker::Invoke<548, bool>(); }
	FORCEINLINE void CREATE_CINEMATIC_SHOT(Hash p0, int time, bool p2, Entity entity) { return YimMenu::NativeInvoker::Invoke<549, void>(p0, time, p2, entity); }
	FORCEINLINE bool IS_CINEMATIC_SHOT_ACTIVE(Hash p0) { return YimMenu::NativeInvoker::Invoke<550, bool>(p0); }
	FORCEINLINE void STOP_CINEMATIC_SHOT(Hash p0) { return YimMenu::NativeInvoker::Invoke<551, void>(p0); }
	FORCEINLINE void FORCE_CINEMATIC_RENDERING_THIS_UPDATE(bool toggle) { return YimMenu::NativeInvoker::Invoke<552, void>(toggle); }
	FORCEINLINE void SET_CINEMATIC_NEWS_CHANNEL_ACTIVE_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<553, void>(); }
	FORCEINLINE void SET_CINEMATIC_MODE_ACTIVE(bool toggle) { return YimMenu::NativeInvoker::Invoke<554, void>(toggle); }
	FORCEINLINE bool IS_IN_VEHICLE_MOBILE_PHONE_CAMERA_RENDERING() { return YimMenu::NativeInvoker::Invoke<555, bool>(); }
	FORCEINLINE bool DISABLE_CINEMATIC_SLOW_MO_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<556, bool>(); }
	FORCEINLINE bool IS_BONNET_CINEMATIC_CAM_RENDERING() { return YimMenu::NativeInvoker::Invoke<557, bool>(); }
	FORCEINLINE bool IS_CINEMATIC_CAM_INPUT_ACTIVE() { return YimMenu::NativeInvoker::Invoke<558, bool>(); }
	FORCEINLINE void IGNORE_MENU_PREFERENCE_FOR_BONNET_CAMERA_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<559, void>(); }
	FORCEINLINE void BYPASS_CUTSCENE_CAM_RENDERING_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<560, void>(); }
	FORCEINLINE void STOP_CUTSCENE_CAM_SHAKING(Any p0) { return YimMenu::NativeInvoker::Invoke<561, void>(p0); }
	FORCEINLINE void SET_CUTSCENE_CAM_FAR_CLIP_THIS_UPDATE(float p0) { return YimMenu::NativeInvoker::Invoke<562, void>(p0); }
	FORCEINLINE Ped GET_FOCUS_PED_ON_SCREEN(float p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, int p8) { return YimMenu::NativeInvoker::Invoke<563, Ped>(p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void DISABLE_NEAR_CLIP_SCAN_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<564, void>(); }
	FORCEINLINE void SET_CAM_DEATH_FAIL_EFFECT_STATE(int p0) { return YimMenu::NativeInvoker::Invoke<565, void>(p0); }
	FORCEINLINE void SET_FIRST_PERSON_FLASH_EFFECT_TYPE(Any p0) { return YimMenu::NativeInvoker::Invoke<566, void>(p0); }
	FORCEINLINE void SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_NAME(const char* vehicleName) { return YimMenu::NativeInvoker::Invoke<567, void>(vehicleName); }
	FORCEINLINE void SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_HASH(Hash vehicleModel) { return YimMenu::NativeInvoker::Invoke<568, void>(vehicleModel); }
	FORCEINLINE bool IS_ALLOWED_INDEPENDENT_CAMERA_MODES() { return YimMenu::NativeInvoker::Invoke<569, bool>(); }
	FORCEINLINE void CAMERA_PREVENT_COLLISION_SETTINGS_FOR_TRIPLEHEAD_IN_INTERIORS_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<570, void>(); }
	FORCEINLINE float REPLAY_GET_MAX_DISTANCE_ALLOWED_FROM_PLAYER() { return YimMenu::NativeInvoker::Invoke<571, float>(); }
}

namespace CLOCK
{
	FORCEINLINE void SET_CLOCK_TIME(int hour, int minute, int second) { return YimMenu::NativeInvoker::Invoke<572, void>(hour, minute, second); }
	FORCEINLINE void PAUSE_CLOCK(bool toggle) { return YimMenu::NativeInvoker::Invoke<573, void>(toggle); }
	FORCEINLINE void ADVANCE_CLOCK_TIME_TO(int hour, int minute, int second) { return YimMenu::NativeInvoker::Invoke<574, void>(hour, minute, second); }
	FORCEINLINE void ADD_TO_CLOCK_TIME(int hours, int minutes, int seconds) { return YimMenu::NativeInvoker::Invoke<575, void>(hours, minutes, seconds); }
	FORCEINLINE int GET_CLOCK_HOURS() { return YimMenu::NativeInvoker::Invoke<576, int>(); }
	FORCEINLINE int GET_CLOCK_MINUTES() { return YimMenu::NativeInvoker::Invoke<577, int>(); }
	FORCEINLINE int GET_CLOCK_SECONDS() { return YimMenu::NativeInvoker::Invoke<578, int>(); }
	FORCEINLINE void SET_CLOCK_DATE(int day, int month, int year) { return YimMenu::NativeInvoker::Invoke<579, void>(day, month, year); }
	FORCEINLINE int GET_CLOCK_DAY_OF_WEEK() { return YimMenu::NativeInvoker::Invoke<580, int>(); }
	FORCEINLINE int GET_CLOCK_DAY_OF_MONTH() { return YimMenu::NativeInvoker::Invoke<581, int>(); }
	FORCEINLINE int GET_CLOCK_MONTH() { return YimMenu::NativeInvoker::Invoke<582, int>(); }
	FORCEINLINE int GET_CLOCK_YEAR() { return YimMenu::NativeInvoker::Invoke<583, int>(); }
	FORCEINLINE int GET_MILLISECONDS_PER_GAME_MINUTE() { return YimMenu::NativeInvoker::Invoke<584, int>(); }
	FORCEINLINE void GET_POSIX_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second) { return YimMenu::NativeInvoker::Invoke<585, void>(year, month, day, hour, minute, second); }
	FORCEINLINE void GET_UTC_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second) { return YimMenu::NativeInvoker::Invoke<586, void>(year, month, day, hour, minute, second); }
	FORCEINLINE void GET_LOCAL_TIME(int* year, int* month, int* day, int* hour, int* minute, int* second) { return YimMenu::NativeInvoker::Invoke<587, void>(year, month, day, hour, minute, second); }
}

namespace CUTSCENE
{
	FORCEINLINE void REQUEST_CUTSCENE(const char* cutsceneName, int flags) { return YimMenu::NativeInvoker::Invoke<588, void>(cutsceneName, flags); }
	FORCEINLINE void REQUEST_CUTSCENE_WITH_PLAYBACK_LIST(const char* cutsceneName, int playbackFlags, int flags) { return YimMenu::NativeInvoker::Invoke<589, void>(cutsceneName, playbackFlags, flags); }
	FORCEINLINE void REMOVE_CUTSCENE() { return YimMenu::NativeInvoker::Invoke<590, void>(); }
	FORCEINLINE bool HAS_CUTSCENE_LOADED() { return YimMenu::NativeInvoker::Invoke<591, bool>(); }
	FORCEINLINE bool HAS_THIS_CUTSCENE_LOADED(const char* cutsceneName) { return YimMenu::NativeInvoker::Invoke<592, bool>(cutsceneName); }
	FORCEINLINE void SET_SCRIPT_CAN_START_CUTSCENE(int threadId) { return YimMenu::NativeInvoker::Invoke<593, void>(threadId); }
	FORCEINLINE bool CAN_REQUEST_ASSETS_FOR_CUTSCENE_ENTITY() { return YimMenu::NativeInvoker::Invoke<594, bool>(); }
	FORCEINLINE bool IS_CUTSCENE_PLAYBACK_FLAG_SET(int flag) { return YimMenu::NativeInvoker::Invoke<595, bool>(flag); }
	FORCEINLINE void SET_CUTSCENE_ENTITY_STREAMING_FLAGS(const char* cutsceneEntName, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<596, void>(cutsceneEntName, p1, p2); }
	FORCEINLINE void REQUEST_CUT_FILE(const char* cutsceneName) { return YimMenu::NativeInvoker::Invoke<597, void>(cutsceneName); }
	FORCEINLINE bool HAS_CUT_FILE_LOADED(const char* cutsceneName) { return YimMenu::NativeInvoker::Invoke<598, bool>(cutsceneName); }
	FORCEINLINE void REMOVE_CUT_FILE(const char* cutsceneName) { return YimMenu::NativeInvoker::Invoke<599, void>(cutsceneName); }
	FORCEINLINE int GET_CUT_FILE_CONCAT_COUNT(const char* cutsceneName) { return YimMenu::NativeInvoker::Invoke<600, int>(cutsceneName); }
	FORCEINLINE void START_CUTSCENE(int flags) { return YimMenu::NativeInvoker::Invoke<601, void>(flags); }
	FORCEINLINE void START_CUTSCENE_AT_COORDS(float x, float y, float z, int flags) { return YimMenu::NativeInvoker::Invoke<602, void>(x, y, z, flags); }
	FORCEINLINE void STOP_CUTSCENE(bool p0) { return YimMenu::NativeInvoker::Invoke<603, void>(p0); }
	FORCEINLINE void STOP_CUTSCENE_IMMEDIATELY() { return YimMenu::NativeInvoker::Invoke<604, void>(); }
	FORCEINLINE void SET_CUTSCENE_ORIGIN(float x, float y, float z, float p3, int p4) { return YimMenu::NativeInvoker::Invoke<605, void>(x, y, z, p3, p4); }
	FORCEINLINE void SET_CUTSCENE_ORIGIN_AND_ORIENTATION(float x1, float y1, float z1, float x2, float y2, float z2, int p6) { return YimMenu::NativeInvoker::Invoke<606, void>(x1, y1, z1, x2, y2, z2, p6); }
	FORCEINLINE int GET_CUTSCENE_TIME() { return YimMenu::NativeInvoker::Invoke<607, int>(); }
	FORCEINLINE int GET_CUTSCENE_TOTAL_DURATION() { return YimMenu::NativeInvoker::Invoke<608, int>(); }
	FORCEINLINE int GET_CUTSCENE_END_TIME() { return YimMenu::NativeInvoker::Invoke<609, int>(); }
	FORCEINLINE int GET_CUTSCENE_PLAY_DURATION() { return YimMenu::NativeInvoker::Invoke<610, int>(); }
	FORCEINLINE bool WAS_CUTSCENE_SKIPPED() { return YimMenu::NativeInvoker::Invoke<611, bool>(); }
	FORCEINLINE bool HAS_CUTSCENE_FINISHED() { return YimMenu::NativeInvoker::Invoke<612, bool>(); }
	FORCEINLINE bool IS_CUTSCENE_ACTIVE() { return YimMenu::NativeInvoker::Invoke<613, bool>(); }
	FORCEINLINE bool IS_CUTSCENE_PLAYING() { return YimMenu::NativeInvoker::Invoke<614, bool>(); }
	FORCEINLINE int GET_CUTSCENE_SECTION_PLAYING() { return YimMenu::NativeInvoker::Invoke<615, int>(); }
	FORCEINLINE Entity GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY(const char* cutsceneEntName, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<616, Entity>(cutsceneEntName, modelHash); }
	FORCEINLINE int GET_CUTSCENE_CONCAT_SECTION_PLAYING() { return YimMenu::NativeInvoker::Invoke<617, int>(); }
	FORCEINLINE bool IS_CUTSCENE_AUTHORIZED(const char* cutsceneName) { return YimMenu::NativeInvoker::Invoke<618, bool>(cutsceneName); }
	FORCEINLINE int DOES_CUTSCENE_HANDLE_EXIST(int cutsceneHandle) { return YimMenu::NativeInvoker::Invoke<619, int>(cutsceneHandle); }
	FORCEINLINE void REGISTER_ENTITY_FOR_CUTSCENE(Ped cutscenePed, const char* cutsceneEntName, int p2, Hash modelHash, int p4) { return YimMenu::NativeInvoker::Invoke<620, void>(cutscenePed, cutsceneEntName, p2, modelHash, p4); }
	FORCEINLINE Entity GET_ENTITY_INDEX_OF_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<621, Entity>(cutsceneEntName, modelHash); }
	FORCEINLINE void SET_VEHICLE_MODEL_PLAYER_WILL_EXIT_SCENE(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<622, void>(modelHash); }
	FORCEINLINE void SET_CUTSCENE_TRIGGER_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<623, void>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE bool CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<624, bool>(cutsceneEntName, modelHash); }
	FORCEINLINE bool CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY(const char* cutsceneEntName, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<625, bool>(cutsceneEntName, modelHash); }
	FORCEINLINE bool CAN_SET_EXIT_STATE_FOR_CAMERA(bool p0) { return YimMenu::NativeInvoker::Invoke<626, bool>(p0); }
	FORCEINLINE void SET_PAD_CAN_SHAKE_DURING_CUTSCENE(bool toggle) { return YimMenu::NativeInvoker::Invoke<627, void>(toggle); }
	FORCEINLINE void SET_CUTSCENE_FADE_VALUES(bool p0, bool p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<628, void>(p0, p1, p2, p3); }
	FORCEINLINE void SET_CUTSCENE_MULTIHEAD_FADE(bool p0, bool p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<629, void>(p0, p1, p2, p3); }
	FORCEINLINE void SET_CUTSCENE_MULTIHEAD_FADE_MANUAL(bool p0) { return YimMenu::NativeInvoker::Invoke<630, void>(p0); }
	FORCEINLINE bool IS_MULTIHEAD_FADE_UP() { return YimMenu::NativeInvoker::Invoke<631, bool>(); }
	FORCEINLINE void NETWORK_SET_MOCAP_CUTSCENE_CAN_BE_SKIPPED(bool p0) { return YimMenu::NativeInvoker::Invoke<632, void>(p0); }
	FORCEINLINE void SET_CAR_GENERATORS_CAN_UPDATE_DURING_CUTSCENE(bool p0) { return YimMenu::NativeInvoker::Invoke<633, void>(p0); }
	FORCEINLINE bool CAN_USE_MOBILE_PHONE_DURING_CUTSCENE() { return YimMenu::NativeInvoker::Invoke<634, bool>(); }
	FORCEINLINE void SET_CUTSCENE_CAN_BE_SKIPPED(bool p0) { return YimMenu::NativeInvoker::Invoke<635, void>(p0); }
	FORCEINLINE void SET_CAN_DISPLAY_MINIMAP_DURING_CUTSCENE_THIS_UPDATE() { return YimMenu::NativeInvoker::Invoke<636, void>(); }
	FORCEINLINE void SET_CUTSCENE_PED_COMPONENT_VARIATION(const char* cutsceneEntName, int componentId, int drawableId, int textureId, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<637, void>(cutsceneEntName, componentId, drawableId, textureId, modelHash); }
	FORCEINLINE void SET_CUTSCENE_PED_COMPONENT_VARIATION_FROM_PED(const char* cutsceneEntName, Ped ped, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<638, void>(cutsceneEntName, ped, modelHash); }
	FORCEINLINE bool DOES_CUTSCENE_ENTITY_EXIST(const char* cutsceneEntName, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<639, bool>(cutsceneEntName, modelHash); }
	FORCEINLINE void SET_CUTSCENE_PED_PROP_VARIATION(const char* cutsceneEntName, int componentId, int drawableId, int textureId, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<640, void>(cutsceneEntName, componentId, drawableId, textureId, modelHash); }
	FORCEINLINE bool HAS_CUTSCENE_CUT_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<641, bool>(); }
}

namespace DATAFILE
{
	FORCEINLINE void DATAFILE_WATCH_REQUEST_ID(int requestId) { return YimMenu::NativeInvoker::Invoke<642, void>(requestId); }
	FORCEINLINE void DATAFILE_CLEAR_WATCH_LIST() { return YimMenu::NativeInvoker::Invoke<643, void>(); }
	FORCEINLINE bool DATAFILE_IS_VALID_REQUEST_ID(int index) { return YimMenu::NativeInvoker::Invoke<644, bool>(index); }
	FORCEINLINE bool DATAFILE_HAS_LOADED_FILE_DATA(int requestId) { return YimMenu::NativeInvoker::Invoke<645, bool>(requestId); }
	FORCEINLINE bool DATAFILE_HAS_VALID_FILE_DATA(int requestId) { return YimMenu::NativeInvoker::Invoke<646, bool>(requestId); }
	FORCEINLINE bool DATAFILE_SELECT_ACTIVE_FILE(int requestId, Any p1) { return YimMenu::NativeInvoker::Invoke<647, bool>(requestId, p1); }
	FORCEINLINE bool DATAFILE_DELETE_REQUESTED_FILE(int requestId) { return YimMenu::NativeInvoker::Invoke<648, bool>(requestId); }
	FORCEINLINE bool UGC_CREATE_CONTENT(Any* data, int dataCount, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, bool publish, Any p7) { return YimMenu::NativeInvoker::Invoke<649, bool>(data, dataCount, contentName, description, tagsCsv, contentTypeName, publish, p7); }
	FORCEINLINE bool UGC_CREATE_MISSION(const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, bool publish, Any p5) { return YimMenu::NativeInvoker::Invoke<650, bool>(contentName, description, tagsCsv, contentTypeName, publish, p5); }
	FORCEINLINE bool UGC_UPDATE_CONTENT(const char* contentId, Any* data, int dataCount, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, Any p7) { return YimMenu::NativeInvoker::Invoke<651, bool>(contentId, data, dataCount, contentName, description, tagsCsv, contentTypeName, p7); }
	FORCEINLINE bool UGC_UPDATE_MISSION(const char* contentId, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, Any p5) { return YimMenu::NativeInvoker::Invoke<652, bool>(contentId, contentName, description, tagsCsv, contentTypeName, p5); }
	FORCEINLINE bool UGC_SET_PLAYER_DATA(const char* contentId, float rating, const char* contentTypeName, Any p3) { return YimMenu::NativeInvoker::Invoke<653, bool>(contentId, rating, contentTypeName, p3); }
	FORCEINLINE bool DATAFILE_SELECT_UGC_DATA(int p0, Any p1) { return YimMenu::NativeInvoker::Invoke<654, bool>(p0, p1); }
	FORCEINLINE bool DATAFILE_SELECT_UGC_STATS(int p0, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<655, bool>(p0, p1, p2); }
	FORCEINLINE bool DATAFILE_SELECT_UGC_PLAYER_DATA(int p0, Any p1) { return YimMenu::NativeInvoker::Invoke<656, bool>(p0, p1); }
	FORCEINLINE bool DATAFILE_SELECT_CREATOR_STATS(int p0, Any p1) { return YimMenu::NativeInvoker::Invoke<657, bool>(p0, p1); }
	FORCEINLINE bool DATAFILE_LOAD_OFFLINE_UGC(const char* filename, Any p1) { return YimMenu::NativeInvoker::Invoke<658, bool>(filename, p1); }
	FORCEINLINE void DATAFILE_CREATE(int p0) { return YimMenu::NativeInvoker::Invoke<659, void>(p0); }
	FORCEINLINE void DATAFILE_DELETE(int p0) { return YimMenu::NativeInvoker::Invoke<660, void>(p0); }
	FORCEINLINE void DATAFILE_STORE_MISSION_HEADER(int p0) { return YimMenu::NativeInvoker::Invoke<661, void>(p0); }
	FORCEINLINE void DATAFILE_FLUSH_MISSION_HEADER() { return YimMenu::NativeInvoker::Invoke<662, void>(); }
	FORCEINLINE Any* DATAFILE_GET_FILE_DICT(int p0) { return YimMenu::NativeInvoker::Invoke<663, Any*>(p0); }
	FORCEINLINE bool DATAFILE_START_SAVE_TO_CLOUD(const char* filename, Any p1) { return YimMenu::NativeInvoker::Invoke<664, bool>(filename, p1); }
	FORCEINLINE bool DATAFILE_UPDATE_SAVE_TO_CLOUD(bool* p0) { return YimMenu::NativeInvoker::Invoke<665, bool>(p0); }
	FORCEINLINE bool DATAFILE_IS_SAVE_PENDING() { return YimMenu::NativeInvoker::Invoke<666, bool>(); }
	FORCEINLINE bool DATAFILE_LOAD_OFFLINE_UGC_FOR_ADDITIONAL_DATA_FILE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<667, bool>(p0, p1); }
	FORCEINLINE void DATAFILE_DELETE_FOR_ADDITIONAL_DATA_FILE(Any p0) { return YimMenu::NativeInvoker::Invoke<668, void>(p0); }
	FORCEINLINE Any* DATAFILE_GET_FILE_DICT_FOR_ADDITIONAL_DATA_FILE(Any p0) { return YimMenu::NativeInvoker::Invoke<669, Any*>(p0); }
	FORCEINLINE void DATADICT_SET_BOOL(Any* objectData, const char* key, bool value) { return YimMenu::NativeInvoker::Invoke<670, void>(objectData, key, value); }
	FORCEINLINE void DATADICT_SET_INT(Any* objectData, const char* key, int value) { return YimMenu::NativeInvoker::Invoke<671, void>(objectData, key, value); }
	FORCEINLINE void DATADICT_SET_FLOAT(Any* objectData, const char* key, float value) { return YimMenu::NativeInvoker::Invoke<672, void>(objectData, key, value); }
	FORCEINLINE void DATADICT_SET_STRING(Any* objectData, const char* key, const char* value) { return YimMenu::NativeInvoker::Invoke<673, void>(objectData, key, value); }
	FORCEINLINE void DATADICT_SET_VECTOR(Any* objectData, const char* key, float valueX, float valueY, float valueZ) { return YimMenu::NativeInvoker::Invoke<674, void>(objectData, key, valueX, valueY, valueZ); }
	FORCEINLINE Any* DATADICT_CREATE_DICT(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<675, Any*>(objectData, key); }
	FORCEINLINE Any* DATADICT_CREATE_ARRAY(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<676, Any*>(objectData, key); }
	FORCEINLINE bool DATADICT_GET_BOOL(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<677, bool>(objectData, key); }
	FORCEINLINE int DATADICT_GET_INT(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<678, int>(objectData, key); }
	FORCEINLINE float DATADICT_GET_FLOAT(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<679, float>(objectData, key); }
	FORCEINLINE const char* DATADICT_GET_STRING(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<680, const char*>(objectData, key); }
	FORCEINLINE Vector3 DATADICT_GET_VECTOR(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<681, Vector3>(objectData, key); }
	FORCEINLINE Any* DATADICT_GET_DICT(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<682, Any*>(objectData, key); }
	FORCEINLINE Any* DATADICT_GET_ARRAY(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<683, Any*>(objectData, key); }
	FORCEINLINE int DATADICT_GET_TYPE(Any* objectData, const char* key) { return YimMenu::NativeInvoker::Invoke<684, int>(objectData, key); }
	FORCEINLINE void DATAARRAY_ADD_BOOL(Any* arrayData, bool value) { return YimMenu::NativeInvoker::Invoke<685, void>(arrayData, value); }
	FORCEINLINE void DATAARRAY_ADD_INT(Any* arrayData, int value) { return YimMenu::NativeInvoker::Invoke<686, void>(arrayData, value); }
	FORCEINLINE void DATAARRAY_ADD_FLOAT(Any* arrayData, float value) { return YimMenu::NativeInvoker::Invoke<687, void>(arrayData, value); }
	FORCEINLINE void DATAARRAY_ADD_STRING(Any* arrayData, const char* value) { return YimMenu::NativeInvoker::Invoke<688, void>(arrayData, value); }
	FORCEINLINE void DATAARRAY_ADD_VECTOR(Any* arrayData, float valueX, float valueY, float valueZ) { return YimMenu::NativeInvoker::Invoke<689, void>(arrayData, valueX, valueY, valueZ); }
	FORCEINLINE Any* DATAARRAY_ADD_DICT(Any* arrayData) { return YimMenu::NativeInvoker::Invoke<690, Any*>(arrayData); }
	FORCEINLINE bool DATAARRAY_GET_BOOL(Any* arrayData, int arrayIndex) { return YimMenu::NativeInvoker::Invoke<691, bool>(arrayData, arrayIndex); }
	FORCEINLINE int DATAARRAY_GET_INT(Any* arrayData, int arrayIndex) { return YimMenu::NativeInvoker::Invoke<692, int>(arrayData, arrayIndex); }
	FORCEINLINE float DATAARRAY_GET_FLOAT(Any* arrayData, int arrayIndex) { return YimMenu::NativeInvoker::Invoke<693, float>(arrayData, arrayIndex); }
	FORCEINLINE const char* DATAARRAY_GET_STRING(Any* arrayData, int arrayIndex) { return YimMenu::NativeInvoker::Invoke<694, const char*>(arrayData, arrayIndex); }
	FORCEINLINE Vector3 DATAARRAY_GET_VECTOR(Any* arrayData, int arrayIndex) { return YimMenu::NativeInvoker::Invoke<695, Vector3>(arrayData, arrayIndex); }
	FORCEINLINE Any* DATAARRAY_GET_DICT(Any* arrayData, int arrayIndex) { return YimMenu::NativeInvoker::Invoke<696, Any*>(arrayData, arrayIndex); }
	FORCEINLINE int DATAARRAY_GET_COUNT(Any* arrayData) { return YimMenu::NativeInvoker::Invoke<697, int>(arrayData); }
	FORCEINLINE int DATAARRAY_GET_TYPE(Any* arrayData, int arrayIndex) { return YimMenu::NativeInvoker::Invoke<698, int>(arrayData, arrayIndex); }
}

namespace DECORATOR
{
	FORCEINLINE bool DECOR_SET_TIME(Entity entity, const char* propertyName, int timestamp) { return YimMenu::NativeInvoker::Invoke<699, bool>(entity, propertyName, timestamp); }
	FORCEINLINE bool DECOR_SET_BOOL(Entity entity, const char* propertyName, bool value) { return YimMenu::NativeInvoker::Invoke<700, bool>(entity, propertyName, value); }
	FORCEINLINE bool DECOR_SET_FLOAT(Entity entity, const char* propertyName, float value) { return YimMenu::NativeInvoker::Invoke<701, bool>(entity, propertyName, value); }
	FORCEINLINE bool DECOR_SET_INT(Entity entity, const char* propertyName, int value) { return YimMenu::NativeInvoker::Invoke<702, bool>(entity, propertyName, value); }
	FORCEINLINE bool DECOR_GET_BOOL(Entity entity, const char* propertyName) { return YimMenu::NativeInvoker::Invoke<703, bool>(entity, propertyName); }
	FORCEINLINE float DECOR_GET_FLOAT(Entity entity, const char* propertyName) { return YimMenu::NativeInvoker::Invoke<704, float>(entity, propertyName); }
	FORCEINLINE int DECOR_GET_INT(Entity entity, const char* propertyName) { return YimMenu::NativeInvoker::Invoke<705, int>(entity, propertyName); }
	FORCEINLINE bool DECOR_EXIST_ON(Entity entity, const char* propertyName) { return YimMenu::NativeInvoker::Invoke<706, bool>(entity, propertyName); }
	FORCEINLINE bool DECOR_REMOVE(Entity entity, const char* propertyName) { return YimMenu::NativeInvoker::Invoke<707, bool>(entity, propertyName); }
	FORCEINLINE void DECOR_REGISTER(const char* propertyName, int type) { return YimMenu::NativeInvoker::Invoke<708, void>(propertyName, type); }
	FORCEINLINE bool DECOR_IS_REGISTERED_AS_TYPE(const char* propertyName, int type) { return YimMenu::NativeInvoker::Invoke<709, bool>(propertyName, type); }
	FORCEINLINE void DECOR_REGISTER_LOCK() { return YimMenu::NativeInvoker::Invoke<710, void>(); }
}

namespace DLC
{
	FORCEINLINE bool ARE_ANY_CCS_PENDING() { return YimMenu::NativeInvoker::Invoke<711, bool>(); }
	FORCEINLINE bool IS_DLC_PRESENT(Hash dlcHash) { return YimMenu::NativeInvoker::Invoke<712, bool>(dlcHash); }
	FORCEINLINE bool DLC_CHECK_CLOUD_DATA_CORRECT() { return YimMenu::NativeInvoker::Invoke<713, bool>(); }
	FORCEINLINE int GET_EXTRACONTENT_CLOUD_RESULT() { return YimMenu::NativeInvoker::Invoke<714, int>(); }
	FORCEINLINE bool DLC_CHECK_COMPAT_PACK_CONFIGURATION() { return YimMenu::NativeInvoker::Invoke<715, bool>(); }
	FORCEINLINE bool GET_EVER_HAD_BAD_PACK_ORDER() { return YimMenu::NativeInvoker::Invoke<716, bool>(); }
	FORCEINLINE bool GET_IS_LOADING_SCREEN_ACTIVE() { return YimMenu::NativeInvoker::Invoke<717, bool>(); }
	FORCEINLINE bool GET_IS_INITIAL_LOADING_SCREEN_ACTIVE() { return YimMenu::NativeInvoker::Invoke<718, bool>(); }
	FORCEINLINE bool HAS_CLOUD_REQUESTS_FINISHED(bool* p0, int unused) { return YimMenu::NativeInvoker::Invoke<719, bool>(p0, unused); }
	FORCEINLINE void ON_ENTER_SP() { return YimMenu::NativeInvoker::Invoke<720, void>(); }
	FORCEINLINE void ON_ENTER_MP() { return YimMenu::NativeInvoker::Invoke<721, void>(); }
}

namespace ENTITY
{
	FORCEINLINE bool DOES_ENTITY_EXIST(Entity entity) { return YimMenu::NativeInvoker::Invoke<722, bool>(entity); }
	FORCEINLINE bool DOES_ENTITY_BELONG_TO_THIS_SCRIPT(Entity entity, bool p1) { return YimMenu::NativeInvoker::Invoke<723, bool>(entity, p1); }
	FORCEINLINE bool DOES_ENTITY_HAVE_DRAWABLE(Entity entity) { return YimMenu::NativeInvoker::Invoke<724, bool>(entity); }
	FORCEINLINE bool DOES_ENTITY_HAVE_PHYSICS(Entity entity) { return YimMenu::NativeInvoker::Invoke<725, bool>(entity); }
	FORCEINLINE bool DOES_ENTITY_HAVE_SKELETON(Entity entity) { return YimMenu::NativeInvoker::Invoke<726, bool>(entity); }
	FORCEINLINE bool DOES_ENTITY_HAVE_ANIM_DIRECTOR(Entity entity) { return YimMenu::NativeInvoker::Invoke<727, bool>(entity); }
	FORCEINLINE bool HAS_ENTITY_ANIM_FINISHED(Entity entity, const char* animDict, const char* animName, int p3) { return YimMenu::NativeInvoker::Invoke<728, bool>(entity, animDict, animName, p3); }
	FORCEINLINE bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(Entity entity) { return YimMenu::NativeInvoker::Invoke<729, bool>(entity); }
	FORCEINLINE bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(Entity entity) { return YimMenu::NativeInvoker::Invoke<730, bool>(entity); }
	FORCEINLINE bool HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(Entity entity) { return YimMenu::NativeInvoker::Invoke<731, bool>(entity); }
	FORCEINLINE bool HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2, bool p2) { return YimMenu::NativeInvoker::Invoke<732, bool>(entity1, entity2, p2); }
	FORCEINLINE bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY(Entity entity1, Entity entity2, int traceType) { return YimMenu::NativeInvoker::Invoke<733, bool>(entity1, entity2, traceType); }
	FORCEINLINE bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER(Entity entity1, Entity entity2, int traceType) { return YimMenu::NativeInvoker::Invoke<734, bool>(entity1, entity2, traceType); }
	FORCEINLINE bool HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(Entity entity1, Entity entity2) { return YimMenu::NativeInvoker::Invoke<735, bool>(entity1, entity2); }
	FORCEINLINE bool HAS_ENTITY_COLLIDED_WITH_ANYTHING(Entity entity) { return YimMenu::NativeInvoker::Invoke<736, bool>(entity); }
	FORCEINLINE Entity _GET_LAST_ENTITY_HIT_BY_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<737, Entity>(entity); }
	FORCEINLINE Hash GET_LAST_MATERIAL_HIT_BY_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<738, Hash>(entity); }
	FORCEINLINE Vector3 GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<739, Vector3>(entity); }
	FORCEINLINE void FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(Entity entity) { return YimMenu::NativeInvoker::Invoke<740, void>(entity); }
	FORCEINLINE float GET_ENTITY_ANIM_CURRENT_TIME(Entity entity, const char* animDict, const char* animName) { return YimMenu::NativeInvoker::Invoke<741, float>(entity, animDict, animName); }
	FORCEINLINE float GET_ENTITY_ANIM_TOTAL_TIME(Entity entity, const char* animDict, const char* animName) { return YimMenu::NativeInvoker::Invoke<742, float>(entity, animDict, animName); }
	FORCEINLINE float GET_ANIM_DURATION(const char* animDict, const char* animName) { return YimMenu::NativeInvoker::Invoke<743, float>(animDict, animName); }
	FORCEINLINE Entity GET_ENTITY_ATTACHED_TO(Entity entity) { return YimMenu::NativeInvoker::Invoke<744, Entity>(entity); }
	FORCEINLINE Vector3 GET_ENTITY_COORDS(Entity entity, bool alive) { return YimMenu::NativeInvoker::Invoke<745, Vector3>(entity, alive); }
	FORCEINLINE Vector3 GET_ENTITY_FORWARD_VECTOR(Entity entity) { return YimMenu::NativeInvoker::Invoke<746, Vector3>(entity); }
	FORCEINLINE float GET_ENTITY_FORWARD_X(Entity entity) { return YimMenu::NativeInvoker::Invoke<747, float>(entity); }
	FORCEINLINE float GET_ENTITY_FORWARD_Y(Entity entity) { return YimMenu::NativeInvoker::Invoke<748, float>(entity); }
	FORCEINLINE float GET_ENTITY_HEADING(Entity entity) { return YimMenu::NativeInvoker::Invoke<749, float>(entity); }
	FORCEINLINE float GET_ENTITY_HEADING_FROM_EULERS(Entity entity) { return YimMenu::NativeInvoker::Invoke<750, float>(entity); }
	FORCEINLINE int GET_ENTITY_HEALTH(Entity entity) { return YimMenu::NativeInvoker::Invoke<751, int>(entity); }
	FORCEINLINE int GET_ENTITY_MAX_HEALTH(Entity entity) { return YimMenu::NativeInvoker::Invoke<752, int>(entity); }
	FORCEINLINE void SET_ENTITY_MAX_HEALTH(Entity entity, int value) { return YimMenu::NativeInvoker::Invoke<753, void>(entity, value); }
	FORCEINLINE float GET_ENTITY_HEIGHT(Entity entity, float X, float Y, float Z, bool atTop, bool inWorldCoords) { return YimMenu::NativeInvoker::Invoke<754, float>(entity, X, Y, Z, atTop, inWorldCoords); }
	FORCEINLINE float GET_ENTITY_HEIGHT_ABOVE_GROUND(Entity entity) { return YimMenu::NativeInvoker::Invoke<755, float>(entity); }
	FORCEINLINE void GET_ENTITY_MATRIX(Entity entity, Vector3* forwardVector, Vector3* rightVector, Vector3* upVector, Vector3* position) { return YimMenu::NativeInvoker::Invoke<756, void>(entity, forwardVector, rightVector, upVector, position); }
	FORCEINLINE Hash GET_ENTITY_MODEL(Entity entity) { return YimMenu::NativeInvoker::Invoke<757, Hash>(entity); }
	FORCEINLINE Vector3 GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(Entity entity, float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<758, Vector3>(entity, posX, posY, posZ); }
	FORCEINLINE Vector3 GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Entity entity, float offsetX, float offsetY, float offsetZ) { return YimMenu::NativeInvoker::Invoke<759, Vector3>(entity, offsetX, offsetY, offsetZ); }
	FORCEINLINE float GET_ENTITY_PITCH(Entity entity) { return YimMenu::NativeInvoker::Invoke<760, float>(entity); }
	FORCEINLINE void GET_ENTITY_QUATERNION(Entity entity, float* x, float* y, float* z, float* w) { return YimMenu::NativeInvoker::Invoke<761, void>(entity, x, y, z, w); }
	FORCEINLINE float GET_ENTITY_ROLL(Entity entity) { return YimMenu::NativeInvoker::Invoke<762, float>(entity); }
	FORCEINLINE Vector3 GET_ENTITY_ROTATION(Entity entity, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<763, Vector3>(entity, rotationOrder); }
	FORCEINLINE Vector3 GET_ENTITY_ROTATION_VELOCITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<764, Vector3>(entity); }
	FORCEINLINE const char* GET_ENTITY_SCRIPT(Entity entity, ScrHandle* script) { return YimMenu::NativeInvoker::Invoke<765, const char*>(entity, script); }
	FORCEINLINE float GET_ENTITY_SPEED(Entity entity) { return YimMenu::NativeInvoker::Invoke<766, float>(entity); }
	FORCEINLINE Vector3 GET_ENTITY_SPEED_VECTOR(Entity entity, bool relative) { return YimMenu::NativeInvoker::Invoke<767, Vector3>(entity, relative); }
	FORCEINLINE float GET_ENTITY_UPRIGHT_VALUE(Entity entity) { return YimMenu::NativeInvoker::Invoke<768, float>(entity); }
	FORCEINLINE Vector3 GET_ENTITY_VELOCITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<769, Vector3>(entity); }
	FORCEINLINE Object GET_OBJECT_INDEX_FROM_ENTITY_INDEX(Entity entity) { return YimMenu::NativeInvoker::Invoke<770, Object>(entity); }
	FORCEINLINE Ped GET_PED_INDEX_FROM_ENTITY_INDEX(Entity entity) { return YimMenu::NativeInvoker::Invoke<771, Ped>(entity); }
	FORCEINLINE Vehicle GET_VEHICLE_INDEX_FROM_ENTITY_INDEX(Entity entity) { return YimMenu::NativeInvoker::Invoke<772, Vehicle>(entity); }
	FORCEINLINE Vector3 GET_WORLD_POSITION_OF_ENTITY_BONE(Entity entity, int boneIndex) { return YimMenu::NativeInvoker::Invoke<773, Vector3>(entity, boneIndex); }
	FORCEINLINE Player GET_NEAREST_PLAYER_TO_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<774, Player>(entity); }
	FORCEINLINE Player GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM(Entity entity, int team) { return YimMenu::NativeInvoker::Invoke<775, Player>(entity, team); }
	FORCEINLINE int GET_ENTITY_TYPE(Entity entity) { return YimMenu::NativeInvoker::Invoke<776, int>(entity); }
	FORCEINLINE int GET_ENTITY_POPULATION_TYPE(Entity entity) { return YimMenu::NativeInvoker::Invoke<777, int>(entity); }
	FORCEINLINE bool IS_AN_ENTITY(ScrHandle handle) { return YimMenu::NativeInvoker::Invoke<778, bool>(handle); }
	FORCEINLINE bool IS_ENTITY_A_PED(Entity entity) { return YimMenu::NativeInvoker::Invoke<779, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_A_MISSION_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<780, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_A_VEHICLE(Entity entity) { return YimMenu::NativeInvoker::Invoke<781, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_AN_OBJECT(Entity entity) { return YimMenu::NativeInvoker::Invoke<782, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_AT_COORD(Entity entity, float xPos, float yPos, float zPos, float xSize, float ySize, float zSize, bool p7, bool p8, int p9) { return YimMenu::NativeInvoker::Invoke<783, bool>(entity, xPos, yPos, zPos, xSize, ySize, zSize, p7, p8, p9); }
	FORCEINLINE bool IS_ENTITY_AT_ENTITY(Entity entity1, Entity entity2, float xSize, float ySize, float zSize, bool p5, bool p6, int p7) { return YimMenu::NativeInvoker::Invoke<784, bool>(entity1, entity2, xSize, ySize, zSize, p5, p6, p7); }
	FORCEINLINE bool IS_ENTITY_ATTACHED(Entity entity) { return YimMenu::NativeInvoker::Invoke<785, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_ATTACHED_TO_ANY_OBJECT(Entity entity) { return YimMenu::NativeInvoker::Invoke<786, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_ATTACHED_TO_ANY_PED(Entity entity) { return YimMenu::NativeInvoker::Invoke<787, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(Entity entity) { return YimMenu::NativeInvoker::Invoke<788, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_ATTACHED_TO_ENTITY(Entity from, Entity to) { return YimMenu::NativeInvoker::Invoke<789, bool>(from, to); }
	FORCEINLINE bool IS_ENTITY_DEAD(Entity entity, bool p1) { return YimMenu::NativeInvoker::Invoke<790, bool>(entity, p1); }
	FORCEINLINE bool IS_ENTITY_IN_AIR(Entity entity) { return YimMenu::NativeInvoker::Invoke<791, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_IN_ANGLED_AREA(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, float width, bool debug, bool includeZ, Any p10) { return YimMenu::NativeInvoker::Invoke<792, bool>(entity, x1, y1, z1, x2, y2, z2, width, debug, includeZ, p10); }
	FORCEINLINE bool IS_ENTITY_IN_AREA(Entity entity, float x1, float y1, float z1, float x2, float y2, float z2, bool p7, bool p8, Any p9) { return YimMenu::NativeInvoker::Invoke<793, bool>(entity, x1, y1, z1, x2, y2, z2, p7, p8, p9); }
	FORCEINLINE bool IS_ENTITY_IN_ZONE(Entity entity, const char* zone) { return YimMenu::NativeInvoker::Invoke<794, bool>(entity, zone); }
	FORCEINLINE bool IS_ENTITY_IN_WATER(Entity entity) { return YimMenu::NativeInvoker::Invoke<795, bool>(entity); }
	FORCEINLINE float GET_ENTITY_SUBMERGED_LEVEL(Entity entity) { return YimMenu::NativeInvoker::Invoke<796, float>(entity); }
	FORCEINLINE void SET_ENTITY_REQUIRES_MORE_EXPENSIVE_RIVER_CHECK(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<797, void>(entity, toggle); }
	FORCEINLINE bool IS_ENTITY_ON_SCREEN(Entity entity) { return YimMenu::NativeInvoker::Invoke<798, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_PLAYING_ANIM(Entity entity, const char* animDict, const char* animName, int taskFlag) { return YimMenu::NativeInvoker::Invoke<799, bool>(entity, animDict, animName, taskFlag); }
	FORCEINLINE bool IS_ENTITY_STATIC(Entity entity) { return YimMenu::NativeInvoker::Invoke<800, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_TOUCHING_ENTITY(Entity entity, Entity targetEntity) { return YimMenu::NativeInvoker::Invoke<801, bool>(entity, targetEntity); }
	FORCEINLINE bool IS_ENTITY_TOUCHING_MODEL(Entity entity, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<802, bool>(entity, modelHash); }
	FORCEINLINE bool IS_ENTITY_UPRIGHT(Entity entity, float angle) { return YimMenu::NativeInvoker::Invoke<803, bool>(entity, angle); }
	FORCEINLINE bool IS_ENTITY_UPSIDEDOWN(Entity entity) { return YimMenu::NativeInvoker::Invoke<804, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_VISIBLE(Entity entity) { return YimMenu::NativeInvoker::Invoke<805, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_VISIBLE_TO_SCRIPT(Entity entity) { return YimMenu::NativeInvoker::Invoke<806, bool>(entity); }
	FORCEINLINE bool IS_ENTITY_OCCLUDED(Entity entity) { return YimMenu::NativeInvoker::Invoke<807, bool>(entity); }
	FORCEINLINE bool WOULD_ENTITY_BE_OCCLUDED(Hash entityModelHash, float x, float y, float z, bool p4) { return YimMenu::NativeInvoker::Invoke<808, bool>(entityModelHash, x, y, z, p4); }
	FORCEINLINE bool IS_ENTITY_WAITING_FOR_WORLD_COLLISION(Entity entity) { return YimMenu::NativeInvoker::Invoke<809, bool>(entity); }
	FORCEINLINE void APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(Entity entity, int forceType, float x, float y, float z, bool p5, bool isDirectionRel, bool isForceRel, bool p8) { return YimMenu::NativeInvoker::Invoke<810, void>(entity, forceType, x, y, z, p5, isDirectionRel, isForceRel, p8); }
	FORCEINLINE void APPLY_FORCE_TO_ENTITY(Entity entity, int forceFlags, float x, float y, float z, float offX, float offY, float offZ, int boneIndex, bool isDirectionRel, bool ignoreUpVec, bool isForceRel, bool p12, bool p13) { return YimMenu::NativeInvoker::Invoke<811, void>(entity, forceFlags, x, y, z, offX, offY, offZ, boneIndex, isDirectionRel, ignoreUpVec, isForceRel, p12, p13); }
	FORCEINLINE void ATTACH_ENTITY_TO_ENTITY(Entity entity1, Entity entity2, int boneIndex, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, bool p9, bool useSoftPinning, bool collision, bool isPed, int vertexIndex, bool fixedRot, Any p15) { return YimMenu::NativeInvoker::Invoke<812, void>(entity1, entity2, boneIndex, xPos, yPos, zPos, xRot, yRot, zRot, p9, useSoftPinning, collision, isPed, vertexIndex, fixedRot, p15); }
	FORCEINLINE void ATTACH_ENTITY_BONE_TO_ENTITY_BONE(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, bool p4, bool p5) { return YimMenu::NativeInvoker::Invoke<813, void>(entity1, entity2, boneIndex1, boneIndex2, p4, p5); }
	FORCEINLINE void ATTACH_ENTITY_BONE_TO_ENTITY_BONE_Y_FORWARD(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, bool p4, bool p5) { return YimMenu::NativeInvoker::Invoke<814, void>(entity1, entity2, boneIndex1, boneIndex2, p4, p5); }
	FORCEINLINE void ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(Entity entity1, Entity entity2, int boneIndex1, int boneIndex2, float xPos1, float yPos1, float zPos1, float xPos2, float yPos2, float zPos2, float xRot, float yRot, float zRot, float breakForce, bool fixedRot, bool p15, bool collision, bool p17, int p18) { return YimMenu::NativeInvoker::Invoke<815, void>(entity1, entity2, boneIndex1, boneIndex2, xPos1, yPos1, zPos1, xPos2, yPos2, zPos2, xRot, yRot, zRot, breakForce, fixedRot, p15, collision, p17, p18); }
	FORCEINLINE void PROCESS_ENTITY_ATTACHMENTS(Entity entity) { return YimMenu::NativeInvoker::Invoke<816, void>(entity); }
	FORCEINLINE int GET_ENTITY_BONE_INDEX_BY_NAME(Entity entity, const char* boneName) { return YimMenu::NativeInvoker::Invoke<817, int>(entity, boneName); }
	FORCEINLINE void CLEAR_ENTITY_LAST_DAMAGE_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<818, void>(entity); }
	FORCEINLINE void DELETE_ENTITY(Entity* entity) { return YimMenu::NativeInvoker::Invoke<819, void>(entity); }
	FORCEINLINE void DETACH_ENTITY(Entity entity, bool dynamic, bool collision) { return YimMenu::NativeInvoker::Invoke<820, void>(entity, dynamic, collision); }
	FORCEINLINE void FREEZE_ENTITY_POSITION(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<821, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<822, void>(entity, toggle); }
	FORCEINLINE bool PLAY_ENTITY_ANIM(Entity entity, const char* animName, const char* animDict, float p3, bool loop, bool stayInAnim, bool p6, float delta, Any bitset) { return YimMenu::NativeInvoker::Invoke<823, bool>(entity, animName, animDict, p3, loop, stayInAnim, p6, delta, bitset); }
	FORCEINLINE bool PLAY_SYNCHRONIZED_ENTITY_ANIM(Entity entity, int syncedScene, const char* animation, const char* propName, float p4, float p5, Any p6, float p7) { return YimMenu::NativeInvoker::Invoke<824, bool>(entity, syncedScene, animation, propName, p4, p5, p6, p7); }
	FORCEINLINE bool PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM(float x1, float y1, float z1, float x2, Any y2, float z2, const char* p6, const char* p7, float p8, float p9, Any p10, float p11) { return YimMenu::NativeInvoker::Invoke<825, bool>(x1, y1, z1, x2, y2, z2, p6, p7, p8, p9, p10, p11); }
	FORCEINLINE bool STOP_SYNCHRONIZED_MAP_ENTITY_ANIM(float x1, float y1, float z1, float x2, Any y2, float z2) { return YimMenu::NativeInvoker::Invoke<826, bool>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE bool STOP_ENTITY_ANIM(Entity entity, const char* animation, const char* animGroup, float p3) { return YimMenu::NativeInvoker::Invoke<827, bool>(entity, animation, animGroup, p3); }
	FORCEINLINE bool STOP_SYNCHRONIZED_ENTITY_ANIM(Entity entity, float p1, bool p2) { return YimMenu::NativeInvoker::Invoke<828, bool>(entity, p1, p2); }
	FORCEINLINE bool HAS_ANIM_EVENT_FIRED(Entity entity, Hash actionHash) { return YimMenu::NativeInvoker::Invoke<829, bool>(entity, actionHash); }
	FORCEINLINE bool FIND_ANIM_EVENT_PHASE(const char* animDictionary, const char* animName, const char* p2, Any* p3, Any* p4) { return YimMenu::NativeInvoker::Invoke<830, bool>(animDictionary, animName, p2, p3, p4); }
	FORCEINLINE void SET_ENTITY_ANIM_CURRENT_TIME(Entity entity, const char* animDictionary, const char* animName, float time) { return YimMenu::NativeInvoker::Invoke<831, void>(entity, animDictionary, animName, time); }
	FORCEINLINE void SET_ENTITY_ANIM_SPEED(Entity entity, const char* animDictionary, const char* animName, float speedMultiplier) { return YimMenu::NativeInvoker::Invoke<832, void>(entity, animDictionary, animName, speedMultiplier); }
	FORCEINLINE void SET_ENTITY_AS_MISSION_ENTITY(Entity entity, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<833, void>(entity, p1, p2); }
	FORCEINLINE void SET_ENTITY_AS_NO_LONGER_NEEDED(Entity* entity) { return YimMenu::NativeInvoker::Invoke<834, void>(entity); }
	FORCEINLINE void SET_PED_AS_NO_LONGER_NEEDED(Ped* ped) { return YimMenu::NativeInvoker::Invoke<835, void>(ped); }
	FORCEINLINE void SET_VEHICLE_AS_NO_LONGER_NEEDED(Vehicle* vehicle) { return YimMenu::NativeInvoker::Invoke<836, void>(vehicle); }
	FORCEINLINE void SET_OBJECT_AS_NO_LONGER_NEEDED(Object* object) { return YimMenu::NativeInvoker::Invoke<837, void>(object); }
	FORCEINLINE void SET_ENTITY_CAN_BE_DAMAGED(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<838, void>(entity, toggle); }
	FORCEINLINE bool GET_ENTITY_CAN_BE_DAMAGED(Entity entity) { return YimMenu::NativeInvoker::Invoke<839, bool>(entity); }
	FORCEINLINE void SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool bCanBeDamaged, int relGroup) { return YimMenu::NativeInvoker::Invoke<840, void>(entity, bCanBeDamaged, relGroup); }
	FORCEINLINE void SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_SCRIPT_PARTICIPANTS(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<841, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<842, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_COLLISION(Entity entity, bool toggle, bool keepPhysics) { return YimMenu::NativeInvoker::Invoke<843, void>(entity, toggle, keepPhysics); }
	FORCEINLINE bool GET_ENTITY_COLLISION_DISABLED(Entity entity) { return YimMenu::NativeInvoker::Invoke<844, bool>(entity); }
	FORCEINLINE void SET_ENTITY_COMPLETELY_DISABLE_COLLISION(Entity entity, bool toggle, bool keepPhysics) { return YimMenu::NativeInvoker::Invoke<845, void>(entity, toggle, keepPhysics); }
	FORCEINLINE void SET_ENTITY_COORDS(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis, bool clearArea) { return YimMenu::NativeInvoker::Invoke<846, void>(entity, xPos, yPos, zPos, xAxis, yAxis, zAxis, clearArea); }
	FORCEINLINE void SET_ENTITY_COORDS_WITHOUT_PLANTS_RESET(Entity entity, float xPos, float yPos, float zPos, bool alive, bool deadFlag, bool ragdollFlag, bool clearArea) { return YimMenu::NativeInvoker::Invoke<847, void>(entity, xPos, yPos, zPos, alive, deadFlag, ragdollFlag, clearArea); }
	FORCEINLINE void SET_ENTITY_COORDS_NO_OFFSET(Entity entity, float xPos, float yPos, float zPos, bool xAxis, bool yAxis, bool zAxis) { return YimMenu::NativeInvoker::Invoke<848, void>(entity, xPos, yPos, zPos, xAxis, yAxis, zAxis); }
	FORCEINLINE void SET_ENTITY_DYNAMIC(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<849, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_HEADING(Entity entity, float heading) { return YimMenu::NativeInvoker::Invoke<850, void>(entity, heading); }
	FORCEINLINE void SET_ENTITY_HEALTH(Entity entity, int health, int p2) { return YimMenu::NativeInvoker::Invoke<851, void>(entity, health, p2); }
	FORCEINLINE void SET_ENTITY_INVINCIBLE(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<852, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_IS_TARGET_PRIORITY(Entity entity, bool p1, float p2) { return YimMenu::NativeInvoker::Invoke<853, void>(entity, p1, p2); }
	FORCEINLINE void SET_ENTITY_LIGHTS(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<854, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_LOAD_COLLISION_FLAG(Entity entity, bool toggle, Any p2) { return YimMenu::NativeInvoker::Invoke<855, void>(entity, toggle, p2); }
	FORCEINLINE bool HAS_COLLISION_LOADED_AROUND_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<856, bool>(entity); }
	FORCEINLINE void SET_ENTITY_MAX_SPEED(Entity entity, float speed) { return YimMenu::NativeInvoker::Invoke<857, void>(entity, speed); }
	FORCEINLINE void SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<858, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Entity entity, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<859, void>(entity, p1, p2); }
	FORCEINLINE void SET_ENTITY_PROOFS(Entity entity, bool bulletProof, bool fireProof, bool explosionProof, bool collisionProof, bool meleeProof, bool steamProof, bool p7, bool waterProof) { return YimMenu::NativeInvoker::Invoke<860, void>(entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, steamProof, p7, waterProof); }
	FORCEINLINE bool GET_ENTITY_PROOFS(Entity entity, bool* bulletProof, bool* fireProof, bool* explosionProof, bool* collisionProof, bool* meleeProof, bool* steamProof, bool* p7, bool* drownProof) { return YimMenu::NativeInvoker::Invoke<861, bool>(entity, bulletProof, fireProof, explosionProof, collisionProof, meleeProof, steamProof, p7, drownProof); }
	FORCEINLINE void SET_ENTITY_QUATERNION(Entity entity, float x, float y, float z, float w) { return YimMenu::NativeInvoker::Invoke<862, void>(entity, x, y, z, w); }
	FORCEINLINE void SET_ENTITY_RECORDS_COLLISIONS(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<863, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_ROTATION(Entity entity, float pitch, float roll, float yaw, int rotationOrder, bool p5) { return YimMenu::NativeInvoker::Invoke<864, void>(entity, pitch, roll, yaw, rotationOrder, p5); }
	FORCEINLINE void SET_ENTITY_VISIBLE(Entity entity, bool toggle, bool p2) { return YimMenu::NativeInvoker::Invoke<865, void>(entity, toggle, p2); }
	FORCEINLINE void SET_ENTITY_WATER_REFLECTION_FLAG(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<866, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_MIRROR_REFLECTION_FLAG(Entity entity, bool p1) { return YimMenu::NativeInvoker::Invoke<867, void>(entity, p1); }
	FORCEINLINE void SET_ENTITY_VELOCITY(Entity entity, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<868, void>(entity, x, y, z); }
	FORCEINLINE void SET_ENTITY_ANGULAR_VELOCITY(Entity entity, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<869, void>(entity, x, y, z); }
	FORCEINLINE void SET_ENTITY_HAS_GRAVITY(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<870, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_LOD_DIST(Entity entity, int value) { return YimMenu::NativeInvoker::Invoke<871, void>(entity, value); }
	FORCEINLINE int GET_ENTITY_LOD_DIST(Entity entity) { return YimMenu::NativeInvoker::Invoke<872, int>(entity); }
	FORCEINLINE void SET_ENTITY_ALPHA(Entity entity, int alphaLevel, bool skin) { return YimMenu::NativeInvoker::Invoke<873, void>(entity, alphaLevel, skin); }
	FORCEINLINE int GET_ENTITY_ALPHA(Entity entity) { return YimMenu::NativeInvoker::Invoke<874, int>(entity); }
	FORCEINLINE void RESET_ENTITY_ALPHA(Entity entity) { return YimMenu::NativeInvoker::Invoke<875, void>(entity); }
	FORCEINLINE void RESET_PICKUP_ENTITY_GLOW(Entity entity) { return YimMenu::NativeInvoker::Invoke<876, void>(entity); }
	FORCEINLINE void SET_PICKUP_COLLIDES_WITH_PROJECTILES(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<877, void>(p0, p1); }
	FORCEINLINE void SET_ENTITY_SORT_BIAS(Entity entity, float p1) { return YimMenu::NativeInvoker::Invoke<878, void>(entity, p1); }
	FORCEINLINE void SET_ENTITY_ALWAYS_PRERENDER(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<879, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_RENDER_SCORCHED(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<880, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_TRAFFICLIGHT_OVERRIDE(Entity entity, int state) { return YimMenu::NativeInvoker::Invoke<881, void>(entity, state); }
	FORCEINLINE void SET_ENTITY_IS_IN_VEHICLE(Entity entity) { return YimMenu::NativeInvoker::Invoke<882, void>(entity); }
	FORCEINLINE void CREATE_MODEL_SWAP(float x, float y, float z, float radius, Hash originalModel, Hash newModel, bool p6) { return YimMenu::NativeInvoker::Invoke<883, void>(x, y, z, radius, originalModel, newModel, p6); }
	FORCEINLINE void REMOVE_MODEL_SWAP(float x, float y, float z, float radius, Hash originalModel, Hash newModel, bool p6) { return YimMenu::NativeInvoker::Invoke<884, void>(x, y, z, radius, originalModel, newModel, p6); }
	FORCEINLINE void CREATE_MODEL_HIDE(float x, float y, float z, float radius, Hash modelHash, bool p5) { return YimMenu::NativeInvoker::Invoke<885, void>(x, y, z, radius, modelHash, p5); }
	FORCEINLINE void CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS(float x, float y, float z, float radius, Hash modelHash, bool p5) { return YimMenu::NativeInvoker::Invoke<886, void>(x, y, z, radius, modelHash, p5); }
	FORCEINLINE void REMOVE_MODEL_HIDE(float x, float y, float z, float radius, Hash modelHash, bool p5) { return YimMenu::NativeInvoker::Invoke<887, void>(x, y, z, radius, modelHash, p5); }
	FORCEINLINE void CREATE_FORCED_OBJECT(float x, float y, float z, Any p3, Hash modelHash, bool p5) { return YimMenu::NativeInvoker::Invoke<888, void>(x, y, z, p3, modelHash, p5); }
	FORCEINLINE void REMOVE_FORCED_OBJECT(float x, float y, float z, float p3, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<889, void>(x, y, z, p3, modelHash); }
	FORCEINLINE void SET_ENTITY_NO_COLLISION_ENTITY(Entity entity1, Entity entity2, bool thisFrameOnly) { return YimMenu::NativeInvoker::Invoke<890, void>(entity1, entity2, thisFrameOnly); }
	FORCEINLINE void SET_ENTITY_MOTION_BLUR(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<891, void>(entity, toggle); }
	FORCEINLINE void SET_CAN_AUTO_VAULT_ON_ENTITY(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<892, void>(entity, toggle); }
	FORCEINLINE void SET_CAN_CLIMB_ON_ENTITY(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<893, void>(entity, toggle); }
	FORCEINLINE void SET_WAIT_FOR_COLLISIONS_BEFORE_PROBE(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<894, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_NOWEAPONDECALS(Entity entity, bool p1) { return YimMenu::NativeInvoker::Invoke<895, void>(entity, p1); }
	FORCEINLINE void SET_ENTITY_USE_MAX_DISTANCE_FOR_WATER_REFLECTION(Entity entity, bool p1) { return YimMenu::NativeInvoker::Invoke<896, void>(entity, p1); }
	FORCEINLINE Vector3 GET_ENTITY_BONE_ROTATION(Entity entity, int boneIndex) { return YimMenu::NativeInvoker::Invoke<897, Vector3>(entity, boneIndex); }
	FORCEINLINE Vector3 GET_ENTITY_BONE_POSTION(Entity entity, int boneIndex) { return YimMenu::NativeInvoker::Invoke<898, Vector3>(entity, boneIndex); }
	FORCEINLINE Vector3 GET_ENTITY_BONE_OBJECT_ROTATION(Entity entity, int boneIndex) { return YimMenu::NativeInvoker::Invoke<899, Vector3>(entity, boneIndex); }
	FORCEINLINE Vector3 GET_ENTITY_BONE_OBJECT_POSTION(Entity entity, int boneIndex) { return YimMenu::NativeInvoker::Invoke<900, Vector3>(entity, boneIndex); }
	FORCEINLINE int GET_ENTITY_BONE_COUNT(Entity entity) { return YimMenu::NativeInvoker::Invoke<901, int>(entity); }
	FORCEINLINE void ENABLE_ENTITY_BULLET_COLLISION(Entity entity) { return YimMenu::NativeInvoker::Invoke<902, void>(entity); }
	FORCEINLINE void SET_ENTITY_CAN_ONLY_BE_DAMAGED_BY_ENTITY(Entity entity1, Entity entity2) { return YimMenu::NativeInvoker::Invoke<903, void>(entity1, entity2); }
	FORCEINLINE void SET_ENTITY_CANT_CAUSE_COLLISION_DAMAGED_ENTITY(Entity entity1, Entity entity2) { return YimMenu::NativeInvoker::Invoke<904, void>(entity1, entity2); }
	FORCEINLINE void SET_ALLOW_MIGRATE_TO_SPECTATOR(Entity entity, Any p1) { return YimMenu::NativeInvoker::Invoke<905, void>(entity, p1); }
	FORCEINLINE Entity GET_ENTITY_OF_TYPE_ATTACHED_TO_ENTITY(Entity entity, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<906, Entity>(entity, modelHash); }
	FORCEINLINE void SET_PICK_UP_BY_CARGOBOB_DISABLED(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<907, void>(entity, toggle); }
}

namespace EVENT
{
	FORCEINLINE void SET_DECISION_MAKER(Ped ped, Hash name) { return YimMenu::NativeInvoker::Invoke<908, void>(ped, name); }
	FORCEINLINE void CLEAR_DECISION_MAKER_EVENT_RESPONSE(Hash name, int eventType) { return YimMenu::NativeInvoker::Invoke<909, void>(name, eventType); }
	FORCEINLINE void BLOCK_DECISION_MAKER_EVENT(Hash name, int eventType) { return YimMenu::NativeInvoker::Invoke<910, void>(name, eventType); }
	FORCEINLINE void UNBLOCK_DECISION_MAKER_EVENT(Hash name, int eventType) { return YimMenu::NativeInvoker::Invoke<911, void>(name, eventType); }
	FORCEINLINE int ADD_SHOCKING_EVENT_AT_POSITION(int eventType, float x, float y, float z, float duration) { return YimMenu::NativeInvoker::Invoke<912, int>(eventType, x, y, z, duration); }
	FORCEINLINE int ADD_SHOCKING_EVENT_FOR_ENTITY(int eventType, Entity entity, float duration) { return YimMenu::NativeInvoker::Invoke<913, int>(eventType, entity, duration); }
	FORCEINLINE bool IS_SHOCKING_EVENT_IN_SPHERE(int eventType, float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<914, bool>(eventType, x, y, z, radius); }
	FORCEINLINE bool REMOVE_SHOCKING_EVENT(ScrHandle event) { return YimMenu::NativeInvoker::Invoke<915, bool>(event); }
	FORCEINLINE void REMOVE_ALL_SHOCKING_EVENTS(bool p0) { return YimMenu::NativeInvoker::Invoke<916, void>(p0); }
	FORCEINLINE void REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS() { return YimMenu::NativeInvoker::Invoke<917, void>(); }
	FORCEINLINE void SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME() { return YimMenu::NativeInvoker::Invoke<918, void>(); }
	FORCEINLINE void SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME(int eventType) { return YimMenu::NativeInvoker::Invoke<919, void>(eventType); }
	FORCEINLINE void SUPPRESS_AGITATION_EVENTS_NEXT_FRAME() { return YimMenu::NativeInvoker::Invoke<920, void>(); }
}

namespace FILES
{
	FORCEINLINE int GET_NUM_TATTOO_SHOP_DLC_ITEMS(int character) { return YimMenu::NativeInvoker::Invoke<921, int>(character); }
	FORCEINLINE bool GET_TATTOO_SHOP_DLC_ITEM_DATA(int characterType, int decorationIndex, Any* outComponent) { return YimMenu::NativeInvoker::Invoke<922, bool>(characterType, decorationIndex, outComponent); }
	FORCEINLINE int GET_TATTOO_SHOP_DLC_ITEM_INDEX(Hash overlayHash, Any p1, int character) { return YimMenu::NativeInvoker::Invoke<923, int>(overlayHash, p1, character); }
	FORCEINLINE void INIT_SHOP_PED_COMPONENT(Any* outComponent) { return YimMenu::NativeInvoker::Invoke<924, void>(outComponent); }
	FORCEINLINE void INIT_SHOP_PED_PROP(Any* outProp) { return YimMenu::NativeInvoker::Invoke<925, void>(outProp); }
	FORCEINLINE int SETUP_SHOP_PED_APPAREL_QUERY(int p0, int p1, int p2, int p3) { return YimMenu::NativeInvoker::Invoke<926, int>(p0, p1, p2, p3); }
	FORCEINLINE int SETUP_SHOP_PED_APPAREL_QUERY_TU(int character, int p1, int p2, bool p3, int p4, int componentId) { return YimMenu::NativeInvoker::Invoke<927, int>(character, p1, p2, p3, p4, componentId); }
	FORCEINLINE void GET_SHOP_PED_QUERY_COMPONENT(int componentId, Any* outComponent) { return YimMenu::NativeInvoker::Invoke<928, void>(componentId, outComponent); }
	FORCEINLINE int GET_SHOP_PED_QUERY_COMPONENT_INDEX(Hash componentHash) { return YimMenu::NativeInvoker::Invoke<929, int>(componentHash); }
	FORCEINLINE void GET_SHOP_PED_COMPONENT(Hash componentHash, Any* outComponent) { return YimMenu::NativeInvoker::Invoke<930, void>(componentHash, outComponent); }
	FORCEINLINE void GET_SHOP_PED_QUERY_PROP(int componentId, Any* outProp) { return YimMenu::NativeInvoker::Invoke<931, void>(componentId, outProp); }
	FORCEINLINE int GET_SHOP_PED_QUERY_PROP_INDEX(Hash componentHash) { return YimMenu::NativeInvoker::Invoke<932, int>(componentHash); }
	FORCEINLINE void GET_SHOP_PED_PROP(Hash componentHash, Any* outProp) { return YimMenu::NativeInvoker::Invoke<933, void>(componentHash, outProp); }
	FORCEINLINE Hash GET_HASH_NAME_FOR_COMPONENT(Entity entity, int componentId, int drawableVariant, int textureVariant) { return YimMenu::NativeInvoker::Invoke<934, Hash>(entity, componentId, drawableVariant, textureVariant); }
	FORCEINLINE Hash GET_HASH_NAME_FOR_PROP(Entity entity, int componentId, int propIndex, int propTextureIndex) { return YimMenu::NativeInvoker::Invoke<935, Hash>(entity, componentId, propIndex, propTextureIndex); }
	FORCEINLINE int GET_SHOP_PED_APPAREL_VARIANT_COMPONENT_COUNT(Hash componentHash) { return YimMenu::NativeInvoker::Invoke<936, int>(componentHash); }
	FORCEINLINE int GET_SHOP_PED_APPAREL_VARIANT_PROP_COUNT(Hash propHash) { return YimMenu::NativeInvoker::Invoke<937, int>(propHash); }
	FORCEINLINE void GET_VARIANT_COMPONENT(Hash componentHash, int variantComponentIndex, Hash* nameHash, int* enumValue, int* componentType) { return YimMenu::NativeInvoker::Invoke<938, void>(componentHash, variantComponentIndex, nameHash, enumValue, componentType); }
	FORCEINLINE void GET_VARIANT_PROP(Hash componentHash, int variantPropIndex, Hash* nameHash, int* enumValue, int* anchorPoint) { return YimMenu::NativeInvoker::Invoke<939, void>(componentHash, variantPropIndex, nameHash, enumValue, anchorPoint); }
	FORCEINLINE int GET_SHOP_PED_APPAREL_FORCED_COMPONENT_COUNT(Hash componentHash) { return YimMenu::NativeInvoker::Invoke<940, int>(componentHash); }
	FORCEINLINE int GET_SHOP_PED_APPAREL_FORCED_PROP_COUNT(Hash componentHash) { return YimMenu::NativeInvoker::Invoke<941, int>(componentHash); }
	FORCEINLINE void GET_FORCED_COMPONENT(Hash componentHash, int forcedComponentIndex, Hash* nameHash, int* enumValue, int* componentType) { return YimMenu::NativeInvoker::Invoke<942, void>(componentHash, forcedComponentIndex, nameHash, enumValue, componentType); }
	FORCEINLINE void GET_FORCED_PROP(Hash componentHash, int forcedPropIndex, Hash* nameHash, int* enumValue, int* anchorPoint) { return YimMenu::NativeInvoker::Invoke<943, void>(componentHash, forcedPropIndex, nameHash, enumValue, anchorPoint); }
	FORCEINLINE bool DOES_SHOP_PED_APPAREL_HAVE_RESTRICTION_TAG(Hash componentHash, Hash restrictionTagHash, int componentId) { return YimMenu::NativeInvoker::Invoke<944, bool>(componentHash, restrictionTagHash, componentId); }
	FORCEINLINE bool DOES_CURRENT_PED_COMPONENT_HAVE_RESTRICTION_TAG(Ped ped, int componentId, Hash restrictionTagHash) { return YimMenu::NativeInvoker::Invoke<945, bool>(ped, componentId, restrictionTagHash); }
	FORCEINLINE bool DOES_CURRENT_PED_PROP_HAVE_RESTRICTION_TAG(Ped ped, int componentId, Hash restrictionTagHash) { return YimMenu::NativeInvoker::Invoke<946, bool>(ped, componentId, restrictionTagHash); }
	FORCEINLINE int SETUP_SHOP_PED_OUTFIT_QUERY(int character, bool p1) { return YimMenu::NativeInvoker::Invoke<947, int>(character, p1); }
	FORCEINLINE void GET_SHOP_PED_QUERY_OUTFIT(int outfitIndex, Any* outfit) { return YimMenu::NativeInvoker::Invoke<948, void>(outfitIndex, outfit); }
	FORCEINLINE void GET_SHOP_PED_OUTFIT(Any p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<949, void>(p0, p1); }
	FORCEINLINE int GET_SHOP_PED_OUTFIT_LOCATE(Any p0) { return YimMenu::NativeInvoker::Invoke<950, int>(p0); }
	FORCEINLINE bool GET_SHOP_PED_OUTFIT_PROP_VARIANT(Hash outfitHash, int variantIndex, Any* outPropVariant) { return YimMenu::NativeInvoker::Invoke<951, bool>(outfitHash, variantIndex, outPropVariant); }
	FORCEINLINE bool GET_SHOP_PED_OUTFIT_COMPONENT_VARIANT(Hash outfitHash, int variantIndex, Any* outComponentVariant) { return YimMenu::NativeInvoker::Invoke<952, bool>(outfitHash, variantIndex, outComponentVariant); }
	FORCEINLINE int GET_NUM_DLC_VEHICLES() { return YimMenu::NativeInvoker::Invoke<953, int>(); }
	FORCEINLINE Hash GET_DLC_VEHICLE_MODEL(int dlcVehicleIndex) { return YimMenu::NativeInvoker::Invoke<954, Hash>(dlcVehicleIndex); }
	FORCEINLINE bool GET_DLC_VEHICLE_DATA(int dlcVehicleIndex, Any* outData) { return YimMenu::NativeInvoker::Invoke<955, bool>(dlcVehicleIndex, outData); }
	FORCEINLINE int GET_DLC_VEHICLE_FLAGS(int dlcVehicleIndex) { return YimMenu::NativeInvoker::Invoke<956, int>(dlcVehicleIndex); }
	FORCEINLINE int GET_NUM_DLC_WEAPONS() { return YimMenu::NativeInvoker::Invoke<957, int>(); }
	FORCEINLINE int GET_NUM_DLC_WEAPONS_SP() { return YimMenu::NativeInvoker::Invoke<958, int>(); }
	FORCEINLINE bool GET_DLC_WEAPON_DATA(int dlcWeaponIndex, Any* outData) { return YimMenu::NativeInvoker::Invoke<959, bool>(dlcWeaponIndex, outData); }
	FORCEINLINE bool GET_DLC_WEAPON_DATA_SP(int dlcWeaponIndex, Any* outData) { return YimMenu::NativeInvoker::Invoke<960, bool>(dlcWeaponIndex, outData); }
	FORCEINLINE int GET_NUM_DLC_WEAPON_COMPONENTS(int dlcWeaponIndex) { return YimMenu::NativeInvoker::Invoke<961, int>(dlcWeaponIndex); }
	FORCEINLINE int GET_NUM_DLC_WEAPON_COMPONENTS_SP(int dlcWeaponIndex) { return YimMenu::NativeInvoker::Invoke<962, int>(dlcWeaponIndex); }
	FORCEINLINE bool GET_DLC_WEAPON_COMPONENT_DATA(int dlcWeaponIndex, int dlcWeapCompIndex, Any* ComponentDataPtr) { return YimMenu::NativeInvoker::Invoke<963, bool>(dlcWeaponIndex, dlcWeapCompIndex, ComponentDataPtr); }
	FORCEINLINE bool GET_DLC_WEAPON_COMPONENT_DATA_SP(int dlcWeaponIndex, int dlcWeapCompIndex, Any* ComponentDataPtr) { return YimMenu::NativeInvoker::Invoke<964, bool>(dlcWeaponIndex, dlcWeapCompIndex, ComponentDataPtr); }
	FORCEINLINE bool IS_CONTENT_ITEM_LOCKED(Hash itemHash) { return YimMenu::NativeInvoker::Invoke<965, bool>(itemHash); }
	FORCEINLINE bool IS_DLC_VEHICLE_MOD(Hash hash) { return YimMenu::NativeInvoker::Invoke<966, bool>(hash); }
	FORCEINLINE Hash GET_DLC_VEHICLE_MOD_LOCK_HASH(Hash hash) { return YimMenu::NativeInvoker::Invoke<967, Hash>(hash); }
	FORCEINLINE void EXECUTE_CONTENT_CHANGESET_GROUP_FOR_ALL(Hash hash) { return YimMenu::NativeInvoker::Invoke<968, void>(hash); }
	FORCEINLINE void REVERT_CONTENT_CHANGESET_GROUP_FOR_ALL(Hash hash) { return YimMenu::NativeInvoker::Invoke<969, void>(hash); }
}

namespace FIRE
{
	FORCEINLINE FireId START_SCRIPT_FIRE(float X, float Y, float Z, int maxChildren, bool isGasFire) { return YimMenu::NativeInvoker::Invoke<970, FireId>(X, Y, Z, maxChildren, isGasFire); }
	FORCEINLINE void REMOVE_SCRIPT_FIRE(FireId fireHandle) { return YimMenu::NativeInvoker::Invoke<971, void>(fireHandle); }
	FORCEINLINE FireId START_ENTITY_FIRE(Entity entity) { return YimMenu::NativeInvoker::Invoke<972, FireId>(entity); }
	FORCEINLINE void STOP_ENTITY_FIRE(Entity entity) { return YimMenu::NativeInvoker::Invoke<973, void>(entity); }
	FORCEINLINE bool IS_ENTITY_ON_FIRE(Entity entity) { return YimMenu::NativeInvoker::Invoke<974, bool>(entity); }
	FORCEINLINE int GET_NUMBER_OF_FIRES_IN_RANGE(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<975, int>(x, y, z, radius); }
	FORCEINLINE void SET_FLAMMABILITY_MULTIPLIER(float p0) { return YimMenu::NativeInvoker::Invoke<976, void>(p0); }
	FORCEINLINE void STOP_FIRE_IN_RANGE(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<977, void>(x, y, z, radius); }
	FORCEINLINE bool GET_CLOSEST_FIRE_POS(Vector3* outPosition, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<978, bool>(outPosition, x, y, z); }
	FORCEINLINE void ADD_EXPLOSION(float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake, bool noDamage) { return YimMenu::NativeInvoker::Invoke<979, void>(x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake, noDamage); }
	FORCEINLINE void ADD_OWNED_EXPLOSION(Ped ped, float x, float y, float z, int explosionType, float damageScale, bool isAudible, bool isInvisible, float cameraShake) { return YimMenu::NativeInvoker::Invoke<980, void>(ped, x, y, z, explosionType, damageScale, isAudible, isInvisible, cameraShake); }
	FORCEINLINE void ADD_EXPLOSION_WITH_USER_VFX(float x, float y, float z, int explosionType, Hash explosionFx, float damageScale, bool isAudible, bool isInvisible, float cameraShake) { return YimMenu::NativeInvoker::Invoke<981, void>(x, y, z, explosionType, explosionFx, damageScale, isAudible, isInvisible, cameraShake); }
	FORCEINLINE bool IS_EXPLOSION_IN_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<982, bool>(explosionType, x1, y1, z1, x2, y2, z2); }
	FORCEINLINE bool IS_EXPLOSION_ACTIVE_IN_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<983, bool>(explosionType, x1, y1, z1, x2, y2, z2); }
	FORCEINLINE bool IS_EXPLOSION_IN_SPHERE(int explosionType, float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<984, bool>(explosionType, x, y, z, radius); }
	FORCEINLINE Entity GET_OWNER_OF_EXPLOSION_IN_SPHERE(int explosionType, float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<985, Entity>(explosionType, x, y, z, radius); }
	FORCEINLINE bool IS_EXPLOSION_IN_ANGLED_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float width) { return YimMenu::NativeInvoker::Invoke<986, bool>(explosionType, x1, y1, z1, x2, y2, z2, width); }
	FORCEINLINE Entity GET_OWNER_OF_EXPLOSION_IN_ANGLED_AREA(int explosionType, float x1, float y1, float z1, float x2, float y2, float z2, float radius) { return YimMenu::NativeInvoker::Invoke<987, Entity>(explosionType, x1, y1, z1, x2, y2, z2, radius); }
}

namespace GRAPHICS
{
	FORCEINLINE void SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(bool enabled) { return YimMenu::NativeInvoker::Invoke<988, void>(enabled); }
	FORCEINLINE void DRAW_DEBUG_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha) { return YimMenu::NativeInvoker::Invoke<989, void>(x1, y1, z1, x2, y2, z2, r, g, b, alpha); }
	FORCEINLINE void DRAW_DEBUG_LINE_WITH_TWO_COLOURS(float x1, float y1, float z1, float x2, float y2, float z2, int r1, int g1, int b1, int r2, int g2, int b2, int alpha1, int alpha2) { return YimMenu::NativeInvoker::Invoke<990, void>(x1, y1, z1, x2, y2, z2, r1, g1, b1, r2, g2, b2, alpha1, alpha2); }
	FORCEINLINE void DRAW_DEBUG_SPHERE(float x, float y, float z, float radius, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<991, void>(x, y, z, radius, red, green, blue, alpha); }
	FORCEINLINE void DRAW_DEBUG_BOX(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha) { return YimMenu::NativeInvoker::Invoke<992, void>(x1, y1, z1, x2, y2, z2, r, g, b, alpha); }
	FORCEINLINE void DRAW_DEBUG_CROSS(float x, float y, float z, float size, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<993, void>(x, y, z, size, red, green, blue, alpha); }
	FORCEINLINE void DRAW_DEBUG_TEXT(const char* text, float x, float y, float z, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<994, void>(text, x, y, z, red, green, blue, alpha); }
	FORCEINLINE void DRAW_DEBUG_TEXT_2D(const char* text, float x, float y, float z, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<995, void>(text, x, y, z, red, green, blue, alpha); }
	FORCEINLINE void DRAW_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<996, void>(x1, y1, z1, x2, y2, z2, red, green, blue, alpha); }
	FORCEINLINE void DRAW_POLY(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<997, void>(x1, y1, z1, x2, y2, z2, x3, y3, z3, red, green, blue, alpha); }
	FORCEINLINE void DRAW_TEXTURED_POLY(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha, const char* textureDict, const char* textureName, float u1, float v1, float w1, float u2, float v2, float w2, float u3, float v3, float w3) { return YimMenu::NativeInvoker::Invoke<998, void>(x1, y1, z1, x2, y2, z2, x3, y3, z3, red, green, blue, alpha, textureDict, textureName, u1, v1, w1, u2, v2, w2, u3, v3, w3); }
	FORCEINLINE void DRAW_TEXTURED_POLY_WITH_THREE_COLOURS(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float red1, float green1, float blue1, int alpha1, float red2, float green2, float blue2, int alpha2, float red3, float green3, float blue3, int alpha3, const char* textureDict, const char* textureName, float u1, float v1, float w1, float u2, float v2, float w2, float u3, float v3, float w3) { return YimMenu::NativeInvoker::Invoke<999, void>(x1, y1, z1, x2, y2, z2, x3, y3, z3, red1, green1, blue1, alpha1, red2, green2, blue2, alpha2, red3, green3, blue3, alpha3, textureDict, textureName, u1, v1, w1, u2, v2, w2, u3, v3, w3); }
	FORCEINLINE void DRAW_BOX(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1000, void>(x1, y1, z1, x2, y2, z2, red, green, blue, alpha); }
	FORCEINLINE void SET_BACKFACECULLING(bool toggle) { return YimMenu::NativeInvoker::Invoke<1001, void>(toggle); }
	FORCEINLINE void SET_DEPTHWRITING(bool toggle) { return YimMenu::NativeInvoker::Invoke<1002, void>(toggle); }
	FORCEINLINE bool BEGIN_TAKE_MISSION_CREATOR_PHOTO() { return YimMenu::NativeInvoker::Invoke<1003, bool>(); }
	FORCEINLINE int GET_STATUS_OF_TAKE_MISSION_CREATOR_PHOTO() { return YimMenu::NativeInvoker::Invoke<1004, int>(); }
	FORCEINLINE void FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO() { return YimMenu::NativeInvoker::Invoke<1005, void>(); }
	FORCEINLINE bool LOAD_MISSION_CREATOR_PHOTO(Any* p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<1006, bool>(p0, p1, p2, p3); }
	FORCEINLINE int GET_STATUS_OF_LOAD_MISSION_CREATOR_PHOTO(Any* p0) { return YimMenu::NativeInvoker::Invoke<1007, int>(p0); }
	FORCEINLINE bool BEGIN_CREATE_MISSION_CREATOR_PHOTO_PREVIEW() { return YimMenu::NativeInvoker::Invoke<1008, bool>(); }
	FORCEINLINE int GET_STATUS_OF_CREATE_MISSION_CREATOR_PHOTO_PREVIEW() { return YimMenu::NativeInvoker::Invoke<1009, int>(); }
	FORCEINLINE void FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO_PREVIEW() { return YimMenu::NativeInvoker::Invoke<1010, void>(); }
	FORCEINLINE bool BEGIN_TAKE_HIGH_QUALITY_PHOTO() { return YimMenu::NativeInvoker::Invoke<1011, bool>(); }
	FORCEINLINE int GET_STATUS_OF_TAKE_HIGH_QUALITY_PHOTO() { return YimMenu::NativeInvoker::Invoke<1012, int>(); }
	FORCEINLINE void FREE_MEMORY_FOR_HIGH_QUALITY_PHOTO() { return YimMenu::NativeInvoker::Invoke<1013, void>(); }
	FORCEINLINE void SET_TAKEN_PHOTO_IS_MUGSHOT(bool toggle) { return YimMenu::NativeInvoker::Invoke<1014, void>(toggle); }
	FORCEINLINE void SET_ARENA_THEME_AND_VARIATION_FOR_TAKEN_PHOTO(Any p0, int p1) { return YimMenu::NativeInvoker::Invoke<1015, void>(p0, p1); }
	FORCEINLINE void SET_ON_ISLAND_X_FOR_TAKEN_PHOTO(Any p0) { return YimMenu::NativeInvoker::Invoke<1016, void>(p0); }
	FORCEINLINE bool SAVE_HIGH_QUALITY_PHOTO(int unused) { return YimMenu::NativeInvoker::Invoke<1017, bool>(unused); }
	FORCEINLINE int GET_STATUS_OF_SAVE_HIGH_QUALITY_PHOTO() { return YimMenu::NativeInvoker::Invoke<1018, int>(); }
	FORCEINLINE bool BEGIN_CREATE_LOW_QUALITY_COPY_OF_PHOTO(Any p0) { return YimMenu::NativeInvoker::Invoke<1019, bool>(p0); }
	FORCEINLINE int GET_STATUS_OF_CREATE_LOW_QUALITY_COPY_OF_PHOTO(int p0) { return YimMenu::NativeInvoker::Invoke<1020, int>(p0); }
	FORCEINLINE void FREE_MEMORY_FOR_LOW_QUALITY_PHOTO() { return YimMenu::NativeInvoker::Invoke<1021, void>(); }
	FORCEINLINE void DRAW_LOW_QUALITY_PHOTO_TO_PHONE(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<1022, void>(p0, p1); }
	FORCEINLINE int GET_MAXIMUM_NUMBER_OF_PHOTOS() { return YimMenu::NativeInvoker::Invoke<1023, int>(); }
	FORCEINLINE int GET_MAXIMUM_NUMBER_OF_CLOUD_PHOTOS() { return YimMenu::NativeInvoker::Invoke<1024, int>(); }
	FORCEINLINE int GET_CURRENT_NUMBER_OF_CLOUD_PHOTOS() { return YimMenu::NativeInvoker::Invoke<1025, int>(); }
	FORCEINLINE bool QUEUE_OPERATION_TO_CREATE_SORTED_LIST_OF_PHOTOS(Any p0) { return YimMenu::NativeInvoker::Invoke<1026, bool>(p0); }
	FORCEINLINE int GET_STATUS_OF_SORTED_LIST_OPERATION(Any p0) { return YimMenu::NativeInvoker::Invoke<1027, int>(p0); }
	FORCEINLINE void CLEAR_STATUS_OF_SORTED_LIST_OPERATION() { return YimMenu::NativeInvoker::Invoke<1028, void>(); }
	FORCEINLINE bool DOES_THIS_PHOTO_SLOT_CONTAIN_A_VALID_PHOTO(Any p0) { return YimMenu::NativeInvoker::Invoke<1029, bool>(p0); }
	FORCEINLINE bool LOAD_HIGH_QUALITY_PHOTO(Any p0) { return YimMenu::NativeInvoker::Invoke<1030, bool>(p0); }
	FORCEINLINE int GET_LOAD_HIGH_QUALITY_PHOTO_STATUS(int p0) { return YimMenu::NativeInvoker::Invoke<1031, int>(p0); }
	FORCEINLINE void DRAW_LIGHT_WITH_RANGEEX(float x, float y, float z, int r, int g, int b, float range, float intensity, float shadow) { return YimMenu::NativeInvoker::Invoke<1032, void>(x, y, z, r, g, b, range, intensity, shadow); }
	FORCEINLINE void DRAW_LIGHT_WITH_RANGE(float posX, float posY, float posZ, int colorR, int colorG, int colorB, float range, float intensity) { return YimMenu::NativeInvoker::Invoke<1033, void>(posX, posY, posZ, colorR, colorG, colorB, range, intensity); }
	FORCEINLINE void DRAW_SPOT_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float hardness, float radius, float falloff) { return YimMenu::NativeInvoker::Invoke<1034, void>(posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, distance, brightness, hardness, radius, falloff); }
	FORCEINLINE void DRAW_SHADOWED_SPOT_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float roundness, float radius, float falloff, int shadowId) { return YimMenu::NativeInvoker::Invoke<1035, void>(posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, distance, brightness, roundness, radius, falloff, shadowId); }
	FORCEINLINE void FADE_UP_PED_LIGHT(float p0) { return YimMenu::NativeInvoker::Invoke<1036, void>(p0); }
	FORCEINLINE void UPDATE_LIGHTS_ON_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1037, void>(entity); }
	FORCEINLINE void SET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE(Any p0) { return YimMenu::NativeInvoker::Invoke<1038, void>(p0); }
	FORCEINLINE float GET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE() { return YimMenu::NativeInvoker::Invoke<1039, float>(); }
	FORCEINLINE void DRAW_MARKER(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, bool bobUpAndDown, bool faceCamera, int p19, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnts) { return YimMenu::NativeInvoker::Invoke<1040, void>(type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict, textureName, drawOnEnts); }
	FORCEINLINE void DRAW_MARKER_EX(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, bool bobUpAndDown, bool faceCamera, Any p19, bool rotate, const char* textureDict, const char* textureName, bool drawOnEnts, bool p24, bool p25) { return YimMenu::NativeInvoker::Invoke<1041, void>(type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict, textureName, drawOnEnts, p24, p25); }
	FORCEINLINE void DRAW_MARKER_SPHERE(float x, float y, float z, float radius, int red, int green, int blue, float alpha) { return YimMenu::NativeInvoker::Invoke<1042, void>(x, y, z, radius, red, green, blue, alpha); }
	FORCEINLINE int CREATE_CHECKPOINT(int type, float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float diameter, int red, int green, int blue, int alpha, int reserved) { return YimMenu::NativeInvoker::Invoke<1043, int>(type, posX1, posY1, posZ1, posX2, posY2, posZ2, diameter, red, green, blue, alpha, reserved); }
	FORCEINLINE void SET_CHECKPOINT_INSIDE_CYLINDER_HEIGHT_SCALE(int checkpoint, float scale) { return YimMenu::NativeInvoker::Invoke<1044, void>(checkpoint, scale); }
	FORCEINLINE void SET_CHECKPOINT_INSIDE_CYLINDER_SCALE(int checkpoint, float scale) { return YimMenu::NativeInvoker::Invoke<1045, void>(checkpoint, scale); }
	FORCEINLINE void SET_CHECKPOINT_CYLINDER_HEIGHT(int checkpoint, float nearHeight, float farHeight, float radius) { return YimMenu::NativeInvoker::Invoke<1046, void>(checkpoint, nearHeight, farHeight, radius); }
	FORCEINLINE void SET_CHECKPOINT_RGBA(int checkpoint, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1047, void>(checkpoint, red, green, blue, alpha); }
	FORCEINLINE void SET_CHECKPOINT_RGBA2(int checkpoint, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1048, void>(checkpoint, red, green, blue, alpha); }
	FORCEINLINE void SET_CHECKPOINT_CLIPPLANE_WITH_POS_NORM(int checkpoint, float posX, float posY, float posZ, float unkX, float unkY, float unkZ) { return YimMenu::NativeInvoker::Invoke<1049, void>(checkpoint, posX, posY, posZ, unkX, unkY, unkZ); }
	FORCEINLINE void SET_CHECKPOINT_FORCE_OLD_ARROW_POINTING(int checkpoint) { return YimMenu::NativeInvoker::Invoke<1050, void>(checkpoint); }
	FORCEINLINE void SET_CHECKPOINT_DECAL_ROT_ALIGNED_TO_CAMERA_ROT(int checkpoint) { return YimMenu::NativeInvoker::Invoke<1051, void>(checkpoint); }
	FORCEINLINE void SET_CHECKPOINT_FORCE_DIRECTION(int checkpoint) { return YimMenu::NativeInvoker::Invoke<1052, void>(checkpoint); }
	FORCEINLINE void SET_CHECKPOINT_DIRECTION(int checkpoint, float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<1053, void>(checkpoint, posX, posY, posZ); }
	FORCEINLINE void DELETE_CHECKPOINT(int checkpoint) { return YimMenu::NativeInvoker::Invoke<1054, void>(checkpoint); }
	FORCEINLINE void DONT_RENDER_IN_GAME_UI(bool p0) { return YimMenu::NativeInvoker::Invoke<1055, void>(p0); }
	FORCEINLINE void FORCE_RENDER_IN_GAME_UI(bool toggle) { return YimMenu::NativeInvoker::Invoke<1056, void>(toggle); }
	FORCEINLINE void REQUEST_STREAMED_TEXTURE_DICT(const char* textureDict, bool p1) { return YimMenu::NativeInvoker::Invoke<1057, void>(textureDict, p1); }
	FORCEINLINE bool HAS_STREAMED_TEXTURE_DICT_LOADED(const char* textureDict) { return YimMenu::NativeInvoker::Invoke<1058, bool>(textureDict); }
	FORCEINLINE void SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(const char* textureDict) { return YimMenu::NativeInvoker::Invoke<1059, void>(textureDict); }
	FORCEINLINE void DRAW_RECT(float x, float y, float width, float height, int r, int g, int b, int a, bool p8) { return YimMenu::NativeInvoker::Invoke<1060, void>(x, y, width, height, r, g, b, a, p8); }
	FORCEINLINE void SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(bool toggle) { return YimMenu::NativeInvoker::Invoke<1061, void>(toggle); }
	FORCEINLINE void SET_SCRIPT_GFX_DRAW_ORDER(int drawOrder) { return YimMenu::NativeInvoker::Invoke<1062, void>(drawOrder); }
	FORCEINLINE void SET_SCRIPT_GFX_ALIGN(int horizontalAlign, int verticalAlign) { return YimMenu::NativeInvoker::Invoke<1063, void>(horizontalAlign, verticalAlign); }
	FORCEINLINE void RESET_SCRIPT_GFX_ALIGN() { return YimMenu::NativeInvoker::Invoke<1064, void>(); }
	FORCEINLINE void SET_SCRIPT_GFX_ALIGN_PARAMS(float x, float y, float w, float h) { return YimMenu::NativeInvoker::Invoke<1065, void>(x, y, w, h); }
	FORCEINLINE void GET_SCRIPT_GFX_ALIGN_POSITION(float x, float y, float* calculatedX, float* calculatedY) { return YimMenu::NativeInvoker::Invoke<1066, void>(x, y, calculatedX, calculatedY); }
	FORCEINLINE float GET_SAFE_ZONE_SIZE() { return YimMenu::NativeInvoker::Invoke<1067, float>(); }
	FORCEINLINE void DRAW_SPRITE(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, bool p11, Any p12) { return YimMenu::NativeInvoker::Invoke<1068, void>(textureDict, textureName, screenX, screenY, width, height, heading, red, green, blue, alpha, p11, p12); }
	FORCEINLINE void DRAW_SPRITE_ARX(const char* textureDict, const char* textureName, float x, float y, float width, float height, float p6, int red, int green, int blue, int alpha, Any p11, Any p12) { return YimMenu::NativeInvoker::Invoke<1069, void>(textureDict, textureName, x, y, width, height, p6, red, green, blue, alpha, p11, p12); }
	FORCEINLINE void DRAW_SPRITE_NAMED_RENDERTARGET(const char* textureDict, const char* textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, Any p11) { return YimMenu::NativeInvoker::Invoke<1070, void>(textureDict, textureName, screenX, screenY, width, height, heading, red, green, blue, alpha, p11); }
	FORCEINLINE void DRAW_SPRITE_ARX_WITH_UV(const char* textureDict, const char* textureName, float x, float y, float width, float height, float u1, float v1, float u2, float v2, float heading, int red, int green, int blue, int alpha, Any p15) { return YimMenu::NativeInvoker::Invoke<1071, void>(textureDict, textureName, x, y, width, height, u1, v1, u2, v2, heading, red, green, blue, alpha, p15); }
	FORCEINLINE int ADD_ENTITY_ICON(Entity entity, const char* icon) { return YimMenu::NativeInvoker::Invoke<1072, int>(entity, icon); }
	FORCEINLINE void SET_ENTITY_ICON_VISIBILITY(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<1073, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_ICON_COLOR(Entity entity, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1074, void>(entity, red, green, blue, alpha); }
	FORCEINLINE void SET_DRAW_ORIGIN(float x, float y, float z, bool p3) { return YimMenu::NativeInvoker::Invoke<1075, void>(x, y, z, p3); }
	FORCEINLINE void CLEAR_DRAW_ORIGIN() { return YimMenu::NativeInvoker::Invoke<1076, void>(); }
	FORCEINLINE int SET_BINK_MOVIE(const char* name) { return YimMenu::NativeInvoker::Invoke<1077, int>(name); }
	FORCEINLINE void PLAY_BINK_MOVIE(int binkMovie) { return YimMenu::NativeInvoker::Invoke<1078, void>(binkMovie); }
	FORCEINLINE void STOP_BINK_MOVIE(int binkMovie) { return YimMenu::NativeInvoker::Invoke<1079, void>(binkMovie); }
	FORCEINLINE void RELEASE_BINK_MOVIE(int binkMovie) { return YimMenu::NativeInvoker::Invoke<1080, void>(binkMovie); }
	FORCEINLINE void DRAW_BINK_MOVIE(int binkMovie, float p1, float p2, float p3, float p4, float p5, int r, int g, int b, int a) { return YimMenu::NativeInvoker::Invoke<1081, void>(binkMovie, p1, p2, p3, p4, p5, r, g, b, a); }
	FORCEINLINE void SET_BINK_MOVIE_TIME(int binkMovie, float progress) { return YimMenu::NativeInvoker::Invoke<1082, void>(binkMovie, progress); }
	FORCEINLINE float GET_BINK_MOVIE_TIME(int binkMovie) { return YimMenu::NativeInvoker::Invoke<1083, float>(binkMovie); }
	FORCEINLINE void SET_BINK_MOVIE_VOLUME(int binkMovie, float value) { return YimMenu::NativeInvoker::Invoke<1084, void>(binkMovie, value); }
	FORCEINLINE void ATTACH_TV_AUDIO_TO_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1085, void>(entity); }
	FORCEINLINE void SET_BINK_MOVIE_AUDIO_FRONTEND(int binkMovie, bool p1) { return YimMenu::NativeInvoker::Invoke<1086, void>(binkMovie, p1); }
	FORCEINLINE void SET_TV_AUDIO_FRONTEND(bool toggle) { return YimMenu::NativeInvoker::Invoke<1087, void>(toggle); }
	FORCEINLINE void SET_BINK_SHOULD_SKIP(int binkMovie, bool bShouldSkip) { return YimMenu::NativeInvoker::Invoke<1088, void>(binkMovie, bShouldSkip); }
	FORCEINLINE int LOAD_MOVIE_MESH_SET(const char* movieMeshSetName) { return YimMenu::NativeInvoker::Invoke<1089, int>(movieMeshSetName); }
	FORCEINLINE void RELEASE_MOVIE_MESH_SET(int movieMeshSet) { return YimMenu::NativeInvoker::Invoke<1090, void>(movieMeshSet); }
	FORCEINLINE int QUERY_MOVIE_MESH_SET_STATE(Any p0) { return YimMenu::NativeInvoker::Invoke<1091, int>(p0); }
	FORCEINLINE void GET_SCREEN_RESOLUTION(int* x, int* y) { return YimMenu::NativeInvoker::Invoke<1092, void>(x, y); }
	FORCEINLINE void GET_ACTUAL_SCREEN_RESOLUTION(int* x, int* y) { return YimMenu::NativeInvoker::Invoke<1093, void>(x, y); }
	FORCEINLINE float GET_ASPECT_RATIO(bool b) { return YimMenu::NativeInvoker::Invoke<1094, float>(b); }
	FORCEINLINE float GET_SCREEN_ASPECT_RATIO() { return YimMenu::NativeInvoker::Invoke<1095, float>(); }
	FORCEINLINE bool GET_IS_WIDESCREEN() { return YimMenu::NativeInvoker::Invoke<1096, bool>(); }
	FORCEINLINE bool GET_IS_HIDEF() { return YimMenu::NativeInvoker::Invoke<1097, bool>(); }
	FORCEINLINE void ADJUST_NEXT_POS_SIZE_AS_NORMALIZED_16_9() { return YimMenu::NativeInvoker::Invoke<1098, void>(); }
	FORCEINLINE void SET_NIGHTVISION(bool toggle) { return YimMenu::NativeInvoker::Invoke<1099, void>(toggle); }
	FORCEINLINE bool GET_REQUESTINGNIGHTVISION() { return YimMenu::NativeInvoker::Invoke<1100, bool>(); }
	FORCEINLINE bool GET_USINGNIGHTVISION() { return YimMenu::NativeInvoker::Invoke<1101, bool>(); }
	FORCEINLINE void SET_EXPOSURETWEAK(bool toggle) { return YimMenu::NativeInvoker::Invoke<1102, void>(toggle); }
	FORCEINLINE void FORCE_EXPOSURE_READBACK(bool toggle) { return YimMenu::NativeInvoker::Invoke<1103, void>(toggle); }
	FORCEINLINE void OVERRIDE_NIGHTVISION_LIGHT_RANGE(float p0) { return YimMenu::NativeInvoker::Invoke<1104, void>(p0); }
	FORCEINLINE void SET_NOISEOVERIDE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1105, void>(toggle); }
	FORCEINLINE void SET_NOISINESSOVERIDE(float value) { return YimMenu::NativeInvoker::Invoke<1106, void>(value); }
	FORCEINLINE bool GET_SCREEN_COORD_FROM_WORLD_COORD(float worldX, float worldY, float worldZ, float* screenX, float* screenY) { return YimMenu::NativeInvoker::Invoke<1107, bool>(worldX, worldY, worldZ, screenX, screenY); }
	FORCEINLINE Vector3 GET_TEXTURE_RESOLUTION(const char* textureDict, const char* textureName) { return YimMenu::NativeInvoker::Invoke<1108, Vector3>(textureDict, textureName); }
	FORCEINLINE bool OVERRIDE_PED_CREW_LOGO_TEXTURE(Ped ped, const char* txd, const char* txn) { return YimMenu::NativeInvoker::Invoke<1109, bool>(ped, txd, txn); }
	FORCEINLINE void SET_DISTANCE_BLUR_STRENGTH_OVERRIDE(float p0) { return YimMenu::NativeInvoker::Invoke<1110, void>(p0); }
	FORCEINLINE void SET_FLASH(float p0, float p1, float fadeIn, float duration, float fadeOut) { return YimMenu::NativeInvoker::Invoke<1111, void>(p0, p1, fadeIn, duration, fadeOut); }
	FORCEINLINE void DISABLE_OCCLUSION_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1112, void>(); }
	FORCEINLINE void SET_ARTIFICIAL_LIGHTS_STATE(bool state) { return YimMenu::NativeInvoker::Invoke<1113, void>(state); }
	FORCEINLINE void SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1114, void>(toggle); }
	FORCEINLINE void DISABLE_HDTEX_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1115, void>(); }
	FORCEINLINE int CREATE_TRACKED_POINT() { return YimMenu::NativeInvoker::Invoke<1116, int>(); }
	FORCEINLINE void SET_TRACKED_POINT_INFO(int point, float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<1117, void>(point, x, y, z, radius); }
	FORCEINLINE bool IS_TRACKED_POINT_VISIBLE(int point) { return YimMenu::NativeInvoker::Invoke<1118, bool>(point); }
	FORCEINLINE void DESTROY_TRACKED_POINT(int point) { return YimMenu::NativeInvoker::Invoke<1119, void>(point); }
	FORCEINLINE int SET_GRASS_CULL_SPHERE(float p0, float p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<1120, int>(p0, p1, p2, p3); }
	FORCEINLINE void REMOVE_GRASS_CULL_SPHERE(int handle) { return YimMenu::NativeInvoker::Invoke<1121, void>(handle); }
	FORCEINLINE void PROCGRASS_ENABLE_CULLSPHERE(int handle, float x, float y, float z, float scale) { return YimMenu::NativeInvoker::Invoke<1122, void>(handle, x, y, z, scale); }
	FORCEINLINE void PROCGRASS_DISABLE_CULLSPHERE(int handle) { return YimMenu::NativeInvoker::Invoke<1123, void>(handle); }
	FORCEINLINE bool PROCGRASS_IS_CULLSPHERE_ENABLED(int handle) { return YimMenu::NativeInvoker::Invoke<1124, bool>(handle); }
	FORCEINLINE void PROCGRASS_ENABLE_AMBSCALESCAN() { return YimMenu::NativeInvoker::Invoke<1125, void>(); }
	FORCEINLINE void PROCGRASS_DISABLE_AMBSCALESCAN() { return YimMenu::NativeInvoker::Invoke<1126, void>(); }
	FORCEINLINE void DISABLE_PROCOBJ_CREATION() { return YimMenu::NativeInvoker::Invoke<1127, void>(); }
	FORCEINLINE void ENABLE_PROCOBJ_CREATION() { return YimMenu::NativeInvoker::Invoke<1128, void>(); }
	FORCEINLINE void GRASSBATCH_ENABLE_FLATTENING_EXT_IN_SPHERE(float x, float y, float z, Any p3, float p4, float p5, float p6, float scale) { return YimMenu::NativeInvoker::Invoke<1129, void>(x, y, z, p3, p4, p5, p6, scale); }
	FORCEINLINE void GRASSBATCH_ENABLE_FLATTENING_IN_SPHERE(float x, float y, float z, float radius, float p4, float p5, float p6) { return YimMenu::NativeInvoker::Invoke<1130, void>(x, y, z, radius, p4, p5, p6); }
	FORCEINLINE void GRASSBATCH_DISABLE_FLATTENING() { return YimMenu::NativeInvoker::Invoke<1131, void>(); }
	FORCEINLINE void CASCADE_SHADOWS_INIT_SESSION() { return YimMenu::NativeInvoker::Invoke<1132, void>(); }
	FORCEINLINE void CASCADE_SHADOWS_SET_CASCADE_BOUNDS(Any p0, bool p1, float p2, float p3, float p4, float p5, bool p6, float p7) { return YimMenu::NativeInvoker::Invoke<1133, void>(p0, p1, p2, p3, p4, p5, p6, p7); }
	FORCEINLINE void CASCADE_SHADOWS_SET_CASCADE_BOUNDS_SCALE(float p0) { return YimMenu::NativeInvoker::Invoke<1134, void>(p0); }
	FORCEINLINE void CASCADE_SHADOWS_SET_ENTITY_TRACKER_SCALE(float p0) { return YimMenu::NativeInvoker::Invoke<1135, void>(p0); }
	FORCEINLINE void CASCADE_SHADOWS_SET_SPLIT_Z_EXP_WEIGHT(float p0) { return YimMenu::NativeInvoker::Invoke<1136, void>(p0); }
	FORCEINLINE void CASCADE_SHADOWS_SET_BOUND_POSITION(Any p0) { return YimMenu::NativeInvoker::Invoke<1137, void>(p0); }
	FORCEINLINE void CASCADE_SHADOWS_ENABLE_ENTITY_TRACKER(bool toggle) { return YimMenu::NativeInvoker::Invoke<1138, void>(toggle); }
	FORCEINLINE void CASCADE_SHADOWS_SET_SCREEN_SIZE_CHECK_ENABLED(bool p0) { return YimMenu::NativeInvoker::Invoke<1139, void>(p0); }
	FORCEINLINE void CASCADE_SHADOWS_SET_SHADOW_SAMPLE_TYPE(const char* type) { return YimMenu::NativeInvoker::Invoke<1140, void>(type); }
	FORCEINLINE void CASCADE_SHADOWS_CLEAR_SHADOW_SAMPLE_TYPE() { return YimMenu::NativeInvoker::Invoke<1141, void>(); }
	FORCEINLINE void CASCADE_SHADOWS_SET_AIRCRAFT_MODE(bool p0) { return YimMenu::NativeInvoker::Invoke<1142, void>(p0); }
	FORCEINLINE void CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_MODE(bool p0) { return YimMenu::NativeInvoker::Invoke<1143, void>(p0); }
	FORCEINLINE void CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_VALUE(float p0) { return YimMenu::NativeInvoker::Invoke<1144, void>(p0); }
	FORCEINLINE void CASCADE_SHADOWS_ENABLE_FREEZER(bool p0) { return YimMenu::NativeInvoker::Invoke<1145, void>(p0); }
	FORCEINLINE void WATER_REFLECTION_SET_SCRIPT_OBJECT_VISIBILITY(Any p0) { return YimMenu::NativeInvoker::Invoke<1146, void>(p0); }
	FORCEINLINE void GOLF_TRAIL_SET_ENABLED(bool toggle) { return YimMenu::NativeInvoker::Invoke<1147, void>(toggle); }
	FORCEINLINE void GOLF_TRAIL_SET_PATH(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8) { return YimMenu::NativeInvoker::Invoke<1148, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void GOLF_TRAIL_SET_RADIUS(float p0, float p1, float p2) { return YimMenu::NativeInvoker::Invoke<1149, void>(p0, p1, p2); }
	FORCEINLINE void GOLF_TRAIL_SET_COLOUR(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11) { return YimMenu::NativeInvoker::Invoke<1150, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); }
	FORCEINLINE void GOLF_TRAIL_SET_TESSELLATION(int p0, int p1) { return YimMenu::NativeInvoker::Invoke<1151, void>(p0, p1); }
	FORCEINLINE void GOLF_TRAIL_SET_FIXED_CONTROL_POINT_ENABLE(bool p0) { return YimMenu::NativeInvoker::Invoke<1152, void>(p0); }
	FORCEINLINE void GOLF_TRAIL_SET_FIXED_CONTROL_POINT(int type, float xPos, float yPos, float zPos, float p4, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1153, void>(type, xPos, yPos, zPos, p4, red, green, blue, alpha); }
	FORCEINLINE void GOLF_TRAIL_SET_SHADER_PARAMS(float p0, float p1, float p2, float p3, float p4) { return YimMenu::NativeInvoker::Invoke<1154, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void GOLF_TRAIL_SET_FACING(bool p0) { return YimMenu::NativeInvoker::Invoke<1155, void>(p0); }
	FORCEINLINE float GOLF_TRAIL_GET_MAX_HEIGHT() { return YimMenu::NativeInvoker::Invoke<1156, float>(); }
	FORCEINLINE Vector3 GOLF_TRAIL_GET_VISUAL_CONTROL_POINT(int p0) { return YimMenu::NativeInvoker::Invoke<1157, Vector3>(p0); }
	FORCEINLINE void SET_SEETHROUGH(bool toggle) { return YimMenu::NativeInvoker::Invoke<1158, void>(toggle); }
	FORCEINLINE bool GET_USINGSEETHROUGH() { return YimMenu::NativeInvoker::Invoke<1159, bool>(); }
	FORCEINLINE void SEETHROUGH_RESET() { return YimMenu::NativeInvoker::Invoke<1160, void>(); }
	FORCEINLINE void SEETHROUGH_SET_FADE_STARTDISTANCE(float distance) { return YimMenu::NativeInvoker::Invoke<1161, void>(distance); }
	FORCEINLINE void SEETHROUGH_SET_FADE_ENDDISTANCE(float distance) { return YimMenu::NativeInvoker::Invoke<1162, void>(distance); }
	FORCEINLINE float SEETHROUGH_GET_MAX_THICKNESS() { return YimMenu::NativeInvoker::Invoke<1163, float>(); }
	FORCEINLINE void SEETHROUGH_SET_MAX_THICKNESS(float thickness) { return YimMenu::NativeInvoker::Invoke<1164, void>(thickness); }
	FORCEINLINE void SEETHROUGH_SET_NOISE_MIN(float amount) { return YimMenu::NativeInvoker::Invoke<1165, void>(amount); }
	FORCEINLINE void SEETHROUGH_SET_NOISE_MAX(float amount) { return YimMenu::NativeInvoker::Invoke<1166, void>(amount); }
	FORCEINLINE void SEETHROUGH_SET_HILIGHT_INTENSITY(float intensity) { return YimMenu::NativeInvoker::Invoke<1167, void>(intensity); }
	FORCEINLINE void SEETHROUGH_SET_HIGHLIGHT_NOISE(float noise) { return YimMenu::NativeInvoker::Invoke<1168, void>(noise); }
	FORCEINLINE void SEETHROUGH_SET_HEATSCALE(int index, float heatScale) { return YimMenu::NativeInvoker::Invoke<1169, void>(index, heatScale); }
	FORCEINLINE void SEETHROUGH_SET_COLOR_NEAR(int red, int green, int blue) { return YimMenu::NativeInvoker::Invoke<1170, void>(red, green, blue); }
	FORCEINLINE void SET_MOTIONBLUR_MAX_VEL_SCALER(float p0) { return YimMenu::NativeInvoker::Invoke<1171, void>(p0); }
	FORCEINLINE float GET_MOTIONBLUR_MAX_VEL_SCALER() { return YimMenu::NativeInvoker::Invoke<1172, float>(); }
	FORCEINLINE void SET_FORCE_MOTIONBLUR(bool toggle) { return YimMenu::NativeInvoker::Invoke<1173, void>(toggle); }
	FORCEINLINE void TOGGLE_PLAYER_DAMAGE_OVERLAY(bool toggle) { return YimMenu::NativeInvoker::Invoke<1174, void>(toggle); }
	FORCEINLINE void RESET_ADAPTATION(int p0) { return YimMenu::NativeInvoker::Invoke<1175, void>(p0); }
	FORCEINLINE bool TRIGGER_SCREENBLUR_FADE_IN(float transitionTime) { return YimMenu::NativeInvoker::Invoke<1176, bool>(transitionTime); }
	FORCEINLINE bool TRIGGER_SCREENBLUR_FADE_OUT(float transitionTime) { return YimMenu::NativeInvoker::Invoke<1177, bool>(transitionTime); }
	FORCEINLINE void DISABLE_SCREENBLUR_FADE() { return YimMenu::NativeInvoker::Invoke<1178, void>(); }
	FORCEINLINE float GET_SCREENBLUR_FADE_CURRENT_TIME() { return YimMenu::NativeInvoker::Invoke<1179, float>(); }
	FORCEINLINE bool IS_SCREENBLUR_FADE_RUNNING() { return YimMenu::NativeInvoker::Invoke<1180, bool>(); }
	FORCEINLINE void TOGGLE_PAUSED_RENDERPHASES(bool toggle) { return YimMenu::NativeInvoker::Invoke<1181, void>(toggle); }
	FORCEINLINE bool GET_TOGGLE_PAUSED_RENDERPHASES_STATUS() { return YimMenu::NativeInvoker::Invoke<1182, bool>(); }
	FORCEINLINE void RESET_PAUSED_RENDERPHASES() { return YimMenu::NativeInvoker::Invoke<1183, void>(); }
	FORCEINLINE void GRAB_PAUSEMENU_OWNERSHIP() { return YimMenu::NativeInvoker::Invoke<1184, void>(); }
	FORCEINLINE void SET_HIDOF_OVERRIDE(bool p0, bool p1, float nearplaneOut, float nearplaneIn, float farplaneOut, float farplaneIn) { return YimMenu::NativeInvoker::Invoke<1185, void>(p0, p1, nearplaneOut, nearplaneIn, farplaneOut, farplaneIn); }
	FORCEINLINE void SET_LOCK_ADAPTIVE_DOF_DISTANCE(bool p0) { return YimMenu::NativeInvoker::Invoke<1186, void>(p0); }
	FORCEINLINE bool PHONEPHOTOEDITOR_TOGGLE(bool p0) { return YimMenu::NativeInvoker::Invoke<1187, bool>(p0); }
	FORCEINLINE bool PHONEPHOTOEDITOR_IS_ACTIVE() { return YimMenu::NativeInvoker::Invoke<1188, bool>(); }
	FORCEINLINE bool PHONEPHOTOEDITOR_SET_FRAME_TXD(const char* textureDict, bool p1) { return YimMenu::NativeInvoker::Invoke<1189, bool>(textureDict, p1); }
	FORCEINLINE bool START_PARTICLE_FX_NON_LOOPED_AT_COORD(const char* effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis) { return YimMenu::NativeInvoker::Invoke<1190, bool>(effectName, xPos, yPos, zPos, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis); }
	FORCEINLINE bool START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(const char* effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11) { return YimMenu::NativeInvoker::Invoke<1191, bool>(effectName, xPos, yPos, zPos, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p11); }
	FORCEINLINE bool START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ) { return YimMenu::NativeInvoker::Invoke<1192, bool>(effectName, ped, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ); }
	FORCEINLINE bool START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ) { return YimMenu::NativeInvoker::Invoke<1193, bool>(effectName, ped, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ); }
	FORCEINLINE bool START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, bool axisX, bool axisY, bool axisZ) { return YimMenu::NativeInvoker::Invoke<1194, bool>(effectName, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scale, axisX, axisY, axisZ); }
	FORCEINLINE bool START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, bool axisX, bool axisY, bool axisZ) { return YimMenu::NativeInvoker::Invoke<1195, bool>(effectName, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scale, axisX, axisY, axisZ); }
	FORCEINLINE bool START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ) { return YimMenu::NativeInvoker::Invoke<1196, bool>(effectName, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ); }
	FORCEINLINE void SET_PARTICLE_FX_NON_LOOPED_COLOUR(float r, float g, float b) { return YimMenu::NativeInvoker::Invoke<1197, void>(r, g, b); }
	FORCEINLINE void SET_PARTICLE_FX_NON_LOOPED_ALPHA(float alpha) { return YimMenu::NativeInvoker::Invoke<1198, void>(alpha); }
	FORCEINLINE void SET_PARTICLE_FX_NON_LOOPED_SCALE(float scale) { return YimMenu::NativeInvoker::Invoke<1199, void>(scale); }
	FORCEINLINE void SET_PARTICLE_FX_NON_LOOPED_EMITTER_SIZE(float p0, float p1, float scale) { return YimMenu::NativeInvoker::Invoke<1200, void>(p0, p1, scale); }
	FORCEINLINE void SET_PARTICLE_FX_FORCE_VEHICLE_INTERIOR(bool toggle) { return YimMenu::NativeInvoker::Invoke<1201, void>(toggle); }
	FORCEINLINE int START_PARTICLE_FX_LOOPED_AT_COORD(const char* effectName, float x, float y, float z, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11) { return YimMenu::NativeInvoker::Invoke<1202, int>(effectName, x, y, z, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p11); }
	FORCEINLINE int START_PARTICLE_FX_LOOPED_ON_PED_BONE(const char* effectName, Ped ped, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis) { return YimMenu::NativeInvoker::Invoke<1203, int>(effectName, ped, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis); }
	FORCEINLINE int START_PARTICLE_FX_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis) { return YimMenu::NativeInvoker::Invoke<1204, int>(effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis); }
	FORCEINLINE int START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis) { return YimMenu::NativeInvoker::Invoke<1205, int>(effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis); }
	FORCEINLINE int START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, float r, float g, float b, float a) { return YimMenu::NativeInvoker::Invoke<1206, int>(effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, r, g, b, a); }
	FORCEINLINE int START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(const char* effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis, float r, float g, float b, float a) { return YimMenu::NativeInvoker::Invoke<1207, int>(effectName, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis, r, g, b, a); }
	FORCEINLINE void STOP_PARTICLE_FX_LOOPED(int ptfxHandle, bool p1) { return YimMenu::NativeInvoker::Invoke<1208, void>(ptfxHandle, p1); }
	FORCEINLINE void REMOVE_PARTICLE_FX(int ptfxHandle, bool p1) { return YimMenu::NativeInvoker::Invoke<1209, void>(ptfxHandle, p1); }
	FORCEINLINE void REMOVE_PARTICLE_FX_FROM_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1210, void>(entity); }
	FORCEINLINE void REMOVE_PARTICLE_FX_IN_RANGE(float X, float Y, float Z, float radius) { return YimMenu::NativeInvoker::Invoke<1211, void>(X, Y, Z, radius); }
	FORCEINLINE void FORCE_PARTICLE_FX_IN_VEHICLE_INTERIOR(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<1212, void>(p0, p1); }
	FORCEINLINE bool DOES_PARTICLE_FX_LOOPED_EXIST(int ptfxHandle) { return YimMenu::NativeInvoker::Invoke<1213, bool>(ptfxHandle); }
	FORCEINLINE void SET_PARTICLE_FX_LOOPED_OFFSETS(int ptfxHandle, float x, float y, float z, float rotX, float rotY, float rotZ) { return YimMenu::NativeInvoker::Invoke<1214, void>(ptfxHandle, x, y, z, rotX, rotY, rotZ); }
	FORCEINLINE void SET_PARTICLE_FX_LOOPED_EVOLUTION(int ptfxHandle, const char* propertyName, float amount, bool noNetwork) { return YimMenu::NativeInvoker::Invoke<1215, void>(ptfxHandle, propertyName, amount, noNetwork); }
	FORCEINLINE void SET_PARTICLE_FX_LOOPED_COLOUR(int ptfxHandle, float r, float g, float b, bool p4) { return YimMenu::NativeInvoker::Invoke<1216, void>(ptfxHandle, r, g, b, p4); }
	FORCEINLINE void SET_PARTICLE_FX_LOOPED_ALPHA(int ptfxHandle, float alpha) { return YimMenu::NativeInvoker::Invoke<1217, void>(ptfxHandle, alpha); }
	FORCEINLINE void SET_PARTICLE_FX_LOOPED_SCALE(int ptfxHandle, float scale) { return YimMenu::NativeInvoker::Invoke<1218, void>(ptfxHandle, scale); }
	FORCEINLINE void SET_PARTICLE_FX_LOOPED_FAR_CLIP_DIST(int ptfxHandle, float range) { return YimMenu::NativeInvoker::Invoke<1219, void>(ptfxHandle, range); }
	FORCEINLINE void SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(bool p0) { return YimMenu::NativeInvoker::Invoke<1220, void>(p0); }
	FORCEINLINE void SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<1221, void>(vehicle, p1); }
	FORCEINLINE void SET_PARTICLE_FX_SHOOTOUT_BOAT(Any p0) { return YimMenu::NativeInvoker::Invoke<1222, void>(p0); }
	FORCEINLINE void CLEAR_PARTICLE_FX_SHOOTOUT_BOAT() { return YimMenu::NativeInvoker::Invoke<1223, void>(); }
	FORCEINLINE void SET_PARTICLE_FX_BLOOD_SCALE(Any p0) { return YimMenu::NativeInvoker::Invoke<1224, void>(p0); }
	FORCEINLINE void DISABLE_IN_WATER_PTFX(bool toggle) { return YimMenu::NativeInvoker::Invoke<1225, void>(toggle); }
	FORCEINLINE void DISABLE_DOWNWASH_PTFX(bool toggle) { return YimMenu::NativeInvoker::Invoke<1226, void>(toggle); }
	FORCEINLINE void SET_PARTICLE_FX_SLIPSTREAM_LODRANGE_SCALE(float scale) { return YimMenu::NativeInvoker::Invoke<1227, void>(scale); }
	FORCEINLINE void ENABLE_CLOWN_BLOOD_VFX(bool toggle) { return YimMenu::NativeInvoker::Invoke<1228, void>(toggle); }
	FORCEINLINE void ENABLE_ALIEN_BLOOD_VFX(bool toggle) { return YimMenu::NativeInvoker::Invoke<1229, void>(toggle); }
	FORCEINLINE void SET_PARTICLE_FX_BULLET_IMPACT_SCALE(float scale) { return YimMenu::NativeInvoker::Invoke<1230, void>(scale); }
	FORCEINLINE void SET_PARTICLE_FX_BULLET_IMPACT_LODRANGE_SCALE(float p0) { return YimMenu::NativeInvoker::Invoke<1231, void>(p0); }
	FORCEINLINE void SET_PARTICLE_FX_BULLET_TRACE_NO_ANGLE_REJECT(bool p0) { return YimMenu::NativeInvoker::Invoke<1232, void>(p0); }
	FORCEINLINE void SET_PARTICLE_FX_BANG_SCRAPE_LODRANGE_SCALE(float p0) { return YimMenu::NativeInvoker::Invoke<1233, void>(p0); }
	FORCEINLINE void SET_PARTICLE_FX_FOOT_LODRANGE_SCALE(float p0) { return YimMenu::NativeInvoker::Invoke<1234, void>(p0); }
	FORCEINLINE void SET_PARTICLE_FX_FOOT_OVERRIDE_NAME(const char* p0) { return YimMenu::NativeInvoker::Invoke<1235, void>(p0); }
	FORCEINLINE void SET_SKIDMARK_RANGE_SCALE(float scale) { return YimMenu::NativeInvoker::Invoke<1236, void>(scale); }
	FORCEINLINE void SET_PTFX_FORCE_VEHICLE_INTERIOR_FLAG(Any p0) { return YimMenu::NativeInvoker::Invoke<1237, void>(p0); }
	FORCEINLINE void REGISTER_POSTFX_BULLET_IMPACT(float weaponWorldPosX, float weaponWorldPosY, float weaponWorldPosZ, float intensity) { return YimMenu::NativeInvoker::Invoke<1238, void>(weaponWorldPosX, weaponWorldPosY, weaponWorldPosZ, intensity); }
	FORCEINLINE void FORCE_POSTFX_BULLET_IMPACTS_AFTER_HUD(bool p0) { return YimMenu::NativeInvoker::Invoke<1239, void>(p0); }
	FORCEINLINE void USE_PARTICLE_FX_ASSET(const char* name) { return YimMenu::NativeInvoker::Invoke<1240, void>(name); }
	FORCEINLINE void SET_PARTICLE_FX_OVERRIDE(const char* oldAsset, const char* newAsset) { return YimMenu::NativeInvoker::Invoke<1241, void>(oldAsset, newAsset); }
	FORCEINLINE void RESET_PARTICLE_FX_OVERRIDE(const char* name) { return YimMenu::NativeInvoker::Invoke<1242, void>(name); }
	FORCEINLINE void SET_WEATHER_PTFX_USE_OVERRIDE_SETTINGS(bool p0) { return YimMenu::NativeInvoker::Invoke<1243, void>(p0); }
	FORCEINLINE void SET_WEATHER_PTFX_OVERRIDE_CURR_LEVEL(float p0) { return YimMenu::NativeInvoker::Invoke<1244, void>(p0); }
	FORCEINLINE void WASH_DECALS_IN_RANGE(float x, float y, float z, float range, float p4) { return YimMenu::NativeInvoker::Invoke<1245, void>(x, y, z, range, p4); }
	FORCEINLINE void WASH_DECALS_FROM_VEHICLE(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<1246, void>(vehicle, p1); }
	FORCEINLINE void FADE_DECALS_IN_RANGE(float x, float y, float z, float p3, float p4) { return YimMenu::NativeInvoker::Invoke<1247, void>(x, y, z, p3, p4); }
	FORCEINLINE void REMOVE_DECALS_IN_RANGE(float x, float y, float z, float range) { return YimMenu::NativeInvoker::Invoke<1248, void>(x, y, z, range); }
	FORCEINLINE void REMOVE_DECALS_FROM_OBJECT(Object obj) { return YimMenu::NativeInvoker::Invoke<1249, void>(obj); }
	FORCEINLINE void REMOVE_DECALS_FROM_OBJECT_FACING(Object obj, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1250, void>(obj, x, y, z); }
	FORCEINLINE void REMOVE_DECALS_FROM_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<1251, void>(vehicle); }
	FORCEINLINE int ADD_DECAL(int decalType, float posX, float posY, float posZ, float p4, float p5, float p6, float p7, float p8, float p9, float width, float height, float rCoef, float gCoef, float bCoef, float opacity, float timeout, bool p17, bool p18, bool p19) { return YimMenu::NativeInvoker::Invoke<1252, int>(decalType, posX, posY, posZ, p4, p5, p6, p7, p8, p9, width, height, rCoef, gCoef, bCoef, opacity, timeout, p17, p18, p19); }
	FORCEINLINE int ADD_PETROL_DECAL(float x, float y, float z, float groundLvl, float width, float transparency) { return YimMenu::NativeInvoker::Invoke<1253, int>(x, y, z, groundLvl, width, transparency); }
	FORCEINLINE int ADD_OIL_DECAL(float x, float y, float z, float groundLvl, float width, float transparency) { return YimMenu::NativeInvoker::Invoke<1254, int>(x, y, z, groundLvl, width, transparency); }
	FORCEINLINE void START_PETROL_TRAIL_DECALS(float p0) { return YimMenu::NativeInvoker::Invoke<1255, void>(p0); }
	FORCEINLINE void ADD_PETROL_TRAIL_DECAL_INFO(float x, float y, float z, float p3) { return YimMenu::NativeInvoker::Invoke<1256, void>(x, y, z, p3); }
	FORCEINLINE void END_PETROL_TRAIL_DECALS() { return YimMenu::NativeInvoker::Invoke<1257, void>(); }
	FORCEINLINE void REMOVE_DECAL(int decal) { return YimMenu::NativeInvoker::Invoke<1258, void>(decal); }
	FORCEINLINE bool IS_DECAL_ALIVE(int decal) { return YimMenu::NativeInvoker::Invoke<1259, bool>(decal); }
	FORCEINLINE float GET_DECAL_WASH_LEVEL(int decal) { return YimMenu::NativeInvoker::Invoke<1260, float>(decal); }
	FORCEINLINE void SET_DISABLE_PETROL_DECALS_IGNITING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1261, void>(); }
	FORCEINLINE void SET_DISABLE_PETROL_DECALS_RECYCLING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1262, void>(); }
	FORCEINLINE void SET_DISABLE_DECAL_RENDERING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1263, void>(); }
	FORCEINLINE bool GET_IS_PETROL_DECAL_IN_RANGE(float xCoord, float yCoord, float zCoord, float radius) { return YimMenu::NativeInvoker::Invoke<1264, bool>(xCoord, yCoord, zCoord, radius); }
	FORCEINLINE void PATCH_DECAL_DIFFUSE_MAP(int decalType, const char* textureDict, const char* textureName) { return YimMenu::NativeInvoker::Invoke<1265, void>(decalType, textureDict, textureName); }
	FORCEINLINE void UNPATCH_DECAL_DIFFUSE_MAP(int decalType) { return YimMenu::NativeInvoker::Invoke<1266, void>(decalType); }
	FORCEINLINE void MOVE_VEHICLE_DECALS(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<1267, void>(p0, p1); }
	FORCEINLINE bool ADD_VEHICLE_CREW_EMBLEM(Vehicle vehicle, Ped ped, int boneIndex, float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3, float scale, Any p13, int alpha) { return YimMenu::NativeInvoker::Invoke<1268, bool>(vehicle, ped, boneIndex, x1, x2, x3, y1, y2, y3, z1, z2, z3, scale, p13, alpha); }
	FORCEINLINE bool ABORT_VEHICLE_CREW_EMBLEM_REQUEST(int* p0) { return YimMenu::NativeInvoker::Invoke<1269, bool>(p0); }
	FORCEINLINE void REMOVE_VEHICLE_CREW_EMBLEM(Vehicle vehicle, int p1) { return YimMenu::NativeInvoker::Invoke<1270, void>(vehicle, p1); }
	FORCEINLINE int GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE(Vehicle vehicle, int p1) { return YimMenu::NativeInvoker::Invoke<1271, int>(vehicle, p1); }
	FORCEINLINE bool DOES_VEHICLE_HAVE_CREW_EMBLEM(Vehicle vehicle, int p1) { return YimMenu::NativeInvoker::Invoke<1272, bool>(vehicle, p1); }
	FORCEINLINE void DISABLE_COMPOSITE_SHOTGUN_DECALS(bool toggle) { return YimMenu::NativeInvoker::Invoke<1273, void>(toggle); }
	FORCEINLINE void DISABLE_SCUFF_DECALS(bool toggle) { return YimMenu::NativeInvoker::Invoke<1274, void>(toggle); }
	FORCEINLINE void SET_DECAL_BULLET_IMPACT_RANGE_SCALE(float p0) { return YimMenu::NativeInvoker::Invoke<1275, void>(p0); }
	FORCEINLINE void OVERRIDE_INTERIOR_SMOKE_NAME(const char* name) { return YimMenu::NativeInvoker::Invoke<1276, void>(name); }
	FORCEINLINE void OVERRIDE_INTERIOR_SMOKE_LEVEL(float level) { return YimMenu::NativeInvoker::Invoke<1277, void>(level); }
	FORCEINLINE void OVERRIDE_INTERIOR_SMOKE_END() { return YimMenu::NativeInvoker::Invoke<1278, void>(); }
	FORCEINLINE void REGISTER_NOIR_LENS_EFFECT() { return YimMenu::NativeInvoker::Invoke<1279, void>(); }
	FORCEINLINE void DISABLE_VEHICLE_DISTANTLIGHTS(bool toggle) { return YimMenu::NativeInvoker::Invoke<1280, void>(toggle); }
	FORCEINLINE void RENDER_SHADOWED_LIGHTS_WITH_NO_SHADOWS(bool p0) { return YimMenu::NativeInvoker::Invoke<1281, void>(p0); }
	FORCEINLINE void REQUEST_EARLY_LIGHT_CHECK() { return YimMenu::NativeInvoker::Invoke<1282, void>(); }
	FORCEINLINE void USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(bool toggle) { return YimMenu::NativeInvoker::Invoke<1283, void>(toggle); }
	FORCEINLINE void USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(bool toggle) { return YimMenu::NativeInvoker::Invoke<1284, void>(toggle); }
	FORCEINLINE void DISABLE_REGION_VFX(Any p0) { return YimMenu::NativeInvoker::Invoke<1285, void>(p0); }
	FORCEINLINE void PRESET_INTERIOR_AMBIENT_CACHE(const char* timecycleModifierName) { return YimMenu::NativeInvoker::Invoke<1286, void>(timecycleModifierName); }
	FORCEINLINE void SET_TIMECYCLE_MODIFIER(const char* modifierName) { return YimMenu::NativeInvoker::Invoke<1287, void>(modifierName); }
	FORCEINLINE void SET_TIMECYCLE_MODIFIER_STRENGTH(float strength) { return YimMenu::NativeInvoker::Invoke<1288, void>(strength); }
	FORCEINLINE void SET_TRANSITION_TIMECYCLE_MODIFIER(const char* modifierName, float transition) { return YimMenu::NativeInvoker::Invoke<1289, void>(modifierName, transition); }
	FORCEINLINE void SET_TRANSITION_OUT_OF_TIMECYCLE_MODIFIER(float strength) { return YimMenu::NativeInvoker::Invoke<1290, void>(strength); }
	FORCEINLINE void CLEAR_TIMECYCLE_MODIFIER() { return YimMenu::NativeInvoker::Invoke<1291, void>(); }
	FORCEINLINE int GET_TIMECYCLE_MODIFIER_INDEX() { return YimMenu::NativeInvoker::Invoke<1292, int>(); }
	FORCEINLINE int GET_TIMECYCLE_TRANSITION_MODIFIER_INDEX() { return YimMenu::NativeInvoker::Invoke<1293, int>(); }
	FORCEINLINE bool GET_IS_TIMECYCLE_TRANSITIONING_OUT() { return YimMenu::NativeInvoker::Invoke<1294, bool>(); }
	FORCEINLINE void PUSH_TIMECYCLE_MODIFIER() { return YimMenu::NativeInvoker::Invoke<1295, void>(); }
	FORCEINLINE void POP_TIMECYCLE_MODIFIER() { return YimMenu::NativeInvoker::Invoke<1296, void>(); }
	FORCEINLINE void SET_CURRENT_PLAYER_TCMODIFIER(const char* modifierName) { return YimMenu::NativeInvoker::Invoke<1297, void>(modifierName); }
	FORCEINLINE void SET_PLAYER_TCMODIFIER_TRANSITION(float value) { return YimMenu::NativeInvoker::Invoke<1298, void>(value); }
	FORCEINLINE void SET_NEXT_PLAYER_TCMODIFIER(const char* modifierName) { return YimMenu::NativeInvoker::Invoke<1299, void>(modifierName); }
	FORCEINLINE void ADD_TCMODIFIER_OVERRIDE(const char* modifierName1, const char* modifierName2) { return YimMenu::NativeInvoker::Invoke<1300, void>(modifierName1, modifierName2); }
	FORCEINLINE void CLEAR_ALL_TCMODIFIER_OVERRIDES(const char* p0) { return YimMenu::NativeInvoker::Invoke<1301, void>(p0); }
	FORCEINLINE void SET_EXTRA_TCMODIFIER(const char* modifierName) { return YimMenu::NativeInvoker::Invoke<1302, void>(modifierName); }
	FORCEINLINE void CLEAR_EXTRA_TCMODIFIER() { return YimMenu::NativeInvoker::Invoke<1303, void>(); }
	FORCEINLINE int GET_EXTRA_TCMODIFIER() { return YimMenu::NativeInvoker::Invoke<1304, int>(); }
	FORCEINLINE void ENABLE_MOON_CYCLE_OVERRIDE(float strength) { return YimMenu::NativeInvoker::Invoke<1305, void>(strength); }
	FORCEINLINE void DISABLE_MOON_CYCLE_OVERRIDE() { return YimMenu::NativeInvoker::Invoke<1306, void>(); }
	FORCEINLINE int REQUEST_SCALEFORM_MOVIE(const char* scaleformName) { return YimMenu::NativeInvoker::Invoke<1307, int>(scaleformName); }
	FORCEINLINE int REQUEST_SCALEFORM_MOVIE_WITH_IGNORE_SUPER_WIDESCREEN(const char* scaleformName) { return YimMenu::NativeInvoker::Invoke<1308, int>(scaleformName); }
	FORCEINLINE int REQUEST_SCALEFORM_MOVIE_INSTANCE(const char* scaleformName) { return YimMenu::NativeInvoker::Invoke<1309, int>(scaleformName); }
	FORCEINLINE int REQUEST_SCALEFORM_MOVIE_SKIP_RENDER_WHILE_PAUSED(const char* scaleformName) { return YimMenu::NativeInvoker::Invoke<1310, int>(scaleformName); }
	FORCEINLINE bool HAS_SCALEFORM_MOVIE_LOADED(int scaleformHandle) { return YimMenu::NativeInvoker::Invoke<1311, bool>(scaleformHandle); }
	FORCEINLINE bool IS_ACTIVE_SCALEFORM_MOVIE_DELETING(int val) { return YimMenu::NativeInvoker::Invoke<1312, bool>(val); }
	FORCEINLINE bool IS_SCALEFORM_MOVIE_DELETING(int val) { return YimMenu::NativeInvoker::Invoke<1313, bool>(val); }
	FORCEINLINE bool HAS_SCALEFORM_MOVIE_FILENAME_LOADED(const char* scaleformName) { return YimMenu::NativeInvoker::Invoke<1314, bool>(scaleformName); }
	FORCEINLINE bool HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT(int scaleformHandle) { return YimMenu::NativeInvoker::Invoke<1315, bool>(scaleformHandle); }
	FORCEINLINE void SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(int* scaleformHandle) { return YimMenu::NativeInvoker::Invoke<1316, void>(scaleformHandle); }
	FORCEINLINE void SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME(int scaleform, bool toggle) { return YimMenu::NativeInvoker::Invoke<1317, void>(scaleform, toggle); }
	FORCEINLINE void SET_SCALEFORM_MOVIE_TO_USE_LARGE_RT(int scaleformHandle, bool toggle) { return YimMenu::NativeInvoker::Invoke<1318, void>(scaleformHandle, toggle); }
	FORCEINLINE void SET_SCALEFORM_MOVIE_TO_USE_SUPER_LARGE_RT(int scaleformHandle, bool toggle) { return YimMenu::NativeInvoker::Invoke<1319, void>(scaleformHandle, toggle); }
	FORCEINLINE void DRAW_SCALEFORM_MOVIE(int scaleformHandle, float x, float y, float width, float height, int red, int green, int blue, int alpha, int p9) { return YimMenu::NativeInvoker::Invoke<1320, void>(scaleformHandle, x, y, width, height, red, green, blue, alpha, p9); }
	FORCEINLINE void DRAW_SCALEFORM_MOVIE_FULLSCREEN(int scaleform, int red, int green, int blue, int alpha, int p5) { return YimMenu::NativeInvoker::Invoke<1321, void>(scaleform, red, green, blue, alpha, p5); }
	FORCEINLINE void DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(int scaleform1, int scaleform2, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1322, void>(scaleform1, scaleform2, red, green, blue, alpha); }
	FORCEINLINE void DRAW_SCALEFORM_MOVIE_3D(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<1323, void>(scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, rotationOrder); }
	FORCEINLINE void DRAW_SCALEFORM_MOVIE_3D_SOLID(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<1324, void>(scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, rotationOrder); }
	FORCEINLINE void CALL_SCALEFORM_MOVIE_METHOD(int scaleform, const char* method) { return YimMenu::NativeInvoker::Invoke<1325, void>(scaleform, method); }
	FORCEINLINE void CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER(int scaleform, const char* methodName, float param1, float param2, float param3, float param4, float param5) { return YimMenu::NativeInvoker::Invoke<1326, void>(scaleform, methodName, param1, param2, param3, param4, param5); }
	FORCEINLINE void CALL_SCALEFORM_MOVIE_METHOD_WITH_STRING(int scaleform, const char* methodName, const char* param1, const char* param2, const char* param3, const char* param4, const char* param5) { return YimMenu::NativeInvoker::Invoke<1327, void>(scaleform, methodName, param1, param2, param3, param4, param5); }
	FORCEINLINE void CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER_AND_STRING(int scaleform, const char* methodName, float floatParam1, float floatParam2, float floatParam3, float floatParam4, float floatParam5, const char* stringParam1, const char* stringParam2, const char* stringParam3, const char* stringParam4, const char* stringParam5) { return YimMenu::NativeInvoker::Invoke<1328, void>(scaleform, methodName, floatParam1, floatParam2, floatParam3, floatParam4, floatParam5, stringParam1, stringParam2, stringParam3, stringParam4, stringParam5); }
	FORCEINLINE bool BEGIN_SCALEFORM_SCRIPT_HUD_MOVIE_METHOD(int hudComponent, const char* methodName) { return YimMenu::NativeInvoker::Invoke<1329, bool>(hudComponent, methodName); }
	FORCEINLINE bool BEGIN_SCALEFORM_MOVIE_METHOD(int scaleform, const char* methodName) { return YimMenu::NativeInvoker::Invoke<1330, bool>(scaleform, methodName); }
	FORCEINLINE bool BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND(const char* methodName) { return YimMenu::NativeInvoker::Invoke<1331, bool>(methodName); }
	FORCEINLINE bool BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER(const char* methodName) { return YimMenu::NativeInvoker::Invoke<1332, bool>(methodName); }
	FORCEINLINE void END_SCALEFORM_MOVIE_METHOD() { return YimMenu::NativeInvoker::Invoke<1333, void>(); }
	FORCEINLINE int END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE() { return YimMenu::NativeInvoker::Invoke<1334, int>(); }
	FORCEINLINE bool IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY(int methodReturn) { return YimMenu::NativeInvoker::Invoke<1335, bool>(methodReturn); }
	FORCEINLINE int GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT(int methodReturn) { return YimMenu::NativeInvoker::Invoke<1336, int>(methodReturn); }
	FORCEINLINE bool GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL(int methodReturn) { return YimMenu::NativeInvoker::Invoke<1337, bool>(methodReturn); }
	FORCEINLINE const char* GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING(int methodReturn) { return YimMenu::NativeInvoker::Invoke<1338, const char*>(methodReturn); }
	FORCEINLINE void SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(int value) { return YimMenu::NativeInvoker::Invoke<1339, void>(value); }
	FORCEINLINE void SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(float value) { return YimMenu::NativeInvoker::Invoke<1340, void>(value); }
	FORCEINLINE void SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(bool value) { return YimMenu::NativeInvoker::Invoke<1341, void>(value); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_SCALEFORM_STRING(const char* componentType) { return YimMenu::NativeInvoker::Invoke<1342, void>(componentType); }
	FORCEINLINE void END_TEXT_COMMAND_SCALEFORM_STRING() { return YimMenu::NativeInvoker::Invoke<1343, void>(); }
	FORCEINLINE void END_TEXT_COMMAND_UNPARSED_SCALEFORM_STRING() { return YimMenu::NativeInvoker::Invoke<1344, void>(); }
	FORCEINLINE void SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(const char* string) { return YimMenu::NativeInvoker::Invoke<1345, void>(string); }
	FORCEINLINE void SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(const char* string) { return YimMenu::NativeInvoker::Invoke<1346, void>(string); }
	FORCEINLINE void SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(const char* string) { return YimMenu::NativeInvoker::Invoke<1347, void>(string); }
	FORCEINLINE bool DOES_LATEST_BRIEF_STRING_EXIST(int p0) { return YimMenu::NativeInvoker::Invoke<1348, bool>(p0); }
	FORCEINLINE void SCALEFORM_MOVIE_METHOD_ADD_PARAM_LATEST_BRIEF_STRING(int value) { return YimMenu::NativeInvoker::Invoke<1349, void>(value); }
	FORCEINLINE void REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE(int hudComponent) { return YimMenu::NativeInvoker::Invoke<1350, void>(hudComponent); }
	FORCEINLINE bool HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED(int hudComponent) { return YimMenu::NativeInvoker::Invoke<1351, bool>(hudComponent); }
	FORCEINLINE void REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE(int hudComponent) { return YimMenu::NativeInvoker::Invoke<1352, void>(hudComponent); }
	FORCEINLINE bool PASS_KEYBOARD_INPUT_TO_SCALEFORM(int scaleformHandle) { return YimMenu::NativeInvoker::Invoke<1353, bool>(scaleformHandle); }
	FORCEINLINE void SET_TV_CHANNEL(int channel) { return YimMenu::NativeInvoker::Invoke<1354, void>(channel); }
	FORCEINLINE int GET_TV_CHANNEL() { return YimMenu::NativeInvoker::Invoke<1355, int>(); }
	FORCEINLINE void SET_TV_VOLUME(float volume) { return YimMenu::NativeInvoker::Invoke<1356, void>(volume); }
	FORCEINLINE float GET_TV_VOLUME() { return YimMenu::NativeInvoker::Invoke<1357, float>(); }
	FORCEINLINE void DRAW_TV_CHANNEL(float xPos, float yPos, float xScale, float yScale, float rotation, int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1358, void>(xPos, yPos, xScale, yScale, rotation, red, green, blue, alpha); }
	FORCEINLINE void SET_TV_CHANNEL_PLAYLIST(int tvChannel, const char* playlistName, bool restart) { return YimMenu::NativeInvoker::Invoke<1359, void>(tvChannel, playlistName, restart); }
	FORCEINLINE void SET_TV_CHANNEL_PLAYLIST_AT_HOUR(int tvChannel, const char* playlistName, int hour) { return YimMenu::NativeInvoker::Invoke<1360, void>(tvChannel, playlistName, hour); }
	FORCEINLINE void CLEAR_TV_CHANNEL_PLAYLIST(int tvChannel) { return YimMenu::NativeInvoker::Invoke<1361, void>(tvChannel); }
	FORCEINLINE bool IS_PLAYLIST_ON_CHANNEL(int tvChannel, Any p1) { return YimMenu::NativeInvoker::Invoke<1362, bool>(tvChannel, p1); }
	FORCEINLINE bool IS_TVSHOW_CURRENTLY_PLAYING(Hash videoCliphash) { return YimMenu::NativeInvoker::Invoke<1363, bool>(videoCliphash); }
	FORCEINLINE void ENABLE_MOVIE_KEYFRAME_WAIT(bool toggle) { return YimMenu::NativeInvoker::Invoke<1364, void>(toggle); }
	FORCEINLINE void SET_TV_PLAYER_WATCHING_THIS_FRAME(Any p0) { return YimMenu::NativeInvoker::Invoke<1365, void>(p0); }
	FORCEINLINE Hash GET_CURRENT_TV_CLIP_NAMEHASH() { return YimMenu::NativeInvoker::Invoke<1366, Hash>(); }
	FORCEINLINE void ENABLE_MOVIE_SUBTITLES(bool toggle) { return YimMenu::NativeInvoker::Invoke<1367, void>(toggle); }
	FORCEINLINE bool UI3DSCENE_IS_AVAILABLE() { return YimMenu::NativeInvoker::Invoke<1368, bool>(); }
	FORCEINLINE bool UI3DSCENE_PUSH_PRESET(const char* presetName) { return YimMenu::NativeInvoker::Invoke<1369, bool>(presetName); }
	FORCEINLINE bool UI3DSCENE_ASSIGN_PED_TO_SLOT(const char* presetName, Ped ped, int slot, float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<1370, bool>(presetName, ped, slot, posX, posY, posZ); }
	FORCEINLINE void UI3DSCENE_CLEAR_PATCHED_DATA() { return YimMenu::NativeInvoker::Invoke<1371, void>(); }
	FORCEINLINE void UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT(bool toggle) { return YimMenu::NativeInvoker::Invoke<1372, void>(toggle); }
	FORCEINLINE void TERRAINGRID_ACTIVATE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1373, void>(toggle); }
	FORCEINLINE void TERRAINGRID_SET_PARAMS(float x, float y, float z, float forwardX, float forwardY, float forwardZ, float sizeX, float sizeY, float sizeZ, float gridScale, float glowIntensity, float normalHeight, float heightDiff) { return YimMenu::NativeInvoker::Invoke<1374, void>(x, y, z, forwardX, forwardY, forwardZ, sizeX, sizeY, sizeZ, gridScale, glowIntensity, normalHeight, heightDiff); }
	FORCEINLINE void TERRAINGRID_SET_COLOURS(int lowR, int lowG, int lowB, int lowAlpha, int r, int g, int b, int alpha, int highR, int highG, int highB, int highAlpha) { return YimMenu::NativeInvoker::Invoke<1375, void>(lowR, lowG, lowB, lowAlpha, r, g, b, alpha, highR, highG, highB, highAlpha); }
	FORCEINLINE void ANIMPOSTFX_PLAY(const char* effectName, int duration, bool looped) { return YimMenu::NativeInvoker::Invoke<1376, void>(effectName, duration, looped); }
	FORCEINLINE void ANIMPOSTFX_STOP(const char* effectName) { return YimMenu::NativeInvoker::Invoke<1377, void>(effectName); }
	FORCEINLINE float ANIMPOSTFX_GET_CURRENT_TIME(const char* effectName) { return YimMenu::NativeInvoker::Invoke<1378, float>(effectName); }
	FORCEINLINE bool ANIMPOSTFX_IS_RUNNING(const char* effectName) { return YimMenu::NativeInvoker::Invoke<1379, bool>(effectName); }
	FORCEINLINE void ANIMPOSTFX_STOP_ALL() { return YimMenu::NativeInvoker::Invoke<1380, void>(); }
	FORCEINLINE void ANIMPOSTFX_STOP_AND_FLUSH_REQUESTS(const char* effectName) { return YimMenu::NativeInvoker::Invoke<1381, void>(effectName); }
}

namespace HUD
{
	FORCEINLINE void BEGIN_TEXT_COMMAND_BUSYSPINNER_ON(const char* string) { return YimMenu::NativeInvoker::Invoke<1382, void>(string); }
	FORCEINLINE void END_TEXT_COMMAND_BUSYSPINNER_ON(int busySpinnerType) { return YimMenu::NativeInvoker::Invoke<1383, void>(busySpinnerType); }
	FORCEINLINE void BUSYSPINNER_OFF() { return YimMenu::NativeInvoker::Invoke<1384, void>(); }
	FORCEINLINE void PRELOAD_BUSYSPINNER() { return YimMenu::NativeInvoker::Invoke<1385, void>(); }
	FORCEINLINE bool BUSYSPINNER_IS_ON() { return YimMenu::NativeInvoker::Invoke<1386, bool>(); }
	FORCEINLINE bool BUSYSPINNER_IS_DISPLAYING() { return YimMenu::NativeInvoker::Invoke<1387, bool>(); }
	FORCEINLINE void DISABLE_PAUSEMENU_SPINNER(bool p0) { return YimMenu::NativeInvoker::Invoke<1388, void>(p0); }
	FORCEINLINE void SET_MOUSE_CURSOR_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1389, void>(); }
	FORCEINLINE void SET_MOUSE_CURSOR_STYLE(int spriteId) { return YimMenu::NativeInvoker::Invoke<1390, void>(spriteId); }
	FORCEINLINE void SET_MOUSE_CURSOR_VISIBLE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1391, void>(toggle); }
	FORCEINLINE bool IS_MOUSE_ROLLED_OVER_INSTRUCTIONAL_BUTTONS() { return YimMenu::NativeInvoker::Invoke<1392, bool>(); }
	FORCEINLINE bool GET_MOUSE_EVENT(int scaleformHandle, Any* p1, Any* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<1393, bool>(scaleformHandle, p1, p2, p3); }
	FORCEINLINE void THEFEED_ONLY_SHOW_TOOLTIPS(bool toggle) { return YimMenu::NativeInvoker::Invoke<1394, void>(toggle); }
	FORCEINLINE void THEFEED_SET_SCRIPTED_MENU_HEIGHT(float pos) { return YimMenu::NativeInvoker::Invoke<1395, void>(pos); }
	FORCEINLINE void THEFEED_HIDE() { return YimMenu::NativeInvoker::Invoke<1396, void>(); }
	FORCEINLINE void THEFEED_HIDE_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1397, void>(); }
	FORCEINLINE void THEFEED_SHOW() { return YimMenu::NativeInvoker::Invoke<1398, void>(); }
	FORCEINLINE void THEFEED_FLUSH_QUEUE() { return YimMenu::NativeInvoker::Invoke<1399, void>(); }
	FORCEINLINE void THEFEED_REMOVE_ITEM(int notificationId) { return YimMenu::NativeInvoker::Invoke<1400, void>(notificationId); }
	FORCEINLINE void THEFEED_FORCE_RENDER_ON() { return YimMenu::NativeInvoker::Invoke<1401, void>(); }
	FORCEINLINE void THEFEED_FORCE_RENDER_OFF() { return YimMenu::NativeInvoker::Invoke<1402, void>(); }
	FORCEINLINE void THEFEED_PAUSE() { return YimMenu::NativeInvoker::Invoke<1403, void>(); }
	FORCEINLINE void THEFEED_RESUME() { return YimMenu::NativeInvoker::Invoke<1404, void>(); }
	FORCEINLINE bool THEFEED_IS_PAUSED() { return YimMenu::NativeInvoker::Invoke<1405, bool>(); }
	FORCEINLINE void THEFEED_REPORT_LOGO_ON() { return YimMenu::NativeInvoker::Invoke<1406, void>(); }
	FORCEINLINE void THEFEED_REPORT_LOGO_OFF() { return YimMenu::NativeInvoker::Invoke<1407, void>(); }
	FORCEINLINE int THEFEED_GET_LAST_SHOWN_PHONE_ACTIVATABLE_FEED_ID() { return YimMenu::NativeInvoker::Invoke<1408, int>(); }
	FORCEINLINE void THEFEED_AUTO_POST_GAMETIPS_ON() { return YimMenu::NativeInvoker::Invoke<1409, void>(); }
	FORCEINLINE void THEFEED_AUTO_POST_GAMETIPS_OFF() { return YimMenu::NativeInvoker::Invoke<1410, void>(); }
	FORCEINLINE void THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(int hudColorIndex) { return YimMenu::NativeInvoker::Invoke<1411, void>(hudColorIndex); }
	FORCEINLINE void THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE(int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1412, void>(red, green, blue, alpha); }
	FORCEINLINE void THEFEED_SET_FLASH_DURATION_PARAMETER_FOR_NEXT_MESSAGE(int count) { return YimMenu::NativeInvoker::Invoke<1413, void>(count); }
	FORCEINLINE void THEFEED_SET_VIBRATE_PARAMETER_FOR_NEXT_MESSAGE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1414, void>(toggle); }
	FORCEINLINE void THEFEED_RESET_ALL_PARAMETERS() { return YimMenu::NativeInvoker::Invoke<1415, void>(); }
	FORCEINLINE void THEFEED_FREEZE_NEXT_POST() { return YimMenu::NativeInvoker::Invoke<1416, void>(); }
	FORCEINLINE void THEFEED_CLEAR_FROZEN_POST() { return YimMenu::NativeInvoker::Invoke<1417, void>(); }
	FORCEINLINE void THEFEED_SET_SNAP_FEED_ITEM_POSITIONS(bool p0) { return YimMenu::NativeInvoker::Invoke<1418, void>(p0); }
	FORCEINLINE void THEFEED_UPDATE_ITEM_TEXTURE(const char* txdString1, const char* txnString1, const char* txdString2, const char* txnString2) { return YimMenu::NativeInvoker::Invoke<1419, void>(txdString1, txnString1, txdString2, txnString2); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_THEFEED_POST(const char* text) { return YimMenu::NativeInvoker::Invoke<1420, void>(text); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_STATS(const char* statTitle, int iconEnum, bool stepVal, int barValue, bool isImportant, const char* pictureTextureDict, const char* pictureTextureName) { return YimMenu::NativeInvoker::Invoke<1421, int>(statTitle, iconEnum, stepVal, barValue, isImportant, pictureTextureDict, pictureTextureName); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT(const char* txdName, const char* textureName, bool flash, int iconType, const char* sender, const char* subject) { return YimMenu::NativeInvoker::Invoke<1422, int>(txdName, textureName, flash, iconType, sender, subject); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_SUBTITLE_LABEL(const char* txdName, const char* textureName, bool flash, int iconType, const char* sender, const char* subject) { return YimMenu::NativeInvoker::Invoke<1423, int>(txdName, textureName, flash, iconType, sender, subject); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU(const char* txdName, const char* textureName, bool flash, int iconType, const char* sender, const char* subject, float duration) { return YimMenu::NativeInvoker::Invoke<1424, int>(txdName, textureName, flash, iconType, sender, subject, duration); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG(const char* txdName, const char* textureName, bool flash, int iconType, const char* sender, const char* subject, float duration, const char* clanTag) { return YimMenu::NativeInvoker::Invoke<1425, int>(txdName, textureName, flash, iconType, sender, subject, duration, clanTag); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON(const char* txdName, const char* textureName, bool flash, int iconType1, const char* sender, const char* subject, float duration, const char* clanTag, int iconType2, int p9) { return YimMenu::NativeInvoker::Invoke<1426, int>(txdName, textureName, flash, iconType1, sender, subject, duration, clanTag, iconType2, p9); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_TICKER(bool blink, bool p1) { return YimMenu::NativeInvoker::Invoke<1427, int>(blink, p1); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED(bool blink, bool p1) { return YimMenu::NativeInvoker::Invoke<1428, int>(blink, p1); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_TICKER_WITH_TOKENS(bool blink, bool p1) { return YimMenu::NativeInvoker::Invoke<1429, int>(blink, p1); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_AWARD(const char* textureDict, const char* textureName, int rpBonus, int colorOverlay, const char* titleLabel) { return YimMenu::NativeInvoker::Invoke<1430, int>(textureDict, textureName, rpBonus, colorOverlay, titleLabel); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_CREWTAG(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, int R, int G, int B) { return YimMenu::NativeInvoker::Invoke<1431, int>(p0, p1, p2, p3, isLeader, unk0, clanDesc, R, G, B); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_CREWTAG_WITH_GAME_NAME(bool p0, bool p1, int* p2, int p3, bool isLeader, bool unk0, int clanDesc, const char* playerName, int R, int G, int B) { return YimMenu::NativeInvoker::Invoke<1432, int>(p0, p1, p2, p3, isLeader, unk0, clanDesc, playerName, R, G, B); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_UNLOCK(const char* gxtLabel1, int p1, const char* gxtLabel2) { return YimMenu::NativeInvoker::Invoke<1433, int>(gxtLabel1, p1, gxtLabel2); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU(const char* gxtLabel1, int p1, const char* gxtLabel2, int p3) { return YimMenu::NativeInvoker::Invoke<1434, int>(gxtLabel1, p1, gxtLabel2, p3); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU_WITH_COLOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<1435, int>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_MPTICKER(bool blink, bool p1) { return YimMenu::NativeInvoker::Invoke<1436, int>(blink, p1); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_CREW_RANKUP_WITH_LITERAL_FLAG(const char* p0, const char* p1, const char* p2, bool p3, bool p4) { return YimMenu::NativeInvoker::Invoke<1437, int>(p0, p1, p2, p3, p4); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU(const char* txdName1, const char* textureName1, int count1, const char* txdName2, const char* textureName2, int count2, int hudColor1, int hudColor2) { return YimMenu::NativeInvoker::Invoke<1438, int>(txdName1, textureName1, count1, txdName2, textureName2, count2, hudColor1, hudColor2); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_REPLAY(int type, int image, const char* text) { return YimMenu::NativeInvoker::Invoke<1439, int>(type, image, text); }
	FORCEINLINE int END_TEXT_COMMAND_THEFEED_POST_REPLAY_INPUT(int type, const char* button, const char* text) { return YimMenu::NativeInvoker::Invoke<1440, int>(type, button, text); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_PRINT(const char* GxtEntry) { return YimMenu::NativeInvoker::Invoke<1441, void>(GxtEntry); }
	FORCEINLINE void END_TEXT_COMMAND_PRINT(int duration, bool drawImmediately) { return YimMenu::NativeInvoker::Invoke<1442, void>(duration, drawImmediately); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(const char* text) { return YimMenu::NativeInvoker::Invoke<1443, void>(text); }
	FORCEINLINE bool END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED() { return YimMenu::NativeInvoker::Invoke<1444, bool>(); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_DISPLAY_TEXT(const char* text) { return YimMenu::NativeInvoker::Invoke<1445, void>(text); }
	FORCEINLINE void END_TEXT_COMMAND_DISPLAY_TEXT(float x, float y, int p2) { return YimMenu::NativeInvoker::Invoke<1446, void>(x, y, p2); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(const char* text) { return YimMenu::NativeInvoker::Invoke<1447, void>(text); }
	FORCEINLINE float END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(bool p0) { return YimMenu::NativeInvoker::Invoke<1448, float>(p0); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(const char* entry) { return YimMenu::NativeInvoker::Invoke<1449, void>(entry); }
	FORCEINLINE int END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(float x, float y) { return YimMenu::NativeInvoker::Invoke<1450, int>(x, y); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_DISPLAY_HELP(const char* inputType) { return YimMenu::NativeInvoker::Invoke<1451, void>(inputType); }
	FORCEINLINE void END_TEXT_COMMAND_DISPLAY_HELP(int p0, bool loop, bool beep, int shape) { return YimMenu::NativeInvoker::Invoke<1452, void>(p0, loop, beep, shape); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(const char* labelName) { return YimMenu::NativeInvoker::Invoke<1453, void>(labelName); }
	FORCEINLINE bool END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(int p0) { return YimMenu::NativeInvoker::Invoke<1454, bool>(p0); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_SET_BLIP_NAME(const char* textLabel) { return YimMenu::NativeInvoker::Invoke<1455, void>(textLabel); }
	FORCEINLINE void END_TEXT_COMMAND_SET_BLIP_NAME(Blip blip) { return YimMenu::NativeInvoker::Invoke<1456, void>(blip); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(const char* p0) { return YimMenu::NativeInvoker::Invoke<1457, void>(p0); }
	FORCEINLINE void END_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(bool p0) { return YimMenu::NativeInvoker::Invoke<1458, void>(p0); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_CLEAR_PRINT(const char* text) { return YimMenu::NativeInvoker::Invoke<1459, void>(text); }
	FORCEINLINE void END_TEXT_COMMAND_CLEAR_PRINT() { return YimMenu::NativeInvoker::Invoke<1460, void>(); }
	FORCEINLINE void BEGIN_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(const char* gxtEntry) { return YimMenu::NativeInvoker::Invoke<1461, void>(gxtEntry); }
	FORCEINLINE void END_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(int p0) { return YimMenu::NativeInvoker::Invoke<1462, void>(p0); }
	FORCEINLINE void ADD_TEXT_COMPONENT_INTEGER(int value) { return YimMenu::NativeInvoker::Invoke<1463, void>(value); }
	FORCEINLINE void ADD_TEXT_COMPONENT_FLOAT(float value, int decimalPlaces) { return YimMenu::NativeInvoker::Invoke<1464, void>(value, decimalPlaces); }
	FORCEINLINE void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL(const char* labelName) { return YimMenu::NativeInvoker::Invoke<1465, void>(labelName); }
	FORCEINLINE void ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY(Hash gxtEntryHash) { return YimMenu::NativeInvoker::Invoke<1466, void>(gxtEntryHash); }
	FORCEINLINE void ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME(Blip blip) { return YimMenu::NativeInvoker::Invoke<1467, void>(blip); }
	FORCEINLINE void ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const char* text) { return YimMenu::NativeInvoker::Invoke<1468, void>(text); }
	FORCEINLINE void ADD_TEXT_COMPONENT_SUBSTRING_TIME(int timestamp, int flags) { return YimMenu::NativeInvoker::Invoke<1469, void>(timestamp, flags); }
	FORCEINLINE void ADD_TEXT_COMPONENT_FORMATTED_INTEGER(int value, bool commaSeparated) { return YimMenu::NativeInvoker::Invoke<1470, void>(value, commaSeparated); }
	FORCEINLINE void ADD_TEXT_COMPONENT_SUBSTRING_PHONE_NUMBER(const char* p0, int p1) { return YimMenu::NativeInvoker::Invoke<1471, void>(p0, p1); }
	FORCEINLINE void ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(const char* website) { return YimMenu::NativeInvoker::Invoke<1472, void>(website); }
	FORCEINLINE void ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY(const char* string) { return YimMenu::NativeInvoker::Invoke<1473, void>(string); }
	FORCEINLINE void SET_COLOUR_OF_NEXT_TEXT_COMPONENT(int hudColor) { return YimMenu::NativeInvoker::Invoke<1474, void>(hudColor); }
	FORCEINLINE const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME(const char* text, int position, int length) { return YimMenu::NativeInvoker::Invoke<1475, const char*>(text, position, length); }
	FORCEINLINE const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_WITH_BYTE_LIMIT(const char* text, int position, int length, int maxLength) { return YimMenu::NativeInvoker::Invoke<1476, const char*>(text, position, length, maxLength); }
	FORCEINLINE const char* GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_BYTES(const char* text, int startPosition, int endPosition) { return YimMenu::NativeInvoker::Invoke<1477, const char*>(text, startPosition, endPosition); }
	FORCEINLINE const char* GET_FILENAME_FOR_AUDIO_CONVERSATION(const char* labelName) { return YimMenu::NativeInvoker::Invoke<1478, const char*>(labelName); }
	FORCEINLINE void CLEAR_PRINTS() { return YimMenu::NativeInvoker::Invoke<1479, void>(); }
	FORCEINLINE void CLEAR_BRIEF() { return YimMenu::NativeInvoker::Invoke<1480, void>(); }
	FORCEINLINE void CLEAR_ALL_HELP_MESSAGES() { return YimMenu::NativeInvoker::Invoke<1481, void>(); }
	FORCEINLINE void CLEAR_THIS_PRINT(const char* p0) { return YimMenu::NativeInvoker::Invoke<1482, void>(p0); }
	FORCEINLINE void CLEAR_SMALL_PRINTS() { return YimMenu::NativeInvoker::Invoke<1483, void>(); }
	FORCEINLINE bool DOES_TEXT_BLOCK_EXIST(const char* gxt) { return YimMenu::NativeInvoker::Invoke<1484, bool>(gxt); }
	FORCEINLINE void REQUEST_ADDITIONAL_TEXT(const char* gxt, int slot) { return YimMenu::NativeInvoker::Invoke<1485, void>(gxt, slot); }
	FORCEINLINE void REQUEST_ADDITIONAL_TEXT_FOR_DLC(const char* gxt, int slot) { return YimMenu::NativeInvoker::Invoke<1486, void>(gxt, slot); }
	FORCEINLINE bool HAS_ADDITIONAL_TEXT_LOADED(int slot) { return YimMenu::NativeInvoker::Invoke<1487, bool>(slot); }
	FORCEINLINE void CLEAR_ADDITIONAL_TEXT(int p0, bool p1) { return YimMenu::NativeInvoker::Invoke<1488, void>(p0, p1); }
	FORCEINLINE bool IS_STREAMING_ADDITIONAL_TEXT(int p0) { return YimMenu::NativeInvoker::Invoke<1489, bool>(p0); }
	FORCEINLINE bool HAS_THIS_ADDITIONAL_TEXT_LOADED(const char* gxt, int slot) { return YimMenu::NativeInvoker::Invoke<1490, bool>(gxt, slot); }
	FORCEINLINE bool IS_MESSAGE_BEING_DISPLAYED() { return YimMenu::NativeInvoker::Invoke<1491, bool>(); }
	FORCEINLINE bool DOES_TEXT_LABEL_EXIST(const char* gxt) { return YimMenu::NativeInvoker::Invoke<1492, bool>(gxt); }
	FORCEINLINE const char* GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING(const char* string, int length) { return YimMenu::NativeInvoker::Invoke<1493, const char*>(string, length); }
	FORCEINLINE int GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(const char* gxt) { return YimMenu::NativeInvoker::Invoke<1494, int>(gxt); }
	FORCEINLINE int GET_LENGTH_OF_LITERAL_STRING(const char* string) { return YimMenu::NativeInvoker::Invoke<1495, int>(string); }
	FORCEINLINE int GET_LENGTH_OF_LITERAL_STRING_IN_BYTES(const char* string) { return YimMenu::NativeInvoker::Invoke<1496, int>(string); }
	FORCEINLINE const char* GET_STREET_NAME_FROM_HASH_KEY(Hash hash) { return YimMenu::NativeInvoker::Invoke<1497, const char*>(hash); }
	FORCEINLINE bool IS_HUD_PREFERENCE_SWITCHED_ON() { return YimMenu::NativeInvoker::Invoke<1498, bool>(); }
	FORCEINLINE bool IS_RADAR_PREFERENCE_SWITCHED_ON() { return YimMenu::NativeInvoker::Invoke<1499, bool>(); }
	FORCEINLINE bool IS_SUBTITLE_PREFERENCE_SWITCHED_ON() { return YimMenu::NativeInvoker::Invoke<1500, bool>(); }
	FORCEINLINE void DISPLAY_HUD(bool toggle) { return YimMenu::NativeInvoker::Invoke<1501, void>(toggle); }
	FORCEINLINE void DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1502, void>(); }
	FORCEINLINE void DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1503, void>(); }
	FORCEINLINE void DISPLAY_RADAR(bool toggle) { return YimMenu::NativeInvoker::Invoke<1504, void>(toggle); }
	FORCEINLINE void SET_FAKE_SPECTATOR_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1505, void>(toggle); }
	FORCEINLINE bool GET_FAKE_SPECTATOR_MODE() { return YimMenu::NativeInvoker::Invoke<1506, bool>(); }
	FORCEINLINE bool IS_HUD_HIDDEN() { return YimMenu::NativeInvoker::Invoke<1507, bool>(); }
	FORCEINLINE bool IS_RADAR_HIDDEN() { return YimMenu::NativeInvoker::Invoke<1508, bool>(); }
	FORCEINLINE bool IS_MINIMAP_RENDERING() { return YimMenu::NativeInvoker::Invoke<1509, bool>(); }
	FORCEINLINE void USE_VEHICLE_TARGETING_RETICULE(Any p0) { return YimMenu::NativeInvoker::Invoke<1510, void>(p0); }
	FORCEINLINE void ADD_VALID_VEHICLE_HIT_HASH(Any p0) { return YimMenu::NativeInvoker::Invoke<1511, void>(p0); }
	FORCEINLINE void CLEAR_VALID_VEHICLE_HIT_HASHES() { return YimMenu::NativeInvoker::Invoke<1512, void>(); }
	FORCEINLINE void SET_BLIP_ROUTE(Blip blip, bool enabled) { return YimMenu::NativeInvoker::Invoke<1513, void>(blip, enabled); }
	FORCEINLINE void CLEAR_ALL_BLIP_ROUTES() { return YimMenu::NativeInvoker::Invoke<1514, void>(); }
	FORCEINLINE void SET_BLIP_ROUTE_COLOUR(Blip blip, int colour) { return YimMenu::NativeInvoker::Invoke<1515, void>(blip, colour); }
	FORCEINLINE void SET_FORCE_SHOW_GPS(bool toggle) { return YimMenu::NativeInvoker::Invoke<1516, void>(toggle); }
	FORCEINLINE void SET_USE_SET_DESTINATION_IN_PAUSE_MAP(bool toggle) { return YimMenu::NativeInvoker::Invoke<1517, void>(toggle); }
	FORCEINLINE void SET_BLOCK_WANTED_FLASH(bool disabled) { return YimMenu::NativeInvoker::Invoke<1518, void>(disabled); }
	FORCEINLINE void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(bool p0) { return YimMenu::NativeInvoker::Invoke<1519, void>(p0); }
	FORCEINLINE void FORCE_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS_LIST(int p0) { return YimMenu::NativeInvoker::Invoke<1520, void>(p0); }
	FORCEINLINE void SET_RADAR_ZOOM_PRECISE(float zoom) { return YimMenu::NativeInvoker::Invoke<1521, void>(zoom); }
	FORCEINLINE void SET_RADAR_ZOOM(int zoomLevel) { return YimMenu::NativeInvoker::Invoke<1522, void>(zoomLevel); }
	FORCEINLINE void SET_RADAR_ZOOM_TO_BLIP(Blip blip, float zoom) { return YimMenu::NativeInvoker::Invoke<1523, void>(blip, zoom); }
	FORCEINLINE void SET_RADAR_ZOOM_TO_DISTANCE(float zoom) { return YimMenu::NativeInvoker::Invoke<1524, void>(zoom); }
	FORCEINLINE void UPDATE_RADAR_ZOOM_TO_BLIP() { return YimMenu::NativeInvoker::Invoke<1525, void>(); }
	FORCEINLINE void GET_HUD_COLOUR(int hudColorIndex, int* r, int* g, int* b, int* a) { return YimMenu::NativeInvoker::Invoke<1526, void>(hudColorIndex, r, g, b, a); }
	FORCEINLINE void SET_SCRIPT_VARIABLE_HUD_COLOUR(int r, int g, int b, int a) { return YimMenu::NativeInvoker::Invoke<1527, void>(r, g, b, a); }
	FORCEINLINE void SET_SECOND_SCRIPT_VARIABLE_HUD_COLOUR(int r, int g, int b, int a) { return YimMenu::NativeInvoker::Invoke<1528, void>(r, g, b, a); }
	FORCEINLINE void REPLACE_HUD_COLOUR(int hudColorIndex, int hudColorIndex2) { return YimMenu::NativeInvoker::Invoke<1529, void>(hudColorIndex, hudColorIndex2); }
	FORCEINLINE void REPLACE_HUD_COLOUR_WITH_RGBA(int hudColorIndex, int r, int g, int b, int a) { return YimMenu::NativeInvoker::Invoke<1530, void>(hudColorIndex, r, g, b, a); }
	FORCEINLINE void SET_ABILITY_BAR_VISIBILITY(bool visible) { return YimMenu::NativeInvoker::Invoke<1531, void>(visible); }
	FORCEINLINE void SET_ALLOW_ABILITY_BAR(bool toggle) { return YimMenu::NativeInvoker::Invoke<1532, void>(toggle); }
	FORCEINLINE void FLASH_ABILITY_BAR(int millisecondsToFlash) { return YimMenu::NativeInvoker::Invoke<1533, void>(millisecondsToFlash); }
	FORCEINLINE void SET_ABILITY_BAR_VALUE(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<1534, void>(p0, p1); }
	FORCEINLINE void FLASH_WANTED_DISPLAY(bool p0) { return YimMenu::NativeInvoker::Invoke<1535, void>(p0); }
	FORCEINLINE void FORCE_OFF_WANTED_STAR_FLASH(bool toggle) { return YimMenu::NativeInvoker::Invoke<1536, void>(toggle); }
	FORCEINLINE void SET_CUSTOM_MP_HUD_COLOR(int hudColorId) { return YimMenu::NativeInvoker::Invoke<1537, void>(hudColorId); }
	FORCEINLINE float GET_RENDERED_CHARACTER_HEIGHT(float size, int font) { return YimMenu::NativeInvoker::Invoke<1538, float>(size, font); }
	FORCEINLINE void SET_TEXT_SCALE(float scale, float size) { return YimMenu::NativeInvoker::Invoke<1539, void>(scale, size); }
	FORCEINLINE void SET_TEXT_COLOUR(int red, int green, int blue, int alpha) { return YimMenu::NativeInvoker::Invoke<1540, void>(red, green, blue, alpha); }
	FORCEINLINE void SET_TEXT_CENTRE(bool align) { return YimMenu::NativeInvoker::Invoke<1541, void>(align); }
	FORCEINLINE void SET_TEXT_RIGHT_JUSTIFY(bool toggle) { return YimMenu::NativeInvoker::Invoke<1542, void>(toggle); }
	FORCEINLINE void SET_TEXT_JUSTIFICATION(int justifyType) { return YimMenu::NativeInvoker::Invoke<1543, void>(justifyType); }
	FORCEINLINE void SET_TEXT_WRAP(float start, float end) { return YimMenu::NativeInvoker::Invoke<1544, void>(start, end); }
	FORCEINLINE void SET_TEXT_LEADING(int p0) { return YimMenu::NativeInvoker::Invoke<1545, void>(p0); }
	FORCEINLINE void SET_TEXT_PROPORTIONAL(bool p0) { return YimMenu::NativeInvoker::Invoke<1546, void>(p0); }
	FORCEINLINE void SET_TEXT_FONT(int fontType) { return YimMenu::NativeInvoker::Invoke<1547, void>(fontType); }
	FORCEINLINE void SET_TEXT_DROP_SHADOW() { return YimMenu::NativeInvoker::Invoke<1548, void>(); }
	FORCEINLINE void SET_TEXT_DROPSHADOW(int distance, int r, int g, int b, int a) { return YimMenu::NativeInvoker::Invoke<1549, void>(distance, r, g, b, a); }
	FORCEINLINE void SET_TEXT_OUTLINE() { return YimMenu::NativeInvoker::Invoke<1550, void>(); }
	FORCEINLINE void SET_TEXT_EDGE(int p0, int r, int g, int b, int a) { return YimMenu::NativeInvoker::Invoke<1551, void>(p0, r, g, b, a); }
	FORCEINLINE void SET_TEXT_RENDER_ID(int renderId) { return YimMenu::NativeInvoker::Invoke<1552, void>(renderId); }
	FORCEINLINE int GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID() { return YimMenu::NativeInvoker::Invoke<1553, int>(); }
	FORCEINLINE bool REGISTER_NAMED_RENDERTARGET(const char* name, bool p1) { return YimMenu::NativeInvoker::Invoke<1554, bool>(name, p1); }
	FORCEINLINE bool IS_NAMED_RENDERTARGET_REGISTERED(const char* name) { return YimMenu::NativeInvoker::Invoke<1555, bool>(name); }
	FORCEINLINE bool RELEASE_NAMED_RENDERTARGET(const char* name) { return YimMenu::NativeInvoker::Invoke<1556, bool>(name); }
	FORCEINLINE void LINK_NAMED_RENDERTARGET(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<1557, void>(modelHash); }
	FORCEINLINE int GET_NAMED_RENDERTARGET_RENDER_ID(const char* name) { return YimMenu::NativeInvoker::Invoke<1558, int>(name); }
	FORCEINLINE bool IS_NAMED_RENDERTARGET_LINKED(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<1559, bool>(modelHash); }
	FORCEINLINE void CLEAR_HELP(bool toggle) { return YimMenu::NativeInvoker::Invoke<1560, void>(toggle); }
	FORCEINLINE bool IS_HELP_MESSAGE_ON_SCREEN() { return YimMenu::NativeInvoker::Invoke<1561, bool>(); }
	FORCEINLINE bool HAS_SCRIPT_HIDDEN_HELP_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1562, bool>(); }
	FORCEINLINE bool IS_HELP_MESSAGE_BEING_DISPLAYED() { return YimMenu::NativeInvoker::Invoke<1563, bool>(); }
	FORCEINLINE bool IS_HELP_MESSAGE_FADING_OUT() { return YimMenu::NativeInvoker::Invoke<1564, bool>(); }
	FORCEINLINE void SET_HELP_MESSAGE_STYLE(int style, int hudColor, int alpha, int p3, int p4) { return YimMenu::NativeInvoker::Invoke<1565, void>(style, hudColor, alpha, p3, p4); }
	FORCEINLINE int GET_STANDARD_BLIP_ENUM_ID() { return YimMenu::NativeInvoker::Invoke<1566, int>(); }
	FORCEINLINE int GET_WAYPOINT_BLIP_ENUM_ID() { return YimMenu::NativeInvoker::Invoke<1567, int>(); }
	FORCEINLINE int GET_NUMBER_OF_ACTIVE_BLIPS() { return YimMenu::NativeInvoker::Invoke<1568, int>(); }
	FORCEINLINE Blip GET_NEXT_BLIP_INFO_ID(int blipSprite) { return YimMenu::NativeInvoker::Invoke<1569, Blip>(blipSprite); }
	FORCEINLINE Blip GET_FIRST_BLIP_INFO_ID(int blipSprite) { return YimMenu::NativeInvoker::Invoke<1570, Blip>(blipSprite); }
	FORCEINLINE Blip GET_CLOSEST_BLIP_INFO_ID(int blipSprite) { return YimMenu::NativeInvoker::Invoke<1571, Blip>(blipSprite); }
	FORCEINLINE Vector3 GET_BLIP_INFO_ID_COORD(Blip blip) { return YimMenu::NativeInvoker::Invoke<1572, Vector3>(blip); }
	FORCEINLINE int GET_BLIP_INFO_ID_DISPLAY(Blip blip) { return YimMenu::NativeInvoker::Invoke<1573, int>(blip); }
	FORCEINLINE int GET_BLIP_INFO_ID_TYPE(Blip blip) { return YimMenu::NativeInvoker::Invoke<1574, int>(blip); }
	FORCEINLINE Entity GET_BLIP_INFO_ID_ENTITY_INDEX(Blip blip) { return YimMenu::NativeInvoker::Invoke<1575, Entity>(blip); }
	FORCEINLINE Pickup GET_BLIP_INFO_ID_PICKUP_INDEX(Blip blip) { return YimMenu::NativeInvoker::Invoke<1576, Pickup>(blip); }
	FORCEINLINE Blip GET_BLIP_FROM_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1577, Blip>(entity); }
	FORCEINLINE Blip ADD_BLIP_FOR_RADIUS(float posX, float posY, float posZ, float radius) { return YimMenu::NativeInvoker::Invoke<1578, Blip>(posX, posY, posZ, radius); }
	FORCEINLINE Blip ADD_BLIP_FOR_AREA(float x, float y, float z, float width, float height) { return YimMenu::NativeInvoker::Invoke<1579, Blip>(x, y, z, width, height); }
	FORCEINLINE Blip ADD_BLIP_FOR_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1580, Blip>(entity); }
	FORCEINLINE Blip ADD_BLIP_FOR_PICKUP(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<1581, Blip>(pickup); }
	FORCEINLINE Blip ADD_BLIP_FOR_COORD(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1582, Blip>(x, y, z); }
	FORCEINLINE void TRIGGER_SONAR_BLIP(float posX, float posY, float posZ, float radius, int p4) { return YimMenu::NativeInvoker::Invoke<1583, void>(posX, posY, posZ, radius, p4); }
	FORCEINLINE void ALLOW_SONAR_BLIPS(bool toggle) { return YimMenu::NativeInvoker::Invoke<1584, void>(toggle); }
	FORCEINLINE void SET_BLIP_COORDS(Blip blip, float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<1585, void>(blip, posX, posY, posZ); }
	FORCEINLINE Vector3 GET_BLIP_COORDS(Blip blip) { return YimMenu::NativeInvoker::Invoke<1586, Vector3>(blip); }
	FORCEINLINE void SET_BLIP_SPRITE(Blip blip, int spriteId) { return YimMenu::NativeInvoker::Invoke<1587, void>(blip, spriteId); }
	FORCEINLINE int GET_BLIP_SPRITE(Blip blip) { return YimMenu::NativeInvoker::Invoke<1588, int>(blip); }
	FORCEINLINE void SET_COP_BLIP_SPRITE(int p0, float p1) { return YimMenu::NativeInvoker::Invoke<1589, void>(p0, p1); }
	FORCEINLINE void SET_COP_BLIP_SPRITE_AS_STANDARD() { return YimMenu::NativeInvoker::Invoke<1590, void>(); }
	FORCEINLINE void SET_BLIP_NAME_FROM_TEXT_FILE(Blip blip, const char* gxtEntry) { return YimMenu::NativeInvoker::Invoke<1591, void>(blip, gxtEntry); }
	FORCEINLINE void SET_BLIP_NAME_TO_PLAYER_NAME(Blip blip, Player player) { return YimMenu::NativeInvoker::Invoke<1592, void>(blip, player); }
	FORCEINLINE void SET_BLIP_ALPHA(Blip blip, int alpha) { return YimMenu::NativeInvoker::Invoke<1593, void>(blip, alpha); }
	FORCEINLINE int GET_BLIP_ALPHA(Blip blip) { return YimMenu::NativeInvoker::Invoke<1594, int>(blip); }
	FORCEINLINE void SET_BLIP_FADE(Blip blip, int opacity, int duration) { return YimMenu::NativeInvoker::Invoke<1595, void>(blip, opacity, duration); }
	FORCEINLINE int GET_BLIP_FADE_DIRECTION(Blip blip) { return YimMenu::NativeInvoker::Invoke<1596, int>(blip); }
	FORCEINLINE void SET_BLIP_ROTATION(Blip blip, int rotation) { return YimMenu::NativeInvoker::Invoke<1597, void>(blip, rotation); }
	FORCEINLINE void SET_BLIP_ROTATION_WITH_FLOAT(Blip blip, float heading) { return YimMenu::NativeInvoker::Invoke<1598, void>(blip, heading); }
	FORCEINLINE int GET_BLIP_ROTATION(Blip blip) { return YimMenu::NativeInvoker::Invoke<1599, int>(blip); }
	FORCEINLINE void SET_BLIP_FLASH_TIMER(Blip blip, int duration) { return YimMenu::NativeInvoker::Invoke<1600, void>(blip, duration); }
	FORCEINLINE void SET_BLIP_FLASH_INTERVAL(Blip blip, Any p1) { return YimMenu::NativeInvoker::Invoke<1601, void>(blip, p1); }
	FORCEINLINE void SET_BLIP_COLOUR(Blip blip, int color) { return YimMenu::NativeInvoker::Invoke<1602, void>(blip, color); }
	FORCEINLINE void SET_BLIP_SECONDARY_COLOUR(Blip blip, int r, int g, int b) { return YimMenu::NativeInvoker::Invoke<1603, void>(blip, r, g, b); }
	FORCEINLINE int GET_BLIP_COLOUR(Blip blip) { return YimMenu::NativeInvoker::Invoke<1604, int>(blip); }
	FORCEINLINE int GET_BLIP_HUD_COLOUR(Blip blip) { return YimMenu::NativeInvoker::Invoke<1605, int>(blip); }
	FORCEINLINE bool IS_BLIP_SHORT_RANGE(Blip blip) { return YimMenu::NativeInvoker::Invoke<1606, bool>(blip); }
	FORCEINLINE bool IS_BLIP_ON_MINIMAP(Blip blip) { return YimMenu::NativeInvoker::Invoke<1607, bool>(blip); }
	FORCEINLINE bool DOES_BLIP_HAVE_GPS_ROUTE(Blip blip) { return YimMenu::NativeInvoker::Invoke<1608, bool>(blip); }
	FORCEINLINE void SET_BLIP_HIDDEN_ON_LEGEND(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1609, void>(blip, toggle); }
	FORCEINLINE void SET_BLIP_HIGH_DETAIL(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1610, void>(blip, toggle); }
	FORCEINLINE void SET_BLIP_AS_MISSION_CREATOR_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1611, void>(blip, toggle); }
	FORCEINLINE bool IS_MISSION_CREATOR_BLIP(Blip blip) { return YimMenu::NativeInvoker::Invoke<1612, bool>(blip); }
	FORCEINLINE Blip GET_NEW_SELECTED_MISSION_CREATOR_BLIP() { return YimMenu::NativeInvoker::Invoke<1613, Blip>(); }
	FORCEINLINE bool IS_HOVERING_OVER_MISSION_CREATOR_BLIP() { return YimMenu::NativeInvoker::Invoke<1614, bool>(); }
	FORCEINLINE void SHOW_START_MISSION_INSTRUCTIONAL_BUTTON(bool toggle) { return YimMenu::NativeInvoker::Invoke<1615, void>(toggle); }
	FORCEINLINE void SHOW_CONTACT_INSTRUCTIONAL_BUTTON(bool toggle) { return YimMenu::NativeInvoker::Invoke<1616, void>(toggle); }
	FORCEINLINE void RELOAD_MAP_MENU() { return YimMenu::NativeInvoker::Invoke<1617, void>(); }
	FORCEINLINE void SET_BLIP_MARKER_LONG_DISTANCE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<1618, void>(p0, p1); }
	FORCEINLINE void SET_BLIP_FLASHES(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1619, void>(blip, toggle); }
	FORCEINLINE void SET_BLIP_FLASHES_ALTERNATE(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1620, void>(blip, toggle); }
	FORCEINLINE bool IS_BLIP_FLASHING(Blip blip) { return YimMenu::NativeInvoker::Invoke<1621, bool>(blip); }
	FORCEINLINE void SET_BLIP_AS_SHORT_RANGE(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1622, void>(blip, toggle); }
	FORCEINLINE void SET_BLIP_SCALE(Blip blip, float scale) { return YimMenu::NativeInvoker::Invoke<1623, void>(blip, scale); }
	FORCEINLINE void SET_BLIP_SCALE_2D(Blip blip, float xScale, float yScale) { return YimMenu::NativeInvoker::Invoke<1624, void>(blip, xScale, yScale); }
	FORCEINLINE void SET_BLIP_PRIORITY(Blip blip, int priority) { return YimMenu::NativeInvoker::Invoke<1625, void>(blip, priority); }
	FORCEINLINE void SET_BLIP_DISPLAY(Blip blip, int displayId) { return YimMenu::NativeInvoker::Invoke<1626, void>(blip, displayId); }
	FORCEINLINE void SET_BLIP_CATEGORY(Blip blip, int index) { return YimMenu::NativeInvoker::Invoke<1627, void>(blip, index); }
	FORCEINLINE void REMOVE_BLIP(Blip* blip) { return YimMenu::NativeInvoker::Invoke<1628, void>(blip); }
	FORCEINLINE void SET_BLIP_AS_FRIENDLY(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1629, void>(blip, toggle); }
	FORCEINLINE void PULSE_BLIP(Blip blip) { return YimMenu::NativeInvoker::Invoke<1630, void>(blip); }
	FORCEINLINE void SHOW_NUMBER_ON_BLIP(Blip blip, int number) { return YimMenu::NativeInvoker::Invoke<1631, void>(blip, number); }
	FORCEINLINE void HIDE_NUMBER_ON_BLIP(Blip blip) { return YimMenu::NativeInvoker::Invoke<1632, void>(blip); }
	FORCEINLINE void SHOW_HEIGHT_ON_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1633, void>(blip, toggle); }
	FORCEINLINE void SHOW_TICK_ON_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1634, void>(blip, toggle); }
	FORCEINLINE void SHOW_GOLD_TICK_ON_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1635, void>(blip, toggle); }
	FORCEINLINE void SHOW_FOR_SALE_ICON_ON_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1636, void>(blip, toggle); }
	FORCEINLINE void SHOW_HEADING_INDICATOR_ON_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1637, void>(blip, toggle); }
	FORCEINLINE void SHOW_OUTLINE_INDICATOR_ON_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1638, void>(blip, toggle); }
	FORCEINLINE void SHOW_FRIEND_INDICATOR_ON_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1639, void>(blip, toggle); }
	FORCEINLINE void SHOW_CREW_INDICATOR_ON_BLIP(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1640, void>(blip, toggle); }
	FORCEINLINE void SET_BLIP_EXTENDED_HEIGHT_THRESHOLD(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1641, void>(blip, toggle); }
	FORCEINLINE void SET_BLIP_SHORT_HEIGHT_THRESHOLD(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<1642, void>(p0, p1); }
	FORCEINLINE void SET_BLIP_USE_HEIGHT_INDICATOR_ON_EDGE(Blip blip, Any p1) { return YimMenu::NativeInvoker::Invoke<1643, void>(blip, p1); }
	FORCEINLINE void SET_BLIP_AS_MINIMAL_ON_EDGE(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1644, void>(blip, toggle); }
	FORCEINLINE void SET_RADIUS_BLIP_EDGE(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1645, void>(blip, toggle); }
	FORCEINLINE bool DOES_BLIP_EXIST(Blip blip) { return YimMenu::NativeInvoker::Invoke<1646, bool>(blip); }
	FORCEINLINE void SET_WAYPOINT_OFF() { return YimMenu::NativeInvoker::Invoke<1647, void>(); }
	FORCEINLINE void DELETE_WAYPOINTS_FROM_THIS_PLAYER() { return YimMenu::NativeInvoker::Invoke<1648, void>(); }
	FORCEINLINE void REFRESH_WAYPOINT() { return YimMenu::NativeInvoker::Invoke<1649, void>(); }
	FORCEINLINE bool IS_WAYPOINT_ACTIVE() { return YimMenu::NativeInvoker::Invoke<1650, bool>(); }
	FORCEINLINE void SET_NEW_WAYPOINT(float x, float y) { return YimMenu::NativeInvoker::Invoke<1651, void>(x, y); }
	FORCEINLINE void SET_BLIP_BRIGHT(Blip blip, bool toggle) { return YimMenu::NativeInvoker::Invoke<1652, void>(blip, toggle); }
	FORCEINLINE void SET_BLIP_SHOW_CONE(Blip blip, bool toggle, int hudColorIndex) { return YimMenu::NativeInvoker::Invoke<1653, void>(blip, toggle, hudColorIndex); }
	FORCEINLINE void REMOVE_COP_BLIP_FROM_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<1654, void>(ped); }
	FORCEINLINE void SETUP_FAKE_CONE_DATA(Blip blip, float p1, float p2, float p3, float p4, float p5, float p6, Any p7, int p8) { return YimMenu::NativeInvoker::Invoke<1655, void>(blip, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void REMOVE_FAKE_CONE_DATA(Blip blip) { return YimMenu::NativeInvoker::Invoke<1656, void>(blip); }
	FORCEINLINE void CLEAR_FAKE_CONE_ARRAY() { return YimMenu::NativeInvoker::Invoke<1657, void>(); }
	FORCEINLINE bool SET_MINIMAP_COMPONENT(int componentId, bool toggle, int overrideColor) { return YimMenu::NativeInvoker::Invoke<1658, bool>(componentId, toggle, overrideColor); }
	FORCEINLINE void SET_MINIMAP_SONAR_SWEEP(bool toggle) { return YimMenu::NativeInvoker::Invoke<1659, void>(toggle); }
	FORCEINLINE void SHOW_ACCOUNT_PICKER() { return YimMenu::NativeInvoker::Invoke<1660, void>(); }
	FORCEINLINE Blip GET_MAIN_PLAYER_BLIP_ID() { return YimMenu::NativeInvoker::Invoke<1661, Blip>(); }
	FORCEINLINE void SET_PM_WARNINGSCREEN_ACTIVE(bool p0) { return YimMenu::NativeInvoker::Invoke<1662, void>(p0); }
	FORCEINLINE void HIDE_LOADING_ON_FADE_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1663, void>(); }
	FORCEINLINE void SET_RADAR_AS_INTERIOR_THIS_FRAME(Hash interior, float x, float y, int z, int zoom) { return YimMenu::NativeInvoker::Invoke<1664, void>(interior, x, y, z, zoom); }
	FORCEINLINE void SET_INSIDE_VERY_SMALL_INTERIOR(bool toggle) { return YimMenu::NativeInvoker::Invoke<1665, void>(toggle); }
	FORCEINLINE void SET_INSIDE_VERY_LARGE_INTERIOR(bool toggle) { return YimMenu::NativeInvoker::Invoke<1666, void>(toggle); }
	FORCEINLINE void SET_RADAR_AS_EXTERIOR_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1667, void>(); }
	FORCEINLINE void SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME(float x, float y) { return YimMenu::NativeInvoker::Invoke<1668, void>(x, y); }
	FORCEINLINE void SET_FAKE_GPS_PLAYER_POSITION_THIS_FRAME(float x, float y, Any p2) { return YimMenu::NativeInvoker::Invoke<1669, void>(x, y, p2); }
	FORCEINLINE bool IS_PAUSEMAP_IN_INTERIOR_MODE() { return YimMenu::NativeInvoker::Invoke<1670, bool>(); }
	FORCEINLINE void HIDE_MINIMAP_EXTERIOR_MAP_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1671, void>(); }
	FORCEINLINE void HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1672, void>(); }
	FORCEINLINE void SET_USE_ISLAND_MAP(bool toggle) { return YimMenu::NativeInvoker::Invoke<1673, void>(toggle); }
	FORCEINLINE void DONT_TILT_MINIMAP_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1674, void>(); }
	FORCEINLINE void DONT_ZOOM_MINIMAP_WHEN_RUNNING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1675, void>(); }
	FORCEINLINE void DONT_ZOOM_MINIMAP_WHEN_SNIPING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1676, void>(); }
	FORCEINLINE void SET_WIDESCREEN_FORMAT(Any p0) { return YimMenu::NativeInvoker::Invoke<1677, void>(p0); }
	FORCEINLINE void DISPLAY_AREA_NAME(bool toggle) { return YimMenu::NativeInvoker::Invoke<1678, void>(toggle); }
	FORCEINLINE void DISPLAY_CASH(bool toggle) { return YimMenu::NativeInvoker::Invoke<1679, void>(toggle); }
	FORCEINLINE void USE_FAKE_MP_CASH(bool toggle) { return YimMenu::NativeInvoker::Invoke<1680, void>(toggle); }
	FORCEINLINE void CHANGE_FAKE_MP_CASH(int cash, int bank) { return YimMenu::NativeInvoker::Invoke<1681, void>(cash, bank); }
	FORCEINLINE void DISPLAY_AMMO_THIS_FRAME(bool display) { return YimMenu::NativeInvoker::Invoke<1682, void>(display); }
	FORCEINLINE void DISPLAY_SNIPER_SCOPE_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1683, void>(); }
	FORCEINLINE void HIDE_HUD_AND_RADAR_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1684, void>(); }
	FORCEINLINE void ALLOW_DISPLAY_OF_MULTIPLAYER_CASH_TEXT(bool allow) { return YimMenu::NativeInvoker::Invoke<1685, void>(allow); }
	FORCEINLINE void SET_MULTIPLAYER_WALLET_CASH() { return YimMenu::NativeInvoker::Invoke<1686, void>(); }
	FORCEINLINE void REMOVE_MULTIPLAYER_WALLET_CASH() { return YimMenu::NativeInvoker::Invoke<1687, void>(); }
	FORCEINLINE void SET_MULTIPLAYER_BANK_CASH() { return YimMenu::NativeInvoker::Invoke<1688, void>(); }
	FORCEINLINE void REMOVE_MULTIPLAYER_BANK_CASH() { return YimMenu::NativeInvoker::Invoke<1689, void>(); }
	FORCEINLINE void SET_MULTIPLAYER_HUD_CASH(int p0, bool p1) { return YimMenu::NativeInvoker::Invoke<1690, void>(p0, p1); }
	FORCEINLINE void REMOVE_MULTIPLAYER_HUD_CASH() { return YimMenu::NativeInvoker::Invoke<1691, void>(); }
	FORCEINLINE void HIDE_HELP_TEXT_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1692, void>(); }
	FORCEINLINE bool IS_IME_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<1693, bool>(); }
	FORCEINLINE void DISPLAY_HELP_TEXT_THIS_FRAME(const char* message, bool p1) { return YimMenu::NativeInvoker::Invoke<1694, void>(message, p1); }
	FORCEINLINE void HUD_FORCE_WEAPON_WHEEL(bool show) { return YimMenu::NativeInvoker::Invoke<1695, void>(show); }
	FORCEINLINE void HUD_FORCE_SPECIAL_VEHICLE_WEAPON_WHEEL() { return YimMenu::NativeInvoker::Invoke<1696, void>(); }
	FORCEINLINE void HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1697, void>(); }
	FORCEINLINE Hash HUD_GET_WEAPON_WHEEL_CURRENTLY_HIGHLIGHTED() { return YimMenu::NativeInvoker::Invoke<1698, Hash>(); }
	FORCEINLINE void HUD_SET_WEAPON_WHEEL_TOP_SLOT(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<1699, void>(weaponHash); }
	FORCEINLINE Hash HUD_GET_WEAPON_WHEEL_TOP_SLOT(int weaponTypeIndex) { return YimMenu::NativeInvoker::Invoke<1700, Hash>(weaponTypeIndex); }
	FORCEINLINE void HUD_SHOWING_CHARACTER_SWITCH_SELECTION(bool toggle) { return YimMenu::NativeInvoker::Invoke<1701, void>(toggle); }
	FORCEINLINE void SET_GPS_FLAGS(int p0, float p1) { return YimMenu::NativeInvoker::Invoke<1702, void>(p0, p1); }
	FORCEINLINE void CLEAR_GPS_FLAGS() { return YimMenu::NativeInvoker::Invoke<1703, void>(); }
	FORCEINLINE void SET_RACE_TRACK_RENDER(bool toggle) { return YimMenu::NativeInvoker::Invoke<1704, void>(toggle); }
	FORCEINLINE void CLEAR_GPS_RACE_TRACK() { return YimMenu::NativeInvoker::Invoke<1705, void>(); }
	FORCEINLINE void START_GPS_CUSTOM_ROUTE(int hudColor, bool displayOnFoot, bool followPlayer) { return YimMenu::NativeInvoker::Invoke<1706, void>(hudColor, displayOnFoot, followPlayer); }
	FORCEINLINE void ADD_POINT_TO_GPS_CUSTOM_ROUTE(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1707, void>(x, y, z); }
	FORCEINLINE void SET_GPS_CUSTOM_ROUTE_RENDER(bool toggle, int radarThickness, int mapThickness) { return YimMenu::NativeInvoker::Invoke<1708, void>(toggle, radarThickness, mapThickness); }
	FORCEINLINE void CLEAR_GPS_CUSTOM_ROUTE() { return YimMenu::NativeInvoker::Invoke<1709, void>(); }
	FORCEINLINE void START_GPS_MULTI_ROUTE(int hudColor, bool routeFromPlayer, bool displayOnFoot) { return YimMenu::NativeInvoker::Invoke<1710, void>(hudColor, routeFromPlayer, displayOnFoot); }
	FORCEINLINE void ADD_POINT_TO_GPS_MULTI_ROUTE(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1711, void>(x, y, z); }
	FORCEINLINE void SET_GPS_MULTI_ROUTE_RENDER(bool toggle) { return YimMenu::NativeInvoker::Invoke<1712, void>(toggle); }
	FORCEINLINE void CLEAR_GPS_MULTI_ROUTE() { return YimMenu::NativeInvoker::Invoke<1713, void>(); }
	FORCEINLINE void CLEAR_GPS_PLAYER_WAYPOINT() { return YimMenu::NativeInvoker::Invoke<1714, void>(); }
	FORCEINLINE void SET_GPS_FLASHES(bool toggle) { return YimMenu::NativeInvoker::Invoke<1715, void>(toggle); }
	FORCEINLINE void SET_PLAYER_ICON_COLOUR(int color) { return YimMenu::NativeInvoker::Invoke<1716, void>(color); }
	FORCEINLINE void FLASH_MINIMAP_DISPLAY() { return YimMenu::NativeInvoker::Invoke<1717, void>(); }
	FORCEINLINE void FLASH_MINIMAP_DISPLAY_WITH_COLOR(int hudColorIndex) { return YimMenu::NativeInvoker::Invoke<1718, void>(hudColorIndex); }
	FORCEINLINE void TOGGLE_STEALTH_RADAR(bool toggle) { return YimMenu::NativeInvoker::Invoke<1719, void>(toggle); }
	FORCEINLINE void SET_MINIMAP_IN_SPECTATOR_MODE(bool toggle, Ped ped) { return YimMenu::NativeInvoker::Invoke<1720, void>(toggle, ped); }
	FORCEINLINE void SET_MISSION_NAME(bool p0, const char* name) { return YimMenu::NativeInvoker::Invoke<1721, void>(p0, name); }
	FORCEINLINE void SET_MISSION_NAME_FOR_UGC_MISSION(bool p0, const char* name) { return YimMenu::NativeInvoker::Invoke<1722, void>(p0, name); }
	FORCEINLINE void SET_DESCRIPTION_FOR_UGC_MISSION_EIGHT_STRINGS(bool p0, const char* p1, const char* p2, const char* p3, const char* p4, const char* p5, const char* p6, const char* p7, const char* p8) { return YimMenu::NativeInvoker::Invoke<1723, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void SET_MINIMAP_BLOCK_WAYPOINT(bool toggle) { return YimMenu::NativeInvoker::Invoke<1724, void>(toggle); }
	FORCEINLINE void SET_MINIMAP_IN_PROLOGUE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1725, void>(toggle); }
	FORCEINLINE void SET_MINIMAP_HIDE_FOW(bool toggle) { return YimMenu::NativeInvoker::Invoke<1726, void>(toggle); }
	FORCEINLINE float GET_MINIMAP_FOW_DISCOVERY_RATIO() { return YimMenu::NativeInvoker::Invoke<1727, float>(); }
	FORCEINLINE bool GET_MINIMAP_FOW_COORDINATE_IS_REVEALED(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1728, bool>(x, y, z); }
	FORCEINLINE void SET_MINIMAP_FOW_DO_NOT_UPDATE(bool p0) { return YimMenu::NativeInvoker::Invoke<1729, void>(p0); }
	FORCEINLINE void SET_MINIMAP_FOW_REVEAL_COORDINATE(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1730, void>(x, y, z); }
	FORCEINLINE void SET_MINIMAP_GOLF_COURSE(int hole) { return YimMenu::NativeInvoker::Invoke<1731, void>(hole); }
	FORCEINLINE void SET_MINIMAP_GOLF_COURSE_OFF() { return YimMenu::NativeInvoker::Invoke<1732, void>(); }
	FORCEINLINE void LOCK_MINIMAP_ANGLE(int angle) { return YimMenu::NativeInvoker::Invoke<1733, void>(angle); }
	FORCEINLINE void UNLOCK_MINIMAP_ANGLE() { return YimMenu::NativeInvoker::Invoke<1734, void>(); }
	FORCEINLINE void LOCK_MINIMAP_POSITION(float x, float y) { return YimMenu::NativeInvoker::Invoke<1735, void>(x, y); }
	FORCEINLINE void UNLOCK_MINIMAP_POSITION() { return YimMenu::NativeInvoker::Invoke<1736, void>(); }
	FORCEINLINE void SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT(float altitude, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<1737, void>(altitude, p1, p2); }
	FORCEINLINE void SET_HEALTH_HUD_DISPLAY_VALUES(int health, int capacity, bool wasAdded) { return YimMenu::NativeInvoker::Invoke<1738, void>(health, capacity, wasAdded); }
	FORCEINLINE void SET_MAX_HEALTH_HUD_DISPLAY(int maximumValue) { return YimMenu::NativeInvoker::Invoke<1739, void>(maximumValue); }
	FORCEINLINE void SET_MAX_ARMOUR_HUD_DISPLAY(int maximumValue) { return YimMenu::NativeInvoker::Invoke<1740, void>(maximumValue); }
	FORCEINLINE void SET_BIGMAP_ACTIVE(bool toggleBigMap, bool showFullMap) { return YimMenu::NativeInvoker::Invoke<1741, void>(toggleBigMap, showFullMap); }
	FORCEINLINE bool IS_HUD_COMPONENT_ACTIVE(int id) { return YimMenu::NativeInvoker::Invoke<1742, bool>(id); }
	FORCEINLINE bool IS_SCRIPTED_HUD_COMPONENT_ACTIVE(int id) { return YimMenu::NativeInvoker::Invoke<1743, bool>(id); }
	FORCEINLINE void HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id) { return YimMenu::NativeInvoker::Invoke<1744, void>(id); }
	FORCEINLINE void SHOW_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id) { return YimMenu::NativeInvoker::Invoke<1745, void>(id); }
	FORCEINLINE bool IS_SCRIPTED_HUD_COMPONENT_HIDDEN_THIS_FRAME(int id) { return YimMenu::NativeInvoker::Invoke<1746, bool>(id); }
	FORCEINLINE void HIDE_HUD_COMPONENT_THIS_FRAME(int id) { return YimMenu::NativeInvoker::Invoke<1747, void>(id); }
	FORCEINLINE void SHOW_HUD_COMPONENT_THIS_FRAME(int id) { return YimMenu::NativeInvoker::Invoke<1748, void>(id); }
	FORCEINLINE void HIDE_STREET_AND_CAR_NAMES_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1749, void>(); }
	FORCEINLINE void RESET_RETICULE_VALUES() { return YimMenu::NativeInvoker::Invoke<1750, void>(); }
	FORCEINLINE void RESET_HUD_COMPONENT_VALUES(int id) { return YimMenu::NativeInvoker::Invoke<1751, void>(id); }
	FORCEINLINE void SET_HUD_COMPONENT_POSITION(int id, float x, float y) { return YimMenu::NativeInvoker::Invoke<1752, void>(id, x, y); }
	FORCEINLINE Vector3 GET_HUD_COMPONENT_POSITION(int id) { return YimMenu::NativeInvoker::Invoke<1753, Vector3>(id); }
	FORCEINLINE void CLEAR_REMINDER_MESSAGE() { return YimMenu::NativeInvoker::Invoke<1754, void>(); }
	FORCEINLINE int GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(float worldX, float worldY, float worldZ, float* screenX, float* screenY) { return YimMenu::NativeInvoker::Invoke<1755, int>(worldX, worldY, worldZ, screenX, screenY); }
	FORCEINLINE void OPEN_REPORTUGC_MENU() { return YimMenu::NativeInvoker::Invoke<1756, void>(); }
	FORCEINLINE void FORCE_CLOSE_REPORTUGC_MENU() { return YimMenu::NativeInvoker::Invoke<1757, void>(); }
	FORCEINLINE bool IS_REPORTUGC_MENU_OPEN() { return YimMenu::NativeInvoker::Invoke<1758, bool>(); }
	FORCEINLINE bool IS_FLOATING_HELP_TEXT_ON_SCREEN(int hudIndex) { return YimMenu::NativeInvoker::Invoke<1759, bool>(hudIndex); }
	FORCEINLINE void SET_FLOATING_HELP_TEXT_SCREEN_POSITION(int hudIndex, float x, float y) { return YimMenu::NativeInvoker::Invoke<1760, void>(hudIndex, x, y); }
	FORCEINLINE void SET_FLOATING_HELP_TEXT_WORLD_POSITION(int hudIndex, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1761, void>(hudIndex, x, y, z); }
	FORCEINLINE void SET_FLOATING_HELP_TEXT_TO_ENTITY(int hudIndex, Entity entity, float offsetX, float offsetY) { return YimMenu::NativeInvoker::Invoke<1762, void>(hudIndex, entity, offsetX, offsetY); }
	FORCEINLINE void SET_FLOATING_HELP_TEXT_STYLE(int hudIndex, int p1, int p2, int p3, int p4, int p5) { return YimMenu::NativeInvoker::Invoke<1763, void>(hudIndex, p1, p2, p3, p4, p5); }
	FORCEINLINE void CLEAR_FLOATING_HELP(int hudIndex, bool p1) { return YimMenu::NativeInvoker::Invoke<1764, void>(hudIndex, p1); }
	FORCEINLINE void CREATE_MP_GAMER_TAG_WITH_CREW_COLOR(Player player, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, int clanFlag, int r, int g, int b) { return YimMenu::NativeInvoker::Invoke<1765, void>(player, username, pointedClanTag, isRockstarClan, clanTag, clanFlag, r, g, b); }
	FORCEINLINE bool IS_MP_GAMER_TAG_MOVIE_ACTIVE() { return YimMenu::NativeInvoker::Invoke<1766, bool>(); }
	FORCEINLINE int CREATE_FAKE_MP_GAMER_TAG(Ped ped, const char* username, bool pointedClanTag, bool isRockstarClan, const char* clanTag, int clanFlag) { return YimMenu::NativeInvoker::Invoke<1767, int>(ped, username, pointedClanTag, isRockstarClan, clanTag, clanFlag); }
	FORCEINLINE void REMOVE_MP_GAMER_TAG(int gamerTagId) { return YimMenu::NativeInvoker::Invoke<1768, void>(gamerTagId); }
	FORCEINLINE bool IS_MP_GAMER_TAG_ACTIVE(int gamerTagId) { return YimMenu::NativeInvoker::Invoke<1769, bool>(gamerTagId); }
	FORCEINLINE bool IS_MP_GAMER_TAG_FREE(int gamerTagId) { return YimMenu::NativeInvoker::Invoke<1770, bool>(gamerTagId); }
	FORCEINLINE void SET_MP_GAMER_TAG_VISIBILITY(int gamerTagId, int component, bool toggle, Any p3) { return YimMenu::NativeInvoker::Invoke<1771, void>(gamerTagId, component, toggle, p3); }
	FORCEINLINE void SET_ALL_MP_GAMER_TAGS_VISIBILITY(int gamerTagId, bool toggle) { return YimMenu::NativeInvoker::Invoke<1772, void>(gamerTagId, toggle); }
	FORCEINLINE void SET_MP_GAMER_TAGS_SHOULD_USE_VEHICLE_HEALTH(int gamerTagId, bool toggle) { return YimMenu::NativeInvoker::Invoke<1773, void>(gamerTagId, toggle); }
	FORCEINLINE void SET_MP_GAMER_TAGS_SHOULD_USE_POINTS_HEALTH(int gamerTagId, bool toggle) { return YimMenu::NativeInvoker::Invoke<1774, void>(gamerTagId, toggle); }
	FORCEINLINE void SET_MP_GAMER_TAGS_POINT_HEALTH(int gamerTagId, int value, int maximumValue) { return YimMenu::NativeInvoker::Invoke<1775, void>(gamerTagId, value, maximumValue); }
	FORCEINLINE void SET_MP_GAMER_TAG_COLOUR(int gamerTagId, int component, int hudColorIndex) { return YimMenu::NativeInvoker::Invoke<1776, void>(gamerTagId, component, hudColorIndex); }
	FORCEINLINE void SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR(int gamerTagId, int hudColorIndex) { return YimMenu::NativeInvoker::Invoke<1777, void>(gamerTagId, hudColorIndex); }
	FORCEINLINE void SET_MP_GAMER_TAG_ALPHA(int gamerTagId, int component, int alpha) { return YimMenu::NativeInvoker::Invoke<1778, void>(gamerTagId, component, alpha); }
	FORCEINLINE void SET_MP_GAMER_TAG_WANTED_LEVEL(int gamerTagId, int wantedlvl) { return YimMenu::NativeInvoker::Invoke<1779, void>(gamerTagId, wantedlvl); }
	FORCEINLINE void SET_MP_GAMER_TAG_NUM_PACKAGES(int gamerTagId, int p1) { return YimMenu::NativeInvoker::Invoke<1780, void>(gamerTagId, p1); }
	FORCEINLINE void SET_MP_GAMER_TAG_NAME(int gamerTagId, const char* string) { return YimMenu::NativeInvoker::Invoke<1781, void>(gamerTagId, string); }
	FORCEINLINE bool IS_UPDATING_MP_GAMER_TAG_NAME_AND_CREW_DETAILS(int gamerTagId) { return YimMenu::NativeInvoker::Invoke<1782, bool>(gamerTagId); }
	FORCEINLINE void SET_MP_GAMER_TAG_BIG_TEXT(int gamerTagId, const char* string) { return YimMenu::NativeInvoker::Invoke<1783, void>(gamerTagId, string); }
	FORCEINLINE int GET_CURRENT_WEBPAGE_ID() { return YimMenu::NativeInvoker::Invoke<1784, int>(); }
	FORCEINLINE int GET_CURRENT_WEBSITE_ID() { return YimMenu::NativeInvoker::Invoke<1785, int>(); }
	FORCEINLINE int GET_GLOBAL_ACTIONSCRIPT_FLAG(int flagIndex) { return YimMenu::NativeInvoker::Invoke<1786, int>(flagIndex); }
	FORCEINLINE void RESET_GLOBAL_ACTIONSCRIPT_FLAG(int flagIndex) { return YimMenu::NativeInvoker::Invoke<1787, void>(flagIndex); }
	FORCEINLINE bool IS_WARNING_MESSAGE_READY_FOR_CONTROL() { return YimMenu::NativeInvoker::Invoke<1788, bool>(); }
	FORCEINLINE void SET_WARNING_MESSAGE(const char* titleMsg, int flags, const char* promptMsg, bool p3, int p4, const char* p5, const char* p6, bool showBackground, int errorCode) { return YimMenu::NativeInvoker::Invoke<1789, void>(titleMsg, flags, promptMsg, p3, p4, p5, p6, showBackground, errorCode); }
	FORCEINLINE void SET_WARNING_MESSAGE_WITH_HEADER(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, bool p4, Any p5, Any* showBackground, Any* p7, bool p8, Any p9) { return YimMenu::NativeInvoker::Invoke<1790, void>(entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, showBackground, p7, p8, p9); }
	FORCEINLINE void SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS(const char* entryHeader, const char* entryLine1, int instructionalKey, const char* entryLine2, bool p4, Any p5, Any additionalIntInfo, const char* additionalTextInfoLine1, const char* additionalTextInfoLine2, bool showBackground, int errorCode) { return YimMenu::NativeInvoker::Invoke<1791, void>(entryHeader, entryLine1, instructionalKey, entryLine2, p4, p5, additionalIntInfo, additionalTextInfoLine1, additionalTextInfoLine2, showBackground, errorCode); }
	FORCEINLINE void SET_WARNING_MESSAGE_WITH_HEADER_EXTENDED(const char* entryHeader, const char* entryLine1, int flags, const char* entryLine2, bool p4, Any p5, Any* p6, Any* p7, bool showBg, Any p9, Any p10) { return YimMenu::NativeInvoker::Invoke<1792, void>(entryHeader, entryLine1, flags, entryLine2, p4, p5, p6, p7, showBg, p9, p10); }
	FORCEINLINE void SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS_EXTENDED(const char* labelTitle, const char* labelMessage, int p2, int p3, const char* labelMessage2, bool p5, int p6, int p7, const char* p8, const char* p9, bool background, int errorCode) { return YimMenu::NativeInvoker::Invoke<1793, void>(labelTitle, labelMessage, p2, p3, labelMessage2, p5, p6, p7, p8, p9, background, errorCode); }
	FORCEINLINE Hash GET_WARNING_SCREEN_MESSAGE_HASH() { return YimMenu::NativeInvoker::Invoke<1794, Hash>(); }
	FORCEINLINE bool SET_WARNING_MESSAGE_OPTION_ITEMS(int index, const char* name, int cash, int rp, int lvl, int colour) { return YimMenu::NativeInvoker::Invoke<1795, bool>(index, name, cash, rp, lvl, colour); }
	FORCEINLINE bool SET_WARNING_MESSAGE_OPTION_HIGHLIGHT(Any p0) { return YimMenu::NativeInvoker::Invoke<1796, bool>(p0); }
	FORCEINLINE void REMOVE_WARNING_MESSAGE_OPTION_ITEMS() { return YimMenu::NativeInvoker::Invoke<1797, void>(); }
	FORCEINLINE bool IS_WARNING_MESSAGE_ACTIVE() { return YimMenu::NativeInvoker::Invoke<1798, bool>(); }
	FORCEINLINE void CLEAR_DYNAMIC_PAUSE_MENU_ERROR_MESSAGE() { return YimMenu::NativeInvoker::Invoke<1799, void>(); }
	FORCEINLINE void CUSTOM_MINIMAP_SET_ACTIVE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1800, void>(toggle); }
	FORCEINLINE void CUSTOM_MINIMAP_SET_BLIP_OBJECT(int spriteId) { return YimMenu::NativeInvoker::Invoke<1801, void>(spriteId); }
	FORCEINLINE int CUSTOM_MINIMAP_CREATE_BLIP(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1802, int>(x, y, z); }
	FORCEINLINE void CUSTOM_MINIMAP_CLEAR_BLIPS() { return YimMenu::NativeInvoker::Invoke<1803, void>(); }
	FORCEINLINE bool FORCE_SONAR_BLIPS_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1804, bool>(); }
	FORCEINLINE Blip GET_NORTH_BLID_INDEX() { return YimMenu::NativeInvoker::Invoke<1805, Blip>(); }
	FORCEINLINE void DISPLAY_PLAYER_NAME_TAGS_ON_BLIPS(bool toggle) { return YimMenu::NativeInvoker::Invoke<1806, void>(toggle); }
	FORCEINLINE void DRAW_FRONTEND_BACKGROUND_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1807, void>(); }
	FORCEINLINE void DRAW_HUD_OVER_FADE_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1808, void>(); }
	FORCEINLINE void ACTIVATE_FRONTEND_MENU(Hash menuhash, bool togglePause, int component) { return YimMenu::NativeInvoker::Invoke<1809, void>(menuhash, togglePause, component); }
	FORCEINLINE void RESTART_FRONTEND_MENU(Hash menuHash, int p1) { return YimMenu::NativeInvoker::Invoke<1810, void>(menuHash, p1); }
	FORCEINLINE Hash GET_CURRENT_FRONTEND_MENU_VERSION() { return YimMenu::NativeInvoker::Invoke<1811, Hash>(); }
	FORCEINLINE void SET_PAUSE_MENU_ACTIVE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1812, void>(toggle); }
	FORCEINLINE void DISABLE_FRONTEND_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1813, void>(); }
	FORCEINLINE void SUPPRESS_FRONTEND_RENDERING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1814, void>(); }
	FORCEINLINE void ALLOW_PAUSE_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1815, void>(); }
	FORCEINLINE void SET_FRONTEND_ACTIVE(bool active) { return YimMenu::NativeInvoker::Invoke<1816, void>(active); }
	FORCEINLINE bool IS_PAUSE_MENU_ACTIVE() { return YimMenu::NativeInvoker::Invoke<1817, bool>(); }
	FORCEINLINE bool IS_STORE_PENDING_NETWORK_SHUTDOWN_TO_OPEN() { return YimMenu::NativeInvoker::Invoke<1818, bool>(); }
	FORCEINLINE int GET_PAUSE_MENU_STATE() { return YimMenu::NativeInvoker::Invoke<1819, int>(); }
	FORCEINLINE Vector3 GET_PAUSE_MENU_POSITION() { return YimMenu::NativeInvoker::Invoke<1820, Vector3>(); }
	FORCEINLINE bool IS_PAUSE_MENU_RESTARTING() { return YimMenu::NativeInvoker::Invoke<1821, bool>(); }
	FORCEINLINE void FORCE_SCRIPTED_GFX_WHEN_FRONTEND_ACTIVE(const char* p0) { return YimMenu::NativeInvoker::Invoke<1822, void>(p0); }
	FORCEINLINE void PAUSE_MENUCEPTION_GO_DEEPER(int page) { return YimMenu::NativeInvoker::Invoke<1823, void>(page); }
	FORCEINLINE void PAUSE_MENUCEPTION_THE_KICK() { return YimMenu::NativeInvoker::Invoke<1824, void>(); }
	FORCEINLINE void PAUSE_TOGGLE_FULLSCREEN_MAP(Any p0) { return YimMenu::NativeInvoker::Invoke<1825, void>(p0); }
	FORCEINLINE void PAUSE_MENU_ACTIVATE_CONTEXT(Hash contextHash) { return YimMenu::NativeInvoker::Invoke<1826, void>(contextHash); }
	FORCEINLINE void PAUSE_MENU_DEACTIVATE_CONTEXT(Hash contextHash) { return YimMenu::NativeInvoker::Invoke<1827, void>(contextHash); }
	FORCEINLINE bool PAUSE_MENU_IS_CONTEXT_ACTIVE(Hash contextHash) { return YimMenu::NativeInvoker::Invoke<1828, bool>(contextHash); }
	FORCEINLINE bool PAUSE_MENU_IS_CONTEXT_MENU_ACTIVE() { return YimMenu::NativeInvoker::Invoke<1829, bool>(); }
	FORCEINLINE int PAUSE_MENU_GET_HAIR_COLOUR_INDEX() { return YimMenu::NativeInvoker::Invoke<1830, int>(); }
	FORCEINLINE int PAUSE_MENU_GET_MOUSE_HOVER_INDEX() { return YimMenu::NativeInvoker::Invoke<1831, int>(); }
	FORCEINLINE int PAUSE_MENU_GET_MOUSE_HOVER_UNIQUE_ID() { return YimMenu::NativeInvoker::Invoke<1832, int>(); }
	FORCEINLINE bool PAUSE_MENU_GET_MOUSE_CLICK_EVENT(Any* p0, Any* p1, Any* p2) { return YimMenu::NativeInvoker::Invoke<1833, bool>(p0, p1, p2); }
	FORCEINLINE void PAUSE_MENU_REDRAW_INSTRUCTIONAL_BUTTONS(int p0) { return YimMenu::NativeInvoker::Invoke<1834, void>(p0); }
	FORCEINLINE void PAUSE_MENU_SET_BUSY_SPINNER(bool p0, int position, int spinnerIndex) { return YimMenu::NativeInvoker::Invoke<1835, void>(p0, position, spinnerIndex); }
	FORCEINLINE void PAUSE_MENU_SET_WARN_ON_TAB_CHANGE(bool p0) { return YimMenu::NativeInvoker::Invoke<1836, void>(p0); }
	FORCEINLINE bool IS_FRONTEND_READY_FOR_CONTROL() { return YimMenu::NativeInvoker::Invoke<1837, bool>(); }
	FORCEINLINE void TAKE_CONTROL_OF_FRONTEND() { return YimMenu::NativeInvoker::Invoke<1838, void>(); }
	FORCEINLINE void RELEASE_CONTROL_OF_FRONTEND() { return YimMenu::NativeInvoker::Invoke<1839, void>(); }
	FORCEINLINE bool CODE_WANTS_SCRIPT_TO_TAKE_CONTROL() { return YimMenu::NativeInvoker::Invoke<1840, bool>(); }
	FORCEINLINE int GET_SCREEN_CODE_WANTS_SCRIPT_TO_CONTROL() { return YimMenu::NativeInvoker::Invoke<1841, int>(); }
	FORCEINLINE bool IS_NAVIGATING_MENU_CONTENT() { return YimMenu::NativeInvoker::Invoke<1842, bool>(); }
	FORCEINLINE bool HAS_MENU_TRIGGER_EVENT_OCCURRED() { return YimMenu::NativeInvoker::Invoke<1843, bool>(); }
	FORCEINLINE bool HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED() { return YimMenu::NativeInvoker::Invoke<1844, bool>(); }
	FORCEINLINE void SET_SAVEGAME_LIST_UNIQUE_ID(Any p0) { return YimMenu::NativeInvoker::Invoke<1845, void>(p0); }
	FORCEINLINE void GET_MENU_TRIGGER_EVENT_DETAILS(int* lastItemMenuId, int* selectedItemUniqueId) { return YimMenu::NativeInvoker::Invoke<1846, void>(lastItemMenuId, selectedItemUniqueId); }
	FORCEINLINE void GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS(int* lastItemMenuId, int* selectedItemMenuId, int* selectedItemUniqueId) { return YimMenu::NativeInvoker::Invoke<1847, void>(lastItemMenuId, selectedItemMenuId, selectedItemUniqueId); }
	FORCEINLINE bool GET_PM_PLAYER_CREW_COLOR(int* r, int* g, int* b) { return YimMenu::NativeInvoker::Invoke<1848, bool>(r, g, b); }
	FORCEINLINE bool GET_MENU_PED_INT_STAT(Any p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<1849, bool>(p0, p1); }
	FORCEINLINE bool GET_CHARACTER_MENU_PED_INT_STAT(Any p0, Any* p1, Any p2) { return YimMenu::NativeInvoker::Invoke<1850, bool>(p0, p1, p2); }
	FORCEINLINE bool GET_MENU_PED_MASKED_INT_STAT(Hash statHash, int* outValue, int mask, bool p3) { return YimMenu::NativeInvoker::Invoke<1851, bool>(statHash, outValue, mask, p3); }
	FORCEINLINE bool GET_CHARACTER_MENU_PED_MASKED_INT_STAT(Hash statHash, Any* outValue, int p2, int mask, bool p4) { return YimMenu::NativeInvoker::Invoke<1852, bool>(statHash, outValue, p2, mask, p4); }
	FORCEINLINE bool GET_MENU_PED_FLOAT_STAT(Hash statHash, float* outValue) { return YimMenu::NativeInvoker::Invoke<1853, bool>(statHash, outValue); }
	FORCEINLINE bool GET_CHARACTER_MENU_PED_FLOAT_STAT(float statHash, float* outValue, bool p2) { return YimMenu::NativeInvoker::Invoke<1854, bool>(statHash, outValue, p2); }
	FORCEINLINE bool GET_MENU_PED_BOOL_STAT(Hash statHash, bool* outValue) { return YimMenu::NativeInvoker::Invoke<1855, bool>(statHash, outValue); }
	FORCEINLINE void CLEAR_PED_IN_PAUSE_MENU() { return YimMenu::NativeInvoker::Invoke<1856, void>(); }
	FORCEINLINE void GIVE_PED_TO_PAUSE_MENU(Ped ped, int p1) { return YimMenu::NativeInvoker::Invoke<1857, void>(ped, p1); }
	FORCEINLINE void SET_PAUSE_MENU_PED_LIGHTING(bool state) { return YimMenu::NativeInvoker::Invoke<1858, void>(state); }
	FORCEINLINE void SET_PAUSE_MENU_PED_SLEEP_STATE(bool state) { return YimMenu::NativeInvoker::Invoke<1859, void>(state); }
	FORCEINLINE void OPEN_ONLINE_POLICIES_MENU() { return YimMenu::NativeInvoker::Invoke<1860, void>(); }
	FORCEINLINE bool ARE_ONLINE_POLICIES_UP_TO_DATE() { return YimMenu::NativeInvoker::Invoke<1861, bool>(); }
	FORCEINLINE bool IS_ONLINE_POLICIES_MENU_ACTIVE() { return YimMenu::NativeInvoker::Invoke<1862, bool>(); }
	FORCEINLINE void OPEN_SOCIAL_CLUB_MENU(Hash menu) { return YimMenu::NativeInvoker::Invoke<1863, void>(menu); }
	FORCEINLINE void CLOSE_SOCIAL_CLUB_MENU() { return YimMenu::NativeInvoker::Invoke<1864, void>(); }
	FORCEINLINE void SET_SOCIAL_CLUB_TOUR(const char* name) { return YimMenu::NativeInvoker::Invoke<1865, void>(name); }
	FORCEINLINE bool IS_SOCIAL_CLUB_ACTIVE() { return YimMenu::NativeInvoker::Invoke<1866, bool>(); }
	FORCEINLINE void SET_TEXT_INPUT_BOX_ENABLED(bool p0) { return YimMenu::NativeInvoker::Invoke<1867, void>(p0); }
	FORCEINLINE void FORCE_CLOSE_TEXT_INPUT_BOX() { return YimMenu::NativeInvoker::Invoke<1868, void>(); }
	FORCEINLINE void SET_ALLOW_COMMA_ON_TEXT_INPUT(Any p0) { return YimMenu::NativeInvoker::Invoke<1869, void>(p0); }
	FORCEINLINE void OVERRIDE_MP_TEXT_CHAT_TEAM_STRING(Hash gxtEntryHash) { return YimMenu::NativeInvoker::Invoke<1870, void>(gxtEntryHash); }
	FORCEINLINE bool IS_MP_TEXT_CHAT_TYPING() { return YimMenu::NativeInvoker::Invoke<1871, bool>(); }
	FORCEINLINE void CLOSE_MP_TEXT_CHAT() { return YimMenu::NativeInvoker::Invoke<1872, void>(); }
	FORCEINLINE void MP_TEXT_CHAT_IS_TEAM_JOB(Any p0) { return YimMenu::NativeInvoker::Invoke<1873, void>(p0); }
	FORCEINLINE void OVERRIDE_MP_TEXT_CHAT_COLOR(int p0, int hudColor) { return YimMenu::NativeInvoker::Invoke<1874, void>(p0, hudColor); }
	FORCEINLINE void MP_TEXT_CHAT_DISABLE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1875, void>(toggle); }
	FORCEINLINE void FLAG_PLAYER_CONTEXT_IN_TOURNAMENT(bool toggle) { return YimMenu::NativeInvoker::Invoke<1876, void>(toggle); }
	FORCEINLINE void SET_PED_HAS_AI_BLIP(Ped ped, bool hasCone) { return YimMenu::NativeInvoker::Invoke<1877, void>(ped, hasCone); }
	FORCEINLINE void SET_PED_HAS_AI_BLIP_WITH_COLOUR(Ped ped, bool hasCone, int color) { return YimMenu::NativeInvoker::Invoke<1878, void>(ped, hasCone, color); }
	FORCEINLINE bool DOES_PED_HAVE_AI_BLIP(Ped ped) { return YimMenu::NativeInvoker::Invoke<1879, bool>(ped); }
	FORCEINLINE void SET_PED_AI_BLIP_GANG_ID(Ped ped, int gangId) { return YimMenu::NativeInvoker::Invoke<1880, void>(ped, gangId); }
	FORCEINLINE void SET_PED_AI_BLIP_HAS_CONE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<1881, void>(ped, toggle); }
	FORCEINLINE void SET_PED_AI_BLIP_FORCED_ON(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<1882, void>(ped, toggle); }
	FORCEINLINE void SET_PED_AI_BLIP_NOTICE_RANGE(Ped ped, float range) { return YimMenu::NativeInvoker::Invoke<1883, void>(ped, range); }
	FORCEINLINE void SET_PED_AI_BLIP_SPRITE(Ped ped, int spriteId) { return YimMenu::NativeInvoker::Invoke<1884, void>(ped, spriteId); }
	FORCEINLINE Blip GET_AI_PED_PED_BLIP_INDEX(Ped ped) { return YimMenu::NativeInvoker::Invoke<1885, Blip>(ped); }
	FORCEINLINE Blip GET_AI_PED_VEHICLE_BLIP_INDEX(Ped ped) { return YimMenu::NativeInvoker::Invoke<1886, Blip>(ped); }
	FORCEINLINE bool HAS_DIRECTOR_MODE_BEEN_LAUNCHED_BY_CODE() { return YimMenu::NativeInvoker::Invoke<1887, bool>(); }
	FORCEINLINE void SET_DIRECTOR_MODE_LAUNCHED_BY_SCRIPT() { return YimMenu::NativeInvoker::Invoke<1888, void>(); }
	FORCEINLINE void SET_PLAYER_IS_IN_DIRECTOR_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1889, void>(toggle); }
	FORCEINLINE void SET_DIRECTOR_MODE_AVAILABLE(bool toggle) { return YimMenu::NativeInvoker::Invoke<1890, void>(toggle); }
	FORCEINLINE void HIDE_HUDMARKERS_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<1891, void>(); }
}

namespace INTERIOR
{
	FORCEINLINE float GET_INTERIOR_HEADING(Interior interior) { return YimMenu::NativeInvoker::Invoke<1892, float>(interior); }
	FORCEINLINE void GET_INTERIOR_LOCATION_AND_NAMEHASH(Interior interior, Vector3* position, Hash* nameHash) { return YimMenu::NativeInvoker::Invoke<1893, void>(interior, position, nameHash); }
	FORCEINLINE int GET_INTERIOR_GROUP_ID(Interior interior) { return YimMenu::NativeInvoker::Invoke<1894, int>(interior); }
	FORCEINLINE Vector3 GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(Interior interior, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1895, Vector3>(interior, x, y, z); }
	FORCEINLINE bool IS_INTERIOR_SCENE() { return YimMenu::NativeInvoker::Invoke<1896, bool>(); }
	FORCEINLINE bool IS_VALID_INTERIOR(Interior interior) { return YimMenu::NativeInvoker::Invoke<1897, bool>(interior); }
	FORCEINLINE void CLEAR_ROOM_FOR_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1898, void>(entity); }
	FORCEINLINE void FORCE_ROOM_FOR_ENTITY(Entity entity, Interior interior, Hash roomHashKey) { return YimMenu::NativeInvoker::Invoke<1899, void>(entity, interior, roomHashKey); }
	FORCEINLINE Hash GET_ROOM_KEY_FROM_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1900, Hash>(entity); }
	FORCEINLINE Hash GET_KEY_FOR_ENTITY_IN_ROOM(Entity entity) { return YimMenu::NativeInvoker::Invoke<1901, Hash>(entity); }
	FORCEINLINE Interior GET_INTERIOR_FROM_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1902, Interior>(entity); }
	FORCEINLINE void RETAIN_ENTITY_IN_INTERIOR(Entity entity, Interior interior) { return YimMenu::NativeInvoker::Invoke<1903, void>(entity, interior); }
	FORCEINLINE void CLEAR_INTERIOR_STATE_OF_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<1904, void>(entity); }
	FORCEINLINE void FORCE_ACTIVATING_TRACKING_ON_ENTITY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<1905, void>(p0, p1); }
	FORCEINLINE void FORCE_ROOM_FOR_GAME_VIEWPORT(int interiorID, Hash roomHashKey) { return YimMenu::NativeInvoker::Invoke<1906, void>(interiorID, roomHashKey); }
	FORCEINLINE void SET_ROOM_FOR_GAME_VIEWPORT_BY_NAME(const char* roomName) { return YimMenu::NativeInvoker::Invoke<1907, void>(roomName); }
	FORCEINLINE void SET_ROOM_FOR_GAME_VIEWPORT_BY_KEY(Hash roomHashKey) { return YimMenu::NativeInvoker::Invoke<1908, void>(roomHashKey); }
	FORCEINLINE Hash GET_ROOM_KEY_FOR_GAME_VIEWPORT() { return YimMenu::NativeInvoker::Invoke<1909, Hash>(); }
	FORCEINLINE void CLEAR_ROOM_FOR_GAME_VIEWPORT() { return YimMenu::NativeInvoker::Invoke<1910, void>(); }
	FORCEINLINE Interior GET_INTERIOR_FROM_PRIMARY_VIEW() { return YimMenu::NativeInvoker::Invoke<1911, Interior>(); }
	FORCEINLINE Interior GET_INTERIOR_AT_COORDS(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1912, Interior>(x, y, z); }
	FORCEINLINE void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(Pickup pickup, const char* roomName) { return YimMenu::NativeInvoker::Invoke<1913, void>(pickup, roomName); }
	FORCEINLINE void PIN_INTERIOR_IN_MEMORY(Interior interior) { return YimMenu::NativeInvoker::Invoke<1914, void>(interior); }
	FORCEINLINE void UNPIN_INTERIOR(Interior interior) { return YimMenu::NativeInvoker::Invoke<1915, void>(interior); }
	FORCEINLINE bool IS_INTERIOR_READY(Interior interior) { return YimMenu::NativeInvoker::Invoke<1916, bool>(interior); }
	FORCEINLINE bool SET_INTERIOR_IN_USE(Interior interior) { return YimMenu::NativeInvoker::Invoke<1917, bool>(interior); }
	FORCEINLINE Interior GET_INTERIOR_AT_COORDS_WITH_TYPE(float x, float y, float z, const char* interiorType) { return YimMenu::NativeInvoker::Invoke<1918, Interior>(x, y, z, interiorType); }
	FORCEINLINE Interior GET_INTERIOR_AT_COORDS_WITH_TYPEHASH(float x, float y, float z, Hash typeHash) { return YimMenu::NativeInvoker::Invoke<1919, Interior>(x, y, z, typeHash); }
	FORCEINLINE void ACTIVATE_INTERIOR_GROUPS_USING_CAMERA() { return YimMenu::NativeInvoker::Invoke<1920, void>(); }
	FORCEINLINE bool IS_COLLISION_MARKED_OUTSIDE(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1921, bool>(x, y, z); }
	FORCEINLINE Interior GET_INTERIOR_FROM_COLLISION(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<1922, Interior>(x, y, z); }
	FORCEINLINE void ENABLE_STADIUM_PROBES_THIS_FRAME(bool toggle) { return YimMenu::NativeInvoker::Invoke<1923, void>(toggle); }
	FORCEINLINE void ACTIVATE_INTERIOR_ENTITY_SET(Interior interior, const char* entitySetName) { return YimMenu::NativeInvoker::Invoke<1924, void>(interior, entitySetName); }
	FORCEINLINE void DEACTIVATE_INTERIOR_ENTITY_SET(Interior interior, const char* entitySetName) { return YimMenu::NativeInvoker::Invoke<1925, void>(interior, entitySetName); }
	FORCEINLINE bool IS_INTERIOR_ENTITY_SET_ACTIVE(Interior interior, const char* entitySetName) { return YimMenu::NativeInvoker::Invoke<1926, bool>(interior, entitySetName); }
	FORCEINLINE void SET_INTERIOR_ENTITY_SET_TINT_INDEX(Interior interior, const char* entitySetName, int color) { return YimMenu::NativeInvoker::Invoke<1927, void>(interior, entitySetName, color); }
	FORCEINLINE void REFRESH_INTERIOR(Interior interior) { return YimMenu::NativeInvoker::Invoke<1928, void>(interior); }
	FORCEINLINE void ENABLE_EXTERIOR_CULL_MODEL_THIS_FRAME(Hash mapObjectHash) { return YimMenu::NativeInvoker::Invoke<1929, void>(mapObjectHash); }
	FORCEINLINE void ENABLE_SHADOW_CULL_MODEL_THIS_FRAME(Hash mapObjectHash) { return YimMenu::NativeInvoker::Invoke<1930, void>(mapObjectHash); }
	FORCEINLINE void DISABLE_INTERIOR(Interior interior, bool toggle) { return YimMenu::NativeInvoker::Invoke<1931, void>(interior, toggle); }
	FORCEINLINE bool IS_INTERIOR_DISABLED(Interior interior) { return YimMenu::NativeInvoker::Invoke<1932, bool>(interior); }
	FORCEINLINE void CAP_INTERIOR(Interior interior, bool toggle) { return YimMenu::NativeInvoker::Invoke<1933, void>(interior, toggle); }
	FORCEINLINE bool IS_INTERIOR_CAPPED(Interior interior) { return YimMenu::NativeInvoker::Invoke<1934, bool>(interior); }
	FORCEINLINE void DISABLE_METRO_SYSTEM(bool toggle) { return YimMenu::NativeInvoker::Invoke<1935, void>(toggle); }
	FORCEINLINE void SET_IS_EXTERIOR_ONLY(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<1936, void>(entity, toggle); }
}

namespace ITEMSET
{
	FORCEINLINE ScrHandle CREATE_ITEMSET(bool p0) { return YimMenu::NativeInvoker::Invoke<1937, ScrHandle>(p0); }
	FORCEINLINE void DESTROY_ITEMSET(ScrHandle itemset) { return YimMenu::NativeInvoker::Invoke<1938, void>(itemset); }
	FORCEINLINE bool IS_ITEMSET_VALID(ScrHandle itemset) { return YimMenu::NativeInvoker::Invoke<1939, bool>(itemset); }
	FORCEINLINE bool ADD_TO_ITEMSET(ScrHandle item, ScrHandle itemset) { return YimMenu::NativeInvoker::Invoke<1940, bool>(item, itemset); }
	FORCEINLINE void REMOVE_FROM_ITEMSET(ScrHandle item, ScrHandle itemset) { return YimMenu::NativeInvoker::Invoke<1941, void>(item, itemset); }
	FORCEINLINE int GET_ITEMSET_SIZE(ScrHandle itemset) { return YimMenu::NativeInvoker::Invoke<1942, int>(itemset); }
	FORCEINLINE ScrHandle GET_INDEXED_ITEM_IN_ITEMSET(int index, ScrHandle itemset) { return YimMenu::NativeInvoker::Invoke<1943, ScrHandle>(index, itemset); }
	FORCEINLINE bool IS_IN_ITEMSET(ScrHandle item, ScrHandle itemset) { return YimMenu::NativeInvoker::Invoke<1944, bool>(item, itemset); }
	FORCEINLINE void CLEAN_ITEMSET(ScrHandle itemset) { return YimMenu::NativeInvoker::Invoke<1945, void>(itemset); }
}

namespace LOADINGSCREEN
{
	FORCEINLINE bool LOBBY_AUTO_MULTIPLAYER_MENU() { return YimMenu::NativeInvoker::Invoke<1946, bool>(); }
	FORCEINLINE bool LOBBY_AUTO_MULTIPLAYER_FREEMODE() { return YimMenu::NativeInvoker::Invoke<1947, bool>(); }
	FORCEINLINE void LOBBY_SET_AUTO_MULTIPLAYER(bool toggle) { return YimMenu::NativeInvoker::Invoke<1948, void>(toggle); }
	FORCEINLINE bool LOBBY_AUTO_MULTIPLAYER_EVENT() { return YimMenu::NativeInvoker::Invoke<1949, bool>(); }
	FORCEINLINE void LOBBY_SET_AUTO_MULTIPLAYER_EVENT(bool toggle) { return YimMenu::NativeInvoker::Invoke<1950, void>(toggle); }
	FORCEINLINE bool LOBBY_AUTO_MULTIPLAYER_RANDOM_JOB() { return YimMenu::NativeInvoker::Invoke<1951, bool>(); }
	FORCEINLINE void LOBBY_SET_AUTO_MP_RANDOM_JOB(bool toggle) { return YimMenu::NativeInvoker::Invoke<1952, void>(toggle); }
	FORCEINLINE void SHUTDOWN_SESSION_CLEARS_AUTO_MULTIPLAYER(bool toggle) { return YimMenu::NativeInvoker::Invoke<1953, void>(toggle); }
}

namespace LOCALIZATION
{
	FORCEINLINE int LOCALIZATION_GET_SYSTEM_LANGUAGE() { return YimMenu::NativeInvoker::Invoke<1954, int>(); }
	FORCEINLINE int GET_CURRENT_LANGUAGE() { return YimMenu::NativeInvoker::Invoke<1955, int>(); }
	FORCEINLINE int LOCALIZATION_GET_SYSTEM_DATE_TYPE() { return YimMenu::NativeInvoker::Invoke<1956, int>(); }
}

namespace MISC
{
	FORCEINLINE int GET_ALLOCATED_STACK_SIZE() { return YimMenu::NativeInvoker::Invoke<1957, int>(); }
	FORCEINLINE int GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(int stackSize) { return YimMenu::NativeInvoker::Invoke<1958, int>(stackSize); }
	FORCEINLINE void SET_RANDOM_SEED(int seed) { return YimMenu::NativeInvoker::Invoke<1959, void>(seed); }
	FORCEINLINE void SET_TIME_SCALE(float timeScale) { return YimMenu::NativeInvoker::Invoke<1960, void>(timeScale); }
	FORCEINLINE void SET_MISSION_FLAG(bool toggle) { return YimMenu::NativeInvoker::Invoke<1961, void>(toggle); }
	FORCEINLINE bool GET_MISSION_FLAG() { return YimMenu::NativeInvoker::Invoke<1962, bool>(); }
	FORCEINLINE void SET_RANDOM_EVENT_FLAG(bool toggle) { return YimMenu::NativeInvoker::Invoke<1963, void>(toggle); }
	FORCEINLINE bool GET_RANDOM_EVENT_FLAG() { return YimMenu::NativeInvoker::Invoke<1964, bool>(); }
	FORCEINLINE const char* GET_CONTENT_TO_LOAD() { return YimMenu::NativeInvoker::Invoke<1965, const char*>(); }
	FORCEINLINE void ACTIVITY_FEED_CREATE(const char* p0, const char* p1) { return YimMenu::NativeInvoker::Invoke<1966, void>(p0, p1); }
	FORCEINLINE void ACTIVITY_FEED_ADD_SUBSTRING_TO_CAPTION(const char* p0) { return YimMenu::NativeInvoker::Invoke<1967, void>(p0); }
	FORCEINLINE void ACTIVITY_FEED_ADD_LITERAL_SUBSTRING_TO_CAPTION(const char* p0) { return YimMenu::NativeInvoker::Invoke<1968, void>(p0); }
	FORCEINLINE void ACTIVITY_FEED_ADD_INT_TO_CAPTION(Any p0) { return YimMenu::NativeInvoker::Invoke<1969, void>(p0); }
	FORCEINLINE void ACTIVITY_FEED_LARGE_IMAGE_URL(const char* p0) { return YimMenu::NativeInvoker::Invoke<1970, void>(p0); }
	FORCEINLINE void ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE(const char* p0, const char* p1) { return YimMenu::NativeInvoker::Invoke<1971, void>(p0, p1); }
	FORCEINLINE void ACTIVITY_FEED_ACTION_START_WITH_COMMAND_LINE_ADD(const char* p0) { return YimMenu::NativeInvoker::Invoke<1972, void>(p0); }
	FORCEINLINE void ACTIVITY_FEED_POST() { return YimMenu::NativeInvoker::Invoke<1973, void>(); }
	FORCEINLINE void ACTIVITY_FEED_ONLINE_PLAYED_WITH_POST(const char* p0) { return YimMenu::NativeInvoker::Invoke<1974, void>(p0); }
	FORCEINLINE bool HAS_RESUMED_FROM_SUSPEND() { return YimMenu::NativeInvoker::Invoke<1975, bool>(); }
	FORCEINLINE void SET_SCRIPT_HIGH_PRIO(bool toggle) { return YimMenu::NativeInvoker::Invoke<1976, void>(toggle); }
	FORCEINLINE void SET_THIS_IS_A_TRIGGER_SCRIPT(bool toggle) { return YimMenu::NativeInvoker::Invoke<1977, void>(toggle); }
	FORCEINLINE void INFORM_CODE_OF_CONTENT_ID_OF_CURRENT_UGC_MISSION(const char* p0) { return YimMenu::NativeInvoker::Invoke<1978, void>(p0); }
	FORCEINLINE bool GET_BASE_ELEMENT_LOCATION_FROM_METADATA_BLOCK(Any* p0, Any* p1, Any p2, bool p3) { return YimMenu::NativeInvoker::Invoke<1979, bool>(p0, p1, p2, p3); }
	FORCEINLINE Hash GET_PREV_WEATHER_TYPE_HASH_NAME() { return YimMenu::NativeInvoker::Invoke<1980, Hash>(); }
	FORCEINLINE Hash GET_NEXT_WEATHER_TYPE_HASH_NAME() { return YimMenu::NativeInvoker::Invoke<1981, Hash>(); }
	FORCEINLINE bool IS_PREV_WEATHER_TYPE(const char* weatherType) { return YimMenu::NativeInvoker::Invoke<1982, bool>(weatherType); }
	FORCEINLINE bool IS_NEXT_WEATHER_TYPE(const char* weatherType) { return YimMenu::NativeInvoker::Invoke<1983, bool>(weatherType); }
	FORCEINLINE void SET_WEATHER_TYPE_PERSIST(const char* weatherType) { return YimMenu::NativeInvoker::Invoke<1984, void>(weatherType); }
	FORCEINLINE void SET_WEATHER_TYPE_NOW_PERSIST(const char* weatherType) { return YimMenu::NativeInvoker::Invoke<1985, void>(weatherType); }
	FORCEINLINE void SET_WEATHER_TYPE_NOW(const char* weatherType) { return YimMenu::NativeInvoker::Invoke<1986, void>(weatherType); }
	FORCEINLINE void SET_WEATHER_TYPE_OVERTIME_PERSIST(const char* weatherType, float time) { return YimMenu::NativeInvoker::Invoke<1987, void>(weatherType, time); }
	FORCEINLINE void SET_RANDOM_WEATHER_TYPE() { return YimMenu::NativeInvoker::Invoke<1988, void>(); }
	FORCEINLINE void CLEAR_WEATHER_TYPE_PERSIST() { return YimMenu::NativeInvoker::Invoke<1989, void>(); }
	FORCEINLINE void CLEAR_WEATHER_TYPE_NOW_PERSIST_NETWORK(int milliseconds) { return YimMenu::NativeInvoker::Invoke<1990, void>(milliseconds); }
	FORCEINLINE void GET_CURR_WEATHER_STATE(Hash* weatherType1, Hash* weatherType2, float* percentWeather2) { return YimMenu::NativeInvoker::Invoke<1991, void>(weatherType1, weatherType2, percentWeather2); }
	FORCEINLINE void SET_CURR_WEATHER_STATE(Hash weatherType1, Hash weatherType2, float percentWeather2) { return YimMenu::NativeInvoker::Invoke<1992, void>(weatherType1, weatherType2, percentWeather2); }
	FORCEINLINE void SET_OVERRIDE_WEATHER(const char* weatherType) { return YimMenu::NativeInvoker::Invoke<1993, void>(weatherType); }
	FORCEINLINE void SET_OVERRIDE_WEATHEREX(const char* weatherType, bool p1) { return YimMenu::NativeInvoker::Invoke<1994, void>(weatherType, p1); }
	FORCEINLINE void CLEAR_OVERRIDE_WEATHER() { return YimMenu::NativeInvoker::Invoke<1995, void>(); }
	FORCEINLINE void WATER_OVERRIDE_SET_SHOREWAVEAMPLITUDE(float amplitude) { return YimMenu::NativeInvoker::Invoke<1996, void>(amplitude); }
	FORCEINLINE void WATER_OVERRIDE_SET_SHOREWAVEMINAMPLITUDE(float minAmplitude) { return YimMenu::NativeInvoker::Invoke<1997, void>(minAmplitude); }
	FORCEINLINE void WATER_OVERRIDE_SET_SHOREWAVEMAXAMPLITUDE(float maxAmplitude) { return YimMenu::NativeInvoker::Invoke<1998, void>(maxAmplitude); }
	FORCEINLINE void WATER_OVERRIDE_SET_OCEANNOISEMINAMPLITUDE(float minAmplitude) { return YimMenu::NativeInvoker::Invoke<1999, void>(minAmplitude); }
	FORCEINLINE void WATER_OVERRIDE_SET_OCEANWAVEAMPLITUDE(float amplitude) { return YimMenu::NativeInvoker::Invoke<2000, void>(amplitude); }
	FORCEINLINE void WATER_OVERRIDE_SET_OCEANWAVEMINAMPLITUDE(float minAmplitude) { return YimMenu::NativeInvoker::Invoke<2001, void>(minAmplitude); }
	FORCEINLINE void WATER_OVERRIDE_SET_OCEANWAVEMAXAMPLITUDE(float maxAmplitude) { return YimMenu::NativeInvoker::Invoke<2002, void>(maxAmplitude); }
	FORCEINLINE void WATER_OVERRIDE_SET_RIPPLEBUMPINESS(float bumpiness) { return YimMenu::NativeInvoker::Invoke<2003, void>(bumpiness); }
	FORCEINLINE void WATER_OVERRIDE_SET_RIPPLEMINBUMPINESS(float minBumpiness) { return YimMenu::NativeInvoker::Invoke<2004, void>(minBumpiness); }
	FORCEINLINE void WATER_OVERRIDE_SET_RIPPLEMAXBUMPINESS(float maxBumpiness) { return YimMenu::NativeInvoker::Invoke<2005, void>(maxBumpiness); }
	FORCEINLINE void WATER_OVERRIDE_SET_RIPPLEDISTURB(float disturb) { return YimMenu::NativeInvoker::Invoke<2006, void>(disturb); }
	FORCEINLINE void WATER_OVERRIDE_SET_STRENGTH(float strength) { return YimMenu::NativeInvoker::Invoke<2007, void>(strength); }
	FORCEINLINE void WATER_OVERRIDE_FADE_IN(float p0) { return YimMenu::NativeInvoker::Invoke<2008, void>(p0); }
	FORCEINLINE void WATER_OVERRIDE_FADE_OUT(float p0) { return YimMenu::NativeInvoker::Invoke<2009, void>(p0); }
	FORCEINLINE void SET_WIND(float speed) { return YimMenu::NativeInvoker::Invoke<2010, void>(speed); }
	FORCEINLINE void SET_WIND_SPEED(float speed) { return YimMenu::NativeInvoker::Invoke<2011, void>(speed); }
	FORCEINLINE float GET_WIND_SPEED() { return YimMenu::NativeInvoker::Invoke<2012, float>(); }
	FORCEINLINE void SET_WIND_DIRECTION(float direction) { return YimMenu::NativeInvoker::Invoke<2013, void>(direction); }
	FORCEINLINE Vector3 GET_WIND_DIRECTION() { return YimMenu::NativeInvoker::Invoke<2014, Vector3>(); }
	FORCEINLINE void SET_RAIN(float intensity) { return YimMenu::NativeInvoker::Invoke<2015, void>(intensity); }
	FORCEINLINE float GET_RAIN_LEVEL() { return YimMenu::NativeInvoker::Invoke<2016, float>(); }
	FORCEINLINE void SET_SNOW(float level) { return YimMenu::NativeInvoker::Invoke<2017, void>(level); }
	FORCEINLINE float GET_SNOW_LEVEL() { return YimMenu::NativeInvoker::Invoke<2018, float>(); }
	FORCEINLINE void FORCE_LIGHTNING_FLASH() { return YimMenu::NativeInvoker::Invoke<2019, void>(); }
	FORCEINLINE void SET_CLOUD_SETTINGS_OVERRIDE(const char* p0) { return YimMenu::NativeInvoker::Invoke<2020, void>(p0); }
	FORCEINLINE void PRELOAD_CLOUD_HAT(const char* name) { return YimMenu::NativeInvoker::Invoke<2021, void>(name); }
	FORCEINLINE void LOAD_CLOUD_HAT(const char* name, float transitionTime) { return YimMenu::NativeInvoker::Invoke<2022, void>(name, transitionTime); }
	FORCEINLINE void UNLOAD_CLOUD_HAT(const char* name, float p1) { return YimMenu::NativeInvoker::Invoke<2023, void>(name, p1); }
	FORCEINLINE void UNLOAD_ALL_CLOUD_HATS() { return YimMenu::NativeInvoker::Invoke<2024, void>(); }
	FORCEINLINE void SET_CLOUDS_ALPHA(float opacity) { return YimMenu::NativeInvoker::Invoke<2025, void>(opacity); }
	FORCEINLINE float GET_CLOUDS_ALPHA() { return YimMenu::NativeInvoker::Invoke<2026, float>(); }
	FORCEINLINE int GET_GAME_TIMER() { return YimMenu::NativeInvoker::Invoke<2027, int>(); }
	FORCEINLINE float GET_FRAME_TIME() { return YimMenu::NativeInvoker::Invoke<2028, float>(); }
	FORCEINLINE float GET_SYSTEM_TIME_STEP() { return YimMenu::NativeInvoker::Invoke<2029, float>(); }
	FORCEINLINE int GET_FRAME_COUNT() { return YimMenu::NativeInvoker::Invoke<2030, int>(); }
	FORCEINLINE float GET_RANDOM_FLOAT_IN_RANGE(float startRange, float endRange) { return YimMenu::NativeInvoker::Invoke<2031, float>(startRange, endRange); }
	FORCEINLINE int GET_RANDOM_INT_IN_RANGE(int startRange, int endRange) { return YimMenu::NativeInvoker::Invoke<2032, int>(startRange, endRange); }
	FORCEINLINE int GET_RANDOM_MWC_INT_IN_RANGE(int startRange, int endRange) { return YimMenu::NativeInvoker::Invoke<2033, int>(startRange, endRange); }
	FORCEINLINE bool GET_GROUND_Z_FOR_3D_COORD(float x, float y, float z, float* groundZ, bool ignoreWater, bool p5) { return YimMenu::NativeInvoker::Invoke<2034, bool>(x, y, z, groundZ, ignoreWater, p5); }
	FORCEINLINE bool GET_GROUND_Z_AND_NORMAL_FOR_3D_COORD(float x, float y, float z, float* groundZ, Vector3* normal) { return YimMenu::NativeInvoker::Invoke<2035, bool>(x, y, z, groundZ, normal); }
	FORCEINLINE bool GET_GROUND_Z_EXCLUDING_OBJECTS_FOR_3D_COORD(float x, float y, float z, float* groundZ, bool p4, bool p5) { return YimMenu::NativeInvoker::Invoke<2036, bool>(x, y, z, groundZ, p4, p5); }
	FORCEINLINE float ASIN(float p0) { return YimMenu::NativeInvoker::Invoke<2037, float>(p0); }
	FORCEINLINE float ACOS(float p0) { return YimMenu::NativeInvoker::Invoke<2038, float>(p0); }
	FORCEINLINE float TAN(float p0) { return YimMenu::NativeInvoker::Invoke<2039, float>(p0); }
	FORCEINLINE float ATAN(float p0) { return YimMenu::NativeInvoker::Invoke<2040, float>(p0); }
	FORCEINLINE float ATAN2(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<2041, float>(p0, p1); }
	FORCEINLINE float GET_DISTANCE_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, bool useZ) { return YimMenu::NativeInvoker::Invoke<2042, float>(x1, y1, z1, x2, y2, z2, useZ); }
	FORCEINLINE float GET_ANGLE_BETWEEN_2D_VECTORS(float x1, float y1, float x2, float y2) { return YimMenu::NativeInvoker::Invoke<2043, float>(x1, y1, x2, y2); }
	FORCEINLINE float GET_HEADING_FROM_VECTOR_2D(float dx, float dy) { return YimMenu::NativeInvoker::Invoke<2044, float>(dx, dy); }
	FORCEINLINE float GET_RATIO_OF_CLOSEST_POINT_ON_LINE(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, bool clamp) { return YimMenu::NativeInvoker::Invoke<2045, float>(x1, y1, z1, x2, y2, z2, x3, y3, z3, clamp); }
	FORCEINLINE Vector3 GET_CLOSEST_POINT_ON_LINE(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, bool clamp) { return YimMenu::NativeInvoker::Invoke<2046, Vector3>(x1, y1, z1, x2, y2, z2, x3, y3, z3, clamp); }
	FORCEINLINE bool GET_LINE_PLANE_INTERSECTION(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float* p12) { return YimMenu::NativeInvoker::Invoke<2047, bool>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	FORCEINLINE bool GET_POINT_AREA_OVERLAP(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12, Any p13) { return YimMenu::NativeInvoker::Invoke<2048, bool>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	FORCEINLINE void SET_BIT(int* address, int offset) { return YimMenu::NativeInvoker::Invoke<2049, void>(address, offset); }
	FORCEINLINE void CLEAR_BIT(int* address, int offset) { return YimMenu::NativeInvoker::Invoke<2050, void>(address, offset); }
	FORCEINLINE Hash GET_HASH_KEY(const char* string) { return YimMenu::NativeInvoker::Invoke<2051, Hash>(string); }
	FORCEINLINE void SLERP_NEAR_QUATERNION(float t, float x, float y, float z, float w, float x1, float y1, float z1, float w1, float* outX, float* outY, float* outZ, float* outW) { return YimMenu::NativeInvoker::Invoke<2052, void>(t, x, y, z, w, x1, y1, z1, w1, outX, outY, outZ, outW); }
	FORCEINLINE bool IS_AREA_OCCUPIED(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7, bool p8, bool p9, bool p10, Any p11, bool p12) { return YimMenu::NativeInvoker::Invoke<2053, bool>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	FORCEINLINE bool IS_AREA_OCCUPIED_SLOW(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10, Any p11, Any p12) { return YimMenu::NativeInvoker::Invoke<2054, bool>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12); }
	FORCEINLINE bool IS_POSITION_OCCUPIED(float x, float y, float z, float range, bool p4, bool checkVehicles, bool checkPeds, bool p7, bool p8, Entity ignoreEntity, bool p10) { return YimMenu::NativeInvoker::Invoke<2055, bool>(x, y, z, range, p4, checkVehicles, checkPeds, p7, p8, ignoreEntity, p10); }
	FORCEINLINE bool IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return YimMenu::NativeInvoker::Invoke<2056, bool>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void CLEAR_AREA(float X, float Y, float Z, float radius, bool p4, bool ignoreCopCars, bool ignoreObjects, bool p7) { return YimMenu::NativeInvoker::Invoke<2057, void>(X, Y, Z, radius, p4, ignoreCopCars, ignoreObjects, p7); }
	FORCEINLINE void CLEAR_AREA_LEAVE_VEHICLE_HEALTH(float x, float y, float z, float radius, bool p4, bool p5, bool p6, bool p7) { return YimMenu::NativeInvoker::Invoke<2058, void>(x, y, z, radius, p4, p5, p6, p7); }
	FORCEINLINE void CLEAR_AREA_OF_VEHICLES(float x, float y, float z, float radius, bool p4, bool p5, bool p6, bool p7, bool p8, bool p9, Any p10) { return YimMenu::NativeInvoker::Invoke<2059, void>(x, y, z, radius, p4, p5, p6, p7, p8, p9, p10); }
	FORCEINLINE void CLEAR_ANGLED_AREA_OF_VEHICLES(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool p7, bool p8, bool p9, bool p10, bool p11, Any p12, Any p13) { return YimMenu::NativeInvoker::Invoke<2060, void>(x1, y1, z1, x2, y2, z2, width, p7, p8, p9, p10, p11, p12, p13); }
	FORCEINLINE void CLEAR_AREA_OF_OBJECTS(float x, float y, float z, float radius, int flags) { return YimMenu::NativeInvoker::Invoke<2061, void>(x, y, z, radius, flags); }
	FORCEINLINE void CLEAR_AREA_OF_PEDS(float x, float y, float z, float radius, int flags) { return YimMenu::NativeInvoker::Invoke<2062, void>(x, y, z, radius, flags); }
	FORCEINLINE void CLEAR_AREA_OF_COPS(float x, float y, float z, float radius, int flags) { return YimMenu::NativeInvoker::Invoke<2063, void>(x, y, z, radius, flags); }
	FORCEINLINE void CLEAR_AREA_OF_PROJECTILES(float x, float y, float z, float radius, int flags) { return YimMenu::NativeInvoker::Invoke<2064, void>(x, y, z, radius, flags); }
	FORCEINLINE void CLEAR_SCENARIO_SPAWN_HISTORY() { return YimMenu::NativeInvoker::Invoke<2065, void>(); }
	FORCEINLINE void SET_SAVE_MENU_ACTIVE(bool ignoreVehicle) { return YimMenu::NativeInvoker::Invoke<2066, void>(ignoreVehicle); }
	FORCEINLINE int GET_STATUS_OF_MANUAL_SAVE() { return YimMenu::NativeInvoker::Invoke<2067, int>(); }
	FORCEINLINE void SET_CREDITS_ACTIVE(bool toggle) { return YimMenu::NativeInvoker::Invoke<2068, void>(toggle); }
	FORCEINLINE void SET_CREDITS_FADE_OUT_WITH_SCREEN(bool toggle) { return YimMenu::NativeInvoker::Invoke<2069, void>(toggle); }
	FORCEINLINE bool HAVE_CREDITS_REACHED_END() { return YimMenu::NativeInvoker::Invoke<2070, bool>(); }
	FORCEINLINE bool ARE_CREDITS_RUNNING() { return YimMenu::NativeInvoker::Invoke<2071, bool>(); }
	FORCEINLINE void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(const char* scriptName) { return YimMenu::NativeInvoker::Invoke<2072, void>(scriptName); }
	FORCEINLINE void NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME() { return YimMenu::NativeInvoker::Invoke<2073, void>(); }
	FORCEINLINE int ADD_HOSPITAL_RESTART(float x, float y, float z, float p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2074, int>(x, y, z, p3, p4); }
	FORCEINLINE void DISABLE_HOSPITAL_RESTART(int hospitalIndex, bool toggle) { return YimMenu::NativeInvoker::Invoke<2075, void>(hospitalIndex, toggle); }
	FORCEINLINE int ADD_POLICE_RESTART(float p0, float p1, float p2, float p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2076, int>(p0, p1, p2, p3, p4); }
	FORCEINLINE void DISABLE_POLICE_RESTART(int policeIndex, bool toggle) { return YimMenu::NativeInvoker::Invoke<2077, void>(policeIndex, toggle); }
	FORCEINLINE void SET_RESTART_COORD_OVERRIDE(float x, float y, float z, float heading) { return YimMenu::NativeInvoker::Invoke<2078, void>(x, y, z, heading); }
	FORCEINLINE void CLEAR_RESTART_COORD_OVERRIDE() { return YimMenu::NativeInvoker::Invoke<2079, void>(); }
	FORCEINLINE void PAUSE_DEATH_ARREST_RESTART(bool toggle) { return YimMenu::NativeInvoker::Invoke<2080, void>(toggle); }
	FORCEINLINE void IGNORE_NEXT_RESTART(bool toggle) { return YimMenu::NativeInvoker::Invoke<2081, void>(toggle); }
	FORCEINLINE void SET_FADE_OUT_AFTER_DEATH(bool toggle) { return YimMenu::NativeInvoker::Invoke<2082, void>(toggle); }
	FORCEINLINE void SET_FADE_OUT_AFTER_ARREST(bool toggle) { return YimMenu::NativeInvoker::Invoke<2083, void>(toggle); }
	FORCEINLINE void SET_FADE_IN_AFTER_DEATH_ARREST(bool toggle) { return YimMenu::NativeInvoker::Invoke<2084, void>(toggle); }
	FORCEINLINE void SET_FADE_IN_AFTER_LOAD(bool toggle) { return YimMenu::NativeInvoker::Invoke<2085, void>(toggle); }
	FORCEINLINE int REGISTER_SAVE_HOUSE(float x, float y, float z, float p3, const char* p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<2086, int>(x, y, z, p3, p4, p5, p6); }
	FORCEINLINE void SET_SAVE_HOUSE(int savehouseHandle, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2087, void>(savehouseHandle, p1, p2); }
	FORCEINLINE bool OVERRIDE_SAVE_HOUSE(bool p0, float p1, float p2, float p3, float p4, bool p5, float p6, float p7) { return YimMenu::NativeInvoker::Invoke<2088, bool>(p0, p1, p2, p3, p4, p5, p6, p7); }
	FORCEINLINE bool GET_SAVE_HOUSE_DETAILS_AFTER_SUCCESSFUL_LOAD(Vector3* p0, float* p1, bool* fadeInAfterLoad, bool* p3) { return YimMenu::NativeInvoker::Invoke<2089, bool>(p0, p1, fadeInAfterLoad, p3); }
	FORCEINLINE void DO_AUTO_SAVE() { return YimMenu::NativeInvoker::Invoke<2090, void>(); }
	FORCEINLINE bool GET_IS_AUTO_SAVE_OFF() { return YimMenu::NativeInvoker::Invoke<2091, bool>(); }
	FORCEINLINE bool IS_AUTO_SAVE_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<2092, bool>(); }
	FORCEINLINE bool HAS_CODE_REQUESTED_AUTOSAVE() { return YimMenu::NativeInvoker::Invoke<2093, bool>(); }
	FORCEINLINE void CLEAR_CODE_REQUESTED_AUTOSAVE() { return YimMenu::NativeInvoker::Invoke<2094, void>(); }
	FORCEINLINE void BEGIN_REPLAY_STATS(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2095, void>(p0, p1); }
	FORCEINLINE void ADD_REPLAY_STAT_VALUE(Any value) { return YimMenu::NativeInvoker::Invoke<2096, void>(value); }
	FORCEINLINE void END_REPLAY_STATS() { return YimMenu::NativeInvoker::Invoke<2097, void>(); }
	FORCEINLINE bool HAVE_REPLAY_STATS_BEEN_STORED() { return YimMenu::NativeInvoker::Invoke<2098, bool>(); }
	FORCEINLINE int GET_REPLAY_STAT_MISSION_ID() { return YimMenu::NativeInvoker::Invoke<2099, int>(); }
	FORCEINLINE int GET_REPLAY_STAT_MISSION_TYPE() { return YimMenu::NativeInvoker::Invoke<2100, int>(); }
	FORCEINLINE int GET_REPLAY_STAT_COUNT() { return YimMenu::NativeInvoker::Invoke<2101, int>(); }
	FORCEINLINE int GET_REPLAY_STAT_AT_INDEX(int index) { return YimMenu::NativeInvoker::Invoke<2102, int>(index); }
	FORCEINLINE void CLEAR_REPLAY_STATS() { return YimMenu::NativeInvoker::Invoke<2103, void>(); }
	FORCEINLINE bool QUEUE_MISSION_REPEAT_LOAD() { return YimMenu::NativeInvoker::Invoke<2104, bool>(); }
	FORCEINLINE bool QUEUE_MISSION_REPEAT_SAVE() { return YimMenu::NativeInvoker::Invoke<2105, bool>(); }
	FORCEINLINE bool QUEUE_MISSION_REPEAT_SAVE_FOR_BENCHMARK_TEST() { return YimMenu::NativeInvoker::Invoke<2106, bool>(); }
	FORCEINLINE int GET_STATUS_OF_MISSION_REPEAT_SAVE() { return YimMenu::NativeInvoker::Invoke<2107, int>(); }
	FORCEINLINE bool IS_MEMORY_CARD_IN_USE() { return YimMenu::NativeInvoker::Invoke<2108, bool>(); }
	FORCEINLINE void SHOOT_SINGLE_BULLET_BETWEEN_COORDS(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed) { return YimMenu::NativeInvoker::Invoke<2109, void>(x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed); }
	FORCEINLINE void SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, Any p14) { return YimMenu::NativeInvoker::Invoke<2110, void>(x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed, entity, p14); }
	FORCEINLINE void SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY_NEW(float x1, float y1, float z1, float x2, float y2, float z2, int damage, bool p7, Hash weaponHash, Ped ownerPed, bool isAudible, bool isInvisible, float speed, Entity entity, bool p14, bool p15, Entity targetEntity, bool p17, Any p18, Any p19, Any p20) { return YimMenu::NativeInvoker::Invoke<2111, void>(x1, y1, z1, x2, y2, z2, damage, p7, weaponHash, ownerPed, isAudible, isInvisible, speed, entity, p14, p15, targetEntity, p17, p18, p19, p20); }
	FORCEINLINE void GET_MODEL_DIMENSIONS(Hash modelHash, Vector3* minimum, Vector3* maximum) { return YimMenu::NativeInvoker::Invoke<2112, void>(modelHash, minimum, maximum); }
	FORCEINLINE void SET_FAKE_WANTED_LEVEL(int fakeWantedLevel) { return YimMenu::NativeInvoker::Invoke<2113, void>(fakeWantedLevel); }
	FORCEINLINE int GET_FAKE_WANTED_LEVEL() { return YimMenu::NativeInvoker::Invoke<2114, int>(); }
	FORCEINLINE void USING_MISSION_CREATOR(bool toggle) { return YimMenu::NativeInvoker::Invoke<2115, void>(toggle); }
	FORCEINLINE void ALLOW_MISSION_CREATOR_WARP(bool toggle) { return YimMenu::NativeInvoker::Invoke<2116, void>(toggle); }
	FORCEINLINE void SET_MINIGAME_IN_PROGRESS(bool toggle) { return YimMenu::NativeInvoker::Invoke<2117, void>(toggle); }
	FORCEINLINE bool IS_MINIGAME_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<2118, bool>(); }
	FORCEINLINE bool IS_THIS_A_MINIGAME_SCRIPT() { return YimMenu::NativeInvoker::Invoke<2119, bool>(); }
	FORCEINLINE bool IS_SNIPER_INVERTED() { return YimMenu::NativeInvoker::Invoke<2120, bool>(); }
	FORCEINLINE bool SHOULD_USE_METRIC_MEASUREMENTS() { return YimMenu::NativeInvoker::Invoke<2121, bool>(); }
	FORCEINLINE int GET_PROFILE_SETTING(int profileSetting) { return YimMenu::NativeInvoker::Invoke<2122, int>(profileSetting); }
	FORCEINLINE bool ARE_STRINGS_EQUAL(const char* string1, const char* string2) { return YimMenu::NativeInvoker::Invoke<2123, bool>(string1, string2); }
	FORCEINLINE int COMPARE_STRINGS(const char* str1, const char* str2, bool matchCase, int maxLength) { return YimMenu::NativeInvoker::Invoke<2124, int>(str1, str2, matchCase, maxLength); }
	FORCEINLINE int ABSI(int value) { return YimMenu::NativeInvoker::Invoke<2125, int>(value); }
	FORCEINLINE float ABSF(float value) { return YimMenu::NativeInvoker::Invoke<2126, float>(value); }
	FORCEINLINE bool IS_SNIPER_BULLET_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<2127, bool>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE bool IS_PROJECTILE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool ownedByPlayer) { return YimMenu::NativeInvoker::Invoke<2128, bool>(x1, y1, z1, x2, y2, z2, ownedByPlayer); }
	FORCEINLINE bool IS_PROJECTILE_TYPE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, int type, bool ownedByPlayer) { return YimMenu::NativeInvoker::Invoke<2129, bool>(x1, y1, z1, x2, y2, z2, type, ownedByPlayer); }
	FORCEINLINE bool IS_PROJECTILE_TYPE_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, Any p7, bool ownedByPlayer) { return YimMenu::NativeInvoker::Invoke<2130, bool>(x1, y1, z1, x2, y2, z2, width, p7, ownedByPlayer); }
	FORCEINLINE bool IS_PROJECTILE_TYPE_WITHIN_DISTANCE(float x, float y, float z, Hash projectileHash, float radius, bool ownedByPlayer) { return YimMenu::NativeInvoker::Invoke<2131, bool>(x, y, z, projectileHash, radius, ownedByPlayer); }
	FORCEINLINE bool GET_COORDS_OF_PROJECTILE_TYPE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, Hash projectileHash, Vector3* projectilePos, bool ownedByPlayer) { return YimMenu::NativeInvoker::Invoke<2132, bool>(x1, y1, z1, x2, y2, z2, projectileHash, projectilePos, ownedByPlayer); }
	FORCEINLINE bool GET_COORDS_OF_PROJECTILE_TYPE_IN_ANGLED_AREA(float vecAngledAreaPoint1X, float vecAngledAreaPoint1Y, float vecAngledAreaPoint1Z, float vecAngledAreaPoint2X, float vecAngledAreaPoint2Y, float vecAngledAreaPoint2Z, float distanceOfOppositeFace, Hash weaponType, Vector3* positionOut, bool bIsPlayer) { return YimMenu::NativeInvoker::Invoke<2133, bool>(vecAngledAreaPoint1X, vecAngledAreaPoint1Y, vecAngledAreaPoint1Z, vecAngledAreaPoint2X, vecAngledAreaPoint2Y, vecAngledAreaPoint2Z, distanceOfOppositeFace, weaponType, positionOut, bIsPlayer); }
	FORCEINLINE bool GET_COORDS_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(Ped ped, Hash weaponHash, float distance, Vector3* outCoords, bool p4) { return YimMenu::NativeInvoker::Invoke<2134, bool>(ped, weaponHash, distance, outCoords, p4); }
	FORCEINLINE bool GET_PROJECTILE_OF_PROJECTILE_TYPE_WITHIN_DISTANCE(Ped ped, Hash weaponHash, float distance, Vector3* outCoords, Object* outProjectile, bool p5) { return YimMenu::NativeInvoker::Invoke<2135, bool>(ped, weaponHash, distance, outCoords, outProjectile, p5); }
	FORCEINLINE bool IS_BULLET_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool ownedByPlayer) { return YimMenu::NativeInvoker::Invoke<2136, bool>(x1, y1, z1, x2, y2, z2, width, ownedByPlayer); }
	FORCEINLINE bool IS_BULLET_IN_AREA(float x, float y, float z, float radius, bool ownedByPlayer) { return YimMenu::NativeInvoker::Invoke<2137, bool>(x, y, z, radius, ownedByPlayer); }
	FORCEINLINE bool IS_BULLET_IN_BOX(float x1, float y1, float z1, float x2, float y2, float z2, bool ownedByPlayer) { return YimMenu::NativeInvoker::Invoke<2138, bool>(x1, y1, z1, x2, y2, z2, ownedByPlayer); }
	FORCEINLINE bool HAS_BULLET_IMPACTED_IN_AREA(float x, float y, float z, float p3, bool p4, bool p5) { return YimMenu::NativeInvoker::Invoke<2139, bool>(x, y, z, p3, p4, p5); }
	FORCEINLINE bool HAS_BULLET_IMPACTED_IN_BOX(float p0, float p1, float p2, float p3, float p4, float p5, bool p6, bool p7) { return YimMenu::NativeInvoker::Invoke<2140, bool>(p0, p1, p2, p3, p4, p5, p6, p7); }
	FORCEINLINE bool IS_ORBIS_VERSION() { return YimMenu::NativeInvoker::Invoke<2141, bool>(); }
	FORCEINLINE bool IS_DURANGO_VERSION() { return YimMenu::NativeInvoker::Invoke<2142, bool>(); }
	FORCEINLINE bool IS_XBOX360_VERSION() { return YimMenu::NativeInvoker::Invoke<2143, bool>(); }
	FORCEINLINE bool IS_PS3_VERSION() { return YimMenu::NativeInvoker::Invoke<2144, bool>(); }
	FORCEINLINE bool IS_PC_VERSION() { return YimMenu::NativeInvoker::Invoke<2145, bool>(); }
	FORCEINLINE bool IS_STEAM_VERSION() { return YimMenu::NativeInvoker::Invoke<2146, bool>(); }
	FORCEINLINE bool IS_AUSSIE_VERSION() { return YimMenu::NativeInvoker::Invoke<2147, bool>(); }
	FORCEINLINE bool IS_JAPANESE_VERSION() { return YimMenu::NativeInvoker::Invoke<2148, bool>(); }
	FORCEINLINE bool IS_XBOX_PLATFORM() { return YimMenu::NativeInvoker::Invoke<2149, bool>(); }
	FORCEINLINE bool IS_SCARLETT_VERSION() { return YimMenu::NativeInvoker::Invoke<2150, bool>(); }
	FORCEINLINE bool IS_SCE_PLATFORM() { return YimMenu::NativeInvoker::Invoke<2151, bool>(); }
	FORCEINLINE bool IS_PROSPERO_VERSION() { return YimMenu::NativeInvoker::Invoke<2152, bool>(); }
	FORCEINLINE bool IS_STRING_NULL(const char* string) { return YimMenu::NativeInvoker::Invoke<2153, bool>(string); }
	FORCEINLINE bool IS_STRING_NULL_OR_EMPTY(const char* string) { return YimMenu::NativeInvoker::Invoke<2154, bool>(string); }
	FORCEINLINE bool STRING_TO_INT(const char* string, int* outInteger) { return YimMenu::NativeInvoker::Invoke<2155, bool>(string, outInteger); }
	FORCEINLINE void SET_BITS_IN_RANGE(int* var, int rangeStart, int rangeEnd, int p3) { return YimMenu::NativeInvoker::Invoke<2156, void>(var, rangeStart, rangeEnd, p3); }
	FORCEINLINE int GET_BITS_IN_RANGE(int var, int rangeStart, int rangeEnd) { return YimMenu::NativeInvoker::Invoke<2157, int>(var, rangeStart, rangeEnd); }
	FORCEINLINE int ADD_STUNT_JUMP(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4, float camX, float camY, float camZ, int p15, int p16, int p17) { return YimMenu::NativeInvoker::Invoke<2158, int>(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, camX, camY, camZ, p15, p16, p17); }
	FORCEINLINE int ADD_STUNT_JUMP_ANGLED(float x1, float y1, float z1, float x2, float y2, float z2, float radius1, float x3, float y3, float z3, float x4, float y4, float z4, float radius2, float camX, float camY, float camZ, int p17, int p18, int p19) { return YimMenu::NativeInvoker::Invoke<2159, int>(x1, y1, z1, x2, y2, z2, radius1, x3, y3, z3, x4, y4, z4, radius2, camX, camY, camZ, p17, p18, p19); }
	FORCEINLINE void TOGGLE_SHOW_OPTIONAL_STUNT_JUMP_CAMERA(bool toggle) { return YimMenu::NativeInvoker::Invoke<2160, void>(toggle); }
	FORCEINLINE void DELETE_STUNT_JUMP(int p0) { return YimMenu::NativeInvoker::Invoke<2161, void>(p0); }
	FORCEINLINE void ENABLE_STUNT_JUMP_SET(int p0) { return YimMenu::NativeInvoker::Invoke<2162, void>(p0); }
	FORCEINLINE void DISABLE_STUNT_JUMP_SET(int p0) { return YimMenu::NativeInvoker::Invoke<2163, void>(p0); }
	FORCEINLINE void SET_STUNT_JUMPS_CAN_TRIGGER(bool toggle) { return YimMenu::NativeInvoker::Invoke<2164, void>(toggle); }
	FORCEINLINE bool IS_STUNT_JUMP_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<2165, bool>(); }
	FORCEINLINE bool IS_STUNT_JUMP_MESSAGE_SHOWING() { return YimMenu::NativeInvoker::Invoke<2166, bool>(); }
	FORCEINLINE int GET_NUM_SUCCESSFUL_STUNT_JUMPS() { return YimMenu::NativeInvoker::Invoke<2167, int>(); }
	FORCEINLINE int GET_TOTAL_SUCCESSFUL_STUNT_JUMPS() { return YimMenu::NativeInvoker::Invoke<2168, int>(); }
	FORCEINLINE void CANCEL_STUNT_JUMP() { return YimMenu::NativeInvoker::Invoke<2169, void>(); }
	FORCEINLINE void SET_GAME_PAUSED(bool toggle) { return YimMenu::NativeInvoker::Invoke<2170, void>(toggle); }
	FORCEINLINE void SET_THIS_SCRIPT_CAN_BE_PAUSED(bool toggle) { return YimMenu::NativeInvoker::Invoke<2171, void>(toggle); }
	FORCEINLINE void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(bool toggle) { return YimMenu::NativeInvoker::Invoke<2172, void>(toggle); }
	FORCEINLINE bool HAS_CHEAT_WITH_HASH_BEEN_ACTIVATED(Hash hash, int amount) { return YimMenu::NativeInvoker::Invoke<2173, bool>(hash, amount); }
	FORCEINLINE bool HAS_PC_CHEAT_WITH_HASH_BEEN_ACTIVATED(Hash hash) { return YimMenu::NativeInvoker::Invoke<2174, bool>(hash); }
	FORCEINLINE void OVERRIDE_FREEZE_FLAGS(bool p0) { return YimMenu::NativeInvoker::Invoke<2175, void>(p0); }
	FORCEINLINE void SET_INSTANCE_PRIORITY_MODE(int p0) { return YimMenu::NativeInvoker::Invoke<2176, void>(p0); }
	FORCEINLINE void SET_INSTANCE_PRIORITY_HINT(int flag) { return YimMenu::NativeInvoker::Invoke<2177, void>(flag); }
	FORCEINLINE bool IS_FRONTEND_FADING() { return YimMenu::NativeInvoker::Invoke<2178, bool>(); }
	FORCEINLINE void POPULATE_NOW() { return YimMenu::NativeInvoker::Invoke<2179, void>(); }
	FORCEINLINE int GET_INDEX_OF_CURRENT_LEVEL() { return YimMenu::NativeInvoker::Invoke<2180, int>(); }
	FORCEINLINE void SET_GRAVITY_LEVEL(int level) { return YimMenu::NativeInvoker::Invoke<2181, void>(level); }
	FORCEINLINE void START_SAVE_DATA(Any* p0, Any p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2182, void>(p0, p1, p2); }
	FORCEINLINE void STOP_SAVE_DATA() { return YimMenu::NativeInvoker::Invoke<2183, void>(); }
	FORCEINLINE int GET_SIZE_OF_SAVE_DATA(bool p0) { return YimMenu::NativeInvoker::Invoke<2184, int>(p0); }
	FORCEINLINE void REGISTER_INT_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2185, void>(p0, name); }
	FORCEINLINE void REGISTER_INT64_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2186, void>(p0, name); }
	FORCEINLINE void REGISTER_ENUM_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2187, void>(p0, name); }
	FORCEINLINE void REGISTER_FLOAT_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2188, void>(p0, name); }
	FORCEINLINE void REGISTER_BOOL_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2189, void>(p0, name); }
	FORCEINLINE void REGISTER_TEXT_LABEL_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2190, void>(p0, name); }
	FORCEINLINE void REGISTER_TEXT_LABEL_15_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2191, void>(p0, name); }
	FORCEINLINE void REGISTER_TEXT_LABEL_23_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2192, void>(p0, name); }
	FORCEINLINE void REGISTER_TEXT_LABEL_31_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2193, void>(p0, name); }
	FORCEINLINE void REGISTER_TEXT_LABEL_63_TO_SAVE(Any* p0, const char* name) { return YimMenu::NativeInvoker::Invoke<2194, void>(p0, name); }
	FORCEINLINE void START_SAVE_STRUCT_WITH_SIZE(Any* p0, int size, const char* structName) { return YimMenu::NativeInvoker::Invoke<2195, void>(p0, size, structName); }
	FORCEINLINE void STOP_SAVE_STRUCT() { return YimMenu::NativeInvoker::Invoke<2196, void>(); }
	FORCEINLINE void START_SAVE_ARRAY_WITH_SIZE(Any* p0, int size, const char* arrayName) { return YimMenu::NativeInvoker::Invoke<2197, void>(p0, size, arrayName); }
	FORCEINLINE void STOP_SAVE_ARRAY() { return YimMenu::NativeInvoker::Invoke<2198, void>(); }
	FORCEINLINE void COPY_SCRIPT_STRUCT(Any* dst, Any* src, int size) { return YimMenu::NativeInvoker::Invoke<2199, void>(dst, src, size); }
	FORCEINLINE void ENABLE_DISPATCH_SERVICE(int dispatchService, bool toggle) { return YimMenu::NativeInvoker::Invoke<2200, void>(dispatchService, toggle); }
	FORCEINLINE void BLOCK_DISPATCH_SERVICE_RESOURCE_CREATION(int dispatchService, bool toggle) { return YimMenu::NativeInvoker::Invoke<2201, void>(dispatchService, toggle); }
	FORCEINLINE int GET_NUMBER_RESOURCES_ALLOCATED_TO_WANTED_LEVEL(int dispatchService) { return YimMenu::NativeInvoker::Invoke<2202, int>(dispatchService); }
	FORCEINLINE bool CREATE_INCIDENT(int dispatchService, float x, float y, float z, int numUnits, float radius, int* outIncidentID, Any p7, Any p8) { return YimMenu::NativeInvoker::Invoke<2203, bool>(dispatchService, x, y, z, numUnits, radius, outIncidentID, p7, p8); }
	FORCEINLINE bool CREATE_INCIDENT_WITH_ENTITY(int dispatchService, Ped ped, int numUnits, float radius, int* outIncidentID, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<2204, bool>(dispatchService, ped, numUnits, radius, outIncidentID, p5, p6); }
	FORCEINLINE void DELETE_INCIDENT(int incidentId) { return YimMenu::NativeInvoker::Invoke<2205, void>(incidentId); }
	FORCEINLINE bool IS_INCIDENT_VALID(int incidentId) { return YimMenu::NativeInvoker::Invoke<2206, bool>(incidentId); }
	FORCEINLINE void SET_INCIDENT_REQUESTED_UNITS(int incidentId, int dispatchService, int numUnits) { return YimMenu::NativeInvoker::Invoke<2207, void>(incidentId, dispatchService, numUnits); }
	FORCEINLINE void SET_IDEAL_SPAWN_DISTANCE_FOR_INCIDENT(int incidentId, float p1) { return YimMenu::NativeInvoker::Invoke<2208, void>(incidentId, p1); }
	FORCEINLINE bool FIND_SPAWN_POINT_IN_DIRECTION(float posX, float posY, float posZ, float fwdVecX, float fwdVecY, float fwdVecZ, float distance, Vector3* spawnPoint) { return YimMenu::NativeInvoker::Invoke<2209, bool>(posX, posY, posZ, fwdVecX, fwdVecY, fwdVecZ, distance, spawnPoint); }
	FORCEINLINE int ADD_POP_MULTIPLIER_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float p6, float p7, bool p8, bool p9) { return YimMenu::NativeInvoker::Invoke<2210, int>(x1, y1, z1, x2, y2, z2, p6, p7, p8, p9); }
	FORCEINLINE bool DOES_POP_MULTIPLIER_AREA_EXIST(int id) { return YimMenu::NativeInvoker::Invoke<2211, bool>(id); }
	FORCEINLINE void REMOVE_POP_MULTIPLIER_AREA(int id, bool p1) { return YimMenu::NativeInvoker::Invoke<2212, void>(id, p1); }
	FORCEINLINE bool IS_POP_MULTIPLIER_AREA_NETWORKED(int id) { return YimMenu::NativeInvoker::Invoke<2213, bool>(id); }
	FORCEINLINE int ADD_POP_MULTIPLIER_SPHERE(float x, float y, float z, float radius, float pedMultiplier, float vehicleMultiplier, bool p6, bool p7) { return YimMenu::NativeInvoker::Invoke<2214, int>(x, y, z, radius, pedMultiplier, vehicleMultiplier, p6, p7); }
	FORCEINLINE bool DOES_POP_MULTIPLIER_SPHERE_EXIST(int id) { return YimMenu::NativeInvoker::Invoke<2215, bool>(id); }
	FORCEINLINE void REMOVE_POP_MULTIPLIER_SPHERE(int id, bool p1) { return YimMenu::NativeInvoker::Invoke<2216, void>(id, p1); }
	FORCEINLINE void ENABLE_TENNIS_MODE(Ped ped, bool toggle, bool p2) { return YimMenu::NativeInvoker::Invoke<2217, void>(ped, toggle, p2); }
	FORCEINLINE bool IS_TENNIS_MODE(Ped ped) { return YimMenu::NativeInvoker::Invoke<2218, bool>(ped); }
	FORCEINLINE void PLAY_TENNIS_SWING_ANIM(Ped ped, const char* animDict, const char* animName, float p3, float p4, bool p5) { return YimMenu::NativeInvoker::Invoke<2219, void>(ped, animDict, animName, p3, p4, p5); }
	FORCEINLINE bool GET_TENNIS_SWING_ANIM_COMPLETE(Ped ped) { return YimMenu::NativeInvoker::Invoke<2220, bool>(ped); }
	FORCEINLINE bool GET_TENNIS_SWING_ANIM_CAN_BE_INTERRUPTED(Ped ped) { return YimMenu::NativeInvoker::Invoke<2221, bool>(ped); }
	FORCEINLINE bool GET_TENNIS_SWING_ANIM_SWUNG(Ped ped) { return YimMenu::NativeInvoker::Invoke<2222, bool>(ped); }
	FORCEINLINE void PLAY_TENNIS_DIVE_ANIM(Ped ped, int p1, float p2, float p3, float p4, bool p5) { return YimMenu::NativeInvoker::Invoke<2223, void>(ped, p1, p2, p3, p4, p5); }
	FORCEINLINE void SET_TENNIS_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* p1, float p2) { return YimMenu::NativeInvoker::Invoke<2224, void>(ped, p1, p2); }
	FORCEINLINE void RESET_DISPATCH_SPAWN_LOCATION() { return YimMenu::NativeInvoker::Invoke<2225, void>(); }
	FORCEINLINE void SET_DISPATCH_SPAWN_LOCATION(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<2226, void>(x, y, z); }
	FORCEINLINE void RESET_DISPATCH_IDEAL_SPAWN_DISTANCE() { return YimMenu::NativeInvoker::Invoke<2227, void>(); }
	FORCEINLINE void SET_DISPATCH_IDEAL_SPAWN_DISTANCE(float distance) { return YimMenu::NativeInvoker::Invoke<2228, void>(distance); }
	FORCEINLINE void RESET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0) { return YimMenu::NativeInvoker::Invoke<2229, void>(p0); }
	FORCEINLINE void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(Any p0, float p1) { return YimMenu::NativeInvoker::Invoke<2230, void>(p0, p1); }
	FORCEINLINE void SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(Any p0, float p1) { return YimMenu::NativeInvoker::Invoke<2231, void>(p0, p1); }
	FORCEINLINE int ADD_DISPATCH_SPAWN_ANGLED_BLOCKING_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width) { return YimMenu::NativeInvoker::Invoke<2232, int>(x1, y1, z1, x2, y2, z2, width); }
	FORCEINLINE int ADD_DISPATCH_SPAWN_SPHERE_BLOCKING_AREA(float x1, float y1, float x2, float y2) { return YimMenu::NativeInvoker::Invoke<2233, int>(x1, y1, x2, y2); }
	FORCEINLINE void REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(int p0) { return YimMenu::NativeInvoker::Invoke<2234, void>(p0); }
	FORCEINLINE void RESET_DISPATCH_SPAWN_BLOCKING_AREAS() { return YimMenu::NativeInvoker::Invoke<2235, void>(); }
	FORCEINLINE void RESET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN() { return YimMenu::NativeInvoker::Invoke<2236, void>(); }
	FORCEINLINE void SET_WANTED_RESPONSE_NUM_PEDS_TO_SPAWN(int p0, int p1) { return YimMenu::NativeInvoker::Invoke<2237, void>(p0, p1); }
	FORCEINLINE void ADD_TACTICAL_NAV_MESH_POINT(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<2238, void>(x, y, z); }
	FORCEINLINE void CLEAR_TACTICAL_NAV_MESH_POINTS() { return YimMenu::NativeInvoker::Invoke<2239, void>(); }
	FORCEINLINE void SET_RIOT_MODE_ENABLED(bool toggle) { return YimMenu::NativeInvoker::Invoke<2240, void>(toggle); }
	FORCEINLINE void DISPLAY_ONSCREEN_KEYBOARD_WITH_LONGER_INITIAL_STRING(int p0, const char* windowTitle, Any* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, const char* defaultConcat4, const char* defaultConcat5, const char* defaultConcat6, const char* defaultConcat7, int maxInputLength) { return YimMenu::NativeInvoker::Invoke<2241, void>(p0, windowTitle, p2, defaultText, defaultConcat1, defaultConcat2, defaultConcat3, defaultConcat4, defaultConcat5, defaultConcat6, defaultConcat7, maxInputLength); }
	FORCEINLINE void DISPLAY_ONSCREEN_KEYBOARD(int p0, const char* windowTitle, const char* p2, const char* defaultText, const char* defaultConcat1, const char* defaultConcat2, const char* defaultConcat3, int maxInputLength) { return YimMenu::NativeInvoker::Invoke<2242, void>(p0, windowTitle, p2, defaultText, defaultConcat1, defaultConcat2, defaultConcat3, maxInputLength); }
	FORCEINLINE int UPDATE_ONSCREEN_KEYBOARD() { return YimMenu::NativeInvoker::Invoke<2243, int>(); }
	FORCEINLINE const char* GET_ONSCREEN_KEYBOARD_RESULT() { return YimMenu::NativeInvoker::Invoke<2244, const char*>(); }
	FORCEINLINE void CANCEL_ONSCREEN_KEYBOARD() { return YimMenu::NativeInvoker::Invoke<2245, void>(); }
	FORCEINLINE void NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS(int p0) { return YimMenu::NativeInvoker::Invoke<2246, void>(p0); }
	FORCEINLINE void ACTION_MANAGER_ENABLE_ACTION(Hash hash, bool enable) { return YimMenu::NativeInvoker::Invoke<2247, void>(hash, enable); }
	FORCEINLINE int GET_REAL_WORLD_TIME() { return YimMenu::NativeInvoker::Invoke<2248, int>(); }
	FORCEINLINE void SUPRESS_RANDOM_EVENT_THIS_FRAME(int eventType, bool suppress) { return YimMenu::NativeInvoker::Invoke<2249, void>(eventType, suppress); }
	FORCEINLINE void SET_EXPLOSIVE_AMMO_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<2250, void>(player); }
	FORCEINLINE void SET_FIRE_AMMO_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<2251, void>(player); }
	FORCEINLINE void SET_EXPLOSIVE_MELEE_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<2252, void>(player); }
	FORCEINLINE void SET_SUPER_JUMP_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<2253, void>(player); }
	FORCEINLINE void SET_BEAST_JUMP_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<2254, void>(player); }
	FORCEINLINE void SET_FORCED_JUMP_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<2255, void>(player); }
	FORCEINLINE bool HAS_GAME_INSTALLED_THIS_SESSION() { return YimMenu::NativeInvoker::Invoke<2256, bool>(); }
	FORCEINLINE void SET_TICKER_JOHNMARSTON_IS_DONE() { return YimMenu::NativeInvoker::Invoke<2257, void>(); }
	FORCEINLINE bool ARE_PROFILE_SETTINGS_VALID() { return YimMenu::NativeInvoker::Invoke<2258, bool>(); }
	FORCEINLINE void PREVENT_ARREST_STATE_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<2259, void>(); }
	FORCEINLINE void FORCE_GAME_STATE_PLAYING() { return YimMenu::NativeInvoker::Invoke<2260, void>(); }
	FORCEINLINE void SCRIPT_RACE_INIT(int p0, int p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2261, void>(p0, p1, p2, p3); }
	FORCEINLINE void SCRIPT_RACE_SHUTDOWN() { return YimMenu::NativeInvoker::Invoke<2262, void>(); }
	FORCEINLINE void SCRIPT_RACE_PLAYER_HIT_CHECKPOINT(Player player, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2263, void>(player, p1, p2, p3); }
	FORCEINLINE bool SCRIPT_RACE_GET_PLAYER_SPLIT_TIME(Player player, int* p1, int* p2) { return YimMenu::NativeInvoker::Invoke<2264, bool>(player, p1, p2); }
	FORCEINLINE void START_END_USER_BENCHMARK() { return YimMenu::NativeInvoker::Invoke<2265, void>(); }
	FORCEINLINE void STOP_END_USER_BENCHMARK() { return YimMenu::NativeInvoker::Invoke<2266, void>(); }
	FORCEINLINE void RESET_END_USER_BENCHMARK() { return YimMenu::NativeInvoker::Invoke<2267, void>(); }
	FORCEINLINE void SAVE_END_USER_BENCHMARK() { return YimMenu::NativeInvoker::Invoke<2268, void>(); }
	FORCEINLINE bool UI_STARTED_END_USER_BENCHMARK() { return YimMenu::NativeInvoker::Invoke<2269, bool>(); }
	FORCEINLINE bool LANDING_SCREEN_STARTED_END_USER_BENCHMARK() { return YimMenu::NativeInvoker::Invoke<2270, bool>(); }
	FORCEINLINE bool IS_COMMANDLINE_END_USER_BENCHMARK() { return YimMenu::NativeInvoker::Invoke<2271, bool>(); }
	FORCEINLINE int GET_BENCHMARK_ITERATIONS() { return YimMenu::NativeInvoker::Invoke<2272, int>(); }
	FORCEINLINE int GET_BENCHMARK_PASS() { return YimMenu::NativeInvoker::Invoke<2273, int>(); }
	FORCEINLINE void RESTART_GAME() { return YimMenu::NativeInvoker::Invoke<2274, void>(); }
	FORCEINLINE void QUIT_GAME() { return YimMenu::NativeInvoker::Invoke<2275, void>(); }
	FORCEINLINE bool HAS_ASYNC_INSTALL_FINISHED() { return YimMenu::NativeInvoker::Invoke<2276, bool>(); }
	FORCEINLINE void CLEANUP_ASYNC_INSTALL() { return YimMenu::NativeInvoker::Invoke<2277, void>(); }
	FORCEINLINE bool PLM_IS_IN_CONSTRAINED_MODE() { return YimMenu::NativeInvoker::Invoke<2278, bool>(); }
	FORCEINLINE int PLM_GET_CONSTRAINED_DURATION_MS() { return YimMenu::NativeInvoker::Invoke<2279, int>(); }
	FORCEINLINE void SET_PLAYER_IS_IN_ANIMAL_FORM(bool toggle) { return YimMenu::NativeInvoker::Invoke<2280, void>(toggle); }
	FORCEINLINE bool GET_IS_PLAYER_IN_ANIMAL_FORM() { return YimMenu::NativeInvoker::Invoke<2281, bool>(); }
	FORCEINLINE void SET_PLAYER_IS_REPEATING_A_MISSION(bool toggle) { return YimMenu::NativeInvoker::Invoke<2282, void>(toggle); }
	FORCEINLINE void DISABLE_SCREEN_DIMMING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<2283, void>(); }
	FORCEINLINE float GET_CITY_DENSITY() { return YimMenu::NativeInvoker::Invoke<2284, float>(); }
	FORCEINLINE void USE_ACTIVE_CAMERA_FOR_TIMESLICING_CENTRE() { return YimMenu::NativeInvoker::Invoke<2285, void>(); }
	FORCEINLINE void SET_CONTENT_ID_INDEX(Hash contentId, int index) { return YimMenu::NativeInvoker::Invoke<2286, void>(contentId, index); }
	FORCEINLINE int GET_CONTENT_ID_INDEX(Hash contentId) { return YimMenu::NativeInvoker::Invoke<2287, int>(contentId); }
}

namespace MOBILE
{
	FORCEINLINE void CREATE_MOBILE_PHONE(int phoneType) { return YimMenu::NativeInvoker::Invoke<2288, void>(phoneType); }
	FORCEINLINE void DESTROY_MOBILE_PHONE() { return YimMenu::NativeInvoker::Invoke<2289, void>(); }
	FORCEINLINE void SET_MOBILE_PHONE_SCALE(float scale) { return YimMenu::NativeInvoker::Invoke<2290, void>(scale); }
	FORCEINLINE void SET_MOBILE_PHONE_ROTATION(float rotX, float rotY, float rotZ, Any p3) { return YimMenu::NativeInvoker::Invoke<2291, void>(rotX, rotY, rotZ, p3); }
	FORCEINLINE void GET_MOBILE_PHONE_ROTATION(Vector3* rotation, Vehicle p1) { return YimMenu::NativeInvoker::Invoke<2292, void>(rotation, p1); }
	FORCEINLINE void SET_MOBILE_PHONE_POSITION(float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<2293, void>(posX, posY, posZ); }
	FORCEINLINE void GET_MOBILE_PHONE_POSITION(Vector3* position) { return YimMenu::NativeInvoker::Invoke<2294, void>(position); }
	FORCEINLINE void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(bool toggle) { return YimMenu::NativeInvoker::Invoke<2295, void>(toggle); }
	FORCEINLINE bool CAN_PHONE_BE_SEEN_ON_SCREEN() { return YimMenu::NativeInvoker::Invoke<2296, bool>(); }
	FORCEINLINE void SET_MOBILE_PHONE_DOF_STATE(bool toggle) { return YimMenu::NativeInvoker::Invoke<2297, void>(toggle); }
	FORCEINLINE void CELL_SET_INPUT(int direction) { return YimMenu::NativeInvoker::Invoke<2298, void>(direction); }
	FORCEINLINE void CELL_HORIZONTAL_MODE_TOGGLE(bool toggle) { return YimMenu::NativeInvoker::Invoke<2299, void>(toggle); }
	FORCEINLINE void CELL_CAM_ACTIVATE(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<2300, void>(p0, p1); }
	FORCEINLINE void CELL_CAM_ACTIVATE_SELFIE_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<2301, void>(toggle); }
	FORCEINLINE void CELL_CAM_ACTIVATE_SHALLOW_DOF_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<2302, void>(toggle); }
	FORCEINLINE void CELL_CAM_SET_SELFIE_MODE_SIDE_OFFSET_SCALING(float p0) { return YimMenu::NativeInvoker::Invoke<2303, void>(p0); }
	FORCEINLINE void CELL_CAM_SET_SELFIE_MODE_HORZ_PAN_OFFSET(float horizontalPan) { return YimMenu::NativeInvoker::Invoke<2304, void>(horizontalPan); }
	FORCEINLINE void CELL_CAM_SET_SELFIE_MODE_VERT_PAN_OFFSET(float vertPan) { return YimMenu::NativeInvoker::Invoke<2305, void>(vertPan); }
	FORCEINLINE void CELL_CAM_SET_SELFIE_MODE_ROLL_OFFSET(float roll) { return YimMenu::NativeInvoker::Invoke<2306, void>(roll); }
	FORCEINLINE void CELL_CAM_SET_SELFIE_MODE_DISTANCE_SCALING(float distanceScaling) { return YimMenu::NativeInvoker::Invoke<2307, void>(distanceScaling); }
	FORCEINLINE void CELL_CAM_SET_SELFIE_MODE_HEAD_YAW_OFFSET(float yaw) { return YimMenu::NativeInvoker::Invoke<2308, void>(yaw); }
	FORCEINLINE void CELL_CAM_SET_SELFIE_MODE_HEAD_ROLL_OFFSET(float roll) { return YimMenu::NativeInvoker::Invoke<2309, void>(roll); }
	FORCEINLINE void CELL_CAM_SET_SELFIE_MODE_HEAD_PITCH_OFFSET(float pitch) { return YimMenu::NativeInvoker::Invoke<2310, void>(pitch); }
	FORCEINLINE bool CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(Entity entity) { return YimMenu::NativeInvoker::Invoke<2311, bool>(entity); }
	FORCEINLINE void GET_MOBILE_PHONE_RENDER_ID(int* renderId) { return YimMenu::NativeInvoker::Invoke<2312, void>(renderId); }
}

namespace MONEY
{
	FORCEINLINE void NETWORK_INITIALIZE_CASH(int wallet, int bank) { return YimMenu::NativeInvoker::Invoke<2313, void>(wallet, bank); }
	FORCEINLINE void NETWORK_DELETE_CHARACTER(int characterSlot, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2314, void>(characterSlot, p1, p2); }
	FORCEINLINE void NETWORK_MANUAL_DELETE_CHARACTER(int characterSlot) { return YimMenu::NativeInvoker::Invoke<2315, void>(characterSlot); }
	FORCEINLINE bool NETWORK_GET_PLAYER_IS_HIGH_EARNER() { return YimMenu::NativeInvoker::Invoke<2316, bool>(); }
	FORCEINLINE void NETWORK_CLEAR_CHARACTER_WALLET(int characterSlot) { return YimMenu::NativeInvoker::Invoke<2317, void>(characterSlot); }
	FORCEINLINE void NETWORK_GIVE_PLAYER_JOBSHARE_CASH(int amount, Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2318, void>(amount, gamerHandle); }
	FORCEINLINE void NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(int value, Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2319, void>(value, gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_SHARE_JOB_CASH() { return YimMenu::NativeInvoker::Invoke<2320, bool>(); }
	FORCEINLINE void NETWORK_REFUND_CASH(int index, const char* context, const char* reason, bool p3) { return YimMenu::NativeInvoker::Invoke<2321, void>(index, context, reason, p3); }
	FORCEINLINE void NETWORK_DEDUCT_CASH(int amount, const char* p1, const char* p2, bool p3, bool p4, bool p5) { return YimMenu::NativeInvoker::Invoke<2322, void>(amount, p1, p2, p3, p4, p5); }
	FORCEINLINE bool NETWORK_MONEY_CAN_BET(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2323, bool>(amount, p1, p2); }
	FORCEINLINE bool NETWORK_CAN_BET(int amount) { return YimMenu::NativeInvoker::Invoke<2324, bool>(amount); }
	FORCEINLINE bool NETWORK_CASINO_CAN_BET(Hash hash) { return YimMenu::NativeInvoker::Invoke<2325, bool>(hash); }
	FORCEINLINE bool NETWORK_CASINO_CAN_BET_PVC() { return YimMenu::NativeInvoker::Invoke<2326, bool>(); }
	FORCEINLINE bool NETWORK_CASINO_CAN_BET_AMOUNT(Any p0) { return YimMenu::NativeInvoker::Invoke<2327, bool>(p0); }
	FORCEINLINE bool NETWORK_CASINO_CAN_BUY_CHIPS_PVC() { return YimMenu::NativeInvoker::Invoke<2328, bool>(); }
	FORCEINLINE bool NETWORK_CASINO_BUY_CHIPS(int p0, int p1) { return YimMenu::NativeInvoker::Invoke<2329, bool>(p0, p1); }
	FORCEINLINE bool NETWORK_CASINO_SELL_CHIPS(int p0, int p1) { return YimMenu::NativeInvoker::Invoke<2330, bool>(p0, p1); }
	FORCEINLINE void NETWORK_DEFER_CASH_TRANSACTIONS_UNTIL_SHOP_SAVE() { return YimMenu::NativeInvoker::Invoke<2331, void>(); }
	FORCEINLINE bool CAN_PAY_AMOUNT_TO_BOSS(int p0, int p1, int amount, int* p3) { return YimMenu::NativeInvoker::Invoke<2332, bool>(p0, p1, amount, p3); }
	FORCEINLINE void NETWORK_EARN_FROM_PICKUP(int amount) { return YimMenu::NativeInvoker::Invoke<2333, void>(amount); }
	FORCEINLINE void NETWORK_EARN_FROM_CASHING_OUT(int amount) { return YimMenu::NativeInvoker::Invoke<2334, void>(amount); }
	FORCEINLINE void NETWORK_EARN_FROM_GANGATTACK_PICKUP(int amount) { return YimMenu::NativeInvoker::Invoke<2335, void>(amount); }
	FORCEINLINE void NETWORK_EARN_ASSASSINATE_TARGET_KILLED(int amount) { return YimMenu::NativeInvoker::Invoke<2336, void>(amount); }
	FORCEINLINE void NETWORK_EARN_FROM_ROB_ARMORED_CARS(int amount) { return YimMenu::NativeInvoker::Invoke<2337, void>(amount); }
	FORCEINLINE void NETWORK_EARN_FROM_CRATE_DROP(int amount) { return YimMenu::NativeInvoker::Invoke<2338, void>(amount); }
	FORCEINLINE void NETWORK_EARN_FROM_BETTING(int amount, const char* p1) { return YimMenu::NativeInvoker::Invoke<2339, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_FROM_JOB(int amount, const char* p1) { return YimMenu::NativeInvoker::Invoke<2340, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_FROM_JOBX2(int amount, const char* p1) { return YimMenu::NativeInvoker::Invoke<2341, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_FROM_PREMIUM_JOB(int amount, const char* p1) { return YimMenu::NativeInvoker::Invoke<2342, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_FROM_BEND_JOB(int amount, const char* heistHash) { return YimMenu::NativeInvoker::Invoke<2343, void>(amount, heistHash); }
	FORCEINLINE void NETWORK_EARN_FROM_CHALLENGE_WIN(Any p0, Any* p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2344, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_FROM_BOUNTY(int amount, Any* gamerHandle, Any* p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2345, void>(amount, gamerHandle, p2, p3); }
	FORCEINLINE void NETWORK_EARN_FROM_IMPORT_EXPORT(int amount, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<2346, void>(amount, modelHash); }
	FORCEINLINE void NETWORK_EARN_FROM_HOLDUPS(int amount) { return YimMenu::NativeInvoker::Invoke<2347, void>(amount); }
	FORCEINLINE void NETWORK_EARN_FROM_PROPERTY(int amount, Hash propertyName) { return YimMenu::NativeInvoker::Invoke<2348, void>(amount, propertyName); }
	FORCEINLINE void NETWORK_EARN_FROM_AI_TARGET_KILL(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2349, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_FROM_NOT_BADSPORT(int amount) { return YimMenu::NativeInvoker::Invoke<2350, void>(amount); }
	FORCEINLINE void NETWORK_EARN_FROM_VEHICLE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return YimMenu::NativeInvoker::Invoke<2351, void>(p0, p1, p2, p3, p4, p5, p6, p7); }
	FORCEINLINE void NETWORK_EARN_FROM_PERSONAL_VEHICLE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return YimMenu::NativeInvoker::Invoke<2352, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void NETWORK_EARN_FROM_DAILY_OBJECTIVES(int amount, const char* type, int characterSlot) { return YimMenu::NativeInvoker::Invoke<2353, void>(amount, type, characterSlot); }
	FORCEINLINE void NETWORK_EARN_FROM_AMBIENT_JOB(int p0, const char* p1, Any* p2) { return YimMenu::NativeInvoker::Invoke<2354, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_FROM_JOB_BONUS(Any p0, Any* p1, Any* p2) { return YimMenu::NativeInvoker::Invoke<2355, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_FROM_CRIMINAL_MASTERMIND(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2356, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_HEIST_AWARD(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2357, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_FIRST_TIME_BONUS(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2358, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_GOON(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2359, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_BOSS(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2360, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_AGENCY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2361, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_FROM_WAREHOUSE(int amount, int id) { return YimMenu::NativeInvoker::Invoke<2362, void>(amount, id); }
	FORCEINLINE void NETWORK_EARN_FROM_CONTRABAND(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2363, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_FROM_DESTROYING_CONTRABAND(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2364, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_FROM_SMUGGLER_WORK(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<2365, void>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void NETWORK_EARN_FROM_HANGAR_TRADE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2366, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_PURCHASE_CLUB_HOUSE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2367, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_FROM_BUSINESS_PRODUCT(int amount, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2368, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_FROM_VEHICLE_EXPORT(int amount, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2369, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_EARN_SMUGGLER_AGENCY(int amount, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2370, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_BOUNTY_HUNTER_REWARD(Any p0) { return YimMenu::NativeInvoker::Invoke<2371, void>(p0); }
	FORCEINLINE void NETWORK_EARN_FROM_BUSINESS_BATTLE(Any p0) { return YimMenu::NativeInvoker::Invoke<2372, void>(p0); }
	FORCEINLINE void NETWORK_EARN_FROM_CLUB_MANAGEMENT_PARTICIPATION(Any p0, int p1) { return YimMenu::NativeInvoker::Invoke<2373, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_FROM_FMBB_PHONECALL_MISSION(Any p0) { return YimMenu::NativeInvoker::Invoke<2374, void>(p0); }
	FORCEINLINE void NETWORK_EARN_FROM_BUSINESS_HUB_SELL(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2375, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_FROM_FMBB_BOSS_WORK(Any p0) { return YimMenu::NativeInvoker::Invoke<2376, void>(p0); }
	FORCEINLINE void NETWORK_EARN_FMBB_WAGE_BONUS(Any p0) { return YimMenu::NativeInvoker::Invoke<2377, void>(p0); }
	FORCEINLINE bool NETWORK_CAN_SPEND_MONEY(Any p0, bool p1, bool p2, bool p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<2378, bool>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE bool NETWORK_CAN_SPEND_MONEY2(Any p0, bool p1, bool p2, bool p3, Any* p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<2379, bool>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void NETWORK_BUY_ITEM(int amount, Hash item, Any p2, Any p3, bool p4, const char* item_name, Any p6, Any p7, Any p8, bool p9) { return YimMenu::NativeInvoker::Invoke<2380, void>(amount, item, p2, p3, p4, item_name, p6, p7, p8, p9); }
	FORCEINLINE void NETWORK_SPENT_TAXI(int amount, bool p1, bool p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2381, void>(amount, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_PAY_EMPLOYEE_WAGE(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2382, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_PAY_MATCH_ENTRY_FEE(int amount, const char* matchId, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2383, void>(amount, matchId, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BETTING(int amount, int p1, const char* matchId, bool p3, bool p4) { return YimMenu::NativeInvoker::Invoke<2384, void>(amount, p1, matchId, p3, p4); }
	FORCEINLINE void NETWORK_SPENT_WAGER(Any p0, Any p1, int amount) { return YimMenu::NativeInvoker::Invoke<2385, void>(p0, p1, amount); }
	FORCEINLINE void NETWORK_SPENT_IN_STRIPCLUB(Any p0, bool p1, Any p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2386, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_BUY_HEALTHCARE(int cost, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2387, void>(cost, p1, p2); }
	FORCEINLINE void NETWORK_BUY_AIRSTRIKE(int cost, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2388, void>(cost, p1, p2, p3); }
	FORCEINLINE void NETWORK_BUY_BACKUP_GANG(int p0, int p1, bool p2, bool p3, int npcProvider) { return YimMenu::NativeInvoker::Invoke<2389, void>(p0, p1, p2, p3, npcProvider); }
	FORCEINLINE void NETWORK_BUY_HELI_STRIKE(int cost, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2390, void>(cost, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_AMMO_DROP(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2391, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_BUY_BOUNTY(int amount, Player victim, bool p2, bool p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2392, void>(amount, victim, p2, p3, p4); }
	FORCEINLINE void NETWORK_BUY_PROPERTY(int cost, Hash propertyName, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2393, void>(cost, propertyName, p2, p3); }
	FORCEINLINE void NETWORK_BUY_SMOKES(int p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2394, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_HELI_PICKUP(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2395, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BOAT_PICKUP(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2396, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BULL_SHARK(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2397, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_CASH_DROP(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2398, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_HIRE_MUGGER(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2399, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_ROBBED_BY_MUGGER(int amount, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2400, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_HIRE_MERCENARY(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2401, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BUY_WANTEDLEVEL(Any p0, Any* p1, bool p2, bool p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2402, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPENT_BUY_OFFTHERADAR(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2403, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BUY_REVEAL_PLAYERS(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2404, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_CARWASH(Any p0, Any p1, Any p2, bool p3, bool p4) { return YimMenu::NativeInvoker::Invoke<2405, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPENT_CINEMA(Any p0, Any p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2406, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_TELESCOPE(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2407, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_HOLDUPS(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2408, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_BUY_PASSIVE_MODE(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2409, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BANK_INTEREST(int p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2410, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_PROSTITUTES(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2411, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_ARREST_BAIL(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2412, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(int amount, Hash vehicleModel, Any* gamerHandle, bool notBankrupt, bool hasTheMoney) { return YimMenu::NativeInvoker::Invoke<2413, void>(amount, vehicleModel, gamerHandle, notBankrupt, hasTheMoney); }
	FORCEINLINE void NETWORK_SPENT_CALL_PLAYER(Any p0, Any* p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2414, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BOUNTY(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2415, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_FROM_ROCKSTAR(int p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2416, void>(p0, p1, p2); }
	FORCEINLINE int NETWORK_SPEND_EARNED_FROM_BANK_AND_WALLETS(int amount) { return YimMenu::NativeInvoker::Invoke<2417, int>(amount); }
	FORCEINLINE const char* PROCESS_CASH_GIFT(int* p0, int* p1, const char* p2) { return YimMenu::NativeInvoker::Invoke<2418, const char*>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_MOVE_SUBMARINE(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2419, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_PLAYER_HEALTHCARE(int p0, int p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2420, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_NO_COPS(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2421, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_CARGO_SOURCING(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<2422, void>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void NETWORK_SPENT_REQUEST_JOB(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2423, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_REQUEST_HEIST(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2424, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_BUY_FAIRGROUND_RIDE(int amount, Any p1, bool p2, bool p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2425, void>(amount, p1, p2, p3, p4); }
	FORCEINLINE bool NETWORK_ECONOMY_HAS_FIXED_CRAZY_NUMBERS() { return YimMenu::NativeInvoker::Invoke<2426, bool>(); }
	FORCEINLINE void NETWORK_SPENT_JOB_SKIP(int amount, const char* matchId, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2427, void>(amount, matchId, p2, p3); }
	FORCEINLINE bool NETWORK_SPENT_BOSS_GOON(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2428, bool>(amount, p1, p2); }
	FORCEINLINE void NETWORK_SPEND_GOON(int p0, int p1, int amount) { return YimMenu::NativeInvoker::Invoke<2429, void>(p0, p1, amount); }
	FORCEINLINE void NETWORK_SPEND_BOSS(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2430, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_MOVE_YACHT(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2431, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_RENAME_ORGANIZATION(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2432, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_BUY_CONTRABAND_MISSION(int p0, int p1, Hash p2, bool p3, bool p4) { return YimMenu::NativeInvoker::Invoke<2433, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPENT_PA_SERVICE_HELI(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2434, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PA_SERVICE_VEHICLE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2435, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PA_SERVICE_SNACK(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2436, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PA_SERVICE_DANCER(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2437, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PA_SERVICE_IMPOUND(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2438, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_PA_HELI_PICKUP(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2439, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_OFFICE_PROPERTY(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2440, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_OFFICE_PROPERTY(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2441, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2442, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2443, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_IMPEXP_WAREHOUSE_PROPERTY(int amount, Any* data, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2444, void>(amount, data, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_IMPEXP_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2445, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_TRADE_IMPEXP_WAREHOUSE_PROPERTY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2446, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_ORDER_WAREHOUSE_VEHICLE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2447, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_ORDER_BODYGUARD_VEHICLE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2448, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_JUKEBOX(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2449, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_CLUB_HOUSE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2450, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_CLUB_HOUSE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2451, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2452, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2453, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_TRADE_BUSINESS_PROPERTY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2454, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_MC_ABILITY(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2455, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPENT_PAY_BUSINESS_SUPPLIES(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2456, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_CHANGE_APPEARANCE(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2457, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_VEHICLE_EXPORT_MODS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return YimMenu::NativeInvoker::Invoke<2458, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_OFFICE_GARAGE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2459, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_OFFICE_GARAGE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2460, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_IMPORT_EXPORT_REPAIR(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2461, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_HANGAR(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2462, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_HANGAR(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2463, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_HANGAR_UTILITY_CHARGES(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2464, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_HANGAR_STAFF_CHARGES(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2465, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_BUY_TRUCK(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2466, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_TRUCK(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2467, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BUY_BUNKER(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2468, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPRADE_BUNKER(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2469, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_FROM_SELL_BUNKER(int amount, Hash bunkerHash) { return YimMenu::NativeInvoker::Invoke<2470, void>(amount, bunkerHash); }
	FORCEINLINE void NETWORK_SPENT_BALLISTIC_EQUIPMENT(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2471, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_EARN_RDR_BONUS(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2472, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_WAGE_PAYMENT(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2473, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_WAGE_PAYMENT_BONUS(int amount) { return YimMenu::NativeInvoker::Invoke<2474, void>(amount); }
	FORCEINLINE void NETWORK_SPENT_BUY_BASE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2475, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_BASE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2476, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_BUY_TILTROTOR(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2477, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_TILTROTOR(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2478, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_EMPLOY_ASSASSINS(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2479, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_GANGOPS_CANNON(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2480, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_GANGOPS_SKIP_MISSION(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2481, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_CASINO_HEIST_SKIP_MISSION(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2482, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_SELL_BASE(int amount, Hash baseNameHash) { return YimMenu::NativeInvoker::Invoke<2483, void>(amount, baseNameHash); }
	FORCEINLINE void NETWORK_EARN_TARGET_REFUND(int amount, int p1) { return YimMenu::NativeInvoker::Invoke<2484, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_GANGOPS_WAGES(int amount, int p1) { return YimMenu::NativeInvoker::Invoke<2485, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_GANGOPS_WAGES_BONUS(int amount, int p1) { return YimMenu::NativeInvoker::Invoke<2486, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_DAR_CHALLENGE(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2487, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_DOOMSDAY_FINALE_BONUS(int amount, Hash vehicleHash) { return YimMenu::NativeInvoker::Invoke<2488, void>(amount, vehicleHash); }
	FORCEINLINE void NETWORK_EARN_GANGOPS_AWARD(int amount, const char* p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2489, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_EARN_GANGOPS_ELITE(int amount, const char* p1, int actIndex) { return YimMenu::NativeInvoker::Invoke<2490, void>(amount, p1, actIndex); }
	FORCEINLINE void NETWORK_SERVICE_EARN_GANGOPS_RIVAL_DELIVERY(int earnedMoney) { return YimMenu::NativeInvoker::Invoke<2491, void>(earnedMoney); }
	FORCEINLINE void NETWORK_SPEND_GANGOPS_START_STRAND(int type, int amount, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2492, void>(type, amount, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_GANGOPS_TRIP_SKIP(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2493, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_EARN_GANGOPS_PREP_PARTICIPATION(int amount) { return YimMenu::NativeInvoker::Invoke<2494, void>(amount); }
	FORCEINLINE void NETWORK_EARN_GANGOPS_SETUP(int amount, const char* p1) { return YimMenu::NativeInvoker::Invoke<2495, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_GANGOPS_FINALE(int amount, const char* p1) { return YimMenu::NativeInvoker::Invoke<2496, void>(amount, p1); }
	FORCEINLINE void NETWORK_SPEND_GANGOPS_REPAIR_COST(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2497, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_NIGHTCLUB(Any p0) { return YimMenu::NativeInvoker::Invoke<2498, void>(p0); }
	FORCEINLINE void NETWORK_EARN_NIGHTCLUB_DANCING(Any p0) { return YimMenu::NativeInvoker::Invoke<2499, void>(p0); }
	FORCEINLINE void NETWORK_EARN_BB_EVENT_BONUS(int amount) { return YimMenu::NativeInvoker::Invoke<2500, void>(amount); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_HACKER_TRUCK(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2501, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_HACKER_TRUCK(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2502, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_HACKER_TRUCK(Any p0, int amount, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2503, void>(p0, amount, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_PURCHASE_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2504, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_UPGRADE_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2505, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<2506, void>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void NETWORK_SPEND_NIGHTCLUB_AND_WAREHOUSE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2507, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_RDR_HATCHET_BONUS(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2508, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_NIGHTCLUB_ENTRY_FEE(Player player, int amount, Any p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2509, void>(player, amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_NIGHTCLUB_BAR_DRINK(int amount, Any p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2510, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_BOUNTY_HUNTER_MISSION(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2511, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_SPENT_REHIRE_DJ(int amount, Any p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2512, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPENT_ARENA_JOIN_SPECTATOR(int amount, Any p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2513, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_ARENA_SKILL_LEVEL_PROGRESSION(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2514, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_ARENA_CAREER_PROGRESSION(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2515, void>(amount, p1); }
	FORCEINLINE void NETWORK_SPEND_MAKE_IT_RAIN(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2516, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_SPEND_BUY_ARENA(int amount, bool p1, bool p2, const char* p3) { return YimMenu::NativeInvoker::Invoke<2517, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_UPGRADE_ARENA(int amount, bool p1, bool p2, const char* p3) { return YimMenu::NativeInvoker::Invoke<2518, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_ARENA_SPECTATOR_BOX(int amount, int type, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2519, void>(amount, type, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_SPIN_THE_WHEEL_PAYMENT(int amount, Any p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2520, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_EARN_SPIN_THE_WHEEL_CASH(int amount) { return YimMenu::NativeInvoker::Invoke<2521, void>(amount); }
	FORCEINLINE void NETWORK_SPEND_ARENA_PREMIUM(int amount, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2522, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_EARN_ARENA_WAR(int amount, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2523, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_ARENA_WAR_ASSASSINATE_TARGET(int amount) { return YimMenu::NativeInvoker::Invoke<2524, void>(amount); }
	FORCEINLINE void NETWORK_EARN_ARENA_WAR_EVENT_CARGO(int amount) { return YimMenu::NativeInvoker::Invoke<2525, void>(amount); }
	FORCEINLINE void NETWORK_EARN_RC_TIME_TRIAL(int amount) { return YimMenu::NativeInvoker::Invoke<2526, void>(amount); }
	FORCEINLINE void NETWORK_EARN_DAILY_OBJECTIVE_EVENT(int amount) { return YimMenu::NativeInvoker::Invoke<2527, void>(amount); }
	FORCEINLINE void NETWORK_SPEND_CASINO_MEMBERSHIP(int amount, bool p1, bool p2, int p3) { return YimMenu::NativeInvoker::Invoke<2528, void>(amount, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_BUY_CASINO(int amount, bool p1, bool p2, Any* data) { return YimMenu::NativeInvoker::Invoke<2529, void>(amount, p1, p2, data); }
	FORCEINLINE void NETWORK_SPEND_UPGRADE_CASINO(int amount, bool p1, bool p2, Any* data) { return YimMenu::NativeInvoker::Invoke<2530, void>(amount, p1, p2, data); }
	FORCEINLINE void NETWORK_SPEND_CASINO_GENERIC(int amount, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2531, void>(amount, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_EARN_CASINO_TIME_TRIAL_WIN(int amount) { return YimMenu::NativeInvoker::Invoke<2532, void>(amount); }
	FORCEINLINE void NETWORK_EARN_COLLECTABLES_ACTION_FIGURES(int amount) { return YimMenu::NativeInvoker::Invoke<2533, void>(amount); }
	FORCEINLINE void NETWORK_EARN_CASINO_COLLECTABLE_COMPLETED_COLLECTION(int amount) { return YimMenu::NativeInvoker::Invoke<2534, void>(amount); }
	FORCEINLINE void NETWORK_EARN_SELL_PRIZE_VEHICLE(int amount, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2535, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_EARN_CASINO_MISSION_REWARD(int amount) { return YimMenu::NativeInvoker::Invoke<2536, void>(amount); }
	FORCEINLINE void NETWORK_EARN_CASINO_STORY_MISSION_REWARD(int amount) { return YimMenu::NativeInvoker::Invoke<2537, void>(amount); }
	FORCEINLINE void NETWORK_EARN_CASINO_MISSION_PARTICIPATION(int amount) { return YimMenu::NativeInvoker::Invoke<2538, void>(amount); }
	FORCEINLINE void NETWORK_EARN_CASINO_AWARD(int amount, Hash hash) { return YimMenu::NativeInvoker::Invoke<2539, void>(amount, hash); }
	FORCEINLINE void NETWORK_SPEND_BUY_ARCADE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2540, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_UPGRADE_ARCADE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2541, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_CASINO_HEIST(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return YimMenu::NativeInvoker::Invoke<2542, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	FORCEINLINE void NETWORK_SPEND_ARCADE_MGMT(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2543, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPEND_PLAY_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2544, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPEND_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2545, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_EARN_CASINO_HEIST(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<2546, void>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void NETWORK_EARN_UPGRADE_ARCADE(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2547, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_ARCADE(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2548, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_EARN_COLLECTABLES(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2549, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_CHALLENGE(int amount, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2550, void>(amount, p1, p2); }
	FORCEINLINE void NETWORK_EARN_CASINO_HEIST_AWARDS(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2551, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_EARN_COLLECTABLE_ITEM(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2552, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_COLLECTABLE_COMPLETED_COLLECTION(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2553, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_YATCH_MISSION(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2554, void>(amount, p1); }
	FORCEINLINE void NETWORK_EARN_DISPATCH_CALL(int amount, Any p1) { return YimMenu::NativeInvoker::Invoke<2555, void>(amount, p1); }
	FORCEINLINE void NETWORK_SPEND_BEACH_PARTY(Any p0) { return YimMenu::NativeInvoker::Invoke<2556, void>(p0); }
	FORCEINLINE void NETWORK_SPEND_SUBMARINE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<2557, void>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void NETWORK_SPEND_CASINO_CLUB(int amount1, Any p1, bool p2, Any p3, int p4, int p5, int p6, int amount2, Any p8) { return YimMenu::NativeInvoker::Invoke<2558, void>(amount1, p1, p2, p3, p4, p5, p6, amount2, p8); }
	FORCEINLINE void NETWORK_SPEND_BUY_SUB(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2559, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_UPGRADE_SUB(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2560, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_ISLAND_HEIST(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2561, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_ISLAND_HEIST(int amount1, Any p1, Any p2, Any p3, int amount2, int p5) { return YimMenu::NativeInvoker::Invoke<2562, void>(amount1, p1, p2, p3, amount2, p5); }
	FORCEINLINE void NETWORK_EARN_BEACH_PARTY_LOST_FOUND(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2563, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_FROM_ISLAND_HEIST_DJ_MISSION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2564, void>(p0, p1); }
	FORCEINLINE void NETWORK_SPEND_CAR_CLUB_MEMBERSHIP(int amount1, Any p1, Any p2, int amount2, Any p4) { return YimMenu::NativeInvoker::Invoke<2565, void>(amount1, p1, p2, amount2, p4); }
	FORCEINLINE void NETWORK_SPEND_CAR_CLUB_BAR(Any p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2566, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_AUTOSHOP_MODIFY(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2567, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPEND_CAR_CLUB_TAKEOVER(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2568, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_BUY_AUTOSHOP(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2569, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_UPGRADE_AUTOSHOP(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2570, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_AUTOSHOP_BUSINESS(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2571, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_AUTOSHOP_INCOME(Any p0, int p1) { return YimMenu::NativeInvoker::Invoke<2572, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_CARCLUB_MEMBERSHIP(Any p0) { return YimMenu::NativeInvoker::Invoke<2573, void>(p0); }
	FORCEINLINE void NETWORK_EARN_DAILY_VEHICLE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2574, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_DAILY_VEHICLE_BONUS(Any p0) { return YimMenu::NativeInvoker::Invoke<2575, void>(p0); }
	FORCEINLINE void NETWORK_EARN_TUNER_AWARD(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2576, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_TUNER_ROBBERY(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2577, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_EARN_UPGRADE_AUTOSHOP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2578, void>(p0, p1); }
	FORCEINLINE void NETWORK_SPEND_INTERACTION_MENU_ABILITY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2579, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_SET_COMMON_FIELDS(Any p0, Any p1, Any p2, bool p3) { return YimMenu::NativeInvoker::Invoke<2580, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_SET_DISCOUNT(bool p0) { return YimMenu::NativeInvoker::Invoke<2581, void>(p0); }
	FORCEINLINE void NETWORK_SPEND_BUY_AGENCY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2582, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_UPGRADE_AGENCY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2583, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_AGENCY(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2584, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPEND_HIDDEN(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2585, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_SOURCE_BIKE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2586, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_COMP_SUV(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2587, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_SUV_FST_TRVL(int p0, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2588, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_SUPPLY(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2589, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_BIKE_SHOP(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2590, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SPEND_VEHICLE_REQUESTED(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2591, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void NETWORK_SPEND_GUNRUNNING(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2592, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_AGENCY_SAFE(Any p0) { return YimMenu::NativeInvoker::Invoke<2593, void>(p0); }
	FORCEINLINE void NETWORK_EARN_AWARD_CONTRACT(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2594, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_AGENCY_CONTRACT(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2595, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_AWARD_PHONE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2596, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_AGENCY_PHONE(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2597, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_EARN_AWARD_FIXER_MISSION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2598, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_FIXER_PREP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2599, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_FIXER_FINALE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2600, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_FIXER_AGENCY_SHORT_TRIP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2601, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_AWARD_SHORT_TRIP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2602, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_FIXER_RIVAL_DELIVERY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2603, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_UPGRADE_AGENCY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2604, void>(p0, p1); }
	FORCEINLINE void NETWORK_SPEND_APARTMENT_UTILITIES(int amount, bool p1, bool p2, Any* data) { return YimMenu::NativeInvoker::Invoke<2605, void>(amount, p1, p2, data); }
	FORCEINLINE void NETWORK_SPEND_BUSINESS_PROPERTY_FEES(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2606, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_SIGHTSEEING_REWARD(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2607, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_EARN_BIKER_SHOP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2608, void>(p0, p1); }
	FORCEINLINE void NETWORK_EARN_BIKER(Any p0) { return YimMenu::NativeInvoker::Invoke<2609, void>(p0); }
	FORCEINLINE void NETWORK_YOHAN_SOURCE_GOODS(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2610, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_BUY_MFGARAGE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2611, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_UPGRADE_MFGARAGE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2612, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_BUY_SUPPLIES(int p0, bool p1, bool p2, int p3) { return YimMenu::NativeInvoker::Invoke<2613, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_BUY_ACID_LAB(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2614, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_UPGRADE_ACID_LAB_EQUIPMENT(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2615, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_UPGRADE_ACID_LAB_ARMOR(int p0, bool p1, bool p2, int p3) { return YimMenu::NativeInvoker::Invoke<2616, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_UPGRADE_ACID_LAB_SCOOP(int p0, bool p1, bool p2, int p3) { return YimMenu::NativeInvoker::Invoke<2617, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_UPGRADE_ACID_LAB_MINES(int p0, bool p1, bool p2, int p3) { return YimMenu::NativeInvoker::Invoke<2618, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_RENAME_ACID_LAB(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2619, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_SPEND_RENAME_ACID_PRODUCT(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2620, void>(p0, p1, p2, p3); }
	FORCEINLINE void _NETWORK_EARN_AWARD_JUGGALO_MISSION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2621, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_AWARD_ACID_LAB(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2622, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_AWARD_DAILY_STASH(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2623, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_AWARD_DEAD_DROP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2624, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_AWARD_RANDOM_EVENT(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2625, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_AWARD_TAXI(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2626, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_STREET_DEALER(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2627, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_SELL_ACID(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2628, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_SETUP_PARTICIPATION_ACID_LAB(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2629, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_SOURCE_PARTICIPATION_ACID_LAB(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2630, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_SELL_PARTICIPATION_ACID_LAB(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2631, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_JUGGALO_STORY_MISSION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2632, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_JUGGALO_STORY_MISSION_PARTICIPATION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2633, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_FOOLIGAN_JOB(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2634, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_FOOLIGAN_JOB_PARTICIPATION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2635, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_TAXI_JOB(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2636, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_DAILY_STASH_HOUSE_COMPLETED(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2637, void>(p0, p1); }
	FORCEINLINE void _NETWORK_EARN_DAILY_STASH_HOUSE_PARTICIPATION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2638, void>(p0, p1); }
	FORCEINLINE int NETWORK_GET_VC_BANK_BALANCE() { return YimMenu::NativeInvoker::Invoke<2639, int>(); }
	FORCEINLINE int NETWORK_GET_VC_WALLET_BALANCE(int characterSlot) { return YimMenu::NativeInvoker::Invoke<2640, int>(characterSlot); }
	FORCEINLINE int NETWORK_GET_VC_BALANCE() { return YimMenu::NativeInvoker::Invoke<2641, int>(); }
	FORCEINLINE int NETWORK_GET_EVC_BALANCE() { return YimMenu::NativeInvoker::Invoke<2642, int>(); }
	FORCEINLINE int NETWORK_GET_PVC_BALANCE() { return YimMenu::NativeInvoker::Invoke<2643, int>(); }
	FORCEINLINE const char* NETWORK_GET_STRING_WALLET_BALANCE(int characterSlot) { return YimMenu::NativeInvoker::Invoke<2644, const char*>(characterSlot); }
	FORCEINLINE const char* NETWORK_GET_STRING_BANK_BALANCE() { return YimMenu::NativeInvoker::Invoke<2645, const char*>(); }
	FORCEINLINE const char* NETWORK_GET_STRING_BANK_WALLET_BALANCE(int character) { return YimMenu::NativeInvoker::Invoke<2646, const char*>(character); }
	FORCEINLINE bool NETWORK_GET_CAN_SPEND_FROM_WALLET(int amount, int characterSlot) { return YimMenu::NativeInvoker::Invoke<2647, bool>(amount, characterSlot); }
	FORCEINLINE bool NETWORK_GET_CAN_SPEND_FROM_BANK(int amount) { return YimMenu::NativeInvoker::Invoke<2648, bool>(amount); }
	FORCEINLINE bool NETWORK_GET_CAN_SPEND_FROM_BANK_AND_WALLET(int amount, int characterSlot) { return YimMenu::NativeInvoker::Invoke<2649, bool>(amount, characterSlot); }
	FORCEINLINE int NETWORK_GET_PVC_TRANSFER_BALANCE() { return YimMenu::NativeInvoker::Invoke<2650, int>(); }
	FORCEINLINE bool NETWORK_GET_CAN_TRANSFER_CASH(int amount) { return YimMenu::NativeInvoker::Invoke<2651, bool>(amount); }
	FORCEINLINE bool NETWORK_CAN_RECEIVE_PLAYER_CASH(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2652, bool>(p0, p1, p2, p3); }
	FORCEINLINE int NETWORK_GET_REMAINING_TRANSFER_BALANCE() { return YimMenu::NativeInvoker::Invoke<2653, int>(); }
	FORCEINLINE int WITHDRAW_VC(int amount) { return YimMenu::NativeInvoker::Invoke<2654, int>(amount); }
	FORCEINLINE bool DEPOSIT_VC(int amount) { return YimMenu::NativeInvoker::Invoke<2655, bool>(amount); }
	FORCEINLINE bool HAS_VC_WITHDRAWAL_COMPLETED(Any p0) { return YimMenu::NativeInvoker::Invoke<2656, bool>(p0); }
	FORCEINLINE bool WAS_VC_WITHDRAWAL_SUCCESSFUL(Any p0) { return YimMenu::NativeInvoker::Invoke<2657, bool>(p0); }
}

namespace NETSHOPPING
{
	FORCEINLINE bool NET_GAMESERVER_USE_SERVER_TRANSACTIONS() { return YimMenu::NativeInvoker::Invoke<2658, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_CATALOG_ITEM_IS_VALID(const char* name) { return YimMenu::NativeInvoker::Invoke<2659, bool>(name); }
	FORCEINLINE bool NET_GAMESERVER_CATALOG_ITEM_KEY_IS_VALID(Hash hash) { return YimMenu::NativeInvoker::Invoke<2660, bool>(hash); }
	FORCEINLINE int NET_GAMESERVER_GET_PRICE(Hash itemHash, Hash categoryHash, bool p2) { return YimMenu::NativeInvoker::Invoke<2661, int>(itemHash, categoryHash, p2); }
	FORCEINLINE bool NET_GAMESERVER_CATALOG_IS_VALID() { return YimMenu::NativeInvoker::Invoke<2662, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_IS_CATALOG_CURRENT() { return YimMenu::NativeInvoker::Invoke<2663, bool>(); }
	FORCEINLINE Hash NET_GAMESERVER_GET_CATALOG_CLOUD_CRC() { return YimMenu::NativeInvoker::Invoke<2664, Hash>(); }
	FORCEINLINE bool NET_GAMESERVER_REFRESH_SERVER_CATALOG() { return YimMenu::NativeInvoker::Invoke<2665, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_RETRIEVE_CATALOG_REFRESH_STATUS(int* state) { return YimMenu::NativeInvoker::Invoke<2666, bool>(state); }
	FORCEINLINE bool NET_GAMESERVER_INIT_SESSION() { return YimMenu::NativeInvoker::Invoke<2667, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_RETRIEVE_INIT_SESSION_STATUS(int* p0) { return YimMenu::NativeInvoker::Invoke<2668, bool>(p0); }
	FORCEINLINE bool NET_GAMESERVER_START_SESSION(int charSlot) { return YimMenu::NativeInvoker::Invoke<2669, bool>(charSlot); }
	FORCEINLINE bool NET_GAMESERVER_START_SESSION_PENDING() { return YimMenu::NativeInvoker::Invoke<2670, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_RETRIEVE_START_SESSION_STATUS(int* p0) { return YimMenu::NativeInvoker::Invoke<2671, bool>(p0); }
	FORCEINLINE bool NET_GAMESERVER_RETRIEVE_SESSION_ERROR_CODE(int* p0) { return YimMenu::NativeInvoker::Invoke<2672, bool>(p0); }
	FORCEINLINE bool NET_GAMESERVER_IS_SESSION_VALID(int charSlot) { return YimMenu::NativeInvoker::Invoke<2673, bool>(charSlot); }
	FORCEINLINE bool NET_GAMESERVER_CLEAR_SESSION(int p0) { return YimMenu::NativeInvoker::Invoke<2674, bool>(p0); }
	FORCEINLINE bool NET_GAMESERVER_SESSION_APPLY_RECEIVED_DATA(int charSlot) { return YimMenu::NativeInvoker::Invoke<2675, bool>(charSlot); }
	FORCEINLINE bool NET_GAMESERVER_IS_SESSION_REFRESH_PENDING() { return YimMenu::NativeInvoker::Invoke<2676, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_START_SESSION_RESTART(bool inventory, bool playerbalance) { return YimMenu::NativeInvoker::Invoke<2677, bool>(inventory, playerbalance); }
	FORCEINLINE bool NET_GAMESERVER_TRANSACTION_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<2678, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_GET_SESSION_STATE_AND_STATUS(int* p0, bool* p1) { return YimMenu::NativeInvoker::Invoke<2679, bool>(p0, p1); }
	FORCEINLINE bool NET_GAMESERVER_BASKET_START(int* transactionId, Hash categoryHash, Hash actionHash, int flags) { return YimMenu::NativeInvoker::Invoke<2680, bool>(transactionId, categoryHash, actionHash, flags); }
	FORCEINLINE bool NET_GAMESERVER_BASKET_END() { return YimMenu::NativeInvoker::Invoke<2681, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_BASKET_IS_ACTIVE() { return YimMenu::NativeInvoker::Invoke<2682, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_BASKET_ADD_ITEM(Any* itemData, int quantity) { return YimMenu::NativeInvoker::Invoke<2683, bool>(itemData, quantity); }
	FORCEINLINE bool NET_GAMESERVER_BASKET_IS_FULL() { return YimMenu::NativeInvoker::Invoke<2684, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_BASKET_APPLY_SERVER_DATA(Any p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<2685, bool>(p0, p1); }
	FORCEINLINE bool NET_GAMESERVER_CHECKOUT_START(int transactionId) { return YimMenu::NativeInvoker::Invoke<2686, bool>(transactionId); }
	FORCEINLINE bool NET_GAMESERVER_BEGIN_SERVICE(int* transactionId, Hash categoryHash, Hash itemHash, Hash actionTypeHash, int value, int flags) { return YimMenu::NativeInvoker::Invoke<2687, bool>(transactionId, categoryHash, itemHash, actionTypeHash, value, flags); }
	FORCEINLINE bool NET_GAMESERVER_END_SERVICE(int transactionId) { return YimMenu::NativeInvoker::Invoke<2688, bool>(transactionId); }
	FORCEINLINE bool NET_GAMESERVER_DELETE_CHARACTER(int slot, bool transfer, Hash reason) { return YimMenu::NativeInvoker::Invoke<2689, bool>(slot, transfer, reason); }
	FORCEINLINE int NET_GAMESERVER_DELETE_CHARACTER_GET_STATUS() { return YimMenu::NativeInvoker::Invoke<2690, int>(); }
	FORCEINLINE bool NET_GAMESERVER_DELETE_SET_TELEMETRY_NONCE_SEED() { return YimMenu::NativeInvoker::Invoke<2691, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_TRANSFER_BANK_TO_WALLET(int charSlot, int amount) { return YimMenu::NativeInvoker::Invoke<2692, bool>(charSlot, amount); }
	FORCEINLINE bool NET_GAMESERVER_TRANSFER_WALLET_TO_BANK(int charSlot, int amount) { return YimMenu::NativeInvoker::Invoke<2693, bool>(charSlot, amount); }
	FORCEINLINE int NET_GAMESERVER_TRANSFER_BANK_TO_WALLET_GET_STATUS() { return YimMenu::NativeInvoker::Invoke<2694, int>(); }
	FORCEINLINE int NET_GAMESERVER_TRANSFER_WALLET_TO_BANK_GET_STATUS() { return YimMenu::NativeInvoker::Invoke<2695, int>(); }
	FORCEINLINE bool NET_GAMESERVER_TRANSFER_CASH_SET_TELEMETRY_NONCE_SEED() { return YimMenu::NativeInvoker::Invoke<2696, bool>(); }
	FORCEINLINE bool NET_GAMESERVER_SET_TELEMETRY_NONCE_SEED(int p0) { return YimMenu::NativeInvoker::Invoke<2697, bool>(p0); }
}

namespace NETWORK
{
	FORCEINLINE const char* GET_ONLINE_VERSION() { return YimMenu::NativeInvoker::Invoke<2698, const char*>(); }
	FORCEINLINE bool NETWORK_IS_SIGNED_IN() { return YimMenu::NativeInvoker::Invoke<2699, bool>(); }
	FORCEINLINE bool NETWORK_IS_SIGNED_ONLINE() { return YimMenu::NativeInvoker::Invoke<2700, bool>(); }
	FORCEINLINE bool NETWORK_IS_NP_AVAILABLE() { return YimMenu::NativeInvoker::Invoke<2701, bool>(); }
	FORCEINLINE bool NETWORK_IS_NP_PENDING() { return YimMenu::NativeInvoker::Invoke<2702, bool>(); }
	FORCEINLINE int NETWORK_GET_NP_UNAVAILABLE_REASON() { return YimMenu::NativeInvoker::Invoke<2703, int>(); }
	FORCEINLINE bool NETWORK_IS_CONNETED_TO_NP_PRESENCE() { return YimMenu::NativeInvoker::Invoke<2704, bool>(); }
	FORCEINLINE bool NETWORK_IS_LOGGED_IN_TO_PSN() { return YimMenu::NativeInvoker::Invoke<2705, bool>(); }
	FORCEINLINE bool NETWORK_HAS_VALID_ROS_CREDENTIALS() { return YimMenu::NativeInvoker::Invoke<2706, bool>(); }
	FORCEINLINE bool NETWORK_IS_REFRESHING_ROS_CREDENTIALS() { return YimMenu::NativeInvoker::Invoke<2707, bool>(); }
	FORCEINLINE bool NETWORK_IS_CLOUD_AVAILABLE() { return YimMenu::NativeInvoker::Invoke<2708, bool>(); }
	FORCEINLINE bool NETWORK_HAS_SOCIAL_CLUB_ACCOUNT() { return YimMenu::NativeInvoker::Invoke<2709, bool>(); }
	FORCEINLINE bool NETWORK_ARE_SOCIAL_CLUB_POLICIES_CURRENT() { return YimMenu::NativeInvoker::Invoke<2710, bool>(); }
	FORCEINLINE bool NETWORK_IS_HOST() { return YimMenu::NativeInvoker::Invoke<2711, bool>(); }
	FORCEINLINE Player NETWORK_GET_HOST_PLAYER_INDEX() { return YimMenu::NativeInvoker::Invoke<2712, Player>(); }
	FORCEINLINE bool NETWORK_WAS_GAME_SUSPENDED() { return YimMenu::NativeInvoker::Invoke<2713, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_ONLINE_PRIVILEGES() { return YimMenu::NativeInvoker::Invoke<2714, bool>(); }
	FORCEINLINE bool NETWORK_HAS_AGE_RESTRICTIONS() { return YimMenu::NativeInvoker::Invoke<2715, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_USER_CONTENT_PRIVILEGES(int p0) { return YimMenu::NativeInvoker::Invoke<2716, bool>(p0); }
	FORCEINLINE bool NETWORK_HAVE_COMMUNICATION_PRIVILEGES(int p0, Player player) { return YimMenu::NativeInvoker::Invoke<2717, bool>(p0, player); }
	FORCEINLINE bool NETWORK_CHECK_ONLINE_PRIVILEGES(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<2718, bool>(p0, p1); }
	FORCEINLINE bool NETWORK_CHECK_USER_CONTENT_PRIVILEGES(int p0, int p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2719, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_CHECK_COMMUNICATION_PRIVILEGES(int p0, int p1, bool p2) { return YimMenu::NativeInvoker::Invoke<2720, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_CHECK_TEXT_COMMUNICATION_PRIVILEGES(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2721, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_IS_USING_ONLINE_PROMOTION() { return YimMenu::NativeInvoker::Invoke<2722, bool>(); }
	FORCEINLINE bool NETWORK_SHOULD_SHOW_PROMOTION_ALERT_SCREEN() { return YimMenu::NativeInvoker::Invoke<2723, bool>(); }
	FORCEINLINE bool NETWORK_HAS_SOCIAL_NETWORKING_SHARING_PRIV() { return YimMenu::NativeInvoker::Invoke<2724, bool>(); }
	FORCEINLINE int NETWORK_GET_AGE_GROUP() { return YimMenu::NativeInvoker::Invoke<2725, int>(); }
	FORCEINLINE bool NETWORK_CHECK_PRIVILEGES(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2726, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_IS_PRIVILEGE_CHECK_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<2727, bool>(); }
	FORCEINLINE void NETWORK_SET_PRIVILEGE_CHECK_RESULT_NOT_NEEDED() { return YimMenu::NativeInvoker::Invoke<2728, void>(); }
	FORCEINLINE bool NETWORK_RESOLVE_PRIVILEGE_USER_CONTENT() { return YimMenu::NativeInvoker::Invoke<2729, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_PLATFORM_SUBSCRIPTION() { return YimMenu::NativeInvoker::Invoke<2730, bool>(); }
	FORCEINLINE bool NETWORK_IS_PLATFORM_SUBSCRIPTION_CHECK_PENDING() { return YimMenu::NativeInvoker::Invoke<2731, bool>(); }
	FORCEINLINE void NETWORK_SHOW_ACCOUNT_UPGRADE_UI() { return YimMenu::NativeInvoker::Invoke<2732, void>(); }
	FORCEINLINE bool NETWORK_IS_SHOWING_SYSTEM_UI_OR_RECENTLY_REQUESTED_UPSELL() { return YimMenu::NativeInvoker::Invoke<2733, bool>(); }
	FORCEINLINE bool NETWORK_NEED_TO_START_NEW_GAME_BUT_BLOCKED() { return YimMenu::NativeInvoker::Invoke<2734, bool>(); }
	FORCEINLINE bool NETWORK_CAN_BAIL() { return YimMenu::NativeInvoker::Invoke<2735, bool>(); }
	FORCEINLINE void NETWORK_BAIL(int p0, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<2736, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_ON_RETURN_TO_SINGLE_PLAYER() { return YimMenu::NativeInvoker::Invoke<2737, void>(); }
	FORCEINLINE bool NETWORK_TRANSITION_START(int p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2738, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool NETWORK_TRANSITION_ADD_STAGE(Hash hash, int p1, int p2, int state, int p4) { return YimMenu::NativeInvoker::Invoke<2739, bool>(hash, p1, p2, state, p4); }
	FORCEINLINE bool NETWORK_TRANSITION_FINISH(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2740, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_CAN_ACCESS_MULTIPLAYER(int* loadingState) { return YimMenu::NativeInvoker::Invoke<2741, bool>(loadingState); }
	FORCEINLINE bool NETWORK_IS_MULTIPLAYER_DISABLED() { return YimMenu::NativeInvoker::Invoke<2742, bool>(); }
	FORCEINLINE bool NETWORK_CAN_ENTER_MULTIPLAYER() { return YimMenu::NativeInvoker::Invoke<2743, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_DO_FREEROAM_QUICKMATCH(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2744, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_SESSION_DO_FRIEND_MATCHMAKING(int p0, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<2745, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_SESSION_DO_CREW_MATCHMAKING(int crewId, int p1, int p2, int maxPlayers) { return YimMenu::NativeInvoker::Invoke<2746, bool>(crewId, p1, p2, maxPlayers); }
	FORCEINLINE bool NETWORK_SESSION_DO_ACTIVITY_QUICKMATCH(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<2747, bool>(p0, p1, p2, p3, p4); }
	FORCEINLINE bool NETWORK_SESSION_HOST(int p0, int maxPlayers, bool p2) { return YimMenu::NativeInvoker::Invoke<2748, bool>(p0, maxPlayers, p2); }
	FORCEINLINE bool NETWORK_SESSION_HOST_CLOSED(int p0, int maxPlayers) { return YimMenu::NativeInvoker::Invoke<2749, bool>(p0, maxPlayers); }
	FORCEINLINE bool NETWORK_SESSION_HOST_FRIENDS_ONLY(int p0, int maxPlayers) { return YimMenu::NativeInvoker::Invoke<2750, bool>(p0, maxPlayers); }
	FORCEINLINE bool NETWORK_SESSION_IS_CLOSED_FRIENDS() { return YimMenu::NativeInvoker::Invoke<2751, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_IS_CLOSED_CREW() { return YimMenu::NativeInvoker::Invoke<2752, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_IS_SOLO() { return YimMenu::NativeInvoker::Invoke<2753, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_IS_PRIVATE() { return YimMenu::NativeInvoker::Invoke<2754, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_END(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<2755, bool>(p0, p1); }
	FORCEINLINE bool NETWORK_SESSION_LEAVE(Any p0) { return YimMenu::NativeInvoker::Invoke<2756, bool>(p0); }
	FORCEINLINE void NETWORK_SESSION_KICK_PLAYER(Player player) { return YimMenu::NativeInvoker::Invoke<2757, void>(player); }
	FORCEINLINE bool NETWORK_SESSION_GET_KICK_VOTE(Player player) { return YimMenu::NativeInvoker::Invoke<2758, bool>(player); }
	FORCEINLINE bool NETWORK_SESSION_RESERVE_SLOTS_TRANSITION(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2759, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_JOIN_PREVIOUSLY_FAILED_SESSION() { return YimMenu::NativeInvoker::Invoke<2760, bool>(); }
	FORCEINLINE bool NETWORK_JOIN_PREVIOUSLY_FAILED_TRANSITION() { return YimMenu::NativeInvoker::Invoke<2761, bool>(); }
	FORCEINLINE void NETWORK_SESSION_SET_MATCHMAKING_GROUP(int matchmakingGroup) { return YimMenu::NativeInvoker::Invoke<2762, void>(matchmakingGroup); }
	FORCEINLINE void NETWORK_SESSION_SET_MATCHMAKING_GROUP_MAX(int playerType, int playerCount) { return YimMenu::NativeInvoker::Invoke<2763, void>(playerType, playerCount); }
	FORCEINLINE int NETWORK_SESSION_GET_MATCHMAKING_GROUP_FREE(int p0) { return YimMenu::NativeInvoker::Invoke<2764, int>(p0); }
	FORCEINLINE void NETWORK_SESSION_ADD_ACTIVE_MATCHMAKING_GROUP(int groupId) { return YimMenu::NativeInvoker::Invoke<2765, void>(groupId); }
	FORCEINLINE void NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT(Any p0) { return YimMenu::NativeInvoker::Invoke<2766, void>(p0); }
	FORCEINLINE void NETWORK_SESSION_SET_UNIQUE_CREW_LIMIT_TRANSITION(Any p0) { return YimMenu::NativeInvoker::Invoke<2767, void>(p0); }
	FORCEINLINE void NETWORK_SESSION_SET_UNIQUE_CREW_ONLY_CREWS_TRANSITION(bool p0) { return YimMenu::NativeInvoker::Invoke<2768, void>(p0); }
	FORCEINLINE void NETWORK_SESSION_SET_CREW_LIMIT_MAX_MEMBERS_TRANSITION(Any p0) { return YimMenu::NativeInvoker::Invoke<2769, void>(p0); }
	FORCEINLINE void NETWORK_SESSION_SET_MATCHMAKING_PROPERTY_ID(bool p0) { return YimMenu::NativeInvoker::Invoke<2770, void>(p0); }
	FORCEINLINE void NETWORK_SESSION_SET_MATCHMAKING_MENTAL_STATE(int p0) { return YimMenu::NativeInvoker::Invoke<2771, void>(p0); }
	FORCEINLINE void NETWORK_SESSION_SET_NUM_BOSSES(int num) { return YimMenu::NativeInvoker::Invoke<2772, void>(num); }
	FORCEINLINE void NETWORK_SESSION_SET_SCRIPT_VALIDATE_JOIN() { return YimMenu::NativeInvoker::Invoke<2773, void>(); }
	FORCEINLINE void NETWORK_SESSION_VALIDATE_JOIN(bool p0) { return YimMenu::NativeInvoker::Invoke<2774, void>(p0); }
	FORCEINLINE void NETWORK_ADD_FOLLOWERS(int* p0, int p1) { return YimMenu::NativeInvoker::Invoke<2775, void>(p0, p1); }
	FORCEINLINE void NETWORK_CLEAR_FOLLOWERS() { return YimMenu::NativeInvoker::Invoke<2776, void>(); }
	FORCEINLINE void NETWORK_GET_GLOBAL_MULTIPLAYER_CLOCK(int* hours, int* minutes, int* seconds) { return YimMenu::NativeInvoker::Invoke<2777, void>(hours, minutes, seconds); }
	FORCEINLINE void NETWORK_SESSION_SET_GAMEMODE(Any p0) { return YimMenu::NativeInvoker::Invoke<2778, void>(p0); }
	FORCEINLINE int NETWORK_SESSION_GET_HOST_AIM_PREFERENCE() { return YimMenu::NativeInvoker::Invoke<2779, int>(); }
	FORCEINLINE bool NETWORK_FIND_GAMERS_IN_CREW(int crewId) { return YimMenu::NativeInvoker::Invoke<2780, bool>(crewId); }
	FORCEINLINE bool NETWORK_FIND_MATCHED_GAMERS(int attribute, float fallbackLimit, float lowerLimit, float upperLimit) { return YimMenu::NativeInvoker::Invoke<2781, bool>(attribute, fallbackLimit, lowerLimit, upperLimit); }
	FORCEINLINE bool NETWORK_IS_FINDING_GAMERS() { return YimMenu::NativeInvoker::Invoke<2782, bool>(); }
	FORCEINLINE bool NETWORK_DID_FIND_GAMERS_SUCCEED() { return YimMenu::NativeInvoker::Invoke<2783, bool>(); }
	FORCEINLINE int NETWORK_GET_NUM_FOUND_GAMERS() { return YimMenu::NativeInvoker::Invoke<2784, int>(); }
	FORCEINLINE bool NETWORK_GET_FOUND_GAMER(Any* p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2785, bool>(p0, p1); }
	FORCEINLINE void NETWORK_CLEAR_FOUND_GAMERS() { return YimMenu::NativeInvoker::Invoke<2786, void>(); }
	FORCEINLINE bool NETWORK_QUEUE_GAMER_FOR_STATUS(Any* p0) { return YimMenu::NativeInvoker::Invoke<2787, bool>(p0); }
	FORCEINLINE bool NETWORK_GET_GAMER_STATUS_FROM_QUEUE() { return YimMenu::NativeInvoker::Invoke<2788, bool>(); }
	FORCEINLINE bool NETWORK_IS_GETTING_GAMER_STATUS() { return YimMenu::NativeInvoker::Invoke<2789, bool>(); }
	FORCEINLINE bool NETWORK_DID_GET_GAMER_STATUS_SUCCEED() { return YimMenu::NativeInvoker::Invoke<2790, bool>(); }
	FORCEINLINE bool NETWORK_GET_GAMER_STATUS_RESULT(Any* p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2791, bool>(p0, p1); }
	FORCEINLINE void NETWORK_CLEAR_GET_GAMER_STATUS() { return YimMenu::NativeInvoker::Invoke<2792, void>(); }
	FORCEINLINE void NETWORK_SESSION_JOIN_INVITE() { return YimMenu::NativeInvoker::Invoke<2793, void>(); }
	FORCEINLINE void NETWORK_SESSION_CANCEL_INVITE() { return YimMenu::NativeInvoker::Invoke<2794, void>(); }
	FORCEINLINE void NETWORK_SESSION_FORCE_CANCEL_INVITE() { return YimMenu::NativeInvoker::Invoke<2795, void>(); }
	FORCEINLINE bool NETWORK_HAS_PENDING_INVITE() { return YimMenu::NativeInvoker::Invoke<2796, bool>(); }
	FORCEINLINE bool NETWORK_HAS_CONFIRMED_INVITE() { return YimMenu::NativeInvoker::Invoke<2797, bool>(); }
	FORCEINLINE bool NETWORK_REQUEST_INVITE_CONFIRMED_EVENT() { return YimMenu::NativeInvoker::Invoke<2798, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_WAS_INVITED() { return YimMenu::NativeInvoker::Invoke<2799, bool>(); }
	FORCEINLINE void NETWORK_SESSION_GET_INVITER(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2800, void>(gamerHandle); }
	FORCEINLINE bool NETWORK_SESSION_IS_AWAITING_INVITE_RESPONSE() { return YimMenu::NativeInvoker::Invoke<2801, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_IS_DISPLAYING_INVITE_CONFIRMATION() { return YimMenu::NativeInvoker::Invoke<2802, bool>(); }
	FORCEINLINE void NETWORK_SUPPRESS_INVITE(bool toggle) { return YimMenu::NativeInvoker::Invoke<2803, void>(toggle); }
	FORCEINLINE void NETWORK_BLOCK_INVITES(bool toggle) { return YimMenu::NativeInvoker::Invoke<2804, void>(toggle); }
	FORCEINLINE void NETWORK_BLOCK_JOIN_QUEUE_INVITES(bool toggle) { return YimMenu::NativeInvoker::Invoke<2805, void>(toggle); }
	FORCEINLINE void NETWORK_SET_CAN_RECEIVE_RS_INVITES(bool p0) { return YimMenu::NativeInvoker::Invoke<2806, void>(p0); }
	FORCEINLINE void NETWORK_STORE_INVITE_THROUGH_RESTART() { return YimMenu::NativeInvoker::Invoke<2807, void>(); }
	FORCEINLINE void NETWORK_ALLOW_INVITE_PROCESS_IN_PLAYER_SWITCH(bool p0) { return YimMenu::NativeInvoker::Invoke<2808, void>(p0); }
	FORCEINLINE void NETWORK_SET_SCRIPT_READY_FOR_EVENTS(bool toggle) { return YimMenu::NativeInvoker::Invoke<2809, void>(toggle); }
	FORCEINLINE bool NETWORK_IS_OFFLINE_INVITE_PENDING() { return YimMenu::NativeInvoker::Invoke<2810, bool>(); }
	FORCEINLINE void NETWORK_CLEAR_OFFLINE_INVITE_PENDING() { return YimMenu::NativeInvoker::Invoke<2811, void>(); }
	FORCEINLINE void NETWORK_SESSION_HOST_SINGLE_PLAYER(int p0) { return YimMenu::NativeInvoker::Invoke<2812, void>(p0); }
	FORCEINLINE void NETWORK_SESSION_LEAVE_SINGLE_PLAYER() { return YimMenu::NativeInvoker::Invoke<2813, void>(); }
	FORCEINLINE bool NETWORK_IS_GAME_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<2814, bool>(); }
	FORCEINLINE bool NETWORK_IS_SESSION_ACTIVE() { return YimMenu::NativeInvoker::Invoke<2815, bool>(); }
	FORCEINLINE bool NETWORK_IS_IN_SESSION() { return YimMenu::NativeInvoker::Invoke<2816, bool>(); }
	FORCEINLINE bool NETWORK_IS_SESSION_STARTED() { return YimMenu::NativeInvoker::Invoke<2817, bool>(); }
	FORCEINLINE bool NETWORK_IS_SESSION_BUSY() { return YimMenu::NativeInvoker::Invoke<2818, bool>(); }
	FORCEINLINE bool NETWORK_CAN_SESSION_END() { return YimMenu::NativeInvoker::Invoke<2819, bool>(); }
	FORCEINLINE int NETWORK_GET_GAME_MODE() { return YimMenu::NativeInvoker::Invoke<2820, int>(); }
	FORCEINLINE void NETWORK_SESSION_MARK_VISIBLE(bool toggle) { return YimMenu::NativeInvoker::Invoke<2821, void>(toggle); }
	FORCEINLINE bool NETWORK_SESSION_IS_VISIBLE() { return YimMenu::NativeInvoker::Invoke<2822, bool>(); }
	FORCEINLINE void NETWORK_SESSION_BLOCK_JOIN_REQUESTS(bool toggle) { return YimMenu::NativeInvoker::Invoke<2823, void>(toggle); }
	FORCEINLINE void NETWORK_SESSION_CHANGE_SLOTS(int slots, bool p1) { return YimMenu::NativeInvoker::Invoke<2824, void>(slots, p1); }
	FORCEINLINE int NETWORK_SESSION_GET_PRIVATE_SLOTS() { return YimMenu::NativeInvoker::Invoke<2825, int>(); }
	FORCEINLINE bool NETWORK_SESSION_VOICE_HOST() { return YimMenu::NativeInvoker::Invoke<2826, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_VOICE_LEAVE() { return YimMenu::NativeInvoker::Invoke<2827, bool>(); }
	FORCEINLINE void NETWORK_SESSION_VOICE_CONNECT_TO_PLAYER(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2828, void>(gamerHandle); }
	FORCEINLINE void NETWORK_SESSION_VOICE_RESPOND_TO_REQUEST(bool p0, int p1) { return YimMenu::NativeInvoker::Invoke<2829, void>(p0, p1); }
	FORCEINLINE void NETWORK_SESSION_VOICE_SET_TIMEOUT(int timeout) { return YimMenu::NativeInvoker::Invoke<2830, void>(timeout); }
	FORCEINLINE bool NETWORK_SESSION_IS_IN_VOICE_SESSION() { return YimMenu::NativeInvoker::Invoke<2831, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_IS_VOICE_SESSION_ACTIVE() { return YimMenu::NativeInvoker::Invoke<2832, bool>(); }
	FORCEINLINE bool NETWORK_SESSION_IS_VOICE_SESSION_BUSY() { return YimMenu::NativeInvoker::Invoke<2833, bool>(); }
	FORCEINLINE bool NETWORK_SEND_TEXT_MESSAGE(const char* message, Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2834, bool>(message, gamerHandle); }
	FORCEINLINE void NETWORK_SET_ACTIVITY_SPECTATOR(bool toggle) { return YimMenu::NativeInvoker::Invoke<2835, void>(toggle); }
	FORCEINLINE bool NETWORK_IS_ACTIVITY_SPECTATOR() { return YimMenu::NativeInvoker::Invoke<2836, bool>(); }
	FORCEINLINE void NETWORK_SET_ACTIVITY_PLAYER_MAX(Any p0) { return YimMenu::NativeInvoker::Invoke<2837, void>(p0); }
	FORCEINLINE void NETWORK_SET_ACTIVITY_SPECTATOR_MAX(int maxSpectators) { return YimMenu::NativeInvoker::Invoke<2838, void>(maxSpectators); }
	FORCEINLINE int NETWORK_GET_ACTIVITY_PLAYER_NUM(bool p0) { return YimMenu::NativeInvoker::Invoke<2839, int>(p0); }
	FORCEINLINE bool NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2840, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_HOST_TRANSITION(int p0, int p1, int p2, int p3, Any p4, bool p5, bool p6, int p7, Any p8, int p9) { return YimMenu::NativeInvoker::Invoke<2841, bool>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	FORCEINLINE bool NETWORK_DO_TRANSITION_QUICKMATCH(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<2842, bool>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE bool NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<2843, bool>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE bool NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP(Any p0, Any p1, Any p2, Any p3, Any* p4, Any p5, Any p6, Any p7) { return YimMenu::NativeInvoker::Invoke<2844, bool>(p0, p1, p2, p3, p4, p5, p6, p7); }
	FORCEINLINE bool NETWORK_JOIN_GROUP_ACTIVITY() { return YimMenu::NativeInvoker::Invoke<2845, bool>(); }
	FORCEINLINE void NETWORK_CLEAR_GROUP_ACTIVITY() { return YimMenu::NativeInvoker::Invoke<2846, void>(); }
	FORCEINLINE void NETWORK_RETAIN_ACTIVITY_GROUP() { return YimMenu::NativeInvoker::Invoke<2847, void>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_CLOSED_FRIENDS() { return YimMenu::NativeInvoker::Invoke<2848, bool>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_CLOSED_CREW() { return YimMenu::NativeInvoker::Invoke<2849, bool>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_SOLO() { return YimMenu::NativeInvoker::Invoke<2850, bool>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_PRIVATE() { return YimMenu::NativeInvoker::Invoke<2851, bool>(); }
	FORCEINLINE int NETWORK_GET_NUM_TRANSITION_NON_ASYNC_GAMERS() { return YimMenu::NativeInvoker::Invoke<2852, int>(); }
	FORCEINLINE void NETWORK_MARK_AS_PREFERRED_ACTIVITY(bool p0) { return YimMenu::NativeInvoker::Invoke<2853, void>(p0); }
	FORCEINLINE void NETWORK_MARK_AS_WAITING_ASYNC(bool p0) { return YimMenu::NativeInvoker::Invoke<2854, void>(p0); }
	FORCEINLINE void NETWORK_SET_IN_PROGRESS_FINISH_TIME(Any p0) { return YimMenu::NativeInvoker::Invoke<2855, void>(p0); }
	FORCEINLINE void NETWORK_SET_TRANSITION_CREATOR_HANDLE(Any* p0) { return YimMenu::NativeInvoker::Invoke<2856, void>(p0); }
	FORCEINLINE void NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE() { return YimMenu::NativeInvoker::Invoke<2857, void>(); }
	FORCEINLINE bool NETWORK_INVITE_GAMERS_TO_TRANSITION(Any* p0, Any p1) { return YimMenu::NativeInvoker::Invoke<2858, bool>(p0, p1); }
	FORCEINLINE void NETWORK_SET_GAMER_INVITED_TO_TRANSITION(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2859, void>(gamerHandle); }
	FORCEINLINE bool NETWORK_LEAVE_TRANSITION() { return YimMenu::NativeInvoker::Invoke<2860, bool>(); }
	FORCEINLINE bool NETWORK_LAUNCH_TRANSITION() { return YimMenu::NativeInvoker::Invoke<2861, bool>(); }
	FORCEINLINE void NETWORK_SET_DO_NOT_LAUNCH_FROM_JOIN_AS_MIGRATED_HOST(bool toggle) { return YimMenu::NativeInvoker::Invoke<2862, void>(toggle); }
	FORCEINLINE void NETWORK_CANCEL_TRANSITION_MATCHMAKING() { return YimMenu::NativeInvoker::Invoke<2863, void>(); }
	FORCEINLINE void NETWORK_BAIL_TRANSITION(int p0, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<2864, void>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_DO_TRANSITION_TO_GAME(bool p0, int maxPlayers) { return YimMenu::NativeInvoker::Invoke<2865, bool>(p0, maxPlayers); }
	FORCEINLINE bool NETWORK_DO_TRANSITION_TO_NEW_GAME(bool p0, int maxPlayers, bool p2) { return YimMenu::NativeInvoker::Invoke<2866, bool>(p0, maxPlayers, p2); }
	FORCEINLINE bool NETWORK_DO_TRANSITION_TO_FREEMODE(Any* p0, Any p1, bool p2, int players, bool p4) { return YimMenu::NativeInvoker::Invoke<2867, bool>(p0, p1, p2, players, p4); }
	FORCEINLINE bool NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(Any* p0, Any p1, int players, bool p3, bool p4, bool p5) { return YimMenu::NativeInvoker::Invoke<2868, bool>(p0, p1, players, p3, p4, p5); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_TO_GAME() { return YimMenu::NativeInvoker::Invoke<2869, bool>(); }
	FORCEINLINE int NETWORK_GET_TRANSITION_MEMBERS(Any* data, int dataCount) { return YimMenu::NativeInvoker::Invoke<2870, int>(data, dataCount); }
	FORCEINLINE void NETWORK_APPLY_TRANSITION_PARAMETER(int p0, int p1) { return YimMenu::NativeInvoker::Invoke<2871, void>(p0, p1); }
	FORCEINLINE void NETWORK_APPLY_TRANSITION_PARAMETER_STRING(int p0, const char* string, bool p2) { return YimMenu::NativeInvoker::Invoke<2872, void>(p0, string, p2); }
	FORCEINLINE bool NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(Any* gamerHandle, const char* p1, int p2, int p3, bool p4) { return YimMenu::NativeInvoker::Invoke<2873, bool>(gamerHandle, p1, p2, p3, p4); }
	FORCEINLINE bool NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(Any* p0) { return YimMenu::NativeInvoker::Invoke<2874, bool>(p0); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_HOST() { return YimMenu::NativeInvoker::Invoke<2875, bool>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2876, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_GET_TRANSITION_HOST(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2877, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_IS_IN_TRANSITION() { return YimMenu::NativeInvoker::Invoke<2878, bool>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_STARTED() { return YimMenu::NativeInvoker::Invoke<2879, bool>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_BUSY() { return YimMenu::NativeInvoker::Invoke<2880, bool>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_MATCHMAKING() { return YimMenu::NativeInvoker::Invoke<2881, bool>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_LEAVE_POSTPONED() { return YimMenu::NativeInvoker::Invoke<2882, bool>(); }
	FORCEINLINE void NETWORK_TRANSITION_SET_IN_PROGRESS(Any p0) { return YimMenu::NativeInvoker::Invoke<2883, void>(p0); }
	FORCEINLINE void NETWORK_TRANSITION_SET_CONTENT_CREATOR(Any p0) { return YimMenu::NativeInvoker::Invoke<2884, void>(p0); }
	FORCEINLINE void NETWORK_TRANSITION_SET_ACTIVITY_ISLAND(Any p0) { return YimMenu::NativeInvoker::Invoke<2885, void>(p0); }
	FORCEINLINE void NETWORK_OPEN_TRANSITION_MATCHMAKING() { return YimMenu::NativeInvoker::Invoke<2886, void>(); }
	FORCEINLINE void NETWORK_CLOSE_TRANSITION_MATCHMAKING() { return YimMenu::NativeInvoker::Invoke<2887, void>(); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_OPEN_TO_MATCHMAKING() { return YimMenu::NativeInvoker::Invoke<2888, bool>(); }
	FORCEINLINE void NETWORK_SET_TRANSITION_VISIBILITY_LOCK(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<2889, void>(p0, p1); }
	FORCEINLINE bool NETWORK_IS_TRANSITION_VISIBILITY_LOCKED() { return YimMenu::NativeInvoker::Invoke<2890, bool>(); }
	FORCEINLINE void NETWORK_SET_TRANSITION_ACTIVITY_ID(Any p0) { return YimMenu::NativeInvoker::Invoke<2891, void>(p0); }
	FORCEINLINE void NETWORK_CHANGE_TRANSITION_SLOTS(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<2892, void>(p0, p1); }
	FORCEINLINE void NETWORK_TRANSITION_BLOCK_JOIN_REQUESTS(bool p0) { return YimMenu::NativeInvoker::Invoke<2893, void>(p0); }
	FORCEINLINE bool NETWORK_HAS_PLAYER_STARTED_TRANSITION(Player player) { return YimMenu::NativeInvoker::Invoke<2894, bool>(player); }
	FORCEINLINE bool NETWORK_ARE_TRANSITION_DETAILS_VALID(Any p0) { return YimMenu::NativeInvoker::Invoke<2895, bool>(p0); }
	FORCEINLINE bool NETWORK_JOIN_TRANSITION(Player player) { return YimMenu::NativeInvoker::Invoke<2896, bool>(player); }
	FORCEINLINE bool NETWORK_HAS_INVITED_GAMER_TO_TRANSITION(Any* p0) { return YimMenu::NativeInvoker::Invoke<2897, bool>(p0); }
	FORCEINLINE bool NETWORK_HAS_TRANSITION_INVITE_BEEN_ACKED(Any* p0) { return YimMenu::NativeInvoker::Invoke<2898, bool>(p0); }
	FORCEINLINE bool NETWORK_IS_ACTIVITY_SESSION() { return YimMenu::NativeInvoker::Invoke<2899, bool>(); }
	FORCEINLINE void NETWORK_DISABLE_REALTIME_MULTIPLAYER() { return YimMenu::NativeInvoker::Invoke<2900, void>(); }
	FORCEINLINE void NETWORK_SET_PRESENCE_SESSION_INVITES_BLOCKED(bool toggle) { return YimMenu::NativeInvoker::Invoke<2901, void>(toggle); }
	FORCEINLINE bool NETWORK_SEND_INVITE_VIA_PRESENCE(Any* gamerHandle, const char* p1, int dataCount, int p3) { return YimMenu::NativeInvoker::Invoke<2902, bool>(gamerHandle, p1, dataCount, p3); }
	FORCEINLINE bool NETWORK_SEND_TRANSITION_INVITE_VIA_PRESENCE(Any* gamerHandle, const char* p1, int dataCount, int p3) { return YimMenu::NativeInvoker::Invoke<2903, bool>(gamerHandle, p1, dataCount, p3); }
	FORCEINLINE bool NETWORK_SEND_IMPORTANT_TRANSITION_INVITE_VIA_PRESENCE(Any* gamerHandle, const char* p1, int dataCount, int p3) { return YimMenu::NativeInvoker::Invoke<2904, bool>(gamerHandle, p1, dataCount, p3); }
	FORCEINLINE int NETWORK_GET_PRESENCE_INVITE_INDEX_BY_ID(int p0) { return YimMenu::NativeInvoker::Invoke<2905, int>(p0); }
	FORCEINLINE int NETWORK_GET_NUM_PRESENCE_INVITES() { return YimMenu::NativeInvoker::Invoke<2906, int>(); }
	FORCEINLINE bool NETWORK_ACCEPT_PRESENCE_INVITE(int p0) { return YimMenu::NativeInvoker::Invoke<2907, bool>(p0); }
	FORCEINLINE bool NETWORK_REMOVE_PRESENCE_INVITE(int p0) { return YimMenu::NativeInvoker::Invoke<2908, bool>(p0); }
	FORCEINLINE int NETWORK_GET_PRESENCE_INVITE_ID(int p0) { return YimMenu::NativeInvoker::Invoke<2909, int>(p0); }
	FORCEINLINE const char* NETWORK_GET_PRESENCE_INVITE_INVITER(int p0) { return YimMenu::NativeInvoker::Invoke<2910, const char*>(p0); }
	FORCEINLINE bool NETWORK_GET_PRESENCE_INVITE_HANDLE(Any p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<2911, bool>(p0, p1); }
	FORCEINLINE int NETWORK_GET_PRESENCE_INVITE_SESSION_ID(Any p0) { return YimMenu::NativeInvoker::Invoke<2912, int>(p0); }
	FORCEINLINE const char* NETWORK_GET_PRESENCE_INVITE_CONTENT_ID(int p0) { return YimMenu::NativeInvoker::Invoke<2913, const char*>(p0); }
	FORCEINLINE int NETWORK_GET_PRESENCE_INVITE_PLAYLIST_LENGTH(int p0) { return YimMenu::NativeInvoker::Invoke<2914, int>(p0); }
	FORCEINLINE int NETWORK_GET_PRESENCE_INVITE_PLAYLIST_CURRENT(int p0) { return YimMenu::NativeInvoker::Invoke<2915, int>(p0); }
	FORCEINLINE bool NETWORK_GET_PRESENCE_INVITE_FROM_ADMIN(int p0) { return YimMenu::NativeInvoker::Invoke<2916, bool>(p0); }
	FORCEINLINE bool NETWORK_GET_PRESENCE_INVITE_IS_TOURNAMENT(Any p0) { return YimMenu::NativeInvoker::Invoke<2917, bool>(p0); }
	FORCEINLINE bool NETWORK_HAS_FOLLOW_INVITE() { return YimMenu::NativeInvoker::Invoke<2918, bool>(); }
	FORCEINLINE bool NETWORK_ACTION_FOLLOW_INVITE() { return YimMenu::NativeInvoker::Invoke<2919, bool>(); }
	FORCEINLINE bool NETWORK_CLEAR_FOLLOW_INVITE() { return YimMenu::NativeInvoker::Invoke<2920, bool>(); }
	FORCEINLINE void NETWORK_REMOVE_AND_CANCEL_ALL_INVITES() { return YimMenu::NativeInvoker::Invoke<2921, void>(); }
	FORCEINLINE void NETWORK_REMOVE_TRANSITION_INVITE(Any* p0) { return YimMenu::NativeInvoker::Invoke<2922, void>(p0); }
	FORCEINLINE void NETWORK_REMOVE_ALL_TRANSITION_INVITE() { return YimMenu::NativeInvoker::Invoke<2923, void>(); }
	FORCEINLINE void NETWORK_REMOVE_AND_CANCEL_ALL_TRANSITION_INVITES() { return YimMenu::NativeInvoker::Invoke<2924, void>(); }
	FORCEINLINE bool NETWORK_INVITE_GAMERS(Any* p0, Any p1, Any* p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2925, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool NETWORK_HAS_INVITED_GAMER(Any* p0) { return YimMenu::NativeInvoker::Invoke<2926, bool>(p0); }
	FORCEINLINE bool NETWORK_HAS_MADE_INVITE_DECISION(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2927, bool>(gamerHandle); }
	FORCEINLINE int NETWORK_GET_INVITE_REPLY_STATUS(Any p0) { return YimMenu::NativeInvoker::Invoke<2928, int>(p0); }
	FORCEINLINE bool NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(Any* p0) { return YimMenu::NativeInvoker::Invoke<2929, bool>(p0); }
	FORCEINLINE bool NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(Any* p0) { return YimMenu::NativeInvoker::Invoke<2930, bool>(p0); }
	FORCEINLINE void NETWORK_SET_INVITE_ON_CALL_FOR_INVITE_MENU(Any* p0) { return YimMenu::NativeInvoker::Invoke<2931, void>(p0); }
	FORCEINLINE bool NETWORK_CHECK_DATA_MANAGER_SUCCEEDED_FOR_HANDLE(int p0, Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2932, bool>(p0, gamerHandle); }
	FORCEINLINE bool NETWORK_CHECK_DATA_MANAGER_FOR_HANDLE(Any p0, Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2933, bool>(p0, gamerHandle); }
	FORCEINLINE void NETWORK_SET_INVITE_FAILED_MESSAGE_FOR_INVITE_MENU(Any* p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<2934, void>(p0, p1); }
	FORCEINLINE bool FILLOUT_PM_PLAYER_LIST(Any* gamerHandle, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2935, bool>(gamerHandle, p1, p2); }
	FORCEINLINE bool FILLOUT_PM_PLAYER_LIST_WITH_NAMES(Any* p0, Any* p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<2936, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool REFRESH_PLAYER_LIST_STATS(int p0) { return YimMenu::NativeInvoker::Invoke<2937, bool>(p0); }
	FORCEINLINE bool NETWORK_SET_CURRENT_DATA_MANAGER_HANDLE(Any* p0) { return YimMenu::NativeInvoker::Invoke<2938, bool>(p0); }
	FORCEINLINE bool NETWORK_IS_IN_PLATFORM_PARTY() { return YimMenu::NativeInvoker::Invoke<2939, bool>(); }
	FORCEINLINE int NETWORK_GET_PLATFORM_PARTY_MEMBER_COUNT() { return YimMenu::NativeInvoker::Invoke<2940, int>(); }
	FORCEINLINE int NETWORK_GET_PLATFORM_PARTY_MEMBERS(Any* data, int dataSize) { return YimMenu::NativeInvoker::Invoke<2941, int>(data, dataSize); }
	FORCEINLINE bool NETWORK_IS_IN_PLATFORM_PARTY_CHAT() { return YimMenu::NativeInvoker::Invoke<2942, bool>(); }
	FORCEINLINE bool NETWORK_IS_CHATTING_IN_PLATFORM_PARTY(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<2943, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_QUEUE_FOR_PREVIOUS_SESSION_JOIN() { return YimMenu::NativeInvoker::Invoke<2944, bool>(); }
	FORCEINLINE bool NETWORK_IS_QUEUING_FOR_SESSION_JOIN() { return YimMenu::NativeInvoker::Invoke<2945, bool>(); }
	FORCEINLINE void NETWORK_CLEAR_QUEUED_JOIN_REQUEST() { return YimMenu::NativeInvoker::Invoke<2946, void>(); }
	FORCEINLINE void NETWORK_SEND_QUEUED_JOIN_REQUEST() { return YimMenu::NativeInvoker::Invoke<2947, void>(); }
	FORCEINLINE void NETWORK_REMOVE_ALL_QUEUED_JOIN_REQUESTS() { return YimMenu::NativeInvoker::Invoke<2948, void>(); }
	FORCEINLINE void NETWORK_SEED_RANDOM_NUMBER_GENERATOR(int seed) { return YimMenu::NativeInvoker::Invoke<2949, void>(seed); }
	FORCEINLINE int NETWORK_GET_RANDOM_INT() { return YimMenu::NativeInvoker::Invoke<2950, int>(); }
	FORCEINLINE int NETWORK_GET_RANDOM_INT_RANGED(int rangeStart, int rangeEnd) { return YimMenu::NativeInvoker::Invoke<2951, int>(rangeStart, rangeEnd); }
	FORCEINLINE float _NETWORK_GET_RANDOM_FLOAT_RANGED(float rangeStart, float rangeEnd) { return YimMenu::NativeInvoker::Invoke<2952, float>(rangeStart, rangeEnd); }
	FORCEINLINE bool NETWORK_PLAYER_IS_CHEATER() { return YimMenu::NativeInvoker::Invoke<2953, bool>(); }
	FORCEINLINE int NETWORK_PLAYER_GET_CHEATER_REASON() { return YimMenu::NativeInvoker::Invoke<2954, int>(); }
	FORCEINLINE bool NETWORK_PLAYER_IS_BADSPORT() { return YimMenu::NativeInvoker::Invoke<2955, bool>(); }
	FORCEINLINE bool REMOTE_CHEATER_PLAYER_DETECTED(Player player, int a, int b) { return YimMenu::NativeInvoker::Invoke<2956, bool>(player, a, b); }
	FORCEINLINE bool BAD_SPORT_PLAYER_LEFT_DETECTED(Any* gamerHandle, int event, int amountReceived) { return YimMenu::NativeInvoker::Invoke<2957, bool>(gamerHandle, event, amountReceived); }
	FORCEINLINE void NETWORK_ADD_INVALID_OBJECT_MODEL(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<2958, void>(modelHash); }
	FORCEINLINE void NETWORK_REMOVE_INVALID_OBJECT_MODEL(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<2959, void>(modelHash); }
	FORCEINLINE void NETWORK_CLEAR_INVALID_OBJECT_MODELS() { return YimMenu::NativeInvoker::Invoke<2960, void>(); }
	FORCEINLINE void NETWORK_APPLY_PED_SCAR_DATA(Ped ped, int p1) { return YimMenu::NativeInvoker::Invoke<2961, void>(ped, p1); }
	FORCEINLINE void NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(int maxNumMissionParticipants, bool p1, int instanceId) { return YimMenu::NativeInvoker::Invoke<2962, void>(maxNumMissionParticipants, p1, instanceId); }
	FORCEINLINE bool NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(Any p0, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2963, bool>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT() { return YimMenu::NativeInvoker::Invoke<2964, bool>(); }
	FORCEINLINE int NETWORK_GET_MAX_NUM_PARTICIPANTS() { return YimMenu::NativeInvoker::Invoke<2965, int>(); }
	FORCEINLINE int NETWORK_GET_NUM_PARTICIPANTS() { return YimMenu::NativeInvoker::Invoke<2966, int>(); }
	FORCEINLINE int NETWORK_GET_SCRIPT_STATUS() { return YimMenu::NativeInvoker::Invoke<2967, int>(); }
	FORCEINLINE void NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(int* vars, int numVars, const char* debugName) { return YimMenu::NativeInvoker::Invoke<2968, void>(vars, numVars, debugName); }
	FORCEINLINE void NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(int* vars, int numVars, const char* debugName) { return YimMenu::NativeInvoker::Invoke<2969, void>(vars, numVars, debugName); }
	FORCEINLINE void NETWORK_REGISTER_HIGH_FREQUENCY_HOST_BROADCAST_VARIABLES(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2970, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_REGISTER_HIGH_FREQUENCY_PLAYER_BROADCAST_VARIABLES(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<2971, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_FINISH_BROADCASTING_DATA() { return YimMenu::NativeInvoker::Invoke<2972, void>(); }
	FORCEINLINE bool NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA() { return YimMenu::NativeInvoker::Invoke<2973, bool>(); }
	FORCEINLINE Player NETWORK_GET_PLAYER_INDEX(Player player) { return YimMenu::NativeInvoker::Invoke<2974, Player>(player); }
	FORCEINLINE int NETWORK_GET_PARTICIPANT_INDEX(int index) { return YimMenu::NativeInvoker::Invoke<2975, int>(index); }
	FORCEINLINE Player NETWORK_GET_PLAYER_INDEX_FROM_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<2976, Player>(ped); }
	FORCEINLINE int NETWORK_GET_NUM_CONNECTED_PLAYERS() { return YimMenu::NativeInvoker::Invoke<2977, int>(); }
	FORCEINLINE bool NETWORK_IS_PLAYER_CONNECTED(Player player) { return YimMenu::NativeInvoker::Invoke<2978, bool>(player); }
	FORCEINLINE int NETWORK_GET_TOTAL_NUM_PLAYERS() { return YimMenu::NativeInvoker::Invoke<2979, int>(); }
	FORCEINLINE bool NETWORK_IS_PARTICIPANT_ACTIVE(int p0) { return YimMenu::NativeInvoker::Invoke<2980, bool>(p0); }
	FORCEINLINE bool NETWORK_IS_PLAYER_ACTIVE(Player player) { return YimMenu::NativeInvoker::Invoke<2981, bool>(player); }
	FORCEINLINE bool NETWORK_IS_PLAYER_A_PARTICIPANT(Player player) { return YimMenu::NativeInvoker::Invoke<2982, bool>(player); }
	FORCEINLINE bool NETWORK_IS_HOST_OF_THIS_SCRIPT() { return YimMenu::NativeInvoker::Invoke<2983, bool>(); }
	FORCEINLINE Player NETWORK_GET_HOST_OF_THIS_SCRIPT() { return YimMenu::NativeInvoker::Invoke<2984, Player>(); }
	FORCEINLINE Player NETWORK_GET_HOST_OF_SCRIPT(const char* scriptName, int instance_id, int position_hash) { return YimMenu::NativeInvoker::Invoke<2985, Player>(scriptName, instance_id, position_hash); }
	FORCEINLINE void NETWORK_SET_MISSION_FINISHED() { return YimMenu::NativeInvoker::Invoke<2986, void>(); }
	FORCEINLINE bool NETWORK_IS_SCRIPT_ACTIVE(const char* scriptName, int instance_id, bool p2, int position_hash) { return YimMenu::NativeInvoker::Invoke<2987, bool>(scriptName, instance_id, p2, position_hash); }
	FORCEINLINE bool NETWORK_IS_SCRIPT_ACTIVE_BY_HASH(Hash scriptHash, int p1, bool p2, int p3) { return YimMenu::NativeInvoker::Invoke<2988, bool>(scriptHash, p1, p2, p3); }
	FORCEINLINE bool NETWORK_IS_THREAD_A_NETWORK_SCRIPT(int threadId) { return YimMenu::NativeInvoker::Invoke<2989, bool>(threadId); }
	FORCEINLINE int NETWORK_GET_NUM_SCRIPT_PARTICIPANTS(const char* scriptName, int instance_id, int position_hash) { return YimMenu::NativeInvoker::Invoke<2990, int>(scriptName, instance_id, position_hash); }
	FORCEINLINE int NETWORK_GET_INSTANCE_ID_OF_THIS_SCRIPT() { return YimMenu::NativeInvoker::Invoke<2991, int>(); }
	FORCEINLINE Hash NETWORK_GET_POSITION_HASH_OF_THIS_SCRIPT() { return YimMenu::NativeInvoker::Invoke<2992, Hash>(); }
	FORCEINLINE bool NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(Player player, const char* script, int instance_id) { return YimMenu::NativeInvoker::Invoke<2993, bool>(player, script, instance_id); }
	FORCEINLINE void NETWORK_PREVENT_SCRIPT_HOST_MIGRATION() { return YimMenu::NativeInvoker::Invoke<2994, void>(); }
	FORCEINLINE void NETWORK_REQUEST_TO_BE_HOST_OF_THIS_SCRIPT() { return YimMenu::NativeInvoker::Invoke<2995, void>(); }
	FORCEINLINE Player PARTICIPANT_ID() { return YimMenu::NativeInvoker::Invoke<2996, Player>(); }
	FORCEINLINE int PARTICIPANT_ID_TO_INT() { return YimMenu::NativeInvoker::Invoke<2997, int>(); }
	FORCEINLINE Player NETWORK_GET_KILLER_OF_PLAYER(Player player, Hash* weaponHash) { return YimMenu::NativeInvoker::Invoke<2998, Player>(player, weaponHash); }
	FORCEINLINE Player NETWORK_GET_DESTROYER_OF_NETWORK_ID(int netId, Hash* weaponHash) { return YimMenu::NativeInvoker::Invoke<2999, Player>(netId, weaponHash); }
	FORCEINLINE Player NETWORK_GET_DESTROYER_OF_ENTITY(Entity entity, Hash* weaponHash) { return YimMenu::NativeInvoker::Invoke<3000, Player>(entity, weaponHash); }
	FORCEINLINE bool NETWORK_GET_ASSISTED_KILL_OF_ENTITY(Player player, Entity entity, int* p2) { return YimMenu::NativeInvoker::Invoke<3001, bool>(player, entity, p2); }
	FORCEINLINE bool NETWORK_GET_ASSISTED_DAMAGE_OF_ENTITY(Player player, Entity entity, int* p2) { return YimMenu::NativeInvoker::Invoke<3002, bool>(player, entity, p2); }
	FORCEINLINE Entity NETWORK_GET_ENTITY_KILLER_OF_PLAYER(Player player, Hash* weaponHash) { return YimMenu::NativeInvoker::Invoke<3003, Entity>(player, weaponHash); }
	FORCEINLINE void NETWORK_SET_CURRENT_PUBLIC_CONTENT_ID(const char* missionId) { return YimMenu::NativeInvoker::Invoke<3004, void>(missionId); }
	FORCEINLINE void NETWORK_SET_CURRENT_CHAT_OPTION(int newChatOption) { return YimMenu::NativeInvoker::Invoke<3005, void>(newChatOption); }
	FORCEINLINE void NETWORK_SET_CURRENT_SPAWN_LOCATION_OPTION(Hash mpSettingSpawn) { return YimMenu::NativeInvoker::Invoke<3006, void>(mpSettingSpawn); }
	FORCEINLINE void NETWORK_SET_VEHICLE_DRIVEN_IN_TEST_DRIVE(bool toggle) { return YimMenu::NativeInvoker::Invoke<3007, void>(toggle); }
	FORCEINLINE void NETWORK_RESURRECT_LOCAL_PLAYER(float x, float y, float z, float heading, bool p4, bool changetime, bool p6, int p7, int p8) { return YimMenu::NativeInvoker::Invoke<3008, void>(x, y, z, heading, p4, changetime, p6, p7, p8); }
	FORCEINLINE void NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(int time) { return YimMenu::NativeInvoker::Invoke<3009, void>(time); }
	FORCEINLINE bool NETWORK_IS_LOCAL_PLAYER_INVINCIBLE() { return YimMenu::NativeInvoker::Invoke<3010, bool>(); }
	FORCEINLINE void NETWORK_DISABLE_INVINCIBLE_FLASHING(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<3011, void>(player, toggle); }
	FORCEINLINE void NETWORK_PATCH_POST_CUTSCENE_HS4F_TUN_ENT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3012, void>(ped); }
	FORCEINLINE void NETWORK_SET_LOCAL_PLAYER_SYNC_LOOK_AT(bool toggle) { return YimMenu::NativeInvoker::Invoke<3013, void>(toggle); }
	FORCEINLINE bool NETWORK_HAS_ENTITY_BEEN_REGISTERED_WITH_THIS_THREAD(Entity entity) { return YimMenu::NativeInvoker::Invoke<3014, bool>(entity); }
	FORCEINLINE int NETWORK_GET_NETWORK_ID_FROM_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<3015, int>(entity); }
	FORCEINLINE Entity NETWORK_GET_ENTITY_FROM_NETWORK_ID(int netId) { return YimMenu::NativeInvoker::Invoke<3016, Entity>(netId); }
	FORCEINLINE bool NETWORK_GET_ENTITY_IS_NETWORKED(Entity entity) { return YimMenu::NativeInvoker::Invoke<3017, bool>(entity); }
	FORCEINLINE bool NETWORK_GET_ENTITY_IS_LOCAL(Entity entity) { return YimMenu::NativeInvoker::Invoke<3018, bool>(entity); }
	FORCEINLINE void NETWORK_REGISTER_ENTITY_AS_NETWORKED(Entity entity) { return YimMenu::NativeInvoker::Invoke<3019, void>(entity); }
	FORCEINLINE void NETWORK_UNREGISTER_NETWORKED_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<3020, void>(entity); }
	FORCEINLINE bool NETWORK_DOES_NETWORK_ID_EXIST(int netId) { return YimMenu::NativeInvoker::Invoke<3021, bool>(netId); }
	FORCEINLINE bool NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(int netId) { return YimMenu::NativeInvoker::Invoke<3022, bool>(netId); }
	FORCEINLINE bool NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(int netId) { return YimMenu::NativeInvoker::Invoke<3023, bool>(netId); }
	FORCEINLINE bool NETWORK_HAS_CONTROL_OF_NETWORK_ID(int netId) { return YimMenu::NativeInvoker::Invoke<3024, bool>(netId); }
	FORCEINLINE bool NETWORK_IS_NETWORK_ID_REMOTELY_CONTROLLED(int netId) { return YimMenu::NativeInvoker::Invoke<3025, bool>(netId); }
	FORCEINLINE bool NETWORK_REQUEST_CONTROL_OF_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<3026, bool>(entity); }
	FORCEINLINE bool NETWORK_REQUEST_CONTROL_OF_DOOR(int doorID) { return YimMenu::NativeInvoker::Invoke<3027, bool>(doorID); }
	FORCEINLINE bool NETWORK_HAS_CONTROL_OF_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<3028, bool>(entity); }
	FORCEINLINE bool NETWORK_HAS_CONTROL_OF_PICKUP(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3029, bool>(pickup); }
	FORCEINLINE bool NETWORK_HAS_CONTROL_OF_DOOR(Hash doorHash) { return YimMenu::NativeInvoker::Invoke<3030, bool>(doorHash); }
	FORCEINLINE bool NETWORK_IS_DOOR_NETWORKED(Hash doorHash) { return YimMenu::NativeInvoker::Invoke<3031, bool>(doorHash); }
	FORCEINLINE int VEH_TO_NET(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<3032, int>(vehicle); }
	FORCEINLINE int PED_TO_NET(Ped ped) { return YimMenu::NativeInvoker::Invoke<3033, int>(ped); }
	FORCEINLINE int OBJ_TO_NET(Object object) { return YimMenu::NativeInvoker::Invoke<3034, int>(object); }
	FORCEINLINE Vehicle NET_TO_VEH(int netHandle) { return YimMenu::NativeInvoker::Invoke<3035, Vehicle>(netHandle); }
	FORCEINLINE Ped NET_TO_PED(int netHandle) { return YimMenu::NativeInvoker::Invoke<3036, Ped>(netHandle); }
	FORCEINLINE Object NET_TO_OBJ(int netHandle) { return YimMenu::NativeInvoker::Invoke<3037, Object>(netHandle); }
	FORCEINLINE Entity NET_TO_ENT(int netHandle) { return YimMenu::NativeInvoker::Invoke<3038, Entity>(netHandle); }
	FORCEINLINE void NETWORK_GET_LOCAL_HANDLE(Any* gamerHandle, int gamerHandleSize) { return YimMenu::NativeInvoker::Invoke<3039, void>(gamerHandle, gamerHandleSize); }
	FORCEINLINE void NETWORK_HANDLE_FROM_USER_ID(const char* userId, Any* gamerHandle, int gamerHandleSize) { return YimMenu::NativeInvoker::Invoke<3040, void>(userId, gamerHandle, gamerHandleSize); }
	FORCEINLINE void NETWORK_HANDLE_FROM_MEMBER_ID(const char* memberId, Any* gamerHandle, int gamerHandleSize) { return YimMenu::NativeInvoker::Invoke<3041, void>(memberId, gamerHandle, gamerHandleSize); }
	FORCEINLINE void NETWORK_HANDLE_FROM_PLAYER(Player player, Any* gamerHandle, int gamerHandleSize) { return YimMenu::NativeInvoker::Invoke<3042, void>(player, gamerHandle, gamerHandleSize); }
	FORCEINLINE Hash NETWORK_HASH_FROM_PLAYER_HANDLE(Player player) { return YimMenu::NativeInvoker::Invoke<3043, Hash>(player); }
	FORCEINLINE Hash NETWORK_HASH_FROM_GAMER_HANDLE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3044, Hash>(gamerHandle); }
	FORCEINLINE void NETWORK_HANDLE_FROM_FRIEND(int friendIndex, Any* gamerHandle, int gamerHandleSize) { return YimMenu::NativeInvoker::Invoke<3045, void>(friendIndex, gamerHandle, gamerHandleSize); }
	FORCEINLINE bool NETWORK_GAMERTAG_FROM_HANDLE_START(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3046, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_GAMERTAG_FROM_HANDLE_PENDING() { return YimMenu::NativeInvoker::Invoke<3047, bool>(); }
	FORCEINLINE bool NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED() { return YimMenu::NativeInvoker::Invoke<3048, bool>(); }
	FORCEINLINE const char* NETWORK_GET_GAMERTAG_FROM_HANDLE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3049, const char*>(gamerHandle); }
	FORCEINLINE int NETWORK_DISPLAYNAMES_FROM_HANDLES_START(Any* p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3050, int>(p0, p1); }
	FORCEINLINE int NETWORK_GET_DISPLAYNAMES_FROM_HANDLES(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<3051, int>(p0, p1, p2); }
	FORCEINLINE bool NETWORK_ARE_HANDLES_THE_SAME(Any* gamerHandle1, Any* gamerHandle2) { return YimMenu::NativeInvoker::Invoke<3052, bool>(gamerHandle1, gamerHandle2); }
	FORCEINLINE bool NETWORK_IS_HANDLE_VALID(Any* gamerHandle, int gamerHandleSize) { return YimMenu::NativeInvoker::Invoke<3053, bool>(gamerHandle, gamerHandleSize); }
	FORCEINLINE Player NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3054, Player>(gamerHandle); }
	FORCEINLINE const char* NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3055, const char*>(gamerHandle); }
	FORCEINLINE bool NETWORK_IS_GAMER_IN_MY_SESSION(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3056, bool>(gamerHandle); }
	FORCEINLINE void NETWORK_SHOW_PROFILE_UI(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3057, void>(gamerHandle); }
	FORCEINLINE const char* NETWORK_PLAYER_GET_NAME(Player player) { return YimMenu::NativeInvoker::Invoke<3058, const char*>(player); }
	FORCEINLINE const char* NETWORK_PLAYER_GET_USERID(Player player, int* userID) { return YimMenu::NativeInvoker::Invoke<3059, const char*>(player, userID); }
	FORCEINLINE bool NETWORK_PLAYER_IS_ROCKSTAR_DEV(Player player) { return YimMenu::NativeInvoker::Invoke<3060, bool>(player); }
	FORCEINLINE bool NETWORK_PLAYER_INDEX_IS_CHEATER(Player player) { return YimMenu::NativeInvoker::Invoke<3061, bool>(player); }
	FORCEINLINE int NETWORK_ENTITY_GET_OBJECT_ID(Entity entity) { return YimMenu::NativeInvoker::Invoke<3062, int>(entity); }
	FORCEINLINE Entity NETWORK_GET_ENTITY_FROM_OBJECT_ID(Any p0) { return YimMenu::NativeInvoker::Invoke<3063, Entity>(p0); }
	FORCEINLINE bool NETWORK_IS_INACTIVE_PROFILE(Any* p0) { return YimMenu::NativeInvoker::Invoke<3064, bool>(p0); }
	FORCEINLINE int NETWORK_GET_MAX_FRIENDS() { return YimMenu::NativeInvoker::Invoke<3065, int>(); }
	FORCEINLINE int NETWORK_GET_FRIEND_COUNT() { return YimMenu::NativeInvoker::Invoke<3066, int>(); }
	FORCEINLINE const char* NETWORK_GET_FRIEND_NAME(int friendIndex) { return YimMenu::NativeInvoker::Invoke<3067, const char*>(friendIndex); }
	FORCEINLINE const char* NETWORK_GET_FRIEND_DISPLAY_NAME(int friendIndex) { return YimMenu::NativeInvoker::Invoke<3068, const char*>(friendIndex); }
	FORCEINLINE bool NETWORK_IS_FRIEND_ONLINE(const char* name) { return YimMenu::NativeInvoker::Invoke<3069, bool>(name); }
	FORCEINLINE bool NETWORK_IS_FRIEND_HANDLE_ONLINE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3070, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_IS_FRIEND_IN_SAME_TITLE(const char* friendName) { return YimMenu::NativeInvoker::Invoke<3071, bool>(friendName); }
	FORCEINLINE bool NETWORK_IS_FRIEND_IN_MULTIPLAYER(const char* friendName) { return YimMenu::NativeInvoker::Invoke<3072, bool>(friendName); }
	FORCEINLINE bool NETWORK_IS_FRIEND(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3073, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_IS_PENDING_FRIEND(Any p0) { return YimMenu::NativeInvoker::Invoke<3074, bool>(p0); }
	FORCEINLINE bool NETWORK_IS_ADDING_FRIEND() { return YimMenu::NativeInvoker::Invoke<3075, bool>(); }
	FORCEINLINE bool NETWORK_ADD_FRIEND(Any* gamerHandle, const char* message) { return YimMenu::NativeInvoker::Invoke<3076, bool>(gamerHandle, message); }
	FORCEINLINE bool NETWORK_IS_FRIEND_INDEX_ONLINE(int friendIndex) { return YimMenu::NativeInvoker::Invoke<3077, bool>(friendIndex); }
	FORCEINLINE void NETWORK_SET_PLAYER_IS_PASSIVE(bool toggle) { return YimMenu::NativeInvoker::Invoke<3078, void>(toggle); }
	FORCEINLINE bool NETWORK_GET_PLAYER_OWNS_WAYPOINT(Player player) { return YimMenu::NativeInvoker::Invoke<3079, bool>(player); }
	FORCEINLINE bool NETWORK_CAN_SET_WAYPOINT() { return YimMenu::NativeInvoker::Invoke<3080, bool>(); }
	FORCEINLINE void NETWORK_IGNORE_REMOTE_WAYPOINTS() { return YimMenu::NativeInvoker::Invoke<3081, void>(); }
	FORCEINLINE bool NETWORK_IS_PLAYER_ON_BLOCKLIST(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3082, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_SET_SCRIPT_AUTOMUTED(Any p0) { return YimMenu::NativeInvoker::Invoke<3083, bool>(p0); }
	FORCEINLINE bool NETWORK_HAS_AUTOMUTE_OVERRIDE() { return YimMenu::NativeInvoker::Invoke<3084, bool>(); }
	FORCEINLINE bool NETWORK_HAS_HEADSET() { return YimMenu::NativeInvoker::Invoke<3085, bool>(); }
	FORCEINLINE void NETWORK_SET_LOOK_AT_TALKERS(bool p0) { return YimMenu::NativeInvoker::Invoke<3086, void>(p0); }
	FORCEINLINE bool NETWORK_IS_PUSH_TO_TALK_ACTIVE() { return YimMenu::NativeInvoker::Invoke<3087, bool>(); }
	FORCEINLINE bool NETWORK_GAMER_HAS_HEADSET(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3088, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_IS_GAMER_TALKING(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3089, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_PERMISSIONS_HAS_GAMER_RECORD(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3090, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_COMMUNICATE_WITH_GAMER(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3091, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_TEXT_CHAT_WITH_GAMER(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3092, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_IS_GAMER_MUTED_BY_ME(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3093, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_AM_I_MUTED_BY_GAMER(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3094, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_IS_GAMER_BLOCKED_BY_ME(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3095, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_AM_I_BLOCKED_BY_GAMER(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3096, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_VIEW_GAMER_USER_CONTENT(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3097, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_HAS_VIEW_GAMER_USER_CONTENT_RESULT(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3098, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_PLAY_MULTIPLAYER_WITH_GAMER(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3099, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_GAMER_PLAY_MULTIPLAYER_WITH_ME(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3100, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_SEND_LOCAL_INVITE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3101, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CAN_RECEIVE_LOCAL_INVITE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3102, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_IS_PLAYER_TALKING(Player player) { return YimMenu::NativeInvoker::Invoke<3103, bool>(player); }
	FORCEINLINE bool NETWORK_PLAYER_HAS_HEADSET(Player player) { return YimMenu::NativeInvoker::Invoke<3104, bool>(player); }
	FORCEINLINE bool NETWORK_IS_PLAYER_MUTED_BY_ME(Player player) { return YimMenu::NativeInvoker::Invoke<3105, bool>(player); }
	FORCEINLINE bool NETWORK_AM_I_MUTED_BY_PLAYER(Player player) { return YimMenu::NativeInvoker::Invoke<3106, bool>(player); }
	FORCEINLINE bool NETWORK_IS_PLAYER_BLOCKED_BY_ME(Player player) { return YimMenu::NativeInvoker::Invoke<3107, bool>(player); }
	FORCEINLINE bool NETWORK_AM_I_BLOCKED_BY_PLAYER(Player player) { return YimMenu::NativeInvoker::Invoke<3108, bool>(player); }
	FORCEINLINE float NETWORK_GET_PLAYER_LOUDNESS(Player player) { return YimMenu::NativeInvoker::Invoke<3109, float>(player); }
	FORCEINLINE void NETWORK_SET_TALKER_PROXIMITY(float value) { return YimMenu::NativeInvoker::Invoke<3110, void>(value); }
	FORCEINLINE float NETWORK_GET_TALKER_PROXIMITY() { return YimMenu::NativeInvoker::Invoke<3111, float>(); }
	FORCEINLINE void NETWORK_SET_VOICE_ACTIVE(bool toggle) { return YimMenu::NativeInvoker::Invoke<3112, void>(toggle); }
	FORCEINLINE void NETWORK_REMAIN_IN_GAME_CHAT(bool p0) { return YimMenu::NativeInvoker::Invoke<3113, void>(p0); }
	FORCEINLINE void NETWORK_OVERRIDE_TRANSITION_CHAT(bool p0) { return YimMenu::NativeInvoker::Invoke<3114, void>(p0); }
	FORCEINLINE void NETWORK_SET_TEAM_ONLY_CHAT(bool toggle) { return YimMenu::NativeInvoker::Invoke<3115, void>(toggle); }
	FORCEINLINE void NETWORK_SET_SCRIPT_CONTROLLING_TEAMS(Any p0) { return YimMenu::NativeInvoker::Invoke<3116, void>(p0); }
	FORCEINLINE bool NETWORK_SET_SAME_TEAM_AS_LOCAL_PLAYER(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3117, bool>(p0, p1); }
	FORCEINLINE void NETWORK_OVERRIDE_TEAM_RESTRICTIONS(int team, bool toggle) { return YimMenu::NativeInvoker::Invoke<3118, void>(team, toggle); }
	FORCEINLINE void NETWORK_SET_OVERRIDE_SPECTATOR_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<3119, void>(toggle); }
	FORCEINLINE void NETWORK_SET_OVERRIDE_TUTORIAL_SESSION_CHAT(bool toggle) { return YimMenu::NativeInvoker::Invoke<3120, void>(toggle); }
	FORCEINLINE void NETWORK_SET_PROXIMITY_AFFECTS_TEAM(bool toggle) { return YimMenu::NativeInvoker::Invoke<3121, void>(toggle); }
	FORCEINLINE void NETWORK_SET_NO_SPECTATOR_CHAT(bool toggle) { return YimMenu::NativeInvoker::Invoke<3122, void>(toggle); }
	FORCEINLINE void NETWORK_SET_IGNORE_SPECTATOR_CHAT_LIMITS_SAME_TEAM(bool toggle) { return YimMenu::NativeInvoker::Invoke<3123, void>(toggle); }
	FORCEINLINE void NETWORK_OVERRIDE_CHAT_RESTRICTIONS(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<3124, void>(player, toggle); }
	FORCEINLINE void NETWORK_OVERRIDE_SEND_RESTRICTIONS(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<3125, void>(player, toggle); }
	FORCEINLINE void NETWORK_OVERRIDE_SEND_RESTRICTIONS_ALL(bool toggle) { return YimMenu::NativeInvoker::Invoke<3126, void>(toggle); }
	FORCEINLINE void NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<3127, void>(player, toggle); }
	FORCEINLINE void NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS_ALL(bool toggle) { return YimMenu::NativeInvoker::Invoke<3128, void>(toggle); }
	FORCEINLINE void NETWORK_SET_VOICE_CHANNEL(int channel) { return YimMenu::NativeInvoker::Invoke<3129, void>(channel); }
	FORCEINLINE void NETWORK_CLEAR_VOICE_CHANNEL() { return YimMenu::NativeInvoker::Invoke<3130, void>(); }
	FORCEINLINE void NETWORK_APPLY_VOICE_PROXIMITY_OVERRIDE(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<3131, void>(x, y, z); }
	FORCEINLINE void NETWORK_CLEAR_VOICE_PROXIMITY_OVERRIDE() { return YimMenu::NativeInvoker::Invoke<3132, void>(); }
	FORCEINLINE void NETWORK_ENABLE_VOICE_BANDWIDTH_RESTRICTION(Player player) { return YimMenu::NativeInvoker::Invoke<3133, void>(player); }
	FORCEINLINE void NETWORK_DISABLE_VOICE_BANDWIDTH_RESTRICTION(Player player) { return YimMenu::NativeInvoker::Invoke<3134, void>(player); }
	FORCEINLINE void NETWORK_GET_MUTE_COUNT_FOR_PLAYER(Player p0, float* p1, float* p2) { return YimMenu::NativeInvoker::Invoke<3135, void>(p0, p1, p2); }
	FORCEINLINE void NETWORK_SET_SPECTATOR_TO_NON_SPECTATOR_TEXT_CHAT(bool toggle) { return YimMenu::NativeInvoker::Invoke<3136, void>(toggle); }
	FORCEINLINE bool NETWORK_TEXT_CHAT_IS_TYPING() { return YimMenu::NativeInvoker::Invoke<3137, bool>(); }
	FORCEINLINE void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME() { return YimMenu::NativeInvoker::Invoke<3138, void>(); }
	FORCEINLINE bool SHUTDOWN_AND_LOAD_MOST_RECENT_SAVE() { return YimMenu::NativeInvoker::Invoke<3139, bool>(); }
	FORCEINLINE void NETWORK_SET_FRIENDLY_FIRE_OPTION(bool toggle) { return YimMenu::NativeInvoker::Invoke<3140, void>(toggle); }
	FORCEINLINE void NETWORK_SET_RICH_PRESENCE(int p0, int p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<3141, void>(p0, p1, p2, p3); }
	FORCEINLINE void NETWORK_SET_RICH_PRESENCE_STRING(int p0, const char* textLabel) { return YimMenu::NativeInvoker::Invoke<3142, void>(p0, textLabel); }
	FORCEINLINE int NETWORK_GET_TIMEOUT_TIME() { return YimMenu::NativeInvoker::Invoke<3143, int>(); }
	FORCEINLINE void NETWORK_LEAVE_PED_BEHIND_BEFORE_WARP(Player player, float x, float y, float z, bool p4, bool p5) { return YimMenu::NativeInvoker::Invoke<3144, void>(player, x, y, z, p4, p5); }
	FORCEINLINE void NETWORK_LEAVE_PED_BEHIND_BEFORE_CUTSCENE(Player player, bool p1) { return YimMenu::NativeInvoker::Invoke<3145, void>(player, p1); }
	FORCEINLINE void REMOVE_ALL_STICKY_BOMBS_FROM_ENTITY(Entity entity, Ped ped) { return YimMenu::NativeInvoker::Invoke<3146, void>(entity, ped); }
	FORCEINLINE void NETWORK_KEEP_ENTITY_COLLISION_DISABLED_AFTER_ANIM_SCENE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3147, void>(p0, p1); }
	FORCEINLINE bool NETWORK_IS_ANY_PLAYER_NEAR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<3148, bool>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE bool NETWORK_CLAN_SERVICE_IS_VALID() { return YimMenu::NativeInvoker::Invoke<3149, bool>(); }
	FORCEINLINE bool NETWORK_CLAN_PLAYER_IS_ACTIVE(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3150, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CLAN_PLAYER_GET_DESC(Any* clanDesc, int bufferSize, Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3151, bool>(clanDesc, bufferSize, gamerHandle); }
	FORCEINLINE bool NETWORK_CLAN_IS_ROCKSTAR_CLAN(Any* clanDesc, int bufferSize) { return YimMenu::NativeInvoker::Invoke<3152, bool>(clanDesc, bufferSize); }
	FORCEINLINE void NETWORK_CLAN_GET_UI_FORMATTED_TAG(Any* clanDesc, int bufferSize, char* formattedTag) { return YimMenu::NativeInvoker::Invoke<3153, void>(clanDesc, bufferSize, formattedTag); }
	FORCEINLINE int NETWORK_CLAN_GET_LOCAL_MEMBERSHIPS_COUNT() { return YimMenu::NativeInvoker::Invoke<3154, int>(); }
	FORCEINLINE bool NETWORK_CLAN_GET_MEMBERSHIP_DESC(Any* memberDesc, int p1) { return YimMenu::NativeInvoker::Invoke<3155, bool>(memberDesc, p1); }
	FORCEINLINE bool NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<3156, bool>(gamerHandle); }
	FORCEINLINE bool NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(Any* p0) { return YimMenu::NativeInvoker::Invoke<3157, bool>(p0); }
	FORCEINLINE bool NETWORK_CLAN_ANY_DOWNLOAD_MEMBERSHIP_PENDING() { return YimMenu::NativeInvoker::Invoke<3158, bool>(); }
	FORCEINLINE bool NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE(int* p0) { return YimMenu::NativeInvoker::Invoke<3159, bool>(p0); }
	FORCEINLINE int NETWORK_CLAN_GET_MEMBERSHIP_COUNT(int* p0) { return YimMenu::NativeInvoker::Invoke<3160, int>(p0); }
	FORCEINLINE bool NETWORK_CLAN_GET_MEMBERSHIP_VALID(int* p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3161, bool>(p0, p1); }
	FORCEINLINE bool NETWORK_CLAN_GET_MEMBERSHIP(int* p0, Any* clanMembership, int p2) { return YimMenu::NativeInvoker::Invoke<3162, bool>(p0, clanMembership, p2); }
	FORCEINLINE bool NETWORK_CLAN_JOIN(int clanDesc) { return YimMenu::NativeInvoker::Invoke<3163, bool>(clanDesc); }
	FORCEINLINE bool NETWORK_CLAN_CREWINFO_GET_STRING_VALUE(const char* animDict, const char* animName) { return YimMenu::NativeInvoker::Invoke<3164, bool>(animDict, animName); }
	FORCEINLINE bool NETWORK_CLAN_CREWINFO_GET_CREWRANKTITLE(int p0, const char* p1) { return YimMenu::NativeInvoker::Invoke<3165, bool>(p0, p1); }
	FORCEINLINE bool NETWORK_CLAN_HAS_CREWINFO_METADATA_BEEN_RECEIVED() { return YimMenu::NativeInvoker::Invoke<3166, bool>(); }
	FORCEINLINE bool NETWORK_CLAN_GET_EMBLEM_TXD_NAME(Any* netHandle, char* txdName) { return YimMenu::NativeInvoker::Invoke<3167, bool>(netHandle, txdName); }
	FORCEINLINE bool NETWORK_CLAN_REQUEST_EMBLEM(Any p0) { return YimMenu::NativeInvoker::Invoke<3168, bool>(p0); }
	FORCEINLINE bool NETWORK_CLAN_IS_EMBLEM_READY(Any p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<3169, bool>(p0, p1); }
	FORCEINLINE void NETWORK_CLAN_RELEASE_EMBLEM(Any p0) { return YimMenu::NativeInvoker::Invoke<3170, void>(p0); }
	FORCEINLINE bool NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR() { return YimMenu::NativeInvoker::Invoke<3171, bool>(); }
	FORCEINLINE void NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL() { return YimMenu::NativeInvoker::Invoke<3172, void>(); }
	FORCEINLINE bool NETWORK_GET_PRIMARY_CLAN_DATA_START(Any* p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3173, bool>(p0, p1); }
	FORCEINLINE bool NETWORK_GET_PRIMARY_CLAN_DATA_PENDING() { return YimMenu::NativeInvoker::Invoke<3174, bool>(); }
	FORCEINLINE bool NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS() { return YimMenu::NativeInvoker::Invoke<3175, bool>(); }
	FORCEINLINE bool NETWORK_GET_PRIMARY_CLAN_DATA_NEW(Any* p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<3176, bool>(p0, p1); }
	FORCEINLINE void SET_NETWORK_ID_CAN_MIGRATE(int netId, bool toggle) { return YimMenu::NativeInvoker::Invoke<3177, void>(netId, toggle); }
	FORCEINLINE void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int netId, bool toggle) { return YimMenu::NativeInvoker::Invoke<3178, void>(netId, toggle); }
	FORCEINLINE void SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER(int netId, Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<3179, void>(netId, player, toggle); }
	FORCEINLINE void SET_NETWORK_ID_CAN_BE_REASSIGNED(int netId, bool toggle) { return YimMenu::NativeInvoker::Invoke<3180, void>(netId, toggle); }
	FORCEINLINE void NETWORK_SET_ENTITY_CAN_BLEND(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3181, void>(entity, toggle); }
	FORCEINLINE void NETWORK_SET_OBJECT_CAN_BLEND_WHEN_FIXED(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3182, void>(object, toggle); }
	FORCEINLINE void NETWORK_SET_ENTITY_ONLY_EXISTS_FOR_PARTICIPANTS(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3183, void>(entity, toggle); }
	FORCEINLINE void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(int netId, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<3184, void>(netId, p1, p2); }
	FORCEINLINE void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_HACK(int netId, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<3185, void>(netId, p1, p2); }
	FORCEINLINE void SET_NETWORK_ID_VISIBLE_IN_CUTSCENE_REMAIN_HACK(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3186, void>(p0, p1); }
	FORCEINLINE void SET_NETWORK_CUTSCENE_ENTITIES(bool toggle) { return YimMenu::NativeInvoker::Invoke<3187, void>(toggle); }
	FORCEINLINE bool ARE_CUTSCENE_ENTITIES_NETWORKED() { return YimMenu::NativeInvoker::Invoke<3188, bool>(); }
	FORCEINLINE void SET_NETWORK_ID_PASS_CONTROL_IN_TUTORIAL(int netId, bool state) { return YimMenu::NativeInvoker::Invoke<3189, void>(netId, state); }
	FORCEINLINE bool IS_NETWORK_ID_OWNED_BY_PARTICIPANT(int netId) { return YimMenu::NativeInvoker::Invoke<3190, bool>(netId); }
	FORCEINLINE void SET_REMOTE_PLAYER_VISIBLE_IN_CUTSCENE(Player player, bool locallyVisible) { return YimMenu::NativeInvoker::Invoke<3191, void>(player, locallyVisible); }
	FORCEINLINE void SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<3192, void>(p0, p1); }
	FORCEINLINE void SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(bool bIncludePlayersVehicle) { return YimMenu::NativeInvoker::Invoke<3193, void>(bIncludePlayersVehicle); }
	FORCEINLINE void SET_LOCAL_PLAYER_VISIBLE_LOCALLY(bool bIncludePlayersVehicle) { return YimMenu::NativeInvoker::Invoke<3194, void>(bIncludePlayersVehicle); }
	FORCEINLINE void SET_PLAYER_INVISIBLE_LOCALLY(Player player, bool bIncludePlayersVehicle) { return YimMenu::NativeInvoker::Invoke<3195, void>(player, bIncludePlayersVehicle); }
	FORCEINLINE void SET_PLAYER_VISIBLE_LOCALLY(Player player, bool bIncludePlayersVehicle) { return YimMenu::NativeInvoker::Invoke<3196, void>(player, bIncludePlayersVehicle); }
	FORCEINLINE void FADE_OUT_LOCAL_PLAYER(bool p0) { return YimMenu::NativeInvoker::Invoke<3197, void>(p0); }
	FORCEINLINE void NETWORK_FADE_OUT_ENTITY(Entity entity, bool normal, bool slow) { return YimMenu::NativeInvoker::Invoke<3198, void>(entity, normal, slow); }
	FORCEINLINE void NETWORK_FADE_IN_ENTITY(Entity entity, bool state, Any p2) { return YimMenu::NativeInvoker::Invoke<3199, void>(entity, state, p2); }
	FORCEINLINE bool NETWORK_IS_PLAYER_FADING(Player player) { return YimMenu::NativeInvoker::Invoke<3200, bool>(player); }
	FORCEINLINE bool NETWORK_IS_ENTITY_FADING(Entity entity) { return YimMenu::NativeInvoker::Invoke<3201, bool>(entity); }
	FORCEINLINE bool IS_PLAYER_IN_CUTSCENE(Player player) { return YimMenu::NativeInvoker::Invoke<3202, bool>(player); }
	FORCEINLINE void SET_ENTITY_VISIBLE_IN_CUTSCENE(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<3203, void>(p0, p1, p2); }
	FORCEINLINE void SET_ENTITY_LOCALLY_INVISIBLE(Entity entity) { return YimMenu::NativeInvoker::Invoke<3204, void>(entity); }
	FORCEINLINE void SET_ENTITY_LOCALLY_VISIBLE(Entity entity) { return YimMenu::NativeInvoker::Invoke<3205, void>(entity); }
	FORCEINLINE bool IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(int netID) { return YimMenu::NativeInvoker::Invoke<3206, bool>(netID); }
	FORCEINLINE void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(int netID, bool toggle) { return YimMenu::NativeInvoker::Invoke<3207, void>(netID, toggle); }
	FORCEINLINE bool IS_DAMAGE_TRACKER_ACTIVE_ON_PLAYER(Player player) { return YimMenu::NativeInvoker::Invoke<3208, bool>(player); }
	FORCEINLINE void ACTIVATE_DAMAGE_TRACKER_ON_PLAYER(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<3209, void>(player, toggle); }
	FORCEINLINE bool IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(float p0, float p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<3210, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool IS_SPHERE_VISIBLE_TO_PLAYER(Any p0, float p1, float p2, float p3, float p4) { return YimMenu::NativeInvoker::Invoke<3211, bool>(p0, p1, p2, p3, p4); }
	FORCEINLINE void RESERVE_NETWORK_MISSION_OBJECTS(int amount) { return YimMenu::NativeInvoker::Invoke<3212, void>(amount); }
	FORCEINLINE void RESERVE_NETWORK_MISSION_PEDS(int amount) { return YimMenu::NativeInvoker::Invoke<3213, void>(amount); }
	FORCEINLINE void RESERVE_NETWORK_MISSION_VEHICLES(int amount) { return YimMenu::NativeInvoker::Invoke<3214, void>(amount); }
	FORCEINLINE void RESERVE_LOCAL_NETWORK_MISSION_OBJECTS(int amount) { return YimMenu::NativeInvoker::Invoke<3215, void>(amount); }
	FORCEINLINE void RESERVE_LOCAL_NETWORK_MISSION_PEDS(int amount) { return YimMenu::NativeInvoker::Invoke<3216, void>(amount); }
	FORCEINLINE void RESERVE_LOCAL_NETWORK_MISSION_VEHICLES(int amount) { return YimMenu::NativeInvoker::Invoke<3217, void>(amount); }
	FORCEINLINE bool CAN_REGISTER_MISSION_OBJECTS(int amount) { return YimMenu::NativeInvoker::Invoke<3218, bool>(amount); }
	FORCEINLINE bool CAN_REGISTER_MISSION_PEDS(int amount) { return YimMenu::NativeInvoker::Invoke<3219, bool>(amount); }
	FORCEINLINE bool CAN_REGISTER_MISSION_VEHICLES(int amount) { return YimMenu::NativeInvoker::Invoke<3220, bool>(amount); }
	FORCEINLINE bool CAN_REGISTER_MISSION_PICKUPS(int amount) { return YimMenu::NativeInvoker::Invoke<3221, bool>(amount); }
	FORCEINLINE bool CAN_REGISTER_MISSION_DOORS(Any p0) { return YimMenu::NativeInvoker::Invoke<3222, bool>(p0); }
	FORCEINLINE bool CAN_REGISTER_MISSION_ENTITIES(int ped_amt, int vehicle_amt, int object_amt, int pickup_amt) { return YimMenu::NativeInvoker::Invoke<3223, bool>(ped_amt, vehicle_amt, object_amt, pickup_amt); }
	FORCEINLINE int GET_NUM_RESERVED_MISSION_OBJECTS(bool p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3224, int>(p0, p1); }
	FORCEINLINE int GET_NUM_RESERVED_MISSION_PEDS(bool p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3225, int>(p0, p1); }
	FORCEINLINE int GET_NUM_RESERVED_MISSION_VEHICLES(bool p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3226, int>(p0, p1); }
	FORCEINLINE int GET_NUM_CREATED_MISSION_OBJECTS(bool p0) { return YimMenu::NativeInvoker::Invoke<3227, int>(p0); }
	FORCEINLINE int GET_NUM_CREATED_MISSION_PEDS(bool p0) { return YimMenu::NativeInvoker::Invoke<3228, int>(p0); }
	FORCEINLINE int GET_NUM_CREATED_MISSION_VEHICLES(bool p0) { return YimMenu::NativeInvoker::Invoke<3229, int>(p0); }
	FORCEINLINE void GET_RESERVED_MISSION_ENTITIES_IN_AREA(float x, float y, float z, Any p3, Any* out1, Any* out2, Any* out3) { return YimMenu::NativeInvoker::Invoke<3230, void>(x, y, z, p3, out1, out2, out3); }
	FORCEINLINE int GET_MAX_NUM_NETWORK_OBJECTS() { return YimMenu::NativeInvoker::Invoke<3231, int>(); }
	FORCEINLINE int GET_MAX_NUM_NETWORK_PEDS() { return YimMenu::NativeInvoker::Invoke<3232, int>(); }
	FORCEINLINE int GET_MAX_NUM_NETWORK_VEHICLES() { return YimMenu::NativeInvoker::Invoke<3233, int>(); }
	FORCEINLINE int GET_MAX_NUM_NETWORK_PICKUPS() { return YimMenu::NativeInvoker::Invoke<3234, int>(); }
	FORCEINLINE void NETWORK_SET_OBJECT_SCOPE_DISTANCE(Object object, float range) { return YimMenu::NativeInvoker::Invoke<3235, void>(object, range); }
	FORCEINLINE void NETWORK_ALLOW_CLONING_WHILE_IN_TUTORIAL(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3236, void>(p0, p1); }
	FORCEINLINE void NETWORK_SET_TASK_CUTSCENE_INSCOPE_MULTIPLER(Any p0) { return YimMenu::NativeInvoker::Invoke<3237, void>(p0); }
	FORCEINLINE int GET_NETWORK_TIME() { return YimMenu::NativeInvoker::Invoke<3238, int>(); }
	FORCEINLINE int GET_NETWORK_TIME_ACCURATE() { return YimMenu::NativeInvoker::Invoke<3239, int>(); }
	FORCEINLINE bool HAS_NETWORK_TIME_STARTED() { return YimMenu::NativeInvoker::Invoke<3240, bool>(); }
	FORCEINLINE int GET_TIME_OFFSET(int timeA, int timeB) { return YimMenu::NativeInvoker::Invoke<3241, int>(timeA, timeB); }
	FORCEINLINE bool IS_TIME_LESS_THAN(int timeA, int timeB) { return YimMenu::NativeInvoker::Invoke<3242, bool>(timeA, timeB); }
	FORCEINLINE bool IS_TIME_MORE_THAN(int timeA, int timeB) { return YimMenu::NativeInvoker::Invoke<3243, bool>(timeA, timeB); }
	FORCEINLINE bool IS_TIME_EQUAL_TO(int timeA, int timeB) { return YimMenu::NativeInvoker::Invoke<3244, bool>(timeA, timeB); }
	FORCEINLINE int GET_TIME_DIFFERENCE(int timeA, int timeB) { return YimMenu::NativeInvoker::Invoke<3245, int>(timeA, timeB); }
	FORCEINLINE const char* GET_TIME_AS_STRING(int time) { return YimMenu::NativeInvoker::Invoke<3246, const char*>(time); }
	FORCEINLINE const char* GET_CLOUD_TIME_AS_STRING() { return YimMenu::NativeInvoker::Invoke<3247, const char*>(); }
	FORCEINLINE int GET_CLOUD_TIME_AS_INT() { return YimMenu::NativeInvoker::Invoke<3248, int>(); }
	FORCEINLINE void CONVERT_POSIX_TIME(int posixTime, Any* timeStructure) { return YimMenu::NativeInvoker::Invoke<3249, void>(posixTime, timeStructure); }
	FORCEINLINE void NETWORK_SET_IN_SPECTATOR_MODE(bool toggle, Ped playerPed) { return YimMenu::NativeInvoker::Invoke<3250, void>(toggle, playerPed); }
	FORCEINLINE void NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED(bool toggle, Ped playerPed, bool p2) { return YimMenu::NativeInvoker::Invoke<3251, void>(toggle, playerPed, p2); }
	FORCEINLINE void NETWORK_SET_IN_FREE_CAM_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<3252, void>(toggle); }
	FORCEINLINE void NETWORK_SET_ANTAGONISTIC_TO_PLAYER(bool toggle, Player player) { return YimMenu::NativeInvoker::Invoke<3253, void>(toggle, player); }
	FORCEINLINE bool NETWORK_IS_IN_SPECTATOR_MODE() { return YimMenu::NativeInvoker::Invoke<3254, bool>(); }
	FORCEINLINE void NETWORK_SET_IN_MP_CUTSCENE(bool p0, bool p1) { return YimMenu::NativeInvoker::Invoke<3255, void>(p0, p1); }
	FORCEINLINE bool NETWORK_IS_IN_MP_CUTSCENE() { return YimMenu::NativeInvoker::Invoke<3256, bool>(); }
	FORCEINLINE bool NETWORK_IS_PLAYER_IN_MP_CUTSCENE(Player player) { return YimMenu::NativeInvoker::Invoke<3257, bool>(player); }
	FORCEINLINE void NETWORK_HIDE_PROJECTILE_IN_CUTSCENE() { return YimMenu::NativeInvoker::Invoke<3258, void>(); }
	FORCEINLINE void SET_NETWORK_VEHICLE_RESPOT_TIMER(int netId, int time, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<3259, void>(netId, time, p2, p3); }
	FORCEINLINE bool IS_NETWORK_VEHICLE_RUNNING_RESPOT_TIMER(int networkID) { return YimMenu::NativeInvoker::Invoke<3260, bool>(networkID); }
	FORCEINLINE void SET_NETWORK_VEHICLE_AS_GHOST(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<3261, void>(vehicle, toggle); }
	FORCEINLINE void SET_NETWORK_VEHICLE_MAX_POSITION_DELTA_MULTIPLIER(Vehicle vehicle, float multiplier) { return YimMenu::NativeInvoker::Invoke<3262, void>(vehicle, multiplier); }
	FORCEINLINE void SET_NETWORK_ENABLE_HIGH_SPEED_EDGE_FALL_DETECTION(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<3263, void>(vehicle, toggle); }
	FORCEINLINE void SET_LOCAL_PLAYER_AS_GHOST(bool toggle, bool p1) { return YimMenu::NativeInvoker::Invoke<3264, void>(toggle, p1); }
	FORCEINLINE bool IS_ENTITY_A_GHOST(Entity entity) { return YimMenu::NativeInvoker::Invoke<3265, bool>(entity); }
	FORCEINLINE void SET_NON_PARTICIPANTS_OF_THIS_SCRIPT_AS_GHOSTS(bool p0) { return YimMenu::NativeInvoker::Invoke<3266, void>(p0); }
	FORCEINLINE void SET_REMOTE_PLAYER_AS_GHOST(Player player, bool p1) { return YimMenu::NativeInvoker::Invoke<3267, void>(player, p1); }
	FORCEINLINE void SET_GHOST_ALPHA(int alpha) { return YimMenu::NativeInvoker::Invoke<3268, void>(alpha); }
	FORCEINLINE void RESET_GHOST_ALPHA() { return YimMenu::NativeInvoker::Invoke<3269, void>(); }
	FORCEINLINE void SET_ENTITY_GHOSTED_FOR_GHOST_PLAYERS(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3270, void>(entity, toggle); }
	FORCEINLINE void SET_INVERT_GHOSTING(bool p0) { return YimMenu::NativeInvoker::Invoke<3271, void>(p0); }
	FORCEINLINE bool IS_ENTITY_IN_GHOST_COLLISION(Entity entity) { return YimMenu::NativeInvoker::Invoke<3272, bool>(entity); }
	FORCEINLINE void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(bool toggle) { return YimMenu::NativeInvoker::Invoke<3273, void>(toggle); }
	FORCEINLINE int NETWORK_CREATE_SYNCHRONISED_SCENE(float x, float y, float z, float xRot, float yRot, float zRot, int rotationOrder, bool useOcclusionPortal, bool looped, float p9, float animTime, float p11) { return YimMenu::NativeInvoker::Invoke<3274, int>(x, y, z, xRot, yRot, zRot, rotationOrder, useOcclusionPortal, looped, p9, animTime, p11); }
	FORCEINLINE void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(Ped ped, int netScene, const char* animDict, const char* animnName, float speed, float speedMultiplier, int duration, int flag, float playbackRate, Any p9) { return YimMenu::NativeInvoker::Invoke<3275, void>(ped, netScene, animDict, animnName, speed, speedMultiplier, duration, flag, playbackRate, p9); }
	FORCEINLINE void NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE_WITH_IK(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return YimMenu::NativeInvoker::Invoke<3276, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	FORCEINLINE void NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(Entity entity, int netScene, const char* animDict, const char* animName, float speed, float speedMulitiplier, int flag) { return YimMenu::NativeInvoker::Invoke<3277, void>(entity, netScene, animDict, animName, speed, speedMulitiplier, flag); }
	FORCEINLINE void NETWORK_ADD_MAP_ENTITY_TO_SYNCHRONISED_SCENE(int netScene, Hash modelHash, float x, float y, float z, float p5, const char* p6, float p7, float p8, int flags) { return YimMenu::NativeInvoker::Invoke<3278, void>(netScene, modelHash, x, y, z, p5, p6, p7, p8, flags); }
	FORCEINLINE void NETWORK_ADD_SYNCHRONISED_SCENE_CAMERA(int netScene, const char* animDict, const char* animName) { return YimMenu::NativeInvoker::Invoke<3279, void>(netScene, animDict, animName); }
	FORCEINLINE void NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(int netScene, Entity entity, int bone) { return YimMenu::NativeInvoker::Invoke<3280, void>(netScene, entity, bone); }
	FORCEINLINE void NETWORK_START_SYNCHRONISED_SCENE(int netScene) { return YimMenu::NativeInvoker::Invoke<3281, void>(netScene); }
	FORCEINLINE void NETWORK_STOP_SYNCHRONISED_SCENE(int netScene) { return YimMenu::NativeInvoker::Invoke<3282, void>(netScene); }
	FORCEINLINE int NETWORK_GET_LOCAL_SCENE_FROM_NETWORK_ID(int netId) { return YimMenu::NativeInvoker::Invoke<3283, int>(netId); }
	FORCEINLINE void NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA(int netScene) { return YimMenu::NativeInvoker::Invoke<3284, void>(netScene); }
	FORCEINLINE void NETWORK_ALLOW_REMOTE_SYNCED_SCENE_LOCAL_PLAYER_REQUESTS(Any p0) { return YimMenu::NativeInvoker::Invoke<3285, void>(p0); }
	FORCEINLINE bool NETWORK_FIND_LARGEST_BUNCH_OF_PLAYERS(int p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3286, bool>(p0, p1); }
	FORCEINLINE bool NETWORK_START_RESPAWN_SEARCH_FOR_PLAYER(Player player, float x, float y, float z, float radius, float p5, float p6, float p7, int flags) { return YimMenu::NativeInvoker::Invoke<3287, bool>(player, x, y, z, radius, p5, p6, p7, flags); }
	FORCEINLINE bool NETWORK_START_RESPAWN_SEARCH_IN_ANGLED_AREA_FOR_PLAYER(Player player, float x1, float y1, float z1, float x2, float y2, float z2, float width, float p8, float p9, float p10, int flags) { return YimMenu::NativeInvoker::Invoke<3288, bool>(player, x1, y1, z1, x2, y2, z2, width, p8, p9, p10, flags); }
	FORCEINLINE int NETWORK_QUERY_RESPAWN_RESULTS(Any* p0) { return YimMenu::NativeInvoker::Invoke<3289, int>(p0); }
	FORCEINLINE void NETWORK_CANCEL_RESPAWN_SEARCH() { return YimMenu::NativeInvoker::Invoke<3290, void>(); }
	FORCEINLINE void NETWORK_GET_RESPAWN_RESULT(int randomInt, Vector3* coordinates, float* heading) { return YimMenu::NativeInvoker::Invoke<3291, void>(randomInt, coordinates, heading); }
	FORCEINLINE int NETWORK_GET_RESPAWN_RESULT_FLAGS(int p0) { return YimMenu::NativeInvoker::Invoke<3292, int>(p0); }
	FORCEINLINE void NETWORK_START_SOLO_TUTORIAL_SESSION() { return YimMenu::NativeInvoker::Invoke<3293, void>(); }
	FORCEINLINE void NETWORK_ALLOW_GANG_TO_JOIN_TUTORIAL_SESSION(int teamId, int instanceId) { return YimMenu::NativeInvoker::Invoke<3294, void>(teamId, instanceId); }
	FORCEINLINE void NETWORK_END_TUTORIAL_SESSION() { return YimMenu::NativeInvoker::Invoke<3295, void>(); }
	FORCEINLINE bool NETWORK_IS_IN_TUTORIAL_SESSION() { return YimMenu::NativeInvoker::Invoke<3296, bool>(); }
	FORCEINLINE bool NETWORK_WAITING_POP_CLEAR_TUTORIAL_SESSION() { return YimMenu::NativeInvoker::Invoke<3297, bool>(); }
	FORCEINLINE bool NETWORK_IS_TUTORIAL_SESSION_CHANGE_PENDING() { return YimMenu::NativeInvoker::Invoke<3298, bool>(); }
	FORCEINLINE int NETWORK_GET_PLAYER_TUTORIAL_SESSION_INSTANCE(Player player) { return YimMenu::NativeInvoker::Invoke<3299, int>(player); }
	FORCEINLINE bool NETWORK_ARE_PLAYERS_IN_SAME_TUTORIAL_SESSION(Player player, int index) { return YimMenu::NativeInvoker::Invoke<3300, bool>(player, index); }
	FORCEINLINE void NETWORK_BLOCK_PROXY_MIGRATION_BETWEEN_TUTORIAL_SESSIONS(Any p0) { return YimMenu::NativeInvoker::Invoke<3301, void>(p0); }
	FORCEINLINE void NETWORK_CONCEAL_PLAYER(Player player, bool toggle, bool p2) { return YimMenu::NativeInvoker::Invoke<3302, void>(player, toggle, p2); }
	FORCEINLINE bool NETWORK_IS_PLAYER_CONCEALED(Player player) { return YimMenu::NativeInvoker::Invoke<3303, bool>(player); }
	FORCEINLINE void NETWORK_CONCEAL_ENTITY(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3304, void>(entity, toggle); }
	FORCEINLINE bool NETWORK_IS_ENTITY_CONCEALED(Entity entity) { return YimMenu::NativeInvoker::Invoke<3305, bool>(entity); }
	FORCEINLINE void NETWORK_OVERRIDE_CLOCK_TIME(int hours, int minutes, int seconds) { return YimMenu::NativeInvoker::Invoke<3306, void>(hours, minutes, seconds); }
	FORCEINLINE void NETWORK_OVERRIDE_CLOCK_RATE(int ms) { return YimMenu::NativeInvoker::Invoke<3307, void>(ms); }
	FORCEINLINE void NETWORK_CLEAR_CLOCK_TIME_OVERRIDE() { return YimMenu::NativeInvoker::Invoke<3308, void>(); }
	FORCEINLINE bool NETWORK_IS_CLOCK_TIME_OVERRIDDEN() { return YimMenu::NativeInvoker::Invoke<3309, bool>(); }
	FORCEINLINE int NETWORK_ADD_ENTITY_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<3310, int>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE int NETWORK_ADD_ENTITY_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width) { return YimMenu::NativeInvoker::Invoke<3311, int>(x1, y1, z1, x2, y2, z2, width); }
	FORCEINLINE int NETWORK_ADD_CLIENT_ENTITY_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<3312, int>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE int NETWORK_ADD_CLIENT_ENTITY_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float radius) { return YimMenu::NativeInvoker::Invoke<3313, int>(x1, y1, z1, x2, y2, z2, radius); }
	FORCEINLINE bool NETWORK_REMOVE_ENTITY_AREA(int areaHandle) { return YimMenu::NativeInvoker::Invoke<3314, bool>(areaHandle); }
	FORCEINLINE bool NETWORK_ENTITY_AREA_DOES_EXIST(int areaHandle) { return YimMenu::NativeInvoker::Invoke<3315, bool>(areaHandle); }
	FORCEINLINE bool NETWORK_ENTITY_AREA_HAVE_ALL_REPLIED(int areaHandle) { return YimMenu::NativeInvoker::Invoke<3316, bool>(areaHandle); }
	FORCEINLINE bool NETWORK_ENTITY_AREA_IS_OCCUPIED(int areaHandle) { return YimMenu::NativeInvoker::Invoke<3317, bool>(areaHandle); }
	FORCEINLINE void NETWORK_USE_HIGH_PRECISION_BLENDING(int netID, bool toggle) { return YimMenu::NativeInvoker::Invoke<3318, void>(netID, toggle); }
	FORCEINLINE void NETWORK_SET_CUSTOM_ARENA_BALL_PARAMS(int netId) { return YimMenu::NativeInvoker::Invoke<3319, void>(netId); }
	FORCEINLINE void NETWORK_ENTITY_USE_HIGH_PRECISION_ROTATION(int netId, bool toggle) { return YimMenu::NativeInvoker::Invoke<3320, void>(netId, toggle); }
	FORCEINLINE bool NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS() { return YimMenu::NativeInvoker::Invoke<3321, bool>(); }
	FORCEINLINE bool NETWORK_IS_CLOUD_BACKGROUND_SCRIPT_REQUEST_PENDING() { return YimMenu::NativeInvoker::Invoke<3322, bool>(); }
	FORCEINLINE void NETWORK_REQUEST_CLOUD_TUNABLES() { return YimMenu::NativeInvoker::Invoke<3323, void>(); }
	FORCEINLINE bool NETWORK_IS_TUNABLE_CLOUD_REQUEST_PENDING() { return YimMenu::NativeInvoker::Invoke<3324, bool>(); }
	FORCEINLINE int NETWORK_GET_TUNABLE_CLOUD_CRC() { return YimMenu::NativeInvoker::Invoke<3325, int>(); }
	FORCEINLINE bool NETWORK_DOES_TUNABLE_EXIST(const char* tunableContext, const char* tunableName) { return YimMenu::NativeInvoker::Invoke<3326, bool>(tunableContext, tunableName); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_INT(const char* tunableContext, const char* tunableName, int* value) { return YimMenu::NativeInvoker::Invoke<3327, bool>(tunableContext, tunableName, value); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_FLOAT(const char* tunableContext, const char* tunableName, float* value) { return YimMenu::NativeInvoker::Invoke<3328, bool>(tunableContext, tunableName, value); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_BOOL(const char* tunableContext, const char* tunableName) { return YimMenu::NativeInvoker::Invoke<3329, bool>(tunableContext, tunableName); }
	FORCEINLINE bool NETWORK_DOES_TUNABLE_EXIST_HASH(Hash tunableContext, Hash tunableName) { return YimMenu::NativeInvoker::Invoke<3330, bool>(tunableContext, tunableName); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_MODIFICATION_DETECTION_CLEAR() { return YimMenu::NativeInvoker::Invoke<3331, bool>(); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_INT_HASH(Hash tunableContext, Hash tunableName, int* value) { return YimMenu::NativeInvoker::Invoke<3332, bool>(tunableContext, tunableName, value); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_INT_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, int* value) { return YimMenu::NativeInvoker::Invoke<3333, bool>(contextHash, nameHash, value); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_FLOAT_HASH(Hash tunableContext, Hash tunableName, float* value) { return YimMenu::NativeInvoker::Invoke<3334, bool>(tunableContext, tunableName, value); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_FLOAT_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, float* value) { return YimMenu::NativeInvoker::Invoke<3335, bool>(contextHash, nameHash, value); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_BOOL_HASH(Hash tunableContext, Hash tunableName) { return YimMenu::NativeInvoker::Invoke<3336, bool>(tunableContext, tunableName); }
	FORCEINLINE bool NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH(Hash contextHash, Hash nameHash, bool* value) { return YimMenu::NativeInvoker::Invoke<3337, bool>(contextHash, nameHash, value); }
	FORCEINLINE bool NETWORK_TRY_ACCESS_TUNABLE_BOOL_HASH(Hash tunableContext, Hash tunableName, bool defaultValue) { return YimMenu::NativeInvoker::Invoke<3338, bool>(tunableContext, tunableName, defaultValue); }
	FORCEINLINE int NETWORK_GET_CONTENT_MODIFIER_LIST_ID(Hash contentHash) { return YimMenu::NativeInvoker::Invoke<3339, int>(contentHash); }
	FORCEINLINE int NETWORK_GET_BONE_ID_OF_FATAL_HIT() { return YimMenu::NativeInvoker::Invoke<3340, int>(); }
	FORCEINLINE void NETWORK_RESET_BODY_TRACKER() { return YimMenu::NativeInvoker::Invoke<3341, void>(); }
	FORCEINLINE int NETWORK_GET_NUMBER_BODY_TRACKER_HITS() { return YimMenu::NativeInvoker::Invoke<3342, int>(); }
	FORCEINLINE bool NETWORK_HAS_BONE_BEEN_HIT_BY_KILLER(int boneIndex) { return YimMenu::NativeInvoker::Invoke<3343, bool>(boneIndex); }
	FORCEINLINE bool NETWORK_SET_ATTRIBUTE_DAMAGE_TO_PLAYER(Ped ped, Player player) { return YimMenu::NativeInvoker::Invoke<3344, bool>(ped, player); }
	FORCEINLINE void NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_DAMAGE(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3345, void>(entity, toggle); }
	FORCEINLINE void NETWORK_TRIGGER_DAMAGE_EVENT_FOR_ZERO_WEAPON_HASH(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3346, void>(entity, toggle); }
	FORCEINLINE void NETWORK_SET_NO_LONGER_NEEDED(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3347, void>(entity, toggle); }
	FORCEINLINE bool NETWORK_EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible, int netId) { return YimMenu::NativeInvoker::Invoke<3348, bool>(vehicle, isAudible, isInvisible, netId); }
	FORCEINLINE void NETWORK_EXPLODE_HELI(Vehicle vehicle, bool isAudible, bool isInvisible, int netId) { return YimMenu::NativeInvoker::Invoke<3349, void>(vehicle, isAudible, isInvisible, netId); }
	FORCEINLINE void NETWORK_USE_LOGARITHMIC_BLENDING_THIS_FRAME(Entity entity) { return YimMenu::NativeInvoker::Invoke<3350, void>(entity); }
	FORCEINLINE void NETWORK_OVERRIDE_COORDS_AND_HEADING(Entity entity, float x, float y, float z, float heading) { return YimMenu::NativeInvoker::Invoke<3351, void>(entity, x, y, z, heading); }
	FORCEINLINE void NETWORK_ENABLE_EXTRA_VEHICLE_ORIENTATION_BLEND_CHECKS(int netId, bool toggle) { return YimMenu::NativeInvoker::Invoke<3352, void>(netId, toggle); }
	FORCEINLINE void NETWORK_DISABLE_PROXIMITY_MIGRATION(int netID) { return YimMenu::NativeInvoker::Invoke<3353, void>(netID); }
	FORCEINLINE void NETWORK_SET_PROPERTY_ID(int id) { return YimMenu::NativeInvoker::Invoke<3354, void>(id); }
	FORCEINLINE void NETWORK_CLEAR_PROPERTY_ID() { return YimMenu::NativeInvoker::Invoke<3355, void>(); }
	FORCEINLINE void NETWORK_SET_PLAYER_MENTAL_STATE(int p0) { return YimMenu::NativeInvoker::Invoke<3356, void>(p0); }
	FORCEINLINE void NETWORK_SET_MINIMUM_RANK_FOR_MISSION(bool p0) { return YimMenu::NativeInvoker::Invoke<3357, void>(p0); }
	FORCEINLINE void NETWORK_CACHE_LOCAL_PLAYER_HEAD_BLEND_DATA() { return YimMenu::NativeInvoker::Invoke<3358, void>(); }
	FORCEINLINE bool NETWORK_HAS_CACHED_PLAYER_HEAD_BLEND_DATA(Player player) { return YimMenu::NativeInvoker::Invoke<3359, bool>(player); }
	FORCEINLINE bool NETWORK_APPLY_CACHED_PLAYER_HEAD_BLEND_DATA(Ped ped, Player player) { return YimMenu::NativeInvoker::Invoke<3360, bool>(ped, player); }
	FORCEINLINE int GET_NUM_COMMERCE_ITEMS() { return YimMenu::NativeInvoker::Invoke<3361, int>(); }
	FORCEINLINE bool IS_COMMERCE_DATA_VALID() { return YimMenu::NativeInvoker::Invoke<3362, bool>(); }
	FORCEINLINE void TRIGGER_COMMERCE_DATA_FETCH(Any p0) { return YimMenu::NativeInvoker::Invoke<3363, void>(p0); }
	FORCEINLINE bool IS_COMMERCE_DATA_FETCH_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<3364, bool>(); }
	FORCEINLINE const char* GET_COMMERCE_ITEM_ID(int index) { return YimMenu::NativeInvoker::Invoke<3365, const char*>(index); }
	FORCEINLINE const char* GET_COMMERCE_ITEM_NAME(int index) { return YimMenu::NativeInvoker::Invoke<3366, const char*>(index); }
	FORCEINLINE const char* GET_COMMERCE_PRODUCT_PRICE(int index) { return YimMenu::NativeInvoker::Invoke<3367, const char*>(index); }
	FORCEINLINE int GET_COMMERCE_ITEM_NUM_CATS(int index) { return YimMenu::NativeInvoker::Invoke<3368, int>(index); }
	FORCEINLINE const char* GET_COMMERCE_ITEM_CAT(int index, int index2) { return YimMenu::NativeInvoker::Invoke<3369, const char*>(index, index2); }
	FORCEINLINE void OPEN_COMMERCE_STORE(const char* p0, const char* p1, int p2) { return YimMenu::NativeInvoker::Invoke<3370, void>(p0, p1, p2); }
	FORCEINLINE bool IS_COMMERCE_STORE_OPEN() { return YimMenu::NativeInvoker::Invoke<3371, bool>(); }
	FORCEINLINE void SET_STORE_ENABLED(bool toggle) { return YimMenu::NativeInvoker::Invoke<3372, void>(toggle); }
	FORCEINLINE bool REQUEST_COMMERCE_ITEM_IMAGE(int index) { return YimMenu::NativeInvoker::Invoke<3373, bool>(index); }
	FORCEINLINE void RELEASE_ALL_COMMERCE_ITEM_IMAGES() { return YimMenu::NativeInvoker::Invoke<3374, void>(); }
	FORCEINLINE const char* GET_COMMERCE_ITEM_TEXTURENAME(int index) { return YimMenu::NativeInvoker::Invoke<3375, const char*>(index); }
	FORCEINLINE bool IS_STORE_AVAILABLE_TO_USER() { return YimMenu::NativeInvoker::Invoke<3376, bool>(); }
	FORCEINLINE void DELAY_MP_STORE_OPEN() { return YimMenu::NativeInvoker::Invoke<3377, void>(); }
	FORCEINLINE void RESET_STORE_NETWORK_GAME_TRACKING() { return YimMenu::NativeInvoker::Invoke<3378, void>(); }
	FORCEINLINE bool IS_USER_OLD_ENOUGH_TO_ACCESS_STORE() { return YimMenu::NativeInvoker::Invoke<3379, bool>(); }
	FORCEINLINE void SET_LAST_VIEWED_SHOP_ITEM(Hash p0, int p1, Hash p2) { return YimMenu::NativeInvoker::Invoke<3380, void>(p0, p1, p2); }
	FORCEINLINE int GET_USER_PREMIUM_ACCESS() { return YimMenu::NativeInvoker::Invoke<3381, int>(); }
	FORCEINLINE int GET_USER_STARTER_ACCESS() { return YimMenu::NativeInvoker::Invoke<3382, int>(); }
	FORCEINLINE int CLOUD_DELETE_MEMBER_FILE(const char* p0) { return YimMenu::NativeInvoker::Invoke<3383, int>(p0); }
	FORCEINLINE bool CLOUD_HAS_REQUEST_COMPLETED(int requestId) { return YimMenu::NativeInvoker::Invoke<3384, bool>(requestId); }
	FORCEINLINE bool CLOUD_DID_REQUEST_SUCCEED(int requestId) { return YimMenu::NativeInvoker::Invoke<3385, bool>(requestId); }
	FORCEINLINE void CLOUD_CHECK_AVAILABILITY() { return YimMenu::NativeInvoker::Invoke<3386, void>(); }
	FORCEINLINE bool CLOUD_IS_CHECKING_AVAILABILITY() { return YimMenu::NativeInvoker::Invoke<3387, bool>(); }
	FORCEINLINE bool CLOUD_GET_AVAILABILITY_CHECK_RESULT() { return YimMenu::NativeInvoker::Invoke<3388, bool>(); }
	FORCEINLINE int GET_CONTENT_TO_LOAD_TYPE() { return YimMenu::NativeInvoker::Invoke<3389, int>(); }
	FORCEINLINE bool GET_IS_LAUNCH_FROM_LIVE_AREA() { return YimMenu::NativeInvoker::Invoke<3390, bool>(); }
	FORCEINLINE bool GET_IS_LIVE_AREA_LAUNCH_WITH_CONTENT() { return YimMenu::NativeInvoker::Invoke<3391, bool>(); }
	FORCEINLINE void CLEAR_SERVICE_EVENT_ARGUMENTS() { return YimMenu::NativeInvoker::Invoke<3392, void>(); }
	FORCEINLINE bool UGC_COPY_CONTENT(Any* p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<3393, bool>(p0, p1); }
	FORCEINLINE bool UGC_IS_CREATING() { return YimMenu::NativeInvoker::Invoke<3394, bool>(); }
	FORCEINLINE bool UGC_HAS_CREATE_FINISHED() { return YimMenu::NativeInvoker::Invoke<3395, bool>(); }
	FORCEINLINE bool UGC_DID_CREATE_SUCCEED() { return YimMenu::NativeInvoker::Invoke<3396, bool>(); }
	FORCEINLINE int UGC_GET_CREATE_RESULT() { return YimMenu::NativeInvoker::Invoke<3397, int>(); }
	FORCEINLINE const char* UGC_GET_CREATE_CONTENT_ID() { return YimMenu::NativeInvoker::Invoke<3398, const char*>(); }
	FORCEINLINE void UGC_CLEAR_CREATE_RESULT() { return YimMenu::NativeInvoker::Invoke<3399, void>(); }
	FORCEINLINE bool UGC_QUERY_MY_CONTENT(Any p0, Any p1, Any* p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<3400, bool>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE bool UGC_QUERY_BY_CATEGORY(Any p0, Any p1, Any p2, const char* p3, Any p4, bool p5) { return YimMenu::NativeInvoker::Invoke<3401, bool>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE bool UGC_QUERY_BY_CONTENT_ID(const char* contentId, bool latestVersion, const char* contentTypeName) { return YimMenu::NativeInvoker::Invoke<3402, bool>(contentId, latestVersion, contentTypeName); }
	FORCEINLINE bool UGC_QUERY_BY_CONTENT_IDS(Any* data, int count, bool latestVersion, const char* contentTypeName) { return YimMenu::NativeInvoker::Invoke<3403, bool>(data, count, latestVersion, contentTypeName); }
	FORCEINLINE bool UGC_QUERY_MOST_RECENTLY_CREATED_CONTENT(int offset, int count, const char* contentTypeName, int p3) { return YimMenu::NativeInvoker::Invoke<3404, bool>(offset, count, contentTypeName, p3); }
	FORCEINLINE bool UGC_GET_BOOKMARKED_CONTENT(Any p0, Any p1, const char* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<3405, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool UGC_GET_MY_CONTENT(Any p0, Any p1, const char* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<3406, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool UGC_GET_FRIEND_CONTENT(Any p0, Any p1, const char* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<3407, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool UGC_GET_CREW_CONTENT(Any p0, Any p1, Any p2, const char* p3, Any* p4) { return YimMenu::NativeInvoker::Invoke<3408, bool>(p0, p1, p2, p3, p4); }
	FORCEINLINE bool UGC_GET_GET_BY_CATEGORY(Any p0, Any p1, Any p2, const char* p3, Any* p4) { return YimMenu::NativeInvoker::Invoke<3409, bool>(p0, p1, p2, p3, p4); }
	FORCEINLINE bool UGC_GET_GET_BY_CONTENT_ID(const char* contentId, const char* contentTypeName) { return YimMenu::NativeInvoker::Invoke<3410, bool>(contentId, contentTypeName); }
	FORCEINLINE bool UGC_GET_GET_BY_CONTENT_IDS(Any* data, int dataCount, const char* contentTypeName) { return YimMenu::NativeInvoker::Invoke<3411, bool>(data, dataCount, contentTypeName); }
	FORCEINLINE bool UGC_GET_MOST_RECENTLY_CREATED_CONTENT(Any p0, Any p1, Any* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<3412, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool UGC_GET_MOST_RECENTLY_PLAYED_CONTENT(Any p0, Any p1, Any* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<3413, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool UGC_GET_TOP_RATED_CONTENT(Any p0, Any p1, Any* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<3414, bool>(p0, p1, p2, p3); }
	FORCEINLINE void UGC_CANCEL_QUERY() { return YimMenu::NativeInvoker::Invoke<3415, void>(); }
	FORCEINLINE bool UGC_IS_GETTING() { return YimMenu::NativeInvoker::Invoke<3416, bool>(); }
	FORCEINLINE bool UGC_HAS_GET_FINISHED() { return YimMenu::NativeInvoker::Invoke<3417, bool>(); }
	FORCEINLINE bool UGC_DID_GET_SUCCEED() { return YimMenu::NativeInvoker::Invoke<3418, bool>(); }
	FORCEINLINE bool UGC_WAS_QUERY_FORCE_CANCELLED() { return YimMenu::NativeInvoker::Invoke<3419, bool>(); }
	FORCEINLINE int UGC_GET_QUERY_RESULT() { return YimMenu::NativeInvoker::Invoke<3420, int>(); }
	FORCEINLINE int UGC_GET_CONTENT_NUM() { return YimMenu::NativeInvoker::Invoke<3421, int>(); }
	FORCEINLINE int UGC_GET_CONTENT_TOTAL() { return YimMenu::NativeInvoker::Invoke<3422, int>(); }
	FORCEINLINE Hash UGC_GET_CONTENT_HASH() { return YimMenu::NativeInvoker::Invoke<3423, Hash>(); }
	FORCEINLINE void UGC_CLEAR_QUERY_RESULTS() { return YimMenu::NativeInvoker::Invoke<3424, void>(); }
	FORCEINLINE const char* UGC_GET_CONTENT_USER_ID(int p0) { return YimMenu::NativeInvoker::Invoke<3425, const char*>(p0); }
	FORCEINLINE bool UGC_GET_CONTENT_CREATOR_GAMER_HANDLE(int p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<3426, bool>(p0, p1); }
	FORCEINLINE bool UGC_GET_CONTENT_CREATED_BY_LOCAL_PLAYER(Any p0) { return YimMenu::NativeInvoker::Invoke<3427, bool>(p0); }
	FORCEINLINE const char* UGC_GET_CONTENT_USER_NAME(Any p0) { return YimMenu::NativeInvoker::Invoke<3428, const char*>(p0); }
	FORCEINLINE bool UGC_GET_CONTENT_IS_USING_SC_NICKNAME(Any p0) { return YimMenu::NativeInvoker::Invoke<3429, bool>(p0); }
	FORCEINLINE int UGC_GET_CONTENT_CATEGORY(int p0) { return YimMenu::NativeInvoker::Invoke<3430, int>(p0); }
	FORCEINLINE const char* UGC_GET_CONTENT_ID(int p0) { return YimMenu::NativeInvoker::Invoke<3431, const char*>(p0); }
	FORCEINLINE const char* UGC_GET_ROOT_CONTENT_ID(int p0) { return YimMenu::NativeInvoker::Invoke<3432, const char*>(p0); }
	FORCEINLINE const char* UGC_GET_CONTENT_NAME(Any p0) { return YimMenu::NativeInvoker::Invoke<3433, const char*>(p0); }
	FORCEINLINE int UGC_GET_CONTENT_DESCRIPTION_HASH(Any p0) { return YimMenu::NativeInvoker::Invoke<3434, int>(p0); }
	FORCEINLINE const char* UGC_GET_CONTENT_PATH(int p0, int p1) { return YimMenu::NativeInvoker::Invoke<3435, const char*>(p0, p1); }
	FORCEINLINE void UGC_GET_CONTENT_UPDATED_DATE(Any p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<3436, void>(p0, p1); }
	FORCEINLINE int UGC_GET_CONTENT_FILE_VERSION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3437, int>(p0, p1); }
	FORCEINLINE bool UGC_GET_CONTENT_HAS_LO_RES_PHOTO(int p0) { return YimMenu::NativeInvoker::Invoke<3438, bool>(p0); }
	FORCEINLINE bool UGC_GET_CONTENT_HAS_HI_RES_PHOTO(int p0) { return YimMenu::NativeInvoker::Invoke<3439, bool>(p0); }
	FORCEINLINE int UGC_GET_CONTENT_LANGUAGE(Any p0) { return YimMenu::NativeInvoker::Invoke<3440, int>(p0); }
	FORCEINLINE bool UGC_GET_CONTENT_IS_PUBLISHED(Any p0) { return YimMenu::NativeInvoker::Invoke<3441, bool>(p0); }
	FORCEINLINE bool UGC_GET_CONTENT_IS_VERIFIED(Any p0) { return YimMenu::NativeInvoker::Invoke<3442, bool>(p0); }
	FORCEINLINE float UGC_GET_CONTENT_RATING(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3443, float>(p0, p1); }
	FORCEINLINE int UGC_GET_CONTENT_RATING_COUNT(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3444, int>(p0, p1); }
	FORCEINLINE int UGC_GET_CONTENT_RATING_POSITIVE_COUNT(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3445, int>(p0, p1); }
	FORCEINLINE int UGC_GET_CONTENT_RATING_NEGATIVE_COUNT(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3446, int>(p0, p1); }
	FORCEINLINE bool UGC_GET_CONTENT_HAS_PLAYER_RECORD(Any p0) { return YimMenu::NativeInvoker::Invoke<3447, bool>(p0); }
	FORCEINLINE bool UGC_GET_CONTENT_HAS_PLAYER_BOOKMARKED(Any p0) { return YimMenu::NativeInvoker::Invoke<3448, bool>(p0); }
	FORCEINLINE int UGC_REQUEST_CONTENT_DATA_FROM_INDEX(int p0, int p1) { return YimMenu::NativeInvoker::Invoke<3449, int>(p0, p1); }
	FORCEINLINE int UGC_REQUEST_CONTENT_DATA_FROM_PARAMS(const char* contentTypeName, const char* contentId, int p2, int p3, int p4) { return YimMenu::NativeInvoker::Invoke<3450, int>(contentTypeName, contentId, p2, p3, p4); }
	FORCEINLINE int UGC_REQUEST_CACHED_DESCRIPTION(int p0) { return YimMenu::NativeInvoker::Invoke<3451, int>(p0); }
	FORCEINLINE bool UGC_IS_DESCRIPTION_REQUEST_IN_PROGRESS(Any p0) { return YimMenu::NativeInvoker::Invoke<3452, bool>(p0); }
	FORCEINLINE bool UGC_HAS_DESCRIPTION_REQUEST_FINISHED(Any p0) { return YimMenu::NativeInvoker::Invoke<3453, bool>(p0); }
	FORCEINLINE bool UGC_DID_DESCRIPTION_REQUEST_SUCCEED(Any p0) { return YimMenu::NativeInvoker::Invoke<3454, bool>(p0); }
	FORCEINLINE const char* UGC_GET_CACHED_DESCRIPTION(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3455, const char*>(p0, p1); }
	FORCEINLINE bool UGC_RELEASE_CACHED_DESCRIPTION(Any p0) { return YimMenu::NativeInvoker::Invoke<3456, bool>(p0); }
	FORCEINLINE void UGC_RELEASE_ALL_CACHED_DESCRIPTIONS() { return YimMenu::NativeInvoker::Invoke<3457, void>(); }
	FORCEINLINE bool UGC_PUBLISH(const char* contentId, const char* baseContentId, const char* contentTypeName) { return YimMenu::NativeInvoker::Invoke<3458, bool>(contentId, baseContentId, contentTypeName); }
	FORCEINLINE bool UGC_SET_BOOKMARKED(const char* contentId, bool bookmarked, const char* contentTypeName) { return YimMenu::NativeInvoker::Invoke<3459, bool>(contentId, bookmarked, contentTypeName); }
	FORCEINLINE bool UGC_SET_DELETED(Any* p0, bool p1, const char* p2) { return YimMenu::NativeInvoker::Invoke<3460, bool>(p0, p1, p2); }
	FORCEINLINE bool UGC_IS_MODIFYING() { return YimMenu::NativeInvoker::Invoke<3461, bool>(); }
	FORCEINLINE bool UGC_HAS_MODIFY_FINISHED() { return YimMenu::NativeInvoker::Invoke<3462, bool>(); }
	FORCEINLINE bool UGC_DID_MODIFY_SUCCEED() { return YimMenu::NativeInvoker::Invoke<3463, bool>(); }
	FORCEINLINE int UGC_GET_MODIFY_RESULT() { return YimMenu::NativeInvoker::Invoke<3464, int>(); }
	FORCEINLINE void UGC_CLEAR_MODIFY_RESULT() { return YimMenu::NativeInvoker::Invoke<3465, void>(); }
	FORCEINLINE bool UGC_GET_CREATORS_BY_USER_ID(Any* p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<3466, bool>(p0, p1); }
	FORCEINLINE bool UGC_HAS_QUERY_CREATORS_FINISHED() { return YimMenu::NativeInvoker::Invoke<3467, bool>(); }
	FORCEINLINE bool UGC_DID_QUERY_CREATORS_SUCCEED() { return YimMenu::NativeInvoker::Invoke<3468, bool>(); }
	FORCEINLINE int UGC_GET_CREATOR_NUM() { return YimMenu::NativeInvoker::Invoke<3469, int>(); }
	FORCEINLINE bool UGC_LOAD_OFFLINE_QUERY(Any p0) { return YimMenu::NativeInvoker::Invoke<3470, bool>(p0); }
	FORCEINLINE void UGC_CLEAR_OFFLINE_QUERY() { return YimMenu::NativeInvoker::Invoke<3471, void>(); }
	FORCEINLINE void UGC_SET_QUERY_DATA_FROM_OFFLINE(bool p0) { return YimMenu::NativeInvoker::Invoke<3472, void>(p0); }
	FORCEINLINE void UGC_SET_USING_OFFLINE_CONTENT(bool p0) { return YimMenu::NativeInvoker::Invoke<3473, void>(p0); }
	FORCEINLINE bool UGC_IS_LANGUAGE_SUPPORTED(Any p0) { return YimMenu::NativeInvoker::Invoke<3474, bool>(p0); }
	FORCEINLINE bool FACEBOOK_POST_COMPLETED_HEIST(const char* heistName, int cashEarned, int xpEarned) { return YimMenu::NativeInvoker::Invoke<3475, bool>(heistName, cashEarned, xpEarned); }
	FORCEINLINE bool FACEBOOK_POST_CREATE_CHARACTER() { return YimMenu::NativeInvoker::Invoke<3476, bool>(); }
	FORCEINLINE bool FACEBOOK_POST_COMPLETED_MILESTONE(int milestoneId) { return YimMenu::NativeInvoker::Invoke<3477, bool>(milestoneId); }
	FORCEINLINE bool FACEBOOK_HAS_POST_COMPLETED() { return YimMenu::NativeInvoker::Invoke<3478, bool>(); }
	FORCEINLINE bool FACEBOOK_DID_POST_SUCCEED() { return YimMenu::NativeInvoker::Invoke<3479, bool>(); }
	FORCEINLINE bool FACEBOOK_CAN_POST_TO_FACEBOOK() { return YimMenu::NativeInvoker::Invoke<3480, bool>(); }
	FORCEINLINE int TEXTURE_DOWNLOAD_REQUEST(Any* gamerHandle, const char* filePath, const char* name, bool p3) { return YimMenu::NativeInvoker::Invoke<3481, int>(gamerHandle, filePath, name, p3); }
	FORCEINLINE int TITLE_TEXTURE_DOWNLOAD_REQUEST(const char* filePath, const char* name, bool p2) { return YimMenu::NativeInvoker::Invoke<3482, int>(filePath, name, p2); }
	FORCEINLINE int UGC_TEXTURE_DOWNLOAD_REQUEST(const char* p0, int p1, int p2, int p3, const char* p4, bool p5) { return YimMenu::NativeInvoker::Invoke<3483, int>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void TEXTURE_DOWNLOAD_RELEASE(int p0) { return YimMenu::NativeInvoker::Invoke<3484, void>(p0); }
	FORCEINLINE bool TEXTURE_DOWNLOAD_HAS_FAILED(int p0) { return YimMenu::NativeInvoker::Invoke<3485, bool>(p0); }
	FORCEINLINE const char* TEXTURE_DOWNLOAD_GET_NAME(int p0) { return YimMenu::NativeInvoker::Invoke<3486, const char*>(p0); }
	FORCEINLINE int GET_STATUS_OF_TEXTURE_DOWNLOAD(int p0) { return YimMenu::NativeInvoker::Invoke<3487, int>(p0); }
	FORCEINLINE bool NETWORK_CHECK_ROS_LINK_WENTDOWN_NOT_NET() { return YimMenu::NativeInvoker::Invoke<3488, bool>(); }
	FORCEINLINE bool NETWORK_SHOULD_SHOW_STRICT_NAT_WARNING() { return YimMenu::NativeInvoker::Invoke<3489, bool>(); }
	FORCEINLINE bool NETWORK_IS_CABLE_CONNECTED() { return YimMenu::NativeInvoker::Invoke<3490, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_SCS_PRIVATE_MSG_PRIV() { return YimMenu::NativeInvoker::Invoke<3491, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_ROS_SOCIAL_CLUB_PRIV() { return YimMenu::NativeInvoker::Invoke<3492, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_ROS_BANNED_PRIV() { return YimMenu::NativeInvoker::Invoke<3493, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_ROS_CREATE_TICKET_PRIV() { return YimMenu::NativeInvoker::Invoke<3494, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_ROS_MULTIPLAYER_PRIV() { return YimMenu::NativeInvoker::Invoke<3495, bool>(); }
	FORCEINLINE bool NETWORK_HAVE_ROS_LEADERBOARD_WRITE_PRIV() { return YimMenu::NativeInvoker::Invoke<3496, bool>(); }
	FORCEINLINE bool NETWORK_HAS_ROS_PRIVILEGE(int index) { return YimMenu::NativeInvoker::Invoke<3497, bool>(index); }
	FORCEINLINE bool NETWORK_HAS_ROS_PRIVILEGE_END_DATE(int privilege, int* banType, Any* timeData) { return YimMenu::NativeInvoker::Invoke<3498, bool>(privilege, banType, timeData); }
	FORCEINLINE bool NETWORK_HAS_ROS_PRIVILEGE_PLAYED_LAST_GEN() { return YimMenu::NativeInvoker::Invoke<3499, bool>(); }
	FORCEINLINE bool NETWORK_HAS_ROS_PRIVILEGE_SPECIAL_EDITION_CONTENT() { return YimMenu::NativeInvoker::Invoke<3500, bool>(); }
	FORCEINLINE int NETWORK_START_COMMUNICATION_PERMISSIONS_CHECK(Any p0) { return YimMenu::NativeInvoker::Invoke<3501, int>(p0); }
	FORCEINLINE int NETWORK_START_USER_CONTENT_PERMISSIONS_CHECK(Any* netHandle) { return YimMenu::NativeInvoker::Invoke<3502, int>(netHandle); }
	FORCEINLINE void NETWORK_SKIP_RADIO_RESET_NEXT_CLOSE() { return YimMenu::NativeInvoker::Invoke<3503, void>(); }
	FORCEINLINE void NETWORK_SKIP_RADIO_RESET_NEXT_OPEN() { return YimMenu::NativeInvoker::Invoke<3504, void>(); }
	FORCEINLINE bool NETWORK_SKIP_RADIO_WARNING() { return YimMenu::NativeInvoker::Invoke<3505, bool>(); }
	FORCEINLINE void NETWORK_FORCE_LOCAL_PLAYER_SCAR_SYNC() { return YimMenu::NativeInvoker::Invoke<3506, void>(); }
	FORCEINLINE void NETWORK_DISABLE_LEAVE_REMOTE_PED_BEHIND(bool toggle) { return YimMenu::NativeInvoker::Invoke<3507, void>(toggle); }
	FORCEINLINE void NETWORK_ALLOW_REMOTE_ATTACHMENT_MODIFICATION(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3508, void>(entity, toggle); }
	FORCEINLINE void NETWORK_SHOW_CHAT_RESTRICTION_MSC(Player player) { return YimMenu::NativeInvoker::Invoke<3509, void>(player); }
	FORCEINLINE void NETWORK_SHOW_PSN_UGC_RESTRICTION() { return YimMenu::NativeInvoker::Invoke<3510, void>(); }
	FORCEINLINE bool NETWORK_IS_TITLE_UPDATE_REQUIRED() { return YimMenu::NativeInvoker::Invoke<3511, bool>(); }
	FORCEINLINE void NETWORK_QUIT_MP_TO_DESKTOP() { return YimMenu::NativeInvoker::Invoke<3512, void>(); }
	FORCEINLINE bool NETWORK_IS_CONNECTED_VIA_RELAY(Player player) { return YimMenu::NativeInvoker::Invoke<3513, bool>(player); }
	FORCEINLINE float NETWORK_GET_AVERAGE_LATENCY(Player player) { return YimMenu::NativeInvoker::Invoke<3514, float>(player); }
	FORCEINLINE float NETWORK_GET_AVERAGE_PING(Player player) { return YimMenu::NativeInvoker::Invoke<3515, float>(player); }
	FORCEINLINE float NETWORK_GET_AVERAGE_PACKET_LOSS(Player player) { return YimMenu::NativeInvoker::Invoke<3516, float>(player); }
	FORCEINLINE int NETWORK_GET_NUM_UNACKED_RELIABLES(Player player) { return YimMenu::NativeInvoker::Invoke<3517, int>(player); }
	FORCEINLINE int NETWORK_GET_UNRELIABLE_RESEND_COUNT(Player player) { return YimMenu::NativeInvoker::Invoke<3518, int>(player); }
	FORCEINLINE int NETWORK_GET_HIGHEST_RELIABLE_RESEND_COUNT(Player player) { return YimMenu::NativeInvoker::Invoke<3519, int>(player); }
	FORCEINLINE void NETWORK_REPORT_CODE_TAMPER() { return YimMenu::NativeInvoker::Invoke<3520, void>(); }
	FORCEINLINE Vector3 NETWORK_GET_LAST_ENTITY_POS_RECEIVED_OVER_NETWORK(Entity entity) { return YimMenu::NativeInvoker::Invoke<3521, Vector3>(entity); }
	FORCEINLINE Vector3 NETWORK_GET_LAST_PLAYER_POS_RECEIVED_OVER_NETWORK(Player player) { return YimMenu::NativeInvoker::Invoke<3522, Vector3>(player); }
	FORCEINLINE Vector3 NETWORK_GET_LAST_VEL_RECEIVED_OVER_NETWORK(Entity entity) { return YimMenu::NativeInvoker::Invoke<3523, Vector3>(entity); }
	FORCEINLINE Vector3 NETWORK_GET_PREDICTED_VELOCITY(Entity entity, float maxSpeedToPredict) { return YimMenu::NativeInvoker::Invoke<3524, Vector3>(entity, maxSpeedToPredict); }
	FORCEINLINE void NETWORK_DUMP_NET_IF_CONFIG() { return YimMenu::NativeInvoker::Invoke<3525, void>(); }
	FORCEINLINE void NETWORK_GET_SIGNALLING_INFO(Any* p0) { return YimMenu::NativeInvoker::Invoke<3526, void>(p0); }
	FORCEINLINE void NETWORK_GET_NET_STATISTICS_INFO(Any* p0) { return YimMenu::NativeInvoker::Invoke<3527, void>(p0); }
	FORCEINLINE int NETWORK_GET_PLAYER_ACCOUNT_ID(Player player) { return YimMenu::NativeInvoker::Invoke<3528, int>(player); }
	FORCEINLINE void NETWORK_UGC_NAV(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3529, void>(p0, p1); }
}

namespace OBJECT
{
	FORCEINLINE Object CREATE_OBJECT(Hash modelHash, float x, float y, float z, bool isNetwork, bool bScriptHostObj, bool dynamic) { return YimMenu::NativeInvoker::Invoke<3530, Object>(modelHash, x, y, z, isNetwork, bScriptHostObj, dynamic); }
	FORCEINLINE Object CREATE_OBJECT_NO_OFFSET(Hash modelHash, float x, float y, float z, bool isNetwork, bool bScriptHostObj, bool dynamic) { return YimMenu::NativeInvoker::Invoke<3531, Object>(modelHash, x, y, z, isNetwork, bScriptHostObj, dynamic); }
	FORCEINLINE void DELETE_OBJECT(Object* object) { return YimMenu::NativeInvoker::Invoke<3532, void>(object); }
	FORCEINLINE bool PLACE_OBJECT_ON_GROUND_PROPERLY(Object object) { return YimMenu::NativeInvoker::Invoke<3533, bool>(object); }
	FORCEINLINE bool PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(Object object) { return YimMenu::NativeInvoker::Invoke<3534, bool>(object); }
	FORCEINLINE bool ROTATE_OBJECT(Object object, float p1, float p2, bool p3) { return YimMenu::NativeInvoker::Invoke<3535, bool>(object, p1, p2, p3); }
	FORCEINLINE bool SLIDE_OBJECT(Object object, float toX, float toY, float toZ, float speedX, float speedY, float speedZ, bool collision) { return YimMenu::NativeInvoker::Invoke<3536, bool>(object, toX, toY, toZ, speedX, speedY, speedZ, collision); }
	FORCEINLINE void SET_OBJECT_TARGETTABLE(Object object, bool targettable) { return YimMenu::NativeInvoker::Invoke<3537, void>(object, targettable); }
	FORCEINLINE void SET_OBJECT_FORCE_VEHICLES_TO_AVOID(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3538, void>(object, toggle); }
	FORCEINLINE Object GET_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, bool isMission, bool p6, bool p7) { return YimMenu::NativeInvoker::Invoke<3539, Object>(x, y, z, radius, modelHash, isMission, p6, p7); }
	FORCEINLINE bool HAS_OBJECT_BEEN_BROKEN(Object object, Any p1) { return YimMenu::NativeInvoker::Invoke<3540, bool>(object, p1); }
	FORCEINLINE bool HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(float p0, float p1, float p2, float p3, Hash modelHash, Any p5) { return YimMenu::NativeInvoker::Invoke<3541, bool>(p0, p1, p2, p3, modelHash, p5); }
	FORCEINLINE bool HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_COMPLETELY_DESTROYED(float x, float y, float z, float radius, Hash modelHash, bool p5) { return YimMenu::NativeInvoker::Invoke<3542, bool>(x, y, z, radius, modelHash, p5); }
	FORCEINLINE bool GET_HAS_OBJECT_BEEN_COMPLETELY_DESTROYED(Any p0) { return YimMenu::NativeInvoker::Invoke<3543, bool>(p0); }
	FORCEINLINE Vector3 GET_OFFSET_FROM_COORD_AND_HEADING_IN_WORLD_COORDS(float xPos, float yPos, float zPos, float heading, float xOffset, float yOffset, float zOffset) { return YimMenu::NativeInvoker::Invoke<3544, Vector3>(xPos, yPos, zPos, heading, xOffset, yOffset, zOffset); }
	FORCEINLINE bool GET_COORDS_AND_ROTATION_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, Vector3* outPosition, Vector3* outRotation, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<3545, bool>(x, y, z, radius, modelHash, outPosition, outRotation, rotationOrder); }
	FORCEINLINE void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, bool locked, float heading, bool p6) { return YimMenu::NativeInvoker::Invoke<3546, void>(type, x, y, z, locked, heading, p6); }
	FORCEINLINE void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(Hash type, float x, float y, float z, bool* locked, float* heading) { return YimMenu::NativeInvoker::Invoke<3547, void>(type, x, y, z, locked, heading); }
	FORCEINLINE void SET_LOCKED_UNSTREAMED_IN_DOOR_OF_TYPE(Hash modelHash, float x, float y, float z, bool locked, float xRotMult, float yRotMult, float zRotMult) { return YimMenu::NativeInvoker::Invoke<3548, void>(modelHash, x, y, z, locked, xRotMult, yRotMult, zRotMult); }
	FORCEINLINE void PLAY_OBJECT_AUTO_START_ANIM(Any p0) { return YimMenu::NativeInvoker::Invoke<3549, void>(p0); }
	FORCEINLINE void ADD_DOOR_TO_SYSTEM(Hash doorHash, Hash modelHash, float x, float y, float z, bool p5, bool scriptDoor, bool isLocal) { return YimMenu::NativeInvoker::Invoke<3550, void>(doorHash, modelHash, x, y, z, p5, scriptDoor, isLocal); }
	FORCEINLINE void REMOVE_DOOR_FROM_SYSTEM(Hash doorHash, Any p1) { return YimMenu::NativeInvoker::Invoke<3551, void>(doorHash, p1); }
	FORCEINLINE void DOOR_SYSTEM_SET_DOOR_STATE(Hash doorHash, int state, bool requestDoor, bool forceUpdate) { return YimMenu::NativeInvoker::Invoke<3552, void>(doorHash, state, requestDoor, forceUpdate); }
	FORCEINLINE int DOOR_SYSTEM_GET_DOOR_STATE(Hash doorHash) { return YimMenu::NativeInvoker::Invoke<3553, int>(doorHash); }
	FORCEINLINE int DOOR_SYSTEM_GET_DOOR_PENDING_STATE(Hash doorHash) { return YimMenu::NativeInvoker::Invoke<3554, int>(doorHash); }
	FORCEINLINE void DOOR_SYSTEM_SET_AUTOMATIC_RATE(Hash doorHash, float rate, bool requestDoor, bool forceUpdate) { return YimMenu::NativeInvoker::Invoke<3555, void>(doorHash, rate, requestDoor, forceUpdate); }
	FORCEINLINE void DOOR_SYSTEM_SET_AUTOMATIC_DISTANCE(Hash doorHash, float distance, bool requestDoor, bool forceUpdate) { return YimMenu::NativeInvoker::Invoke<3556, void>(doorHash, distance, requestDoor, forceUpdate); }
	FORCEINLINE void DOOR_SYSTEM_SET_OPEN_RATIO(Hash doorHash, float ajar, bool requestDoor, bool forceUpdate) { return YimMenu::NativeInvoker::Invoke<3557, void>(doorHash, ajar, requestDoor, forceUpdate); }
	FORCEINLINE float DOOR_SYSTEM_GET_AUTOMATIC_DISTANCE(Hash doorHash) { return YimMenu::NativeInvoker::Invoke<3558, float>(doorHash); }
	FORCEINLINE float DOOR_SYSTEM_GET_OPEN_RATIO(Hash doorHash) { return YimMenu::NativeInvoker::Invoke<3559, float>(doorHash); }
	FORCEINLINE void DOOR_SYSTEM_SET_SPRING_REMOVED(Hash doorHash, bool removed, bool requestDoor, bool forceUpdate) { return YimMenu::NativeInvoker::Invoke<3560, void>(doorHash, removed, requestDoor, forceUpdate); }
	FORCEINLINE void DOOR_SYSTEM_SET_HOLD_OPEN(Hash doorHash, bool toggle) { return YimMenu::NativeInvoker::Invoke<3561, void>(doorHash, toggle); }
	FORCEINLINE void DOOR_SYSTEM_SET_DOOR_OPEN_FOR_RACES(Hash doorHash, bool p1) { return YimMenu::NativeInvoker::Invoke<3562, void>(doorHash, p1); }
	FORCEINLINE bool IS_DOOR_REGISTERED_WITH_SYSTEM(Hash doorHash) { return YimMenu::NativeInvoker::Invoke<3563, bool>(doorHash); }
	FORCEINLINE bool IS_DOOR_CLOSED(Hash doorHash) { return YimMenu::NativeInvoker::Invoke<3564, bool>(doorHash); }
	FORCEINLINE void OPEN_ALL_BARRIERS_FOR_RACE(bool p0) { return YimMenu::NativeInvoker::Invoke<3565, void>(p0); }
	FORCEINLINE void CLOSE_ALL_BARRIERS_FOR_RACE() { return YimMenu::NativeInvoker::Invoke<3566, void>(); }
	FORCEINLINE bool DOOR_SYSTEM_GET_IS_PHYSICS_LOADED(Any p0) { return YimMenu::NativeInvoker::Invoke<3567, bool>(p0); }
	FORCEINLINE bool DOOR_SYSTEM_FIND_EXISTING_DOOR(float x, float y, float z, Hash modelHash, Hash* outDoorHash) { return YimMenu::NativeInvoker::Invoke<3568, bool>(x, y, z, modelHash, outDoorHash); }
	FORCEINLINE bool IS_GARAGE_EMPTY(Hash garageHash, bool p1, int p2) { return YimMenu::NativeInvoker::Invoke<3569, bool>(garageHash, p1, p2); }
	FORCEINLINE bool IS_PLAYER_ENTIRELY_INSIDE_GARAGE(Hash garageHash, Player player, float p2, int p3) { return YimMenu::NativeInvoker::Invoke<3570, bool>(garageHash, player, p2, p3); }
	FORCEINLINE bool IS_PLAYER_PARTIALLY_INSIDE_GARAGE(Hash garageHash, Player player, int p2) { return YimMenu::NativeInvoker::Invoke<3571, bool>(garageHash, player, p2); }
	FORCEINLINE bool ARE_ENTITIES_ENTIRELY_INSIDE_GARAGE(Hash garageHash, bool p1, bool p2, bool p3, Any p4) { return YimMenu::NativeInvoker::Invoke<3572, bool>(garageHash, p1, p2, p3, p4); }
	FORCEINLINE bool IS_ANY_ENTITY_ENTIRELY_INSIDE_GARAGE(Hash garageHash, bool p1, bool p2, bool p3, Any p4) { return YimMenu::NativeInvoker::Invoke<3573, bool>(garageHash, p1, p2, p3, p4); }
	FORCEINLINE bool IS_OBJECT_ENTIRELY_INSIDE_GARAGE(Hash garageHash, Entity entity, float p2, int p3) { return YimMenu::NativeInvoker::Invoke<3574, bool>(garageHash, entity, p2, p3); }
	FORCEINLINE bool IS_OBJECT_PARTIALLY_INSIDE_GARAGE(Hash garageHash, Entity entity, int p2) { return YimMenu::NativeInvoker::Invoke<3575, bool>(garageHash, entity, p2); }
	FORCEINLINE void CLEAR_GARAGE(Hash garageHash, bool isNetwork) { return YimMenu::NativeInvoker::Invoke<3576, void>(garageHash, isNetwork); }
	FORCEINLINE void CLEAR_OBJECTS_INSIDE_GARAGE(Hash garageHash, bool vehicles, bool peds, bool objects, bool isNetwork) { return YimMenu::NativeInvoker::Invoke<3577, void>(garageHash, vehicles, peds, objects, isNetwork); }
	FORCEINLINE void DISABLE_TIDYING_UP_IN_GARAGE(int id, bool toggle) { return YimMenu::NativeInvoker::Invoke<3578, void>(id, toggle); }
	FORCEINLINE void ENABLE_SAVING_IN_GARAGE(Hash garageHash, bool toggle) { return YimMenu::NativeInvoker::Invoke<3579, void>(garageHash, toggle); }
	FORCEINLINE void CLOSE_SAFEHOUSE_GARAGES() { return YimMenu::NativeInvoker::Invoke<3580, void>(); }
	FORCEINLINE bool DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(float x, float y, float z, float radius, Hash hash, bool p5) { return YimMenu::NativeInvoker::Invoke<3581, bool>(x, y, z, radius, hash, p5); }
	FORCEINLINE bool IS_POINT_IN_ANGLED_AREA(float xPos, float yPos, float zPos, float x1, float y1, float z1, float x2, float y2, float z2, float width, bool debug, bool includeZ) { return YimMenu::NativeInvoker::Invoke<3582, bool>(xPos, yPos, zPos, x1, y1, z1, x2, y2, z2, width, debug, includeZ); }
	FORCEINLINE void SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3583, void>(object, toggle); }
	FORCEINLINE void SET_OBJECT_PHYSICS_PARAMS(Object object, float weight, float p2, float p3, float p4, float p5, float gravity, float p7, float p8, float p9, float p10, float buoyancy) { return YimMenu::NativeInvoker::Invoke<3584, void>(object, weight, p2, p3, p4, p5, gravity, p7, p8, p9, p10, buoyancy); }
	FORCEINLINE float GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<3585, float>(p0, p1); }
	FORCEINLINE void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3586, void>(object, toggle); }
	FORCEINLINE bool IS_ANY_OBJECT_NEAR_POINT(float x, float y, float z, float range, bool p4) { return YimMenu::NativeInvoker::Invoke<3587, bool>(x, y, z, range, p4); }
	FORCEINLINE bool IS_OBJECT_NEAR_POINT(Hash objectHash, float x, float y, float z, float range) { return YimMenu::NativeInvoker::Invoke<3588, bool>(objectHash, x, y, z, range); }
	FORCEINLINE void REMOVE_OBJECT_HIGH_DETAIL_MODEL(Object object) { return YimMenu::NativeInvoker::Invoke<3589, void>(object); }
	FORCEINLINE void BREAK_OBJECT_FRAGMENT_CHILD(Object p0, Any p1, bool p2) { return YimMenu::NativeInvoker::Invoke<3590, void>(p0, p1, p2); }
	FORCEINLINE void DAMAGE_OBJECT_FRAGMENT_CHILD(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<3591, void>(p0, p1, p2); }
	FORCEINLINE void FIX_OBJECT_FRAGMENT(Object object) { return YimMenu::NativeInvoker::Invoke<3592, void>(object); }
	FORCEINLINE void TRACK_OBJECT_VISIBILITY(Object object) { return YimMenu::NativeInvoker::Invoke<3593, void>(object); }
	FORCEINLINE bool IS_OBJECT_VISIBLE(Object object) { return YimMenu::NativeInvoker::Invoke<3594, bool>(object); }
	FORCEINLINE void SET_OBJECT_IS_SPECIAL_GOLFBALL(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3595, void>(object, toggle); }
	FORCEINLINE void SET_OBJECT_TAKES_DAMAGE_FROM_COLLIDING_WITH_BUILDINGS(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<3596, void>(p0, p1); }
	FORCEINLINE void ALLOW_DAMAGE_EVENTS_FOR_NON_NETWORKED_OBJECTS(bool value) { return YimMenu::NativeInvoker::Invoke<3597, void>(value); }
	FORCEINLINE void SET_CUTSCENES_WEAPON_FLASHLIGHT_ON_THIS_FRAME(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3598, void>(object, toggle); }
	FORCEINLINE Object GET_RAYFIRE_MAP_OBJECT(float x, float y, float z, float radius, const char* name) { return YimMenu::NativeInvoker::Invoke<3599, Object>(x, y, z, radius, name); }
	FORCEINLINE void SET_STATE_OF_RAYFIRE_MAP_OBJECT(Object object, int state) { return YimMenu::NativeInvoker::Invoke<3600, void>(object, state); }
	FORCEINLINE int GET_STATE_OF_RAYFIRE_MAP_OBJECT(Object object) { return YimMenu::NativeInvoker::Invoke<3601, int>(object); }
	FORCEINLINE bool DOES_RAYFIRE_MAP_OBJECT_EXIST(Object object) { return YimMenu::NativeInvoker::Invoke<3602, bool>(object); }
	FORCEINLINE float GET_RAYFIRE_MAP_OBJECT_ANIM_PHASE(Object object) { return YimMenu::NativeInvoker::Invoke<3603, float>(object); }
	FORCEINLINE Pickup CREATE_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int p4, int value, bool p6, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<3604, Pickup>(pickupHash, posX, posY, posZ, p4, value, p6, modelHash); }
	FORCEINLINE Pickup CREATE_PICKUP_ROTATE(Hash pickupHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, int flag, int amount, Any p9, bool p10, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<3605, Pickup>(pickupHash, posX, posY, posZ, rotX, rotY, rotZ, flag, amount, p9, p10, modelHash); }
	FORCEINLINE void FORCE_PICKUP_ROTATE_FACE_UP() { return YimMenu::NativeInvoker::Invoke<3606, void>(); }
	FORCEINLINE void SET_CUSTOM_PICKUP_WEAPON_HASH(Hash pickupHash, Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3607, void>(pickupHash, pickup); }
	FORCEINLINE Object CREATE_AMBIENT_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int flags, int value, Hash modelHash, bool p7, bool p8) { return YimMenu::NativeInvoker::Invoke<3608, Object>(pickupHash, posX, posY, posZ, flags, value, modelHash, p7, p8); }
	FORCEINLINE Object CREATE_NON_NETWORKED_AMBIENT_PICKUP(Hash pickupHash, float posX, float posY, float posZ, int flags, int value, Hash modelHash, bool p7, bool p8) { return YimMenu::NativeInvoker::Invoke<3609, Object>(pickupHash, posX, posY, posZ, flags, value, modelHash, p7, p8); }
	FORCEINLINE void BLOCK_PLAYERS_FOR_AMBIENT_PICKUP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3610, void>(p0, p1); }
	FORCEINLINE Object CREATE_PORTABLE_PICKUP(Hash pickupHash, float x, float y, float z, bool placeOnGround, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<3611, Object>(pickupHash, x, y, z, placeOnGround, modelHash); }
	FORCEINLINE Object CREATE_NON_NETWORKED_PORTABLE_PICKUP(Hash pickupHash, float x, float y, float z, bool placeOnGround, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<3612, Object>(pickupHash, x, y, z, placeOnGround, modelHash); }
	FORCEINLINE void ATTACH_PORTABLE_PICKUP_TO_PED(Object pickupObject, Ped ped) { return YimMenu::NativeInvoker::Invoke<3613, void>(pickupObject, ped); }
	FORCEINLINE void DETACH_PORTABLE_PICKUP_FROM_PED(Object pickupObject) { return YimMenu::NativeInvoker::Invoke<3614, void>(pickupObject); }
	FORCEINLINE void FORCE_PORTABLE_PICKUP_LAST_ACCESSIBLE_POSITION_SETTING(Object object) { return YimMenu::NativeInvoker::Invoke<3615, void>(object); }
	FORCEINLINE void HIDE_PORTABLE_PICKUP_WHEN_DETACHED(Object pickupObject, bool toggle) { return YimMenu::NativeInvoker::Invoke<3616, void>(pickupObject, toggle); }
	FORCEINLINE void SET_MAX_NUM_PORTABLE_PICKUPS_CARRIED_BY_PLAYER(Hash modelHash, int number) { return YimMenu::NativeInvoker::Invoke<3617, void>(modelHash, number); }
	FORCEINLINE void SET_LOCAL_PLAYER_CAN_COLLECT_PORTABLE_PICKUPS(bool toggle) { return YimMenu::NativeInvoker::Invoke<3618, void>(toggle); }
	FORCEINLINE Vector3 GET_SAFE_PICKUP_COORDS(float x, float y, float z, float p3, float p4) { return YimMenu::NativeInvoker::Invoke<3619, Vector3>(x, y, z, p3, p4); }
	FORCEINLINE void ADD_EXTENDED_PICKUP_PROBE_AREA(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<3620, void>(x, y, z, radius); }
	FORCEINLINE void CLEAR_EXTENDED_PICKUP_PROBE_AREAS() { return YimMenu::NativeInvoker::Invoke<3621, void>(); }
	FORCEINLINE Vector3 GET_PICKUP_COORDS(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3622, Vector3>(pickup); }
	FORCEINLINE void SUPPRESS_PICKUP_SOUND_FOR_PICKUP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3623, void>(p0, p1); }
	FORCEINLINE void REMOVE_ALL_PICKUPS_OF_TYPE(Hash pickupHash) { return YimMenu::NativeInvoker::Invoke<3624, void>(pickupHash); }
	FORCEINLINE bool HAS_PICKUP_BEEN_COLLECTED(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3625, bool>(pickup); }
	FORCEINLINE void REMOVE_PICKUP(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3626, void>(pickup); }
	FORCEINLINE void CREATE_MONEY_PICKUPS(float x, float y, float z, int value, int amount, Hash model) { return YimMenu::NativeInvoker::Invoke<3627, void>(x, y, z, value, amount, model); }
	FORCEINLINE bool DOES_PICKUP_EXIST(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3628, bool>(pickup); }
	FORCEINLINE bool DOES_PICKUP_OBJECT_EXIST(Object pickupObject) { return YimMenu::NativeInvoker::Invoke<3629, bool>(pickupObject); }
	FORCEINLINE Object GET_PICKUP_OBJECT(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3630, Object>(pickup); }
	FORCEINLINE bool IS_OBJECT_A_PICKUP(Object object) { return YimMenu::NativeInvoker::Invoke<3631, bool>(object); }
	FORCEINLINE bool IS_OBJECT_A_PORTABLE_PICKUP(Object object) { return YimMenu::NativeInvoker::Invoke<3632, bool>(object); }
	FORCEINLINE bool DOES_PICKUP_OF_TYPE_EXIST_IN_AREA(Hash pickupHash, float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<3633, bool>(pickupHash, x, y, z, radius); }
	FORCEINLINE void SET_PICKUP_REGENERATION_TIME(Pickup pickup, int duration) { return YimMenu::NativeInvoker::Invoke<3634, void>(pickup, duration); }
	FORCEINLINE void FORCE_PICKUP_REGENERATE(Any p0) { return YimMenu::NativeInvoker::Invoke<3635, void>(p0); }
	FORCEINLINE void SET_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_OF_TYPE(Player player, Hash pickupHash, bool toggle) { return YimMenu::NativeInvoker::Invoke<3636, void>(player, pickupHash, toggle); }
	FORCEINLINE void SET_LOCAL_PLAYER_PERMITTED_TO_COLLECT_PICKUPS_WITH_MODEL(Hash modelHash, bool toggle) { return YimMenu::NativeInvoker::Invoke<3637, void>(modelHash, toggle); }
	FORCEINLINE void ALLOW_ALL_PLAYERS_TO_COLLECT_PICKUPS_OF_TYPE(Hash pickupHash) { return YimMenu::NativeInvoker::Invoke<3638, void>(pickupHash); }
	FORCEINLINE void SET_TEAM_PICKUP_OBJECT(Object object, Any p1, bool p2) { return YimMenu::NativeInvoker::Invoke<3639, void>(object, p1, p2); }
	FORCEINLINE void PREVENT_COLLECTION_OF_PORTABLE_PICKUP(Object object, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<3640, void>(object, p1, p2); }
	FORCEINLINE void SET_PICKUP_OBJECT_GLOW_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3641, void>(pickup, toggle); }
	FORCEINLINE void SET_PICKUP_GLOW_OFFSET(Pickup pickup, float p1) { return YimMenu::NativeInvoker::Invoke<3642, void>(pickup, p1); }
	FORCEINLINE void SET_PICKUP_OBJECT_GLOW_OFFSET(Pickup pickup, float p1, bool p2) { return YimMenu::NativeInvoker::Invoke<3643, void>(pickup, p1, p2); }
	FORCEINLINE void SET_OBJECT_GLOW_IN_SAME_TEAM(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3644, void>(pickup); }
	FORCEINLINE void SET_PICKUP_OBJECT_ARROW_MARKER(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3645, void>(pickup, toggle); }
	FORCEINLINE void ALLOW_PICKUP_ARROW_MARKER_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3646, void>(pickup, toggle); }
	FORCEINLINE int GET_DEFAULT_AMMO_FOR_WEAPON_PICKUP(Hash pickupHash) { return YimMenu::NativeInvoker::Invoke<3647, int>(pickupHash); }
	FORCEINLINE void SET_PICKUP_GENERATION_RANGE_MULTIPLIER(float multiplier) { return YimMenu::NativeInvoker::Invoke<3648, void>(multiplier); }
	FORCEINLINE float GET_PICKUP_GENERATION_RANGE_MULTIPLIER() { return YimMenu::NativeInvoker::Invoke<3649, float>(); }
	FORCEINLINE void SET_ONLY_ALLOW_AMMO_COLLECTION_WHEN_LOW(bool p0) { return YimMenu::NativeInvoker::Invoke<3650, void>(p0); }
	FORCEINLINE void SET_PICKUP_UNCOLLECTABLE(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3651, void>(pickup, toggle); }
	FORCEINLINE void SET_PICKUP_TRANSPARENT_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3652, void>(pickup, toggle); }
	FORCEINLINE void SET_PICKUP_HIDDEN_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3653, void>(pickup, toggle); }
	FORCEINLINE void SET_PICKUP_OBJECT_TRANSPARENT_WHEN_UNCOLLECTABLE(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3654, void>(pickup, toggle); }
	FORCEINLINE void SET_PICKUP_OBJECT_ALPHA_WHEN_TRANSPARENT(int p0) { return YimMenu::NativeInvoker::Invoke<3655, void>(p0); }
	FORCEINLINE void SET_PORTABLE_PICKUP_PERSIST(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3656, void>(pickup, toggle); }
	FORCEINLINE void ALLOW_PORTABLE_PICKUP_TO_MIGRATE_TO_NON_PARTICIPANTS(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3657, void>(pickup, toggle); }
	FORCEINLINE void FORCE_ACTIVATE_PHYSICS_ON_UNFIXED_PICKUP(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3658, void>(pickup, toggle); }
	FORCEINLINE void ALLOW_PICKUP_BY_NONE_PARTICIPANT(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3659, void>(pickup, toggle); }
	FORCEINLINE void SUPPRESS_PICKUP_REWARD_TYPE(int rewardType, bool suppress) { return YimMenu::NativeInvoker::Invoke<3660, void>(rewardType, suppress); }
	FORCEINLINE void CLEAR_ALL_PICKUP_REWARD_TYPE_SUPPRESSION() { return YimMenu::NativeInvoker::Invoke<3661, void>(); }
	FORCEINLINE void CLEAR_PICKUP_REWARD_TYPE_SUPPRESSION(int rewardType) { return YimMenu::NativeInvoker::Invoke<3662, void>(rewardType); }
	FORCEINLINE void RENDER_FAKE_PICKUP_GLOW(float x, float y, float z, int colorIndex) { return YimMenu::NativeInvoker::Invoke<3663, void>(x, y, z, colorIndex); }
	FORCEINLINE void SET_PICKUP_OBJECT_COLLECTABLE_IN_VEHICLE(Pickup pickup) { return YimMenu::NativeInvoker::Invoke<3664, void>(pickup); }
	FORCEINLINE void SET_PICKUP_TRACK_DAMAGE_EVENTS(Pickup pickup, bool toggle) { return YimMenu::NativeInvoker::Invoke<3665, void>(pickup, toggle); }
	FORCEINLINE void SET_ENTITY_FLAG_SUPPRESS_SHADOW(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<3666, void>(entity, toggle); }
	FORCEINLINE void SET_ENTITY_FLAG_RENDER_SMALL_SHADOW(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3667, void>(object, toggle); }
	FORCEINLINE Hash GET_WEAPON_TYPE_FROM_PICKUP_TYPE(Hash pickupHash) { return YimMenu::NativeInvoker::Invoke<3668, Hash>(pickupHash); }
	FORCEINLINE Hash GET_PICKUP_TYPE_FROM_WEAPON_HASH(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<3669, Hash>(weaponHash); }
	FORCEINLINE bool IS_PICKUP_WEAPON_OBJECT_VALID(Object object) { return YimMenu::NativeInvoker::Invoke<3670, bool>(object); }
	FORCEINLINE int GET_OBJECT_TINT_INDEX(Object object) { return YimMenu::NativeInvoker::Invoke<3671, int>(object); }
	FORCEINLINE void SET_OBJECT_TINT_INDEX(Object object, int textureVariation) { return YimMenu::NativeInvoker::Invoke<3672, void>(object, textureVariation); }
	FORCEINLINE bool SET_TINT_INDEX_CLOSEST_BUILDING_OF_TYPE(float x, float y, float z, float radius, Hash modelHash, int textureVariation) { return YimMenu::NativeInvoker::Invoke<3673, bool>(x, y, z, radius, modelHash, textureVariation); }
	FORCEINLINE void SET_PROP_TINT_INDEX(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3674, void>(p0, p1); }
	FORCEINLINE bool SET_PROP_LIGHT_COLOR(Object object, bool p1, int r, int g, int b) { return YimMenu::NativeInvoker::Invoke<3675, bool>(object, p1, r, g, b); }
	FORCEINLINE bool IS_PROP_LIGHT_OVERRIDEN(Object object) { return YimMenu::NativeInvoker::Invoke<3676, bool>(object); }
	FORCEINLINE void SET_OBJECT_IS_VISIBLE_IN_MIRRORS(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3677, void>(object, toggle); }
	FORCEINLINE void SET_OBJECT_SPEED_BOOST_AMOUNT(Object object, Any p1) { return YimMenu::NativeInvoker::Invoke<3678, void>(object, p1); }
	FORCEINLINE void SET_OBJECT_SPEED_BOOST_DURATION(Object object, float duration) { return YimMenu::NativeInvoker::Invoke<3679, void>(object, duration); }
	FORCEINLINE Hash CONVERT_OLD_PICKUP_TYPE_TO_NEW(Hash pickupHash) { return YimMenu::NativeInvoker::Invoke<3680, Hash>(pickupHash); }
	FORCEINLINE void SET_FORCE_OBJECT_THIS_FRAME(float x, float y, float z, float p3) { return YimMenu::NativeInvoker::Invoke<3681, void>(x, y, z, p3); }
	FORCEINLINE void ONLY_CLEAN_UP_OBJECT_WHEN_OUT_OF_RANGE(Object object) { return YimMenu::NativeInvoker::Invoke<3682, void>(object); }
	FORCEINLINE void SET_DISABLE_COLLISIONS_BETWEEN_CARS_AND_CAR_PARACHUTE(Any p0) { return YimMenu::NativeInvoker::Invoke<3683, void>(p0); }
	FORCEINLINE void SET_PROJECTILES_SHOULD_EXPLODE_ON_CONTACT(Entity entity, Any p1) { return YimMenu::NativeInvoker::Invoke<3684, void>(entity, p1); }
	FORCEINLINE void SET_DRIVE_ARTICULATED_JOINT(Object object, bool toggle, int p2) { return YimMenu::NativeInvoker::Invoke<3685, void>(object, toggle, p2); }
	FORCEINLINE void SET_DRIVE_ARTICULATED_JOINT_WITH_INFLICTOR(Object object, bool toggle, int p2, Ped ped) { return YimMenu::NativeInvoker::Invoke<3686, void>(object, toggle, p2, ped); }
	FORCEINLINE void SET_OBJECT_IS_A_PRESSURE_PLATE(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3687, void>(object, toggle); }
	FORCEINLINE void SET_WEAPON_IMPACTS_APPLY_GREATER_FORCE(Object object, bool p1) { return YimMenu::NativeInvoker::Invoke<3688, void>(object, p1); }
	FORCEINLINE bool GET_IS_ARTICULATED_JOINT_AT_MIN_ANGLE(Object object, Any p1) { return YimMenu::NativeInvoker::Invoke<3689, bool>(object, p1); }
	FORCEINLINE bool GET_IS_ARTICULATED_JOINT_AT_MAX_ANGLE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3690, bool>(p0, p1); }
	FORCEINLINE void SET_IS_OBJECT_ARTICULATED(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3691, void>(object, toggle); }
	FORCEINLINE void SET_IS_OBJECT_BALL(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<3692, void>(object, toggle); }
}

namespace PAD
{
	FORCEINLINE bool IS_CONTROL_ENABLED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3693, bool>(control, action); }
	FORCEINLINE bool IS_CONTROL_PRESSED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3694, bool>(control, action); }
	FORCEINLINE bool IS_CONTROL_RELEASED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3695, bool>(control, action); }
	FORCEINLINE bool IS_CONTROL_JUST_PRESSED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3696, bool>(control, action); }
	FORCEINLINE bool IS_CONTROL_JUST_RELEASED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3697, bool>(control, action); }
	FORCEINLINE int GET_CONTROL_VALUE(int control, int action) { return YimMenu::NativeInvoker::Invoke<3698, int>(control, action); }
	FORCEINLINE float GET_CONTROL_NORMAL(int control, int action) { return YimMenu::NativeInvoker::Invoke<3699, float>(control, action); }
	FORCEINLINE void SET_USE_ADJUSTED_MOUSE_COORDS(bool toggle) { return YimMenu::NativeInvoker::Invoke<3700, void>(toggle); }
	FORCEINLINE float GET_CONTROL_UNBOUND_NORMAL(int control, int action) { return YimMenu::NativeInvoker::Invoke<3701, float>(control, action); }
	FORCEINLINE bool SET_CONTROL_VALUE_NEXT_FRAME(int control, int action, float value) { return YimMenu::NativeInvoker::Invoke<3702, bool>(control, action, value); }
	FORCEINLINE bool IS_DISABLED_CONTROL_PRESSED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3703, bool>(control, action); }
	FORCEINLINE bool IS_DISABLED_CONTROL_RELEASED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3704, bool>(control, action); }
	FORCEINLINE bool IS_DISABLED_CONTROL_JUST_PRESSED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3705, bool>(control, action); }
	FORCEINLINE bool IS_DISABLED_CONTROL_JUST_RELEASED(int control, int action) { return YimMenu::NativeInvoker::Invoke<3706, bool>(control, action); }
	FORCEINLINE float GET_DISABLED_CONTROL_NORMAL(int control, int action) { return YimMenu::NativeInvoker::Invoke<3707, float>(control, action); }
	FORCEINLINE float GET_DISABLED_CONTROL_UNBOUND_NORMAL(int control, int action) { return YimMenu::NativeInvoker::Invoke<3708, float>(control, action); }
	FORCEINLINE int GET_CONTROL_HOW_LONG_AGO(int control) { return YimMenu::NativeInvoker::Invoke<3709, int>(control); }
	FORCEINLINE bool IS_USING_KEYBOARD_AND_MOUSE(int control) { return YimMenu::NativeInvoker::Invoke<3710, bool>(control); }
	FORCEINLINE bool IS_USING_CURSOR(int control) { return YimMenu::NativeInvoker::Invoke<3711, bool>(control); }
	FORCEINLINE bool SET_CURSOR_POSITION(float x, float y) { return YimMenu::NativeInvoker::Invoke<3712, bool>(x, y); }
	FORCEINLINE bool IS_USING_REMOTE_PLAY(int control) { return YimMenu::NativeInvoker::Invoke<3713, bool>(control); }
	FORCEINLINE bool HAVE_CONTROLS_CHANGED(int control) { return YimMenu::NativeInvoker::Invoke<3714, bool>(control); }
	FORCEINLINE const char* GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(int control, int action, bool allowXOSwap) { return YimMenu::NativeInvoker::Invoke<3715, const char*>(control, action, allowXOSwap); }
	FORCEINLINE const char* GET_CONTROL_GROUP_INSTRUCTIONAL_BUTTONS_STRING(int control, int controlGroup, bool allowXOSwap) { return YimMenu::NativeInvoker::Invoke<3716, const char*>(control, controlGroup, allowXOSwap); }
	FORCEINLINE void SET_CONTROL_LIGHT_EFFECT_COLOR(int control, int red, int green, int blue) { return YimMenu::NativeInvoker::Invoke<3717, void>(control, red, green, blue); }
	FORCEINLINE void CLEAR_CONTROL_LIGHT_EFFECT(int control) { return YimMenu::NativeInvoker::Invoke<3718, void>(control); }
	FORCEINLINE void SET_CONTROL_SHAKE(int control, int duration, int frequency) { return YimMenu::NativeInvoker::Invoke<3719, void>(control, duration, frequency); }
	FORCEINLINE void SET_CONTROL_TRIGGER_SHAKE(int control, int leftDuration, int leftFrequency, int rightDuration, int rightFrequency) { return YimMenu::NativeInvoker::Invoke<3720, void>(control, leftDuration, leftFrequency, rightDuration, rightFrequency); }
	FORCEINLINE void STOP_CONTROL_SHAKE(int control) { return YimMenu::NativeInvoker::Invoke<3721, void>(control); }
	FORCEINLINE void SET_CONTROL_SHAKE_SUPPRESSED_ID(int control, int uniqueId) { return YimMenu::NativeInvoker::Invoke<3722, void>(control, uniqueId); }
	FORCEINLINE void CLEAR_CONTROL_SHAKE_SUPPRESSED_ID(int control) { return YimMenu::NativeInvoker::Invoke<3723, void>(control); }
	FORCEINLINE bool IS_LOOK_INVERTED() { return YimMenu::NativeInvoker::Invoke<3724, bool>(); }
	FORCEINLINE bool IS_MOUSE_LOOK_INVERTED() { return YimMenu::NativeInvoker::Invoke<3725, bool>(); }
	FORCEINLINE int GET_LOCAL_PLAYER_AIM_STATE() { return YimMenu::NativeInvoker::Invoke<3726, int>(); }
	FORCEINLINE int GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE() { return YimMenu::NativeInvoker::Invoke<3727, int>(); }
	FORCEINLINE bool GET_IS_USING_ALTERNATE_HANDBRAKE() { return YimMenu::NativeInvoker::Invoke<3728, bool>(); }
	FORCEINLINE bool GET_IS_USING_ALTERNATE_DRIVEBY() { return YimMenu::NativeInvoker::Invoke<3729, bool>(); }
	FORCEINLINE bool GET_ALLOW_MOVEMENT_WHILE_ZOOMED() { return YimMenu::NativeInvoker::Invoke<3730, bool>(); }
	FORCEINLINE void SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(bool toggle) { return YimMenu::NativeInvoker::Invoke<3731, void>(toggle); }
	FORCEINLINE void SET_INPUT_EXCLUSIVE(int control, int action) { return YimMenu::NativeInvoker::Invoke<3732, void>(control, action); }
	FORCEINLINE void DISABLE_CONTROL_ACTION(int control, int action, bool disableRelatedActions) { return YimMenu::NativeInvoker::Invoke<3733, void>(control, action, disableRelatedActions); }
	FORCEINLINE void ENABLE_CONTROL_ACTION(int control, int action, bool enableRelatedActions) { return YimMenu::NativeInvoker::Invoke<3734, void>(control, action, enableRelatedActions); }
	FORCEINLINE void DISABLE_ALL_CONTROL_ACTIONS(int control) { return YimMenu::NativeInvoker::Invoke<3735, void>(control); }
	FORCEINLINE void ENABLE_ALL_CONTROL_ACTIONS(int control) { return YimMenu::NativeInvoker::Invoke<3736, void>(control); }
	FORCEINLINE bool INIT_PC_SCRIPTED_CONTROLS(const char* schemeName) { return YimMenu::NativeInvoker::Invoke<3737, bool>(schemeName); }
	FORCEINLINE bool SWITCH_PC_SCRIPTED_CONTROLS(const char* schemeName) { return YimMenu::NativeInvoker::Invoke<3738, bool>(schemeName); }
	FORCEINLINE void SHUTDOWN_PC_SCRIPTED_CONTROLS() { return YimMenu::NativeInvoker::Invoke<3739, void>(); }
	FORCEINLINE void ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT(int control) { return YimMenu::NativeInvoker::Invoke<3740, void>(control); }
}

namespace PATHFIND
{
	FORCEINLINE void SET_ROADS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool nodeEnabled, bool unknown2) { return YimMenu::NativeInvoker::Invoke<3741, void>(x1, y1, z1, x2, y2, z2, nodeEnabled, unknown2); }
	FORCEINLINE void SET_ROADS_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, bool unknown1, bool unknown2, bool unknown3) { return YimMenu::NativeInvoker::Invoke<3742, void>(x1, y1, z1, x2, y2, z2, width, unknown1, unknown2, unknown3); }
	FORCEINLINE void SET_PED_PATHS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, Any p7) { return YimMenu::NativeInvoker::Invoke<3743, void>(x1, y1, z1, x2, y2, z2, p6, p7); }
	FORCEINLINE bool GET_SAFE_COORD_FOR_PED(float x, float y, float z, bool onGround, Vector3* outPosition, int flags) { return YimMenu::NativeInvoker::Invoke<3744, bool>(x, y, z, onGround, outPosition, flags); }
	FORCEINLINE bool GET_CLOSEST_VEHICLE_NODE(float x, float y, float z, Vector3* outPosition, int nodeFlags, float p5, float p6) { return YimMenu::NativeInvoker::Invoke<3745, bool>(x, y, z, outPosition, nodeFlags, p5, p6); }
	FORCEINLINE bool GET_CLOSEST_MAJOR_VEHICLE_NODE(float x, float y, float z, Vector3* outPosition, float unknown1, float unknown2) { return YimMenu::NativeInvoker::Invoke<3746, bool>(x, y, z, outPosition, unknown1, unknown2); }
	FORCEINLINE bool GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(float x, float y, float z, Vector3* outPosition, float* outHeading, int nodeType, float p6, float p7) { return YimMenu::NativeInvoker::Invoke<3747, bool>(x, y, z, outPosition, outHeading, nodeType, p6, p7); }
	FORCEINLINE bool GET_NTH_CLOSEST_VEHICLE_NODE(float x, float y, float z, int nthClosest, Vector3* outPosition, int nodeFlags, float unknown1, float unknown2) { return YimMenu::NativeInvoker::Invoke<3748, bool>(x, y, z, nthClosest, outPosition, nodeFlags, unknown1, unknown2); }
	FORCEINLINE int GET_NTH_CLOSEST_VEHICLE_NODE_ID(float x, float y, float z, int nth, int nodeFlags, float p5, float p6) { return YimMenu::NativeInvoker::Invoke<3749, int>(x, y, z, nth, nodeFlags, p5, p6); }
	FORCEINLINE bool GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(float x, float y, float z, int nthClosest, Vector3* outPosition, float* outHeading, int* outNumLanes, int nodeFlags, float unknown3, float unknown4) { return YimMenu::NativeInvoker::Invoke<3750, bool>(x, y, z, nthClosest, outPosition, outHeading, outNumLanes, nodeFlags, unknown3, unknown4); }
	FORCEINLINE int GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(float x, float y, float z, int nthClosest, Vector3* outPosition, float* outHeading, int nodeFlags, float p7, float p8) { return YimMenu::NativeInvoker::Invoke<3751, int>(x, y, z, nthClosest, outPosition, outHeading, nodeFlags, p7, p8); }
	FORCEINLINE bool GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(float x, float y, float z, float desiredX, float desiredY, float desiredZ, int nthClosest, Vector3* outPosition, float* outHeading, int nodeFlags, float p10, float p11) { return YimMenu::NativeInvoker::Invoke<3752, bool>(x, y, z, desiredX, desiredY, desiredZ, nthClosest, outPosition, outHeading, nodeFlags, p10, p11); }
	FORCEINLINE bool GET_VEHICLE_NODE_PROPERTIES(float x, float y, float z, int* density, int* flags) { return YimMenu::NativeInvoker::Invoke<3753, bool>(x, y, z, density, flags); }
	FORCEINLINE bool IS_VEHICLE_NODE_ID_VALID(int vehicleNodeId) { return YimMenu::NativeInvoker::Invoke<3754, bool>(vehicleNodeId); }
	FORCEINLINE void GET_VEHICLE_NODE_POSITION(int nodeId, Vector3* outPosition) { return YimMenu::NativeInvoker::Invoke<3755, void>(nodeId, outPosition); }
	FORCEINLINE bool GET_VEHICLE_NODE_IS_GPS_ALLOWED(int nodeID) { return YimMenu::NativeInvoker::Invoke<3756, bool>(nodeID); }
	FORCEINLINE bool GET_VEHICLE_NODE_IS_SWITCHED_OFF(int nodeID) { return YimMenu::NativeInvoker::Invoke<3757, bool>(nodeID); }
	FORCEINLINE bool GET_CLOSEST_ROAD(float x, float y, float z, float p3, int p4, Vector3* p5, Vector3* p6, Any* p7, Any* p8, float* p9, bool p10) { return YimMenu::NativeInvoker::Invoke<3758, bool>(x, y, z, p3, p4, p5, p6, p7, p8, p9, p10); }
	FORCEINLINE bool LOAD_ALL_PATH_NODES(bool set) { return YimMenu::NativeInvoker::Invoke<3759, bool>(set); }
	FORCEINLINE void SET_ALLOW_STREAM_PROLOGUE_NODES(bool toggle) { return YimMenu::NativeInvoker::Invoke<3760, void>(toggle); }
	FORCEINLINE void SET_ALLOW_STREAM_HEIST_ISLAND_NODES(int type) { return YimMenu::NativeInvoker::Invoke<3761, void>(type); }
	FORCEINLINE bool ARE_NODES_LOADED_FOR_AREA(float x1, float y1, float x2, float y2) { return YimMenu::NativeInvoker::Invoke<3762, bool>(x1, y1, x2, y2); }
	FORCEINLINE bool REQUEST_PATH_NODES_IN_AREA_THIS_FRAME(float x1, float y1, float x2, float y2) { return YimMenu::NativeInvoker::Invoke<3763, bool>(x1, y1, x2, y2); }
	FORCEINLINE void SET_ROADS_BACK_TO_ORIGINAL(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return YimMenu::NativeInvoker::Invoke<3764, void>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, Any p7) { return YimMenu::NativeInvoker::Invoke<3765, void>(x1, y1, z1, x2, y2, z2, width, p7); }
	FORCEINLINE void SET_AMBIENT_PED_RANGE_MULTIPLIER_THIS_FRAME(float multiplier) { return YimMenu::NativeInvoker::Invoke<3766, void>(multiplier); }
	FORCEINLINE void ADJUST_AMBIENT_PED_SPAWN_DENSITIES_THIS_FRAME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<3767, void>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void SET_PED_PATHS_BACK_TO_ORIGINAL(float x1, float y1, float z1, float x2, float y2, float z2, Any p6) { return YimMenu::NativeInvoker::Invoke<3768, void>(x1, y1, z1, x2, y2, z2, p6); }
	FORCEINLINE bool GET_RANDOM_VEHICLE_NODE(float x, float y, float z, float radius, bool p4, bool p5, bool p6, Vector3* outPosition, int* nodeId) { return YimMenu::NativeInvoker::Invoke<3769, bool>(x, y, z, radius, p4, p5, p6, outPosition, nodeId); }
	FORCEINLINE void GET_STREET_NAME_AT_COORD(float x, float y, float z, Hash* streetName, Hash* crossingRoad) { return YimMenu::NativeInvoker::Invoke<3770, void>(x, y, z, streetName, crossingRoad); }
	FORCEINLINE int GENERATE_DIRECTIONS_TO_COORD(float x, float y, float z, bool p3, int* direction, float* p5, float* distToNxJunction) { return YimMenu::NativeInvoker::Invoke<3771, int>(x, y, z, p3, direction, p5, distToNxJunction); }
	FORCEINLINE void SET_IGNORE_NO_GPS_FLAG(bool toggle) { return YimMenu::NativeInvoker::Invoke<3772, void>(toggle); }
	FORCEINLINE void SET_IGNORE_NO_GPS_FLAG_UNTIL_FIRST_NORMAL_NODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<3773, void>(toggle); }
	FORCEINLINE void SET_GPS_DISABLED_ZONE(float x1, float y1, float z1, float x2, float y2, float z3) { return YimMenu::NativeInvoker::Invoke<3774, void>(x1, y1, z1, x2, y2, z3); }
	FORCEINLINE int GET_GPS_BLIP_ROUTE_LENGTH() { return YimMenu::NativeInvoker::Invoke<3775, int>(); }
	FORCEINLINE bool GET_POS_ALONG_GPS_TYPE_ROUTE(Vector3* result, bool p1, float p2, int p3) { return YimMenu::NativeInvoker::Invoke<3776, bool>(result, p1, p2, p3); }
	FORCEINLINE bool GET_GPS_BLIP_ROUTE_FOUND() { return YimMenu::NativeInvoker::Invoke<3777, bool>(); }
	FORCEINLINE bool GET_ROAD_BOUNDARY_USING_HEADING(float x, float y, float z, float heading, Vector3* outPosition) { return YimMenu::NativeInvoker::Invoke<3778, bool>(x, y, z, heading, outPosition); }
	FORCEINLINE bool GET_POSITION_BY_SIDE_OF_ROAD(float x, float y, float z, int p3, Vector3* outPosition) { return YimMenu::NativeInvoker::Invoke<3779, bool>(x, y, z, p3, outPosition); }
	FORCEINLINE bool IS_POINT_ON_ROAD(float x, float y, float z, Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<3780, bool>(x, y, z, vehicle); }
	FORCEINLINE int GET_NEXT_GPS_DISABLED_ZONE_INDEX() { return YimMenu::NativeInvoker::Invoke<3781, int>(); }
	FORCEINLINE void SET_GPS_DISABLED_ZONE_AT_INDEX(float x1, float y1, float z1, float x2, float y2, float z2, int index) { return YimMenu::NativeInvoker::Invoke<3782, void>(x1, y1, z1, x2, y2, z2, index); }
	FORCEINLINE void CLEAR_GPS_DISABLED_ZONE_AT_INDEX(int index) { return YimMenu::NativeInvoker::Invoke<3783, void>(index); }
	FORCEINLINE void ADD_NAVMESH_REQUIRED_REGION(float x, float y, float radius) { return YimMenu::NativeInvoker::Invoke<3784, void>(x, y, radius); }
	FORCEINLINE void REMOVE_NAVMESH_REQUIRED_REGIONS() { return YimMenu::NativeInvoker::Invoke<3785, void>(); }
	FORCEINLINE bool IS_NAVMESH_REQUIRED_REGION_IN_USE() { return YimMenu::NativeInvoker::Invoke<3786, bool>(); }
	FORCEINLINE void DISABLE_NAVMESH_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool toggle) { return YimMenu::NativeInvoker::Invoke<3787, void>(x1, y1, z1, x2, y2, z2, toggle); }
	FORCEINLINE bool ARE_ALL_NAVMESH_REGIONS_LOADED() { return YimMenu::NativeInvoker::Invoke<3788, bool>(); }
	FORCEINLINE bool IS_NAVMESH_LOADED_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<3789, bool>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE int GET_NUM_NAVMESHES_EXISTING_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<3790, int>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE int ADD_NAVMESH_BLOCKING_OBJECT(float p0, float p1, float p2, float p3, float p4, float p5, float p6, bool p7, Any p8) { return YimMenu::NativeInvoker::Invoke<3791, int>(p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void UPDATE_NAVMESH_BLOCKING_OBJECT(Any p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, Any p8) { return YimMenu::NativeInvoker::Invoke<3792, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void REMOVE_NAVMESH_BLOCKING_OBJECT(Any p0) { return YimMenu::NativeInvoker::Invoke<3793, void>(p0); }
	FORCEINLINE bool DOES_NAVMESH_BLOCKING_OBJECT_EXIST(Any p0) { return YimMenu::NativeInvoker::Invoke<3794, bool>(p0); }
	FORCEINLINE float GET_APPROX_HEIGHT_FOR_POINT(float x, float y) { return YimMenu::NativeInvoker::Invoke<3795, float>(x, y); }
	FORCEINLINE float GET_APPROX_HEIGHT_FOR_AREA(float x1, float y1, float x2, float y2) { return YimMenu::NativeInvoker::Invoke<3796, float>(x1, y1, x2, y2); }
	FORCEINLINE float GET_APPROX_FLOOR_FOR_POINT(float x, float y) { return YimMenu::NativeInvoker::Invoke<3797, float>(x, y); }
	FORCEINLINE float GET_APPROX_FLOOR_FOR_AREA(float x1, float y1, float x2, float y2) { return YimMenu::NativeInvoker::Invoke<3798, float>(x1, y1, x2, y2); }
	FORCEINLINE float CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<3799, float>(x1, y1, z1, x2, y2, z2); }
}

namespace PED
{
	FORCEINLINE Ped CREATE_PED(int pedType, Hash modelHash, float x, float y, float z, float heading, bool isNetwork, bool bScriptHostPed) { return YimMenu::NativeInvoker::Invoke<3800, Ped>(pedType, modelHash, x, y, z, heading, isNetwork, bScriptHostPed); }
	FORCEINLINE void DELETE_PED(Ped* ped) { return YimMenu::NativeInvoker::Invoke<3801, void>(ped); }
	FORCEINLINE Ped CLONE_PED(Ped ped, bool isNetwork, bool bScriptHostPed, bool copyHeadBlendFlag) { return YimMenu::NativeInvoker::Invoke<3802, Ped>(ped, isNetwork, bScriptHostPed, copyHeadBlendFlag); }
	FORCEINLINE Ped CLONE_PED_ALT(Ped ped, bool isNetwork, bool bScriptHostPed, bool copyHeadBlendFlag, bool p4) { return YimMenu::NativeInvoker::Invoke<3803, Ped>(ped, isNetwork, bScriptHostPed, copyHeadBlendFlag, p4); }
	FORCEINLINE void CLONE_PED_TO_TARGET(Ped ped, Ped targetPed) { return YimMenu::NativeInvoker::Invoke<3804, void>(ped, targetPed); }
	FORCEINLINE void CLONE_PED_TO_TARGET_ALT(Ped ped, Ped targetPed, bool p2) { return YimMenu::NativeInvoker::Invoke<3805, void>(ped, targetPed, p2); }
	FORCEINLINE bool IS_PED_IN_VEHICLE(Ped ped, Vehicle vehicle, bool atGetIn) { return YimMenu::NativeInvoker::Invoke<3806, bool>(ped, vehicle, atGetIn); }
	FORCEINLINE bool IS_PED_IN_MODEL(Ped ped, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<3807, bool>(ped, modelHash); }
	FORCEINLINE bool IS_PED_IN_ANY_VEHICLE(Ped ped, bool atGetIn) { return YimMenu::NativeInvoker::Invoke<3808, bool>(ped, atGetIn); }
	FORCEINLINE bool IS_COP_PED_IN_AREA_3D(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<3809, bool>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE bool IS_PED_INJURED(Ped ped) { return YimMenu::NativeInvoker::Invoke<3810, bool>(ped); }
	FORCEINLINE bool IS_PED_HURT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3811, bool>(ped); }
	FORCEINLINE bool IS_PED_FATALLY_INJURED(Ped ped) { return YimMenu::NativeInvoker::Invoke<3812, bool>(ped); }
	FORCEINLINE bool IS_PED_DEAD_OR_DYING(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<3813, bool>(ped, p1); }
	FORCEINLINE bool IS_CONVERSATION_PED_DEAD(Ped ped) { return YimMenu::NativeInvoker::Invoke<3814, bool>(ped); }
	FORCEINLINE bool IS_PED_AIMING_FROM_COVER(Ped ped) { return YimMenu::NativeInvoker::Invoke<3815, bool>(ped); }
	FORCEINLINE bool IS_PED_RELOADING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3816, bool>(ped); }
	FORCEINLINE bool IS_PED_A_PLAYER(Ped ped) { return YimMenu::NativeInvoker::Invoke<3817, bool>(ped); }
	FORCEINLINE Ped CREATE_PED_INSIDE_VEHICLE(Vehicle vehicle, int pedType, Hash modelHash, int seat, bool isNetwork, bool bScriptHostPed) { return YimMenu::NativeInvoker::Invoke<3818, Ped>(vehicle, pedType, modelHash, seat, isNetwork, bScriptHostPed); }
	FORCEINLINE void SET_PED_DESIRED_HEADING(Ped ped, float heading) { return YimMenu::NativeInvoker::Invoke<3819, void>(ped, heading); }
	FORCEINLINE void FORCE_ALL_HEADING_VALUES_TO_ALIGN(Ped ped) { return YimMenu::NativeInvoker::Invoke<3820, void>(ped); }
	FORCEINLINE bool IS_PED_FACING_PED(Ped ped, Ped otherPed, float angle) { return YimMenu::NativeInvoker::Invoke<3821, bool>(ped, otherPed, angle); }
	FORCEINLINE bool IS_PED_IN_MELEE_COMBAT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3822, bool>(ped); }
	FORCEINLINE bool IS_PED_STOPPED(Ped ped) { return YimMenu::NativeInvoker::Invoke<3823, bool>(ped); }
	FORCEINLINE bool IS_PED_SHOOTING_IN_AREA(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, bool p7, bool p8) { return YimMenu::NativeInvoker::Invoke<3824, bool>(ped, x1, y1, z1, x2, y2, z2, p7, p8); }
	FORCEINLINE bool IS_ANY_PED_SHOOTING_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, bool p7) { return YimMenu::NativeInvoker::Invoke<3825, bool>(x1, y1, z1, x2, y2, z2, p6, p7); }
	FORCEINLINE bool IS_PED_SHOOTING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3826, bool>(ped); }
	FORCEINLINE void SET_PED_ACCURACY(Ped ped, int accuracy) { return YimMenu::NativeInvoker::Invoke<3827, void>(ped, accuracy); }
	FORCEINLINE int GET_PED_ACCURACY(Ped ped) { return YimMenu::NativeInvoker::Invoke<3828, int>(ped); }
	FORCEINLINE void SET_AMBIENT_LAW_PED_ACCURACY_MODIFIER(float multiplier) { return YimMenu::NativeInvoker::Invoke<3829, void>(multiplier); }
	FORCEINLINE bool IS_PED_MODEL(Ped ped, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<3830, bool>(ped, modelHash); }
	FORCEINLINE void EXPLODE_PED_HEAD(Ped ped, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<3831, void>(ped, weaponHash); }
	FORCEINLINE void REMOVE_PED_ELEGANTLY(Ped* ped) { return YimMenu::NativeInvoker::Invoke<3832, void>(ped); }
	FORCEINLINE void ADD_ARMOUR_TO_PED(Ped ped, int amount) { return YimMenu::NativeInvoker::Invoke<3833, void>(ped, amount); }
	FORCEINLINE void SET_PED_ARMOUR(Ped ped, int amount) { return YimMenu::NativeInvoker::Invoke<3834, void>(ped, amount); }
	FORCEINLINE void SET_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seatIndex) { return YimMenu::NativeInvoker::Invoke<3835, void>(ped, vehicle, seatIndex); }
	FORCEINLINE void SET_PED_ALLOW_VEHICLES_OVERRIDE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3836, void>(ped, toggle); }
	FORCEINLINE bool CAN_CREATE_RANDOM_PED(bool p0) { return YimMenu::NativeInvoker::Invoke<3837, bool>(p0); }
	FORCEINLINE Ped CREATE_RANDOM_PED(float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<3838, Ped>(posX, posY, posZ); }
	FORCEINLINE Ped CREATE_RANDOM_PED_AS_DRIVER(Vehicle vehicle, bool returnHandle) { return YimMenu::NativeInvoker::Invoke<3839, Ped>(vehicle, returnHandle); }
	FORCEINLINE bool CAN_CREATE_RANDOM_DRIVER() { return YimMenu::NativeInvoker::Invoke<3840, bool>(); }
	FORCEINLINE bool CAN_CREATE_RANDOM_BIKE_RIDER() { return YimMenu::NativeInvoker::Invoke<3841, bool>(); }
	FORCEINLINE void SET_PED_MOVE_ANIMS_BLEND_OUT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3842, void>(ped); }
	FORCEINLINE void SET_PED_CAN_BE_DRAGGED_OUT(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3843, void>(ped, toggle); }
	FORCEINLINE void SET_PED_ALLOW_HURT_COMBAT_FOR_ALL_MISSION_PEDS(bool toggle) { return YimMenu::NativeInvoker::Invoke<3844, void>(toggle); }
	FORCEINLINE bool IS_PED_MALE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3845, bool>(ped); }
	FORCEINLINE bool IS_PED_HUMAN(Ped ped) { return YimMenu::NativeInvoker::Invoke<3846, bool>(ped); }
	FORCEINLINE Vehicle GET_VEHICLE_PED_IS_IN(Ped ped, bool includeEntering) { return YimMenu::NativeInvoker::Invoke<3847, Vehicle>(ped, includeEntering); }
	FORCEINLINE void RESET_PED_LAST_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3848, void>(ped); }
	FORCEINLINE void SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier) { return YimMenu::NativeInvoker::Invoke<3849, void>(multiplier); }
	FORCEINLINE void SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(float p0, float p1) { return YimMenu::NativeInvoker::Invoke<3850, void>(p0, p1); }
	FORCEINLINE void SUPPRESS_AMBIENT_PED_AGGRESSIVE_CLEANUP_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<3851, void>(); }
	FORCEINLINE void SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<3852, void>(x, y, z); }
	FORCEINLINE void SET_PED_NON_CREATION_AREA(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<3853, void>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE void CLEAR_PED_NON_CREATION_AREA() { return YimMenu::NativeInvoker::Invoke<3854, void>(); }
	FORCEINLINE void INSTANTLY_FILL_PED_POPULATION() { return YimMenu::NativeInvoker::Invoke<3855, void>(); }
	FORCEINLINE bool IS_PED_ON_MOUNT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3856, bool>(ped); }
	FORCEINLINE Ped GET_MOUNT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3857, Ped>(ped); }
	FORCEINLINE bool IS_PED_ON_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3858, bool>(ped); }
	FORCEINLINE bool IS_PED_ON_SPECIFIC_VEHICLE(Ped ped, Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<3859, bool>(ped, vehicle); }
	FORCEINLINE void SET_PED_MONEY(Ped ped, int amount) { return YimMenu::NativeInvoker::Invoke<3860, void>(ped, amount); }
	FORCEINLINE int GET_PED_MONEY(Ped ped) { return YimMenu::NativeInvoker::Invoke<3861, int>(ped); }
	FORCEINLINE void SET_HEALTH_SNACKS_CARRIED_BY_ALL_NEW_PEDS(float p0, Any p1) { return YimMenu::NativeInvoker::Invoke<3862, void>(p0, p1); }
	FORCEINLINE void SET_AMBIENT_PEDS_DROP_MONEY(bool p0) { return YimMenu::NativeInvoker::Invoke<3863, void>(p0); }
	FORCEINLINE void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME(bool p0) { return YimMenu::NativeInvoker::Invoke<3864, void>(p0); }
	FORCEINLINE void SET_PED_SUFFERS_CRITICAL_HITS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3865, void>(ped, toggle); }
	FORCEINLINE void SET_PED_UPPER_BODY_DAMAGE_ONLY(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3866, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_SITTING_IN_VEHICLE(Ped ped, Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<3867, bool>(ped, vehicle); }
	FORCEINLINE bool IS_PED_SITTING_IN_ANY_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3868, bool>(ped); }
	FORCEINLINE bool IS_PED_ON_FOOT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3869, bool>(ped); }
	FORCEINLINE bool IS_PED_ON_ANY_BIKE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3870, bool>(ped); }
	FORCEINLINE bool IS_PED_PLANTING_BOMB(Ped ped) { return YimMenu::NativeInvoker::Invoke<3871, bool>(ped); }
	FORCEINLINE Vector3 GET_DEAD_PED_PICKUP_COORDS(Ped ped, float p1, float p2) { return YimMenu::NativeInvoker::Invoke<3872, Vector3>(ped, p1, p2); }
	FORCEINLINE bool IS_PED_IN_ANY_BOAT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3873, bool>(ped); }
	FORCEINLINE bool IS_PED_IN_ANY_SUB(Ped ped) { return YimMenu::NativeInvoker::Invoke<3874, bool>(ped); }
	FORCEINLINE bool IS_PED_IN_ANY_HELI(Ped ped) { return YimMenu::NativeInvoker::Invoke<3875, bool>(ped); }
	FORCEINLINE bool IS_PED_IN_ANY_PLANE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3876, bool>(ped); }
	FORCEINLINE bool IS_PED_IN_FLYING_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3877, bool>(ped); }
	FORCEINLINE void SET_PED_DIES_IN_WATER(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3878, void>(ped, toggle); }
	FORCEINLINE bool GET_PED_DIES_IN_WATER(Ped ped) { return YimMenu::NativeInvoker::Invoke<3879, bool>(ped); }
	FORCEINLINE void SET_PED_DIES_IN_SINKING_VEHICLE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3880, void>(ped, toggle); }
	FORCEINLINE int GET_PED_ARMOUR(Ped ped) { return YimMenu::NativeInvoker::Invoke<3881, int>(ped); }
	FORCEINLINE void SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3882, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_BE_SHOT_IN_VEHICLE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3883, void>(ped, toggle); }
	FORCEINLINE bool GET_PED_LAST_DAMAGE_BONE(Ped ped, int* outBone) { return YimMenu::NativeInvoker::Invoke<3884, bool>(ped, outBone); }
	FORCEINLINE void CLEAR_PED_LAST_DAMAGE_BONE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3885, void>(ped); }
	FORCEINLINE void SET_AI_WEAPON_DAMAGE_MODIFIER(float value) { return YimMenu::NativeInvoker::Invoke<3886, void>(value); }
	FORCEINLINE void RESET_AI_WEAPON_DAMAGE_MODIFIER() { return YimMenu::NativeInvoker::Invoke<3887, void>(); }
	FORCEINLINE void SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(float modifier) { return YimMenu::NativeInvoker::Invoke<3888, void>(modifier); }
	FORCEINLINE void RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER() { return YimMenu::NativeInvoker::Invoke<3889, void>(); }
	FORCEINLINE void SET_TREAT_AS_AMBIENT_PED_FOR_DRIVER_LOCKON(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<3890, void>(ped, p1); }
	FORCEINLINE void SET_PED_CAN_BE_TARGETTED(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3891, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_BE_TARGETTED_BY_TEAM(Ped ped, int team, bool toggle) { return YimMenu::NativeInvoker::Invoke<3892, void>(ped, team, toggle); }
	FORCEINLINE void SET_PED_CAN_BE_TARGETTED_BY_PLAYER(Ped ped, Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<3893, void>(ped, player, toggle); }
	FORCEINLINE void SET_ALLOW_LOCKON_TO_PED_IF_FRIENDLY(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3894, void>(ped, toggle); }
	FORCEINLINE void SET_USE_CAMERA_HEADING_FOR_DESIRED_DIRECTION_LOCK_ON_TEST(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3895, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_IN_ANY_POLICE_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3896, bool>(ped); }
	FORCEINLINE void FORCE_PED_TO_OPEN_PARACHUTE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3897, void>(ped); }
	FORCEINLINE bool IS_PED_IN_PARACHUTE_FREE_FALL(Ped ped) { return YimMenu::NativeInvoker::Invoke<3898, bool>(ped); }
	FORCEINLINE bool IS_PED_FALLING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3899, bool>(ped); }
	FORCEINLINE bool IS_PED_JUMPING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3900, bool>(ped); }
	FORCEINLINE bool IS_PED_LANDING(Any p0) { return YimMenu::NativeInvoker::Invoke<3901, bool>(p0); }
	FORCEINLINE bool IS_PED_DOING_A_BEAST_JUMP(Any p0) { return YimMenu::NativeInvoker::Invoke<3902, bool>(p0); }
	FORCEINLINE bool IS_PED_CLIMBING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3903, bool>(ped); }
	FORCEINLINE bool IS_PED_VAULTING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3904, bool>(ped); }
	FORCEINLINE bool IS_PED_DIVING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3905, bool>(ped); }
	FORCEINLINE bool IS_PED_JUMPING_OUT_OF_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3906, bool>(ped); }
	FORCEINLINE bool IS_PED_OPENING_DOOR(Ped ped) { return YimMenu::NativeInvoker::Invoke<3907, bool>(ped); }
	FORCEINLINE int GET_PED_PARACHUTE_STATE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3908, int>(ped); }
	FORCEINLINE int GET_PED_PARACHUTE_LANDING_TYPE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3909, int>(ped); }
	FORCEINLINE void SET_PED_PARACHUTE_TINT_INDEX(Ped ped, int tintIndex) { return YimMenu::NativeInvoker::Invoke<3910, void>(ped, tintIndex); }
	FORCEINLINE void GET_PED_PARACHUTE_TINT_INDEX(Ped ped, int* outTintIndex) { return YimMenu::NativeInvoker::Invoke<3911, void>(ped, outTintIndex); }
	FORCEINLINE void SET_PED_RESERVE_PARACHUTE_TINT_INDEX(Ped ped, Any p1) { return YimMenu::NativeInvoker::Invoke<3912, void>(ped, p1); }
	FORCEINLINE Object CREATE_PARACHUTE_BAG_OBJECT(Ped ped, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<3913, Object>(ped, p1, p2); }
	FORCEINLINE void SET_PED_DUCKING(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3914, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_DUCKING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3915, bool>(ped); }
	FORCEINLINE bool IS_PED_IN_ANY_TAXI(Ped ped) { return YimMenu::NativeInvoker::Invoke<3916, bool>(ped); }
	FORCEINLINE void SET_PED_ID_RANGE(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<3917, void>(ped, value); }
	FORCEINLINE void SET_PED_HIGHLY_PERCEPTIVE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3918, void>(ped, toggle); }
	FORCEINLINE void SET_COP_PERCEPTION_OVERRIDES(float seeingRange, float seeingRangePeripheral, float hearingRange, float visualFieldMinAzimuthAngle, float visualFieldMaxAzimuthAngle, float fieldOfGazeMaxAngle, float p6) { return YimMenu::NativeInvoker::Invoke<3919, void>(seeingRange, seeingRangePeripheral, hearingRange, visualFieldMinAzimuthAngle, visualFieldMaxAzimuthAngle, fieldOfGazeMaxAngle, p6); }
	FORCEINLINE void SET_PED_INJURED_ON_GROUND_BEHAVIOUR(Ped ped, float p1) { return YimMenu::NativeInvoker::Invoke<3920, void>(ped, p1); }
	FORCEINLINE void DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR(Ped ped) { return YimMenu::NativeInvoker::Invoke<3921, void>(ped); }
	FORCEINLINE void SET_PED_SEEING_RANGE(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<3922, void>(ped, value); }
	FORCEINLINE void SET_PED_HEARING_RANGE(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<3923, void>(ped, value); }
	FORCEINLINE void SET_PED_VISUAL_FIELD_MIN_ANGLE(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<3924, void>(ped, value); }
	FORCEINLINE void SET_PED_VISUAL_FIELD_MAX_ANGLE(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<3925, void>(ped, value); }
	FORCEINLINE void SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(Ped ped, float angle) { return YimMenu::NativeInvoker::Invoke<3926, void>(ped, angle); }
	FORCEINLINE void SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(Ped ped, float angle) { return YimMenu::NativeInvoker::Invoke<3927, void>(ped, angle); }
	FORCEINLINE void SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(Ped ped, float range) { return YimMenu::NativeInvoker::Invoke<3928, void>(ped, range); }
	FORCEINLINE void SET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped, float angle) { return YimMenu::NativeInvoker::Invoke<3929, void>(ped, angle); }
	FORCEINLINE float GET_PED_VISUAL_FIELD_CENTER_ANGLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3930, float>(ped); }
	FORCEINLINE void SET_PED_STEALTH_MOVEMENT(Ped ped, bool p1, const char* action) { return YimMenu::NativeInvoker::Invoke<3931, void>(ped, p1, action); }
	FORCEINLINE bool GET_PED_STEALTH_MOVEMENT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3932, bool>(ped); }
	FORCEINLINE int CREATE_GROUP(int unused) { return YimMenu::NativeInvoker::Invoke<3933, int>(unused); }
	FORCEINLINE void SET_PED_AS_GROUP_LEADER(Ped ped, int groupId) { return YimMenu::NativeInvoker::Invoke<3934, void>(ped, groupId); }
	FORCEINLINE void SET_PED_AS_GROUP_MEMBER(Ped ped, int groupId) { return YimMenu::NativeInvoker::Invoke<3935, void>(ped, groupId); }
	FORCEINLINE void SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(Ped pedHandle, int groupHandle, bool toggle) { return YimMenu::NativeInvoker::Invoke<3936, void>(pedHandle, groupHandle, toggle); }
	FORCEINLINE void REMOVE_GROUP(int groupId) { return YimMenu::NativeInvoker::Invoke<3937, void>(groupId); }
	FORCEINLINE void REMOVE_PED_FROM_GROUP(Ped ped) { return YimMenu::NativeInvoker::Invoke<3938, void>(ped); }
	FORCEINLINE bool IS_PED_GROUP_MEMBER(Ped ped, int groupId) { return YimMenu::NativeInvoker::Invoke<3939, bool>(ped, groupId); }
	FORCEINLINE bool IS_PED_HANGING_ON_TO_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3940, bool>(ped); }
	FORCEINLINE void SET_GROUP_SEPARATION_RANGE(int groupHandle, float separationRange) { return YimMenu::NativeInvoker::Invoke<3941, void>(groupHandle, separationRange); }
	FORCEINLINE void SET_PED_MIN_GROUND_TIME_FOR_STUNGUN(Ped ped, int ms) { return YimMenu::NativeInvoker::Invoke<3942, void>(ped, ms); }
	FORCEINLINE bool IS_PED_PRONE(Ped ped) { return YimMenu::NativeInvoker::Invoke<3943, bool>(ped); }
	FORCEINLINE bool IS_PED_IN_COMBAT(Ped ped, Ped target) { return YimMenu::NativeInvoker::Invoke<3944, bool>(ped, target); }
	FORCEINLINE Entity GET_PED_TARGET_FROM_COMBAT_PED(Ped ped, Any p1) { return YimMenu::NativeInvoker::Invoke<3945, Entity>(ped, p1); }
	FORCEINLINE bool CAN_PED_IN_COMBAT_SEE_TARGET(Ped ped, Ped target) { return YimMenu::NativeInvoker::Invoke<3946, bool>(ped, target); }
	FORCEINLINE bool IS_PED_DOING_DRIVEBY(Ped ped) { return YimMenu::NativeInvoker::Invoke<3947, bool>(ped); }
	FORCEINLINE bool IS_PED_JACKING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3948, bool>(ped); }
	FORCEINLINE bool IS_PED_BEING_JACKED(Ped ped) { return YimMenu::NativeInvoker::Invoke<3949, bool>(ped); }
	FORCEINLINE bool IS_PED_BEING_STUNNED(Ped ped, int p1) { return YimMenu::NativeInvoker::Invoke<3950, bool>(ped, p1); }
	FORCEINLINE Ped GET_PEDS_JACKER(Ped ped) { return YimMenu::NativeInvoker::Invoke<3951, Ped>(ped); }
	FORCEINLINE Ped GET_JACK_TARGET(Ped ped) { return YimMenu::NativeInvoker::Invoke<3952, Ped>(ped); }
	FORCEINLINE bool IS_PED_FLEEING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3953, bool>(ped); }
	FORCEINLINE bool IS_PED_IN_COVER(Ped ped, bool exceptUseWeapon) { return YimMenu::NativeInvoker::Invoke<3954, bool>(ped, exceptUseWeapon); }
	FORCEINLINE bool IS_PED_IN_COVER_FACING_LEFT(Ped ped) { return YimMenu::NativeInvoker::Invoke<3955, bool>(ped); }
	FORCEINLINE bool IS_PED_IN_HIGH_COVER(Ped ped) { return YimMenu::NativeInvoker::Invoke<3956, bool>(ped); }
	FORCEINLINE bool IS_PED_GOING_INTO_COVER(Ped ped) { return YimMenu::NativeInvoker::Invoke<3957, bool>(ped); }
	FORCEINLINE bool SET_PED_PINNED_DOWN(Ped ped, bool pinned, int i) { return YimMenu::NativeInvoker::Invoke<3958, bool>(ped, pinned, i); }
	FORCEINLINE int GET_SEAT_PED_IS_TRYING_TO_ENTER(Ped ped) { return YimMenu::NativeInvoker::Invoke<3959, int>(ped); }
	FORCEINLINE Vehicle GET_VEHICLE_PED_IS_TRYING_TO_ENTER(Ped ped) { return YimMenu::NativeInvoker::Invoke<3960, Vehicle>(ped); }
	FORCEINLINE Entity GET_PED_SOURCE_OF_DEATH(Ped ped) { return YimMenu::NativeInvoker::Invoke<3961, Entity>(ped); }
	FORCEINLINE Hash GET_PED_CAUSE_OF_DEATH(Ped ped) { return YimMenu::NativeInvoker::Invoke<3962, Hash>(ped); }
	FORCEINLINE int GET_PED_TIME_OF_DEATH(Ped ped) { return YimMenu::NativeInvoker::Invoke<3963, int>(ped); }
	FORCEINLINE int COUNT_PEDS_IN_COMBAT_WITH_TARGET(Ped ped) { return YimMenu::NativeInvoker::Invoke<3964, int>(ped); }
	FORCEINLINE int COUNT_PEDS_IN_COMBAT_WITH_TARGET_WITHIN_RADIUS(Ped ped, float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<3965, int>(ped, x, y, z, radius); }
	FORCEINLINE void SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped, Hash hash) { return YimMenu::NativeInvoker::Invoke<3966, void>(ped, hash); }
	FORCEINLINE void SET_PED_RELATIONSHIP_GROUP_HASH(Ped ped, Hash hash) { return YimMenu::NativeInvoker::Invoke<3967, void>(ped, hash); }
	FORCEINLINE void SET_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2) { return YimMenu::NativeInvoker::Invoke<3968, void>(relationship, group1, group2); }
	FORCEINLINE void CLEAR_RELATIONSHIP_BETWEEN_GROUPS(int relationship, Hash group1, Hash group2) { return YimMenu::NativeInvoker::Invoke<3969, void>(relationship, group1, group2); }
	FORCEINLINE bool ADD_RELATIONSHIP_GROUP(const char* name, Hash* groupHash) { return YimMenu::NativeInvoker::Invoke<3970, bool>(name, groupHash); }
	FORCEINLINE void REMOVE_RELATIONSHIP_GROUP(Hash groupHash) { return YimMenu::NativeInvoker::Invoke<3971, void>(groupHash); }
	FORCEINLINE bool DOES_RELATIONSHIP_GROUP_EXIST(Hash groupHash) { return YimMenu::NativeInvoker::Invoke<3972, bool>(groupHash); }
	FORCEINLINE int GET_RELATIONSHIP_BETWEEN_PEDS(Ped ped1, Ped ped2) { return YimMenu::NativeInvoker::Invoke<3973, int>(ped1, ped2); }
	FORCEINLINE Hash GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(Ped ped) { return YimMenu::NativeInvoker::Invoke<3974, Hash>(ped); }
	FORCEINLINE Hash GET_PED_RELATIONSHIP_GROUP_HASH(Ped ped) { return YimMenu::NativeInvoker::Invoke<3975, Hash>(ped); }
	FORCEINLINE int GET_RELATIONSHIP_BETWEEN_GROUPS(Hash group1, Hash group2) { return YimMenu::NativeInvoker::Invoke<3976, int>(group1, group2); }
	FORCEINLINE void SET_RELATIONSHIP_GROUP_AFFECTS_WANTED_LEVEL(Hash group, bool p1) { return YimMenu::NativeInvoker::Invoke<3977, void>(group, p1); }
	FORCEINLINE void TELL_GROUP_PEDS_IN_AREA_TO_ATTACK(Ped ped, Any p1, float p2, Hash hash, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<3978, void>(ped, p1, p2, hash, p4, p5); }
	FORCEINLINE void SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3979, void>(ped, toggle); }
	FORCEINLINE void SET_PED_TO_INFORM_RESPECTED_FRIENDS(Ped ped, float radius, int maxFriends) { return YimMenu::NativeInvoker::Invoke<3980, void>(ped, radius, maxFriends); }
	FORCEINLINE bool IS_PED_RESPONDING_TO_EVENT(Ped ped, Any event) { return YimMenu::NativeInvoker::Invoke<3981, bool>(ped, event); }
	FORCEINLINE bool GET_POS_FROM_FIRED_EVENT(Ped ped, int eventType, Any* outData) { return YimMenu::NativeInvoker::Invoke<3982, bool>(ped, eventType, outData); }
	FORCEINLINE void SET_PED_FIRING_PATTERN(Ped ped, Hash patternHash) { return YimMenu::NativeInvoker::Invoke<3983, void>(ped, patternHash); }
	FORCEINLINE void SET_PED_SHOOT_RATE(Ped ped, int shootRate) { return YimMenu::NativeInvoker::Invoke<3984, void>(ped, shootRate); }
	FORCEINLINE void SET_COMBAT_FLOAT(Ped ped, int combatType, float p2) { return YimMenu::NativeInvoker::Invoke<3985, void>(ped, combatType, p2); }
	FORCEINLINE float GET_COMBAT_FLOAT(Ped ped, int p1) { return YimMenu::NativeInvoker::Invoke<3986, float>(ped, p1); }
	FORCEINLINE void GET_GROUP_SIZE(int groupID, Any* p1, int* sizeInMembers) { return YimMenu::NativeInvoker::Invoke<3987, void>(groupID, p1, sizeInMembers); }
	FORCEINLINE bool DOES_GROUP_EXIST(int groupId) { return YimMenu::NativeInvoker::Invoke<3988, bool>(groupId); }
	FORCEINLINE int GET_PED_GROUP_INDEX(Ped ped) { return YimMenu::NativeInvoker::Invoke<3989, int>(ped); }
	FORCEINLINE bool IS_PED_IN_GROUP(Ped ped) { return YimMenu::NativeInvoker::Invoke<3990, bool>(ped); }
	FORCEINLINE Player GET_PLAYER_PED_IS_FOLLOWING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3991, Player>(ped); }
	FORCEINLINE void SET_GROUP_FORMATION(int groupId, int formationType) { return YimMenu::NativeInvoker::Invoke<3992, void>(groupId, formationType); }
	FORCEINLINE void SET_GROUP_FORMATION_SPACING(int groupId, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<3993, void>(groupId, x, y, z); }
	FORCEINLINE void RESET_GROUP_FORMATION_DEFAULT_SPACING(int groupHandle) { return YimMenu::NativeInvoker::Invoke<3994, void>(groupHandle); }
	FORCEINLINE Vehicle GET_VEHICLE_PED_IS_USING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3995, Vehicle>(ped); }
	FORCEINLINE Vehicle GET_VEHICLE_PED_IS_ENTERING(Ped ped) { return YimMenu::NativeInvoker::Invoke<3996, Vehicle>(ped); }
	FORCEINLINE void SET_PED_GRAVITY(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<3997, void>(ped, toggle); }
	FORCEINLINE void APPLY_DAMAGE_TO_PED(Ped ped, int damageAmount, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<3998, void>(ped, damageAmount, p2, p3); }
	FORCEINLINE int GET_TIME_PED_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<3999, int>(ped, weaponHash); }
	FORCEINLINE void SET_PED_ALLOWED_TO_DUCK(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4000, void>(ped, toggle); }
	FORCEINLINE void SET_PED_NEVER_LEAVES_GROUP(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4001, void>(ped, toggle); }
	FORCEINLINE int GET_PED_TYPE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4002, int>(ped); }
	FORCEINLINE void SET_PED_AS_COP(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4003, void>(ped, toggle); }
	FORCEINLINE void SET_PED_HEALTH_PENDING_LAST_DAMAGE_EVENT_OVERRIDE_FLAG(bool toggle) { return YimMenu::NativeInvoker::Invoke<4004, void>(toggle); }
	FORCEINLINE void SET_PED_MAX_HEALTH(Ped ped, int value) { return YimMenu::NativeInvoker::Invoke<4005, void>(ped, value); }
	FORCEINLINE int GET_PED_MAX_HEALTH(Ped ped) { return YimMenu::NativeInvoker::Invoke<4006, int>(ped); }
	FORCEINLINE void SET_PED_MAX_TIME_IN_WATER(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<4007, void>(ped, value); }
	FORCEINLINE void SET_PED_MAX_TIME_UNDERWATER(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<4008, void>(ped, value); }
	FORCEINLINE void SET_CORPSE_RAGDOLL_FRICTION(Ped ped, float p1) { return YimMenu::NativeInvoker::Invoke<4009, void>(ped, p1); }
	FORCEINLINE void SET_PED_VEHICLE_FORCED_SEAT_USAGE(Ped ped, Vehicle vehicle, int seatIndex, int flags, Any p4) { return YimMenu::NativeInvoker::Invoke<4010, void>(ped, vehicle, seatIndex, flags, p4); }
	FORCEINLINE void CLEAR_ALL_PED_VEHICLE_FORCED_SEAT_USAGE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4011, void>(ped); }
	FORCEINLINE void SET_PED_CAN_BE_KNOCKED_OFF_BIKE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4012, void>(p0, p1); }
	FORCEINLINE void SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Ped ped, int state) { return YimMenu::NativeInvoker::Invoke<4013, void>(ped, state); }
	FORCEINLINE bool CAN_KNOCK_PED_OFF_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4014, bool>(ped); }
	FORCEINLINE void KNOCK_PED_OFF_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4015, void>(ped); }
	FORCEINLINE void SET_PED_COORDS_NO_GANG(Ped ped, float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<4016, void>(ped, posX, posY, posZ); }
	FORCEINLINE Ped GET_PED_AS_GROUP_MEMBER(int groupID, int memberNumber) { return YimMenu::NativeInvoker::Invoke<4017, Ped>(groupID, memberNumber); }
	FORCEINLINE Ped GET_PED_AS_GROUP_LEADER(int groupID) { return YimMenu::NativeInvoker::Invoke<4018, Ped>(groupID); }
	FORCEINLINE void SET_PED_KEEP_TASK(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4019, void>(ped, toggle); }
	FORCEINLINE void SET_PED_ALLOW_MINOR_REACTIONS_AS_MISSION_PED(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4020, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_SWIMMING(Ped ped) { return YimMenu::NativeInvoker::Invoke<4021, bool>(ped); }
	FORCEINLINE bool IS_PED_SWIMMING_UNDER_WATER(Ped ped) { return YimMenu::NativeInvoker::Invoke<4022, bool>(ped); }
	FORCEINLINE void SET_PED_COORDS_KEEP_VEHICLE(Ped ped, float posX, float posY, float posZ) { return YimMenu::NativeInvoker::Invoke<4023, void>(ped, posX, posY, posZ); }
	FORCEINLINE void SET_PED_DIES_IN_VEHICLE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4024, void>(ped, toggle); }
	FORCEINLINE void SET_CREATE_RANDOM_COPS(bool toggle) { return YimMenu::NativeInvoker::Invoke<4025, void>(toggle); }
	FORCEINLINE void SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(bool toggle) { return YimMenu::NativeInvoker::Invoke<4026, void>(toggle); }
	FORCEINLINE void SET_CREATE_RANDOM_COPS_ON_SCENARIOS(bool toggle) { return YimMenu::NativeInvoker::Invoke<4027, void>(toggle); }
	FORCEINLINE bool CAN_CREATE_RANDOM_COPS() { return YimMenu::NativeInvoker::Invoke<4028, bool>(); }
	FORCEINLINE void SET_PED_AS_ENEMY(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4029, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_SMASH_GLASS(Ped ped, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<4030, void>(ped, p1, p2); }
	FORCEINLINE bool IS_PED_IN_ANY_TRAIN(Ped ped) { return YimMenu::NativeInvoker::Invoke<4031, bool>(ped); }
	FORCEINLINE bool IS_PED_GETTING_INTO_A_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4032, bool>(ped); }
	FORCEINLINE bool IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4033, bool>(ped); }
	FORCEINLINE void SET_ENABLE_HANDCUFFS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4034, void>(ped, toggle); }
	FORCEINLINE void SET_ENABLE_BOUND_ANKLES(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4035, void>(ped, toggle); }
	FORCEINLINE void SET_ENABLE_SCUBA(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4036, void>(ped, toggle); }
	FORCEINLINE void SET_CAN_ATTACK_FRIENDLY(Ped ped, bool toggle, bool p2) { return YimMenu::NativeInvoker::Invoke<4037, void>(ped, toggle, p2); }
	FORCEINLINE int GET_PED_ALERTNESS(Ped ped) { return YimMenu::NativeInvoker::Invoke<4038, int>(ped); }
	FORCEINLINE void SET_PED_ALERTNESS(Ped ped, int value) { return YimMenu::NativeInvoker::Invoke<4039, void>(ped, value); }
	FORCEINLINE void SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4040, void>(ped, toggle); }
	FORCEINLINE void SET_PED_MOVEMENT_CLIPSET(Ped ped, const char* clipSet, float transitionSpeed) { return YimMenu::NativeInvoker::Invoke<4041, void>(ped, clipSet, transitionSpeed); }
	FORCEINLINE void RESET_PED_MOVEMENT_CLIPSET(Ped ped, float p1) { return YimMenu::NativeInvoker::Invoke<4042, void>(ped, p1); }
	FORCEINLINE void SET_PED_STRAFE_CLIPSET(Ped ped, const char* clipSet) { return YimMenu::NativeInvoker::Invoke<4043, void>(ped, clipSet); }
	FORCEINLINE void RESET_PED_STRAFE_CLIPSET(Ped ped) { return YimMenu::NativeInvoker::Invoke<4044, void>(ped); }
	FORCEINLINE void SET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped, const char* clipSet) { return YimMenu::NativeInvoker::Invoke<4045, void>(ped, clipSet); }
	FORCEINLINE void RESET_PED_WEAPON_MOVEMENT_CLIPSET(Ped ped) { return YimMenu::NativeInvoker::Invoke<4046, void>(ped); }
	FORCEINLINE void SET_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped, const char* clipset) { return YimMenu::NativeInvoker::Invoke<4047, void>(ped, clipset); }
	FORCEINLINE void CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4048, void>(ped); }
	FORCEINLINE void SET_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(Ped ped, const char* p1) { return YimMenu::NativeInvoker::Invoke<4049, void>(ped, p1); }
	FORCEINLINE void CLEAR_PED_MOTION_IN_COVER_CLIPSET_OVERRIDE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4050, void>(ped); }
	FORCEINLINE void CLEAR_PED_FALL_UPPER_BODY_CLIPSET_OVERRIDE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4051, void>(ped); }
	FORCEINLINE void SET_PED_IN_VEHICLE_CONTEXT(Ped ped, Hash context) { return YimMenu::NativeInvoker::Invoke<4052, void>(ped, context); }
	FORCEINLINE void RESET_PED_IN_VEHICLE_CONTEXT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4053, void>(ped); }
	FORCEINLINE bool IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM(Ped ped, const char* animDict, const char* anim) { return YimMenu::NativeInvoker::Invoke<4054, bool>(ped, animDict, anim); }
	FORCEINLINE void SET_PED_ALTERNATE_WALK_ANIM(Ped ped, const char* animDict, const char* animName, float p3, bool p4) { return YimMenu::NativeInvoker::Invoke<4055, void>(ped, animDict, animName, p3, p4); }
	FORCEINLINE void CLEAR_PED_ALTERNATE_WALK_ANIM(Ped ped, float p1) { return YimMenu::NativeInvoker::Invoke<4056, void>(ped, p1); }
	FORCEINLINE void SET_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, const char* animDictionary, const char* animationName, float p4, bool p5) { return YimMenu::NativeInvoker::Invoke<4057, void>(ped, stance, animDictionary, animationName, p4, p5); }
	FORCEINLINE void CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(Ped ped, int stance, float p2) { return YimMenu::NativeInvoker::Invoke<4058, void>(ped, stance, p2); }
	FORCEINLINE void SET_PED_GESTURE_GROUP(Ped ped, const char* animGroupGesture) { return YimMenu::NativeInvoker::Invoke<4059, void>(ped, animGroupGesture); }
	FORCEINLINE Vector3 GET_ANIM_INITIAL_OFFSET_POSITION(const char* animDict, const char* animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9) { return YimMenu::NativeInvoker::Invoke<4060, Vector3>(animDict, animName, x, y, z, xRot, yRot, zRot, p8, p9); }
	FORCEINLINE Vector3 GET_ANIM_INITIAL_OFFSET_ROTATION(const char* animDict, const char* animName, float x, float y, float z, float xRot, float yRot, float zRot, float p8, int p9) { return YimMenu::NativeInvoker::Invoke<4061, Vector3>(animDict, animName, x, y, z, xRot, yRot, zRot, p8, p9); }
	FORCEINLINE int GET_PED_DRAWABLE_VARIATION(Ped ped, int componentId) { return YimMenu::NativeInvoker::Invoke<4062, int>(ped, componentId); }
	FORCEINLINE int GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(Ped ped, int componentId) { return YimMenu::NativeInvoker::Invoke<4063, int>(ped, componentId); }
	FORCEINLINE int GET_PED_TEXTURE_VARIATION(Ped ped, int componentId) { return YimMenu::NativeInvoker::Invoke<4064, int>(ped, componentId); }
	FORCEINLINE int GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(Ped ped, int componentId, int drawableId) { return YimMenu::NativeInvoker::Invoke<4065, int>(ped, componentId, drawableId); }
	FORCEINLINE int GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(Ped ped, int propId) { return YimMenu::NativeInvoker::Invoke<4066, int>(ped, propId); }
	FORCEINLINE int GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(Ped ped, int propId, int drawableId) { return YimMenu::NativeInvoker::Invoke<4067, int>(ped, propId, drawableId); }
	FORCEINLINE int GET_PED_PALETTE_VARIATION(Ped ped, int componentId) { return YimMenu::NativeInvoker::Invoke<4068, int>(ped, componentId); }
	FORCEINLINE bool GET_MP_OUTFIT_DATA_FROM_METADATA(Any* p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<4069, bool>(p0, p1); }
	FORCEINLINE int GET_FM_MALE_SHOP_PED_APPAREL_ITEM_INDEX(int p0) { return YimMenu::NativeInvoker::Invoke<4070, int>(p0); }
	FORCEINLINE int GET_FM_FEMALE_SHOP_PED_APPAREL_ITEM_INDEX(int p0) { return YimMenu::NativeInvoker::Invoke<4071, int>(p0); }
	FORCEINLINE bool IS_PED_COMPONENT_VARIATION_VALID(Ped ped, int componentId, int drawableId, int textureId) { return YimMenu::NativeInvoker::Invoke<4072, bool>(ped, componentId, drawableId, textureId); }
	FORCEINLINE void SET_PED_COMPONENT_VARIATION(Ped ped, int componentId, int drawableId, int textureId, int paletteId) { return YimMenu::NativeInvoker::Invoke<4073, void>(ped, componentId, drawableId, textureId, paletteId); }
	FORCEINLINE void SET_PED_RANDOM_COMPONENT_VARIATION(Ped ped, int p1) { return YimMenu::NativeInvoker::Invoke<4074, void>(ped, p1); }
	FORCEINLINE void SET_PED_RANDOM_PROPS(Ped ped) { return YimMenu::NativeInvoker::Invoke<4075, void>(ped); }
	FORCEINLINE void SET_PED_DEFAULT_COMPONENT_VARIATION(Ped ped) { return YimMenu::NativeInvoker::Invoke<4076, void>(ped); }
	FORCEINLINE void SET_PED_BLEND_FROM_PARENTS(Ped ped, Any p1, Any p2, float p3, float p4) { return YimMenu::NativeInvoker::Invoke<4077, void>(ped, p1, p2, p3, p4); }
	FORCEINLINE void SET_PED_HEAD_BLEND_DATA(Ped ped, int shapeFirstID, int shapeSecondID, int shapeThirdID, int skinFirstID, int skinSecondID, int skinThirdID, float shapeMix, float skinMix, float thirdMix, bool isParent) { return YimMenu::NativeInvoker::Invoke<4078, void>(ped, shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID, shapeMix, skinMix, thirdMix, isParent); }
	FORCEINLINE bool GET_PED_HEAD_BLEND_DATA(Ped ped, Any* headBlendData) { return YimMenu::NativeInvoker::Invoke<4079, bool>(ped, headBlendData); }
	FORCEINLINE void UPDATE_PED_HEAD_BLEND_DATA(Ped ped, float shapeMix, float skinMix, float thirdMix) { return YimMenu::NativeInvoker::Invoke<4080, void>(ped, shapeMix, skinMix, thirdMix); }
	FORCEINLINE void SET_HEAD_BLEND_EYE_COLOR(Ped ped, int index) { return YimMenu::NativeInvoker::Invoke<4081, void>(ped, index); }
	FORCEINLINE int GET_HEAD_BLEND_EYE_COLOR(Ped ped) { return YimMenu::NativeInvoker::Invoke<4082, int>(ped); }
	FORCEINLINE void SET_PED_HEAD_OVERLAY(Ped ped, int overlayID, int index, float opacity) { return YimMenu::NativeInvoker::Invoke<4083, void>(ped, overlayID, index, opacity); }
	FORCEINLINE int GET_PED_HEAD_OVERLAY(Ped ped, int overlayID) { return YimMenu::NativeInvoker::Invoke<4084, int>(ped, overlayID); }
	FORCEINLINE int GET_PED_HEAD_OVERLAY_NUM(int overlayID) { return YimMenu::NativeInvoker::Invoke<4085, int>(overlayID); }
	FORCEINLINE void SET_PED_HEAD_OVERLAY_TINT(Ped ped, int overlayID, int colorType, int colorID, int secondColorID) { return YimMenu::NativeInvoker::Invoke<4086, void>(ped, overlayID, colorType, colorID, secondColorID); }
	FORCEINLINE void SET_PED_HAIR_TINT(Ped ped, int colorID, int highlightColorID) { return YimMenu::NativeInvoker::Invoke<4087, void>(ped, colorID, highlightColorID); }
	FORCEINLINE int GET_NUM_PED_HAIR_TINTS() { return YimMenu::NativeInvoker::Invoke<4088, int>(); }
	FORCEINLINE int GET_NUM_PED_MAKEUP_TINTS() { return YimMenu::NativeInvoker::Invoke<4089, int>(); }
	FORCEINLINE void GET_PED_HAIR_TINT_COLOR(int hairColorIndex, int* outR, int* outG, int* outB) { return YimMenu::NativeInvoker::Invoke<4090, void>(hairColorIndex, outR, outG, outB); }
	FORCEINLINE void GET_PED_MAKEUP_TINT_COLOR(int makeupColorIndex, int* outR, int* outG, int* outB) { return YimMenu::NativeInvoker::Invoke<4091, void>(makeupColorIndex, outR, outG, outB); }
	FORCEINLINE bool IS_PED_HAIR_TINT_FOR_CREATOR(int colorId) { return YimMenu::NativeInvoker::Invoke<4092, bool>(colorId); }
	FORCEINLINE int GET_DEFAULT_SECONDARY_TINT_FOR_CREATOR(int colorId) { return YimMenu::NativeInvoker::Invoke<4093, int>(colorId); }
	FORCEINLINE bool IS_PED_LIPSTICK_TINT_FOR_CREATOR(int colorId) { return YimMenu::NativeInvoker::Invoke<4094, bool>(colorId); }
	FORCEINLINE bool IS_PED_BLUSH_TINT_FOR_CREATOR(int colorId) { return YimMenu::NativeInvoker::Invoke<4095, bool>(colorId); }
	FORCEINLINE bool IS_PED_HAIR_TINT_FOR_BARBER(int colorID) { return YimMenu::NativeInvoker::Invoke<4096, bool>(colorID); }
	FORCEINLINE int GET_DEFAULT_SECONDARY_TINT_FOR_BARBER(int colorID) { return YimMenu::NativeInvoker::Invoke<4097, int>(colorID); }
	FORCEINLINE bool IS_PED_LIPSTICK_TINT_FOR_BARBER(int colorID) { return YimMenu::NativeInvoker::Invoke<4098, bool>(colorID); }
	FORCEINLINE bool IS_PED_BLUSH_TINT_FOR_BARBER(int colorID) { return YimMenu::NativeInvoker::Invoke<4099, bool>(colorID); }
	FORCEINLINE bool IS_PED_BLUSH_FACEPAINT_TINT_FOR_BARBER(int colorId) { return YimMenu::NativeInvoker::Invoke<4100, bool>(colorId); }
	FORCEINLINE int GET_TINT_INDEX_FOR_LAST_GEN_HAIR_TEXTURE(Hash modelHash, int drawableId, int textureId) { return YimMenu::NativeInvoker::Invoke<4101, int>(modelHash, drawableId, textureId); }
	FORCEINLINE void SET_PED_MICRO_MORPH(Ped ped, int index, float scale) { return YimMenu::NativeInvoker::Invoke<4102, void>(ped, index, scale); }
	FORCEINLINE bool HAS_PED_HEAD_BLEND_FINISHED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4103, bool>(ped); }
	FORCEINLINE void FINALIZE_HEAD_BLEND(Ped ped) { return YimMenu::NativeInvoker::Invoke<4104, void>(ped); }
	FORCEINLINE void SET_HEAD_BLEND_PALETTE_COLOR(Ped ped, int r, int g, int b, int id) { return YimMenu::NativeInvoker::Invoke<4105, void>(ped, r, g, b, id); }
	FORCEINLINE void DISABLE_HEAD_BLEND_PALETTE_COLOR(Ped ped) { return YimMenu::NativeInvoker::Invoke<4106, void>(ped); }
	FORCEINLINE int GET_PED_HEAD_BLEND_FIRST_INDEX(int type) { return YimMenu::NativeInvoker::Invoke<4107, int>(type); }
	FORCEINLINE int GET_PED_HEAD_BLEND_NUM_HEADS(int type) { return YimMenu::NativeInvoker::Invoke<4108, int>(type); }
	FORCEINLINE int SET_PED_PRELOAD_VARIATION_DATA(Ped ped, int slot, int drawableId, int textureId) { return YimMenu::NativeInvoker::Invoke<4109, int>(ped, slot, drawableId, textureId); }
	FORCEINLINE bool HAS_PED_PRELOAD_VARIATION_DATA_FINISHED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4110, bool>(ped); }
	FORCEINLINE void RELEASE_PED_PRELOAD_VARIATION_DATA(Ped ped) { return YimMenu::NativeInvoker::Invoke<4111, void>(ped); }
	FORCEINLINE int SET_PED_PRELOAD_PROP_DATA(Ped ped, int componentId, int drawableId, int TextureId) { return YimMenu::NativeInvoker::Invoke<4112, int>(ped, componentId, drawableId, TextureId); }
	FORCEINLINE bool HAS_PED_PRELOAD_PROP_DATA_FINISHED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4113, bool>(ped); }
	FORCEINLINE void RELEASE_PED_PRELOAD_PROP_DATA(Ped ped) { return YimMenu::NativeInvoker::Invoke<4114, void>(ped); }
	FORCEINLINE int GET_PED_PROP_INDEX(Ped ped, int componentId, Any p2) { return YimMenu::NativeInvoker::Invoke<4115, int>(ped, componentId, p2); }
	FORCEINLINE void SET_PED_PROP_INDEX(Ped ped, int componentId, int drawableId, int TextureId, bool attach, Any p5) { return YimMenu::NativeInvoker::Invoke<4116, void>(ped, componentId, drawableId, TextureId, attach, p5); }
	FORCEINLINE void KNOCK_OFF_PED_PROP(Ped ped, bool p1, bool p2, bool p3, bool p4) { return YimMenu::NativeInvoker::Invoke<4117, void>(ped, p1, p2, p3, p4); }
	FORCEINLINE void CLEAR_PED_PROP(Ped ped, int propId, Any p2) { return YimMenu::NativeInvoker::Invoke<4118, void>(ped, propId, p2); }
	FORCEINLINE void CLEAR_ALL_PED_PROPS(Ped ped, Any p1) { return YimMenu::NativeInvoker::Invoke<4119, void>(ped, p1); }
	FORCEINLINE void DROP_AMBIENT_PROP(Ped ped) { return YimMenu::NativeInvoker::Invoke<4120, void>(ped); }
	FORCEINLINE int GET_PED_PROP_TEXTURE_INDEX(Ped ped, int componentId) { return YimMenu::NativeInvoker::Invoke<4121, int>(ped, componentId); }
	FORCEINLINE void CLEAR_PED_PARACHUTE_PACK_VARIATION(Ped ped) { return YimMenu::NativeInvoker::Invoke<4122, void>(ped); }
	FORCEINLINE void SET_PED_SCUBA_GEAR_VARIATION(Ped ped) { return YimMenu::NativeInvoker::Invoke<4123, void>(ped); }
	FORCEINLINE void CLEAR_PED_SCUBA_GEAR_VARIATION(Ped ped) { return YimMenu::NativeInvoker::Invoke<4124, void>(ped); }
	FORCEINLINE bool IS_USING_PED_SCUBA_GEAR_VARIATION(Any p0) { return YimMenu::NativeInvoker::Invoke<4125, bool>(p0); }
	FORCEINLINE void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4126, void>(ped, toggle); }
	FORCEINLINE void SET_PED_BOUNDS_ORIENTATION(Ped ped, float p1, float p2, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<4127, void>(ped, p1, p2, x, y, z); }
	FORCEINLINE void REGISTER_TARGET(Ped ped, Ped target) { return YimMenu::NativeInvoker::Invoke<4128, void>(ped, target); }
	FORCEINLINE void REGISTER_HATED_TARGETS_AROUND_PED(Ped ped, float radius) { return YimMenu::NativeInvoker::Invoke<4129, void>(ped, radius); }
	FORCEINLINE Ped GET_RANDOM_PED_AT_COORD(float x, float y, float z, float xRadius, float yRadius, float zRadius, int pedType) { return YimMenu::NativeInvoker::Invoke<4130, Ped>(x, y, z, xRadius, yRadius, zRadius, pedType); }
	FORCEINLINE bool GET_CLOSEST_PED(float x, float y, float z, float radius, bool p4, bool p5, Ped* outPed, bool p7, bool p8, int pedType) { return YimMenu::NativeInvoker::Invoke<4131, bool>(x, y, z, radius, p4, p5, outPed, p7, p8, pedType); }
	FORCEINLINE void SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(bool value) { return YimMenu::NativeInvoker::Invoke<4132, void>(value); }
	FORCEINLINE bool GET_CAN_PED_BE_GRABBED_BY_SCRIPT(Ped ped, bool p1, bool p2, bool p3, bool p4, bool p5, bool p6, bool p7, Any p8) { return YimMenu::NativeInvoker::Invoke<4133, bool>(ped, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void SET_DRIVER_RACING_MODIFIER(Ped driver, float modifier) { return YimMenu::NativeInvoker::Invoke<4134, void>(driver, modifier); }
	FORCEINLINE void SET_DRIVER_ABILITY(Ped driver, float ability) { return YimMenu::NativeInvoker::Invoke<4135, void>(driver, ability); }
	FORCEINLINE void SET_DRIVER_AGGRESSIVENESS(Ped driver, float aggressiveness) { return YimMenu::NativeInvoker::Invoke<4136, void>(driver, aggressiveness); }
	FORCEINLINE bool CAN_PED_RAGDOLL(Ped ped) { return YimMenu::NativeInvoker::Invoke<4137, bool>(ped); }
	FORCEINLINE bool SET_PED_TO_RAGDOLL(Ped ped, int time1, int time2, int ragdollType, bool p4, bool p5, bool p6) { return YimMenu::NativeInvoker::Invoke<4138, bool>(ped, time1, time2, ragdollType, p4, p5, p6); }
	FORCEINLINE bool SET_PED_TO_RAGDOLL_WITH_FALL(Ped ped, int time, int p2, int ragdollType, float x, float y, float z, float velocity, float p8, float p9, float p10, float p11, float p12, float p13) { return YimMenu::NativeInvoker::Invoke<4139, bool>(ped, time, p2, ragdollType, x, y, z, velocity, p8, p9, p10, p11, p12, p13); }
	FORCEINLINE void SET_PED_RAGDOLL_ON_COLLISION(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4140, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_RAGDOLL(Ped ped) { return YimMenu::NativeInvoker::Invoke<4141, bool>(ped); }
	FORCEINLINE bool IS_PED_RUNNING_RAGDOLL_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<4142, bool>(ped); }
	FORCEINLINE void SET_PED_RAGDOLL_FORCE_FALL(Ped ped) { return YimMenu::NativeInvoker::Invoke<4143, void>(ped); }
	FORCEINLINE void RESET_PED_RAGDOLL_TIMER(Ped ped) { return YimMenu::NativeInvoker::Invoke<4144, void>(ped); }
	FORCEINLINE void SET_PED_CAN_RAGDOLL(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4145, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_RUNNING_MELEE_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<4146, bool>(ped); }
	FORCEINLINE bool IS_PED_RUNNING_MOBILE_PHONE_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<4147, bool>(ped); }
	FORCEINLINE bool IS_MOBILE_PHONE_TO_PED_EAR(Ped ped) { return YimMenu::NativeInvoker::Invoke<4148, bool>(ped); }
	FORCEINLINE void SET_RAGDOLL_BLOCKING_FLAGS(Ped ped, int blockingFlag) { return YimMenu::NativeInvoker::Invoke<4149, void>(ped, blockingFlag); }
	FORCEINLINE void CLEAR_RAGDOLL_BLOCKING_FLAGS(Ped ped, int blockingFlag) { return YimMenu::NativeInvoker::Invoke<4150, void>(ped, blockingFlag); }
	FORCEINLINE void SET_PED_ANGLED_DEFENSIVE_AREA(Ped ped, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8, bool p9) { return YimMenu::NativeInvoker::Invoke<4151, void>(ped, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	FORCEINLINE void SET_PED_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius, bool p5, bool p6) { return YimMenu::NativeInvoker::Invoke<4152, void>(ped, x, y, z, radius, p5, p6); }
	FORCEINLINE void SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED(Ped ped, Ped target, float xOffset, float yOffset, float zOffset, float radius, bool p6) { return YimMenu::NativeInvoker::Invoke<4153, void>(ped, target, xOffset, yOffset, zOffset, radius, p6); }
	FORCEINLINE void SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_VEHICLE(Ped ped, Vehicle target, float xOffset, float yOffset, float zOffset, float radius, bool p6) { return YimMenu::NativeInvoker::Invoke<4154, void>(ped, target, xOffset, yOffset, zOffset, radius, p6); }
	FORCEINLINE void SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(Ped ped, Ped attachPed, float p2, float p3, float p4, float p5, float p6, float p7, float p8, bool p9, bool p10) { return YimMenu::NativeInvoker::Invoke<4155, void>(ped, attachPed, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	FORCEINLINE void SET_PED_DEFENSIVE_AREA_DIRECTION(Ped ped, float p1, float p2, float p3, bool p4) { return YimMenu::NativeInvoker::Invoke<4156, void>(ped, p1, p2, p3, p4); }
	FORCEINLINE void REMOVE_PED_DEFENSIVE_AREA(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4157, void>(ped, toggle); }
	FORCEINLINE Vector3 GET_PED_DEFENSIVE_AREA_POSITION(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4158, Vector3>(ped, p1); }
	FORCEINLINE bool IS_PED_DEFENSIVE_AREA_ACTIVE(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4159, bool>(ped, p1); }
	FORCEINLINE void SET_PED_PREFERRED_COVER_SET(Ped ped, Any itemSet) { return YimMenu::NativeInvoker::Invoke<4160, void>(ped, itemSet); }
	FORCEINLINE void REMOVE_PED_PREFERRED_COVER_SET(Ped ped) { return YimMenu::NativeInvoker::Invoke<4161, void>(ped); }
	FORCEINLINE void REVIVE_INJURED_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4162, void>(ped); }
	FORCEINLINE void RESURRECT_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4163, void>(ped); }
	FORCEINLINE void SET_PED_NAME_DEBUG(Ped ped, const char* name) { return YimMenu::NativeInvoker::Invoke<4164, void>(ped, name); }
	FORCEINLINE Vector3 GET_PED_EXTRACTED_DISPLACEMENT(Ped ped, bool worldSpace) { return YimMenu::NativeInvoker::Invoke<4165, Vector3>(ped, worldSpace); }
	FORCEINLINE void SET_PED_DIES_WHEN_INJURED(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4166, void>(ped, toggle); }
	FORCEINLINE void SET_PED_ENABLE_WEAPON_BLOCKING(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4167, void>(ped, toggle); }
	FORCEINLINE void SPECIAL_FUNCTION_DO_NOT_USE(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4168, void>(ped, p1); }
	FORCEINLINE void RESET_PED_VISIBLE_DAMAGE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4169, void>(ped); }
	FORCEINLINE void APPLY_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, Any p1, float p2, float p3, Any p4) { return YimMenu::NativeInvoker::Invoke<4170, void>(ped, p1, p2, p3, p4); }
	FORCEINLINE void APPLY_PED_BLOOD(Ped ped, int boneIndex, float xRot, float yRot, float zRot, const char* woundType) { return YimMenu::NativeInvoker::Invoke<4171, void>(ped, boneIndex, xRot, yRot, zRot, woundType); }
	FORCEINLINE void APPLY_PED_BLOOD_BY_ZONE(Ped ped, int p1, float p2, float p3, const char* p4) { return YimMenu::NativeInvoker::Invoke<4172, void>(ped, p1, p2, p3, p4); }
	FORCEINLINE void APPLY_PED_BLOOD_SPECIFIC(Ped ped, int p1, float p2, float p3, float p4, float p5, int p6, float p7, const char* p8) { return YimMenu::NativeInvoker::Invoke<4173, void>(ped, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void APPLY_PED_DAMAGE_DECAL(Ped ped, int damageZone, float xOffset, float yOffset, float heading, float scale, float alpha, int variation, bool fadeIn, const char* decalName) { return YimMenu::NativeInvoker::Invoke<4174, void>(ped, damageZone, xOffset, yOffset, heading, scale, alpha, variation, fadeIn, decalName); }
	FORCEINLINE void APPLY_PED_DAMAGE_PACK(Ped ped, const char* damagePack, float damage, float mult) { return YimMenu::NativeInvoker::Invoke<4175, void>(ped, damagePack, damage, mult); }
	FORCEINLINE void CLEAR_PED_BLOOD_DAMAGE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4176, void>(ped); }
	FORCEINLINE void CLEAR_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, int p1) { return YimMenu::NativeInvoker::Invoke<4177, void>(ped, p1); }
	FORCEINLINE void HIDE_PED_BLOOD_DAMAGE_BY_ZONE(Ped ped, Any p1, bool p2) { return YimMenu::NativeInvoker::Invoke<4178, void>(ped, p1, p2); }
	FORCEINLINE void CLEAR_PED_DAMAGE_DECAL_BY_ZONE(Ped ped, int p1, const char* p2) { return YimMenu::NativeInvoker::Invoke<4179, void>(ped, p1, p2); }
	FORCEINLINE int GET_PED_DECORATIONS_STATE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4180, int>(ped); }
	FORCEINLINE void MARK_PED_DECORATIONS_AS_CLONED_FROM_LOCAL_PLAYER(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4181, void>(ped, p1); }
	FORCEINLINE void CLEAR_PED_WETNESS(Ped ped) { return YimMenu::NativeInvoker::Invoke<4182, void>(ped); }
	FORCEINLINE void SET_PED_WETNESS_HEIGHT(Ped ped, float height) { return YimMenu::NativeInvoker::Invoke<4183, void>(ped, height); }
	FORCEINLINE void SET_PED_WETNESS_ENABLED_THIS_FRAME(Ped ped) { return YimMenu::NativeInvoker::Invoke<4184, void>(ped); }
	FORCEINLINE void SET_PED_WETNESS(Ped ped, float wetLevel) { return YimMenu::NativeInvoker::Invoke<4185, void>(ped, wetLevel); }
	FORCEINLINE void CLEAR_PED_ENV_DIRT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4186, void>(ped); }
	FORCEINLINE void SET_PED_SWEAT(Ped ped, float sweat) { return YimMenu::NativeInvoker::Invoke<4187, void>(ped, sweat); }
	FORCEINLINE void ADD_PED_DECORATION_FROM_HASHES(Ped ped, Hash collection, Hash overlay) { return YimMenu::NativeInvoker::Invoke<4188, void>(ped, collection, overlay); }
	FORCEINLINE void ADD_PED_DECORATION_FROM_HASHES_IN_CORONA(Ped ped, Hash collection, Hash overlay) { return YimMenu::NativeInvoker::Invoke<4189, void>(ped, collection, overlay); }
	FORCEINLINE int GET_PED_DECORATION_ZONE_FROM_HASHES(Hash collection, Hash overlay) { return YimMenu::NativeInvoker::Invoke<4190, int>(collection, overlay); }
	FORCEINLINE void CLEAR_PED_DECORATIONS(Ped ped) { return YimMenu::NativeInvoker::Invoke<4191, void>(ped); }
	FORCEINLINE void CLEAR_PED_DECORATIONS_LEAVE_SCARS(Ped ped) { return YimMenu::NativeInvoker::Invoke<4192, void>(ped); }
	FORCEINLINE bool WAS_PED_SKELETON_UPDATED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4193, bool>(ped); }
	FORCEINLINE Vector3 GET_PED_BONE_COORDS(Ped ped, int boneId, float offsetX, float offsetY, float offsetZ) { return YimMenu::NativeInvoker::Invoke<4194, Vector3>(ped, boneId, offsetX, offsetY, offsetZ); }
	FORCEINLINE void CREATE_NM_MESSAGE(bool startImmediately, int messageId) { return YimMenu::NativeInvoker::Invoke<4195, void>(startImmediately, messageId); }
	FORCEINLINE void GIVE_PED_NM_MESSAGE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4196, void>(ped); }
	FORCEINLINE int ADD_SCENARIO_BLOCKING_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool p6, bool p7, bool p8, bool p9) { return YimMenu::NativeInvoker::Invoke<4197, int>(x1, y1, z1, x2, y2, z2, p6, p7, p8, p9); }
	FORCEINLINE void REMOVE_SCENARIO_BLOCKING_AREAS() { return YimMenu::NativeInvoker::Invoke<4198, void>(); }
	FORCEINLINE void REMOVE_SCENARIO_BLOCKING_AREA(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<4199, void>(p0, p1); }
	FORCEINLINE void SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(float x, float y, float z, float range, int p4) { return YimMenu::NativeInvoker::Invoke<4200, void>(x, y, z, range, p4); }
	FORCEINLINE bool DOES_SCENARIO_BLOCKING_AREA_EXISTS(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<4201, bool>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE bool IS_PED_USING_SCENARIO(Ped ped, const char* scenario) { return YimMenu::NativeInvoker::Invoke<4202, bool>(ped, scenario); }
	FORCEINLINE bool IS_PED_USING_ANY_SCENARIO(Ped ped) { return YimMenu::NativeInvoker::Invoke<4203, bool>(ped); }
	FORCEINLINE bool SET_PED_PANIC_EXIT_SCENARIO(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4204, bool>(p0, p1, p2, p3); }
	FORCEINLINE void TOGGLE_SCENARIO_PED_COWER_IN_PLACE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4205, void>(ped, toggle); }
	FORCEINLINE bool TRIGGER_PED_SCENARIO_PANICEXITTOFLEE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4206, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool SET_PED_SHOULD_PLAY_DIRECTED_NORMAL_SCENARIO_EXIT(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4207, bool>(p0, p1, p2, p3); }
	FORCEINLINE void SET_PED_SHOULD_PLAY_NORMAL_SCENARIO_EXIT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4208, void>(ped); }
	FORCEINLINE void SET_PED_SHOULD_PLAY_IMMEDIATE_SCENARIO_EXIT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4209, void>(ped); }
	FORCEINLINE bool SET_PED_SHOULD_PLAY_FLEE_SCENARIO_EXIT(Ped ped, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4210, bool>(ped, p1, p2, p3); }
	FORCEINLINE void SET_PED_SHOULD_IGNORE_SCENARIO_EXIT_COLLISION_CHECKS(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4211, void>(ped, p1); }
	FORCEINLINE void SET_PED_SHOULD_IGNORE_SCENARIO_NAV_CHECKS(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<4212, void>(p0, p1); }
	FORCEINLINE void SET_PED_SHOULD_PROBE_FOR_SCENARIO_EXITS_IN_ONE_FRAME(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<4213, void>(p0, p1); }
	FORCEINLINE bool IS_PED_GESTURING(Any p0) { return YimMenu::NativeInvoker::Invoke<4214, bool>(p0); }
	FORCEINLINE void RESET_FACIAL_IDLE_ANIM(Ped ped) { return YimMenu::NativeInvoker::Invoke<4215, void>(ped); }
	FORCEINLINE void PLAY_FACIAL_ANIM(Ped ped, const char* animName, const char* animDict) { return YimMenu::NativeInvoker::Invoke<4216, void>(ped, animName, animDict); }
	FORCEINLINE void SET_FACIAL_CLIPSET(Ped ped, const char* animDict) { return YimMenu::NativeInvoker::Invoke<4217, void>(ped, animDict); }
	FORCEINLINE void SET_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped, const char* animName, const char* animDict) { return YimMenu::NativeInvoker::Invoke<4218, void>(ped, animName, animDict); }
	FORCEINLINE void CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4219, void>(ped); }
	FORCEINLINE void SET_PED_CAN_PLAY_GESTURE_ANIMS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4220, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_PLAY_VISEME_ANIMS(Ped ped, bool toggle, bool p2) { return YimMenu::NativeInvoker::Invoke<4221, void>(ped, toggle, p2); }
	FORCEINLINE void SET_PED_IS_IGNORED_BY_AUTO_OPEN_DOORS(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4222, void>(ped, p1); }
	FORCEINLINE void SET_PED_CAN_PLAY_AMBIENT_ANIMS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4223, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4224, void>(ped, toggle); }
	FORCEINLINE void TRIGGER_IDLE_ANIMATION_ON_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4225, void>(ped); }
	FORCEINLINE void SET_PED_CAN_ARM_IK(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4226, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_HEAD_IK(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4227, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_LEG_IK(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4228, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_TORSO_IK(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4229, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_TORSO_REACT_IK(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4230, void>(ped, p1); }
	FORCEINLINE void SET_PED_CAN_TORSO_VEHICLE_IK(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4231, void>(ped, p1); }
	FORCEINLINE void SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4232, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_HEADTRACKING_PED(Ped ped1, Ped ped2) { return YimMenu::NativeInvoker::Invoke<4233, bool>(ped1, ped2); }
	FORCEINLINE bool IS_PED_HEADTRACKING_ENTITY(Ped ped, Entity entity) { return YimMenu::NativeInvoker::Invoke<4234, bool>(ped, entity); }
	FORCEINLINE void SET_PED_PRIMARY_LOOKAT(Ped ped, Ped lookAt) { return YimMenu::NativeInvoker::Invoke<4235, void>(ped, lookAt); }
	FORCEINLINE void SET_PED_CLOTH_PIN_FRAMES(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4236, void>(p0, p1); }
	FORCEINLINE void SET_PED_CLOTH_PACKAGE_INDEX(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4237, void>(p0, p1); }
	FORCEINLINE void SET_PED_CLOTH_PRONE(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<4238, void>(p0, p1); }
	FORCEINLINE void SET_PED_CONFIG_FLAG(Ped ped, int flagId, bool value) { return YimMenu::NativeInvoker::Invoke<4239, void>(ped, flagId, value); }
	FORCEINLINE void SET_PED_RESET_FLAG(Ped ped, int flagId, bool doReset) { return YimMenu::NativeInvoker::Invoke<4240, void>(ped, flagId, doReset); }
	FORCEINLINE bool GET_PED_CONFIG_FLAG(Ped ped, int flagId, bool p2) { return YimMenu::NativeInvoker::Invoke<4241, bool>(ped, flagId, p2); }
	FORCEINLINE bool GET_PED_RESET_FLAG(Ped ped, int flagId) { return YimMenu::NativeInvoker::Invoke<4242, bool>(ped, flagId); }
	FORCEINLINE void SET_PED_GROUP_MEMBER_PASSENGER_INDEX(Ped ped, int index) { return YimMenu::NativeInvoker::Invoke<4243, void>(ped, index); }
	FORCEINLINE void SET_PED_CAN_EVASIVE_DIVE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4244, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_EVASIVE_DIVING(Ped ped, Entity* evadingEntity) { return YimMenu::NativeInvoker::Invoke<4245, bool>(ped, evadingEntity); }
	FORCEINLINE void SET_PED_SHOOTS_AT_COORD(Ped ped, float x, float y, float z, bool toggle) { return YimMenu::NativeInvoker::Invoke<4246, void>(ped, x, y, z, toggle); }
	FORCEINLINE void SET_PED_MODEL_IS_SUPPRESSED(Hash modelHash, bool toggle) { return YimMenu::NativeInvoker::Invoke<4247, void>(modelHash, toggle); }
	FORCEINLINE void STOP_ANY_PED_MODEL_BEING_SUPPRESSED() { return YimMenu::NativeInvoker::Invoke<4248, void>(); }
	FORCEINLINE void SET_PED_CAN_BE_TARGETED_WHEN_INJURED(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4249, void>(ped, toggle); }
	FORCEINLINE void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4250, void>(ped, toggle); }
	FORCEINLINE void BLOCK_PED_FROM_GENERATING_DEAD_BODY_EVENTS_WHEN_DEAD(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4251, void>(ped, toggle); }
	FORCEINLINE void SET_PED_WILL_ONLY_ATTACK_WANTED_PLAYER(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4252, void>(p0, p1); }
	FORCEINLINE void SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4253, void>(ped, toggle); }
	FORCEINLINE void GIVE_PED_HELMET(Ped ped, bool cannotRemove, int helmetFlag, int textureIndex) { return YimMenu::NativeInvoker::Invoke<4254, void>(ped, cannotRemove, helmetFlag, textureIndex); }
	FORCEINLINE void REMOVE_PED_HELMET(Ped ped, bool instantly) { return YimMenu::NativeInvoker::Invoke<4255, void>(ped, instantly); }
	FORCEINLINE bool IS_PED_TAKING_OFF_HELMET(Ped ped) { return YimMenu::NativeInvoker::Invoke<4256, bool>(ped); }
	FORCEINLINE void SET_PED_HELMET(Ped ped, bool canWearHelmet) { return YimMenu::NativeInvoker::Invoke<4257, void>(ped, canWearHelmet); }
	FORCEINLINE void SET_PED_HELMET_FLAG(Ped ped, int helmetFlag) { return YimMenu::NativeInvoker::Invoke<4258, void>(ped, helmetFlag); }
	FORCEINLINE void SET_PED_HELMET_PROP_INDEX(Ped ped, int propIndex, bool p2) { return YimMenu::NativeInvoker::Invoke<4259, void>(ped, propIndex, p2); }
	FORCEINLINE void SET_PED_HELMET_VISOR_PROP_INDICES(Ped ped, bool p1, int p2, int p3) { return YimMenu::NativeInvoker::Invoke<4260, void>(ped, p1, p2, p3); }
	FORCEINLINE bool IS_PED_HELMET_VISOR_UP(Ped ped) { return YimMenu::NativeInvoker::Invoke<4261, bool>(ped); }
	FORCEINLINE void SET_PED_HELMET_TEXTURE_INDEX(Ped ped, int textureIndex) { return YimMenu::NativeInvoker::Invoke<4262, void>(ped, textureIndex); }
	FORCEINLINE bool IS_PED_WEARING_HELMET(Ped ped) { return YimMenu::NativeInvoker::Invoke<4263, bool>(ped); }
	FORCEINLINE void CLEAR_PED_STORED_HAT_PROP(Ped ped) { return YimMenu::NativeInvoker::Invoke<4264, void>(ped); }
	FORCEINLINE int GET_PED_HELMET_STORED_HAT_PROP_INDEX(Ped ped) { return YimMenu::NativeInvoker::Invoke<4265, int>(ped); }
	FORCEINLINE int GET_PED_HELMET_STORED_HAT_TEX_INDEX(Ped ped) { return YimMenu::NativeInvoker::Invoke<4266, int>(ped); }
	FORCEINLINE bool IS_CURRENT_HEAD_PROP_A_HELMET(Any p0) { return YimMenu::NativeInvoker::Invoke<4267, bool>(p0); }
	FORCEINLINE void SET_PED_TO_LOAD_COVER(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4268, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_COWER_IN_COVER(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4269, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_PEEK_IN_COVER(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4270, void>(ped, toggle); }
	FORCEINLINE void SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4271, void>(ped, toggle); }
	FORCEINLINE void SET_PED_LEG_IK_MODE(Ped ped, int mode) { return YimMenu::NativeInvoker::Invoke<4272, void>(ped, mode); }
	FORCEINLINE void SET_PED_MOTION_BLUR(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4273, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CAN_SWITCH_WEAPON(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4274, void>(ped, toggle); }
	FORCEINLINE void SET_PED_DIES_INSTANTLY_IN_WATER(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4275, void>(ped, toggle); }
	FORCEINLINE void SET_LADDER_CLIMB_INPUT_STATE(Ped ped, int p1) { return YimMenu::NativeInvoker::Invoke<4276, void>(ped, p1); }
	FORCEINLINE void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4277, void>(ped); }
	FORCEINLINE void SET_SCRIPTED_ANIM_SEAT_OFFSET(Ped ped, float p1) { return YimMenu::NativeInvoker::Invoke<4278, void>(ped, p1); }
	FORCEINLINE void SET_PED_COMBAT_MOVEMENT(Ped ped, int combatMovement) { return YimMenu::NativeInvoker::Invoke<4279, void>(ped, combatMovement); }
	FORCEINLINE int GET_PED_COMBAT_MOVEMENT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4280, int>(ped); }
	FORCEINLINE void SET_PED_COMBAT_ABILITY(Ped ped, int abilityLevel) { return YimMenu::NativeInvoker::Invoke<4281, void>(ped, abilityLevel); }
	FORCEINLINE void SET_PED_COMBAT_RANGE(Ped ped, int combatRange) { return YimMenu::NativeInvoker::Invoke<4282, void>(ped, combatRange); }
	FORCEINLINE int GET_PED_COMBAT_RANGE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4283, int>(ped); }
	FORCEINLINE void SET_PED_COMBAT_ATTRIBUTES(Ped ped, int attributeId, bool enabled) { return YimMenu::NativeInvoker::Invoke<4284, void>(ped, attributeId, enabled); }
	FORCEINLINE void SET_PED_TARGET_LOSS_RESPONSE(Ped ped, int responseType) { return YimMenu::NativeInvoker::Invoke<4285, void>(ped, responseType); }
	FORCEINLINE bool IS_PED_PERFORMING_MELEE_ACTION(Ped ped) { return YimMenu::NativeInvoker::Invoke<4286, bool>(ped); }
	FORCEINLINE bool IS_PED_PERFORMING_STEALTH_KILL(Ped ped) { return YimMenu::NativeInvoker::Invoke<4287, bool>(ped); }
	FORCEINLINE bool IS_PED_PERFORMING_A_COUNTER_ATTACK(Ped ped) { return YimMenu::NativeInvoker::Invoke<4288, bool>(ped); }
	FORCEINLINE bool IS_PED_BEING_STEALTH_KILLED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4289, bool>(ped); }
	FORCEINLINE Ped GET_MELEE_TARGET_FOR_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4290, Ped>(ped); }
	FORCEINLINE bool WAS_PED_KILLED_BY_STEALTH(Ped ped) { return YimMenu::NativeInvoker::Invoke<4291, bool>(ped); }
	FORCEINLINE bool WAS_PED_KILLED_BY_TAKEDOWN(Ped ped) { return YimMenu::NativeInvoker::Invoke<4292, bool>(ped); }
	FORCEINLINE bool WAS_PED_KNOCKED_OUT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4293, bool>(ped); }
	FORCEINLINE void SET_PED_FLEE_ATTRIBUTES(Ped ped, int attributeFlags, bool enable) { return YimMenu::NativeInvoker::Invoke<4294, void>(ped, attributeFlags, enable); }
	FORCEINLINE void SET_PED_COWER_HASH(Ped ped, const char* p1) { return YimMenu::NativeInvoker::Invoke<4295, void>(ped, p1); }
	FORCEINLINE void SET_PED_STEERS_AROUND_DEAD_BODIES(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4296, void>(ped, toggle); }
	FORCEINLINE void SET_PED_STEERS_AROUND_PEDS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4297, void>(ped, toggle); }
	FORCEINLINE void SET_PED_STEERS_AROUND_OBJECTS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4298, void>(ped, toggle); }
	FORCEINLINE void SET_PED_STEERS_AROUND_VEHICLES(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4299, void>(ped, toggle); }
	FORCEINLINE void SET_PED_IS_AVOIDED_BY_OTHERS(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<4300, void>(p0, p1); }
	FORCEINLINE void SET_PED_INCREASED_AVOIDANCE_RADIUS(Ped ped) { return YimMenu::NativeInvoker::Invoke<4301, void>(ped); }
	FORCEINLINE void SET_PED_BLOCKS_PATHING_WHEN_DEAD(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4302, void>(ped, toggle); }
	FORCEINLINE void SET_PED_NO_TIME_DELAY_BEFORE_SHOT(Any p0) { return YimMenu::NativeInvoker::Invoke<4303, void>(p0); }
	FORCEINLINE bool IS_ANY_PED_NEAR_POINT(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<4304, bool>(x, y, z, radius); }
	FORCEINLINE void FORCE_PED_AI_AND_ANIMATION_UPDATE(Ped ped, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<4305, void>(ped, p1, p2); }
	FORCEINLINE bool IS_PED_HEADING_TOWARDS_POSITION(Ped ped, float x, float y, float z, float p4) { return YimMenu::NativeInvoker::Invoke<4306, bool>(ped, x, y, z, p4); }
	FORCEINLINE void REQUEST_PED_VISIBILITY_TRACKING(Ped ped) { return YimMenu::NativeInvoker::Invoke<4307, void>(ped); }
	FORCEINLINE void REQUEST_PED_VEHICLE_VISIBILITY_TRACKING(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4308, void>(ped, p1); }
	FORCEINLINE void REQUEST_PED_RESTRICTED_VEHICLE_VISIBILITY_TRACKING(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4309, void>(ped, p1); }
	FORCEINLINE void REQUEST_PED_USE_SMALL_BBOX_VISIBILITY_TRACKING(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<4310, void>(ped, p1); }
	FORCEINLINE bool IS_TRACKED_PED_VISIBLE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4311, bool>(ped); }
	FORCEINLINE int GET_TRACKED_PED_PIXELCOUNT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4312, int>(ped); }
	FORCEINLINE bool IS_PED_TRACKED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4313, bool>(ped); }
	FORCEINLINE bool HAS_PED_RECEIVED_EVENT(Ped ped, int eventId) { return YimMenu::NativeInvoker::Invoke<4314, bool>(ped, eventId); }
	FORCEINLINE bool CAN_PED_SEE_HATED_PED(Ped ped1, Ped ped2) { return YimMenu::NativeInvoker::Invoke<4315, bool>(ped1, ped2); }
	FORCEINLINE bool CAN_PED_SHUFFLE_TO_OR_FROM_TURRET_SEAT(Ped ped, int* p1) { return YimMenu::NativeInvoker::Invoke<4316, bool>(ped, p1); }
	FORCEINLINE bool CAN_PED_SHUFFLE_TO_OR_FROM_EXTRA_SEAT(Ped ped, int* p1) { return YimMenu::NativeInvoker::Invoke<4317, bool>(ped, p1); }
	FORCEINLINE int GET_PED_BONE_INDEX(Ped ped, int boneId) { return YimMenu::NativeInvoker::Invoke<4318, int>(ped, boneId); }
	FORCEINLINE int GET_PED_RAGDOLL_BONE_INDEX(Ped ped, int bone) { return YimMenu::NativeInvoker::Invoke<4319, int>(ped, bone); }
	FORCEINLINE void SET_PED_ENVEFF_SCALE(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<4320, void>(ped, value); }
	FORCEINLINE float GET_PED_ENVEFF_SCALE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4321, float>(ped); }
	FORCEINLINE void SET_ENABLE_PED_ENVEFF_SCALE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4322, void>(ped, toggle); }
	FORCEINLINE void SET_PED_ENVEFF_CPV_ADD(Ped ped, float p1) { return YimMenu::NativeInvoker::Invoke<4323, void>(ped, p1); }
	FORCEINLINE void SET_PED_ENVEFF_COLOR_MODULATOR(Ped ped, int p1, int p2, int p3) { return YimMenu::NativeInvoker::Invoke<4324, void>(ped, p1, p2, p3); }
	FORCEINLINE void SET_PED_EMISSIVE_SCALE(Ped ped, float intensity) { return YimMenu::NativeInvoker::Invoke<4325, void>(ped, intensity); }
	FORCEINLINE float GET_PED_EMISSIVE_SCALE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4326, float>(ped); }
	FORCEINLINE bool IS_PED_SHADER_READY(Ped ped) { return YimMenu::NativeInvoker::Invoke<4327, bool>(ped); }
	FORCEINLINE void SET_PED_ENABLE_CREW_EMBLEM(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4328, void>(ped, toggle); }
	FORCEINLINE void REQUEST_RAGDOLL_BOUNDS_UPDATE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4329, void>(p0, p1); }
	FORCEINLINE void SET_PED_AO_BLOB_RENDERING(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4330, void>(ped, toggle); }
	FORCEINLINE bool IS_PED_SHELTERED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4331, bool>(ped); }
	FORCEINLINE int CREATE_SYNCHRONIZED_SCENE(float x, float y, float z, float roll, float pitch, float yaw, int p6) { return YimMenu::NativeInvoker::Invoke<4332, int>(x, y, z, roll, pitch, yaw, p6); }
	FORCEINLINE int CREATE_SYNCHRONIZED_SCENE_AT_MAP_OBJECT(float x, float y, float z, float radius, Hash object) { return YimMenu::NativeInvoker::Invoke<4333, int>(x, y, z, radius, object); }
	FORCEINLINE bool IS_SYNCHRONIZED_SCENE_RUNNING(int sceneId) { return YimMenu::NativeInvoker::Invoke<4334, bool>(sceneId); }
	FORCEINLINE void SET_SYNCHRONIZED_SCENE_ORIGIN(int sceneID, float x, float y, float z, float roll, float pitch, float yaw, bool p7) { return YimMenu::NativeInvoker::Invoke<4335, void>(sceneID, x, y, z, roll, pitch, yaw, p7); }
	FORCEINLINE void SET_SYNCHRONIZED_SCENE_PHASE(int sceneID, float phase) { return YimMenu::NativeInvoker::Invoke<4336, void>(sceneID, phase); }
	FORCEINLINE float GET_SYNCHRONIZED_SCENE_PHASE(int sceneID) { return YimMenu::NativeInvoker::Invoke<4337, float>(sceneID); }
	FORCEINLINE void SET_SYNCHRONIZED_SCENE_RATE(int sceneID, float rate) { return YimMenu::NativeInvoker::Invoke<4338, void>(sceneID, rate); }
	FORCEINLINE float GET_SYNCHRONIZED_SCENE_RATE(int sceneID) { return YimMenu::NativeInvoker::Invoke<4339, float>(sceneID); }
	FORCEINLINE void SET_SYNCHRONIZED_SCENE_LOOPED(int sceneID, bool toggle) { return YimMenu::NativeInvoker::Invoke<4340, void>(sceneID, toggle); }
	FORCEINLINE bool IS_SYNCHRONIZED_SCENE_LOOPED(int sceneID) { return YimMenu::NativeInvoker::Invoke<4341, bool>(sceneID); }
	FORCEINLINE void SET_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(int sceneID, bool toggle) { return YimMenu::NativeInvoker::Invoke<4342, void>(sceneID, toggle); }
	FORCEINLINE bool IS_SYNCHRONIZED_SCENE_HOLD_LAST_FRAME(int sceneID) { return YimMenu::NativeInvoker::Invoke<4343, bool>(sceneID); }
	FORCEINLINE void ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(int sceneID, Entity entity, int boneIndex) { return YimMenu::NativeInvoker::Invoke<4344, void>(sceneID, entity, boneIndex); }
	FORCEINLINE void DETACH_SYNCHRONIZED_SCENE(int sceneID) { return YimMenu::NativeInvoker::Invoke<4345, void>(sceneID); }
	FORCEINLINE void TAKE_OWNERSHIP_OF_SYNCHRONIZED_SCENE(int scene) { return YimMenu::NativeInvoker::Invoke<4346, void>(scene); }
	FORCEINLINE bool FORCE_PED_MOTION_STATE(Ped ped, Hash motionStateHash, bool p2, int p3, bool p4) { return YimMenu::NativeInvoker::Invoke<4347, bool>(ped, motionStateHash, p2, p3, p4); }
	FORCEINLINE bool GET_PED_CURRENT_MOVE_BLEND_RATIO(Ped ped, float* speedX, float* speedY) { return YimMenu::NativeInvoker::Invoke<4348, bool>(ped, speedX, speedY); }
	FORCEINLINE void SET_PED_MAX_MOVE_BLEND_RATIO(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<4349, void>(ped, value); }
	FORCEINLINE void SET_PED_MIN_MOVE_BLEND_RATIO(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<4350, void>(ped, value); }
	FORCEINLINE void SET_PED_MOVE_RATE_OVERRIDE(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<4351, void>(ped, value); }
	FORCEINLINE void SET_PED_MOVE_RATE_IN_WATER_OVERRIDE(Ped ped, float p1) { return YimMenu::NativeInvoker::Invoke<4352, void>(ped, p1); }
	FORCEINLINE bool PED_HAS_SEXINESS_FLAG_SET(Ped ped, int sexinessFlag) { return YimMenu::NativeInvoker::Invoke<4353, bool>(ped, sexinessFlag); }
	FORCEINLINE int GET_PED_NEARBY_VEHICLES(Ped ped, Any* sizeAndVehs) { return YimMenu::NativeInvoker::Invoke<4354, int>(ped, sizeAndVehs); }
	FORCEINLINE int GET_PED_NEARBY_PEDS(Ped ped, Any* sizeAndPeds, int ignore) { return YimMenu::NativeInvoker::Invoke<4355, int>(ped, sizeAndPeds, ignore); }
	FORCEINLINE bool HAVE_ALL_STREAMING_REQUESTS_COMPLETED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4356, bool>(ped); }
	FORCEINLINE bool IS_PED_USING_ACTION_MODE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4357, bool>(ped); }
	FORCEINLINE void SET_PED_USING_ACTION_MODE(Ped ped, bool p1, int p2, const char* action) { return YimMenu::NativeInvoker::Invoke<4358, void>(ped, p1, p2, action); }
	FORCEINLINE void SET_MOVEMENT_MODE_OVERRIDE(Ped ped, const char* name) { return YimMenu::NativeInvoker::Invoke<4359, void>(ped, name); }
	FORCEINLINE void SET_PED_CAPSULE(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<4360, void>(ped, value); }
	FORCEINLINE int REGISTER_PEDHEADSHOT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4361, int>(ped); }
	FORCEINLINE int REGISTER_PEDHEADSHOT_HIRES(Ped ped) { return YimMenu::NativeInvoker::Invoke<4362, int>(ped); }
	FORCEINLINE int REGISTER_PEDHEADSHOT_TRANSPARENT(Ped ped) { return YimMenu::NativeInvoker::Invoke<4363, int>(ped); }
	FORCEINLINE void UNREGISTER_PEDHEADSHOT(int id) { return YimMenu::NativeInvoker::Invoke<4364, void>(id); }
	FORCEINLINE bool IS_PEDHEADSHOT_VALID(int id) { return YimMenu::NativeInvoker::Invoke<4365, bool>(id); }
	FORCEINLINE bool IS_PEDHEADSHOT_READY(int id) { return YimMenu::NativeInvoker::Invoke<4366, bool>(id); }
	FORCEINLINE const char* GET_PEDHEADSHOT_TXD_STRING(int id) { return YimMenu::NativeInvoker::Invoke<4367, const char*>(id); }
	FORCEINLINE bool REQUEST_PEDHEADSHOT_IMG_UPLOAD(int id) { return YimMenu::NativeInvoker::Invoke<4368, bool>(id); }
	FORCEINLINE void RELEASE_PEDHEADSHOT_IMG_UPLOAD(int id) { return YimMenu::NativeInvoker::Invoke<4369, void>(id); }
	FORCEINLINE bool IS_PEDHEADSHOT_IMG_UPLOAD_AVAILABLE() { return YimMenu::NativeInvoker::Invoke<4370, bool>(); }
	FORCEINLINE bool HAS_PEDHEADSHOT_IMG_UPLOAD_FAILED() { return YimMenu::NativeInvoker::Invoke<4371, bool>(); }
	FORCEINLINE bool HAS_PEDHEADSHOT_IMG_UPLOAD_SUCCEEDED() { return YimMenu::NativeInvoker::Invoke<4372, bool>(); }
	FORCEINLINE void SET_PED_HEATSCALE_OVERRIDE(Ped ped, float heatScale) { return YimMenu::NativeInvoker::Invoke<4373, void>(ped, heatScale); }
	FORCEINLINE void DISABLE_PED_HEATSCALE_OVERRIDE(Ped ped) { return YimMenu::NativeInvoker::Invoke<4374, void>(ped); }
	FORCEINLINE void SPAWNPOINTS_START_SEARCH(float p0, float p1, float p2, float p3, float p4, int interiorFlags, float scale, int duration) { return YimMenu::NativeInvoker::Invoke<4375, void>(p0, p1, p2, p3, p4, interiorFlags, scale, duration); }
	FORCEINLINE void SPAWNPOINTS_START_SEARCH_IN_ANGLED_AREA(float x1, float y1, float z1, float x2, float y2, float z2, float width, int interiorFlags, float scale, int duration) { return YimMenu::NativeInvoker::Invoke<4376, void>(x1, y1, z1, x2, y2, z2, width, interiorFlags, scale, duration); }
	FORCEINLINE void SPAWNPOINTS_CANCEL_SEARCH() { return YimMenu::NativeInvoker::Invoke<4377, void>(); }
	FORCEINLINE bool SPAWNPOINTS_IS_SEARCH_ACTIVE() { return YimMenu::NativeInvoker::Invoke<4378, bool>(); }
	FORCEINLINE bool SPAWNPOINTS_IS_SEARCH_COMPLETE() { return YimMenu::NativeInvoker::Invoke<4379, bool>(); }
	FORCEINLINE bool SPAWNPOINTS_IS_SEARCH_FAILED() { return YimMenu::NativeInvoker::Invoke<4380, bool>(); }
	FORCEINLINE int SPAWNPOINTS_GET_NUM_SEARCH_RESULTS() { return YimMenu::NativeInvoker::Invoke<4381, int>(); }
	FORCEINLINE void SPAWNPOINTS_GET_SEARCH_RESULT(int randomInt, float* x, float* y, float* z) { return YimMenu::NativeInvoker::Invoke<4382, void>(randomInt, x, y, z); }
	FORCEINLINE void SPAWNPOINTS_GET_SEARCH_RESULT_FLAGS(int p0, int* p1) { return YimMenu::NativeInvoker::Invoke<4383, void>(p0, p1); }
	FORCEINLINE void SET_IK_TARGET(Ped ped, int ikIndex, Entity entityLookAt, int boneLookAt, float offsetX, float offsetY, float offsetZ, Any p7, int blendInDuration, int blendOutDuration) { return YimMenu::NativeInvoker::Invoke<4384, void>(ped, ikIndex, entityLookAt, boneLookAt, offsetX, offsetY, offsetZ, p7, blendInDuration, blendOutDuration); }
	FORCEINLINE void FORCE_INSTANT_LEG_IK_SETUP(Ped ped) { return YimMenu::NativeInvoker::Invoke<4385, void>(ped); }
	FORCEINLINE void REQUEST_ACTION_MODE_ASSET(const char* asset) { return YimMenu::NativeInvoker::Invoke<4386, void>(asset); }
	FORCEINLINE bool HAS_ACTION_MODE_ASSET_LOADED(const char* asset) { return YimMenu::NativeInvoker::Invoke<4387, bool>(asset); }
	FORCEINLINE void REMOVE_ACTION_MODE_ASSET(const char* asset) { return YimMenu::NativeInvoker::Invoke<4388, void>(asset); }
	FORCEINLINE void REQUEST_STEALTH_MODE_ASSET(const char* asset) { return YimMenu::NativeInvoker::Invoke<4389, void>(asset); }
	FORCEINLINE bool HAS_STEALTH_MODE_ASSET_LOADED(const char* asset) { return YimMenu::NativeInvoker::Invoke<4390, bool>(asset); }
	FORCEINLINE void REMOVE_STEALTH_MODE_ASSET(const char* asset) { return YimMenu::NativeInvoker::Invoke<4391, void>(asset); }
	FORCEINLINE void SET_PED_LOD_MULTIPLIER(Ped ped, float multiplier) { return YimMenu::NativeInvoker::Invoke<4392, void>(ped, multiplier); }
	FORCEINLINE void SET_PED_CAN_LOSE_PROPS_ON_DAMAGE(Ped ped, bool toggle, int p2) { return YimMenu::NativeInvoker::Invoke<4393, void>(ped, toggle, p2); }
	FORCEINLINE void SET_FORCE_FOOTSTEP_UPDATE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4394, void>(ped, toggle); }
	FORCEINLINE void SET_FORCE_STEP_TYPE(Ped ped, bool p1, int type, int p3) { return YimMenu::NativeInvoker::Invoke<4395, void>(ped, p1, type, p3); }
	FORCEINLINE bool IS_ANY_HOSTILE_PED_NEAR_POINT(Ped ped, float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<4396, bool>(ped, x, y, z, radius); }
	FORCEINLINE void SET_PED_CAN_PLAY_IN_CAR_IDLES(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4397, void>(ped, toggle); }
	FORCEINLINE bool IS_TARGET_PED_IN_PERCEPTION_AREA(Ped ped, Ped targetPed, float p2, float p3, float p4, float p5) { return YimMenu::NativeInvoker::Invoke<4398, bool>(ped, targetPed, p2, p3, p4, p5); }
	FORCEINLINE void SET_POP_CONTROL_SPHERE_THIS_FRAME(float x, float y, float z, float min, float max) { return YimMenu::NativeInvoker::Invoke<4399, void>(x, y, z, min, max); }
	FORCEINLINE void FORCE_ZERO_MASS_IN_COLLISIONS(Ped ped) { return YimMenu::NativeInvoker::Invoke<4400, void>(ped); }
	FORCEINLINE void SET_DISABLE_HIGH_FALL_DEATH(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4401, void>(ped, toggle); }
	FORCEINLINE void SET_PED_PHONE_PALETTE_IDX(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4402, void>(p0, p1); }
	FORCEINLINE void SET_PED_STEER_BIAS(Ped ped, float value) { return YimMenu::NativeInvoker::Invoke<4403, void>(ped, value); }
	FORCEINLINE bool IS_PED_SWITCHING_WEAPON(Ped Ped) { return YimMenu::NativeInvoker::Invoke<4404, bool>(Ped); }
	FORCEINLINE void SET_PED_TREATED_AS_FRIENDLY(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4405, void>(p0, p1, p2); }
	FORCEINLINE void SET_DISABLE_PED_MAP_COLLISION(Ped ped) { return YimMenu::NativeInvoker::Invoke<4406, void>(ped); }
	FORCEINLINE void ENABLE_MP_LIGHT(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4407, void>(ped, toggle); }
	FORCEINLINE bool GET_MP_LIGHT_ENABLED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4408, bool>(ped); }
	FORCEINLINE void CLEAR_COVER_POINT_FOR_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<4409, void>(ped); }
	FORCEINLINE void SET_ALLOW_STUNT_JUMP_CAMERA(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<4410, void>(ped, toggle); }
}

namespace PHYSICS
{
	FORCEINLINE int ADD_ROPE(float x, float y, float z, float rotX, float rotY, float rotZ, float length, int ropeType, float maxLength, float minLength, float windingSpeed, bool p11, bool p12, bool rigid, float p14, bool breakWhenShot, Any* unkPtr) { return YimMenu::NativeInvoker::Invoke<4411, int>(x, y, z, rotX, rotY, rotZ, length, ropeType, maxLength, minLength, windingSpeed, p11, p12, rigid, p14, breakWhenShot, unkPtr); }
	FORCEINLINE void DELETE_ROPE(int* ropeId) { return YimMenu::NativeInvoker::Invoke<4412, void>(ropeId); }
	FORCEINLINE void DELETE_CHILD_ROPE(int ropeId) { return YimMenu::NativeInvoker::Invoke<4413, void>(ropeId); }
	FORCEINLINE bool DOES_ROPE_EXIST(int* ropeId) { return YimMenu::NativeInvoker::Invoke<4414, bool>(ropeId); }
	FORCEINLINE void ROPE_DRAW_ENABLED(int* ropeId, bool p1) { return YimMenu::NativeInvoker::Invoke<4415, void>(ropeId, p1); }
	FORCEINLINE void ROPE_DRAW_SHADOW_ENABLED(int* ropeId, bool toggle) { return YimMenu::NativeInvoker::Invoke<4416, void>(ropeId, toggle); }
	FORCEINLINE void LOAD_ROPE_DATA(int ropeId, const char* rope_preset) { return YimMenu::NativeInvoker::Invoke<4417, void>(ropeId, rope_preset); }
	FORCEINLINE void PIN_ROPE_VERTEX(int ropeId, int vertex, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<4418, void>(ropeId, vertex, x, y, z); }
	FORCEINLINE void UNPIN_ROPE_VERTEX(int ropeId, int vertex) { return YimMenu::NativeInvoker::Invoke<4419, void>(ropeId, vertex); }
	FORCEINLINE int GET_ROPE_VERTEX_COUNT(int ropeId) { return YimMenu::NativeInvoker::Invoke<4420, int>(ropeId); }
	FORCEINLINE void ATTACH_ENTITIES_TO_ROPE(int ropeId, Entity ent1, Entity ent2, float ent1_x, float ent1_y, float ent1_z, float ent2_x, float ent2_y, float ent2_z, float length, bool p10, bool p11, Any* p12, Any* p13) { return YimMenu::NativeInvoker::Invoke<4421, void>(ropeId, ent1, ent2, ent1_x, ent1_y, ent1_z, ent2_x, ent2_y, ent2_z, length, p10, p11, p12, p13); }
	FORCEINLINE void ATTACH_ROPE_TO_ENTITY(int ropeId, Entity entity, float x, float y, float z, bool p5) { return YimMenu::NativeInvoker::Invoke<4422, void>(ropeId, entity, x, y, z, p5); }
	FORCEINLINE void DETACH_ROPE_FROM_ENTITY(int ropeId, Entity entity) { return YimMenu::NativeInvoker::Invoke<4423, void>(ropeId, entity); }
	FORCEINLINE void ROPE_SET_UPDATE_PINVERTS(int ropeId) { return YimMenu::NativeInvoker::Invoke<4424, void>(ropeId); }
	FORCEINLINE void ROPE_SET_UPDATE_ORDER(int ropeId, Any p1) { return YimMenu::NativeInvoker::Invoke<4425, void>(ropeId, p1); }
	FORCEINLINE void ROPE_SET_SMOOTH_REELIN(int ropeId, bool p1) { return YimMenu::NativeInvoker::Invoke<4426, void>(ropeId, p1); }
	FORCEINLINE bool IS_ROPE_ATTACHED_AT_BOTH_ENDS(int* ropeId) { return YimMenu::NativeInvoker::Invoke<4427, bool>(ropeId); }
	FORCEINLINE Vector3 GET_ROPE_LAST_VERTEX_COORD(int ropeId) { return YimMenu::NativeInvoker::Invoke<4428, Vector3>(ropeId); }
	FORCEINLINE Vector3 GET_ROPE_VERTEX_COORD(int ropeId, int vertex) { return YimMenu::NativeInvoker::Invoke<4429, Vector3>(ropeId, vertex); }
	FORCEINLINE void START_ROPE_WINDING(int ropeId) { return YimMenu::NativeInvoker::Invoke<4430, void>(ropeId); }
	FORCEINLINE void STOP_ROPE_WINDING(int ropeId) { return YimMenu::NativeInvoker::Invoke<4431, void>(ropeId); }
	FORCEINLINE void START_ROPE_UNWINDING_FRONT(int ropeId) { return YimMenu::NativeInvoker::Invoke<4432, void>(ropeId); }
	FORCEINLINE void STOP_ROPE_UNWINDING_FRONT(int ropeId) { return YimMenu::NativeInvoker::Invoke<4433, void>(ropeId); }
	FORCEINLINE void ROPE_CONVERT_TO_SIMPLE(int ropeId) { return YimMenu::NativeInvoker::Invoke<4434, void>(ropeId); }
	FORCEINLINE void ROPE_LOAD_TEXTURES() { return YimMenu::NativeInvoker::Invoke<4435, void>(); }
	FORCEINLINE bool ROPE_ARE_TEXTURES_LOADED() { return YimMenu::NativeInvoker::Invoke<4436, bool>(); }
	FORCEINLINE void ROPE_UNLOAD_TEXTURES() { return YimMenu::NativeInvoker::Invoke<4437, void>(); }
	FORCEINLINE bool DOES_SCRIPT_OWN_ROPE(int ropeId) { return YimMenu::NativeInvoker::Invoke<4438, bool>(ropeId); }
	FORCEINLINE void ROPE_ATTACH_VIRTUAL_BOUND_GEOM(int ropeId, int p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float p9, float p10, float p11, float p12, float p13) { return YimMenu::NativeInvoker::Invoke<4439, void>(ropeId, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13); }
	FORCEINLINE void ROPE_CHANGE_SCRIPT_OWNER(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<4440, void>(p0, p1, p2); }
	FORCEINLINE void ROPE_SET_REFFRAMEVELOCITY_COLLIDERORDER(int ropeId, int p1) { return YimMenu::NativeInvoker::Invoke<4441, void>(ropeId, p1); }
	FORCEINLINE float ROPE_GET_DISTANCE_BETWEEN_ENDS(int ropeId) { return YimMenu::NativeInvoker::Invoke<4442, float>(ropeId); }
	FORCEINLINE void ROPE_FORCE_LENGTH(int ropeId, float length) { return YimMenu::NativeInvoker::Invoke<4443, void>(ropeId, length); }
	FORCEINLINE void ROPE_RESET_LENGTH(int ropeId, float length) { return YimMenu::NativeInvoker::Invoke<4444, void>(ropeId, length); }
	FORCEINLINE void APPLY_IMPULSE_TO_CLOTH(float posX, float posY, float posZ, float vecX, float vecY, float vecZ, float impulse) { return YimMenu::NativeInvoker::Invoke<4445, void>(posX, posY, posZ, vecX, vecY, vecZ, impulse); }
	FORCEINLINE void SET_DAMPING(Entity entity, int vertex, float value) { return YimMenu::NativeInvoker::Invoke<4446, void>(entity, vertex, value); }
	FORCEINLINE void ACTIVATE_PHYSICS(Entity entity) { return YimMenu::NativeInvoker::Invoke<4447, void>(entity); }
	FORCEINLINE void SET_CGOFFSET(Entity entity, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<4448, void>(entity, x, y, z); }
	FORCEINLINE Vector3 GET_CGOFFSET(Entity entity) { return YimMenu::NativeInvoker::Invoke<4449, Vector3>(entity); }
	FORCEINLINE void SET_CG_AT_BOUNDCENTER(Entity entity) { return YimMenu::NativeInvoker::Invoke<4450, void>(entity); }
	FORCEINLINE void BREAK_ENTITY_GLASS(Entity entity, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, Any p9, bool p10) { return YimMenu::NativeInvoker::Invoke<4451, void>(entity, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	FORCEINLINE bool GET_IS_ENTITY_A_FRAG(Object object) { return YimMenu::NativeInvoker::Invoke<4452, bool>(object); }
	FORCEINLINE void SET_DISABLE_BREAKING(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<4453, void>(object, toggle); }
	FORCEINLINE void RESET_DISABLE_BREAKING(Object object) { return YimMenu::NativeInvoker::Invoke<4454, void>(object); }
	FORCEINLINE void SET_DISABLE_FRAG_DAMAGE(Object object, bool toggle) { return YimMenu::NativeInvoker::Invoke<4455, void>(object, toggle); }
	FORCEINLINE void SET_USE_KINEMATIC_PHYSICS(Entity entity, bool toggle) { return YimMenu::NativeInvoker::Invoke<4456, void>(entity, toggle); }
	FORCEINLINE void SET_IN_STUNT_MODE(bool p0) { return YimMenu::NativeInvoker::Invoke<4457, void>(p0); }
	FORCEINLINE void SET_IN_ARENA_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<4458, void>(toggle); }
}

namespace PLAYER
{
	FORCEINLINE Ped GET_PLAYER_PED(Player player) { return YimMenu::NativeInvoker::Invoke<4459, Ped>(player); }
	FORCEINLINE Ped GET_PLAYER_PED_SCRIPT_INDEX(Player player) { return YimMenu::NativeInvoker::Invoke<4460, Ped>(player); }
	FORCEINLINE void SET_PLAYER_MODEL(Player player, Hash model) { return YimMenu::NativeInvoker::Invoke<4461, void>(player, model); }
	FORCEINLINE void CHANGE_PLAYER_PED(Player player, Ped ped, bool p2, bool resetDamage) { return YimMenu::NativeInvoker::Invoke<4462, void>(player, ped, p2, resetDamage); }
	FORCEINLINE void GET_PLAYER_RGB_COLOUR(Player player, int* r, int* g, int* b) { return YimMenu::NativeInvoker::Invoke<4463, void>(player, r, g, b); }
	FORCEINLINE int GET_NUMBER_OF_PLAYERS() { return YimMenu::NativeInvoker::Invoke<4464, int>(); }
	FORCEINLINE int GET_PLAYER_TEAM(Player player) { return YimMenu::NativeInvoker::Invoke<4465, int>(player); }
	FORCEINLINE void SET_PLAYER_TEAM(Player player, int team) { return YimMenu::NativeInvoker::Invoke<4466, void>(player, team); }
	FORCEINLINE int GET_NUMBER_OF_PLAYERS_IN_TEAM(int team) { return YimMenu::NativeInvoker::Invoke<4467, int>(team); }
	FORCEINLINE const char* GET_PLAYER_NAME(Player player) { return YimMenu::NativeInvoker::Invoke<4468, const char*>(player); }
	FORCEINLINE float GET_WANTED_LEVEL_RADIUS(Player player) { return YimMenu::NativeInvoker::Invoke<4469, float>(player); }
	FORCEINLINE Vector3 GET_PLAYER_WANTED_CENTRE_POSITION(Player player) { return YimMenu::NativeInvoker::Invoke<4470, Vector3>(player); }
	FORCEINLINE void SET_PLAYER_WANTED_CENTRE_POSITION(Player player, Vector3* position, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<4471, void>(player, position, p2, p3); }
	FORCEINLINE int GET_WANTED_LEVEL_THRESHOLD(int wantedLevel) { return YimMenu::NativeInvoker::Invoke<4472, int>(wantedLevel); }
	FORCEINLINE void SET_PLAYER_WANTED_LEVEL(Player player, int wantedLevel, bool disableNoMission) { return YimMenu::NativeInvoker::Invoke<4473, void>(player, wantedLevel, disableNoMission); }
	FORCEINLINE void SET_PLAYER_WANTED_LEVEL_NO_DROP(Player player, int wantedLevel, bool p2) { return YimMenu::NativeInvoker::Invoke<4474, void>(player, wantedLevel, p2); }
	FORCEINLINE void SET_PLAYER_WANTED_LEVEL_NOW(Player player, bool p1) { return YimMenu::NativeInvoker::Invoke<4475, void>(player, p1); }
	FORCEINLINE bool ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(Player player) { return YimMenu::NativeInvoker::Invoke<4476, bool>(player); }
	FORCEINLINE bool ARE_PLAYER_STARS_GREYED_OUT(Player player) { return YimMenu::NativeInvoker::Invoke<4477, bool>(player); }
	FORCEINLINE bool IS_WANTED_AND_HAS_BEEN_SEEN_BY_COPS(Player player) { return YimMenu::NativeInvoker::Invoke<4478, bool>(player); }
	FORCEINLINE void SET_DISPATCH_COPS_FOR_PLAYER(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4479, void>(player, toggle); }
	FORCEINLINE bool IS_PLAYER_WANTED_LEVEL_GREATER(Player player, int wantedLevel) { return YimMenu::NativeInvoker::Invoke<4480, bool>(player, wantedLevel); }
	FORCEINLINE void CLEAR_PLAYER_WANTED_LEVEL(Player player) { return YimMenu::NativeInvoker::Invoke<4481, void>(player); }
	FORCEINLINE bool IS_PLAYER_DEAD(Player player) { return YimMenu::NativeInvoker::Invoke<4482, bool>(player); }
	FORCEINLINE bool IS_PLAYER_PRESSING_HORN(Player player) { return YimMenu::NativeInvoker::Invoke<4483, bool>(player); }
	FORCEINLINE void SET_PLAYER_CONTROL(Player player, bool bHasControl, int flags) { return YimMenu::NativeInvoker::Invoke<4484, void>(player, bHasControl, flags); }
	FORCEINLINE int GET_PLAYER_WANTED_LEVEL(Player player) { return YimMenu::NativeInvoker::Invoke<4485, int>(player); }
	FORCEINLINE void SET_MAX_WANTED_LEVEL(int maxWantedLevel) { return YimMenu::NativeInvoker::Invoke<4486, void>(maxWantedLevel); }
	FORCEINLINE void SET_POLICE_RADAR_BLIPS(bool toggle) { return YimMenu::NativeInvoker::Invoke<4487, void>(toggle); }
	FORCEINLINE void SET_POLICE_IGNORE_PLAYER(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4488, void>(player, toggle); }
	FORCEINLINE bool IS_PLAYER_PLAYING(Player player) { return YimMenu::NativeInvoker::Invoke<4489, bool>(player); }
	FORCEINLINE void SET_EVERYONE_IGNORE_PLAYER(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4490, void>(player, toggle); }
	FORCEINLINE void SET_ALL_RANDOM_PEDS_FLEE(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4491, void>(player, toggle); }
	FORCEINLINE void SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<4492, void>(player); }
	FORCEINLINE void SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4493, void>(player, toggle); }
	FORCEINLINE void SET_ALL_NEUTRAL_RANDOM_PEDS_FLEE_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<4494, void>(player); }
	FORCEINLINE void SET_LAW_PEDS_CAN_ATTACK_NON_WANTED_PLAYER_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<4495, void>(player); }
	FORCEINLINE void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4496, void>(player, toggle); }
	FORCEINLINE void SET_WANTED_LEVEL_MULTIPLIER(float multiplier) { return YimMenu::NativeInvoker::Invoke<4497, void>(multiplier); }
	FORCEINLINE void SET_WANTED_LEVEL_DIFFICULTY(Player player, float difficulty) { return YimMenu::NativeInvoker::Invoke<4498, void>(player, difficulty); }
	FORCEINLINE void RESET_WANTED_LEVEL_DIFFICULTY(Player player) { return YimMenu::NativeInvoker::Invoke<4499, void>(player); }
	FORCEINLINE int GET_WANTED_LEVEL_TIME_TO_ESCAPE() { return YimMenu::NativeInvoker::Invoke<4500, int>(); }
	FORCEINLINE void SET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(Player player, int wantedLevel, int lossTime) { return YimMenu::NativeInvoker::Invoke<4501, void>(player, wantedLevel, lossTime); }
	FORCEINLINE void RESET_WANTED_LEVEL_HIDDEN_ESCAPE_TIME(Player player) { return YimMenu::NativeInvoker::Invoke<4502, void>(player); }
	FORCEINLINE void START_FIRING_AMNESTY(int duration) { return YimMenu::NativeInvoker::Invoke<4503, void>(duration); }
	FORCEINLINE void REPORT_CRIME(Player player, int crimeType, int wantedLvlThresh) { return YimMenu::NativeInvoker::Invoke<4504, void>(player, crimeType, wantedLvlThresh); }
	FORCEINLINE void SUPPRESS_CRIME_THIS_FRAME(Player player, int crimeType) { return YimMenu::NativeInvoker::Invoke<4505, void>(player, crimeType); }
	FORCEINLINE void UPDATE_WANTED_POSITION_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<4506, void>(player); }
	FORCEINLINE void SUPPRESS_LOSING_WANTED_LEVEL_IF_HIDDEN_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<4507, void>(player); }
	FORCEINLINE void ALLOW_EVASION_HUD_IF_DISABLING_HIDDEN_EVASION_THIS_FRAME(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4508, void>(player, p1); }
	FORCEINLINE void FORCE_START_HIDDEN_EVASION(Player player) { return YimMenu::NativeInvoker::Invoke<4509, void>(player); }
	FORCEINLINE void SUPPRESS_WITNESSES_CALLING_POLICE_THIS_FRAME(Player player) { return YimMenu::NativeInvoker::Invoke<4510, void>(player); }
	FORCEINLINE void REPORT_POLICE_SPOTTED_PLAYER(Player player) { return YimMenu::NativeInvoker::Invoke<4511, void>(player); }
	FORCEINLINE void SET_LAW_RESPONSE_DELAY_OVERRIDE(float p0) { return YimMenu::NativeInvoker::Invoke<4512, void>(p0); }
	FORCEINLINE void RESET_LAW_RESPONSE_DELAY_OVERRIDE() { return YimMenu::NativeInvoker::Invoke<4513, void>(); }
	FORCEINLINE bool CAN_PLAYER_START_MISSION(Player player) { return YimMenu::NativeInvoker::Invoke<4514, bool>(player); }
	FORCEINLINE bool IS_PLAYER_READY_FOR_CUTSCENE(Player player) { return YimMenu::NativeInvoker::Invoke<4515, bool>(player); }
	FORCEINLINE bool IS_PLAYER_TARGETTING_ENTITY(Player player, Entity entity) { return YimMenu::NativeInvoker::Invoke<4516, bool>(player, entity); }
	FORCEINLINE bool GET_PLAYER_TARGET_ENTITY(Player player, Entity* entity) { return YimMenu::NativeInvoker::Invoke<4517, bool>(player, entity); }
	FORCEINLINE bool IS_PLAYER_FREE_AIMING(Player player) { return YimMenu::NativeInvoker::Invoke<4518, bool>(player); }
	FORCEINLINE bool IS_PLAYER_FREE_AIMING_AT_ENTITY(Player player, Entity entity) { return YimMenu::NativeInvoker::Invoke<4519, bool>(player, entity); }
	FORCEINLINE bool GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(Player player, Entity* entity) { return YimMenu::NativeInvoker::Invoke<4520, bool>(player, entity); }
	FORCEINLINE void SET_PLAYER_LOCKON_RANGE_OVERRIDE(Player player, float range) { return YimMenu::NativeInvoker::Invoke<4521, void>(player, range); }
	FORCEINLINE void SET_PLAYER_CAN_DO_DRIVE_BY(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4522, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4523, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_CAN_USE_COVER(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4524, void>(player, toggle); }
	FORCEINLINE int GET_MAX_WANTED_LEVEL() { return YimMenu::NativeInvoker::Invoke<4525, int>(); }
	FORCEINLINE bool IS_PLAYER_TARGETTING_ANYTHING(Player player) { return YimMenu::NativeInvoker::Invoke<4526, bool>(player); }
	FORCEINLINE void SET_PLAYER_SPRINT(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4527, void>(player, toggle); }
	FORCEINLINE void RESET_PLAYER_STAMINA(Player player) { return YimMenu::NativeInvoker::Invoke<4528, void>(player); }
	FORCEINLINE void RESTORE_PLAYER_STAMINA(Player player, float p1) { return YimMenu::NativeInvoker::Invoke<4529, void>(player, p1); }
	FORCEINLINE float GET_PLAYER_SPRINT_STAMINA_REMAINING(Player player) { return YimMenu::NativeInvoker::Invoke<4530, float>(player); }
	FORCEINLINE float GET_PLAYER_SPRINT_TIME_REMAINING(Player player) { return YimMenu::NativeInvoker::Invoke<4531, float>(player); }
	FORCEINLINE float GET_PLAYER_UNDERWATER_TIME_REMAINING(Player player) { return YimMenu::NativeInvoker::Invoke<4532, float>(player); }
	FORCEINLINE float SET_PLAYER_UNDERWATER_BREATH_PERCENT_REMAINING(Player player, float time) { return YimMenu::NativeInvoker::Invoke<4533, float>(player, time); }
	FORCEINLINE int GET_PLAYER_GROUP(Player player) { return YimMenu::NativeInvoker::Invoke<4534, int>(player); }
	FORCEINLINE int GET_PLAYER_MAX_ARMOUR(Player player) { return YimMenu::NativeInvoker::Invoke<4535, int>(player); }
	FORCEINLINE bool IS_PLAYER_CONTROL_ON(Player player) { return YimMenu::NativeInvoker::Invoke<4536, bool>(player); }
	FORCEINLINE bool GET_ARE_CAMERA_CONTROLS_DISABLED() { return YimMenu::NativeInvoker::Invoke<4537, bool>(); }
	FORCEINLINE bool IS_PLAYER_SCRIPT_CONTROL_ON(Player player) { return YimMenu::NativeInvoker::Invoke<4538, bool>(player); }
	FORCEINLINE bool IS_PLAYER_CLIMBING(Player player) { return YimMenu::NativeInvoker::Invoke<4539, bool>(player); }
	FORCEINLINE bool IS_PLAYER_BEING_ARRESTED(Player player, bool atArresting) { return YimMenu::NativeInvoker::Invoke<4540, bool>(player, atArresting); }
	FORCEINLINE void RESET_PLAYER_ARREST_STATE(Player player) { return YimMenu::NativeInvoker::Invoke<4541, void>(player); }
	FORCEINLINE Vehicle GET_PLAYERS_LAST_VEHICLE() { return YimMenu::NativeInvoker::Invoke<4542, Vehicle>(); }
	FORCEINLINE Player GET_PLAYER_INDEX() { return YimMenu::NativeInvoker::Invoke<4543, Player>(); }
	FORCEINLINE Player INT_TO_PLAYERINDEX(int value) { return YimMenu::NativeInvoker::Invoke<4544, Player>(value); }
	FORCEINLINE int INT_TO_PARTICIPANTINDEX(int value) { return YimMenu::NativeInvoker::Invoke<4545, int>(value); }
	FORCEINLINE int GET_TIME_SINCE_PLAYER_HIT_VEHICLE(Player player) { return YimMenu::NativeInvoker::Invoke<4546, int>(player); }
	FORCEINLINE int GET_TIME_SINCE_PLAYER_HIT_PED(Player player) { return YimMenu::NativeInvoker::Invoke<4547, int>(player); }
	FORCEINLINE int GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(Player player) { return YimMenu::NativeInvoker::Invoke<4548, int>(player); }
	FORCEINLINE int GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(Player player) { return YimMenu::NativeInvoker::Invoke<4549, int>(player); }
	FORCEINLINE bool IS_PLAYER_FREE_FOR_AMBIENT_TASK(Player player) { return YimMenu::NativeInvoker::Invoke<4550, bool>(player); }
	FORCEINLINE Player PLAYER_ID() { return YimMenu::NativeInvoker::Invoke<4551, Player>(); }
	FORCEINLINE Ped PLAYER_PED_ID() { return YimMenu::NativeInvoker::Invoke<4552, Ped>(); }
	FORCEINLINE int NETWORK_PLAYER_ID_TO_INT() { return YimMenu::NativeInvoker::Invoke<4553, int>(); }
	FORCEINLINE bool HAS_FORCE_CLEANUP_OCCURRED(int cleanupFlags) { return YimMenu::NativeInvoker::Invoke<4554, bool>(cleanupFlags); }
	FORCEINLINE void FORCE_CLEANUP(int cleanupFlags) { return YimMenu::NativeInvoker::Invoke<4555, void>(cleanupFlags); }
	FORCEINLINE void FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME(const char* name, int cleanupFlags) { return YimMenu::NativeInvoker::Invoke<4556, void>(name, cleanupFlags); }
	FORCEINLINE void FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID(int id, int cleanupFlags) { return YimMenu::NativeInvoker::Invoke<4557, void>(id, cleanupFlags); }
	FORCEINLINE int GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP() { return YimMenu::NativeInvoker::Invoke<4558, int>(); }
	FORCEINLINE void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(Player player, Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<4559, void>(player, vehicle); }
	FORCEINLINE void SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE(Player player) { return YimMenu::NativeInvoker::Invoke<4560, void>(player); }
	FORCEINLINE bool GIVE_ACHIEVEMENT_TO_PLAYER(int achievementId) { return YimMenu::NativeInvoker::Invoke<4561, bool>(achievementId); }
	FORCEINLINE bool SET_ACHIEVEMENT_PROGRESS(int achievementId, int progress) { return YimMenu::NativeInvoker::Invoke<4562, bool>(achievementId, progress); }
	FORCEINLINE int GET_ACHIEVEMENT_PROGRESS(int achievementId) { return YimMenu::NativeInvoker::Invoke<4563, int>(achievementId); }
	FORCEINLINE bool HAS_ACHIEVEMENT_BEEN_PASSED(int achievementId) { return YimMenu::NativeInvoker::Invoke<4564, bool>(achievementId); }
	FORCEINLINE bool IS_PLAYER_ONLINE() { return YimMenu::NativeInvoker::Invoke<4565, bool>(); }
	FORCEINLINE bool IS_PLAYER_LOGGING_IN_NP() { return YimMenu::NativeInvoker::Invoke<4566, bool>(); }
	FORCEINLINE void DISPLAY_SYSTEM_SIGNIN_UI(bool p0) { return YimMenu::NativeInvoker::Invoke<4567, void>(p0); }
	FORCEINLINE bool IS_SYSTEM_UI_BEING_DISPLAYED() { return YimMenu::NativeInvoker::Invoke<4568, bool>(); }
	FORCEINLINE void SET_PLAYER_INVINCIBLE(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4569, void>(player, toggle); }
	FORCEINLINE bool GET_PLAYER_INVINCIBLE(Player player) { return YimMenu::NativeInvoker::Invoke<4570, bool>(player); }
	FORCEINLINE bool GET_PLAYER_DEBUG_INVINCIBLE(Player player) { return YimMenu::NativeInvoker::Invoke<4571, bool>(player); }
	FORCEINLINE void SET_PLAYER_INVINCIBLE_BUT_HAS_REACTIONS(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4572, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_CAN_COLLECT_DROPPED_MONEY(Player player, bool p1) { return YimMenu::NativeInvoker::Invoke<4573, void>(player, p1); }
	FORCEINLINE void REMOVE_PLAYER_HELMET(Player player, bool p2) { return YimMenu::NativeInvoker::Invoke<4574, void>(player, p2); }
	FORCEINLINE void GIVE_PLAYER_RAGDOLL_CONTROL(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4575, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_LOCKON(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4576, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_TARGETING_MODE(int targetMode) { return YimMenu::NativeInvoker::Invoke<4577, void>(targetMode); }
	FORCEINLINE void SET_PLAYER_TARGET_LEVEL(int targetLevel) { return YimMenu::NativeInvoker::Invoke<4578, void>(targetLevel); }
	FORCEINLINE bool GET_IS_USING_FPS_THIRD_PERSON_COVER() { return YimMenu::NativeInvoker::Invoke<4579, bool>(); }
	FORCEINLINE bool GET_IS_USING_HOOD_CAMERA() { return YimMenu::NativeInvoker::Invoke<4580, bool>(); }
	FORCEINLINE void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Player player) { return YimMenu::NativeInvoker::Invoke<4581, void>(player); }
	FORCEINLINE bool HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Player player) { return YimMenu::NativeInvoker::Invoke<4582, bool>(player); }
	FORCEINLINE void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player) { return YimMenu::NativeInvoker::Invoke<4583, void>(player); }
	FORCEINLINE bool HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(Player player) { return YimMenu::NativeInvoker::Invoke<4584, bool>(player); }
	FORCEINLINE void SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(Player player, float multiplier) { return YimMenu::NativeInvoker::Invoke<4585, void>(player, multiplier); }
	FORCEINLINE void SET_SWIM_MULTIPLIER_FOR_PLAYER(Player player, float multiplier) { return YimMenu::NativeInvoker::Invoke<4586, void>(player, multiplier); }
	FORCEINLINE void SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(Player player, float multiplier) { return YimMenu::NativeInvoker::Invoke<4587, void>(player, multiplier); }
	FORCEINLINE int GET_TIME_SINCE_LAST_ARREST() { return YimMenu::NativeInvoker::Invoke<4588, int>(); }
	FORCEINLINE int GET_TIME_SINCE_LAST_DEATH() { return YimMenu::NativeInvoker::Invoke<4589, int>(); }
	FORCEINLINE void ASSISTED_MOVEMENT_CLOSE_ROUTE() { return YimMenu::NativeInvoker::Invoke<4590, void>(); }
	FORCEINLINE void ASSISTED_MOVEMENT_FLUSH_ROUTE() { return YimMenu::NativeInvoker::Invoke<4591, void>(); }
	FORCEINLINE void SET_PLAYER_FORCED_AIM(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4592, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_FORCED_ZOOM(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4593, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_FORCE_SKIP_AIM_INTRO(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4594, void>(player, toggle); }
	FORCEINLINE void DISABLE_PLAYER_FIRING(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4595, void>(player, toggle); }
	FORCEINLINE void DISABLE_PLAYER_THROW_GRENADE_WHILE_USING_GUN() { return YimMenu::NativeInvoker::Invoke<4596, void>(); }
	FORCEINLINE void SET_DISABLE_AMBIENT_MELEE_MOVE(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4597, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_MAX_ARMOUR(Player player, int value) { return YimMenu::NativeInvoker::Invoke<4598, void>(player, value); }
	FORCEINLINE void SPECIAL_ABILITY_ACTIVATE(Player player, int p1) { return YimMenu::NativeInvoker::Invoke<4599, void>(player, p1); }
	FORCEINLINE void SET_SPECIAL_ABILITY_MP(Player player, int p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4600, void>(player, p1, p2); }
	FORCEINLINE void SPECIAL_ABILITY_DEACTIVATE_MP(Player player, int p1) { return YimMenu::NativeInvoker::Invoke<4601, void>(player, p1); }
	FORCEINLINE void SPECIAL_ABILITY_DEACTIVATE(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4602, void>(player, p1); }
	FORCEINLINE void SPECIAL_ABILITY_DEACTIVATE_FAST(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4603, void>(player, p1); }
	FORCEINLINE void SPECIAL_ABILITY_RESET(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4604, void>(player, p1); }
	FORCEINLINE void SPECIAL_ABILITY_CHARGE_ON_MISSION_FAILED(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4605, void>(player, p1); }
	FORCEINLINE void SPECIAL_ABILITY_CHARGE_SMALL(Player player, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4606, void>(player, p1, p2, p3); }
	FORCEINLINE void SPECIAL_ABILITY_CHARGE_MEDIUM(Player player, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4607, void>(player, p1, p2, p3); }
	FORCEINLINE void SPECIAL_ABILITY_CHARGE_LARGE(Player player, bool p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4608, void>(player, p1, p2, p3); }
	FORCEINLINE void SPECIAL_ABILITY_CHARGE_CONTINUOUS(Player player, Ped p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4609, void>(player, p1, p2); }
	FORCEINLINE void SPECIAL_ABILITY_CHARGE_ABSOLUTE(Player player, int p1, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4610, void>(player, p1, p2, p3); }
	FORCEINLINE void SPECIAL_ABILITY_CHARGE_NORMALIZED(Player player, float normalizedValue, bool p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4611, void>(player, normalizedValue, p2, p3); }
	FORCEINLINE void SPECIAL_ABILITY_FILL_METER(Player player, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4612, void>(player, p1, p2); }
	FORCEINLINE void SPECIAL_ABILITY_DEPLETE_METER(Player player, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4613, void>(player, p1, p2); }
	FORCEINLINE void SPECIAL_ABILITY_LOCK(Hash playerModel, Any p1) { return YimMenu::NativeInvoker::Invoke<4614, void>(playerModel, p1); }
	FORCEINLINE void SPECIAL_ABILITY_UNLOCK(Hash playerModel, Any p1) { return YimMenu::NativeInvoker::Invoke<4615, void>(playerModel, p1); }
	FORCEINLINE bool IS_SPECIAL_ABILITY_UNLOCKED(Hash playerModel) { return YimMenu::NativeInvoker::Invoke<4616, bool>(playerModel); }
	FORCEINLINE bool IS_SPECIAL_ABILITY_ACTIVE(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4617, bool>(player, p1); }
	FORCEINLINE bool IS_SPECIAL_ABILITY_METER_FULL(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4618, bool>(player, p1); }
	FORCEINLINE void ENABLE_SPECIAL_ABILITY(Player player, bool toggle, Any p2) { return YimMenu::NativeInvoker::Invoke<4619, void>(player, toggle, p2); }
	FORCEINLINE bool IS_SPECIAL_ABILITY_ENABLED(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4620, bool>(player, p1); }
	FORCEINLINE void SET_SPECIAL_ABILITY_MULTIPLIER(float multiplier) { return YimMenu::NativeInvoker::Invoke<4621, void>(multiplier); }
	FORCEINLINE void UPDATE_SPECIAL_ABILITY_FROM_STAT(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4622, void>(player, p1); }
	FORCEINLINE bool GET_IS_PLAYER_DRIVING_ON_HIGHWAY(Player player) { return YimMenu::NativeInvoker::Invoke<4623, bool>(player); }
	FORCEINLINE bool GET_IS_PLAYER_DRIVING_WRECKLESS(Player player, int p1) { return YimMenu::NativeInvoker::Invoke<4624, bool>(player, p1); }
	FORCEINLINE bool GET_IS_MOPPING_AREA_FREE_IN_FRONT_OF_PLAYER(Player player, float p1) { return YimMenu::NativeInvoker::Invoke<4625, bool>(player, p1); }
	FORCEINLINE void START_PLAYER_TELEPORT(Player player, float x, float y, float z, float heading, bool p5, bool findCollisionLand, bool p7) { return YimMenu::NativeInvoker::Invoke<4626, void>(player, x, y, z, heading, p5, findCollisionLand, p7); }
	FORCEINLINE bool UPDATE_PLAYER_TELEPORT(Player player) { return YimMenu::NativeInvoker::Invoke<4627, bool>(player); }
	FORCEINLINE void STOP_PLAYER_TELEPORT() { return YimMenu::NativeInvoker::Invoke<4628, void>(); }
	FORCEINLINE bool IS_PLAYER_TELEPORT_ACTIVE() { return YimMenu::NativeInvoker::Invoke<4629, bool>(); }
	FORCEINLINE float GET_PLAYER_CURRENT_STEALTH_NOISE(Player player) { return YimMenu::NativeInvoker::Invoke<4630, float>(player); }
	FORCEINLINE void SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(Player player, float regenRate) { return YimMenu::NativeInvoker::Invoke<4631, void>(player, regenRate); }
	FORCEINLINE float GET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(Player player) { return YimMenu::NativeInvoker::Invoke<4632, float>(player); }
	FORCEINLINE void SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(Player player, float limit) { return YimMenu::NativeInvoker::Invoke<4633, void>(player, limit); }
	FORCEINLINE void DISABLE_PLAYER_HEALTH_RECHARGE(Player player) { return YimMenu::NativeInvoker::Invoke<4634, void>(player); }
	FORCEINLINE void SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_RAGDOLL_OVERRIDE(Player player, float p1) { return YimMenu::NativeInvoker::Invoke<4635, void>(player, p1); }
	FORCEINLINE void SET_PLAYER_WEAPON_DAMAGE_MODIFIER(Player player, float modifier) { return YimMenu::NativeInvoker::Invoke<4636, void>(player, modifier); }
	FORCEINLINE void SET_PLAYER_WEAPON_DEFENSE_MODIFIER(Player player, float modifier) { return YimMenu::NativeInvoker::Invoke<4637, void>(player, modifier); }
	FORCEINLINE void SET_PLAYER_WEAPON_MINIGUN_DEFENSE_MODIFIER(Player player, float modifier) { return YimMenu::NativeInvoker::Invoke<4638, void>(player, modifier); }
	FORCEINLINE void SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Player player, float modifier, bool p2) { return YimMenu::NativeInvoker::Invoke<4639, void>(player, modifier, p2); }
	FORCEINLINE void SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(Player player, float modifier) { return YimMenu::NativeInvoker::Invoke<4640, void>(player, modifier); }
	FORCEINLINE void SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(Player player, float modifier) { return YimMenu::NativeInvoker::Invoke<4641, void>(player, modifier); }
	FORCEINLINE void SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(Player player, float modifier) { return YimMenu::NativeInvoker::Invoke<4642, void>(player, modifier); }
	FORCEINLINE void SET_PLAYER_MAX_EXPLOSIVE_DAMAGE(Player player, float p1) { return YimMenu::NativeInvoker::Invoke<4643, void>(player, p1); }
	FORCEINLINE void SET_PLAYER_EXPLOSIVE_DAMAGE_MODIFIER(Player player, Any p1) { return YimMenu::NativeInvoker::Invoke<4644, void>(player, p1); }
	FORCEINLINE void SET_PLAYER_WEAPON_TAKEDOWN_DEFENSE_MODIFIER(Player player, float p1) { return YimMenu::NativeInvoker::Invoke<4645, void>(player, p1); }
	FORCEINLINE void SET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int tintIndex) { return YimMenu::NativeInvoker::Invoke<4646, void>(player, tintIndex); }
	FORCEINLINE void GET_PLAYER_PARACHUTE_TINT_INDEX(Player player, int* tintIndex) { return YimMenu::NativeInvoker::Invoke<4647, void>(player, tintIndex); }
	FORCEINLINE void SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int index) { return YimMenu::NativeInvoker::Invoke<4648, void>(player, index); }
	FORCEINLINE void GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(Player player, int* index) { return YimMenu::NativeInvoker::Invoke<4649, void>(player, index); }
	FORCEINLINE void SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int tintIndex) { return YimMenu::NativeInvoker::Invoke<4650, void>(player, tintIndex); }
	FORCEINLINE void GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(Player player, int* tintIndex) { return YimMenu::NativeInvoker::Invoke<4651, void>(player, tintIndex); }
	FORCEINLINE void SET_PLAYER_HAS_RESERVE_PARACHUTE(Player player) { return YimMenu::NativeInvoker::Invoke<4652, void>(player); }
	FORCEINLINE bool GET_PLAYER_HAS_RESERVE_PARACHUTE(Player player) { return YimMenu::NativeInvoker::Invoke<4653, bool>(player); }
	FORCEINLINE void SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(Player player, bool enabled) { return YimMenu::NativeInvoker::Invoke<4654, void>(player, enabled); }
	FORCEINLINE void SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int r, int g, int b) { return YimMenu::NativeInvoker::Invoke<4655, void>(player, r, g, b); }
	FORCEINLINE void GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(Player player, int* r, int* g, int* b) { return YimMenu::NativeInvoker::Invoke<4656, void>(player, r, g, b); }
	FORCEINLINE void SET_PLAYER_PHONE_PALETTE_IDX(Player player, int flags) { return YimMenu::NativeInvoker::Invoke<4657, void>(player, flags); }
	FORCEINLINE void SET_PLAYER_NOISE_MULTIPLIER(Player player, float multiplier) { return YimMenu::NativeInvoker::Invoke<4658, void>(player, multiplier); }
	FORCEINLINE void SET_PLAYER_SNEAKING_NOISE_MULTIPLIER(Player player, float multiplier) { return YimMenu::NativeInvoker::Invoke<4659, void>(player, multiplier); }
	FORCEINLINE bool CAN_PED_HEAR_PLAYER(Player player, Ped ped) { return YimMenu::NativeInvoker::Invoke<4660, bool>(player, ped); }
	FORCEINLINE void SIMULATE_PLAYER_INPUT_GAIT(Player player, float amount, int gaitType, float speed, bool p4, bool p5, Any p6) { return YimMenu::NativeInvoker::Invoke<4661, void>(player, amount, gaitType, speed, p4, p5, p6); }
	FORCEINLINE void RESET_PLAYER_INPUT_GAIT(Player player) { return YimMenu::NativeInvoker::Invoke<4662, void>(player); }
	FORCEINLINE void SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4663, void>(player, toggle); }
	FORCEINLINE void SET_AUTO_GIVE_SCUBA_GEAR_WHEN_EXIT_VEHICLE(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4664, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(Player player, float value) { return YimMenu::NativeInvoker::Invoke<4665, void>(player, value); }
	FORCEINLINE bool IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(Player player) { return YimMenu::NativeInvoker::Invoke<4666, bool>(player); }
	FORCEINLINE void INCREASE_PLAYER_JUMP_SUPPRESSION_RANGE(Player player) { return YimMenu::NativeInvoker::Invoke<4667, void>(player); }
	FORCEINLINE void SET_PLAYER_SIMULATE_AIMING(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4668, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_CLOTH_PIN_FRAMES(Player player, int p1) { return YimMenu::NativeInvoker::Invoke<4669, void>(player, p1); }
	FORCEINLINE void SET_PLAYER_CLOTH_PACKAGE_INDEX(int index) { return YimMenu::NativeInvoker::Invoke<4670, void>(index); }
	FORCEINLINE void SET_PLAYER_CLOTH_LOCK_COUNTER(int value) { return YimMenu::NativeInvoker::Invoke<4671, void>(value); }
	FORCEINLINE void PLAYER_ATTACH_VIRTUAL_BOUND(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7) { return YimMenu::NativeInvoker::Invoke<4672, void>(p0, p1, p2, p3, p4, p5, p6, p7); }
	FORCEINLINE void PLAYER_DETACH_VIRTUAL_BOUND() { return YimMenu::NativeInvoker::Invoke<4673, void>(); }
	FORCEINLINE bool HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE(Player player) { return YimMenu::NativeInvoker::Invoke<4674, bool>(player); }
	FORCEINLINE bool IS_PLAYER_BATTLE_AWARE(Player player) { return YimMenu::NativeInvoker::Invoke<4675, bool>(player); }
	FORCEINLINE bool GET_PLAYER_RECEIVED_BATTLE_EVENT_RECENTLY(Player player, int p1, bool p2) { return YimMenu::NativeInvoker::Invoke<4676, bool>(player, p1, p2); }
	FORCEINLINE void EXTEND_WORLD_BOUNDARY_FOR_PLAYER(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<4677, void>(x, y, z); }
	FORCEINLINE void RESET_WORLD_BOUNDARY_FOR_PLAYER() { return YimMenu::NativeInvoker::Invoke<4678, void>(); }
	FORCEINLINE bool IS_PLAYER_RIDING_TRAIN(Player player) { return YimMenu::NativeInvoker::Invoke<4679, bool>(player); }
	FORCEINLINE bool HAS_PLAYER_LEFT_THE_WORLD(Player player) { return YimMenu::NativeInvoker::Invoke<4680, bool>(player); }
	FORCEINLINE void SET_PLAYER_LEAVE_PED_BEHIND(Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<4681, void>(player, toggle); }
	FORCEINLINE void SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player, int p1, Any p2, Any p3, bool p4) { return YimMenu::NativeInvoker::Invoke<4682, void>(player, p1, p2, p3, p4); }
	FORCEINLINE void CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE(Player player) { return YimMenu::NativeInvoker::Invoke<4683, void>(player); }
	FORCEINLINE void SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model) { return YimMenu::NativeInvoker::Invoke<4684, void>(player, model); }
	FORCEINLINE void SET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player, Hash model) { return YimMenu::NativeInvoker::Invoke<4685, void>(player, model); }
	FORCEINLINE Hash GET_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player) { return YimMenu::NativeInvoker::Invoke<4686, Hash>(player); }
	FORCEINLINE Hash GET_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player) { return YimMenu::NativeInvoker::Invoke<4687, Hash>(player); }
	FORCEINLINE void CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE(Player player) { return YimMenu::NativeInvoker::Invoke<4688, void>(player); }
	FORCEINLINE void CLEAR_PLAYER_RESERVE_PARACHUTE_MODEL_OVERRIDE(Player player) { return YimMenu::NativeInvoker::Invoke<4689, void>(player); }
	FORCEINLINE void SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player, Hash model) { return YimMenu::NativeInvoker::Invoke<4690, void>(player, model); }
	FORCEINLINE void CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(Player player) { return YimMenu::NativeInvoker::Invoke<4691, void>(player); }
	FORCEINLINE void DISABLE_PLAYER_VEHICLE_REWARDS(Player player) { return YimMenu::NativeInvoker::Invoke<4692, void>(player); }
	FORCEINLINE void SET_PLAYER_SPECTATED_VEHICLE_RADIO_OVERRIDE(bool p0) { return YimMenu::NativeInvoker::Invoke<4693, void>(p0); }
	FORCEINLINE void SET_PLAYER_BLUETOOTH_STATE(Player player, bool state) { return YimMenu::NativeInvoker::Invoke<4694, void>(player, state); }
	FORCEINLINE bool IS_PLAYER_BLUETOOTH_ENABLE(Player player) { return YimMenu::NativeInvoker::Invoke<4695, bool>(player); }
	FORCEINLINE void DISABLE_CAMERA_VIEW_MODE_CYCLE(Player player) { return YimMenu::NativeInvoker::Invoke<4696, void>(player); }
	FORCEINLINE int GET_PLAYER_FAKE_WANTED_LEVEL(Player player) { return YimMenu::NativeInvoker::Invoke<4697, int>(player); }
	FORCEINLINE void SET_PLAYER_CAN_DAMAGE_PLAYER(Player player1, Player player2, bool toggle) { return YimMenu::NativeInvoker::Invoke<4698, void>(player1, player2, toggle); }
	FORCEINLINE void SET_APPLY_WAYPOINT_OF_PLAYER(Player player, int hudColor) { return YimMenu::NativeInvoker::Invoke<4699, void>(player, hudColor); }
	FORCEINLINE bool IS_PLAYER_VEHICLE_WEAPON_TOGGLED_TO_NON_HOMING(Any p0) { return YimMenu::NativeInvoker::Invoke<4700, bool>(p0); }
	FORCEINLINE void SET_PLAYER_VEHICLE_WEAPON_TO_NON_HOMING(Any p0) { return YimMenu::NativeInvoker::Invoke<4701, void>(p0); }
	FORCEINLINE void SET_PLAYER_HOMING_DISABLED_FOR_ALL_VEHICLE_WEAPONS(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4702, void>(p0, p1); }
	FORCEINLINE void ADD_PLAYER_TARGETABLE_ENTITY(Player player, Entity entity) { return YimMenu::NativeInvoker::Invoke<4703, void>(player, entity); }
	FORCEINLINE void REMOVE_PLAYER_TARGETABLE_ENTITY(Player player, Entity entity) { return YimMenu::NativeInvoker::Invoke<4704, void>(player, entity); }
	FORCEINLINE void SET_PLAYER_PREVIOUS_VARIATION_DATA(Player player, int p1, int p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<4705, void>(player, p1, p2, p3, p4, p5); }
	FORCEINLINE void REMOVE_SCRIPT_FIRE_POSITION() { return YimMenu::NativeInvoker::Invoke<4706, void>(); }
	FORCEINLINE void SET_SCRIPT_FIRE_POSITION(float coordX, float coordY, float coordZ) { return YimMenu::NativeInvoker::Invoke<4707, void>(coordX, coordY, coordZ); }
}

namespace RECORDING
{
	FORCEINLINE void REPLAY_START_EVENT(int p0) { return YimMenu::NativeInvoker::Invoke<4708, void>(p0); }
	FORCEINLINE void REPLAY_STOP_EVENT() { return YimMenu::NativeInvoker::Invoke<4709, void>(); }
	FORCEINLINE void REPLAY_CANCEL_EVENT() { return YimMenu::NativeInvoker::Invoke<4710, void>(); }
	FORCEINLINE void REPLAY_RECORD_BACK_FOR_TIME(float p0, float p1, int p2) { return YimMenu::NativeInvoker::Invoke<4711, void>(p0, p1, p2); }
	FORCEINLINE void REPLAY_CHECK_FOR_EVENT_THIS_FRAME(const char* missionNameLabel, Any p1) { return YimMenu::NativeInvoker::Invoke<4712, void>(missionNameLabel, p1); }
	FORCEINLINE void REPLAY_PREVENT_RECORDING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<4713, void>(); }
	FORCEINLINE void REPLAY_RESET_EVENT_INFO() { return YimMenu::NativeInvoker::Invoke<4714, void>(); }
	FORCEINLINE void REPLAY_DISABLE_CAMERA_MOVEMENT_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<4715, void>(); }
	FORCEINLINE void RECORD_GREATEST_MOMENT(int p0, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<4716, void>(p0, p1, p2); }
	FORCEINLINE void START_REPLAY_RECORDING(int mode) { return YimMenu::NativeInvoker::Invoke<4717, void>(mode); }
	FORCEINLINE void STOP_REPLAY_RECORDING() { return YimMenu::NativeInvoker::Invoke<4718, void>(); }
	FORCEINLINE void CANCEL_REPLAY_RECORDING() { return YimMenu::NativeInvoker::Invoke<4719, void>(); }
	FORCEINLINE bool SAVE_REPLAY_RECORDING() { return YimMenu::NativeInvoker::Invoke<4720, bool>(); }
	FORCEINLINE bool IS_REPLAY_RECORDING() { return YimMenu::NativeInvoker::Invoke<4721, bool>(); }
	FORCEINLINE bool IS_REPLAY_INITIALIZED() { return YimMenu::NativeInvoker::Invoke<4722, bool>(); }
	FORCEINLINE bool IS_REPLAY_AVAILABLE() { return YimMenu::NativeInvoker::Invoke<4723, bool>(); }
	FORCEINLINE bool IS_REPLAY_RECORD_SPACE_AVAILABLE(bool p0) { return YimMenu::NativeInvoker::Invoke<4724, bool>(p0); }
}

namespace REPLAY
{
	FORCEINLINE void REGISTER_EFFECT_FOR_REPLAY_EDITOR(const char* p0, bool p1) { return YimMenu::NativeInvoker::Invoke<4725, void>(p0, p1); }
	FORCEINLINE bool REPLAY_SYSTEM_HAS_REQUESTED_A_SCRIPT_CLEANUP() { return YimMenu::NativeInvoker::Invoke<4726, bool>(); }
	FORCEINLINE void SET_SCRIPTS_HAVE_CLEANED_UP_FOR_REPLAY_SYSTEM() { return YimMenu::NativeInvoker::Invoke<4727, void>(); }
	FORCEINLINE void SET_REPLAY_SYSTEM_PAUSED_FOR_SAVE(bool p0) { return YimMenu::NativeInvoker::Invoke<4728, void>(p0); }
	FORCEINLINE void REPLAY_CONTROL_SHUTDOWN() { return YimMenu::NativeInvoker::Invoke<4729, void>(); }
	FORCEINLINE void ACTIVATE_ROCKSTAR_EDITOR(int p0) { return YimMenu::NativeInvoker::Invoke<4730, void>(p0); }
}

namespace SAVEMIGRATION
{
	FORCEINLINE bool SAVEMIGRATION_IS_MP_ENABLED() { return YimMenu::NativeInvoker::Invoke<4731, bool>(); }
	FORCEINLINE bool SAVEMIGRATION_MP_REQUEST_ACCOUNTS() { return YimMenu::NativeInvoker::Invoke<4732, bool>(); }
	FORCEINLINE int SAVEMIGRATION_MP_GET_ACCOUNTS_STATUS() { return YimMenu::NativeInvoker::Invoke<4733, int>(); }
	FORCEINLINE int SAVEMIGRATION_MP_NUM_ACCOUNTS() { return YimMenu::NativeInvoker::Invoke<4734, int>(); }
	FORCEINLINE bool SAVEMIGRATION_MP_GET_ACCOUNT(int p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<4735, bool>(p0, p1); }
	FORCEINLINE bool SAVEMIGRATION_MP_REQUEST_STATUS() { return YimMenu::NativeInvoker::Invoke<4736, bool>(); }
	FORCEINLINE int SAVEMIGRATION_MP_GET_STATUS() { return YimMenu::NativeInvoker::Invoke<4737, int>(); }
}

namespace SCRIPT
{
	FORCEINLINE void REQUEST_SCRIPT(const char* scriptName) { return YimMenu::NativeInvoker::Invoke<4738, void>(scriptName); }
	FORCEINLINE void SET_SCRIPT_AS_NO_LONGER_NEEDED(const char* scriptName) { return YimMenu::NativeInvoker::Invoke<4739, void>(scriptName); }
	FORCEINLINE bool HAS_SCRIPT_LOADED(const char* scriptName) { return YimMenu::NativeInvoker::Invoke<4740, bool>(scriptName); }
	FORCEINLINE bool DOES_SCRIPT_EXIST(const char* scriptName) { return YimMenu::NativeInvoker::Invoke<4741, bool>(scriptName); }
	FORCEINLINE void REQUEST_SCRIPT_WITH_NAME_HASH(Hash scriptHash) { return YimMenu::NativeInvoker::Invoke<4742, void>(scriptHash); }
	FORCEINLINE void SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(Hash scriptHash) { return YimMenu::NativeInvoker::Invoke<4743, void>(scriptHash); }
	FORCEINLINE bool HAS_SCRIPT_WITH_NAME_HASH_LOADED(Hash scriptHash) { return YimMenu::NativeInvoker::Invoke<4744, bool>(scriptHash); }
	FORCEINLINE bool DOES_SCRIPT_WITH_NAME_HASH_EXIST(Hash scriptHash) { return YimMenu::NativeInvoker::Invoke<4745, bool>(scriptHash); }
	FORCEINLINE void TERMINATE_THREAD(int threadId) { return YimMenu::NativeInvoker::Invoke<4746, void>(threadId); }
	FORCEINLINE bool IS_THREAD_ACTIVE(int threadId) { return YimMenu::NativeInvoker::Invoke<4747, bool>(threadId); }
	FORCEINLINE const char* GET_NAME_OF_SCRIPT_WITH_THIS_ID(int threadId) { return YimMenu::NativeInvoker::Invoke<4748, const char*>(threadId); }
	FORCEINLINE void SCRIPT_THREAD_ITERATOR_RESET() { return YimMenu::NativeInvoker::Invoke<4749, void>(); }
	FORCEINLINE int SCRIPT_THREAD_ITERATOR_GET_NEXT_THREAD_ID() { return YimMenu::NativeInvoker::Invoke<4750, int>(); }
	FORCEINLINE int GET_ID_OF_THIS_THREAD() { return YimMenu::NativeInvoker::Invoke<4751, int>(); }
	FORCEINLINE void TERMINATE_THIS_THREAD() { return YimMenu::NativeInvoker::Invoke<4752, void>(); }
	FORCEINLINE int GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(Hash scriptHash) { return YimMenu::NativeInvoker::Invoke<4753, int>(scriptHash); }
	FORCEINLINE const char* GET_THIS_SCRIPT_NAME() { return YimMenu::NativeInvoker::Invoke<4754, const char*>(); }
	FORCEINLINE Hash GET_HASH_OF_THIS_SCRIPT_NAME() { return YimMenu::NativeInvoker::Invoke<4755, Hash>(); }
	FORCEINLINE int GET_NUMBER_OF_EVENTS(int eventGroup) { return YimMenu::NativeInvoker::Invoke<4756, int>(eventGroup); }
	FORCEINLINE bool GET_EVENT_EXISTS(int eventGroup, int eventIndex) { return YimMenu::NativeInvoker::Invoke<4757, bool>(eventGroup, eventIndex); }
	FORCEINLINE int GET_EVENT_AT_INDEX(int eventGroup, int eventIndex) { return YimMenu::NativeInvoker::Invoke<4758, int>(eventGroup, eventIndex); }
	FORCEINLINE bool GET_EVENT_DATA(int eventGroup, int eventIndex, Any* eventData, int eventDataSize) { return YimMenu::NativeInvoker::Invoke<4759, bool>(eventGroup, eventIndex, eventData, eventDataSize); }
	FORCEINLINE void TRIGGER_SCRIPT_EVENT(int eventGroup, Any* eventData, int eventDataSize, int playerBits) { return YimMenu::NativeInvoker::Invoke<4760, void>(eventGroup, eventData, eventDataSize, playerBits); }
	FORCEINLINE void SHUTDOWN_LOADING_SCREEN() { return YimMenu::NativeInvoker::Invoke<4761, void>(); }
	FORCEINLINE void SET_NO_LOADING_SCREEN(bool toggle) { return YimMenu::NativeInvoker::Invoke<4762, void>(toggle); }
	FORCEINLINE bool GET_NO_LOADING_SCREEN() { return YimMenu::NativeInvoker::Invoke<4763, bool>(); }
	FORCEINLINE void COMMIT_TO_LOADINGSCREEN_SELCTION() { return YimMenu::NativeInvoker::Invoke<4764, void>(); }
	FORCEINLINE bool BG_IS_EXITFLAG_SET() { return YimMenu::NativeInvoker::Invoke<4765, bool>(); }
	FORCEINLINE void BG_SET_EXITFLAG_RESPONSE() { return YimMenu::NativeInvoker::Invoke<4766, void>(); }
	FORCEINLINE void BG_START_CONTEXT_HASH(Hash contextHash) { return YimMenu::NativeInvoker::Invoke<4767, void>(contextHash); }
	FORCEINLINE void BG_END_CONTEXT_HASH(Hash contextHash) { return YimMenu::NativeInvoker::Invoke<4768, void>(contextHash); }
	FORCEINLINE void BG_START_CONTEXT(const char* contextName) { return YimMenu::NativeInvoker::Invoke<4769, void>(contextName); }
	FORCEINLINE void BG_END_CONTEXT(const char* contextName) { return YimMenu::NativeInvoker::Invoke<4770, void>(contextName); }
	FORCEINLINE bool BG_DOES_LAUNCH_PARAM_EXIST(int scriptIndex, const char* p1) { return YimMenu::NativeInvoker::Invoke<4771, bool>(scriptIndex, p1); }
	FORCEINLINE int BG_GET_LAUNCH_PARAM_VALUE(int scriptIndex, const char* p1) { return YimMenu::NativeInvoker::Invoke<4772, int>(scriptIndex, p1); }
	FORCEINLINE int BG_GET_SCRIPT_ID_FROM_NAME_HASH(Hash p0) { return YimMenu::NativeInvoker::Invoke<4773, int>(p0); }
	FORCEINLINE void SEND_TU_SCRIPT_EVENT(int eventGroup, Any* eventData, int eventDataSize, int playerBits) { return YimMenu::NativeInvoker::Invoke<4774, void>(eventGroup, eventData, eventDataSize, playerBits); }
}

namespace SECURITY
{
	FORCEINLINE void REGISTER_SCRIPT_VARIABLE(Any* variable) { return YimMenu::NativeInvoker::Invoke<4775, void>(variable); }
	FORCEINLINE void UNREGISTER_SCRIPT_VARIABLE(Any* variable) { return YimMenu::NativeInvoker::Invoke<4776, void>(variable); }
	FORCEINLINE void FORCE_CHECK_SCRIPT_VARIABLES() { return YimMenu::NativeInvoker::Invoke<4777, void>(); }
}

namespace SHAPETEST
{
	FORCEINLINE int START_SHAPE_TEST_LOS_PROBE(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8) { return YimMenu::NativeInvoker::Invoke<4778, int>(x1, y1, z1, x2, y2, z2, flags, entity, p8); }
	FORCEINLINE int START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(float x1, float y1, float z1, float x2, float y2, float z2, int flags, Entity entity, int p8) { return YimMenu::NativeInvoker::Invoke<4779, int>(x1, y1, z1, x2, y2, z2, flags, entity, p8); }
	FORCEINLINE int START_SHAPE_TEST_BOUNDING_BOX(Entity entity, int flags1, int flags2) { return YimMenu::NativeInvoker::Invoke<4780, int>(entity, flags1, flags2); }
	FORCEINLINE int START_SHAPE_TEST_BOX(float x, float y, float z, float dimX, float dimY, float dimZ, float rotX, float rotY, float rotZ, Any p9, int flags, Entity entity, Any p12) { return YimMenu::NativeInvoker::Invoke<4781, int>(x, y, z, dimX, dimY, dimZ, rotX, rotY, rotZ, p9, flags, entity, p12); }
	FORCEINLINE int START_SHAPE_TEST_BOUND(Entity entity, int flags1, int flags2) { return YimMenu::NativeInvoker::Invoke<4782, int>(entity, flags1, flags2); }
	FORCEINLINE int START_SHAPE_TEST_CAPSULE(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, int p9) { return YimMenu::NativeInvoker::Invoke<4783, int>(x1, y1, z1, x2, y2, z2, radius, flags, entity, p9); }
	FORCEINLINE int START_SHAPE_TEST_SWEPT_SPHERE(float x1, float y1, float z1, float x2, float y2, float z2, float radius, int flags, Entity entity, Any p9) { return YimMenu::NativeInvoker::Invoke<4784, int>(x1, y1, z1, x2, y2, z2, radius, flags, entity, p9); }
	FORCEINLINE int START_SHAPE_TEST_MOUSE_CURSOR_LOS_PROBE(Vector3* pVec1, Vector3* pVec2, int flag, Entity entity, int flag2) { return YimMenu::NativeInvoker::Invoke<4785, int>(pVec1, pVec2, flag, entity, flag2); }
	FORCEINLINE int GET_SHAPE_TEST_RESULT(int shapeTestHandle, bool* hit, Vector3* endCoords, Vector3* surfaceNormal, Entity* entityHit) { return YimMenu::NativeInvoker::Invoke<4786, int>(shapeTestHandle, hit, endCoords, surfaceNormal, entityHit); }
	FORCEINLINE int GET_SHAPE_TEST_RESULT_INCLUDING_MATERIAL(int shapeTestHandle, bool* hit, Vector3* endCoords, Vector3* surfaceNormal, Hash* materialHash, Entity* entityHit) { return YimMenu::NativeInvoker::Invoke<4787, int>(shapeTestHandle, hit, endCoords, surfaceNormal, materialHash, entityHit); }
	FORCEINLINE void RELEASE_SCRIPT_GUID_FROM_ENTITY(Entity entityHit) { return YimMenu::NativeInvoker::Invoke<4788, void>(entityHit); }
}

namespace SOCIALCLUB
{
	FORCEINLINE int SC_INBOX_GET_TOTAL_NUM_MESSAGES() { return YimMenu::NativeInvoker::Invoke<4789, int>(); }
	FORCEINLINE Hash SC_INBOX_GET_MESSAGE_TYPE_AT_INDEX(int msgIndex) { return YimMenu::NativeInvoker::Invoke<4790, Hash>(msgIndex); }
	FORCEINLINE bool SC_INBOX_GET_MESSAGE_IS_READ_AT_INDEX(int msgIndex) { return YimMenu::NativeInvoker::Invoke<4791, bool>(msgIndex); }
	FORCEINLINE bool SC_INBOX_SET_MESSAGE_AS_READ_AT_INDEX(int msgIndex) { return YimMenu::NativeInvoker::Invoke<4792, bool>(msgIndex); }
	FORCEINLINE bool SC_INBOX_MESSAGE_GET_DATA_INT(int p0, const char* context, int* out) { return YimMenu::NativeInvoker::Invoke<4793, bool>(p0, context, out); }
	FORCEINLINE bool SC_INBOX_MESSAGE_GET_DATA_BOOL(int p0, const char* p1) { return YimMenu::NativeInvoker::Invoke<4794, bool>(p0, p1); }
	FORCEINLINE bool SC_INBOX_MESSAGE_GET_DATA_STRING(int p0, const char* context, char* out) { return YimMenu::NativeInvoker::Invoke<4795, bool>(p0, context, out); }
	FORCEINLINE bool SC_INBOX_MESSAGE_DO_APPLY(int p0) { return YimMenu::NativeInvoker::Invoke<4796, bool>(p0); }
	FORCEINLINE const char* SC_INBOX_MESSAGE_GET_RAW_TYPE_AT_INDEX(int p0) { return YimMenu::NativeInvoker::Invoke<4797, const char*>(p0); }
	FORCEINLINE void SC_INBOX_MESSAGE_PUSH_GAMER_T0_RECIP_LIST(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<4798, void>(gamerHandle); }
	FORCEINLINE void SC_INBOX_SEND_UGCSTATUPDATE_TO_RECIP_LIST(Any* data) { return YimMenu::NativeInvoker::Invoke<4799, void>(data); }
	FORCEINLINE bool SC_INBOX_MESSAGE_GET_UGCDATA(int p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<4800, bool>(p0, p1); }
	FORCEINLINE bool SC_INBOX_SEND_BOUNTY_TO_RECIP_LIST(Any* data) { return YimMenu::NativeInvoker::Invoke<4801, bool>(data); }
	FORCEINLINE bool SC_INBOX_GET_BOUNTY_DATA_AT_INDEX(int index, Any* outData) { return YimMenu::NativeInvoker::Invoke<4802, bool>(index, outData); }
	FORCEINLINE void SC_EMAIL_RETRIEVE_EMAILS(int offset, int limit) { return YimMenu::NativeInvoker::Invoke<4803, void>(offset, limit); }
	FORCEINLINE int SC_EMAIL_GET_RETRIEVAL_STATUS() { return YimMenu::NativeInvoker::Invoke<4804, int>(); }
	FORCEINLINE int SC_EMAIL_GET_NUM_RETRIEVED_EMAILS() { return YimMenu::NativeInvoker::Invoke<4805, int>(); }
	FORCEINLINE bool SC_EMAIL_GET_EMAIL_AT_INDEX(int p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<4806, bool>(p0, p1); }
	FORCEINLINE void SC_EMAIL_DELETE_EMAILS(Any* p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4807, void>(p0, p1); }
	FORCEINLINE void SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST(Any* gamerHandle) { return YimMenu::NativeInvoker::Invoke<4808, void>(gamerHandle); }
	FORCEINLINE void SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST() { return YimMenu::NativeInvoker::Invoke<4809, void>(); }
	FORCEINLINE void SC_EMAIL_SEND_EMAIL(const char* p0) { return YimMenu::NativeInvoker::Invoke<4810, void>(p0); }
	FORCEINLINE bool SC_EMAIL_SET_CURRENT_EMAIL_TAG(Any p0) { return YimMenu::NativeInvoker::Invoke<4811, bool>(p0); }
	FORCEINLINE void SC_CACHE_NEW_ROCKSTAR_MSGS(bool toggle) { return YimMenu::NativeInvoker::Invoke<4812, void>(toggle); }
	FORCEINLINE bool SC_HAS_NEW_ROCKSTAR_MSG() { return YimMenu::NativeInvoker::Invoke<4813, bool>(); }
	FORCEINLINE const char* SC_GET_NEW_ROCKSTAR_MSG() { return YimMenu::NativeInvoker::Invoke<4814, const char*>(); }
	FORCEINLINE bool SC_PRESENCE_ATTR_SET_INT(Hash attrHash, int value) { return YimMenu::NativeInvoker::Invoke<4815, bool>(attrHash, value); }
	FORCEINLINE bool SC_PRESENCE_ATTR_SET_FLOAT(Hash attrHash, float value) { return YimMenu::NativeInvoker::Invoke<4816, bool>(attrHash, value); }
	FORCEINLINE bool SC_PRESENCE_ATTR_SET_STRING(Hash attrHash, const char* value) { return YimMenu::NativeInvoker::Invoke<4817, bool>(attrHash, value); }
	FORCEINLINE bool SC_PRESENCE_SET_ACTIVITY_RATING(Any p0, float p1) { return YimMenu::NativeInvoker::Invoke<4818, bool>(p0, p1); }
	FORCEINLINE bool SC_GAMERDATA_GET_INT(const char* name, int* value) { return YimMenu::NativeInvoker::Invoke<4819, bool>(name, value); }
	FORCEINLINE bool SC_GAMERDATA_GET_FLOAT(const char* name, float* value) { return YimMenu::NativeInvoker::Invoke<4820, bool>(name, value); }
	FORCEINLINE bool SC_GAMERDATA_GET_BOOL(const char* name) { return YimMenu::NativeInvoker::Invoke<4821, bool>(name); }
	FORCEINLINE bool SC_GAMERDATA_GET_STRING(const char* name, char* value) { return YimMenu::NativeInvoker::Invoke<4822, bool>(name, value); }
	FORCEINLINE bool SC_GAMERDATA_GET_ACTIVE_XP_BONUS(float* value) { return YimMenu::NativeInvoker::Invoke<4823, bool>(value); }
	FORCEINLINE bool SC_PROFANITY_CHECK_STRING(const char* string, int* token) { return YimMenu::NativeInvoker::Invoke<4824, bool>(string, token); }
	FORCEINLINE bool SC_PROFANITY_CHECK_STRING_UGC(const char* string, int* token) { return YimMenu::NativeInvoker::Invoke<4825, bool>(string, token); }
	FORCEINLINE bool SC_PROFANITY_GET_CHECK_IS_VALID(int token) { return YimMenu::NativeInvoker::Invoke<4826, bool>(token); }
	FORCEINLINE bool SC_PROFANITY_GET_CHECK_IS_PENDING(int token) { return YimMenu::NativeInvoker::Invoke<4827, bool>(token); }
	FORCEINLINE bool SC_PROFANITY_GET_STRING_PASSED(int token) { return YimMenu::NativeInvoker::Invoke<4828, bool>(token); }
	FORCEINLINE int SC_PROFANITY_GET_STRING_STATUS(int token) { return YimMenu::NativeInvoker::Invoke<4829, int>(token); }
	FORCEINLINE bool SC_LICENSEPLATE_CHECK_STRING(const char* p0, int* p1) { return YimMenu::NativeInvoker::Invoke<4830, bool>(p0, p1); }
	FORCEINLINE bool SC_LICENSEPLATE_GET_CHECK_IS_VALID(Any p0) { return YimMenu::NativeInvoker::Invoke<4831, bool>(p0); }
	FORCEINLINE bool SC_LICENSEPLATE_GET_CHECK_IS_PENDING(Any p0) { return YimMenu::NativeInvoker::Invoke<4832, bool>(p0); }
	FORCEINLINE int SC_LICENSEPLATE_GET_COUNT(int token) { return YimMenu::NativeInvoker::Invoke<4833, int>(token); }
	FORCEINLINE const char* SC_LICENSEPLATE_GET_PLATE(int token, int plateIndex) { return YimMenu::NativeInvoker::Invoke<4834, const char*>(token, plateIndex); }
	FORCEINLINE const char* SC_LICENSEPLATE_GET_PLATE_DATA(int token, int plateIndex) { return YimMenu::NativeInvoker::Invoke<4835, const char*>(token, plateIndex); }
	FORCEINLINE bool SC_LICENSEPLATE_SET_PLATE_DATA(const char* oldPlateText, const char* newPlateText, Any* plateData) { return YimMenu::NativeInvoker::Invoke<4836, bool>(oldPlateText, newPlateText, plateData); }
	FORCEINLINE bool SC_LICENSEPLATE_ADD(const char* plateText, Any* plateData, int* token) { return YimMenu::NativeInvoker::Invoke<4837, bool>(plateText, plateData, token); }
	FORCEINLINE bool SC_LICENSEPLATE_GET_ADD_IS_PENDING(int token) { return YimMenu::NativeInvoker::Invoke<4838, bool>(token); }
	FORCEINLINE int SC_LICENSEPLATE_GET_ADD_STATUS(int token) { return YimMenu::NativeInvoker::Invoke<4839, int>(token); }
	FORCEINLINE bool SC_LICENSEPLATE_ISVALID(const char* plateText, int* token) { return YimMenu::NativeInvoker::Invoke<4840, bool>(plateText, token); }
	FORCEINLINE bool SC_LICENSEPLATE_GET_ISVALID_IS_PENDING(int token) { return YimMenu::NativeInvoker::Invoke<4841, bool>(token); }
	FORCEINLINE int SC_LICENSEPLATE_GET_ISVALID_STATUS(int token) { return YimMenu::NativeInvoker::Invoke<4842, int>(token); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_IS_ACTIVE() { return YimMenu::NativeInvoker::Invoke<4843, bool>(); }
	FORCEINLINE int SC_COMMUNITY_EVENT_GET_EVENT_ID() { return YimMenu::NativeInvoker::Invoke<4844, int>(); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT(const char* p0, int* p1) { return YimMenu::NativeInvoker::Invoke<4845, bool>(p0, p1); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT(const char* p0, float* p1) { return YimMenu::NativeInvoker::Invoke<4846, bool>(p0, p1); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING(const char* p0, char* p1) { return YimMenu::NativeInvoker::Invoke<4847, bool>(p0, p1); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_DISPLAY_NAME(char* p0) { return YimMenu::NativeInvoker::Invoke<4848, bool>(p0); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_IS_ACTIVE_FOR_TYPE(const char* p0) { return YimMenu::NativeInvoker::Invoke<4849, bool>(p0); }
	FORCEINLINE int SC_COMMUNITY_EVENT_GET_EVENT_ID_FOR_TYPE(const char* p0) { return YimMenu::NativeInvoker::Invoke<4850, int>(p0); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_FOR_TYPE(const char* p0, int* p1, const char* p2) { return YimMenu::NativeInvoker::Invoke<4851, bool>(p0, p1, p2); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_FOR_TYPE(const char* p0, float* p1, const char* p2) { return YimMenu::NativeInvoker::Invoke<4852, bool>(p0, p1, p2); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_FOR_TYPE(const char* p0, char* p1, const char* p2) { return YimMenu::NativeInvoker::Invoke<4853, bool>(p0, p1, p2); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_FOR_TYPE(char* p0, const char* p1) { return YimMenu::NativeInvoker::Invoke<4854, bool>(p0, p1); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_IS_ACTIVE_BY_ID(int p0) { return YimMenu::NativeInvoker::Invoke<4855, bool>(p0); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_BY_ID(int p0, const char* p1, int* p2) { return YimMenu::NativeInvoker::Invoke<4856, bool>(p0, p1, p2); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_BY_ID(int p0, const char* p1, float* p2) { return YimMenu::NativeInvoker::Invoke<4857, bool>(p0, p1, p2); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_BY_ID(int p0, const char* p1, char* p2) { return YimMenu::NativeInvoker::Invoke<4858, bool>(p0, p1, p2); }
	FORCEINLINE bool SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_BY_ID(int p0, char* p1) { return YimMenu::NativeInvoker::Invoke<4859, bool>(p0, p1); }
	FORCEINLINE bool SC_TRANSITION_NEWS_SHOW(Any p0) { return YimMenu::NativeInvoker::Invoke<4860, bool>(p0); }
	FORCEINLINE bool SC_TRANSITION_NEWS_SHOW_TIMED(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4861, bool>(p0, p1); }
	FORCEINLINE bool SC_TRANSITION_NEWS_SHOW_NEXT_ITEM() { return YimMenu::NativeInvoker::Invoke<4862, bool>(); }
	FORCEINLINE bool SC_TRANSITION_NEWS_HAS_EXTRA_DATA_TU() { return YimMenu::NativeInvoker::Invoke<4863, bool>(); }
	FORCEINLINE bool SC_TRANSITION_NEWS_GET_EXTRA_DATA_INT_TU(const char* p0, int* p1) { return YimMenu::NativeInvoker::Invoke<4864, bool>(p0, p1); }
	FORCEINLINE void SC_TRANSITION_NEWS_END() { return YimMenu::NativeInvoker::Invoke<4865, void>(); }
	FORCEINLINE bool SC_PAUSE_NEWS_INIT_STARTER_PACK(Any p0) { return YimMenu::NativeInvoker::Invoke<4866, bool>(p0); }
	FORCEINLINE bool SC_PAUSE_NEWS_GET_PENDING_STORY(Any p0) { return YimMenu::NativeInvoker::Invoke<4867, bool>(p0); }
	FORCEINLINE void SC_PAUSE_NEWS_SHUTDOWN() { return YimMenu::NativeInvoker::Invoke<4868, void>(); }
	FORCEINLINE const char* SC_ACCOUNT_INFO_GET_NICKNAME() { return YimMenu::NativeInvoker::Invoke<4869, const char*>(); }
	FORCEINLINE bool SC_ACHIEVEMENT_INFO_STATUS(int* p0) { return YimMenu::NativeInvoker::Invoke<4870, bool>(p0); }
	FORCEINLINE bool SC_HAS_ACHIEVEMENT_BEEN_PASSED(int achievementId) { return YimMenu::NativeInvoker::Invoke<4871, bool>(achievementId); }
}

namespace STATS
{
	FORCEINLINE bool STAT_CLEAR_SLOT_FOR_RELOAD(int statSlot) { return YimMenu::NativeInvoker::Invoke<4872, bool>(statSlot); }
	FORCEINLINE bool STAT_LOAD(int statSlot) { return YimMenu::NativeInvoker::Invoke<4873, bool>(statSlot); }
	FORCEINLINE bool STAT_SAVE(int p0, bool p1, int p2, bool p3) { return YimMenu::NativeInvoker::Invoke<4874, bool>(p0, p1, p2, p3); }
	FORCEINLINE void STAT_SET_OPEN_SAVETYPE_IN_JOB(int p0) { return YimMenu::NativeInvoker::Invoke<4875, void>(p0); }
	FORCEINLINE bool STAT_LOAD_PENDING(int statSlot) { return YimMenu::NativeInvoker::Invoke<4876, bool>(statSlot); }
	FORCEINLINE bool STAT_SAVE_PENDING() { return YimMenu::NativeInvoker::Invoke<4877, bool>(); }
	FORCEINLINE bool STAT_SAVE_PENDING_OR_REQUESTED() { return YimMenu::NativeInvoker::Invoke<4878, bool>(); }
	FORCEINLINE bool STAT_DELETE_SLOT(int p0) { return YimMenu::NativeInvoker::Invoke<4879, bool>(p0); }
	FORCEINLINE bool STAT_SLOT_IS_LOADED(int statSlot) { return YimMenu::NativeInvoker::Invoke<4880, bool>(statSlot); }
	FORCEINLINE bool STAT_CLOUD_SLOT_LOAD_FAILED(int p0) { return YimMenu::NativeInvoker::Invoke<4881, bool>(p0); }
	FORCEINLINE int STAT_CLOUD_SLOT_LOAD_FAILED_CODE(Any p0) { return YimMenu::NativeInvoker::Invoke<4882, int>(p0); }
	FORCEINLINE void STAT_SET_BLOCK_SAVES(bool toggle) { return YimMenu::NativeInvoker::Invoke<4883, void>(toggle); }
	FORCEINLINE bool STAT_GET_BLOCK_SAVES() { return YimMenu::NativeInvoker::Invoke<4884, bool>(); }
	FORCEINLINE bool STAT_CLOUD_SLOT_SAVE_FAILED(Any p0) { return YimMenu::NativeInvoker::Invoke<4885, bool>(p0); }
	FORCEINLINE void STAT_CLEAR_PENDING_SAVES(Any p0) { return YimMenu::NativeInvoker::Invoke<4886, void>(p0); }
	FORCEINLINE bool STAT_LOAD_DIRTY_READ_DETECTED() { return YimMenu::NativeInvoker::Invoke<4887, bool>(); }
	FORCEINLINE void STAT_CLEAR_DIRTY_READ_DETECTED() { return YimMenu::NativeInvoker::Invoke<4888, void>(); }
	FORCEINLINE bool STAT_GET_LOAD_SAFE_TO_PROGRESS_TO_MP_FROM_SP() { return YimMenu::NativeInvoker::Invoke<4889, bool>(); }
	FORCEINLINE bool STAT_SET_INT(Hash statName, int value, bool save) { return YimMenu::NativeInvoker::Invoke<4890, bool>(statName, value, save); }
	FORCEINLINE bool STAT_SET_FLOAT(Hash statName, float value, bool save) { return YimMenu::NativeInvoker::Invoke<4891, bool>(statName, value, save); }
	FORCEINLINE bool STAT_SET_BOOL(Hash statName, bool value, bool save) { return YimMenu::NativeInvoker::Invoke<4892, bool>(statName, value, save); }
	FORCEINLINE bool STAT_SET_GXT_LABEL(Hash statName, const char* value, bool save) { return YimMenu::NativeInvoker::Invoke<4893, bool>(statName, value, save); }
	FORCEINLINE bool STAT_SET_DATE(Hash statName, Any* value, int numFields, bool save) { return YimMenu::NativeInvoker::Invoke<4894, bool>(statName, value, numFields, save); }
	FORCEINLINE bool STAT_SET_STRING(Hash statName, const char* value, bool save) { return YimMenu::NativeInvoker::Invoke<4895, bool>(statName, value, save); }
	FORCEINLINE bool STAT_SET_POS(Hash statName, float x, float y, float z, bool save) { return YimMenu::NativeInvoker::Invoke<4896, bool>(statName, x, y, z, save); }
	FORCEINLINE bool STAT_SET_MASKED_INT(Hash statName, int p1, int p2, int p3, bool save) { return YimMenu::NativeInvoker::Invoke<4897, bool>(statName, p1, p2, p3, save); }
	FORCEINLINE bool STAT_SET_USER_ID(Hash statName, const char* value, bool save) { return YimMenu::NativeInvoker::Invoke<4898, bool>(statName, value, save); }
	FORCEINLINE bool STAT_SET_CURRENT_POSIX_TIME(Hash statName, bool p1) { return YimMenu::NativeInvoker::Invoke<4899, bool>(statName, p1); }
	FORCEINLINE bool STAT_GET_INT(Hash statHash, int* outValue, int p2) { return YimMenu::NativeInvoker::Invoke<4900, bool>(statHash, outValue, p2); }
	FORCEINLINE bool STAT_GET_FLOAT(Hash statHash, float* outValue, Any p2) { return YimMenu::NativeInvoker::Invoke<4901, bool>(statHash, outValue, p2); }
	FORCEINLINE bool STAT_GET_BOOL(Hash statHash, bool* outValue, Any p2) { return YimMenu::NativeInvoker::Invoke<4902, bool>(statHash, outValue, p2); }
	FORCEINLINE bool STAT_GET_DATE(Hash statHash, Any* outValue, int numFields, Any p3) { return YimMenu::NativeInvoker::Invoke<4903, bool>(statHash, outValue, numFields, p3); }
	FORCEINLINE const char* STAT_GET_STRING(Hash statHash, int p1) { return YimMenu::NativeInvoker::Invoke<4904, const char*>(statHash, p1); }
	FORCEINLINE bool STAT_GET_POS(Hash statName, float* outX, float* outY, float* outZ, Any p4) { return YimMenu::NativeInvoker::Invoke<4905, bool>(statName, outX, outY, outZ, p4); }
	FORCEINLINE bool STAT_GET_MASKED_INT(Hash statHash, int* outValue, int p2, int p3, Any p4) { return YimMenu::NativeInvoker::Invoke<4906, bool>(statHash, outValue, p2, p3, p4); }
	FORCEINLINE const char* STAT_GET_USER_ID(Hash statHash) { return YimMenu::NativeInvoker::Invoke<4907, const char*>(statHash); }
	FORCEINLINE const char* STAT_GET_LICENSE_PLATE(Hash statName) { return YimMenu::NativeInvoker::Invoke<4908, const char*>(statName); }
	FORCEINLINE bool STAT_SET_LICENSE_PLATE(Hash statName, const char* str) { return YimMenu::NativeInvoker::Invoke<4909, bool>(statName, str); }
	FORCEINLINE void STAT_INCREMENT(Hash statName, float value) { return YimMenu::NativeInvoker::Invoke<4910, void>(statName, value); }
	FORCEINLINE bool STAT_COMMUNITY_START_SYNCH() { return YimMenu::NativeInvoker::Invoke<4911, bool>(); }
	FORCEINLINE bool STAT_COMMUNITY_SYNCH_IS_PENDING() { return YimMenu::NativeInvoker::Invoke<4912, bool>(); }
	FORCEINLINE bool STAT_COMMUNITY_GET_HISTORY(Hash statName, int p1, float* outValue) { return YimMenu::NativeInvoker::Invoke<4913, bool>(statName, p1, outValue); }
	FORCEINLINE void STAT_RESET_ALL_ONLINE_CHARACTER_STATS(int p0) { return YimMenu::NativeInvoker::Invoke<4914, void>(p0); }
	FORCEINLINE void STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS(int p0) { return YimMenu::NativeInvoker::Invoke<4915, void>(p0); }
	FORCEINLINE int STAT_GET_NUMBER_OF_DAYS(Hash statName) { return YimMenu::NativeInvoker::Invoke<4916, int>(statName); }
	FORCEINLINE int STAT_GET_NUMBER_OF_HOURS(Hash statName) { return YimMenu::NativeInvoker::Invoke<4917, int>(statName); }
	FORCEINLINE int STAT_GET_NUMBER_OF_MINUTES(Hash statName) { return YimMenu::NativeInvoker::Invoke<4918, int>(statName); }
	FORCEINLINE int STAT_GET_NUMBER_OF_SECONDS(Hash statName) { return YimMenu::NativeInvoker::Invoke<4919, int>(statName); }
	FORCEINLINE void STAT_SET_PROFILE_SETTING_VALUE(int profileSetting, int value) { return YimMenu::NativeInvoker::Invoke<4920, void>(profileSetting, value); }
	FORCEINLINE void STATS_COMPLETED_CHARACTER_CREATION(Any p0) { return YimMenu::NativeInvoker::Invoke<4921, void>(p0); }
	FORCEINLINE int PACKED_STAT_GET_INT_STAT_INDEX(int p0) { return YimMenu::NativeInvoker::Invoke<4922, int>(p0); }
	FORCEINLINE Hash GET_PACKED_INT_STAT_KEY(int index, bool spStat, bool charStat, int character) { return YimMenu::NativeInvoker::Invoke<4923, Hash>(index, spStat, charStat, character); }
	FORCEINLINE Hash GET_PACKED_TU_INT_STAT_KEY(int index, bool spStat, bool charStat, int character) { return YimMenu::NativeInvoker::Invoke<4924, Hash>(index, spStat, charStat, character); }
	FORCEINLINE Hash GET_PACKED_NG_INT_STAT_KEY(int index, bool spStat, bool charStat, int character, const char* section) { return YimMenu::NativeInvoker::Invoke<4925, Hash>(index, spStat, charStat, character, section); }
	FORCEINLINE bool GET_PACKED_STAT_BOOL_CODE(int index, int characterSlot) { return YimMenu::NativeInvoker::Invoke<4926, bool>(index, characterSlot); }
	FORCEINLINE int GET_PACKED_STAT_INT_CODE(int index, int characterSlot) { return YimMenu::NativeInvoker::Invoke<4927, int>(index, characterSlot); }
	FORCEINLINE void SET_PACKED_STAT_BOOL_CODE(int index, bool value, int characterSlot) { return YimMenu::NativeInvoker::Invoke<4928, void>(index, value, characterSlot); }
	FORCEINLINE void SET_PACKED_STAT_INT_CODE(int index, int value, int characterSlot) { return YimMenu::NativeInvoker::Invoke<4929, void>(index, value, characterSlot); }
	FORCEINLINE void PLAYSTATS_BACKGROUND_SCRIPT_ACTION(const char* action, int value) { return YimMenu::NativeInvoker::Invoke<4930, void>(action, value); }
	FORCEINLINE void PLAYSTATS_NPC_INVITE(const char* p0) { return YimMenu::NativeInvoker::Invoke<4931, void>(p0); }
	FORCEINLINE void PLAYSTATS_AWARD_XP(int amount, Hash type, Hash category) { return YimMenu::NativeInvoker::Invoke<4932, void>(amount, type, category); }
	FORCEINLINE void PLAYSTATS_RANK_UP(int rank) { return YimMenu::NativeInvoker::Invoke<4933, void>(rank); }
	FORCEINLINE void PLAYSTATS_STARTED_SESSION_IN_OFFLINEMODE() { return YimMenu::NativeInvoker::Invoke<4934, void>(); }
	FORCEINLINE void PLAYSTATS_ACTIVITY_DONE(int p0, int activityId) { return YimMenu::NativeInvoker::Invoke<4935, void>(p0, activityId); }
	FORCEINLINE void PLAYSTATS_LEAVE_JOB_CHAIN(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<4936, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_MISSION_STARTED(const char* p0, Any p1, Any p2, bool p3) { return YimMenu::NativeInvoker::Invoke<4937, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_MISSION_OVER(const char* p0, Any p1, Any p2, bool p3, bool p4, bool p5) { return YimMenu::NativeInvoker::Invoke<4938, void>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void PLAYSTATS_MISSION_CHECKPOINT(const char* p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4939, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_RANDOM_MISSION_DONE(const char* name, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4940, void>(name, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_ROS_BET(int amount, int act, Player player, float cm) { return YimMenu::NativeInvoker::Invoke<4941, void>(amount, act, player, cm); }
	FORCEINLINE void PLAYSTATS_RACE_CHECKPOINT(Vehicle p0, Any p1, int p2, int p3, Any p4) { return YimMenu::NativeInvoker::Invoke<4942, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE bool PLAYSTATS_CREATE_MATCH_HISTORY_ID_2(int* playerAccountId, int* posixTime) { return YimMenu::NativeInvoker::Invoke<4943, bool>(playerAccountId, posixTime); }
	FORCEINLINE void PLAYSTATS_MATCH_STARTED(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4944, void>(p0, p1, p2); }
	FORCEINLINE void PLAYSTATS_SHOP_ITEM(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<4945, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_CRATE_DROP_MISSION_DONE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return YimMenu::NativeInvoker::Invoke<4946, void>(p0, p1, p2, p3, p4, p5, p6, p7); }
	FORCEINLINE void PLAYSTATS_CRATE_CREATED(float p0, float p1, float p2) { return YimMenu::NativeInvoker::Invoke<4947, void>(p0, p1, p2); }
	FORCEINLINE void PLAYSTATS_HOLD_UP_MISSION_DONE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4948, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_IMPORT_EXPORT_MISSION_DONE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4949, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_RACE_TO_POINT_MISSION_DONE(int p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<4950, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_ACQUIRED_HIDDEN_PACKAGE(Any p0) { return YimMenu::NativeInvoker::Invoke<4951, void>(p0); }
	FORCEINLINE void PLAYSTATS_WEBSITE_VISITED(Hash scaleformHash, int p1) { return YimMenu::NativeInvoker::Invoke<4952, void>(scaleformHash, p1); }
	FORCEINLINE void PLAYSTATS_FRIEND_ACTIVITY(int p0, bool p1) { return YimMenu::NativeInvoker::Invoke<4953, void>(p0, p1); }
	FORCEINLINE void PLAYSTATS_ODDJOB_DONE(int totalTimeMs, int p1, bool p2) { return YimMenu::NativeInvoker::Invoke<4954, void>(totalTimeMs, p1, p2); }
	FORCEINLINE void PLAYSTATS_PROP_CHANGE(Ped p0, int p1, int p2, int p3) { return YimMenu::NativeInvoker::Invoke<4955, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_CLOTH_CHANGE(Ped p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<4956, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_WEAPON_MODE_CHANGE(Hash weaponHash, Hash componentHashTo, Hash componentHashFrom) { return YimMenu::NativeInvoker::Invoke<4957, void>(weaponHash, componentHashTo, componentHashFrom); }
	FORCEINLINE void PLAYSTATS_CHEAT_APPLIED(const char* cheat) { return YimMenu::NativeInvoker::Invoke<4958, void>(cheat); }
	FORCEINLINE void PLAYSTATS_JOB_ACTIVITY_END(Any* p0, Any* p1, Any* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<4959, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_JOB_BEND(Any* p0, Any* p1, Any* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<4960, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_JOB_LTS_END(Any* p0, Any* p1, Any* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<4961, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_JOB_LTS_ROUND_END(Any* p0, Any* p1, Any* p2, Any* p3) { return YimMenu::NativeInvoker::Invoke<4962, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_QUICKFIX_TOOL(int element, const char* item) { return YimMenu::NativeInvoker::Invoke<4963, void>(element, item); }
	FORCEINLINE void PLAYSTATS_IDLE_KICK(int msStoodIdle) { return YimMenu::NativeInvoker::Invoke<4964, void>(msStoodIdle); }
	FORCEINLINE void PLAYSTATS_SET_JOIN_TYPE(int joinType) { return YimMenu::NativeInvoker::Invoke<4965, void>(joinType); }
	FORCEINLINE void PLAYSTATS_HEIST_SAVE_CHEAT(Hash hash, int p1) { return YimMenu::NativeInvoker::Invoke<4966, void>(hash, p1); }
	FORCEINLINE void PLAYSTATS_APPEND_DIRECTOR_METRIC(Any* p0) { return YimMenu::NativeInvoker::Invoke<4967, void>(p0); }
	FORCEINLINE void PLAYSTATS_AWARD_BAD_SPORT(int id) { return YimMenu::NativeInvoker::Invoke<4968, void>(id); }
	FORCEINLINE void PLAYSTATS_PEGASUS_AS_PERSONAL_AIRCRAFT(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<4969, void>(modelHash); }
	FORCEINLINE void _PLAYSTATS_SHOPMENU_NAV(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4970, void>(p0, p1, p2); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_CHALLENGES(Any p0) { return YimMenu::NativeInvoker::Invoke<4971, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_VEHICLETARGET(Any p0) { return YimMenu::NativeInvoker::Invoke<4972, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_URBANWARFARE(Any p0) { return YimMenu::NativeInvoker::Invoke<4973, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_CHECKPOINTCOLLECTION(Any p0) { return YimMenu::NativeInvoker::Invoke<4974, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_ATOB(Any p0) { return YimMenu::NativeInvoker::Invoke<4975, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_PENNEDIN(Any p0) { return YimMenu::NativeInvoker::Invoke<4976, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_PASSTHEPARCEL(Any p0) { return YimMenu::NativeInvoker::Invoke<4977, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_HOTPROPERTY(Any p0) { return YimMenu::NativeInvoker::Invoke<4978, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_DEADDROP(Any p0) { return YimMenu::NativeInvoker::Invoke<4979, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_KINGOFTHECASTLE(Any p0) { return YimMenu::NativeInvoker::Invoke<4980, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_CRIMINALDAMAGE(Any p0) { return YimMenu::NativeInvoker::Invoke<4981, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_COMPETITIVEURBANWARFARE(Any p0) { return YimMenu::NativeInvoker::Invoke<4982, void>(p0); }
	FORCEINLINE void PLAYSTATS_FM_EVENT_HUNTBEAST(Any p0) { return YimMenu::NativeInvoker::Invoke<4983, void>(p0); }
	FORCEINLINE void PLAYSTATS_PIMENU_HIDE_OPTIONS(Any* data) { return YimMenu::NativeInvoker::Invoke<4984, void>(data); }
	FORCEINLINE int LEADERBOARDS_GET_NUMBER_OF_COLUMNS(int p0, Any p1) { return YimMenu::NativeInvoker::Invoke<4985, int>(p0, p1); }
	FORCEINLINE int LEADERBOARDS_GET_COLUMN_ID(int p0, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<4986, int>(p0, p1, p2); }
	FORCEINLINE int LEADERBOARDS_GET_COLUMN_TYPE(int p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4987, int>(p0, p1, p2); }
	FORCEINLINE int LEADERBOARDS_READ_CLEAR_ALL() { return YimMenu::NativeInvoker::Invoke<4988, int>(); }
	FORCEINLINE int LEADERBOARDS_READ_CLEAR(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4989, int>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS_READ_PENDING(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4990, bool>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS_READ_ANY_PENDING() { return YimMenu::NativeInvoker::Invoke<4991, bool>(); }
	FORCEINLINE bool LEADERBOARDS_READ_SUCCESSFUL(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4992, bool>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS2_READ_FRIENDS_BY_ROW(Any* p0, Any* p1, Any p2, bool p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<4993, bool>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE bool LEADERBOARDS2_READ_BY_HANDLE(Any* p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<4994, bool>(p0, p1); }
	FORCEINLINE bool LEADERBOARDS2_READ_BY_ROW(Any* p0, Any* p1, Any p2, Any* p3, Any p4, Any* p5, Any p6) { return YimMenu::NativeInvoker::Invoke<4995, bool>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE bool LEADERBOARDS2_READ_BY_RANK(Any* p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4996, bool>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS2_READ_BY_RADIUS(Any* p0, Any p1, Any* p2) { return YimMenu::NativeInvoker::Invoke<4997, bool>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS2_READ_BY_SCORE_INT(Any* p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4998, bool>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS2_READ_BY_SCORE_FLOAT(Any* p0, float p1, Any p2) { return YimMenu::NativeInvoker::Invoke<4999, bool>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS2_READ_RANK_PREDICTION(Any* p0, Any* p1, Any* p2) { return YimMenu::NativeInvoker::Invoke<5000, bool>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS2_READ_BY_PLAFORM(Any* p0, const char* gamerHandleCsv, const char* platformName) { return YimMenu::NativeInvoker::Invoke<5001, bool>(p0, gamerHandleCsv, platformName); }
	FORCEINLINE bool LEADERBOARDS2_READ_GET_ROW_DATA_START(Any* p0) { return YimMenu::NativeInvoker::Invoke<5002, bool>(p0); }
	FORCEINLINE void LEADERBOARDS2_READ_GET_ROW_DATA_END() { return YimMenu::NativeInvoker::Invoke<5003, void>(); }
	FORCEINLINE bool LEADERBOARDS2_READ_GET_ROW_DATA_INFO(Any p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<5004, bool>(p0, p1); }
	FORCEINLINE int LEADERBOARDS2_READ_GET_ROW_DATA_INT(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5005, int>(p0, p1); }
	FORCEINLINE float LEADERBOARDS2_READ_GET_ROW_DATA_FLOAT(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5006, float>(p0, p1); }
	FORCEINLINE bool LEADERBOARDS2_WRITE_DATA(Any* p0) { return YimMenu::NativeInvoker::Invoke<5007, bool>(p0); }
	FORCEINLINE void LEADERBOARDS_WRITE_ADD_COLUMN(Any p0, Any p1, float p2) { return YimMenu::NativeInvoker::Invoke<5008, void>(p0, p1, p2); }
	FORCEINLINE void LEADERBOARDS_WRITE_ADD_COLUMN_LONG(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5009, void>(p0, p1, p2); }
	FORCEINLINE bool LEADERBOARDS_CACHE_DATA_ROW(Any* p0) { return YimMenu::NativeInvoker::Invoke<5010, bool>(p0); }
	FORCEINLINE void LEADERBOARDS_CLEAR_CACHE_DATA() { return YimMenu::NativeInvoker::Invoke<5011, void>(); }
	FORCEINLINE void LEADERBOARDS_CLEAR_CACHE_DATA_ID(Any p0) { return YimMenu::NativeInvoker::Invoke<5012, void>(p0); }
	FORCEINLINE bool LEADERBOARDS_GET_CACHE_EXISTS(Any p0) { return YimMenu::NativeInvoker::Invoke<5013, bool>(p0); }
	FORCEINLINE int LEADERBOARDS_GET_CACHE_TIME(Any p0) { return YimMenu::NativeInvoker::Invoke<5014, int>(p0); }
	FORCEINLINE int LEADERBOARDS_GET_CACHE_NUMBER_OF_ROWS(Any p0) { return YimMenu::NativeInvoker::Invoke<5015, int>(p0); }
	FORCEINLINE bool LEADERBOARDS_GET_CACHE_DATA_ROW(Any p0, Any p1, Any* p2) { return YimMenu::NativeInvoker::Invoke<5016, bool>(p0, p1, p2); }
	FORCEINLINE void PRESENCE_EVENT_UPDATESTAT_INT(Hash statHash, int value, int p2) { return YimMenu::NativeInvoker::Invoke<5017, void>(statHash, value, p2); }
	FORCEINLINE void PRESENCE_EVENT_UPDATESTAT_FLOAT(Hash statHash, float value, int p2) { return YimMenu::NativeInvoker::Invoke<5018, void>(statHash, value, p2); }
	FORCEINLINE void PRESENCE_EVENT_UPDATESTAT_INT_WITH_STRING(Hash statHash, int value, int p2, const char* string) { return YimMenu::NativeInvoker::Invoke<5019, void>(statHash, value, p2, string); }
	FORCEINLINE bool GET_PLAYER_HAS_DRIVEN_ALL_VEHICLES() { return YimMenu::NativeInvoker::Invoke<5020, bool>(); }
	FORCEINLINE void SET_HAS_POSTED_ALL_VEHICLES_DRIVEN() { return YimMenu::NativeInvoker::Invoke<5021, void>(); }
	FORCEINLINE void SET_PROFILE_SETTING_PROLOGUE_COMPLETE() { return YimMenu::NativeInvoker::Invoke<5022, void>(); }
	FORCEINLINE void SET_PROFILE_SETTING_SP_CHOP_MISSION_COMPLETE() { return YimMenu::NativeInvoker::Invoke<5023, void>(); }
	FORCEINLINE void SET_PROFILE_SETTING_CREATOR_RACES_DONE(int value) { return YimMenu::NativeInvoker::Invoke<5024, void>(value); }
	FORCEINLINE void SET_PROFILE_SETTING_CREATOR_DM_DONE(int value) { return YimMenu::NativeInvoker::Invoke<5025, void>(value); }
	FORCEINLINE void SET_PROFILE_SETTING_CREATOR_CTF_DONE(int value) { return YimMenu::NativeInvoker::Invoke<5026, void>(value); }
	FORCEINLINE void SET_JOB_ACTIVITY_ID_STARTED(Any p0, int characterSlot) { return YimMenu::NativeInvoker::Invoke<5027, void>(p0, characterSlot); }
	FORCEINLINE void SET_FREEMODE_PROLOGUE_DONE(Any p0, int characterSlot) { return YimMenu::NativeInvoker::Invoke<5028, void>(p0, characterSlot); }
	FORCEINLINE void SET_FREEMODE_STRAND_PROGRESSION_STATUS(int profileSetting, int settingValue) { return YimMenu::NativeInvoker::Invoke<5029, void>(profileSetting, settingValue); }
	FORCEINLINE void STAT_NETWORK_INCREMENT_ON_SUICIDE(Any p0, float p1) { return YimMenu::NativeInvoker::Invoke<5030, void>(p0, p1); }
	FORCEINLINE void STAT_SET_CHEAT_IS_ACTIVE() { return YimMenu::NativeInvoker::Invoke<5031, void>(); }
	FORCEINLINE bool LEADERBOARDS2_WRITE_DATA_FOR_EVENT_TYPE(Any* p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<5032, bool>(p0, p1); }
	FORCEINLINE void FORCE_CLOUD_MP_STATS_DOWNLOAD_AND_OVERWRITE_LOCAL_SAVE() { return YimMenu::NativeInvoker::Invoke<5033, void>(); }
	FORCEINLINE void STAT_MIGRATE_CLEAR_FOR_RESTART() { return YimMenu::NativeInvoker::Invoke<5034, void>(); }
	FORCEINLINE bool STAT_MIGRATE_SAVEGAME_START(const char* platformName) { return YimMenu::NativeInvoker::Invoke<5035, bool>(platformName); }
	FORCEINLINE int STAT_MIGRATE_SAVEGAME_GET_STATUS() { return YimMenu::NativeInvoker::Invoke<5036, int>(); }
	FORCEINLINE bool STAT_MIGRATE_CHECK_ALREADY_DONE() { return YimMenu::NativeInvoker::Invoke<5037, bool>(); }
	FORCEINLINE bool STAT_MIGRATE_CHECK_START() { return YimMenu::NativeInvoker::Invoke<5038, bool>(); }
	FORCEINLINE int STAT_MIGRATE_CHECK_GET_IS_PLATFORM_AVAILABLE(int p0) { return YimMenu::NativeInvoker::Invoke<5039, int>(p0); }
	FORCEINLINE int STAT_MIGRATE_CHECK_GET_PLATFORM_STATUS(int p0, Any* p1) { return YimMenu::NativeInvoker::Invoke<5040, int>(p0, p1); }
	FORCEINLINE int STAT_GET_SAVE_MIGRATION_STATUS(Any* data) { return YimMenu::NativeInvoker::Invoke<5041, int>(data); }
	FORCEINLINE bool STAT_SAVE_MIGRATION_CANCEL_PENDING_OPERATION() { return YimMenu::NativeInvoker::Invoke<5042, bool>(); }
	FORCEINLINE int STAT_GET_CANCEL_SAVE_MIGRATION_STATUS() { return YimMenu::NativeInvoker::Invoke<5043, int>(); }
	FORCEINLINE bool STAT_SAVE_MIGRATION_CONSUME_CONTENT(Hash contentId, const char* srcPlatform, const char* srcGamerHandle) { return YimMenu::NativeInvoker::Invoke<5044, bool>(contentId, srcPlatform, srcGamerHandle); }
	FORCEINLINE int STAT_GET_SAVE_MIGRATION_CONSUME_CONTENT_STATUS(int* p0) { return YimMenu::NativeInvoker::Invoke<5045, int>(p0); }
	FORCEINLINE void STAT_ENABLE_STATS_TRACKING() { return YimMenu::NativeInvoker::Invoke<5046, void>(); }
	FORCEINLINE void STAT_DISABLE_STATS_TRACKING() { return YimMenu::NativeInvoker::Invoke<5047, void>(); }
	FORCEINLINE bool STAT_IS_STATS_TRACKING_ENABLED() { return YimMenu::NativeInvoker::Invoke<5048, bool>(); }
	FORCEINLINE bool STAT_START_RECORD_STAT(int statType, int valueType) { return YimMenu::NativeInvoker::Invoke<5049, bool>(statType, valueType); }
	FORCEINLINE bool STAT_STOP_RECORD_STAT() { return YimMenu::NativeInvoker::Invoke<5050, bool>(); }
	FORCEINLINE bool STAT_GET_RECORDED_VALUE(float* value) { return YimMenu::NativeInvoker::Invoke<5051, bool>(value); }
	FORCEINLINE bool STAT_IS_RECORDING_STAT() { return YimMenu::NativeInvoker::Invoke<5052, bool>(); }
	FORCEINLINE int STAT_GET_CURRENT_NEAR_MISS_NOCRASH_PRECISE() { return YimMenu::NativeInvoker::Invoke<5053, int>(); }
	FORCEINLINE float STAT_GET_CURRENT_REAR_WHEEL_DISTANCE() { return YimMenu::NativeInvoker::Invoke<5054, float>(); }
	FORCEINLINE float STAT_GET_CURRENT_FRONT_WHEEL_DISTANCE() { return YimMenu::NativeInvoker::Invoke<5055, float>(); }
	FORCEINLINE float STAT_GET_CURRENT_JUMP_DISTANCE() { return YimMenu::NativeInvoker::Invoke<5056, float>(); }
	FORCEINLINE float STAT_GET_CURRENT_DRIVE_NOCRASH_DISTANCE() { return YimMenu::NativeInvoker::Invoke<5057, float>(); }
	FORCEINLINE float STAT_GET_CURRENT_SPEED() { return YimMenu::NativeInvoker::Invoke<5058, float>(); }
	FORCEINLINE float STAT_GET_CURRENT_DRIVING_REVERSE_DISTANCE() { return YimMenu::NativeInvoker::Invoke<5059, float>(); }
	FORCEINLINE float STAT_GET_CURRENT_SKYDIVING_DISTANCE() { return YimMenu::NativeInvoker::Invoke<5060, float>(); }
	FORCEINLINE float STAT_GET_CHALLENGE_FLYING_DIST() { return YimMenu::NativeInvoker::Invoke<5061, float>(); }
	FORCEINLINE bool STAT_GET_FLYING_ALTITUDE(float* outValue) { return YimMenu::NativeInvoker::Invoke<5062, bool>(outValue); }
	FORCEINLINE bool STAT_IS_PLAYER_VEHICLE_ABOVE_OCEAN() { return YimMenu::NativeInvoker::Invoke<5063, bool>(); }
	FORCEINLINE float STAT_GET_VEHICLE_BAIL_DISTANCE() { return YimMenu::NativeInvoker::Invoke<5064, float>(); }
	FORCEINLINE bool STAT_ROLLBACK_SAVE_MIGRATION() { return YimMenu::NativeInvoker::Invoke<5065, bool>(); }
	FORCEINLINE void SET_HAS_SPECIALEDITION_CONTENT(int value) { return YimMenu::NativeInvoker::Invoke<5066, void>(value); }
	FORCEINLINE void SET_SAVE_MIGRATION_TRANSACTION_ID_WARNING(int transactionId) { return YimMenu::NativeInvoker::Invoke<5067, void>(transactionId); }
	FORCEINLINE void GET_BOSS_GOON_UUID(int characterSlot, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5068, void>(characterSlot, p1, p2); }
	FORCEINLINE void PLAYSTATS_BW_BOSSONBOSSDEATHMATCH(Any p0) { return YimMenu::NativeInvoker::Invoke<5069, void>(p0); }
	FORCEINLINE void PLAYSTATS_BW_YATCHATTACK(Any p0) { return YimMenu::NativeInvoker::Invoke<5070, void>(p0); }
	FORCEINLINE void PLAYSTATS_BW_HUNT_THE_BOSS(Any p0) { return YimMenu::NativeInvoker::Invoke<5071, void>(p0); }
	FORCEINLINE void PLAYSTATS_BW_SIGHTSEER(Any p0) { return YimMenu::NativeInvoker::Invoke<5072, void>(p0); }
	FORCEINLINE void PLAYSTATS_BW_ASSAULT(Any p0) { return YimMenu::NativeInvoker::Invoke<5073, void>(p0); }
	FORCEINLINE void PLAYSTATS_BW_BELLY_OF_THE_BEAST(Any p0) { return YimMenu::NativeInvoker::Invoke<5074, void>(p0); }
	FORCEINLINE void PLAYSTATS_BW_HEAD_HUNTER(Any p0) { return YimMenu::NativeInvoker::Invoke<5075, void>(p0); }
	FORCEINLINE void PLAYSTATS_BW_FRAGILE_GOODS(Any p0) { return YimMenu::NativeInvoker::Invoke<5076, void>(p0); }
	FORCEINLINE void PLAYSTATS_BW_AIR_FREIGHT(Any p0) { return YimMenu::NativeInvoker::Invoke<5077, void>(p0); }
	FORCEINLINE void PLAYSTATS_BC_CAR_JACKING(Any p0) { return YimMenu::NativeInvoker::Invoke<5078, void>(p0); }
	FORCEINLINE void PLAYSTATS_BC_SMASH_AND_GRAB(Any p0) { return YimMenu::NativeInvoker::Invoke<5079, void>(p0); }
	FORCEINLINE void PLAYSTATS_BC_PROTECTION_RACKET(Any p0) { return YimMenu::NativeInvoker::Invoke<5080, void>(p0); }
	FORCEINLINE void PLAYSTATS_BC_MOST_WANTED(Any p0) { return YimMenu::NativeInvoker::Invoke<5081, void>(p0); }
	FORCEINLINE void PLAYSTATS_BC_FINDERS_KEEPERS(Any p0) { return YimMenu::NativeInvoker::Invoke<5082, void>(p0); }
	FORCEINLINE void PLAYSTATS_BC_POINT_TO_POINT(Any p0) { return YimMenu::NativeInvoker::Invoke<5083, void>(p0); }
	FORCEINLINE void PLAYSTATS_BC_CASHING(Any p0) { return YimMenu::NativeInvoker::Invoke<5084, void>(p0); }
	FORCEINLINE void PLAYSTATS_BC_SALVAGE(Any p0) { return YimMenu::NativeInvoker::Invoke<5085, void>(p0); }
	FORCEINLINE void PLAYSTATS_SPENT_PI_CUSTOM_LOADOUT(int amount) { return YimMenu::NativeInvoker::Invoke<5086, void>(amount); }
	FORCEINLINE void PLAYSTATS_BUY_CONTRABAND_MISSION(Any* data) { return YimMenu::NativeInvoker::Invoke<5087, void>(data); }
	FORCEINLINE void PLAYSTATS_SELL_CONTRABAND_MISSION(Any* data) { return YimMenu::NativeInvoker::Invoke<5088, void>(data); }
	FORCEINLINE void PLAYSTATS_DEFEND_CONTRABAND_MISSION(Any* data) { return YimMenu::NativeInvoker::Invoke<5089, void>(data); }
	FORCEINLINE void PLAYSTATS_RECOVER_CONTRABAND_MISSION(Any* data) { return YimMenu::NativeInvoker::Invoke<5090, void>(data); }
	FORCEINLINE void PLAYSTATS_HIT_CONTRABAND_DESTROY_LIMIT(Any p0) { return YimMenu::NativeInvoker::Invoke<5091, void>(p0); }
	FORCEINLINE void START_BEING_BOSS(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5092, void>(p0, p1); }
	FORCEINLINE void START_BEING_GOON(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5093, void>(p0, p1, p2); }
	FORCEINLINE void END_BEING_BOSS(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5094, void>(p0, p1, p2); }
	FORCEINLINE void END_BEING_GOON(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<5095, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void HIRED_LIMO(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5096, void>(p0, p1); }
	FORCEINLINE void ORDER_BOSS_VEHICLE(Any p0, Any p1, Hash vehicleHash) { return YimMenu::NativeInvoker::Invoke<5097, void>(p0, p1, vehicleHash); }
	FORCEINLINE void CHANGE_UNIFORM(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5098, void>(p0, p1, p2); }
	FORCEINLINE void CHANGE_GOON_LOOKING_FOR_WORK(Any p0) { return YimMenu::NativeInvoker::Invoke<5099, void>(p0); }
	FORCEINLINE void SEND_METRIC_GHOSTING_TO_PLAYER(Any p0) { return YimMenu::NativeInvoker::Invoke<5100, void>(p0); }
	FORCEINLINE void SEND_METRIC_VIP_POACH(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5101, void>(p0, p1, p2); }
	FORCEINLINE void SEND_METRIC_PUNISH_BODYGUARD(Any p0) { return YimMenu::NativeInvoker::Invoke<5102, void>(p0); }
	FORCEINLINE void PLAYSTATS_START_TRACKING_STUNTS() { return YimMenu::NativeInvoker::Invoke<5103, void>(); }
	FORCEINLINE void PLAYSTATS_STOP_TRACKING_STUNTS() { return YimMenu::NativeInvoker::Invoke<5104, void>(); }
	FORCEINLINE void PLAYSTATS_MISSION_ENDED(Any p0) { return YimMenu::NativeInvoker::Invoke<5105, void>(p0); }
	FORCEINLINE void PLAYSTATS_IMPEXP_MISSION_ENDED(Any p0) { return YimMenu::NativeInvoker::Invoke<5106, void>(p0); }
	FORCEINLINE void PLAYSTATS_CHANGE_MC_ROLE(Any p0, Any p1, Any p2, Any p3, int role, int p5, Any p6) { return YimMenu::NativeInvoker::Invoke<5107, void>(p0, p1, p2, p3, role, p5, p6); }
	FORCEINLINE void PLAYSTATS_CHANGE_MC_OUTFIT(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<5108, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_SWITCH_MC_EMBLEM(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<5109, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_MC_REQUEST_BIKE(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<5110, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_MC_KILLED_RIVAL_MC_MEMBER(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<5111, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_ABANDONED_MC(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<5112, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_EARNED_MC_POINTS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<5113, void>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void PLAYSTATS_MC_FORMATION_ENDS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<5114, void>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void PLAYSTATS_MC_CLUBHOUSE_ACTIVITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7) { return YimMenu::NativeInvoker::Invoke<5115, void>(p0, p1, p2, p3, p4, p5, p6, p7); }
	FORCEINLINE void PLAYSTATS_RIVAL_BEHAVIOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9) { return YimMenu::NativeInvoker::Invoke<5116, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9); }
	FORCEINLINE void PLAYSTATS_COPY_RANK_INTO_NEW_SLOT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<5117, void>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void PLAYSTATS_DUPE_DETECTED(Any* data) { return YimMenu::NativeInvoker::Invoke<5118, void>(data); }
	FORCEINLINE void PLAYSTATS_BAN_ALERT(int p0) { return YimMenu::NativeInvoker::Invoke<5119, void>(p0); }
	FORCEINLINE void PLAYSTATS_GUNRUNNING_MISSION_ENDED(Any* data) { return YimMenu::NativeInvoker::Invoke<5120, void>(data); }
	FORCEINLINE void PLAYSTATS_GUNRUNNING_RND(Any p0) { return YimMenu::NativeInvoker::Invoke<5121, void>(p0); }
	FORCEINLINE void PLAYSTATS_BUSINESS_BATTLE_ENDED(Any p0) { return YimMenu::NativeInvoker::Invoke<5122, void>(p0); }
	FORCEINLINE void PLAYSTATS_WAREHOUSE_MISSION_ENDED(Any p0) { return YimMenu::NativeInvoker::Invoke<5123, void>(p0); }
	FORCEINLINE void PLAYSTATS_NIGHTCLUB_MISSION_ENDED(Any p0) { return YimMenu::NativeInvoker::Invoke<5124, void>(p0); }
	FORCEINLINE void PLAYSTATS_DJ_USAGE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5125, void>(p0, p1); }
	FORCEINLINE void PLAYSTATS_MINIGAME_USAGE(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5126, void>(p0, p1, p2); }
	FORCEINLINE void PLAYSTATS_STONE_HATCHET_ENDED(Any* data) { return YimMenu::NativeInvoker::Invoke<5127, void>(data); }
	FORCEINLINE void PLAYSTATS_SMUGGLER_MISSION_ENDED(Any* data) { return YimMenu::NativeInvoker::Invoke<5128, void>(data); }
	FORCEINLINE void PLAYSTATS_FM_HEIST_PREP_ENDED(Any* data) { return YimMenu::NativeInvoker::Invoke<5129, void>(data); }
	FORCEINLINE void PLAYSTATS_INSTANCED_HEIST_ENDED(Any* data, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<5130, void>(data, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_DAR_CHECKPOINT(Any* data) { return YimMenu::NativeInvoker::Invoke<5131, void>(data); }
	FORCEINLINE void PLAYSTATS_ENTER_SESSION_PACK(Any* data) { return YimMenu::NativeInvoker::Invoke<5132, void>(data); }
	FORCEINLINE void PLAYSTATS_DRONE_USAGE(int p0, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<5133, void>(p0, p1, p2); }
	FORCEINLINE void PLAYSTATS_SPIN_WHEEL(int p0, int p1, int p2, int p3) { return YimMenu::NativeInvoker::Invoke<5134, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_ARENA_WARS_SPECTATOR(int p0, int p1, int p2, int p3, int p4) { return YimMenu::NativeInvoker::Invoke<5135, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_ARENA_WARS_ENDED(Any* data) { return YimMenu::NativeInvoker::Invoke<5136, void>(data); }
	FORCEINLINE void PLAYSTATS_SWITCH_PASSIVE_MODE(bool p0, int p1, int p2, int p3) { return YimMenu::NativeInvoker::Invoke<5137, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_COLLECTIBLE_PICKED_UP(int p0, Hash objectHash, Any p2, Any p3, int moneyAmount, int rpAmount, int chipsAmount, Any p7, int p8, Any p9, Any p10) { return YimMenu::NativeInvoker::Invoke<5138, void>(p0, objectHash, p2, p3, moneyAmount, rpAmount, chipsAmount, p7, p8, p9, p10); }
	FORCEINLINE void PLAYSTATS_CASINO_STORY_MISSION_ENDED(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5139, void>(p0, p1); }
	FORCEINLINE void PLAYSTATS_CASINO_CHIP(Any p0) { return YimMenu::NativeInvoker::Invoke<5140, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_ROULETTE(Any p0) { return YimMenu::NativeInvoker::Invoke<5141, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_BLACKJACK(Any p0) { return YimMenu::NativeInvoker::Invoke<5142, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_THREE_CARD_POKER(Any p0) { return YimMenu::NativeInvoker::Invoke<5143, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_SLOT_MACHINE(Any p0) { return YimMenu::NativeInvoker::Invoke<5144, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_INSIDE_TRACK(Any p0) { return YimMenu::NativeInvoker::Invoke<5145, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_LUCKY_SEVEN(Any p0) { return YimMenu::NativeInvoker::Invoke<5146, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_ROULETTE_LIGHT(Any p0) { return YimMenu::NativeInvoker::Invoke<5147, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_BLACKJACK_LIGHT(Any p0) { return YimMenu::NativeInvoker::Invoke<5148, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_THREE_CARD_POKER_LIGHT(Any p0) { return YimMenu::NativeInvoker::Invoke<5149, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_SLOT_MACHINE_LIGHT(Any p0) { return YimMenu::NativeInvoker::Invoke<5150, void>(p0); }
	FORCEINLINE void PLAYSTATS_CASINO_INSIDE_TRACK_LIGHT(Any p0) { return YimMenu::NativeInvoker::Invoke<5151, void>(p0); }
	FORCEINLINE void PLAYSTATS_ARCADE_GAME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<5152, void>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void PLAYSTATS_ARCADE_LOVE_MATCH(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5153, void>(p0, p1); }
	FORCEINLINE void PLAYSTATS_FREEMODE_CASINO_MISSION_ENDED(Any* data) { return YimMenu::NativeInvoker::Invoke<5154, void>(data); }
	FORCEINLINE void PLAYSTATS_HEIST3_DRONE(Any p0) { return YimMenu::NativeInvoker::Invoke<5155, void>(p0); }
	FORCEINLINE void PLAYSTATS_HEIST3_HACK(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<5156, void>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void PLAYSTATS_NPC_PHONE(Any* p0) { return YimMenu::NativeInvoker::Invoke<5157, void>(p0); }
	FORCEINLINE void PLAYSTATS_ARCADE_CABINET(Any p0) { return YimMenu::NativeInvoker::Invoke<5158, void>(p0); }
	FORCEINLINE void PLAYSTATS_HEIST3_FINALE(Any p0) { return YimMenu::NativeInvoker::Invoke<5159, void>(p0); }
	FORCEINLINE void PLAYSTATS_HEIST3_PREP(Any p0) { return YimMenu::NativeInvoker::Invoke<5160, void>(p0); }
	FORCEINLINE void PLAYSTATS_MASTER_CONTROL(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<5161, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_QUIT_MODE(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<5162, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_MISSION_VOTE(Any p0) { return YimMenu::NativeInvoker::Invoke<5163, void>(p0); }
	FORCEINLINE void PLAYSTATS_NJVS_VOTE(Any p0) { return YimMenu::NativeInvoker::Invoke<5164, void>(p0); }
	FORCEINLINE void PLAYSTATS_KILL_YOURSELF() { return YimMenu::NativeInvoker::Invoke<5165, void>(); }
	FORCEINLINE void PLAYSTATS_FM_MISSION_END(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5166, void>(p0, p1, p2); }
	FORCEINLINE void PLAYSTATS_HEIST4_PREP(Any p0) { return YimMenu::NativeInvoker::Invoke<5167, void>(p0); }
	FORCEINLINE void PLAYSTATS_HEIST4_FINALE(Any p0) { return YimMenu::NativeInvoker::Invoke<5168, void>(p0); }
	FORCEINLINE void PLAYSTATS_HEIST4_HACK(Any p0, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<5169, void>(p0, p1, p2, p3, p4); }
	FORCEINLINE void PLAYSTATS_SUB_WEAP(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<5170, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_FAST_TRVL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10) { return YimMenu::NativeInvoker::Invoke<5171, void>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); }
	FORCEINLINE void PLAYSTATS_HUB_ENTRY(Any p0) { return YimMenu::NativeInvoker::Invoke<5172, void>(p0); }
	FORCEINLINE void PLAYSTATS_DJ_MISSION_ENDED(Any p0) { return YimMenu::NativeInvoker::Invoke<5173, void>(p0); }
	FORCEINLINE void PLAYSTATS_ROBBERY_PREP(Any p0) { return YimMenu::NativeInvoker::Invoke<5174, void>(p0); }
	FORCEINLINE void PLAYSTATS_ROBBERY_FINALE(Any p0) { return YimMenu::NativeInvoker::Invoke<5175, void>(p0); }
	FORCEINLINE void PLAYSTATS_EXTRA_EVENT(Any p0) { return YimMenu::NativeInvoker::Invoke<5176, void>(p0); }
	FORCEINLINE void PLAYSTATS_CARCLUB_POINTS(Any p0) { return YimMenu::NativeInvoker::Invoke<5177, void>(p0); }
	FORCEINLINE void PLAYSTATS_CARCLUB_CHALLENGE(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<5178, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_CARCLUB_PRIZE(int p0, Hash vehicleModel) { return YimMenu::NativeInvoker::Invoke<5179, void>(p0, vehicleModel); }
	FORCEINLINE void PLAYSTATS_AWARD_NAV(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<5180, void>(p0, p1, p2, p3); }
	FORCEINLINE void PLAYSTATS_INST_MISSION_END(Any p0) { return YimMenu::NativeInvoker::Invoke<5181, void>(p0); }
	FORCEINLINE void PLAYSTATS_HUB_EXIT(Any p0) { return YimMenu::NativeInvoker::Invoke<5182, void>(p0); }
	FORCEINLINE void PLAYSTATS_INVENTORY(Any p0) { return YimMenu::NativeInvoker::Invoke<5183, void>(p0); }
	FORCEINLINE void _PLAYSTATS_ACID_MISSION_END(Any p0) { return YimMenu::NativeInvoker::Invoke<5184, void>(p0); }
	FORCEINLINE void _PLAYSTATS_ACID_RND(Any p0) { return YimMenu::NativeInvoker::Invoke<5185, void>(p0); }
	FORCEINLINE void _PLAYSTATS_IDLE(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5186, void>(p0, p1, p2); }
	FORCEINLINE void _PLAYSTATS_PLAYER_STYLE(Any p0) { return YimMenu::NativeInvoker::Invoke<5187, void>(p0); }
}

namespace STREAMING
{
	FORCEINLINE void LOAD_ALL_OBJECTS_NOW() { return YimMenu::NativeInvoker::Invoke<5188, void>(); }
	FORCEINLINE void LOAD_SCENE(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5189, void>(x, y, z); }
	FORCEINLINE bool NETWORK_UPDATE_LOAD_SCENE() { return YimMenu::NativeInvoker::Invoke<5190, bool>(); }
	FORCEINLINE bool IS_NETWORK_LOADING_SCENE() { return YimMenu::NativeInvoker::Invoke<5191, bool>(); }
	FORCEINLINE void SET_INTERIOR_ACTIVE(int interiorID, bool toggle) { return YimMenu::NativeInvoker::Invoke<5192, void>(interiorID, toggle); }
	FORCEINLINE void REQUEST_MODEL(Hash model) { return YimMenu::NativeInvoker::Invoke<5193, void>(model); }
	FORCEINLINE void REQUEST_MENU_PED_MODEL(Hash model) { return YimMenu::NativeInvoker::Invoke<5194, void>(model); }
	FORCEINLINE bool HAS_MODEL_LOADED(Hash model) { return YimMenu::NativeInvoker::Invoke<5195, bool>(model); }
	FORCEINLINE void REQUEST_MODELS_IN_ROOM(Interior interior, const char* roomName) { return YimMenu::NativeInvoker::Invoke<5196, void>(interior, roomName); }
	FORCEINLINE void SET_MODEL_AS_NO_LONGER_NEEDED(Hash model) { return YimMenu::NativeInvoker::Invoke<5197, void>(model); }
	FORCEINLINE bool IS_MODEL_IN_CDIMAGE(Hash model) { return YimMenu::NativeInvoker::Invoke<5198, bool>(model); }
	FORCEINLINE bool IS_MODEL_VALID(Hash model) { return YimMenu::NativeInvoker::Invoke<5199, bool>(model); }
	FORCEINLINE bool IS_MODEL_A_PED(Hash model) { return YimMenu::NativeInvoker::Invoke<5200, bool>(model); }
	FORCEINLINE bool IS_MODEL_A_VEHICLE(Hash model) { return YimMenu::NativeInvoker::Invoke<5201, bool>(model); }
	FORCEINLINE void REQUEST_COLLISION_AT_COORD(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5202, void>(x, y, z); }
	FORCEINLINE void REQUEST_COLLISION_FOR_MODEL(Hash model) { return YimMenu::NativeInvoker::Invoke<5203, void>(model); }
	FORCEINLINE bool HAS_COLLISION_FOR_MODEL_LOADED(Hash model) { return YimMenu::NativeInvoker::Invoke<5204, bool>(model); }
	FORCEINLINE void REQUEST_ADDITIONAL_COLLISION_AT_COORD(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5205, void>(x, y, z); }
	FORCEINLINE bool DOES_ANIM_DICT_EXIST(const char* animDict) { return YimMenu::NativeInvoker::Invoke<5206, bool>(animDict); }
	FORCEINLINE void REQUEST_ANIM_DICT(const char* animDict) { return YimMenu::NativeInvoker::Invoke<5207, void>(animDict); }
	FORCEINLINE bool HAS_ANIM_DICT_LOADED(const char* animDict) { return YimMenu::NativeInvoker::Invoke<5208, bool>(animDict); }
	FORCEINLINE void REMOVE_ANIM_DICT(const char* animDict) { return YimMenu::NativeInvoker::Invoke<5209, void>(animDict); }
	FORCEINLINE void REQUEST_ANIM_SET(const char* animSet) { return YimMenu::NativeInvoker::Invoke<5210, void>(animSet); }
	FORCEINLINE bool HAS_ANIM_SET_LOADED(const char* animSet) { return YimMenu::NativeInvoker::Invoke<5211, bool>(animSet); }
	FORCEINLINE void REMOVE_ANIM_SET(const char* animSet) { return YimMenu::NativeInvoker::Invoke<5212, void>(animSet); }
	FORCEINLINE void REQUEST_CLIP_SET(const char* clipSet) { return YimMenu::NativeInvoker::Invoke<5213, void>(clipSet); }
	FORCEINLINE bool HAS_CLIP_SET_LOADED(const char* clipSet) { return YimMenu::NativeInvoker::Invoke<5214, bool>(clipSet); }
	FORCEINLINE void REMOVE_CLIP_SET(const char* clipSet) { return YimMenu::NativeInvoker::Invoke<5215, void>(clipSet); }
	FORCEINLINE void REQUEST_IPL(const char* iplName) { return YimMenu::NativeInvoker::Invoke<5216, void>(iplName); }
	FORCEINLINE void REMOVE_IPL(const char* iplName) { return YimMenu::NativeInvoker::Invoke<5217, void>(iplName); }
	FORCEINLINE bool IS_IPL_ACTIVE(const char* iplName) { return YimMenu::NativeInvoker::Invoke<5218, bool>(iplName); }
	FORCEINLINE void SET_STREAMING(bool toggle) { return YimMenu::NativeInvoker::Invoke<5219, void>(toggle); }
	FORCEINLINE void LOAD_GLOBAL_WATER_FILE(int waterType) { return YimMenu::NativeInvoker::Invoke<5220, void>(waterType); }
	FORCEINLINE int GET_GLOBAL_WATER_FILE() { return YimMenu::NativeInvoker::Invoke<5221, int>(); }
	FORCEINLINE void SET_GAME_PAUSES_FOR_STREAMING(bool toggle) { return YimMenu::NativeInvoker::Invoke<5222, void>(toggle); }
	FORCEINLINE void SET_REDUCE_PED_MODEL_BUDGET(bool toggle) { return YimMenu::NativeInvoker::Invoke<5223, void>(toggle); }
	FORCEINLINE void SET_REDUCE_VEHICLE_MODEL_BUDGET(bool toggle) { return YimMenu::NativeInvoker::Invoke<5224, void>(toggle); }
	FORCEINLINE void SET_DITCH_POLICE_MODELS(bool toggle) { return YimMenu::NativeInvoker::Invoke<5225, void>(toggle); }
	FORCEINLINE int GET_NUMBER_OF_STREAMING_REQUESTS() { return YimMenu::NativeInvoker::Invoke<5226, int>(); }
	FORCEINLINE void REQUEST_PTFX_ASSET() { return YimMenu::NativeInvoker::Invoke<5227, void>(); }
	FORCEINLINE bool HAS_PTFX_ASSET_LOADED() { return YimMenu::NativeInvoker::Invoke<5228, bool>(); }
	FORCEINLINE void REMOVE_PTFX_ASSET() { return YimMenu::NativeInvoker::Invoke<5229, void>(); }
	FORCEINLINE void REQUEST_NAMED_PTFX_ASSET(const char* fxName) { return YimMenu::NativeInvoker::Invoke<5230, void>(fxName); }
	FORCEINLINE bool HAS_NAMED_PTFX_ASSET_LOADED(const char* fxName) { return YimMenu::NativeInvoker::Invoke<5231, bool>(fxName); }
	FORCEINLINE void REMOVE_NAMED_PTFX_ASSET(const char* fxName) { return YimMenu::NativeInvoker::Invoke<5232, void>(fxName); }
	FORCEINLINE void SET_VEHICLE_POPULATION_BUDGET(int p0) { return YimMenu::NativeInvoker::Invoke<5233, void>(p0); }
	FORCEINLINE void SET_PED_POPULATION_BUDGET(int p0) { return YimMenu::NativeInvoker::Invoke<5234, void>(p0); }
	FORCEINLINE void CLEAR_FOCUS() { return YimMenu::NativeInvoker::Invoke<5235, void>(); }
	FORCEINLINE void SET_FOCUS_POS_AND_VEL(float x, float y, float z, float offsetX, float offsetY, float offsetZ) { return YimMenu::NativeInvoker::Invoke<5236, void>(x, y, z, offsetX, offsetY, offsetZ); }
	FORCEINLINE void SET_FOCUS_ENTITY(Entity entity) { return YimMenu::NativeInvoker::Invoke<5237, void>(entity); }
	FORCEINLINE bool IS_ENTITY_FOCUS(Entity entity) { return YimMenu::NativeInvoker::Invoke<5238, bool>(entity); }
	FORCEINLINE void SET_RESTORE_FOCUS_ENTITY(Entity p0) { return YimMenu::NativeInvoker::Invoke<5239, void>(p0); }
	FORCEINLINE void SET_MAPDATACULLBOX_ENABLED(const char* name, bool toggle) { return YimMenu::NativeInvoker::Invoke<5240, void>(name, toggle); }
	FORCEINLINE void SET_ALL_MAPDATA_CULLED(Any p0) { return YimMenu::NativeInvoker::Invoke<5241, void>(p0); }
	FORCEINLINE int STREAMVOL_CREATE_SPHERE(float x, float y, float z, float rad, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<5242, int>(x, y, z, rad, p4, p5); }
	FORCEINLINE int STREAMVOL_CREATE_FRUSTUM(float p0, float p1, float p2, float p3, float p4, float p5, float p6, Any p7, Any p8) { return YimMenu::NativeInvoker::Invoke<5243, int>(p0, p1, p2, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE int STREAMVOL_CREATE_LINE(float p0, float p1, float p2, float p3, float p4, float p5, Any p6) { return YimMenu::NativeInvoker::Invoke<5244, int>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void STREAMVOL_DELETE(Any unused) { return YimMenu::NativeInvoker::Invoke<5245, void>(unused); }
	FORCEINLINE bool STREAMVOL_HAS_LOADED(Any unused) { return YimMenu::NativeInvoker::Invoke<5246, bool>(unused); }
	FORCEINLINE bool STREAMVOL_IS_VALID(Any unused) { return YimMenu::NativeInvoker::Invoke<5247, bool>(unused); }
	FORCEINLINE bool IS_STREAMVOL_ACTIVE() { return YimMenu::NativeInvoker::Invoke<5248, bool>(); }
	FORCEINLINE bool NEW_LOAD_SCENE_START(float posX, float posY, float posZ, float offsetX, float offsetY, float offsetZ, float radius, int p7) { return YimMenu::NativeInvoker::Invoke<5249, bool>(posX, posY, posZ, offsetX, offsetY, offsetZ, radius, p7); }
	FORCEINLINE bool NEW_LOAD_SCENE_START_SPHERE(float x, float y, float z, float radius, Any p4) { return YimMenu::NativeInvoker::Invoke<5250, bool>(x, y, z, radius, p4); }
	FORCEINLINE void NEW_LOAD_SCENE_STOP() { return YimMenu::NativeInvoker::Invoke<5251, void>(); }
	FORCEINLINE bool IS_NEW_LOAD_SCENE_ACTIVE() { return YimMenu::NativeInvoker::Invoke<5252, bool>(); }
	FORCEINLINE bool IS_NEW_LOAD_SCENE_LOADED() { return YimMenu::NativeInvoker::Invoke<5253, bool>(); }
	FORCEINLINE bool IS_SAFE_TO_START_PLAYER_SWITCH() { return YimMenu::NativeInvoker::Invoke<5254, bool>(); }
	FORCEINLINE void START_PLAYER_SWITCH(Ped from, Ped to, int flags, int switchType) { return YimMenu::NativeInvoker::Invoke<5255, void>(from, to, flags, switchType); }
	FORCEINLINE void STOP_PLAYER_SWITCH() { return YimMenu::NativeInvoker::Invoke<5256, void>(); }
	FORCEINLINE bool IS_PLAYER_SWITCH_IN_PROGRESS() { return YimMenu::NativeInvoker::Invoke<5257, bool>(); }
	FORCEINLINE int GET_PLAYER_SWITCH_TYPE() { return YimMenu::NativeInvoker::Invoke<5258, int>(); }
	FORCEINLINE int GET_IDEAL_PLAYER_SWITCH_TYPE(float x1, float y1, float z1, float x2, float y2, float z2) { return YimMenu::NativeInvoker::Invoke<5259, int>(x1, y1, z1, x2, y2, z2); }
	FORCEINLINE int GET_PLAYER_SWITCH_STATE() { return YimMenu::NativeInvoker::Invoke<5260, int>(); }
	FORCEINLINE int GET_PLAYER_SHORT_SWITCH_STATE() { return YimMenu::NativeInvoker::Invoke<5261, int>(); }
	FORCEINLINE void SET_PLAYER_SHORT_SWITCH_STYLE(int p0) { return YimMenu::NativeInvoker::Invoke<5262, void>(p0); }
	FORCEINLINE int GET_PLAYER_SWITCH_JUMP_CUT_INDEX() { return YimMenu::NativeInvoker::Invoke<5263, int>(); }
	FORCEINLINE void SET_PLAYER_SWITCH_OUTRO(float cameraCoordX, float cameraCoordY, float cameraCoordZ, float camRotationX, float camRotationY, float camRotationZ, float camFov, float camFarClip, int rotationOrder) { return YimMenu::NativeInvoker::Invoke<5264, void>(cameraCoordX, cameraCoordY, cameraCoordZ, camRotationX, camRotationY, camRotationZ, camFov, camFarClip, rotationOrder); }
	FORCEINLINE void SET_PLAYER_SWITCH_ESTABLISHING_SHOT(const char* name) { return YimMenu::NativeInvoker::Invoke<5265, void>(name); }
	FORCEINLINE void ALLOW_PLAYER_SWITCH_PAN() { return YimMenu::NativeInvoker::Invoke<5266, void>(); }
	FORCEINLINE void ALLOW_PLAYER_SWITCH_OUTRO() { return YimMenu::NativeInvoker::Invoke<5267, void>(); }
	FORCEINLINE void ALLOW_PLAYER_SWITCH_ASCENT() { return YimMenu::NativeInvoker::Invoke<5268, void>(); }
	FORCEINLINE void ALLOW_PLAYER_SWITCH_DESCENT() { return YimMenu::NativeInvoker::Invoke<5269, void>(); }
	FORCEINLINE bool IS_SWITCH_READY_FOR_DESCENT() { return YimMenu::NativeInvoker::Invoke<5270, bool>(); }
	FORCEINLINE void ENABLE_SWITCH_PAUSE_BEFORE_DESCENT() { return YimMenu::NativeInvoker::Invoke<5271, void>(); }
	FORCEINLINE void DISABLE_SWITCH_OUTRO_FX() { return YimMenu::NativeInvoker::Invoke<5272, void>(); }
	FORCEINLINE void SWITCH_TO_MULTI_FIRSTPART(Ped ped, int flags, int switchType) { return YimMenu::NativeInvoker::Invoke<5273, void>(ped, flags, switchType); }
	FORCEINLINE void SWITCH_TO_MULTI_SECONDPART(Ped ped) { return YimMenu::NativeInvoker::Invoke<5274, void>(ped); }
	FORCEINLINE bool IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED() { return YimMenu::NativeInvoker::Invoke<5275, bool>(); }
	FORCEINLINE int GET_PLAYER_SWITCH_INTERP_OUT_DURATION() { return YimMenu::NativeInvoker::Invoke<5276, int>(); }
	FORCEINLINE int GET_PLAYER_SWITCH_INTERP_OUT_CURRENT_TIME() { return YimMenu::NativeInvoker::Invoke<5277, int>(); }
	FORCEINLINE bool IS_SWITCH_SKIPPING_DESCENT() { return YimMenu::NativeInvoker::Invoke<5278, bool>(); }
	FORCEINLINE void SET_SCENE_STREAMING_TRACKS_CAM_POS_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<5279, void>(); }
	FORCEINLINE float GET_LODSCALE() { return YimMenu::NativeInvoker::Invoke<5280, float>(); }
	FORCEINLINE void OVERRIDE_LODSCALE_THIS_FRAME(float scaling) { return YimMenu::NativeInvoker::Invoke<5281, void>(scaling); }
	FORCEINLINE void REMAP_LODSCALE_RANGE_THIS_FRAME(float p0, float p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<5282, void>(p0, p1, p2, p3); }
	FORCEINLINE void SUPPRESS_HD_MAP_STREAMING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<5283, void>(); }
	FORCEINLINE void SET_RENDER_HD_ONLY(bool toggle) { return YimMenu::NativeInvoker::Invoke<5284, void>(toggle); }
	FORCEINLINE void FORCE_ALLOW_TIME_BASED_FADING_THIS_FRAME() { return YimMenu::NativeInvoker::Invoke<5285, void>(); }
	FORCEINLINE void IPL_GROUP_SWAP_START(const char* iplName1, const char* iplName2) { return YimMenu::NativeInvoker::Invoke<5286, void>(iplName1, iplName2); }
	FORCEINLINE void IPL_GROUP_SWAP_CANCEL() { return YimMenu::NativeInvoker::Invoke<5287, void>(); }
	FORCEINLINE bool IPL_GROUP_SWAP_IS_READY() { return YimMenu::NativeInvoker::Invoke<5288, bool>(); }
	FORCEINLINE void IPL_GROUP_SWAP_FINISH() { return YimMenu::NativeInvoker::Invoke<5289, void>(); }
	FORCEINLINE bool IPL_GROUP_SWAP_IS_ACTIVE() { return YimMenu::NativeInvoker::Invoke<5290, bool>(); }
	FORCEINLINE void PREFETCH_SRL(const char* srl) { return YimMenu::NativeInvoker::Invoke<5291, void>(srl); }
	FORCEINLINE bool IS_SRL_LOADED() { return YimMenu::NativeInvoker::Invoke<5292, bool>(); }
	FORCEINLINE void BEGIN_SRL() { return YimMenu::NativeInvoker::Invoke<5293, void>(); }
	FORCEINLINE void END_SRL() { return YimMenu::NativeInvoker::Invoke<5294, void>(); }
	FORCEINLINE void SET_SRL_TIME(float p0) { return YimMenu::NativeInvoker::Invoke<5295, void>(p0); }
	FORCEINLINE void SET_SRL_POST_CUTSCENE_CAMERA(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<5296, void>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void SET_SRL_READAHEAD_TIMES(Any p0, Any p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<5297, void>(p0, p1, p2, p3); }
	FORCEINLINE void SET_SRL_LONG_JUMP_MODE(bool p0) { return YimMenu::NativeInvoker::Invoke<5298, void>(p0); }
	FORCEINLINE void SET_SRL_FORCE_PRESTREAM(Any p0) { return YimMenu::NativeInvoker::Invoke<5299, void>(p0); }
	FORCEINLINE void SET_HD_AREA(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<5300, void>(x, y, z, radius); }
	FORCEINLINE void CLEAR_HD_AREA() { return YimMenu::NativeInvoker::Invoke<5301, void>(); }
	FORCEINLINE void INIT_CREATOR_BUDGET() { return YimMenu::NativeInvoker::Invoke<5302, void>(); }
	FORCEINLINE void SHUTDOWN_CREATOR_BUDGET() { return YimMenu::NativeInvoker::Invoke<5303, void>(); }
	FORCEINLINE bool ADD_MODEL_TO_CREATOR_BUDGET(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<5304, bool>(modelHash); }
	FORCEINLINE void REMOVE_MODEL_FROM_CREATOR_BUDGET(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<5305, void>(modelHash); }
	FORCEINLINE float GET_USED_CREATOR_BUDGET() { return YimMenu::NativeInvoker::Invoke<5306, float>(); }
	FORCEINLINE void SET_ISLAND_ENABLED(const char* name, bool toggle) { return YimMenu::NativeInvoker::Invoke<5307, void>(name, toggle); }
}

namespace TASK
{
	FORCEINLINE void TASK_PAUSE(Ped ped, int ms) { return YimMenu::NativeInvoker::Invoke<5308, void>(ped, ms); }
	FORCEINLINE void TASK_STAND_STILL(Ped ped, int time) { return YimMenu::NativeInvoker::Invoke<5309, void>(ped, time); }
	FORCEINLINE void TASK_JUMP(Ped ped, bool usePlayerLaunchForce, bool doSuperJump, bool useFullSuperJumpForce) { return YimMenu::NativeInvoker::Invoke<5310, void>(ped, usePlayerLaunchForce, doSuperJump, useFullSuperJumpForce); }
	FORCEINLINE void TASK_COWER(Ped ped, int duration) { return YimMenu::NativeInvoker::Invoke<5311, void>(ped, duration); }
	FORCEINLINE void TASK_HANDS_UP(Ped ped, int duration, Ped facingPed, int timeToFacePed, int flags) { return YimMenu::NativeInvoker::Invoke<5312, void>(ped, duration, facingPed, timeToFacePed, flags); }
	FORCEINLINE void UPDATE_TASK_HANDS_UP_DURATION(Ped ped, int duration) { return YimMenu::NativeInvoker::Invoke<5313, void>(ped, duration); }
	FORCEINLINE void TASK_OPEN_VEHICLE_DOOR(Ped ped, Vehicle vehicle, int timeOut, int seat, float speed) { return YimMenu::NativeInvoker::Invoke<5314, void>(ped, vehicle, timeOut, seat, speed); }
	FORCEINLINE void TASK_ENTER_VEHICLE(Ped ped, Vehicle vehicle, int timeout, int seat, float speed, int flag, const char* overrideEntryClipsetName) { return YimMenu::NativeInvoker::Invoke<5315, void>(ped, vehicle, timeout, seat, speed, flag, overrideEntryClipsetName); }
	FORCEINLINE void TASK_LEAVE_VEHICLE(Ped ped, Vehicle vehicle, int flags) { return YimMenu::NativeInvoker::Invoke<5316, void>(ped, vehicle, flags); }
	FORCEINLINE void TASK_GET_OFF_BOAT(Ped ped, Vehicle boat) { return YimMenu::NativeInvoker::Invoke<5317, void>(ped, boat); }
	FORCEINLINE void TASK_SKY_DIVE(Ped ped, bool instant) { return YimMenu::NativeInvoker::Invoke<5318, void>(ped, instant); }
	FORCEINLINE void TASK_PARACHUTE(Ped ped, bool giveParachuteItem, bool instant) { return YimMenu::NativeInvoker::Invoke<5319, void>(ped, giveParachuteItem, instant); }
	FORCEINLINE void TASK_PARACHUTE_TO_TARGET(Ped ped, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5320, void>(ped, x, y, z); }
	FORCEINLINE void SET_PARACHUTE_TASK_TARGET(Ped ped, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5321, void>(ped, x, y, z); }
	FORCEINLINE void SET_PARACHUTE_TASK_THRUST(Ped ped, float thrust) { return YimMenu::NativeInvoker::Invoke<5322, void>(ped, thrust); }
	FORCEINLINE void TASK_RAPPEL_FROM_HELI(Ped ped, float minHeightAboveGround) { return YimMenu::NativeInvoker::Invoke<5323, void>(ped, minHeightAboveGround); }
	FORCEINLINE void TASK_VEHICLE_DRIVE_TO_COORD(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, Any p6, Hash vehicleModel, int drivingMode, float stopRange, float straightLineDistance) { return YimMenu::NativeInvoker::Invoke<5324, void>(ped, vehicle, x, y, z, speed, p6, vehicleModel, drivingMode, stopRange, straightLineDistance); }
	FORCEINLINE void TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int driveMode, float stopRange) { return YimMenu::NativeInvoker::Invoke<5325, void>(ped, vehicle, x, y, z, speed, driveMode, stopRange); }
	FORCEINLINE void TASK_VEHICLE_DRIVE_WANDER(Ped ped, Vehicle vehicle, float speed, int drivingStyle) { return YimMenu::NativeInvoker::Invoke<5326, void>(ped, vehicle, speed, drivingStyle); }
	FORCEINLINE void TASK_FOLLOW_TO_OFFSET_OF_ENTITY(Ped ped, Entity entity, float offsetX, float offsetY, float offsetZ, float movementSpeed, int timeout, float stoppingRange, bool persistFollowing) { return YimMenu::NativeInvoker::Invoke<5327, void>(ped, entity, offsetX, offsetY, offsetZ, movementSpeed, timeout, stoppingRange, persistFollowing); }
	FORCEINLINE void TASK_GO_STRAIGHT_TO_COORD(Ped ped, float x, float y, float z, float speed, int timeout, float targetHeading, float distanceToSlide) { return YimMenu::NativeInvoker::Invoke<5328, void>(ped, x, y, z, speed, timeout, targetHeading, distanceToSlide); }
	FORCEINLINE void TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(Ped ped, Entity entity, float x, float y, float z, float moveBlendRatio, int time) { return YimMenu::NativeInvoker::Invoke<5329, void>(ped, entity, x, y, z, moveBlendRatio, time); }
	FORCEINLINE void TASK_ACHIEVE_HEADING(Ped ped, float heading, int timeout) { return YimMenu::NativeInvoker::Invoke<5330, void>(ped, heading, timeout); }
	FORCEINLINE void TASK_FLUSH_ROUTE() { return YimMenu::NativeInvoker::Invoke<5331, void>(); }
	FORCEINLINE void TASK_EXTEND_ROUTE(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5332, void>(x, y, z); }
	FORCEINLINE void TASK_FOLLOW_POINT_ROUTE(Ped ped, float speed, int mode) { return YimMenu::NativeInvoker::Invoke<5333, void>(ped, speed, mode); }
	FORCEINLINE void TASK_GO_TO_ENTITY(Entity entity, Entity target, int duration, float distance, float moveBlendRatio, float slowDownDistance, int flags) { return YimMenu::NativeInvoker::Invoke<5334, void>(entity, target, duration, distance, moveBlendRatio, slowDownDistance, flags); }
	FORCEINLINE void TASK_SMART_FLEE_COORD(Ped ped, float x, float y, float z, float distance, int time, bool preferPavements, bool quitIfOutOfRange) { return YimMenu::NativeInvoker::Invoke<5335, void>(ped, x, y, z, distance, time, preferPavements, quitIfOutOfRange); }
	FORCEINLINE void TASK_SMART_FLEE_PED(Ped ped, Ped fleeTarget, float safeDistance, int fleeTime, bool preferPavements, bool updateToNearestHatedPed) { return YimMenu::NativeInvoker::Invoke<5336, void>(ped, fleeTarget, safeDistance, fleeTime, preferPavements, updateToNearestHatedPed); }
	FORCEINLINE void TASK_REACT_AND_FLEE_PED(Ped ped, Ped fleeTarget) { return YimMenu::NativeInvoker::Invoke<5337, void>(ped, fleeTarget); }
	FORCEINLINE void TASK_SHOCKING_EVENT_REACT(Ped ped, int eventHandle) { return YimMenu::NativeInvoker::Invoke<5338, void>(ped, eventHandle); }
	FORCEINLINE void TASK_WANDER_IN_AREA(Ped ped, float x, float y, float z, float radius, float minimalLength, float timeBetweenWalks) { return YimMenu::NativeInvoker::Invoke<5339, void>(ped, x, y, z, radius, minimalLength, timeBetweenWalks); }
	FORCEINLINE void TASK_WANDER_STANDARD(Ped ped, float heading, int flags) { return YimMenu::NativeInvoker::Invoke<5340, void>(ped, heading, flags); }
	FORCEINLINE void TASK_WANDER_SPECIFIC(Ped ped, const char* conditionalAnimGroupStr, const char* conditionalAnimStr, float heading) { return YimMenu::NativeInvoker::Invoke<5341, void>(ped, conditionalAnimGroupStr, conditionalAnimStr, heading); }
	FORCEINLINE void TASK_VEHICLE_PARK(Ped ped, Vehicle vehicle, float x, float y, float z, float heading, int mode, float radius, bool keepEngineOn) { return YimMenu::NativeInvoker::Invoke<5342, void>(ped, vehicle, x, y, z, heading, mode, radius, keepEngineOn); }
	FORCEINLINE void TASK_STEALTH_KILL(Ped killer, Ped target, Hash stealthKillActionResultHash, float desiredMoveBlendRatio, int stealthFlags) { return YimMenu::NativeInvoker::Invoke<5343, void>(killer, target, stealthKillActionResultHash, desiredMoveBlendRatio, stealthFlags); }
	FORCEINLINE void TASK_PLANT_BOMB(Ped ped, float x, float y, float z, float heading) { return YimMenu::NativeInvoker::Invoke<5344, void>(ped, x, y, z, heading); }
	FORCEINLINE void TASK_FOLLOW_NAV_MESH_TO_COORD(Ped ped, float x, float y, float z, float moveBlendRatio, int time, float targetRadius, int flags, float targetHeading) { return YimMenu::NativeInvoker::Invoke<5345, void>(ped, x, y, z, moveBlendRatio, time, targetRadius, flags, targetHeading); }
	FORCEINLINE void TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED(Ped ped, float x, float y, float z, float moveBlendRatio, int time, float targetRadius, int flags, float slideToCoordHeading, float maxSlopeNavigable, float clampMaxSearchDistance, float targetHeading) { return YimMenu::NativeInvoker::Invoke<5346, void>(ped, x, y, z, moveBlendRatio, time, targetRadius, flags, slideToCoordHeading, maxSlopeNavigable, clampMaxSearchDistance, targetHeading); }
	FORCEINLINE void SET_PED_PATH_CAN_USE_CLIMBOVERS(Ped ped, bool Toggle) { return YimMenu::NativeInvoker::Invoke<5347, void>(ped, Toggle); }
	FORCEINLINE void SET_PED_PATH_CAN_USE_LADDERS(Ped ped, bool Toggle) { return YimMenu::NativeInvoker::Invoke<5348, void>(ped, Toggle); }
	FORCEINLINE void SET_PED_PATH_CAN_DROP_FROM_HEIGHT(Ped ped, bool Toggle) { return YimMenu::NativeInvoker::Invoke<5349, void>(ped, Toggle); }
	FORCEINLINE void SET_PED_PATH_CLIMB_COST_MODIFIER(Ped ped, float modifier) { return YimMenu::NativeInvoker::Invoke<5350, void>(ped, modifier); }
	FORCEINLINE void SET_PED_PATH_MAY_ENTER_WATER(Ped ped, bool mayEnterWater) { return YimMenu::NativeInvoker::Invoke<5351, void>(ped, mayEnterWater); }
	FORCEINLINE void SET_PED_PATH_PREFER_TO_AVOID_WATER(Ped ped, bool avoidWater) { return YimMenu::NativeInvoker::Invoke<5352, void>(ped, avoidWater); }
	FORCEINLINE void SET_PED_PATH_AVOID_FIRE(Ped ped, bool avoidFire) { return YimMenu::NativeInvoker::Invoke<5353, void>(ped, avoidFire); }
	FORCEINLINE void SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT(float height) { return YimMenu::NativeInvoker::Invoke<5354, void>(height); }
	FORCEINLINE int GET_NAVMESH_ROUTE_DISTANCE_REMAINING(Ped ped, float* distanceRemaining, bool* isPathReady) { return YimMenu::NativeInvoker::Invoke<5355, int>(ped, distanceRemaining, isPathReady); }
	FORCEINLINE int GET_NAVMESH_ROUTE_RESULT(Ped ped) { return YimMenu::NativeInvoker::Invoke<5356, int>(ped); }
	FORCEINLINE bool IS_CONTROLLED_VEHICLE_UNABLE_TO_GET_TO_ROAD(Ped ped) { return YimMenu::NativeInvoker::Invoke<5357, bool>(ped); }
	FORCEINLINE void TASK_GO_TO_COORD_ANY_MEANS(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets) { return YimMenu::NativeInvoker::Invoke<5358, void>(ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets); }
	FORCEINLINE void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets, float extraVehToTargetDistToPreferVehicle, float driveStraightLineDistance, int extraFlags, float warpTimerMS) { return YimMenu::NativeInvoker::Invoke<5359, void>(ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets, extraVehToTargetDistToPreferVehicle, driveStraightLineDistance, extraFlags, warpTimerMS); }
	FORCEINLINE void TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(Ped ped, float x, float y, float z, float moveBlendRatio, Vehicle vehicle, bool useLongRangeVehiclePathing, int drivingFlags, float maxRangeToShootTargets, float extraVehToTargetDistToPreferVehicle, float driveStraightLineDistance, int extraFlags, float cruiseSpeed, float targetArriveDist) { return YimMenu::NativeInvoker::Invoke<5360, void>(ped, x, y, z, moveBlendRatio, vehicle, useLongRangeVehiclePathing, drivingFlags, maxRangeToShootTargets, extraVehToTargetDistToPreferVehicle, driveStraightLineDistance, extraFlags, cruiseSpeed, targetArriveDist); }
	FORCEINLINE void TASK_PLAY_ANIM(Ped ped, const char* animDictionary, const char* animationName, float blendInSpeed, float blendOutSpeed, int duration, int flag, float playbackRate, bool lockX, bool lockY, bool lockZ) { return YimMenu::NativeInvoker::Invoke<5361, void>(ped, animDictionary, animationName, blendInSpeed, blendOutSpeed, duration, flag, playbackRate, lockX, lockY, lockZ); }
	FORCEINLINE void TASK_PLAY_ANIM_ADVANCED(Ped ped, const char* animDict, const char* animName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float animEnterSpeed, float animExitSpeed, int duration, Any flag, float animTime, int rotOrder, int ikFlags) { return YimMenu::NativeInvoker::Invoke<5362, void>(ped, animDict, animName, posX, posY, posZ, rotX, rotY, rotZ, animEnterSpeed, animExitSpeed, duration, flag, animTime, rotOrder, ikFlags); }
	FORCEINLINE void STOP_ANIM_TASK(Entity entity, const char* animDictionary, const char* animationName, float blendDelta) { return YimMenu::NativeInvoker::Invoke<5363, void>(entity, animDictionary, animationName, blendDelta); }
	FORCEINLINE void TASK_SCRIPTED_ANIMATION(Ped ped, int* priorityLowData, int* priorityMidData, int* priorityHighData, float blendInDelta, float blendOutDelta) { return YimMenu::NativeInvoker::Invoke<5364, void>(ped, priorityLowData, priorityMidData, priorityHighData, blendInDelta, blendOutDelta); }
	FORCEINLINE void PLAY_ENTITY_SCRIPTED_ANIM(Entity entity, int* priorityLowData, int* priorityMidData, int* priorityHighData, float blendInDelta, float blendOutDelta) { return YimMenu::NativeInvoker::Invoke<5365, void>(entity, priorityLowData, priorityMidData, priorityHighData, blendInDelta, blendOutDelta); }
	FORCEINLINE void STOP_ANIM_PLAYBACK(Entity entity, int priority, bool secondary) { return YimMenu::NativeInvoker::Invoke<5366, void>(entity, priority, secondary); }
	FORCEINLINE void SET_ANIM_WEIGHT(Entity entity, float weight, int priority, int index, bool secondary) { return YimMenu::NativeInvoker::Invoke<5367, void>(entity, weight, priority, index, secondary); }
	FORCEINLINE void SET_ANIM_PHASE(Entity entity, float phase, int priority, bool secondary) { return YimMenu::NativeInvoker::Invoke<5368, void>(entity, phase, priority, secondary); }
	FORCEINLINE void SET_ANIM_RATE(Entity entity, float rate, int priority, bool secondary) { return YimMenu::NativeInvoker::Invoke<5369, void>(entity, rate, priority, secondary); }
	FORCEINLINE void SET_ANIM_LOOPED(Entity entity, bool looped, int priority, bool secondary) { return YimMenu::NativeInvoker::Invoke<5370, void>(entity, looped, priority, secondary); }
	FORCEINLINE void TASK_PLAY_PHONE_GESTURE_ANIMATION(Ped ped, const char* animDict, const char* animation, const char* boneMaskType, float blendInDuration, float blendOutDuration, bool isLooping, bool holdLastFrame) { return YimMenu::NativeInvoker::Invoke<5371, void>(ped, animDict, animation, boneMaskType, blendInDuration, blendOutDuration, isLooping, holdLastFrame); }
	FORCEINLINE void TASK_STOP_PHONE_GESTURE_ANIMATION(Ped ped, float blendOutOverride) { return YimMenu::NativeInvoker::Invoke<5372, void>(ped, blendOutOverride); }
	FORCEINLINE bool IS_PLAYING_PHONE_GESTURE_ANIM(Ped ped) { return YimMenu::NativeInvoker::Invoke<5373, bool>(ped); }
	FORCEINLINE float GET_PHONE_GESTURE_ANIM_CURRENT_TIME(Ped ped) { return YimMenu::NativeInvoker::Invoke<5374, float>(ped); }
	FORCEINLINE float GET_PHONE_GESTURE_ANIM_TOTAL_TIME(Ped ped) { return YimMenu::NativeInvoker::Invoke<5375, float>(ped); }
	FORCEINLINE void TASK_VEHICLE_PLAY_ANIM(Vehicle vehicle, const char* animationSet, const char* animationName) { return YimMenu::NativeInvoker::Invoke<5376, void>(vehicle, animationSet, animationName); }
	FORCEINLINE void TASK_LOOK_AT_COORD(Entity entity, float x, float y, float z, int duration, int flags, int priority) { return YimMenu::NativeInvoker::Invoke<5377, void>(entity, x, y, z, duration, flags, priority); }
	FORCEINLINE void TASK_LOOK_AT_ENTITY(Ped ped, Entity lookAt, int duration, int flags, int priority) { return YimMenu::NativeInvoker::Invoke<5378, void>(ped, lookAt, duration, flags, priority); }
	FORCEINLINE void TASK_CLEAR_LOOK_AT(Ped ped) { return YimMenu::NativeInvoker::Invoke<5379, void>(ped); }
	FORCEINLINE void OPEN_SEQUENCE_TASK(int* taskSequenceId) { return YimMenu::NativeInvoker::Invoke<5380, void>(taskSequenceId); }
	FORCEINLINE void CLOSE_SEQUENCE_TASK(int taskSequenceId) { return YimMenu::NativeInvoker::Invoke<5381, void>(taskSequenceId); }
	FORCEINLINE void TASK_PERFORM_SEQUENCE(Ped ped, int taskSequenceId) { return YimMenu::NativeInvoker::Invoke<5382, void>(ped, taskSequenceId); }
	FORCEINLINE void TASK_PERFORM_SEQUENCE_LOCALLY(Ped ped, int taskSequenceId) { return YimMenu::NativeInvoker::Invoke<5383, void>(ped, taskSequenceId); }
	FORCEINLINE void CLEAR_SEQUENCE_TASK(int* taskSequenceId) { return YimMenu::NativeInvoker::Invoke<5384, void>(taskSequenceId); }
	FORCEINLINE void SET_SEQUENCE_TO_REPEAT(int taskSequenceId, bool repeat) { return YimMenu::NativeInvoker::Invoke<5385, void>(taskSequenceId, repeat); }
	FORCEINLINE int GET_SEQUENCE_PROGRESS(Ped ped) { return YimMenu::NativeInvoker::Invoke<5386, int>(ped); }
	FORCEINLINE bool GET_IS_TASK_ACTIVE(Ped ped, int taskIndex) { return YimMenu::NativeInvoker::Invoke<5387, bool>(ped, taskIndex); }
	FORCEINLINE int GET_SCRIPT_TASK_STATUS(Ped ped, Hash taskHash) { return YimMenu::NativeInvoker::Invoke<5388, int>(ped, taskHash); }
	FORCEINLINE int GET_ACTIVE_VEHICLE_MISSION_TYPE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5389, int>(vehicle); }
	FORCEINLINE void TASK_LEAVE_ANY_VEHICLE(Ped ped, int delayTime, int flags) { return YimMenu::NativeInvoker::Invoke<5390, void>(ped, delayTime, flags); }
	FORCEINLINE void TASK_AIM_GUN_SCRIPTED(Ped ped, Hash scriptTask, bool disableBlockingClip, bool instantBlendToAim) { return YimMenu::NativeInvoker::Invoke<5391, void>(ped, scriptTask, disableBlockingClip, instantBlendToAim); }
	FORCEINLINE void TASK_AIM_GUN_SCRIPTED_WITH_TARGET(Ped ped, Ped target, float x, float y, float z, int gunTaskType, bool disableBlockingClip, bool forceAim) { return YimMenu::NativeInvoker::Invoke<5392, void>(ped, target, x, y, z, gunTaskType, disableBlockingClip, forceAim); }
	FORCEINLINE void UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET(Ped ped, Ped target, float x, float y, float z, bool disableBlockingClip) { return YimMenu::NativeInvoker::Invoke<5393, void>(ped, target, x, y, z, disableBlockingClip); }
	FORCEINLINE const char* GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK(int gunTaskType) { return YimMenu::NativeInvoker::Invoke<5394, const char*>(gunTaskType); }
	FORCEINLINE void TASK_AIM_GUN_AT_ENTITY(Ped ped, Entity entity, int duration, bool instantBlendToAim) { return YimMenu::NativeInvoker::Invoke<5395, void>(ped, entity, duration, instantBlendToAim); }
	FORCEINLINE void TASK_TURN_PED_TO_FACE_ENTITY(Ped ped, Entity entity, int duration) { return YimMenu::NativeInvoker::Invoke<5396, void>(ped, entity, duration); }
	FORCEINLINE void TASK_AIM_GUN_AT_COORD(Ped ped, float x, float y, float z, int time, bool instantBlendToAim, bool playAnimIntro) { return YimMenu::NativeInvoker::Invoke<5397, void>(ped, x, y, z, time, instantBlendToAim, playAnimIntro); }
	FORCEINLINE void TASK_SHOOT_AT_COORD(Ped ped, float x, float y, float z, int duration, Hash firingPattern) { return YimMenu::NativeInvoker::Invoke<5398, void>(ped, x, y, z, duration, firingPattern); }
	FORCEINLINE void TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(Ped ped, Vehicle vehicle, bool useAlternateShuffle) { return YimMenu::NativeInvoker::Invoke<5399, void>(ped, vehicle, useAlternateShuffle); }
	FORCEINLINE void CLEAR_PED_TASKS(Ped ped) { return YimMenu::NativeInvoker::Invoke<5400, void>(ped); }
	FORCEINLINE void CLEAR_PED_SECONDARY_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<5401, void>(ped); }
	FORCEINLINE void TASK_EVERYONE_LEAVE_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5402, void>(vehicle); }
	FORCEINLINE void TASK_GOTO_ENTITY_OFFSET(Ped ped, Entity entity, int time, float seekRadius, float seekAngleDeg, float moveBlendRatio, int gotoEntityOffsetFlags) { return YimMenu::NativeInvoker::Invoke<5403, void>(ped, entity, time, seekRadius, seekAngleDeg, moveBlendRatio, gotoEntityOffsetFlags); }
	FORCEINLINE void TASK_GOTO_ENTITY_OFFSET_XY(Ped ped, Entity entity, int duration, float targetRadius, float offsetX, float offsetY, float moveBlendRatio, int gotoEntityOffsetFlags) { return YimMenu::NativeInvoker::Invoke<5404, void>(ped, entity, duration, targetRadius, offsetX, offsetY, moveBlendRatio, gotoEntityOffsetFlags); }
	FORCEINLINE void TASK_TURN_PED_TO_FACE_COORD(Ped ped, float x, float y, float z, int duration) { return YimMenu::NativeInvoker::Invoke<5405, void>(ped, x, y, z, duration); }
	FORCEINLINE void TASK_VEHICLE_TEMP_ACTION(Ped driver, Vehicle vehicle, int action, int time) { return YimMenu::NativeInvoker::Invoke<5406, void>(driver, vehicle, action, time); }
	FORCEINLINE void TASK_VEHICLE_MISSION(Ped driver, Vehicle vehicle, Vehicle vehicleTarget, int missionType, float cruiseSpeed, int drivingStyle, float targetReached, float straightLineDistance, bool DriveAgainstTraffic) { return YimMenu::NativeInvoker::Invoke<5407, void>(driver, vehicle, vehicleTarget, missionType, cruiseSpeed, drivingStyle, targetReached, straightLineDistance, DriveAgainstTraffic); }
	FORCEINLINE void TASK_VEHICLE_MISSION_PED_TARGET(Ped ped, Vehicle vehicle, Ped pedTarget, int missionType, float maxSpeed, int drivingStyle, float minDistance, float straightLineDistance, bool DriveAgainstTraffic) { return YimMenu::NativeInvoker::Invoke<5408, void>(ped, vehicle, pedTarget, missionType, maxSpeed, drivingStyle, minDistance, straightLineDistance, DriveAgainstTraffic); }
	FORCEINLINE void TASK_VEHICLE_MISSION_COORS_TARGET(Ped ped, Vehicle vehicle, float x, float y, float z, int mission, float cruiseSpeed, int drivingStyle, float targetReached, float straightLineDistance, bool DriveAgainstTraffic) { return YimMenu::NativeInvoker::Invoke<5409, void>(ped, vehicle, x, y, z, mission, cruiseSpeed, drivingStyle, targetReached, straightLineDistance, DriveAgainstTraffic); }
	FORCEINLINE void TASK_VEHICLE_ESCORT(Ped ped, Vehicle vehicle, Vehicle targetVehicle, int mode, float speed, int drivingStyle, float minDistance, int minHeightAboveTerrain, float noRoadsDistance) { return YimMenu::NativeInvoker::Invoke<5410, void>(ped, vehicle, targetVehicle, mode, speed, drivingStyle, minDistance, minHeightAboveTerrain, noRoadsDistance); }
	FORCEINLINE void TASK_VEHICLE_FOLLOW(Ped driver, Vehicle vehicle, Entity targetEntity, float speed, int drivingStyle, int minDistance) { return YimMenu::NativeInvoker::Invoke<5411, void>(driver, vehicle, targetEntity, speed, drivingStyle, minDistance); }
	FORCEINLINE void TASK_VEHICLE_CHASE(Ped driver, Entity targetEnt) { return YimMenu::NativeInvoker::Invoke<5412, void>(driver, targetEnt); }
	FORCEINLINE void TASK_VEHICLE_HELI_PROTECT(Ped pilot, Vehicle vehicle, Entity entityToFollow, float targetSpeed, int drivingFlags, float radius, int altitude, int heliFlags) { return YimMenu::NativeInvoker::Invoke<5413, void>(pilot, vehicle, entityToFollow, targetSpeed, drivingFlags, radius, altitude, heliFlags); }
	FORCEINLINE void SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(Ped ped, int flag, bool set) { return YimMenu::NativeInvoker::Invoke<5414, void>(ped, flag, set); }
	FORCEINLINE void SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(Ped ped, float distance) { return YimMenu::NativeInvoker::Invoke<5415, void>(ped, distance); }
	FORCEINLINE void TASK_HELI_CHASE(Ped pilot, Entity entityToFollow, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5416, void>(pilot, entityToFollow, x, y, z); }
	FORCEINLINE void TASK_PLANE_CHASE(Ped pilot, Entity entityToFollow, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5417, void>(pilot, entityToFollow, x, y, z); }
	FORCEINLINE void TASK_PLANE_LAND(Ped pilot, Vehicle plane, float runwayStartX, float runwayStartY, float runwayStartZ, float runwayEndX, float runwayEndY, float runwayEndZ) { return YimMenu::NativeInvoker::Invoke<5418, void>(pilot, plane, runwayStartX, runwayStartY, runwayStartZ, runwayEndX, runwayEndY, runwayEndZ); }
	FORCEINLINE void CLEAR_DEFAULT_PRIMARY_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<5419, void>(ped); }
	FORCEINLINE void CLEAR_PRIMARY_VEHICLE_TASK(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5420, void>(vehicle); }
	FORCEINLINE void CLEAR_VEHICLE_CRASH_TASK(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5421, void>(vehicle); }
	FORCEINLINE void TASK_PLANE_GOTO_PRECISE_VTOL(Ped ped, Vehicle vehicle, float x, float y, float z, int flightHeight, int minHeightAboveTerrain, bool useDesiredOrientation, float desiredOrientation, bool autopilot) { return YimMenu::NativeInvoker::Invoke<5422, void>(ped, vehicle, x, y, z, flightHeight, minHeightAboveTerrain, useDesiredOrientation, desiredOrientation, autopilot); }
	FORCEINLINE void TASK_SUBMARINE_GOTO_AND_STOP(Ped ped, Vehicle submarine, float x, float y, float z, bool autopilot) { return YimMenu::NativeInvoker::Invoke<5423, void>(ped, submarine, x, y, z, autopilot); }
	FORCEINLINE void TASK_HELI_MISSION(Ped pilot, Vehicle aircraft, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionFlag, float maxSpeed, float radius, float targetHeading, int maxHeight, int minHeight, float slowDownDistance, int behaviorFlags) { return YimMenu::NativeInvoker::Invoke<5424, void>(pilot, aircraft, targetVehicle, targetPed, destinationX, destinationY, destinationZ, missionFlag, maxSpeed, radius, targetHeading, maxHeight, minHeight, slowDownDistance, behaviorFlags); }
	FORCEINLINE void TASK_HELI_ESCORT_HELI(Ped pilot, Vehicle heli1, Vehicle heli2, float offsetX, float offsetY, float offsetZ) { return YimMenu::NativeInvoker::Invoke<5425, void>(pilot, heli1, heli2, offsetX, offsetY, offsetZ); }
	FORCEINLINE void TASK_PLANE_MISSION(Ped pilot, Vehicle aircraft, Vehicle targetVehicle, Ped targetPed, float destinationX, float destinationY, float destinationZ, int missionFlag, float angularDrag, float targetReached, float targetHeading, float maxZ, float minZ, bool precise) { return YimMenu::NativeInvoker::Invoke<5426, void>(pilot, aircraft, targetVehicle, targetPed, destinationX, destinationY, destinationZ, missionFlag, angularDrag, targetReached, targetHeading, maxZ, minZ, precise); }
	FORCEINLINE void TASK_PLANE_TAXI(Ped pilot, Vehicle aircraft, float x, float y, float z, float cruiseSpeed, float targetReached) { return YimMenu::NativeInvoker::Invoke<5427, void>(pilot, aircraft, x, y, z, cruiseSpeed, targetReached); }
	FORCEINLINE void TASK_BOAT_MISSION(Ped pedDriver, Vehicle vehicle, Vehicle targetVehicle, Ped targetPed, float x, float y, float z, int mission, float maxSpeed, int drivingStyle, float targetReached, Any boatFlags) { return YimMenu::NativeInvoker::Invoke<5428, void>(pedDriver, vehicle, targetVehicle, targetPed, x, y, z, mission, maxSpeed, drivingStyle, targetReached, boatFlags); }
	FORCEINLINE void TASK_DRIVE_BY(Ped driverPed, Ped targetPed, Vehicle targetVehicle, float targetX, float targetY, float targetZ, float distanceToShoot, int pedAccuracy, bool pushUnderneathDrivingTaskIfDriving, Hash firingPattern) { return YimMenu::NativeInvoker::Invoke<5429, void>(driverPed, targetPed, targetVehicle, targetX, targetY, targetZ, distanceToShoot, pedAccuracy, pushUnderneathDrivingTaskIfDriving, firingPattern); }
	FORCEINLINE void SET_DRIVEBY_TASK_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5430, void>(shootingPed, targetPed, targetVehicle, x, y, z); }
	FORCEINLINE void CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<5431, void>(ped); }
	FORCEINLINE bool IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<5432, bool>(ped); }
	FORCEINLINE bool CONTROL_MOUNTED_WEAPON(Ped ped) { return YimMenu::NativeInvoker::Invoke<5433, bool>(ped); }
	FORCEINLINE void SET_MOUNTED_WEAPON_TARGET(Ped shootingPed, Ped targetPed, Vehicle targetVehicle, float x, float y, float z, int taskMode, bool ignoreTargetVehDeadCheck) { return YimMenu::NativeInvoker::Invoke<5434, void>(shootingPed, targetPed, targetVehicle, x, y, z, taskMode, ignoreTargetVehDeadCheck); }
	FORCEINLINE bool IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<5435, bool>(ped); }
	FORCEINLINE void TASK_USE_MOBILE_PHONE(Ped ped, bool usePhone, int desiredPhoneMode) { return YimMenu::NativeInvoker::Invoke<5436, void>(ped, usePhone, desiredPhoneMode); }
	FORCEINLINE void TASK_USE_MOBILE_PHONE_TIMED(Ped ped, int duration) { return YimMenu::NativeInvoker::Invoke<5437, void>(ped, duration); }
	FORCEINLINE void TASK_CHAT_TO_PED(Ped ped, Ped target, int flags, float goToLocationX, float goToLocationY, float goToLocationZ, float headingDegs, float idleTime) { return YimMenu::NativeInvoker::Invoke<5438, void>(ped, target, flags, goToLocationX, goToLocationY, goToLocationZ, headingDegs, idleTime); }
	FORCEINLINE void TASK_WARP_PED_INTO_VEHICLE(Ped ped, Vehicle vehicle, int seat) { return YimMenu::NativeInvoker::Invoke<5439, void>(ped, vehicle, seat); }
	FORCEINLINE void TASK_SHOOT_AT_ENTITY(Entity entity, Entity target, int duration, Hash firingPattern) { return YimMenu::NativeInvoker::Invoke<5440, void>(entity, target, duration, firingPattern); }
	FORCEINLINE void TASK_CLIMB(Ped ped, bool usePlayerLaunchForce) { return YimMenu::NativeInvoker::Invoke<5441, void>(ped, usePlayerLaunchForce); }
	FORCEINLINE void TASK_CLIMB_LADDER(Ped ped, bool fast) { return YimMenu::NativeInvoker::Invoke<5442, void>(ped, fast); }
	FORCEINLINE void TASK_RAPPEL_DOWN_WALL_USING_CLIPSET_OVERRIDE(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, float minZ, int ropeHandle, const char* clipSet, Any p10) { return YimMenu::NativeInvoker::Invoke<5443, void>(ped, x1, y1, z1, x2, y2, z2, minZ, ropeHandle, clipSet, p10); }
	FORCEINLINE int GET_TASK_RAPPEL_DOWN_WALL_STATE(Ped ped) { return YimMenu::NativeInvoker::Invoke<5444, int>(ped); }
	FORCEINLINE void CLEAR_PED_TASKS_IMMEDIATELY(Ped ped) { return YimMenu::NativeInvoker::Invoke<5445, void>(ped); }
	FORCEINLINE void TASK_PERFORM_SEQUENCE_FROM_PROGRESS(Ped ped, int taskIndex, int progress1, int progress2) { return YimMenu::NativeInvoker::Invoke<5446, void>(ped, taskIndex, progress1, progress2); }
	FORCEINLINE void SET_NEXT_DESIRED_MOVE_STATE(float nextMoveState) { return YimMenu::NativeInvoker::Invoke<5447, void>(nextMoveState); }
	FORCEINLINE void SET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped, float newMoveBlendRatio) { return YimMenu::NativeInvoker::Invoke<5448, void>(ped, newMoveBlendRatio); }
	FORCEINLINE float GET_PED_DESIRED_MOVE_BLEND_RATIO(Ped ped) { return YimMenu::NativeInvoker::Invoke<5449, float>(ped); }
	FORCEINLINE void TASK_GOTO_ENTITY_AIMING(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist) { return YimMenu::NativeInvoker::Invoke<5450, void>(ped, target, distanceToStopAt, StartAimingDist); }
	FORCEINLINE void TASK_SET_DECISION_MAKER(Ped ped, Hash decisionMakerId) { return YimMenu::NativeInvoker::Invoke<5451, void>(ped, decisionMakerId); }
	FORCEINLINE void TASK_SET_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<5452, void>(ped, x, y, z, radius); }
	FORCEINLINE void TASK_CLEAR_DEFENSIVE_AREA(Ped ped) { return YimMenu::NativeInvoker::Invoke<5453, void>(ped); }
	FORCEINLINE void TASK_PED_SLIDE_TO_COORD(Ped ped, float x, float y, float z, float heading, float speed) { return YimMenu::NativeInvoker::Invoke<5454, void>(ped, x, y, z, heading, speed); }
	FORCEINLINE void TASK_PED_SLIDE_TO_COORD_HDG_RATE(Ped ped, float x, float y, float z, float heading, float speed, float headingChangeRate) { return YimMenu::NativeInvoker::Invoke<5455, void>(ped, x, y, z, heading, speed, headingChangeRate); }
	FORCEINLINE ScrHandle ADD_COVER_POINT(float x, float y, float z, float direction, int usage, int height, int arc, bool isPriority) { return YimMenu::NativeInvoker::Invoke<5456, ScrHandle>(x, y, z, direction, usage, height, arc, isPriority); }
	FORCEINLINE void REMOVE_COVER_POINT(ScrHandle coverpoint) { return YimMenu::NativeInvoker::Invoke<5457, void>(coverpoint); }
	FORCEINLINE bool DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5458, bool>(x, y, z); }
	FORCEINLINE Vector3 GET_SCRIPTED_COVER_POINT_COORDS(ScrHandle coverpoint) { return YimMenu::NativeInvoker::Invoke<5459, Vector3>(coverpoint); }
	FORCEINLINE void ADD_SCRIPTED_COVER_AREA(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<5460, void>(x, y, z, radius); }
	FORCEINLINE void TASK_COMBAT_PED(Ped ped, Ped targetPed, int combatFlags, int threatResponseFlags) { return YimMenu::NativeInvoker::Invoke<5461, void>(ped, targetPed, combatFlags, threatResponseFlags); }
	FORCEINLINE void TASK_COMBAT_PED_TIMED(Ped ped, Ped target, int time, int flags) { return YimMenu::NativeInvoker::Invoke<5462, void>(ped, target, time, flags); }
	FORCEINLINE void TASK_SEEK_COVER_FROM_POS(Ped ped, float x, float y, float z, int duration, bool allowPeekingAndFiring) { return YimMenu::NativeInvoker::Invoke<5463, void>(ped, x, y, z, duration, allowPeekingAndFiring); }
	FORCEINLINE void TASK_SEEK_COVER_FROM_PED(Ped ped, Ped target, int duration, bool allowPeekingAndFiring) { return YimMenu::NativeInvoker::Invoke<5464, void>(ped, target, duration, allowPeekingAndFiring); }
	FORCEINLINE void TASK_SEEK_COVER_TO_COVER_POINT(Ped ped, ScrHandle coverpoint, float x, float y, float z, int time, bool allowPeekingAndFiring) { return YimMenu::NativeInvoker::Invoke<5465, void>(ped, coverpoint, x, y, z, time, allowPeekingAndFiring); }
	FORCEINLINE void TASK_SEEK_COVER_TO_COORDS(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, int timeout, bool shortRoute) { return YimMenu::NativeInvoker::Invoke<5466, void>(ped, x1, y1, z1, x2, y2, z2, timeout, shortRoute); }
	FORCEINLINE void TASK_PUT_PED_DIRECTLY_INTO_COVER(Ped ped, float x, float y, float z, int time, bool allowPeekingAndFiring, float blendInDuration, bool forceInitialFacingDirection, bool forceFaceLeft, int identifier, bool doEntry) { return YimMenu::NativeInvoker::Invoke<5467, void>(ped, x, y, z, time, allowPeekingAndFiring, blendInDuration, forceInitialFacingDirection, forceFaceLeft, identifier, doEntry); }
	FORCEINLINE void TASK_WARP_PED_DIRECTLY_INTO_COVER(Ped ped, int time, bool allowPeekingAndFiring, bool forceInitialFacingDirection, bool forceFaceLeft, int identifier) { return YimMenu::NativeInvoker::Invoke<5468, void>(ped, time, allowPeekingAndFiring, forceInitialFacingDirection, forceFaceLeft, identifier); }
	FORCEINLINE void TASK_EXIT_COVER(Ped ped, int exitType, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5469, void>(ped, exitType, x, y, z); }
	FORCEINLINE void TASK_PUT_PED_DIRECTLY_INTO_MELEE(Ped ped, Ped meleeTarget, float blendInDuration, float timeInMelee, float strafePhaseSync, int aiCombatFlags) { return YimMenu::NativeInvoker::Invoke<5470, void>(ped, meleeTarget, blendInDuration, timeInMelee, strafePhaseSync, aiCombatFlags); }
	FORCEINLINE void TASK_TOGGLE_DUCK(Ped ped, int toggleType) { return YimMenu::NativeInvoker::Invoke<5471, void>(ped, toggleType); }
	FORCEINLINE void TASK_GUARD_CURRENT_POSITION(Ped ped, float maxPatrolProximity, float defensiveAreaRadius, bool setDefensiveArea) { return YimMenu::NativeInvoker::Invoke<5472, void>(ped, maxPatrolProximity, defensiveAreaRadius, setDefensiveArea); }
	FORCEINLINE void TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float heading, float maxPatrolProximity, int timer) { return YimMenu::NativeInvoker::Invoke<5473, void>(ped, x, y, z, heading, maxPatrolProximity, timer); }
	FORCEINLINE void TASK_GUARD_SPHERE_DEFENSIVE_AREA(Ped ped, float defendPositionX, float defendPositionY, float defendPositionZ, float heading, float maxPatrolProximity, int time, float x, float y, float z, float defensiveAreaRadius) { return YimMenu::NativeInvoker::Invoke<5474, void>(ped, defendPositionX, defendPositionY, defendPositionZ, heading, maxPatrolProximity, time, x, y, z, defensiveAreaRadius); }
	FORCEINLINE void TASK_STAND_GUARD(Ped ped, float x, float y, float z, float heading, const char* scenarioName) { return YimMenu::NativeInvoker::Invoke<5475, void>(ped, x, y, z, heading, scenarioName); }
	FORCEINLINE void SET_DRIVE_TASK_CRUISE_SPEED(Ped driver, float cruiseSpeed) { return YimMenu::NativeInvoker::Invoke<5476, void>(driver, cruiseSpeed); }
	FORCEINLINE void SET_DRIVE_TASK_MAX_CRUISE_SPEED(Ped ped, float speed) { return YimMenu::NativeInvoker::Invoke<5477, void>(ped, speed); }
	FORCEINLINE void SET_DRIVE_TASK_DRIVING_STYLE(Ped ped, int drivingStyle) { return YimMenu::NativeInvoker::Invoke<5478, void>(ped, drivingStyle); }
	FORCEINLINE void ADD_COVER_BLOCKING_AREA(float startX, float startY, float startZ, float endX, float endY, float endZ, bool blockObjects, bool blockVehicles, bool blockMap, bool blockPlayer) { return YimMenu::NativeInvoker::Invoke<5479, void>(startX, startY, startZ, endX, endY, endZ, blockObjects, blockVehicles, blockMap, blockPlayer); }
	FORCEINLINE void REMOVE_ALL_COVER_BLOCKING_AREAS() { return YimMenu::NativeInvoker::Invoke<5480, void>(); }
	FORCEINLINE void REMOVE_COVER_BLOCKING_AREAS_AT_POSITION(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5481, void>(x, y, z); }
	FORCEINLINE void REMOVE_SPECIFIC_COVER_BLOCKING_AREAS(float startX, float startY, float startZ, float endX, float endY, float endZ, bool blockObjects, bool blockVehicles, bool blockMap, bool blockPlayer) { return YimMenu::NativeInvoker::Invoke<5482, void>(startX, startY, startZ, endX, endY, endZ, blockObjects, blockVehicles, blockMap, blockPlayer); }
	FORCEINLINE void TASK_START_SCENARIO_IN_PLACE(Ped ped, const char* scenarioName, int unkDelay, bool playEnterAnim) { return YimMenu::NativeInvoker::Invoke<5483, void>(ped, scenarioName, unkDelay, playEnterAnim); }
	FORCEINLINE void TASK_START_SCENARIO_AT_POSITION(Ped ped, const char* scenarioName, float x, float y, float z, float heading, int duration, bool sittingScenario, bool teleport) { return YimMenu::NativeInvoker::Invoke<5484, void>(ped, scenarioName, x, y, z, heading, duration, sittingScenario, teleport); }
	FORCEINLINE void TASK_USE_NEAREST_SCENARIO_TO_COORD(Ped ped, float x, float y, float z, float distance, int duration) { return YimMenu::NativeInvoker::Invoke<5485, void>(ped, x, y, z, distance, duration); }
	FORCEINLINE void TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(Ped ped, float x, float y, float z, float radius, int timeToLeave) { return YimMenu::NativeInvoker::Invoke<5486, void>(ped, x, y, z, radius, timeToLeave); }
	FORCEINLINE void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(Ped ped, float x, float y, float z, float maxRange, int timeToLeave) { return YimMenu::NativeInvoker::Invoke<5487, void>(ped, x, y, z, maxRange, timeToLeave); }
	FORCEINLINE void TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(Ped ped, float x, float y, float z, float radius, int timeToLeave) { return YimMenu::NativeInvoker::Invoke<5488, void>(ped, x, y, z, radius, timeToLeave); }
	FORCEINLINE bool DOES_SCENARIO_EXIST_IN_AREA(float x, float y, float z, float radius, bool mustBeFree) { return YimMenu::NativeInvoker::Invoke<5489, bool>(x, y, z, radius, mustBeFree); }
	FORCEINLINE bool DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA(float x, float y, float z, const char* scenarioName, float radius, bool mustBeFree) { return YimMenu::NativeInvoker::Invoke<5490, bool>(x, y, z, scenarioName, radius, mustBeFree); }
	FORCEINLINE bool IS_SCENARIO_OCCUPIED(float x, float y, float z, float maxRange, bool onlyUsersActuallyAtScenario) { return YimMenu::NativeInvoker::Invoke<5491, bool>(x, y, z, maxRange, onlyUsersActuallyAtScenario); }
	FORCEINLINE bool PED_HAS_USE_SCENARIO_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<5492, bool>(ped); }
	FORCEINLINE void PLAY_ANIM_ON_RUNNING_SCENARIO(Ped ped, const char* animDict, const char* animName) { return YimMenu::NativeInvoker::Invoke<5493, void>(ped, animDict, animName); }
	FORCEINLINE bool DOES_SCENARIO_GROUP_EXIST(const char* scenarioGroup) { return YimMenu::NativeInvoker::Invoke<5494, bool>(scenarioGroup); }
	FORCEINLINE bool IS_SCENARIO_GROUP_ENABLED(const char* scenarioGroup) { return YimMenu::NativeInvoker::Invoke<5495, bool>(scenarioGroup); }
	FORCEINLINE void SET_SCENARIO_GROUP_ENABLED(const char* scenarioGroup, bool enabled) { return YimMenu::NativeInvoker::Invoke<5496, void>(scenarioGroup, enabled); }
	FORCEINLINE void RESET_SCENARIO_GROUPS_ENABLED() { return YimMenu::NativeInvoker::Invoke<5497, void>(); }
	FORCEINLINE void SET_EXCLUSIVE_SCENARIO_GROUP(const char* scenarioGroup) { return YimMenu::NativeInvoker::Invoke<5498, void>(scenarioGroup); }
	FORCEINLINE void RESET_EXCLUSIVE_SCENARIO_GROUP() { return YimMenu::NativeInvoker::Invoke<5499, void>(); }
	FORCEINLINE bool IS_SCENARIO_TYPE_ENABLED(const char* scenarioType) { return YimMenu::NativeInvoker::Invoke<5500, bool>(scenarioType); }
	FORCEINLINE void SET_SCENARIO_TYPE_ENABLED(const char* scenarioType, bool toggle) { return YimMenu::NativeInvoker::Invoke<5501, void>(scenarioType, toggle); }
	FORCEINLINE void RESET_SCENARIO_TYPES_ENABLED() { return YimMenu::NativeInvoker::Invoke<5502, void>(); }
	FORCEINLINE bool IS_PED_ACTIVE_IN_SCENARIO(Ped ped) { return YimMenu::NativeInvoker::Invoke<5503, bool>(ped); }
	FORCEINLINE bool IS_PED_PLAYING_BASE_CLIP_IN_SCENARIO(Ped ped) { return YimMenu::NativeInvoker::Invoke<5504, bool>(ped); }
	FORCEINLINE void SET_PED_CAN_PLAY_AMBIENT_IDLES(Ped ped, bool blockIdleClips, bool removeIdleClipIfPlaying) { return YimMenu::NativeInvoker::Invoke<5505, void>(ped, blockIdleClips, removeIdleClipIfPlaying); }
	FORCEINLINE void TASK_COMBAT_HATED_TARGETS_IN_AREA(Ped ped, float x, float y, float z, float radius, int combatFlags) { return YimMenu::NativeInvoker::Invoke<5506, void>(ped, x, y, z, radius, combatFlags); }
	FORCEINLINE void TASK_COMBAT_HATED_TARGETS_AROUND_PED(Ped ped, float radius, int combatFlags) { return YimMenu::NativeInvoker::Invoke<5507, void>(ped, radius, combatFlags); }
	FORCEINLINE void TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(Ped ped, float radius, int time, int combatFlags) { return YimMenu::NativeInvoker::Invoke<5508, void>(ped, radius, time, combatFlags); }
	FORCEINLINE void TASK_THROW_PROJECTILE(Ped ped, float x, float y, float z, int ignoreCollisionEntityIndex, bool createInvincibleProjectile) { return YimMenu::NativeInvoker::Invoke<5509, void>(ped, x, y, z, ignoreCollisionEntityIndex, createInvincibleProjectile); }
	FORCEINLINE void TASK_SWAP_WEAPON(Ped ped, bool drawWeapon) { return YimMenu::NativeInvoker::Invoke<5510, void>(ped, drawWeapon); }
	FORCEINLINE void TASK_RELOAD_WEAPON(Ped ped, bool drawWeapon) { return YimMenu::NativeInvoker::Invoke<5511, void>(ped, drawWeapon); }
	FORCEINLINE bool IS_PED_GETTING_UP(Ped ped) { return YimMenu::NativeInvoker::Invoke<5512, bool>(ped); }
	FORCEINLINE void TASK_WRITHE(Ped ped, Ped target, int minFireLoops, int startState, bool forceShootOnGround, int shootFromGroundTimer) { return YimMenu::NativeInvoker::Invoke<5513, void>(ped, target, minFireLoops, startState, forceShootOnGround, shootFromGroundTimer); }
	FORCEINLINE bool IS_PED_IN_WRITHE(Ped ped) { return YimMenu::NativeInvoker::Invoke<5514, bool>(ped); }
	FORCEINLINE void OPEN_PATROL_ROUTE(const char* patrolRoute) { return YimMenu::NativeInvoker::Invoke<5515, void>(patrolRoute); }
	FORCEINLINE void CLOSE_PATROL_ROUTE() { return YimMenu::NativeInvoker::Invoke<5516, void>(); }
	FORCEINLINE void ADD_PATROL_ROUTE_NODE(int nodeId, const char* nodeType, float posX, float posY, float posZ, float headingX, float headingY, float headingZ, int duration) { return YimMenu::NativeInvoker::Invoke<5517, void>(nodeId, nodeType, posX, posY, posZ, headingX, headingY, headingZ, duration); }
	FORCEINLINE void ADD_PATROL_ROUTE_LINK(int nodeId1, int nodeId2) { return YimMenu::NativeInvoker::Invoke<5518, void>(nodeId1, nodeId2); }
	FORCEINLINE void CREATE_PATROL_ROUTE() { return YimMenu::NativeInvoker::Invoke<5519, void>(); }
	FORCEINLINE void DELETE_PATROL_ROUTE(const char* patrolRoute) { return YimMenu::NativeInvoker::Invoke<5520, void>(patrolRoute); }
	FORCEINLINE bool GET_PATROL_TASK_INFO(Ped ped, int* timeLeftAtNode, int* nodeId) { return YimMenu::NativeInvoker::Invoke<5521, bool>(ped, timeLeftAtNode, nodeId); }
	FORCEINLINE void TASK_PATROL(Ped ped, const char* patrolRouteName, int alertState, bool canChatToPeds, bool useHeadLookAt) { return YimMenu::NativeInvoker::Invoke<5522, void>(ped, patrolRouteName, alertState, canChatToPeds, useHeadLookAt); }
	FORCEINLINE void TASK_STAY_IN_COVER(Ped ped) { return YimMenu::NativeInvoker::Invoke<5523, void>(ped); }
	FORCEINLINE void ADD_VEHICLE_SUBTASK_ATTACK_COORD(Ped ped, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5524, void>(ped, x, y, z); }
	FORCEINLINE void ADD_VEHICLE_SUBTASK_ATTACK_PED(Ped ped, Ped target) { return YimMenu::NativeInvoker::Invoke<5525, void>(ped, target); }
	FORCEINLINE void TASK_VEHICLE_SHOOT_AT_PED(Ped ped, Ped target, float fireTolerance) { return YimMenu::NativeInvoker::Invoke<5526, void>(ped, target, fireTolerance); }
	FORCEINLINE void TASK_VEHICLE_AIM_AT_PED(Ped ped, Ped target) { return YimMenu::NativeInvoker::Invoke<5527, void>(ped, target); }
	FORCEINLINE void TASK_VEHICLE_SHOOT_AT_COORD(Ped ped, float x, float y, float z, float fireTolerance) { return YimMenu::NativeInvoker::Invoke<5528, void>(ped, x, y, z, fireTolerance); }
	FORCEINLINE void TASK_VEHICLE_AIM_AT_COORD(Ped ped, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5529, void>(ped, x, y, z); }
	FORCEINLINE void TASK_VEHICLE_GOTO_NAVMESH(Ped ped, Vehicle vehicle, float x, float y, float z, float speed, int behaviorFlag, float stoppingRange) { return YimMenu::NativeInvoker::Invoke<5530, void>(ped, vehicle, x, y, z, speed, behaviorFlag, stoppingRange); }
	FORCEINLINE void TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(Ped ped, float x, float y, float z, float aimAtX, float aimAtY, float aimAtZ, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, int navFlags, bool instantBlendToAim, Hash firingPattern) { return YimMenu::NativeInvoker::Invoke<5531, void>(ped, x, y, z, aimAtX, aimAtY, aimAtZ, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, navFlags, instantBlendToAim, firingPattern); }
	FORCEINLINE void TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(Ped ped, float x, float y, float z, Entity aimAtID, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, int navFlags, bool instantBlendToAim, Hash firingPattern, int time) { return YimMenu::NativeInvoker::Invoke<5532, void>(ped, x, y, z, aimAtID, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, navFlags, instantBlendToAim, firingPattern, time); }
	FORCEINLINE void TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(Ped pedHandle, float goToLocationX, float goToLocationY, float goToLocationZ, float focusLocationX, float focusLocationY, float focusLocationZ, float speed, bool shootAtEnemies, float distanceToStopAt, float noRoadsDistance, bool useNavMesh, int navFlags, int taskFlags, Hash firingPattern) { return YimMenu::NativeInvoker::Invoke<5533, void>(pedHandle, goToLocationX, goToLocationY, goToLocationZ, focusLocationX, focusLocationY, focusLocationZ, speed, shootAtEnemies, distanceToStopAt, noRoadsDistance, useNavMesh, navFlags, taskFlags, firingPattern); }
	FORCEINLINE void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(Ped ped, Entity entity, float aimX, float aimY, float aimZ, float moveBlendRatio, bool shoot, float targetRadius, float slowDistance, bool useNavMesh, bool instantBlendToAim, Hash firingPattern) { return YimMenu::NativeInvoker::Invoke<5534, void>(ped, entity, aimX, aimY, aimZ, moveBlendRatio, shoot, targetRadius, slowDistance, useNavMesh, instantBlendToAim, firingPattern); }
	FORCEINLINE void TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(Ped ped, Entity entityToWalkTo, Entity entityToAimAt, float speed, bool shootatEntity, float targetRadius, float slowDistance, bool useNavMesh, bool instantBlendToAim, Hash firingPattern) { return YimMenu::NativeInvoker::Invoke<5535, void>(ped, entityToWalkTo, entityToAimAt, speed, shootatEntity, targetRadius, slowDistance, useNavMesh, instantBlendToAim, firingPattern); }
	FORCEINLINE void SET_HIGH_FALL_TASK(Ped ped, int minTime, int maxTime, int entryType) { return YimMenu::NativeInvoker::Invoke<5536, void>(ped, minTime, maxTime, entryType); }
	FORCEINLINE void REQUEST_WAYPOINT_RECORDING(const char* name) { return YimMenu::NativeInvoker::Invoke<5537, void>(name); }
	FORCEINLINE bool GET_IS_WAYPOINT_RECORDING_LOADED(const char* name) { return YimMenu::NativeInvoker::Invoke<5538, bool>(name); }
	FORCEINLINE void REMOVE_WAYPOINT_RECORDING(const char* name) { return YimMenu::NativeInvoker::Invoke<5539, void>(name); }
	FORCEINLINE bool WAYPOINT_RECORDING_GET_NUM_POINTS(const char* name, int* points) { return YimMenu::NativeInvoker::Invoke<5540, bool>(name, points); }
	FORCEINLINE bool WAYPOINT_RECORDING_GET_COORD(const char* name, int point, Vector3* coord) { return YimMenu::NativeInvoker::Invoke<5541, bool>(name, point, coord); }
	FORCEINLINE float WAYPOINT_RECORDING_GET_SPEED_AT_POINT(const char* name, int point) { return YimMenu::NativeInvoker::Invoke<5542, float>(name, point); }
	FORCEINLINE bool WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT(const char* name, float x, float y, float z, int* point) { return YimMenu::NativeInvoker::Invoke<5543, bool>(name, x, y, z, point); }
	FORCEINLINE void TASK_FOLLOW_WAYPOINT_RECORDING(Ped ped, const char* name, int p2, int p3, int p4) { return YimMenu::NativeInvoker::Invoke<5544, void>(ped, name, p2, p3, p4); }
	FORCEINLINE bool IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<5545, bool>(ped); }
	FORCEINLINE int GET_PED_WAYPOINT_PROGRESS(Ped ped) { return YimMenu::NativeInvoker::Invoke<5546, int>(ped); }
	FORCEINLINE float GET_PED_WAYPOINT_DISTANCE(Any p0) { return YimMenu::NativeInvoker::Invoke<5547, float>(p0); }
	FORCEINLINE bool SET_PED_WAYPOINT_ROUTE_OFFSET(Ped ped, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5548, bool>(ped, x, y, z); }
	FORCEINLINE float GET_WAYPOINT_DISTANCE_ALONG_ROUTE(const char* name, int point) { return YimMenu::NativeInvoker::Invoke<5549, float>(name, point); }
	FORCEINLINE bool WAYPOINT_PLAYBACK_GET_IS_PAUSED(Any p0) { return YimMenu::NativeInvoker::Invoke<5550, bool>(p0); }
	FORCEINLINE void WAYPOINT_PLAYBACK_PAUSE(Any p0, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<5551, void>(p0, p1, p2); }
	FORCEINLINE void WAYPOINT_PLAYBACK_RESUME(Any p0, bool p1, Any p2, Any p3) { return YimMenu::NativeInvoker::Invoke<5552, void>(p0, p1, p2, p3); }
	FORCEINLINE void WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Any p0, float p1, bool p2) { return YimMenu::NativeInvoker::Invoke<5553, void>(p0, p1, p2); }
	FORCEINLINE void WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Any p0) { return YimMenu::NativeInvoker::Invoke<5554, void>(p0); }
	FORCEINLINE void USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE(const char* name, bool p1, float p2, float p3) { return YimMenu::NativeInvoker::Invoke<5555, void>(name, p1, p2, p3); }
	FORCEINLINE void WAYPOINT_PLAYBACK_START_AIMING_AT_PED(Ped ped, Ped target, bool p2) { return YimMenu::NativeInvoker::Invoke<5556, void>(ped, target, p2); }
	FORCEINLINE void WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(Ped ped, float x, float y, float z, bool p4) { return YimMenu::NativeInvoker::Invoke<5557, void>(ped, x, y, z, p4); }
	FORCEINLINE void WAYPOINT_PLAYBACK_START_SHOOTING_AT_PED(Ped ped, Ped ped2, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<5558, void>(ped, ped2, p2, p3); }
	FORCEINLINE void WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(Ped ped, float x, float y, float z, bool p4, Hash firingPattern) { return YimMenu::NativeInvoker::Invoke<5559, void>(ped, x, y, z, p4, firingPattern); }
	FORCEINLINE void WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(Ped ped) { return YimMenu::NativeInvoker::Invoke<5560, void>(ped); }
	FORCEINLINE void ASSISTED_MOVEMENT_REQUEST_ROUTE(const char* route) { return YimMenu::NativeInvoker::Invoke<5561, void>(route); }
	FORCEINLINE void ASSISTED_MOVEMENT_REMOVE_ROUTE(const char* route) { return YimMenu::NativeInvoker::Invoke<5562, void>(route); }
	FORCEINLINE bool ASSISTED_MOVEMENT_IS_ROUTE_LOADED(const char* route) { return YimMenu::NativeInvoker::Invoke<5563, bool>(route); }
	FORCEINLINE void ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES(const char* route, int props) { return YimMenu::NativeInvoker::Invoke<5564, void>(route, props); }
	FORCEINLINE void ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME(float dist) { return YimMenu::NativeInvoker::Invoke<5565, void>(dist); }
	FORCEINLINE void TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(Ped ped, Vehicle vehicle, const char* WPRecording, int p3, int p4, int p5, int p6, float p7, bool p8, float p9) { return YimMenu::NativeInvoker::Invoke<5566, void>(ped, vehicle, WPRecording, p3, p4, p5, p6, p7, p8, p9); }
	FORCEINLINE bool IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5567, bool>(vehicle); }
	FORCEINLINE int GET_VEHICLE_WAYPOINT_PROGRESS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5568, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_WAYPOINT_TARGET_POINT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5569, int>(vehicle); }
	FORCEINLINE void VEHICLE_WAYPOINT_PLAYBACK_PAUSE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5570, void>(vehicle); }
	FORCEINLINE void VEHICLE_WAYPOINT_PLAYBACK_RESUME(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5571, void>(vehicle); }
	FORCEINLINE void VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5572, void>(vehicle); }
	FORCEINLINE void VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(Vehicle vehicle, float speed) { return YimMenu::NativeInvoker::Invoke<5573, void>(vehicle, speed); }
	FORCEINLINE void TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<5574, void>(ped, toggle); }
	FORCEINLINE void TASK_FORCE_MOTION_STATE(Ped ped, Hash state, bool forceRestart) { return YimMenu::NativeInvoker::Invoke<5575, void>(ped, state, forceRestart); }
	FORCEINLINE void TASK_MOVE_NETWORK_BY_NAME(Ped ped, const char* task, float multiplier, bool allowOverrideCloneUpdate, const char* animDict, int flags) { return YimMenu::NativeInvoker::Invoke<5576, void>(ped, task, multiplier, allowOverrideCloneUpdate, animDict, flags); }
	FORCEINLINE void TASK_MOVE_NETWORK_ADVANCED_BY_NAME(Ped ped, const char* network, float x, float y, float z, float rotX, float rotY, float rotZ, int rotOrder, float blendDuration, bool allowOverrideCloneUpdate, const char* animDict, int flags) { return YimMenu::NativeInvoker::Invoke<5577, void>(ped, network, x, y, z, rotX, rotY, rotZ, rotOrder, blendDuration, allowOverrideCloneUpdate, animDict, flags); }
	FORCEINLINE void TASK_MOVE_NETWORK_BY_NAME_WITH_INIT_PARAMS(Ped ped, const char* network, int* initialParameters, float blendDuration, bool allowOverrideCloneUpdate, const char* animDict, int flags) { return YimMenu::NativeInvoker::Invoke<5578, void>(ped, network, initialParameters, blendDuration, allowOverrideCloneUpdate, animDict, flags); }
	FORCEINLINE void TASK_MOVE_NETWORK_ADVANCED_BY_NAME_WITH_INIT_PARAMS(Ped ped, const char* network, int* initialParameters, float x, float y, float z, float rotX, float rotY, float rotZ, int rotOrder, float blendDuration, bool allowOverrideCloneUpdate, const char* dictionary, int flags) { return YimMenu::NativeInvoker::Invoke<5579, void>(ped, network, initialParameters, x, y, z, rotX, rotY, rotZ, rotOrder, blendDuration, allowOverrideCloneUpdate, dictionary, flags); }
	FORCEINLINE bool IS_TASK_MOVE_NETWORK_ACTIVE(Ped ped) { return YimMenu::NativeInvoker::Invoke<5580, bool>(ped); }
	FORCEINLINE bool IS_TASK_MOVE_NETWORK_READY_FOR_TRANSITION(Ped ped) { return YimMenu::NativeInvoker::Invoke<5581, bool>(ped); }
	FORCEINLINE bool REQUEST_TASK_MOVE_NETWORK_STATE_TRANSITION(Ped ped, const char* name) { return YimMenu::NativeInvoker::Invoke<5582, bool>(ped, name); }
	FORCEINLINE bool SET_EXPECTED_CLONE_NEXT_TASK_MOVE_NETWORK_STATE(Ped ped, const char* state) { return YimMenu::NativeInvoker::Invoke<5583, bool>(ped, state); }
	FORCEINLINE const char* GET_TASK_MOVE_NETWORK_STATE(Ped ped) { return YimMenu::NativeInvoker::Invoke<5584, const char*>(ped); }
	FORCEINLINE void SET_TASK_MOVE_NETWORK_ANIM_SET(Ped ped, Hash clipSet, Hash variableClipSet) { return YimMenu::NativeInvoker::Invoke<5585, void>(ped, clipSet, variableClipSet); }
	FORCEINLINE void SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* signalName, float value) { return YimMenu::NativeInvoker::Invoke<5586, void>(ped, signalName, value); }
	FORCEINLINE void SET_TASK_MOVE_NETWORK_SIGNAL_LOCAL_FLOAT(Ped ped, const char* signalName, float value) { return YimMenu::NativeInvoker::Invoke<5587, void>(ped, signalName, value); }
	FORCEINLINE void SET_TASK_MOVE_NETWORK_SIGNAL_FLOAT_LERP_RATE(Ped ped, const char* signalName, float value) { return YimMenu::NativeInvoker::Invoke<5588, void>(ped, signalName, value); }
	FORCEINLINE void SET_TASK_MOVE_NETWORK_SIGNAL_BOOL(Ped ped, const char* signalName, bool value) { return YimMenu::NativeInvoker::Invoke<5589, void>(ped, signalName, value); }
	FORCEINLINE float GET_TASK_MOVE_NETWORK_SIGNAL_FLOAT(Ped ped, const char* signalName) { return YimMenu::NativeInvoker::Invoke<5590, float>(ped, signalName); }
	FORCEINLINE bool GET_TASK_MOVE_NETWORK_SIGNAL_BOOL(Ped ped, const char* signalName) { return YimMenu::NativeInvoker::Invoke<5591, bool>(ped, signalName); }
	FORCEINLINE bool GET_TASK_MOVE_NETWORK_EVENT(Ped ped, const char* eventName) { return YimMenu::NativeInvoker::Invoke<5592, bool>(ped, eventName); }
	FORCEINLINE bool SET_TASK_MOVE_NETWORK_ENABLE_COLLISION_ON_NETWORK_CLONE_WHEN_FIXED(Ped ped, bool enable) { return YimMenu::NativeInvoker::Invoke<5593, bool>(ped, enable); }
	FORCEINLINE bool IS_MOVE_BLEND_RATIO_STILL(Ped ped) { return YimMenu::NativeInvoker::Invoke<5594, bool>(ped); }
	FORCEINLINE bool IS_MOVE_BLEND_RATIO_WALKING(Ped ped) { return YimMenu::NativeInvoker::Invoke<5595, bool>(ped); }
	FORCEINLINE bool IS_MOVE_BLEND_RATIO_RUNNING(Ped ped) { return YimMenu::NativeInvoker::Invoke<5596, bool>(ped); }
	FORCEINLINE bool IS_MOVE_BLEND_RATIO_SPRINTING(Ped ped) { return YimMenu::NativeInvoker::Invoke<5597, bool>(ped); }
	FORCEINLINE bool IS_PED_STILL(Ped ped) { return YimMenu::NativeInvoker::Invoke<5598, bool>(ped); }
	FORCEINLINE bool IS_PED_WALKING(Ped ped) { return YimMenu::NativeInvoker::Invoke<5599, bool>(ped); }
	FORCEINLINE bool IS_PED_RUNNING(Ped ped) { return YimMenu::NativeInvoker::Invoke<5600, bool>(ped); }
	FORCEINLINE bool IS_PED_SPRINTING(Ped ped) { return YimMenu::NativeInvoker::Invoke<5601, bool>(ped); }
	FORCEINLINE bool IS_PED_STRAFING(Ped ped) { return YimMenu::NativeInvoker::Invoke<5602, bool>(ped); }
	FORCEINLINE void TASK_SYNCHRONIZED_SCENE(Ped ped, int scene, const char* animDictionary, const char* animationName, float blendIn, float blendOut, int flags, int ragdollBlockingFlags, float moverBlendDelta, int ikFlags) { return YimMenu::NativeInvoker::Invoke<5603, void>(ped, scene, animDictionary, animationName, blendIn, blendOut, flags, ragdollBlockingFlags, moverBlendDelta, ikFlags); }
	FORCEINLINE void TASK_AGITATED_ACTION_CONFRONT_RESPONSE(Ped ped, Ped ped2) { return YimMenu::NativeInvoker::Invoke<5604, void>(ped, ped2); }
	FORCEINLINE void TASK_SWEEP_AIM_ENTITY(Ped ped, const char* animDict, const char* lowAnimName, const char* medAnimName, const char* hiAnimName, int runtime, Entity targetEntity, float turnRate, float blendInDuration) { return YimMenu::NativeInvoker::Invoke<5605, void>(ped, animDict, lowAnimName, medAnimName, hiAnimName, runtime, targetEntity, turnRate, blendInDuration); }
	FORCEINLINE void UPDATE_TASK_SWEEP_AIM_ENTITY(Ped ped, Entity entity) { return YimMenu::NativeInvoker::Invoke<5606, void>(ped, entity); }
	FORCEINLINE void TASK_SWEEP_AIM_POSITION(Ped ped, const char* animDict, const char* lowAnimName, const char* medAnimName, const char* hiAnimName, int runtime, float x, float y, float z, float turnRate, float blendInDuration) { return YimMenu::NativeInvoker::Invoke<5607, void>(ped, animDict, lowAnimName, medAnimName, hiAnimName, runtime, x, y, z, turnRate, blendInDuration); }
	FORCEINLINE void UPDATE_TASK_SWEEP_AIM_POSITION(Ped ped, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5608, void>(ped, x, y, z); }
	FORCEINLINE void TASK_ARREST_PED(Ped ped, Ped target) { return YimMenu::NativeInvoker::Invoke<5609, void>(ped, target); }
	FORCEINLINE bool IS_PED_RUNNING_ARREST_TASK(Ped ped) { return YimMenu::NativeInvoker::Invoke<5610, bool>(ped); }
	FORCEINLINE bool IS_PED_BEING_ARRESTED(Ped ped) { return YimMenu::NativeInvoker::Invoke<5611, bool>(ped); }
	FORCEINLINE void UNCUFF_PED(Ped ped) { return YimMenu::NativeInvoker::Invoke<5612, void>(ped); }
	FORCEINLINE bool IS_PED_CUFFED(Ped ped) { return YimMenu::NativeInvoker::Invoke<5613, bool>(ped); }
}

namespace VEHICLE
{
	FORCEINLINE Vehicle CREATE_VEHICLE(Hash modelHash, float x, float y, float z, float heading, bool isNetwork, bool bScriptHostVeh, bool p7) { return YimMenu::NativeInvoker::Invoke<5614, Vehicle>(modelHash, x, y, z, heading, isNetwork, bScriptHostVeh, p7); }
	FORCEINLINE void DELETE_VEHICLE(Vehicle* vehicle) { return YimMenu::NativeInvoker::Invoke<5615, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON(Vehicle vehicle, bool toggle, bool p2) { return YimMenu::NativeInvoker::Invoke<5616, void>(vehicle, toggle, p2); }
	FORCEINLINE void SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED(Vehicle vehicle, bool canBeLockedOn, bool p2) { return YimMenu::NativeInvoker::Invoke<5617, void>(vehicle, canBeLockedOn, p2); }
	FORCEINLINE void SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(Vehicle veh, bool toggle) { return YimMenu::NativeInvoker::Invoke<5618, void>(veh, toggle); }
	FORCEINLINE int GET_VEHICLE_HOMING_LOCKON_STATE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5619, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_HOMING_LOCKEDONTO_STATE(Any p0) { return YimMenu::NativeInvoker::Invoke<5620, int>(p0); }
	FORCEINLINE void SET_VEHICLE_HOMING_LOCKEDONTO_STATE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5621, void>(p0, p1); }
	FORCEINLINE bool IS_VEHICLE_MODEL(Vehicle vehicle, Hash model) { return YimMenu::NativeInvoker::Invoke<5622, bool>(vehicle, model); }
	FORCEINLINE bool DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(int vehicleGenerator) { return YimMenu::NativeInvoker::Invoke<5623, bool>(vehicleGenerator); }
	FORCEINLINE int CREATE_SCRIPT_VEHICLE_GENERATOR(float x, float y, float z, float heading, float p4, float p5, Hash modelHash, int p7, int p8, int p9, int p10, bool p11, bool p12, bool p13, bool p14, bool p15, int p16) { return YimMenu::NativeInvoker::Invoke<5624, int>(x, y, z, heading, p4, p5, modelHash, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16); }
	FORCEINLINE void DELETE_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator) { return YimMenu::NativeInvoker::Invoke<5625, void>(vehicleGenerator); }
	FORCEINLINE void SET_SCRIPT_VEHICLE_GENERATOR(int vehicleGenerator, bool enabled) { return YimMenu::NativeInvoker::Invoke<5626, void>(vehicleGenerator, enabled); }
	FORCEINLINE void SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, bool toggle, bool p7) { return YimMenu::NativeInvoker::Invoke<5627, void>(x1, y1, z1, x2, y2, z2, toggle, p7); }
	FORCEINLINE void SET_ALL_VEHICLE_GENERATORS_ACTIVE() { return YimMenu::NativeInvoker::Invoke<5628, void>(); }
	FORCEINLINE void SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(bool active) { return YimMenu::NativeInvoker::Invoke<5629, void>(active); }
	FORCEINLINE void SET_VEHICLE_GENERATOR_AREA_OF_INTEREST(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<5630, void>(x, y, z, radius); }
	FORCEINLINE void CLEAR_VEHICLE_GENERATOR_AREA_OF_INTEREST() { return YimMenu::NativeInvoker::Invoke<5631, void>(); }
	FORCEINLINE bool SET_VEHICLE_ON_GROUND_PROPERLY(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<5632, bool>(vehicle, p1); }
	FORCEINLINE bool SET_VEHICLE_USE_CUTSCENE_WHEEL_COMPRESSION(Vehicle p0, bool p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<5633, bool>(p0, p1, p2, p3); }
	FORCEINLINE bool IS_VEHICLE_STUCK_ON_ROOF(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5634, bool>(vehicle); }
	FORCEINLINE void ADD_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5635, void>(vehicle); }
	FORCEINLINE void REMOVE_VEHICLE_UPSIDEDOWN_CHECK(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5636, void>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_STOPPED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5637, bool>(vehicle); }
	FORCEINLINE int GET_VEHICLE_NUMBER_OF_PASSENGERS(Vehicle vehicle, bool includeDriver, bool includeDeadOccupants) { return YimMenu::NativeInvoker::Invoke<5638, int>(vehicle, includeDriver, includeDeadOccupants); }
	FORCEINLINE int GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5639, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_MODEL_NUMBER_OF_SEATS(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<5640, int>(modelHash); }
	FORCEINLINE bool IS_SEAT_WARP_ONLY(Vehicle vehicle, int seatIndex) { return YimMenu::NativeInvoker::Invoke<5641, bool>(vehicle, seatIndex); }
	FORCEINLINE bool IS_TURRET_SEAT(Vehicle vehicle, int seatIndex) { return YimMenu::NativeInvoker::Invoke<5642, bool>(vehicle, seatIndex); }
	FORCEINLINE bool DOES_VEHICLE_ALLOW_RAPPEL(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5643, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier) { return YimMenu::NativeInvoker::Invoke<5644, void>(multiplier); }
	FORCEINLINE void SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier) { return YimMenu::NativeInvoker::Invoke<5645, void>(multiplier); }
	FORCEINLINE void SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(float multiplier) { return YimMenu::NativeInvoker::Invoke<5646, void>(multiplier); }
	FORCEINLINE void SET_DISABLE_RANDOM_TRAINS_THIS_FRAME(bool toggle) { return YimMenu::NativeInvoker::Invoke<5647, void>(toggle); }
	FORCEINLINE void SET_AMBIENT_VEHICLE_RANGE_MULTIPLIER_THIS_FRAME(float value) { return YimMenu::NativeInvoker::Invoke<5648, void>(value); }
	FORCEINLINE void SET_FAR_DRAW_VEHICLES(bool toggle) { return YimMenu::NativeInvoker::Invoke<5649, void>(toggle); }
	FORCEINLINE void SET_NUMBER_OF_PARKED_VEHICLES(int value) { return YimMenu::NativeInvoker::Invoke<5650, void>(value); }
	FORCEINLINE void SET_VEHICLE_DOORS_LOCKED(Vehicle vehicle, int doorLockStatus) { return YimMenu::NativeInvoker::Invoke<5651, void>(vehicle, doorLockStatus); }
	FORCEINLINE void SET_VEHICLE_INDIVIDUAL_DOORS_LOCKED(Vehicle vehicle, int doorId, int doorLockStatus) { return YimMenu::NativeInvoker::Invoke<5652, void>(vehicle, doorId, doorLockStatus); }
	FORCEINLINE void SET_VEHICLE_HAS_MUTED_SIRENS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5653, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player, bool toggle) { return YimMenu::NativeInvoker::Invoke<5654, void>(vehicle, player, toggle); }
	FORCEINLINE bool GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(Vehicle vehicle, Player player) { return YimMenu::NativeInvoker::Invoke<5655, bool>(vehicle, player); }
	FORCEINLINE void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5656, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5657, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(Vehicle vehicle, int team, bool toggle) { return YimMenu::NativeInvoker::Invoke<5658, void>(vehicle, team, toggle); }
	FORCEINLINE void SET_VEHICLE_DOORS_LOCKED_FOR_ALL_TEAMS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5659, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_DONT_TERMINATE_TASK_WHEN_ACHIEVED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5660, void>(vehicle); }
	FORCEINLINE void EXPLODE_VEHICLE(Vehicle vehicle, bool isAudible, bool isInvisible) { return YimMenu::NativeInvoker::Invoke<5661, void>(vehicle, isAudible, isInvisible); }
	FORCEINLINE void SET_VEHICLE_OUT_OF_CONTROL(Vehicle vehicle, bool killDriver, bool explodeOnImpact) { return YimMenu::NativeInvoker::Invoke<5662, void>(vehicle, killDriver, explodeOnImpact); }
	FORCEINLINE void SET_VEHICLE_TIMED_EXPLOSION(Vehicle vehicle, Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<5663, void>(vehicle, ped, toggle); }
	FORCEINLINE void ADD_VEHICLE_PHONE_EXPLOSIVE_DEVICE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5664, void>(vehicle); }
	FORCEINLINE void CLEAR_VEHICLE_PHONE_EXPLOSIVE_DEVICE() { return YimMenu::NativeInvoker::Invoke<5665, void>(); }
	FORCEINLINE bool HAS_VEHICLE_PHONE_EXPLOSIVE_DEVICE() { return YimMenu::NativeInvoker::Invoke<5666, bool>(); }
	FORCEINLINE void DETONATE_VEHICLE_PHONE_EXPLOSIVE_DEVICE() { return YimMenu::NativeInvoker::Invoke<5667, void>(); }
	FORCEINLINE void SET_TAXI_LIGHTS(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<5668, void>(vehicle, state); }
	FORCEINLINE bool IS_TAXI_LIGHT_ON(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5669, bool>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_IN_GARAGE_AREA(const char* garageName, Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5670, bool>(garageName, vehicle); }
	FORCEINLINE void SET_VEHICLE_COLOURS(Vehicle vehicle, int colorPrimary, int colorSecondary) { return YimMenu::NativeInvoker::Invoke<5671, void>(vehicle, colorPrimary, colorSecondary); }
	FORCEINLINE void SET_VEHICLE_FULLBEAM(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5672, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_IS_RACING(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5673, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int r, int g, int b) { return YimMenu::NativeInvoker::Invoke<5674, void>(vehicle, r, g, b); }
	FORCEINLINE void GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b) { return YimMenu::NativeInvoker::Invoke<5675, void>(vehicle, r, g, b); }
	FORCEINLINE void CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5676, void>(vehicle); }
	FORCEINLINE bool GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5677, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int r, int g, int b) { return YimMenu::NativeInvoker::Invoke<5678, void>(vehicle, r, g, b); }
	FORCEINLINE void GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle, int* r, int* g, int* b) { return YimMenu::NativeInvoker::Invoke<5679, void>(vehicle, r, g, b); }
	FORCEINLINE void CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5680, void>(vehicle); }
	FORCEINLINE bool GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5681, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle, float fade) { return YimMenu::NativeInvoker::Invoke<5682, void>(vehicle, fade); }
	FORCEINLINE float GET_VEHICLE_ENVEFF_SCALE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5683, float>(vehicle); }
	FORCEINLINE void SET_CAN_RESPRAY_VEHICLE(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<5684, void>(vehicle, state); }
	FORCEINLINE void SET_GOON_BOSS_VEHICLE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5685, void>(vehicle, toggle); }
	FORCEINLINE void SET_OPEN_REAR_DOORS_ON_EXPLOSION(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5686, void>(vehicle, toggle); }
	FORCEINLINE void FORCE_SUBMARINE_SURFACE_MODE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5687, void>(vehicle, toggle); }
	FORCEINLINE void FORCE_SUBMARINE_NEURTAL_BUOYANCY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5688, void>(p0, p1); }
	FORCEINLINE void SET_SUBMARINE_CRUSH_DEPTHS(Vehicle vehicle, bool p1, float depth1, float depth2, float depth3) { return YimMenu::NativeInvoker::Invoke<5689, void>(vehicle, p1, depth1, depth2, depth3); }
	FORCEINLINE bool GET_SUBMARINE_IS_UNDER_DESIGN_DEPTH(Vehicle submarine) { return YimMenu::NativeInvoker::Invoke<5690, bool>(submarine); }
	FORCEINLINE int GET_SUBMARINE_NUMBER_OF_AIR_LEAKS(Vehicle submarine) { return YimMenu::NativeInvoker::Invoke<5691, int>(submarine); }
	FORCEINLINE void SET_BOAT_IGNORE_LAND_PROBES(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5692, void>(p0, p1); }
	FORCEINLINE void _SET_BOUNDS_AFFECT_WATER_PROBES(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5693, void>(vehicle, toggle); }
	FORCEINLINE void SET_BOAT_ANCHOR(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5694, void>(vehicle, toggle); }
	FORCEINLINE bool CAN_ANCHOR_BOAT_HERE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5695, bool>(vehicle); }
	FORCEINLINE bool CAN_ANCHOR_BOAT_HERE_IGNORE_PLAYERS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5696, bool>(vehicle); }
	FORCEINLINE void SET_BOAT_REMAINS_ANCHORED_WHILE_PLAYER_IS_DRIVER(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5697, void>(vehicle, toggle); }
	FORCEINLINE void SET_FORCE_LOW_LOD_ANCHOR_MODE(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5698, void>(vehicle, p1); }
	FORCEINLINE void SET_BOAT_LOW_LOD_ANCHOR_DISTANCE(Vehicle vehicle, float value) { return YimMenu::NativeInvoker::Invoke<5699, void>(vehicle, value); }
	FORCEINLINE bool IS_BOAT_ANCHORED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5700, bool>(vehicle); }
	FORCEINLINE void SET_BOAT_SINKS_WHEN_WRECKED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5701, void>(vehicle, toggle); }
	FORCEINLINE void SET_BOAT_WRECKED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5702, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_SIREN(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5703, void>(vehicle, toggle); }
	FORCEINLINE bool IS_VEHICLE_SIREN_ON(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5704, bool>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_SIREN_AUDIO_ON(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5705, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_STRONG(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5706, void>(vehicle, toggle); }
	FORCEINLINE void REMOVE_VEHICLE_STUCK_CHECK(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5707, void>(vehicle); }
	FORCEINLINE void GET_VEHICLE_COLOURS(Vehicle vehicle, int* colorPrimary, int* colorSecondary) { return YimMenu::NativeInvoker::Invoke<5708, void>(vehicle, colorPrimary, colorSecondary); }
	FORCEINLINE bool IS_VEHICLE_SEAT_FREE(Vehicle vehicle, int seatIndex, bool isTaskRunning) { return YimMenu::NativeInvoker::Invoke<5709, bool>(vehicle, seatIndex, isTaskRunning); }
	FORCEINLINE Ped GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex, bool p2) { return YimMenu::NativeInvoker::Invoke<5710, Ped>(vehicle, seatIndex, p2); }
	FORCEINLINE Ped GET_LAST_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int seatIndex) { return YimMenu::NativeInvoker::Invoke<5711, Ped>(vehicle, seatIndex); }
	FORCEINLINE bool GET_VEHICLE_LIGHTS_STATE(Vehicle vehicle, bool* lightsOn, bool* highbeamsOn) { return YimMenu::NativeInvoker::Invoke<5712, bool>(vehicle, lightsOn, highbeamsOn); }
	FORCEINLINE bool IS_VEHICLE_TYRE_BURST(Vehicle vehicle, int wheelID, bool completely) { return YimMenu::NativeInvoker::Invoke<5713, bool>(vehicle, wheelID, completely); }
	FORCEINLINE void SET_VEHICLE_FORWARD_SPEED(Vehicle vehicle, float speed) { return YimMenu::NativeInvoker::Invoke<5714, void>(vehicle, speed); }
	FORCEINLINE void SET_VEHICLE_FORWARD_SPEED_XY(Vehicle vehicle, float speed) { return YimMenu::NativeInvoker::Invoke<5715, void>(vehicle, speed); }
	FORCEINLINE void BRING_VEHICLE_TO_HALT(Vehicle vehicle, float distance, int duration, bool p3) { return YimMenu::NativeInvoker::Invoke<5716, void>(vehicle, distance, duration, p3); }
	FORCEINLINE void SET_VEHICLE_STEER_FOR_BUILDINGS(Vehicle vehicle, Any p1) { return YimMenu::NativeInvoker::Invoke<5717, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_CAUSES_SWERVING(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5718, void>(vehicle, toggle); }
	FORCEINLINE void SET_IGNORE_PLANES_SMALL_PITCH_CHANGE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5719, void>(p0, p1); }
	FORCEINLINE void STOP_BRINGING_VEHICLE_TO_HALT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5720, void>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_BEING_BROUGHT_TO_HALT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5721, bool>(vehicle); }
	FORCEINLINE void LOWER_FORKLIFT_FORKS(Vehicle forklift) { return YimMenu::NativeInvoker::Invoke<5722, void>(forklift); }
	FORCEINLINE void SET_FORKLIFT_FORK_HEIGHT(Vehicle vehicle, float height) { return YimMenu::NativeInvoker::Invoke<5723, void>(vehicle, height); }
	FORCEINLINE bool IS_ENTITY_ATTACHED_TO_HANDLER_FRAME(Vehicle vehicle, Entity entity) { return YimMenu::NativeInvoker::Invoke<5724, bool>(vehicle, entity); }
	FORCEINLINE bool IS_ANY_ENTITY_ATTACHED_TO_HANDLER_FRAME(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5725, bool>(vehicle); }
	FORCEINLINE Vehicle FIND_HANDLER_VEHICLE_CONTAINER_IS_ATTACHED_TO(Entity entity) { return YimMenu::NativeInvoker::Invoke<5726, Vehicle>(entity); }
	FORCEINLINE bool IS_HANDLER_FRAME_LINED_UP_WITH_CONTAINER(Vehicle vehicle, Entity entity) { return YimMenu::NativeInvoker::Invoke<5727, bool>(vehicle, entity); }
	FORCEINLINE void ATTACH_CONTAINER_TO_HANDLER_FRAME_WHEN_LINED_UP(Vehicle vehicle, Entity entity) { return YimMenu::NativeInvoker::Invoke<5728, void>(vehicle, entity); }
	FORCEINLINE void DETACH_CONTAINER_FROM_HANDLER_FRAME(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5729, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_DISABLE_HEIGHT_MAP_AVOIDANCE(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5730, void>(vehicle, p1); }
	FORCEINLINE void SET_BOAT_DISABLE_AVOIDANCE(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5731, void>(vehicle, p1); }
	FORCEINLINE bool IS_HELI_LANDING_AREA_BLOCKED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5732, bool>(vehicle); }
	FORCEINLINE void SET_SHORT_SLOWDOWN_FOR_LANDING(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5733, void>(vehicle); }
	FORCEINLINE void SET_HELI_TURBULENCE_SCALAR(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<5734, void>(vehicle, p1); }
	FORCEINLINE void SET_CAR_BOOT_OPEN(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5735, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_TYRE_BURST(Vehicle vehicle, int index, bool onRim, float p3) { return YimMenu::NativeInvoker::Invoke<5736, void>(vehicle, index, onRim, p3); }
	FORCEINLINE void SET_VEHICLE_DOORS_SHUT(Vehicle vehicle, bool closeInstantly) { return YimMenu::NativeInvoker::Invoke<5737, void>(vehicle, closeInstantly); }
	FORCEINLINE void SET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5738, void>(vehicle, toggle); }
	FORCEINLINE bool GET_VEHICLE_TYRES_CAN_BURST(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5739, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_WHEELS_CAN_BREAK(Vehicle vehicle, bool enabled) { return YimMenu::NativeInvoker::Invoke<5740, void>(vehicle, enabled); }
	FORCEINLINE void SET_VEHICLE_DOOR_OPEN(Vehicle vehicle, int doorId, bool loose, bool openInstantly) { return YimMenu::NativeInvoker::Invoke<5741, void>(vehicle, doorId, loose, openInstantly); }
	FORCEINLINE void SET_VEHICLE_DOOR_AUTO_LOCK(Vehicle vehicle, int doorId, bool toggle) { return YimMenu::NativeInvoker::Invoke<5742, void>(vehicle, doorId, toggle); }
	FORCEINLINE void SET_FLEEING_VEHICLES_USE_SWITCHED_OFF_NODES(Any p0) { return YimMenu::NativeInvoker::Invoke<5743, void>(p0); }
	FORCEINLINE void REMOVE_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex) { return YimMenu::NativeInvoker::Invoke<5744, void>(vehicle, windowIndex); }
	FORCEINLINE void ROLL_DOWN_WINDOWS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5745, void>(vehicle); }
	FORCEINLINE void ROLL_DOWN_WINDOW(Vehicle vehicle, int windowIndex) { return YimMenu::NativeInvoker::Invoke<5746, void>(vehicle, windowIndex); }
	FORCEINLINE void ROLL_UP_WINDOW(Vehicle vehicle, int windowIndex) { return YimMenu::NativeInvoker::Invoke<5747, void>(vehicle, windowIndex); }
	FORCEINLINE void SMASH_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex) { return YimMenu::NativeInvoker::Invoke<5748, void>(vehicle, windowIndex); }
	FORCEINLINE void FIX_VEHICLE_WINDOW(Vehicle vehicle, int windowIndex) { return YimMenu::NativeInvoker::Invoke<5749, void>(vehicle, windowIndex); }
	FORCEINLINE void POP_OUT_VEHICLE_WINDSCREEN(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5750, void>(vehicle); }
	FORCEINLINE void POP_OFF_VEHICLE_ROOF_WITH_IMPULSE(Vehicle vehicle, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5751, void>(vehicle, x, y, z); }
	FORCEINLINE void SET_VEHICLE_LIGHTS(Vehicle vehicle, int state) { return YimMenu::NativeInvoker::Invoke<5752, void>(vehicle, state); }
	FORCEINLINE void SET_VEHICLE_USE_PLAYER_LIGHT_SETTINGS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5753, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_HEADLIGHT_SHADOWS(Vehicle vehicle, int p1) { return YimMenu::NativeInvoker::Invoke<5754, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_ALARM(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<5755, void>(vehicle, state); }
	FORCEINLINE void START_VEHICLE_ALARM(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5756, void>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_ALARM_ACTIVATED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5757, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_INTERIORLIGHT(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5758, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_FORCE_INTERIORLIGHT(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5759, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_LIGHT_MULTIPLIER(Vehicle vehicle, float multiplier) { return YimMenu::NativeInvoker::Invoke<5760, void>(vehicle, multiplier); }
	FORCEINLINE void ATTACH_VEHICLE_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float radius) { return YimMenu::NativeInvoker::Invoke<5761, void>(vehicle, trailer, radius); }
	FORCEINLINE void ATTACH_VEHICLE_ON_TO_TRAILER(Vehicle vehicle, Vehicle trailer, float offsetX, float offsetY, float offsetZ, float coordsX, float coordsY, float coordsZ, float rotationX, float rotationY, float rotationZ, float disableCollisions) { return YimMenu::NativeInvoker::Invoke<5762, void>(vehicle, trailer, offsetX, offsetY, offsetZ, coordsX, coordsY, coordsZ, rotationX, rotationY, rotationZ, disableCollisions); }
	FORCEINLINE void STABILISE_ENTITY_ATTACHED_TO_HELI(Vehicle vehicle, Entity entity, float p2) { return YimMenu::NativeInvoker::Invoke<5763, void>(vehicle, entity, p2); }
	FORCEINLINE void DETACH_VEHICLE_FROM_TRAILER(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5764, void>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_ATTACHED_TO_TRAILER(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5765, bool>(vehicle); }
	FORCEINLINE void SET_TRAILER_INVERSE_MASS_SCALE(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<5766, void>(vehicle, p1); }
	FORCEINLINE void SET_TRAILER_LEGS_RAISED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5767, void>(vehicle); }
	FORCEINLINE void SET_TRAILER_LEGS_LOWERED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5768, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_TYRE_FIXED(Vehicle vehicle, int tyreIndex) { return YimMenu::NativeInvoker::Invoke<5769, void>(vehicle, tyreIndex); }
	FORCEINLINE void SET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle, const char* plateText) { return YimMenu::NativeInvoker::Invoke<5770, void>(vehicle, plateText); }
	FORCEINLINE const char* GET_VEHICLE_NUMBER_PLATE_TEXT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5771, const char*>(vehicle); }
	FORCEINLINE int GET_NUMBER_OF_VEHICLE_NUMBER_PLATES() { return YimMenu::NativeInvoker::Invoke<5772, int>(); }
	FORCEINLINE void SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle, int plateIndex) { return YimMenu::NativeInvoker::Invoke<5773, void>(vehicle, plateIndex); }
	FORCEINLINE int GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5774, int>(vehicle); }
	FORCEINLINE void SET_RANDOM_TRAINS(bool toggle) { return YimMenu::NativeInvoker::Invoke<5775, void>(toggle); }
	FORCEINLINE Vehicle CREATE_MISSION_TRAIN(int variation, float x, float y, float z, bool direction, Any p5, Any p6) { return YimMenu::NativeInvoker::Invoke<5776, Vehicle>(variation, x, y, z, direction, p5, p6); }
	FORCEINLINE void SWITCH_TRAIN_TRACK(int trackId, bool state) { return YimMenu::NativeInvoker::Invoke<5777, void>(trackId, state); }
	FORCEINLINE void SET_TRAIN_TRACK_SPAWN_FREQUENCY(int trackIndex, int frequency) { return YimMenu::NativeInvoker::Invoke<5778, void>(trackIndex, frequency); }
	FORCEINLINE void ALLOW_TRAIN_TO_BE_REMOVED_BY_POPULATION(Any p0) { return YimMenu::NativeInvoker::Invoke<5779, void>(p0); }
	FORCEINLINE void DELETE_ALL_TRAINS() { return YimMenu::NativeInvoker::Invoke<5780, void>(); }
	FORCEINLINE void SET_TRAIN_SPEED(Vehicle train, float speed) { return YimMenu::NativeInvoker::Invoke<5781, void>(train, speed); }
	FORCEINLINE void SET_TRAIN_CRUISE_SPEED(Vehicle train, float speed) { return YimMenu::NativeInvoker::Invoke<5782, void>(train, speed); }
	FORCEINLINE void SET_RANDOM_BOATS(bool toggle) { return YimMenu::NativeInvoker::Invoke<5783, void>(toggle); }
	FORCEINLINE void SET_RANDOM_BOATS_MP(bool toggle) { return YimMenu::NativeInvoker::Invoke<5784, void>(toggle); }
	FORCEINLINE void SET_GARBAGE_TRUCKS(bool toggle) { return YimMenu::NativeInvoker::Invoke<5785, void>(toggle); }
	FORCEINLINE bool DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5786, bool>(vehicle); }
	FORCEINLINE int GET_VEHICLE_RECORDING_ID(int recording, const char* script) { return YimMenu::NativeInvoker::Invoke<5787, int>(recording, script); }
	FORCEINLINE void REQUEST_VEHICLE_RECORDING(int recording, const char* script) { return YimMenu::NativeInvoker::Invoke<5788, void>(recording, script); }
	FORCEINLINE bool HAS_VEHICLE_RECORDING_BEEN_LOADED(int recording, const char* script) { return YimMenu::NativeInvoker::Invoke<5789, bool>(recording, script); }
	FORCEINLINE void REMOVE_VEHICLE_RECORDING(int recording, const char* script) { return YimMenu::NativeInvoker::Invoke<5790, void>(recording, script); }
	FORCEINLINE Vector3 GET_POSITION_OF_VEHICLE_RECORDING_ID_AT_TIME(int id, float time) { return YimMenu::NativeInvoker::Invoke<5791, Vector3>(id, time); }
	FORCEINLINE Vector3 GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(int recording, float time, const char* script) { return YimMenu::NativeInvoker::Invoke<5792, Vector3>(recording, time, script); }
	FORCEINLINE Vector3 GET_ROTATION_OF_VEHICLE_RECORDING_ID_AT_TIME(int id, float time) { return YimMenu::NativeInvoker::Invoke<5793, Vector3>(id, time); }
	FORCEINLINE Vector3 GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(int recording, float time, const char* script) { return YimMenu::NativeInvoker::Invoke<5794, Vector3>(recording, time, script); }
	FORCEINLINE float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(int id) { return YimMenu::NativeInvoker::Invoke<5795, float>(id); }
	FORCEINLINE float GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(int recording, const char* script) { return YimMenu::NativeInvoker::Invoke<5796, float>(recording, script); }
	FORCEINLINE float GET_POSITION_IN_RECORDING(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5797, float>(vehicle); }
	FORCEINLINE float GET_TIME_POSITION_IN_RECORDING(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5798, float>(vehicle); }
	FORCEINLINE void START_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, int recording, const char* script, bool p3) { return YimMenu::NativeInvoker::Invoke<5799, void>(vehicle, recording, script, p3); }
	FORCEINLINE void START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(Vehicle vehicle, int recording, const char* script, int flags, int time, int drivingStyle) { return YimMenu::NativeInvoker::Invoke<5800, void>(vehicle, recording, script, flags, time, drivingStyle); }
	FORCEINLINE void FORCE_PLAYBACK_RECORDED_VEHICLE_UPDATE(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5801, void>(vehicle, p1); }
	FORCEINLINE void STOP_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5802, void>(vehicle); }
	FORCEINLINE void PAUSE_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5803, void>(vehicle); }
	FORCEINLINE void UNPAUSE_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5804, void>(vehicle); }
	FORCEINLINE bool IS_PLAYBACK_GOING_ON_FOR_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5805, bool>(vehicle); }
	FORCEINLINE bool IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5806, bool>(vehicle); }
	FORCEINLINE int GET_CURRENT_PLAYBACK_FOR_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5807, int>(vehicle); }
	FORCEINLINE void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5808, void>(vehicle); }
	FORCEINLINE void SET_PLAYBACK_SPEED(Vehicle vehicle, float speed) { return YimMenu::NativeInvoker::Invoke<5809, void>(vehicle, speed); }
	FORCEINLINE void START_PLAYBACK_RECORDED_VEHICLE_USING_AI(Vehicle vehicle, int recording, const char* script, float speed, int drivingStyle) { return YimMenu::NativeInvoker::Invoke<5810, void>(vehicle, recording, script, speed, drivingStyle); }
	FORCEINLINE void SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(Vehicle vehicle, float time) { return YimMenu::NativeInvoker::Invoke<5811, void>(vehicle, time); }
	FORCEINLINE void SET_PLAYBACK_TO_USE_AI(Vehicle vehicle, int drivingStyle) { return YimMenu::NativeInvoker::Invoke<5812, void>(vehicle, drivingStyle); }
	FORCEINLINE void SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(Vehicle vehicle, int time, int drivingStyle, bool p3) { return YimMenu::NativeInvoker::Invoke<5813, void>(vehicle, time, drivingStyle, p3); }
	FORCEINLINE void SET_ADDITIONAL_ROTATION_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z, Any p4) { return YimMenu::NativeInvoker::Invoke<5814, void>(vehicle, x, y, z, p4); }
	FORCEINLINE void SET_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5815, void>(vehicle, x, y, z); }
	FORCEINLINE void SET_GLOBAL_POSITION_OFFSET_FOR_RECORDED_VEHICLE_PLAYBACK(Vehicle vehicle, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5816, void>(vehicle, x, y, z); }
	FORCEINLINE void SET_SHOULD_LERP_FROM_AI_TO_FULL_RECORDING(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5817, void>(vehicle, p1); }
	FORCEINLINE void EXPLODE_VEHICLE_IN_CUTSCENE(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5818, void>(vehicle, p1); }
	FORCEINLINE void ADD_VEHICLE_STUCK_CHECK_WITH_WARP(Any p0, float p1, Any p2, bool p3, bool p4, bool p5, Any p6) { return YimMenu::NativeInvoker::Invoke<5819, void>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void SET_VEHICLE_MODEL_IS_SUPPRESSED(Hash model, bool suppressed) { return YimMenu::NativeInvoker::Invoke<5820, void>(model, suppressed); }
	FORCEINLINE Vehicle GET_RANDOM_VEHICLE_IN_SPHERE(float x, float y, float z, float radius, Hash modelHash, int flags) { return YimMenu::NativeInvoker::Invoke<5821, Vehicle>(x, y, z, radius, modelHash, flags); }
	FORCEINLINE Vehicle GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6) { return YimMenu::NativeInvoker::Invoke<5822, Vehicle>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE Vehicle GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(float p0, float p1, float p2, float p3, int p4, int p5, int p6) { return YimMenu::NativeInvoker::Invoke<5823, Vehicle>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE Vehicle GET_CLOSEST_VEHICLE(float x, float y, float z, float radius, Hash modelHash, int flags) { return YimMenu::NativeInvoker::Invoke<5824, Vehicle>(x, y, z, radius, modelHash, flags); }
	FORCEINLINE Vehicle GET_TRAIN_CARRIAGE(Vehicle train, int trailerNumber) { return YimMenu::NativeInvoker::Invoke<5825, Vehicle>(train, trailerNumber); }
	FORCEINLINE bool IS_MISSION_TRAIN(Vehicle train) { return YimMenu::NativeInvoker::Invoke<5826, bool>(train); }
	FORCEINLINE void DELETE_MISSION_TRAIN(Vehicle* train) { return YimMenu::NativeInvoker::Invoke<5827, void>(train); }
	FORCEINLINE void SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Vehicle* train, bool p1) { return YimMenu::NativeInvoker::Invoke<5828, void>(train, p1); }
	FORCEINLINE void SET_MISSION_TRAIN_COORDS(Vehicle train, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<5829, void>(train, x, y, z); }
	FORCEINLINE bool IS_THIS_MODEL_A_BOAT(Hash model) { return YimMenu::NativeInvoker::Invoke<5830, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_A_JETSKI(Hash model) { return YimMenu::NativeInvoker::Invoke<5831, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_A_PLANE(Hash model) { return YimMenu::NativeInvoker::Invoke<5832, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_A_HELI(Hash model) { return YimMenu::NativeInvoker::Invoke<5833, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_A_CAR(Hash model) { return YimMenu::NativeInvoker::Invoke<5834, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_A_TRAIN(Hash model) { return YimMenu::NativeInvoker::Invoke<5835, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_A_BIKE(Hash model) { return YimMenu::NativeInvoker::Invoke<5836, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_A_BICYCLE(Hash model) { return YimMenu::NativeInvoker::Invoke<5837, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_A_QUADBIKE(Hash model) { return YimMenu::NativeInvoker::Invoke<5838, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(Hash model) { return YimMenu::NativeInvoker::Invoke<5839, bool>(model); }
	FORCEINLINE bool IS_THIS_MODEL_AN_AMPHIBIOUS_QUADBIKE(Hash model) { return YimMenu::NativeInvoker::Invoke<5840, bool>(model); }
	FORCEINLINE void SET_HELI_BLADES_FULL_SPEED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5841, void>(vehicle); }
	FORCEINLINE void SET_HELI_BLADES_SPEED(Vehicle vehicle, float speed) { return YimMenu::NativeInvoker::Invoke<5842, void>(vehicle, speed); }
	FORCEINLINE void FORCE_SUB_THROTTLE_FOR_TIME(Vehicle vehicle, float p1, float p2) { return YimMenu::NativeInvoker::Invoke<5843, void>(vehicle, p1, p2); }
	FORCEINLINE void SET_VEHICLE_CAN_BE_TARGETTED(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<5844, void>(vehicle, state); }
	FORCEINLINE void SET_DONT_ALLOW_PLAYER_TO_ENTER_VEHICLE_IF_LOCKED_FOR_PLAYER(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5845, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<5846, void>(vehicle, state); }
	FORCEINLINE void SET_VEHICLE_HAS_UNBREAKABLE_LIGHTS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5847, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_RESPECTS_LOCKS_WHEN_HAS_DRIVER(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5848, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_CAN_EJECT_PASSENGERS_IF_LOCKED(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5849, void>(p0, p1); }
	FORCEINLINE float GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5850, float>(vehicle); }
	FORCEINLINE void SET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float dirtLevel) { return YimMenu::NativeInvoker::Invoke<5851, void>(vehicle, dirtLevel); }
	FORCEINLINE bool GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5852, bool>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_DOOR_FULLY_OPEN(Vehicle vehicle, int doorId) { return YimMenu::NativeInvoker::Invoke<5853, bool>(vehicle, doorId); }
	FORCEINLINE void SET_VEHICLE_ENGINE_ON(Vehicle vehicle, bool value, bool instantly, bool disableAutoStart) { return YimMenu::NativeInvoker::Invoke<5854, void>(vehicle, value, instantly, disableAutoStart); }
	FORCEINLINE void SET_VEHICLE_UNDRIVEABLE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5855, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_PROVIDES_COVER(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5856, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_DOOR_CONTROL(Vehicle vehicle, int doorId, int speed, float angle) { return YimMenu::NativeInvoker::Invoke<5857, void>(vehicle, doorId, speed, angle); }
	FORCEINLINE void SET_VEHICLE_DOOR_LATCHED(Vehicle vehicle, int doorId, bool p2, bool p3, bool p4) { return YimMenu::NativeInvoker::Invoke<5858, void>(vehicle, doorId, p2, p3, p4); }
	FORCEINLINE float GET_VEHICLE_DOOR_ANGLE_RATIO(Vehicle vehicle, int doorId) { return YimMenu::NativeInvoker::Invoke<5859, float>(vehicle, doorId); }
	FORCEINLINE Ped GET_PED_USING_VEHICLE_DOOR(Vehicle vehicle, int doord) { return YimMenu::NativeInvoker::Invoke<5860, Ped>(vehicle, doord); }
	FORCEINLINE void SET_VEHICLE_DOOR_SHUT(Vehicle vehicle, int doorId, bool closeInstantly) { return YimMenu::NativeInvoker::Invoke<5861, void>(vehicle, doorId, closeInstantly); }
	FORCEINLINE void SET_VEHICLE_DOOR_BROKEN(Vehicle vehicle, int doorId, bool deleteDoor) { return YimMenu::NativeInvoker::Invoke<5862, void>(vehicle, doorId, deleteDoor); }
	FORCEINLINE void SET_VEHICLE_CAN_BREAK(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5863, void>(vehicle, toggle); }
	FORCEINLINE bool DOES_VEHICLE_HAVE_ROOF(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5864, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_REMOVE_AGGRESSIVE_CARJACK_MISSION(Any p0) { return YimMenu::NativeInvoker::Invoke<5865, void>(p0); }
	FORCEINLINE void SET_VEHICLE_AVOID_PLAYER_VEHICLE_RIOT_VAN_MISSION(Any p0) { return YimMenu::NativeInvoker::Invoke<5866, void>(p0); }
	FORCEINLINE void SET_CARJACK_MISSION_REMOVAL_PARAMETERS(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<5867, void>(p0, p1); }
	FORCEINLINE bool IS_BIG_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5868, bool>(vehicle); }
	FORCEINLINE int GET_NUMBER_OF_VEHICLE_COLOURS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5869, int>(vehicle); }
	FORCEINLINE void SET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle, int colorCombination) { return YimMenu::NativeInvoker::Invoke<5870, void>(vehicle, colorCombination); }
	FORCEINLINE int GET_VEHICLE_COLOUR_COMBINATION(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5871, int>(vehicle); }
	FORCEINLINE void SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Vehicle vehicle, int colorIndex) { return YimMenu::NativeInvoker::Invoke<5872, void>(vehicle, colorIndex); }
	FORCEINLINE int GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5873, int>(vehicle); }
	FORCEINLINE void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5874, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_WILL_FORCE_OTHER_VEHICLES_TO_STOP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5875, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_ACT_AS_IF_HAS_SIREN_ON(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5876, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_USE_MORE_RESTRICTIVE_SPAWN_CHECKS(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5877, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_MAY_BE_USED_BY_GOTO_POINT_ANY_MEANS(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5878, void>(vehicle, p1); }
	FORCEINLINE void GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(bool p0, Hash* modelHash, int* successIndicator) { return YimMenu::NativeInvoker::Invoke<5879, void>(p0, modelHash, successIndicator); }
	FORCEINLINE int GET_VEHICLE_DOOR_LOCK_STATUS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5880, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_INDIVIDUAL_DOOR_LOCK_STATUS(Vehicle vehicle, int doorId) { return YimMenu::NativeInvoker::Invoke<5881, int>(vehicle, doorId); }
	FORCEINLINE bool IS_VEHICLE_DOOR_DAMAGED(Vehicle veh, int doorID) { return YimMenu::NativeInvoker::Invoke<5882, bool>(veh, doorID); }
	FORCEINLINE void SET_DOOR_ALLOWED_TO_BE_BROKEN_OFF(Vehicle vehicle, int doorId, bool isBreakable) { return YimMenu::NativeInvoker::Invoke<5883, void>(vehicle, doorId, isBreakable); }
	FORCEINLINE bool IS_VEHICLE_BUMPER_BOUNCING(Vehicle vehicle, bool frontBumper) { return YimMenu::NativeInvoker::Invoke<5884, bool>(vehicle, frontBumper); }
	FORCEINLINE bool IS_VEHICLE_BUMPER_BROKEN_OFF(Vehicle vehicle, bool frontBumper) { return YimMenu::NativeInvoker::Invoke<5885, bool>(vehicle, frontBumper); }
	FORCEINLINE bool IS_COP_VEHICLE_IN_AREA_3D(float x1, float x2, float y1, float y2, float z1, float z2) { return YimMenu::NativeInvoker::Invoke<5886, bool>(x1, x2, y1, y2, z1, z2); }
	FORCEINLINE bool IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5887, bool>(vehicle); }
	FORCEINLINE int GET_VEHICLE_MODEL_VALUE(Hash vehicleModel) { return YimMenu::NativeInvoker::Invoke<5888, int>(vehicleModel); }
	FORCEINLINE Hash GET_VEHICLE_LAYOUT_HASH(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5889, Hash>(vehicle); }
	FORCEINLINE Hash GET_IN_VEHICLE_CLIPSET_HASH_FOR_SEAT(Vehicle vehicle, int p1) { return YimMenu::NativeInvoker::Invoke<5890, Hash>(vehicle, p1); }
	FORCEINLINE void SET_RENDER_TRAIN_AS_DERAILED(Vehicle train, bool toggle) { return YimMenu::NativeInvoker::Invoke<5891, void>(train, toggle); }
	FORCEINLINE void SET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int pearlescentColor, int wheelColor) { return YimMenu::NativeInvoker::Invoke<5892, void>(vehicle, pearlescentColor, wheelColor); }
	FORCEINLINE void GET_VEHICLE_EXTRA_COLOURS(Vehicle vehicle, int* pearlescentColor, int* wheelColor) { return YimMenu::NativeInvoker::Invoke<5893, void>(vehicle, pearlescentColor, wheelColor); }
	FORCEINLINE void SET_VEHICLE_EXTRA_COLOUR_5(Vehicle vehicle, int color) { return YimMenu::NativeInvoker::Invoke<5894, void>(vehicle, color); }
	FORCEINLINE void GET_VEHICLE_EXTRA_COLOUR_5(Vehicle vehicle, int* color) { return YimMenu::NativeInvoker::Invoke<5895, void>(vehicle, color); }
	FORCEINLINE void SET_VEHICLE_EXTRA_COLOUR_6(Vehicle vehicle, int color) { return YimMenu::NativeInvoker::Invoke<5896, void>(vehicle, color); }
	FORCEINLINE void GET_VEHICLE_EXTRA_COLOUR_6(Vehicle vehicle, int* color) { return YimMenu::NativeInvoker::Invoke<5897, void>(vehicle, color); }
	FORCEINLINE void STOP_ALL_GARAGE_ACTIVITY() { return YimMenu::NativeInvoker::Invoke<5898, void>(); }
	FORCEINLINE void SET_VEHICLE_FIXED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5899, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_DEFORMATION_FIXED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5900, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_CAN_ENGINE_MISSFIRE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5901, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_CAN_LEAK_OIL(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5902, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_CAN_LEAK_PETROL(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5903, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5904, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5905, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_VEHICLE_ENGINE_FIRES(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5906, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_LIMIT_SPEED_WHEN_PLAYER_INACTIVE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5907, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_STOP_INSTANTLY_WHEN_PLAYER_INACTIVE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5908, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_PRETEND_OCCUPANTS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5909, void>(vehicle, toggle); }
	FORCEINLINE void REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(float x1, float y1, float z1, float x2, float y2, float z2, Any p6) { return YimMenu::NativeInvoker::Invoke<5910, void>(x1, y1, z1, x2, y2, z2, p6); }
	FORCEINLINE void SET_VEHICLE_STEER_BIAS(Vehicle vehicle, float value) { return YimMenu::NativeInvoker::Invoke<5911, void>(vehicle, value); }
	FORCEINLINE bool IS_VEHICLE_EXTRA_TURNED_ON(Vehicle vehicle, int extraId) { return YimMenu::NativeInvoker::Invoke<5912, bool>(vehicle, extraId); }
	FORCEINLINE void SET_VEHICLE_EXTRA(Vehicle vehicle, int extraId, bool disable) { return YimMenu::NativeInvoker::Invoke<5913, void>(vehicle, extraId, disable); }
	FORCEINLINE bool DOES_EXTRA_EXIST(Vehicle vehicle, int extraId) { return YimMenu::NativeInvoker::Invoke<5914, bool>(vehicle, extraId); }
	FORCEINLINE bool IS_EXTRA_BROKEN_OFF(Vehicle vehicle, int extraId) { return YimMenu::NativeInvoker::Invoke<5915, bool>(vehicle, extraId); }
	FORCEINLINE void SET_CONVERTIBLE_ROOF(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5916, void>(vehicle, p1); }
	FORCEINLINE void LOWER_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyLower) { return YimMenu::NativeInvoker::Invoke<5917, void>(vehicle, instantlyLower); }
	FORCEINLINE void RAISE_CONVERTIBLE_ROOF(Vehicle vehicle, bool instantlyRaise) { return YimMenu::NativeInvoker::Invoke<5918, void>(vehicle, instantlyRaise); }
	FORCEINLINE int GET_CONVERTIBLE_ROOF_STATE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5919, int>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_A_CONVERTIBLE(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5920, bool>(vehicle, p1); }
	FORCEINLINE bool TRANSFORM_TO_SUBMARINE(Vehicle vehicle, bool noAnimation) { return YimMenu::NativeInvoker::Invoke<5921, bool>(vehicle, noAnimation); }
	FORCEINLINE void TRANSFORM_TO_CAR(Vehicle vehicle, bool noAnimation) { return YimMenu::NativeInvoker::Invoke<5922, void>(vehicle, noAnimation); }
	FORCEINLINE bool IS_VEHICLE_IN_SUBMARINE_MODE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5923, bool>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5924, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_DAMAGE(Vehicle vehicle, float xOffset, float yOffset, float zOffset, float damage, float radius, bool focusOnModel) { return YimMenu::NativeInvoker::Invoke<5925, void>(vehicle, xOffset, yOffset, zOffset, damage, radius, focusOnModel); }
	FORCEINLINE void SET_VEHICLE_OCCUPANTS_TAKE_EXPLOSIVE_DAMAGE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5926, void>(vehicle, toggle); }
	FORCEINLINE float GET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5927, float>(vehicle); }
	FORCEINLINE void SET_VEHICLE_ENGINE_HEALTH(Vehicle vehicle, float health) { return YimMenu::NativeInvoker::Invoke<5928, void>(vehicle, health); }
	FORCEINLINE void SET_PLANE_ENGINE_HEALTH(Vehicle vehicle, float health) { return YimMenu::NativeInvoker::Invoke<5929, void>(vehicle, health); }
	FORCEINLINE float GET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5930, float>(vehicle); }
	FORCEINLINE void SET_VEHICLE_PETROL_TANK_HEALTH(Vehicle vehicle, float health) { return YimMenu::NativeInvoker::Invoke<5931, void>(vehicle, health); }
	FORCEINLINE bool IS_VEHICLE_STUCK_TIMER_UP(Vehicle vehicle, int p1, int ms) { return YimMenu::NativeInvoker::Invoke<5932, bool>(vehicle, p1, ms); }
	FORCEINLINE void RESET_VEHICLE_STUCK_TIMER(Vehicle vehicle, int nullAttributes) { return YimMenu::NativeInvoker::Invoke<5933, void>(vehicle, nullAttributes); }
	FORCEINLINE bool IS_VEHICLE_DRIVEABLE(Vehicle vehicle, bool isOnFireCheck) { return YimMenu::NativeInvoker::Invoke<5934, bool>(vehicle, isOnFireCheck); }
	FORCEINLINE void SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(Vehicle vehicle, bool owned) { return YimMenu::NativeInvoker::Invoke<5935, void>(vehicle, owned); }
	FORCEINLINE void SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5936, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_BLIP_THROTTLE_RANDOMLY(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5937, void>(vehicle, p1); }
	FORCEINLINE void SET_POLICE_FOCUS_WILL_TRACK_VEHICLE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5938, void>(vehicle, toggle); }
	FORCEINLINE void START_VEHICLE_HORN(Vehicle vehicle, int duration, Hash mode, bool forever) { return YimMenu::NativeInvoker::Invoke<5939, void>(vehicle, duration, mode, forever); }
	FORCEINLINE void SET_VEHICLE_IN_CAR_MOD_SHOP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5940, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_HAS_STRONG_AXLES(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5941, void>(vehicle, toggle); }
	FORCEINLINE const char* GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<5942, const char*>(modelHash); }
	FORCEINLINE const char* GET_MAKE_NAME_FROM_VEHICLE_MODEL(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<5943, const char*>(modelHash); }
	FORCEINLINE Vector3 GET_VEHICLE_DEFORMATION_AT_POS(Vehicle vehicle, float offsetX, float offsetY, float offsetZ) { return YimMenu::NativeInvoker::Invoke<5944, Vector3>(vehicle, offsetX, offsetY, offsetZ); }
	FORCEINLINE void SET_VEHICLE_LIVERY(Vehicle vehicle, int livery) { return YimMenu::NativeInvoker::Invoke<5945, void>(vehicle, livery); }
	FORCEINLINE int GET_VEHICLE_LIVERY(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5946, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_LIVERY_COUNT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5947, int>(vehicle); }
	FORCEINLINE void SET_VEHICLE_LIVERY2(Vehicle vehicle, int livery) { return YimMenu::NativeInvoker::Invoke<5948, void>(vehicle, livery); }
	FORCEINLINE int GET_VEHICLE_LIVERY2(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5949, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_LIVERY2_COUNT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5950, int>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_WINDOW_INTACT(Vehicle vehicle, int windowIndex) { return YimMenu::NativeInvoker::Invoke<5951, bool>(vehicle, windowIndex); }
	FORCEINLINE bool ARE_ALL_VEHICLE_WINDOWS_INTACT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5952, bool>(vehicle); }
	FORCEINLINE bool ARE_ANY_VEHICLE_SEATS_FREE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5953, bool>(vehicle); }
	FORCEINLINE void RESET_VEHICLE_WHEELS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5954, void>(vehicle, toggle); }
	FORCEINLINE bool IS_HELI_PART_BROKEN(Vehicle vehicle, bool p1, bool p2, bool p3) { return YimMenu::NativeInvoker::Invoke<5955, bool>(vehicle, p1, p2, p3); }
	FORCEINLINE float GET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5956, float>(vehicle); }
	FORCEINLINE float GET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5957, float>(vehicle); }
	FORCEINLINE float GET_HELI_TAIL_BOOM_HEALTH(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5958, float>(vehicle); }
	FORCEINLINE void SET_HELI_MAIN_ROTOR_HEALTH(Vehicle vehicle, float health) { return YimMenu::NativeInvoker::Invoke<5959, void>(vehicle, health); }
	FORCEINLINE void SET_HELI_TAIL_ROTOR_HEALTH(Vehicle vehicle, float health) { return YimMenu::NativeInvoker::Invoke<5960, void>(vehicle, health); }
	FORCEINLINE bool SET_HELI_TAIL_BOOM_CAN_BREAK_OFF(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5961, bool>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_NAME_DEBUG(Vehicle vehicle, const char* name) { return YimMenu::NativeInvoker::Invoke<5962, void>(vehicle, name); }
	FORCEINLINE void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5963, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_EXPLODES_ON_EXPLOSION_DAMAGE_AT_ZERO_BODY_HEALTH(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5964, void>(vehicle, toggle); }
	FORCEINLINE void SET_ALLOW_VEHICLE_EXPLODES_ON_CONTACT(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5965, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_DISABLE_TOWING(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5966, void>(vehicle, toggle); }
	FORCEINLINE bool GET_VEHICLE_HAS_LANDING_GEAR(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5967, bool>(vehicle); }
	FORCEINLINE void CONTROL_LANDING_GEAR(Vehicle vehicle, int state) { return YimMenu::NativeInvoker::Invoke<5968, void>(vehicle, state); }
	FORCEINLINE int GET_LANDING_GEAR_STATE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5969, int>(vehicle); }
	FORCEINLINE bool IS_ANY_VEHICLE_NEAR_POINT(float x, float y, float z, float radius) { return YimMenu::NativeInvoker::Invoke<5970, bool>(x, y, z, radius); }
	FORCEINLINE void REQUEST_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5971, void>(vehicle); }
	FORCEINLINE void REMOVE_VEHICLE_HIGH_DETAIL_MODEL(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5972, void>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_HIGH_DETAIL(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5973, bool>(vehicle); }
	FORCEINLINE void REQUEST_VEHICLE_ASSET(Hash vehicleHash, int vehicleAsset) { return YimMenu::NativeInvoker::Invoke<5974, void>(vehicleHash, vehicleAsset); }
	FORCEINLINE bool HAS_VEHICLE_ASSET_LOADED(int vehicleAsset) { return YimMenu::NativeInvoker::Invoke<5975, bool>(vehicleAsset); }
	FORCEINLINE void REMOVE_VEHICLE_ASSET(int vehicleAsset) { return YimMenu::NativeInvoker::Invoke<5976, void>(vehicleAsset); }
	FORCEINLINE void SET_VEHICLE_TOW_TRUCK_ARM_POSITION(Vehicle vehicle, float position) { return YimMenu::NativeInvoker::Invoke<5977, void>(vehicle, position); }
	FORCEINLINE void ATTACH_VEHICLE_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle, bool rear, float hookOffsetX, float hookOffsetY, float hookOffsetZ) { return YimMenu::NativeInvoker::Invoke<5978, void>(towTruck, vehicle, rear, hookOffsetX, hookOffsetY, hookOffsetZ); }
	FORCEINLINE void DETACH_VEHICLE_FROM_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5979, void>(towTruck, vehicle); }
	FORCEINLINE bool DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5980, bool>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck, Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5981, bool>(towTruck, vehicle); }
	FORCEINLINE Entity GET_ENTITY_ATTACHED_TO_TOW_TRUCK(Vehicle towTruck) { return YimMenu::NativeInvoker::Invoke<5982, Entity>(towTruck); }
	FORCEINLINE Entity SET_VEHICLE_AUTOMATICALLY_ATTACHES(Vehicle vehicle, bool p1, Any p2) { return YimMenu::NativeInvoker::Invoke<5983, Entity>(vehicle, p1, p2); }
	FORCEINLINE void SET_VEHICLE_BULLDOZER_ARM_POSITION(Vehicle vehicle, float position, bool p2) { return YimMenu::NativeInvoker::Invoke<5984, void>(vehicle, position, p2); }
	FORCEINLINE void SET_VEHICLE_TANK_TURRET_POSITION(Vehicle vehicle, float position, bool p2) { return YimMenu::NativeInvoker::Invoke<5985, void>(vehicle, position, p2); }
	FORCEINLINE void SET_VEHICLE_TURRET_TARGET(Vehicle vehicle, bool p1, float x, float y, float z, bool p5) { return YimMenu::NativeInvoker::Invoke<5986, void>(vehicle, p1, x, y, z, p5); }
	FORCEINLINE void SET_VEHICLE_TANK_STATIONARY(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<5987, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_TURRET_SPEED_THIS_FRAME(Vehicle vehicle, float speed) { return YimMenu::NativeInvoker::Invoke<5988, void>(vehicle, speed); }
	FORCEINLINE void DISABLE_VEHICLE_TURRET_MOVEMENT_THIS_FRAME(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5989, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_FLIGHT_NOZZLE_POSITION(Vehicle vehicle, float angleRatio) { return YimMenu::NativeInvoker::Invoke<5990, void>(vehicle, angleRatio); }
	FORCEINLINE void SET_VEHICLE_FLIGHT_NOZZLE_POSITION_IMMEDIATE(Vehicle vehicle, float angle) { return YimMenu::NativeInvoker::Invoke<5991, void>(vehicle, angle); }
	FORCEINLINE float GET_VEHICLE_FLIGHT_NOZZLE_POSITION(Vehicle plane) { return YimMenu::NativeInvoker::Invoke<5992, float>(plane); }
	FORCEINLINE void SET_DISABLE_VERTICAL_FLIGHT_MODE_TRANSITION(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5993, void>(vehicle, toggle); }
	FORCEINLINE bool GENERATE_VEHICLE_CREATION_POS_FROM_PATHS(Vector3* outVec, Any p1, Vector3* outVec1, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8) { return YimMenu::NativeInvoker::Invoke<5994, bool>(outVec, p1, outVec1, p3, p4, p5, p6, p7, p8); }
	FORCEINLINE void SET_VEHICLE_BURNOUT(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5995, void>(vehicle, toggle); }
	FORCEINLINE bool IS_VEHICLE_IN_BURNOUT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<5996, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_REDUCE_GRIP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<5997, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_REDUCE_GRIP_LEVEL(Vehicle vehicle, int val) { return YimMenu::NativeInvoker::Invoke<5998, void>(vehicle, val); }
	FORCEINLINE void SET_VEHICLE_INDICATOR_LIGHTS(Vehicle vehicle, int turnSignal, bool toggle) { return YimMenu::NativeInvoker::Invoke<5999, void>(vehicle, turnSignal, toggle); }
	FORCEINLINE void SET_VEHICLE_BRAKE_LIGHTS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6000, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_TAIL_LIGHTS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6001, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_HANDBRAKE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6002, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_BRAKE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6003, void>(vehicle, toggle); }
	FORCEINLINE void INSTANTLY_FILL_VEHICLE_POPULATION() { return YimMenu::NativeInvoker::Invoke<6004, void>(); }
	FORCEINLINE bool HAS_INSTANT_FILL_VEHICLE_POPULATION_FINISHED() { return YimMenu::NativeInvoker::Invoke<6005, bool>(); }
	FORCEINLINE void NETWORK_ENABLE_EMPTY_CROWDING_VEHICLES_REMOVAL(bool toggle) { return YimMenu::NativeInvoker::Invoke<6006, void>(toggle); }
	FORCEINLINE void NETWORK_CAP_EMPTY_CROWDING_VEHICLES_REMOVAL(int p0) { return YimMenu::NativeInvoker::Invoke<6007, void>(p0); }
	FORCEINLINE bool GET_VEHICLE_TRAILER_VEHICLE(Vehicle vehicle, Vehicle* trailer) { return YimMenu::NativeInvoker::Invoke<6008, bool>(vehicle, trailer); }
	FORCEINLINE Vehicle _GET_VEHICLE_TRAILER_PARENT_VEHICLE(Vehicle trailer) { return YimMenu::NativeInvoker::Invoke<6009, Vehicle>(trailer); }
	FORCEINLINE void SET_VEHICLE_USES_LARGE_REAR_RAMP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6010, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_RUDDER_BROKEN(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6011, void>(vehicle, toggle); }
	FORCEINLINE void SET_CONVERTIBLE_ROOF_LATCH_STATE(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<6012, void>(vehicle, state); }
	FORCEINLINE float GET_VEHICLE_ESTIMATED_MAX_SPEED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6013, float>(vehicle); }
	FORCEINLINE float GET_VEHICLE_MAX_BRAKING(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6014, float>(vehicle); }
	FORCEINLINE float GET_VEHICLE_MAX_TRACTION(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6015, float>(vehicle); }
	FORCEINLINE float GET_VEHICLE_ACCELERATION(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6016, float>(vehicle); }
	FORCEINLINE float GET_VEHICLE_MODEL_ESTIMATED_MAX_SPEED(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6017, float>(modelHash); }
	FORCEINLINE float GET_VEHICLE_MODEL_MAX_BRAKING(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6018, float>(modelHash); }
	FORCEINLINE float GET_VEHICLE_MODEL_MAX_BRAKING_MAX_MODS(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6019, float>(modelHash); }
	FORCEINLINE float GET_VEHICLE_MODEL_MAX_TRACTION(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6020, float>(modelHash); }
	FORCEINLINE float GET_VEHICLE_MODEL_ACCELERATION(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6021, float>(modelHash); }
	FORCEINLINE float GET_VEHICLE_MODEL_ACCELERATION_MAX_MODS(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6022, float>(modelHash); }
	FORCEINLINE float GET_FLYING_VEHICLE_MODEL_AGILITY(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6023, float>(modelHash); }
	FORCEINLINE float GET_BOAT_VEHICLE_MODEL_AGILITY(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6024, float>(modelHash); }
	FORCEINLINE float GET_VEHICLE_CLASS_ESTIMATED_MAX_SPEED(int vehicleClass) { return YimMenu::NativeInvoker::Invoke<6025, float>(vehicleClass); }
	FORCEINLINE float GET_VEHICLE_CLASS_MAX_TRACTION(int vehicleClass) { return YimMenu::NativeInvoker::Invoke<6026, float>(vehicleClass); }
	FORCEINLINE float GET_VEHICLE_CLASS_MAX_AGILITY(int vehicleClass) { return YimMenu::NativeInvoker::Invoke<6027, float>(vehicleClass); }
	FORCEINLINE float GET_VEHICLE_CLASS_MAX_ACCELERATION(int vehicleClass) { return YimMenu::NativeInvoker::Invoke<6028, float>(vehicleClass); }
	FORCEINLINE float GET_VEHICLE_CLASS_MAX_BRAKING(int vehicleClass) { return YimMenu::NativeInvoker::Invoke<6029, float>(vehicleClass); }
	FORCEINLINE int ADD_ROAD_NODE_SPEED_ZONE(float x, float y, float z, float radius, float speed, bool p5) { return YimMenu::NativeInvoker::Invoke<6030, int>(x, y, z, radius, speed, p5); }
	FORCEINLINE bool REMOVE_ROAD_NODE_SPEED_ZONE(int speedzone) { return YimMenu::NativeInvoker::Invoke<6031, bool>(speedzone); }
	FORCEINLINE void OPEN_BOMB_BAY_DOORS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6032, void>(vehicle); }
	FORCEINLINE void CLOSE_BOMB_BAY_DOORS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6033, void>(vehicle); }
	FORCEINLINE bool GET_ARE_BOMB_BAY_DOORS_OPEN(Vehicle aircraft) { return YimMenu::NativeInvoker::Invoke<6034, bool>(aircraft); }
	FORCEINLINE bool IS_VEHICLE_SEARCHLIGHT_ON(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6035, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_SEARCHLIGHT(Vehicle heli, bool toggle, bool canBeUsedByAI) { return YimMenu::NativeInvoker::Invoke<6036, void>(heli, toggle, canBeUsedByAI); }
	FORCEINLINE bool DOES_VEHICLE_HAVE_SEARCHLIGHT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6037, bool>(vehicle); }
	FORCEINLINE bool IS_ENTRY_POINT_FOR_SEAT_CLEAR(Ped ped, Vehicle vehicle, int seatIndex, bool side, bool onEnter) { return YimMenu::NativeInvoker::Invoke<6038, bool>(ped, vehicle, seatIndex, side, onEnter); }
	FORCEINLINE Vector3 GET_ENTRY_POINT_POSITION(Vehicle vehicle, int doorId) { return YimMenu::NativeInvoker::Invoke<6039, Vector3>(vehicle, doorId); }
	FORCEINLINE bool CAN_SHUFFLE_SEAT(Vehicle vehicle, int seatIndex) { return YimMenu::NativeInvoker::Invoke<6040, bool>(vehicle, seatIndex); }
	FORCEINLINE int GET_NUM_MOD_KITS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6041, int>(vehicle); }
	FORCEINLINE void SET_VEHICLE_MOD_KIT(Vehicle vehicle, int modKit) { return YimMenu::NativeInvoker::Invoke<6042, void>(vehicle, modKit); }
	FORCEINLINE int GET_VEHICLE_MOD_KIT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6043, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_MOD_KIT_TYPE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6044, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_WHEEL_TYPE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6045, int>(vehicle); }
	FORCEINLINE void SET_VEHICLE_WHEEL_TYPE(Vehicle vehicle, int WheelType) { return YimMenu::NativeInvoker::Invoke<6046, void>(vehicle, WheelType); }
	FORCEINLINE int GET_NUM_MOD_COLORS(int paintType, bool p1) { return YimMenu::NativeInvoker::Invoke<6047, int>(paintType, p1); }
	FORCEINLINE void SET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int paintType, int color, int pearlescentColor) { return YimMenu::NativeInvoker::Invoke<6048, void>(vehicle, paintType, color, pearlescentColor); }
	FORCEINLINE void SET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int paintType, int color) { return YimMenu::NativeInvoker::Invoke<6049, void>(vehicle, paintType, color); }
	FORCEINLINE void GET_VEHICLE_MOD_COLOR_1(Vehicle vehicle, int* paintType, int* color, int* pearlescentColor) { return YimMenu::NativeInvoker::Invoke<6050, void>(vehicle, paintType, color, pearlescentColor); }
	FORCEINLINE void GET_VEHICLE_MOD_COLOR_2(Vehicle vehicle, int* paintType, int* color) { return YimMenu::NativeInvoker::Invoke<6051, void>(vehicle, paintType, color); }
	FORCEINLINE const char* GET_VEHICLE_MOD_COLOR_1_NAME(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6052, const char*>(vehicle, p1); }
	FORCEINLINE const char* GET_VEHICLE_MOD_COLOR_2_NAME(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6053, const char*>(vehicle); }
	FORCEINLINE bool HAVE_VEHICLE_MODS_STREAMED_IN(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6054, bool>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_MOD_GEN9_EXCLUSIVE(Vehicle vehicle, int modType, int modIndex) { return YimMenu::NativeInvoker::Invoke<6055, bool>(vehicle, modType, modIndex); }
	FORCEINLINE void SET_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex, bool customTires) { return YimMenu::NativeInvoker::Invoke<6056, void>(vehicle, modType, modIndex, customTires); }
	FORCEINLINE int GET_VEHICLE_MOD(Vehicle vehicle, int modType) { return YimMenu::NativeInvoker::Invoke<6057, int>(vehicle, modType); }
	FORCEINLINE int GET_VEHICLE_MOD_VARIATION(Vehicle vehicle, int modType) { return YimMenu::NativeInvoker::Invoke<6058, int>(vehicle, modType); }
	FORCEINLINE int GET_NUM_VEHICLE_MODS(Vehicle vehicle, int modType) { return YimMenu::NativeInvoker::Invoke<6059, int>(vehicle, modType); }
	FORCEINLINE void REMOVE_VEHICLE_MOD(Vehicle vehicle, int modType) { return YimMenu::NativeInvoker::Invoke<6060, void>(vehicle, modType); }
	FORCEINLINE void TOGGLE_VEHICLE_MOD(Vehicle vehicle, int modType, bool toggle) { return YimMenu::NativeInvoker::Invoke<6061, void>(vehicle, modType, toggle); }
	FORCEINLINE bool IS_TOGGLE_MOD_ON(Vehicle vehicle, int modType) { return YimMenu::NativeInvoker::Invoke<6062, bool>(vehicle, modType); }
	FORCEINLINE const char* GET_MOD_TEXT_LABEL(Vehicle vehicle, int modType, int modValue) { return YimMenu::NativeInvoker::Invoke<6063, const char*>(vehicle, modType, modValue); }
	FORCEINLINE const char* GET_MOD_SLOT_NAME(Vehicle vehicle, int modType) { return YimMenu::NativeInvoker::Invoke<6064, const char*>(vehicle, modType); }
	FORCEINLINE const char* GET_LIVERY_NAME(Vehicle vehicle, int liveryIndex) { return YimMenu::NativeInvoker::Invoke<6065, const char*>(vehicle, liveryIndex); }
	FORCEINLINE int GET_VEHICLE_MOD_MODIFIER_VALUE(Vehicle vehicle, int modType, int modIndex) { return YimMenu::NativeInvoker::Invoke<6066, int>(vehicle, modType, modIndex); }
	FORCEINLINE Hash GET_VEHICLE_MOD_IDENTIFIER_HASH(Vehicle vehicle, int modType, int modIndex) { return YimMenu::NativeInvoker::Invoke<6067, Hash>(vehicle, modType, modIndex); }
	FORCEINLINE void PRELOAD_VEHICLE_MOD(Vehicle vehicle, int modType, int modIndex) { return YimMenu::NativeInvoker::Invoke<6068, void>(vehicle, modType, modIndex); }
	FORCEINLINE bool HAS_PRELOAD_MODS_FINISHED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6069, bool>(vehicle); }
	FORCEINLINE void RELEASE_PRELOAD_MODS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6070, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int r, int g, int b) { return YimMenu::NativeInvoker::Invoke<6071, void>(vehicle, r, g, b); }
	FORCEINLINE void GET_VEHICLE_TYRE_SMOKE_COLOR(Vehicle vehicle, int* r, int* g, int* b) { return YimMenu::NativeInvoker::Invoke<6072, void>(vehicle, r, g, b); }
	FORCEINLINE void SET_VEHICLE_WINDOW_TINT(Vehicle vehicle, int tint) { return YimMenu::NativeInvoker::Invoke<6073, void>(vehicle, tint); }
	FORCEINLINE int GET_VEHICLE_WINDOW_TINT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6074, int>(vehicle); }
	FORCEINLINE int GET_NUM_VEHICLE_WINDOW_TINTS() { return YimMenu::NativeInvoker::Invoke<6075, int>(); }
	FORCEINLINE void GET_VEHICLE_COLOR(Vehicle vehicle, int* r, int* g, int* b) { return YimMenu::NativeInvoker::Invoke<6076, void>(vehicle, r, g, b); }
	FORCEINLINE int GET_VEHICLE_COLOURS_WHICH_CAN_BE_SET(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6077, int>(vehicle); }
	FORCEINLINE Hash GET_VEHICLE_CAUSE_OF_DESTRUCTION(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6078, Hash>(vehicle); }
	FORCEINLINE void OVERRIDE_PLANE_DAMAGE_THREHSOLD(Vehicle vehicle, float health) { return YimMenu::NativeInvoker::Invoke<6079, void>(vehicle, health); }
	FORCEINLINE bool GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6080, bool>(vehicle); }
	FORCEINLINE bool GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6081, bool>(vehicle); }
	FORCEINLINE bool GET_BOTH_VEHICLE_HEADLIGHTS_DAMAGED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6082, bool>(vehicle); }
	FORCEINLINE void MODIFY_VEHICLE_TOP_SPEED(Vehicle vehicle, float value) { return YimMenu::NativeInvoker::Invoke<6083, void>(vehicle, value); }
	FORCEINLINE void SET_VEHICLE_MAX_SPEED(Vehicle vehicle, float speed) { return YimMenu::NativeInvoker::Invoke<6084, void>(vehicle, speed); }
	FORCEINLINE void SET_VEHICLE_STAYS_FROZEN_WHEN_CLEANED_UP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6085, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_ACT_AS_IF_HIGH_SPEED_FOR_FRAG_SMASHING(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6086, void>(vehicle, p1); }
	FORCEINLINE void SET_PEDS_CAN_FALL_OFF_THIS_VEHICLE_FROM_LARGE_FALL_DAMAGE(Vehicle vehicle, bool toggle, float p2) { return YimMenu::NativeInvoker::Invoke<6087, void>(vehicle, toggle, p2); }
	FORCEINLINE int ADD_VEHICLE_COMBAT_ANGLED_AVOIDANCE_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6) { return YimMenu::NativeInvoker::Invoke<6088, int>(p0, p1, p2, p3, p4, p5, p6); }
	FORCEINLINE void REMOVE_VEHICLE_COMBAT_AVOIDANCE_AREA(int p0) { return YimMenu::NativeInvoker::Invoke<6089, void>(p0); }
	FORCEINLINE bool IS_ANY_PED_RAPPELLING_FROM_HELI(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6090, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_CHEAT_POWER_INCREASE(Vehicle vehicle, float value) { return YimMenu::NativeInvoker::Invoke<6091, void>(vehicle, value); }
	FORCEINLINE void SET_VEHICLE_INFLUENCES_WANTED_LEVEL(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<6092, void>(p0, p1); }
	FORCEINLINE void SET_VEHICLE_IS_WANTED(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<6093, void>(vehicle, state); }
	FORCEINLINE void SWING_BOAT_BOOM_TO_RATIO(Vehicle vehicle, float ratio) { return YimMenu::NativeInvoker::Invoke<6094, void>(vehicle, ratio); }
	FORCEINLINE void SWING_BOAT_BOOM_FREELY(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6095, void>(vehicle, toggle); }
	FORCEINLINE void ALLOW_BOAT_BOOM_TO_ANIMATE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6096, void>(vehicle, toggle); }
	FORCEINLINE float GET_BOAT_BOOM_POSITION_RATIO(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6097, float>(vehicle); }
	FORCEINLINE void DISABLE_PLANE_AILERON(Vehicle vehicle, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<6098, void>(vehicle, p1, p2); }
	FORCEINLINE bool GET_IS_VEHICLE_ENGINE_RUNNING(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6099, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_USE_ALTERNATE_HANDLING(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6100, void>(vehicle, toggle); }
	FORCEINLINE void SET_BIKE_ON_STAND(Vehicle vehicle, float x, float y) { return YimMenu::NativeInvoker::Invoke<6101, void>(vehicle, x, y); }
	FORCEINLINE void SET_VEHICLE_NOT_STEALABLE_AMBIENTLY(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6102, void>(vehicle, p1); }
	FORCEINLINE void LOCK_DOORS_WHEN_NO_LONGER_NEEDED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6103, void>(vehicle); }
	FORCEINLINE void SET_LAST_DRIVEN_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6104, void>(vehicle); }
	FORCEINLINE Vehicle GET_LAST_DRIVEN_VEHICLE() { return YimMenu::NativeInvoker::Invoke<6105, Vehicle>(); }
	FORCEINLINE void CLEAR_LAST_DRIVEN_VEHICLE() { return YimMenu::NativeInvoker::Invoke<6106, void>(); }
	FORCEINLINE void SET_VEHICLE_HAS_BEEN_DRIVEN_FLAG(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6107, void>(vehicle, toggle); }
	FORCEINLINE void SET_TASK_VEHICLE_GOTO_PLANE_MIN_HEIGHT_ABOVE_TERRAIN(Vehicle plane, int height) { return YimMenu::NativeInvoker::Invoke<6108, void>(plane, height); }
	FORCEINLINE void SET_VEHICLE_LOD_MULTIPLIER(Vehicle vehicle, float multiplier) { return YimMenu::NativeInvoker::Invoke<6109, void>(vehicle, multiplier); }
	FORCEINLINE void SET_VEHICLE_CAN_SAVE_IN_GARAGE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6110, void>(vehicle, toggle); }
	FORCEINLINE int GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6111, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6112, int>(vehicle); }
	FORCEINLINE void SET_FORCE_VEHICLE_ENGINE_DAMAGE_BY_BULLET(Any p0, bool p1) { return YimMenu::NativeInvoker::Invoke<6113, void>(p0, p1); }
	FORCEINLINE void SET_VEHICLE_GENERATES_ENGINE_SHOCKING_EVENTS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6114, void>(vehicle, toggle); }
	FORCEINLINE void COPY_VEHICLE_DAMAGES(Vehicle sourceVehicle, Vehicle targetVehicle) { return YimMenu::NativeInvoker::Invoke<6115, void>(sourceVehicle, targetVehicle); }
	FORCEINLINE void DISABLE_VEHICLE_EXPLOSION_BREAK_OFF_PARTS() { return YimMenu::NativeInvoker::Invoke<6116, void>(); }
	FORCEINLINE void SET_LIGHTS_CUTOFF_DISTANCE_TWEAK(float distance) { return YimMenu::NativeInvoker::Invoke<6117, void>(distance); }
	FORCEINLINE void SET_VEHICLE_SHOOT_AT_TARGET(Ped driver, Entity entity, float xTarget, float yTarget, float zTarget) { return YimMenu::NativeInvoker::Invoke<6118, void>(driver, entity, xTarget, yTarget, zTarget); }
	FORCEINLINE bool GET_VEHICLE_LOCK_ON_TARGET(Vehicle vehicle, Entity* entity) { return YimMenu::NativeInvoker::Invoke<6119, bool>(vehicle, entity); }
	FORCEINLINE void SET_FORCE_HD_VEHICLE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6120, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_CUSTOM_PATH_NODE_STREAMING_RADIUS(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<6121, void>(vehicle, p1); }
	FORCEINLINE int GET_VEHICLE_PLATE_TYPE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6122, int>(vehicle); }
	FORCEINLINE void TRACK_VEHICLE_VISIBILITY(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6123, void>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_VISIBLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6124, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_GRAVITY(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6125, void>(vehicle, toggle); }
	FORCEINLINE void SET_ENABLE_VEHICLE_SLIPSTREAMING(bool toggle) { return YimMenu::NativeInvoker::Invoke<6126, void>(toggle); }
	FORCEINLINE void SET_VEHICLE_SLIPSTREAMING_SHOULD_TIME_OUT(bool toggle) { return YimMenu::NativeInvoker::Invoke<6127, void>(toggle); }
	FORCEINLINE float GET_VEHICLE_CURRENT_TIME_IN_SLIP_STREAM(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6128, float>(vehicle); }
	FORCEINLINE bool IS_VEHICLE_PRODUCING_SLIP_STREAM(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6129, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_INACTIVE_DURING_PLAYBACK(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6130, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_ACTIVE_DURING_PLAYBACK(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6131, void>(vehicle, toggle); }
	FORCEINLINE bool IS_VEHICLE_SPRAYABLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6132, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_ENGINE_CAN_DEGRADE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6133, void>(vehicle, toggle); }
	FORCEINLINE void DISABLE_VEHCILE_DYNAMIC_AMBIENT_SCALES(Vehicle vehicle, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<6134, void>(vehicle, p1, p2); }
	FORCEINLINE void ENABLE_VEHICLE_DYNAMIC_AMBIENT_SCALES(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6135, void>(vehicle); }
	FORCEINLINE bool IS_PLANE_LANDING_GEAR_INTACT(Vehicle plane) { return YimMenu::NativeInvoker::Invoke<6136, bool>(plane); }
	FORCEINLINE bool ARE_PLANE_PROPELLERS_INTACT(Vehicle plane) { return YimMenu::NativeInvoker::Invoke<6137, bool>(plane); }
	FORCEINLINE bool SET_PLANE_PROPELLER_HEALTH(Vehicle plane, float health) { return YimMenu::NativeInvoker::Invoke<6138, bool>(plane, health); }
	FORCEINLINE void SET_VEHICLE_CAN_DEFORM_WHEELS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6139, void>(vehicle, toggle); }
	FORCEINLINE bool IS_VEHICLE_STOLEN(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6140, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_IS_STOLEN(Vehicle vehicle, bool isStolen) { return YimMenu::NativeInvoker::Invoke<6141, void>(vehicle, isStolen); }
	FORCEINLINE void SET_PLANE_TURBULENCE_MULTIPLIER(Vehicle vehicle, float multiplier) { return YimMenu::NativeInvoker::Invoke<6142, void>(vehicle, multiplier); }
	FORCEINLINE bool ARE_WINGS_OF_PLANE_INTACT(Vehicle plane) { return YimMenu::NativeInvoker::Invoke<6143, bool>(plane); }
	FORCEINLINE void ALLOW_AMBIENT_VEHICLES_TO_AVOID_ADVERSE_CONDITIONS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6144, void>(vehicle); }
	FORCEINLINE void DETACH_VEHICLE_FROM_CARGOBOB(Vehicle vehicle, Vehicle cargobob) { return YimMenu::NativeInvoker::Invoke<6145, void>(vehicle, cargobob); }
	FORCEINLINE bool DETACH_VEHICLE_FROM_ANY_CARGOBOB(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6146, bool>(vehicle); }
	FORCEINLINE bool DETACH_ENTITY_FROM_CARGOBOB(Vehicle cargobob, Entity entity) { return YimMenu::NativeInvoker::Invoke<6147, bool>(cargobob, entity); }
	FORCEINLINE bool IS_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob, Vehicle vehicleAttached) { return YimMenu::NativeInvoker::Invoke<6148, bool>(cargobob, vehicleAttached); }
	FORCEINLINE Vehicle GET_VEHICLE_ATTACHED_TO_CARGOBOB(Vehicle cargobob) { return YimMenu::NativeInvoker::Invoke<6149, Vehicle>(cargobob); }
	FORCEINLINE Entity GET_ENTITY_ATTACHED_TO_CARGOBOB(Any p0) { return YimMenu::NativeInvoker::Invoke<6150, Entity>(p0); }
	FORCEINLINE void ATTACH_VEHICLE_TO_CARGOBOB(Vehicle vehicle, Vehicle cargobob, int p2, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<6151, void>(vehicle, cargobob, p2, x, y, z); }
	FORCEINLINE void ATTACH_ENTITY_TO_CARGOBOB(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5) { return YimMenu::NativeInvoker::Invoke<6152, void>(p0, p1, p2, p3, p4, p5); }
	FORCEINLINE void SET_CARGOBOB_FORCE_DONT_DETACH_VEHICLE(Vehicle cargobob, bool toggle) { return YimMenu::NativeInvoker::Invoke<6153, void>(cargobob, toggle); }
	FORCEINLINE void SET_CARGOBOB_EXCLUDE_FROM_PICKUP_ENTITY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6154, void>(p0, p1); }
	FORCEINLINE bool CAN_CARGOBOB_PICK_UP_ENTITY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6155, bool>(p0, p1); }
	FORCEINLINE Vector3 GET_ATTACHED_PICK_UP_HOOK_POSITION(Vehicle cargobob) { return YimMenu::NativeInvoker::Invoke<6156, Vector3>(cargobob); }
	FORCEINLINE bool DOES_CARGOBOB_HAVE_PICK_UP_ROPE(Vehicle cargobob) { return YimMenu::NativeInvoker::Invoke<6157, bool>(cargobob); }
	FORCEINLINE void CREATE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob, int state) { return YimMenu::NativeInvoker::Invoke<6158, void>(cargobob, state); }
	FORCEINLINE void REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(Vehicle cargobob) { return YimMenu::NativeInvoker::Invoke<6159, void>(cargobob); }
	FORCEINLINE void SET_PICKUP_ROPE_LENGTH_FOR_CARGOBOB(Vehicle cargobob, float length1, float length2, bool p3) { return YimMenu::NativeInvoker::Invoke<6160, void>(cargobob, length1, length2, p3); }
	FORCEINLINE void SET_PICKUP_ROPE_LENGTH_WITHOUT_CREATING_ROPE_FOR_CARGOBOB(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<6161, void>(p0, p1, p2); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_ROPE_DAMPING_MULTIPLIER(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6162, void>(p0, p1); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_ROPE_TYPE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6163, void>(p0, p1); }
	FORCEINLINE bool DOES_CARGOBOB_HAVE_PICKUP_MAGNET(Vehicle cargobob) { return YimMenu::NativeInvoker::Invoke<6164, bool>(cargobob); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(Vehicle cargobob, bool isActive) { return YimMenu::NativeInvoker::Invoke<6165, void>(cargobob, isActive); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(Vehicle cargobob, float strength) { return YimMenu::NativeInvoker::Invoke<6166, void>(cargobob, strength); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_FALLOFF(Vehicle cargobob, float p1) { return YimMenu::NativeInvoker::Invoke<6167, void>(cargobob, p1); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_REDUCED_STRENGTH(Vehicle cargobob, float p1) { return YimMenu::NativeInvoker::Invoke<6168, void>(cargobob, p1); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_REDUCED_FALLOFF(Vehicle cargobob, float p1) { return YimMenu::NativeInvoker::Invoke<6169, void>(cargobob, p1); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_PULL_STRENGTH(Vehicle cargobob, float p1) { return YimMenu::NativeInvoker::Invoke<6170, void>(cargobob, p1); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_PULL_ROPE_LENGTH(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<6171, void>(vehicle, p1); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_SET_TARGETED_MODE(Vehicle vehicle, Vehicle cargobob) { return YimMenu::NativeInvoker::Invoke<6172, void>(vehicle, cargobob); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_SET_AMBIENT_MODE(Vehicle vehicle, bool p1, bool p2) { return YimMenu::NativeInvoker::Invoke<6173, void>(vehicle, p1, p2); }
	FORCEINLINE void SET_CARGOBOB_PICKUP_MAGNET_ENSURE_PICKUP_ENTITY_UPRIGHT(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6174, void>(vehicle, p1); }
	FORCEINLINE bool DOES_VEHICLE_HAVE_WEAPONS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6175, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_WILL_TELL_OTHERS_TO_HURRY(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6176, void>(vehicle, p1); }
	FORCEINLINE void DISABLE_VEHICLE_WEAPON(bool disabled, Hash weaponHash, Vehicle vehicle, Ped owner) { return YimMenu::NativeInvoker::Invoke<6177, void>(disabled, weaponHash, vehicle, owner); }
	FORCEINLINE bool IS_VEHICLE_WEAPON_DISABLED(Hash weaponHash, Vehicle vehicle, Ped owner) { return YimMenu::NativeInvoker::Invoke<6178, bool>(weaponHash, vehicle, owner); }
	FORCEINLINE void SET_VEHICLE_USED_FOR_PILOT_SCHOOL(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6179, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_ACTIVE_FOR_PED_NAVIGATION(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6180, void>(vehicle, toggle); }
	FORCEINLINE int GET_VEHICLE_CLASS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6181, int>(vehicle); }
	FORCEINLINE int GET_VEHICLE_CLASS_FROM_NAME(Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6182, int>(modelHash); }
	FORCEINLINE void SET_PLAYERS_LAST_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6183, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6184, void>(vehicle, toggle); }
	FORCEINLINE void SET_AIRCRAFT_PILOT_SKILL_NOISE_SCALAR(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<6185, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_DROPS_MONEY_WHEN_BLOWN_UP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6186, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_KEEP_ENGINE_ON_WHEN_ABANDONED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6187, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_IMPATIENCE_TIMER(Vehicle vehicle, Any p1) { return YimMenu::NativeInvoker::Invoke<6188, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_HANDLING_OVERRIDE(Vehicle vehicle, Hash hash) { return YimMenu::NativeInvoker::Invoke<6189, void>(vehicle, hash); }
	FORCEINLINE void SET_VEHICLE_EXTENDED_REMOVAL_RANGE(Vehicle vehicle, int range) { return YimMenu::NativeInvoker::Invoke<6190, void>(vehicle, range); }
	FORCEINLINE void SET_VEHICLE_STEERING_BIAS_SCALAR(Any p0, float p1) { return YimMenu::NativeInvoker::Invoke<6191, void>(p0, p1); }
	FORCEINLINE void SET_HELI_CONTROL_LAGGING_RATE_SCALAR(Vehicle helicopter, float multiplier) { return YimMenu::NativeInvoker::Invoke<6192, void>(helicopter, multiplier); }
	FORCEINLINE void SET_VEHICLE_FRICTION_OVERRIDE(Vehicle vehicle, float friction) { return YimMenu::NativeInvoker::Invoke<6193, void>(vehicle, friction); }
	FORCEINLINE void SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6194, void>(vehicle, toggle); }
	FORCEINLINE bool ARE_PLANE_CONTROL_PANELS_INTACT(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6195, bool>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_CEILING_HEIGHT(Vehicle vehicle, float height) { return YimMenu::NativeInvoker::Invoke<6196, void>(vehicle, height); }
	FORCEINLINE void SET_VEHICLE_NO_EXPLOSION_DAMAGE_FROM_DRIVER(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6197, void>(vehicle, toggle); }
	FORCEINLINE void CLEAR_VEHICLE_ROUTE_HISTORY(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6198, void>(vehicle); }
	FORCEINLINE Vehicle DOES_VEHICLE_EXIST_WITH_DECORATOR(const char* decorator) { return YimMenu::NativeInvoker::Invoke<6199, Vehicle>(decorator); }
	FORCEINLINE void SET_VEHICLE_AI_CAN_USE_EXCLUSIVE_SEATS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6200, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_EXCLUSIVE_DRIVER(Vehicle vehicle, Ped ped, int index) { return YimMenu::NativeInvoker::Invoke<6201, void>(vehicle, ped, index); }
	FORCEINLINE bool IS_PED_EXCLUSIVE_DRIVER_OF_VEHICLE(Ped ped, Vehicle vehicle, int* outIndex) { return YimMenu::NativeInvoker::Invoke<6202, bool>(ped, vehicle, outIndex); }
	FORCEINLINE void DISABLE_INDIVIDUAL_PLANE_PROPELLER(Vehicle vehicle, int propeller) { return YimMenu::NativeInvoker::Invoke<6203, void>(vehicle, propeller); }
	FORCEINLINE void SET_VEHICLE_FORCE_AFTERBURNER(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6204, void>(vehicle, toggle); }
	FORCEINLINE void SET_DONT_PROCESS_VEHICLE_GLASS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6205, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_WANTED_CONES_RESPONSE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6206, void>(vehicle, toggle); }
	FORCEINLINE void SET_USE_DESIRED_Z_CRUISE_SPEED_FOR_LANDING(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6207, void>(vehicle, toggle); }
	FORCEINLINE void SET_ARRIVE_DISTANCE_OVERRIDE_FOR_VEHICLE_PERSUIT_ATTACK(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<6208, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_READY_FOR_CLEANUP(Any p0) { return YimMenu::NativeInvoker::Invoke<6209, void>(p0); }
	FORCEINLINE void SET_DISTANT_CARS_ENABLED(bool toggle) { return YimMenu::NativeInvoker::Invoke<6210, void>(toggle); }
	FORCEINLINE void SET_VEHICLE_NEON_COLOUR(Vehicle vehicle, int r, int g, int b) { return YimMenu::NativeInvoker::Invoke<6211, void>(vehicle, r, g, b); }
	FORCEINLINE void SET_VEHICLE_NEON_INDEX_COLOUR(Vehicle vehicle, int index) { return YimMenu::NativeInvoker::Invoke<6212, void>(vehicle, index); }
	FORCEINLINE void GET_VEHICLE_NEON_COLOUR(Vehicle vehicle, int* r, int* g, int* b) { return YimMenu::NativeInvoker::Invoke<6213, void>(vehicle, r, g, b); }
	FORCEINLINE void SET_VEHICLE_NEON_ENABLED(Vehicle vehicle, int index, bool toggle) { return YimMenu::NativeInvoker::Invoke<6214, void>(vehicle, index, toggle); }
	FORCEINLINE bool GET_VEHICLE_NEON_ENABLED(Vehicle vehicle, int index) { return YimMenu::NativeInvoker::Invoke<6215, bool>(vehicle, index); }
	FORCEINLINE void SET_AMBIENT_VEHICLE_NEON_ENABLED(bool p0) { return YimMenu::NativeInvoker::Invoke<6216, void>(p0); }
	FORCEINLINE void SUPPRESS_NEONS_ON_VEHICLE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6217, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_SUPERDUMMY(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6218, void>(vehicle, p1); }
	FORCEINLINE void REQUEST_VEHICLE_DIAL(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6219, void>(vehicle); }
	FORCEINLINE float GET_VEHICLE_BODY_HEALTH(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6220, float>(vehicle); }
	FORCEINLINE void SET_VEHICLE_BODY_HEALTH(Vehicle vehicle, float value) { return YimMenu::NativeInvoker::Invoke<6221, void>(vehicle, value); }
	FORCEINLINE void GET_VEHICLE_SIZE(Vehicle vehicle, Vector3* out1, Vector3* out2) { return YimMenu::NativeInvoker::Invoke<6222, void>(vehicle, out1, out2); }
	FORCEINLINE float GET_FAKE_SUSPENSION_LOWERING_AMOUNT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6223, float>(vehicle); }
	FORCEINLINE void SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER(float multiplier) { return YimMenu::NativeInvoker::Invoke<6224, void>(multiplier); }
	FORCEINLINE int GET_NUMBER_OF_VEHICLE_DOORS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6225, int>(vehicle); }
	FORCEINLINE void SET_HYDRAULICS_CONTROL(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6226, void>(vehicle, toggle); }
	FORCEINLINE void SET_CAN_ADJUST_GROUND_CLEARANCE(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6227, void>(vehicle, p1); }
	FORCEINLINE float GET_VEHICLE_HEALTH_PERCENTAGE(Vehicle vehicle, float maxEngineHealth, float maxPetrolTankHealth, float maxBodyHealth, float maxMainRotorHealth, float maxTailRotorHealth, float maxUnkHealth) { return YimMenu::NativeInvoker::Invoke<6228, float>(vehicle, maxEngineHealth, maxPetrolTankHealth, maxBodyHealth, maxMainRotorHealth, maxTailRotorHealth, maxUnkHealth); }
	FORCEINLINE bool GET_VEHICLE_IS_MERCENARY(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6229, bool>(vehicle); }
	FORCEINLINE void SET_VEHICLE_BROKEN_PARTS_DONT_AFFECT_AI_HANDLING(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6230, void>(vehicle, p1); }
	FORCEINLINE void SET_VEHICLE_KERS_ALLOWED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6231, void>(vehicle, toggle); }
	FORCEINLINE bool GET_VEHICLE_HAS_KERS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6232, bool>(vehicle); }
	FORCEINLINE void SET_PLANE_RESIST_TO_EXPLOSION(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6233, void>(vehicle, toggle); }
	FORCEINLINE void SET_HELI_RESIST_TO_EXPLOSION(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6234, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_BMX_EXTRA_TRICK_FORCES(Any p0) { return YimMenu::NativeInvoker::Invoke<6235, void>(p0); }
	FORCEINLINE void SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(Vehicle vehicle, int wheelId, float value) { return YimMenu::NativeInvoker::Invoke<6236, void>(vehicle, wheelId, value); }
	FORCEINLINE float GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(Vehicle vehicle, int wheelId) { return YimMenu::NativeInvoker::Invoke<6237, float>(vehicle, wheelId); }
	FORCEINLINE void SET_CAN_USE_HYDRAULICS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6238, void>(vehicle, toggle); }
	FORCEINLINE void SET_HYDRAULIC_VEHICLE_STATE(Vehicle vehicle, int state) { return YimMenu::NativeInvoker::Invoke<6239, void>(vehicle, state); }
	FORCEINLINE void SET_HYDRAULIC_WHEEL_STATE(Vehicle vehicle, int wheelId, int state, float value, Any p4) { return YimMenu::NativeInvoker::Invoke<6240, void>(vehicle, wheelId, state, value, p4); }
	FORCEINLINE bool HAS_VEHICLE_PETROLTANK_SET_ON_FIRE_BY_ENTITY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6241, bool>(p0, p1); }
	FORCEINLINE void CLEAR_VEHICLE_PETROLTANK_FIRE_CULPRIT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6242, void>(vehicle); }
	FORCEINLINE void SET_VEHICLE_BOBBLEHEAD_VELOCITY(float x, float y, float p2) { return YimMenu::NativeInvoker::Invoke<6243, void>(x, y, p2); }
	FORCEINLINE bool GET_VEHICLE_IS_DUMMY(Any p0) { return YimMenu::NativeInvoker::Invoke<6244, bool>(p0); }
	FORCEINLINE bool SET_VEHICLE_DAMAGE_SCALE(Vehicle vehicle, float p1) { return YimMenu::NativeInvoker::Invoke<6245, bool>(vehicle, p1); }
	FORCEINLINE bool SET_VEHICLE_WEAPON_DAMAGE_SCALE(Vehicle vehicle, float multiplier) { return YimMenu::NativeInvoker::Invoke<6246, bool>(vehicle, multiplier); }
	FORCEINLINE bool SET_DISABLE_DAMAGE_WITH_PICKED_UP_ENTITY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6247, bool>(p0, p1); }
	FORCEINLINE void SET_VEHICLE_USES_MP_PLAYER_DAMAGE_MULTIPLIER(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6248, void>(p0, p1); }
	FORCEINLINE void SET_BIKE_EASY_TO_LAND(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6249, void>(vehicle, toggle); }
	FORCEINLINE void SET_INVERT_VEHICLE_CONTROLS(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<6250, void>(vehicle, state); }
	FORCEINLINE void SET_SPEED_BOOST_EFFECT_DISABLED(bool disabled) { return YimMenu::NativeInvoker::Invoke<6251, void>(disabled); }
	FORCEINLINE void SET_SLOW_DOWN_EFFECT_DISABLED(bool disabled) { return YimMenu::NativeInvoker::Invoke<6252, void>(disabled); }
	FORCEINLINE void SET_FORMATION_LEADER(Vehicle vehicle, float x, float y, float z, float p4) { return YimMenu::NativeInvoker::Invoke<6253, void>(vehicle, x, y, z, p4); }
	FORCEINLINE void RESET_FORMATION_LEADER() { return YimMenu::NativeInvoker::Invoke<6254, void>(); }
	FORCEINLINE bool GET_IS_BOAT_CAPSIZED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6255, bool>(vehicle); }
	FORCEINLINE void SET_ALLOW_RAMMING_SOOP_OR_RAMP(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6256, void>(p0, p1); }
	FORCEINLINE void SET_SCRIPT_RAMP_IMPULSE_SCALE(Vehicle vehicle, float impulseScale) { return YimMenu::NativeInvoker::Invoke<6257, void>(vehicle, impulseScale); }
	FORCEINLINE bool GET_IS_DOOR_VALID(Vehicle vehicle, int doorId) { return YimMenu::NativeInvoker::Invoke<6258, bool>(vehicle, doorId); }
	FORCEINLINE void SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(Vehicle vehicle, float seconds) { return YimMenu::NativeInvoker::Invoke<6259, void>(vehicle, seconds); }
	FORCEINLINE bool GET_HAS_ROCKET_BOOST(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6260, bool>(vehicle); }
	FORCEINLINE bool IS_ROCKET_BOOST_ACTIVE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6261, bool>(vehicle); }
	FORCEINLINE void SET_ROCKET_BOOST_ACTIVE(Vehicle vehicle, bool active) { return YimMenu::NativeInvoker::Invoke<6262, void>(vehicle, active); }
	FORCEINLINE bool GET_HAS_RETRACTABLE_WHEELS(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6263, bool>(vehicle); }
	FORCEINLINE bool GET_IS_WHEELS_RETRACTED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6264, bool>(vehicle); }
	FORCEINLINE void SET_WHEELS_EXTENDED_INSTANTLY(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6265, void>(vehicle); }
	FORCEINLINE void SET_WHEELS_RETRACTED_INSTANTLY(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6266, void>(vehicle); }
	FORCEINLINE bool GET_CAR_HAS_JUMP(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6267, bool>(vehicle); }
	FORCEINLINE void SET_USE_HIGHER_CAR_JUMP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6268, void>(vehicle, toggle); }
	FORCEINLINE void SET_CLEAR_FREEZE_WAITING_ON_COLLISION_ONCE_PLAYER_ENTERS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6269, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_WEAPON_RESTRICTED_AMMO(Vehicle vehicle, int weaponIndex, int capacity) { return YimMenu::NativeInvoker::Invoke<6270, void>(vehicle, weaponIndex, capacity); }
	FORCEINLINE int GET_VEHICLE_WEAPON_RESTRICTED_AMMO(Vehicle vehicle, int weaponIndex) { return YimMenu::NativeInvoker::Invoke<6271, int>(vehicle, weaponIndex); }
	FORCEINLINE bool GET_VEHICLE_HAS_PARACHUTE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6272, bool>(vehicle); }
	FORCEINLINE bool GET_VEHICLE_CAN_DEPLOY_PARACHUTE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6273, bool>(vehicle); }
	FORCEINLINE void VEHICLE_START_PARACHUTING(Vehicle vehicle, bool active) { return YimMenu::NativeInvoker::Invoke<6274, void>(vehicle, active); }
	FORCEINLINE bool IS_VEHICLE_PARACHUTE_DEPLOYED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6275, bool>(vehicle); }
	FORCEINLINE void VEHICLE_SET_RAMP_AND_RAMMING_CARS_TAKE_DAMAGE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6276, void>(vehicle, toggle); }
	FORCEINLINE void VEHICLE_SET_ENABLE_RAMP_CAR_SIDE_IMPULSE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6277, void>(p0, p1); }
	FORCEINLINE void VEHICLE_SET_ENABLE_NORMALISE_RAMP_CAR_VERTICAL_VELOCTIY(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6278, void>(p0, p1); }
	FORCEINLINE void VEHICLE_SET_JET_WASH_FORCE_ENABLED(Any p0) { return YimMenu::NativeInvoker::Invoke<6279, void>(p0); }
	FORCEINLINE void SET_VEHICLE_WEAPON_CAN_TARGET_OBJECTS(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6280, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_USE_BOOST_BUTTON_FOR_WHEEL_RETRACT(bool toggle) { return YimMenu::NativeInvoker::Invoke<6281, void>(toggle); }
	FORCEINLINE void VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE(Vehicle vehicle, Hash modelHash) { return YimMenu::NativeInvoker::Invoke<6282, void>(vehicle, modelHash); }
	FORCEINLINE void VEHICLE_SET_PARACHUTE_MODEL_TINT_INDEX(Vehicle vehicle, int textureVariation) { return YimMenu::NativeInvoker::Invoke<6283, void>(vehicle, textureVariation); }
	FORCEINLINE int VEHICLE_SET_OVERRIDE_EXTENABLE_SIDE_RATIO(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6284, int>(p0, p1); }
	FORCEINLINE int VEHICLE_SET_EXTENABLE_SIDE_TARGET_RATIO(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6285, int>(p0, p1); }
	FORCEINLINE int VEHICLE_SET_OVERRIDE_SIDE_RATIO(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6286, int>(p0, p1); }
	FORCEINLINE int GET_ALL_VEHICLES(Any* vehsStruct) { return YimMenu::NativeInvoker::Invoke<6287, int>(vehsStruct); }
	FORCEINLINE void SET_CARGOBOB_EXTA_PICKUP_RANGE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6288, void>(p0, p1); }
	FORCEINLINE void SET_OVERRIDE_VEHICLE_DOOR_TORQUE(Any p0, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<6289, void>(p0, p1, p2); }
	FORCEINLINE void SET_WHEELIE_ENABLED(Vehicle vehicle, bool enabled) { return YimMenu::NativeInvoker::Invoke<6290, void>(vehicle, enabled); }
	FORCEINLINE void SET_DISABLE_HELI_EXPLODE_FROM_BODY_DAMAGE(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6291, void>(p0, p1); }
	FORCEINLINE void SET_DISABLE_EXPLODE_FROM_BODY_DAMAGE_ON_COLLISION(Vehicle vehicle, float value) { return YimMenu::NativeInvoker::Invoke<6292, void>(vehicle, value); }
	FORCEINLINE void SET_TRAILER_ATTACHMENT_ENABLED(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6293, void>(p0, p1); }
	FORCEINLINE void SET_ROCKET_BOOST_FILL(Vehicle vehicle, float percentage) { return YimMenu::NativeInvoker::Invoke<6294, void>(vehicle, percentage); }
	FORCEINLINE void SET_GLIDER_ACTIVE(Vehicle vehicle, bool state) { return YimMenu::NativeInvoker::Invoke<6295, void>(vehicle, state); }
	FORCEINLINE void SET_SHOULD_RESET_TURRET_IN_SCRIPTED_CAMERAS(Vehicle vehicle, bool shouldReset) { return YimMenu::NativeInvoker::Invoke<6296, void>(vehicle, shouldReset); }
	FORCEINLINE void SET_VEHICLE_DISABLE_COLLISION_UPON_CREATION(Vehicle vehicle, bool disable) { return YimMenu::NativeInvoker::Invoke<6297, void>(vehicle, disable); }
	FORCEINLINE void SET_GROUND_EFFECT_REDUCES_DRAG(bool toggle) { return YimMenu::NativeInvoker::Invoke<6298, void>(toggle); }
	FORCEINLINE void SET_DISABLE_MAP_COLLISION(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6299, void>(vehicle); }
	FORCEINLINE void SET_DISABLE_PED_STAND_ON_TOP(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6300, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_DAMAGE_SCALES(Vehicle vehicle, Any p1, Any p2, Any p3, Any p4) { return YimMenu::NativeInvoker::Invoke<6301, void>(vehicle, p1, p2, p3, p4); }
	FORCEINLINE void SET_PLANE_SECTION_DAMAGE_SCALE(Vehicle vehicle, Any p1, Any p2) { return YimMenu::NativeInvoker::Invoke<6302, void>(vehicle, p1, p2); }
	FORCEINLINE void SET_HELI_CAN_PICKUP_ENTITY_THAT_HAS_PICK_UP_DISABLED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6303, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_BOMB_AMMO(Vehicle vehicle, int bombCount) { return YimMenu::NativeInvoker::Invoke<6304, void>(vehicle, bombCount); }
	FORCEINLINE int GET_VEHICLE_BOMB_AMMO(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6305, int>(vehicle); }
	FORCEINLINE void SET_VEHICLE_COUNTERMEASURE_AMMO(Vehicle vehicle, int counterMeasureCount) { return YimMenu::NativeInvoker::Invoke<6306, void>(vehicle, counterMeasureCount); }
	FORCEINLINE int GET_VEHICLE_COUNTERMEASURE_AMMO(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6307, int>(vehicle); }
	FORCEINLINE void SET_HELI_COMBAT_OFFSET(Vehicle vehicle, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<6308, void>(vehicle, x, y, z); }
	FORCEINLINE bool GET_CAN_VEHICLE_BE_PLACED_HERE(Vehicle vehicle, float x, float y, float z, float rotX, float rotY, float rotZ, int p7, Any p8) { return YimMenu::NativeInvoker::Invoke<6309, bool>(vehicle, x, y, z, rotX, rotY, rotZ, p7, p8); }
	FORCEINLINE void SET_DISABLE_AUTOMATIC_CRASH_TASK(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6310, void>(vehicle, toggle); }
	FORCEINLINE void SET_SPECIAL_FLIGHT_MODE_RATIO(Vehicle vehicle, float ratio) { return YimMenu::NativeInvoker::Invoke<6311, void>(vehicle, ratio); }
	FORCEINLINE void SET_SPECIAL_FLIGHT_MODE_TARGET_RATIO(Vehicle vehicle, float targetRatio) { return YimMenu::NativeInvoker::Invoke<6312, void>(vehicle, targetRatio); }
	FORCEINLINE void SET_SPECIAL_FLIGHT_MODE_ALLOWED(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6313, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_HOVER_MODE_FLIGHT(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6314, void>(vehicle, toggle); }
	FORCEINLINE bool GET_OUTRIGGERS_DEPLOYED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6315, bool>(vehicle); }
	FORCEINLINE Vector3 FIND_SPAWN_COORDINATES_FOR_HELI(Ped ped) { return YimMenu::NativeInvoker::Invoke<6316, Vector3>(ped); }
	FORCEINLINE void SET_DEPLOY_FOLDING_WINGS(Vehicle vehicle, bool deploy, bool p2) { return YimMenu::NativeInvoker::Invoke<6317, void>(vehicle, deploy, p2); }
	FORCEINLINE bool ARE_FOLDING_WINGS_DEPLOYED(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6318, bool>(vehicle); }
	FORCEINLINE void SET_DIP_STRAIGHT_DOWN_WHEN_CRASHING_PLANE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6319, void>(vehicle, toggle); }
	FORCEINLINE void SET_TURRET_HIDDEN(Vehicle vehicle, int index, bool toggle) { return YimMenu::NativeInvoker::Invoke<6320, void>(vehicle, index, toggle); }
	FORCEINLINE void SET_HOVER_MODE_WING_RATIO(Vehicle vehicle, float ratio) { return YimMenu::NativeInvoker::Invoke<6321, void>(vehicle, ratio); }
	FORCEINLINE void SET_DISABLE_TURRET_MOVEMENT(Vehicle vehicle, int turretId) { return YimMenu::NativeInvoker::Invoke<6322, void>(vehicle, turretId); }
	FORCEINLINE void SET_FORCE_FIX_LINK_MATRICES(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6323, void>(vehicle); }
	FORCEINLINE void SET_TRANSFORM_RATE_FOR_ANIMATION(Vehicle vehicle, float transformRate) { return YimMenu::NativeInvoker::Invoke<6324, void>(vehicle, transformRate); }
	FORCEINLINE void SET_TRANSFORM_TO_SUBMARINE_USES_ALTERNATE_INPUT(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6325, void>(vehicle, toggle); }
	FORCEINLINE void SET_VEHICLE_COMBAT_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<6326, void>(toggle); }
	FORCEINLINE void SET_VEHICLE_DETONATION_MODE(bool toggle) { return YimMenu::NativeInvoker::Invoke<6327, void>(toggle); }
	FORCEINLINE void SET_VEHICLE_SHUNT_ON_STICK(bool toggle) { return YimMenu::NativeInvoker::Invoke<6328, void>(toggle); }
	FORCEINLINE bool GET_IS_VEHICLE_SHUNTING(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6329, bool>(vehicle); }
	FORCEINLINE bool GET_HAS_VEHICLE_BEEN_HIT_BY_SHUNT(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6330, bool>(vehicle); }
	FORCEINLINE Vehicle GET_LAST_SHUNT_VEHICLE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6331, Vehicle>(vehicle); }
	FORCEINLINE void SET_DISABLE_VEHICLE_EXPLOSIONS_DAMAGE(bool toggle) { return YimMenu::NativeInvoker::Invoke<6332, void>(toggle); }
	FORCEINLINE void SET_OVERRIDE_NITROUS_LEVEL(Vehicle vehicle, bool toggle, float level, float power, float rechargeTime, bool disableSound) { return YimMenu::NativeInvoker::Invoke<6333, void>(vehicle, toggle, level, power, rechargeTime, disableSound); }
	FORCEINLINE void SET_INCREASE_WHEEL_CRUSH_DAMAGE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6334, void>(vehicle, toggle); }
	FORCEINLINE void SET_DISABLE_WEAPON_BLADE_FORCES(bool toggle) { return YimMenu::NativeInvoker::Invoke<6335, void>(toggle); }
	FORCEINLINE void SET_USE_DOUBLE_CLICK_FOR_CAR_JUMP(bool toggle) { return YimMenu::NativeInvoker::Invoke<6336, void>(toggle); }
	FORCEINLINE bool GET_DOES_VEHICLE_HAVE_TOMBSTONE(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6337, bool>(vehicle); }
	FORCEINLINE void HIDE_TOMBSTONE(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6338, void>(vehicle, toggle); }
	FORCEINLINE bool GET_IS_VEHICLE_DISABLED_BY_EMP(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6339, bool>(vehicle); }
	FORCEINLINE void SET_DISABLE_RETRACTING_WEAPON_BLADES(bool toggle) { return YimMenu::NativeInvoker::Invoke<6340, void>(toggle); }
	FORCEINLINE float GET_TYRE_HEALTH(Vehicle vehicle, int wheelIndex) { return YimMenu::NativeInvoker::Invoke<6341, float>(vehicle, wheelIndex); }
	FORCEINLINE void SET_TYRE_HEALTH(Vehicle vehicle, int wheelIndex, float health) { return YimMenu::NativeInvoker::Invoke<6342, void>(vehicle, wheelIndex, health); }
	FORCEINLINE float GET_TYRE_WEAR_RATE(Vehicle vehicle, int wheelIndex) { return YimMenu::NativeInvoker::Invoke<6343, float>(vehicle, wheelIndex); }
	FORCEINLINE void SET_TYRE_WEAR_RATE(Vehicle vehicle, int wheelIndex, float multiplier) { return YimMenu::NativeInvoker::Invoke<6344, void>(vehicle, wheelIndex, multiplier); }
	FORCEINLINE void SET_TYRE_WEAR_RATE_SCALE(Vehicle vehicle, int wheelIndex, float multiplier) { return YimMenu::NativeInvoker::Invoke<6345, void>(vehicle, wheelIndex, multiplier); }
	FORCEINLINE void SET_TYRE_MAXIMUM_GRIP_DIFFERENCE_DUE_TO_WEAR_RATE(Vehicle vehicle, int wheelIndex, float multiplier) { return YimMenu::NativeInvoker::Invoke<6346, void>(vehicle, wheelIndex, multiplier); }
	FORCEINLINE void SET_AIRCRAFT_IGNORE_HIGHTMAP_OPTIMISATION(Vehicle vehicle, int p1) { return YimMenu::NativeInvoker::Invoke<6347, void>(vehicle, p1); }
	FORCEINLINE void SET_REDUCED_SUSPENSION_FORCE(Vehicle vehicle, bool enable) { return YimMenu::NativeInvoker::Invoke<6348, void>(vehicle, enable); }
	FORCEINLINE void SET_DRIFT_TYRES(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6349, void>(vehicle, toggle); }
	FORCEINLINE bool GET_DRIFT_TYRES_SET(Vehicle vehicle) { return YimMenu::NativeInvoker::Invoke<6350, bool>(vehicle); }
	FORCEINLINE void NETWORK_USE_HIGH_PRECISION_TRAIN_BLENDING(Vehicle vehicle, bool toggle) { return YimMenu::NativeInvoker::Invoke<6351, void>(vehicle, toggle); }
	FORCEINLINE void SET_CHECK_FOR_ENOUGH_ROOM_FOR_PED(Vehicle vehicle, bool p1) { return YimMenu::NativeInvoker::Invoke<6352, void>(vehicle, p1); }
}

namespace WATER
{
	FORCEINLINE bool GET_WATER_HEIGHT(float x, float y, float z, float* height) { return YimMenu::NativeInvoker::Invoke<6353, bool>(x, y, z, height); }
	FORCEINLINE bool GET_WATER_HEIGHT_NO_WAVES(float x, float y, float z, float* height) { return YimMenu::NativeInvoker::Invoke<6354, bool>(x, y, z, height); }
	FORCEINLINE bool TEST_PROBE_AGAINST_WATER(float x1, float y1, float z1, float x2, float y2, float z2, Vector3* result) { return YimMenu::NativeInvoker::Invoke<6355, bool>(x1, y1, z1, x2, y2, z2, result); }
	FORCEINLINE int TEST_PROBE_AGAINST_ALL_WATER(float x1, float y1, float z1, float x2, float y2, float z2, int flags, float* waterHeight) { return YimMenu::NativeInvoker::Invoke<6356, int>(x1, y1, z1, x2, y2, z2, flags, waterHeight); }
	FORCEINLINE int TEST_VERTICAL_PROBE_AGAINST_ALL_WATER(float x, float y, float z, int flags, float* waterHeight) { return YimMenu::NativeInvoker::Invoke<6357, int>(x, y, z, flags, waterHeight); }
	FORCEINLINE void MODIFY_WATER(float x, float y, float radius, float height) { return YimMenu::NativeInvoker::Invoke<6358, void>(x, y, radius, height); }
	FORCEINLINE int ADD_EXTRA_CALMING_QUAD(float xLow, float yLow, float xHigh, float yHigh, float height) { return YimMenu::NativeInvoker::Invoke<6359, int>(xLow, yLow, xHigh, yHigh, height); }
	FORCEINLINE void REMOVE_EXTRA_CALMING_QUAD(int calmingQuad) { return YimMenu::NativeInvoker::Invoke<6360, void>(calmingQuad); }
	FORCEINLINE void SET_DEEP_OCEAN_SCALER(float intensity) { return YimMenu::NativeInvoker::Invoke<6361, void>(intensity); }
	FORCEINLINE float GET_DEEP_OCEAN_SCALER() { return YimMenu::NativeInvoker::Invoke<6362, float>(); }
	FORCEINLINE void SET_CALMED_WAVE_HEIGHT_SCALER(float height) { return YimMenu::NativeInvoker::Invoke<6363, void>(height); }
	FORCEINLINE void RESET_DEEP_OCEAN_SCALER() { return YimMenu::NativeInvoker::Invoke<6364, void>(); }
}

namespace WEAPON
{
	FORCEINLINE void ENABLE_LASER_SIGHT_RENDERING(bool toggle) { return YimMenu::NativeInvoker::Invoke<6365, void>(toggle); }
	FORCEINLINE Hash GET_WEAPON_COMPONENT_TYPE_MODEL(Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6366, Hash>(componentHash); }
	FORCEINLINE Hash GET_WEAPONTYPE_MODEL(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6367, Hash>(weaponHash); }
	FORCEINLINE Hash GET_WEAPONTYPE_SLOT(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6368, Hash>(weaponHash); }
	FORCEINLINE Hash GET_WEAPONTYPE_GROUP(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6369, Hash>(weaponHash); }
	FORCEINLINE int GET_WEAPON_COMPONENT_VARIANT_EXTRA_COUNT(Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6370, int>(componentHash); }
	FORCEINLINE Hash GET_WEAPON_COMPONENT_VARIANT_EXTRA_MODEL(Hash componentHash, int extraComponentIndex) { return YimMenu::NativeInvoker::Invoke<6371, Hash>(componentHash, extraComponentIndex); }
	FORCEINLINE void SET_CURRENT_PED_WEAPON(Ped ped, Hash weaponHash, bool bForceInHand) { return YimMenu::NativeInvoker::Invoke<6372, void>(ped, weaponHash, bForceInHand); }
	FORCEINLINE bool GET_CURRENT_PED_WEAPON(Ped ped, Hash* weaponHash, bool p2) { return YimMenu::NativeInvoker::Invoke<6373, bool>(ped, weaponHash, p2); }
	FORCEINLINE Entity GET_CURRENT_PED_WEAPON_ENTITY_INDEX(Ped ped, Any p1) { return YimMenu::NativeInvoker::Invoke<6374, Entity>(ped, p1); }
	FORCEINLINE Hash GET_BEST_PED_WEAPON(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<6375, Hash>(ped, p1); }
	FORCEINLINE bool SET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6376, bool>(ped, weaponHash); }
	FORCEINLINE bool GET_CURRENT_PED_VEHICLE_WEAPON(Ped ped, Hash* weaponHash) { return YimMenu::NativeInvoker::Invoke<6377, bool>(ped, weaponHash); }
	FORCEINLINE void SET_PED_CYCLE_VEHICLE_WEAPONS_ONLY(Ped ped) { return YimMenu::NativeInvoker::Invoke<6378, void>(ped); }
	FORCEINLINE bool IS_PED_ARMED(Ped ped, int typeFlags) { return YimMenu::NativeInvoker::Invoke<6379, bool>(ped, typeFlags); }
	FORCEINLINE bool IS_WEAPON_VALID(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6380, bool>(weaponHash); }
	FORCEINLINE bool HAS_PED_GOT_WEAPON(Ped ped, Hash weaponHash, bool p2) { return YimMenu::NativeInvoker::Invoke<6381, bool>(ped, weaponHash, p2); }
	FORCEINLINE bool IS_PED_WEAPON_READY_TO_SHOOT(Ped ped) { return YimMenu::NativeInvoker::Invoke<6382, bool>(ped); }
	FORCEINLINE Hash GET_PED_WEAPONTYPE_IN_SLOT(Ped ped, Hash weaponSlot) { return YimMenu::NativeInvoker::Invoke<6383, Hash>(ped, weaponSlot); }
	FORCEINLINE int GET_AMMO_IN_PED_WEAPON(Ped ped, Hash weaponhash) { return YimMenu::NativeInvoker::Invoke<6384, int>(ped, weaponhash); }
	FORCEINLINE void ADD_AMMO_TO_PED(Ped ped, Hash weaponHash, int ammo) { return YimMenu::NativeInvoker::Invoke<6385, void>(ped, weaponHash, ammo); }
	FORCEINLINE void SET_PED_AMMO(Ped ped, Hash weaponHash, int ammo, bool p3) { return YimMenu::NativeInvoker::Invoke<6386, void>(ped, weaponHash, ammo, p3); }
	FORCEINLINE void SET_PED_INFINITE_AMMO(Ped ped, bool toggle, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6387, void>(ped, toggle, weaponHash); }
	FORCEINLINE void SET_PED_INFINITE_AMMO_CLIP(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<6388, void>(ped, toggle); }
	FORCEINLINE void SET_PED_STUN_GUN_FINITE_AMMO(Any p0, Any p1) { return YimMenu::NativeInvoker::Invoke<6389, void>(p0, p1); }
	FORCEINLINE void GIVE_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, bool isHidden, bool bForceInHand) { return YimMenu::NativeInvoker::Invoke<6390, void>(ped, weaponHash, ammoCount, isHidden, bForceInHand); }
	FORCEINLINE void GIVE_DELAYED_WEAPON_TO_PED(Ped ped, Hash weaponHash, int ammoCount, bool bForceInHand) { return YimMenu::NativeInvoker::Invoke<6391, void>(ped, weaponHash, ammoCount, bForceInHand); }
	FORCEINLINE void REMOVE_ALL_PED_WEAPONS(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<6392, void>(ped, p1); }
	FORCEINLINE void REMOVE_WEAPON_FROM_PED(Ped ped, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6393, void>(ped, weaponHash); }
	FORCEINLINE void HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<6394, void>(ped, toggle); }
	FORCEINLINE void SET_PED_CURRENT_WEAPON_VISIBLE(Ped ped, bool visible, bool deselectWeapon, bool p3, bool p4) { return YimMenu::NativeInvoker::Invoke<6395, void>(ped, visible, deselectWeapon, p3, p4); }
	FORCEINLINE void SET_PED_DROPS_WEAPONS_WHEN_DEAD(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<6396, void>(ped, toggle); }
	FORCEINLINE bool HAS_PED_BEEN_DAMAGED_BY_WEAPON(Ped ped, Hash weaponHash, int weaponType) { return YimMenu::NativeInvoker::Invoke<6397, bool>(ped, weaponHash, weaponType); }
	FORCEINLINE void CLEAR_PED_LAST_WEAPON_DAMAGE(Ped ped) { return YimMenu::NativeInvoker::Invoke<6398, void>(ped); }
	FORCEINLINE bool HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(Entity entity, Hash weaponHash, int weaponType) { return YimMenu::NativeInvoker::Invoke<6399, bool>(entity, weaponHash, weaponType); }
	FORCEINLINE void CLEAR_ENTITY_LAST_WEAPON_DAMAGE(Entity entity) { return YimMenu::NativeInvoker::Invoke<6400, void>(entity); }
	FORCEINLINE void SET_PED_DROPS_WEAPON(Ped ped) { return YimMenu::NativeInvoker::Invoke<6401, void>(ped); }
	FORCEINLINE void SET_PED_DROPS_INVENTORY_WEAPON(Ped ped, Hash weaponHash, float xOffset, float yOffset, float zOffset, int ammoCount) { return YimMenu::NativeInvoker::Invoke<6402, void>(ped, weaponHash, xOffset, yOffset, zOffset, ammoCount); }
	FORCEINLINE int GET_MAX_AMMO_IN_CLIP(Ped ped, Hash weaponHash, bool p2) { return YimMenu::NativeInvoker::Invoke<6403, int>(ped, weaponHash, p2); }
	FORCEINLINE bool GET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int* ammo) { return YimMenu::NativeInvoker::Invoke<6404, bool>(ped, weaponHash, ammo); }
	FORCEINLINE bool SET_AMMO_IN_CLIP(Ped ped, Hash weaponHash, int ammo) { return YimMenu::NativeInvoker::Invoke<6405, bool>(ped, weaponHash, ammo); }
	FORCEINLINE bool GET_MAX_AMMO(Ped ped, Hash weaponHash, int* ammo) { return YimMenu::NativeInvoker::Invoke<6406, bool>(ped, weaponHash, ammo); }
	FORCEINLINE bool GET_MAX_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int* ammo) { return YimMenu::NativeInvoker::Invoke<6407, bool>(ped, ammoTypeHash, ammo); }
	FORCEINLINE void ADD_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo) { return YimMenu::NativeInvoker::Invoke<6408, void>(ped, ammoTypeHash, ammo); }
	FORCEINLINE void SET_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash, int ammo) { return YimMenu::NativeInvoker::Invoke<6409, void>(ped, ammoTypeHash, ammo); }
	FORCEINLINE int GET_PED_AMMO_BY_TYPE(Ped ped, Hash ammoTypeHash) { return YimMenu::NativeInvoker::Invoke<6410, int>(ped, ammoTypeHash); }
	FORCEINLINE void SET_PED_AMMO_TO_DROP(Ped ped, int p1) { return YimMenu::NativeInvoker::Invoke<6411, void>(ped, p1); }
	FORCEINLINE void SET_PICKUP_AMMO_AMOUNT_SCALER(float p0) { return YimMenu::NativeInvoker::Invoke<6412, void>(p0); }
	FORCEINLINE Hash GET_PED_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6413, Hash>(ped, weaponHash); }
	FORCEINLINE Hash GET_PED_ORIGINAL_AMMO_TYPE_FROM_WEAPON(Ped ped, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6414, Hash>(ped, weaponHash); }
	FORCEINLINE bool GET_PED_LAST_WEAPON_IMPACT_COORD(Ped ped, Vector3* coords) { return YimMenu::NativeInvoker::Invoke<6415, bool>(ped, coords); }
	FORCEINLINE void SET_PED_GADGET(Ped ped, Hash gadgetHash, bool p2) { return YimMenu::NativeInvoker::Invoke<6416, void>(ped, gadgetHash, p2); }
	FORCEINLINE bool GET_IS_PED_GADGET_EQUIPPED(Ped ped, Hash gadgetHash) { return YimMenu::NativeInvoker::Invoke<6417, bool>(ped, gadgetHash); }
	FORCEINLINE Hash GET_SELECTED_PED_WEAPON(Ped ped) { return YimMenu::NativeInvoker::Invoke<6418, Hash>(ped); }
	FORCEINLINE void EXPLODE_PROJECTILES(Ped ped, Hash weaponHash, bool p2) { return YimMenu::NativeInvoker::Invoke<6419, void>(ped, weaponHash, p2); }
	FORCEINLINE void REMOVE_ALL_PROJECTILES_OF_TYPE(Hash weaponHash, bool explode) { return YimMenu::NativeInvoker::Invoke<6420, void>(weaponHash, explode); }
	FORCEINLINE float GET_LOCKON_DISTANCE_OF_CURRENT_PED_WEAPON(Ped ped) { return YimMenu::NativeInvoker::Invoke<6421, float>(ped); }
	FORCEINLINE float GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(Ped ped) { return YimMenu::NativeInvoker::Invoke<6422, float>(ped); }
	FORCEINLINE bool HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(Ped driver, Vehicle vehicle, Hash weaponHash, Any p3) { return YimMenu::NativeInvoker::Invoke<6423, bool>(driver, vehicle, weaponHash, p3); }
	FORCEINLINE void GIVE_WEAPON_COMPONENT_TO_PED(Ped ped, Hash weaponHash, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6424, void>(ped, weaponHash, componentHash); }
	FORCEINLINE void REMOVE_WEAPON_COMPONENT_FROM_PED(Ped ped, Hash weaponHash, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6425, void>(ped, weaponHash, componentHash); }
	FORCEINLINE bool HAS_PED_GOT_WEAPON_COMPONENT(Ped ped, Hash weaponHash, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6426, bool>(ped, weaponHash, componentHash); }
	FORCEINLINE bool IS_PED_WEAPON_COMPONENT_ACTIVE(Ped ped, Hash weaponHash, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6427, bool>(ped, weaponHash, componentHash); }
	FORCEINLINE bool REFILL_AMMO_INSTANTLY(Ped ped) { return YimMenu::NativeInvoker::Invoke<6428, bool>(ped); }
	FORCEINLINE bool MAKE_PED_RELOAD(Ped ped) { return YimMenu::NativeInvoker::Invoke<6429, bool>(ped); }
	FORCEINLINE void REQUEST_WEAPON_ASSET(Hash weaponHash, int p1, int p2) { return YimMenu::NativeInvoker::Invoke<6430, void>(weaponHash, p1, p2); }
	FORCEINLINE bool HAS_WEAPON_ASSET_LOADED(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6431, bool>(weaponHash); }
	FORCEINLINE void REMOVE_WEAPON_ASSET(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6432, void>(weaponHash); }
	FORCEINLINE Object CREATE_WEAPON_OBJECT(Hash weaponHash, int ammoCount, float x, float y, float z, bool showWorldModel, float scale, Any p7, Any p8, Any p9) { return YimMenu::NativeInvoker::Invoke<6433, Object>(weaponHash, ammoCount, x, y, z, showWorldModel, scale, p7, p8, p9); }
	FORCEINLINE void GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(Object weaponObject, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6434, void>(weaponObject, componentHash); }
	FORCEINLINE void REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(Object object, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6435, void>(object, componentHash); }
	FORCEINLINE bool HAS_WEAPON_GOT_WEAPON_COMPONENT(Object weapon, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6436, bool>(weapon, componentHash); }
	FORCEINLINE void GIVE_WEAPON_OBJECT_TO_PED(Object weaponObject, Ped ped) { return YimMenu::NativeInvoker::Invoke<6437, void>(weaponObject, ped); }
	FORCEINLINE bool DOES_WEAPON_TAKE_WEAPON_COMPONENT(Hash weaponHash, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6438, bool>(weaponHash, componentHash); }
	FORCEINLINE Object GET_WEAPON_OBJECT_FROM_PED(Ped ped, bool p1) { return YimMenu::NativeInvoker::Invoke<6439, Object>(ped, p1); }
	FORCEINLINE void GIVE_LOADOUT_TO_PED(Ped ped, Hash loadoutHash) { return YimMenu::NativeInvoker::Invoke<6440, void>(ped, loadoutHash); }
	FORCEINLINE void SET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash, int tintIndex) { return YimMenu::NativeInvoker::Invoke<6441, void>(ped, weaponHash, tintIndex); }
	FORCEINLINE int GET_PED_WEAPON_TINT_INDEX(Ped ped, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6442, int>(ped, weaponHash); }
	FORCEINLINE void SET_WEAPON_OBJECT_TINT_INDEX(Object weapon, int tintIndex) { return YimMenu::NativeInvoker::Invoke<6443, void>(weapon, tintIndex); }
	FORCEINLINE int GET_WEAPON_OBJECT_TINT_INDEX(Object weapon) { return YimMenu::NativeInvoker::Invoke<6444, int>(weapon); }
	FORCEINLINE int GET_WEAPON_TINT_COUNT(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6445, int>(weaponHash); }
	FORCEINLINE void SET_PED_WEAPON_COMPONENT_TINT_INDEX(Ped ped, Hash weaponHash, Hash camoComponentHash, int colorIndex) { return YimMenu::NativeInvoker::Invoke<6446, void>(ped, weaponHash, camoComponentHash, colorIndex); }
	FORCEINLINE int GET_PED_WEAPON_COMPONENT_TINT_INDEX(Ped ped, Hash weaponHash, Hash camoComponentHash) { return YimMenu::NativeInvoker::Invoke<6447, int>(ped, weaponHash, camoComponentHash); }
	FORCEINLINE void SET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(Object weaponObject, Hash camoComponentHash, int colorIndex) { return YimMenu::NativeInvoker::Invoke<6448, void>(weaponObject, camoComponentHash, colorIndex); }
	FORCEINLINE int GET_WEAPON_OBJECT_COMPONENT_TINT_INDEX(Object weaponObject, Hash camoComponentHash) { return YimMenu::NativeInvoker::Invoke<6449, int>(weaponObject, camoComponentHash); }
	FORCEINLINE int GET_PED_WEAPON_CAMO_INDEX(Ped ped, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6450, int>(ped, weaponHash); }
	FORCEINLINE void SET_WEAPON_OBJECT_CAMO_INDEX(Object weaponObject, int p1) { return YimMenu::NativeInvoker::Invoke<6451, void>(weaponObject, p1); }
	FORCEINLINE bool GET_WEAPON_HUD_STATS(Hash weaponHash, Any* outData) { return YimMenu::NativeInvoker::Invoke<6452, bool>(weaponHash, outData); }
	FORCEINLINE bool GET_WEAPON_COMPONENT_HUD_STATS(Hash componentHash, Any* outData) { return YimMenu::NativeInvoker::Invoke<6453, bool>(componentHash, outData); }
	FORCEINLINE float GET_WEAPON_DAMAGE(Hash weaponHash, Hash componentHash) { return YimMenu::NativeInvoker::Invoke<6454, float>(weaponHash, componentHash); }
	FORCEINLINE int GET_WEAPON_CLIP_SIZE(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6455, int>(weaponHash); }
	FORCEINLINE float GET_WEAPON_TIME_BETWEEN_SHOTS(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6456, float>(weaponHash); }
	FORCEINLINE void SET_PED_CHANCE_OF_FIRING_BLANKS(Ped ped, float xBias, float yBias) { return YimMenu::NativeInvoker::Invoke<6457, void>(ped, xBias, yBias); }
	FORCEINLINE Object SET_PED_SHOOT_ORDNANCE_WEAPON(Ped ped, float p1) { return YimMenu::NativeInvoker::Invoke<6458, Object>(ped, p1); }
	FORCEINLINE void REQUEST_WEAPON_HIGH_DETAIL_MODEL(Entity weaponObject) { return YimMenu::NativeInvoker::Invoke<6459, void>(weaponObject); }
	FORCEINLINE void SET_WEAPON_DAMAGE_MODIFIER(Hash weaponHash, float damageMultiplier) { return YimMenu::NativeInvoker::Invoke<6460, void>(weaponHash, damageMultiplier); }
	FORCEINLINE void SET_WEAPON_AOE_MODIFIER(Hash weaponHash, float multiplier) { return YimMenu::NativeInvoker::Invoke<6461, void>(weaponHash, multiplier); }
	FORCEINLINE void SET_WEAPON_EFFECT_DURATION_MODIFIER(Hash p0, float p1) { return YimMenu::NativeInvoker::Invoke<6462, void>(p0, p1); }
	FORCEINLINE bool IS_PED_CURRENT_WEAPON_SILENCED(Ped ped) { return YimMenu::NativeInvoker::Invoke<6463, bool>(ped); }
	FORCEINLINE bool IS_FLASH_LIGHT_ON(Ped ped) { return YimMenu::NativeInvoker::Invoke<6464, bool>(ped); }
	FORCEINLINE bool SET_FLASH_LIGHT_FADE_DISTANCE(float distance) { return YimMenu::NativeInvoker::Invoke<6465, bool>(distance); }
	FORCEINLINE void SET_FLASH_LIGHT_ACTIVE_HISTORY(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<6466, void>(ped, toggle); }
	FORCEINLINE void SET_WEAPON_ANIMATION_OVERRIDE(Ped ped, Hash animStyle) { return YimMenu::NativeInvoker::Invoke<6467, void>(ped, animStyle); }
	FORCEINLINE int GET_WEAPON_DAMAGE_TYPE(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6468, int>(weaponHash); }
	FORCEINLINE void SET_EQIPPED_WEAPON_START_SPINNING_AT_FULL_SPEED(Ped ped) { return YimMenu::NativeInvoker::Invoke<6469, void>(ped); }
	FORCEINLINE bool CAN_USE_WEAPON_ON_PARACHUTE(Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6470, bool>(weaponHash); }
	FORCEINLINE int CREATE_AIR_DEFENCE_SPHERE(float x, float y, float z, float radius, float p4, float p5, float p6, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6471, int>(x, y, z, radius, p4, p5, p6, weaponHash); }
	FORCEINLINE int CREATE_AIR_DEFENCE_ANGLED_AREA(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, float p8, float radius, Hash weaponHash) { return YimMenu::NativeInvoker::Invoke<6472, int>(p0, p1, p2, p3, p4, p5, p6, p7, p8, radius, weaponHash); }
	FORCEINLINE bool REMOVE_AIR_DEFENCE_SPHERE(int zoneId) { return YimMenu::NativeInvoker::Invoke<6473, bool>(zoneId); }
	FORCEINLINE void REMOVE_ALL_AIR_DEFENCE_SPHERES() { return YimMenu::NativeInvoker::Invoke<6474, void>(); }
	FORCEINLINE void SET_PLAYER_TARGETTABLE_FOR_AIR_DEFENCE_SPHERE(Player player, int zoneId, bool enable) { return YimMenu::NativeInvoker::Invoke<6475, void>(player, zoneId, enable); }
	FORCEINLINE bool IS_AIR_DEFENCE_SPHERE_IN_AREA(float x, float y, float z, float radius, int* outZoneId) { return YimMenu::NativeInvoker::Invoke<6476, bool>(x, y, z, radius, outZoneId); }
	FORCEINLINE void FIRE_AIR_DEFENCE_SPHERE_WEAPON_AT_POSITION(int zoneId, float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<6477, void>(zoneId, x, y, z); }
	FORCEINLINE bool DOES_AIR_DEFENCE_SPHERE_EXIST(int zoneId) { return YimMenu::NativeInvoker::Invoke<6478, bool>(zoneId); }
	FORCEINLINE void SET_CAN_PED_SELECT_INVENTORY_WEAPON(Ped ped, Hash weaponHash, bool toggle) { return YimMenu::NativeInvoker::Invoke<6479, void>(ped, weaponHash, toggle); }
	FORCEINLINE void SET_CAN_PED_SELECT_ALL_WEAPONS(Ped ped, bool toggle) { return YimMenu::NativeInvoker::Invoke<6480, void>(ped, toggle); }
}

namespace ZONE
{
	FORCEINLINE int GET_ZONE_AT_COORDS(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<6481, int>(x, y, z); }
	FORCEINLINE int GET_ZONE_FROM_NAME_ID(const char* zoneName) { return YimMenu::NativeInvoker::Invoke<6482, int>(zoneName); }
	FORCEINLINE int GET_ZONE_POPSCHEDULE(int zoneId) { return YimMenu::NativeInvoker::Invoke<6483, int>(zoneId); }
	FORCEINLINE const char* GET_NAME_OF_ZONE(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<6484, const char*>(x, y, z); }
	FORCEINLINE void SET_ZONE_ENABLED(int zoneId, bool toggle) { return YimMenu::NativeInvoker::Invoke<6485, void>(zoneId, toggle); }
	FORCEINLINE int GET_ZONE_SCUMMINESS(int zoneId) { return YimMenu::NativeInvoker::Invoke<6486, int>(zoneId); }
	FORCEINLINE void OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(int scheduleId, Hash vehicleHash) { return YimMenu::NativeInvoker::Invoke<6487, void>(scheduleId, vehicleHash); }
	FORCEINLINE void CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(int scheduleId) { return YimMenu::NativeInvoker::Invoke<6488, void>(scheduleId); }
	FORCEINLINE Hash GET_HASH_OF_MAP_AREA_AT_COORDS(float x, float y, float z) { return YimMenu::NativeInvoker::Invoke<6489, Hash>(x, y, z); }
}
// clang-format on
