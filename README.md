## 一、使用方法

```shell
git clone git@github.com:huanghantao/hht_webbench.git
cd dockerfileDir/
sh build_mirror.sh
sh start_container.sh
make clean
make
./hht_webbench -c 6 -n 1000 -m POST http://www.baidu.com
```

## 二、可以控制的选项

| 选项 | 描述                                              |
| ---- | ------------------------------------------------- |
| -c   | 模拟出的客户端数目                                |
| -n   | 总请求数                                          |
| -t   | 限制测试的最大时间（单位s）。默认时没有时间限制。 |
| -V   | 显示软件的版本                                    |
| -h   | 显示软件的使用方法                                |
| -m   | 请求方法（GET/POST）                              |

