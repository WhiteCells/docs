SQL 可以单行或多行，默认以分号结尾。

默认情况下，MySQL 在处理表名和列名时不区分大小写，但在处理数据库名时区分大小写。

Oracle 在处理表名和列名时默认不区分大小写，但在处理字符串时区分大小写。如果你在创建对象时使用了双引号，则会区分大小写。

SQL Server 默认情况下不区分大小写。

PostgreSQL 在处理表名和列名时默认区分大小写，但如果对象名没有用双引号引起来，则会将其转换为小写。

SQLite 在处理表名和列名时不区分大小写，但在处理字符串时区分大小写。

关键字建议大写。

注释：

```sql
-- 注释
# 注释（MySQL）
/* 
注释
*/
```

### DDL(Data Definition Language)

数据定义语言，用于定义数据库对象（数据库、表、字段）。

#### 创建数据库

```sql
CREATE DATABASE [IF NOT EXISTS] <DataBaseName>;
```

`DATABASE` 关键字可以使用 `SCHEMA` 替换。

#### 删除数据库

```sql
DROP DATABASE [IF EXISTS] <DataBaseName>;
```

#### 创建表

```sql
CREATE TABLE <TableName> (
    <field1> <type> [COMMENT <file1_comment>],
    <field2> <type> [COMMENT <file2_comment>],
    <field3> <type> [COMMENT <file1_comment>]
) [COMMENT <table_comment>];
```

#### 删除表

```sql
DROP TABLE [IF EXISTS] <TableName>;

-- 删除指定表，并重新创建该表
TRUNCATE TABLE <TableName>;
```

#### 修改表

```sql
-- 添加字段
ALTER TABLE <TabelName>
ADD <new_field> <type> [COMMENT <field_comment>];

-- 修改字段
ALTER TABLE <TableName> CHANGE <old_field> <new_field> <type> [COMMENT <field_comment>];

-- 删除字段
ALTER TABLE <TableName> DROP <delete_field>;

-- 修改表名
ALTER TABLE <OldTableName> RENAME <NewTableName>;
```

### DML(Data Manipulation Language)

数据操作语言，用于对数据库表中的数据进行**增删改**



### DQL(Data Query Language)

数据查询语言，用于对数据库表中的数据进行**查**



### DCL(Data Control Language)

数据控制语言，用于创建数据库用户和控制数据库的访问权限。





