# TMX文件

首先给出资料：[TMX Map Format &mdash; Tiled 1.11.0 documentation](https://doc.mapeditor.org/en/stable/reference/tmx-map-format/#)

由于TMX文件格式变动比较多，要保证兼容性最好所有以弃用的也实现，同意为了兼容性，解析文件时对未知标签直接忽略而不同报错。

示例项目[GitHub - sainteos/tmxparser](https://github.com/sainteos/tmxparser)，[GitHub - leethomason/tinyxml2](https://github.com/leethomason/tinyxml2?tab=readme-ov-file)，可参照实现。

注意tmx文件的数据写在Tools/TMXMap里，而读取解析要写在Engine/FileIO里
