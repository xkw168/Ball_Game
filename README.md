# Ball_Game


## English version

### Game Introduction
&emsp;&emsp;A simplify version of "Battle of Balls", player 1 use W、A、S、D to control and player 2 use ↑、↓、←、→ to control. There will be a *target ball* show on random position on the screen in a fixed time period, the player need to control their own ball to eat the *target ball* while avoid hitting the wall or eated by another player. Once the player died(hit the wall or be eated), he will start again from the init position with the init ball. Scores are showen on the top-right, any player who achieve the *target score* will win.

### Tech
1. [EasyX](http://www.easyx.cn/)（a library used to drawing under win32 environment)

2. Win32 multi-thread（Two-player game, each player is in a seperate thread）

## 中文介绍

### 游戏介绍
&emsp;&emsp;一个简易版的双人《球球大作战》，玩家1使用W、A、S、D控制方向，玩家2使用↑、↓、←、→控制方向。屏幕上会随机出现一个球，玩家吃到球后会变大，撞墙或被吃都会重新回到初始位置。右上角显示分数，任意玩家到达一定分数游戏结束。

### 所用知识
1. [EasyX](http://www.easyx.cn/)（一个用于在win32下面图形绘制的第三方库）

2. Win32多线程（双人游戏，每一个玩家单独一个线程）
