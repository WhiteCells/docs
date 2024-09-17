| 名称           | 全称                                                         | 简称                             |
| -------------- | ------------------------------------------------------------ | -------------------------------- |
| 数据库         | 存储数据的仓库，数据是有组织的进行存储                       | DataBase(DB)                     |
| 数据库管理系统 | 操作和管理数据库的大型软件                                   | DataBase Management System(DBMS) |
| SQL            | 操作关系型数据库的编程语言，定义了一套操作关系型数据库的统一标准 | Structured Query language(SQL)   |

主流的关系型数据库管理系统

1. Oracle
2. MySQL
3. Microsoft SQL Server
4. PostgreSQL

[MySQL Community Downloads](https://dev.mysql.com/downloads/)

### MySQL 图形化界面

- [Sqlyog](https://webyog.com/product/sqlyog/)
- [Navicat](https://www.navicat.com.cn/products)
- [DataGrip](https://www.jetbrains.com/zh-cn/datagrip/download/#section=windows)
- [mysql workbench](https://dev.mysql.com/downloads/workbench/)

### 启动与停止

1. 使用系统**服务管理器**

2. 使用命令

   ```sh
   # Windows
   net start [ServiceName]
   net stop [ServiceName]
   
   # Linux
   sudo service [ServiceName] start
   # or
   sudo systemctl start [ServiceName]
   
   # MySQL 开发库
   # #include <mysql/mysql.h>
   sudo apt install libmysqlclient-dev
   sudo pacman -S mariadb
   ```

### 客户端连接

1. 使用 MySQL提供的客户端命令行工具 `MySQL 8.0 Command Line Client`

2. 使用命令

   需要配置 PATH 环境变量（MySQL bin 目录）

   ```sh
   mysql [-h 127.0.0.1] [-P 3306] -u root -p
   # [] 为可选参数
   # -h 127.0.0.1  连接的 MySQL 服务器的主机地址为 127.0.0.1
   # -P 3306       连接的 MySQL 服务器的端口号为 3306
   # -u root       连接的 MySQL 服务器的用户名为 root
   # -p            表示在连接时提示输入密码
   
   # 由于默认服务器地址为 local host 127.0.0.1，端口号为 3306，所以可以缩写
   mysql -u root -p
   ```

### 数据模型

关系型数据库

建立在关系模型基础上，由多张相互连接的二维表组成的数据库。

优点：

1. 使用表存储数据，结构统一，便于维护
2. 使用 SQL 语言操作，标准统一，使用方便

### SQL语法

1. SQL 语句可以单行或多行，以分号结尾

2. SQL 语句可以使用 空格 / 缩进 使语句具有可读性

3. MySQL 数据库的 SQL 语句不区分大小写，关键字建议大写

4. 注释：

   ```mysql
   -- 注释
   # 注释 (MySQL 特有)
   
   /* 
   注释
   */
   ```

### SQL语句分类

| 分类 | 全称                       | 说明                                               |
| ---- | -------------------------- | -------------------------------------------------- |
| DDL  | Data Definition Language   | 数据定义语言，定义数据库对象（数据库、表、字段）   |
| DML  | Date Manipulation Language | 数据操作语言，对数据库中的数据进行增删改查         |
| DQL  | Data Query Language        | 数据查询语言，查询数据库中表的记录                 |
| DCL  | Data Control Language      | 数据控制语言，创建数据库用户，控制数据库的访问权限 |

### 内置函数

#### 字符串函数

| 函数                       | 功能                                                         |
| -------------------------- | ------------------------------------------------------------ |
| CONCAT(S1, S2, ... Sn)     | 字符串拼接，将 S1, S2, .. Sn 拼接成一个字符串                |
| LOWER(str)                 | 将字符串 str 全部转为小写                                    |
| UPPER(str)                 | 将字符串 str 全部转为大写                                    |
| LPAD(str, n, pad)          | 左填充，用字符串 pad 对 str 的左边进行填充，达到 n 个字符串长度 |
| RPAD(str, n, pad)          | 右填充，用字符串 pad 对 str 的右边进行填充，达到 n 个字符串长度 |
| TRIM(str)                  | 去掉字符串头部和尾部的空格                                   |
| SUBSTRING(str, start, len) | 返回从字符串 str 从 start 位置起的 len 个长度的字符串（下标从 1 开始） |

```sql
select concat('user', '000', '111'); -- 'user000111'

select lower('USER'); -- 'user'

select upper('user'); -- 'USER'

select lpad('1', 3, '234'); -- '231'

select rpad('1', 3, '234'); -- '123'

select trim(' test '); -- 'test'

select substr('hello', 3); -- 'llo'
select substring('hello', 3); -- 'llo'
select substring('hello', 2, 3); -- 'ell'

# workno 前补 0，1 号为 00001，10 为 00010
update emp set workno = lpad(workno, 5, '0');
```

#### 数值函数

| 函数        | 功能                                 |
| ----------- | ------------------------------------ |
| CEIL(x)     | 返回 x 向上取整的结果                |
| FLOOR(x)    | 返回 x 向下取整的结果                |
| MOD(x, y)   | 返回 x/y 的模                        |
| RAND()      | 返回 0~1 内随机数                    |
| ROUND(x, y) | 返回 x 四舍五入的结果，保留 y 位小数 |

```sql
select ceil(1.1); -- 2

select floor(1.1); -- 1

select mod(10, 3); -- 1

select rand(); -- [0, 1]

select round(3.14159, 4); -- 3.1416

select lpad(round(rand() * 1000000, 0), 6, '0');
```

#### 日期函数

| 函数                               | 功能                                           |
| ---------------------------------- | ---------------------------------------------- |
| CURDATE()                          | 返回当前日期                                   |
| CURTIME()                          | 返回当前时间                                   |
| NOW()                              | 返回当前日期和时间                             |
| YEAR(date)                         | 获取 date 的年份                               |
| MONTH(date)                        | 获取 date 的月份                               |
| DAY(date)                          | 获取 date 的日期                               |
| DATE_ADD(date, INTERVAL expr type) | 返回一个日期/时间值加上一个时间间隔后的时间值  |
| DATEDIFF(date1, date2)             | 返回起始时间 date1 和结束时间 date2 之间的天数 |

```sql
select curdate(); -- 2024-01-13

select curtime(); -- 17:19:29

select now(); -- 2024-01-13 17:19:36

select year(curtime()); -- 2024

select month(curtime()); -- 1

select day(curtime()); -- 13

select date_add(curtime(), interval 18 day);

select datediff('2024-01-13', '2024-01-10'); -- 3
```

#### 流程控制函数

| 函数            | 功能                                     |
| --------------- | ---------------------------------------- |
| IF(value, t, f) | 如果 value 为 true，则返回 t，否则返回 f |
|                 |                                          |
|                 |                                          |
|                 |                                          |

