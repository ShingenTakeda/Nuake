#pragma once
#include "src/Core/Core.h"
#include "src/Rendering/AABB.h"
#include "src/Resource/Resource.h"
#include "src/Resource/Serializable.h"
#include "src/Rendering/Vertex.h"

namespace Nuake
{
	class VertexBuffer;
	class VertexArray;
	class Material;
	struct Vertex;
	class Shader;

	struct BoneVertexWeight
	{
		uint32_t VertexID;
		float Weight;
	};

	struct Bone
	{
		std::string Name;
		Matrix4 Offset;
		std::vector<BoneVertexWeight> VertexWeights;
	};

	class SkinnedMesh : ISerializable, Resource
	{
	public:
		SkinnedMesh() = default;
		~SkinnedMesh() = default;

		void AddSurface(std::vector<SkinnedVertex> vertices, std::vector<uint32_t> indices, std::vector<Bone> bones);
		std::vector<SkinnedVertex>& GetVertices();
		std::vector<uint32_t>& GetIndices();
		std::vector<Bone>& GetBones();

		Ref<Material> GetMaterial() inline const;
		void SetMaterial(Ref<Material> material);

		void Bind() const;
		void Draw(Shader* shader, bool bindMaterial = true);
		void DebugDraw();

		inline AABB GetAABB() const { return m_AABB; }

		json Serialize() override;
		bool Deserialize(const json& j) override;

	private:
		Ref<Material> m_Material = nullptr;
		std::vector<uint32_t> m_Indices;
		std::vector<SkinnedVertex> m_Vertices;
		std::vector<Bone> m_Bones;

		Scope<VertexBuffer> m_VertexBuffer;
		Scope<VertexArray> m_VertexArray;
		Scope<VertexBuffer> m_ElementBuffer;

		void SetupMesh();

		AABB m_AABB;
		void CalculateAABB();
	};
}