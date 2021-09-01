#ifndef __LCD_H__
#define __LCD_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "jpeglib.h"

// 打开帧缓冲设备 并且建立映射关系
// 操作成功则返回  否则返回 -1
int
lcd_Init();

// 解除映射关系 并且关闭帧缓冲设备
void
lcd_close();

// 在屏幕上(x,y) 位置画一个指定颜色的点
void
draw_point(int x, int y,unsigned int color);

// 在屏幕上由矩阵的两对角点画一个矩阵
void
draw_rectangle(int x, int y0, int x1, int y1,unsigned int color);

// 在屏幕的(x0,y0)的位置显示一张bmp图片 
int
show_pic(const char* bmpfile, int x0, int y0);

// 显示一张jpeg图片
void jpg_displasy(char* jpgfile, int x0, int y0);

#endif