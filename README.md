# Explode-爆炸事件

原理:

爆炸事件和生物受伤事件

会漏判,但不会误判(除非两个及以上玩家聚集在一起)

有效范围: 欧氏距离(三维)  X小于等于5

.

漏判:    [时间] 苦力怕 在 主世界(11,45,14) 爆炸

非漏判:  [时间] TwOnEnd 在 主世界(11,45,14) 引爆位于 主世界(11,45,14) 的 苦力怕 并受到伤害

.

使用方法:

用任意dll加载器

在 bedrock_server.exe 根目录创建 Plugin\Log\All 文件夹

记录输出在 OnLevelExplode.log 文件里

总之很low
求大佬改改漏判,,

参考:

-https://github.com/zhkj-liuxiaohua/mcmoddll-cpp

-https://github.com/twoone-3/BDSpyrunner
