### Windows 安装 Java 环境

[Java Downloads | Oracle](https://www.oracle.com/java/technologies/downloads/#jdk18-windows)

1. 右键点击“此电脑”，选择“属性”。
2. 在“系统属性”窗口中，点击“高级系统设置”。
3. 在“系统属性”窗口中，点击“环境变量”。
4. 在“系统变量”中，找到并点击“新建”。
5. 输入变量名：JAVA_HOME，变量值：JDK的安装目录，例如：C:\Program Files\Java\jdk1.8.0_221。
6. 在“系统变量”中，找到并点击“Path”，点击“编辑”。
7. 在“编辑环境变量”窗口中，点击“新建”，将JDK的bin目录添加到环境变量中，例如：C:\Program Files\Java\jdk1.8.0_221\bin。
8. 在“系统变量”中，找到并点击 `CLASSPATH`，如果没有此变量，则点击“新建”。在“变量值”中输入：`.;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar`。

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
    
    
