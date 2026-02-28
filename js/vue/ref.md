`ref` 转换出的对象需要使用 `.value`，底层调用 `reactive`。

```vue
<template>
	<div>
        {{ name }}
    </div>
</template>

<script lang="ts" setup>
    import {ref} from 'vue'
    let name = ref(name)
    function changeName() {
        name.value = "111"
    }
</script>
```

`reactive` 只能定义对象类型。

对于 `ref` 可以使用 `volar` 插件自动添加 `.value`。

`reactive` 重新分配一个新对象，会失去响应式，可以使用 `Object.assign` 去整体替换。

```vue
<template>
    <div>
        <div>name: {{ name }}</div>
        <div>age: {{ age }}</div>
        <div>tel: {{ tel }}</div>
        <button @click="changeName">changeName</button>
        <button @click="changeAge">changeAge</button>
        <button @click="showTel">showTel</button>
        <hr>
        <div>book: {{ book.name }}</div>
        <div>book: {{ book.no }}</div>
        <button @click="incrBookNo">incrBookNo</button>
    </div>
</template>

<script lang="ts" setup>
import { ref } from 'vue'
import { reactive } from 'vue'
let name = ref("111")
let age = 111
let tel = 1100
let flag = true
let book = reactive({
    name: "xxx",
    no: 1,
})
function changeName() {
    if (flag == true) {
        name.value = "222"
        flag = false
    } else {
        name.value = "111"
        flag = true
    }
}
function changeAge() {
    age = 222
}
function showTel() {
    alert(tel)
}
function incrBookNo() {
    book.no += 1
}
</script>
```

reactive 不需要使用 `.value`。

toRef 和 toRefs

`ref` 可以调用基本数据类型，也可以调用对用数据类型，reactive 只能定义对象数据类型响应式数据类型。

`ref` 定义对象数据类型响应式数据类型需要 `.value`。





### 计算属性

competed

### v-model

```vue
<template>

</template>
```





### watch

监视数据变化

- ref
- reactive
- 函数返回一个值
- 包含上述内容的数组

