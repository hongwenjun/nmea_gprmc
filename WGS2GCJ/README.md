# C/C++ 使用ChinaMapShift库 测试互转: 地球WGS-84 火星GCJ-02 百度BD-09


**重点内容**必应-中国地图 采用的是火星坐标
http://cn.bing.com/ditu/
	
	**重点内容**NMEA Tools 采集的度分格式要先转成小数格式
	**重点内容**再转成火星坐标，才能在中国地图上对应。
算法库只能自己下载了	
https://github.com/Dronaldo17/ChinaMapShift
	Algorithm for the map offset problem in China. 
	**重点内容**解决中国地图偏移问题的算法。
	
![必应-中国地图 采用的是火星坐标](https://github.com/hongwenjun/nmea_gprmc/blob/master/WGS2GCJ/WGS2GCJ.png) 

***
测试代码
```
#include <iostream>
#include <string>
#include <stdio.h>
#include "china_shift.h"
#include <iomanip>

// Transform WGS-84 to GCJ-02 (Chinese encrypted coordination system)

//    typedef struct {
//        double lng;
//        double lat;
//    } Location;
//
//    Location transformFromWGSToGCJ(Location wgLoc);
//    Location transformFromGCJToWGS(Location gcLoc);
//    Location bd_encrypt(Location gcLoc);
//    Location bd_decrypt(Location bdLoc);


using namespace std;

int main()
{

    puts("地球WGS-84 转 火星GCJ-02 转  百度BD-09");

    Location gps = { 119.465265, 29.1934702};
    cout << setprecision(9) << "地球WGS-84: "  << gps.lat << "  " << gps.lng << endl;

    gps = transformFromWGSToGCJ(gps);
    cout << "火星GCJ-02: "  << gps.lat << "  " << gps.lng << endl;

    gps = bd_encrypt(gps);
    cout << "百度 BD-09: "  << gps.lat << "  " << gps.lng << endl;

    cout << endl << endl;



    puts("百度BD-09  转 火星GCJ-02 转  地球WGS-84");

    gps = { 119.476936, 29.196518};
    cout << "百度 BD-09: "  << gps.lat << "  " << gps.lng << endl;

    gps = bd_decrypt(gps);
    cout << "火星GCJ-02: "  << gps.lat << "  " << gps.lng << endl;

    gps = transformFromGCJToWGS(gps);
    cout << "地球WGS-84: "  << gps.lat << "  " << gps.lng << endl;

    return 0;
}


```
***
```
地球WGS-84 转 火星GCJ-02 转  百度BD-09
地球WGS-84: 29.1934702  119.465265
火星GCJ-02: 29.1908196  119.470341
百度 BD-09: 29.1965172  119.476936


百度BD-09  转 火星GCJ-02 转  地球WGS-84
百度 BD-09: 29.196518  119.476936
火星GCJ-02: 29.1908195  119.470342
地球WGS-84: 29.1934702  119.465265

以上是输出结果，使用百度API地图取的点，能转到WGS-84坐标，在 maps.google.com上地图对应。 
Google地图中国版，方便把输入几个火星坐标，通过如下方式连接起来，%09是转义符
http://www.google.cn/maps/dir/29.1934702%09119.465265/29.1908196%09119.470341/29.1965172%09119.476936/

```
相关链接
https://github.com/hongwenjun/nmea_gprmc
https://github.com/hongwenjun/TrajectoryCombine
