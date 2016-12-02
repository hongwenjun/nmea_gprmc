# Google Earth 支持打开导入  kml   nmea  gpx 还有 txt格式

    txt文件要自己指定精度 纬度 没有航迹。

    nmea和gpx文件支持航迹比较方便。

    gpx格式比较简单，支持转换还不错，所以接下来要写个 txt2gpx 工具
    
'''

    WGS-84:纬度	经度	时速(Km/H)	时间戳
    29.212143	119.471453	11.0	2016-10-23 16:11:27
    29.212553	119.471644	10.0	2016-10-23 16:11:45
    29.212903	119.471774	4.0	2016-10-23 16:12:03
    29.213713	119.472105	13.0	2016-10-23 16:13:04

    ---------------------------------------------------

    <?xml version="1.0" encoding="UTF-8"?>
    <gpx xmlns="http://www.topografix.com/GPX/1/1" version="1.1" creator="https://github.com/hongwenjun">
    <name>test.gpx</name>
    <desc/>
    <trk>
    <trkseg>
    <trkpt lat="29.213713" lon="119.472105"><ele></ele><speed>1</speed><time>2016-12-02T08:18:18</time></trkpt>
    <trkpt lat="29.214613" lon="119.472296"><ele></ele><speed>2</speed><time>2016-12-02T08:19:18</time></trkpt>
    <trkpt lat="29.215558" lon="119.470590"><ele></ele><speed>3</speed><time>2016-12-02T08:20:18</time></trkpt>
    <trkpt lat="29.215189" lon="119.467048"><ele></ele><speed>4</speed><time>2016-12-02T08:21:18</time></trkpt>
    <trkpt lat="29.214759" lon="119.463115"><ele></ele><speed>5</speed><time>2016-12-02T08:22:18</time></trkpt>
    </trkseg>
    </trk>
    </gpx>


'''
