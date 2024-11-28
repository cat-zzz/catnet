## 日志模块

### 1  日志模块概述

用于格式化输出程序日志，方便从日志中定位程序运行过程中出现的问题。

日志模块类似于Log4j风格。

日志模块有如下几个主要类：

1. `class LogLevel`：日志级别，例如常见的`DEBUG/INFO/WARN/ERROR/FATAL`等级别。日志模块可以通过指定级别实现只输出某个级别以上的日志，并提供将日志级别与文本之间的互相转化。

2. `class Logger`：日志器，定义日志级别，设置日志输出目标，设置日志输出格式。

3. `class LogEvent`：日志事件，保存日志信息，例如该日志级别、线程号、文件名行号等。`LogEvent`是一次性的，一个日志事件对应一条日志。`LogEvent`同时包含了`Logger`指针。

4. `class LogEventWrap `：日志事件包装器，`LogEventWrap`在析构时会调用日志器的`log()`方法将日志事件进行输出。

5. `class LogFormatter`：日志格式化，与log4cpp的`PatternLayout`对应。该类可以在创建时指定日志输出格式。通过`format()`方法将日志时间格式化为字符串。

	`LogFormatter::formatter()`方法的形参包含一个流对象。该流对象即是日志事件的输出地。

6. `class LogAppender`：日志输出目标，用于将一个日志事件输出到`LogAppender`对应的输出地。该类是一个抽象类，需要继承该类以指定一个具体的输出地。



### 2 LogEvent

主要包括以下成员变量

```c++
const char* m_file = nullptr;   	//文件名
int32_t m_line = 0;             	//行号
uint32_t m_elapse = 0;          	//程序启动开始到现在的毫秒数
uint32_t m_thieadId = 0;        	//线程id
uint32_t m_fiberId = 0;         	//协程id
uint64_t m_time;                	//时间戳
std::string m_threadName;       	//线程名称
std::stringstream m_ss;         	//日志内容流
std::shared_ptr<Logger> m_logger;   //日志器
LogLevel::Level m_level;        	//日志等级
```

`LogEvent`的构造函数将初始化所有成员变量，即使最后输出的日志可能不包括某些变量，因为此时我们并不知道最后需要输出什么。



### 3 LogFormatter



### 疑问

仍然不理解`LogEventWrap`的作用，以及相关宏定义的用法。



### 待改进的内容

1. 当前的版本：一条日志只会在一个日志器上输出，所以是否可以实现一条日志能在多个日志器上输出？以及是否有在多个日志器上输出的需求？
2. `LogFormatter::init()`是否有优化的地方？
3. `LogAppender`是否可以不为抽象类？具体的输出地是一个流对象，不管是标准输出还是文件，对应的都是一个流对象。是否可以用一个成员变量存储这个流对象？我们在创建`LogAppender`时，同时传入一个流对象给`LogAppender`。
4. 代码全部采用C++17标准。