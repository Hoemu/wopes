# aLog 模块文档

`aLog` 开发日志

### 功能日志

- 宏功能接口（已完成）
- 控制台输出（已完成）
- 输出日志文件（已完成）
- 文件设置接口（已完成）
- 线程安全（已完成）


单文件写入数据量如下：

 性能测试 | 测试值 |
| ----------- | ----------- |
| 写入速度（debug模式） | 13w/s~15w/s |
| 写入速度（release模式）| 30w/s |
| ns/op（release模式）| 4.2k ns/op |

如下图写入速度测试（release模式）：

![图片 speed ](../img/test-Release.png)

如下图 `ns/op` 测试（release模式）
![图片 ns/op](../img/test-Release-ns_op.png)

注：当使用多个文件同时写入，会导致性能下降