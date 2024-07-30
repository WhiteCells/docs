### d管理用户

#### 查询用户

```sql
USE mysql;
SELECT * FROM user;
```

#### 创建用户

```sql
CREATE USER [IF NOT EXISTS] '用户名'@'主机名' IDENTIFIED BY '密码';
-- 主机名 % 表示任意主机可以访问
```

#### 修改用户密码

```sql
ALTER USER [IF EXISTS] '用户名'@'用户名' IDENTIFIED with mysql_native_password BY '新密码';
```

#### 删除用户

```sql
DROP USER [IF EXISTS] '用户名'@'主机名';
```

### 权限控制

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

#### 查询权限

```sql
SHOW GRANTS FOR '用户名'@'主机名';
```

#### 授予权限

```sql
GRANTS 权限列表 ON 数据库名.表名 TO '用户名'@'主机名';
-- grants all on mysql.* to 'xxx'@'%';
-- 所有权限 all
-- 多个权限之间使用 , 进行分隔
-- 数据库名和表名可以使用 * 进行通配
-- 主机名 % 表示任意主机可以访问
```

#### 撤销权限

```sql
REVOKE 权限列表 ON 数据库名.表名 FROM '用户名'@'主机名';
-- 所有权限 all
-- 全部数据库和表 *.*
```
