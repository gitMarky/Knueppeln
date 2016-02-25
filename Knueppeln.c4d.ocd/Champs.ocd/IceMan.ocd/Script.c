/**
	IceMan
	

	@author 
*/

#include Man

local Name = "$Name$";
local Description = "$Description$";

local Special1Spell = IceProjectile;
local Special2Spell = IceShard;
local Special3Spell = IceShardUltimate;

func Special1(object clonk, int x, int y, bool released, bool mouseclick, bool abletocast, bool cooldown)
{
	if(!released && !mouseclick && abletocast && !cooldown)
		clonk->LaunchSpell(IceProjectile, x, y, 0, 0);
}

func Special2(object clonk, int x, int y, bool released, bool mouseclick, bool abletocast,  bool cooldown)
{
	if (released || mouseclick || cooldown) return;
	
	var existing = FindObject(Find_ID(IceShard), Find_Owner(clonk->GetOwner()), Find_Category(C4D_StaticBack), Find_Func("GetProperty", "is_selected"));
	if (existing)
	{
		existing->FireNow();
		var other = FindObjects(Find_ID(IceShard), Find_Owner(clonk->GetOwner()), Find_Category(C4D_StaticBack), Sort_Func("GetProperty", "number"));
		if (GetLength(other))
		{
			other[0].is_selected = true;
		}
		for (var shard in other)
			shard.offset += shard.angle_distance;
		return;
	}
	
	if(abletocast)
	{
		if(clonk->LaunchSpell(IceShard, x, y, 0, 0))
			return 1;
	}
	
	return 0;
}

func Special3(object clonk, int x, int y, bool released, bool mouseclick, bool abletocast, bool cooldown)
{
	if (released || mouseclick || cooldown) return;
	
	var existing = FindObject(Find_ID(IceShardUltimate), Find_Owner(clonk->GetOwner()), Find_Category(C4D_StaticBack), Find_Func("GetProperty", "is_selected"));
	if (existing)
	{
		existing->FireNow();
		var other = FindObjects(Find_ID(IceShardUltimate), Find_Owner(clonk->GetOwner()), Find_Category(C4D_StaticBack), Sort_Func("GetProperty", "number"));
		if (GetLength(other))
		{
			other[0].is_selected = true;
		}
		for (var shard in other)
			shard.offset += shard.angle_distance;
		return;
	}
	
	if(abletocast)
	{
		if(clonk->LaunchSpell(IceShardUltimate, x, y, 0, 0))
			return 1;
	}
	
	return 0;
}

func JumpEffect(object clonk, dir)
{
	var from, to;

	if (dir == "Up")
	{
		from = 50; 
		to = 130;
	}
	if (dir == "Left")
	{
		from = -30; 
		to = 50;
	}
	if (dir == "Right")
	{
		from = 130; 
		to = 210;
	}
	if (dir == "Down")
	{
		from = 230; 
		to = 310;
	}

	clonk->Sound("Fire::Inflame", false, 30, nil, nil, nil, 200);
	
	var trailparticles =
	{
		R = 255,
		G = 255,
		B = 255,
		Size = PV_Linear(PV_Random(4, 6), 0),
		OnCollision = PC_Die(),
		CollisionVertex = 0,
		ForceX = PV_Linear(0, PV_Random(-20, 20, 10)),
		ForceY = PV_Linear(0, PV_Random(-20, 20, 10)),
		DampingX = 900, DampingY = 900,
		BlitMode = GFX_BLIT_Additive
	};
	
	for(var i = from; i < to; i+=5)
	{
		var r = 10;
		var x = Cos(i, r);
		var y = Sin(i, r);
		clonk->CreateParticle("StarFlash", x, y, Cos(i, r), Sin(i, r), 60, trailparticles, 10);
	}
}

func BlockEffect(object clonk, int radius)
{
	var border = 
	{
		R = 255,
		G = 255,
		B = 255,
		Size = PV_Linear(PV_Random(4, 6), 0),
		OnCollision = PC_Die(),
		CollisionVertex = 0,
		ForceX = PV_Linear(0, PV_Random(-10, 10, 10)),
		ForceY = PV_Linear(0, PV_Random(-10, 10, 10)),
		DampingX = 900, DampingY = 900,
		BlitMode = GFX_BLIT_Additive
	};
	
	for (var angle = 0; angle < 360; angle += 20)
	{
		clonk->CreateParticle("StarFlash", Sin(angle + RandomX(-5, 5), radius), -Cos(angle + RandomX(-5, 5), radius), 0, 0, PV_Random(20, 30), border, 16);
	}
}