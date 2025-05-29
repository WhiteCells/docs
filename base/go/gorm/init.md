```go
package main

import (
	"fmt"

	_ "github.com/go-sql-driver/mysql" // Add this line
	"github.com/jinzhu/gorm"
)

type Product struct {
	// gorm.Model        // 添加 ID、created_at、updated_at、deleted_at 字段
	Code  string `gorm:"primary_key"`
	Price uint
}

func main() {
	db, err := gorm.Open("mysql", "root:3215@tcp(127.0.0.1:3306)/testdb?charset=utf8&parseTime=True&loc=Local")
	if err != nil {
		fmt.Printf("connect err: %s\n", err.Error())
		return
	}
	defer db.Close()

	// 检查 Product 结构是否变化，变化则进行迁移
	db.AutoMigrate(&Product{})

	// 增
	db.Create(&Product{Code: "1", Price: 100})

	// 查
	var product Product
	if err := db.First(&product, "Code = ?", "1").Error; err != nil {
		fmt.Println("Query Failed", err)
	} else {
		fmt.Printf("Query: Code=%s, Price=%d\n", product.Code, product.Price)
	}

	// 改
	if err := db.Model(&product).Update("Price", 200).Error; err != nil {
		fmt.Println("Update Failed", err)
	} else {
		fmt.Println("Update Success")
	}

	// 删
	if err := db.Delete(&product).Error; err != nil {
		fmt.Println("Delete Failed", err)
	} else {
		fmt.Println("Delete Success")
	}
}
```

