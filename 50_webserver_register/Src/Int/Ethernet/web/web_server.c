#include "web_server.h"

/********ȫ�ֶ�����Ҫ�Ĳ���**********/
uint8_t tx_buf[2048];
uint8_t rx_buf[2048];
uint8_t cnt = 1;                //��Ҫ�򿪵�socket��
uint8_t socketlist[1] = { 0 };  // �򿪵�socket�б�

uint8_t* connectName = "index.html";

/* ��Ӧ����ҳ������ */
// uint8_t content[2048] = "<!doctype html>\n"
// "<html lang=\"en\">\n"
// "<head>\n"
// "    <meta charset=\"GBK\">\n"
// "    <meta name=\"viewport\"\n"
// "          content=\"width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0\">\n"
// "    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n"
// "    <title>�й��Ƕ��ʽ�γ�</title>\n"
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
// "<a href=\"/index.html?action=1\"><button id=\"open_red\" >����</button></a>\n"
// "<a href=\"/index.html?action=2\"><button id=\"close_red\" >�ص�</button></a>\n"
// "</body>\n"
// "</html>";
// uint8_t content[2048] =
// "<!DOCTYPE html>\n"
// "<html><head><meta charset=GBK><title>ħ������</title>\n"//ѹ������
// "<style>\n"
// "body{background:#ffe6f0;font-family:sans-serif;margin:0;height:100vh;display:flex;justify-content:center;align-items:center}\n"
// ".c{background:linear-gradient(45deg,#ffb3d9,#ff80bf);padding:2rem;border-radius:1.5rem;box-shadow:0 8px 16px rgba(255,128,191,0.3)}\n"
// "h1{color:#fff;text-shadow:2px 2px #ff66b2;text-align:center;margin:0 0 1.5rem 0}\n"
// ".b{display:flex;gap:1rem}\n"
// "a{background:#fff;padding:0.8rem 1.5rem;border-radius:0.8rem;color:#ff66b2;text-decoration:none;transition:0.3s}\n"
// "a:hover{transform:translateY(-3px);box-shadow:0 5px 15px rgba(255,102,178,0.4)}\n"
// "</style></head>\n" //����ѹ����CSS
// "<body>\n"
// "<div class=c>\n"
// "<h1>ħ����յ����</h1>\n"
// "<div class=b>\n"
// "<a href='/index.html?action=1' onmouseover='this.innerHTML=\"���� ʥ��\"' onmouseout='this.innerHTML=\"����\"'>����</a>\n"
// "<a href='/index.html?action=2' onmouseover='this.innerHTML=\"��ӡ ��Ӱ\"' onmouseout='this.innerHTML=\"�ص�\"'>�ص�</a>\n" //������ʾѹ��
// "</div></div></body></html>\n";
uint8_t content[4096] =
"<!DOCTYPE html>\n"
"<html lang=\"zh\">\n"
"<head>\n"
"    <meta charset=\"GBK\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0\">\n"
"    <title>??�������ܿ���̨??</title>\n"
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
"        <h1>??ħ��������������??</h1>\n"
"        <div class=\"btn-box\">\n"
"            <a href=\"/index.html?action=1\" class=\"moe-btn\" \n"
"               onmouseover=\"this.innerHTML='����??����ħ����';\" \n"
"               onmouseout=\"this.innerHTML='����';\">\n"
"               ����\n"
"            </a>\n"
"            <a href=\"/index.html?action=2\" class=\"moe-btn\"\n"
"               onmouseover=\"this.innerHTML='��ӡ??��Ԩ֮��';\"\n"
"               onmouseout=\"this.innerHTML='�ص�';\">\n"
"               �ص�\n"
"            </a>\n"
"        </div>\n"
"    </div>\n"
"    \n"
"    <!-- Ư����Ч -->\n"
"    <div class=\"floating-heart\" style=\"left:10%;top:20%\">?</div>\n"
"    <div class=\"floating-heart\" style=\"left:80%;top:30%\">?</div>\n"
"    <div class=\"floating-heart\" style=\"left:50%;top:80%\">?</div>\n"
"</body>\n"
"</html>";
void WebServer_Init()
{
    //http��������ʼ��
    httpServer_init(tx_buf, rx_buf, cnt, socketlist);

    //ע��http������Ҫ��Ӧ���ص�����
    reg_httpServer_webContent(connectName, content);

}

void WebServer_Start()
{
    while (1)
    {
        httpServer_run(0);

    }

}

//�û��Զ��庯��������uri�н������Ĳ���ִ�п��ص�
void httpServer_Handle(uint8_t* uri)
{
    //�������action=1���ǾͿ���
    if (strstr((char*)uri, "action=1"))
        Int_LED_On(LED1);

    else if (strstr((char*)uri, "action=2"))
        Int_LED_Off(LED1);

    else
        printf("wrong!\n");

}

