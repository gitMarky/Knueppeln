/**
	BallAttackOrder
	

	@author 
*/

local ManaCost = 25;

func Launch(object clonk, int x, int y, proplist params)
{
	params.ball->HomeCall(x, y);
	RemoveObject();
}