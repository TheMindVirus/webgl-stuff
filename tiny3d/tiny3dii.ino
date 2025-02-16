 #include <Ethernet.h>

#define Server_localIP() Ethernet.localIP()
#define Server_localPort() 80 //DNS?
#define Server_remoteIP() Client.remoteIP()
#define Server_remotePort() Client.localPort()

#define Server_Idle            0
#define Server_RenewError      1
#define Server_RenewSuccess    2
#define Server_RebindError     3
#define Server_RebindSuccess   4
#define Server_InitSuccess     5

int status = Server_Idle;
byte MAC[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress IP = { 192, 168, 1, 177 }; //DHCP?
EthernetServer Server(Server_localPort());
//EthernetClient Client();
bool BlankLine = true;
char TempChar = '\0';
bool OneShot = true;

const char Server_Data[] PROGMEM = 
"<!DOCTYPE html>\r\n\
<html>\r\n\
<head>\r\n\
<title>tiny3dii</title>\r\n\
<script>\r\n\
RX=0;RY=0;RZ=0;X=[];Y=[];Z=1000;DX=[];DY=[];DZ=[];\r\n\
RA=[];RB=[];II=0;Q1=[];Q2=[];Q3=[];Q4=[];\r\n\
w=0;h=0;hw=0;hh=0;th=0;tbh=76;\r\n\
o=2;n=12;ii=1/n;t=0.01;\r\n\
ox=0;oy=0;oz=0;s=100;\r\n\
var play=function(element)\r\n\
{\r\n\
alert(\"hello\");\r\n\
element.style.display=\"none\";\r\n\
setup();\r\n\
}\r\n\
var setup=function()\r\n\
{\r\n\
canvas=document.getElementById(\"canvas\");\r\n\
ctx=canvas.getContext(\"2d\");\r\n\
var style=window.getComputedStyle(canvas);\r\n\
w=canvas.width=parseFloat(style.width);\r\n\
h=canvas.height=parseFloat(style.height);\r\n\
hw=w/2;hh=h/2;th=h-tbh;\r\n\
setInterval(loop,0);\r\n\
}\r\n\
var loop=function()\r\n\
{\r\n\
clear();\r\n\
reset();\r\n\
rotate();\r\n\
draw();\r\n\
}\r\n\
var clear=function()\r\n\
{\r\n\
X=[];Y=[];\r\n\
DX=[];DY=[];DZ=[];\r\n\
RA=[];RB=[];\r\n\
Q1=[];Q2=[];Q3=[];Q4=[];\r\n\
canvas.width=canvas.width;\r\n\
ctx.fillStyle=\"#000000\";\r\n\
ctx.fillRect(0,0,w,h);\r\n\
ctx.lineWidth=0.6;\r\n\
ctx.strokeStyle=\"#00FFFF\";\r\n\
ctx.shadowBlur=6;\r\n\
ctx.shadowColor=\"#00FFFF\";\r\n\
ctx.lineCap=\"round\";\r\n\
ctx.lineJoin=\"round\";\r\n\
ctx.beginPath();\r\n\
ctx.moveTo(0,0);\r\n\
ctx.lineTo(w,h);\r\n\
ctx.stroke();\r\n\
ctx.beginPath();\r\n\
ctx.moveTo(0,0);\r\n\
ctx.lineTo(w,th);\r\n\
ctx.stroke();\r\n\
}\r\n\
var reset=function()\r\n\
{\r\n\
point(ox-s,oy+s,oz+s);\r\n\
point(ox+s,oy+s,oz+s);\r\n\
point(ox+s,oy+s,oz-s);\r\n\
point(ox-s,oy+s,oz-s);\r\n\
point(ox-s,oy-s,oz+s);\r\n\
point(ox+s,oy-s,oz+s);\r\n\
point(ox+s,oy-s,oz-s);\r\n\
point(ox-s,oy-s,oz-s);\r\n\
line(0,1);line(1,2);line(2,3);line(3,0);\r\n\
line(4,5);line(5,6);line(6,7);line(7,4);\r\n\
line(0,4);line(5,1);line(2,6);line(7,3);\r\n\
}\r\n\
var point=function(x,y,z)\r\n\
{\r\n\
DX.push(x);DY.push(y);DZ.push(z);\r\n\
}\r\n\
var line=function(a,b)\r\n\
{\r\n\
RA.push(a);RB.push(b);\r\n\
}\r\n\
var rotate=function()\r\n\
{\r\n\
var rx=RY/-100;\r\n\
var ry=RX/-100;\r\n\
var rz=RZ/-100;\r\n\
var A=Math.sin(rx);\r\n\
var B=Math.sin(ry);\r\n\
var C=Math.sin(rz);\r\n\
var D=Math.cos(rx);\r\n\
var E=Math.cos(ry);\r\n\
var F=Math.cos(rz);\r\n\
for(var i=0;i<DX.length;++i)\r\n\
{\r\n\
var x=DX[i];\r\n\
var y=DY[i];\r\n\
var z=DZ[i];\r\n\
var R=(A*y)+(D*z);\r\n\
var S=(D*y)-(A*z);\r\n\
var T=(E*x)+(B*R);\r\n\
var nx=(F*T)-(C*S);\r\n\
var ny=(C*T)+(F*S);\r\n\
var nz=(E*R)-(B*x);\r\n\
X[i]=((nx/(nz+Z))*Z)+hw;\r\n\
Y[i]=((ny/(nz+Z))*Z)+hh;\r\n\
}\r\n\
}\r\n\
var draw=function()\r\n\
{\r\n\
for(var k=0;k<RA.length;++k)\r\n\
{\r\n\
ctx.beginPath();\r\n\
ctx.moveTo(X[RA[k]],Y[RA[k]]);\r\n\
ctx.lineTo(X[RB[k]],Y[RB[k]]);\r\n\
ctx.closePath();\r\n\
ctx.stroke();\r\n\
}\r\n\
}\r\n\
var mouse=function(event)\r\n\
{\r\n\
RX=event.x;RY=event.y;\r\n\
}\r\n\
</script>\r\n\
<style>\r\n\
*{box-sizing:border-box;margin:auto;font-family:calibri;}\r\n\
body{background:#0000AA;text-align:center;}\r\n\
button{background:#0000AA;color:#FFFFFF;font-size:150pt;border:none;user-select:none;}\r\n\
[fullscreen]{position:fixed;top:0;left:0;width:100%;height:100%;z-index:9999;}\r\n\
</style>\r\n\
</head>\r\n\
<body>\r\n\
<canvas fullscreen id=\"canvas\" onmousemove=\"mouse(event);\"></canvas>\r\n\
<button fullscreen onclick=\"play(this);\">Wii</button>\r\n\
</body>\r\n\
</html>";

const size_t Server_DataLength = sizeof(Server_Data);

char* Server_Headers()
{
    char buffer[255] = "\0"; //Null Terminators required only here for strcat
    char* headers = "\0";
    strcat(headers, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ");
    itoa(Server_DataLength, buffer, 10);
    strcat(headers, buffer);
    strcat(headers, "\r\n\r\n");
    return headers;
}

void setup()
{
    Serial.begin(115200);
    Serial.print("[INFO]: ");
    Serial.println("tiny3dii");
    //Serial.println(Server_ResponseText());
    //Serial.println("[CKPT]");
    //Ethernet.begin(MAC, IP);
    Ethernet.begin(MAC);
    Server.begin();
    OneShot = true;
}

void loop()
{
    status = Ethernet.maintain() + (OneShot ? Server_InitSuccess : 0);
    switch (status)
    {
        case (Server_InitSuccess): OneShot = false;
        case (Server_RenewSuccess):
        case (Server_RebindSuccess):
        {
            Serial.print("[INFO]: ");
            Serial.print("Server: ");
            Serial.print(Server_localIP());
            Serial.print(":");
            Serial.println(Server_localPort());
        }
        break;
        case (Server_RenewError):
        case (Server_RebindError):
        {
            Serial.print("[WARN]: ");
            Serial.print("Server: ");
            Serial.println("Error");
        }
        break;
        case (Server_Idle):
        default:
        {
            //Serial.println(status);
        }
        break;
    }
    
    EthernetClient Client = Server.available();
    if (Client)
    {
        BlankLine = true;
        Serial.print("[INFO]: ");
        Serial.print("Client: ");
        Serial.print(Server_remoteIP());
        Serial.print(":");
        Serial.println(Server_remotePort());
        while (Client.connected())
        {
            if (Client.available())
            {
                TempChar = Client.read();
                if ((TempChar == '\n') && (BlankLine))
                {
                    Client.print(Server_Headers());
                    for (size_t i = 0; i < Server_DataLength; ++i)
                    {
                        Client.print((char)pgm_read_byte(&(Server_Data[i])));
                    }
                    Client.print("\r\n\r\n");
                    break;
                }
                if (TempChar == '\n') { BlankLine = true; }
                else if (TempChar != '\r') { BlankLine = false; }
            }
        }
        //delay(10);
        Client.flush();
        Client.stop();
    }
}
