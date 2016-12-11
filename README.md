# gprmc
本工具从NMEA文件里读取GPRMC的GPS时间戳  BY Hong Wenjun

Usage: gprmc.exe  [NMEA.txt]  [gps.txt]  [8484]

输出文件不填，结果显示在屏幕上
*   WGS-84 和 GCJ-02 的 EMEA 打印转换第三个参数 code 定义
*   02  表示 GCJ-02;
*   84  表示 WGS-84;
*
*   code 定义 默认 8484
*   8484: 输入WGS-84 度分格式, 输出WGS-84 度小数
*   8402: 输入WGS-84 度分格式, 输出GCJ-02 火星坐标
*
*   0202: 输入GCJ-02 火星坐标, 输出GCJ-02 火星坐标
*   0284: 输入GCJ-02 火星坐标, 输出WGS-84 度小数
***

![](https://github.com/hongwenjun/nmea_gprmc/blob/master/img/nmea_gprmc.png) 
# NMEA GPRMC 格式图解，NMEA_GPRMC.H 是本图文本格式
https://github.com/hongwenjun/nmea_gprmc/blob/master/img/NMEA_GPRMC.H
		
		
***		
		
![](https://github.com/hongwenjun/nmea_gprmc/blob/master/img/bdgps_in_china_google.jpg)  
		
# 百度导航记录的轨迹文件GPS数据是火星坐标,，使用google地图和Bing地图中国版无偏差
		5143e676-9d9d-43c6-8fb2-abfe62f4fecb.bin.gz
	使用工具 https://github.com/hongwenjun/TrajectoryCombine 提取
		
		纬度    经度    时速(Km/H)      时间戳
		29.20859        119.54156       0.0     2016-10-23 15:29:23
		29.20384        119.53863       15.4    2016-10-23 15:33:50
		29.21070        119.53882       0.0     2016-10-23 15:38:37
		29.20282        119.53762       32.1    2016-10-23 15:44:02
		29.20668        119.51324       49.6    2016-10-23 15:48:25
		
http://www.google.cn/maps/dir/29.20859%09119.54156/29.20384%09119.53863/29.21070%09119.53882/29.20282%09119.53762/29.20668%09119.51324
		
***

![](https://github.com/hongwenjun/nmea_gprmc/blob/master/img/mapbar_in_bing.jpg)  

		
# 图吧汽车位置抓的NEMA数据是火星坐标，使用google地图和Bing地图中国版无偏差
		20161023152954-1-syn.nmea
		$GPRMC,153013,A,2920.864000,N,11954.167000,E,3.00,0.00,20161023,,,D*7D
		$PTUBA,167.94,,17,GPS,,8.00,F,F*15
		$GPRMC,153015,A,2920.863000,N,11954.167000,E,3.00,0.00,20161023,,,D*7C
		$PTUBA,168.68,,17,GPS,,12.00,F,F*22
		
http://www.google.cn/maps/dir/29.20863000%09119.54168000
		
# 本工具 https://github.com/hongwenjun/nmea_gprmc (编写中) 可以提取转换
		
# NEMA TOOLS 工具抓的 GPS坐标是 度分格式
		
		log_20161023_152959.txt
		$GPRMC,073001.00,A,2912.691526,N,11932.212546,E,000.1,,231016,,,A*7A
		$GPRMC,073059.00,A,2912.726239,N,11932.183854,E,007.6,330.1,231016,,,A*59
		$GPRMC,073100.00,A,2912.728339,N,11932.182502,E,007.8,328.5,231016,,,A*57
		$GPRMC,073101.00,A,2912.730270,N,11932.180878,E,007.9,323.8,231016,,,A*56
		
		度分格式：2912.730270,N,11932.180878,E
		转换成度小数格式是: 29.212171       119.536348
		
		使用google地图中国版 位置偏差
http://www.google.cn/maps/dir/29.212171%09119.536348
![](https://github.com/hongwenjun/nmea_gprmc/blob/master/img/NEMA_in_china_google.jpg)  

![](https://github.com/hongwenjun/nmea_gprmc/blob/master/img/NEMA_in_google.jpg)  
		
		使用google国际版，位置正确的
https://www.google.com/maps/place/29°12'43.8"N+119°32'10.8"E/@29.2126606,119.5334187

***

# GPS NMEA 工具抓的 GPS坐标是 度分格式
		
		20161023140958.txt
		$GPRMC,060947.00,A,2912.680607,N,11932.222854,E,002.3,288.3,231016,,,A*51
		$GPRMC,060948.00,A,2912.680646,N,11932.222077,E,002.3,268.5,231016,,,A*5A
		$GPRMC,060949.00,A,2912.680596,N,11932.221495,E,002.3,247.4,231016,,,A*52
		$GPRMC,060950.00,A,2912.680666,N,11932.220951,E,002.3,261.8,231016,,,A*5A
		$GPRMC,060951.00,A,2912.680943,N,11932.220313,E,002.3,285.0,231016,,,A*5D
		
		度分格式：2912.680607,N,11932.222854,E
		转换成度小数格式是: 29.211343       119.537048
		使用google国际版，位置正确的
https://www.google.com/maps/place/29°12'40.8"N+119°32'13.4"E/@29.211343,119.5348593

![](https://github.com/hongwenjun/nmea_gprmc/blob/master/img/GPS_NMEA_in_google.jpg)  

***

# 以上相关 GPS数据文件已经提供测试 URL如下
https://github.com/hongwenjun/nmea_gprmc/tree/master/test_nmea


# Google Earth 支持打开导入  kml   nmea  gpx 还有 txt格式

    txt文件要自己指定精度 纬度 没有航迹。
    nmea和gpx文件支持航迹比较方便。
    gpx格式比较简单，支持转换还不错。

![image](https://github.com/hongwenjun/TrajectoryCombine/raw/master/img/gpx_on_ge.jpg)

# 工具执行命令
***

gprmc.exe  MAPBAR_NMEA_20161023152954-2-syn.nmea  gps.txt  0284

将自动把 gps.txt 转换成 gps.txt.gpx
并且 GPS里的火星坐标会转换成地球坐标
然后把gpx 拉到Google地球将显示航迹轨迹
***