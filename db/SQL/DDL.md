### 库操作

#### 查询数据库

```sql
# 查询所有数据库
SHOW DATABASES;

# 查询当前数据库
SELECT DATABASE();
```

#### 创建数据库

```sql
# 创建数据库
CREATE DATABASE [IF NOT EXISTS] 数据库名 [DEFAULT CHARSET=CharacterSet] [COLLATE SortRules];
CREATE SCHEMA [IF NOT EXISTS] 数据库名 [DEFAULT CHARSET=CharacterSet] [COLLATE SortRules];
```

#### 删除数据库

```sql
# 删除数据库
DROP DATABASE [IF EXISTS] 数据库名;
```

#### 使用数据库

```sql
# 使用数据库
USE 数据库名;
```

### 表操作

#### 查询表

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

#### 创建表

```sql
# 创建表
CREATE TABLE TableName (
	字段1 类型 [COMMENT 注释],
	字段2 类型 [COMMENT 注释],
	字段3 类型 [COMMENT 注释]
) [COMMENT 注释内容];
-- mysql> create table stu_info(
--     -> name varchar(20),
--     -> gender char(1),
--     -> age tinyint unsigned,
--     -> idcode char(18)
--     -> ) comment 'student_table';
```

#### 修改表

```sql
# 添加字段
ALTER TABLE 表名 ADD 字段 字段类型 [COMMENT 注释] [constraint];
-- alter table stu_info add score tinyint unsigned;

# 修改字段
ALTER TABLE 表名 CHANGE 旧字段 新字段 新字段类型 [COMMENT 注释] [constraint];
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

### 数据类型

#### 数值类型

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

##### 字符串类型

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

##### 日期类型

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
