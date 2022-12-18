## 项目内容

- 来自[编译原理之美](https://time.geekbang.org/column/intro/219)
- 手工实现简易脚本语言

## 本地运行


- 文件根目录下拉取Ubuntu镜像(等待时长较长)
```
docker-compose up -d
```

- 进入test目录编译
```
cd test
make
```

- 运行脚本
```
./SimpleScript
or

./SimleScript -v #打印AST树状结构
```
