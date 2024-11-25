### 创建

```go
user := User{Name: "user1", Pass: "sa9qwe"}
db.NewRecord(user) // 返回 true
db.Create(&user)
db.NewRecord(user) // 返回 false
```

### 查询

```go
// 获取一条数据，按主键排序
db.First(&user)

// 获取一条数据，不指定排序
db.Take(&user)

// 获取最后一条数据，按主键排序
db.Last(&user)

// 获取所有数据
db.Find(&user)

// 通过主键进行查询，适用于之间为数字类型
db.First(&user, 1)

// 原生 SQL
db.Where("Name = ?", "user1").First(&user)
db.Where("Name in (?)", []string{"user1", "user2"}).Find(&user)
db.Where("Name LIKE ?", "%sr%").Find(&user)
// AND
// Time
// BETWEEN

// Struct
// Map
// 
```



### 更新





### 删除

