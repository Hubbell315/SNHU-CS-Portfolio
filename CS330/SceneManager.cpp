///////////////////////////////////////////////////////////////////////////////
// scenemanager.cpp
// manage the preparing and rendering of 3D scenes - textures, materials, lighting
//
// AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
// Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
// Modified by: Tyler Hubbell
///////////////////////////////////////////////////////////////////////////////

#include "SceneManager.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include <glm/gtx/transform.hpp>

namespace
{
	const char* g_ModelName = "model";
	const char* g_ColorValueName = "objectColor";
	const char* g_TextureValueName = "objectTexture";
	const char* g_UseTextureName = "bUseTexture";
	const char* g_UseLightingName = "bUseLighting";
}

/***********************************************************
 * SceneManager()
 ***********************************************************/
SceneManager::SceneManager(ShaderManager* pShaderManager)
{
	m_pShaderManager = pShaderManager;
	m_basicMeshes = new ShapeMeshes();

	for (int i = 0; i < 16; i++)
	{
		m_textureIDs[i].tag = "/0";
		m_textureIDs[i].ID = -1;
	}

	m_loadedTextures = 0;
}

/***********************************************************
 * ~SceneManager()
 ***********************************************************/
SceneManager::~SceneManager()
{
	m_pShaderManager = NULL;
	delete m_basicMeshes;
	m_basicMeshes = NULL;
}

/***********************************************************
 * CreateGLTexture()
 ***********************************************************/
bool SceneManager::CreateGLTexture(const char* filename, std::string tag)
{
	int width = 0;
	int height = 0;
	int colorChannels = 0;
	GLuint textureID = 0;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* image = stbi_load(
		filename,
		&width,
		&height,
		&colorChannels,
		0
	);

	if (image)
	{
		std::cout << "Successfully loaded image:" << filename
			<< ", width:" << width
			<< ", height:" << height
			<< ", channels:" << colorChannels << std::endl;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (colorChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		}
		else if (colorChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		}
		else
		{
			std::cout << "Not implemented to handle image with " << colorChannels << " channels" << std::endl;
			return false;
		}

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_textureIDs[m_loadedTextures].ID = textureID;
		m_textureIDs[m_loadedTextures].tag = tag;
		m_loadedTextures++;

		return true;
	}

	std::cout << "Could not load image:" << filename << std::endl;
	return false;
}

/***********************************************************
 * BindGLTextures()
 ***********************************************************/
void SceneManager::BindGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textureIDs[i].ID);
	}
}

/***********************************************************
 * DestroyGLTextures()
 ***********************************************************/
void SceneManager::DestroyGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		glDeleteTextures(1, &m_textureIDs[i].ID);
	}
}

/***********************************************************
 * FindTextureID()
 ***********************************************************/
int SceneManager::FindTextureID(std::string tag)
{
	int textureID = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureID = m_textureIDs[index].ID;
			bFound = true;
		}
		else
		{
			index++;
		}
	}

	return textureID;
}

/***********************************************************
 * FindTextureSlot()
 ***********************************************************/
int SceneManager::FindTextureSlot(std::string tag)
{
	int textureSlot = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureSlot = index;
			bFound = true;
		}
		else
		{
			index++;
		}
	}

	return textureSlot;
}

/***********************************************************
 * FindMaterial()
 ***********************************************************/
bool SceneManager::FindMaterial(std::string tag, OBJECT_MATERIAL& material)
{
	if (m_objectMaterials.size() == 0)
	{
		return false;
	}

	unsigned int index = 0;
	bool bFound = false;

	while ((index < m_objectMaterials.size()) && (bFound == false))
	{
		if (m_objectMaterials[index].tag.compare(tag) == 0)
		{
			bFound = true;
			material.diffuseColor = m_objectMaterials[index].diffuseColor;
			material.specularColor = m_objectMaterials[index].specularColor;
			material.shininess = m_objectMaterials[index].shininess;
		}
		else
		{
			index++;
		}
	}

	return bFound;
}

/***********************************************************
 * SetTransformations()
 ***********************************************************/
void SceneManager::SetTransformations(
	glm::vec3 scaleXYZ,
	float XrotationDegrees,
	float YrotationDegrees,
	float ZrotationDegrees,
	glm::vec3 positionXYZ,
	glm::vec3 offset)
{
	glm::mat4 model;
	glm::mat4 scale;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 translation;

	scale = glm::scale(scaleXYZ);

	rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

	translation = glm::translate(positionXYZ + offset);

	model = translation * rotationZ * rotationY * rotationX * scale;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setMat4Value(g_ModelName, model);
	}
}

/***********************************************************
 * SetShaderColor()
 ***********************************************************/
void SceneManager::SetShaderColor(
	float redColorValue,
	float greenColorValue,
	float blueColorValue,
	float alphaValue)
{
	glm::vec4 currentColor;

	currentColor.r = redColorValue;
	currentColor.g = greenColorValue;
	currentColor.b = blueColorValue;
	currentColor.a = alphaValue;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, false);
		m_pShaderManager->setVec4Value(g_ColorValueName, currentColor);
	}
}

/***********************************************************
 * SetShaderTexture()
 ***********************************************************/
void SceneManager::SetShaderTexture(std::string textureTag)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, true);

		int textureID = -1;
		textureID = FindTextureSlot(textureTag);
		m_pShaderManager->setSampler2DValue(g_TextureValueName, textureID);
	}
}

/***********************************************************
 * SetTextureUVScale()
 ***********************************************************/
void SceneManager::SetTextureUVScale(float u, float v)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setVec2Value("UVscale", glm::vec2(u, v));
	}
}

/***********************************************************
 * SetShaderMaterial()
 ***********************************************************/
void SceneManager::SetShaderMaterial(std::string materialTag)
{
	if (m_objectMaterials.size() > 0)
	{
		OBJECT_MATERIAL material;
		bool bReturn = false;

		bReturn = FindMaterial(materialTag, material);
		if (bReturn == true)
		{
			m_pShaderManager->setVec3Value("material.diffuseColor", material.diffuseColor);
			m_pShaderManager->setVec3Value("material.specularColor", material.specularColor);
			m_pShaderManager->setFloatValue("material.shininess", material.shininess);
		}
	}
}

/***********************************************************
 * LoadSceneTextures()
 ***********************************************************/
void SceneManager::LoadSceneTextures()
{
	CreateGLTexture("textures/Building_Concrete.jpg", "concreteTexture");
	CreateGLTexture("textures/Freight_Car_Metal.jpg", "freightMetalTexture");
	CreateGLTexture("textures/Freight_Car_Second.jpg", "freightMetalSecondaryTexture");
	CreateGLTexture("textures/Freight_Car_3.jpg", "freightMetalThirdTexture");
	CreateGLTexture("textures/Rock_Ground.jpg", "groundTexture");
	CreateGLTexture("textures/Silo.jpg", "siloTexture");
	CreateGLTexture("textures/Building.jpg", "mainBuilding");

	BindGLTextures();
}

/***********************************************************
 * DefineObjectMaterials()
 ***********************************************************/
void SceneManager::DefineObjectMaterials()
{
	OBJECT_MATERIAL groundMaterial;
	groundMaterial.tag = "groundMaterial";
	groundMaterial.diffuseColor = glm::vec3(0.55f, 0.55f, 0.55f);
	groundMaterial.specularColor = glm::vec3(0.08f, 0.08f, 0.08f);
	groundMaterial.shininess = 6.0f;
	m_objectMaterials.push_back(groundMaterial);

	OBJECT_MATERIAL metalMaterial;
	metalMaterial.tag = "metalMaterial";
	metalMaterial.diffuseColor = glm::vec3(0.60f, 0.60f, 0.60f);
	metalMaterial.specularColor = glm::vec3(0.25f, 0.25f, 0.25f);
	metalMaterial.shininess = 18.0f;
	m_objectMaterials.push_back(metalMaterial);

	OBJECT_MATERIAL woodMaterial;
	woodMaterial.tag = "woodMaterial";
	woodMaterial.diffuseColor = glm::vec3(0.38f, 0.26f, 0.16f);
	woodMaterial.specularColor = glm::vec3(0.06f, 0.06f, 0.06f);
	woodMaterial.shininess = 4.0f;
	m_objectMaterials.push_back(woodMaterial);

	OBJECT_MATERIAL buildingMaterial;
	buildingMaterial.tag = "buildingMaterial";
	buildingMaterial.diffuseColor = glm::vec3(0.62f, 0.62f, 0.62f);
	buildingMaterial.specularColor = glm::vec3(0.10f, 0.10f, 0.10f);
	buildingMaterial.shininess = 8.0f;
	m_objectMaterials.push_back(buildingMaterial);
}

/***********************************************************
 * SetupSceneLights()
 ***********************************************************/
void SceneManager::SetupSceneLights()
{
	m_pShaderManager->setBoolValue(g_UseLightingName, true);

	m_pShaderManager->setVec3Value("directionalLight.direction", -0.3f, -1.0f, -0.2f);
	m_pShaderManager->setVec3Value("directionalLight.ambient", 0.18f, 0.18f, 0.20f);
	m_pShaderManager->setVec3Value("directionalLight.diffuse", 0.68f, 0.68f, 0.70f);
	m_pShaderManager->setVec3Value("directionalLight.specular", 0.30f, 0.30f, 0.32f);
	m_pShaderManager->setBoolValue("directionalLight.bActive", true);

	m_pShaderManager->setVec3Value("pointLights[0].position", 2.0f, 18.0f, 14.0f);
	m_pShaderManager->setVec3Value("pointLights[0].ambient", 0.12f, 0.12f, 0.13f);
	m_pShaderManager->setVec3Value("pointLights[0].diffuse", 0.68f, 0.68f, 0.70f);
	m_pShaderManager->setVec3Value("pointLights[0].specular", 0.30f, 0.30f, 0.32f);
	m_pShaderManager->setBoolValue("pointLights[0].bActive", true);

	m_pShaderManager->setVec3Value("pointLights[1].position", -24.0f, 10.0f, 26.0f);
	m_pShaderManager->setVec3Value("pointLights[1].ambient", 0.06f, 0.07f, 0.08f);
	m_pShaderManager->setVec3Value("pointLights[1].diffuse", 0.22f, 0.24f, 0.28f);
	m_pShaderManager->setVec3Value("pointLights[1].specular", 0.06f, 0.07f, 0.08f);
	m_pShaderManager->setBoolValue("pointLights[1].bActive", true);

	m_pShaderManager->setVec3Value("pointLights[2].position", 18.0f, 8.0f, -18.0f);
	m_pShaderManager->setVec3Value("pointLights[2].ambient", 0.05f, 0.04f, 0.03f);
	m_pShaderManager->setVec3Value("pointLights[2].diffuse", 0.18f, 0.16f, 0.14f);
	m_pShaderManager->setVec3Value("pointLights[2].specular", 0.06f, 0.05f, 0.04f);
	m_pShaderManager->setBoolValue("pointLights[2].bActive", true);

	m_pShaderManager->setBoolValue("pointLights[3].bActive", false);
}

/***********************************************************
 * PrepareScene()
 ***********************************************************/
void SceneManager::PrepareScene()
{
	LoadSceneTextures();
	DefineObjectMaterials();
	SetupSceneLights();

	m_basicMeshes->LoadPlaneMesh();
	m_basicMeshes->LoadBoxMesh();
	m_basicMeshes->LoadCylinderMesh();
	m_basicMeshes->LoadTorusMesh(0.15f);
}

/***********************************************************
 * RenderScene()
 *
 * Builds and renders the complete railroad yard scene by
 * combining reusable primitive meshes, shared materials,
 * textures, and object transformations.
 ***********************************************************/
void SceneManager::RenderScene()
{
	// transformation values reused during scene construction
	glm::vec3 scaleXYZ;
	float XrotationDegrees = 0.0f;
	float YrotationDegrees = 0.0f;
	float ZrotationDegrees = 0.0f;
	glm::vec3 positionXYZ;

	// shared scene layout values used to keep proportions
	// spacing, and placement consistent across the full yard
	const float groundHalfWidth = 46.0f;
	const float groundHalfDepth = 88.0f;

	const float railY = -1.08f;
	const float tieY = -1.22f;

	const float railWidth = 0.08f;
	const float railHeight = 0.06f;
	const float tieHeight = 0.08f;
	const float railGaugeHalf = 0.72f;

	const float firstTrackX = -9.6f;
	const float trackSpacing = 3.2f;
	const int trackCount = 9;
	const float yardTrackLength = 86.0f;
	const float yardTrackCenterZ = 0.0f;

	// Reusable wheel-and-axle assembly to be
	// positioned under locomotives and freight cars
	auto drawWheelSet = [&](float centerX, float axleZ)
		{
			scaleXYZ = glm::vec3(0.42f, 0.42f, 0.14f);
			YrotationDegrees = 90.0f;

			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.03f, 0.03f, 0.03f, 1.0f);

			positionXYZ = glm::vec3(centerX - 0.62f, -0.63f, axleZ);
			SetTransformations(scaleXYZ, 0.0f, YrotationDegrees, 0.0f, positionXYZ);
			m_basicMeshes->DrawTorusMesh();

			positionXYZ = glm::vec3(centerX + 0.62f, -0.63f, axleZ);
			SetTransformations(scaleXYZ, 0.0f, YrotationDegrees, 0.0f, positionXYZ);
			m_basicMeshes->DrawTorusMesh();

			scaleXYZ = glm::vec3(1.24f, 0.05f, 0.05f);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.20f, 0.20f, 0.20f, 1.0f);

			positionXYZ = glm::vec3(centerX, -0.63f, axleZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();
		};

	// Reusable tank car from a frame, cylindrical tank,
	// top hatch and repeated wheel assemblies
	auto drawTankCar = [&](float centerX, float frameCenterZ, bool useTexture, std::string bodyTexture, glm::vec3 solidColor)
		{
			scaleXYZ = glm::vec3(2.4f, 0.18f, 7.2f);
			positionXYZ = glm::vec3(centerX, -0.45f, frameCenterZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");

			if (useTexture)
			{
				SetShaderTexture("freightMetalSecondaryTexture");
				SetTextureUVScale(2.0f, 2.0f);
			}
			else
			{
				SetShaderColor(0.08f, 0.08f, 0.08f, 1.0f);
			}
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(1.55f, 8.4f, 1.55f);
			XrotationDegrees = 90.0f;
			positionXYZ = glm::vec3(centerX, 0.88f, frameCenterZ - 4.2f);
			SetTransformations(scaleXYZ, XrotationDegrees, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");

			if (useTexture)
			{
				SetShaderTexture(bodyTexture);
				SetTextureUVScale(6.0f, 2.0f);
			}
			else
			{
				SetShaderColor(solidColor.r, solidColor.g, solidColor.b, 1.0f);
			}
			m_basicMeshes->DrawCylinderMesh(true, true, true);

			scaleXYZ = glm::vec3(0.35f, 0.25f, 0.35f);
			positionXYZ = glm::vec3(centerX, 1.75f, frameCenterZ + 0.2f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");

			if (useTexture)
			{
				SetShaderTexture("freightMetalSecondaryTexture");
				SetTextureUVScale(1.0f, 1.0f);
			}
			else
			{
				SetShaderColor(0.12f, 0.12f, 0.12f, 1.0f);
			}
			m_basicMeshes->DrawCylinderMesh(true, true, true);

			drawWheelSet(centerX, frameCenterZ + 2.8f);
			drawWheelSet(centerX, frameCenterZ + 1.6f);
			drawWheelSet(centerX, frameCenterZ - 1.6f);
			drawWheelSet(centerX, frameCenterZ - 2.8f);
		};

	// Reusable box car using a simple underframe,
	// textured cargo body, roof, and wheel assemblies
	auto drawBoxCar = [&](float centerX, float carCenterZ, std::string bodyTexture)
		{
			scaleXYZ = glm::vec3(2.55f, 0.22f, 8.8f);
			positionXYZ = glm::vec3(centerX, -0.45f, carCenterZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.28f, 0.22f, 0.14f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.55f, 2.35f, 8.4f);
			positionXYZ = glm::vec3(centerX, 0.95f, carCenterZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("buildingMaterial");
			SetShaderTexture(bodyTexture);
			SetTextureUVScale(2.0f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.65f, 0.16f, 8.55f);
			positionXYZ = glm::vec3(centerX, 2.28f, carCenterZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.82f, 0.82f, 0.80f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(0.12f, 1.75f, 2.85f);
			positionXYZ = glm::vec3(centerX + 1.32f, 0.75f, carCenterZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.12f, 0.12f, 0.12f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(0.10f, 0.08f, 3.05f);
			positionXYZ = glm::vec3(centerX + 1.31f, 1.75f, carCenterZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.20f, 0.20f, 0.20f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			drawWheelSet(centerX, carCenterZ + 2.8f);
			drawWheelSet(centerX, carCenterZ + 1.6f);
			drawWheelSet(centerX, carCenterZ - 1.6f);
			drawWheelSet(centerX, carCenterZ - 2.8f);
		};

	// Lead CSX locomotive from multiple primitive
	// meshes to approximate the body, cab, nose, rails,
	// exhaust details, and wheel assemblies
	auto drawCSXEngine = [&](float centerX, float centerZ)
		{
			scaleXYZ = glm::vec3(2.9f, 0.22f, 11.8f);
			positionXYZ = glm::vec3(centerX, -0.40f, centerZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.16f, 0.16f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(1.55f, 0.70f, 5.4f);
			positionXYZ = glm::vec3(centerX, -0.95f, centerZ);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.10f, 0.10f, 0.10f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.45f, 2.35f, 7.2f);
			positionXYZ = glm::vec3(centerX, 1.10f, centerZ - 0.9f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.08f, 0.20f, 0.42f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.48f, 2.55f, 2.6f);
			positionXYZ = glm::vec3(centerX, 1.35f, centerZ - 4.2f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.07f, 0.17f, 0.36f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(0.42f, 0.12f, 0.42f);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.12f, 0.12f, 0.12f, 1.0f);

			positionXYZ = glm::vec3(centerX - 0.85f, 2.70f, centerZ - 4.2f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawCylinderMesh(true, true, true);

			positionXYZ = glm::vec3(centerX, 2.70f, centerZ - 4.2f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawCylinderMesh(true, true, true);

			positionXYZ = glm::vec3(centerX + 0.85f, 2.70f, centerZ - 4.2f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawCylinderMesh(true, true, true);

			scaleXYZ = glm::vec3(2.10f, 2.10f, 2.10f);
			positionXYZ = glm::vec3(centerX, 1.45f, centerZ + 3.35f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.08f, 0.20f, 0.42f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.20f, 0.18f, 1.85f);
			positionXYZ = glm::vec3(centerX, 2.55f, centerZ + 3.25f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.85f, 0.85f, 0.85f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.00f, 1.45f, 0.90f);
			positionXYZ = glm::vec3(centerX, 1.12f, centerZ + 4.55f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(1.70f, 0.95f, 0.75f);
			positionXYZ = glm::vec3(centerX, 1.85f, centerZ + 4.65f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.15f, 1.85f, 1.55f);
			positionXYZ = glm::vec3(centerX, 1.10f, centerZ + 5.70f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(1.80f, 1.10f, 1.05f);
			positionXYZ = glm::vec3(centerX, 1.80f, centerZ + 6.45f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.00f, 0.85f, 0.85f);
			positionXYZ = glm::vec3(centerX, 0.30f, centerZ + 6.30f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(1.65f, 0.95f, 0.45f);
			positionXYZ = glm::vec3(centerX, 1.10f, centerZ + 7.00f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(1.20f, 0.35f, 0.18f);
			positionXYZ = glm::vec3(centerX, 1.95f, centerZ + 7.18f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.10f, 0.10f, 0.10f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.35f, 0.70f, 0.42f);
			positionXYZ = glm::vec3(centerX, -0.05f, centerZ + 7.45f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.10f, 0.10f, 0.10f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(0.28f, 0.55f, 0.55f);
			positionXYZ = glm::vec3(centerX - 0.95f, -0.05f, centerZ + 7.05f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.10f, 0.10f, 0.10f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			positionXYZ = glm::vec3(centerX + 0.95f, -0.05f, centerZ + 7.05f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(0.42f, 0.30f, 0.40f);
			positionXYZ = glm::vec3(centerX, -0.20f, centerZ + 7.80f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.06f, 0.06f, 0.06f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.52f, 0.14f, 10.8f);
			positionXYZ = glm::vec3(centerX, 0.15f, centerZ + 0.1f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.10f, 0.12f, 2.35f);
			positionXYZ = glm::vec3(centerX, 0.45f, centerZ + 5.95f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.08f, 0.20f, 0.42f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);

			scaleXYZ = glm::vec3(0.05f, 0.55f, 10.6f);
			positionXYZ = glm::vec3(centerX - 1.52f, 0.55f, centerZ + 0.2f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();

			positionXYZ = glm::vec3(centerX + 1.52f, 0.55f, centerZ + 0.2f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(2.0f, 0.05f, 0.05f);
			positionXYZ = glm::vec3(centerX, 0.70f, centerZ + 7.05f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();

			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.12f, 0.18f, 0.24f, 1.0f);

			scaleXYZ = glm::vec3(1.35f, 0.72f, 0.10f);
			positionXYZ = glm::vec3(centerX, 1.80f, centerZ + 4.2f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(0.10f, 0.65f, 0.75f);
			positionXYZ = glm::vec3(centerX + 1.08f, 1.75f, centerZ + 3.05f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(0.10f, 0.65f, 0.75f);
			positionXYZ = glm::vec3(centerX - 1.08f, 1.75f, centerZ + 3.05f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();

			scaleXYZ = glm::vec3(0.08f, 0.95f, 2.2f);
			positionXYZ = glm::vec3(centerX + 1.27f, 1.20f, centerZ - 0.4f);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			SetShaderMaterial("metalMaterial");
			SetShaderColor(0.88f, 0.72f, 0.18f, 1.0f);
			m_basicMeshes->DrawBoxMesh();

			drawWheelSet(centerX, centerZ + 4.25f);
			drawWheelSet(centerX, centerZ + 3.0f);
			drawWheelSet(centerX, centerZ + 1.75f);

			drawWheelSet(centerX, centerZ - 2.4f);
			drawWheelSet(centerX, centerZ - 3.65f);
			drawWheelSet(centerX, centerZ - 4.9f);
		};

	// Textured ground plane that anchors the full scene
	scaleXYZ = glm::vec3(groundHalfWidth, 1.0f, groundHalfDepth);
	positionXYZ = glm::vec3(2.0f, -1.5f, 0.0f);
	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	SetShaderMaterial("groundMaterial");
	SetShaderTexture("groundTexture");
	SetTextureUVScale(14.0f, 20.0f);
	m_basicMeshes->DrawPlaneMesh();

	// Parallel yard tracks using repeated rail and tie geometry
	for (int i = 0; i < trackCount; i++)
	{
		float trackCenterX = firstTrackX + (i * trackSpacing);

		SetShaderMaterial("metalMaterial");
		SetShaderColor(0.22f, 0.22f, 0.22f, 1.0f);

		float currentTrackLength = yardTrackLength;
		float currentTrackCenterZ = yardTrackCenterZ;

		if (i == trackCount - 1)
		{
			currentTrackLength = 122.0f;
			currentTrackCenterZ = -18.0f;
		}

		scaleXYZ = glm::vec3(railWidth, railHeight, currentTrackLength);
		positionXYZ = glm::vec3(trackCenterX - railGaugeHalf, railY, currentTrackCenterZ);
		SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
		m_basicMeshes->DrawBoxMesh();

		positionXYZ = glm::vec3(trackCenterX + railGaugeHalf, railY, currentTrackCenterZ);
		SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
		m_basicMeshes->DrawBoxMesh();

		SetShaderMaterial("woodMaterial");
		SetShaderColor(0.30f, 0.20f, 0.12f, 1.0f);

		float tieStartZ = -42.0f;
		float tieEndZ = 42.0f;

		if (i == trackCount - 1)
		{
			tieStartZ = -78.0f;
			tieEndZ = 42.0f;
		}

		for (float z = tieStartZ; z <= tieEndZ; z += 1.6f)
		{
			scaleXYZ = glm::vec3(1.95f, tieHeight, 0.24f);
			positionXYZ = glm::vec3(trackCenterX, tieY, z);
			SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
			m_basicMeshes->DrawBoxMesh();
		}
	}

	// Mainline tracks to separate active consist from yard tracks
	float mainTrack1X = 26.0f;
	float mainTrack2X = 30.0f;

	float mainTrackStartZ = -78.0f;
	float mainTrackEndZ = 78.0f;

	SetShaderMaterial("metalMaterial");
	SetShaderColor(0.22f, 0.22f, 0.22f, 1.0f);

	float mainTrackCenterZ = (mainTrackStartZ + mainTrackEndZ) * 0.5f;
	float mainTrackLength = fabs(mainTrackEndZ - mainTrackStartZ);

	scaleXYZ = glm::vec3(railWidth, railHeight, mainTrackLength);
	positionXYZ = glm::vec3(mainTrack1X - railGaugeHalf, railY, mainTrackCenterZ);
	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	m_basicMeshes->DrawBoxMesh();

	positionXYZ = glm::vec3(mainTrack1X + railGaugeHalf, railY, mainTrackCenterZ);
	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	m_basicMeshes->DrawBoxMesh();

	positionXYZ = glm::vec3(mainTrack2X - railGaugeHalf, railY, mainTrackCenterZ);
	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	m_basicMeshes->DrawBoxMesh();

	positionXYZ = glm::vec3(mainTrack2X + railGaugeHalf, railY, mainTrackCenterZ);
	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	m_basicMeshes->DrawBoxMesh();

	SetShaderMaterial("woodMaterial");
	SetShaderColor(0.30f, 0.20f, 0.12f, 1.0f);

	for (float z = mainTrackStartZ; z <= mainTrackEndZ; z += 1.6f)
	{
		scaleXYZ = glm::vec3(1.95f, tieHeight, 0.24f);

		positionXYZ = glm::vec3(mainTrack1X, tieY, z);
		SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
		m_basicMeshes->DrawBoxMesh();

		positionXYZ = glm::vec3(mainTrack2X, tieY, z);
		SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
		m_basicMeshes->DrawBoxMesh();
	}

	// Roadway surfaces to better match the industrial rail yard layout
	scaleXYZ = glm::vec3(3.6f, 0.05f, 150.0f);
	positionXYZ = glm::vec3(-16.5f, -1.40f, -8.0f);
	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	SetShaderMaterial("groundMaterial");
	SetShaderColor(0.32f, 0.32f, 0.32f, 1.0f);
	m_basicMeshes->DrawBoxMesh();

	scaleXYZ = glm::vec3(3.0f, 0.05f, 48.0f);
	positionXYZ = glm::vec3(-29.8f, -1.40f, 69.0f);
	SetTransformations(scaleXYZ, 0.0f, -32.0f, 0.0f, positionXYZ);
	SetShaderMaterial("groundMaterial");
	SetShaderColor(0.30f, 0.30f, 0.30f, 1.0f);
	m_basicMeshes->DrawBoxMesh();

	// Main building for an established industrial setting
	// Provides a large textured background structure
	scaleXYZ = glm::vec3(17.0f, 5.0f, 4.0f);
	positionXYZ = glm::vec3(-22.5f, 1.0f, 22.0f);
	SetTransformations(scaleXYZ, 0.0f, 90.0f, 0.0f, positionXYZ);
	SetShaderMaterial("buildingMaterial");
	SetShaderTexture("mainBuilding");
	SetTextureUVScale(2.2f, 2.0f);
	m_basicMeshes->DrawBoxMesh();

	// Silo as a vertical cylindrical structure to add
	// shape variation and depth to the background
	scaleXYZ = glm::vec3(8.6f, 8.6f, 8.6f);
	positionXYZ = glm::vec3(-31.5f, -1.0f, 44.0f);
	SetTransformations(scaleXYZ, 0.0f, 0.0f, 0.0f, positionXYZ);
	SetShaderMaterial("buildingMaterial");
	SetShaderTexture("siloTexture");
	SetTextureUVScale(1.0f, 1.0f);
	m_basicMeshes->DrawCylinderMesh(true, true, true);

	// Compute reusable X positions for the occupied yard tracks
	float track1 = firstTrackX + (1 * trackSpacing);
	float track2 = firstTrackX + (2 * trackSpacing);
	float track3 = firstTrackX + (3 * trackSpacing);
	float track4 = firstTrackX + (4 * trackSpacing);
	float track5 = firstTrackX + (5 * trackSpacing);
	float track7 = firstTrackX + (7 * trackSpacing);
	float track8 = firstTrackX + (8 * trackSpacing);

	// Place parked yard equipment across selected storage tracks
	// to add liveliness and visual interest to the scene, while also providing
	// a variety of freight car types to better demonstrate the 3D composition
	drawTankCar(track1, 30.0f, true, "freightMetalTexture", glm::vec3(0.10f, 0.10f, 0.10f));
	drawTankCar(track1, 20.8f, true, "freightMetalTexture", glm::vec3(0.10f, 0.10f, 0.10f));
	drawTankCar(track1, 11.6f, true, "freightMetalTexture", glm::vec3(0.10f, 0.10f, 0.10f));

	drawBoxCar(track2, 29.5f, "freightMetalThirdTexture");
	drawBoxCar(track2, 20.3f, "freightMetalThirdTexture");
	drawBoxCar(track2, 11.1f, "freightMetalThirdTexture");

	drawTankCar(track3, 24.0f, false, "", glm::vec3(0.05f, 0.05f, 0.05f));
	drawTankCar(track3, 14.8f, false, "", glm::vec3(0.05f, 0.05f, 0.05f));
	drawTankCar(track3, 5.6f, false, "", glm::vec3(0.05f, 0.05f, 0.05f));

	drawBoxCar(track4, 26.0f, "freightMetalThirdTexture");
	drawTankCar(track4, 16.8f, false, "", glm::vec3(0.07f, 0.07f, 0.07f));
	drawBoxCar(track4, 7.6f, "freightMetalThirdTexture");

	drawTankCar(track5, 22.0f, true, "freightMetalTexture", glm::vec3(0.10f, 0.10f, 0.10f));
	drawTankCar(track5, 12.8f, true, "freightMetalTexture", glm::vec3(0.10f, 0.10f, 0.10f));

	drawTankCar(track7, -2.0f, false, "", glm::vec3(0.06f, 0.06f, 0.06f));
	drawTankCar(track7, -11.2f, false, "", glm::vec3(0.06f, 0.06f, 0.06f));

	drawBoxCar(track8, -6.0f, "freightMetalThirdTexture");
	drawBoxCar(track8, -15.2f, "freightMetalThirdTexture");

	// Place the active mainline consist separately so it reads
	// as the focal train movement path within the scene
	drawCSXEngine(26.0f, 42.0f);
	drawBoxCar(26.0f, 30.5f, "freightMetalThirdTexture");
	drawTankCar(26.0f, 21.3f, true, "freightMetalTexture", glm::vec3(0.10f, 0.10f, 0.10f));
	drawBoxCar(26.0f, 12.1f, "freightMetalThirdTexture");
	drawTankCar(26.0f, 2.9f, false, "", glm::vec3(0.06f, 0.06f, 0.06f));
}
