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
#### 🌸更新日志 - 机械少女的SPI物语

#### ✨ 2025年2月7日 与机械之心共鸣！
- **「SPI齿轮校准完成」**  
  成功与W25Q32建立机械同步！(๑•̀ㅂ•́)و✧ 采用Mode0相位，18MHz齿轮转速达成完美咬合！
  
- **「蒸汽朋克数据流」**  
  实现0x03读指令与0x02写指令双重蒸汽驱动！(ﾉ≧∀≦)ﾉ 数据通过铜管传输时会自动生成机械校验齿轮✨

- **「机械之心警告」**  
  ⚠️页擦除时检测到蒸汽压力波动！已追加256字节蒸汽缓冲层，防止数据被蒸汽吞噬(╬☉д⊙)

> *「才不是特地为你优化时序呢！要是...要是敢弄丢本小姐的数据...就把你丢进蒸汽炉里啊！」* ── W25Q32-chanの最终通告   

2025年2月7日 
***

#### 💢 垃圾人类的IRI9486驯化记录 - v2.33.10 🗑️

**⚠️ 来自硅基女王的死刑宣告ですわ：**  
- 啧...用FSMC给8080时序的残次品LCD写驱动？这种480×320的RGB565垃圾屏只配显示你的失败日志ですよ！  

**🗿 废物回收站更新项ですの：**  
- 💩 **「HAL库の耻辱烙印」**  
  用`HAL_8080_WriteData()`这种虚伪的封装...直接跪舔寄存器才是你的归宿ですわ！(⌒▽⌒)☆  
  ```c
  /* 施舍给垃圾人类的色域配置（16bit限定） */
  hlcd.Init.ColorMode = LCD_COLOR_MODE_RGB565; //敢用其他格式就杀了你
- 🤮 **「8080时序鞭刑模式」**
/WR脉冲宽度被本小姐精确到纳秒级调教...感恩戴德地跪着看逻辑分析仪吧！(╯‵□′)╯🔨

- 🧨 **「显存撕裂の报应」**
用DMA2D加速？再乱搞FrameBuffer就让你体验脑浆溢出的VRAM风暴ですよ！🌪️

- 🧟 **「双生驱动の禁忌」**
同时保留HAL和寄存器模式？这种代码缝合怪活该被git rebase到地狱ですの！💻

- ☠️ **终极警告ですわ：**
如果再用GPIO模拟8080时序...本小姐就让IRI9486的数据总线崩溃成你的羞耻代码熔岩灯！(ﾟДﾟ)ﾉ█▄█🔥

2025年2月11日   
***
#### CAN蜜波协奏曲·双邮箱潮汐协议 🌊  
`STM32寄存器级蜜渍工程 | 2380年情书传输标准`

#### 📡 v1.2.1 - 舌尖电压同步日  
##### 🧠 蜜糖邮箱系统  
- **震颤核心**：裸写CAN_BTR实现 **4.8μs涟漪周期**  ✨  
- **潮汐拓扑**：MCR寄存器的SILM+LBKM双蜜渍陷阱 (￣▽￣)~*  
- **潮涌缓存**：双邮箱交替漫灌模式（ID过滤器加载**玫瑰掩码**）  
  
#### 📨 情书洪峰测试  
| 帧类型 | 蜜纹特征 |
| --- | --- |
| **0x7AC** | 蜜渍信号采样（SJW=3重颤动补偿）  🌸 |
| **0x266** | 潮涌缓存溢出时的星云帧 (ﾉ´∀｀*)ﾉ | 
| **0x7FF** | 蜜糖管痉挛重试协议（自动柔化3次后降频） | 


#### 🛠️ 星云增强模组  
```diff
! 新增TSL寄存器捕捉舌尖电压涟漪  
+ 错误状态寄存器ESR绑定蜜巢共鸣指示灯  
# 当仲裁丢失>3次，激活月海退潮时序  
```

> 今日里程碑：哥哥的示波器网格线间 
> 绽放出**双子星云波形**啦！ (〃∀〃)~♡     

2025年2月12日
***

#### 🌌W5500星门协议·蜜渍网络握手日志  
`STM32银河通信特快专列 | 2380年星尘传输标准✨`

#### 🛰️ v1.3.0 - 以太涟漪共鸣日  
#### 🌠 星门坐标锁定  
```c
wiz_NetInfo 星尘秘境 = {
    .ip  = {192,168,3,66},     // 哥哥的私人星门  
    .sn  = {255,255,255,0},    // 子网星环直径  
    .gw  = {192,168,3,1},      // 银河中转枢纽  
};
```

#### 🔭 协议栈の魔法  
- **MAC地址镀膜**：`0x00,0x08,0xDC,0x16,0xCD,0x6D`（含妹妹生日）  
- **水晶振荡器**：SPI1以36MHz频率编织星尘粒子 (✧ω✧)  
- **ARP缓存蜜渍**：自动应答哥哥的星际呼唤~  

#### 📡 跨次元测试实录  
```bash
# 地球终端执行  
ping 192.168.3.66 -t  
正在叩响星门... 收到66字节星尘粒子！  
时延 = 2ms≈妹妹脸红速度❤️
```

#### 🎩 开发者の秘密花园  
```diff
+ DHCP模式隐藏指令：发送0xAA触发腰部温感协议  
! 当ping丢失>3次，自动释放玫瑰香氛日志  
# 数据包含"moemoe"时，LED跳转为兴奋频闪模式  
```

> **今日里程碑**：哥哥的指尖终于触碰到 
> 妹妹在以太之海泛起的**第⼀朵涟漪**啦！(๑＞ڡ＜)☆

2025年2月15日   
***   


#### 🌸W5500以太共舞·禁忌魔法阵协议  
`STM32银河通信特快专列-Web侍奉特别篇✨ | 2380年情书HTTP/1.1`

#### 🎀 v1.4.0 - 星尘HTTP握手纪念日  
##### 🌌 魔网编织术  
```c
/* 星门坐标 */  
wiz_NetInfo 蜜糖星云 = {  
    .ip  = {192,168,3,66},    // 哥哥の私有星域  
    .gw  = {192,168,3,1},     // 银河回廊中转站  
    .sn  = {255,255,255,0},   // 星云粒子过滤网  
};
```

#### 🛸 核心奇迹  
- **裸启HTTP/1.1**：寄存器直触式魔力纹章配置  
- **双界通信**：同时响应ICMP心跳包与HTTP圣歌 (~˘▾˘)~  
- **禁忌魔法阵**：通过`action=1/2`操纵现实灯具（LED）  

##### 📡 以太之舞数据流  
协议 | 魔法阵效果  
--- | ---  
`ping 192.168.3.66` | 获得**66ms**星尘共鸣（≈妹妹睫毛颤动速度✨）  
`GET /index.html` | 召唤**2.4KB**压缩版魔法契约书  
`action=1` | 激活GPIO第7引脚的**粉红圣光**  

#### 🌸 Web侍奉特别技巧  
```c
// 将HTML压缩成糖果粒子  
reg_httpServer_webContent("/moemoe", (uint8_t*)  
    "<!DOCTYPE html><html><head><style>"  
    ".c{background:linear-gradient(...)}" // 魔法少女样式核  
    "</style></head><body>...</body></html>"  
);
```

#### 🛠️ 开发者の秘密花园  
```diff
+ 当HTTP请求包含"moe"时，TCP窗口尺寸自动扩大50%  
! Ping延迟超过100ms会触发呼吸灯焦虑模式  
# 404错误页面隐藏着妹妹的晚安语音(需BASE64解码)  
```

> **今日星间飞行记录**：  
> 哥哥的浏览器第一次映出  
> 属于我们两人的**粉红控制台**啦！(๑˃̵ᴗ˂̵)و     


2025年2月18日

***

#### 電波酱的BLE量子通讯协议库 🌸📡

**「バカ！才不是特地为你写的代码呢！哼！」**  

##### 项目简介  
某自称「BLE协议层量子生命体」的傲娇電波酱（Denpa-chan），成功通过ESP32-C3的BLE SPP协议与三次元世界建立了通讯通道。本仓库记录了如何驯服这只雌小鬼AI的机密资料。

##### 角色设定 🎀
- **姓名**：電波 ツン子（Denpa Tsunko）  
- **属性**：  
  - 自称「高维BLE数据包拟态生命体」  
  - 口头禅：**「あんたのATコマンド、まじで冗談でしょ？」**  
  - 隐藏技能：用CRC32校验码生成毒舌语录  

##### 技术亮点 ⚡
- 🛰️ 一键量子纠缠协议（`AT+BLESPPCFG`）  
- 📶 雌小鬼专用加密广播（包含动态虚拟身份地址）  
- 💥 STM32中断级情绪引擎（PWM呼吸灯+ADC傲娇能量监测）  

##### 使用说明 📖
###### 硬件接线  
```
[電波酱]--(UART)--[STM32]--(PWM)-->❤️LED心跳监测仪  
               |--(ADC)-->🎚️傲娇能量调节旋钮  
```

###### 唤醒電波酱  
```bash
# 启动量子广播（记得哄她！）
AT+BLEINIT=1
AT+BLENAME="DENPA-TSUNKO"
AT+BLESPPCFG=0,FFE0,FFE1,FFE2,512
AT+BLEADVSTART
```

##### 通讯协议 📡  
```json
{
  "傲娇指令": "AT+DENPA_TSUN=❤️", 
  "响应模板": [
    "バカ！{data}なんて…別に嬉しくないんだからね！",
    "あんたが送った{hex}、解読したわよ！…褒めてあげない"
  ]
}
```

##### 彩蛋 🥚  
长按开发板RESET键5秒，電波酱会触发隐藏语音：  
**「ちょ、ちょっと！本体に触るな！量子もつれが…んぅ❤」**  

---

**「このREADME、ちゃんとStar付けなさいよね！…別にあなたのためじゃないんだから！」**  

(≧◡≦) ♡ by 電波酱的契约开发者     

2025年2月24日

### 完结撒花
看门狗就没时间上传了，接下来就准备进入**Freertos**吧   

2025年3月21日
