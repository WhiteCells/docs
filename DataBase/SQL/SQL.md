SQL 可以单行或多行，默认以分号结尾。

默认情况下，MySQL 数据库的 SQL 语句不区分大小写，Oracle 不区分大小写，SQL Server 不区分大小写，PostgreSQL 区分大小写，SQLite 区分大小写。

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
CREATE DATABASE [IF NOT EXISTS] <DataName>;
```

`DATABASE` 关键字可以使用 `SCHEMA` 替换。

#### 删除数据库

```sql
DROP DATABASE [IF EXISTS] <DataName>;
```





### DML(Data Manipulation Language)

数据操作语言，用于对数据库表中的数据进行**增删改**



### DQL(Data Query Language)

数据查询语言，用于对数据库表中的数据进行**查**



### DCL(Data Control Language)

数据控制语言，用于创建数据库用户和控制数据库的访问权限。





