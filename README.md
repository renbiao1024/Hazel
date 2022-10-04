# Hazel Engine


## 任务

- 入口
- 应用层
- 窗口层
  - 输入
  - 事件
- 渲染器
- 渲染API抽象
- 调试支持
- 内存系统
- ECS
- 物理
- 文件IO，VFS
- 构建系统

## 入口

将引擎作为dll给application动态加载使用



通过预编译头，自动决定宏在不同文件中的含义

```
#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only supports Windows!
#endif
```



> git reset .
>
> git add .
>
> git status
>
> git commit -m "...."
>
> git push origin main

## Log

接入spdlog

使用宏封装spdlog方法，方便使用

```

//core log macros
#define HZ_CORE_TRACE(...)	::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)	::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)	::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)	::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HZ_CORE_FATAL(...)	::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client log macro
#define HZ_TRACE(...)	::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)		::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)		::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)	::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HZ_FATAL(...)	::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)
```

## premake

使用premake5对项目预配置

![image-20221001175412356](./assets/image-20221001175412356.png)

## Event System

![image-20221002165823928](./assets/image-20221002165823928.png)

![image-20221002215339453](./assets/image-20221002215339453.png)

<< 重载 返回ToString()

![image-20221002220213227](./assets/image-20221002220213227.png)

![image-20221002220108832](./assets/image-20221002220108832.png)

## 预编译头

使用预编译头节省编译时间

![image-20221002225156392](./assets/image-20221002225156392.png)

![image-20221002225216348](./assets/image-20221002225216348.png)

## 窗口

使用GLFW创建窗口

创建一个window抽象类，给不同平台创建窗口使用

![image-20221003122920973](./assets/image-20221003122920973.png)

## 窗口事件

![image-20221003152753903](./assets/image-20221003152753903.png)

在OnUpdate中拉取事件

![image-20221003160700483](./assets/image-20221003160700483.png)

设置glfw 回调函数

![image-20221003161112566](./assets/image-20221003161112566.png)

![image-20221003161400482](./assets/image-20221003161400482.png)

![image-20221003160913280](./assets/image-20221003160913280.png)

![image-20221003161255251](./assets/image-20221003161255251.png)

事件调度器绑定回调函数

![image-20221003160920476](./assets/image-20221003160920476.png)

## 层/层栈

![image-20221004093814740](./assets/image-20221004093814740.png)
