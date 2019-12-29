## 创建一个共享库(so)

### 步骤

以下列文件示例

1. **foo.h**

```c
#include <stdio.h>
#include "foo.h"

int main(void)
{
    puts("This is a shared library test...");
    foo();
    return 0;
}
```

2. **foo.c**

```c
#include <stdio.h>
void foo(void)
{
    puts("Hello, I am a shared library");
}
```

3.**main.c**

```c
#include <stdio.h>
#include "foo.h"

int main(void)
{
    puts("This is a shared library test...");
    foo();
    return 0;
}
```

#### 使用地址无关代码(PIC)编译

`gcc -c -Wall -Werror -fpic foo.c`

生成目标文件`foo.o`

#### 从一个目标文件中创建共享库

`gcc -shared -o libfoo.so foo.o`

生成共享库`libgoo.so`

#### 与共享库链接

现在编译`main.c`并将它和`libfoo.so`链接起来。gcc 假定所有库均以 GCC 假定所有库均以 lib 开头，并以.so 或.a 结尾(.so 用于共享库或共享库，.a 用于静态链接库)

`gcc -Wall -o test main.c -lfoo`

但 gcc 会在其默认的位置寻找该名为`foo`的共享库，当然是失败。所以此处应指定位置

`gcc -L$yourpath$ -Wall -o test main.c -lfoo`

得到最终文件`test`

![](imgs/error.png)

试图运行发现加载共享库失败，因为没有将其安装在标准位置。有以下两种解决方式：

- `Using LD_LIBRARY_PATH`

顾名思义，使用下列命令将加载库路径短暂修改为本例 libfoo.so 所在的路径
`export LD_LIBRARY_PATH=$yourpath$`

![](imgs/ld_library_path.png)

- `Using rpath`

rpath 是一种将共享库的位置**嵌入到可执行文件本身**中的方法，而不是依赖于默认位置或环境变量。在链接阶段执行此操作。

首先`unset LD_LIBRARY_PATH`取消刚才的设定防止找到 lib 库。

`gcc -L$yourpath1$ -Wl,-rpath=$yourpath2$ -Wall -o test main.c -lfoo`

path1 用来指示链接时共享库所在的位置

path2 用于程序加载时寻找共享库
