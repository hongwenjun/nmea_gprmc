#include <stdio.h>
#include <string.h>
#include <time.h>
#include "china_shift.h"


#define LINE_SIZE 256

// 本地时间转换转换UCT时间   2016-12-01 07:11:27 ==> 2016-11-30T23:11:27Z
char* time_str_local2UTC(char* time_str)
{
    if (strlen(time_str) < 19)
        return NULL;

    struct tm rawtm;
    sscanf(time_str, "%d-%d-%d %d:%d:%d",
           &rawtm.tm_year, &rawtm.tm_mon, &rawtm.tm_mday,
           &rawtm.tm_hour, &rawtm.tm_min, &rawtm.tm_sec);
    rawtm.tm_year -= 1900;
    rawtm.tm_mon -= 1;

    time_t timet;
    timet = mktime(&rawtm);

    struct tm* timeinfo = gmtime(&timet);
    strftime(time_str, strlen(time_str) + 2, "%Y-%m-%dT%H:%M:%SZ", timeinfo);

    return time_str;

}

//  格式化gps_csv行 空格 或者 , 分隔的如下行
//  29.212903   119.471784  4.0 2016-10-23 16:12:02
//  29.21525, 119.467489, 36.0, 2016-10-23 16:14:28
//  转换成  gpx_line轨迹节点行
//  <trkpt lat="29.213713" lon="119.472105"><ele></ele><speed>1</speed><time>2016-12-02T08:18:18</time></trkpt>

char* gps_csv_to_gpx_line(char* gpx_line, const char* gps_csv, bool GCJToWGS)
{

    double  lat, lon, speed;
    char date[32], time[32];

    if (strrchr(gps_csv, ','))
        sscanf(gps_csv, "%lf,%lf,%lf,%s %s",  &lat, &lon, &speed, date, time);
    else
        sscanf(gps_csv, "%lf %lf %lf %s %s",  &lat, &lon, &speed, date, time);

    //   坐标转换    速度转换    时间 本地转 UTC
    Location gps;
    gps.lat = lat;
    gps.lng = lon;

    if (GCJToWGS == true)
        gps = transformFromGCJToWGS(gps);  // 火星GCJ-02 转  地球WGS-84

    speed = speed * 1000 / 3600;        // Km/H 转换成 米/秒

    strcat(date, " ");
    strcat(date, time);
    strcpy(time, date);
    time_str_local2UTC(time);

    // 格式化 GPX 轨迹节点行
    char* trkpt[6] = {
        "<trkpt lat=\"", "\" lon=\"",
        "\"><ele>", "</ele><speed>",
        "</speed><time>", "</time></trkpt>"
    };

    sprintf(gpx_line, "%s%.6f%s%.6f%s%s%.6f%s%s%s\n",
            trkpt[0], gps.lat, trkpt[1], gps.lng,
            trkpt[2], trkpt[3], speed, trkpt[4],
            time, trkpt[5]);

    return gpx_line;
}


// gps_txt 转 gpx格式
int gps_txt2gpx(FILE* input, FILE* outfile)
{


    int fraction = 10;   // 默认输出 1/N

    char* gpx_xml[4] = {"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n",
                        "<gpx xmlns=\"http://www.topografix.com/GPX/1/1\" version=\"1.1\" creator=\"https://github.com/hongwenjun\">\n<name>",
                        "</name>\n<desc/>\n<trk>\n<trkseg>\n",
                        "</trkseg>\n</trk>\n</gpx>\n"
                       };


    // 写 GPX XXML 文件头
    fprintf(outfile, "%s%s%s%s", gpx_xml[0], gpx_xml[1], "https://github.com/hongwenjun", gpx_xml[2]);

// char  line[] = "29.21525, 119.467489, 36.0, 2016-10-23 16:14:28";
// 输出  <trkpt lat="29.217875" lon="119.462401"><ele></ele><speed>10.000000</speed><time>2016-10-23T08:14:28Z</time></trkpt>

    char line[LINE_SIZE];
    char gpx_line[LINE_SIZE];
    int cnt_line = 0;
    bool save_number = true;

    // 读取标题行
    fgets(line, LINE_SIZE, input);

    while (fgets(line, LINE_SIZE, input)) {   // 读取每一行

        if (save_number =  !(cnt_line % fraction)) {
            gps_csv_to_gpx_line(gpx_line, line, false);  // bool GCJToWGS = true
            fprintf(outfile, "%s", gpx_line);
        }
        cnt_line++;
    }

    fprintf(outfile, "%s\n",  gpx_xml[3]);

    return cnt_line;
}


