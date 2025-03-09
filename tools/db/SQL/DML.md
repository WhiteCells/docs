### 添加数据

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

### 修改数据

```sql
UPDATE TableName SET Field1 = Value1, Field2 = Value2, ...[WHERE Condition];
-- 修改语句的条件为可选，没有条件则会修改整张表的所有数据
-- update stu_info set nickname = 'ccc' where nickname = 'aaa';
```

### 删除数据

```sql
DELETE FROM TableName [WHERE Condition];
-- DELETE 语句的条件为可选，没有条件则会删除整张表的所有数据
-- DELETE 语句不能删除某一个字段的值（可以使用 UPDATE）
-- delete from stu_info where id = 'AAA';

SHOW VARIABLES LIKE 'SQL_SAFE_UPDATES'; # 查看数据库安全参数
SET SQL_SAFE_UPDATES = 0; # 设置安全参数
```
