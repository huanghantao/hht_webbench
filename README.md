## 一、使用方法

```shell
git clone git@github.com:huanghantao/hht_webbench.git
cd dockerfileDir/
sh start_container.sh
make clean && make
./hht_webbench -m get -t 4 -c 2000 http://www.baidu.com/
```

## 二、可以控制的选项

| 选项 | 描述                        |
| ---- | --------------------------- |
| -t   | 线程个数                    |
| -c   | 总的连接数                  |
| -d   | 限制测试的最大时间（单位s） |
| -V   | 显示软件的版本              |
| -h   | 显示软件的使用方法          |
| -m   | 请求方法（GET/POST）        |

