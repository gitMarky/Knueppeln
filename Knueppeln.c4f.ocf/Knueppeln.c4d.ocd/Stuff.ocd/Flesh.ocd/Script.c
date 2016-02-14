/**
	Flesh
	

	@author 
*/

local Name = "$Name$";
local Description = "$Description$";

local randX = 10;
local randY = 10;

func Initialize()
{
	SetClrModulation(RGB(128,0,0));
	AddEffect("DrawBlood", this, 1, 1, this);
}

func FxDrawBloodTimer(object target, proplist effect, int time)
{
	for(var i = 0; i < 10; i++)
	{
		var x = GetX() + Random(randX) - randX/2;
		var y = GetY() + Random(randY) - randY/2;
		
		if(!CanDrawOn(x-GetX(), y-GetY()))
		{		
			continue;
		}
		
		DrawMaterialQuad("BackgroundBlood-gore", x, y, x+1, y, x+1, y+1, x, y+1, true);
	}
	
	return 0;
}

func Hit()
{
	Sound("splash*", false, 10);
	//CastPXS("Blood", 25, 10);
	RemoveObject();
}

func CanDrawOn(x, y)
{
	if(GBackSemiSolid(x,y) || GBackSky(x,y))
	{
		return false;
	}
	return true;
}