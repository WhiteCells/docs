**String Operations**:

- `GET key`: 返回类型为 `REDIS_REPLY_STRING`，表示返回键 `key` 对应的字符串值。
- `SET key value`: 返回类型为 `REDIS_REPLY_STATUS`，表示返回一个状态回复，通常为 "OK"。

**Hash Operations**:

- `HGET key field`: 返回类型为 `REDIS_REPLY_STRING`，表示返回哈希表 `key` 中字段 `field` 的值。
- `HSET key field value`: 返回类型为 `REDIS_REPLY_INTEGER`，表示返回一个整数，通常为 1 表示新字段被设置，0 表示字段已经存在并更新。

**List Operations**:

- `LPUSH key value`: 返回类型为 `REDIS_REPLY_INTEGER`，表示返回一个整数，表示列表 `key` 的长度。
- `RPOP key`: 返回类型为 `REDIS_REPLY_STRING`，表示返回并移除列表 `key` 的最后一个元素。

**Set Operations**:

- `SADD key member`: 返回类型为 `REDIS_REPLY_INTEGER`，表示返回一个整数，表示被添加到集合 `key` 的新元素数量。
- `SMEMBERS key`: 返回类型为 `REDIS_REPLY_ARRAY`，表示返回一个数组，包含集合 `key` 中的所有成员。

**Sorted Set Operations**:

- `ZADD key score member`: 返回类型为 `REDIS_REPLY_INTEGER`，表示返回一个整数，表示被成功添加到有序集合 `key` 的新成员数量。
- `ZRANGE key start stop`: 返回类型为 `REDIS_REPLY_ARRAY`，表示返回一个数组，包含有序集合 `key` 中指定范围内的成员。

**Pub/Sub Operations**:

- `PUBLISH channel message`: 返回类型为 `REDIS_REPLY_INTEGER`，表示返回一个整数，表示消息被发送到指定频道的订阅者数量。

**Transaction Operations**:

- Redis 事务通过 `MULTI`、`EXEC` 等命令进行操作，`EXEC` 命令执行后返回类型为 `REDIS_REPLY_ARRAY`，表示返回一个数组，包含事务中各个命令的执行结果。



`DEL` 操作用于删除 Redis 中的一个或多个键。其返回值类型为 `REDIS_REPLY_INTEGER`，表示返回一个整数，该整数表示被删除的键的数量。