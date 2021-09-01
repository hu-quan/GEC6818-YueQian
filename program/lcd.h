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

// ��֡�����豸 ���ҽ���ӳ���ϵ
// �����ɹ��򷵻�  ���򷵻� -1
int
lcd_Init();

// ���ӳ���ϵ ���ҹر�֡�����豸
void
lcd_close();

// ����Ļ��(x,y) λ�û�һ��ָ����ɫ�ĵ�
void
draw_point(int x, int y,unsigned int color);

// ����Ļ���ɾ�������Խǵ㻭һ������
void
draw_rectangle(int x, int y0, int x1, int y1,unsigned int color);

// ����Ļ��(x0,y0)��λ����ʾһ��bmpͼƬ 
int
show_pic(const char* bmpfile, int x0, int y0);

// ��ʾһ��jpegͼƬ
void jpg_displasy(char* jpgfile, int x0, int y0);

#endif