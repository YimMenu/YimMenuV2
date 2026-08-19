#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <string>
#include <vector>

namespace YimMenu::Lua
{
	// Lua-facing ImGui binding. The class is intentionally named "ImGuiBind"
	// to avoid a name clash with the global ::ImGui namespace; the table is
	// still exposed to Lua under the global name "ImGui".
	class ImGuiBind : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		// ----------------------------------------------------------------
		// Helpers
		// ----------------------------------------------------------------

		// Reads N numbers from a Lua array table at `idx` into `out`.
		static void ReadFloatArray(lua_State* state, int idx, float* out, int count)
		{
			luaL_checktype(state, idx, LUA_TTABLE);
			for (int i = 0; i < count; i++)
			{
				lua_rawgeti(state, idx, i + 1);
				out[i] = static_cast<float>(luaL_checknumber(state, -1));
				lua_pop(state, 1);
			}
		}

		static void ReadIntArray(lua_State* state, int idx, int* out, int count)
		{
			luaL_checktype(state, idx, LUA_TTABLE);
			for (int i = 0; i < count; i++)
			{
				lua_rawgeti(state, idx, i + 1);
				out[i] = static_cast<int>(luaL_checkinteger(state, -1));
				lua_pop(state, 1);
			}
		}

		// Pushes a Lua array table built from `count` floats.
		static void PushFloatArray(lua_State* state, const float* in, int count)
		{
			lua_createtable(state, count, 0);
			for (int i = 0; i < count; i++)
			{
				lua_pushnumber(state, in[i]);
				lua_rawseti(state, -2, i + 1);
			}
		}

		static void PushIntArray(lua_State* state, const int* in, int count)
		{
			lua_createtable(state, count, 0);
			for (int i = 0; i < count; i++)
			{
				lua_pushinteger(state, in[i]);
				lua_rawseti(state, -2, i + 1);
			}
		}

		// Reads a NULL-terminated string at `idx` if provided, else returns nullptr.
		static const char* OptString(lua_State* state, int idx)
		{
			if (lua_isnoneornil(state, idx))
				return nullptr;
			return luaL_checkstring(state, idx);
		}

		// ----------------------------------------------------------------
		// Internal: DrawList helpers
		// ----------------------------------------------------------------

		static ImU32 PackColor(int r, int g, int b, int a)
		{
			return IM_COL32(r, g, b, a);
		}

		static int AddCircle(lua_State* state)
		{
			float x          = (float)luaL_checknumber(state, 1);
			float y          = (float)luaL_checknumber(state, 2);
			float radius     = (float)luaL_checknumber(state, 3);
			int r            = (int)luaL_checkinteger(state, 4);
			int g            = (int)luaL_checkinteger(state, 5);
			int b            = (int)luaL_checkinteger(state, 6);
			int a            = (int)luaL_checkinteger(state, 7);
			int numSegments  = (int)luaL_optinteger(state, 8, 0);
			float thickness  = (float)luaL_optnumber(state, 9, 1.0);
			ImGui::GetWindowDrawList()->AddCircle(ImVec2(x, y), radius, PackColor(r, g, b, a), numSegments, thickness);
			return 0;
		}

		static int AddCircleFilled(lua_State* state)
		{
			float x         = (float)luaL_checknumber(state, 1);
			float y         = (float)luaL_checknumber(state, 2);
			float radius    = (float)luaL_checknumber(state, 3);
			int r           = (int)luaL_checkinteger(state, 4);
			int g           = (int)luaL_checkinteger(state, 5);
			int b           = (int)luaL_checkinteger(state, 6);
			int a           = (int)luaL_checkinteger(state, 7);
			int numSegments = (int)luaL_optinteger(state, 8, 0);
			ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(x, y), radius, PackColor(r, g, b, a), numSegments);
			return 0;
		}

		static int AddLine(lua_State* state)
		{
			float x1        = (float)luaL_checknumber(state, 1);
			float y1        = (float)luaL_checknumber(state, 2);
			float x2        = (float)luaL_checknumber(state, 3);
			float y2        = (float)luaL_checknumber(state, 4);
			int r           = (int)luaL_checkinteger(state, 5);
			int g           = (int)luaL_checkinteger(state, 6);
			int b           = (int)luaL_checkinteger(state, 7);
			int a           = (int)luaL_checkinteger(state, 8);
			float thickness = (float)luaL_optnumber(state, 9, 1.0);
			ImGui::GetWindowDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), PackColor(r, g, b, a), thickness);
			return 0;
		}

		static int AddRect(lua_State* state)
		{
			float x1        = (float)luaL_checknumber(state, 1);
			float y1        = (float)luaL_checknumber(state, 2);
			float x2        = (float)luaL_checknumber(state, 3);
			float y2        = (float)luaL_checknumber(state, 4);
			int r           = (int)luaL_checkinteger(state, 5);
			int g           = (int)luaL_checkinteger(state, 6);
			int b           = (int)luaL_checkinteger(state, 7);
			int a           = (int)luaL_checkinteger(state, 8);
			float rounding  = (float)luaL_optnumber(state, 9, 0.0);
			int drawFlags   = (int)luaL_optinteger(state, 10, 0);
			float thickness = (float)luaL_optnumber(state, 11, 1.0);
			ImGui::GetWindowDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), PackColor(r, g, b, a), rounding, drawFlags, thickness);
			return 0;
		}

		static int AddRectFilled(lua_State* state)
		{
			float x1       = (float)luaL_checknumber(state, 1);
			float y1       = (float)luaL_checknumber(state, 2);
			float x2       = (float)luaL_checknumber(state, 3);
			float y2       = (float)luaL_checknumber(state, 4);
			int r          = (int)luaL_checkinteger(state, 5);
			int g          = (int)luaL_checkinteger(state, 6);
			int b          = (int)luaL_checkinteger(state, 7);
			int a          = (int)luaL_checkinteger(state, 8);
			float rounding = (float)luaL_optnumber(state, 9, 0.0);
			int drawFlags  = (int)luaL_optinteger(state, 10, 0);
			ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), PackColor(r, g, b, a), rounding, drawFlags);
			return 0;
		}

		static int AddRectFilledMultiColor(lua_State* state)
		{
			float x1     = (float)luaL_checknumber(state, 1);
			float y1     = (float)luaL_checknumber(state, 2);
			float x2     = (float)luaL_checknumber(state, 3);
			float y2     = (float)luaL_checknumber(state, 4);
			ImU32 ul     = (ImU32)luaL_checkinteger(state, 5);
			ImU32 ur     = (ImU32)luaL_checkinteger(state, 6);
			ImU32 br     = (ImU32)luaL_checkinteger(state, 7);
			ImU32 bl     = (ImU32)luaL_checkinteger(state, 8);
			ImGui::GetWindowDrawList()->AddRectFilledMultiColor(ImVec2(x1, y1), ImVec2(x2, y2), ul, ur, br, bl);
			return 0;
		}

		static int AddText(lua_State* state)
		{
			float x          = (float)luaL_checknumber(state, 1);
			float y          = (float)luaL_checknumber(state, 2);
			const char* text = CheckStringSafe(state, 3);
			int r            = (int)luaL_checkinteger(state, 4);
			int g            = (int)luaL_checkinteger(state, 5);
			int b            = (int)luaL_checkinteger(state, 6);
			int a            = (int)luaL_checkinteger(state, 7);
			ImGui::GetWindowDrawList()->AddText(ImVec2(x, y), PackColor(r, g, b, a), text);
			return 0;
		}

		static int AddTriangle(lua_State* state)
		{
			float x1        = (float)luaL_checknumber(state, 1);
			float y1        = (float)luaL_checknumber(state, 2);
			float x2        = (float)luaL_checknumber(state, 3);
			float y2        = (float)luaL_checknumber(state, 4);
			float x3        = (float)luaL_checknumber(state, 5);
			float y3        = (float)luaL_checknumber(state, 6);
			int r           = (int)luaL_checkinteger(state, 7);
			int g           = (int)luaL_checkinteger(state, 8);
			int b           = (int)luaL_checkinteger(state, 9);
			int a           = (int)luaL_checkinteger(state, 10);
			float thickness = (float)luaL_optnumber(state, 11, 1.0);
			ImGui::GetWindowDrawList()->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), PackColor(r, g, b, a), thickness);
			return 0;
		}

		static int AddTriangleFilled(lua_State* state)
		{
			float x1 = (float)luaL_checknumber(state, 1);
			float y1 = (float)luaL_checknumber(state, 2);
			float x2 = (float)luaL_checknumber(state, 3);
			float y2 = (float)luaL_checknumber(state, 4);
			float x3 = (float)luaL_checknumber(state, 5);
			float y3 = (float)luaL_checknumber(state, 6);
			int r    = (int)luaL_checkinteger(state, 7);
			int g    = (int)luaL_checkinteger(state, 8);
			int b    = (int)luaL_checkinteger(state, 9);
			int a    = (int)luaL_checkinteger(state, 10);
			ImGui::GetWindowDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3), PackColor(r, g, b, a));
			return 0;
		}

		// ----------------------------------------------------------------
		// Tables
		// ----------------------------------------------------------------

		static int BeginTable(lua_State* state)
		{
			const char* str_id = CheckStringSafe(state, 1);
			int columns        = (int)luaL_checkinteger(state, 2);
			int flags          = (int)luaL_optinteger(state, 3, 0);
			lua_pushboolean(state, ImGui::BeginTable(str_id, columns, flags));
			return 1;
		}

		static int EndTable(lua_State*)
		{
			ImGui::EndTable();
			return 0;
		}

		static int TableNextColumn(lua_State*)
		{
			ImGui::TableNextColumn();
			return 0;
		}

		static int TableNextRow(lua_State*)
		{
			ImGui::TableNextRow();
			return 0;
		}

		static int TableSetColumnIndex(lua_State* state)
		{
			int column = (int)luaL_checkinteger(state, 1);
			lua_pushboolean(state, ImGui::TableSetColumnIndex(column));
			return 1;
		}

		static int TableSetupColumn(lua_State* state)
		{
			const char* str_id = CheckStringSafe(state, 1);
			int flags          = (int)luaL_checkinteger(state, 2);
			ImGui::TableSetupColumn(str_id, flags);
			return 0;
		}

		// Submits one header row using the labels from prior TableSetupColumn
		// calls. Call once per table, after all TableSetupColumn calls and
		// before the first data row.
		static int TableHeadersRow(lua_State*)
		{
			ImGui::TableHeadersRow();
			return 0;
		}

		// ----------------------------------------------------------------
		// Color conversion
		// ----------------------------------------------------------------

		static int ColorConvertFloat4ToU32(lua_State* state)
		{
			float v[4];
			ReadFloatArray(state, 1, v, 4);
			lua_pushinteger(state, ImGui::ColorConvertFloat4ToU32(ImVec4(v[0], v[1], v[2], v[3])));
			return 1;
		}

		static int ColorConvertRGBAToU32(lua_State* state)
		{
			int v[4];
			ReadIntArray(state, 1, v, 4);
			lua_pushinteger(state, IM_COL32(v[0], v[1], v[2], v[3]));
			return 1;
		}

		static int ColorConvertU32ToFloat4(lua_State* state)
		{
			ImU32 c = (ImU32)luaL_checkinteger(state, 1);
			ImVec4 v = ImGui::ColorConvertU32ToFloat4(c);
			float arr[4] = {v.x, v.y, v.z, v.w};
			PushFloatArray(state, arr, 4);
			return 1;
		}

		static int ColorConvertRGBtoHSV(lua_State* state)
		{
			float r = (float)luaL_checknumber(state, 1);
			float g = (float)luaL_checknumber(state, 2);
			float b = (float)luaL_checknumber(state, 3);
			float h, s, v;
			ImGui::ColorConvertRGBtoHSV(r, g, b, h, s, v);
			lua_pushnumber(state, h);
			lua_pushnumber(state, s);
			lua_pushnumber(state, v);
			return 3;
		}

		static int ColorConvertHSVtoRGB(lua_State* state)
		{
			float h = (float)luaL_checknumber(state, 1);
			float s = (float)luaL_checknumber(state, 2);
			float v = (float)luaL_checknumber(state, 3);
			float r, g, b;
			ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b);
			lua_pushnumber(state, r);
			lua_pushnumber(state, g);
			lua_pushnumber(state, b);
			return 3;
		}

		// ----------------------------------------------------------------
		// Misc getters
		// ----------------------------------------------------------------

		static int GetDisplaySize(lua_State* state)
		{
			ImVec2 sz = ImGui::GetIO().DisplaySize;
			lua_pushnumber(state, sz.x);
			lua_pushnumber(state, sz.y);
			return 2;
		}

		static int GetFrameRate(lua_State* state)
		{
			lua_pushnumber(state, ImGui::GetIO().Framerate);
			return 1;
		}

		// ----------------------------------------------------------------
		// Windows
		// ----------------------------------------------------------------

		static int Begin(lua_State* state)
		{
			const char* name = CheckStringSafe(state, 1);
			int top          = lua_gettop(state);

			if (top >= 2 && lua_type(state, 2) == LUA_TBOOLEAN)
			{
				bool open    = lua_toboolean(state, 2);
				int flags    = (int)luaL_optinteger(state, 3, 0);
				bool draw    = ImGui::Begin(name, &open, flags);
				lua_pushboolean(state, open);
				lua_pushboolean(state, draw);
				return 2;
			}

			int flags = (int)luaL_optinteger(state, 3, 0);
			bool draw = ImGui::Begin(name, nullptr, flags);
			lua_pushboolean(state, draw);
			return 1;
		}

		static int End(lua_State*)
		{
			ImGui::End();
			return 0;
		}

		static int BeginChild(lua_State* state)
		{
			const char* name = CheckStringSafe(state, 1);
			float sx         = (float)luaL_optnumber(state, 2, 0.0);
			float sy         = (float)luaL_optnumber(state, 3, 0.0);
			bool border      = lua_isnoneornil(state, 4) ? false : lua_toboolean(state, 4);
			int flags        = (int)luaL_optinteger(state, 5, 0);
			ImGuiChildFlags child_flags = border ? ImGuiChildFlags_Borders : ImGuiChildFlags_None;
			lua_pushboolean(state, ImGui::BeginChild(name, ImVec2(sx, sy), child_flags, flags));
			return 1;
		}

		static int EndChild(lua_State*)
		{
			ImGui::EndChild();
			return 0;
		}

		// ----------------------------------------------------------------
		// Window utilities
		// ----------------------------------------------------------------

		static int IsWindowAppearing(lua_State* state)
		{
			lua_pushboolean(state, ImGui::IsWindowAppearing());
			return 1;
		}

		static int IsWindowCollapsed(lua_State* state)
		{
			lua_pushboolean(state, ImGui::IsWindowCollapsed());
			return 1;
		}

		static int IsWindowFocused(lua_State* state)
		{
			int flags = (int)luaL_optinteger(state, 1, 0);
			lua_pushboolean(state, ImGui::IsWindowFocused(flags));
			return 1;
		}

		static int IsWindowHovered(lua_State* state)
		{
			int flags = (int)luaL_optinteger(state, 1, 0);
			lua_pushboolean(state, ImGui::IsWindowHovered(flags));
			return 1;
		}

		static int GetWindowPos(lua_State* state)
		{
			ImVec2 v = ImGui::GetWindowPos();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetWindowSize(lua_State* state)
		{
			ImVec2 v = ImGui::GetWindowSize();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetWindowWidth(lua_State* state)
		{
			lua_pushnumber(state, ImGui::GetWindowWidth());
			return 1;
		}

		static int GetWindowHeight(lua_State* state)
		{
			lua_pushnumber(state, ImGui::GetWindowHeight());
			return 1;
		}

		static int SetNextWindowPos(lua_State* state)
		{
			float x     = (float)luaL_checknumber(state, 1);
			float y     = (float)luaL_checknumber(state, 2);
			int cond    = (int)luaL_optinteger(state, 3, 0);
			float px    = (float)luaL_optnumber(state, 4, 0.0);
			float py    = (float)luaL_optnumber(state, 5, 0.0);
			ImGui::SetNextWindowPos(ImVec2(x, y), cond, ImVec2(px, py));
			return 0;
		}

		static int SetNextWindowSize(lua_State* state)
		{
			float x  = (float)luaL_checknumber(state, 1);
			float y  = (float)luaL_checknumber(state, 2);
			int cond = (int)luaL_optinteger(state, 3, 0);
			ImGui::SetNextWindowSize(ImVec2(x, y), cond);
			return 0;
		}

		static int SetNextWindowSizeConstraints(lua_State* state)
		{
			float minx = (float)luaL_checknumber(state, 1);
			float miny = (float)luaL_checknumber(state, 2);
			float maxx = (float)luaL_checknumber(state, 3);
			float maxy = (float)luaL_checknumber(state, 4);
			ImGui::SetNextWindowSizeConstraints(ImVec2(minx, miny), ImVec2(maxx, maxy));
			return 0;
		}

		static int SetNextWindowContentSize(lua_State* state)
		{
			float x = (float)luaL_checknumber(state, 1);
			float y = (float)luaL_checknumber(state, 2);
			ImGui::SetNextWindowContentSize(ImVec2(x, y));
			return 0;
		}

		static int SetNextWindowCollapsed(lua_State* state)
		{
			bool c   = CheckBooleanSafe(state, 1);
			int cond = (int)luaL_optinteger(state, 2, 0);
			ImGui::SetNextWindowCollapsed(c, cond);
			return 0;
		}

		static int SetNextWindowFocus(lua_State*)
		{
			ImGui::SetNextWindowFocus();
			return 0;
		}

		static int SetNextWindowBgAlpha(lua_State* state)
		{
			ImGui::SetNextWindowBgAlpha((float)luaL_checknumber(state, 1));
			return 0;
		}

		// Overload: SetWindowPos(x, y, cond?) or SetWindowPos(name, x, y, cond?)
		static int SetWindowPos(lua_State* state)
		{
			if (lua_type(state, 1) == LUA_TSTRING)
			{
				const char* name = lua_tostring(state, 1);
				float x          = (float)luaL_checknumber(state, 2);
				float y          = (float)luaL_checknumber(state, 3);
				int cond         = (int)luaL_optinteger(state, 4, 0);
				ImGui::SetWindowPos(name, ImVec2(x, y), cond);
			}
			else
			{
				float x  = (float)luaL_checknumber(state, 1);
				float y  = (float)luaL_checknumber(state, 2);
				int cond = (int)luaL_optinteger(state, 3, 0);
				ImGui::SetWindowPos(ImVec2(x, y), cond);
			}
			return 0;
		}

		// Overload: SetWindowSize(x, y, cond?) or SetWindowSize(name, x, y, cond?)
		static int SetWindowSize(lua_State* state)
		{
			if (lua_type(state, 1) == LUA_TSTRING)
			{
				const char* name = lua_tostring(state, 1);
				float x          = (float)luaL_checknumber(state, 2);
				float y          = (float)luaL_checknumber(state, 3);
				int cond         = (int)luaL_optinteger(state, 4, 0);
				ImGui::SetWindowSize(name, ImVec2(x, y), cond);
			}
			else
			{
				float x  = (float)luaL_checknumber(state, 1);
				float y  = (float)luaL_checknumber(state, 2);
				int cond = (int)luaL_optinteger(state, 3, 0);
				ImGui::SetWindowSize(ImVec2(x, y), cond);
			}
			return 0;
		}

		// Overload: SetWindowCollapsed(c, cond?) or SetWindowCollapsed(name, c, cond?)
		static int SetWindowCollapsed(lua_State* state)
		{
			if (lua_type(state, 1) == LUA_TSTRING)
			{
				const char* name = lua_tostring(state, 1);
				bool c           = CheckBooleanSafe(state, 2);
				int cond         = (int)luaL_optinteger(state, 3, 0);
				ImGui::SetWindowCollapsed(name, c, cond);
			}
			else
			{
				bool c   = CheckBooleanSafe(state, 1);
				int cond = (int)luaL_optinteger(state, 2, 0);
				ImGui::SetWindowCollapsed(c, cond);
			}
			return 0;
		}

		// Overload: SetWindowFocus() or SetWindowFocus(name)
		static int SetWindowFocus(lua_State* state)
		{
			if (lua_gettop(state) >= 1 && lua_type(state, 1) == LUA_TSTRING)
				ImGui::SetWindowFocus(lua_tostring(state, 1));
			else
				ImGui::SetWindowFocus();
			return 0;
		}

		static int SetWindowFontScale(lua_State* state)
		{
			ImGui::SetWindowFontScale((float)luaL_checknumber(state, 1));
			return 0;
		}

		// ----------------------------------------------------------------
		// Content region
		// ----------------------------------------------------------------

		static int GetContentRegionMax(lua_State* state)
		{
			ImVec2 v = ImGui::GetContentRegionMax();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetContentRegionAvail(lua_State* state)
		{
			ImVec2 v = ImGui::GetContentRegionAvail();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetWindowContentRegionMin(lua_State* state)
		{
			ImVec2 v = ImGui::GetWindowContentRegionMin();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetWindowContentRegionMax(lua_State* state)
		{
			ImVec2 v = ImGui::GetWindowContentRegionMax();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		// ----------------------------------------------------------------
		// Scrolling
		// ----------------------------------------------------------------

		static int GetScrollX(lua_State* state) { lua_pushnumber(state, ImGui::GetScrollX()); return 1; }
		static int GetScrollY(lua_State* state) { lua_pushnumber(state, ImGui::GetScrollY()); return 1; }
		static int GetScrollMaxX(lua_State* state) { lua_pushnumber(state, ImGui::GetScrollMaxX()); return 1; }
		static int GetScrollMaxY(lua_State* state) { lua_pushnumber(state, ImGui::GetScrollMaxY()); return 1; }

		static int SetScrollX(lua_State* state)
		{
			ImGui::SetScrollX((float)luaL_checknumber(state, 1));
			return 0;
		}

		static int SetScrollY(lua_State* state)
		{
			ImGui::SetScrollY((float)luaL_checknumber(state, 1));
			return 0;
		}

		static int SetScrollHereX(lua_State* state)
		{
			ImGui::SetScrollHereX((float)luaL_optnumber(state, 1, 0.5));
			return 0;
		}

		static int SetScrollHereY(lua_State* state)
		{
			ImGui::SetScrollHereY((float)luaL_optnumber(state, 1, 0.5));
			return 0;
		}

		static int SetScrollFromPosX(lua_State* state)
		{
			float lx = (float)luaL_checknumber(state, 1);
			float c  = (float)luaL_optnumber(state, 2, 0.5);
			ImGui::SetScrollFromPosX(lx, c);
			return 0;
		}

		static int SetScrollFromPosY(lua_State* state)
		{
			float ly = (float)luaL_checknumber(state, 1);
			float c  = (float)luaL_optnumber(state, 2, 0.5);
			ImGui::SetScrollFromPosY(ly, c);
			return 0;
		}

		// ----------------------------------------------------------------
		// Parameter stacks (shared)
		// ----------------------------------------------------------------

		static int PushStyleColor(lua_State* state)
		{
			int idx = (int)luaL_checkinteger(state, 1);
			float r = (float)luaL_checknumber(state, 2);
			float g = (float)luaL_checknumber(state, 3);
			float b = (float)luaL_checknumber(state, 4);
			float a = (float)luaL_checknumber(state, 5);
			ImGui::PushStyleColor(idx, ImVec4(r, g, b, a));
			return 0;
		}

		static int PopStyleColor(lua_State* state)
		{
			int count = (int)luaL_optinteger(state, 1, 1);
			ImGui::PopStyleColor(count);
			return 0;
		}

		// Overload: PushStyleVar(idx, value) or PushStyleVar(idx, value_x, value_y)
		static int PushStyleVar(lua_State* state)
		{
			int idx = (int)luaL_checkinteger(state, 1);
			if (lua_gettop(state) >= 3)
			{
				float x = (float)luaL_checknumber(state, 2);
				float y = (float)luaL_checknumber(state, 3);
				ImGui::PushStyleVar(idx, ImVec2(x, y));
			}
			else
			{
				ImGui::PushStyleVar(idx, (float)luaL_checknumber(state, 2));
			}
			return 0;
		}

		static int PopStyleVar(lua_State* state)
		{
			int count = (int)luaL_optinteger(state, 1, 1);
			ImGui::PopStyleVar(count);
			return 0;
		}

		static int GetStyleColorVec4(lua_State* state)
		{
			int idx = (int)luaL_checkinteger(state, 1);
			ImVec4 c = ImGui::GetStyleColorVec4(idx);
			lua_pushnumber(state, c.x);
			lua_pushnumber(state, c.y);
			lua_pushnumber(state, c.z);
			lua_pushnumber(state, c.w);
			return 4;
		}

		static int GetFontSize(lua_State* state)
		{
			lua_pushnumber(state, ImGui::GetFontSize());
			return 1;
		}

		static int GetFontTexUvWhitePixel(lua_State* state)
		{
			ImVec2 v = ImGui::GetFontTexUvWhitePixel();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		// ----------------------------------------------------------------
		// Parameter stacks (current window)
		// ----------------------------------------------------------------

		static int PushItemWidth(lua_State* state)
		{
			ImGui::PushItemWidth((float)luaL_checknumber(state, 1));
			return 0;
		}

		static int PopItemWidth(lua_State*)
		{
			ImGui::PopItemWidth();
			return 0;
		}

		static int SetNextItemWidth(lua_State* state)
		{
			ImGui::SetNextItemWidth((float)luaL_checknumber(state, 1));
			return 0;
		}

		static int CalcItemWidth(lua_State* state)
		{
			lua_pushnumber(state, ImGui::CalcItemWidth());
			return 1;
		}

		static int PushTextWrapPos(lua_State* state)
		{
			ImGui::PushTextWrapPos((float)luaL_optnumber(state, 1, 0.0));
			return 0;
		}

		static int PopTextWrapPos(lua_State*)
		{
			ImGui::PopTextWrapPos();
			return 0;
		}

		static int PushButtonRepeat(lua_State* state)
		{
			ImGui::PushButtonRepeat(CheckBooleanSafe(state, 1));
			return 0;
		}

		static int PopButtonRepeat(lua_State*)
		{
			ImGui::PopButtonRepeat();
			return 0;
		}

		// ----------------------------------------------------------------
		// Cursor / layout
		// ----------------------------------------------------------------

		static int Separator(lua_State*) { ImGui::Separator(); return 0; }

		static int SeparatorText(lua_State* state)
		{
			ImGui::SeparatorText(CheckStringSafe(state, 1));
			return 0;
		}

		static int BeginDisabled(lua_State* state)
		{
			bool disabled = lua_isnoneornil(state, 1) ? true : lua_toboolean(state, 1);
			ImGui::BeginDisabled(disabled);
			return 0;
		}

		static int EndDisabled(lua_State*) { ImGui::EndDisabled(); return 0; }

		// Returns a read-only snapshot of the active style as a table. Vec2
		// fields are { x = , y = } sub-tables. Not all fields are exposed.
		static int GetStyle(lua_State* state)
		{
			const ImGuiStyle& st = ImGui::GetStyle();

			auto push_vec2 = [&](const char* name, const ImVec2& v) {
				lua_newtable(state);
				lua_pushnumber(state, v.x);
				lua_setfield(state, -2, "x");
				lua_pushnumber(state, v.y);
				lua_setfield(state, -2, "y");
				lua_setfield(state, -2, name);
			};
			auto push_num = [&](const char* name, float v) {
				lua_pushnumber(state, v);
				lua_setfield(state, -2, name);
			};

			lua_newtable(state);
			push_num("Alpha", st.Alpha);
			push_num("DisabledAlpha", st.DisabledAlpha);
			push_vec2("WindowPadding", st.WindowPadding);
			push_num("WindowRounding", st.WindowRounding);
			push_num("WindowBorderSize", st.WindowBorderSize);
			push_vec2("WindowMinSize", st.WindowMinSize);
			push_vec2("WindowTitleAlign", st.WindowTitleAlign);
			push_num("ChildRounding", st.ChildRounding);
			push_num("ChildBorderSize", st.ChildBorderSize);
			push_num("PopupRounding", st.PopupRounding);
			push_num("PopupBorderSize", st.PopupBorderSize);
			push_vec2("FramePadding", st.FramePadding);
			push_num("FrameRounding", st.FrameRounding);
			push_num("FrameBorderSize", st.FrameBorderSize);
			push_vec2("ItemSpacing", st.ItemSpacing);
			push_vec2("ItemInnerSpacing", st.ItemInnerSpacing);
			push_vec2("CellPadding", st.CellPadding);
			push_num("IndentSpacing", st.IndentSpacing);
			push_num("ScrollbarSize", st.ScrollbarSize);
			push_num("ScrollbarRounding", st.ScrollbarRounding);
			push_num("GrabMinSize", st.GrabMinSize);
			push_num("GrabRounding", st.GrabRounding);
			push_vec2("ButtonTextAlign", st.ButtonTextAlign);
			push_vec2("SelectableTextAlign", st.SelectableTextAlign);
			return 1;
		}

		static int SameLine(lua_State* state)
		{
			float off = (float)luaL_optnumber(state, 1, 0.0);
			float sp  = (float)luaL_optnumber(state, 2, -1.0);
			ImGui::SameLine(off, sp);
			return 0;
		}

		static int NewLine(lua_State*) { ImGui::NewLine(); return 0; }
		static int Spacing(lua_State*) { ImGui::Spacing(); return 0; }

		static int Dummy(lua_State* state)
		{
			float x = (float)luaL_checknumber(state, 1);
			float y = (float)luaL_checknumber(state, 2);
			ImGui::Dummy(ImVec2(x, y));
			return 0;
		}

		static int Indent(lua_State* state)
		{
			ImGui::Indent((float)luaL_optnumber(state, 1, 0.0));
			return 0;
		}

		static int Unindent(lua_State* state)
		{
			ImGui::Unindent((float)luaL_optnumber(state, 1, 0.0));
			return 0;
		}

		static int BeginGroup(lua_State*) { ImGui::BeginGroup(); return 0; }
		static int EndGroup(lua_State*)   { ImGui::EndGroup();   return 0; }

		static int GetCursorPos(lua_State* state)
		{
			ImVec2 v = ImGui::GetCursorPos();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetCursorPosX(lua_State* state) { lua_pushnumber(state, ImGui::GetCursorPosX()); return 1; }
		static int GetCursorPosY(lua_State* state) { lua_pushnumber(state, ImGui::GetCursorPosY()); return 1; }

		static int SetCursorPos(lua_State* state)
		{
			float x = (float)luaL_checknumber(state, 1);
			float y = (float)luaL_checknumber(state, 2);
			ImGui::SetCursorPos(ImVec2(x, y));
			return 0;
		}

		static int SetCursorPosX(lua_State* state) { ImGui::SetCursorPosX((float)luaL_checknumber(state, 1)); return 0; }
		static int SetCursorPosY(lua_State* state) { ImGui::SetCursorPosY((float)luaL_checknumber(state, 1)); return 0; }

		static int GetCursorStartPos(lua_State* state)
		{
			ImVec2 v = ImGui::GetCursorStartPos();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetCursorScreenPos(lua_State* state)
		{
			ImVec2 v = ImGui::GetCursorScreenPos();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int SetCursorScreenPos(lua_State* state)
		{
			float x = (float)luaL_checknumber(state, 1);
			float y = (float)luaL_checknumber(state, 2);
			ImGui::SetCursorScreenPos(ImVec2(x, y));
			return 0;
		}

		static int AlignTextToFramePadding(lua_State*) { ImGui::AlignTextToFramePadding(); return 0; }

		static int GetTextLineHeight(lua_State* state)             { lua_pushnumber(state, ImGui::GetTextLineHeight()); return 1; }
		static int GetTextLineHeightWithSpacing(lua_State* state)  { lua_pushnumber(state, ImGui::GetTextLineHeightWithSpacing()); return 1; }
		static int GetFrameHeight(lua_State* state)                { lua_pushnumber(state, ImGui::GetFrameHeight()); return 1; }
		static int GetFrameHeightWithSpacing(lua_State* state)     { lua_pushnumber(state, ImGui::GetFrameHeightWithSpacing()); return 1; }

		// ----------------------------------------------------------------
		// ID stack
		// ----------------------------------------------------------------

		// Overload: PushID(int) | PushID(str) | PushID(str_begin, str_end)
		static int PushID(lua_State* state)
		{
			int top = lua_gettop(state);
			if (top >= 2 && lua_type(state, 1) == LUA_TSTRING && lua_type(state, 2) == LUA_TSTRING)
			{
				ImGui::PushID(lua_tostring(state, 1), lua_tostring(state, 2));
			}
			else if (lua_type(state, 1) == LUA_TSTRING)
			{
				ImGui::PushID(lua_tostring(state, 1));
			}
			else
			{
				ImGui::PushID((int)luaL_checkinteger(state, 1));
			}
			return 0;
		}

		static int PopID(lua_State*) { ImGui::PopID(); return 0; }

		// Overload: GetID(str) | GetID(str_begin, str_end)
		static int GetID(lua_State* state)
		{
			ImGuiID id;
			if (lua_gettop(state) >= 2)
				id = ImGui::GetID(CheckStringSafe(state, 1), CheckStringSafe(state, 2));
			else
				id = ImGui::GetID(CheckStringSafe(state, 1));
			lua_pushinteger(state, id);
			return 1;
		}

		// ----------------------------------------------------------------
		// Text widgets
		// ----------------------------------------------------------------

		static int TextUnformatted(lua_State* state)
		{
			const char* text = CheckStringSafe(state, 1);
			const char* end  = lua_isnoneornil(state, 2) ? nullptr : luaL_checkstring(state, 2);
			ImGui::TextUnformatted(text, end);
			return 0;
		}

		// Lua's `...` variadic format is handled by the caller via string.format; we accept
		// the already-formatted string here verbatim.
		static int Text(lua_State* state)
		{
			ImGui::TextUnformatted(luaL_checkstring(state, 1));
			return 0;
		}

		static int TextColored(lua_State* state)
		{
			float r          = (float)luaL_checknumber(state, 1);
			float g          = (float)luaL_checknumber(state, 2);
			float b          = (float)luaL_checknumber(state, 3);
			float a          = (float)luaL_checknumber(state, 4);
			const char* text = CheckStringSafe(state, 5);
			ImGui::TextColored(ImVec4(r, g, b, a), "%s", text);
			return 0;
		}

		static int TextDisabled(lua_State* state)
		{
			ImGui::TextDisabled("%s", luaL_checkstring(state, 1));
			return 0;
		}

		static int TextWrapped(lua_State* state)
		{
			ImGui::TextWrapped("%s", luaL_checkstring(state, 1));
			return 0;
		}

		static int LabelText(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			const char* text  = CheckStringSafe(state, 2);
			ImGui::LabelText(label, "%s", text);
			return 0;
		}

		static int BulletText(lua_State* state)
		{
			ImGui::BulletText("%s", luaL_checkstring(state, 1));
			return 0;
		}

		// ----------------------------------------------------------------
		// Main widgets
		// ----------------------------------------------------------------

		static int Button(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float sx = (float)luaL_optnumber(state, 2, 0.0);
			float sy = (float)luaL_optnumber(state, 3, 0.0);
			lua_pushboolean(state, ImGui::Button(label, ImVec2(sx, sy)));
			return 1;
		}

		static int SmallButton(lua_State* state)
		{
			lua_pushboolean(state, ImGui::SmallButton(CheckStringSafe(state, 1)));
			return 1;
		}

		static int InvisibleButton(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float sx          = (float)luaL_checknumber(state, 2);
			float sy          = (float)luaL_checknumber(state, 3);
			lua_pushboolean(state, ImGui::InvisibleButton(label, ImVec2(sx, sy)));
			return 1;
		}

		static int ArrowButton(lua_State* state)
		{
			const char* str_id = CheckStringSafe(state, 1);
			ImGuiDir dir       = (ImGuiDir)luaL_checkinteger(state, 2);
			lua_pushboolean(state, ImGui::ArrowButton(str_id, dir));
			return 1;
		}

		static int Checkbox(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			bool value        = CheckBooleanSafe(state, 2);
			bool pressed      = ImGui::Checkbox(label, &value);
			lua_pushboolean(state, value);
			lua_pushboolean(state, pressed);
			return 2;
		}

		// Overload: RadioButton(label, active: bool) | RadioButton(label, value: int, v_button: int)
		static int RadioButton(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			if (lua_type(state, 2) == LUA_TBOOLEAN)
			{
				lua_pushboolean(state, ImGui::RadioButton(label, lua_toboolean(state, 2)));
				return 1;
			}
			int value    = (int)luaL_checkinteger(state, 2);
			int v_button = (int)luaL_checkinteger(state, 3);
			bool pressed = ImGui::RadioButton(label, &value, v_button);
			lua_pushinteger(state, value);
			lua_pushboolean(state, pressed);
			return 2;
		}

		static int ProgressBar(lua_State* state)
		{
			float fraction      = (float)luaL_checknumber(state, 1);
			float sx            = (float)luaL_optnumber(state, 2, -FLT_MIN);
			float sy            = (float)luaL_optnumber(state, 3, 0.0);
			const char* overlay = OptString(state, 4);
			ImGui::ProgressBar(fraction, ImVec2(sx, sy), overlay);
			return 0;
		}

		static int Bullet(lua_State*) { ImGui::Bullet(); return 0; }

		// ----------------------------------------------------------------
		// Combo box
		// ----------------------------------------------------------------

		static int BeginCombo(lua_State* state)
		{
			const char* label   = CheckStringSafe(state, 1);
			const char* preview = CheckStringSafe(state, 2);
			int flags           = (int)luaL_optinteger(state, 3, 0);
			lua_pushboolean(state, ImGui::BeginCombo(label, preview, flags));
			return 1;
		}

		static int EndCombo(lua_State*) { ImGui::EndCombo(); return 0; }

		// Overload: Combo(label, current, items_table, items_count, popup_max?)
		// Overload: Combo(label, current, items_separated_by_zeros, popup_max?)
		static int Combo(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int current       = (int)luaL_checkinteger(state, 2);
			bool clicked;

			if (lua_type(state, 3) == LUA_TSTRING)
			{
				const char* items_zero = lua_tostring(state, 3);
				int popup_max          = (int)luaL_optinteger(state, 4, -1);
				clicked                = ImGui::Combo(label, &current, items_zero, popup_max);
			}
			else
			{
				int items_count = (int)luaL_checkinteger(state, 4);
				std::vector<std::string> storage(items_count);
				std::vector<const char*> ptrs(items_count);
				for (int i = 0; i < items_count; i++)
				{
					lua_rawgeti(state, 3, i + 1);
					storage[i] = luaL_checkstring(state, -1);
					ptrs[i]    = storage[i].c_str();
					lua_pop(state, 1);
				}
				int popup_max = (int)luaL_optinteger(state, 5, -1);
				clicked       = ImGui::Combo(label, &current, ptrs.data(), items_count, popup_max);
			}

			lua_pushinteger(state, current);
			lua_pushboolean(state, clicked);
			return 2;
		}

		// ----------------------------------------------------------------
		// Drag widgets
		// ----------------------------------------------------------------

		static int DragFloat(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float value       = (float)luaL_checknumber(state, 2);
			float speed       = (float)luaL_optnumber(state, 3, 1.0);
			float vmin        = (float)luaL_optnumber(state, 4, 0.0);
			float vmax        = (float)luaL_optnumber(state, 5, 0.0);
			const char* fmt   = lua_isnoneornil(state, 6) ? "%.3f" : luaL_checkstring(state, 6);
			// `power` is deprecated in modern ImGui; flags are used instead. We accept and ignore it.
			bool used = ImGui::DragFloat(label, &value, speed, vmin, vmax, fmt, 0);
			lua_pushnumber(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		template<int N>
		static int DragFloatN(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float v[N];
			ReadFloatArray(state, 2, v, N);
			float speed     = (float)luaL_optnumber(state, 3, 1.0);
			float vmin      = (float)luaL_optnumber(state, 4, 0.0);
			float vmax      = (float)luaL_optnumber(state, 5, 0.0);
			const char* fmt = lua_isnoneornil(state, 6) ? "%.3f" : luaL_checkstring(state, 6);
			bool used;
			if constexpr (N == 2) used = ImGui::DragFloat2(label, v, speed, vmin, vmax, fmt, 0);
			else if constexpr (N == 3) used = ImGui::DragFloat3(label, v, speed, vmin, vmax, fmt, 0);
			else used = ImGui::DragFloat4(label, v, speed, vmin, vmax, fmt, 0);
			PushFloatArray(state, v, N);
			lua_pushboolean(state, used);
			return 2;
		}

		static int DragFloat2(lua_State* state) { return DragFloatN<2>(state); }
		static int DragFloat3(lua_State* state) { return DragFloatN<3>(state); }
		static int DragFloat4(lua_State* state) { return DragFloatN<4>(state); }

		static int DragInt(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int value         = (int)luaL_checkinteger(state, 2);
			float speed       = (float)luaL_optnumber(state, 3, 1.0);
			int vmin          = (int)luaL_optinteger(state, 4, 0);
			int vmax          = (int)luaL_optinteger(state, 5, 0);
			const char* fmt   = lua_isnoneornil(state, 6) ? "%d" : luaL_checkstring(state, 6);
			bool used = ImGui::DragInt(label, &value, speed, vmin, vmax, fmt, 0);
			lua_pushinteger(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		template<int N>
		static int DragIntN(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int v[N];
			ReadIntArray(state, 2, v, N);
			float speed     = (float)luaL_optnumber(state, 3, 1.0);
			int vmin        = (int)luaL_optinteger(state, 4, 0);
			int vmax        = (int)luaL_optinteger(state, 5, 0);
			const char* fmt = lua_isnoneornil(state, 6) ? "%d" : luaL_checkstring(state, 6);
			bool used;
			if constexpr (N == 2) used = ImGui::DragInt2(label, v, speed, vmin, vmax, fmt, 0);
			else if constexpr (N == 3) used = ImGui::DragInt3(label, v, speed, vmin, vmax, fmt, 0);
			else used = ImGui::DragInt4(label, v, speed, vmin, vmax, fmt, 0);
			PushIntArray(state, v, N);
			lua_pushboolean(state, used);
			return 2;
		}

		static int DragInt2(lua_State* state) { return DragIntN<2>(state); }
		static int DragInt3(lua_State* state) { return DragIntN<3>(state); }
		static int DragInt4(lua_State* state) { return DragIntN<4>(state); }

		// ----------------------------------------------------------------
		// Sliders
		// ----------------------------------------------------------------

		static int SliderFloat(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float value       = (float)luaL_checknumber(state, 2);
			float vmin        = (float)luaL_checknumber(state, 3);
			float vmax        = (float)luaL_checknumber(state, 4);
			const char* fmt   = lua_isnoneornil(state, 5) ? "%.3f" : luaL_checkstring(state, 5);
			bool used         = ImGui::SliderFloat(label, &value, vmin, vmax, fmt, 0);
			lua_pushnumber(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		template<int N>
		static int SliderFloatN(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float v[N];
			ReadFloatArray(state, 2, v, N);
			float vmin      = (float)luaL_checknumber(state, 3);
			float vmax      = (float)luaL_checknumber(state, 4);
			const char* fmt = lua_isnoneornil(state, 5) ? "%.3f" : luaL_checkstring(state, 5);
			bool used;
			if constexpr (N == 2) used = ImGui::SliderFloat2(label, v, vmin, vmax, fmt, 0);
			else if constexpr (N == 3) used = ImGui::SliderFloat3(label, v, vmin, vmax, fmt, 0);
			else used = ImGui::SliderFloat4(label, v, vmin, vmax, fmt, 0);
			PushFloatArray(state, v, N);
			lua_pushboolean(state, used);
			return 2;
		}

		static int SliderFloat2(lua_State* state) { return SliderFloatN<2>(state); }
		static int SliderFloat3(lua_State* state) { return SliderFloatN<3>(state); }
		static int SliderFloat4(lua_State* state) { return SliderFloatN<4>(state); }

		static int SliderAngle(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float v_rad       = (float)luaL_checknumber(state, 2);
			float vmin        = (float)luaL_optnumber(state, 3, -360.0);
			float vmax        = (float)luaL_optnumber(state, 4, 360.0);
			const char* fmt   = lua_isnoneornil(state, 5) ? "%.0f deg" : luaL_checkstring(state, 5);
			bool used         = ImGui::SliderAngle(label, &v_rad, vmin, vmax, fmt, 0);
			lua_pushnumber(state, v_rad);
			lua_pushboolean(state, used);
			return 2;
		}

		static int SliderInt(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int value         = (int)luaL_checkinteger(state, 2);
			int vmin          = (int)luaL_checkinteger(state, 3);
			int vmax          = (int)luaL_checkinteger(state, 4);
			const char* fmt   = lua_isnoneornil(state, 5) ? "%d" : luaL_checkstring(state, 5);
			bool used         = ImGui::SliderInt(label, &value, vmin, vmax, fmt, 0);
			lua_pushinteger(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		template<int N>
		static int SliderIntN(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int v[N];
			ReadIntArray(state, 2, v, N);
			int vmin        = (int)luaL_checkinteger(state, 3);
			int vmax        = (int)luaL_checkinteger(state, 4);
			const char* fmt = lua_isnoneornil(state, 5) ? "%d" : luaL_checkstring(state, 5);
			bool used;
			if constexpr (N == 2) used = ImGui::SliderInt2(label, v, vmin, vmax, fmt, 0);
			else if constexpr (N == 3) used = ImGui::SliderInt3(label, v, vmin, vmax, fmt, 0);
			else used = ImGui::SliderInt4(label, v, vmin, vmax, fmt, 0);
			PushIntArray(state, v, N);
			lua_pushboolean(state, used);
			return 2;
		}

		static int SliderInt2(lua_State* state) { return SliderIntN<2>(state); }
		static int SliderInt3(lua_State* state) { return SliderIntN<3>(state); }
		static int SliderInt4(lua_State* state) { return SliderIntN<4>(state); }

		static int VSliderFloat(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float sx          = (float)luaL_checknumber(state, 2);
			float sy          = (float)luaL_checknumber(state, 3);
			float value       = (float)luaL_checknumber(state, 4);
			float vmin        = (float)luaL_checknumber(state, 5);
			float vmax        = (float)luaL_checknumber(state, 6);
			const char* fmt   = lua_isnoneornil(state, 7) ? "%.3f" : luaL_checkstring(state, 7);
			bool used = ImGui::VSliderFloat(label, ImVec2(sx, sy), &value, vmin, vmax, fmt, 0);
			lua_pushnumber(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		static int VSliderInt(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float sx          = (float)luaL_checknumber(state, 2);
			float sy          = (float)luaL_checknumber(state, 3);
			int value         = (int)luaL_checkinteger(state, 4);
			int vmin          = (int)luaL_checkinteger(state, 5);
			int vmax          = (int)luaL_checkinteger(state, 6);
			const char* fmt   = lua_isnoneornil(state, 7) ? "%d" : luaL_checkstring(state, 7);
			bool used = ImGui::VSliderInt(label, ImVec2(sx, sy), &value, vmin, vmax, fmt, 0);
			lua_pushinteger(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		// ----------------------------------------------------------------
		// Input with keyboard
		// ----------------------------------------------------------------

		static int InputText(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			std::string buf   = CheckStringSafe(state, 2);
			int flags         = (int)luaL_optinteger(state, 3, 0);
			bool changed      = ImGui::InputText(label, &buf, flags);
			lua_pushstring(state, buf.c_str());
			lua_pushboolean(state, changed);
			return 2;
		}

		static int InputTextMultiline(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			std::string buf   = CheckStringSafe(state, 2);
			float sx          = (float)luaL_optnumber(state, 3, 0.0);
			float sy          = (float)luaL_optnumber(state, 4, 0.0);
			int flags         = (int)luaL_optinteger(state, 5, 0);
			bool changed      = ImGui::InputTextMultiline(label, &buf, ImVec2(sx, sy), flags);
			lua_pushstring(state, buf.c_str());
			lua_pushboolean(state, changed);
			return 2;
		}

		static int InputTextWithHint(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			const char* hint  = CheckStringSafe(state, 2);
			std::string buf   = CheckStringSafe(state, 3);
			int flags         = (int)luaL_optinteger(state, 4, 0);
			bool changed      = ImGui::InputTextWithHint(label, hint, &buf, flags);
			lua_pushstring(state, buf.c_str());
			lua_pushboolean(state, changed);
			return 2;
		}

		static int InputFloat(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float value       = (float)luaL_checknumber(state, 2);
			float step        = (float)luaL_optnumber(state, 3, 0.0);
			float step_fast   = (float)luaL_optnumber(state, 4, 0.0);
			const char* fmt   = lua_isnoneornil(state, 5) ? "%.3f" : luaL_checkstring(state, 5);
			int flags         = (int)luaL_optinteger(state, 6, 0);
			bool used         = ImGui::InputFloat(label, &value, step, step_fast, fmt, flags);
			lua_pushnumber(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		template<int N>
		static int InputFloatN(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float v[N];
			ReadFloatArray(state, 2, v, N);
			const char* fmt = lua_isnoneornil(state, 3) ? "%.3f" : luaL_checkstring(state, 3);
			int flags       = (int)luaL_optinteger(state, 4, 0);
			bool used;
			if constexpr (N == 2) used = ImGui::InputFloat2(label, v, fmt, flags);
			else if constexpr (N == 3) used = ImGui::InputFloat3(label, v, fmt, flags);
			else used = ImGui::InputFloat4(label, v, fmt, flags);
			PushFloatArray(state, v, N);
			lua_pushboolean(state, used);
			return 2;
		}

		static int InputFloat2(lua_State* state) { return InputFloatN<2>(state); }
		static int InputFloat3(lua_State* state) { return InputFloatN<3>(state); }
		static int InputFloat4(lua_State* state) { return InputFloatN<4>(state); }

		static int InputInt(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int value         = (int)luaL_checkinteger(state, 2);
			int step          = (int)luaL_optinteger(state, 3, 1);
			int step_fast     = (int)luaL_optinteger(state, 4, 100);
			int flags         = (int)luaL_optinteger(state, 5, 0);
			bool used         = ImGui::InputInt(label, &value, step, step_fast, flags);
			lua_pushinteger(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		template<int N>
		static int InputIntN(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int v[N];
			ReadIntArray(state, 2, v, N);
			int flags = (int)luaL_optinteger(state, 3, 0);
			bool used;
			if constexpr (N == 2) used = ImGui::InputInt2(label, v, flags);
			else if constexpr (N == 3) used = ImGui::InputInt3(label, v, flags);
			else used = ImGui::InputInt4(label, v, flags);
			PushIntArray(state, v, N);
			lua_pushboolean(state, used);
			return 2;
		}

		static int InputInt2(lua_State* state) { return InputIntN<2>(state); }
		static int InputInt3(lua_State* state) { return InputIntN<3>(state); }
		static int InputInt4(lua_State* state) { return InputIntN<4>(state); }

		static int InputDouble(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			double value      = luaL_checknumber(state, 2);
			double step       = luaL_optnumber(state, 3, 0.0);
			double step_fast  = luaL_optnumber(state, 4, 0.0);
			const char* fmt   = lua_isnoneornil(state, 5) ? "%.6f" : luaL_checkstring(state, 5);
			int flags         = (int)luaL_optinteger(state, 6, 0);
			bool used         = ImGui::InputDouble(label, &value, step, step_fast, fmt, flags);
			lua_pushnumber(state, value);
			lua_pushboolean(state, used);
			return 2;
		}

		// ----------------------------------------------------------------
		// Color editor / picker
		// ----------------------------------------------------------------

		static int ColorEdit3(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float c[3];
			ReadFloatArray(state, 2, c, 3);
			int flags = (int)luaL_optinteger(state, 3, 0);
			bool used = ImGui::ColorEdit3(label, c, flags);
			PushFloatArray(state, c, 3);
			lua_pushboolean(state, used);
			return 2;
		}

		static int ColorEdit4(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float c[4];
			ReadFloatArray(state, 2, c, 4);
			int flags = (int)luaL_optinteger(state, 3, 0);
			bool used = ImGui::ColorEdit4(label, c, flags);
			PushFloatArray(state, c, 4);
			lua_pushboolean(state, used);
			return 2;
		}

		static int ColorPicker3(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float c[3];
			ReadFloatArray(state, 2, c, 3);
			int flags = (int)luaL_optinteger(state, 3, 0);
			bool used = ImGui::ColorPicker3(label, c, flags);
			PushFloatArray(state, c, 3);
			lua_pushboolean(state, used);
			return 2;
		}

		static int ColorPicker4(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			float c[4];
			ReadFloatArray(state, 2, c, 4);
			int flags = (int)luaL_optinteger(state, 3, 0);
			bool used = ImGui::ColorPicker4(label, c, flags);
			PushFloatArray(state, c, 4);
			lua_pushboolean(state, used);
			return 2;
		}

		static int ColorButton(lua_State* state)
		{
			const char* desc_id = CheckStringSafe(state, 1);
			float c[4];
			ReadFloatArray(state, 2, c, 4);
			int flags = (int)luaL_optinteger(state, 3, 0);
			float sx  = (float)luaL_optnumber(state, 4, 0.0);
			float sy  = (float)luaL_optnumber(state, 5, 0.0);
			lua_pushboolean(state, ImGui::ColorButton(desc_id, ImVec4(c[0], c[1], c[2], c[3]), flags, ImVec2(sx, sy)));
			return 1;
		}

		static int SetColorEditOptions(lua_State* state)
		{
			ImGui::SetColorEditOptions((int)luaL_checkinteger(state, 1));
			return 0;
		}

		// ----------------------------------------------------------------
		// Trees
		// ----------------------------------------------------------------

		static int TreeNode(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			if (lua_isnoneornil(state, 2))
				lua_pushboolean(state, ImGui::TreeNode(label));
			else
				lua_pushboolean(state, ImGui::TreeNode(label, "%s", luaL_checkstring(state, 2)));
			return 1;
		}

		static int TreeNodeEx(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int flags         = (int)luaL_optinteger(state, 2, 0);
			if (lua_isnoneornil(state, 3))
				lua_pushboolean(state, ImGui::TreeNodeEx(label, flags));
			else
				lua_pushboolean(state, ImGui::TreeNodeEx(label, flags, "%s", luaL_checkstring(state, 3)));
			return 1;
		}

		static int TreePush(lua_State* state)
		{
			ImGui::TreePush(CheckStringSafe(state, 1));
			return 0;
		}

		static int TreePop(lua_State*) { ImGui::TreePop(); return 0; }

		static int GetTreeNodeToLabelSpacing(lua_State* state)
		{
			lua_pushnumber(state, ImGui::GetTreeNodeToLabelSpacing());
			return 1;
		}

		// Overload: CollapsingHeader(label, flags?) | CollapsingHeader(label, open: bool, flags?)
		static int CollapsingHeader(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			if (lua_type(state, 2) == LUA_TBOOLEAN)
			{
				bool open    = lua_toboolean(state, 2);
				int flags    = (int)luaL_optinteger(state, 3, 0);
				bool notCol  = ImGui::CollapsingHeader(label, &open, flags);
				lua_pushboolean(state, open);
				lua_pushboolean(state, notCol);
				return 2;
			}
			int flags = (int)luaL_optinteger(state, 2, 0);
			lua_pushboolean(state, ImGui::CollapsingHeader(label, flags));
			return 1;
		}

		static int SetNextItemOpen(lua_State* state)
		{
			bool open = CheckBooleanSafe(state, 1);
			int cond  = (int)luaL_optinteger(state, 2, 0);
			ImGui::SetNextItemOpen(open, cond);
			return 0;
		}

		// ----------------------------------------------------------------
		// Selectables
		// ----------------------------------------------------------------

		static int Selectable(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			bool selected     = lua_isnoneornil(state, 2) ? false : lua_toboolean(state, 2);
			int flags         = (int)luaL_optinteger(state, 3, 0);
			float sx          = (float)luaL_optnumber(state, 4, 0.0);
			float sy          = (float)luaL_optnumber(state, 5, 0.0);
			bool clicked      = ImGui::Selectable(label, &selected, flags, ImVec2(sx, sy));
			(void)clicked; // doc says it returns the new selected state
			lua_pushboolean(state, selected);
			return 1;
		}

		// ----------------------------------------------------------------
		// List boxes
		// ----------------------------------------------------------------

		static int ListBox(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int current       = (int)luaL_checkinteger(state, 2);
			int items_count   = (int)luaL_checkinteger(state, 4);
			std::vector<std::string> storage(items_count);
			std::vector<const char*> ptrs(items_count);
			for (int i = 0; i < items_count; i++)
			{
				lua_rawgeti(state, 3, i + 1);
				storage[i] = luaL_checkstring(state, -1);
				ptrs[i]    = storage[i].c_str();
				lua_pop(state, 1);
			}
			int height_in_items = (int)luaL_optinteger(state, 5, -1);
			bool clicked = ImGui::ListBox(label, &current, ptrs.data(), items_count, height_in_items);
			lua_pushinteger(state, current);
			lua_pushboolean(state, clicked);
			return 2;
		}

		// BeginListBox(label, size_x, size_y) | BeginListBox(label, items_count, height?)
		// The second overload's height is computed using the standard sizing formula.
		// (Was ListBoxHeader in old ImGui, renamed to BeginListBox.)
		static int BeginListBox(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			int top           = lua_gettop(state);
			if (top >= 3)
			{
				float sx = (float)luaL_checknumber(state, 2);
				float sy = (float)luaL_checknumber(state, 3);
				lua_pushboolean(state, ImGui::BeginListBox(label, ImVec2(sx, sy)));
				return 1;
			}
			// (label, items_count, height?) form — approximate height based on text line height
			int items_count     = (int)luaL_checkinteger(state, 2);
			int height_in_items = (int)luaL_optinteger(state, 3, -1);
			if (height_in_items < 0)
				height_in_items = items_count < 7 ? items_count : 7;
			float h = ImGui::GetTextLineHeightWithSpacing() * (height_in_items + 0.25f) + ImGui::GetStyle().FramePadding.y * 2.0f;
			lua_pushboolean(state, ImGui::BeginListBox(label, ImVec2(0.0f, h)));
			return 1;
		}

		// (Was ListBoxFooter in old ImGui, renamed to EndListBox.)
		static int EndListBox(lua_State*)
		{
			ImGui::EndListBox();
			return 0;
		}

		// ----------------------------------------------------------------
		// Value() helpers
		// ----------------------------------------------------------------
		static int Value(lua_State* state)
		{
			const char* prefix = OptString(state, 1);
			if (!prefix)
				return 0;
			if (lua_isnumber(state, 2))
			{
				const char* fmt = OptString(state, 3);
				if (fmt)
					ImGui::Value(prefix, (float)lua_tonumber(state, 2), fmt);
				else
					ImGui::Value(prefix, (float)lua_tonumber(state, 2));
			}
			else if (lua_type(state, 2) == LUA_TBOOLEAN)
			{
				ImGui::Value(prefix, (bool)lua_toboolean(state, 2));
			}
			return 0;
		}

		// ----------------------------------------------------------------
		// Menus
		// ----------------------------------------------------------------

		static int BeginMenuBar(lua_State* state)     { lua_pushboolean(state, ImGui::BeginMenuBar()); return 1; }
		static int EndMenuBar(lua_State*)             { ImGui::EndMenuBar(); return 0; }
		static int BeginMainMenuBar(lua_State* state) { lua_pushboolean(state, ImGui::BeginMainMenuBar()); return 1; }
		static int EndMainMenuBar(lua_State*)         { ImGui::EndMainMenuBar(); return 0; }

		static int BeginMenu(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			bool enabled      = lua_isnoneornil(state, 2) ? true : lua_toboolean(state, 2);
			lua_pushboolean(state, ImGui::BeginMenu(label, enabled));
			return 1;
		}

		static int EndMenu(lua_State*) { ImGui::EndMenu(); return 0; }

		// Overload: MenuItem(label, shortcut?) | MenuItem(label, shortcut, selected)
		static int MenuItem(lua_State* state)
		{
			const char* label    = CheckStringSafe(state, 1);
			const char* shortcut = OptString(state, 2);
			if (lua_type(state, 3) == LUA_TBOOLEAN)
			{
				bool selected   = lua_toboolean(state, 3);
				bool activated  = ImGui::MenuItem(label, shortcut, &selected);
				lua_pushboolean(state, selected);
				lua_pushboolean(state, activated);
				return 2;
			}
			lua_pushboolean(state, ImGui::MenuItem(label, shortcut));
			return 1;
		}

		// ----------------------------------------------------------------
		// Tooltips
		// ----------------------------------------------------------------

		static int BeginTooltip(lua_State*) { ImGui::BeginTooltip(); return 0; }
		static int EndTooltip(lua_State*)   { ImGui::EndTooltip();   return 0; }

		static int SetTooltip(lua_State* state)
		{
			ImGui::SetTooltip("%s", luaL_checkstring(state, 1));
			return 0;
		}

		// ----------------------------------------------------------------
		// Popups, modals
		// ----------------------------------------------------------------

		static int BeginPopup(lua_State* state)
		{
			const char* id = CheckStringSafe(state, 1);
			int flags      = (int)luaL_optinteger(state, 2, 0);
			lua_pushboolean(state, ImGui::BeginPopup(id, flags));
			return 1;
		}

		static int BeginPopupModal(lua_State* state)
		{
			const char* name = CheckStringSafe(state, 1);
			int top          = lua_gettop(state);
			if (top >= 2 && lua_type(state, 2) == LUA_TBOOLEAN)
			{
				bool open = lua_toboolean(state, 2);
				int flags = (int)luaL_optinteger(state, 3, 0);
				bool draw = ImGui::BeginPopupModal(name, &open, flags);
				lua_pushboolean(state, open);
				lua_pushboolean(state, draw);
				return 2;
			}
			int flags = (int)luaL_optinteger(state, 3, 0);
			lua_pushboolean(state, ImGui::BeginPopupModal(name, nullptr, flags));
			return 1;
		}

		static int EndPopup(lua_State*) { ImGui::EndPopup(); return 0; }

		static int OpenPopup(lua_State* state)
		{
			const char* id = CheckStringSafe(state, 1);
			int flags      = (int)luaL_optinteger(state, 2, 0);
			ImGui::OpenPopup(id, flags);
			return 0;
		}

		// OpenPopupContextItem was renamed to OpenPopupOnItemClick in newer ImGui.
		static int OpenPopupContextItem(lua_State* state)
		{
			const char* id = OptString(state, 1);
			int flags      = (int)luaL_optinteger(state, 2, 1);
			ImGui::OpenPopupOnItemClick(id, flags);
			lua_pushboolean(state, true);
			return 1;
		}

		static int CloseCurrentPopup(lua_State*) { ImGui::CloseCurrentPopup(); return 0; }

		static int BeginPopupContextItem(lua_State* state)
		{
			const char* id = OptString(state, 1);
			int flags      = (int)luaL_optinteger(state, 2, 1);
			lua_pushboolean(state, ImGui::BeginPopupContextItem(id, flags));
			return 1;
		}

		static int BeginPopupContextWindow(lua_State* state)
		{
			const char* id = OptString(state, 1);
			int flags      = (int)luaL_optinteger(state, 2, 1);
			lua_pushboolean(state, ImGui::BeginPopupContextWindow(id, flags));
			return 1;
		}

		static int BeginPopupContextVoid(lua_State* state)
		{
			const char* id = OptString(state, 1);
			int flags      = (int)luaL_optinteger(state, 2, 1);
			lua_pushboolean(state, ImGui::BeginPopupContextVoid(id, flags));
			return 1;
		}

		static int IsPopupOpen(lua_State* state)
		{
			const char* id = CheckStringSafe(state, 1);
			int flags      = (int)luaL_optinteger(state, 2, 0);
			lua_pushboolean(state, ImGui::IsPopupOpen(id, flags));
			return 1;
		}

		// ----------------------------------------------------------------
		// Columns
		// ----------------------------------------------------------------

		static int Columns(lua_State* state)
		{
			int count      = (int)luaL_optinteger(state, 1, 1);
			const char* id = OptString(state, 2);
			bool border    = lua_isnoneornil(state, 3) ? true : lua_toboolean(state, 3);
			ImGui::Columns(count, id, border);
			return 0;
		}

		static int NextColumn(lua_State*) { ImGui::NextColumn(); return 0; }

		static int GetColumnIndex(lua_State* state) { lua_pushinteger(state, ImGui::GetColumnIndex()); return 1; }

		static int GetColumnWidth(lua_State* state)
		{
			int idx = (int)luaL_optinteger(state, 1, -1);
			lua_pushnumber(state, ImGui::GetColumnWidth(idx));
			return 1;
		}

		static int SetColumnWidth(lua_State* state)
		{
			int idx   = (int)luaL_checkinteger(state, 1);
			float w   = (float)luaL_checknumber(state, 2);
			ImGui::SetColumnWidth(idx, w);
			return 0;
		}

		static int GetColumnOffset(lua_State* state)
		{
			int idx = (int)luaL_optinteger(state, 1, -1);
			lua_pushnumber(state, ImGui::GetColumnOffset(idx));
			return 1;
		}

		static int SetColumnOffset(lua_State* state)
		{
			int idx = (int)luaL_checkinteger(state, 1);
			float o = (float)luaL_checknumber(state, 2);
			ImGui::SetColumnOffset(idx, o);
			return 0;
		}

		static int GetColumnsCount(lua_State* state) { lua_pushinteger(state, ImGui::GetColumnsCount()); return 1; }

		// ----------------------------------------------------------------
		// Tab bars
		// ----------------------------------------------------------------

		static int BeginTabBar(lua_State* state)
		{
			const char* id = CheckStringSafe(state, 1);
			int flags      = (int)luaL_optinteger(state, 2, 0);
			lua_pushboolean(state, ImGui::BeginTabBar(id, flags));
			return 1;
		}

		static int EndTabBar(lua_State*) { ImGui::EndTabBar(); return 0; }

		// Overload: BeginTabItem(label) | BeginTabItem(label, open, flags?)
		static int BeginTabItem(lua_State* state)
		{
			const char* label = CheckStringSafe(state, 1);
			if (lua_type(state, 2) == LUA_TBOOLEAN)
			{
				bool open    = lua_toboolean(state, 2);
				int flags    = (int)luaL_optinteger(state, 3, 0);
				bool selected = ImGui::BeginTabItem(label, &open, flags);
				lua_pushboolean(state, open);
				lua_pushboolean(state, selected);
				return 2;
			}
			lua_pushboolean(state, ImGui::BeginTabItem(label));
			return 1;
		}

		static int EndTabItem(lua_State*) { ImGui::EndTabItem(); return 0; }

		static int SetTabItemClosed(lua_State* state)
		{
			ImGui::SetTabItemClosed(CheckStringSafe(state, 1));
			return 0;
		}

		// ----------------------------------------------------------------
		// Logging
		// ----------------------------------------------------------------

		static int LogToTTY(lua_State* state)
		{
			ImGui::LogToTTY((int)luaL_optinteger(state, 1, -1));
			return 0;
		}

		static int LogToFile(lua_State* state)
		{
			int depth          = (int)luaL_optinteger(state, 1, -1);
			const char* fname  = OptString(state, 2);
			ImGui::LogToFile(depth, fname);
			return 0;
		}

		static int LogToClipboard(lua_State* state)
		{
			ImGui::LogToClipboard((int)luaL_optinteger(state, 1, -1));
			return 0;
		}

		static int LogFinish(lua_State*)  { ImGui::LogFinish();  return 0; }
		static int LogButtons(lua_State*) { ImGui::LogButtons(); return 0; }

		static int LogText(lua_State* state)
		{
			ImGui::LogText("%s", luaL_checkstring(state, 1));
			return 0;
		}

		// ----------------------------------------------------------------
		// Clipping
		// ----------------------------------------------------------------

		static int PushClipRect(lua_State* state)
		{
			float minx = (float)luaL_checknumber(state, 1);
			float miny = (float)luaL_checknumber(state, 2);
			float maxx = (float)luaL_checknumber(state, 3);
			float maxy = (float)luaL_checknumber(state, 4);
			bool inter = CheckBooleanSafe(state, 5);
			ImGui::PushClipRect(ImVec2(minx, miny), ImVec2(maxx, maxy), inter);
			return 0;
		}

		static int PopClipRect(lua_State*) { ImGui::PopClipRect(); return 0; }

		// ----------------------------------------------------------------
		// Focus / activation
		// ----------------------------------------------------------------

		static int SetItemDefaultFocus(lua_State*) { ImGui::SetItemDefaultFocus(); return 0; }

		static int SetKeyboardFocusHere(lua_State* state)
		{
			ImGui::SetKeyboardFocusHere((int)luaL_optinteger(state, 1, 0));
			return 0;
		}

		// ----------------------------------------------------------------
		// Item / widget utilities
		// ----------------------------------------------------------------

		static int IsItemHovered(lua_State* state)
		{
			int flags = (int)luaL_optinteger(state, 1, 0);
			lua_pushboolean(state, ImGui::IsItemHovered(flags));
			return 1;
		}

		static int IsItemActive(lua_State* state)                { lua_pushboolean(state, ImGui::IsItemActive()); return 1; }
		static int IsItemFocused(lua_State* state)               { lua_pushboolean(state, ImGui::IsItemFocused()); return 1; }

		static int IsItemClicked(lua_State* state)
		{
			int btn = (int)luaL_optinteger(state, 1, 0);
			lua_pushboolean(state, ImGui::IsItemClicked(btn));
			return 1;
		}

		static int IsItemVisible(lua_State* state)               { lua_pushboolean(state, ImGui::IsItemVisible()); return 1; }
		static int IsItemEdited(lua_State* state)                { lua_pushboolean(state, ImGui::IsItemEdited()); return 1; }
		static int IsItemActivated(lua_State* state)             { lua_pushboolean(state, ImGui::IsItemActivated()); return 1; }
		static int IsItemDeactivated(lua_State* state)           { lua_pushboolean(state, ImGui::IsItemDeactivated()); return 1; }
		static int IsItemDeactivatedAfterEdit(lua_State* state)  { lua_pushboolean(state, ImGui::IsItemDeactivatedAfterEdit()); return 1; }
		static int IsItemToggledOpen(lua_State* state)           { lua_pushboolean(state, ImGui::IsItemToggledOpen()); return 1; }
		static int IsAnyItemHovered(lua_State* state)            { lua_pushboolean(state, ImGui::IsAnyItemHovered()); return 1; }
		static int IsAnyItemActive(lua_State* state)             { lua_pushboolean(state, ImGui::IsAnyItemActive()); return 1; }
		static int IsAnyItemFocused(lua_State* state)            { lua_pushboolean(state, ImGui::IsAnyItemFocused()); return 1; }

		static int GetItemRectMin(lua_State* state)
		{
			ImVec2 v = ImGui::GetItemRectMin();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetItemRectMax(lua_State* state)
		{
			ImVec2 v = ImGui::GetItemRectMax();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetItemRectSize(lua_State* state)
		{
			ImVec2 v = ImGui::GetItemRectSize();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		// ----------------------------------------------------------------
		// Miscellaneous utilities
		// ----------------------------------------------------------------

		// Overload: IsRectVisible(size_x, size_y) | IsRectVisible(min_x, min_y, max_x, max_y)
		static int IsRectVisible(lua_State* state)
		{
			if (lua_gettop(state) >= 4)
			{
				float minx = (float)luaL_checknumber(state, 1);
				float miny = (float)luaL_checknumber(state, 2);
				float maxx = (float)luaL_checknumber(state, 3);
				float maxy = (float)luaL_checknumber(state, 4);
				lua_pushboolean(state, ImGui::IsRectVisible(ImVec2(minx, miny), ImVec2(maxx, maxy)));
				return 1;
			}
			float sx = (float)luaL_checknumber(state, 1);
			float sy = (float)luaL_checknumber(state, 2);
			lua_pushboolean(state, ImGui::IsRectVisible(ImVec2(sx, sy)));
			return 1;
		}

		static int GetTime(lua_State* state)       { lua_pushnumber(state, ImGui::GetTime()); return 1; }
		static int GetFrameCount(lua_State* state) { lua_pushinteger(state, ImGui::GetFrameCount()); return 1; }

		static int GetStyleColorName(lua_State* state)
		{
			lua_pushstring(state, ImGui::GetStyleColorName((int)luaL_checkinteger(state, 1)));
			return 1;
		}

		// BeginChildFrame / EndChildFrame were removed in newer ImGui; fall back to BeginChild.
		static int BeginChildFrame(lua_State* state)
		{
			ImGuiID id = (ImGuiID)luaL_checkinteger(state, 1);
			float sx   = (float)luaL_checknumber(state, 2);
			float sy   = (float)luaL_checknumber(state, 3);
			int flags  = (int)luaL_optinteger(state, 4, 0);
			lua_pushboolean(state, ImGui::BeginChild(id, ImVec2(sx, sy), ImGuiChildFlags_FrameStyle, flags));
			return 1;
		}

		static int EndChildFrame(lua_State*) { ImGui::EndChild(); return 0; }

		// ----------------------------------------------------------------
		// Text utilities
		// ----------------------------------------------------------------

		static int CalcTextSize(lua_State* state)
		{
			const char* text   = CheckStringSafe(state, 1);
			const char* tend   = lua_isnoneornil(state, 2) ? nullptr : luaL_checkstring(state, 2);
			bool hide_after_dh = lua_isnoneornil(state, 3) ? false : lua_toboolean(state, 3);
			float wrap         = (float)luaL_optnumber(state, 4, -1.0);
			ImVec2 sz = ImGui::CalcTextSize(text, tend, hide_after_dh, wrap);
			lua_pushnumber(state, sz.x);
			lua_pushnumber(state, sz.y);
			return 2;
		}

		// ----------------------------------------------------------------
		// Inputs: keyboard
		// ----------------------------------------------------------------

		static int IsKeyDown(lua_State* state)
		{
			ImGuiKey key = (ImGuiKey)luaL_checkinteger(state, 1);
			lua_pushboolean(state, ImGui::IsKeyDown(key));
			return 1;
		}

		static int IsKeyPressed(lua_State* state)
		{
			ImGuiKey key = (ImGuiKey)luaL_checkinteger(state, 1);
			bool repeat  = lua_isnoneornil(state, 2) ? true : lua_toboolean(state, 2);
			lua_pushboolean(state, ImGui::IsKeyPressed(key, repeat));
			return 1;
		}

		static int IsKeyReleased(lua_State* state)
		{
			ImGuiKey key = (ImGuiKey)luaL_checkinteger(state, 1);
			lua_pushboolean(state, ImGui::IsKeyReleased(key));
			return 1;
		}

		static int GetKeyPressedAmount(lua_State* state)
		{
			ImGuiKey key = (ImGuiKey)luaL_checkinteger(state, 1);
			float delay  = (float)luaL_checknumber(state, 2);
			float rate   = (float)luaL_checknumber(state, 3);
			lua_pushinteger(state, ImGui::GetKeyPressedAmount(key, delay, rate));
			return 1;
		}

		static int SetNextFrameWantCaptureKeyboard(lua_State* state)
		{
			bool want = lua_isnoneornil(state, 1) ? true : lua_toboolean(state, 1);
			ImGui::SetNextFrameWantCaptureKeyboard(want);
			return 0;
		}

		// ----------------------------------------------------------------
		// Inputs: mouse
		// ----------------------------------------------------------------

		static int IsMouseDown(lua_State* state)
		{
			lua_pushboolean(state, ImGui::IsMouseDown((int)luaL_checkinteger(state, 1)));
			return 1;
		}

		static int IsMouseClicked(lua_State* state)
		{
			int btn     = (int)luaL_checkinteger(state, 1);
			bool repeat = lua_isnoneornil(state, 2) ? false : lua_toboolean(state, 2);
			lua_pushboolean(state, ImGui::IsMouseClicked(btn, repeat));
			return 1;
		}

		static int IsMouseReleased(lua_State* state)
		{
			lua_pushboolean(state, ImGui::IsMouseReleased((int)luaL_checkinteger(state, 1)));
			return 1;
		}

		static int IsMouseDoubleClicked(lua_State* state)
		{
			lua_pushboolean(state, ImGui::IsMouseDoubleClicked((int)luaL_checkinteger(state, 1)));
			return 1;
		}

		static int IsMouseHoveringRect(lua_State* state)
		{
			float minx = (float)luaL_checknumber(state, 1);
			float miny = (float)luaL_checknumber(state, 2);
			float maxx = (float)luaL_checknumber(state, 3);
			float maxy = (float)luaL_checknumber(state, 4);
			bool clip  = lua_isnoneornil(state, 5) ? true : lua_toboolean(state, 5);
			lua_pushboolean(state, ImGui::IsMouseHoveringRect(ImVec2(minx, miny), ImVec2(maxx, maxy), clip));
			return 1;
		}

		static int IsAnyMouseDown(lua_State* state)
		{
			lua_pushboolean(state, ImGui::IsAnyMouseDown());
			return 1;
		}

		static int GetMousePos(lua_State* state)
		{
			ImVec2 v = ImGui::GetMousePos();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int GetMousePosOnOpeningCurrentPopup(lua_State* state)
		{
			ImVec2 v = ImGui::GetMousePosOnOpeningCurrentPopup();
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int IsMouseDragging(lua_State* state)
		{
			int btn        = (int)luaL_checkinteger(state, 1);
			float lock_thr = (float)luaL_optnumber(state, 2, -1.0);
			lua_pushboolean(state, ImGui::IsMouseDragging(btn, lock_thr));
			return 1;
		}

		static int GetMouseDragDelta(lua_State* state)
		{
			int btn        = (int)luaL_optinteger(state, 1, 0);
			float lock_thr = (float)luaL_optnumber(state, 2, -1.0);
			ImVec2 v = ImGui::GetMouseDragDelta(btn, lock_thr);
			lua_pushnumber(state, v.x);
			lua_pushnumber(state, v.y);
			return 2;
		}

		static int ResetMouseDragDelta(lua_State* state)
		{
			int btn = (int)luaL_optinteger(state, 1, 0);
			ImGui::ResetMouseDragDelta(btn);
			return 0;
		}

		static int GetMouseCursor(lua_State* state)
		{
			lua_pushinteger(state, ImGui::GetMouseCursor());
			return 1;
		}

		static int SetMouseCursor(lua_State* state)
		{
			ImGui::SetMouseCursor((int)luaL_checkinteger(state, 1));
			return 0;
		}

		static int SetNextFrameWantCaptureMouse(lua_State* state)
		{
			bool want = lua_isnoneornil(state, 1) ? true : lua_toboolean(state, 1);
			ImGui::SetNextFrameWantCaptureMouse(want);
			return 0;
		}

		// ----------------------------------------------------------------
		// Clipboard
		// ----------------------------------------------------------------

		static int GetClipboardText(lua_State* state)
		{
			lua_pushstring(state, ImGui::GetClipboardText());
			return 1;
		}

		static int SetClipboardText(lua_State* state)
		{
			ImGui::SetClipboardText(CheckStringSafe(state, 1));
			return 0;
		}

		// ----------------------------------------------------------------
		// Register
		// ----------------------------------------------------------------

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);

			// Internal / drawing
			SetFunction(state, AddCircle, "AddCircle");
			SetFunction(state, AddCircleFilled, "AddCircleFilled");
			SetFunction(state, AddLine, "AddLine");
			SetFunction(state, AddRect, "AddRect");
			SetFunction(state, AddRectFilled, "AddRectFilled");
			SetFunction(state, AddRectFilledMultiColor, "AddRectFilledMultiColor");
			SetFunction(state, AddText, "AddText");
			SetFunction(state, AddTriangle, "AddTriangle");
			SetFunction(state, AddTriangleFilled, "AddTriangleFilled");

			// Tables
			SetFunction(state, BeginTable, "BeginTable");
			SetFunction(state, EndTable, "EndTable");
			SetFunction(state, TableNextColumn, "TableNextColumn");
			SetFunction(state, TableNextRow, "TableNextRow");
			SetFunction(state, TableSetColumnIndex, "TableSetColumnIndex");
			SetFunction(state, TableSetupColumn, "TableSetupColumn");
			SetFunction(state, TableHeadersRow, "TableHeadersRow");

			// Color conversions
			SetFunction(state, ColorConvertFloat4ToU32, "ColorConvertFloat4ToU32");
			SetFunction(state, ColorConvertRGBAToU32, "ColorConvertRGBAToU32");
			SetFunction(state, ColorConvertU32ToFloat4, "ColorConvertU32ToFloat4");
			SetFunction(state, ColorConvertRGBtoHSV, "ColorConvertRGBtoHSV");
			SetFunction(state, ColorConvertHSVtoRGB, "ColorConvertHSVtoRGB");

			// Display
			SetFunction(state, GetDisplaySize, "GetDisplaySize");
			SetFunction(state, GetFrameRate, "GetFrameRate");

			// Windows
			SetFunction(state, Begin, "Begin");
			SetFunction(state, End, "End");
			SetFunction(state, BeginChild, "BeginChild");
			SetFunction(state, EndChild, "EndChild");

			// Window utilities
			SetFunction(state, IsWindowAppearing, "IsWindowAppearing");
			SetFunction(state, IsWindowCollapsed, "IsWindowCollapsed");
			SetFunction(state, IsWindowFocused, "IsWindowFocused");
			SetFunction(state, IsWindowHovered, "IsWindowHovered");
			SetFunction(state, GetWindowPos, "GetWindowPos");
			SetFunction(state, GetWindowSize, "GetWindowSize");
			SetFunction(state, GetWindowWidth, "GetWindowWidth");
			SetFunction(state, GetWindowHeight, "GetWindowHeight");
			SetFunction(state, SetNextWindowPos, "SetNextWindowPos");
			SetFunction(state, SetNextWindowSize, "SetNextWindowSize");
			SetFunction(state, SetNextWindowSizeConstraints, "SetNextWindowSizeConstraints");
			SetFunction(state, SetNextWindowContentSize, "SetNextWindowContentSize");
			SetFunction(state, SetNextWindowCollapsed, "SetNextWindowCollapsed");
			SetFunction(state, SetNextWindowFocus, "SetNextWindowFocus");
			SetFunction(state, SetNextWindowBgAlpha, "SetNextWindowBgAlpha");
			SetFunction(state, SetWindowPos, "SetWindowPos");
			SetFunction(state, SetWindowSize, "SetWindowSize");
			SetFunction(state, SetWindowCollapsed, "SetWindowCollapsed");
			SetFunction(state, SetWindowFocus, "SetWindowFocus");
			SetFunction(state, SetWindowFontScale, "SetWindowFontScale");

			// Content region
			SetFunction(state, GetContentRegionMax, "GetContentRegionMax");
			SetFunction(state, GetContentRegionAvail, "GetContentRegionAvail");
			SetFunction(state, GetWindowContentRegionMin, "GetWindowContentRegionMin");
			SetFunction(state, GetWindowContentRegionMax, "GetWindowContentRegionMax");

			// Scrolling
			SetFunction(state, GetScrollX, "GetScrollX");
			SetFunction(state, GetScrollY, "GetScrollY");
			SetFunction(state, GetScrollMaxX, "GetScrollMaxX");
			SetFunction(state, GetScrollMaxY, "GetScrollMaxY");
			SetFunction(state, SetScrollX, "SetScrollX");
			SetFunction(state, SetScrollY, "SetScrollY");
			SetFunction(state, SetScrollHereX, "SetScrollHereX");
			SetFunction(state, SetScrollHereY, "SetScrollHereY");
			SetFunction(state, SetScrollFromPosX, "SetScrollFromPosX");
			SetFunction(state, SetScrollFromPosY, "SetScrollFromPosY");

			// Parameter stacks (shared)
			SetFunction(state, PushStyleColor, "PushStyleColor");
			SetFunction(state, PopStyleColor, "PopStyleColor");
			SetFunction(state, PushStyleVar, "PushStyleVar");
			SetFunction(state, PopStyleVar, "PopStyleVar");
			SetFunction(state, GetStyleColorVec4, "GetStyleColorVec4");
			SetFunction(state, GetFontSize, "GetFontSize");
			SetFunction(state, GetFontTexUvWhitePixel, "GetFontTexUvWhitePixel");

			// Parameter stacks (current window)
			SetFunction(state, PushItemWidth, "PushItemWidth");
			SetFunction(state, PopItemWidth, "PopItemWidth");
			SetFunction(state, SetNextItemWidth, "SetNextItemWidth");
			SetFunction(state, CalcItemWidth, "CalcItemWidth");
			SetFunction(state, PushTextWrapPos, "PushTextWrapPos");
			SetFunction(state, PopTextWrapPos, "PopTextWrapPos");
			SetFunction(state, PushButtonRepeat, "PushButtonRepeat");
			SetFunction(state, PopButtonRepeat, "PopButtonRepeat");

			// Cursor / layout
			SetFunction(state, Separator, "Separator");
			SetFunction(state, SeparatorText, "SeparatorText");
			SetFunction(state, BeginDisabled, "BeginDisabled");
			SetFunction(state, EndDisabled, "EndDisabled");
			SetFunction(state, GetStyle, "GetStyle");
			SetFunction(state, SameLine, "SameLine");
			SetFunction(state, NewLine, "NewLine");
			SetFunction(state, Spacing, "Spacing");
			SetFunction(state, Dummy, "Dummy");
			SetFunction(state, Indent, "Indent");
			SetFunction(state, Unindent, "Unindent");
			SetFunction(state, BeginGroup, "BeginGroup");
			SetFunction(state, EndGroup, "EndGroup");
			SetFunction(state, GetCursorPos, "GetCursorPos");
			SetFunction(state, GetCursorPosX, "GetCursorPosX");
			SetFunction(state, GetCursorPosY, "GetCursorPosY");
			SetFunction(state, SetCursorPos, "SetCursorPos");
			SetFunction(state, SetCursorPosX, "SetCursorPosX");
			SetFunction(state, SetCursorPosY, "SetCursorPosY");
			SetFunction(state, GetCursorStartPos, "GetCursorStartPos");
			SetFunction(state, GetCursorScreenPos, "GetCursorScreenPos");
			SetFunction(state, SetCursorScreenPos, "SetCursorScreenPos");
			SetFunction(state, AlignTextToFramePadding, "AlignTextToFramePadding");
			SetFunction(state, GetTextLineHeight, "GetTextLineHeight");
			SetFunction(state, GetTextLineHeightWithSpacing, "GetTextLineHeightWithSpacing");
			SetFunction(state, GetFrameHeight, "GetFrameHeight");
			SetFunction(state, GetFrameHeightWithSpacing, "GetFrameHeightWithSpacing");

			// ID stack
			SetFunction(state, PushID, "PushID");
			SetFunction(state, PopID, "PopID");
			SetFunction(state, GetID, "GetID");

			// Text widgets
			SetFunction(state, TextUnformatted, "TextUnformatted");
			SetFunction(state, Text, "Text");
			SetFunction(state, TextColored, "TextColored");
			SetFunction(state, TextDisabled, "TextDisabled");
			SetFunction(state, TextWrapped, "TextWrapped");
			SetFunction(state, LabelText, "LabelText");
			SetFunction(state, BulletText, "BulletText");

			// Main widgets
			SetFunction(state, Button, "Button");
			SetFunction(state, SmallButton, "SmallButton");
			SetFunction(state, InvisibleButton, "InvisibleButton");
			SetFunction(state, ArrowButton, "ArrowButton");
			SetFunction(state, Checkbox, "Checkbox");
			SetFunction(state, RadioButton, "RadioButton");
			SetFunction(state, ProgressBar, "ProgressBar");
			SetFunction(state, Bullet, "Bullet");

			// Combo
			SetFunction(state, BeginCombo, "BeginCombo");
			SetFunction(state, EndCombo, "EndCombo");
			SetFunction(state, Combo, "Combo");

			// Drag
			SetFunction(state, DragFloat, "DragFloat");
			SetFunction(state, DragFloat2, "DragFloat2");
			SetFunction(state, DragFloat3, "DragFloat3");
			SetFunction(state, DragFloat4, "DragFloat4");
			SetFunction(state, DragInt, "DragInt");
			SetFunction(state, DragInt2, "DragInt2");
			SetFunction(state, DragInt3, "DragInt3");
			SetFunction(state, DragInt4, "DragInt4");

			// Sliders
			SetFunction(state, SliderFloat, "SliderFloat");
			SetFunction(state, SliderFloat2, "SliderFloat2");
			SetFunction(state, SliderFloat3, "SliderFloat3");
			SetFunction(state, SliderFloat4, "SliderFloat4");
			SetFunction(state, SliderAngle, "SliderAngle");
			SetFunction(state, SliderInt, "SliderInt");
			SetFunction(state, SliderInt2, "SliderInt2");
			SetFunction(state, SliderInt3, "SliderInt3");
			SetFunction(state, SliderInt4, "SliderInt4");
			SetFunction(state, VSliderFloat, "VSliderFloat");
			SetFunction(state, VSliderInt, "VSliderInt");

			// Input with keyboard
			SetFunction(state, InputText, "InputText");
			SetFunction(state, InputTextMultiline, "InputTextMultiline");
			SetFunction(state, InputTextWithHint, "InputTextWithHint");
			SetFunction(state, InputFloat, "InputFloat");
			SetFunction(state, InputFloat2, "InputFloat2");
			SetFunction(state, InputFloat3, "InputFloat3");
			SetFunction(state, InputFloat4, "InputFloat4");
			SetFunction(state, InputInt, "InputInt");
			SetFunction(state, InputInt2, "InputInt2");
			SetFunction(state, InputInt3, "InputInt3");
			SetFunction(state, InputInt4, "InputInt4");
			SetFunction(state, InputDouble, "InputDouble");

			// Color editor / picker
			SetFunction(state, ColorEdit3, "ColorEdit3");
			SetFunction(state, ColorEdit4, "ColorEdit4");
			SetFunction(state, ColorPicker3, "ColorPicker3");
			SetFunction(state, ColorPicker4, "ColorPicker4");
			SetFunction(state, ColorButton, "ColorButton");
			SetFunction(state, SetColorEditOptions, "SetColorEditOptions");

			// Trees
			SetFunction(state, TreeNode, "TreeNode");
			SetFunction(state, TreeNodeEx, "TreeNodeEx");
			SetFunction(state, TreePush, "TreePush");
			SetFunction(state, TreePop, "TreePop");
			SetFunction(state, GetTreeNodeToLabelSpacing, "GetTreeNodeToLabelSpacing");
			SetFunction(state, CollapsingHeader, "CollapsingHeader");
			SetFunction(state, SetNextItemOpen, "SetNextItemOpen");

			// Selectables
			SetFunction(state, Selectable, "Selectable");

			// List boxes
			SetFunction(state, ListBox, "ListBox");
			SetFunction(state, BeginListBox, "BeginListBox");
			SetFunction(state, EndListBox, "EndListBox");

			// Value()
			SetFunction(state, Value, "Value");

			// Menus
			SetFunction(state, BeginMenuBar, "BeginMenuBar");
			SetFunction(state, EndMenuBar, "EndMenuBar");
			SetFunction(state, BeginMainMenuBar, "BeginMainMenuBar");
			SetFunction(state, EndMainMenuBar, "EndMainMenuBar");
			SetFunction(state, BeginMenu, "BeginMenu");
			SetFunction(state, EndMenu, "EndMenu");
			SetFunction(state, MenuItem, "MenuItem");

			// Tooltips
			SetFunction(state, BeginTooltip, "BeginTooltip");
			SetFunction(state, EndTooltip, "EndTooltip");
			SetFunction(state, SetTooltip, "SetTooltip");

			// Popups / modals
			SetFunction(state, BeginPopup, "BeginPopup");
			SetFunction(state, BeginPopupModal, "BeginPopupModal");
			SetFunction(state, EndPopup, "EndPopup");
			SetFunction(state, OpenPopup, "OpenPopup");
			SetFunction(state, OpenPopupContextItem, "OpenPopupContextItem");
			SetFunction(state, CloseCurrentPopup, "CloseCurrentPopup");
			SetFunction(state, BeginPopupContextItem, "BeginPopupContextItem");
			SetFunction(state, BeginPopupContextWindow, "BeginPopupContextWindow");
			SetFunction(state, BeginPopupContextVoid, "BeginPopupContextVoid");
			SetFunction(state, IsPopupOpen, "IsPopupOpen");

			// Columns
			SetFunction(state, Columns, "Columns");
			SetFunction(state, NextColumn, "NextColumn");
			SetFunction(state, GetColumnIndex, "GetColumnIndex");
			SetFunction(state, GetColumnWidth, "GetColumnWidth");
			SetFunction(state, SetColumnWidth, "SetColumnWidth");
			SetFunction(state, GetColumnOffset, "GetColumnOffset");
			SetFunction(state, SetColumnOffset, "SetColumnOffset");
			SetFunction(state, GetColumnsCount, "GetColumnsCount");

			// Tab bars
			SetFunction(state, BeginTabBar, "BeginTabBar");
			SetFunction(state, EndTabBar, "EndTabBar");
			SetFunction(state, BeginTabItem, "BeginTabItem");
			SetFunction(state, EndTabItem, "EndTabItem");
			SetFunction(state, SetTabItemClosed, "SetTabItemClosed");

			// Logging
			SetFunction(state, LogToTTY, "LogToTTY");
			SetFunction(state, LogToFile, "LogToFile");
			SetFunction(state, LogToClipboard, "LogToClipboard");
			SetFunction(state, LogFinish, "LogFinish");
			SetFunction(state, LogButtons, "LogButtons");
			SetFunction(state, LogText, "LogText");

			// Clipping
			SetFunction(state, PushClipRect, "PushClipRect");
			SetFunction(state, PopClipRect, "PopClipRect");

			// Focus / activation
			SetFunction(state, SetItemDefaultFocus, "SetItemDefaultFocus");
			SetFunction(state, SetKeyboardFocusHere, "SetKeyboardFocusHere");

			// Item utilities
			SetFunction(state, IsItemHovered, "IsItemHovered");
			SetFunction(state, IsItemActive, "IsItemActive");
			SetFunction(state, IsItemFocused, "IsItemFocused");
			SetFunction(state, IsItemClicked, "IsItemClicked");
			SetFunction(state, IsItemVisible, "IsItemVisible");
			SetFunction(state, IsItemEdited, "IsItemEdited");
			SetFunction(state, IsItemActivated, "IsItemActivated");
			SetFunction(state, IsItemDeactivated, "IsItemDeactivated");
			SetFunction(state, IsItemDeactivatedAfterEdit, "IsItemDeactivatedAfterEdit");
			SetFunction(state, IsItemToggledOpen, "IsItemToggledOpen");
			SetFunction(state, IsAnyItemHovered, "IsAnyItemHovered");
			SetFunction(state, IsAnyItemActive, "IsAnyItemActive");
			SetFunction(state, IsAnyItemFocused, "IsAnyItemFocused");
			SetFunction(state, GetItemRectMin, "GetItemRectMin");
			SetFunction(state, GetItemRectMax, "GetItemRectMax");
			SetFunction(state, GetItemRectSize, "GetItemRectSize");

			// Miscellaneous utilities
			SetFunction(state, IsRectVisible, "IsRectVisible");
			SetFunction(state, GetTime, "GetTime");
			SetFunction(state, GetFrameCount, "GetFrameCount");
			SetFunction(state, GetStyleColorName, "GetStyleColorName");
			SetFunction(state, BeginChildFrame, "BeginChildFrame");
			SetFunction(state, EndChildFrame, "EndChildFrame");

			// Text utilities
			SetFunction(state, CalcTextSize, "CalcTextSize");

			// Keyboard inputs
			SetFunction(state, IsKeyDown, "IsKeyDown");
			SetFunction(state, IsKeyPressed, "IsKeyPressed");
			SetFunction(state, IsKeyReleased, "IsKeyReleased");
			SetFunction(state, GetKeyPressedAmount, "GetKeyPressedAmount");
			SetFunction(state, SetNextFrameWantCaptureKeyboard, "SetNextFrameWantCaptureKeyboard");

			// Mouse inputs
			SetFunction(state, IsMouseDown, "IsMouseDown");
			SetFunction(state, IsMouseClicked, "IsMouseClicked");
			SetFunction(state, IsMouseReleased, "IsMouseReleased");
			SetFunction(state, IsMouseDoubleClicked, "IsMouseDoubleClicked");
			SetFunction(state, IsMouseHoveringRect, "IsMouseHoveringRect");
			SetFunction(state, IsAnyMouseDown, "IsAnyMouseDown");
			SetFunction(state, GetMousePos, "GetMousePos");
			SetFunction(state, GetMousePosOnOpeningCurrentPopup, "GetMousePosOnOpeningCurrentPopup");
			SetFunction(state, IsMouseDragging, "IsMouseDragging");
			SetFunction(state, GetMouseDragDelta, "GetMouseDragDelta");
			SetFunction(state, ResetMouseDragDelta, "ResetMouseDragDelta");
			SetFunction(state, GetMouseCursor, "GetMouseCursor");
			SetFunction(state, SetMouseCursor, "SetMouseCursor");
			SetFunction(state, SetNextFrameWantCaptureMouse, "SetNextFrameWantCaptureMouse");

			// Clipboard
			SetFunction(state, GetClipboardText, "GetClipboardText");
			SetFunction(state, SetClipboardText, "SetClipboardText");

			lua_setglobal(state, "ImGui");

			static const EnumEntry windowFlags[] = {
				{"None", 0}, {"NoTitleBar", 1}, {"NoResize", 2}, {"NoMove", 4},
				{"NoScrollbar", 8}, {"NoScrollWithMouse", 16}, {"NoCollapse", 32},
				{"AlwaysAutoResize", 64}, {"NoBackground", 128}, {"NoSavedSettings", 256},
				{"NoMouseInputs", 512}, {"MenuBar", 1024}, {"HorizontalScrollbar", 2048},
				{"NoFocusOnAppearing", 4096}, {"NoBringToFrontOnFocus", 8192},
				{"AlwaysVerticalScrollbar", 16384}, {"AlwaysHorizontalScrollbar", 32768},
				{"NoNavInputs", 65536}, {"NoNavFocus", 131072}, {"UnsavedDocument", 262144},
				{"NoNav", 196608}, {"NoDecoration", 43}, {"NoInputs", 197120},
				{"ChildWindow", 16777216}, {"Tooltip", 33554432}, {"Popup", 67108864},
				{"Modal", 134217728}, {"ChildMenu", 268435456}, {"NavFlattened", 536870912}
			};
			RegisterEnum(state, "ImGuiWindowFlags", windowFlags, std::size(windowFlags));

			static const EnumEntry childFlags[] = {
				{"None", 0}, {"Borders", 1}, {"Border", 1},
				{"AlwaysUseWindowPadding", 2}, {"ResizeX", 4},
				{"ResizeY", 8}, {"AutoResizeX", 16},
				{"AutoResizeY", 32}, {"AlwaysAutoResize", 64},
				{"FrameStyle", 128}, {"NavFlattened", 256}
			};
			RegisterEnum(state, "ImGuiChildFlags", childFlags, std::size(childFlags));

			static const EnumEntry mouseCursor[] = {
				{"None", -1}, {"Arrow", 0}, {"TextInput", 1}, {"ResizeAll", 2},
				{"ResizeNS", 3}, {"ResizeEW", 4}, {"ResizeNESW", 5}, {"ResizeNWSE", 6},
				{"Hand", 7}, {"Wait", 8}, {"Progress", 9}, {"NotAllowed", 10}, {"COUNT", 11}
			};
			RegisterEnum(state, "ImGuiMouseCursor", mouseCursor, std::size(mouseCursor));

			static const EnumEntry mouseButton[] = {
				{"ImGuiMouseButton_COUNT", 5}, {"ImGuiMouseButton_Left", 0},
				{"ImGuiMouseButton_Middle", 2}, {"ImGuiMouseButton_Right", 1}
			};
			RegisterEnum(state, "ImGuiMouseButton", mouseButton, std::size(mouseButton));

			static const EnumEntry imKey[] = {
				{"A", 546}, {"Backspace", 523}, {"C", 548}, {"COUNT", 645},
				{"Delete", 522}, {"DownArrow", 516}, {"End", 520}, {"Enter", 525},
				{"Escape", 526}, {"Home", 519}, {"Insert", 521}, {"KeyPadEnter", 615},
				{"LeftArrow", 513}, {"PageDown", 518}, {"PageUp", 517}, {"RightArrow", 514},
				{"Space", 524}, {"Tab", 512}, {"UpArrow", 515}, {"V", 567},
				{"X", 569}, {"Y", 570}, {"Z", 571}
			};
			RegisterEnum(state, "ImGuiKey", imKey, std::size(imKey));

			static const EnumEntry hoveredFlags[] = {
				{"None", 0}, {"ChildWindows", 1}, {"RootWindow", 2}, {"AnyWindow", 4},
				{"NoPopupHierarchy", 8}, {"AllowWhenBlockedByPopup", 32},
				{"AllowWhenBlockedByActiveItem", 128}, {"AllowWhenOverlappedByItem", 256},
				{"AllowWhenOverlappedByWindow", 512}, {"AllowWhenDisabled", 1024},
				{"NoNavOverride", 2048}, {"AllowWhenOverlapped", 768}, {"RectOnly", 928},
				{"RootAndChildWindows", 3}, {"ForTooltip", 4096}, {"Stationary", 8192},
				{"DelayNone", 16384}, {"DelayShort", 32768}, {"DelayNormal", 65536},
				{"NoSharedDelay", 131072}
			};
			RegisterEnum(state, "ImGuiHoveredFlags", hoveredFlags, std::size(hoveredFlags));

			static const EnumEntry focusedFlags[] = {
				{"AnyWindow", 4}, {"ChildWindows", 1}, {"None", 0},
				{"RootAndChildWindows", 3}, {"RootWindow", 2}
			};
			RegisterEnum(state, "ImGuiFocusedFlags", focusedFlags, std::size(focusedFlags));

			static const EnumEntry cond[] = {
				{"Always", 1}, {"Appearing", 8}, {"FirstUseEver", 4},
				{"None", 0}, {"Once", 2}
			};
			RegisterEnum(state, "ImGuiCond", cond, std::size(cond));

			static const EnumEntry col[] = {
				{"Text", 0}, {"TextDisabled", 1}, {"WindowBg", 2}, {"ChildBg", 3},
				{"PopupBg", 4}, {"Border", 5}, {"BorderShadow", 6}, {"FrameBg", 7},
				{"FrameBgHovered", 8}, {"FrameBgActive", 9}, {"TitleBg", 10},
				{"TitleBgActive", 11}, {"TitleBgCollapsed", 12}, {"MenuBarBg", 13},
				{"ScrollbarBg", 14}, {"ScrollbarGrab", 15}, {"ScrollbarGrabHovered", 16},
				{"ScrollbarGrabActive", 17}, {"CheckMark", 18}, {"SliderGrab", 19},
				{"SliderGrabActive", 20}, {"Button", 21}, {"ButtonHovered", 22},
				{"ButtonActive", 23}, {"Header", 24}, {"HeaderHovered", 25},
				{"HeaderActive", 26}, {"Separator", 27}, {"SeparatorHovered", 28},
				{"SeparatorActive", 29}, {"ResizeGrip", 30}, {"ResizeGripHovered", 31},
				{"ResizeGripActive", 32}, {"InputTextCursor", 33}, {"TabHovered", 34},
				{"Tab", 35}, {"TabSelected", 36}, {"TabSelectedOverline", 37},
				{"TabDimmed", 38}, {"TabDimmedSelected", 39}, {"TabDimmedSelectedOverline", 40},
				{"PlotLines", 41}, {"PlotLinesHovered", 42}, {"PlotHistogram", 43},
				{"PlotHistogramHovered", 44}, {"TableHeaderBg", 45}, {"TableBorderStrong", 46},
				{"TableBorderLight", 47}, {"TableRowBg", 48}, {"TableRowBgAlt", 49},
				{"TextLink", 50}, {"TextSelectedBg", 51}, {"TreeLines", 52},
				{"DragDropTarget", 53}, {"NavCursor", 54}, {"NavWindowingHighlight", 55},
				{"NavWindowingDimBg", 56}, {"ModalWindowDimBg", 57}, {"COUNT", 58},
				// renamed aliases kept for script compatibility
				{"TabActive", 36}, {"TabUnfocused", 38}, {"TabUnfocusedActive", 39},
				{"NavHighlight", 54}, {"ModalWindowDarkening", 57}
			};
			RegisterEnum(state, "ImGuiCol", col, std::size(col));

			static const EnumEntry dir[] = {
				{"COUNT", 4}, {"Down", 3}, {"Left", 0},
				{"None", -1}, {"Right", 1}, {"Up", 2}
			};
			RegisterEnum(state, "ImGuiDir", dir, std::size(dir));

			static const EnumEntry comboFlags[] = {
				{"HeightLarge", 8}, {"HeightLargest", 16}, {"HeightMask", 30},
				{"HeightRegular", 4}, {"HeightSmall", 2}, {"NoArrowButton", 32},
				{"NoPreview", 64}, {"None", 0}, {"PopupAlignLeft", 1}
			};
			RegisterEnum(state, "ImGuiComboFlags", comboFlags, std::size(comboFlags));

			static const EnumEntry inputFlags[] = {
				{"None", 0}, {"CharsDecimal", 1}, {"CharsHexadecimal", 2},
				{"CharsScientific", 4}, {"CharsUppercase", 8}, {"CharsNoBlank", 16},
				{"AllowTabInput", 32}, {"EnterReturnsTrue", 64}, {"EscapeClearsAll", 128},
				{"CtrlEnterForNewLine", 256}, {"ReadOnly", 512}, {"Password", 1024},
				{"AlwaysOverwrite", 2048}, {"AutoSelectAll", 4096}, {"ParseEmptyRefVal", 8192},
				{"DisplayEmptyRefVal", 16384}, {"NoHorizontalScroll", 32768},
				{"NoUndoRedo", 65536}, {"ElideLeft", 131072}, {"CallbackCompletion", 262144},
				{"CallbackHistory", 524288}, {"CallbackAlways", 1048576},
				{"CallbackCharFilter", 2097152}, {"CallbackResize", 4194304},
				{"CallbackEdit", 8388608}
			};
			RegisterEnum(state, "ImGuiInputTextFlags", inputFlags, std::size(inputFlags));

			static const EnumEntry colorEdit[] = {
				{"None", 0}, {"NoAlpha", 2}, {"NoPicker", 4}, {"NoOptions", 8},
				{"NoSmallPreview", 16}, {"NoInputs", 32}, {"NoTooltip", 64}, {"NoLabel", 128},
				{"NoSidePreview", 256}, {"NoDragDrop", 512}, {"NoBorder", 1024},
				{"AlphaOpaque", 2048}, {"AlphaNoBg", 4096}, {"AlphaPreviewHalf", 8192},
				{"AlphaBar", 65536}, {"HDR", 524288}, {"DisplayRGB", 1048576},
				{"DisplayHSV", 2097152}, {"DisplayHex", 4194304}, {"Uint8", 8388608},
				{"Float", 16777216}, {"PickerHueBar", 33554432}, {"PickerHueWheel", 67108864},
				{"InputRGB", 134217728}, {"InputHSV", 268435456}, {"DefaultOptions_", 177209344},
				{"DisplayMask_", 7340032}, {"DataTypeMask_", 25165824}, {"PickerMask_", 100663296},
				{"InputMask_", 402653184}
			};
			RegisterEnum(state, "ImGuiColorEditFlags", colorEdit, std::size(colorEdit));

			static const EnumEntry treeFlags[] = {
				{"None", 0}, {"Selected", 1}, {"Framed", 2}, {"AllowOverlap", 4},
				{"NoTreePushOnOpen", 8}, {"NoAutoOpenOnLog", 16}, {"DefaultOpen", 32},
				{"OpenOnDoubleClick", 64}, {"OpenOnArrow", 128}, {"Leaf", 256},
				{"Bullet", 512}, {"FramePadding", 1024}, {"SpanAvailWidth", 2048},
				{"SpanFullWidth", 4096}, {"SpanLabelWidth", 8192}, {"SpanAllColumns", 16384},
				{"LabelSpanAllColumns", 32768}, {"NavLeftJumpsToParent", 131072},
				{"CollapsingHeader", 26},
				// renamed aliases kept for script compatibility
				{"AllowItemOverlap", 4}, {"NavLeftJumpsBackHere", 131072}
			};
			RegisterEnum(state, "ImGuiTreeNodeFlags", treeFlags, std::size(treeFlags));

			static const EnumEntry selectFlags[] = {
				{"AllowDoubleClick", 4}, {"AllowItemOverlap", 16},
				{"Disabled", 8}, {"DontClosePopups", 1},
				{"None", 0}, {"SpanAllColumns", 2}
			};
			RegisterEnum(state, "ImGuiSelectableFlags", selectFlags, std::size(selectFlags));

			static const EnumEntry popupFlags[] = {
				{"None", 0}, {"MouseButtonLeft", 0}, {"MouseButtonRight", 1},
				{"MouseButtonMiddle", 2}, {"MouseButtonMask_", 31}, {"MouseButtonDefault_", 1},
				{"NoReopen", 32}, {"NoOpenOverExistingPopup", 128}, {"NoOpenOverItems", 256},
				{"AnyPopupId", 1024}, {"AnyPopupLevel", 2048}, {"AnyPopup", 3072}
			};
			RegisterEnum(state, "ImGuiPopupFlags", popupFlags, std::size(popupFlags));

			static const EnumEntry tabBar[] = {
				{"None", 0}, {"Reorderable", 1}, {"AutoSelectNewTabs", 2},
				{"TabListPopupButton", 4}, {"NoCloseWithMiddleMouseButton", 8},
				{"NoTabListScrollingButtons", 16}, {"NoTooltip", 32},
				{"DrawSelectedOverline", 64}, {"FittingPolicyResizeDown", 128},
				{"FittingPolicyScroll", 256}, {"FittingPolicyMask_", 384},
				{"FittingPolicyDefault_", 128}
			};
			RegisterEnum(state, "ImGuiTabBarFlags", tabBar, std::size(tabBar));

			static const EnumEntry tableColumn[] = {
				{"DefaultSort", 4}, {"Disabled", 1},
				{"IndentDisabled", 131072}, {"IndentEnable", 65536},
				{"IndentMask_", 196608}, {"IsEnabled", 16777216},
				{"IsHovered", 134217728}, {"IsSorted", 67108864},
				{"IsVisible", 33554432}, {"NoClip", 256},
				{"NoDirectResize_", 1073741824}, {"NoHeaderLabel", 4096},
				{"NoHeaderWidth", 8192}, {"NoHide", 128},
				{"NoReorder", 64}, {"NoResize", 32},
				{"NoSort", 512}, {"NoSortAscending", 1024},
				{"NoSortDescending", 2048}, {"None", 0},
				{"PreferSortAscending", 16384}, {"PreferSortDescending", 32768},
				{"StatusMask_", 251658240}, {"WidthFixed", 16},
				{"WidthMask_", 24}, {"WidthStretch", 8}
			};
			RegisterEnum(state, "ImGuiTableColumnFlags", tableColumn, std::size(tableColumn));

			static const EnumEntry tableFlags[] = {
				{"Borders", 1920}, {"BordersH", 384},
				{"BordersInner", 640}, {"BordersInnerH", 128},
				{"BordersInnerV", 512}, {"BordersOuter", 1280},
				{"BordersOuterH", 256}, {"BordersOuterV", 1024},
				{"BordersV", 1536}, {"ContextMenuInBody", 32},
				{"Hideable", 4}, {"NoBordersInBody", 2048},
				{"NoBordersInBodyUntilResize", 4096}, {"NoClip", 1048576},
				{"NoHostExtendX", 65536}, {"NoHostExtendY", 131072},
				{"NoKeepColumnsVisible", 262144}, {"NoPadInnerX", 8388608},
				{"NoPadOuterX", 4194304}, {"NoSavedSettings", 16},
				{"None", 0}, {"PadOuterX", 2097152},
				{"PreciseWidths", 524288}, {"Reorderable", 2},
				{"Resizable", 1}, {"RowBg", 64},
				{"ScrollX", 16777216}, {"ScrollY", 33554432},
				{"SizingFixedFit", 8192}, {"SizingFixedSame", 16384},
				{"SizingMask_", 57344}, {"SizingStretchProp", 24576},
				{"SizingStretchSame", 32768}, {"SortMulti", 67108864},
				{"SortTristate", 134217728}, {"Sortable", 8}
			};
			RegisterEnum(state, "ImGuiTableFlags", tableFlags, std::size(tableFlags));

			static const EnumEntry styleVar[] = {
				{"Alpha", 0}, {"DisabledAlpha", 1}, {"WindowPadding", 2}, {"WindowRounding", 3},
				{"WindowBorderSize", 4}, {"WindowMinSize", 5}, {"WindowTitleAlign", 6},
				{"ChildRounding", 7}, {"ChildBorderSize", 8}, {"PopupRounding", 9},
				{"PopupBorderSize", 10}, {"FramePadding", 11}, {"FrameRounding", 12},
				{"FrameBorderSize", 13}, {"ItemSpacing", 14}, {"ItemInnerSpacing", 15},
				{"IndentSpacing", 16}, {"CellPadding", 17}, {"ScrollbarSize", 18},
				{"ScrollbarRounding", 19}, {"GrabMinSize", 20}, {"GrabRounding", 21},
				{"ImageBorderSize", 22}, {"TabRounding", 23}, {"TabBorderSize", 24},
				{"TabBarBorderSize", 25}, {"TabBarOverlineSize", 26}, {"TableAngledHeadersAngle", 27},
				{"TableAngledHeadersTextAlign", 28}, {"TreeLinesSize", 29}, {"TreeLinesRounding", 30},
				{"ButtonTextAlign", 31}, {"SelectableTextAlign", 32}, {"SeparatorTextBorderSize", 33},
				{"SeparatorTextAlign", 34}, {"SeparatorTextPadding", 35}, {"COUNT", 36}
			};
			RegisterEnum(state, "ImGuiStyleVar", styleVar, std::size(styleVar));

			static const EnumEntry tabItem[] = {
				{"NoCloseWithMiddleMouseButton", 4}, {"NoPushId", 8},
				{"NoTooltip", 16}, {"None", 0},
				{"SetSelected", 2}, {"UnsavedDocument", 1}
			};
			RegisterEnum(state, "ImGuiTabItemFlags", tabItem, std::size(tabItem));
		}
	};

	ImGuiBind _ImGuiBind;
}
