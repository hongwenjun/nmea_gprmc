#include <iostream>    // 数据流输入／输出
#include <string>      // 字符串类
#include <algorithm>   // STL 通用算法
#include <vector>      // STL 动态数组容器
#include <fstream>     //文件输入／输出
#include <cstdio>      // 定义输入／输出函数
#include <cctype>      // 字符处理
#include <cstring>

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

// 打印 GPS坐标速度时间戳
void print_gps_point(FILE* outfile, gprmc_format* gps_point);
double degree_minute2dec_degrees(double deg);

// c_string 字符串替换
char* cs_replace(char* cs, const char* str1, const char* str2);
// c_string 多重字符串替换
char* multi_replace(char* cs, const char* str1, const char* str2);

using namespace std;
int main(int argc, char* argv[])
{

    // 从数据读取一行
    const char* gpc = "$GPRMC,060947.00,A,2912.680607,N,11932.222854,E,002.3,288.3,231016,,,A*51";
    char line_buf[512] = {0} ;


    if (1 == argc) {

        printf("Usage: nmea_gprmc  %s\n", gpc);
        return 0;
    }


    if (2 == argc)
        strcpy(line_buf, argv[1]);   // 接受一个 参数输入数据


    gprmc_format rmc;

    int chksum = 0;
    char tempstr[512];
    char finalstr[512];

    if ('$' != line_buf[0]) {
        print_error(1);
        return -1;

    } else {

        char* pch = strrchr(line_buf, '*');
        if (pch != NULL) {
            *pch = '\0';
            pch++;
            rmc.chksum = strtol(pch, &pch, 16);
            // printf("%X\n", chksum);

            if (rmc.chksum != checksum(line_buf + 1)) {
                print_error(2);
                return -1;
            }
        } else {
            print_error(3);
            return -1;
        }


        if (strstr(line_buf, ",,"))
            multi_replace(line_buf, ",,", ",|,");

        pch = strtok(line_buf, ",");
        if ((pch != NULL) && !strcmp(pch, "$GPRMC")) {
            // printf("%s\n", pch);    //GPRMC

            pch = strtok(NULL, ",");
            rmc.rcv_time = atof(pch);

            pch = strtok(NULL, ",");
            rmc.status = *pch;

            pch = strtok(NULL, ",");
            rmc.lat = atof(pch);

            pch = strtok(NULL, ",");
            rmc.lat_direct  = *pch;

            pch = strtok(NULL, ",");
            rmc.lon = atof(pch);

            pch = strtok(NULL, ",");
            rmc.lon_direct = *pch;

            pch = strtok(NULL, ",");
            rmc.speed  = atof(pch);

            pch = strtok(NULL, ",");
            rmc.cog  = atof(pch);

            pch = strtok(NULL, ",");
            rmc.date  = atoi(pch);

            // 一般为空
            pch = strtok(NULL, ",");
            rmc.mag_variation   = 0;
            pch = strtok(NULL, ",");
            rmc.mag_var_direct  = 'W';

            pch = strtok(NULL, ",");
            rmc.mode =  *pch;

        } else {
            print_error(4);
            return -1;

        }



    }

    // 测试重新生成 GPRMC 数据，校验值会变化
    sprintf(tempstr, "%s,%0.2f,%c,%.6f,%c,%.6f,%c,%.2f,%03.1f,%06u,,,%c",
            "GPRMC",
            rmc.rcv_time,
            rmc.status,
            rmc.lat,
            rmc.lat_direct,
            rmc.lon,
            rmc.lon_direct,
            rmc.speed,
            rmc.cog,
            rmc.date,
            rmc.mode
           );

    //printf("%s\n", tempstr);
    chksum = checksum(tempstr);
    sprintf(finalstr, "$%s*%X", tempstr, chksum);
    printf("%s\n", finalstr);


    // 打印 GPS坐标速度时间戳
    fprintf(stdout, "纬度\t经度\t时速(Km/H)\t时间戳\n");
    print_gps_point(stdout, &rmc);

    return 0;
}


// 计算校验:异或
int checksum(const char* s)
{
    int c = 0;

    while (*s)
        c ^= *s++;

    return c;
}

// 打印错误信息
int print_error(int err)
{
    switch (err) {
    case 1:
        printf("行首不是 $ --> ");
        break;

    case 2:
        printf("校验值错误 --> ");
        break;

    case 3:
        printf("找不到校验值 --> ");
        break;

    case 4:
        printf("不是$GPRMC帧头--> ");
        break;

    default:
        printf("数据错误 --> ");
        break;
    }

    printf("请检查是否 NMEA 183 数据!\n");

    return err;
}



void print_gps_point(FILE* outfile, gprmc_format* gps_point)
{

    double lat = degree_minute2dec_degrees(gps_point->lat);
    double lon = degree_minute2dec_degrees(gps_point->lon);

    fprintf(outfile, "%.6f\t", lat);       // 纬度
    fprintf(outfile, "%.6f\t", lon);        // 经度
    fprintf(outfile, "%.1f\t", gps_point->speed * 1.852);     // 时速:节换算公里



//   strftime(time_str, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    char time_str [80] = "";
    int date = gps_point->date;
    int time = (int)gps_point->rcv_time;

    sprintf(time_str, "%d-%02d-%02d %02d:%02d:%02d",
            date / 10000, (date % 10000) / 100,  date % 100,
            time / 10000, (time % 10000) / 100,  time % 100);


    fprintf(outfile, "%s\n", time_str);


}


// 经纬度ddmm.mmmm，度分格式 转换成 10进制 度小数
double degree_minute2dec_degrees(double deg)
{
    deg = (deg / 100.0 - (int)deg / 100) * 100.0 / 60.0 + (int)deg / 100 ;
    return deg;
}


// c_string 字符串替换
char* cs_replace(char* cs, const char* str1, const char* str2)
{
    char* ret = cs;
    char* pc = new char[strlen(cs) + 1];

    char* pch = strstr(cs, str1); // 找到替换处
    if (pch == NULL)
        return pch;

    // 从目标出重新组合
    strcpy(pc, cs);     // 复制副本
    strcpy(pch, str2);
    strcat(pch + strlen(str2), pc + (pch - cs) + strlen(str1));

    delete[] pc;

    return ret;
}

// c_string 多重字符串替换
char* multi_replace(char* cs, const char* str1, const char* str2)
{
    char* pch = strstr(cs, str1); // 检查是否要替换
    if (pch == NULL)
        return pch;

    while (strstr(cs, str1))
        cs_replace(cs, str1, str2);
    return cs;
}


