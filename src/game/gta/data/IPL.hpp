#pragma once
#include <string>
#include <types/script/types.hpp>

namespace YimMenu
{
	class IPLLibrary
	{
	public:
		std::string_view FriendlyName;
		rage::fvector3 Location;

		std::vector<std::string_view> IPLNames;
		std::vector<std::string_view> IPLNamesRemove;
		std::vector<std::string_view> IPLNamesRemoveWhenLoad;
	};

	// thanks to https://github.com/DurtyFree/gta-v-data-dumps
	const IPLLibrary IPLs[] = {
	    {
	        "North Yankton",
	        {3211.42, -4836.89, 111.81},
	        {{"prologue01"}, {"prologue01c"}, {"prologue01d"}, {"prologue01e"}, {"prologue01f"}, {"prologue01g"}, {"prologue01h"}, {"prologue01i"}, {"prologue01j"}, {"prologue01k"}, {"prologue01z"}, {"prologue02"}, {"prologue03"}, {"prologue03_grv_cov"}, {"prologue03_grv_dug"}, {"prologue03_grv_fun"}, {"prologue03b"}, {"prologue_grv_torch"}, {"des_protree_end"}, {"des_protree_start"}, {"prologue04"}, {"prologue04_cover"}, {"prologue04b"}, {"prologue05"}, {"prologue05b"}, {"prologue06"}, {"prologue06_int"}, {"prologue06_pannel"}, {"prologue06b"}, {"prologue_m2_door"}, {"prologue_occl"}, {"prologuerd"}, {"prologuerdb"}},
	        {{""}},
	        {{""}},
	    },

	    //{
	    //    "Cayo Perico",
	    //    {4915.78, -4907.40, 3.39},
	    //    {{"h4_mph4_terrain_01_grass_0", "h4_mph4_terrain_01_grass_1", "h4_mph4_terrain_02_grass_0", "h4_mph4_terrain_02_grass_1", "h4_mph4_terrain_02_grass_2", "h4_mph4_terrain_02_grass_3", "h4_mph4_terrain_04_grass_0", "h4_mph4_terrain_04_grass_1", "h4_mph4_terrain_05_grass_0", "h4_mph4_terrain_06_grass_0", "h4_islandx_terrain_01", "h4_islandx_terrain_01_lod", "h4_islandx_terrain_01_slod", "h4_islandx_terrain_02", "h4_islandx_terrain_02_lod", "h4_islandx_terrain_02_slod", "h4_islandx_terrain_03", "h4_islandx_terrain_03_lod", "h4_islandx_terrain_04", "h4_islandx_terrain_04_lod", "h4_islandx_terrain_04_slod", "h4_islandx_terrain_05", "h4_islandx_terrain_05_lod", "h4_islandx_terrain_05_slod", "h4_islandx_terrain_06", "h4_islandx_terrain_06_lod", "h4_islandx_terrain_06_slod", "h4_islandx_terrain_props_05_a", "h4_islandx_terrain_props_05_a_lod", "h4_islandx_terrain_props_05_b", "h4_islandx_terrain_props_05_b_lod", "h4_islandx_terrain_props_05_c", "h4_islandx_terrain_props_05_c_lod", "h4_islandx_terrain_props_05_d", "h4_islandx_terrain_props_05_d_lod", "h4_islandx_terrain_props_05_d_slod", "h4_islandx_terrain_props_05_e", "h4_islandx_terrain_props_05_e_lod", "h4_islandx_terrain_props_05_e_slod", "h4_islandx_terrain_props_05_f", "h4_islandx_terrain_props_05_f_lod", "h4_islandx_terrain_props_05_f_slod", "h4_islandx_terrain_props_06_a", "h4_islandx_terrain_props_06_a_lod", "h4_islandx_terrain_props_06_a_slod", "h4_islandx_terrain_props_06_b", "h4_islandx_terrain_props_06_b_lod", "h4_islandx_terrain_props_06_b_slod", "h4_islandx_terrain_props_06_c", "h4_islandx_terrain_props_06_c_lod", "h4_islandx_terrain_props_06_c_slod", "h4_mph4_terrain_01", "h4_mph4_terrain_01_long_0", "h4_mph4_terrain_02", "h4_mph4_terrain_03", "h4_mph4_terrain_04", "h4_mph4_terrain_05", "h4_mph4_terrain_06", "h4_mph4_terrain_06_strm_0", "h4_mph4_terrain_lod", "h4_mph4_terrain_occ_00", "h4_mph4_terrain_occ_01", "h4_mph4_terrain_occ_02", "h4_mph4_terrain_occ_03", "h4_mph4_terrain_occ_04", "h4_mph4_terrain_occ_05", "h4_mph4_terrain_occ_06", "h4_mph4_terrain_occ_07", "h4_mph4_terrain_occ_08", "h4_mph4_terrain_occ_09", "h4_boatblockers", "h4_islandx", "h4_islandx_disc_strandedshark", "h4_islandx_disc_strandedshark_lod", "h4_islandx_disc_strandedwhale", "h4_islandx_disc_strandedwhale_lod", "h4_islandx_props", "h4_islandx_props_lod", "h4_islandx_sea_mines", "h4_mph4_island", "h4_mph4_island_long_0", "h4_mph4_island_strm_0", "h4_aa_guns", "h4_aa_guns_lod", "h4_beach", "h4_beach_bar_props", "h4_beach_lod", "h4_beach_party", "h4_beach_party_lod", "h4_beach_props", "h4_beach_props_lod", "h4_beach_props_party", "h4_beach_props_slod", "h4_beach_slod", "h4_islandairstrip", "h4_islandairstrip_doorsclosed", "h4_islandairstrip_doorsclosed_lod", "h4_islandairstrip_doorsopen", "h4_islandairstrip_doorsopen_lod", "h4_islandairstrip_hangar_props", "h4_islandairstrip_hangar_props_lod", "h4_islandairstrip_hangar_props_slod", "h4_islandairstrip_lod", "h4_islandairstrip_props", "h4_islandairstrip_propsb", "h4_islandairstrip_propsb_lod", "h4_islandairstrip_propsb_slod", "h4_islandairstrip_props_lod", "h4_islandairstrip_props_slod", "h4_islandairstrip_slod", "h4_islandxcanal_props", "h4_islandxcanal_props_lod", "h4_islandxcanal_props_slod", "h4_islandxdock", "h4_islandxdock_lod", "h4_islandxdock_props", "h4_islandxdock_props_2", "h4_islandxdock_props_2_lod", "h4_islandxdock_props_2_slod", "h4_islandxdock_props_lod", "h4_islandxdock_props_slod", "h4_islandxdock_slod", "h4_islandxdock_water_hatch", "h4_islandxtower", "h4_islandxtower_lod", "h4_islandxtower_slod", "h4_islandxtower_veg", "h4_islandxtower_veg_lod", "h4_islandxtower_veg_slod", "h4_islandx_barrack_hatch", "h4_islandx_barrack_props", "h4_islandx_barrack_props_lod", "h4_islandx_barrack_props_slod", "h4_islandx_checkpoint", "h4_islandx_checkpoint_lod", "h4_islandx_checkpoint_props", "h4_islandx_checkpoint_props_lod", "h4_islandx_checkpoint_props_slod", "h4_islandx_maindock", "h4_islandx_maindock_lod", "h4_islandx_maindock_props", "h4_islandx_maindock_props_2", "h4_islandx_maindock_props_2_lod", "h4_islandx_maindock_props_2_slod", "h4_islandx_maindock_props_lod", "h4_islandx_maindock_props_slod", "h4_islandx_maindock_slod", "h4_islandx_mansion", "h4_islandx_mansion_b", "h4_islandx_mansion_b_lod", "h4_islandx_mansion_b_side_fence", "h4_islandx_mansion_b_slod", "h4_islandx_mansion_entrance_fence", "h4_islandx_mansion_guardfence", "h4_islandx_mansion_lights", "h4_islandx_mansion_lockup_01", "h4_islandx_mansion_lockup_01_lod", "h4_islandx_mansion_lockup_02", "h4_islandx_mansion_lockup_02_lod", "h4_islandx_mansion_lockup_03", "h4_islandx_mansion_lockup_03_lod", "h4_islandx_mansion_lod", "h4_islandx_mansion_office", "h4_islandx_mansion_office_lod", "h4_islandx_mansion_props", "h4_islandx_mansion_props_lod", "h4_islandx_mansion_props_slod", "h4_islandx_mansion_slod", "h4_islandx_mansion_vault", "h4_islandx_mansion_vault_lod", "h4_island_padlock_props", "h4_mansion_gate_closed", "h4_mansion_remains_cage", "h4_mph4_airstrip", "h4_mph4_airstrip_interior_0_airstrip_hanger", "h4_mph4_beach", "h4_mph4_dock", "h4_mph4_island_lod", "h4_mph4_island_ne_placement", "h4_mph4_island_nw_placement", "h4_mph4_island_se_placement", "h4_mph4_island_sw_placement", "h4_mph4_mansion", "h4_mph4_mansion_b", "h4_mph4_mansion_b_strm_0", "h4_mph4_mansion_strm_0", "h4_mph4_wtowers", "h4_ne_ipl_00", "h4_ne_ipl_00_lod", "h4_ne_ipl_00_slod", "h4_ne_ipl_01", "h4_ne_ipl_01_lod", "h4_ne_ipl_01_slod", "h4_ne_ipl_02", "h4_ne_ipl_02_lod", "h4_ne_ipl_02_slod", "h4_ne_ipl_03", "h4_ne_ipl_03_lod", "h4_ne_ipl_03_slod", "h4_ne_ipl_04", "h4_ne_ipl_04_lod", "h4_ne_ipl_04_slod", "h4_ne_ipl_05", "h4_ne_ipl_05_lod", "h4_ne_ipl_05_slod", "h4_ne_ipl_06", "h4_ne_ipl_06_lod", "h4_ne_ipl_06_slod", "h4_ne_ipl_07", "h4_ne_ipl_07_lod", "h4_ne_ipl_07_slod", "h4_ne_ipl_08", "h4_ne_ipl_08_lod", "h4_ne_ipl_08_slod", "h4_ne_ipl_09", "h4_ne_ipl_09_lod", "h4_ne_ipl_09_slod", "h4_nw_ipl_00", "h4_nw_ipl_00_lod", "h4_nw_ipl_00_slod", "h4_nw_ipl_01", "h4_nw_ipl_01_lod", "h4_nw_ipl_01_slod", "h4_nw_ipl_02", "h4_nw_ipl_02_lod", "h4_nw_ipl_02_slod", "h4_nw_ipl_03", "h4_nw_ipl_03_lod", "h4_nw_ipl_03_slod", "h4_nw_ipl_04", "h4_nw_ipl_04_lod", "h4_nw_ipl_04_slod", "h4_nw_ipl_05", "h4_nw_ipl_05_lod", "h4_nw_ipl_05_slod", "h4_nw_ipl_06", "h4_nw_ipl_06_lod", "h4_nw_ipl_06_slod", "h4_nw_ipl_07", "h4_nw_ipl_07_lod", "h4_nw_ipl_07_slod", "h4_nw_ipl_08", "h4_nw_ipl_08_lod", "h4_nw_ipl_08_slod", "h4_nw_ipl_09", "h4_nw_ipl_09_lod", "h4_nw_ipl_09_slod", "h4_se_ipl_00", "h4_se_ipl_00_lod", "h4_se_ipl_00_slod", "h4_se_ipl_01", "h4_se_ipl_01_lod", "h4_se_ipl_01_slod", "h4_se_ipl_02", "h4_se_ipl_02_lod", "h4_se_ipl_02_slod", "h4_se_ipl_03", "h4_se_ipl_03_lod", "h4_se_ipl_03_slod", "h4_se_ipl_04", "h4_se_ipl_04_lod", "h4_se_ipl_04_slod", "h4_se_ipl_05", "h4_se_ipl_05_lod", "h4_se_ipl_05_slod", "h4_se_ipl_06", "h4_se_ipl_06_lod", "h4_se_ipl_06_slod", "h4_se_ipl_07", "h4_se_ipl_07_lod", "h4_se_ipl_07_slod", "h4_se_ipl_08", "h4_se_ipl_08_lod", "h4_se_ipl_08_slod", "h4_se_ipl_09", "h4_se_ipl_09_lod", "h4_se_ipl_09_slod", "h4_sw_ipl_00", "h4_sw_ipl_00_lod", "h4_sw_ipl_00_slod", "h4_sw_ipl_01", "h4_sw_ipl_01_lod", "h4_sw_ipl_01_slod", "h4_sw_ipl_02", "h4_sw_ipl_02_lod", "h4_sw_ipl_02_slod", "h4_sw_ipl_03", "h4_sw_ipl_03_lod", "h4_sw_ipl_03_slod", "h4_sw_ipl_04", "h4_sw_ipl_04_lod", "h4_sw_ipl_04_slod", "h4_sw_ipl_05", "h4_sw_ipl_05_lod", "h4_sw_ipl_05_slod", "h4_sw_ipl_06", "h4_sw_ipl_06_lod", "h4_sw_ipl_06_slod", "h4_sw_ipl_07", "h4_sw_ipl_07_lod", "h4_sw_ipl_07_slod", "h4_sw_ipl_08", "h4_sw_ipl_08_lod", "h4_sw_ipl_08_slod", "h4_sw_ipl_09", "h4_sw_ipl_09_lod", "h4_sw_ipl_09_slod", "h4_underwater_gate_closed", "h4_islandx_placement_01", "h4_islandx_placement_02", "h4_islandx_placement_03", "h4_islandx_placement_04", "h4_islandx_placement_05", "h4_islandx_placement_06", "h4_islandx_placement_07", "h4_islandx_placement_08", "h4_islandx_placement_09", "h4_islandx_placement_10", "h4_mph4_island_placement"}},
	    //    {{""}},
	    //    {{""}},
	    //},

	    {
	        "Dignity Party Yacht",
	        {-2045.8, -1031.2, 11.9},
	        {{"smboat"}, {"apa_smboat_lodlights"}, {"ba_sm_boat_window"}},
	        {{""}},
	        {{""}},
	    },
	    {
	        "Aircraft Carrier",
	        {3069.33, -4632.4, 15.04},
	        {{"hei_carrier_lodlights"}, {"hei_carrier"}, {"hei_carrier_int1"}, {"hei_carrier_int2"}, {"hei_carrier_int3"}, {"hei_carrier_int4"}, {"hei_carrier_int5"}, {"hei_carrier_int6"}},
	        {{""}},
	        {{""}},
	    },
	    {
	        "Sunken Cargo Ship",
	        {-162.89, -2365.76, 0.0},
	        {{"sunk_ship_fire"}, {"sunkcargoship"}},
	        {{"cargoship"}},
	        {{"cargoship"}},
	    },
	    {
	        "Destroyed Pillbox Hospital",
	        {297.84, -584.41, 43.26},
	        {{"rc12b_hospitalinterior"}},
	        {{"rc12b_default"}},
	        {{"rc12b_default"}},
	    },
	    {
	        "O'Neil Farm Destroyed",
	        {2471.49, 4954.18, 45.12},
	        {{"farm_burnt"}, {"farm_burnt_props"}},
	        {{"farm"}, {"farmint"}, {"farmint_cap"}, {"farm_props"}, {"des_farmhs_startimap"}},
	        {{"farm"}, {"farmint"}, {"farmint_cap"}, {"farm_props"}, {"des_farmhs_startimap"}},
	    },
	    {
	        "LifeInvader Interior",
	        {-1082.77, -258.67, 37.76},
	        {{"facelobby"}},
	        {{"facelobbyfake"}},
	        {{"facelobbyfake"}},
	    },
	    {
	        "Jewelry Store Interior",
	        {-630.4, -236.7, 40.0},
	        {{"post_hiest_unload"}},
	        {{"jewel2fake"}},
	        {{"jewel2fake"}, {"bh1_16_refurb"}},
	    },
	    {
	        "Coroner Morgue Interior",
	        {244.9, -1374.7, 39.5},
	        {{"coroner_int_on"}, {"coronertrash"}},
	        {{"coroner_int_off"}},
	        {{"coroner_int_off"}},
	    }};
};