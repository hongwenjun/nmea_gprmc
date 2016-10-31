#include <cstdio>      // 定义输入／输出函数
#include <cctype>      // 字符处理
#include <cstring>
#include "gprmc.h"

void help();

int main(int argc, char* argv[])
{

    if (1 == argc) {
        help();
        return -1;
    }

    FILE* input = fopen(argv[1], "r"); // 数据输入文件
    if (ferror(input)) {
        printf("文件错误：不能打开输入文件: %s \n", argv[1]);
        return -1;
    }

    FILE* outfile;
    if (2 < argc)  // 如果没有输出文件，输出到屏幕
        outfile = fopen(argv[2], "w"); // 输出结果文件
    else
        outfile = stdout;

    int code = 8402;  // 定义在 print_gps_point里
    if (4 == argc) {
        if (atoi(argv[3]) > 0)
            code = atoi(argv[3]);
    }
//    printf("code : %d\n", code);

    char line[BUFSIZ]; // 读取一行 GPRMC
    gprmc_format rmc;  // 存储 GPRMC
    bool read_rmc = false;

    int out_code = code % 100;
    const char* gps = NULL;

    if (out_code == 84)
        gps = "WGS-84";

    if (out_code == 02)
        gps = "GCJ-02";
    fprintf(outfile, "%s:纬度\t经度\t时速(Km/H)\t时间戳\n", gps);


    while (fgets(line, BUFSIZ, input)) {
        read_rmc = read_gprmc(line, rmc);

        if (read_rmc) {
            // 打印 GPS坐标速度时间戳

            print_gps_point(outfile, rmc, code);

//    fprint_gprmc(stdout, rmc);

        }
    }
    return 0;

}


void help()
{
    printf("本工具从NMEA文件里读取GPRMC的GPS时间戳  BY Hong Wenjun\n\n");
    printf("Usage: gprmc.exe  [NMEA.txt]  [gps.txt]  [8402]\n");
    printf("\n输出文件不填，结果显示在屏幕上\n");
    printf("*   WGS-84 和 GCJ-02 的 EMEA 打印转换第三个参数 code 定义\n"
           "*   02  表示 GCJ-02;\n"
           "*   84  表示 WGS-84;\n"
           "*\n"
           "*   code 定义 默认 8402\n"
           "*   8484: 输入WGS-84 度分格式, 输出WGS-84 度小数\n"
           "*   8402: 输入WGS-84 度分格式, 输出GCJ-02 火星坐标\n"
           "*\n"
           "*   0202: 输入GCJ-02 火星坐标, 输出GCJ-02 火星坐标\n"
           "*   0284: 输入GCJ-02 火星坐标, 输出WGS-84 度小数\n");
}

