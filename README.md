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

