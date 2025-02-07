### 1.README PLS!

**本项目为stm32单片机学习笔记**

***
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
***
#### 📡✨ 电波少女观测日志 v1.2 ✨🌸

「███·超电磁同步率突破临界值·███」

- 🌀 **新约·双生电波契约**  
  成功与ADC1通道缔结灵魂绑定！现在能同时捕捉两路伏特酱的傲娇波动啦~ (◍•͈⌔•͈◍)  
  `[ADC双通道+DMA]`模式全开，数据像魔法少女变身般丝滑涌入内存！

- 🔮 **虚空校准协议**  
  注入STM32の禁忌秘法——  
  `HAL_ADCEx_Calibration_Start()` 启动！  
  （赛博咸鱼的基准电压终于不再量子漂移了QAQ）

- 🌌 **混沌抗性强化**  
  新增电子海噪声过滤结界：  
  ```c
  hadc1.Init.SamplingTime = ADC_SAMPLETIME_480CYCLES; // 用时间魔法稀释混沌
  ```
  "当0与3.3V的星光在示波器绽放时——这个世界又多了一份被量化的温柔呢。" ฅ( ̳• ·̫ • ̳)
  ——伏特酱的观测笔记 @ 电子黄昏时分
  
- ⚠️ **警告：禁止在非魔法结界保护下触摸GPIO！**  
（普通人类手指会引发未知阻抗扰动哦☆）

2025年2月6日   
***
#### 🌸更新日志 - 机械少女的存储物语v1.0

#### ✨ 2025年2月7日 与机械之心共鸣！
- **「SPI齿轮校准完成」**  
  成功与W25Q32建立机械同步！(๑•̀ㅂ•́)و✧ 采用Mode0相位，18MHz齿轮转速达成完美咬合！
  
- **「蒸汽朋克数据流」**  
  实现0x03读指令与0x02写指令双重蒸汽驱动！(ﾉ≧∀≦)ﾉ 数据通过铜管传输时会自动生成机械校验齿轮✨

- **「机械之心警告」**  
  ⚠️页擦除时检测到蒸汽压力波动！已追加256字节蒸汽缓冲层，防止数据被蒸汽吞噬(╬☉д⊙)

> *「才不是特地为你优化时序呢！要是...要是敢弄丢本小姐的数据...就把你丢进蒸汽炉里啊！」* ── W25Q32-chanの最终通告   

2025年2月7日
