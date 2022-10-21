![Hazel](./assets/Hazel_Logo_Text_Light_Square.png "Hazel")

# 任务

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

## 事件系统

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

## 添加GLAD

> GLFW 提供 OpenGL, OpenGL ES 和 Vulkan 的桌面开发环境，是一个跨平台的开源库。利用它可以创建窗口、处理键盘鼠标等事件。windows下它使用win32 api创建窗口，WGL关联OPENGL上下文。Linux 下使用 X11创建窗口，GLX关联OPENGL上下文。MAC下使用cocoa创建窗口，AGL关联OPENGL上下文。
>
> GLAD 的功能比较专一，专门加载OpenGL的函数指针。查看源码有大量看起来重复的代码，但是是很必要的，因为每一个函数都要重复相同的搜寻过程。都是些dirty work,dirty code。

## 添加UI界面

封装ImGUI

设置输入回调事件

![image-20221005104250875](./assets/image-20221005104250875.png)

![image-20221005104300633](./assets/image-20221005104300633.png)

## 输入轮询

在Input类写一些轮询输入的接口

在windowsInput写windows输入轮询

![image-20221005162848531](./assets/image-20221005162848531.png)

定义 按键/鼠标 编码

![image-20221005164325027](./assets/image-20221005164325027.png)

![image-20221005164311713](./assets/image-20221005164311713.png)

使用事件系统给按键添加回调

## 添加glm

## imgui吸附界面

## 渲染

### 抽象渲染上下文

![image-20221007162203084](./assets/image-20221007162203084.png)

![image-20221007162211999](./assets/image-20221007162211999.png)

为以后可能添加的directX等留空

### 绘制三角形

>  glEnableVertexAttribArray(no)
>
> no是一个数字，比如6，这个数字就表示某个顶点属性，或者表示其编号，因为VAO可以看成一个数组，这个数字也可以看成这个数组的索引，它对应的应该是glsl中的layout (location = 6) 这段代码。
>
> 我们可以认为VAO这个数组中的每个元素都有两个状态，enabled和disabled，默认都是disabled，此时 VertexShader去读取对应的值时，读到的将是一个默认值（而不是数组中的值）
>
> glEnableVertexAttribArray的作用就是将该状态置为enabled，此时着色器读取值才能生效
>
> glVertexAttribPointer 
>
> 我们可以看到这个参数基本上是顶点格式信息，同时第一个参数是一个索引，这个索引和上面的索引应该是同一个意思，表示这个顶点格式信息（顶点属性）要存放在VAO的哪个元素中                       

![image-20221007201031966](./assets/image-20221007201031966.png)

![image-20221007201045135](./assets/image-20221007201045135.png)

### shader

![image-20221008120223540](./assets/image-20221008120223540.png)

顶点着色器和片段着色器

![image-20221008120542913](./assets/image-20221008120542913.png)

![image-20221008120923431](./assets/image-20221008120923431.png)

- 将顶点传入顶点着色器
- 根据顶点位置计算颜色

### 抽象渲染API

使用工厂模式，根据不同的RendererAPI创建对应的buffer

![image-20221008151248521](./assets/image-20221008151248521.png)

![image-20221008151258415](./assets/image-20221008151258415.png)

### 顶点buffer层

![image-20221009161134290](./assets/image-20221009161146379.png)

![image-20221009161222792](./assets/image-20221009161222792.png)

用于对顶点buffer的统一数据理解和分解

### 顶点数组

拥有顶点buffer和索引buffer的引用

![image-20221009153852300](./assets/image-20221009153852300.png)

方便统一管理

![image-20221009162541438](./assets/image-20221009162541438.png)

![image-20221009162549379](./assets/image-20221009162549379.png)

![image-20221009162610368](./assets/image-20221009162610368.png)

![image-20221009162629128](./assets/image-20221009162629128.png)

### 添加渲染API

用RendererAPI和工厂方法封装OpenGL DirectX等

用RendererCommand封装RendererAPI的操作

### 添加正交相机

![image-20221010192145444](./assets/image-20221010192145444.png)

根据相机的位置 计算vp矩阵

在场景开始时获取到vp矩阵

![image-20221010192430647](./assets/image-20221010192430647.png)

在shader中调用这个vp矩阵

![image-20221010192615983](./assets/image-20221010192615983.png)

## Timestep

游戏中要统一运行速度

![image-20221011091852066](./assets/image-20221011091852066.png)

![image-20221011092042831](./assets/image-20221011092042831.png)

![image-20221011092526563](./assets/image-20221011092526563.png)

## 创建Shader工厂

将之前的OpenGLShader转移到Shader工厂的子类下

## 添加Texture

加载纹理

![image-20221011153842617](./assets/image-20221011153842617.png)

gl传送纹理到gpu

![image-20221011155617759](./assets/image-20221011155617759.png)

通过vs传入纹素然后通过fs上色![image-20221011160628484](./assets/image-20221011160628484.png)

## 纹理blend

![image-20221011163730798](./assets/image-20221011163730798.png)

![image-20221011183956711](./assets/image-20221011183956711.png)

## 独立出shader文件

![image-20221011210158923](./assets/image-20221011210158923.png)

使用 fstream读取文件

![image-20221011210339682](./assets/image-20221011210339682.png)

规定每个shader中的 vertex 和fragment 都是用 #type 分割的

所以字符串处理把对应的shader存到unordered_map中

![image-20221011210123407](./assets/image-20221011210123407.png)

使用gl编译ma中的shader

![image-20221011210519658](./assets/image-20221011210519658.png)

使用：

![image-20221011210808354](./assets/image-20221011210808354.png)

## 添加ShaderLibrary记录拥有的shader

![image-20221011213055046](./assets/image-20221011213055046.png)

## 相机Controller

![image-20221012115414526](./assets/image-20221012115414526.png)

```c++
namespace Hazel {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(HZ_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(HZ_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		//...
		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
```

## 2D Renderer

![image-20221013195538832](./assets/image-20221013195538832.png)

开启深度测试添加几个方形

## 调试工具

### 计算各个操作的耗时

使用chrono计算各个操作的耗时

![image-20221014102223097](./assets/image-20221014102223097.png)

![image-20221014102207737](./assets/image-20221014102207737.png)

渲染到imgui上

![image-20221014102310858](./assets/image-20221014102310858.png)

将上述代码封装在Instrumentor中

## 计算图形的旋转

![image-20221014174335894](./assets/image-20221014174335894.png)

## 批处理

![image-20221014202457901](./assets/image-20221014202457901.png)

![image-20221014202223441](./assets/image-20221014202223441.png)

将需要的信息存到buffer 依次赋值![image-20221014203044235](./assets/image-20221014203044235.png)

在一次drawcall中全部处理

![image-20221014203220697](./assets/image-20221014203220697.png)

添加对材质的批处理

![image-20221015154806865](./assets/image-20221015154806865.png)

添加对旋转图形的drawcall

添加对drawcall的状态的检测

![image-20221015164956033](./assets/image-20221015164956033.png)

![image-20221015165007109](./assets/image-20221015165007109.png)

## 添加可扩展空间

![image-20221015193016259](./assets/image-20221015193016259.png)

## 封装opengl的帧缓冲

## 编辑器界面

创建了一个新的editor项目，把sandbox的文件做了些修改

### 添加视口

![image-20221016161009198](./assets/image-20221016161009198.png)

从帧缓冲中获取颜色 输出到视口中

### 处理视口控制

![image-20221016163934454](./assets/image-20221016163934454.png)

根据对视口是否聚焦和悬停决定是否允许对其操作

![image-20221016164135958](./assets/image-20221016164135958.png)

## ECS

将相同的entity存到数组中，统一绘制

![image-20221016175641832](./assets/image-20221016175641832.png)

### entity

entity是component的集合

使用entity在scene的注册表中增删改查

![image-20221017102546297](./assets/image-20221017102546297.png)

![image-20221017102809779](./assets/image-20221017102809779.png)

### 添加camera

区分主相机和其他相机

![image-20221017163538054](./assets/image-20221017163538054.png)

添加场景相机用来计算矩阵变换，支持调整大小

## 添加细节面板

点击entity创建细节信息

![image-20221018204338394](./assets/image-20221018204338394.png)

![image-20221018204405162](./assets/image-20221018204405162.png)

# 添加保存系统

对entity序列化 和 反序列化

用于save open

![image-20221021161656131](./assets/image-20221021161656131.png)
