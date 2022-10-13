#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;

		uint32_t m_VertexBufferIndex = 0;
		// 顶点缓冲区不一定只存储顶点位置。它们还用于存储顶点法线，UV坐标等。所以有多个
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}