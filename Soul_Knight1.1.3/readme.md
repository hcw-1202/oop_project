
## date0322

新增class block 
未來目標:把monster跟hero另外獨立出來，不要寫在library裡面==
把寶箱房間、門做出來

## date0323

新增class bonusroom,spawnroom
遇到問題:寶箱與地板的重疊讓保箱顯示不出來

## date0325

### from bullet

### if (room->Is_crash(*this, 0) || room->Is_crash(*this, 1) || room->Is_crash(*this, 2) || room->Is_crash(*this, 3)) this->flying = false;

我把輸入值改為Character，因為英雄跟怪物碰撞你用CMovingbitmap傳的話，你還要傳right跟left，這很智障。所以子彈碰撞這部分你要重寫一個function，這樣還比較彈性，後面子但要變長條的話也比較好改

### void Bullet::shoot(bool check_dis, CMovingBitmap Hero, CMovingBitmap Monster,bool isright) 

跟上面一樣的問題，你都已經有character、hero、monster了不用再傳Cmovingbitmap了，這樣程式可讀性很低。
多寫了一個Detect_chest的函式來偵測寶箱是否被英雄開啟，與英雄是否到了寶箱旁邊。

#### 遇到問題

現在房間是用多行的方式去存的(vecter<Room *>)但我不知道如何在呼叫其他房間的function，因為她現在只能呼叫Room的function，這部分要再想想。
-->以解決(寫在Room裡面，之後再去override)

## date0326

刪掉了Detect_chest，並利用框架中的is_overlap來寫判斷寶相是否可以開啟
初步構思gate該如何呈現，目前的想法是，跟wall寫在同個_block，假如要生成的話就切換圖片到gate。這部分我有問助教有沒有比較好的寫法，但他沒回我zz
初步構思monster_room的怪物隨機生成，利用vector<Monster>來新增怪物，怪物死掉的話再把他delete掉，vector為空及為怪物全部死亡
寫完TF_entry

HCW:
我把Monster_room裡的vector所存型別從Monster變Monster*，這樣在坐起來應該比較簡單也比較好刪
我做出護盾會隨時間流逝慢慢回復了，怪物碰到角色後角色會短暫無敵(我現在設一秒)，優化子彈飛行的判定

#### For HCW

你要把mygame_run裡面有關monster的東西寫在Monster的class裡面，像是無敵朝向Hero之類的。我們run裡面主要是呈現最外層的東西，所以其他東西要給他包起來。
你要把Monster跟Hero的init寫成constructor，不要額外寫成一個function，不然我不知道怎麼把她push_back到Monster的vector裡面。

## 0329

目前做完戰鬥的雛形，將原本測試用的monster移除，全部改成monsterroom裡的monster，目前除了子彈有時候會****爆走，其他完成了。
如果我發射時範圍內沒怪物，子彈向前飛的過程中，我靠近怪物，子彈就會停住或轉彎。

#### problem
現在能一次顯示多個房間，但碰撞到房間時，其他房間還會繼續動(已在3/31解決)。
Gate無法正常顯示(已在3/31解決)
`在物件_block要被重複寫入的時候，Room的Set_position要放在最後面，room的寫法是先決定_block的物件，之後再給予xy值`

## 0331

隨著英雄身上的For迴圈越來越多，他似乎有越來越慢的趨勢qq。
完成Gate_Close與 Gate_Open的功能，並解決固定英雄碰撞後，其他房間移動的問題ouo

## 0401 0402

1.優化房間移動(應該是有啦)，並寫了DistributeMap來分配與控制房間


2.寫了Hero operator=


3.修改Block load的logic


## 0403

- 現在能自動控制門了
    1. 偵測英雄是否進入房間，然後關起門
    2. 偵測怪物是否全都死亡，然後打開門，並生成寶箱
- 寫了隨機生成房間的雛型


## 0406

- 已經將mygame_run.cpp做了初步的優化，將怪物移動的內容都搬到distribute.cpp裡了
- 將怪物隨機生成、怪物移動都做完了。
- 目前要想辦法處理子彈的bug，但感覺會是個大工程QAQ

## 0408

- 怪物現在有分左右了
- 子彈也完成了
- 但我還沒讓怪物會射子彈，感覺這樣記憶體會爆炸
- 動畫不知道為甚麼出不來QAQ

## 0409

- 完成房間分配(未隨機)
- 新增開起寶箱的圖片
- 利用破解apk get到很多素材:D
- 更改房間位置配置定義:`從中間開始擴展 `

## 0411

- 完成自動生成通道，但還沒處理碰撞 p.s戰地風雲好玩

## 0415

- 方塊大小(now 60*60)
- 寶箱呈現方式
- 優化碰撞
- TF_entry()的判斷修改
- 新增TF_in_route
- 修復route bug
- 修復crash bug

## 0424

- 刪除chest,並新增TF_interaction用於判斷是否與物件互動
- 新增TF_inner_room 用於偵測英雄是否進入房間


|     |TF_inner_room | TF_entry |
| ----| ---- | ---- |
| 範圍 | 房間外側 | 房間內測 |

- 修復route的碰撞
- 把房間分成上下兩層，用於區分物件與地板

## 0425

- 完成隨機生成房間 (挖庫挖庫:D)
- 寫了一個涵蓋所有rand的class `RandForAll`

## 0426

- 完成寶箱隨機生成
- 把portal修得美美的
- 可以重複生成地圖(傳送雛形)
- 完成木箱雛形
## 0427
- 將圍牆新增陰影

## 0505
- 新增三張中型地圖
- 目前剩下叛逆的豬，怪物子彈，走道子彈碰撞！

## 0506
- 新增藥水並在怪物房寶箱中呈現。

` orange目前地圖的部分就先差不多這樣ouo 未來可能會新增地刺陷阱`

## 0508
- 讓傳送門可以傳送至下張地圖(重新生成)

## 0509
- 完成地刺
- 修改怪物生成避開障礙物和怪物

## 0515
- 完成遊俠動畫

## 0516
- 完成遊俠技能(躲避子彈、加速)
- 優化怪物移動

## 0517
- 移除陰影(框架不支援所以放棄)
- 把地板往下移20，使地板不與牆壁切齊
- 技能冷卻

## 0519
- 調整障礙物碰撞範圍
- 註解調怪物移動
- 修改英雄與障礙物的塗層順序(新增判斷)

## 0526
- 解決塗層問題(留下通道塗層的小bug，因為好難改zz)
- 完成暴走小豬的動畫
- 新增V健打開無敵
- 考慮修改怪物移動方式(使用Astar algorithm)

## 0527
- 發現改偵數的方式可以提高遊戲順暢度:D
- 完成哥布林動畫

## 0528
- 修改門的圖片
- 將英雄血條與護甲條修改為動態呈現
## 0529
- 新增勝利與失敗動畫
- 新增樓層顯示

## 0601
- 優化怪物移動


# 問題
- 武器
- 怪物距離判定
- 怪物子彈memory leak
- 第二層
- 小地圖
- ~~ boss血條 ~~
=======
## date0322

新增class block 
未來目標:把monster跟hero另外獨立出來，不要寫在library裡面==
把寶箱房間、門做出來

## date0323

新增class bonusroom,spawnroom
遇到問題:寶箱與地板的重疊讓保箱顯示不出來

## date0325

### from bullet

### if (room->Is_crash(*this, 0) || room->Is_crash(*this, 1) || room->Is_crash(*this, 2) || room->Is_crash(*this, 3)) this->flying = false;

我把輸入值改為Character，因為英雄跟怪物碰撞你用CMovingbitmap傳的話，你還要傳right跟left，這很智障。所以子彈碰撞這部分你要重寫一個function，這樣還比較彈性，後面子但要變長條的話也比較好改

### void Bullet::shoot(bool check_dis, CMovingBitmap Hero, CMovingBitmap Monster,bool isright) 

跟上面一樣的問題，你都已經有character、hero、monster了不用再傳Cmovingbitmap了，這樣程式可讀性很低。
多寫了一個Detect_chest的函式來偵測寶箱是否被英雄開啟，與英雄是否到了寶箱旁邊。

#### 遇到問題

現在房間是用多行的方式去存的(vecter<Room *>)但我不知道如何在呼叫其他房間的function，因為她現在只能呼叫Room的function，這部分要再想想。
-->以解決(寫在Room裡面，之後再去override)

## date0326

刪掉了Detect_chest，並利用框架中的is_overlap來寫判斷寶相是否可以開啟
初步構思gate該如何呈現，目前的想法是，跟wall寫在同個_block，假如要生成的話就切換圖片到gate。這部分我有問助教有沒有比較好的寫法，但他沒回我zz
初步構思monster_room的怪物隨機生成，利用vector<Monster>來新增怪物，怪物死掉的話再把他delete掉，vector為空及為怪物全部死亡
寫完TF_entry

HCW:
我把Monster_room裡的vector所存型別從Monster變Monster*，這樣在坐起來應該比較簡單也比較好刪
我做出護盾會隨時間流逝慢慢回復了，怪物碰到角色後角色會短暫無敵(我現在設一秒)，優化子彈飛行的判定

#### For HCW

你要把mygame_run裡面有關monster的東西寫在Monster的class裡面，像是無敵朝向Hero之類的。我們run裡面主要是呈現最外層的東西，所以其他東西要給他包起來。
你要把Monster跟Hero的init寫成constructor，不要額外寫成一個function，不然我不知道怎麼把她push_back到Monster的vector裡面。

## 0329

目前做完戰鬥的雛形，將原本測試用的monster移除，全部改成monsterroom裡的monster，目前除了子彈有時候會****爆走，其他完成了。
如果我發射時範圍內沒怪物，子彈向前飛的過程中，我靠近怪物，子彈就會停住或轉彎。

#### problem
現在能一次顯示多個房間，但碰撞到房間時，其他房間還會繼續動(已在3/31解決)。
Gate無法正常顯示(已在3/31解決)
`在物件_block要被重複寫入的時候，Room的Set_position要放在最後面，room的寫法是先決定_block的物件，之後再給予xy值`

## 0331

隨著英雄身上的For迴圈越來越多，他似乎有越來越慢的趨勢qq。
完成Gate_Close與 Gate_Open的功能，並解決固定英雄碰撞後，其他房間移動的問題ouo

## 0401 0402

1.優化房間移動(應該是有啦)，並寫了DistributeMap來分配與控制房間


2.寫了Hero operator=


3.修改Block load的logic


## 0403

- 現在能自動控制門了
    1. 偵測英雄是否進入房間，然後關起門
    2. 偵測怪物是否全都死亡，然後打開門，並生成寶箱
- 寫了隨機生成房間的雛型


## 0406

- 已經將mygame_run.cpp做了初步的優化，將怪物移動的內容都搬到distribute.cpp裡了
- 將怪物隨機生成、怪物移動都做完了。
- 目前要想辦法處理子彈的bug，但感覺會是個大工程QAQ

## 0408

- 怪物現在有分左右了
- 子彈也完成了
- 但我還沒讓怪物會射子彈，感覺這樣記憶體會爆炸
- 動畫不知道為甚麼出不來QAQ

## 0409

- 完成房間分配(未隨機)
- 新增開起寶箱的圖片
- 利用破解apk get到很多素材:D
- 更改房間位置配置定義:`從中間開始擴展 `

## 0411

- 完成自動生成通道，但還沒處理碰撞 p.s戰地風雲好玩

## 0415

- 方塊大小(now 60*60)
- 寶箱呈現方式
- 優化碰撞
- TF_entry()的判斷修改
- 新增TF_in_route
- 修復route bug
- 修復crash bug

## 0424

- 刪除chest,並新增TF_interaction用於判斷是否與物件互動
- 新增TF_inner_room 用於偵測英雄是否進入房間


|     |TF_inner_room | TF_entry |
| ----| ---- | ---- |
| 範圍 | 房間外側 | 房間內測 |

- 修復route的碰撞
- 把房間分成上下兩層，用於區分物件與地板

## 0425

- 完成隨機生成房間 (挖庫挖庫:D)
- 寫了一個涵蓋所有rand的class `RandForAll`

## 0426

- 完成寶箱隨機生成
- 把portal修得美美的
- 可以重複生成地圖(傳送雛形)
- 完成木箱雛形
## 0427
- 將圍牆新增陰影

## 0505
- 新增三張中型地圖
- 目前剩下叛逆的豬，怪物子彈，走道子彈碰撞！

## 0506
- 新增藥水並在怪物房寶箱中呈現。

` orange目前地圖的部分就先差不多這樣ouo 未來可能會新增地刺陷阱`

## 0508
- 讓傳送門可以傳送至下張地圖(重新生成)

## 0509
- 完成地刺
- 修改怪物生成避開障礙物和怪物

## 0515
- 完成遊俠動畫

## 0516
- 完成遊俠技能(躲避子彈、加速)
- 優化怪物移動

## 0517
- 移除陰影(框架不支援所以放棄)
- 把地板往下移20，使地板不與牆壁切齊
- 技能冷卻

## 0519
- 調整障礙物碰撞範圍
- 註解調怪物移動
- 修改英雄與障礙物的塗層順序(新增判斷)

## 0526
- 解決塗層問題(留下通道塗層的小bug，因為好難改zz)
- 完成暴走小豬的動畫
- 新增V健打開無敵
- 考慮修改怪物移動方式(使用Astar algorithm)

## 0527
- 發現改偵數的方式可以提高遊戲順暢度:D
- 完成哥布林動畫

## 0528
- 修改門的圖片
- 將英雄血條與護甲條修改為動態呈現
## 0529
- 新增勝利與失敗動畫
- 新增樓層顯示

## 0601
- 優化怪物移動
# 0603by HCW
- 我第二關boss弄完 但有bug，在Distribute room叫第二支boss，程式可以正常運作，但boss不會出現...
## 0607
- 完成英雄天賦雛形
- 預計將英雄天賦變為static(testing) `完成`
- 完成通過畫面
- 新增破完怪物房的通知動畫
## 0611
- 新增近戰
- 新增近戰特效
- 新增音效
- 更改icon、about me
- 新怪物偵測驚嘆號


# 問題
- ~~顯示bug~~
- ~~通道bug~~
- 武器
- ~~怪物距離判定~~
- ~~怪物子彈memory leak~~
- 第二層
- 小地圖(放棄)
- ~~boss血條~~

# 第二關需求
- 怪物、boss血量、速度提升




