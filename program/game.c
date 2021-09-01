#include "game.h"
#include "lcd.h"

extern int fd_fb;//帧缓冲设备的文件描述符
extern int* plcd; //帧缓冲的首地址
extern int fd_touch; // 触摸屏设备的文件描述符

/* 点亮标记数组 flag[n] = 1 表示第n个顶点被点亮*/
int flag[MAXVEX] = { 0 };

/*错误提示数组 用于标识答错的点*/
int errorsign[MAXVEX] = { 0 };

/*正确提示数组 同于标识未正确回答的点*/
int rightsign[MAXVEX] = { 0 };

/*记录错误的个数*/
int errnum = 0;

/*标识游戏难度*/
int hard;

/*游戏说明*/
int sign_index = 1;

// 初始化各顶点信息
Game*
InitGameVex(void)
{
    Game* g = NULL;
    g = malloc(sizeof(Game));
    if (g == NULL)
    {
        printf("g is NULL");
        return NULL;
    }
    g->game = NULL;
    g->game = malloc(sizeof(Vex) * 25);
    if (g->game == NULL)
    {
        printf("g->game is NULL");
        free(g);
        return NULL;
    }
    return g;
}

// 销毁游戏申请的内存
void
DestoryGame(Game* g)
{
    if (g == NULL)
        return;
    free(g->game);
    g->game = NULL;
    g = NULL;
}
// 初始化顶点坐标
void
InitVexPosition(Game* g)
{
    if (g == NULL)
        return;
    g->game[0].x = 72;
    g->game[0].y = 9;

    g->game[1].x = 258;
    g->game[1].y = 193;

    g->game[2].x = 200;
    g->game[2].y = 179;

    g->game[3].x = 356;
    g->game[3].y = 98;

    g->game[4].x = 330;
    g->game[4].y = 212;

    g->game[5].x = 251;
    g->game[5].y = 271;

    g->game[6].x = 270;
    g->game[6].y = 351;

    g->game[7].x = 200;
    g->game[7].y = 374;

    g->game[8].x = 445;
    g->game[8].y = 124;

    g->game[9].x = 400;
    g->game[9].y = 213;

    g->game[10].x = 402;
    g->game[10].y = 280;

    g->game[11].x = 375;
    g->game[11].y = 341;

    g->game[12].x = 311;
    g->game[12].y = 382;

    g->game[13].x = 270;
    g->game[13].y = 410;

    g->game[14].x = 485;
    g->game[14].y = 159;

    g->game[15].x = 471;
    g->game[15].y = 220;

    g->game[16].x = 515;
    g->game[16].y = 282;

    g->game[17].x = 438;
    g->game[17].y = 335;

    g->game[18].x = 500;
    g->game[18].y = 352;

    g->game[19].x = 375;
    g->game[19].y = 397;

    g->game[20].x = 425;
    g->game[20].y = 417;

    g->game[21].x = 578;
    g->game[21].y = 113;

    g->game[22].x = 560;
    g->game[22].y = 169;

    g->game[23].x = 612;
    g->game[23].y = 70;

    g->game[24].x = 650;
    g->game[24].y = 26;
}

int
LightVex(Game* g,unsigned int x,unsigned int y)
{
    if (g == NULL)
        return -1;
    int i;
            // 0
            if (x >= 70 && x <= 100 && y >= 0 && y <= 30)
            {
                i = 0;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x,g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }
            // 1
            if (x >= 260 && x <= 290 && y >= 155 && y <= 175)
            {
                i = 1;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 2
            if (x >= 205 && x <= 235 && y >= 140 && y <= 160)
            {
                i = 2;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 3
            if (x >= 355 && x <= 385 && y >= 85 && y <= 105)
            {
                i = 3;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 4
            if (x >= 335 && x <= 365 && y >= 165 && y <= 185)
            {
                i = 4;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 5
            if (x >= 255 && x <= 285 && y >= 215 && y <= 235)
            {
                i = 5;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 6
            if (x >= 275 && x <= 305 && y >= 270 && y <= 290)
            {
                i = 6;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 7
            if (x >= 205 && x <= 235 && y >= 290 && y <= 310)
            {
                i = 7;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 8
            if (x >= 450 && x <= 480 && y >= 100 && y <= 120)
            {
                i = 8;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 9
            if (x >= 410 && x <= 440 && y >= 170 && y <= 190)
            {
                i = 9;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 10
            if (x >= 410 && x <= 440 && y >= 220 && y <= 240)
            {
                i = 10;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }
            // 11
            if (x >= 380 && x <= 410 && y >= 270 && y <= 290)
            {
                i = 11;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 12
            if (x >= 325 && x <= 355 && y >= 300 && y <= 320)
            {
                i = 12;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 13
            if (x >= 275 && x <= 305 && y >= 310 && y <= 330)
            {
                i = 13;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 14
            if (x >= 495 && x <= 525 && y >= 130 && y <= 150)
            {
                i = 14;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 15
            if (x >= 480 && x <= 510 && y >= 170 && y <= 190)
            {
                i = 15;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 16
            if (x >= 525 && x <= 555 && y >= 215 && y <= 235)
            {
                i = 16;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 17
            if (x >= 450 && x <= 480 && y >= 265 && y <= 285)
            {
                i = 17;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 18
            if (x >= 510 && x <= 540 && y >= 270 && y <= 290)
            {
                i = 18;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 19
            if (x >= 385 && x <= 415 && y >= 300 && y <= 320)
            {
                i = 19;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 20
            if (x >= 430 && x <= 460 && y >= 325 && y <= 355)
            {
                i = 20;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 21
            if (x >= 585 && x <= 615 && y >= 95 && y <= 115)
            {
                i = 21;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }


            // 22
            if (x >= 565 && x <= 595 && y >= 135 && y <= 155)
            {
                i = 22;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 23
            if (x >= 610 && x <= 640 && y >= 60 && y <= 80)
            {
                i = 23;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }

            // 24
            if (x >= 655 && x <= 685 && y >= 25 && y <= 45)
            {
                i = 24;
                if (flag[i] == 0)
                {
                    show_pic("light.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 1;
                }
                else
                {
                    show_pic("off.bmp", g->game[i].x, g->game[i].y);
                    flag[i] = 0;
                }
            }
}

// game start
int
GameStart()
{
    // 初始化帧缓冲设备
    lcd_Init();
    fd_touch = open("/dev/input/event0", O_RDONLY);
    if (-1 == fd_touch)
    {
        //打开触摸屏设备失败
        perror("open fd_touch error");
        return -1;
    }

    // 初始化游戏主界面
    InitData();

    // 顶点存储结构初始化
    Game* g = NULL;
    g = InitGameVex();
    InitVexPosition(g);

    // 坐标相关的变量定义及初始化
    unsigned int x = 0;
    unsigned int y = 0;
    struct input_event ev;//定义一个结构体变量用来保存输入事件的值

    // 游戏相关的变量定义及初始化
    int level = 3;
    int isbegin = -1;             // 判断用户是否已经开始答题
    int isfailed = -1;            // 判断游戏是否已经失败
    int isclicksignbutton = -1;   // 判断是否点击游戏说明按钮
    int question[MAXVEX] = { 0 };
    int solution[MAXVEX] = { 0 };
    char buf[24];
    // begin
    while (1)
    {
        while (1)
        {
            read(fd_touch, &ev, sizeof(ev));
            if (ev.type == 3 && ev.code == 0)
            {
                x = ev.value * 800.0 / 1024;
            }
            if (ev.type == 3 && ev.code == 1)
            {
                y = ev.value * 480.0 / 800;
            }
            if (ev.type == 1 && ev.code == 330 && ev.value == 1)
            {
                read(fd_touch, &ev, sizeof(ev));
                if (ev.type == 3 && ev.code == 0)
                {
                    x = ev.value * 800.0 / 1024;
                }
                read(fd_touch, &ev, sizeof(ev));
                if (ev.type == 3 && ev.code == 0)
                {
                    x = ev.value * 800.0 / 1024;
                }
                printf("x = %d y = %d\n", x, y);
                // 答题未开始
                if (isbegin == -1)
                {
                    // 用户没有点击游戏说明按钮
                    if (isclicksignbutton == -1)
                    {
                        // 开始按钮 点击开始答题
                        if (x >= 665 && x <= 715 && y >= 245 && y <= 285)
                        {
                            isbegin = 1;
                            SetHard();
                            break;
                        }
                        // 说明按钮 点击进入游戏说明界面
                        else if (x >= 620 && x <= 800 && y >= 165 && y <= 210)
                        {
                            show_pic("gamesign1.bmp", 0, 0);
                            isclicksignbutton = 1;
                            sign_index = 1;
                        }
                        // 点击某点则点亮 或 熄灭该点
                        else
                        {
                            LightVex(g, x, y);
                        }
                    }
                    else
                    {
                        if (x >= 730 && x <= 790 && y >= 0 && y <= 50)
                        {
                            // 还原桌面
                            InitData();
                            isclicksignbutton = -1;
                        }
                        else
                        {
                            // 用户查看游戏说明
                            ShowGameSign(x, y);
                        }
                    }
                }
                // 检测答案是否正确
                else
                {
                    if (x >= 665 && x <= 750 && y >= 270 && y <= 320)
                    {
                        // 检测两个数组是否相等
                        show_pic("clear.bmp", 618, 120);
                        // 答对啦
                        if (IsEqual(question, flag, MAXVEX))
                        {
                            show_pic("right.bmp", 648, 120);
                        }
                        else
                        {
                            show_pic("errno.bmp", 648, 120);
                            for (int i = 0; i < errnum; i++)
                            {
                                // 用户少输
                                if(errorsign[i] == -1)
                                {
                                    show_pic("rightsign.bmp", g->game[rightsign[i]].x, g->game[rightsign[i]].y);
                                }
                                // 用户答错
                                if(rightsign[i] == -1)
                                {
                                    show_pic("errorsign.bmp", g->game[errorsign[i]].x, g->game[errorsign[i]].y);
                                }
                            }
                            isfailed = 1;
                        }
                        sleep(2);
                        level += 1;
                        break;
                    }
                    else
                    {
                        LightVex(g, x, y);
                    }
                }
            }// 获取坐标结束
        } // while(1)结束

        if (isfailed == -1)
        {
            // 答题开始
            /*一些初始化工作*/
            Mymemset(question, MAXVEX);
            Mymemset(solution, MAXVEX);
            show_pic("game.bmp", 0, 0);

            // 生成题目
            InitQuestion(question, solution, level);
            // 显示题目
            ShowChallengVex(g, solution, level);

            // 用户答题
           /* 一些初始化工作*/
            x = 0;
            y = 0;
            sprintf(buf, "%s%d%s", "answersign", level - 2, ".bmp\0");
            show_pic(buf, 628, 120);
            show_pic("submit.bmp", 648, 302);
            Mymemset(flag, MAXVEX);
        }
        else
        {
            break;
        }
    } // while(1)
    // 关闭触摸屏文件
    close(fd_touch);
    // 关闭帧缓冲设备
    lcd_close();
    // 销毁申请的空间
    DestoryGame(g);
}

/*  显示题目  */
void
ShowChallengVex(Game* g, int* arr, int level)
{
    if (g == NULL || arr == NULL)
        return;
    char buf[12];
    sprintf(buf, "%d%s", level - 2, ".bmp\0");
    show_pic(buf, 680, 120);
    for (int i = 0; i < level; i++)
    {
        show_pic("light.bmp", g->game[arr[i]].x, g->game[arr[i]].y);
        usleep(hard);
        show_pic("game.bmp", 0, 0);
    }
}

/*   
*  检测用户的答题情况 
*  如果回答正确返回 1 否则返回 0 并且errsign 和 rightsign会被设置 
*  src保存的是题目 dest保存的是用户的答案
*/
int
IsEqual(int* src, int *dest,int level)
{
    if (src == NULL || dest == NULL)
        return 0;
    Mymemset(errorsign, MAXVEX);
    Mymemset(rightsign, MAXVEX);
    int flag = -1;
    for (int i = 0; i < level; i++)
    {
        if (src[i] != dest[i])
        {
            // 用户答错
            if (!src[i])
            {
                errorsign[errnum] = i;
                rightsign[errnum] = -1;
            }
            // 用户漏答
            else
            {
                errorsign[errnum] = -1;
                rightsign[errnum] = i;
            }
            flag = 1;
            errnum++;
        }
    }

    if(flag == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


/*
*  初始化函数 把数组arr的前len个字节初始化为0
*/
void
Mymemset(int*arr, int len)
{
    if (arr == NULL || len <= 0)
        return;
    for(int i = 0; i < len; i++)
    {
        arr[i] = 0;
    }
}

/*根据用户点灯情况设置难度
* 点亮的灯越多游戏难度越高
*/
void
SetHard()
{
    int count = 0;
    hard = 0;
    for (int i = 0; i < MAXVEX; i++)
    {
        if (flag[i] == 1)
            count++;
    }
    hard = 1200000 - count * 40000;
}

/* 显示游戏说明 */
void
ShowGameSign(unsigned int x, unsigned int y)
{
    char buf[16] = { 0 };
    // 下一张图片
    if (x >= 665 && x <= 710 && y >= 290 && y <= 325)
    {
        sign_index++;
        if (sign_index > 5)
            sign_index = 5;
    }
    // 上一张图片
    else if (x >= 60 && x <= 120 && y >= 295 && y <= 340)
    {
        sign_index--;
        if (sign_index < 0)
            sign_index = 0;
    }
    sprintf(buf, "%s%d%s", "gamesign", sign_index, ".bmp\0");
    show_pic(buf, 0, 0);
}
/* 显示游戏主界面 */
void
InitData(void)
{
    show_pic("game.bmp", 0, 0);
    show_pic("startbutton.bmp", 648, 322);
    show_pic("gamesignbutton.bmp", 590, 200);
    show_pic("logo1.bmp", 180, 10);
    show_pic("logo2.bmp", 405, 30);
    Mymemset(flag, MAXVEX);
}
void
InitQuestion(int *question,int *solution,int level)
{
    srand(time(NULL));
    // 产生level个0 - 24 的不重复的随机数
    for (int j = 0; j < level; j++)
    {
        int flag = -1;
        int key = rand() % 25;
        for (int k = 0; k < j; k++)
        {
            if (solution[k] == key)
            {
                j--;
                flag = 1;
                break;
            }
        }
        if (flag == -1)
            solution[j] = key;
    }
    for (int i = 0; i < level; i++)
    {
        question[solution[i]] = 1;
    }
}