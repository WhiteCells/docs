### Windows 安装 Java 环境

[Java Downloads | Oracle](https://www.oracle.com/java/technologies/downloads/)

配置环境变量：

1. `JAVA_HOME`，变量值：JDK的安装目录，例如：`D:\dev\env\java`
2. `CLASSPATH`，变量值：`.;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;`
3. `Path`，**添加**变量值：`%JAVA_HOME%\bin;%JAVA_HOME%\jre\bin`

### Linux 安装 Java 环境

1. 打开终端，编辑系统环境变量

    ```sh
     sudo vim ~/.bashrc
    ```

2. 将以下内容添加到文件末尾

    ```sh
    export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
    export PATH=$JAVA_HOME/bin:$PATH
    export CLASSPATH=.:$JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar
    ```

4. 保存文件并退出
5. 输入以下命令以使更改生效

    ```sh
    source ~/.bashrc
    ```
    
    
