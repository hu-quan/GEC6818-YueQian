#include "lcd.h"

 int fd_fb = -1;//帧缓冲设备的文件描述符
 int* plcd = MAP_FAILED; //帧缓冲的首地址
 int fd_touch = -1; // 触摸屏设备的文件描述符

// 打开帧缓冲设备 并且建立映射关系
int
lcd_Init()
{
	// 打开帧缓冲设备
	fd_fb = open("/dev/fb0", O_RDWR);
	if (fd_fb == -1)
	{
		perror("open error:");
		return -1;
	}

	// 建立映射关系
	plcd = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
	if (plcd == MAP_FAILED)
	{
		perror("open mmap error");
		return -1;
	}

	return 0;
}

// 解除映射关系 并且关闭帧缓冲设备
void
lcd_close()
{
	// 解除映射关系
	munmap(plcd, 800 * 480 * 4);

	// 关闭帧缓冲设备
	close(fd_fb);
}

// 在屏幕上(x,y) 位置画一个指定颜色的点
void
draw_point(int x, int y, unsigned int color)
{
	if (x >= 0 && x <= 800 && y >= 0 && y <= 480)
	{
		*(plcd + y * 800 + x) = color;
	}
}

// 在屏幕上由矩阵的两对角点画一个矩阵
void
draw_rectangle(int x0, int y0, int x1, int y1,unsigned int color)
{
	if (x0 >= 0 && x0 <= 800 && y0 >= 0 && y0 <= 480 && x0 < x1 && y0 < y1)
	{
		for (int y = y0; y <= y1; y++)
		{
			for (int x = x0; x <= x1; x++)
			{
				draw_point(x, y, color);
			}
		}
	}
}

int
show_pic(const char* bmpfile, int x0, int y0)
{
    // 打开bmp文件
    int fd = open(bmpfile, O_RDONLY);
    if (fd == -1)
    {
        perror("open bmp error:");
        return -1;
    }

    int width, height;
    short depth;

    //  buf用于保存读取的四个字节的文件信息
    /*
    * 为什么要定义成unsigned 类型?
    * 因为读取到的四个字节还需要通过位操作还原成数据
    * 如果不是unsigned 类型位移时可能会出错
    */
    unsigned char buf[4];

    lseek(fd, 0x0012, SEEK_SET);
    read(fd, buf, 4);
    width = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | (buf[0]);

    lseek(fd, 0x0016, SEEK_SET);
    read(fd, buf, 4);
    height = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | (buf[0]);

    // 色深 即每个像素所占的bits位数
    lseek(fd, 0x001c, SEEK_SET);
    read(fd, buf, 2);
    depth = (buf[1] << 8) | (buf[0]);

    if (!(depth == 24 || depth == 32))
    {
        printf("Not Supported! GoodBye\n");
        close(fd);
        return -1;
    }

    //一次性把bmp文件中像素数组中所有数据全部读取出来
    int line_valid_bytes; // 一行有效数据量 
   // 一行中的"赖子"数量
    /*
    *  何为癞子? 每行像素个数必须是4的整数倍 否则会在行末添加几个癞子
    */
    int laizi = 0;
    int line_bytes;  // 一行总字节数
    int total_bytes; // 整个像素数组数据的字节数

    line_valid_bytes = abs(width) * (depth / 8);

    if (line_valid_bytes % 4)
    {
        laizi = 4 - line_valid_bytes % 4;
    }
    line_bytes = line_valid_bytes + laizi;

    total_bytes = line_bytes * abs(height);
    unsigned char* pixels = malloc(total_bytes);
    lseek(fd, 54, SEEK_SET);
    read(fd, pixels, total_bytes);

    //todo ...
    unsigned char a = 0, r, g, b;
    int color;
    int x1, y1;//像素点对应在显示屏上的坐标
    int i = 0;
    int x, y;

    for (y = 0; y < abs(height); y++)
    {
        for (x = 0; x < abs(width); x++)
        {
            b = pixels[i++];
            g = pixels[i++];
            r = pixels[i++];
            if (depth == 32)
            {
                a = pixels[i++];
            }
            color = (a << 24) | (r << 16) | (g << 8) | (b);

            x1 = (width > 0 ? (x0 + x) : (x0 + abs(width) - 1 - x));
            y1 = (height > 0 ? (y0 + abs(height) - 1 - y) : (y0 + y));

            draw_point(x1, y1, color);
        }
        i += laizi; //跳过“赖子”
    }

    free(pixels);
    close(fd);
    return 0;
}

void jpg_displasy(char* jpgfile, int x0, int y0)
{

    //(1) 分配并初始化一个Jpeg解压对象
    struct jpeg_decompress_struct dinfo;//定义一个jpeg decompress对象
    struct jpeg_error_mgr error; //定义一个出错对象

    //jpeg_std_error用来初始化一个“出错对象的”，返回一个出错对象
    dinfo.err = jpeg_std_error(&error);
    jpeg_create_decompress(&dinfo); //初始化dinfo对象

    //(2)指定要解压缩的数据的来源
    FILE* fp = fopen(jpgfile, "r");
    if (fp == NULL)
    {
    }
    jpeg_stdio_src(&dinfo, fp);

    //(3) 调用jpeg_read_header获取图像头信息
    jpeg_read_header(&dinfo, TRUE);


    //(4) 调用 jpeg_start_decompress启动解压过程
    jpeg_start_decompress(&dinfo);

    //(5)
    //在调用完 jpeg_start_decompress后，往往需要为解压后的扫描线上所有像素点分配空间
    //buf用来保存一行的解压后的数据!!
    unsigned char* buf = malloc(dinfo.output_width * dinfo.output_components);


    //(6) 读取一行或者多行扫描线上数据，处理的代码通常是这样子的

    while (dinfo.output_scanline < dinfo.output_height)
    {

        jpeg_read_scanlines(
            &dinfo, //解压对象
            &buf, //char**, 保存解压后数据的二级指针
            1  //读取多少行数据

        );
        // dinfo.output_scanlines + 1
        // 每一行解压后的数据的从左至右的像素点的   (A) R G B  ... buffer
        unsigned char a = 0, r, g, b;
        unsigned int color;
        int x;
        int i = 0;

        for (x = 0; x < dinfo.output_width; x++)
        {
            if (dinfo.output_components == 4)
            {
                a = buf[i++];
            }
            r = buf[i++];
            g = buf[i++];
            b = buf[i++];
            color = (a << 24) | (r << 16) | (g << 8) | (b);
            draw_point(x0 + x, y0 + dinfo.output_scanline -1, color);
        }

    }


    // (7) 调用jpeg_finish_decompress 完成解压过程

    jpeg_finish_decompress(&dinfo);

    //(8) 调用jpeg_destroy_decompress 释放jpeg解压对象及其他的空间

    jpeg_destroy_decompress(&dinfo);
    free(buf);
    fclose(fp);

    return;
}