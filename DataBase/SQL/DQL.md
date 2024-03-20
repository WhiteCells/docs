### 编写顺序

```sql
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

### 基本查询

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

### 条件查询

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

### 聚合函数

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

### 分组查询

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

### 排序查询

```sql
SELECT 字段列表 FROM 表名 ORDER BY 字段1 排序方式1, 字段2 排序方式2;
-- 排序方式
-- ASC 升序 （默认）
-- DESC 降序
-- 多个字段排序，当 字段1 相同时，才会根据 字段2 进行排序
```

### 分页查询

```sql
SELECT 字段列表 FROM 表名 起始索引, 查询记录数;
-- 起始索引从 0 开始，起始索引 = (索引页码 - 1) * 每页显示记录数
-- 查询记录数，[起始索引, 起始索引 + 查询记录数) 查询这个区间的记录
-- 分页查询是数据库的方言，不同的数据库有不同的实现，MySQL 中使用 LIMIT
SELECT 字段列表 FROM 表名 limit 起始索引, 查询记录数;
-- 如果查询的是第 1 页数据(索引从 0 开始)，起始索引可以忽略: SELECT 字段列表 FROM 表名 查询记录数;
```

### 执行顺序

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
