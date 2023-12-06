## 概念

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

## MySQL 数据库

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

### SQL 通用语法

1. SQL 语句可以单行或多行，以分号结尾

2. SQL 语句可以使用 空格 / 缩进 使语句具有可读性

3. MySQL 数据库的 SQL 语句不区分大小写，关键字建议大写

4. 注释：

   1. 单行注释：

      ```sql
      -- 注释
      # 注释 (MySQL 特有)
      ```

   2. 多行注释：

      ```sql
      /* 
      注释            
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

#### DDL 语句

##### 库操作

###### 查询数据库

```sql
# 查询所有数据库
SHOW DATABASES;

# 查询当前数据库
SELECT DATABASE();
```

###### 创建数据库

```sql
# 创建数据库
CREATE DATABASE [IF NOT EXISTS] 数据库名 [DEFAULT CHARSET=CharacterSet] [COLLATE SortRules];
CREATE SCHEMA [IF NOT EXISTS] 数据库名 [DEFAULT CHARSET=CharacterSet] [COLLATE SortRules];
```

###### 删除数据库

```sql
# 删除数据库
DROP DATABASE [IF EXISTS] 数据库名;
```

###### 使用数据库

```sql
# 使用数据库
USE 数据库名;
```

##### 表操作	

###### 查询表

```sql
# 查询当前数据库所有表
SHOW TABLES;

# 查询表结构
DESC 表名; -- DESCRIBE 表名;
SHOW COLUMNS FROM 表名;

# 查询指定表的建表语句
SHOW CREATE TABLE 表名;

# 显示表内容
select * from 表名;
```

###### 创建表

```sql
# 创建表
CREATE TABLE TableName (
	字段1 字段1类型 [COMMENT 注释内容],
	字段2 字段2类型 [COMMENT 注释内容],
	字段3 字段3类型 [COMMENT 注释内容]
) [COMMENT 注释内容];
-- mysql> create table stu_info(
--     -> name varchar(20),
--     -> gender char(1),
--     -> age tinyint unsigned,
--     -> idcode char(18)
--     -> ) comment 'student_table';
```

###### 修改表

```sql
# 添加字段
ALTER TABLE 表名 ADD 字段 字段类型 [COMMENT 注释内容] [constraint];
-- alter table stu_info add score tinyint unsigned;

# 修改字段
ALTER TABLE 表名 CHANGE 旧字段 新字段 新字段类型 [COMMENT 注释内容] [constraint];
-- alter table stu_info change name nickname varchar(10);

# 删除字段
ALTER TABLE 表名 DROP 字段;
-- alter table stu_info drop nickname;

# 修改表名
ALTER TABLE 旧表名 RENAME TO 新表名;
-- alter table stu_info rename to stu;

# 删除表
DROP TABLE [IF EXISTS] 表名;
-- drop table if exits stu_info;

# 删除指定表，并重新创建该表
TRUNCATE TABLE 表名;
-- truncate table stu_info;
```

##### 数据类型

###### 数值类型

- `TINYINT`：占用 1 个字节，有符号范围为 -128 到 127，无符号范围为 0 到 255。

  ```sql
  TINYINT
  TINYINT UNSIGNED
  ```

- `SMALLINT`：占用 2 个字节，有符号范围为 -32768 到 32767，无符号范围为 0 到 65535。

  ```sql
  SMALLINT
  SMALLINT UNSIGNED
  ```

- `MEDIUMINT`：占用 3 个字节，有符号范围为 -8388608 到 8388607，无符号范围为 0 到 16777215。

  ```sql
  MEDIUMINT
  MEDIUMINT UNSIGNED
  ```

- `INT / INTEGER`：占用 4 个字节，有符号范围为 -2147483648 到 2147483647，无符号范围为 0 到 4294967295。

  ```sql
  INT
  INT UNSIGNED
  ```

- `BIGINT`：占用 8 个字节，有符号范围为 -9223372036854775808 到 9223372036854775807，无符号范围为 0 到 18446744073709551615。

  ```sql
  BIGINT
  BIGINT UNSIGNED
  ```

- `FLOAT`：占用 4 个字节，单精度浮点数范围可表示约 -3.402823466E+38 到 -1.175494351E-38，以及 0 和 1.175494351E-38 到 3.402823466E+38。

  ```sql
  FLOAT(4, 2) -- 整体长度 4 位(包括 .)，1 位小数
  FLOAT UNSIGNED
  ```

- `DOUBLE`：占用 8 个字节，双精度浮点数范围可表示约 -1.7976931348623157E+308 到 -2.2250738585072014E-308，以及 0 和 2.2250738585072014E-308 到 1.7976931348623157E+308。

  ```sql
  DOUBLE(4, 2) -- 整体长度 4 位(包括 .)，2 位小数
  DOUBLE UNSIGNED
  ```

- `DECIMAL`：用于精确表示小数和定点数，具体范围需要根据数据类型定义时指定的参数来确定。

###### 字符串类型

- `CHAR` 定长字符串，占用 0~255 字节

  ```sql
  char(10) -- 定长 10 个字符，占用固定空间，为占用空间使用 空格 进行补位
  -- 性能高
  ```
- `VARCHAR` 变长字符串，占用 0~65535 字节

  ```sql
  varchar(10) -- 最多 10 个字符，占用空间取决于实际字符空间
  -- 性能较差
  ```
- `TINYBLOB` 不超过 255 个字符的二进制数据，占用 0~255 字节
- `TINYTEXT` 短文本字符串，占用 0~255 字节
- `BLOB` 二进制形式的长文本数据，占用 0~65535 字节
- `TEXT` 长文本数据，占用 0~65535 字节
- `MEDIUMBLOB` 二进制形式的中等长度文本数据，占用 0~16777215 字节
- `MEDIUMTEXT` 中等长度文本数据，占用 0~16777215 字节
- `LONGBLOB` 二进制形式的极大文本数据，占用 0~4294967295 字节
- `LONGTEXT` 极大文本数据，占用 0~4294967295 字节

###### 日期类型

```sql
# 日期值
DATE
-- 格式: YYYY-MM--DD
-- 范围: 1000-01-01 至 9999-12-31
-- 占用: 3 字节

# 时间值或持续时间
TIME
-- 格式: HH:MM:SS
-- 范围: -838:59:59 至 838:59:59
-- 占用: 3 字节

# 年份值
YEAR
-- 格式: YYYY
-- 范围: 1901 至 2155
-- 占用: 1 字节

# 混合日期和时间值
DATETIME
-- 格式: YYYY-MM-DD HH:MM:SS
-- 范围: 1000-01-01 00:00:00 至 9999:12-31 23:59:59
-- 占用: 8 个字节

# 混合日期和时间值，时间戳
TIMESTAMP
-- 格式: YYYY-MM-DD HH:MM:SS
-- 范围: 1970-01-01 00:00:01 至 2038-01-19 03:14:07
-- 占用: 4 个字节
```

#### DML 语句

##### 添加数据

```sql
# 指定字段添加数据
INSERT INTO TableName (Field1, Field2, ...) VALUES (Value1, Value2, ...);
-- insert into stu_info (id, nickname, age, gender, score) values ('AAA', 'aaa', 20, '男', 90);

# 全部字段添加数据
INSERT INTO TableName VALUES (Value1, Value2, ...);
-- insert into stu_info values ('BBB', 'bbb', 31, '男', 89);

# 批量添加数据
INSERT INTO TableName (Field1, Field2, ...) VALUES (Value1, Value2, ...), (Value1, Value2, ...), (Value1, Value2, ...);
INSERT INTO TableName VALUES (Value1, Value2, ...), (Value1, Value2, ...), (Value1, Value2, ...);

-- 插入数据时，指定的字段顺序需要与值的顺序一一对应
-- 字符串和日期值应包含在单引号中
-- 插入的数据大小，应该在字段的规定范围内，否则报错
```

##### 修改数据

```sql
UPDATE TableName SET Field1 = Value1, Field2 = Value2, ...[WHERE Condition];
-- 修改语句的条件为可选，没有条件则会修改整张表的所有数据
-- update stu_info set nickname = 'ccc' where nickname = 'aaa';
```

##### 删除数据

```sql
DELETE FROM TableName [WHERE Condition];
-- DELETE 语句的条件为可选，没有条件则会删除整张表的所有数据
-- DELETE 语句不能删除某一个字段的值（可以使用 UPDATE）
-- delete from stu_info where id = 'AAA';

SHOW VARIABLES LIKE 'SQL_SAFE_UPDATES'; # 查看数据库安全参数
SET SQL_SAFE_UPDATES = 0; # 设置安全参数
```

#### DQL 语句

```sql
-- 语句编写顺序要求
SELECT
    字段列表
FROM
    表名列表
WHERE
    条件列表
GROUP BY
    分组字段列表
HAVING
    分组后条件列表
ORDER BY
    排序字段列表
LIMIT
    分页参数
```

##### 基本查询

```sql
# 查询多个字段
SELECT 字段列表 FROM 表名;
SELECT * FROM TableName; -- 查询所有字段 (尽量不使用 * , 可读性低)

# 字段设置别名
SELECT 字段 | [AS 别名1], [AS 别名2] ... FROM 表名;
-- select nickname as 昵称 FROM stu_info;
-- as 可以省略

# 查询 (去除重复记录)
SELECT DISTINCT 字段列表 FROM 表名;
-- select distinct nickname from stu_info;
```

##### 条件查询

```sql
SELECT 字段列表 FROM 表名 WHERE 条件;
-- select id, score from stu_info where score > 80 && score < 90;
```

```sql
>                      # 大于
>=                     # 大于等于
<                      # 小于
<=                     # 小于等于
=                      # 等于
<>                     # 不等于
!=                     # 不等于
BETWEEN ... AND ...    # 在某个范围之内(含最小值、最大值)
IN(...)                # 在 in 之后的列表中的值，... 多选，只要满足其一即可
LIKE 占位符            # 模糊匹配( _ 匹配单个字符，% 匹配任意个字符)
IS NULL                # 是 NULL
AND                    # 并且
&&                     # 并且, 未来版本删除
OR                     # 或者(多个条件任意一个成立)
||                     # 或者, 未来版本删除
NOT                    # 非
!                      # 非, 未来版本删除
```

##### 聚合函数

将**一列**数据作为一个整体，进行纵向计算。所有 null 值不参与聚合函数的运算。

常见聚合函数

- count 统计数据
- max 最大值
- min 最小值
- avg 平均值
- sum 求和

语法

```sql
SELECT AggregateFunc(字段列表) FROM 表名 [WHERE 条件];
-- select count(*) from stu_info; -- 统计数量
-- select max(age) from stu_info; 
```

##### 分组查询

where 和 having 区别：

执行时机不同：where 是分组之前进行过滤，不满足 where 条件，不参与分组，而 having 是分组之后对结果进行过滤。

判断条件：where 不能对聚合函数进行判断，having 可以对聚合函数进行判断。

执行顺序：where > 聚合函数 > having

分组之后，查询的字段一般为聚合函数和分组字段，查询其他字段无任何意义。 

```sql
SELECT 字段列表 FROM 表名 [WHERE 条件] GROUP BY 分组字段 [HAVING 条件];
-- select gender, count(*) from stu_info group by gender; -- 统计男性和女性各又多少人
-- select address, count(*) from stu_info where age < 45 group by address having count(*) >= 3;
```

##### 排序查询

```sql
SELECT 字段列表 FROM 表名 ORDER BY 字段1 排序方式1, 字段2 排序方式2;
-- 排序方式
-- ASC 升序 （默认）
-- DESC 降序
-- 多个字段排序，当 字段1 相同时，才会根据 字段2 进行排序
```

##### 分页查询

```sql
SELECT 字段列表 FROM 表名 起始索引, 查询记录数;
-- 起始索引从 0 开始，起始索引 = (索引页码 - 1) * 每页显示记录数
-- 查询记录数，[起始索引, 起始索引 + 查询记录数) 查询这个区间的记录
-- 分页查询是数据库的方言，不同的数据库有不同的实现，MySQL 中使用 LIMIT
SELECT 字段列表 FROM 表名 limit 起始索引, 查询记录数;
-- 如果查询的是第 1 页数据(索引从 0 开始)，起始索引可以忽略: SELECT 字段列表 FROM 表名 查询记录数;
```

##### DQL 执行顺序

```sql
FROM
    表名列表
WHERE
    条件列表
GROUP BY
    分组字段列表
HAVING
    分组后条件列表
SELECT
    字段列表
ORDER BY
    排序字段列表
LIMIT
    分页参数
```

#### DCL 语句

##### 管理用户

###### 查询用户

```sql
USE mysql;
SELECT * FROM user;
```

###### 创建用户

```sql
CREATE USER [IF NOT EXISTS] '用户名'@'主机名' IDENTIFIED BY '密码';
-- 主机名 % 表示任意主机可以访问
```

###### 修改用户密码

```sql
ALTER USER [IF EXISTS] '用户名'@'用户名' IDENTIFIED with mysql_native_password BY '新密码';
```

###### 删除用户

```sql
DROP USER [IF EXISTS] '用户名'@'主机名';
```

##### 权限控制

常用权限

| 权限                | 说明                   |
| ------------------- | ---------------------- |
| ALL, ALL PRIVILEGES | 所有权限               |
| SELECT              | 查询权限               |
| INSERT              | 插入数据               |
| UPDATE              | 修改数据               |
| DELETE              | 删除数据               |
| ALTER               | 修改表                 |
| DROP                | 删除数据库 / 表 / 视图 |
| CREATE              | 创建数据库 / 表        |

###### 查询权限

```sql
SHOW GRANTS FOR '用户名'@'主机名';
```

###### 授予权限

```sql
GRANTS 权限列表 ON 数据库名.表名 TO '用户名'@'主机名';
-- grants all on mysql.* to 'xxx'@'%';
-- 所有权限 all
-- 多个权限之间使用 , 进行分隔
-- 数据库名和表名可以使用 * 进行通配
-- 主机名 % 表示任意主机可以访问
```

###### 撤销权限

```sql
REVOKE 权限列表 ON 数据库名.表名 FROM '用户名'@'主机名';
-- 所有权限 all
-- 全部数据库和表 *.*
```

### 内置函数

#### 字符串函数

| 函数                       | 功能                                                         |
| -------------------------- | ------------------------------------------------------------ |
| CONCAT(S1, S2, ... Sn)     | 字符串拼接，将 S1, S2, .. Sn 拼接成一个字符串                |
| LOWER(str)                 | 将字符串 str 全部转为小写                                    |
| UPPER(str)                 | 将字符串 str 全部转为大写                                    |
| LAPD(str, n, pad)          | 左填充，用字符串 pad 对 str 的左边进行填充，达到 n 个字符串长度 |
| RPAD(str, n, pad)          | 右填充，用字符串 pad 对 str 的右边进行填充，达到 n 个字符串长度 |
| TRIM(str)                  | 去掉字符串头部和尾部的空格                                   |
| SUBSTRING(str, start, len) | 返回从字符串 str 从 start 位置起的 len 个长度的字符串（下标从 1 开始） |

> eg：将员工工号 workno 前补 0，1 号为 00001，10 为 00010
>
> ```sql
> update emp set workno = lpad(workno, 5, '0');
> ```

#### 数值函数









