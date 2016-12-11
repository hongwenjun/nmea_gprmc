#ifndef GPRMC_H_INCLUDED
#define GPRMC_H_INCLUDED

#include <stdio.h>      // 定义输入／输出函数
#include <ctype.h>      // 字符处理
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
//        由于$GPRMC比较重要，所以重点讲解：
//        $GPRMC(Recommended Minimum Specific GPS/TRANSIT Data)
//
//        帧头    UTC时间    状态   纬度  北纬/南纬   经度  东经/西经   速度
//        $GPRMC  hhmmss.sss  A/V   ddmm.mmmm   N/S   dddmm.mmmm  E/W    节
//
//        方位角   UTC日期   磁偏角     磁偏角方向 模式      校验   回车换行
//          度     ddmmyy   000 - 180    E/W       A/D/E/N   *hh     CR+LF
//
//        格 式： $GPRMC,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>*hh<CR><LF>
//        $GPRMC,024813.640,A,3158.4608,N,11848.3737,E,10.05,324.27,150706,,,A*50
//
//        $GPRMC,175622,A,2921.219000,N,11946.287000,E,13.00,348.27,20161006,,,D*4E
//
//        说 明：
//        字段 0：$GPRMC，语句ID，表明该语句为Recommended Minimum Specific GPS/TRANSIT Data（RMC）推荐最小定位信息
//          字段 1：UTC时间，hhmmss.sss格式
//          字段 2：状态，A=定位，V=未定位
//          字段 3：纬度ddmm.mmmm，度分格式（前导位数不足则补0）
//          字段 4：纬度N（北纬）或S（南纬）
//          字段 5：经度dddmm.mmmm，度分格式（前导位数不足则补0）
//          字段 6：经度E（东经）或W（西经）
//          字段 7：速度，节，Knots（一节也是1.852千米／小时）
//          字段 8：方位角，度（二维方向指向，相当于二维罗盘）
//          字段 9：UTC日期，DDMMYY格式
//          字段10：磁偏角，（000 - 180）度（前导位数不足则补0）
//          字段11：磁偏角方向，E=东，W=西
//          字段12：模式，A=自动，D=差分，E=估测，N=数据无效（3.0协议内容）
//          字段13：校验值


// NMEA Decoding here
// Wait for gps data, want RMC sentence:
//$GPRMC,230046,A,3759.8006,N,12205.4429,W,0.0,190.3,260702,15.1,E,A*3C
//              |     |    /     |      /   |   |
//$GPRMC,233834,A,3759.842,N,12205.440,W,000.0,173.7,200602,015.8,E*63
//              |    |     |    |      |   |     |             |     |--checksum
//              |    |     |    |      |   |     |             |- Magnetic Deviation?
//              |    |     |    |      |   |     |- course over ground
//              |    |     |    |      |   |- speed over ground
//              |    |     |    |      |--Lon E/W
//              |    |     |    |-- Lon 122' 5.44"
//              |    |     |-- Lat N/S
//              |    |-- Lat 37' 59.842"
//              |-- A=Good, V=Bad

*/


typedef struct {
    double  rcv_time;
    char    status;
    double  lat;
    char    lat_direct;
    double  lon;
    char    lon_direct;
    double  speed;
    double  cog;
    int     date;
    double  mag_variation;
    char    mag_var_direct;
    char    mode;
    int     chksum;
} gprmc_format;


// 计算校验:异或
int checksum(const char* s);
// 打印错误信息
int print_error(int err);


// 读取一行GPRMC数据，判断是否是GPRMC数据行
bool read_gprmc(const char* line, gprmc_format& rmc);

// 打印 GPS坐标速度时间戳
void print_gps_point(FILE* outfile, gprmc_format gps_point, int code );

// 重新生成 GPRMC 数据行, 校验值会变化
void fprint_gprmc(FILE* outfile, gprmc_format rmc);

double degree_minute2dec_degrees(double deg);

// c_string 字符串替换
char* cs_replace(char* cs, const char* str1, const char* str2);
// c_string 多重字符串替换
char* multi_replace(char* cs, const char* str1, const char* str2);

// gps_txt 转 gpx格式
int gps_txt2gpx(FILE* input, FILE* outfile);

// 是否打印调试数据
// #define DEBUG


#endif // GPRMC_H_INCLUDED
