#include "gprmc.h"
#include "china_shift.h"

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

#ifdef DEBUG

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

#endif

    return err;

}

// 读取一行GPRMC数据，判断是否是GPRMC数据行
bool read_gprmc(const char* line, gprmc_format& rmc)
{

    char line_buf[BUFSIZ];
    strncpy(line_buf, line, BUFSIZ);

    int chksum = 0;

    if ('$' != line_buf[0]) {
        print_error(1);
        return false;;

    } else {

        char* pch = strrchr(line_buf, '*');
        if (pch != NULL) {
            *pch = '\0';
            rmc.mode = *(pch - 1);
            pch++;
            rmc.chksum = strtol(pch, &pch, 16);
            // printf("%X\n", chksum);

            if (rmc.chksum != checksum(line_buf + 1)) {
                print_error(2);
                return false;;
            }
        } else {
            print_error(3);
            return false;;
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

            // 一般空
            rmc.mag_variation   = 0;
            rmc.mag_var_direct  = 'W';

            rmc.mode = rmc.mode; // 之前已经读到

        } else {
            print_error(4);
            return false;;

        }

    }

    return true;
}

void print_gps_point(FILE* outfile, gprmc_format gps_point, int code)
{

    double lat = gps_point.lat;
    double lon = gps_point.lon;


    int in_code = code / 100;
    int out_code = code % 100;

#ifdef DEBUG
    /*
    *   WGS-84 和 GCJ-02 的 EMEA 打印转换第三个参数 code 定义
    *   02  表示 GCJ-02;
    *   84  表示 WGS-84;
    *
    *   int code 定义
    *   8484: 输入WGS-84 度分格式, 输出WGS-84 度小数
    *   8402: 输入WGS-84 度分格式, 输出GCJ-02 火星坐标
    *
    *   0202: 输入GCJ-02 火星坐标, 输出GCJ-02 火星坐标
    *   0284: 输入GCJ-02 火星坐标, 输出WGS-84 度小数
    */

    if (out_code == 02)
        printf("输出GCJ-02 火星坐标 code = %d\n", code);
    if (out_code == 84)
        printf("输出WGS-84 度小数 code = %d\n", code);

#endif // DEBUG


    if (code / 100 == 84) {   // WGS-84 度分格式  需转度小数
        lat = degree_minute2dec_degrees(gps_point.lat);
        lon = degree_minute2dec_degrees(gps_point.lon);

    } else {
        // CJ-02 记录是度小数 只需除100
        lat = lat / 100.0;
        lon = lon / 100.0;
    }

    if (in_code != out_code) {
        Location gps;
        gps.lat = lat;
        gps.lng = lon;

        if (in_code / out_code == 42)
            gps = transformFromWGSToGCJ(gps);    // 地球WGS-84 转 火星GCJ-02
        else if (out_code / in_code == 42)
            gps = transformFromGCJToWGS(gps);    // 火星GCJ-02 转  地球WGS-84

        lat = gps.lat;
        lon = gps.lng;
    }



    fprintf(outfile, "%.6f\t", lat);       // 纬度
    fprintf(outfile, "%.6f\t", lon);        // 经度

    double nm_to_km = 1.852;  // 时速:节换算公里
    if (in_code == 02)
        nm_to_km = 1.0;       // CJ-02 记录是公里
    fprintf(outfile, "%.1f\t", gps_point.speed * nm_to_km);


    // UTC 时间转本地时间等有空实现

    char time_str [80] = "";
    int date = gps_point.date;
    int time = (int)gps_point.rcv_time;

    if (in_code == 02) {
        sprintf(time_str, "%d-%02d-%02d %02d:%02d:%02d",
                date / 10000, (date % 10000) / 100,  date % 100,
                time / 10000, (time % 10000) / 100,  time % 100);
    } else {
        sprintf(time_str, "%d-%02d-%02d %02d:%02d:%02d",
                2000 + date % 100, (date % 10000) / 100,  date / 10000,
                time / 10000, (time % 10000) / 100,  time % 100);

        struct tm gmt;
        sscanf(time_str, "%d-%d-%d %d:%d:%d",
               &gmt.tm_year, &gmt.tm_mon, &gmt.tm_mday,
               &gmt.tm_hour, &gmt.tm_min, &gmt.tm_sec);
        gmt.tm_year -= 1900;
        gmt.tm_mon -= 1;

        time_t timet;
        timet = mktime(&gmt) + 8 * 3600;

        struct tm* timeinfo = localtime(&timet);

        strftime(time_str, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    }

    fprintf(outfile, "%s\n", time_str);
}

// 重新生成 GPRMC 数据行, 校验值会变化
void fprint_gprmc(FILE* outfile, gprmc_format rmc)
{
    int chksum = 0;
    char tempstr[BUFSIZ];
    char finalstr[BUFSIZ];

    sprintf(tempstr, "%s,%06.0f,%c,%.5f,%c,%.5f,%c,%.2f,%.1f,%06u,,,%c",
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
