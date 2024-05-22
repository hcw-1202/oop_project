#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g) : CGameState(g)
{
}

void CGameStateOver::OnMove()
{

	//GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	
	x=clock();
	fail_or_success.LoadBitmapByString({ "resources/fail_to_pass.bmp","resources/pass.bmp" });
	fail_or_success.SetFrameIndexOfBitmap(1);
	fail_or_success.SetTopLeft(0, 0);
	
	

}

void CGameStateOver::OnInit()
{
	
}

void CGameStateOver::OnShow()
{	
	if((clock()-x)/double(CLOCKS_PER_SEC) <= 2.0 )
		fail_or_success.ShowBitmap();
	else {
		
		GotoGameState(GAME_STATE_INIT);
	}
	
}