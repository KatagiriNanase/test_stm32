#include "web_server.h"

/********全局定义需要的参数**********/
uint8_t tx_buf[2048];
uint8_t rx_buf[2048];
uint8_t cnt = 1;                //需要打开的socket数
uint8_t socketlist[1] = { 0 };  // 打开的socket列表

uint8_t* connectName = "index.html";

/* 响应的网页的内容 */
// uint8_t content[2048] = "<!doctype html>\n"
// "<html lang=\"en\">\n"
// "<head>\n"
// "    <meta charset=\"GBK\">\n"
// "    <meta name=\"viewport\"\n"
// "          content=\"width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0\">\n"
// "    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n"
// "    <title>尚硅谷嵌入式课程</title>\n"
// "\n"
// "    <style type=\"text/css\">\n"
// "        #open_red{\n"
// "            color: red;\n"
// "            width: 100px;\n"
// "            height: 40px;\n"
// "\n"
// "\n"
// "        }\n"
// "        #close_red{\n"
// "            color: black;\n"
// "            width: 100px;\n"
// "            height: 40px;\n"
// "        }\n"
// "    </style>\n"
// "</head>\n"
// "<body>\n"
// "<a href=\"/index.html?action=1\"><button id=\"open_red\" >开灯</button></a>\n"
// "<a href=\"/index.html?action=2\"><button id=\"close_red\" >关灯</button></a>\n"
// "</body>\n"
// "</html>";
// uint8_t content[2048] =
// "<!DOCTYPE html>\n"
// "<html><head><meta charset=GBK><title>魔法管制</title>\n"//压缩标题
// "<style>\n"
// "body{background:#ffe6f0;font-family:sans-serif;margin:0;height:100vh;display:flex;justify-content:center;align-items:center}\n"
// ".c{background:linear-gradient(45deg,#ffb3d9,#ff80bf);padding:2rem;border-radius:1.5rem;box-shadow:0 8px 16px rgba(255,128,191,0.3)}\n"
// "h1{color:#fff;text-shadow:2px 2px #ff66b2;text-align:center;margin:0 0 1.5rem 0}\n"
// ".b{display:flex;gap:1rem}\n"
// "a{background:#fff;padding:0.8rem 1.5rem;border-radius:0.8rem;color:#ff66b2;text-decoration:none;transition:0.3s}\n"
// "a:hover{transform:translateY(-3px);box-shadow:0 5px 15px rgba(255,102,178,0.4)}\n"
// "</style></head>\n" //极致压缩的CSS
// "<body>\n"
// "<div class=c>\n"
// "<h1>魔法灯盏控制</h1>\n"
// "<div class=b>\n"
// "<a href='/index.html?action=1' onmouseover='this.innerHTML=\"启动 圣光\"' onmouseout='this.innerHTML=\"开灯\"'>开灯</a>\n"
// "<a href='/index.html?action=2' onmouseover='this.innerHTML=\"封印 暗影\"' onmouseout='this.innerHTML=\"关灯\"'>关灯</a>\n" //悬浮提示压缩
// "</div></div></body></html>\n";
uint8_t content[4096] =
"<!DOCTYPE html>\n"
"<html lang=\"zh\">\n"
"<head>\n"
"    <meta charset=\"GBK\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0\">\n"
"    <title>??哥哥的秘密控制台??</title>\n"
"    \n"
"    <style>\n"
"        body {\n"
"            background: url('https://i.imgur.com/3ZqX9Jl.jpg') no-repeat center fixed;\n"
"            background-size: cover;\n"
"            font-family: 'Comic Neue', cursive;\n"
"        }\n"
"        .moe-container {\n"
"            background: rgba(255, 240, 245, 0.9);\n"
"            width: 300px;\n"
"            margin: 15% auto;\n"
"            padding: 30px;\n"
"            border-radius: 20px;\n"
"            box-shadow: 0 0 20px rgba(255, 182, 193, 0.6);\n"
"            border: 3px solid #ff69b4;\n"
"        }\n"
"        h1 {\n"
"            color: #ff1493;\n"
"            text-align: center;\n"
"            text-shadow: 2px 2px #fff;\n"
"            font-size: 28px;\n"
"            margin-bottom: 30px;\n"
"            position: relative;\n"
"        }\n"
"        h1:after {\n"
"            content: '?';\n"
"            position: absolute;\n"
"            right: -30px;\n"
"            animation: sparkle 1s infinite;\n"
"        }\n"
"        .btn-box {\n"
"            display: flex;\n"
"            justify-content: space-around;\n"
"        }\n"
"        .moe-btn {\n"
"            background: linear-gradient(45deg, #ff99cc, #ff66b2);\n"
"            border: none;\n"
"            padding: 15px 25px;\n"
"            border-radius: 15px;\n"
"            color: white !important;\n"
"            font-size: 18px;\n"
"            cursor: pointer;\n"
"            transition: all 0.3s;\n"
"            box-shadow: 0 5px #ff3399;\n"
"            text-decoration: none;\n"
"        }\n"
"        .moe-btn:hover {\n"
"            transform: translateY(-3px);\n"
"            box-shadow: 0 8px #ff0066;\n"
"            background: linear-gradient(45deg, #ff66b2, #ff3399);\n"
"        }\n"
"        .moe-btn:active {\n"
"            transform: scale(0.95);\n"
"        }\n"
"        @keyframes sparkle {\n"
"            0% { opacity: 0; }\n"
"            50% { opacity: 1; }\n"
"            100% { opacity: 0; }\n"
"        }\n"
"        .floating-heart {\n"
"            position: fixed;\n"
"            animation: float 3s infinite;\n"
"            opacity: 0.6;\n"
"        }\n"
"        @keyframes float {\n"
"            0% { transform: translateY(0); }\n"
"            50% { transform: translateY(-20px); }\n"
"            100% { transform: translateY(0); }\n"
"        }\n"
"    </style>\n"
"    <link href=\"https://fonts.googleapis.com/css2?family=Comic+Neue:wght@700&amp;display=swap\" rel=\"stylesheet\">\n"
"</head>\n"
"<body>\n"
"    <div class=\"moe-container\">\n"
"        <h1>??魔界照明管制中心??</h1>\n"
"        <div class=\"btn-box\">\n"
"            <a href=\"/index.html?action=1\" class=\"moe-btn\" \n"
"               onmouseover=\"this.innerHTML='开启??禁忌魔法阵';\" \n"
"               onmouseout=\"this.innerHTML='开灯';\">\n"
"               开灯\n"
"            </a>\n"
"            <a href=\"/index.html?action=2\" class=\"moe-btn\"\n"
"               onmouseover=\"this.innerHTML='封印??深渊之门';\"\n"
"               onmouseout=\"this.innerHTML='关灯';\">\n"
"               关灯\n"
"            </a>\n"
"        </div>\n"
"    </div>\n"
"    \n"
"    <!-- 漂浮特效 -->\n"
"    <div class=\"floating-heart\" style=\"left:10%;top:20%\">?</div>\n"
"    <div class=\"floating-heart\" style=\"left:80%;top:30%\">?</div>\n"
"    <div class=\"floating-heart\" style=\"left:50%;top:80%\">?</div>\n"
"</body>\n"
"</html>";
void WebServer_Init()
{
    //http服务器初始化
    httpServer_init(tx_buf, rx_buf, cnt, socketlist);

    //注册http服务器要响应返回的内容
    reg_httpServer_webContent(connectName, content);

}

void WebServer_Start()
{
    while (1)
    {
        httpServer_run(0);

    }

}

//用户自定义函数，根据uri中解析出的参数执行开关灯
void httpServer_Handle(uint8_t* uri)
{
    //如果存在action=1，那就开灯
    if (strstr((char*)uri, "action=1"))
        Int_LED_On(LED1);

    else if (strstr((char*)uri, "action=2"))
        Int_LED_Off(LED1);

    else
        printf("wrong!\n");

}

