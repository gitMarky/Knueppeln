static team_exclusiveChampions;
static lastChosenChampion;

global func GetChampions()
{
	var Champ_Def = [ElectroMan, FireMan, LaserMan, TimeMan, IceMan, EarthMan, NinjaMan, BallsMan, BombMan];
	return Champ_Def;
}

global func UpdateAllSelectionMenus()
{
	for(var o in FindObjects(Find_ID(Clonk), Find_OCF(OCF_Alive)))
	{
		o->UpdateSelectionMenu();
	}
}

global func SetLastChosenChampion(int plr, id champ)
{
	if(lastChosenChampion == nil)
		lastChosenChampion = CreateArray(GetPlayerCount()*2);
		
	lastChosenChampion[plr] = champ;
}

global func GetLastChosenChampion(int plr)
{
	if(lastChosenChampion == nil)
		return nil;
		
	return lastChosenChampion[plr];
}

global func InitTeamExclusiveChamps(int teamcount)
{
	team_exclusiveChampions = CreateArray(2);
	
	for(var i = 0; i < GetLength(team_exclusiveChampions); i++)
	{
		team_exclusiveChampions[i] = [];
	}
}

global func RemoveTeamChamp(int teamid, id ChampType)
{
	var banned = team_exclusiveChampions[teamid -1];
	var newb = CreateArray(GetLength(banned) +1);
	
	for(var i = 0; i < GetLength(banned); i++)
	{
		newb[i] = banned[i];
	}
	
	newb[GetLength(newb) - 1] = ChampType;
	team_exclusiveChampions[teamid -1] = newb;
}

global func ResetTeamExclusiveChamps()
{
	for(var i = 0; i < GetLength(team_exclusiveChampions); i++)
	{
		team_exclusiveChampions[i] = [];
	}
}

global func GetBannedTeamChampions(int teamid)
{
	return team_exclusiveChampions[teamid -1];
}


global func DrawLightningSmall(fromX, fromY, toX, toY, props)
{
	props = props ??
	{
		Size = 10, // will be overwritten
		R = 255, G = 255, B = 255,
		Alpha = PV_KeyFrames(0, 0, 200, 100, 0, 200, 255, 1000, 0),
		Phase = PV_Random(0, 5),
		BlitMode = GFX_BLIT_Additive
	};
	var a = Angle(fromX, fromY, toX, toY);
	var d = Distance(fromX, fromY, toX, toY);
	props.Rotation = a;
	props.Size = d;
	CreateParticle("Lightning", (fromX + toX) / 2, (fromY + toY) / 2, 0, 0, PV_Random(15, 25), props, 1);
}

global func DrawLightning(fromX, fromY, toX, toY, props)
{
	props = props ??
	{
		Size = 10, // will be overwritten
		R = 255, G = 255, B = 255,
		Alpha = PV_KeyFrames(0, 0, 200, 100, 0, 200, 255, 1000, 0),
		Phase = PV_Random(0, 5),
		BlitMode = GFX_BLIT_Additive
	};
	var lastX,lastY;
    var x1=fromX;
    var y1=fromY;
    var x2=toX;
    var y2=toY;
    
    lastX=x1;
    lastY=y1;
    
    var i, deltax, deltay, numpixels;
    var d, dinc1, dinc2;
    var x, xinc1, xinc2;
    var y, yinc1, yinc2;

    deltax = Abs(x2 - x1);
    deltay = Abs(y2 - y1);

    if(deltax >= deltay) {
        numpixels = deltax + 1;
        d = (2 * deltay) - deltax;
        dinc1 = deltay << 1;
        dinc2 = (deltay - deltax) << 1;
        xinc1 = 1;
        xinc2 = 1;
        yinc1 = 0;
        yinc2 = 1;
    } else {
        numpixels = deltay + 1;
        d = (2 * deltax) - deltay;
        dinc1 = deltax << 1;
        dinc2 = (deltax - deltay) << 1;
        xinc1 = 0;
        xinc2 = 1;
        yinc1 = 1;
        yinc2 = 1;
    }

    if(x1 > x2) {
        xinc1 = -xinc1;
        xinc2 = -xinc2;
    }
    if(y1 > y2) {
        yinc1 = -yinc1;
        yinc2 = -yinc2;
    }

    x=x1;
    y=y1;
	
	var last = 1;
    for(i = 1; i < numpixels; i++) {
        if((!Random(25)) || (last < i - 12) || ((i % (numpixels - 1)/2) == 0))
        {
        	last = i;
        	var aX=x+RandomX(-10,10);
        	var aY=y+RandomX(-10,10);
        	DrawLightningSmall(lastX,lastY,aX,aY, props);
        	lastX=aX;
        	lastY=aY;
        }

        if(d < 0) {
            d = d + dinc1;
            x = x + xinc1;
            y = y + yinc1;
        } else {
            d = d + dinc2;
            x = x + xinc2;
            y = y + yinc2;
        }
    }
}

global func Unstuck()
{
	if(!this->Stuck())
		return;

	var flag = false;
	
	var ix = GetX();
	var iy = GetY();

	for(var i = 0; i < 40; i += 5)
	{
		for(var r = 0; r < 360; r += 10)
		{
			var x = Sin(r, i);
			var y = -Cos(r, i);
		
			if(!GBackSolid(x, y))
			{
				SetPosition(ix + x, iy + y);
				
				if(!this->Stuck())
				{
					flag = true;
					break;
				}
			}

		}
		
		if(flag)
			break;
	}
	
}

global func ShuffleArray(array arr)
  {
    for (var i = GetLength(arr) - 1; i > 0; i--)
    {
      var index = Random(i + 1);
      // Simple swap
      var a = arr[index];
      arr[index] = arr[i];
      arr[i] = a;
    }
    
    return arr;
  }