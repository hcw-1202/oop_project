#include "stdafx.h"
#include "Block.h"

namespace game_framework {
	
	void Block::blocktype(int type) {
		
		_type = type;
		CMovingBitmap temp;
		
		if (_type == TOP_WALL) {
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/w1top.bmp" });
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else
				_block.LoadBitmapByString({ "resources/w1top.bmp" });
		}
		else if (_type == RIGHT_WALL) {
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/w1.bmp" });
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else
				
			_block.LoadBitmapByString({ "resources/w1.bmp" });	
		}
		else if (_type == DOWN_WALL) {
			_block.LoadBitmapByString({ "resources/w1down.bmp" });	
		}
		else if (_type == LEFT_WALL) {
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/w1.bmp" });
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else

				_block.LoadBitmapByString({ "resources/w1.bmp" });
		}
		else if (_type == FLOOR) {
			_block.LoadBitmapByString({ "resources/1.16.bmp" });	
		}
		else if (_type == OBSTACLE) {
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/w1top.bmp" });
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else
				_block.LoadBitmapByString({ "resources/w1top.bmp" });
		}
		else if (_type == TRAP) {
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/trapdown.bmp", "resources/trapup.bmp" },RGB(255,255,255));
				temp.SetTopLeft(_block.GetLeft() + (_block.GetWidth() - temp.GetWidth()) / 2, _block.GetTop() + (_block.GetHeight() - temp.GetHeight()) / 2);
				_block = temp;
			}
			else {
				_block.LoadBitmapByString({ "resources/trapdown.bmp", "resources/trapup.bmp" }, RGB(255, 255, 255));
				_block.SetTopLeft(_block.GetLeft() + (_block.GetWidth() - temp.GetWidth()) / 2, _block.GetTop() + (_block.GetHeight() - temp.GetHeight()) / 2);
			}
			
		}
		
		else if (_type == CHEST_OPEN) {	
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/chest_OPEN.bmp" });
				temp.SetTopLeft(_block.GetLeft()+(_block.GetWidth()-temp.GetWidth())/2, _block.GetTop() + (_block.GetHeight() - temp.GetHeight()) / 2);
				_block = temp;
			}
			else {
				_block.LoadBitmapByString({"resources/chest_OPEN.bmp" });
				_block.SetTopLeft(_block.GetLeft() + (_block.GetWidth() - temp.GetWidth()) / 2, _block.GetTop() + (_block.GetHeight() - temp.GetHeight()) / 2);
			}
			
			
			
		}
		else if (_type == CHEST_CLOSE) {
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/chest_close.bmp" });
				temp.SetTopLeft(_block.GetLeft() + (_block.GetWidth() - temp.GetWidth()) / 2, _block.GetTop() + (_block.GetHeight() - temp.GetHeight()) / 2);
				//printf("temp=%d\n", _block.GetLeft());
				_block = temp;
			}
			else {
				_block.LoadBitmapByString({ "resources/chest_close.bmp" });
				_block.SetTopLeft(_block.GetLeft() + (_block.GetWidth() - temp.GetWidth()) / 2, _block.GetTop() + (_block.GetHeight() - temp.GetHeight()) / 2);
			}
		}
		else if (_type == GATE_CLOSE) {
			if (_block.IsBitmapLoaded()) {
				
				temp.LoadBitmapByString({ "resources/doorClose.bmp" }, RGB(255, 255, 255));
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else {
				_block.LoadBitmapByString({ "resources/doorClose.bmp" }, RGB(255, 255, 255));
			}
			
			
		}
		else if (_type == GATE_OPEN) {
			if (_block.IsBitmapLoaded()) {
				
				temp.LoadBitmapByString({ "resources/doorOpen.bmp" }, RGB(255, 255, 255));
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else {
				_block.LoadBitmapByString({ "resources/doorOpen.bmp" }, RGB(255, 255, 255));
			}

		}
		else if (_type == WOOD) {
			_BlockBlood = 3;
			
			
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/Wooden_Crate.bmp" });
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else {
				_block.LoadBitmapByString({ "resources/Wooden_Crate.bmp" });
			}
			
				
			
		}
		else if (_type == CUTEANIME) {
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/cuteanime.bmp" },RGB(255,255,255));
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else {
				_block.LoadBitmapByString({ "resources/cuteanime.bmp" }, RGB(255, 255, 255));
			}
		}
		else if(_type==FIRE){
		if (_block.IsBitmapLoaded()) {
			temp.LoadBitmapByString({ "resources/fire.bmp" }, RGB(255, 255, 255));
			temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
			
			_block = temp;
		}
		else {
			_block.LoadBitmapByString({ "resources/fire.bmp" }, RGB(255, 255, 255));
		}
		}
		else if (_type == TELEPORT) {
			if (_block.IsBitmapLoaded()) {

				temp.LoadBitmapByString({ "resources/teleport.bmp" },RGB(202,232,255));
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());
				_block = temp;
			}
			else {
				_block.LoadBitmapByString({ "resources/teleport.bmp" },RGB(255, 255, 255));
			}
			
		}
		else {
			if (_block.IsBitmapLoaded()) {
				temp.LoadBitmapByString({ "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
				temp.SetTopLeft(_block.GetLeft(), _block.GetTop());

				_block = temp;
			}
			else {
				_block.LoadBitmapByString({ "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
			}
			
		}
			
			
	}
	void Block::starttrap(Hero *hero,bool avoid) {
		
		if (_type == TRAP) {
			_block.SetAnimation(1000, false);
			if (_block.GetFrameIndexOfBitmap() == 1) {
				
				_clk.hero_(hero, clock(), hero->get_hurt_time());
				if ((_block.IsOverlap(_block, hero->get_deter_area()))&& !hero->get_invincible() ) {
					
					
					
					if (!avoid) {
						printf("OAO\n");
						hero->hurt_time();
						hero->hurt(1);
						hero->is_invincible(0);//µL¼Ä;
					}
					;
					
				}

			}
		}
			
	}
	
	bool Block::TF_ContainPosition() {
		return _TF_potion;
	}
	void Block::ContainPotion(bool tf,DROP type) {
		_potiontype = type;
		_TF_potion = tf;
		if (_TF_potion) {
			printf("POTION!!!!!!!\n");
			_drops.Dropstype(_potiontype);

		}
		
		
		
		
	}
	bool Block::is_obstacle() {
		return (_type == TOP_WALL) ||
			(_type == RIGHT_WALL) ||
			(_type == DOWN_WALL) ||
			(_type == LEFT_WALL) ||
			(_type == GATE_CLOSE) ||
			(_type == OBSTACLE) ||
			(_type==WOOD);
	}
	bool Block::CanBeBroken() {
		return (_type == WOOD);
			
	}
	int Block::GetTop() {
		return _block.GetTop();
	}
	int Block::GetHeight() {
		return _block.GetHeight();
	}
	int Block::GetWidth() {
		return _block.GetWidth();
	}
	int Block::GetLeft() {
		return _block.GetLeft();
	}
	void Block::block_gethurt() {

		_BlockBlood--;
		if (_BlockBlood == 0)
			this->blocktype(OTHER);
		
	}
	void Block::AppearDrop(bool TF) {
		_TF_Appear_drop = TF;
	}
	void Block::GetDrop(Hero *hero, bool increase) {
		if(_type==CHEST_OPEN && _TF_Appear_drop){

			_drops.TF_GetDrop(hero,increase);
		}
		
	}
	int Block::block_blood() {
		return _BlockBlood;
	}
	void Block::block_position(int x, int y) {
		
		_block.SetTopLeft(x,y);
		
		if (_TF_potion ) {
			_drops.Drops_position(_block.GetLeft() + ( _block.GetWidth()- _drops.GetWidth()) / 2, _block.GetTop() + (_block.GetHeight() - _drops.GetHeight()) / 2);
			
		}
		//if(this->is_obstacle())
		//	_block.SetTopLeft(x, y);
		
	}
	int Block::Gettype() {
		return _type;
	}
	void Block::show() {
		if (_TF_potion && _TF_Appear_drop) {
			if (_type == CHEST_OPEN) {
				_block.ShowBitmap();
				_drops.show();
			}
			else {
				
				_block.ShowBitmap();
			}
		}
		else{
			_block.ShowBitmap();
		}
		
		
	}
	CMovingBitmap Block::get_block() {
		
		return _block;
	}
}
