合约是可部署到区块链的最小单元，一个合约通常由状态变量（合约数据）和合约函数组成。

声明编译器版本：

```solidity
pragma solidity >=0.8.0;
```

类似的表达：

```solidity
pragma solidity >=0.8.0 <0.9.0;
pragma solidity ^0.8.0;
```

### 定义合约

```solidity
contract Counter {
}
```

使用地址表示合约。

#### 合约构造函数

用于初始化合约，使用 `constructor` 关键字，合约构造函数可以忽略（编译器会添加一个默认的构造函数）。

```solidity
pragma solidity >=0.8.0;

contract Token {
    uint private x;
    constructor(uint _x) public {
        x = _x;
        owner = msg.sender;
    }
}
```

### 可见性

可以使用 `public`、`private` 等关键字来控制变量和函数是否可以被外部使用。

#### public

```solidity
contract Token {
    uint private x;
    // auto generate
    function x() external view returns (uint) {
        return x;
    }
    // auto generate
}
```

可以到暴露合约外部。会自动创建一个同名的外部函数（访问器）来获取状态变量的值。

#### external

不可以修改状态变量，声明为 `external` 的函数只能在外部调用，用于修饰外部函数。

在合约内部调用外部函数，需要使用 `this.func()`。

```solidity
contract Token {
    uint val;
    function add(uint x) external {
        val += x;
    }
    function increase() public {
        this.add(1);
    }
}
```

#### internal

声明为 `internal` 函数和状态变量只能在当前合约中使用及派生合约中访问。

#### private

声明为 `private` 函数和状态变量仅可在当前合约中使用。

### 变量

定义变量格式：`变量类型` `变量可见性` `变量名`。

### 变量类型

#### 值类型



#### 引用类型

用于表示复杂类型，引用类型包括数组和结构体。

定义引用类型时，有一个额外属性来标识数据的存储位置：

- `memory`：变量运行时存在，生命周期只在函数调用期间，gas 开销小。
- `storage`：保存状态变量，只要合约存在就一直保存在区块链中，gas 开销大。
- calldata：存储函数参数的特殊数据位置，接受外部数据，是一个不可修改的、非持久的函数参数存储区域，gas 开销最小。

```solidity
contract Token {
    uint[] arr; // 存储位置 storage
    function foo(uint[] memory memoryArr) public {
        arr = memoryArr; // 拷贝到 storage 中
        uintp[] storage arr2 = arr; // 仅分配一个指针指向同一位置
    }
}
```

#### 映射类型

键值对的映射关系存储结构。

#### 地址类型

表示账号。

```solidity
contract Token {
    address public user;
    function getUserAddress() public {
        user = msg.sender;
    }
}
```

地址类型有两种：

- `address`：保存 20 字节的值（以太坊地址大小）
- `address payable`：可支付地址（可接受以太币的地址）（20 字节）

`address payable` 拥有两个成员函数 `transfer` 和 `send`。

大部分时候时使用 `address`，当需要向地址转账时，可以将 `address` 转为 `address payable`：

```solidity
address payable ap = payable(user);

# solidity <=0.5
address payable ap = address(uint160(addr));
```

可以进行地址比较（`==`、`!=`、`<=`、`>=`、`<`、`>`）：

```solidity
function isOwner() internal view {
    require(owner() == msg.sender, "caller not owner");
}
function transferOwnership(address newOwner) public onlyOwner {
    require(newOwner != address(0)); // 不可以是零地址
    // ...
}
```

常用的地址类型属性及成员函数：

- `user.balance` 属性：返回地址余额，单位为 wei（uint256）。
- `user_payable.transfer(uint256 amount)`：向地址发送 `amount` 数量以太币（wei），使用固定 2300 gas，发送失败时抛出异常。
- `user_payable.send(uint256 amount) returns (bool)`：功能及费用和 `transfer` 一样，但发送失败返回 `false`，不抛出异常。

### 常量

使用 `constant` 声明常量，常量不占用合约的存储空间，而是在编译时使用对应的表达式值替换常量名，所以只能使用在编译时有确定值的表达式来给变量赋值。

```solidity
contract Token {
    string constant str = "token_";
}
```



### 不可变量

不可变量在构造函数中进行赋值，构造函数是在部署的时候执行，因此是运行时赋值。

使用 `immutable` 定义不可变量，不可变量不占用状态变量存储空间，在部署时，值会被追加到字节码中，因此比使用状态变量便宜，也更安全（值无法再修改）。

```solidity
contract Token {
    uint immutable decimals;
    constructor(uint _decimals) public {
        decimals = _decimals;
    }
}
```

### 函数

函数形式：

```solidity
function <func_name>(<param-type> <param-name>) <visiable> <state-variable> [returns (<return-type [res-name]>)]
```

#### 返回值

```solidity
function add(uint x, uint y) public returns (uint res) {
    res = x + y; // return x + y;
}
```

返回值可以仅指定类型，省略名称。

支持多个返回值：

```solidity
function foo() public returns (uint, bool) {
    return (1, true);
}
```

#### 状态可变性

描述如何修改区块链的状态。

- `view`：修饰视图函数，只读状态。
- `pure`：修饰纯函数，不可读状态。
- `payable`：可以接受以太币。

##### 视图函数

视图函数不需要提交交易，也不需要花费交易费，调用试图函数时，只需要当前链接的节点执行。但是如果视图函数在会修改状态的函数中调用，则试图函数会消耗 gas。

交易需要全网节点共识之后才会确认，状态修改才会生效。

##### 纯函数

纯函数仅做计算。

```solidity
contract Token {
    function cal(uint x) public pure return (uint) {
        return x * x;
    }
}
```

### 关注 gas

当确定运算不会发生溢出时，使用 `unchecked` 有更高的 gas 效率。

