### 1.README PLS!

**本项目为stm32单片机学习笔记**

***

准备参加大唐杯的5G+智能车赛道，听说以往都没有，这是第一届   
赛事说明中推荐stm32主控的小车，正好原本就计划51学完后学32~，可所谓契合度高达100%   
EIDE是真好用啊这插件，编译速度，烧录速度比Keil Assistant快不少，毕竟人家是自带编译器    
不知道学完stm32又要多久呢……   
2025年1月4日
***
printf重定向方便又好玩啊！！   
***
#### PWMの心跳律动——定时器魔导书与脉冲调律契约   
（战术注释）   
✦ 心跳律动 = PWM波形模拟心脏搏动   
✦ 魔导书 = 寄存器配置秘籍   
✦ 调律契约 = 占空比与频率的灵魂共鸣协议    
※**警告**※占空比超过50%会触发傲娇阈值哦(´-ω-`)      

2025年2月3日
***
#### 时之回响——STM32捕获中断与脉冲心跳的羁绊契约
（战术注释）   
♯ 时之回响 = 输入捕获的时基共振   
♯ 脉冲心跳 = 边沿检测的电气生命   
♯ 羁绊契约 = 捕获/比较寄存器的灵魂共鸣   

※**注意**※ 当CCR寄存器溢出时，会触发「时之泪」现象，请备好72MHz圣晶石护体！(ﾉ≧∀≦)ﾉ

2025年2月4日   

***
#### 「死区结界の咏叹调——STM32高階時空制御術式·限定PWM輪舞曲」

##### 時空調律宣言

- **ARR/PSC時之沙漏**  
  設定72MHz星霊力場的脈衝心跳周期

- **RCR轮回计数器**  
  刻印PWM重生次数（突破255次元限制的禁忌魔方阵）

- **BDTR相位护盾**  
  - 死区时间 = 両刀流劍士の安全结界（納秒級時空扭曲力場）  
  - MOE/MOE2 = 光與闇の出力使徒（OCx/OCxN覺醒開關）

##### 警告
※禁忌※  
CCR影子寄存器暴走时，会引发「PWM无限剑制」事件！需在中断服务函数内咏唱`__HAL_TIM_DISABLE_IT()`封印咒文(๑•̀ㅂ•́)و✧

##### 結語
**「このPWMは…たった168回の輪廻で魂を燃やすのです」**   

2025年2月4日   
***
#### 「⚡DMAの記憶漂流戦記～ROMから現世への超次元転送術⚡」

#### 📜術式概要
**「FLASHの森からSRAMの海へ、時空を超える冒険が始まる！」**  
- ✨ **ROM → RAM 転送**  
  `FLASH_BASE`(封印された記憶の書庫) ➔💫 `SRAM_BUFFER`(覚醒の転送門)  
  📌 転送単位：`DMA_MDATAALIGN_WORD`(4字节の神聖刻印)  
  🔥 転送量：`0x666`(悪魔的数字じゃないわ！ただのテスト用666バイトよ)  

- 🌌 **RAM → USART 次元通信**  
  `SRAM_BUFFER`(転送門の出口) ➔🚪 `USART1->DR`(異世界通信の扉)  
  ⚔️ 転送速度：`115200bps`(神速の通信剣技)  
  🌀 転送模式：`DMA_CIRCULAR`(無限ループの時空渦)  

2025年2月5日   

