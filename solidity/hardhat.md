

### Hardhat 框架

```sh
mkdir project
cd project
npm init
npm install --save-dev hardhat # 将 hardhat 作为开发依赖安装
npx hardhat init # 选择 Create a JavaScript project
```

#### 项目结构

- `contracts`：为智能合约目录
- `scripts`：部署脚本文件
- `tests`：智能合约测试用例文件夹
- `hardhat.config.js`：配置文件，配置 `hardhat` 连接的网络及编译选项

#### 使用第三方库

```sh
npm install @openzeppelin/contracts --save-dev
```

安装成功后在智能合约文件中 `import` 即可。

```solidity
import "@openzeppelin/contracts/token/ERC20.sol"
```

#### 编译

```sh
npx hardhat compile

npx hardhat clean # 清除缓存
```

编译成功后，会在 `artifacts/contract` 目录下生成 `<.sol-file>.json`（包含智能合约 `abi`，字节码（`bytecode`）等）和 build-info

`abi`（Application Binary Interface）信息，其中包括合约的函数、事件等接口信息。

`bytecode` 是部署合约所需要的字节码（创建时字节码），部署合约时，把字节码作为交易的输入数据发送到链上。

#### 测试

 使用 `Hardhat` 内置的网络，使用 `ethers.js` 与前面的合约进行交互，并使用 `Mocha` 作为测试运行器。

在 `test` 目录下创建相应的测试文件 `.js`。

```sh
npx hardhat test
```

#### 部署

可以在 `scripts` 文件夹中新建 `deploy.js` 编写部署脚本：

```js
const { ethers } = require("hardhat");

async function main() {

    const Counter = await ethers.getContractFactory("Counter");
    const counter = await Counter.deploy();
    await counter.deployed();

    console.log("Counter address:", counter.address);
}

main();
```

使用命令部署：

```sh
npx hardhat run scripts/deploy.js
```

在运行任务时指定连接的特定 EVM 网络，可以使用 `--network` 参数：

```sh
npx hardhat run scripts/deploy.js --network <network-name>
```

`network-name` 需要在 `hardhat.config.js` 中进行配置：

```js
require("@nomicfoundation/hardhat-toolbox");

// 填入自己的私钥或助记词，
const PRIVATE_KEY1 = "0x.... YOUR PRIVATE KEY1";
const PRIVATE_KEY2 = "0x....  YOUR PRIVATE KEY1";
const Mnemonic = "YOUR Mnemonic";


module.exports = {
  solidity: "0.8.9", // solidity的编译版本
  networks: {
    goerli: {
      url: "https://eth-goerli.api.onfinality.io/public",
      accounts: [PRIVATE_KEY1,PRIVATE_KEY2],
      chainId: 5,
    }, // 以太坊测试网
    
     mumbai: {
      url: "https://endpoints.omniatech.io/v1/matic/mumbai/public",
      accounts: {
        mnemonic: Mnemonic,
      },
      chainId: 80001,
    }, // Polygon 测试网
  }
};
```

`goerli` 及 `mumbai` 就是 `network-name`。

https://chainlist.org/  查找每个网络的节点 `url` 及 `chainID`。

在网络配置中需要提交交易账号，可以通过私钥或助记词进行配置，配置的账号，在 `hardhat` 脚本中调用 `getSingers` 即可获得。

一个私钥对应一个 Singer，助记词则对应无数个 Singer。

使用 https://chaintool.tech/generateWallet/evmWallet 可以生成账号。

在 Goerli 上进行部署，需要将 Goerli-ETH 发送到将要进行部署的地址中。

可以从水龙头免费获取测试币。

#### 代码开源验证

智能合约开源会增加透明度和可靠性，在 `hardhat-toolbox` 工具箱里，包含了 `hardhat-etherscan` 插件用于验证已经部署到区块链网络上的智能合约代码与源代码是否匹配。

```sh
npx hardhat verify <deployed-contract-address> --network <network-name>
```

#### 插件

https://hardhat.org/hardhat-runner/plugins



#### 文档

https://learnblockchain.cn/docs/hardhat/getting-started/



#### 连接钱包或 Dapp 到 Hardhat 网络

Hardhat 在启动时，默认会启动一个 Hardhat Network 的内存实例，可以独立的方式运行 Hardhat Network，以便外部客户连接它。

```sh
$ npx hardhat node
Started HTTP and WebSocket JSON-RPC server at http://127.0.0.1:8545/
```

将钱包或应用连接到 `http://127.0.0.1:8545/` 就可以使用它。

如需在该网络上运行一个部署脚本，只需要使用 `--network localhost` 来运行脚本。











