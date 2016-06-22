/**
	Lib_BuildingElement
	

	@author KKenny
*/

#include Lib_BuildingElement
#include Library_Stackable

func MaxStackCount() { return 48; }
func InitialStackCount() { return 4; }

local Name = "$Name$";
local Description = "$Description$";

local build_offset_x = 0;
local build_offset_y = 0;

local build_grid_x = 8;
local build_grid_y = 8;

func IsBuildingTile() { return true; }
func CanBeHitByPickaxe() { return true; }

func Construction()
{
	SetClrModulation(RGBa(180, 180, 180, 255));
	return _inherited();
}

func Constructed()
{
	SetCategory(C4D_StaticBack);
	SetClrModulation(RGBa(255,255,255,255));
	this.Collectible = false;
	return _inherited();
}

func Destruct()
{
	SetCategory(C4D_Object);
	SetClrModulation(RGBa(180, 180, 180, 255));
	this.Collectible = true;
	return _inherited();
}

func OnHitByPickaxe()
{
	Destruct();
}