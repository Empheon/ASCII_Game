#pragma once

#include <render/Texture.h>

const Texture TEX_TANK_BODY = {
5, 5,
L"/═╤═\\"
L"║   ║"
L"╠ ☼ ╣"
L"║   ║"
L"\\═╧═/" };

const Texture TEX_TANK_CURSOR = {
3, 3,
L" ≡ "
L"─Φ─"
L" ≡ ",
true };

const Texture TEX_TANK_CANNON[] = {
	{
		7, 7,
		L"       "
		L"       "
		L"       "
		L"Θ══    "
		L"       "
		L"       "
		L"       ",
		true
	},
	{
		7, 7,
		L"Θ      "
		L" \\     "
		L"  \\    "
		L"       "
		L"       "
		L"       "
		L"       ",
		true
	},
	{
		7, 7,
		L"   Θ   "
		L"   ║   "
		L"   ║   "
		L"       "
		L"       "
		L"       "
		L"       ",
		true
	},
	{
		7, 7,
		L"      Θ"
		L"     / "
		L"    /  "
		L"       "
		L"       "
		L"       "
		L"       ",
		true
	},
	{
		7, 7,
		L"       "
		L"       "
		L"       "
		L"    ══Θ"
		L"       "
		L"       "
		L"       ",
		true
	},
	{
		7, 7,
		L"       "
		L"       "
		L"       "
		L"       "
		L"    \\  "
		L"     \\ "
		L"      Θ",
		true
	},
	{
		7, 7,
		L"       "
		L"       "
		L"       "
		L"       "
		L"   ║   "
		L"   ║   "
		L"   Θ   ",
		true
	},
	{
		7, 7,
		L"       "
		L"       "
		L"       "
		L"       "
		L"  /    "
		L" /     "
		L"Θ      ",
		true
	},
};